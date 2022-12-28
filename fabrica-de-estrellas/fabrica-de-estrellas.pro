TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
#CONFIG += c++11

#QMAKE_CXXFLAGS += c++11
#QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

LIBS += -L"C:\IT\sfml\SFML-2.3.2\lib"

CONFIG(release, debug|release):
LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

CONFIG(debug, debug|release):
LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "C:\IT\sfml\SFML-2.3.2\include"


SOURCES += main.cpp \
    entity.cpp \
    enemy.cpp \
    enemy.cpp \
    player.cpp \
    bullet.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    entity.h \
    enemy.h \
    player.h \
    map.h \
    bullet.h \
#    map.h
    player.h \
    map.h \
    bullet.h

