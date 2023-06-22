#include <QCoreApplication>
#include <QDebug>

#include "qudpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    new QUdpServer(&a);

    return a.exec();
}
