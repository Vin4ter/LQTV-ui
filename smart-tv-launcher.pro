QT       += core gui
QT += webenginewidgets
QT += multimedia
QT += multimediawidgets
INCLUDEPATH += . vlc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appitem.cpp \
    archiveextractor.cpp \
    displayset.cpp \
    epgthread.cpp \
    main.cpp \
    setting.cpp \
    setupdesktop.cpp \
    simpleplayer.cpp \
    test.cpp \
    tvoverlay.cpp \
    widget.cpp

HEADERS += \
    appitem.h \
    archiveextractor.h \
    displayset.h \
    epgthread.h \
    setting.h \
    setupdesktop.h \
    simpleplayer.h \
    test.h \
    tvoverlay.h \
    widget.h

FORMS += \
    VolumeOverlay.ui \
    displayset.ui \
    setting.ui \
    setupdesktop.ui \
    tvoverlay.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -lz
LIBS +=-lvlc
LIBS       += -lVLCQtCore -lVLCQtWidgets

DISTFILES += \
    res/setting.png

