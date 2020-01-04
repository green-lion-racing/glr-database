QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfile.cpp \
    createactivity.cpp \
    createcommunication.cpp \
    createcompany.cpp \
    createperson.cpp \
    error.cpp \
    main.cpp \
    mainwindow.cpp \
    modifycompany.cpp \
    modifytables.cpp \
    savefile.cpp \
    seetables.cpp

HEADERS += \
    addfile.h \
    createactivity.h \
    createcommunication.h \
    createcompany.h \
    createperson.h \
    error.h \
    mainwindow.h \
    modifycompany.h \
    modifytables.h \
    savefile.h \
    seetables.h

FORMS += \
    addfile.ui \
    createactivity.ui \
    createcommunication.ui \
    createcompany.ui \
    createperson.ui \
    error.ui \
    mainwindow.ui \
    modifycompany.ui \
    modifytables.ui \
    savefile.ui \
    seetables.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
