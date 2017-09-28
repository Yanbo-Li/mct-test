QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    dialog.cpp \
    qcustomplot.cpp \
    bodewindow.cpp \
    sliders.cpp \
    bodeplotwindow.cpp \
    mathengine.cpp

FORMS += \
    dialog.ui \
    bodewindow.ui \
    bodeplotwindow.ui

HEADERS += \
    dialog.h \
    qcustomplot.h \
    bodewindow.h \
    sliders.h \
    bodeplotwindow.h \
    mathengine.h

