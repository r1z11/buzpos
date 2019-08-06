#include "accountsdialog.h"
#include "ui_accountsdialog.h"
#include <QDebug>

#include "paymenthistory.h"

AccountsDialog::AccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountsDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    cacon.db = QSqlDatabase::database("buz");

    //populate account table
    setAccountHeaders();

    //add auto complete to the search form
    model = new QSqlQueryModel();
    model->setQuery("SELECT DISTINCT c_name FROM sales", cacon.db);
    searchcompleter = new QCompleter(model, this);
    searchcompleter->setCompletionColumn(0);
    searchcompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_customers->setCompleter(searchcompleter);
}

AccountsDialog::~AccountsDialog()
{
    delete ui;
}

/*
Refresh customer accounts
*/
void AccountsDialog::on_pushButton_refreshAcc_clicked()
{
    setAccountHeaders();
}

/*
Set cash sales table column headers
*/
void AccountsDialog::setAccountHeaders()
{
    QSqlTableModel *querymodel2 = new QSqlTableModel(this, cacon.db);
    querymodel2->setTable("accounts");
    querymodel2->setEditStrategy(QSqlTableModel::OnManualSubmit);

    cacon.querymodel = new QSqlQueryModel();

    cacon.querymodel->setQuery("SELECT sales.c_name AS customer_name, "
                               "COALESCE(SUM(sales.amt),0) AS total_debt,"
                               "COALESCE(SUM(payments.amt),0) AS amount_paid,"
                               "(COALESCE(SUM(sales.amt),0) - COALESCE(SUM(payments.amt),0)) AS balance "
                               "FROM sales "
                               "INNER JOIN payments ON sales.c_name = payments.c_name", cacon.db);

    cacon.querymodel->setHeaderData(0, Qt::Horizontal, tr("Customer name"));
    cacon.querymodel->setHeaderData(1, Qt::Horizontal, tr("Total debt"));
    cacon.querymodel->setHeaderData(2, Qt::Horizontal, tr("Total payments"));
    cacon.querymodel->setHeaderData(3, Qt::Horizontal, tr("Balance"));

    QString zero, one, two, three;
    int rowno = cacon.querymodel->rowCount();

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    for(int i=0; i<rowno; i++){
        zero = cacon.querymodel->index(i, 0).data().toString();
        one = QString("%L1").arg(cacon.querymodel->index(i,1).data().toLongLong());
        two = QString("%L1").arg(cacon.querymodel->index(i,2).data().toLongLong());
        three = QString("%L1").arg(cacon.querymodel->index(i,3).data().toLongLong());

        int row = querymodel2->rowCount();

        if(querymodel2->insertRows(row, 1)){
            querymodel2->setData(querymodel2->index(i, 0), zero);
            querymodel2->setData(querymodel2->index(i, 1), one);
            querymodel2->setData(querymodel2->index(i, 2), two);
            querymodel2->setData(querymodel2->index(i, 3), three);
        }
    }

    ui->tableView_Acc->setModel(cacon.querymodel);
    ui->tableView_Acc->horizontalHeader()->show();
    ui->tableView_Acc->show();
}

/*
Search accounts
*/
void AccountsDialog::search_accounts(QString customername)
{
    QSqlTableModel *querymodel2 = new QSqlTableModel(this, cacon.db);
    querymodel2->setTable("accounts");
    querymodel2->setEditStrategy(QSqlTableModel::OnManualSubmit);

    cacon.querymodel->setQuery("SELECT d.c_name, COALESCE(SUM(w.amt),0) AS TotalDebt,"
                               " COALESCE(SUM(d.amt),0) AS AmountPaid, COALESCE(SUM(d.amt),0) - "
                               "COALESCE(SUM(w.amt),0) AS Balance FROM payments d LEFT JOIN(SELECT "
                               "c_name, COALESCE(SUM(amt),0) amt FROM sales GROUP BY "
                               "c_name) w ON d.c_name = w.c_name LEFT JOIN payments c ON"
                               " d.c_name = c.c_name WHERE d.c_name LIKE '%"+customername+"%'"
                                                                                          "GROUP BY c_name", cacon.db);

    querymodel2->setHeaderData(0, Qt::Horizontal, tr("Customer name"));
    querymodel2->setHeaderData(1, Qt::Horizontal, tr("Total debt"));
    querymodel2->setHeaderData(2, Qt::Horizontal, tr("Total payments"));
    querymodel2->setHeaderData(3, Qt::Horizontal, tr("Balance"));

    QString zero, one, two, three;
    int rowno = cacon.querymodel->rowCount();

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    for(int i=0; i<rowno; i++){
        zero = cacon.querymodel->index(i, 0).data().toString();
        one = QString("%L1").arg(cacon.querymodel->index(i,1).data().toLongLong());
        two = QString("%L1").arg(cacon.querymodel->index(i,2).data().toLongLong());
        three = QString("%L1").arg(cacon.querymodel->index(i,3).data().toLongLong());

        int row = querymodel2->rowCount();

        if(querymodel2->insertRows(row, 1)){
            querymodel2->setData(querymodel2->index(i, 0), zero);
            querymodel2->setData(querymodel2->index(i, 1), one);
            querymodel2->setData(querymodel2->index(i, 2), two);
            querymodel2->setData(querymodel2->index(i, 3), three);
        }
    }

    ui->tableView_Acc->setModel(querymodel2);
    ui->tableView_Acc->horizontalHeader()->show();
    ui->tableView_Acc->show();
}

/*
Search accounts on return pressed
*/
void AccountsDialog::on_lineEdit_customers_returnPressed()
{
    completion = searchcompleter->currentCompletion();
    searchstr = ui->lineEdit_customers->text();

    if(completion != NULL)
        search_accounts(completion);
    else
        search_accounts(searchstr);
}

/*
Search button
*/
void AccountsDialog::on_pushButton_searchAcc_clicked()
{
    //search accounts
    QString searchstr = ui->lineEdit_customers->text();

    search_accounts(searchstr);
}

//Open Payment history
void AccountsDialog::on_pushButton_payHistory_clicked()
{
    QModelIndexList selection = ui->tableView_Acc->selectionModel()->selectedRows();
    QString c_name = "null";

    if(!selection.empty()){
        c_name = selection.at(0).data().toString();
        qDebug() << "Accounts dialog customer name is "+c_name;
    } else {
        QMessageBox::warning(this, "No item selected",
                             "Please select a customer to view payment history.", QMessageBox::Close);
    }

    PaymentHistory *phistory = new PaymentHistory();
    phistory->getPayments(c_name);
    phistory->show();
}
