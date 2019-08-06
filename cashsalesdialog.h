#ifndef CASHSALESDIALOG_H
#define CASHSALESDIALOG_H

#include <QDialog>
#include <QCompleter>
#include "dbconnection.h"

namespace Ui {
class CashSalesDialog;
}

class CashSalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CashSalesDialog(QWidget *parent = 0);
    ~CashSalesDialog();

private slots:

    void on_lineEdit_searchcs_returnPressed();

    void on_pushButton_searchcs_clicked();

    void on_pushButton_refreshcs_clicked();

    void on_pushButton_filterCs_clicked();

private:
    Ui::CashSalesDialog *ui;

    DBConnection cscon;
    QCompleter *searchcompleter;
    QString completion, searchstr;

    void search_invoices(QString invoiceno);
    void setCashSalesHeaders();
};

#endif // CASHSALESDIALOG_H
