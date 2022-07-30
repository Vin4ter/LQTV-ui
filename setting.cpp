#include "setting.h"
#include "ui_setting.h"

Setting::Setting(int height, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget#Setting{"
"background-color: rgb(21, 21, 21);"
"}");
   ui->bg->setMinimumHeight(height);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::showPage()
{
    this->show();
    ui->WIFIclick->setFocus();
}

void Setting::on_DISPLAYclick_clicked()
{
    emit onopenDisplay();
}
void Setting::keyPressEvent(QKeyEvent *event) { //HOME
 int key=event->key();//event->key() - целочисленный код клавиши
 if (key==Qt::Key_Menu) {
     this->hide();
 }
}
