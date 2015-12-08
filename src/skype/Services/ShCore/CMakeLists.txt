cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
)
if (APPLE)
 list(APPEND include_directories "macosx/include/json-c")
endif (APPLE)
set (OWN_LIBS
    litesql
    skype_dbs
)
message("own libs: ${OWN_LIBS}")

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
file (GLOB SOURCE_LIST "*.cpp")
set(SOURCE_LIST
    DBCtrlImpl.cpp
    DBEventImpl.cpp
    DBObserverImpl.cpp
    SettingsImpl.cpp
    module.cpp
)
if (APPLE)
    list(APPEND SOURCE_LIST macosx/PlatformUtilsImpl.cpp)
elseif (UNIX)
    list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/linux/PlatformUtilsImpl.cpp)
elseif (WIN32)
    list(APPEND SOURCE_LIST win/PlatformUtilsImpl.cpp)
else (APPLE)
    list(APPEND SOURCE_LIST PlatformUtilsImpl.cpp)
endif (APPLE)

add_library(${SELF_NAME} SHARED ${SOURCE_LIST})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS} ${OWN_LIBS})

reg_lib(${SELF_NAME})
