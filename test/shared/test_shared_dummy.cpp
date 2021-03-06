#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"
#include "../../src/shared/utils.h"
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>

using namespace state;
using namespace engine;

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestState) {

  // State
  {
    State st;

    // State() constructor and gameOver, turn, currentPlayerId, nbPlayer getter
    bool go = st.getGameOver();
    int turn = st.getTurn();
    int cpi = st.getCurrentPlayerId();
    BOOST_CHECK_EQUAL(go, false);
    BOOST_CHECK_EQUAL(turn, 0);
    BOOST_CHECK_EQUAL(cpi, 0);

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

    // nextTurn
    turn = st.getTurn();
    BOOST_CHECK_EQUAL(st.nextTurn(), turn + 1);

    // getBoard
    // Board brd;
    // st.setBoard(brd);
    // BOOST_CHECK_EQUAL(st.getBoard(), brd);

    // getPlayer and addPlayer
    int playersSize = st.getPlayers().size();
    std::unique_ptr<Player> p;
    st.addPlayer(move(p));
    BOOST_CHECK_EQUAL(st.getPlayers().size(), playersSize + 1);
  }

  // Territory
  {
    Territory tr;

    // getUid
    BOOST_CHECK_EQUAL(tr.getUid(), 0); // Second territory created: uid = 1

    // CapitalRow getter and setter
    // tr.setCapitalRow(5);
    // BOOST_CHECK_EQUAL(tr.getCapitalRow(), 5);

    // CapitalCol getter and setter
    // tr.setCapitalCol(3);
    // BOOST_CHECK_EQUAL(tr.getCapitalCol(), 3);

    // setCapitalCoors
    // tr.setCapitalCoords(10, 20);
    // BOOST_CHECK_EQUAL(tr.getCapitalRow(), 10);
    // BOOST_CHECK_EQUAL(tr.getCapitalCol(), 20);

    // Savings getter and setter
    // tr.setSavings(100);
    // BOOST_CHECK_EQUAL(tr.getSavings(), 100);

    // Income getter and setter
    // tr.setIncome(50);
    // BOOST_CHECK_EQUAL(tr.getIncome(), 50);

    // Wages getter and setter
    // tr.setWages(20);
    // BOOST_CHECK_EQUAL(tr.getWages(), 20);

    // Balance getter and setter
    // tr.setBalance(30);
    // BOOST_CHECK_EQUAL(tr.getBalance(), 30);

    // Size getter and setter
    // tr.setSize(10);
    // BOOST_CHECK_EQUAL(tr.getSize(), 10);
  }

  // Player
  {
    Player pl;

    // getUid
    pl.getUid();

    // Name getter and setter
    std::string name = "Luffy";
    pl.setName(name);
    BOOST_CHECK_EQUAL(pl.getName(), name);

    // Status
    PlayerStatus status = PLAYING;
    pl.setStatus(status);
    BOOST_CHECK_EQUAL(pl.getStatus(), PLAYING);
  }

  // Board
  {
    Board bd;

    // resize
    bd.resize(30, 30);
    BOOST_CHECK_EQUAL(bd.getNCol(), 30);
    BOOST_CHECK_EQUAL(bd.getNRow(), 30);

    bd.load("../../../res/map.txt");
    //    BOOST_CHECK_EQUAL(bd.getNCol(), 3);
  }

  // AccessibleCell
  {
    AccessibleCell aCell;

    aCell.setPlayerId(1);
    BOOST_CHECK_EQUAL(aCell.getPlayerId(), 1);

    aCell.setTerritoryId(2);
    BOOST_CHECK_EQUAL(aCell.getTerritoryId(), 2);
  }

  // Cell
  {
    Cell cell;
    cell.setRow(4);
    BOOST_CHECK_EQUAL(cell.getRow(), 4);

    cell.setCol(8);
    BOOST_CHECK_EQUAL(cell.getCol(), 8);
  }

  // Entity
  {
    Entity e;

    BOOST_CHECK(!e.isEmpty());
    BOOST_CHECK(!e.isFacility());
    BOOST_CHECK(!e.isSoldier());
    BOOST_CHECK(!e.isTree());

    // e.getUid();

    // e.setAttack(1);
    // BOOST_CHECK_EQUAL(e.getAttack(), 1);

    // e.setDefense(2);
    // BOOST_CHECK_EQUAL(e.getDefense(), 2);

    // e.setIncome(0);
    // BOOST_CHECK_EQUAL(e.getIncome(), 0);
  }

  // InnaccessibleCell
  {
    InaccessibleCell iCell;
    Cell c;

    BOOST_CHECK(!iCell.isAccessible());
  }

  // Soldier
  {
      // Soldier sld;

      // sld.setPA(1);
      // BOOST_CHECK_EQUAL(sld.getPA(), 1);
  }

  // Tree
  {
    // Tree tree;

    // tree.setSubTypeId(PINE);
    // BOOST_CHECK_EQUAL(tree.getSubTypeId(), PINE);
  }
}

BOOST_AUTO_TEST_CASE(TestEngine) {

  // Engine
  {
    Engine e;
    e.init("res/map.txt");

    // State st;
    // ngine.setCurrentState(st);
    // ngine.getCurrentState();
    // Json::Value record;
    // ngine.setRecord(record);
    // ngine.getRecord();
    // To do when other classes are coded
    // Command *finish = new FinishTurnCommand();
    // ngine.addCommand(std::unique_ptr<Command>(finish));
  }

  // FinishTurnCommand
  {
      // FinishTurnCommand finish;
      // finish.serialize();
      // State st;
      // int turn = st.getTurn();
      // st.getBoard().load("../../../res/map.txt");
      // Entity ent = (Entity)Soldier(SOLDIER, BARON, 4, 4);
      // std::vector<std::shared_ptr<state::Cell>> cells =
      // st.getBoard().getCells(); cells[0]->setEntity(ent); Player pl;
      // std::shared_ptr<Territory> t(new Territory);
      // t->setSelected(true);
      // pl.addTerritory(t);
      // finish.setCurrentPlayer(pl);
      // finish.execute(st);
      // BOOST_CHECK_EQUAL(st.getTurn(), turn + 1);
      // finish.setCommandTypeId(FINISH_TURN);
      // BOOST_CHECK_EQUAL(finish.getCommandTypeId(), FINISH_TURN);
      // finish.setCurrentPlayerStatus(PLAYING);
      // BOOST_CHECK_EQUAL(finish.getCurrentPlayerStatus(), PLAYING);
  }

  // MoveCommand
  {
      // State ste;
      // Board &bd = ste.getBoard();
      // utils::PathUtils path_u = utils::PathUtils();
      // bd.load(path_u.resolveRelative("res/map.txt"));    // Issue on Jenkins
      // Soldier soldier;
      // std::vector<std::unique_ptr<state::Cell>> &cells =
      // st.getBoard().getCells();
      // cells[1]->setEntity(soldier);
      // AccessibleCell destination;
      // MoveCommand move(soldier, destination);
      // move.serialize();
      // move.execute(ste);
  }

  // SelectTerritoryCommand
  {
    // State st;
    // std::shared_ptr<Territory> tr(new Territory);
    // std::shared_ptr<Territory> tr2(new Territory);
    // SelectTerritoryCommand selTerr(*tr);
    // selTerr.serialize();
    // Player pl;
    // pl.addTerritory(tr);
    // pl.addTerritory(tr2);
    // selTerr.setCurrentPlayer(pl);
    // selTerr.execute(st);
    // selTerr.execute(st);
  }
}

/* vim: set sw=2 sts=2 et : */
