cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    include
)

file (GLOB SOURCE_LIST "calc_service/*.cpp")

add_library(simple_component SHARED ${SOURCE_LIST})
target_link_libraries(simple_component ${COMMON_LIBS})

file (GLOB SOURCE_LIST_CLIENT "client/*.cpp")

add_executable(simple_component_client ${SOURCE_LIST_CLIENT})
target_link_libraries(simple_component_client ${COMMON_LIBS})