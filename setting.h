#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QKeyEvent>
#include <QEvent>
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(int height, QWidget *parent = nullptr);
    ~Setting();
void showPage();
private:
    Ui::Setting *ui;
signals:
 void onopenDisplay();
private slots:
 void on_DISPLAYclick_clicked();
protected:
       virtual void keyPressEvent(QKeyEvent *event);
};

#endif // SETTING_H
