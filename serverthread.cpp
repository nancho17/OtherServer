#include "serverthread.h"

ServerThread::ServerThread(QTcpServer *serv)
{
    sem = new QSemaphore(1);
    tMutex=new QMutex;
    socket = serv->nextPendingConnection();
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    //timerThread.start();
    //timer->moveToThread(&timerThread);
    timer = new QTimer;
    QObject::connect(timer,  &QTimer::timeout,               this,&ServerThread::sendData );
    timer->start(5);


   }


//ServerThread::~ServerThread(){}

void ServerThread::run()
{
    exec();
}


// Fake simulation 25 samples per 5 miliseconds
#define S_TIME  0.0002 // 200 microseconds sample period

void ServerThread::sendData()
{

    if (image.size() > 0)
    {
        memcpy((char *)dataPacket.imageVar, (char *)image.data(), image.size() * sizeof(double));
        dataPacket.validCount = image.size();
        image.clear();
        QByteArray data((char *)&dataPacket, sizeof(protocolStruct));
        socket->write(data);
        socket->flush();
    }

    // Fake simulation pre-store 25 samples
    // TODO: Prepare vector in other thread
    for (size_t i = 0; i < 25; i++)
    {
        image.append(1.4142 * qSin((sampleTime)*50 * 2 * M_PI));
        sampleTime = sampleTime + S_TIME;
    }

}

void ServerThread::bytesWritten(qint64 nBytes)
{
    qDebug() << nBytes;
}
