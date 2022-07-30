#ifndef SETUPDESKTOP_H
#define SETUPDESKTOP_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace Ui {
class setupDesktop;
}

class setupDesktop : public QWidget
{
    Q_OBJECT

public:
    explicit setupDesktop(QWidget *parent = nullptr);
    ~setupDesktop();

private:
    Ui::setupDesktop *ui;
 private slots:
    void downloadFinished(QNetworkReply *reply);
    void unpacked();
signals:
    void onComplete();
};

#endif // SETUPDESKTOP_H
