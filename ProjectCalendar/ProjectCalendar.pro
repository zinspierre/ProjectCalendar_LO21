#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T17:18:02
#
#-------------------------------------------------

QT       += core \
              xml \
              widgets\


QT       -= gui

TARGET = ProjectCalendar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tacheunitaire.cpp \
    tachecomposite.cpp \
    tache.cpp \
    projetmanager.cpp \
    projet.cpp \
    programmation.cpp \
    precedencemanager.cpp \
    precedence.cpp \
    agenda.cpp \
    programmationrdv.cpp \
    programmationevenement.cpp \
    programmationtacheunitaire.cpp \
    programmationpartietache.cpp \
    programmationevenement1j.cpp \
    programmationevenementplsj.cpp \
    calendarexception.cpp \
    duree.cpp \
    mainwindow.cpp \
    observateur.cpp \
    observable.cpp \
    dialogprecedence.cpp \
    precedenceitem.cpp \
    jourscene.cpp \
    programmationitem.cpp \
    dialogprogevt.cpp \
    dialogprogtache.cpp \
    dialogprogpartie.cpp \
    xmlexporter.cpp \
    affichable.cpp

HEADERS += \
    tache.h \
    tachecomposite.h \
    tacheunitaire.h \
    projet.h \
    programmation.h \
    precedencemanager.h \
    precedence.h \
    agenda.h \
    programmationrdv.h \
    programmationevenement.h \
    programmationtacheunitaire.h \
    programmationpartietache.h \
    programmationevenement1j.h \
    programmationevenementplsj.h \
    calendarexception.h \
    duree.h \
    projetmanager.h \
    mainwindow.h \
    observateur.h \
    observable.h \
    dialogprecedence.h \
    precedenceitem.h \
    jourscene.h \
    programmationitem.h \
    dialogprogevt.h \
    dialogprogtache.h \
    dialogprogpartie.h \
    xmlexporter.h \
    affichable.h

FORMS += \
    mainwindow.ui \
    dialogprecedence.ui \
    dialogprogevt.ui \
    dialogprogtache.ui \
    dialogprogpartie.ui
