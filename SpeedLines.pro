TARGET=SpeedLines
SOURCES += $$PWD/src/*
OTHER_FILES += $$PWD/examples/Draw2D.cpp \
                $$PWD/examples/SimpleBlur.cpp \
                $$PWD/examples/AddInputs.cp \
                $$PWD/examples/Keymix.cpp
INCLUDEPATH += /home/s4920723
LIBS += -L /opt/Nuke11.1v3 -l DDImage
