#include "customernamedialog.h"
#include "ui_customernamedialog.h"
#include <QDebug>

//old customer is set to true because existing customer is checked by default
bool oldc = true, newc = false;

CustomerNameDialog::CustomerNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerNameDialog)
{
    ui->setupUi(this);

    ui->lineEdit_name->setDisabled(true);

    cdcon.db = QSqlDatabase::database("buz");

    //credit sales model
    cdcon.csdmodel = new QSqlTableModel(this, cdcon.db);

    cdcon.csdmodel->setTable("sales");
    cdcon.csdmodel->select();

    cdcon.csdmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //add entries to customer name comboBox
    cdcon.querymodel = new QSqlQueryModel();
    cdcon.querymodel->setQuery("SELECT DISTINCT c_name FROM sales", cdcon.db);

    ui->comboBox_name->setModel(cdcon.querymodel);
    ui->comboBox_name->setModelColumn(0);
}

CustomerNameDialog::~CustomerNameDialog()
{
    delete ui;
}

/*
Get the customer name
*/
QString CustomerNameDialog::getCustomer()
{
    QString customer;

    if(oldc){
        customer = ui->comboBox_name->currentText();
        return customer;
    }else{
        customer = ui->lineEdit_name->text();
        return customer;
    }
}

/*
Old customer toggled
*/
void CustomerNameDialog::on_radioButton_old_toggled(bool checked)
{
    if(checked){
        oldc = true;
        newc = false;
        ui->radioButton_new->setChecked(false);
        ui->lineEdit_name->setDisabled(true);
    }else{
        newc = true;
        oldc = false;
        ui->radioButton_new->setChecked(true);
        ui->lineEdit_name->setDisabled(false);
    }
}

/*
New customer toggled
*/
void CustomerNameDialog::on_radioButton_new_toggled(bool checked)
{
    if(checked){
        newc = true;
        oldc = false;
        ui->radioButton_old->setChecked(false);
        ui->comboBox_name->setDisabled(true);
    }else{
        oldc = true;
        newc = false;
        ui->radioButton_old->setChecked(true);
        ui->comboBox_name->setDisabled(false);
    }
}

/*
Close dialog
*/
void CustomerNameDialog::on_pushButton_cancel_clicked()
{
    CustomerNameDialog::close();
}

/*
Ok clicked, save credit sale
*/
void CustomerNameDialog::on_pushButton_ok_clicked()
{
    QString customername = getCustomer();

    QStringList products, qtys;

    QString product;
    int qty, rate, amt;
    QSqlQuery query(cdcon.db);
    QString credit = "credit";
    double discount = 0;
    double taxrate = cdcon.getTax();

    for(int i=0; i<currentorder->rowCount(); i++)
    {
        product = currentorder->data(currentorder->index(i,4)).toString();
        products.append(product);

        qty = currentorder->data(currentorder->index(i,5)).toDouble();
        qtys.append(QString::number(qty));

        rate = currentorder->data(currentorder->index(i,6)).toDouble();
        amt = qty * rate;
        QDate date = QDate::currentDate();

        query.prepare(QString("INSERT INTO sales (type, invoiceno, c_name, product, qty, price, discount, tax, amt, date) VALUES(:type, :invno, :cname, :product, "
                              ":qty, :rate, :discount, :tax, :amt, :date) "));
        query.bindValue(":type", credit);
        query.bindValue(":invno", invno);
        query.bindValue(":cname", customername);
        query.bindValue(":product", product);
        query.bindValue(":qty", qty);
        query.bindValue(":rate", rate);
        query.bindValue(":discount", discount);
        query.bindValue(":tax", taxrate);
        query.bindValue(":amt", amt);
        query.bindValue(":date", date);
        query.exec();
    }

    updateStock(products, qtys);

    QMessageBox::information(this, "Success!",
                             "Credit order added successfully!", QMessageBox::Close);

    //clear current order
//    int numrows = currentorder->rowCount();
//    currentorder->removeRows(0, numrows);

    CustomerNameDialog::close();
}

//Stock management
void CustomerNameDialog::updateStock(QStringList products, QStringList qtys)
{
    QSqlQuery query(cdcon.db);
    for(int i=0; i<products.size(); i++)
    {
        query.prepare(QString("UPDATE products SET qty = qty - :i  WHERE p_name = :product"));
        query.bindValue(":product", products.at(i));
        query.bindValue(":i", qtys.at(i));
        query.exec();
    }
}
