#include <QCoreApplication>
#include <deserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Deserver Mserver;

    return a.exec();
}
