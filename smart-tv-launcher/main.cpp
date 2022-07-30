#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
        QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
   // a.setOrganizationDomain("AlexeyT");
    // a.setApplicationName("stvl");
     qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");
    w.show();
    return a.exec();
}
