#include "cashsalesdialog.h"
#include "ui_cashsalesdialog.h"

CashSalesDialog::CashSalesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CashSalesDialog)
{
    ui->setupUi(this);

    //set date filter to current date
    QDate today = QDate::currentDate();
    ui->dateEdit_filterCs->setDate(today);

    cscon.db = QSqlDatabase::database("buz");

    //populate tables if db connection is open
    if(cscon.isDbOpen()){

        //cash sales table
        cscon.csmodel = new QSqlTableModel(this, cscon.db);
        cscon.csmodel->setTable("sales");
        cscon.csmodel->setFilter("type='cash'");
        cscon.csmodel->select();

        setCashSalesHeaders();

        //add auto complete to the search form customer names
        searchcompleter = new QCompleter(cscon.csmodel, this);
        searchcompleter->setCompletionColumn(2);
        searchcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit_searchcs->setCompleter(searchcompleter);
    }
}

CashSalesDialog::~CashSalesDialog()
{
    delete ui;
}

/*
Search invoice nos on return
*/
void CashSalesDialog::on_lineEdit_searchcs_returnPressed()
{
    completion = searchcompleter->currentCompletion();
    searchstr = ui->lineEdit_searchcs->text();

    if(completion != NULL)
        search_invoices(completion);
    else
        search_invoices(searchstr);
}

/*
Search invoice nos
*/
void CashSalesDialog::on_pushButton_searchcs_clicked()
{
    //search invoices
    QString searchstr = ui->lineEdit_searchcs->text();

    search_invoices(searchstr);
}

/*
Search invoices function
*/
void CashSalesDialog::search_invoices(QString invoiceno)
{
    cscon.csmodel->setTable("sales");
    cscon.csmodel->setFilter("invoiceno LIKE '%"+invoiceno+"%' AND type='cash' ");
    cscon.csmodel->select();

    setCashSalesHeaders();
}

/*
Set cash sales table column headers
*/
void CashSalesDialog::setCashSalesHeaders()
{
    cscon.csmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    cscon.csmodel->setHeaderData(4, Qt::Horizontal, tr("Product Name"));
    cscon.csmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    cscon.csmodel->setHeaderData(6, Qt::Horizontal, tr("Price"));
    cscon.csmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    cscon.csmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    cscon.csmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView_cs->setModel(cscon.csmodel);
    ui->tableView_cs->hideColumn(0); // don't show uid
    ui->tableView_cs->hideColumn(1); // don't show type
    ui->tableView_cs->hideColumn(3); // don't show customer
    ui->tableView_cs->hideColumn(7); // don't show discount
    ui->tableView_cs->hideColumn(8); // don't show tax

    ui->tableView_cs->horizontalHeader()->show();
    ui->tableView_cs->show();
}

/*
Refresh cash sales
*/
void CashSalesDialog::on_pushButton_refreshcs_clicked()
{
    cscon.csmodel = new QSqlTableModel(this, cscon.db);
    cscon.csmodel->setTable("sales");
    cscon.csmodel->setFilter("type='cash'");
    cscon.csmodel->select();
    setCashSalesHeaders();
}
/*
Filter cash sales by date
*/
void CashSalesDialog::on_pushButton_filterCs_clicked()
{
    QDate date = ui->dateEdit_filterCs->date();
    QString datestr = date.toString("yyyy-MM-dd");

    cscon.csmodel = new QSqlTableModel(this, cscon.db);
    cscon.csmodel->setTable("sales");
    cscon.csmodel->setFilter("date = '"+datestr+"' AND type='cash' ");
    cscon.csmodel->select();
    setCashSalesHeaders();
}
