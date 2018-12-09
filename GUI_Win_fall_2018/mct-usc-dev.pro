QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    sliders.cpp \
    bodeplotwindow.cpp \
    mathengine.cpp \
    startwindow.cpp \
    controlwindow.cpp \
    mousedrag.cpp \
    wolframlink.cpp \
    controlsystemwindow.cpp \
    controlsystemwindow.cpp

FORMS += \
    bodeplotwindow.ui \
    startwindow.ui \
    controlwindow.ui \
    controlsystemwindow.ui \
    controlsystemwindow.ui

HEADERS += \
    qcustomplot.h \
    sliders.h \
    bodeplotwindow.h \
    mathengine.h \
    startwindow.h \
    controlwindow.h \
    wstp.h \
    mousedrag.h \
    wolframlink.h \
    controlsystemwindow.h \
    controlsystemwindow.h

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32: LIBS += -L$$PWD/./ -lwstp64i4

win32: LIBS += -L$$PWD/./ -lwstp64i4m



