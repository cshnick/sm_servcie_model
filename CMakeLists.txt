cmake_minimum_required(VERSION 2.8.11)

project(Sm)

SET (EXECUTABLE_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/bin"
)
SET(LIBRARY_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/bin"
)	

SET (INCLUDES_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

SET (SRC_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

SET (COMMON_LIBS
    dl
)

SET (TOP_LEVEL ${CMAKE_CURRENT_SOURCE_DIR})

SET (service_registry service_registry)
SET (class_factory class_factory)
SET (regtool regtool)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)
