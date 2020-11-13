#include "render.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <state.h>
#include <string.h>

using namespace render;

/* ----------------------------------------------------------------------------
                                GLOBAL VARIABLE
-----------------------------------------------------------------------------*/
const char *HELP_MESSAGE = R"V0G0N(
usage: client <command> [<args>]

    hello       Print a Hello World message to the console.

    state       Test the State module

    render      Display state render
)V0G0N";

// const char* UNKNOWN_MESSAGE = "client: '?' is not a command. See 'command
// --help'."

/* ----------------------------------------------------------------------------
                         check if SFML is working
-----------------------------------------------------------------------------*/

void testSFML() { sf::Texture texture; }

/* --------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
  // parse arguments
  if (argc > 1) {
    std::string arg1(argv[1]);

    if (arg1 == "hello") {
      std::cout << "Hello PLT !" << std::endl;
    } else if (arg1 == "state") {
      std::cout << "STATE" << std::endl;

      state::State state0();
    } else if (arg1 == "render") {
      std::cout << "RENDER" << std::endl;

      state::State state;
      sf::RenderWindow window(
          sf::VideoMode(state.getBoard().getNCol() * 32 + 256,
                        state.getBoard().getNRow() * 32 + 32, 32),
          "map");
      StateLayer layer(state, window);
      layer.initSurfaces(state);
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();
        }
        // render
        layer.draw(window);
      }
    } else {
      // std::cout << "Unknown command" << std::endl;
    }
  } else {
    std::cout << HELP_MESSAGE << std::endl;
  }

  // begin test
  // testSFML();

  // Exemple exemple;
  // exemple.setX(53);
  return 0;
}
