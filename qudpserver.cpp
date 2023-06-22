#include "qudpserver.h"
#include "stunclient.h"

#include <QUdpSocket>

union __attribute__((__packed__)) Connection {
    struct __attribute__((__packed__)) {
        quint64 connection_id;
        quint32 action;
        quint32 transaction_id;
    } request ;
    struct __attribute__((__packed__)) {
        quint32 action;
        quint32 transaction_id;
        quint64 connection_id;
    } response ;
};

QUdpServer::QUdpServer(QObject *parent)
    : QObject {parent}
    , socket (new StunClient("udp://stun.l.google.com:19302"))
{
    socket->bind(QHostAddress::Any, 7755);
    socket->binding();

    for(;;) {
        Connection response;
        QHostAddress sender;
        quint16 senderPort;

        qDebug() << "Aguardando...";
        while(!socket->hasPendingDatagrams());
        socket->readDatagram(reinterpret_cast<char*>(&response),
                             sizeof(Connection),
                             &sender, &senderPort);
        qDebug() << "Recebido de "
                 << sender.toString()
                 << " porta "
                 << senderPort
                 << "\naction "
                 << response.response.action
                 << "\nconnection_id "
                 << response.response.connection_id
                 << "\ntransaction_id "
                 << response.response.transaction_id;
        socket->writeDatagram(QByteArray(reinterpret_cast<char*>(&response),
                                         sizeof(response)), sender, senderPort);

    }
}
