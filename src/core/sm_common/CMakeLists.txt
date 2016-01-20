cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(SELF_NAME ${sm_common})
file (GLOB SOURCE_LIST "*.cpp")
set(SOURCE_LIST
    sm_common.cpp
)

add_library(${SELF_NAME} ${DEFAULT_LIB_TYPE} ${SOURCE_LIST})
#target_link_libraries(${SELF_NAME})

