#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T17:18:02
#
#-------------------------------------------------

QT       += core \
              xml \
              widgets

QT       -= gui

TARGET = ProjectCalendar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tacheunitaire.cpp \
    tachemanager.cpp \
    tacheEditeur.cpp \
    tachecomposite.cpp \
    tache.cpp \
    projetmanager.cpp \
    projet.cpp \
    programmation.cpp \
    precedencemanager.cpp \
    precedence.cpp \
    calendar.cpp \
    agenda.cpp \
    programmationrdv.cpp \
    programmationevenement.cpp \
    programmationtacheunitaire.cpp \
    programmationpartietache.cpp

HEADERS += \
    tache.h \
    tachecomposite.h \
    tacheunitaire.h \
    tachemanager.h \
    tacheEditeur.h \
    projetmanager.h \
    projet.h \
    programmation.h \
    precedencemanager.h \
    precedence.h \
    calendar.h \
    agenda.h \
    programmationrdv.h \
    programmationevenement.h \
    programmationtacheunitaire.h \
    programmationpartietache.h
