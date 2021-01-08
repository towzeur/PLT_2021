#include <iostream> // readlink
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "engine.h"
#include "render.h"
#include "state.h"

/* -------------------------------------------------------------------------- */

const char *HELP_MESSAGE = R"V0G0N(
usage: client <command> [<args>]

    hello       Print a Hello World message to the console.

    state       Test the State module

    render      Display state render

    render2     Display state render v2

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

      char pBuf[256];
      size_t len = sizeof(pBuf);
      size_t bytes = readlink("/proc/self/exe", pBuf, len);
      if (bytes >= 0 && bytes < len)
        pBuf[bytes] = '\0';
      std::cout << pBuf << std::endl;

      client::Client clt = client::Client(); // = client::Client();
      clt.run();

    } else if (arg1 == "engine") {
      // -----------------------------------------------------------------------
      //                               ENGINE
      // -----------------------------------------------------------------------
      std::cout << "ENGINE" << std::endl;

      engine::Engine ngine;
      ngine.init();

      sf::RenderWindow window(sf::VideoMode(1900, 1080, 32), "SLAY - RENDER");
      render::StateLayer layer(ngine.getCurrentState(), window);
      layer.initSurfaces(ngine.getCurrentState());

      render::StateLayer *ptr_layer = &layer;
      ngine.getCurrentState().registerObserver(ptr_layer);

      bool once = true;
      while (window.isOpen()) {
        sf::Event event;
        if (once) {
          layer.draw(window, ngine.getCurrentState());
          once = false;
          std::cout << "ATENTION!! push some key to trigger a turn..."
                    << std::endl;
        }
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();
          else if (event.type == sf::Event::KeyPressed) {
            std::cout << "key pressed !" << std::endl;
            std::cout << std::endl
                      << "#########################################"
                      << std::endl;

            for (int turn = 1; turn < 9; turn++) {
              if (turn == 1) {
                // select territory
                auto player = ngine.getCurrentState()
                                  .getPlayers()[ngine.getCurrentState()
                                                    .getCurrentPlayerId()];

                auto territory = player->getTerritories()[0];
                std::unique_ptr<engine::Command> ptr_st(
                    new engine::SelectTerritoryCommand(*territory));
                ptr_st->execute(ngine.getCurrentState());

                state::Soldier sldr(state::SOLDIER, state::PEASANT, 1, 1);
                std::unique_ptr<engine::Command> ptr_be(
                    new engine::BuyEntityCommand(sldr));
                ptr_be->execute(ngine.getCurrentState());

                // sleep(10);
              }
            }
            /*
                        sleep(2);
                        std::cout << "No more turns left" << std::endl;
                        std::cout << "ENGINE SHOW finished, closing window" <<
               std::endl; window.close();
                        */
          }
        }
        // render
        layer.draw(window, ngine.getCurrentState());
      }

    } else {
      // std::cout << "Unknown command" << std::endl;
    }

  } else {
    // -------------------------------------------------------------------------
    //                                  HELP
    // -------------------------------------------------------------------------
    std::cout << HELP_MESSAGE << std::endl;
  }

  return 0;
}
