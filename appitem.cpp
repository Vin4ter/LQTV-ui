#include "appitem.h"
#include "QDir"
#include "QStandardPaths"
#include "QDebug"
appItem::appItem(QString icons, QString paths, int types, qreal scales,QString appType, QPushButton *parent) : QPushButton(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                         * дальнейшая работа с кнопок
                         * */


    appTypes = appType;
    type = types;
    icon = icons;
    path = paths;
   // processLabel
    scale = scales;
    this->setMinimumHeight(130);
    this->setMinimumWidth(215);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setText("");
 //   this->set
 //   pathicon = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
 //   qDebug()<< iconpath;

    QString style="QPushButton{"
"border-style: solid;"
"border-image: url("+icon+");"

"border-width: 8px;"
"border-color: red;"
"border-radius: 9px;"

"}"
"QPushButton:focus{"
"border-width:0px;"
"border-radius: 5px;"
"}";
    this->setStyleSheet(style);
this->setDefault(true);

}

int appItem::getID()
{
    return buttonID;
}

QString appItem::getPath()
{
    return path;
}

QString appItem::getIcon()
{
    return icon;
}

int appItem::getType()
{
    return type;
}

qreal appItem::getScaleFactor()
{
    return scale;
}

void appItem::loadingSlate(bool slate)
{
    if(slate==true){
   // black = new QWidget(this);
      //  QMovie *movie = new QMovie(":/res/progress.gif");
      //  QLabel *processLabel = new QLabel(this);
      //  processLabel->setMovie(movie);
      //    processLabel->setGeometry(0,0,100,100);
      //  movie->start();
        //processLabel->setFocusPolicy()

    qDebug()<<"movie start";


    }else{
       // black->hide();
     //   processLabel->hide();

    }
}

void appItem::setLoadingSlate(bool slate)
{
 if(slate==true){
     loadingSlate(true);
 }else{
     loadingSlate(false);
 }
}


void appItem::focusOutEvent(QFocusEvent *event)
 {
   if (event->type() == QEvent::FocusOut){
      qDebug()<<"UNFOCUESED! "<<getID();

      this->setStyleSheet("QPushButton{"
"border-style: solid;"
"border-image: url("+icon+");"

"border-width: 8px;"
"border-color: red;"
"border-radius: 9px;"

"}");
   }
         // здесь обрабатываем левую кнопку мыши

    // } else {
       //     qDebug()<<"UNFOCUESED!";
         // передаём остальные кнопки в базовый класс
         //QCheckBox::mousePressEvent(event);
     //}
 }

void appItem::focusInEvent(QFocusEvent *event)
 {


    if(event->type() == QEvent::FocusIn){





        if(appTypes=="app"){
                status="home_app";
        }else if(appTypes=="game"){
         status="game_app";
        }
    emit editStatus();


                qDebug()<<"FOCUSED ! "<<getID();
 this->setStyleSheet(
"border-style: solid;"
"border-image: url("+icon+");"
"border-color: red;"
"border-width:0px;"
"border-radius: 5px;"
);

       }

}

QString appItem::getStatus()
{
    return status;

}





/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int appItem::ResID = 0;
