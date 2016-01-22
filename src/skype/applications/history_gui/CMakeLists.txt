cmake_minimum_required(VERSION 2.8.11)
project(history_gui)
set(CMAKE_PREFIX_PATH ${QT_5_DIR})
SET (SRC_DIR "src")
include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
    .
    ${SRC_DIR}
)
SET (SRC_LIST
    ${SRC_DIR}/history_gui.cpp
    ${SRC_DIR}/skymodel.cpp
    ${SRC_DIR}/skyproxymodel.cpp
    ${SRC_DIR}/skycontactstreemodel.cpp
)
SET (HEADERS
    ${SRC_DIR}/skymodel.h
    ${SRC_DIR}/skyproxymodel.h
)
message(CMAKE_CONFIGURATION_TYPES ${CMAKE_INTDIR})
message(CFG_INTDIR: ${Configuration})

find_package(Qt5 COMPONENTS Quick Core Network Xml Widgets)

qt5_add_resources(RESOURCES qml.qrc)
qt5_wrap_cpp(skymodel_MOC ${SRC_DIR}/skymodel.h)
qt5_wrap_cpp(skyproxymodel_MOC ${SRC_DIR}/skyproxymodel.h)
qt5_wrap_cpp(skycontactstreemodel_MOC ${SRC_DIR}/skycontactstreemodel.h)

#set(_PLATFORM_LINK_FLAGS "/ENTRY:WinMainCRTStartup")
if (MSVC)
list(APPEND CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif(MSVC)
add_executable(${PROJECT_NAME}
    ${SRC_LIST}
    ${skymodel_MOC}
    ${skyproxymodel_MOC}
    ${skycontactstreemodel_MOC}
    ${RESOURCES}
    ${HEADERS}
)

qt5_use_modules(${PROJECT_NAME} Quick Core Network Xml Widgets)
target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})

#if (MSVC)
#add_custom_command (
#    TARGET ${PROJECT_NAME}
#    POST_BUILD
#    COMMENT Copying Qt libraries
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${QT_5_DIR}/bin/Qt5Widgets${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
#            ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${QT_5_DIR}/bin/Qt5Gui${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
#            ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${QT_5_DIR}/bin/Qt5Core${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
#            ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${QT_5_DIR}/bin/Qt5Qml${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
#            ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${QT_5_DIR}/bin/Qt5Network${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
#            ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
#    )
#endif (MSVC)