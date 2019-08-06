#ifndef ADDPAYMENTDIALOG_H
#define ADDPAYMENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddPaymentDialog;
}

class AddPaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPaymentDialog(QWidget *parent = 0);
    ~AddPaymentDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddPaymentDialog *ui;
};

#endif // ADDPAYMENTDIALOG_H
