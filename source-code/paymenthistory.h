#ifndef PAYMENTHISTORY_H
#define PAYMENTHISTORY_H

#include <QDialog>
#include <dbconnection.h>

namespace Ui {
class PaymentHistory;
}

class PaymentHistory : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentHistory(QWidget *parent = 0);
    ~PaymentHistory();

    void getPayments(QString customer_name);

private slots:
    void on_pushButton_dateFilter_clicked();

    void on_pushButton_pDelete_clicked();

private:
    Ui::PaymentHistory *ui;

    DBConnection phcon;
    void setupTable();
};

#endif // PAYMENTHISTORY_H
