QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car.cpp \
    fscene.cpp \
    gspeedometer.cpp \
    gscene.cpp \
    main.cpp \
    mainwindow.cpp \
    mscene.cpp \
    personaje.cpp \
    pmenu.cpp \
    tscene.cpp

HEADERS += \
    car.h \
    fscene.h \
    gspeedometer.h \
    gscene.h \
    mainwindow.h \
    mscene.h \
    personaje.h \
    pmenu.h \
    tscene.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

