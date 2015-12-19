######################################################################
# Automatically generated by qmake (3.0) Mon Dec 8 00:21:03 2014
######################################################################

QT += widgets serialport multimedia multimediawidgets
TEMPLATE = app
TARGET = peanuts
INCLUDEPATH += .

# Input
HEADERS += livescreen.h \
           MainWindow.h \
           modules/BalloonsModule.h \
           modules/BaseModule.h \
           modules/BuzzerModule.h \
           modules/NumberChoiceModule.h \
           modules/PrizeBoardModule.h \
           modules/QuestionsModule.h \
           modules/ScoresModule.h \
           modules/SongsModule.h \
           modules/ThemeCutModule.h
SOURCES += livescreen.cpp \
           main.cpp \
           MainWindow.cpp \
           modules/BalloonsModule.cpp \
           modules/BaseModule.cpp \
           modules/BuzzerModule.cpp \
           modules/NumberChoiceModule.cpp \
           modules/PrizeBoardModule.cpp \
           modules/QuestionsModule.cpp \
           modules/ScoresModule.cpp \
           modules/SongsModule.cpp \
           modules/ThemeCutModule.cpp

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
