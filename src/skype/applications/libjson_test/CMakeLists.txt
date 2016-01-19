cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    include
    ../../include
)

set(OWN_LIBS "")
if (MSVC)
    list(APPEND OWN_LIBS ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}/json${CMAKE_DEBUG_POSTFIX}.lib)
endif (MSVC)

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)

file (GLOB SOURCE_LIST "*.cpp")

add_executable(${SELF_NAME} ${SOURCE_LIST})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS} ${OWN_LIBS})