#ifndef ADDUSER_H
#define ADDUSER_H
#include <QDialog>
#include "udpserver.h"
#include <QtSql>

using namespace std;

namespace Ui {
class addUser;
}
class addUser : public QDialog
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = 0);
    ~addUser();
    QString login, password;
    quint8 age;
    quint16 id;
    QSqlDatabase dbEdit;
    QSettings *write_settings; 
    QTime time;

private slots:
    void on_login_edit_editingFinished();
    void on_password_edit_editingFinished();
    void on_age_edit_editingFinished();
    void on_create_clicked();

    void on_cancel_clicked();

signals:

private:
    Ui::addUser *ui;
};

#endif // ADDUSER_H
