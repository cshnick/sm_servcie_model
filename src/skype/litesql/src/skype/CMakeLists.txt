set (output_files_main_db
    ${CMAKE_CURRENT_SOURCE_DIR}/skype_main_db.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/skype_main_db.hpp
)
gen_file_depend(
    main_skype.xml
    "${output_files_main_db}"
)

set (output_files_history_db
    ${CMAKE_CURRENT_SOURCE_DIR}/history_main_db.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/history_main_db.hpp
)
gen_file_depend(
    history_skype.xml
    "${output_files_history_db}"
)

set(SkypeDB_SOURCES "${output_files_main_db}")
set(HistoryDB_SOURCES "${output_files_history_db}")

add_executable(skype_db skype.cpp ${SkypeDB_SOURCES})
target_link_libraries (skype_db litesql litesql-util ${BACKEND_LIBRARIES})

add_library(skype_dbs SHARED ${SkypeDB_SOURCES} ${HistoryDB_SOURCES})
target_link_libraries (skype_dbs litesql litesql-util ${BACKEND_LIBRARIES})
