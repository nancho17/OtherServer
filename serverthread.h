#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>




typedef struct {
    uint8_t validCount;
    double image_var[10];
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
    double sampleTime;
    protocolStruct dataPacket;
    QVector <double> image;
};

#endif // SERVERTHREAD_H
