set(SkypeDB_SOURCES skype.cpp main.cpp main.hpp)

message("Cmake current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
#add_custom_command(
#   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/main.hpp
#   COMMAND litesql-gen -v -t c++ main_skype.xml
#   MAIN_DEPENDENCY main_skype.xml
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#   DEPENDS litesql-gen main_skype.xml
#)

add_executable(skype_db ${SkypeDB_SOURCES})

target_link_libraries (skype_db litesql litesql-util ${BACKEND_LIBRARIES})


