#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_passLineEdit_returnPressed();

    void buzLogin();

    void on_actionBuz_POS_triggered();

    void on_actionHelp_topics_triggered();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
