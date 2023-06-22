#ifndef QUDPSERVER_H
#define QUDPSERVER_H

#include <QObject>
#include <QHostAddress>

class StunClient;

class QUdpServer : public QObject
{
    Q_OBJECT
public:
    explicit QUdpServer(QObject *parent = nullptr);

private:
    StunClient *socket = nullptr;

};

#endif // QUDPSERVER_H
