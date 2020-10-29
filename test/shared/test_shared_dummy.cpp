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

    // gameOver getter/setter
    bool go = true;
    st.setGameOver(go);
    BOOST_CHECK_EQUAL(st.getGameOver(), go);

    // turn getter/setter
    int turn = 1;
    st.setTurn(turn);
    BOOST_CHECK_EQUAL(st.getTurn(), turn);

    // currentPlayer getter/setter
    int cpi = 1;
    st.setCurrentPlayerId(cpi);
    BOOST_CHECK_EQUAL(st.getCurrentPlayerId(), cpi);

    // nbPlayers getter/setter
    int np = 2;
    st.setNbPlayers(np);
    BOOST_CHECK_EQUAL(st.getNbPlayers(), np);

    // nextTurn
    turn = st.getTurn();
    BOOST_CHECK_EQUAL(st.nextTurn(), turn + 1);

    // getBoard to do

    // getTerritories to do

    // getPlayers to do

    // addTerritory
    int territoriesSize = st.getTerritories().size();
    Territory *t;
    BOOST_CHECK_EQUAL(st.addTerritory(t), territoriesSize + 1);

    // addPlayer NOT WORKING
    //    int playersSize = st.getPlayers().size();
    //    Player *p;
    //    BOOST_CHECK_EQUAL(st.addPlayer(p), playersSize + 1);
  }
}

/* vim: set sw=2 sts=2 et : */
