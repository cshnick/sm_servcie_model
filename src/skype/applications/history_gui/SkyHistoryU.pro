QMAKE_CC = gcc-4.9
QMAKE_CXX = g++-4.9

TEMPLATE = app
QT += qml quick widgets qml

isEmpty(MAIN_SRC)       : MAIN_SRC=/home/ilia/Development/sm_servcie_model
isEmpty(LITE_SQL_CMAKE) : MAIN_LIB_DIR=/home/ilia/Development/cmake_sm/lib

LITE_SQL_SRC=$$MAIN_SRC/src/skype/litesql

SOURCES += \
    src/history_gui.cpp \
    src/skymodel.cpp       \
    src/skyproxymodel.cpp \
    src/skycontactstreemodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

message($$MAIN_SRC/include)

INCLUDEPATH += $$LITE_SQL_SRC/include \
               $$LITE_SQL_SRC/src/skype \
               src \
               $$MAIN_SRC/include


LIBS += \
        -lstdc++ -ldl \
        -L$$MAIN_LIB_DIR -llitesql -ljson

HEADERS += \
    src/skymodel.h \
    src/skyproxymodel.h \
    src/skycontactstreemodel.h

DEFINES += \
    __SM_QTCREATOR__

CONFIG += c++14
OTHER_FILES += CMakeLists.txt

QMAKE_CXXFLAGS += -Wno-vla -Wno-reorder -Wno-enum-compare

DISTFILES += \
    images/profile.svg
