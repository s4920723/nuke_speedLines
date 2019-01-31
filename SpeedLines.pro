TARGET=SpeedLines
SOURCES += $$PWD/src/*.cpp \
        $PWD/src/SpeedLine.cpp \
        $PWD/src/ControlPoint.cpp

HEADERS += $$PWD/include/*.h \
        $$PWD/include/SpeedLine.h \
        $$PWD/include/ControlPoint.h

OTHER_FILES += $$PWD/examples/Draw2D.cpp \
        $$PWD/examples/SimpleBlur.cpp \
        $$PWD/examples/AddInputs.cp \
        $PWD/examples/Keymix.cpp \
        $$PWD/examples/Mult.cpp \
        $$PWD/examples/Rectangle.cpp


INCLUDEPATH += /home/s4920723
LIBS += -L /opt/Nuke11.1v3 -l DDImage

HEADERS += \
    src/SpeedLine.h
