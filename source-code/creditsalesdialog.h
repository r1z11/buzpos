#ifndef CREDITSALESDIALOG_H
#define CREDITSALESDIALOG_H

#include <QDialog>
#include "dbconnection.h"
#include <QCompleter>

namespace Ui {
class CreditSalesDialog;
}

class CreditSalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditSalesDialog(QWidget *parent = 0);
    ~CreditSalesDialog();

private slots:
    void on_pushButton_refresh_clicked();

    void on_pushButton_search_clicked();

    void on_lineEdit_customers_returnPressed();

    void on_pushButton_filter_clicked();

private:
    Ui::CreditSalesDialog *ui;
    DBConnection csdcon;
    QCompleter *searchcompleter;
    QString completion, searchstr;

    void setCreditSalesHeaders();
    void search_customers(QString customer);
};

#endif // CREDITSALESDIALOG_H
