#ifndef PASSCHANGEDIALOG_H
#define PASSCHANGEDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class PassChangeDialog;
}

class PassChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassChangeDialog(QWidget *parent = 0);
    ~PassChangeDialog();

    static int passrow;
    static QString fullname;
    static QString origpass;


private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::PassChangeDialog *ui;
};

#endif // PASSCHANGEDIALOG_H
