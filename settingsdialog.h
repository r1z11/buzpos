#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_usersTableView_clicked(const QModelIndex &index);

    void on_changePassButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_psTableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void refreshUsers();

    void on_pushButton_10_clicked();

    void on_lineEdit_biz_editingFinished();

    void on_lineEdit_phone_editingFinished();

    void on_textEdit_address_textChanged();

    void on_comboBox_currency_currentIndexChanged(int index);

    void on_lineEdit_tax_editingFinished();

    void on_pushButton_8_clicked();

private:
    Ui::SettingsDialog *ui;

    QString branch;
    void saveGenSettings();
};

#endif // SETTINGSDIALOG_H
