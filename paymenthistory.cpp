#include "paymenthistory.h"
#include "ui_paymenthistory.h"

PaymentHistory::PaymentHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentHistory)
{
    ui->setupUi(this);

    phcon.db = QSqlDatabase::database("buz");

    //set current date on date filters
    QDate today = QDate::currentDate();
    ui->dateEdit_pfrom->setDate(today);
    ui->dateEdit_pto->setDate(today);
}

PaymentHistory::~PaymentHistory()
{
    delete ui;
}

void PaymentHistory::getPayments(QString customer_name)
{
    //    //populate table if db connection is open
    if(phcon.isDbOpen()){

        //products table
        phcon.pmodel = new QSqlTableModel(this, phcon.db);

        phcon.pmodel->setTable("payments");
        phcon.pmodel->setFilter("c_name = '"%customer_name%"'");
        phcon.pmodel->select();

        setupTable();
    }
}

void PaymentHistory::setupTable()
{
    //setup the payment history table headers
    phcon.pmodel->setHeaderData(1, Qt::Horizontal, tr("Invoice No"));
    phcon.pmodel->setHeaderData(2, Qt::Horizontal, tr("Name"));
    phcon.pmodel->setHeaderData(3, Qt::Horizontal, tr("Amount"));
    phcon.pmodel->setHeaderData(4, Qt::Horizontal, tr("Date"));

    phcon.pmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView_paymentHistory->setModel(phcon.pmodel);
    ui->tableView_paymentHistory->hideColumn(0); // don't show the id

    ui->tableView_paymentHistory->horizontalHeader()->show();
    ui->tableView_paymentHistory->show();
}

//Filter by date
void PaymentHistory::on_pushButton_dateFilter_clicked()
{
    QDate from = ui->dateEdit_pfrom->date();
    QDate to = ui->dateEdit_pto->date();

    phcon.pmodel->setTable("payments");
    phcon.pmodel->setFilter("date > '"%from.toString("yyyy/MM/dd")%"' AND < '"%to.toString("yyyy/MM/dd"));
    phcon.pmodel->select();

    setupTable();
}

//Delete payment
void PaymentHistory::on_pushButton_pDelete_clicked()
{
    //
}
