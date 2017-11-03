QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    sliders.cpp \
    bodeplotwindow.cpp \
    mathengine.cpp \
    startwindow.cpp \
    controlwindow.cpp

FORMS += \
    bodeplotwindow.ui \
    startwindow.ui \
    controlwindow.ui

HEADERS += \
    qcustomplot.h \
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

# Linkers for Windows EXAMPLE
# wstp*i*.lib --> wstp32i3.lib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../wstp-example/release/ -lWSTPi4.36
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../wstp-example/debug/ -lWSTPi4.36

INCLUDEPATH += $$PWD/../../../wstp-example
DEPENDPATH += $$PWD/../../../wstp-example

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../wstp-example/release/libWSTPi4.36.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../wstp-example/debug/libWSTPi4.36.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../wstp-example/release/WSTPi4.36.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../wstp-example/debug/WSTPi4.36.lib
