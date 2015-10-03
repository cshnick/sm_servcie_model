cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    include
)

file (GLOB SOURCE_LIST "service/*.cpp")

add_library(multy_component_service SHARED ${SOURCE_LIST})
target_link_libraries(multy_component_service ${COMMON_LIBS})

file (GLOB SOURCE_LIST_CLIENT "client/*.cpp")

add_executable(multy_component_client ${SOURCE_LIST_CLIENT})
target_link_libraries(multy_component_client ${COMMON_LIBS})

add_dependencies(multy_component_client RegExamples)