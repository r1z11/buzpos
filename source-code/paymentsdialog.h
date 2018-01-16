#ifndef PAYMENTSDIALOG_H
#define PAYMENTSDIALOG_H

#include <QDialog>
#include <QCompleter>
#include "dbconnection.h"

namespace Ui {
class PaymentsDialog;
}

class PaymentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentsDialog(QWidget *parent = 0);
    ~PaymentsDialog();

private slots:
    void on_lineEdit_searchpts_returnPressed();

    void on_pushButton_searchpts_clicked();

    void on_pushButton_makepts_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_filterP_clicked();

    void on_pushButton_delPaymt_clicked();

private:
    Ui::PaymentsDialog *ui;

    DBConnection pcon;

    QCompleter *searchcompleter;
    QString completion, searchstr;

    void search_customers(QString customer);

    void setPaymentHeaders();
};

#endif // PAYMENTSDIALOG_H
