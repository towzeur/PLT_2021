#include "../../src/shared/state.h"
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestExemple) {

  // State
  {
    State st;

    // State() constructor and gameOver, turn, currentPlayerId, nbPlayer getter
    bool go = st.getGameOver();
    int turn = st.getTurn();
    int cpi = st.getCurrentPlayerId();
    int np = st.getNbPlayers();
    BOOST_CHECK_EQUAL(go, false);
    BOOST_CHECK_EQUAL(turn, 0);
    BOOST_CHECK_EQUAL(cpi, 0);
    BOOST_CHECK_EQUAL(np, 0);

    // gameOver setter
    go = true;
    st.setGameOver(go);
    BOOST_CHECK_EQUAL(st.getGameOver(), go);

    // turn setter
    turn = 1;
    st.setTurn(turn);
    BOOST_CHECK_EQUAL(st.getTurn(), turn);

    // currentPlayer setter
    cpi = 1;
    st.setCurrentPlayerId(cpi);
    BOOST_CHECK_EQUAL(st.getCurrentPlayerId(), cpi);

    // nbPlayers setter
    np = 2;
    st.setNbPlayers(np);
    BOOST_CHECK_EQUAL(st.getNbPlayers(), np);

    // nextTurn
    turn = st.getTurn();
    BOOST_CHECK_EQUAL(st.nextTurn(), turn + 1);

    // getBoard TO DO

    // getTerritoties and addTerritory
    int territoriesSize = st.getTerritories().size();
    Territory t;
    BOOST_CHECK_EQUAL(st.addTerritory(&t), territoriesSize + 1);

    // getPlayer and addPlayer
    int playersSize = st.getPlayers().size();
    Player p;
    BOOST_CHECK_EQUAL(st.addPlayer(&p), playersSize + 1);
  }

  // Territory
  {
    Territory tr;

    // getUid
    BOOST_CHECK_EQUAL(tr.getUid(), 1); // Second territory created: uid = 1

    // CapitalRow getter and setter
    tr.setCapitalRow(5);
    BOOST_CHECK_EQUAL(tr.getCapitalRow(), 5);

    // CapitalCol getter and setter
    tr.setCapitalCol(3);
    BOOST_CHECK_EQUAL(tr.getCapitalCol(), 3);

    // setCapitalCoors
    tr.setCapitalCoords(10, 20);
    BOOST_CHECK_EQUAL(tr.getCapitalRow(), 10);
    BOOST_CHECK_EQUAL(tr.getCapitalCol(), 20);

    // Savings getter and setter
    tr.setSavings(100);
    BOOST_CHECK_EQUAL(tr.getSavings(), 100);

    // Income getter and setter
    tr.setIncome(50);
    BOOST_CHECK_EQUAL(tr.getIncome(), 50);

    // Wages getter and setter
    tr.setWages(20);
    BOOST_CHECK_EQUAL(tr.getWages(), 20);

    // Balance getter and setter
    tr.setBalance(30);
    BOOST_CHECK_EQUAL(tr.getBalance(), 30);

    // Size getter and setter
    tr.setSize(10);
    BOOST_CHECK_EQUAL(tr.getSize(), 10);
  }

  // Player
  {
    Player pl;

    // getUid
    BOOST_CHECK_EQUAL(pl.getUid(), 1); // Second player created: uid = 1

    // Name getter and setter
    std::string name = "Luffy";
    pl.setName(name);
    BOOST_CHECK_EQUAL(pl.getName(), name);

    // Playing getter and setter
    pl.setPlaying(true);
    BOOST_CHECK(pl.getPlaying());

    // Status TO DO
  }

  // Board
  {
    Board bd;

    // Board() constructor and getNCol, getNRow
    int nc = bd.getNCol();
    int nr = bd.getNRow();
    BOOST_CHECK_EQUAL(nc, 50);
    BOOST_CHECK_EQUAL(nr, 50);

    // resize
    bd.resize(30, 30);
    BOOST_CHECK_EQUAL(bd.getNCol(), 30);
    BOOST_CHECK_EQUAL(bd.getNRow(), 30);
  }
}

/* vim: set sw=2 sts=2 et : */
