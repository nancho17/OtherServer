#include "resoccket.h"

Soccket::Soccket(QObject *parent)
    : QObject{parent}
{

}

void Soccket::Basic(){

    //connect
    socket =new QTcpSocket(this);
    socket->connectToHost("www.google.com",80);
    if(socket->waitForConnected(3000)){
    qDebug()<<"connected";
    socket->close();
    }
    else{
        qDebug()<<"NOT C";
    };

}


void Soccket:: Test(){
    socket =new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()) );

    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()) );

    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()) );

    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)) );


    qDebug()<<"Connecting...";
    socket->connectToHost("www.google.com",80);
    if(! socket->waitForConnected(3000)){
    qDebug()<<"Not C";
    }

    for(int aa=0; aa<15000000; aa++){
    };
   //socket->close();
}

void Soccket:: connected(){
    qDebug()<<"Connected!";

    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n\r\n\r\n");

}

void Soccket:: disconnected(){
    qDebug()<<"Disconnected";

}

void Soccket:: bytesWritten(qint64 bytes){
    qDebug()<<"Connecting..."<< bytes;

}

void Soccket:: readyRead(){
    qDebug()<<"Reading";
    qDebug()<<socket->readAll();

}
