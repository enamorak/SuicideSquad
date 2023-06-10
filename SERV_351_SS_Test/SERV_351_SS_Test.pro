QT += testlib sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_un1.cpp \
    ../SERV_351_SS/function.cpp \
    ../SERV_351_SS/mytcpserver.cpp \
    ../SERV_351_SS/singletonbd.cpp

HEADERS += \
    ../SERV_351_SS/function.h \
    ../SERV_351_SS/mytcpserver.h \
    ../SERV_351_SS/singletonbd.h
