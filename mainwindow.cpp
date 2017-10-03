#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QtGui>
#include <QtCore>
#include "adduser.h"
#include "udpserver.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Messenger");
    read_settings = new QSettings("settings",QSettings::NativeFormat);
    login = read_settings->value("CurrentUser/Login").toString();
    ui->textBrowser->append(login + " is connected");

    //Udp server
    server = new UdpServer;
    connect(server, SIGNAL(ready(QString)), ui->textBrowser, SLOT(append(QString)));
    connect(ui->lineEdit, SIGNAL(returnPressed()),this, SLOT(on_pushButton_clicked()));
    connect(ui->quit, SIGNAL(triggered(bool)), this, SLOT(close()));

    //DataBase
  /*  db = QSqlDatabase::addDatabase("QPSQL","db2");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("UserDB");
    db.setUserName("postgres");
    db.setPassword("crysis12");

    ui->statusBar->showMessage("Соединение с базой данных...",1500);
    bool ok = db.open();
    (ok) ? ui->statusBar->showMessage("Соединение с базой данных успешно",15000) : ui->statusBar->showMessage("Соединение с базой данных не установлено",15000);

    model = new QSqlTableModel(this, db);
    model->setTable("users_table");
    model->select();
    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);*/
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (key == Qt::Key_Enter)
    {
        on_pushButton_clicked();
    }
}

void MainWindow::on_about_triggered()
{
    Dialog dialog;
        dialog.setWindowFlags(Qt::WindowContextHelpButtonHint);
        dialog.exec();
}

void MainWindow::on_pushButton_clicked()
{
   QString message = ui->lineEdit->text();
   QString msg = ("<font color='blue'>" + login +"</font>: " + message +"</br>" );
   ui->textBrowser->append(msg);
   server->writeDatagram(ui->lineEdit->text());
   ui->lineEdit->clear();
}

void MainWindow::on_addUser_triggered()
{
    //editUser editUser;
    this->setHidden(true);
   // editUser.exec();
    this->setVisible(true);
}
