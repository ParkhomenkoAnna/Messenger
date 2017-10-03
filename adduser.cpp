#include "adduser.h"
#include "ui_adduser.h"
#include <QDebug>
#include <QPalette>
#include <QHostAddress>
#include <mainwindow.h>
#include <login_manager.h>
#include <QSettings>

using namespace Qt;

addUser::addUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);
    this->setWindowFlags(Window | FramelessWindowHint);
    QPalette pal1, pal2;
    pal1.setColor(ui->create->backgroundRole(), green);
    ui->create->setPalette(pal1);
    pal2.setColor(ui->cancel->backgroundRole(), red);
    ui->cancel->setPalette(pal2);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    int id = random();
    ui->label->setText(QString::number(id));
    write_settings = new QSettings("settings",QSettings::NativeFormat);
    dbEdit = QSqlDatabase::addDatabase("QPSQL");
    dbEdit.setHostName("127.0.0.1");
    dbEdit.setDatabaseName("UserDB");
    dbEdit.setUserName("postgres");
    dbEdit.setPassword("crysis12");

    bool ok = dbEdit.open();
    (ok) ? qDebug() << "Вход в базу данных совершен" : qDebug() << "Невозможно зайти в базу данных";
    if(dbEdit.tables().empty())
       {
           QSqlQuery creatingQuery;
           QString str = "CREATE TABLE users_table ("
                      "ID integer PRIMARY KEY NOT NULL, "
                      "nickname VARCHAR(63), "
                      "password VARCHAR(63), "
                      "age integer, "
                      "time time"
                      ");";
            bool tableIsCreating = creatingQuery.exec(str);
            (tableIsCreating) ? qDebug() << "Таблица создана" : qDebug() << "Не удается создать таблицу";
            QSqlDatabase::removeDatabase("PSQL");
       }
    connect(ui->cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

    time=QTime::currentTime();
 }

addUser::~addUser()
{
        delete ui;
}

void addUser::on_login_edit_editingFinished()
{
    login = ui->login_edit->text();
}

void addUser::on_password_edit_editingFinished()
{
    password = ui->password_edit->text();
}

void addUser::on_age_edit_editingFinished()
{
    age = ui->age_edit->text().toInt();
}

void addUser::on_create_clicked()
{
     QSqlQuery query;
     QString str = ("insert into users_table VALUES  (" + QString::number(id) + ", '" + login + "', '" + password + "', " +  QString::number(age) + ", '" + time.toString() + "');");
     bool isrecorded = query.exec(str);
     (isrecorded) ? qDebug() << "Запись прошла успешно" : qDebug() << dbEdit.lastError();
     QSqlDatabase::removeDatabase("QPSQL");
     write_settings->setValue("CurrentUser/Login",login);
     MainWindow * widget = new MainWindow;
     widget->show();
     this->close();
}

void addUser::on_cancel_clicked()
{
    Login_manager* loginManage = new Login_manager;
    loginManage->show();
    this->close();
}
