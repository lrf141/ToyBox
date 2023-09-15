INCLUDE_DIRECTORIES(SYSTEM ${BOOST_PATCHES_DIR} ${BOOST_INCLUDE_DIR})

INCLUDE_DIRECTORIES(SYSTEM ${GMOCK_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/sql
        ${CMAKE_SOURCE_DIR}/storage/toybox
)

SET(TESTS
        sample_test.cc
        bufpool_test.cc
        system_tablespace_test.cc
        file_handler_test.cc
)

SET(ALL_TOYBOX_TESTS)
FOREACH (test ${TESTS})
    LIST(APPEND ALL_TOYBOX_TESTS ${test})
ENDFOREACH ()

MYSQL_ADD_EXECUTABLE(toybox_tests ${ALL_TOYBOX_TESTS}
        ENABLE_EXPORTS
        ADD_TEST toybox_tests
        LINK_LIBRARIES gunit_large server_unittest_library
)
