#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = 0);
    ~AddProductDialog();

    int productRow() { return productrow; }

    void setProductRow(int value) { productrow = value; }

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AddProductDialog *ui;

    int productrow;
};

#endif // ADDPRODUCTDIALOG_H
