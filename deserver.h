#ifndef DESERVER_H
#define DESERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "serverthread.h"

class Deserver : public QObject
{
    Q_OBJECT
public:
    explicit Deserver(QObject *parent = nullptr);
    QTcpServer * server;

signals:

public slots:
    void newConnection();
private:
};

#endif // DESERVER_H
