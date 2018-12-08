TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wolframlink.cpp

HEADERS += \
    wstp.h \
    wolframlink.h

# Note: for absolute path, replace $$PWD/ with
# $$PWD/../../../Applications/Mathematica.app/Contents/SystemFiles/Links/WSTP/DeveloperKit/MacOSX-x86-64/CompilerAdditions/

INCLUDEPATH += $$PWD/ # find the .h in this directory
DEPENDPATH += $$PWD/

# Linkers for Mac
# Find the lib file (.a) in this directory
macx: LIBS += -L$$PWD/  \
    -lWSTPi4 -lc++ -"framework Foundation"

macx: PRE_TARGETDEPS += $$PWD/libWSTPi4.a

