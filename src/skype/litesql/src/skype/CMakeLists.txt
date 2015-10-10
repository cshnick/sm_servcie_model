set(SkypeDB_SOURCES skype.cpp skype_main_db.cpp skype_main_db.hpp)

set (output_files
    ${CMAKE_CURRENT_SOURCE_DIR}/skype_main_db.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/skype_main_db.hpp
)
gen_file_depend(
    main_skype.xml
    "${output_files}"
)

add_executable(skype_db ${SkypeDB_SOURCES})
target_link_libraries (skype_db litesql litesql-util ${BACKEND_LIBRARIES})

set (skype_dbs skype_dbs PARENT_SCOPE)

add_library(skype_dbs SHARED ${SkypeDB_SOURCES})
target_link_libraries (skype_dbs litesql litesql-util ${BACKEND_LIBRARIES})


