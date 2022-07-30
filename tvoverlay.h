#ifndef TVOVERLAY_H
#define TVOVERLAY_H

#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
namespace Ui {
class tvOverlay;
}

class tvOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit tvOverlay(int width, int height,QString PlayerType, QWidget *parent = nullptr);
    ~tvOverlay();
    QTimer * timeShowOverlay;
    QString ttype;
 void hideOverlay();
 void startTimer(int ms);
 void updateLayout(int width, int height,int Ol, int Or,int Ot,int Ob);
 int overlaySec;
 QString status;
 void setStatus(QString statuss);
 void setSec(int secc);
 void showOV();
 void setPickon(QString file);
 void setName(QString name);
 void setCurrentProgram(QString text);
  void setNextProgram(QString text);
    void setStartTimes(QString startt,QString stopt);
      //void setStopTime();
 void updateEPG(QString server);
private slots:


private:
    Ui::tvOverlay *ui;
  void  paintEvent(QPaintEvent*);

protected:
       virtual void keyPressEvent(QKeyEvent *event);
};

#endif // TVOVERLAY_H
