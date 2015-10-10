cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
)

set (OWN_LIBS
    skype_dbs
    #litesql
)
message("own libs: ${OWN_LIBS}")

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
file (GLOB SOURCE_LIST "*.cpp")

add_library(${SELF_NAME} SHARED ${SOURCE_LIST})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS} ${OWN_LIBS})

reg_lib(${SELF_NAME})