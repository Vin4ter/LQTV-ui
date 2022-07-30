#ifndef APPITEM_H
#define APPITEM_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QEvent>
#include <QFocusEvent>
class appItem : public QPushButton
{
    Q_OBJECT
public:
   explicit appItem(QString icons, QString paths, int types, qreal scales,QString appType, QPushButton *parent = nullptr);
    int type=0; //0-webApp url, 1-pathToOptimized Native application for your os
    QString path="";
    QString icon=""; //icon path to png logo
    //  void enterEvent(QEnterEvent * event);
     static int ResID;
    int getID();
    QString getPath();
    QString getIcon();
    int getType();
    qreal scale;
    QString pathicon;
    qreal getScaleFactor();
   // QMovie *movie = new QMovie(":/res/progress.gif");
   // QLabel *processLabel;
   // QWidget *black; // = new QWidget();

    void loadingSlate(bool slate);
    void setLoadingSlate(bool slate);
void focusOutEvent(QFocusEvent *event);
void  focusInEvent(QFocusEvent *event);
QString getStatus();
QString status;
QString appTypes;

signals:
    void open();
    void editStatus();
private:
       int buttonID = 0;

};

#endif // APPITEM_H
