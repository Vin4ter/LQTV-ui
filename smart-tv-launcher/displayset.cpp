#include "displayset.h"
#include "ui_displayset.h"
#include "QSettings"
#include "QStandardPaths"
DisplaySet::DisplaySet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplaySet)
{
    ui->setupUi(this);
    QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QSettings sets(path+"/main.conf",QSettings::IniFormat);
    sets.beginGroup("display");
    oleft=sets.value("overscan_left").toInt();
  oright=sets.value("overscan_right").toInt();
  otop=sets.value("overscan_top").toInt();
  obottom=sets.value("overscan_bottom").toInt();
    sets.endGroup();
    ui->leftl->setText(QString::number(oleft));
       ui->rightl->setText(QString::number(oright));
    ui->topl->setText(QString::number(otop));
        ui->bottoml->setText(QString::number(obottom));
}

DisplaySet::~DisplaySet()
{
    delete ui;
}

int DisplaySet::getLeft()
{
return oleft;
}

int DisplaySet::getRight()
{
return oright;
}

int DisplaySet::getTop()
{
return otop;
}

int DisplaySet::getBottom()
{
    return obottom;
}

void DisplaySet::showPage()
{
    this->show();
    ui->pushButton_2->setFocus();

}

void DisplaySet::on_pushButton_clicked()//left +
{
    oleft+=1;
    ui->leftl->setText(QString::number(oleft));
    emit onEdit();
    QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QSettings sets(path+"/main.conf",QSettings::IniFormat);
    sets.beginGroup("display");
    sets.setValue("overscan_left",oleft);
    sets.endGroup();
}

void DisplaySet::on_pushButton_4_clicked()//right +
{
       oright+=1;
          ui->rightl->setText(QString::number(oright));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_right",oright);
          sets.endGroup();
}

void DisplaySet::on_pushButton_5_clicked()//top +
{
       otop+=1;
          ui->topl->setText(QString::number(otop));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_top",otop);
          sets.endGroup();
}

void DisplaySet::on_pushButton_7_clicked() //bottom +
{
       obottom+=1;
          ui->bottoml->setText(QString::number(obottom));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_bottom",obottom);
          sets.endGroup();
}

void DisplaySet::on_pushButton_2_clicked()//left -
{
       oleft-=1;
          ui->leftl->setText(QString::number(oleft));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_left",oleft);
          sets.endGroup();
}

void DisplaySet::on_pushButton_3_clicked() //right -
{
       oright-=1;
          ui->rightl->setText(QString::number(oright));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_right",oright);
          sets.endGroup();
}

void DisplaySet::on_pushButton_6_clicked()//top -
{
       otop-=1;
          ui->topl->setText(QString::number(otop));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_top",otop);
          sets.endGroup();
}

void DisplaySet::on_pushButton_8_clicked()//bottom -
{
       obottom-=1;
          ui->bottoml->setText(QString::number(obottom));
              emit onEdit();
          QString path=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
          QSettings sets(path+"/main.conf",QSettings::IniFormat);
          sets.beginGroup("display");
          sets.setValue("overscan_bottom",obottom);
          sets.endGroup();
}
void DisplaySet::keyPressEvent(QKeyEvent *event) { //HOME
 int key=event->key();//event->key() - целочисленный код клавиши
 if (key==Qt::Key_Menu) {
     this->hide();
 }
}

