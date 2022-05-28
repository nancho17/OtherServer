#include "serverthread.h"

ServerThread::ServerThread(QTcpServer *serv)
{
    socket = serv->nextPendingConnection();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ServerThread::sendData);
    sampleTime=0;
    timer->start(50);
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)) );


    //QTcpSocket *socket=server->nextPendingConnection();
}


#define S_TIME 0.001 //seconds
void ServerThread::run(){
    qDebug()<<"Thread starting";

    qDebug()<< "A\n\r";
    double variable_to_graph=0;
  
    if (false) {

        variable_to_graph = 1.4142* qSin((sampleTime) * 50 * 2 * M_PI );
        QByteArray data ((char *) &(variable_to_graph), sizeof(double));
        //qDebug()<< data;
        socket->write(data);
        socket->flush();

        //sample_time=sample_time+S_TIME;
        msleep(200);
    }

    /*
    socket->waitForBytesWritten(3000);
    msleep(1000);
    socket->write("Bye\n\r");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
*/
    exec();
}

void ServerThread::sendData(){

    //Paralel Gen
    for (size_t i = 0; i < 9; i++)
    {
    image.append (1.4142* qSin((sampleTime) * 50 * 2 * M_PI ));
    sampleTime=sampleTime+S_TIME;
    }
    //Protect
    //dataPacket.image_var[0]=1.6;
    //dataPacket.image_var[1]=2.7;
    //dataPacket.image_var[2]=3.8;
    //dataPacket.image_var[3]=4.9; image.size()
    memcpy( (char *) dataPacket.image_var, (char *) image.data(), image.size()*sizeof(double));
    dataPacket.validCount=image.size();
    image.clear();
    //qDebug()<<dataPacket.image_var;
    //Release

    QByteArray data ((char *) &dataPacket, sizeof(protocolStruct ));

    socket->write(data);
    socket->flush();


}

void ServerThread::bytesWritten(qint64 nBytes){
    qDebug()<<nBytes;
}
