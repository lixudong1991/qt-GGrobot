#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T20:28:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

RC_ICONS    += robot.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = r
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp\
        dialog.cpp \
    main_widget.cpp \
    exportwidget.cpp \
    cloudwidget.cpp \
    logindialog.cpp \
    mainmenu.cpp \
    titlewidget.cpp \
    tool_button.cpp \
    push_button.cpp \
    loading_widget.cpp \
    msg_box.cpp \
    settingdialog.cpp \
    userterminal.cpp \
    substationdata.cpp \
    ftpmanager.cpp \
    thread.cpp \
    login_device_info.cpp \
    infowidget.cpp \
    loginthread.cpp \
    finddatathread.cpp \
    exportdownima.cpp \
    expordownthread.cpp \
    log4z.cpp \
    routewidget.cpp

HEADERS  += dialog.h \
    head.h \
    main_widget.h \
    titlewidget.h \
    cloudwidget.h \
    logindialog.h \
    mainmenu.h \
    push_button.h \
    tool_button.h \
    exportwidget.h \
    common.h \
    loading_widget.h \
    msg_box.h \
    settingdialog.h \
    userterminal.h \
    substationdata.h \
    ftpmanager.h \
    thread.h \
    HCNetSdk/DataType.h \
    HCNetSdk/DecodeCardSdk.h \
    HCNetSdk/HCNetSDK.h \
    HCNetSdk/plaympeg4.h \
    login_device_info.h \
    infowidget.h \
    loginthread.h \
    finddatathread.h \
    exportdownima.h \
    expordownthread.h \
    log4z.h \
    routewidget.h



LIBS += -LD:/HCNetSdk/ -lHCNetSDK \
            -LD:/HCNetSdk/ -lHCCore \
            -LD:/HCNetSdk/ -lPlayCtrl \
            -LD:/HCNetSdk/HCNetSDKCom/ -lHCPreview \
            -LD:/HCNetSdk/HCNetSDKCom/ -lHCAlarm \
            -LD:/HCNetSdk/HCNetSDKCom/ -lHCGeneralCfgMgr \

FORMS +=

RESOURCES += \
    r.qrc


