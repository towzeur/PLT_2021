#include <iostream> // readlink
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "client.h"
#include "engine.h"
#include "render.h"
#include "state.h"

// -----------------------------------------------------------------------------
//   ######   ##           ###     ##    ##
//  ##    ##  ##          ## ##     ##  ##
//  ##        ##         ##   ##     ####
//   ######   ##        ##     ##     ##
//        ##  ##        #########     ##
//  ##    ##  ##        ##     ##     ##
//   ######   ########  ##     ##     ##
// -----------------------------------------------------------------------------

const char *HELP_MESSAGE = R"V0G0N(
usage: client <command> [<args>]

    hello         Print a Hello World message to the console.

    state         Test the State module

    render        Display state render

    render2       Display state render v2

    engine        Display a succession of different states on the screen

    random_ai     Display a game played by a random AI

    heuristic_ai  Display a game played by a heuristic AI

    deep_ai       Display a game played by a deep AI

    thread        Display a game played by IAs, with the game engine running in 
                  a separate thread.

    record        Output a game log to replay.txt played by AIs

    play          plays the games through the record stored in replay.txt

    listen        Respond to the services defined by the API

    network       Allows the client to be added to the list of players.

)V0G0N";

/* -------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
  // parse arguments
  if (argc > 1) {
    std::string arg1(argv[1]);

    if (arg1 == "hello") {
      // -----------------------------------------------------------------------
      //                                HELLO
      // -----------------------------------------------------------------------
      std::cout << "Hello PLT !" << std::endl;

    } else if (arg1 == "state") {
      // -----------------------------------------------------------------------
      //                                STATE
      // -----------------------------------------------------------------------
      std::cout << "STATE" << std::endl;

      state::State state0();

    } else if (arg1 == "render") {
      // -----------------------------------------------------------------------
      //                                RENDER
      // -----------------------------------------------------------------------
      std::cout << "RENDER" << std::endl;

      state::State state;

      // add a few player
      std::string texts[] = {"Badisse", "Nico", "Hicham", "Kaan"};

      for (const std::string &text : texts) {
        std::unique_ptr<state::Player> p(new state::Player);
        p->setName(text);
        state.addPlayer(move(p));
      }

      try {
        state.getBoard().load("../res/map.txt");
      } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        state.getBoard().load("res/map.txt");
      }

      sf::RenderWindow window(sf::VideoMode(1900, 1080, 32), "SLAY - RENDER");
      render::StateLayer layer(state, window);
      layer.initSurfaces(state);

      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();
        }
        // render
        layer.draw(window, state);
      }

    } else if (arg1 == "render2") {
      // -----------------------------------------------------------------------
      //                               RENDER 2
      // -----------------------------------------------------------------------

      // generate a random state
      int n_row = 22, n_col = 30;
      state::State s = state::State();
      state::Board &b = s.getBoard();
      std::vector<std::shared_ptr<state::Cell>> &cells = b.getCells();
      b.resize(n_row, n_col);

      srand(time(NULL));

      std::shared_ptr<state::Cell> cell_ptr;
      for (int r = 0; r < n_row; ++r) {
        for (int c = 0; c < n_col; ++c) {

          // random token
          char tmp_str[4] = "000";
          tmp_str[0] = '0' + (rand() % 2);  // accessiblity
          tmp_str[1] = '1' + (rand() % 6);  // player
          tmp_str[2] = '0' + (rand() % 10); // entity

          cell_ptr = b.detokenize(std::string(tmp_str));
          cell_ptr->setCol(c);
          cell_ptr->setRow(r);
          cells[c + n_col * r] = std::move(cell_ptr);
        }
      }

      render::Render render;
      render.init("medieval");
      render.display_map(s);
      render.run();

    } else if (arg1 == "engine") {
      // -----------------------------------------------------------------------
      //                               ENGINE
      // -----------------------------------------------------------------------
      std::cout << "ENGINE" << std::endl;

      engine::Engine eng;
      state::Board &b = eng.getCurrentState().getBoard();

      eng.init("res/map_22_30_is.txt");
      b.print();

      Json::Value ser;
      ser["player_id"] = 1;
      ser["action_id"] = engine::ActionId::SOLDIER;
      ser["r0"] = 0;
      ser["c0"] = 0;
      ser["r1"] = 1;
      ser["c1"] = 1;
      eng.processAction(ser);

      Json::Value ser1;
      ser1["player_id"] = 1;
      ser1["action_id"] = engine::ActionId::SELECT_TERRITORY;
      ser1["r0"] = 0;
      ser1["c0"] = 0;
      eng.processAction(ser1);

      render::Render render;
      render.init("medieval");
      render.bind(eng);
      render.display_map(eng.getCurrentState());
      render.run();

    } else if (arg1 == "random_ai") {

    } else if (arg1 == "heuristic_ai") {

    } else if (arg1 == "deep_ai") {

    } else if (arg1 == "thread") {

    } else if (arg1 == "record") {

    } else if (arg1 == "play") {

    } else if (arg1 == "listen") { // 4.2

    } else if (arg1 == "network") {

    } else {
      std::cout << "Unknown command" << std::endl;
    }

  } else {
    std::cout << HELP_MESSAGE << std::endl;
  }

  return 0;
}
