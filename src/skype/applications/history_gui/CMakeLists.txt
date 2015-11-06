cmake_minimum_required(VERSION 2.8.11)
project(history_gui)
set(CMAKE_PREFIX_PATH ${QT_5_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET (SRC_DIR "src")
include_directories(
    ${INCLUDES_DIR}
    include
    ../../litesql/include/
    ../../litesql/src/skype/
    .
    ${SRC_DIR}
)
SET (SRC_LIST
    ${SRC_DIR}/history_gui.cpp
    ${SRC_DIR}/skymodel.cpp
    ${SRC_DIR}/skyproxymodel.cpp
)
SET (HEADERS
    ${SRC_DIR}/skymodel.h
    ${SRC_DIR}/skyproxymodel.h
)

find_package(Qt5 COMPONENTS Quick Core Network Xml Widgets)

qt5_add_resources(RESOURCES qml.qrc)
qt5_wrap_cpp(skymodel_MOC ${SRC_DIR}/skymodel.h)
qt5_wrap_cpp(skyproxymodel_MOC ${SRC_DIR}/skyproxymodel.h)

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
    ${skymodel_MOC}
    ${skyproxymodel_MOC}
    ${RESOURCES}
    ${HEADERS}
)

qt5_use_modules(${PROJECT_NAME} Quick Core Network Xml Widgets)
target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})