#include "qudpserver.h"
#include "stunclient.h"

#include <QUdpSocket>
#include <iostream>

struct Comando {
    quint16 id;
    quint16 cmd;
    quint16 val;
};

struct __attribute__((__packed__)) Connection {
    quint32 action;
    quint32 transaction_id;
    quint64 connection_id;
    Comando comando;

    QString toString() {
        QString ret;

        ret.append("action ");
        ret.append(QString("%01").arg(action));
        ret.append("\nconnection_id ");
        ret.append(QString("%01").arg(connection_id));
        ret.append("\ntransaction_id ");
        ret.append(QString("%01").arg(transaction_id));
        ret.append("comando\nid");
        ret.append(QString("%01").arg(comando.id));
        ret.append("\ncmd");
        ret.append(QString("%01").arg(comando.cmd));
        ret.append("\nval");
        ret.append(QString("%01").arg(comando.val));

        return ret;
    }
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

        std::cout << "Aguardando...\n";
        std::cout.flush();
        while(!socket->hasPendingDatagrams());
        socket->readDatagram(reinterpret_cast<char*>(&response),
                             sizeof(Connection),
                             &sender, &senderPort);
        std::cout << "Recebido de "
                  << sender.toString().toStdString()
                  << " porta "
                  << senderPort
                  << '\n'
                  << response.toString().toStdString()
                  << std::endl;
        std::cout.flush();
        socket->writeDatagram(QByteArray(reinterpret_cast<char*>(&response),
                                         sizeof(response)), sender, senderPort);
    }
}
