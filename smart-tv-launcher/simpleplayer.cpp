/*
* VLC-Qt Simple Player
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*/

#include <QFileDialog>
#include <QInputDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <QHBoxLayout>
#include <VLCQtCore/Audio.h>
#include "simpleplayer.h"


SimplePlayer::SimplePlayer(int width, int height,QWidget *parent)
    : QWidget(parent),
      _media(0)
{

  widgetVideo = new VlcWidgetVideo(this);
  QStringList args = VlcCommon::args();
  args <<" --audio-replay-gain-preamp 1.25";
    _instance = new VlcInstance(args, this);
    _player = new VlcMediaPlayer(_instance);
//      audio = new VlcAudio(_player);
    _player->setVideoWidget(widgetVideo);
    widgetVideo->setMediaPlayer(_player);

  //  audio->setVolume(125);
    QHBoxLayout * box = new QHBoxLayout(this);
    this->setLayout(box);
    box->setMargin(0);
    box->setSpacing(0);
    box->addWidget(widgetVideo);
    // widgetVideo->setGeometry(0,0,width,height);


  //  musicInstance = new VlcInstance(args);
   // musicPlayer = new VlcMediaPlayer(musicInstance);
    //musicMedia = new VlcMedia(filename,true,musicInstance);
    //musicPlayer->open(musicMedia);

  connect(_player,&VlcMediaPlayer::playing,this, &SimplePlayer::updateVolume);




}

SimplePlayer::~SimplePlayer()
{
    delete _player;
    delete _media;
    delete _instance;

}

void SimplePlayer::openLocal(QString path)
{
    _player->stop();
    _media = new VlcMedia(path, true, _instance);

    _player->open(_media);

}

void SimplePlayer::openUrl(QString url)
{


//_instance->setUserAgent("","Mozilla/5.0 WINK/1.31.1 (AndroidTV/7.1.1) HlsWinkPlayer");
    if (url.isEmpty())
        return;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
    //   _player->
   //  VlcAudio *audio = new VlcAudio(_player);
       //   audio->setVolume(140);

}

void SimplePlayer::updateLayout(int width, int height)
{
    _player->setVideoWidget(widgetVideo);
    widgetVideo->setMediaPlayer(_player);
         widgetVideo->setGeometry(0,0,width,height);
         this->setGeometry(0,0,width,height);
}

void SimplePlayer::on_openUrl_clicked()
{

}

void SimplePlayer::stopPlayer()
{
    _player->stop();
}

void SimplePlayer::updateVolume()
{
   //   audio->setVolume(140);
}
