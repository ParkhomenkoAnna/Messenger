#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <QWidget>
#include <adduser.h>
#include <QSettings>
#include <QFile>
namespace Ui {
class Login_manager;
class User;
}

class Login_manager : public QWidget
{
    Q_OBJECT

public:
    explicit Login_manager(QWidget *parent = 0);
    ~Login_manager();
     QString login;
     QSettings *write_settings, *read_settings;

     QString password;
     QSqlDatabase dbAuth;

private slots:
    void on_sign_up_clicked();
    void on_sign_in_clicked();
    void on_loginEdit_selectionChanged();

    void on_passwdEdit_selectionChanged();
private:
    Ui::Login_manager *ui;
};

#endif // LOGIN_MANAGER_H
