#include "setupdesktop.h"
#include "ui_setupdesktop.h"
#include "QMovie"
#include "zlib.h"
#include "QNetworkAccessManager"
#include "archiveextractor.h"
#include "QStandardPaths"
#include "QDir"
#include "QFile"
#include "QFileInfo"

setupDesktop::setupDesktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setupDesktop)
{

    ui->setupUi(this);
       QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
               QString configsp = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QMovie *movie = new QMovie(":/res/cicles.gif");
    //QLabel *processLabel = new QLabel(this);
    ui->lprocess_2->setMovie(movie);
    movie->start();
    QFileInfo configs(path+"/configs.zip");
    if(configs.exists()){
        ui->label_2->setText("extact Addons");
        archiveExtractor *extractor = new archiveExtractor(path+"/configs.zip",configsp+"/",0);
        connect(extractor,&archiveExtractor::onArchiveExtracted,this,&setupDesktop::unpacked);
    }else{
           ui->label_2->setText("download addons");
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://github.com/Vin4ter/LWTV-ui/releases/download/v0.1-alpha/standardConfigs.zip"); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    manager->get(request);      // Выполняем запрос
 qDebug() << "Downloading is start";

    connect(manager, &QNetworkAccessManager::finished, this, &setupDesktop::downloadFinished);
}
}

setupDesktop::~setupDesktop()
{
    delete ui;
}

void setupDesktop::downloadFinished(QNetworkReply *reply)
{

     qDebug() << "Downloading is completed";
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        QString configsp = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QFile *file = new QFile(path+"/configs.zip");
          // Создаём файл или открываем его на перезапись ...
          if(file->open(QFile::WriteOnly)){
              file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
              file->close();                  // закрываем файл

          //emit onReady(); // Посылаем сигнал о завершении получения файла
          }
            ui->label_2->setText("extact Addons");
   archiveExtractor *extractor = new archiveExtractor(path+"/configs.zip",configsp+"/",0);
   connect(extractor,&archiveExtractor::onArchiveExtracted,this,&setupDesktop::unpacked);
}

void setupDesktop::unpacked()
{
      ui->label_2->setText("complete!");
    qDebug()<<"unpacked GOod";
    emit onComplete();
}
