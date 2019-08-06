#include "creditsalesdialog.h"
#include "ui_creditsalesdialog.h"

CreditSalesDialog::CreditSalesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditSalesDialog)
{
    ui->setupUi(this);

    QDate today = QDate::currentDate();
    ui->dateEdit_filter->setDate(today);

    csdcon.db = QSqlDatabase::database("buz");

    //populate tables if db connection is open
    if(csdcon.isDbOpen()){

        //cash sales table
        csdcon.csdmodel = new QSqlTableModel(this, csdcon.db);
        csdcon.csdmodel->setTable("sales");
        csdcon.csdmodel->setFilter("type='credit'");
        csdcon.csdmodel->select();

        setCreditSalesHeaders();

        //add auto complete to the search form
        searchcompleter = new QCompleter(csdcon.csdmodel, this);
        searchcompleter->setCompletionColumn(3);
        searchcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit_customers->setCompleter(searchcompleter);
    }
}

CreditSalesDialog::~CreditSalesDialog()
{
    delete ui;
}

/*
Set Credit sales headers
*/
void CreditSalesDialog::setCreditSalesHeaders()
{
    csdcon.csdmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    csdcon.csdmodel->setHeaderData(3, Qt::Horizontal, tr("Customer Name"));
    csdcon.csdmodel->setHeaderData(4, Qt::Horizontal, tr("Product Name"));
    csdcon.csdmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    csdcon.csdmodel->setHeaderData(6, Qt::Horizontal, tr("Price"));
    csdcon.csdmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    csdcon.csdmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    csdcon.csdmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView_css->setModel(csdcon.csdmodel);
    ui->tableView_css->hideColumn(0); // don't show uid
    ui->tableView_css->hideColumn(1); // don't show type
    ui->tableView_css->hideColumn(7); // don't show discount
    ui->tableView_css->hideColumn(8); // don't show tax

    ui->tableView_css->horizontalHeader()->show();
    ui->tableView_css->show();
}

/*
Refresh credit sales
*/
void CreditSalesDialog::on_pushButton_refresh_clicked()
{
    csdcon.csdmodel = new QSqlTableModel(this, csdcon.db);
    csdcon.csdmodel->setTable("sales");
    csdcon.csdmodel->setFilter("type='credit'");
    csdcon.csdmodel->select();
    setCreditSalesHeaders();
}

/*
Search button pressed
*/
void CreditSalesDialog::on_pushButton_search_clicked()
{
    QString name = ui->lineEdit_customers->text();
    search_customers(name);
}

/*
Search customers
*/
void CreditSalesDialog::search_customers(QString customer)
{
    csdcon.csdmodel->setTable("sales");
    csdcon.csdmodel->setFilter("c_name LIKE '%"+customer+"%' AND type='credit'");
    csdcon.csdmodel->select();
    setCreditSalesHeaders();
}

/*
Search customers on return pressed
*/
void CreditSalesDialog::on_lineEdit_customers_returnPressed()
{
    completion = searchcompleter->currentCompletion();
    searchstr = ui->lineEdit_customers->text();

    if(completion != NULL)
        search_customers(completion);
    else
        search_customers(searchstr);
}

/*
Filter credit sales by date
*/
void CreditSalesDialog::on_pushButton_filter_clicked()
{
    QDate date = ui->dateEdit_filter->date();
    QString datestr = date.toString("yyyy/MM/dd");

    csdcon.csdmodel = new QSqlTableModel(this, csdcon.db);
    csdcon.csdmodel->setTable("sales");
    csdcon.csdmodel->setFilter("date = '"+datestr+"' AND type='credit'");
    csdcon.csdmodel->select();
    setCreditSalesHeaders();
}
