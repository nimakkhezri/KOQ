QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Category.cpp \
    PVPGame.cpp \
    Player.cpp \
    Question.cpp \
    Record.cpp \
    SurvivalGame.cpp \
    TriviaAPI.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Category.h \
    PVPGame.h \
    Player.h \
    Question.h \
    Record.h \
    SurvivalGame.h \
    TriviaAPI.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    "C:\vcpkg\installed\x64-windows\include"

LIBS += \
    -L"C:\vcpkg\installed\x64-windows\lib" -lcurl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
