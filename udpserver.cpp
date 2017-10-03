#include "udpserver.h"
#include <QNetworkInterface>
#include <QDebug>
#include <QObject>

UdpServer::UdpServer(QObject *parent) : QObject(parent)
{
    QHostAddress serverIp;
    serverIp= getIp();
    server = new QUdpSocket();
    server->bind(serverIp,1234);
    connect(server, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

QHostAddress UdpServer::getIp()
{
    QHostAddress address;
    QList<QHostAddress> networkAddresses = QNetworkInterface::allAddresses();
    address = networkAddresses.at(2);
    return address;
}

void UdpServer::readPendingDatagrams()
{
    while (server->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(server->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        server->readDatagram(datagram.data(),datagram.size(), &sender, &senderPort);
        emit  ready("<font color='red'> " + sender.toString() + "</font>:  " + QString(datagram) );
    }

}

void UdpServer::writeDatagram(QString msg)
{
    QByteArray datagram;
    datagram = msg.toLocal8Bit();
    server->writeDatagram(datagram,QHostAddress("192.168.1.5"),1234);

}
