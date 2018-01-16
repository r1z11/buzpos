#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = 0);
    ~AddUserDialog();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

private:
    Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
