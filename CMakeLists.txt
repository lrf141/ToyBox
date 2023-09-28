DISABLE_MISSING_PROFILE_WARNING()
ADD_DEFINITIONS(-DMYSQL_SERVER)

SET(TOYBOX_SRC
        ha_toybox.cc ha_toybox.h
        file_util.cc file_util.h
        bufpool.cc bufpool.h
        system/system_tablespace.cc
        file_handler.cc
        tablespace/tablespace.cc
        page/page.cc
        )

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/storage/toybox/include/)

MYSQL_ADD_PLUGIN(toybox ${TOYBOX_SRC}
  STORAGE_ENGINE MANDATORY
  LINK_LIBRARIES ext::zlib
  )

ADD_SUBDIRECTORY(tests)
