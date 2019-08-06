#ifndef DBCONNECTION
#define DBCONNECTION

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <globals.h>

/*
    function to connect to a database.
*/

class DBConnection {
public:
    QSqlDatabase db;

    //query model
    QSqlQueryModel *querymodel;

    //products model
    QSqlTableModel *model;
    //current order model
    QSqlTableModel *comodel;
    //users model
    QSqlTableModel *usmodel;
    //products (settings) model
    QSqlTableModel *psmodel;
    //payments model
    QSqlTableModel *pmodel;
    //customers model
    QSqlTableModel *cmodel;
    //cash sales model
    QSqlTableModel *csmodel;
    //credit sales model
    QSqlTableModel *csdmodel;
    //customer accounts model
    QSqlTableModel *camodel;
    //customer settings model
    QSqlTableModel *smodel;

    //create database connection
    void createConnection(QString connectionName){
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        QString currentPath = QDir::currentPath()+"/buzpos";
        db.setDatabaseName(currentPath);
        db.open();
    }

    //check if connection is open
    bool isDbOpen()
    {
        if (!db.open()) {
            qDebug() << db.lastError().text();

            QMessageBox::critical(0, qApp->tr("Database error!"),
                                  qApp->tr("Unable to establish a database connection.\n"),
                                  QMessageBox::Close);

            return false;
        }
        return true;
    }

    //get the current user logged in
    QString getCurrentUser()
    {
        QString username = Globals::instance()->getUser();
        return username;
    }

    //set the current user logged in
    void setCurrentUser(QString username)
    {
        QSqlQuery query(db);
        query.prepare(QString("INSERT INTO users_loggedin(username) VALUES ( :username) WHERE NOT EXISTS"));
        query.bindValue(":username", username);
        query.exec();
    }

    //is the current user logged in
    bool isUserLoggedIn()
    {
        //get current user
        QString username = Globals::instance()->getUser();

        //check if logged in
        QSqlQuery query(db);
        query.prepare(QString("SELECT username FROM users_loggedin WHERE username = :username "));
        query.bindValue(":username", username);
        query.exec();

        if(query.next()){
            return true;
        } else {
            return false;
        }
    }

    //logout current user
    void logoutCurrentUser(QString username)
    {
        QSqlQuery query(db);
        query.prepare(QString("DELETE FROM users_loggedin WHERE username = :username "));
        query.bindValue(":username", username);
        query.exec();
    }

    //does user exist
    bool userExists(QString username)
    {
        bool exists = false;
        QSqlQuery query(db);
        query.prepare(QString("SELECT username FROM users WHERE username = :username "));
        query.bindValue(":username", username);
        query.exec();

        while (query.next()) {
            QString username2 = query.value(0).toString();

            if(username == username2)
                exists = true;
        }
        return exists;
    }

    //does product exist
    bool productExists(QString pname)
    {
        bool exists = false;
        QSqlQuery query(db);
        query.prepare(QString("SELECT pname FROM products WHERE pname = :pname "));
        query.bindValue(":pname", pname);
        query.exec();

        while (query.next()) {
            QString pname2 = query.value(0).toString();

            if(pname == pname2)
                exists = true;
        }
        return exists;
    }

    //get tax rate
    double getTax()
    {
        double tax = 0;

        QSqlQuery query(db);
        query.prepare(QString("SELECT tax FROM settings"));
        query.exec();

        while (query.next()) {
            tax = query.value(0).toDouble();
        }

        return tax;
    }

    //does invoice no exist
    bool invoiceNoExists(QString invno)
    {
        bool exists = false;
        QSqlQuery query(db);
        query.prepare(QString("SELECT invoiceno FROM sales WHERE invoiceno = :invno "));
        query.bindValue(":invno", invno);
        query.exec();

        while (query.next()) {
            QString invno2 = query.value(0).toString();

            if(invno == invno2){
                exists = true;
                qDebug() << "invoice no exists? "+exists;
            }
        }
        return exists;
    }

    //get the current branch
    QString getBranch()
    {
        QString branch;
        QSqlQuery query(db);
        query.prepare(QString("SELECT branch_name FROM settings"));
        query.exec();

        while (query.next()) {
            branch = query.value(0).toString();
        }
        return branch;
    }

};

#endif // DBCONNECTION

