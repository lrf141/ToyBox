DISABLE_MISSING_PROFILE_WARNING()
ADD_DEFINITIONS(-DMYSQL_SERVER)

SET(TOYBOX_SRC
        ha_toybox.cc ha_toybox.h
        table_file.cc table_file.h
        file_util.cc
        bufpool.cc bufpool.h
        page.cc page.h
        file.cc file.h
        systemtable/system_table_repo.cc
        systemtable/system_table_logic.cc
        systemtable/system_table_usecase.cc
        systemtable/system_table_handler.cc
        systemtable/system_table_helper.cc
        tablespace/tablespace_helper.cc
        tablespace/tablespace_repo.cc
        tablespace/tablespace_logic.cc
        tablespace/tablespace_usecase.cc
        tablespace/tablespace_handler.cc
        tablespace/tablespace_header_repo.cc
        tablespace/tablespace_header_logic.cc
        )

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/storage/toybox/include/)

STRING_APPEND(CMAKE_CXX_FLAGS " -Wno-unused-variable")

MYSQL_ADD_PLUGIN(toybox ${TOYBOX_SRC}
  STORAGE_ENGINE MANDATORY
  LINK_LIBRARIES ext::zlib
  )

ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/storage/toybox/unittest/)
