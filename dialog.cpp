#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


   ui->textEdit->setText("<h3><p align='center'>Developer</p></h3>"
           "<p align='center'>Sorokina Anna Alexandrovna, "
           "<p align='center'>student of group A-45 "
           "<p align='center'>FAES.</p>"
          "<p align='center'>Novosibirsk</p> <p align='center'> 2015г.</p>");
    ;
}

Dialog::~Dialog()
{
    delete ui;
}
