cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_C_COMPILER "gcc-4.9")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.9")

project(Sm)

#if(APPLE)
	set(CMAKE_MACOSX_RPATH 1)
        SET(CMAKE_INSTALL_RPATH
        "@executable_path/../../lib/Debug:@executable_path/:@loader_path/")
#endif(APPLE)

SET (EXECUTABLE_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/bin"
)
SET(LIBRARY_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/lib"
)	

SET (INCLUDES_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

SET (SRC_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

SET (REGISTRY_FILE sc_reg.xml)

SET (COMMON_LIBS
    dl
    pthread
)

add_definitions (
)

SET (TOP_LEVEL ${CMAKE_CURRENT_SOURCE_DIR})

SET (service_registry service_registry)
SET (class_factory class_factory)
SET (regtool regtool)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-vla")

set (lib_path_prefix ./../lib)
if (APPLE)
set (lib_path_prefix
	 ./../../Debug/lib)
endif(APPLE)
function (reg_lib reg_lib_name)
    add_custom_command(
    TARGET ${reg_lib_name}
    POST_BUILD
    #COMMAND ./regtool -reg ${REGISTRY_FILE} ${lib_path_prefix}/lib${reg_lib_name}.so
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Debug
    COMMENT "Registering ${reg_lib_name}"
    )
endfunction(reg_lib)

add_subdirectory(src)
