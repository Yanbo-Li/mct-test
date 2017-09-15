QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    dialog.cpp \
    qcustomplot.cpp \
    bodewindow.cpp

FORMS += \
    dialog.ui \
    bodewindow.ui

HEADERS += \
    dialog.h \
    qcustomplot.h \
    bodewindow.h

