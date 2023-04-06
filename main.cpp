#include <QCoreApplication>
#include <HeartBeat>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HeartBeat *heartBeat = new HeartBeat();

    return a.exec();
}
