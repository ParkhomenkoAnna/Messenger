#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <login_manager.h>
#include <QFile>

using namespace Qt;

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QFile * file_settings;
   file_settings = new QFile("./settings");
   Login_manager loginManager;
   MainWindow widget;
   (!file_settings->exists()) ? loginManager.show() : widget.show();
   return a.exec();
}
