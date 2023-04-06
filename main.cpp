#include <QCoreApplication>
#include <HeartBeat>
#include "RunGuard.h"
int main(int argc, char *argv[])
{

    RunGuard guardCopyServer( "consoleWatcher" );
    if ( !guardCopyServer.tryToRun() ) {

        qDebug()<<"consoleWatcher уже запущен ";
        guardCopyServer.release();
        return 0;
    }

    RunGuard guardServer( "consoleWatcher" );
    guardServer.tryToRun();

    QCoreApplication a(argc, argv);
    HeartBeat *heartBeat = new HeartBeat();

    return a.exec();
}
