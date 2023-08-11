DISABLE_MISSING_PROFILE_WARNING()
ADD_DEFINITIONS(-DMYSQL_SERVER)

option(HAVE_PSI_FILE_INTERFACE "enable psi interface options" ON)

FILE(GLOB avid_handler_src "*.cc" "*.h")

SET(AVID_SRC
        ha_avid.cc ha_avid.h
        table_file.cc table_file.h
        file_util.cc file_util.h
        bufpool.cc bufpool.h
        page.cc page.h
        file.cc file.h
        system_table.cc system_table.h
        )

MYSQL_ADD_PLUGIN(avid ${AVID_SRC}
  STORAGE_ENGINE MANDATORY STATIC_ONLY
  LINK_LIBRARIES ext::zlib
  )

ADD_SUBDIRECTORY(tests/)
