#include "../../src/shared/state.h"
#include <boost/test/unit_test.hpp>


using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestExemple) {

  {
    State st();
    BOOST_CHECK_EQUAL(0, 0);

    Player p();
    BOOST_CHECK_EQUAL(-1, 0);
  }

  {
    BOOST_CHECK_EQUAL(21, 21);

    // BOOST_CHECK_LE(ex.x, 32); // Less than equal
    // BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}

/* vim: set sw=2 sts=2 et : */
