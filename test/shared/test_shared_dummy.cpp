#include "../../src/shared/state.h"
#include <boost/test/unit_test.hpp>

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestExemple) {

  {
    State st();
    BOOST_CHECK_EQUAL(0, 0);

    Player p();
    BOOST_CHECK_EQUAL(0, 0);
  }

  {
    BOOST_CHECK_EQUAL(21, 21);

    // BOOST_CHECK_LE(ex.x, 32); // Less than equal
    // BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }

  // State
  {
    State st;

    bool go = true;
    st.setGameOver(go);
    BOOST_CHECK_EQUAL(st.getGameOver(), go);

    int turn = 1;
    st.setTurn(turn);
    BOOST_CHECK_EQUAL(st.getTurn(), turn);

    int cpi = 1;
    st.setCurrentPlayerId(cpi);
    BOOST_CHECK_EQUAL(st.getCurrentPlayerId(), cpi);

    int np = 2;
    st.setNbPlayers(np);
    BOOST_CHECK_EQUAL(st.getNbPlayers(), np);
  }
}

/* vim: set sw=2 sts=2 et : */
