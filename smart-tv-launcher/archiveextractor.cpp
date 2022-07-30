#include "archiveextractor.h"
#include "QDebug"
#include "QTimer"
archiveExtractor::archiveExtractor(QString pathToArchive, QString pathToUnpacked,int type,QObject *parent): pathToArchiveF(pathToArchive), pathToUnpackedF(pathToUnpacked),  typeF(type)
,QObject(parent)
{
    mainArchiver = new QProcess(this);
//mainArchiver->setWorkingDirectory(pathToArchiveF);
    if(type==zip){
mainArchiver->start("bash -c \"unzip "+pathToArchiveF+" -d "+pathToUnpackedF+"\"");
    }else if(type==gzip){
       mainArchiver->start("bash -c \"unzip "+pathToArchiveF+" -d "+pathToUnpackedF+"\"");
    }
      //QObject::connect(mainArchiver, SIGNAL(finished(int, QProcess::exitStatus)), this, SLOT(finished()));
qDebug()<<"unpacking!";
timer = new QTimer(this);
connect(timer,&QTimer::timeout,this,&archiveExtractor::finished);
timer->setInterval(200);
timer->start();


//QObject::connect(mainArchiver, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &archiveExtractor::finished);
}

void archiveExtractor::finished()
{
    if(mainArchiver->state() == QProcess::NotRunning){
     qDebug()<<"Extracted!!!;";
     emit onArchiveExtracted();
     timer->stop();
    }

    //      qDebug()<<"Archive EXTRACT SUC!";

}






//https://forum.qt.io/topic/78593/shell-commands-on-android
