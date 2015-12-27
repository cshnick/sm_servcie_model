cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_C_COMPILER "gcc-4.9")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.9")

project(Sm)
SET(LIB_DIR lib)
SET(BIN_DIR bin)
IF (MSVC)
	SET(LIB_DIR ${BIN_DIR})
ENDIF (MSVC)

SET (EXECUTABLE_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/${BIN_DIR}"
)
SET(LIBRARY_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/${LIB_DIR}"
)	

SET (INCLUDES_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set (BUILD_TYPE_NAME Release)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set (BUILD_TYPE_NAME Debug)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

if(APPLE)
        set(CMAKE_MACOSX_RPATH 1)
        SET(CMAKE_INSTALL_RPATH
            "@executable_path/../../lib/Debug/:@executable_path/:@loader_path/")
        list(APPEND INCLUDES_DIR "./src/skype/Services/ShCore/macos/include/json-c")
        list(APPEND INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/skype/Services/ShCore/include")
elseif (MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        list(APPEND INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/skype/Services/ShCore/win/include/json-c")
        list(APPEND INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/skype/Services/ShCore/include")
        set(CMAKE_FIND_LIBRARY_PREFIXES "")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
        set(CMAKE_STATIC_LIBRARY_PREFIX "")
        set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
        set(CMAKE_SHARED_LIBRARY_PREFIX "")         # lib
        set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")         # .so
        set(CMAKE_IMPORT_LIBRARY_PREFIX "")
        set(CMAKE_IMPORT_LIBRARY_SUFFIX ".lib")
        set(CMAKE_EXECUTABLE_SUFFIX ".exe")         # .exe
        set(CMAKE_LINK_LIBRARY_SUFFIX ".lib")
        set(CMAKE_DL_LIBS "")
        set(CMAKE_DEBUG_POSTFIX "d") 
endif (APPLE)

SET (SRC_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

SET (REGISTRY_FILE sc_reg.xml)

SET (COMMON_LIBS "")
if (APPLE)
    FIND_LIBRARY(MAC_CORE_SERVICES CoreServices )
    SET(MAC_COMMON_LIBS ${MAC_CORE_SERVICES})
    list(APPEND COMMON_LIBS ${MAC_COMMON_LIBS})
elseif (MSVC)
    SET(WIN_COMMON_LIBS "")
    list(APPEND COMMON_LIBS ${WIN_COMMON_LIBS})
endif (APPLE)
if (UNIX)
    list (APPEND COMMON_LIBS
	   dl
	   pthread
	   json
    )
endif (UNIX)

SET(DB_WRAPPERS_LIB
	skype_dbs
)

SET(LITESQL_LIB
	litesql
)

add_definitions (
)

SET (TOP_LEVEL ${CMAKE_CURRENT_SOURCE_DIR})

SET (service_registry service_registry)
SET (class_factory class_factory)
SET (regtool regtool)

SET (OWN_CXX_FLAGS  "")
IF (NOT MSVC)
	LIST (APPEND OWN_CXX_FLAGS "-std=c++14 -Wno-vla -Wno-deprecated-declarations")	
ENDIF (NOT MSVC)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OWN_CXX_FLAGS}")

function (reg_lib reg_lib_name)
    set(regtool_name ./regtool)
    set (lib_path ../lib/lib${reg_lib_name}.so)
    set (working_dir_path ${EXECUTABLE_OUTPUT_PATH})
    if (MSVC)
        set (lib_path ${reg_lib_name}.dll)
        set (working_dir_path ${EXECUTABLE_OUTPUT_PATH}/${BUILD_TYPE_NAME})
    elseif (APPLE)
        set (lib_path ../lib/Debug/lib${reg_lib_name}.dylib)
        set (working_dir_path ${EXECUTABLE_OUTPUT_PATH}/${BUILD_TYPE_NAME})
    endif (MSVC)
    add_custom_command(
    TARGET ${reg_lib_name}
    POST_BUILD
    COMMAND ${regtool_name} -reg ${REGISTRY_FILE} ${lib_path}
    WORKING_DIRECTORY ${working_dir_path}
    COMMENT "Registering ${reg_lib_name}"
    )
endfunction(reg_lib)

function (cp_json targt)
    get_target_property(loc_prefix ${targt} PREFIX)
    #if (NOT EXISTS ${LIBRARY_OUTPUT_PATH}/)

    #endif()
endfunction(cp_json)

add_subdirectory(src)
