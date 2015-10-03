cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(string_enum ${SOURCE_LIST})
target_link_libraries(string_enum ${COMMON_LIBS})