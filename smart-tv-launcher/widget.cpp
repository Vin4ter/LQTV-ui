#include "widget.h"
#include "ui_widget.h"
#include "appitem.h"
#include "QStandardPaths"
#include "QDebug"
#include "QSettings"
#include "QFont"
#include "QFontDatabase"
#include "QMessageBox"
#include <QWebEngineSettings>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include <tvoverlay.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegExp>
#include <epgthread.h>
#include "QDateTime"
#include <zip.h>
#include <archiveextractor.h>
#include <setupdesktop.h>
#include <QMovie>
#include <setting.h>
#include <displayset.h>

//#include <VLCQtCore/>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)

{
    ui->setupUi(this);

    //QSettings *wsetconf = new QSettings(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/main.conf",QSettings::IniFormat);

    //QMovie *movie = new QMovie(":/res/progress.gif");
   // QLabel *processLabel = new QLabel(this);
   // processLabel->setMovie(movie);
  //  movie->start();
//extractor->run();
    //QProcess *proc = new QProcess(this);
   // mainArchiver
//    proc->start("bash -c \"unzip /home/alexey/app-data.zip -d /home/alexey/app-data!!!!\"");
          // _media = new VlcMedia("http://50.7.92.90/HD_Kino/mono.m3u8", _instance);
         //  _player->open(_media);

   //   ui->stackedWidget->setCurrentIndex(4);

/*
    libvlc_instance_t * inst;
       libvlc_media_player_t *mp;
       libvlc_media_t *m;

            // Load the VLC engine
            inst = libvlc_new(0, NULL);

            // Create a new item

            m = libvlc_media_new_path (inst, "/home/alexey/music.mp3");

            // Create a media player playing environement
            mp = libvlc_media_player_new_from_media (m);

            // play the media_player
            libvlc_media_player_play (mp);

*/

    const int zip=0;
    const int gzip=1;
    //archiveExtractor *extractor = new archiveExtractor("/home/alexey/app-data.zip","/home/alexey/app-data!!!!",zip,this);
QString pathw = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    profile = new QWebEngineProfile("webview");
     profile->setHttpUserAgent("Roku/DVP-9.30 (309.30E04182A)");
     profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
   profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
   profile->setCachePath(pathw+"/webview/cache");
   profile->setPersistentStoragePath(pathw+"/webview/storage");
  page = new QWebEnginePage(profile);


             ui->webView->setPage(page);



currentTimeUpdate = new QTimer(this);
connect(currentTimeUpdate,&QTimer::timeout,this,&Widget::updateTime);
currentTimeUpdate->setInterval(1000);
currentTimeUpdate->start();



EPGpath=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/apps/iptv/EPG/";
QSettings sets(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/apps/iptv/addon.conf",QSettings::IniFormat);
sets.beginGroup("app");
EPGurl=sets.value("EPG_url").toString();
PlayerType = sets.value("usingVideoPlayer").toString();
sets.endGroup();

//http://epg.it999.ru/epg.xml
    ui->stackedWidget->setCurrentIndex(0);
  ui->appLayout->setAlignment(Qt::AlignLeft);
    ui->gameLayout->setAlignment(Qt::AlignLeft);

  //  appItem *al = new appItem("test123");
   // ui->appLayout->addWidget(al);
    //QString iconpath = ;
    //qDebug()<< iconpath;
  QFontDatabase::addApplicationFont(":/res/font/Nunito-Bold.ttf");
  ui->appLayout->setSpacing(-3);
  ui->appLayout->setMargin(0);
  QFontDatabase db;
  QFont nunito("Nunito");
  ui->label->setFont(nunito);

 // QString family = QFontDatabase::applicationFontFamilies(id).at(1);
 // QFont monospace(family);
 // ui->label->setFont(monospace);

    updateIApps();
    wset = new Setting(this->geometry().size().height(),this);
    wset->setGeometry(this->geometry().size().width()-346,0,346,this->geometry().size().height());
    displaySettings = new DisplaySet(this);
    displaySettings->setGeometry(this->geometry().size().width()-346,0,346,this->geometry().size().height());
    displaySettings->hide();
    //init overscan
ui->overscanUi->setContentsMargins(displaySettings->getLeft(),displaySettings->getTop(), displaySettings->getRight(), displaySettings->getBottom());
    wset->hide();
connect(displaySettings,&DisplaySet::onEdit,this,&Widget::setOverscan);
    overlay = new tvOverlay(this->geometry().size().width(), this->geometry().size().height(),PlayerType,this);
    overlay->hide();
    overlay->setSec(overlaySec);
    player = new SimplePlayer(this->geometry().size().width(),this->geometry().size().height(),this);
   player->updateLayout(this->geometry().size().width(),this->geometry().size().height());
   ui->playerLayout->addWidget(player);
  // player->hide();

   QFileInfo info(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/apps.conf");
   if(info.exists()==true){
       qDebug()<<"exist okey";


   }else{
  // setupDesktop* wsetup = new setupDesktop(this);
  // wsetup->setGeometry(0,0,1366,768);
  // wsetup->show();
       setupDesktop *desk = new setupDesktop(this);
       desk->setGeometry(0,0,this->geometry().size().width(),this->geometry().size().height());
       desk->show();
       connect(desk, &setupDesktop::onComplete,this,&Widget::reloadApp);
   }

}

Widget::~Widget()
{
    delete ui;
}

//unpack .gzip for epg from server
QByteArray gUncompress(const QByteArray &data)
{
    if (data.size() <= 4) {
        qWarning("gUncompress: Input data is truncated");
        return QByteArray();
    }

    QByteArray result;

    int ret;
    z_stream strm;
    static const int CHUNK_SIZE = 1024;
    char out[CHUNK_SIZE];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = data.size();
    strm.next_in = (Bytef*)(data.data());

    ret = inflateInit2(&strm, 15 +  32); // gzip decoding
    if (ret != Z_OK)
        return QByteArray();

    // run inflate()
    do {
        strm.avail_out = CHUNK_SIZE;
        strm.next_out = (Bytef*)(out);

        ret = inflate(&strm, Z_NO_FLUSH);
        Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

        switch (ret) {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;     // and fall through
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&strm);
            return QByteArray();
        }

        result.append(out, CHUNK_SIZE - strm.avail_out);
    } while (strm.avail_out == 0);

    // clean up and return
    inflateEnd(&strm);
    return result;
}





//zip.h









void Widget::updateIApps()
{
    QString pathd=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+"/apps/";
    QDir dir(pathd);
     QFileInfoList dirContent = dir.entryInfoList(QStringList(),
            QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
  qDebug()<<dirContent;
bool abtn=false;
  for(int i=0;i<dirContent.count();i++){
    QFileInfo df(dirContent.at(i));
  qDebug()<< pathd+df.fileName()+"/addon.conf";
  QSettings apps(pathd+df.fileName()+"/addon.conf", QSettings::IniFormat);
   apps.beginGroup("app");
  QString icons = pathd+df.fileName()+"/"+apps.value("icon").toString();
  qDebug()<<"icons: "<<icons;
    QString program = apps.value("program").toString();
  QString paths = apps.value("path").toString();
  int types = apps.value("type").toInt();
  qreal scales = apps.value("scale").toReal();
  //int type =
  if(program=="game"){
   appItem *item = new appItem(icons,  paths, types, scales,program);
   ui->gameLayout->addWidget(item);
   connect(item, &appItem::clicked,this, &Widget::openApplication);
   connect(item, &appItem::editStatus,this, &Widget::editStatus);

  }else{

   appItem *item = new appItem(icons,  paths, types, scales,"app");
   ui->appLayout->addWidget(item);
   connect(item, &appItem::clicked,this, &Widget::openApplication);
   connect(item, &appItem::editStatus,this, &Widget::editStatus);
   if(abtn==false){
       item->setFocus();
       abtn=true;
   }
  }


 apps.endGroup();


     }






}

void Widget::iptv()
{
    status="iptv";
         overlay->setStatus("iptv");
         overlay->show();
         overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());

 //tvOverlay *overlay = new tvOverlay(this->geometry().size().width(), this);
   // overlay->showFullScreen();
  //  overlay->setGeometry(0,0,this->geometry().size().width(),this->geometry().size().height());
    //overlay->show();
  QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if(QFileInfo::exists(path+"/apps/iptv/playlist/playlist.m3u")){
qDebug()<<path;
        QFile file(path+"/apps/iptv/playlist/playlist.m3u");
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
          QString text = file.readAll();
        data = text.split("\n",QString::SkipEmptyParts);

        }
        file.close();

     //  qDebug()<<"data: "<<data;

     //   QRegExp exp("(#EXTINF:)");
        for(int i=0; i<data.count(); i++){
        QString curline = data.at(i);
        if(curline.contains("#EXTINF", Qt::CaseInsensitive)){
         //   qDebug()<<"curline: "<<curline;
            QStringList tmp1;
            tmp1 = curline.split(",");
            qDebug()<<"name"<<tmp1.at(1);
            names.append(tmp1.at(1));

            countChannel=countChannel+1;
        }
        if(curline.contains("https://", Qt::CaseInsensitive)){
            m3u8.append(curline);
            qDebug()<<"m3u8: "<<curline;
        }else if(curline.contains("http://", Qt::CaseInsensitive)){
              m3u8.append(curline);
              qDebug()<<"m3u8: "<<curline;
           }

        //QStringList tmp1 = curline.split(",");
      // names.append(tmp1.at(1));
       // qDebug()<<"name: "<<curline;
        }

        // qDebug()<<"name: "<<names;
      updateEPG();
       if(PlayerType=="libvlc"){

        //   _media = new VlcMedia(m3u8.at(currentChannel), _instance);
           //_player->open(_media);

      // player->show();
  //  player->updateLayout(this->geometry().size().width(),this->geometry().size().height());

           ui->stackedWidget->setCurrentIndex(3);
      player->openUrl(m3u8.at(currentChannel));

       }else if(PlayerType=="qwebview"){
    //       QWebEngineProfile *profile = new QWebEngineProfile(this);

          //profile->setHttpUserAgent("Mozilla/5.0 (SMART-TV; Linux; Tizen 2.3) AppleWebkit/538.1 (KHTML%2C like Gecko) SamsungBrowser/1.0 TV Safari/538.1");
      //    QWebEnginePage *page = new QWebEnginePage(profile);


                  //ui->webViewIptv->setPage(page);
    ui->webViewIptv->load(QUrl("file://"+path+"/apps/iptv/index.html?m3u8="+m3u8.at(currentChannel)));
       // overlay->show();
   }
    }
  //

}

void Widget::setEpgDataToOverlay(tvOverlay *overlay)
{
    if(!currentProgram.isEmpty()){
    overlay->setCurrentProgram(currentProgram.at(currentChannel));
        overlay->setNextProgram(nextProgram.at(currentChannel));
           overlay->setStartTimes(startTime.at(currentChannel),stopTime.at(currentChannel));
             //   overlay->setStopTime(stopTime.at(currentChannel));
    }
}

void Widget::openDisplay()
{
    displaySettings->setGeometry(this->geometry().size().width()-346-displaySettings->getRight(),displaySettings->getTop(),346,this->geometry().size().height()-(displaySettings->getBottom()+displaySettings->getTop()));
    displaySettings->showPage();

   // status="displaySettings";
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if path exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}

void Widget::openApplication()
{
      appItem* item = qobject_cast<appItem*>(sender());
 //   int id = item->getID();

 if(item->getType()==0){ //webApp url internet
     item->setLoadingSlate(true);
    page->setZoomFactor(item->getScaleFactor());
 connect(ui->webView,&QWebEngineView::loadFinished,this, &Widget::toWebPage);
   if(item->getPath().contains("https://", Qt::CaseInsensitive) or item->getPath().contains("http://", Qt::CaseInsensitive) ){
    ui->webView->load(QUrl(item->getPath()));
   }else{ //load local app
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
  ui->webView->load(QUrl("file://"+path+"/apps/"+item->getPath()));
   }

}else if(item->getType()==3){ //default apps
 if(item->getPath()=="iptv"){



//QWebEngineProfile *profile = new QWebEngineProfile(this);
//profile->setHttpUserAgent("Mozilla/5.0 (SMART-TV; Linux; Tizen 2.3) AppleWebkit/538.1 (KHTML%2C like Gecko) SamsungBrowser/1.0 TV Safari/538.1");
//QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
QWebEngineSettings *wsettings  =	QWebEngineSettings::defaultSettings();
wsettings->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
wsettings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
//.setAttribute(QtWebEngineWidgets.QWebEngineSettings.LocalContentCanAccessRemoteUrls, True)
//QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::all, false);

//QWebEnginePage *page = new QWebEnginePage(profile);


//QWebEngineSettings set();
//set.setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, False);

     //  ui->webViewIptv->setPage(page);
//connect(ui->webViewIptv,&QWebEngineView::loadFinished,this, &Widget::toWebPage);

  //
  if(PlayerType=="libvlc"){


  }else if(PlayerType=="qwebview"){
   ui->stackedWidget->setCurrentIndex(2);
  }
   iptv();
 }else if(item->getPath()=="kodi"){
  QProcess *kodi = new QProcess(this);
  kodi->start("bash -c \"kodi\"");
 }
 }

}

void Widget::toWebPage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::hideOverlay()
{

}

void Widget::updateEPG()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(EPGurl); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    manager->get(request);      // Выполняем запрос

    connect(manager, &QNetworkAccessManager::finished, this, &Widget::downloadEpgFinished);




    //   qDebug()<<"EPG: "<<datae;
}

void Widget::downloadEpgFinished(QNetworkReply *reply)
{
    if(reply->error()){
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        qDebug()<<"download ok!";
        QByteArray byte = reply->readAll();
        QByteArray uncompressed = gUncompress(byte);
if(QFileInfo::exists(EPGpath+"epg.xml")==true){
    QDir dir;
     dir.remove(EPGpath+"epg.xml");
}
    QFile file(EPGpath+"epg.xml");


           if(file.open(QFile::WriteOnly)){
               file.write(uncompressed); //запись распакованного epg.xml
               file.close();
    }
    EpgThread *epgThread = new  EpgThread(EPGpath,names,EPGurl);
    epgThread->start();
    connect(epgThread,&EpgThread::epgReadFinished,this,&Widget::epgRead);

    }
    }




void Widget::epgRead()
{
    EpgThread* epgThread = qobject_cast<EpgThread*>(sender());
 currentProgram = epgThread->getCurProgramm();
  nextProgram = epgThread->getNextProgramm();
    startTime = epgThread->getPStartTime();
        stopTime = epgThread->getPStopTime();
   delete epgThread;

}

void Widget::editStatus()
{
     appItem* item = qobject_cast<appItem*>(sender());
     status=item->getStatus();
     qDebug()<<"status: "<<status;
}

void Widget::updateTime()
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

   ui->time_label->setText(hh+":"+min);
}

void Widget::setOverscan()
{
//  ui->widget->layout()->setContentsMargins
ui->overscanUi->setContentsMargins(displaySettings->getLeft(),displaySettings->getTop(), displaySettings->getRight(), displaySettings->getBottom());
   // displaySettings->getTop();
    //displaySettings->getLeft();
    //displaySettings->getRight();
//update layout
 wset->setGeometry(this->geometry().size().width()-346-displaySettings->getRight(),displaySettings->getTop(),346,this->geometry().size().height()-(displaySettings->getBottom()+displaySettings->getTop()));
 displaySettings->setGeometry(this->geometry().size().width()-346-displaySettings->getRight(),displaySettings->getTop(),346,this->geometry().size().height()-(displaySettings->getBottom()+displaySettings->getTop()));
}

void Widget::reloadApp()
{
  Widget *main = new Widget();
  main->showFullScreen();
 this->close();
}



void Widget::keyPressEvent(QKeyEvent *event) { //HOME
 int key=event->key();//event->key() - целочисленный код клавиши
 if (key==Qt::Key_HomePage) {
     //BackSpace стирает символ
        ui->stackedWidget->setCurrentIndex(0);
       ui->webViewIptv->load(QUrl(""));
 ui->webView->load(QUrl("https://"));
     overlay->hide();
     overlay->hideOverlay();
     overlay->setStatus("home");

     this->showFullScreen();

      if(status=="settings"){

       displaySettings->hide();
        wset->hide();
      }
      appItem *item= qobject_cast<appItem*>(ui->appLayout->itemAt(0)->widget());
        item->setFocus();
         status="home";
 }else if(key==Qt::Key_Up){
    if(status=="iptv"){
if(currentChannel<countChannel-1){
        currentChannel=currentChannel+1;
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        if(PlayerType=="libvlc"){
          //  _media = new VlcMedia(m3u8.at(currentChannel), _instance);

         //   _player->open(_media);
            player->openUrl(m3u8.at(currentChannel));
        }else if(PlayerType=="qwebview"){

        ui->webViewIptv->load(QUrl("file://"+path+"/apps/iptv/index.html?m3u8="+m3u8.at(currentChannel)));
        }

       overlay->showOV();
         overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());
         overlay->setPickon(names.at(currentChannel)+".png");
          overlay->setName(names.at(currentChannel));
          setEpgDataToOverlay(overlay);
       overlay->startTimer(overlaySec);
    }else{
    currentChannel=0;
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if(PlayerType=="libvlc"){
     //   _media = new VlcMedia(m3u8.at(currentChannel), _instance);
    //      player->stopPlayer();
 player->openUrl(m3u8.at(currentChannel));
       // _player->open(_media);
  //player->audio->setVolume(140);
    }else if(PlayerType=="qwebview"){
    ui->webViewIptv->load(QUrl("file://"+path+"/apps/iptv/index.html?m3u8="+m3u8.at(currentChannel)));
    }
   overlay->showOV();
   overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());
   overlay->setPickon(names.at(currentChannel)+".png");
    overlay->setName(names.at(currentChannel));
 setEpgDataToOverlay(overlay);
          overlay->startTimer(overlaySec);
}
 }
}else if(key==Qt::Key_Down){
     if(status=="iptv"){
         if(currentChannel<1){
         currentChannel=countChannel-1;
         QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
         if(PlayerType=="libvlc"){
      //       _media = new VlcMedia(m3u8.at(currentChannel), _instance);
 player->openUrl(m3u8.at(currentChannel));
         //    _player->open(_media);
 // player->audio->setVolume(140);
         }else if(PlayerType=="qwebview"){
         ui->webViewIptv->load(QUrl("file://"+path+"/apps/iptv/index.html?m3u8="+m3u8.at(currentChannel)));
         }
        overlay->showOV();
           overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());

          overlay->setPickon(names.at(currentChannel)+".png");
           overlay->setName(names.at(currentChannel));
            setEpgDataToOverlay(overlay);
               overlay->startTimer(overlaySec);
 //player->audio->setVolume(140);
         }else{

             currentChannel=currentChannel-1;
             QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
             if(PlayerType=="libvlc"){
        //         _media = new VlcMedia(m3u8.at(currentChannel), _instance);
      //           player->stopPlayer();
 player->openUrl(m3u8.at(currentChannel));
         //        _player->open(_media);
 //player->audio->setVolume(140);
             }else if(PlayerType=="qwebview"){
             ui->webViewIptv->load(QUrl("file://"+path+"/apps/iptv/index.html?m3u8="+m3u8.at(currentChannel)));
             }
            overlay->showOV();
            overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());
              overlay->setPickon(names.at(currentChannel)+".png");
               overlay->setName(names.at(currentChannel));
                setEpgDataToOverlay(overlay);
                   overlay->startTimer(overlaySec);

         }
     }else if(status=="home_app"){

     //      appItem *item =// ui->gameLayout->itemAt(i)->widget());
    appItem *item= qobject_cast<appItem*>(ui->gameLayout->itemAt(0)->widget());
      item->setFocus();
      //break;

     }
 }else if(key==Qt::Key_Return){
     if(status=="iptv"){
       overlay->showOV();
       overlay->setPickon(names.at(currentChannel)+".png");
        overlay->setName(names.at(currentChannel));
          overlay->updateLayout(this->geometry().size().width(),this->geometry().size().height(),displaySettings->getLeft(),displaySettings->getRight(),displaySettings->getTop(),displaySettings->getBottom());
          setEpgDataToOverlay(overlay);
             overlay->  startTimer(overlaySec);
     }
 }else if(key==Qt::Key_PowerOff){
  qDebug()<<"poweroff";
  QProcess *shutdown = new QProcess(this);
  shutdown->start("bash -c \"systemctl poweroff\"");
 }
}



 //   QMediaPlayer *player = new QMediaPlayer(this);
 // QVideoWidget *videoWidget = new QVideoWidget(this);
  //  videoWidget->setSizeIncrement(900,900);
   // player->setVideoOutput(videoWidget);
 //ui->videoLayout->addWidget(videoWidget);

   // player->setMedia(QUrl::fromLocalFile("/home/alexey/video.mp4"));
   // player->play();



void Widget::on_pushButton_clicked()
{
wset->setGeometry(this->geometry().size().width()-346-displaySettings->getRight(),displaySettings->getTop(),346,this->geometry().size().height()-(displaySettings->getBottom()+displaySettings->getTop()));
    wset->showPage();

 status="settings";
    connect(wset,&Setting::onopenDisplay,this,&Widget::openDisplay);

}

void Widget::on_pushButton_2_clicked()
{
    QProcess *shutdown = new QProcess(this);
    shutdown->start("bash -c \"systemctl poweroff\"");
}
