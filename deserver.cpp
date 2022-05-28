#include "deserver.h"

Deserver::Deserver(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress("127.0.0.1"),5400)){
        qDebug()<< "Server Could not start";
    }
    else
    {
        qDebug()<< "Starting server";
    }
}


void Deserver::newConnection(){
    ServerThread *task = new ServerThread(server);
    task->run();
    task->wait();
}
