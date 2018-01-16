#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "dbconnection.h"
#include "passchangedialog.h"
#include "adduserdialog.h"
#include "addproductdialog.h"

DBConnection setcon;
int selecteduser;
static int selectedproduct;

//general settings variables
QString bizname, phno, address, currency, tax;
bool b=false, p=false, a=false, c=false, t=false;

PassChangeDialog *psd;

void saveGenSettings();

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    //set the general tab as the first page
    ui->stackedWidget->setCurrentIndex(0);

    setcon.db = QSqlDatabase::database("buz");

    //populate tables if db connection is open
    if(setcon.isDbOpen()){

        //users table
        setcon.usmodel = new QSqlTableModel(this, setcon.db);

        //refresh
        refreshUsers();

        //products table model
        setcon.psmodel = new QSqlTableModel(this, setcon.db);
        setcon.psmodel->setTable("products");
        setcon.psmodel->select();

        //setup the products table headers
        setcon.psmodel->setHeaderData(1, Qt::Horizontal, tr("Product name"));
        setcon.psmodel->setHeaderData(2, Qt::Horizontal, tr("Price"));
        setcon.psmodel->setHeaderData(3, Qt::Horizontal, tr("Quantity"));

        setcon.psmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        ui->psTableView->setModel(setcon.psmodel);
        ui->psTableView->hideColumn(0); // don't show uid
        ui->psTableView->hideColumn(4); // don't show sku
        ui->psTableView->hideColumn(5); // don't show last modified

        ui->psTableView->horizontalHeader()->show();
        ui->psTableView->show();

        //settings table model
        setcon.smodel = new QSqlTableModel(this, setcon.db);
        setcon.smodel->setTable("settings");
        setcon.smodel->select();
        setcon.smodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        //set values for general settings
        QString bizname = setcon.smodel->data(setcon.smodel->index(0,0)).toString();
        ui->lineEdit_biz->setText(bizname);

        QString address = setcon.smodel->data(setcon.smodel->index(0,1)).toString();
        ui->textEdit_address->setText(address);

        QString phone = setcon.smodel->data(setcon.smodel->index(0,4)).toString();
        ui->lineEdit_phone->setText(phone);

        QString tax = setcon.smodel->data(setcon.smodel->index(0,6)).toString();
        ui->lineEdit_tax->setText(tax);

        QString currency = setcon.smodel->data(setcon.smodel->index(0,7)).toString();

        //get currencies
        QSqlQuery query(setcon.db);
        query.exec("SELECT currency FROM currencies");

        while (query.next()) {

            QString currency = query.value(0).toString();
            ui->comboBox_currency->addItem(currency);
        }

        int index = ui->comboBox_currency->findText(currency);
        ui->comboBox_currency->setCurrentIndex(index);

    }

    //get current branch
    branch = setcon.getBranch();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

/*
Settings navigation
*/
void SettingsDialog::on_listWidget_clicked(const QModelIndex &index)
{
    //show matching stackwidget page
    switch(index.row()){
    case 0:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case 1:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case 2:
        ui->stackedWidget->setCurrentIndex(2);
        break;
    default:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    }
}

/*
Delete user
*/
void SettingsDialog::on_pushButton_5_clicked()
{
    setcon.usmodel->removeRows(selecteduser, 1);
}

/*
Get the selected user
*/
void SettingsDialog::on_usersTableView_clicked(const QModelIndex &index)
{
    psd = new PassChangeDialog();

    //get the selected user row
    selecteduser = index.row();

    psd->passrow = selecteduser;

    psd->origpass = setcon.usmodel->data(setcon.usmodel->index(selecteduser,3)).toString();
    psd->fullname = setcon.usmodel->data(setcon.usmodel->index(selecteduser,1)).toString();

}

/*
Open change password dialog
*/
void SettingsDialog::on_changePassButton_clicked()
{
    psd = new PassChangeDialog();

    if(psd->fullname != NULL){

        psd->show();

    }else{
        QMessageBox::information(this, "Error!",
                                 "No user selected.",
                                 QMessageBox::Close);
    }
}

/*
Add new user
*/
void SettingsDialog::on_pushButton_4_clicked()
{
    AddUserDialog *au = new AddUserDialog();
    au->show();
}

/*
Add new product
*/
void SettingsDialog::on_pushButton_7_clicked()
{
    AddProductDialog *apd = new AddProductDialog();
    apd->show();
}

/*
Get the selected product
*/
void SettingsDialog::on_psTableView_clicked(const QModelIndex &index)
{
    selectedproduct = index.row();
}

/*
Save all changes
*/
void SettingsDialog::on_pushButton_3_clicked()
{
    //save general settings
    saveGenSettings();
    setcon.smodel->submitAll();

    //save user table changes
    setcon.usmodel->submitAll();

    //save products table changes
    setcon.psmodel->submitAll();
}

/*
Close the settings dialog
*/
void SettingsDialog::on_pushButton_2_clicked()
{
    SettingsDialog::close();
}


/*
Save all settings and close dialog box
*/
void SettingsDialog::on_pushButton_clicked()
{
    //save general settings
    saveGenSettings();
    setcon.smodel->submitAll();

    //save user table changes
    setcon.usmodel->submitAll();

    //save products table changes
    setcon.psmodel->submitAll();

    //close dialog after
    SettingsDialog::close();

}


/*
Refresh the users
*/
void SettingsDialog::on_pushButton_9_clicked()
{
    refreshUsers();
}

/*
Refresh function
*/
void SettingsDialog::refreshUsers()
{
    setcon.usmodel->setTable("users");
    setcon.usmodel->select();

    //setup the users table headers
    setcon.usmodel->setHeaderData(4, Qt::Horizontal, tr("Account"));
    setcon.usmodel->setHeaderData(1, Qt::Horizontal, tr("Full name"));
    setcon.usmodel->setHeaderData(2, Qt::Horizontal, tr("Username"));

    setcon.usmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->usersTableView->setModel(setcon.usmodel);
    ui->usersTableView->hideColumn(0); // don't show uid
    ui->usersTableView->hideColumn(3); // don't show password
    ui->usersTableView->hideColumn(5); // don't show hash
    ui->usersTableView->hideColumn(6); // don't show isloggedin

    ui->usersTableView->horizontalHeader()->show();
    ui->usersTableView->show();
}

/*
Refresh products
*/
void SettingsDialog::on_pushButton_10_clicked()
{
    setcon.psmodel->setTable("products");
    setcon.psmodel->select();

    //setup the users table headers
    setcon.psmodel->setHeaderData(1, Qt::Horizontal, tr("Product name"));
    setcon.psmodel->setHeaderData(2, Qt::Horizontal, tr("Price"));
    setcon.psmodel->setHeaderData(3, Qt::Horizontal, tr("Stock"));

    setcon.psmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->psTableView->setModel(setcon.psmodel);
    ui->psTableView->hideColumn(0); // don't show uid
    ui->psTableView->hideColumn(4); // don't show sku
    ui->psTableView->hideColumn(5); // don't show last modified

    ui->psTableView->horizontalHeader()->show();
    ui->psTableView->show();
}

/*
Bisness name
*/
void SettingsDialog::on_lineEdit_biz_editingFinished()
{/*
    b=true;
    bizname = ui->lineEdit_biz->text();*/
}

/*
Phone number
*/
void SettingsDialog::on_lineEdit_phone_editingFinished()
{/*
    p=true;
    phno = ui->lineEdit_phone->text();*/
}

/*
Currency
*/
void SettingsDialog::on_comboBox_currency_currentIndexChanged(int index)
{/*
    c=true;
    selectedtax = index;
    currency = ui->comboBox_currency->currentText();*/
}

/*
Tax rate
*/
void SettingsDialog::on_lineEdit_tax_editingFinished()
{/*
    t=true;
    tax = ui->lineEdit_tax->text().toInt();*/
}

/*
Save all general settings
*/
void SettingsDialog::saveGenSettings()
{
    bizname = ui->lineEdit_biz->text();
    setcon.smodel->setData(setcon.smodel->index(0,0), bizname);

    phno = ui->lineEdit_phone->text();
    setcon.smodel->setData(setcon.smodel->index(0,4), phno);

    address = ui->textEdit_address->toPlainText();
    setcon.smodel->setData(setcon.smodel->index(0,1), address);

    currency = ui->comboBox_currency->currentText();
    setcon.smodel->setData(setcon.smodel->index(0,7), currency);

    tax = ui->lineEdit_tax->text();
    setcon.smodel->setData(setcon.smodel->index(0,6), tax);
}

/*
Address
*/
void SettingsDialog::on_textEdit_address_textChanged()
{/*
    a=true;
    address = ui->textEdit_address->toPlainText();*/
}

//Delete product
void SettingsDialog::on_pushButton_8_clicked()
{
    QModelIndexList selectedUsers = ui->psTableView->selectionModel()->selectedIndexes();

    if(selectedUsers.size() > 0){
        for(int i=0; i < selectedUsers.size(); i++){
            setcon.psmodel->removeRow(selectedUsers.at(i).row());
        }
        setcon.psmodel->submitAll();
        QMessageBox::information(this, "Success!",
                                 "Product(s) deleted.",
                                 QMessageBox::Close);
    } else {
        QMessageBox::warning(this, "Error!",
                                 "No product(s) selected.",
                                 QMessageBox::Close);
    }
}
