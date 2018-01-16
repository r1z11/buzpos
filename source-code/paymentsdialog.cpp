#include "paymentsdialog.h"
#include "ui_paymentsdialog.h"
#include "addpaymentdialog.h"


PaymentsDialog::PaymentsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentsDialog)
{
    ui->setupUi(this);

    QDate today = QDate::currentDate();
    ui->dateEdit_filterP->setDate(today);

    pcon.db = QSqlDatabase::database("buz");

    //populate tables if db connection is open
    if(pcon.isDbOpen()){

        //payments table
        pcon.pmodel = new QSqlTableModel(this, pcon.db);
        pcon.pmodel->setTable("payments");
        pcon.pmodel->select();
        setPaymentHeaders();

        //add auto complete to the search form
        searchcompleter = new QCompleter(pcon.pmodel, this);
        searchcompleter->setCompletionColumn(2);
        searchcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit_searchpts->setCompleter(searchcompleter);
    }
}

PaymentsDialog::~PaymentsDialog()
{
    delete ui;
}

/*
Search payments on return pressed
*/
void PaymentsDialog::on_lineEdit_searchpts_returnPressed()
{
    completion = searchcompleter->currentCompletion();
    searchstr = ui->lineEdit_searchpts->text();

    if(completion != NULL)
        search_customers(completion);
    else
        search_customers(searchstr);
}

/*
Search button
*/
void PaymentsDialog::on_pushButton_searchpts_clicked()
{
    //search customers
    QString searchstr = ui->lineEdit_searchpts->text();

    search_customers(searchstr);
}

/*
Search payments function
*/
void PaymentsDialog::search_customers(QString customer)
{
    pcon.pmodel->setTable("payments");
    pcon.pmodel->setFilter("c_name LIKE '%"+customer+"%'");
    pcon.pmodel->select();

    setPaymentHeaders();
}

/*
Set payment table column headers
*/
void PaymentsDialog::setPaymentHeaders()
{
    //setup the payments table headers
    pcon.pmodel->setHeaderData(1, Qt::Horizontal, tr("Receipt No"));
    pcon.pmodel->setHeaderData(2, Qt::Horizontal, tr("Customer Name"));
    pcon.pmodel->setHeaderData(4, Qt::Horizontal, tr("Date"));
    pcon.pmodel->setHeaderData(3, Qt::Horizontal, tr("Amount"));

    pcon.pmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView_payments->setModel(pcon.pmodel);
    ui->tableView_payments->hideColumn(0); // don't show id

    ui->tableView_payments->horizontalHeader()->show();
    ui->tableView_payments->show();
}

/*
Add payment
*/
void PaymentsDialog::on_pushButton_makepts_clicked()
{
    AddPaymentDialog *apd = new AddPaymentDialog();
    apd->show();
}

/*
Refresh
*/
void PaymentsDialog::on_pushButton_refresh_clicked()
{
    //refresh payments table
    pcon.pmodel = new QSqlTableModel(this, pcon.db);
    pcon.pmodel->setTable("payments");
    pcon.pmodel->select();
    setPaymentHeaders();
}

/*
Filter payments by date
*/
void PaymentsDialog::on_pushButton_filterP_clicked()
{
    QDate date = ui->dateEdit_filterP->date();
    QString datestr = date.toString("yyyy/MM/dd");

    pcon.pmodel->setTable("payments");
    pcon.pmodel->setFilter("date = '"+datestr+"'");
    pcon.pmodel->select();

    setPaymentHeaders();
}

//Delete payment
void PaymentsDialog::on_pushButton_delPaymt_clicked()
{
    QStringList payment_ids;
    QSqlQuery query(pcon.db);

    QModelIndexList selection = ui->tableView_payments->selectionModel()->selectedRows();

    if(!selection.empty()){
        for(int i=0; i<selection.count(); i++){
            payment_ids.append(selection.at(i).data().toString());
            qDebug() << "Payment ID "+QString::number(i)+" is "+payment_ids.at(i);
        }

        if(!payment_ids.isEmpty()) {

            for(int i=0; i<payment_ids.length(); i++)
            {
                query.prepare(QString("DELETE FROM payments WHERE id = :id "));
                query.bindValue(":id", payment_ids.at(i));
                query.exec();
            }
            //refresh payments table
            pcon.pmodel = new QSqlTableModel(this, pcon.db);
            pcon.pmodel->setTable("payments");
            pcon.pmodel->select();
            setPaymentHeaders();
        }
    } else {
        QMessageBox::warning(this, "No item selected",
                             "Please select an item to delete.", QMessageBox::Close);
    }
}
