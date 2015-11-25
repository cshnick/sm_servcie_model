cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
)

set (OWN_LIBS
    litesql
    skype_dbs
)
message("own libs: ${OWN_LIBS}")

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)

#SET(SOURCE_LIST PlatformUtilsImpl.cpp)
if (APPLE)
    SET(SOURCE_LIST macosx/PlatformUtilsImpl.cpp)
elseif (UNIX)
    SET(SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/linux/PlatformUtilsImpl.cpp)
elseif (WIN32)
    SET(SOURCE_LIST win/PlatformUtilsImpl.cpp)
endif (APPLE)
list(APPEND SOURCE_LIST module.cpp)

add_library(${SELF_NAME} SHARED ${SOURCE_LIST})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS} ${OWN_LIBS})

reg_lib(${SELF_NAME})