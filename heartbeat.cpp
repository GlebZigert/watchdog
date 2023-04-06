#include "HeartBeat"
#include <QIODevice>
#include <QFileInfo>
#include <RunGuard.h>

HeartBeat::HeartBeat(QObject *parent)

{
    qDebug()<<"HeartBeat::HeartBeat(QObject *parent)";

    connect(&reload, SIGNAL(timeout()), this, SLOT(do_reload()));





   if(this->listen(QHostAddress::Any,1974)){
       qDebug()<<"слушаем порт "<<1974;
   }   else{
       qDebug()<<"сервер heartbeat не запустился.";
   }







   reload.start(1000);
}

void HeartBeat::sockReady()
{
//qDebug()<<"sockReady";


        Data = socket->readAll();

   //      qDebug()<<(QString)Data;
         reload.stop();
         reload.start();

}

void HeartBeat::sockDisc()
{

}

void HeartBeat::do_reload()
{

/*
qDebug()<<"do_reload";

    QString pathToExecutable = QString("/opt/Rif+/m_server");

        // Check the path string was written correctly and Qt can see it
        QFileInfo fileInfo(pathToExecutable);

        QProcess *process = new QProcess(this);

        if (fileInfo.exists())
        {
            if(fileInfo.isExecutable())
            {
                QObject::connect(process, &QProcess::errorOccurred,
                    process, [&]()
                {
                    qWarning() << process->errorString();
                });


                QString executableDir = fileInfo.absolutePath();
                process->setWorkingDirectory(executableDir);

                QString absuluteExecutableFilePath = fileInfo.absoluteFilePath();



                // If you need to check errors, use start(), but not startDetached()
                qDebug()<<"absuluteExecutableFilePath "<<absuluteExecutableFilePath;
                QProcess p;
                p.start("pkill m_server");
                p.waitForFinished();
                process->start(absuluteExecutableFilePath, QStringList());
              //  process.waitForFinished(1);
            }
            else
            {
                qWarning() << "Given file is not executable";
            }
        }
        else
        {
            qWarning() << "File path does not exist or is set incorrectly";
        }
*/

    QProcess p;
    p.start("pkill m_server");
    p.waitForFinished();


    qDebug()<<"do_reload";
 //       QProcess::execute("/opt/Rif+/m_server > /home/master/1.txt");
    delete(process);
    process = new QProcess(this);
    QString file = QString("/opt/Rif+/m_server" );

process->setReadChannel(QProcess::StandardOutput);
process->setProcessChannelMode(QProcess::ForwardedChannels);


//process->setProcessChannelMode( QProcess::ForwardedOutputChannel );
connect(process, SIGNAL(started()), this, SLOT(processStarted()));
connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
connect(process, SIGNAL(finished(int)), this, SLOT(encodingFinished(int)));

/*
process->connect(process,&QProcess::readyReadStandardOutput,[=]{
        qDebug()<<"new Data:";
        qDebug().noquote()<<process->readAll();
    });

*/
 //   connect( process, SIGNAL( finished( int, QProcess::ExitStatus ) ),
 //            this, SLOT( onProgramFinished( int, QProcess::ExitStatus ) ), Qt::DirectConnection );

process->start(file, QStringList(),QIODevice::ReadWrite);

}

void HeartBeat::read()
{
qDebug()<<"read";
}

void HeartBeat::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<" Client connected";
    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
}

void HeartBeat::processStarted()
{
    qDebug()<<"HeartBeat::processStarted()";
}

void HeartBeat::readyReadStandardOutput()
{
     qDebug()<<"HeartBeat::readyReadStandardOutput()";
}

void HeartBeat::encodingFinished(int)
{
      qDebug()<<"HeartBeat::encodingFinished(int)";
}
