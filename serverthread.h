#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>


class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(QTcpServer*serv);
    void run();
    //
    QTcpSocket *socket;
};

#endif // SERVERTHREAD_H
