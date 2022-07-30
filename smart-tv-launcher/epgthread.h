#ifndef EPGTHREAD_H
#define EPGTHREAD_H

#include <QThread>
#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class EpgThread : public QThread
{
    Q_OBJECT
public:
    EpgThread( QString epgPath,QStringList namess,QString epgUrl);
    void run();
    QStringList datae;
    QStringList EGPid;
QStringList currentProgramm;
QStringList nextProgramm;
QStringList startTimePretty;
QStringList stopTimePretty;

QStringList getPStartTime();
QStringList getPStopTime();
QStringList getCurProgramm();
QStringList getNextProgramm();
QStringList getEpgId();

private:
      QString EPGpath;
      QString EPGurl;
    QStringList names;
    QString name;   // Имя потока
public slots:

signals:
  void epgReadFinished();
};

#endif // EPGTHREAD_H
//https://www.stackfinder.ru/questions/5741657/error-decompressing-gzip-data-using-qt   zlib gzip
