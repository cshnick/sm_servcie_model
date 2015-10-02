cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

SET (SOURCE_LIST
    ${class_factory}.cpp
    module.cpp
)

add_library(${class_factory} SHARED ${SOURCE_LIST})
target_link_libraries(${class_factory} ${COMMON_LIBS})
