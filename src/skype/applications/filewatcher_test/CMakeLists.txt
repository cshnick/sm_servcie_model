cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    include
    ../../include
)

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(${SELF_NAME} ${SOURCE_LIST})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS})