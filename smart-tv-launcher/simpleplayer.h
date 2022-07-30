/*
* VLC-Qt Simple Player
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*/

#ifndef SIMPLEPLAYER_H_
#define SIMPLEPLAYER_H_
#include <VLCQtCore/Audio.h>
#include <QWidget>
#include <VLCQtWidgets/WidgetVideo.h>
namespace Ui {
    class SimplePlayer;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class EqualizerDialog;

class SimplePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit SimplePlayer(int width, int height,QWidget *parent = 0);
    ~SimplePlayer();
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    VlcWidgetVideo *widgetVideo;

    void openLocal(QString path);
    void openUrl(QString url);
    void updateLayout(int width, int height);
    void on_openUrl_clicked();
    void stopPlayer();
private slots:


private:

 public slots:

private slots:
    void updateVolume();



};

#endif // SIMPLEPLAYER_H_
