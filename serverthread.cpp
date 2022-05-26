#include "serverthread.h"

ServerThread::ServerThread(QTcpServer *serv)
{
    socket = serv->nextPendingConnection();
    //QTcpSocket *socket=server->nextPendingConnection();
}


void ServerThread::run(){
    qDebug()<<"Thread starting";

    qDebug()<< "A\n\r";
    quint32 variable_to_graph=44;
    while (true) {
        QByteArray data ((char *) &(variable_to_graph), 4);
        socket->write(data);
        socket->flush();
        variable_to_graph++;
        qDebug()<< data;
        msleep(1000);
    }
    socket->waitForBytesWritten(3000);
    msleep(1000);
    socket->write("Bye\n\r");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();

}

