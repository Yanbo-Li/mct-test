QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    bodewindow.cpp \
    sliders.cpp \
    bodeplotwindow.cpp \
    mathengine.cpp \
    startwindow.cpp \
    controlwindow.cpp

FORMS += \
    bodewindow.ui \
    bodeplotwindow.ui \
    startwindow.ui \
    controlwindow.ui

HEADERS += \
    qcustomplot.h \
    bodewindow.h \
    sliders.h \
    bodeplotwindow.h \
    mathengine.h \
    wstp.h \
    startwindow.h \
    controlwindow.h

