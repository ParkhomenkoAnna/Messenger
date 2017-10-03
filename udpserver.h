#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = 0);
private:
    QHostAddress * serverIp;
    QUdpSocket * server;
    QHostAddress getIp();
private slots:


public slots:
    void readPendingDatagrams();
    void writeDatagram(QString msg);

signals:
    void ready(QString);
};

#endif // UDPSERVER_H
