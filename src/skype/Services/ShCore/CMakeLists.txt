cmake_minimum_required(VERSION 2.8.11)

include_directories(
    ${INCLUDES_DIR}
    ../../include
    ../../litesql/include/
    ../../litesql/src/skype/
)
set (OWN_LIBS
    litesql
    skype_dbs
)
message("own libs: ${OWN_LIBS}")
message("CXX_FLAGS for ShCore: ${CMAKE_CXX_FLAGS}")

if (APPLE)
 list(APPEND include_directories "macosx/include/json-c")
elseif (MSVC)
    add_definitions(-DNOMINMAX)
    list(APPEND OWN_LIBS ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}/json${CMAKE_DEBUG_POSTFIX}.lib)
endif (APPLE)

get_filename_component(SELF_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
file (GLOB SOURCE_LIST "*.cpp")
set(SOURCE_LIST
    DBCtrlImpl.cpp
    DBEventImpl.cpp
    DBObserverImpl.cpp
    SettingsImpl.cpp
    module.cpp
)
if (APPLE)
    list(APPEND SOURCE_LIST macosx/PlatformUtilsImpl.cpp)
elseif (UNIX)
    list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/linux/PlatformUtilsImpl.cpp)
elseif (MSVC)
    list(APPEND SOURCE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/win/PlatformUtilsImpl.cpp)
else (APPLE)
    list(APPEND SOURCE_LIST PlatformUtilsImpl.cpp)
endif (APPLE)

add_library(${SELF_NAME} SHARED ${SOURCE_LIST})
message(COMMON LIBS: ${COMMON_LIBS})
target_link_libraries(${SELF_NAME} ${COMMON_LIBS} ${OWN_LIBS})

if (MSVC)
    set(json_path "${TOP_LEVEL}/src/skype/Services/ShCore/win/files/${BUILD_TYPE_NAME}")
    set(json_name "${CMAKE_STATIC_LIBRARY_PREFIX}json${CMAKE_DEBUG_POSTFIX}${CMAKE_LINK_LIBRARY_SUFFIX}")
endif (MSVC)
add_custom_target(
    copy_json
    #COMMENT("Copy json library...")
    COMMENT(json_path ${json_path})
    #COMMAND ${copy_command} ${json_path}/${json_name} ${LIBRARY_OUTPUT_PATH}
    COMMAND ${CMAKE_COMMAND} -E echo what ${${json_path}} #${json_path}/${json_name} ${LIBRARY_OUTPUT_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy ${json_path}/${json_name} ${LIBRARY_OUTPUT_PATH}/${BUILD_TYPE_NAME}
    )

add_dependencies(${SELF_NAME} copy_json)
reg_lib(${SELF_NAME})
