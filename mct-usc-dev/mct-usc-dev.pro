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
    startwindow.h \
    controlwindow.h \
    wstp.h \

# Note: for absolute path, replace $$PWD/ with
# $$PWD/../../../Applications/Mathematica.app/Contents/SystemFiles/Links/WSTP/DeveloperKit/MacOSX-x86-64/CompilerAdditions/

INCLUDEPATH += $$PWD/ # find the .h in this directory
DEPENDPATH += $$PWD/

# Linkers for Mac
# Find the lib file (.a) in this directory
macx: LIBS += -L$$PWD/  \
    -lWSTPi4 -lc++ -"framework Foundation"

macx: PRE_TARGETDEPS += $$PWD/libWSTPi4.a

