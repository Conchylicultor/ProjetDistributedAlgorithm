TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    nodeinfo.cpp \
    udpwrapper.cpp \
    storemap.cpp \
    messagemanager.cpp

HEADERS += \
    nodeinfo.h \
    udpwrapper.h \
    storemap.h \
    messagemanager.h

