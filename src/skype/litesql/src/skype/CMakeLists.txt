set(SkypeDB_SOURCES skype.cpp skype_main_db.cpp skype_main_db.hpp)

gen_from_xml(main_skype.xml fake_skype_db)

add_executable(skype_db ${SkypeDB_SOURCES})
target_link_libraries (skype_db litesql litesql-util ${BACKEND_LIBRARIES})

add_dependencies(skype_db fake_skype_db)

add_library(skype_dbs SHARED ${SkypeDB_SOURCES})
target_link_libraries (skype_dbs litesql litesql-util ${BACKEND_LIBRARIES})
