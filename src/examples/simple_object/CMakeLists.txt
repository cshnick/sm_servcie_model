cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(simple_object ${SOURCE_LIST})
target_link_libraries(simple_object ${COMMON_LIBS})