#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QSemaphore>
#include <QMutex>




typedef struct {
    uint8_t validCount;
    double imageVar[30];
    double timeVar[30];
}protocolStruct;

class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(QTcpServer *serv);
    void run();
    void sendData();
    //
    QTcpSocket *socket;

public slots:
    void bytesWritten(qint64);

private:
    QTimer *timer;
    QMutex *tMutex;
    QSemaphore * sem;
    double sampleTime;
    protocolStruct dataPacket;
    QVector <double> image;
    QThread timerThread;
};

#endif // SERVERTHREAD_H
