#include "login_manager.h"
#include "ui_login_manager.h"
#include <QPalette>
#include <adduser.h>
#include <mainwindow.h>
#include <QDebug>

using namespace Qt;

Login_manager::Login_manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login_manager)
{
    setlocale(LC_ALL,"Russian");
    ui->setupUi(this);
    QPalette pal1, pal2;
    pal1.setColor(this->backgroundRole(), white);
    this->setPalette(pal1);
    pal2.setColor(ui->sign_up->backgroundRole(), green);
    ui->sign_up->setPalette(pal2);
    this->setAutoFillBackground(true);
    this->setWindowFlags(Window | FramelessWindowHint);
    this->setWindowTitle("Авторизация");
    connect(ui->quit, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->move(750,200);
    write_settings = new QSettings("settings",QSettings::NativeFormat);
    read_settings = new QSettings("settings",QSettings::NativeFormat);

    ui->passwdEdit->setEchoMode(QLineEdit::Password);
}

Login_manager::~Login_manager()
{
    delete ui;
}

void Login_manager::on_sign_up_clicked()
{
    addUser adduser;
    this->hide();
    adduser.exec();
    this->close();
}

void Login_manager::on_sign_in_clicked()
{
    dbAuth = QSqlDatabase::addDatabase("QPSQL");
    dbAuth.setHostName("127.0.0.1");
    dbAuth.setDatabaseName("UserDB");
    dbAuth.setUserName("postgres");
    dbAuth.setPassword("crysis12");
    bool ok = dbAuth.open();
    (ok) ? qDebug() << "Вход в базу данных совершен" : qDebug() << "Невозможно зайти в базу данных";

    QSqlQuery query("select nickname from users_table WHERE password = '"  + ui->passwdEdit->text() +"' AND nickname = '" + ui->loginEdit->text() + "'");
    while (query.next()) {
        login = query.value(0).toString();
    }
    if (login.isEmpty())
        ui->error_label->setText("Неверный логин или пароль");
    else
    {
        dbAuth.close();
        dbAuth.removeDatabase("");
        write_settings->setValue("CurrentUser/Login",login);
        MainWindow* wid = new MainWindow;
        wid->show();
        this->close();
    }
}

void Login_manager::on_loginEdit_selectionChanged()
{
    ui->loginEdit->clear();
}

void Login_manager::on_passwdEdit_selectionChanged()
{
    ui->passwdEdit->clear();
}
