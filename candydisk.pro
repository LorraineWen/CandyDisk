QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LoginUi.cpp \
    TitleUi.cpp \
    file.cpp \
    logintoken.cpp \
    main.cpp \
    mainmenuui.cpp \
    mainui.cpp \
    myfilepage.cpp \
    rightmenu.cpp \
    serverdatautil.cpp \
    util.cpp \
    des.c

HEADERS += \
    LoginUi.h \
    TitleUi.h \
    file.h \
    logintoken.h \
    mainmenuui.h \
    mainui.h \
    myfilepage.h \
    rightmenu.h \
    serverdatautil.h \
    util.h \
    des.h

FORMS += \
    LoginUi.ui \
    TitleUi.ui \
    mainmenuui.ui \
    mainui.ui \
   myfilepage.ui \
    rightmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    conf/cfg.json
