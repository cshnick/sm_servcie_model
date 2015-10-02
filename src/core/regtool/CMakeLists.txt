cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ${SRC_DIR}/core/${service_registry}
)

SET (SOURCE_LIST
    main.cpp
    ${SRC_DIR}/core/${service_registry}/${service_registry}.cpp
)

add_executable(${regtool} ${SOURCE_LIST})
target_link_libraries(${regtool} ${COMMON_LIBS})
