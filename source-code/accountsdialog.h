#ifndef ACCOUNTSDIALOG_H
#define ACCOUNTSDIALOG_H

#include <QDialog>
#include <QCompleter>
#include "dbconnection.h"

namespace Ui {
class AccountsDialog;
}

class AccountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountsDialog(QWidget *parent = 0);
    ~AccountsDialog();

private slots:
    void on_pushButton_refreshAcc_clicked();

    void on_lineEdit_customers_returnPressed();

    void on_pushButton_searchAcc_clicked();

    void on_pushButton_payHistory_clicked();

private:
    Ui::AccountsDialog *ui;

    DBConnection cacon;
    QCompleter *searchcompleter;
    QString completion, searchstr;
    QSqlQueryModel *model;

    void setAccountHeaders();
    void search_accounts(QString customername);
};

#endif // ACCOUNTSDIALOG_H
