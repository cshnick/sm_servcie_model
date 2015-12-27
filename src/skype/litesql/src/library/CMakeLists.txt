set(LIBNAME litesql)

##############################################################################
# litesql-util library
##############################################################################

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC") 
endif (NOT MSVC)

set(litesql_util_SOURCES split.cpp 
            string.cpp
               ../../include/litesql/split.hpp 
            ../../include/litesql/string.hpp 
            )    

add_library(litesql-util STATIC ${litesql_util_SOURCES})

##############################################################################
# litesql library
##############################################################################
set(litesql_SOURCES    database.cpp 
            expr.cpp 
            selectquery.cpp 
            persistent.cpp 
            backend.cpp 
            updatequery.cpp 
            field.cpp 
            datasource.cpp 
            compatibility.hpp 
            compatibility.cpp 
            datetime.cpp
            ../../include/litesql/commontypes.h
            ../../include/litesql/database.hpp 
            ../../include/litesql/expr.hpp 
            ../../include/litesql/selectquery.hpp 
            ../../include/litesql/persistent.hpp 
            ../../include/litesql/backend.hpp 
            ../../include/litesql/updatequery.hpp 
            ../../include/litesql/field.hpp 
            ../../include/litesql/datasource.hpp 
            ../../include/litesql/datetime.hpp
)

set (SQLITE3_LIB sqlite3)
if (LITESQL_WITH_SQLITE3)
  set(${LIBNAME}_sqlite_SRC
                sqlite3_backend.cpp 
                sqlite3.hpp )
if(NOT SQLITE3_FOUND)
	set (SQLITE3_LIB "")
    list(APPEND ${LIBNAME}_sqlite_SRC 
                sqlite3.c
                sqlite3.h
                sqlite3ext.h
                )
endif(NOT SQLITE3_FOUND)

add_library(${LIBNAME}_sqlite STATIC ${${LIBNAME}_sqlite_SRC}) 

endif (LITESQL_WITH_SQLITE3)

if (LITESQL_WITH_MYSQL)
  add_library(  ${LIBNAME}_mysql SHARED
                        mysql.cpp
   
  )
endif (LITESQL_WITH_MYSQL)

if (LITESQL_WITH_OCILIB)
  add_library(${LIBNAME}_ocilib SHARED
                        ocilib_backend.cpp
                        ocilib_backend.hpp
   
  )
endif (LITESQL_WITH_OCILIB)

if (LITESQL_WITH_POSTGRES)
  add_library(  ${LIBNAME}_postgresql SHARED
                postgresql.cpp 
  )
endif (LITESQL_WITH_POSTGRES)

if (LITESQL_WITH_ODBC)
  add_library(  ${LIBNAME}_odbc SHARED
                      odbc_backend.cpp 
                      odbc_backend.hpp 
  )
endif (LITESQL_WITH_ODBC)

set (LIB_TYPE SHARED)
if (MSVC)
  set (LIB_TYPE STATIC)
endif (MSVC)
add_library(${LIBNAME} ${LIB_TYPE} ${litesql_SOURCES})
target_link_libraries(${LIBNAME} litesql-util ${LIBNAME}_sqlite ${SQLITE3_LIB})
include_directories(../../src/library ../../include)

