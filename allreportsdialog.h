#ifndef ALLREPORTSDIALOG_H
#define ALLREPORTSDIALOG_H

#include <QDialog>
#include "dbconnection.h"

namespace Ui {
class AllReportsDialog;
}

class AllReportsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AllReportsDialog(QWidget *parent = 0);
    ~AllReportsDialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_generate_clicked();

    void on_checkBox_single_toggled(bool checked);

    void on_checkBox_start_toggled(bool checked);

    void on_checkBox_end_toggled(bool checked);

    void on_checkBox_cash_clicked();

private:
    Ui::AllReportsDialog *ui;

    DBConnection arcon;

    void checkedCombination();
    void setupCashSalesModel(QString datestr);
    void setupCashSalesModel(QString startdatestr, QString enddatestr);
    void setupCreditSalesModel(QString datestr);
    void setupCreditSalesModel(QString startdatestr, QString enddatestr);
    void setupPaymentsModel(QString datestr);
    void setupPaymentsModel(QString startdatestr, QString enddatestr);
};

#endif // ALLREPORTSDIALOG_H
