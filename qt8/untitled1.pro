QT       += core gui \
    quick

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_bill.cpp \
    addwindow.cpp \
    client.cpp \
    close_bill.cpp \
    codewindow.cpp \
    dwindow.cpp \
    findclient.cpp \
    givemoney.cpp \
    main.cpp \
    mainwindow.cpp \
    off_bill.cpp \
    plusemoney.cpp \
    regwindow.cpp \
    reportwindow.cpp \
    tablebills.cpp \
    tablewindow.cpp \
    valutes.cpp

HEADERS += \
    add_bill.h \
    addwindow.h \
    client.h \
    close_bill.h \
    codewindow.h \
    dwindow.h \
    findclient.h \
    givemoney.h \
    mainwindow.h \
    off_bill.h \
    plusemoney.h \
    regwindow.h \
    reportwindow.h \
    tablebills.h \
    tablewindow.h \
    valutes.h

FORMS += \
    mainwindow.ui \
    reportwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    files.qrc
