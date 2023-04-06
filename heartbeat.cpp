#include "HeartBeat"

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
    QProcess p;
    p.start("pkill m_server");
    p.waitForFinished();


    qDebug()<<"do_reload";
 //       QProcess::execute("/opt/Rif+/m_server > /home/master/1.txt");
    QProcess *process = new QProcess(this);
    QString file = QString("/opt/Rif+/m_server" );
#if (defined (_WIN32) || defined (_WIN64))
    // windows code
    file.append(".exe");
#endif



    process->start(file, QStringList());
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
