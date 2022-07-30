#include "tvoverlay.h"
#include "ui_tvoverlay.h"
#include "QStandardPaths"
#include "QDir"
#include "QFile"
#include "QFileInfo"
#include "QDateTime"
tvOverlay::tvOverlay(int width,int height,QString PlayerType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tvOverlay)
{
    ttype = PlayerType;
    ui->setupUi(this);
   // this->setWindowOpacity(0);
 //   this->showFullScreen();
    ui->end_time->setGeometry(width-73,72,71,21);
    ui->progressBar->setGeometry(208,74,width-280,20);
    timeShowOverlay = new QTimer(this);
    connect(timeShowOverlay,&QTimer::timeout,this,&tvOverlay::hideOverlay);
    hideOverlay();

   }



void tvOverlay::paintEvent(QPaintEvent*)
{

}
tvOverlay::~tvOverlay()
{
    delete ui;
}

void tvOverlay::hideOverlay()
{
    //ui->main_overlay->hide();

   if(ttype=="libvlc"){
          this->hide();
   }else{
       ui->main_overlay->hide();
   }
 }

void tvOverlay::startTimer(int ms)
{
    timeShowOverlay->setInterval(ms);
    timeShowOverlay->start();
}

void tvOverlay::updateLayout(int width, int height,int Ol, int Or,int Ot,int Ob)
{
    if(ttype=="libvlc"){
     this->setGeometry(0,height-149,width,149);
    }else{
            this->setGeometry(Ol,Ot,width-(Ol+Or),height-(Ot+Ob));
    }
    ui->end_time->setGeometry(width-73-Or-Ol,72,71,21);
    ui->progressBar->setGeometry(208+Ol-Or,74,width-295-(Ol+Or),20);
    ui->chanel->setGeometry(136,8,width-136,31);
     ui->current_programm->setGeometry(136,35,width-136,31);
          ui->next_programm->setGeometry(225,95,width-225,31);





}

void tvOverlay::setStatus(QString statuss)
{
    status=statuss;
}

void tvOverlay::setSec(int secc)
{
    overlaySec=secc;
}

void tvOverlay::showOV()
{

    if(ttype=="libvlc"){
            this->show();
    }else{
        ui->main_overlay->show();
    }
}

void tvOverlay::setPickon(QString file)
{
            QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QPixmap image (path+"/apps/iptv/Picks/"+file);
    QPixmap pickon = image.scaled(QSize(119,119),  Qt::KeepAspectRatio);

 ui->chanel_pick->setPixmap(pickon);

}

void tvOverlay::setName(QString name)
{
    ui->chanel->setText(name);
}

void tvOverlay::setCurrentProgram(QString text)
{
    ui->current_programm->setText(text);
}

void tvOverlay::setNextProgram(QString text)
{
    ui->next_programm->setText(text);
}

void tvOverlay::setStartTimes(QString startt,QString stopt)
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


    long curt = hh.toLong()+min.toLong();

    ui->start_time->setText(startt);
    ui->end_time->setText(stopt);
    QStringList stime = startt.split(":");
    QStringList etime = stopt.split(":");

    long stimen = stime.at(0).toLong()+stime.at(1).toLong();
    long sstopn = etime.at(0).toLong()+etime.at(1).toLong();
    long val = sstopn-stimen;
    ui->progressBar->setMaximum(val);
    long s = sstopn - curt;
    long sval = val - s;
    ui->progressBar->setValue(sval);



}



void tvOverlay::keyPressEvent(QKeyEvent *event) { //HOME
 int key=event->key();
 if(key==Qt::Key_D){
      if(status=="iptv"){
        this->show();
          //  updateLayout(this->geometry().size().width(),this->geometry().size().height(),);
                startTimer(overlaySec);
      }
  }
}
