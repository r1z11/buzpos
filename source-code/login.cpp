#include "login.h"
#include "ui_login.h"
#include "dbconnection.h"
#include "dashboard.h"
#include "helpdialog.h"
#include "globals.h"

DBConnection con;
QString buz = "buz";

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    con.createConnection(buz);

    //set username if last user didn't logout
    QString user = con.getCurrentUser();

    if(user != NULL){
        ui->userLineEdit->setText(user);
    }
}

/*
Close login form
*/
Login::~Login()
{
    delete ui;
}

/*
Login button
*/
void Login::on_loginButton_clicked()
{
    buzLogin();

}

void Login::on_passLineEdit_returnPressed()
{
    buzLogin();
}

/*
Login function
*/
void Login::buzLogin(){
    if(con.isDbOpen()){
        QString account = ui->accComboBox->currentText();
        QString username = ui->userLineEdit->text();
        QString password = ui->passLineEdit->text();

        QSqlQuery query(con.db);
        query.prepare(QString("SELECT account, username, password FROM users WHERE username = :username "));
        query.bindValue(":username", username);
        query.exec();

        while (query.next()) {
            QString acc = query.value(0).toString();
            QString user = query.value(1).toString();
            QString pass = query.value(2).toString();

            int x = QString::compare(username, user, Qt::CaseInsensitive);

            if(account == acc && x == 0 && password == pass){
                //set current user
                Globals::instance()->setUser(username);
                con.setCurrentUser(username);

                //close login form
                Login::hide();

                //open dashboard
                Dashboard *dashboard = new Dashboard();
                dashboard->showMaximized();
            }else{
                QMessageBox::critical(this, "Access Denied",
                                         "Make sure you use the right username,"
                                         " password and account", QMessageBox::Close);
            }
        }
    }
}

/*
Show about BuzPOS
*/
void Login::on_actionBuz_POS_triggered()
{
    QMessageBox::information(this, "About BuzPOS",
                             "Buz Point of Sale was created by Eric Sentongo\n"
                             "Phone No: +25675 996 1228\n"
                             "Email: eric_sentongo@yahoo.com", QMessageBox::Close);
}

/*
Show help dialog
*/
void Login::on_actionHelp_topics_triggered()
{
    HelpDialog *help = new HelpDialog();
    help->show();
}
