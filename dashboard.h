#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "dbconnection.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

private slots:
    void on_actionLogout_triggered();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_actionSettings_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void calculate_bill();

    void on_pushButton_3_clicked();

    void on_removeRowButton_clicked();

    void on_actionHelp_topics_triggered();

    void on_searchLineEdit_returnPressed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void setProductHeaders();

    void search_products(QString product);

    void on_pushButton_8_clicked();

    void on_lineEdit_cash_textChanged(const QString &arg1);

    void on_actionAll_payments_triggered();

    void on_actionCash_sales_triggered();

    void on_actionCredit_sales_triggered();

    void on_actionAll_reports_triggered();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_actionAbout_Buz_POS_triggered();

    void on_actionCustomer_accounts_triggered();

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_2_activated(const QModelIndex &index);

private:
    Ui::Dashboard *ui;

    DBConnection dbcon;
    int selectedrow;
    QCompleter *searchcompleter;
    QString completion, searchstr;
    void updateStock(QStringList products, QStringList nos);

    int taxrate;
};

#endif // DASHBOARD_H
