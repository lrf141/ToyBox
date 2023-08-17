INCLUDE_DIRECTORIES(SYSTEM ${BOOST_PATCHES_DIR} ${BOOST_INCLUDE_DIR})

INCLUDE_DIRECTORIES(SYSTEM ${GMOCK_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/sql
        ${CMAKE_SOURCE_DIR}/storage/avid
)

SET(TESTS
        sample_test.cc
        bufpool_test.cc
)

SET(ALL_AVID_TESTS)
FOREACH (test ${TESTS})
    LIST(APPEND ALL_AVID_TESTS ${test})
ENDFOREACH ()

MYSQL_ADD_EXECUTABLE(avid_tests ${ALL_AVID_TESTS}
        ENABLE_EXPORTS
        ADD_TEST avid_tests
        LINK_LIBRARIES gunit_large server_unittest_library
)
