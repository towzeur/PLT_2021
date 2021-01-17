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

      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();
        }
        // render
        layer.draw(window, ngine.getCurrentState());
      }

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
