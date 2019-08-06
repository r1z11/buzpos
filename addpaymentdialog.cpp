#include "addpaymentdialog.h"
#include "ui_addpaymentdialog.h"
#include "dbconnection.h"

DBConnection apdcon;

AddPaymentDialog::AddPaymentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPaymentDialog)
{
    ui->setupUi(this);

    QDate currentDate = QDate::currentDate();
    ui->dateEdit->setDate(currentDate);

    apdcon.db = QSqlDatabase::database("buz");

    if(apdcon.isDbOpen()){
        //payments model
        apdcon.pmodel = new QSqlTableModel(this, apdcon.db);
        apdcon.pmodel->setTable("payments");
        apdcon.pmodel->select();

        apdcon.pmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        //add entries to customer name comboBox
        apdcon.querymodel = new QSqlQueryModel();
        apdcon.querymodel->setQuery("SELECT DISTINCT c_name FROM sales", apdcon.db);

        ui->comboBox_customer->setModel(apdcon.querymodel);
        ui->comboBox_customer->setModelColumn(0);
    }
}

AddPaymentDialog::~AddPaymentDialog()
{
    delete ui;
}

/*
Close dialog
*/
void AddPaymentDialog::on_pushButton_2_clicked()
{
    AddPaymentDialog::close();
}

/*
Add new payment
*/
void AddPaymentDialog::on_pushButton_clicked()
{
    QString customer = ui->comboBox_customer->currentText();
    int amount = ui->lineEdit_2->text().toInt();
    QDate date = ui->dateEdit->date();
    QString receiptno = ui->lineEdit_receipt->text();

    int row = apdcon.pmodel->rowCount();

    if(customer != NULL && amount > 0 && !date.isNull() && receiptno != NULL) {
        if(apdcon.pmodel->insertRows(row, 1)){
            apdcon.pmodel->setData(apdcon.pmodel->index(row, 2), customer);
            apdcon.pmodel->setData(apdcon.pmodel->index(row, 4), date);
            apdcon.pmodel->setData(apdcon.pmodel->index(row, 3), amount);
            apdcon.pmodel->setData(apdcon.pmodel->index(row, 1), receiptno);

            apdcon.pmodel->submitAll();

            AddPaymentDialog::close();

            QMessageBox::information(this, "Success!",
                                     "The payment was added successfully! \nPlease refresh to view the entry",
                                     QMessageBox::Close);
        }else{

            QMessageBox::warning(this, "Sorry!",
                                 "The payment was unsuccessful.",
                                 QMessageBox::Close);
        }
    }else{

        QMessageBox::warning(this, "Error!",
                             "Some fields have not been entered.",
                             QMessageBox::Close);
    }
}
