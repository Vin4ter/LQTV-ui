#ifndef ARCHIVEEXTRACTOR_H
#define ARCHIVEEXTRACTOR_H

#include <QObject>
#include <QProcess>
#include <QThread>
#include <QTimer>
class archiveExtractor : public QObject
{
    Q_OBJECT
    const int zip=0;
    const int gzip=1;
        //const int gzip=1;
public:
    explicit archiveExtractor(QString pathToArchive, QString pathToUnpacked, int type, QObject *parent = nullptr);
QTimer *timer;
QProcess *mainArchiver;
private:
QString pathToArchiveF;
QString pathToUnpackedF;
int typeF;
signals:
void onArchiveExtracted();


public slots:
        void finished();
};

#endif // ARCHIVEEXTRACTOR_H
