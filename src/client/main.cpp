//#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

#include "client.h"
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
      state::Player p;
      for (const std::string &text : texts) {
        p = state::Player();
        p.setName(text);
        state.addPlayer(&p);
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

      client::Client clt = client::Client(); // = client::Client();
      clt.run();

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
