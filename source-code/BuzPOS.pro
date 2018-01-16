#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T12:45:48
#
#-------------------------------------------------
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BuzPOS
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    dashboard.cpp \
    settingsdialog.cpp \
    helpdialog.cpp \
    passchangedialog.cpp \
    adduserdialog.cpp \
    addproductdialog.cpp \
    paymentsdialog.cpp \
    addpaymentdialog.cpp \
    cashsalesdialog.cpp \
    creditsalesdialog.cpp \
    allreportsdialog.cpp \
    customernamedialog.cpp \
    accountsdialog.cpp \
    globals.cpp \
    paymenthistory.cpp

HEADERS  += login.h \
    dashboard.h \
    dbconnection.h \
    settingsdialog.h \
    helpdialog.h \
    passchangedialog.h \
    adduserdialog.h \
    addproductdialog.h \
    paymentsdialog.h \
    addpaymentdialog.h \
    cashsalesdialog.h \
    creditsalesdialog.h \
    allreportsdialog.h \
    customernamedialog.h \
    accountsdialog.h \
    globals.h \
    paymenthistory.h

FORMS    += login.ui \
    dashboard.ui \
    settingsdialog.ui \
    helpdialog.ui \
    passchangedialog.ui \
    adduserdialog.ui \
    addproductdialog.ui \
    paymentsdialog.ui \
    addpaymentdialog.ui \
    cashsalesdialog.ui \
    creditsalesdialog.ui \
    allreportsdialog.ui \
    customernamedialog.ui \
    accountsdialog.ui \
    paymenthistory.ui

RESOURCES += \
    images/images.qrc

