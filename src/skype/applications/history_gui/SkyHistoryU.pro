TEMPLATE = app

QT += qml quick widgets

isEmpty(LITE_SQL_SRC) : LITE_SQL_SRC=/home/ilia/Development/orm/litesql-git
isEmpty(LITE_SQL_CMAKE) : LITE_SQL_CMAKE=/home/ilia/Development/orm/cmake_liteSQL

SOURCES += \
    src/SkyHistoryMain.cpp \
    src/skymodel.cpp       \
    src/skyproxymodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


#INCLUDEPATH += $$LITE_SQL_SRC/include \
#              $$LITE_SQL_SRC/src/examples
#LIBS += \
#        -L$$LITE_SQL_CMAKE/src/library -llitesql

HEADERS += \
    src/skymodel.h \
    src/skyproxymodel.h

CONFIG += c++11

OTHER_FILES += CMakeLists.txt
