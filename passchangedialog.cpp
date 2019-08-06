#include "passchangedialog.h"
#include "ui_passchangedialog.h"
#include "dbconnection.h"
#include <QDebug>

DBConnection cpcon;
int PassChangeDialog::passrow;
QString PassChangeDialog::fullname;
QString PassChangeDialog::origpass;

PassChangeDialog::PassChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassChangeDialog)
{
    ui->setupUi(this);

    cpcon.db = QSqlDatabase::database("buz");

    this->setWindowTitle("Change password for "+fullname);

    if(cpcon.isDbOpen()){
        //users table
        cpcon.usmodel = new QSqlTableModel(this, cpcon.db);
        cpcon.usmodel->setTable("users");
        cpcon.usmodel->select();

        cpcon.usmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

PassChangeDialog::~PassChangeDialog()
{
    delete ui;
}

/*
Change password if OK is clicked
*/
void PassChangeDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        //get old password
        QString oldpass = ui->oldPassLineEdit->text();

        //get new password
        QString newpass = ui->newPassLineEdit->text();
        QString newpass2 = ui->newPassLineEdit_2->text();

        if(cpcon.isDbOpen()){

            //check if old password correct
            if(oldpass == origpass){
                if(newpass == newpass2){

                    QModelIndex index = cpcon.usmodel->index(passrow, 3);
                    cpcon.usmodel->setData(index, newpass);
                    cpcon.usmodel->submitAll();

                    QMessageBox::information(this, "Success!",
                                             "Successfully changed password for "+fullname,
                                             QMessageBox::Close);

                }else{

                    QMessageBox::warning(this, "Password error!",
                                         "The new passwords you entered do not match.",
                                         QMessageBox::Close);
                }
            }else{

                QMessageBox::warning(this, "Password error!",
                                     "The old password you entered is incorrect.",
                                     QMessageBox::Close);
            }

        }

    }else{
        PassChangeDialog::close();
    }
}
