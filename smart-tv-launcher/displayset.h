#ifndef DISPLAYSET_H
#define DISPLAYSET_H

#include <QWidget>
#include <QKeyEvent>
#include <QEvent>


namespace Ui {
class DisplaySet;
}

class DisplaySet : public QWidget
{
    Q_OBJECT

public:
    explicit DisplaySet(QWidget *parent = nullptr);
    ~DisplaySet();
    int getLeft();
    int getRight();
    int getTop();
    int getBottom();
    void showPage();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::DisplaySet *ui;
    int oleft;
    int oright;
    int otop;
    int obottom;
signals:
    void onEdit();
protected:
       virtual void keyPressEvent(QKeyEvent *event);
};

#endif // DISPLAYSET_H
