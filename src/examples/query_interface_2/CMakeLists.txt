cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(query_interface_2 ${SOURCE_LIST})
target_link_libraries(query_interface_2 ${COMMON_LIBS})