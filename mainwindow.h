#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include "adduser.h"
#include "udpserver.h"

namespace Ui {
class MainWindow;
class UdpServer;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit  MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString login;
    UdpServer * server;
    QSettings *read_settings;
    QSqlDatabase db;
    QSqlTableModel * model;

protected:
   virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void on_about_triggered();
    void on_pushButton_clicked();
    void on_addUser_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
