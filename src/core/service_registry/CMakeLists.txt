cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

SET (SOURCE_LIST
    ${service_registry}.cpp
    module.cpp
)

add_library(${service_registry} SHARED ${SOURCE_LIST})
target_link_libraries(${service_registry} ${COMMON_LIBS})