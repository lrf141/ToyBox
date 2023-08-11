#ifndef AVID_SAMPLE_TEST
#define AVID_SAMPLE_TEST
#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_STATIC_LINK
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "file_util.h"

BOOST_AUTO_TEST_SUITE(SampleTest)

BOOST_AUTO_TEST_CASE(sample_test) {
  bool result = true;
  BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_SUITE_END()
#endif
