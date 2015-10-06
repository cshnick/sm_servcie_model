cmake_minimum_required(VERSION 2.8.11)

set (LIB_NME
    SCCore
)
    
include_directories(
    ${INCLUDES_DIR}
    ../../include
)

file (GLOB SOURCE_LIST "*.cpp")

add_library(${LIB_NME} SHARED ${SOURCE_LIST})
target_link_libraries(${LIB_NME} ${COMMON_LIBS})