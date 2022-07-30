#include "epgthread.h"
#include "QDebug"
#include "QDateTime"
#include "QNetworkRequest"
#include "QNetworkAccessManager"
#include "QNetworkReply"
EpgThread::EpgThread(QString epgPath, QStringList namess, QString epgUrl) :
  EPGpath(epgPath),  names(namess), EPGurl(epgUrl)
{

}
void EpgThread::run() //парсим распакованный egp.xml
{
    QString time =QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
    //QDateTime::currentDateTime();
  QStringList tmpy=time.split(".");
    QString yy = tmpy.at(0);

  QStringList tmpm =tmpy.at(1).split(".");
  QString mm= tmpm.at(0);
QString dd=time.remove(0,8);
         dd = dd.remove(dd.count()-9,9);
         QStringList tmp5 = time.split(":");
         QString hh= tmp5.at(0);
      hh=hh.remove(0,3);
         QString min = tmp5.at(1);
         QString sec = tmp5.at(2);
 // QString dd = tmpm.at(1);
         int curSec = sec.toInt();
         int curMin = min.toInt();
         int curHour = hh.toInt();
         QString ymdhm = yy+mm+dd+hh+min;
         qlonglong curYMDHM = ymdhm.toLongLong();
         qDebug()<<"TIMESTEPymdhm: "<<curYMDHM;
        // int curhhmm=hhmm.toInt();
         int curDay = dd.toInt();
         int curMonth = mm.toInt();


qDebug()<<"yyyy: "<<yy;
qDebug()<<"mm: "<<mm;
qDebug()<<"dd: "<<dd;

qDebug()<<"hh: "<<hh;
qDebug()<<"min: "<<min;
qDebug()<<"sec: "<<sec;

  //  names.append("!!!!!end");
    QFile epg(EPGpath+"epg.xml");
    if(epg.open(QIODevice::ReadOnly|QIODevice::Text)) {
      QString text = epg.readAll();
    datae = text.split("\n",QString::SkipEmptyParts);

    }
    epg.close();
  qDebug()<<"count"<<names.count();
           int c=0;

              // qDebug()<<"cycle1";

//qDebug()<<"curline:"<<curline;

while(c<=names.count()-1){
    for(int i=0; i<datae.count(); i++){
        QString curline = datae.at(i);
   if(curline.contains("<display-name>"+names.at(c)+"</display-name>", Qt::CaseInsensitive)){
      // m3u8.append(curline);
       qDebug()<<"idchanell: "<<curline;

       QStringList tmp1 = curline.split("id=");

    //
     //  qDebug()<<"TMP333: "<<tmp1;
     QStringList tmp2 = tmp1.at(1).split(">");
     QString tmp3 = tmp2.at(0);
 tmp3 =    tmp3.remove(0,1);
  tmp3=  tmp3.remove(tmp3.count()-1,3);
     qDebug()<<"TMP333: "<<tmp3;
     EGPid.append(tmp3);
 c=c+1;
 break;
   }
}
}

  // if(c==names.count()){
    //   break;
   //}
     //  }


           qDebug()<<"OKJ!: "<<EGPid;
         //  qDebug()<<"lastID: "<< ;

qDebug()<<"names.count: "<<names.count();
qDebug()<<"names"<<names;
EGPid.append("end");
//bool check = true;
    // int l=0;
           for(int l=0; l<EGPid.count()-1;){
     //    if(EGPid.at(l)==EGPid.at(EGPid.count()-1)) break;
            //   break;
              // if(l==EGPid.count()){
             //      break;
           //        check=false;
            //   }
           for(int i=0; i<datae.count(); i++){
               QString curline = datae.at(i);
             //  QString id =  EGPid.at(l);
               //  qDebug()<<"id: "<<id;
               if(curline.contains("channel=\""+ EGPid.at(l)+"\"><title", Qt::CaseInsensitive)){
                  // m3u8.append(curline);
       //           qDebug()<<"programLine: "<<curline;
                   for(int c=i;c<i+909; c++){
                       QString programline=datae.at(c);


                   if(programline.contains("channel=\""+EGPid.at(l) +"\"><title", Qt::CaseInsensitive)){
                                                    QStringList tmp1 = programline.split("stop=");

                                                    QString startTime =   tmp1.at(0);
                                                    startTime = startTime.remove(0,18);
                                                    startTime = startTime.remove(startTime.count()-10,10);
                                                    qlonglong ustartTime = startTime.toLongLong();//полное время


                                              QStringList tmp5  = tmp1.at(1).split("channel=");
                                                     QString stopTime = tmp5.at(0);
                                                     stopTime = stopTime.remove(0,1);
                                                    stopTime = stopTime.remove(stopTime.count()-10,10);//полное время
                                                           qlonglong ustopTime = stopTime.toLongLong();



                                         if(curYMDHM<ustopTime and curYMDHM>ustartTime){
                                         QString phm = stopTime.remove(0,8);
                                       QString ph=  phm.mid(0,2);
                                        QString pm=  phm.mid(2,2);
                                             QString prettyStoptime=ph+":"+pm;

                                             QString shm = startTime.remove(0,8);
                                           QString sh=  shm.mid(0,2);
                                            QString sm=  shm.mid(2,2);
                                                 QString prettyStarttime=sh+":"+sm;

                                             //qDebug() <<"pretty start"<<shour+":"+sminutes;
 //  qDebug()<<"programLine: "<<programline;
                                                 qDebug()<<"chanelID: "<< EGPid.at(l);
qDebug()<<"startTime: "<<prettyStarttime; // распарсили время старта
   qDebug()<<"stopTime: "<<prettyStoptime; // распарсили время стопа
  QStringList tmp11 =  programline.split("<title lang=");
  QString currentProgrammText = tmp11.at(1);
  currentProgrammText = currentProgrammText.remove(0,5);
    currentProgrammText = currentProgrammText.remove(currentProgrammText.count()-20,20);
    qDebug()<<"ProgramText: "<< currentProgrammText;
    startTimePretty.append(prettyStarttime);
    stopTimePretty.append(prettyStoptime);
    currentProgramm.append(currentProgrammText);

    QString nextProgramLine = datae.at(i+1);
    QStringList tmp12=  nextProgramLine.split("<title lang=");
    QString nextProgrammText = tmp12.at(1);
    nextProgrammText = nextProgrammText.remove(0,5);
      nextProgrammText = nextProgrammText.remove(nextProgrammText.count()-20,20);
      nextProgramm.append(nextProgrammText);
qDebug()<<"nexTPTEXT: "<<nextProgrammText;
    qDebug()<<"     \n";

    l=l+1;
       break;
                                         }

                                       }


                   }




               }

           }
//if(l==23) break;

                   }


           qDebug()<<"Suceful!";
           emit epgReadFinished();
}

QStringList EpgThread::getPStartTime()
{
    return startTimePretty;
}

QStringList EpgThread::getPStopTime()
{
    return stopTimePretty;
}

QStringList EpgThread::getCurProgramm()
{
    return currentProgramm;
}

QStringList EpgThread::getNextProgramm()
{
    return nextProgramm;
}

QStringList EpgThread::getEpgId()
{
   EGPid.removeAt(EGPid.count()-1);
   return EGPid;
}





