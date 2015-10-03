cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(objects_as_params ${SOURCE_LIST})
target_link_libraries(objects_as_params ${COMMON_LIBS})