#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QKeyEvent>
#include <QSettings>
#include <QTimer>
#include <tvoverlay.h>
#include <zlib.h>
#include "QNetworkRequest"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "simpleplayer.h"
#include "setting.h"
#include "displayset.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTimer *timeShowOverlay;
bool fbtn = true;
virtual void keyPressEvent(QKeyEvent *event);
QSettings m3u8chanels;
private:
    Ui::Widget *ui;
    void updateIApps();
    bool fileExists(QString path);
    void iptv();
    QStringList data;

    QStringList datae;
Setting *wset;

    QWebEngineProfile *profile;
     QWebEnginePage *page;



DisplaySet *displaySettings;
    QStringList m3u8;
    QStringList names;
    QStringList currentProgram;
    QStringList nextProgram;
    QStringList startTime;
    QStringList stopTime;

    QString status="home";
    QStringList EPGid;
    QString EPGpath;
    QString EPGurl;
    QString PlayerType;
    int currentChannel=0;
      int countChannel=0;
      tvOverlay *overlay;
      void setEpgDataToOverlay(tvOverlay *overlay);
     int overlaySec=6000; //time show tv overlay in iptv app
QTimer * currentTimeUpdate;
SimplePlayer *player;
public slots:
void openDisplay();
      void openApplication();
      void toWebPage();
      void hideOverlay();
      void  updateEPG();
      void epgRead();
      void editStatus();
      void updateTime();
      void setOverscan();
      void reloadApp();
      void downloadEpgFinished(QNetworkReply *reply);
protected:

private slots:

      void on_pushButton_clicked();
      void on_pushButton_2_clicked();
};
#endif // WIDGET_H
