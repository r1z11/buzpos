#include "addproductdialog.h"
#include "ui_addproductdialog.h"
#include "dbconnection.h"

DBConnection apcon;

AddProductDialog::AddProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);

    apcon.db = QSqlDatabase::database("buz");

    if(apcon.isDbOpen()){
        //products model
        apcon.psmodel = new QSqlTableModel(this, apcon.db);
        apcon.psmodel->setTable("products");
        apcon.psmodel->select();
        apcon.psmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}

/*
Accept / Reject
*/
void AddProductDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString pname = ui->lineEdit->text();

    int price = ui->lineEdit_2->text().toInt();

    int stock = ui->spinBox_2->text().toInt();

    bool exists = false;
    exists = apcon.productExists(pname);

    int row = apcon.psmodel->rowCount();

    if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Ok) )
    {

        if(exists == 0){

            if(apcon.psmodel->insertRows(row, 1)){

                apcon.psmodel->setData(apcon.psmodel->index(row, 1), pname);
                apcon.psmodel->setData(apcon.psmodel->index(row, 2), price);
                apcon.psmodel->setData(apcon.psmodel->index(row, 3), stock);

                apcon.psmodel->submitAll();

                QMessageBox::information(this, "Success!",
                                         "The product was added successfully.",
                                         QMessageBox::Close);
            }else{
                QMessageBox::warning(this, "Database error!",
                                     "Failed to make changes to database.",
                                     QMessageBox::Close);
            }

        }else{
            QMessageBox::warning(this, "Error!",
                                 "The product already exists.",
                                 QMessageBox::Close);
        }

    }else{
        AddProductDialog::close();
    }
}
