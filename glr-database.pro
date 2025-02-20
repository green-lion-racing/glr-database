QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Changing the logo under windows doesn't work instantly (cache?) rename to see change
RC_ICONS = img/logo_glr_white.ico

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
    about.cpp \
    activity.cpp \
    communication.cpp \
    company.cpp \
    databaseporting.cpp \
    error.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    person.cpp \
    tables.cpp

HEADERS += \
    about.h \
    activity.h \
    communication.h \
    company.h \
    databaseporting.h \
    error.h \
    mainwindow.h \
    member.h \
    person.h \
    tables.h

FORMS += \
    about.ui \
    activity.ui \
    communication.ui \
    company.ui \
    error.ui \
    mainwindow.ui \
    member.ui \
    person.ui \
    tables.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
