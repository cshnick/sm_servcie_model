cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(construct_destroy ${SOURCE_LIST})
target_link_libraries(construct_destroy ${COMMON_LIBS})