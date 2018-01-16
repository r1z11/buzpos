#ifndef CUSTOMERNAMEDIALOG_H
#define CUSTOMERNAMEDIALOG_H

#include <QDialog>
#include "dbconnection.h"

namespace Ui {
class CustomerNameDialog;
}

class CustomerNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerNameDialog(QWidget *parent = 0);
    ~CustomerNameDialog();

    QString invno;

    QSqlTableModel *currentorder;

    int items;

private slots:
    void on_radioButton_old_toggled(bool checked);

    void on_radioButton_new_toggled(bool checked);

    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::CustomerNameDialog *ui;

    QString getCustomer();

    DBConnection cdcon;

    void updateStock(QStringList products, QStringList qty);
};

#endif // CUSTOMERNAMEDIALOG_H
