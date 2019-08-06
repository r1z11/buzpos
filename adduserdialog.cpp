#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "dbconnection.h"

DBConnection aucon;

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    aucon.db = QSqlDatabase::database("buz");

    if(aucon.isDbOpen()){
        //users model
        aucon.usmodel = new QSqlTableModel(this, aucon.db);
        aucon.usmodel->setTable("users");
        aucon.usmodel->select();
        aucon.usmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

/*
Add new user if OK is clicked
*/
void AddUserDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString acc = ui->comboBox->currentText();
    QString name = ui->lineEdit->text();
    QString username = ui->lineEdit_2->text();
    QString pass = ui->lineEdit_3->text();
    QString pass2 = ui->lineEdit_4->text();

    bool exists = false;
    exists = aucon.userExists(username);

    int row = aucon.usmodel->rowCount();

    if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Ok) ){

        if(exists == 0){

            if(pass == pass2){

                if(aucon.usmodel->insertRows(row, 1)){

                    aucon.usmodel->setData(aucon.usmodel->index(row, 4), acc);
                    aucon.usmodel->setData(aucon.usmodel->index(row, 2), username);
                    aucon.usmodel->setData(aucon.usmodel->index(row, 3), pass);
                    aucon.usmodel->setData(aucon.usmodel->index(row, 1), name);

                    aucon.usmodel->submitAll();

                    QMessageBox::information(this, "Success!",
                                             "The user was added successfully.",
                                             QMessageBox::Close);
                }else{
                    QMessageBox::warning(this, "Database error!",
                                         "Failed to make changes to database.",
                                         QMessageBox::Close);
                }

            }else{

                QMessageBox::warning(this, "Password error!",
                                     "The passwords you entered do not match.",
                                     QMessageBox::Close);
            }

        }else{
            QMessageBox::warning(this, "Error!",
                                 "The username already exists.",
                                 QMessageBox::Close);
        }

    }else{
        AddUserDialog::close();
    }
}

void AddUserDialog::on_buttonBox_accepted()
{
    //
}
