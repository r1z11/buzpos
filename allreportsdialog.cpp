#include "allreportsdialog.h"
#include "ui_allreportsdialog.h"
#include <QFileDialog>
#include <qdebug.h>

bool cashChecked = false;
bool creditChecked = false;
bool paymentsChecked = false;
bool startChecked = false;
bool endChecked = false;
bool singleChecked = false;

bool singleDateChecked = false;

bool allReportsChecked = false;
bool cashCreditChecked = false;
bool cashOnlyChecked = false;
bool creditOnlyChecked = false;
bool paymentsOnlyChecked = false;
bool cashPaymentsChecked = false;
bool creditPaymentsChecked = false;
bool allNotChecked = false;

AllReportsDialog::AllReportsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllReportsDialog)
{
    ui->setupUi(this);

    arcon.db = QSqlDatabase::database("buz");

    QDate today = QDate::currentDate();
    ui->dateEdit_start->setDate(today);
    ui->dateEdit_end->setDate(today);
    ui->dateEdit_single->setDate(today);
}

AllReportsDialog::~AllReportsDialog()
{
    delete ui;
}

/*
Close dialog
*/
void AllReportsDialog::on_pushButton_cancel_clicked()
{
    AllReportsDialog::close();
}

/*********************
Generate report
**********************/
void AllReportsDialog::on_pushButton_generate_clicked()
{
    //get the check combination
    checkedCombination();

    /***
    all reports selected for one day
    ***/
    if(allReportsChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(datestr);

        //credit sales model
        setupCreditSalesModel(datestr);

        //payments model
        setupPaymentsModel(datestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales, credit sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    all reports checked for multiple days
    ***/
    if(allReportsChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(startdatestr, enddatestr);

        //credit sales model
        setupCreditSalesModel(startdatestr, enddatestr);

        //payments model
        setupPaymentsModel(startdatestr, enddatestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales, credit sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash report checked for one day
    ***/
    if(cashOnlyChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(datestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //success message
        QMessageBox::information(this, "Report exported successfully!",
                                 "The cash sales report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash report checked for multiple days
    ***/
    if(cashOnlyChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(startdatestr, enddatestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash and credit report checked for one day
    ***/
    if(cashCreditChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(datestr);

        //credit sales model
        setupCreditSalesModel(datestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales and credit sales reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash and credit report checked for multiple days
    ***/
    if(cashCreditChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(startdatestr, enddatestr);

        //credit sales model
        setupCreditSalesModel(startdatestr, enddatestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales and credit sales reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash sales and payments report checked for one day
    ***/
    if(cashPaymentsChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(datestr);

        //payments model
        setupPaymentsModel(datestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    cash sales and payments reports checked for multiple days
    ***/
    if(cashPaymentsChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //cash sales model
        setupCashSalesModel(startdatestr, enddatestr);

        //payments model
        setupPaymentsModel(startdatestr, enddatestr);

        //cash sales csv
        QString cashData;
        int cashrows=arcon.csmodel->rowCount();
        int cashcols=arcon.csmodel->columnCount();

        for (int i = 0; i < cashrows; i++)
        {
            for (int j = 0; j < cashcols; j++)
            {
                cashData += arcon.csmodel->data(arcon.csmodel->index(i,j)).toString();
                cashData += ", ";      // for .csv file format
            }
            cashData += "\n";             // for new line segmentation
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save cash sale csv
        QFile cashfile(fileName+"cashsales.csv");
        if(cashfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&cashfile);
            out<<cashData;
        }
        cashfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The cash sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    credit sales and payments report checked for one day
    ***/
    if(creditPaymentsChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //credit sales model
        setupCreditSalesModel(datestr);

        //payments model
        setupPaymentsModel(datestr);

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The credit sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    credit sales and payments report checked for multiple days
    ***/
    if(creditPaymentsChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //credit sales model
        setupCreditSalesModel(startdatestr, enddatestr);

        //payments model
        setupPaymentsModel(startdatestr, enddatestr);

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The credit sales and payments reports have been saved to "+fileName, QMessageBox::Close);
    }

    /***
    credit sales only report checked for one day
    ***/
    if(creditOnlyChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //credit sales model
        setupCreditSalesModel(datestr);

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The credit sales report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    credit only report checked for multiple days
    ***/
    if(creditOnlyChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //credit sales model
        setupCreditSalesModel(startdatestr, enddatestr);

        //credit sales csv
        QString creditData;
        int creditrows=arcon.csdmodel->rowCount();
        int creditcols=arcon.csdmodel->columnCount();

        for (int i = 0; i < creditrows; i++)
        {
            for (int j = 0; j < creditcols; j++)
            {
                creditData += arcon.csdmodel->data(arcon.csdmodel->index(i,j)).toString();
                creditData += ", ";      // for .csv file format
            }
            creditData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save credit sale csv
        QFile creditfile(fileName+"creditsales.csv");
        if(creditfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&creditfile);
            out<<creditData;
        }
        creditfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The credit sales report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    payments only report checked for one day
    ***/
    if(paymentsOnlyChecked && singleDateChecked){
        QDate date = ui->dateEdit_single->date();
        QString datestr = date.toString("yyyy-MM-dd");

        //payments model
        setupPaymentsModel(datestr);

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The payments report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    payments only report checked for multiple days
    ***/
    if(paymentsOnlyChecked && !singleDateChecked){
        QDate startdate = ui->dateEdit_start->date();
        QString startdatestr = startdate.toString("yyyy-MM-dd");

        QDate enddate = ui->dateEdit_end->date();
        QString enddatestr = enddate.toString("yyyy-MM-dd");

        //payments model
        setupPaymentsModel(startdatestr, enddatestr);

        //payments csv
        QString payData;
        int payrows=arcon.pmodel->rowCount();
        int paycols=arcon.pmodel->columnCount();

        for (int i = 0; i < payrows; i++)
        {
            for (int j = 0; j < paycols; j++)
            {
                payData += arcon.pmodel->data(arcon.pmodel->index(i,j)).toString();
                payData += ", ";      // for .csv file format
            }
            payData += "\n";             // (for new line segmentation)
        }

        //get the filename and directory to save exported data
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "exported_",
                                                        tr("Data export (*.)"));

        //save payments sale csv
        QFile payfile(fileName+"payments.csv");
        if(payfile.open(QIODevice::WriteOnly))
        {
            QTextStream out(&payfile);
            out<<payData;
        }
        payfile.close();

        //success message
        QMessageBox::information(this, "Reports exported successfully!",
                                 "The payments report has been saved to "+fileName, QMessageBox::Close);
    }

    /***
    all reports not checked
    ***/
    if(allNotChecked){
        QMessageBox::warning(this, "Cannot generate report!",
                             "Please select a report to generate!", QMessageBox::Close);
    }
}

//Cash sales model setup
void AllReportsDialog::setupCashSalesModel(QString datestr)
{
    arcon.csmodel = new QSqlTableModel(this, arcon.db);
    arcon.csmodel->setTable("sales");
    arcon.csmodel->setFilter("date ='"+datestr+"' AND type = 'cash' ");
    arcon.csmodel->select();

    arcon.csmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    arcon.csmodel->setHeaderData(4, Qt::Horizontal, tr("Product name"));
    arcon.csmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    arcon.csmodel->setHeaderData(6, Qt::Horizontal, tr("Rate"));
    arcon.csmodel->setHeaderData(7, Qt::Horizontal, tr("Discount"));
    arcon.csmodel->setHeaderData(8, Qt::Horizontal, tr("Tax"));
    arcon.csmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    arcon.csmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    arcon.csmodel->removeColumn(0); //remove uid column
    arcon.csmodel->removeColumn(1); //remove type
    arcon.csmodel->removeColumn(3); //remove customer
}

void AllReportsDialog::setupCashSalesModel(QString startdatestr, QString enddatestr)
{

    arcon.csmodel = new QSqlTableModel(this, arcon.db);
    arcon.csmodel->setTable("sales");
    arcon.csmodel->setFilter("DATE BETWEEN '"+startdatestr+"' AND '"+enddatestr+"' AND type='cash' ");
    arcon.csmodel->select();

    arcon.csmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    arcon.csmodel->setHeaderData(4, Qt::Horizontal, tr("Product name"));
    arcon.csmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    arcon.csmodel->setHeaderData(6, Qt::Horizontal, tr("Rate"));
    arcon.csmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    arcon.csmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    arcon.csmodel->removeColumn(0); //remove uid column
    arcon.csmodel->removeColumn(1); //remove type
    arcon.csmodel->removeColumn(3); //remove customer
    arcon.csmodel->removeColumn(7); //remove discount
    arcon.csmodel->removeColumn(8); //remove tax
}

//Credit sales model setup
void AllReportsDialog::setupCreditSalesModel(QString datestr)
{

    arcon.csdmodel = new QSqlTableModel(this, arcon.db);
    arcon.csdmodel->setTable("sales");
    arcon.csdmodel->setFilter("date = '"+datestr+"' AND type='credit' ");
    arcon.csdmodel->select();

    arcon.csdmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    arcon.csdmodel->setHeaderData(3, Qt::Horizontal, tr("Customer name"));
    arcon.csdmodel->setHeaderData(4, Qt::Horizontal, tr("Product name"));
    arcon.csdmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    arcon.csdmodel->setHeaderData(6, Qt::Horizontal, tr("Rate"));
    arcon.csmodel->setHeaderData(7, Qt::Horizontal, tr("Discount"));
    arcon.csmodel->setHeaderData(8, Qt::Horizontal, tr("Tax"));
    arcon.csdmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    arcon.csdmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    arcon.csdmodel->removeColumn(0); //remove uid column
    arcon.csdmodel->removeColumn(1); //remove type
}

void AllReportsDialog::setupCreditSalesModel(QString startdatestr, QString enddatestr)
{
    arcon.csdmodel = new QSqlTableModel(this, arcon.db);
    arcon.csdmodel->setTable("sales");
    arcon.csdmodel->setFilter("DATE BETWEEN '"+startdatestr+"' AND '"+enddatestr+"' AND type='credit' ");
    arcon.csdmodel->select();

    arcon.csdmodel->setHeaderData(2, Qt::Horizontal, tr("Invoice No"));
    arcon.csdmodel->setHeaderData(3, Qt::Horizontal, tr("Customer name"));
    arcon.csdmodel->setHeaderData(4, Qt::Horizontal, tr("Product name"));
    arcon.csdmodel->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
    arcon.csdmodel->setHeaderData(6, Qt::Horizontal, tr("Rate"));
    arcon.csdmodel->setHeaderData(9, Qt::Horizontal, tr("Amount"));
    arcon.csdmodel->setHeaderData(10, Qt::Horizontal, tr("Date"));

    arcon.csdmodel->removeColumn(0); //remove uid column
    arcon.csdmodel->removeColumn(1); //remove type
    arcon.csdmodel->removeColumn(7); //remove discount
    arcon.csdmodel->removeColumn(8); //remove tax
}

//Payments model setup
void AllReportsDialog::setupPaymentsModel(QString datestr)
{
    arcon.pmodel = new QSqlTableModel(this, arcon.db);
    arcon.pmodel->setTable("payments");
    arcon.pmodel->setFilter("date = '"+datestr+"'");
    arcon.pmodel->select();

    arcon.pmodel->setHeaderData(2, Qt::Horizontal, tr("Cutomer name"));
    arcon.pmodel->setHeaderData(4, Qt::Horizontal, tr("Date"));
    arcon.pmodel->setHeaderData(3, Qt::Horizontal, tr("Amount"));
    arcon.pmodel->setHeaderData(1, Qt::Horizontal, tr("Receipt No"));

    arcon.pmodel->removeColumn(0); //remove uid column
}

void AllReportsDialog::setupPaymentsModel(QString startdatestr, QString enddatestr)
{
    arcon.pmodel = new QSqlTableModel(this, arcon.db);
    arcon.pmodel->setTable("payments");
    arcon.pmodel->setFilter("DATE BETWEEN '"+startdatestr+"' AND '"+enddatestr+"'");
    arcon.pmodel->select();

    arcon.pmodel->setHeaderData(2, Qt::Horizontal, tr("Customer name"));
    arcon.pmodel->setHeaderData(4, Qt::Horizontal, tr("Date"));
    arcon.pmodel->setHeaderData(3, Qt::Horizontal, tr("Amount"));
    arcon.pmodel->setHeaderData(1, Qt::Horizontal, tr("Receipt No"));

    arcon.pmodel->removeColumn(0); //remove uid column
}

/*
Find out which combination was checked
*/
void AllReportsDialog::checkedCombination()
{
    cashChecked = ui->checkBox_cash->isChecked();

    creditChecked = ui->checkBox_credit->isChecked();

    paymentsChecked = ui->checkBox_payments->isChecked();

    startChecked = ui->checkBox_start->isChecked();

    endChecked = ui->checkBox_end->isChecked();

    singleChecked = ui->checkBox_single->isChecked();

    //checked combinations
    if(cashChecked && creditChecked && paymentsChecked){
        allReportsChecked = true;
    }
    if(cashChecked && creditChecked && !paymentsChecked){
        cashCreditChecked = true;
    }
    if(cashChecked && !creditChecked && !paymentsChecked){
        cashOnlyChecked = true;
    }
    if(!cashChecked && creditChecked && !paymentsChecked){
        creditOnlyChecked = true;
    }
    if(!cashChecked && !creditChecked && paymentsChecked){
        paymentsOnlyChecked = true;
    }
    if(cashChecked && !creditChecked && paymentsChecked){
        cashPaymentsChecked = true;
    }
    if(!cashChecked && creditChecked && paymentsChecked){
        creditPaymentsChecked = true;
    }
    if(!cashChecked && !creditChecked && !paymentsChecked){
        allNotChecked = true;
    }

    if(singleChecked){
        singleDateChecked = true;
    }
}

/*
Singled date toggled
*/
void AllReportsDialog::on_checkBox_single_toggled(bool checked)
{
    if(checked){
        ui->checkBox_start->setChecked(false);
        ui->checkBox_end->setChecked(false);
        singleDateChecked = true;
    }else{
        ui->checkBox_start->setChecked(true);
        ui->checkBox_end->setChecked(true);
        singleDateChecked = false;
    }
}

/*
Start date toggled
*/
void AllReportsDialog::on_checkBox_start_toggled(bool checked)
{
    if(checked){
        ui->checkBox_single->setChecked(false);
    }
}

/*
End date toggled
*/
void AllReportsDialog::on_checkBox_end_toggled(bool checked)
{
    if(checked){
        ui->checkBox_single->setChecked(false);
    }
}

void AllReportsDialog::on_checkBox_cash_clicked()
{
    //
}
