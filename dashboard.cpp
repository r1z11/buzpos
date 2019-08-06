#include "dashboard.h"
#include "ui_dashboard.h"
#include "settingsdialog.h"
#include "helpdialog.h"
#include "paymentsdialog.h"
#include "cashsalesdialog.h"
#include "creditsalesdialog.h"
#include "allreportsdialog.h"
#include "customernamedialog.h"
#include "accountsdialog.h"
#include <QDebug>
#include <QCompleter>

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    dbcon.db = QSqlDatabase::database("buz");

    //populate table if db connection is open
    if(dbcon.isDbOpen()){

        //products table
        dbcon.model = new QSqlTableModel(this, dbcon.db);

        dbcon.model->setTable("products");
        dbcon.model->select();

        setProductHeaders();

        ui->tableView_2->horizontalHeader()->show();

        ui->tableView_2->show();

        //add auto complete to the search form
        searchcompleter = new QCompleter(dbcon.model, this);
        searchcompleter->setCompletionColumn(1);
        searchcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->searchLineEdit->setCompleter(searchcompleter);

        //current order table model
        dbcon.comodel = new QSqlTableModel(this, dbcon.db);
        dbcon.comodel->setTable("sales");

        //setup the current order table headers
        dbcon.comodel->setHeaderData(4, Qt::Horizontal, tr("Product name"));
        dbcon.comodel->setHeaderData(6, Qt::Horizontal, tr("Price"));
        dbcon.comodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));

        //set price and quantity column as editable

        dbcon.comodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        ui->tableView->setModel(dbcon.comodel);
        ui->tableView->hideColumn(0); // don't show the id
        ui->tableView->hideColumn(1); // don't show the type
        ui->tableView->hideColumn(2); // don't show the invoiceno
        ui->tableView->hideColumn(3); // don't show the customer name
        ui->tableView->hideColumn(7); // don't show the discount
        ui->tableView->hideColumn(8); // don't show the tax
        ui->tableView->hideColumn(9); // don't show the amount
        ui->tableView->hideColumn(10); // don't show the date

        //ui->tableView->horizontalHeader()->show();
        ui->tableView->show();

        //get the tax rate
        taxrate = dbcon.getTax();

    }
}

/*
Close dashboard
*/
Dashboard::~Dashboard()
{
    delete ui;
}

/*
Logout
*/
void Dashboard::on_actionLogout_triggered()
{
    //close the dashboard and show login screen
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Logout?",
                                  "Are you sure you want to logout?\n",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        QString user = dbcon.getCurrentUser();
        dbcon.logoutCurrentUser(user);
        Dashboard::close();
    }
}

/*
Add selected items to current order
*/
void Dashboard::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    int rowidx = index.row();
    QString product = dbcon.model->index(rowidx , 1).data().toString();
    int price = dbcon.model->index(rowidx , 2).data().toDouble();
    int qty = 1;

    //insert the row into current order table
    int row = dbcon.comodel->rowCount();

    if(dbcon.comodel->insertRows(row, 1)){
        //check if item already exists before adding it
        dbcon.comodel->setData(dbcon.comodel->index(row, 4), product);
        dbcon.comodel->setData(dbcon.comodel->index(row, 5), qty);
        dbcon.comodel->setData(dbcon.comodel->index(row, 6), price);
    }

    calculate_bill();
}

/*
Open settings dialog
*/
void Dashboard::on_actionSettings_triggered()
{
    SettingsDialog *sd = new SettingsDialog();
    sd->show();
}

/*
Calculate values when current order table is clicked
*/
void Dashboard::on_tableView_clicked(const QModelIndex &index)
{
    selectedrow = index.row();
    calculate_bill();
}

/*
Calculate current order values function
*/
void Dashboard::calculate_bill()
{
    //add up the total items, tax and bill amount
    //no of items
    int items = dbcon.comodel->rowCount();
    QString itemstr = QString::number(items);
    ui->label_itemNo->setText(itemstr);

    int qty, rate, itemamt;
    //each item amount
    for(int i=0; i<items; i++){
        qty = dbcon.comodel->data(dbcon.comodel->index(i,5)).toInt();
        rate = dbcon.comodel->data(dbcon.comodel->index(i,6)).toInt();
        itemamt = qty * rate;
        dbcon.comodel->setData(dbcon.comodel->index(i,9), itemamt);
    }

    //bill amount
    QModelIndex index4;
    int taxrateamt;
    int amt = 0;

    for(int i=0; i<dbcon.comodel->rowCount(); i++){
        index4 = dbcon.comodel->index(i, 9, QModelIndex());
        amt = amt + dbcon.comodel->data(index4).toDouble();
    }

    //calculate taxes
    taxrateamt = taxrate * amt;
    taxrateamt = taxrateamt/100;

    QString taxstr = QString::number(taxrateamt);
    ui->label_tax->setText(taxstr);

    QString amtstr = QString::number(amt);
    ui->label_bill->setText(amtstr);
}

/*
Calculate current order values button
*/
void Dashboard::on_pushButton_3_clicked()
{
    calculate_bill();
}

/*
Remove selected row from current order
*/
void Dashboard::on_removeRowButton_clicked()
{
    dbcon.comodel->removeRows(selectedrow, 1);
    calculate_bill();
}

/*
Open help dialog
*/
void Dashboard::on_actionHelp_topics_triggered()
{
    HelpDialog *hd = new HelpDialog();
    hd->show();
}

/*
Search products on enter
*/
void Dashboard::on_searchLineEdit_returnPressed()
{
    completion = searchcompleter->currentCompletion();
    searchstr = ui->searchLineEdit->text();

    if(completion != NULL)
        search_products(completion);
    else
        search_products(searchstr);
}

/*
Search products on button clicked
*/
void Dashboard::on_pushButton_clicked()
{
    //search products
    QString searchstr = ui->searchLineEdit->text();

    search_products(searchstr);

}

/*
Search products function
*/
void Dashboard::search_products(QString product)
{
    dbcon.model->setTable("products");
    dbcon.model->setFilter("p_name LIKE '%"+product+"%'");
    dbcon.model->select();

    setProductHeaders();
}

/*
Refresh products table
*/
void Dashboard::on_pushButton_2_clicked()
{
    dbcon.model->setTable("products");
    dbcon.model->select();

    setProductHeaders();
}

/*
Set product table column headers
*/
void Dashboard::setProductHeaders()
{
    //setup products table column headers
    dbcon.model->setHeaderData(1, Qt::Horizontal, tr("Product name"));
    dbcon.model->setHeaderData(2, Qt::Horizontal, tr("Price"));
    dbcon.model->setHeaderData(3, Qt::Horizontal, tr("Stock"));

    ui->tableView_2->setModel(dbcon.model);
    ui->tableView_2->hideColumn(0); // don't show the uid
    ui->tableView_2->hideColumn(4); // don't show the sku
    ui->tableView_2->hideColumn(5); // don't show last modified
}

/*
Cash sale
*/
void Dashboard::on_pushButton_8_clicked()
{
    calculate_bill();

    //get invoice number
    QString invno = NULL;
    invno = ui->lineEdit_invoiceno->text();

    int items = ui->label_itemNo->text().toInt();

    if(invno != NULL && items>0){

        QStringList products, qtys;
        QString product;
        QString cash = "cash";
        int qty, rate, amt;
        QSqlQuery query(dbcon.db);
        double discount = 0;

        if(!dbcon.invoiceNoExists(invno)) {

            for(int i=0; i<dbcon.comodel->rowCount(); i++)
            {
                product = dbcon.comodel->data(dbcon.comodel->index(i,4)).toString();
                products.append(product);

                qty = dbcon.comodel->data(dbcon.comodel->index(i,5)).toDouble();
                qtys.append(QString::number(qty));

                rate = dbcon.comodel->data(dbcon.comodel->index(i,6)).toDouble();
                amt = dbcon.comodel->data(dbcon.comodel->index(i,9)).toDouble();
                QDate date = QDate::currentDate();

                query.prepare(QString("INSERT INTO sales (type, invoiceno, product, qty, price, discount, tax, amt, date) VALUES(:type, :invno, :product, "
                                      ":qty, :rate, :discount, :tax, :amt, :date) "));
                query.bindValue(":type", cash);
                query.bindValue(":invno", invno);
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

            //TO-DO -> check if query executed successfully before displaying this message
            QMessageBox::information(this, "Success!",
                                     "Cash order added successfully!", QMessageBox::Close);
            //TO-DO -> clear the current order when close button is clicked
        } else {
            QMessageBox::warning(this, "Sorry",
                                 "That invoice number already exists!\n"
                                 "Please enter another one.", QMessageBox::Close);
        }

    } else{

        QMessageBox::warning(this, "Sorry!",
                             "Some fields have not been filled in.", QMessageBox::Close);
    }
}

/*
Calculate balance
*/
void Dashboard::on_lineEdit_cash_textChanged(const QString &arg1)
{
    int cash = arg1.toInt();
    int amt = ui->label_bill->text().toInt();
    int balance = cash - amt;

    QString balancestr = QString::number(balance);
    ui->label_balance->setText(balancestr);
}

//Stock management
void Dashboard::updateStock(QStringList products, QStringList qtys)
{
    QSqlQuery query(dbcon.db);
    for(int i=0; i<products.size(); i++)
    {
        query.prepare(QString("UPDATE products SET qty = qty - :i  WHERE p_name = :product"));
        query.bindValue(":product", products.at(i));
        query.bindValue(":i", qtys.at(i));
        query.exec();
    }
}

/*
Open payments dialog
*/
void Dashboard::on_actionAll_payments_triggered()
{
    PaymentsDialog *pd = new PaymentsDialog();
    pd->show();
}

/*
Open cash sales
*/
void Dashboard::on_actionCash_sales_triggered()
{
    CashSalesDialog *cs = new CashSalesDialog();
    cs->show();
}

/*
Open Credit sales
*/
void Dashboard::on_actionCredit_sales_triggered()
{
    CreditSalesDialog *csd = new CreditSalesDialog();
    csd->show();
}

/*
Open all reports dialog
*/
void Dashboard::on_actionAll_reports_triggered()
{
    AllReportsDialog *ard = new AllReportsDialog();
    ard->show();
}

/*
Credit sale, open customer dialog
*/
void Dashboard::on_pushButton_7_clicked()
{
    calculate_bill();

    CustomerNameDialog *cnd = new CustomerNameDialog();

    cnd->currentorder = new QSqlTableModel(this, dbcon.db);
    cnd->currentorder = dbcon.comodel;

    cnd->invno = ui->lineEdit_invoiceno->text();

    cnd->items = ui->label_itemNo->text().toInt();

    if(cnd->invno != NULL && cnd->items>0)
    {
        if(!dbcon.invoiceNoExists(ui->lineEdit_invoiceno->text()))
        {
            cnd->show();

        } else{
            QMessageBox::warning(this, "Sorry",
                                 "That invoice number already exists\n"
                                 "Please enter another one", QMessageBox::Close);
        }
    } else{
        QMessageBox::warning(this, "Sorry!",
                             "Please enter the invoice number", QMessageBox::Close);
    }
}

/*
Clear current order
*/
void Dashboard::on_pushButton_6_clicked()
{
    int numrows = dbcon.comodel->rowCount();
    dbcon.comodel->removeRows(0, numrows);

    ui->lineEdit_invoiceno->setText("invoice no");
    ui->label_itemNo->setText("no of items");
    ui->label_tax->setText("total tax");
    ui->label_bill->setText("totall bill amount");
    ui->lineEdit_cash->setText("cash");
}

/*
About Buz POS
*/
void Dashboard::on_actionAbout_Buz_POS_triggered()
{
    QMessageBox::information(this, "About BuzPOS",
                             "Buz Point of Sale was created by Eric Sentongo\n"
                             "Phone No: +256759961228\n"
                             "Email: eric_sentongo@yahoo.com", QMessageBox::Close);
}

/*
Customer accounts dialog
*/
void Dashboard::on_actionCustomer_accounts_triggered()
{
    AccountsDialog *ad = new AccountsDialog();
    ad->show();
}

/*
Current order table activated
*/
void Dashboard::on_tableView_activated(const QModelIndex &index)
{
    //
}

/*
Products table activated
*/
void Dashboard::on_tableView_2_activated(const QModelIndex &index)
{
    //
}
