#include "Client.h"

//#include <SFML/Graphics.hpp>
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <time.h>

using namespace client;

const unsigned int ROW = 22;
const unsigned int COL = 30;
const unsigned int BOX_R = 14;

// =============================================================================
// CLIENT
// =============================================================================

Client::Client() {}

void Client::run() {
  std::cout << "HELLO WORLD" << std::endl;
  std::cout << std::endl;
  srand(time(NULL));

  render::RenderConfig config = render::RenderConfig();
  config.load("medieval");

  // ---------------------------------------------------------------------------
  //                                WINDOWS
  // ---------------------------------------------------------------------------

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window({config.window_width, config.window_height},
                          "Hexagons", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  // set window's icon
  window.setIcon(config.window_icon.getSize().x, config.window_icon.getSize().y,
                 config.window_icon.getPixelsPtr());

  // ---------------------------------------------------------------------------
  //                                 VIEW
  // ---------------------------------------------------------------------------

  // view
  // sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
  // window.setView(view);
  // view.setRotation(20.f);

  // ---------------------------------------------------------------------------
  //                                BACKGROUND
  // ---------------------------------------------------------------------------

  render::Background bg = render::Background(config);

  // ---------------------------------------------------------------------------
  //                                    FPS
  // ---------------------------------------------------------------------------

  int frame = 0;
  sf::Clock clock;
  sf::Time time_curr; //, time_prev = clock.getElapsedTime();

  sf::Text text;
  text.setFont(config.fps_font);
  text.setString("60");
  // sf::FloatRect blabla = text.getLocalBounds();
  text.setPosition(config.window_width - text.getLocalBounds().width - 10, 0);
  text.setCharacterSize(30); // in pixel !
  text.setFillColor(sf::Color::Yellow);
  // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  // ---------------------------------------------------------------------------
  //                              SOUND TEST
  // ---------------------------------------------------------------------------

  // render::AudioEngine ae = render::AudioEngine();
  // ae.play("res/sound/Victory.wav");
  // sf::SoundBuffer buffer;
  // if (!buffer.loadFromFile("res/sound/Victory.wav")) {
  //  return;
  //}
  // sf::Sound sound;
  // sound.setBuffer(buffer);
  // sound.play();

  // ---------------------------------------------------------------------------
  //                               HEXA MAP
  // ---------------------------------------------------------------------------

  render::HexaMap hm = render::HexaMap(config, ROW, COL, BOX_R);
  hm.initialize();
  hm.update();

  // ---------------------------------------------------------------------------
  //                              ENTITTY
  // ---------------------------------------------------------------------------

  render::HexaEntity he = render::HexaEntity(config, hm);
  he.initialize();
  he.update();

  // ---------------------------------------------------------------------------
  //                              GAME LOOP
  // ---------------------------------------------------------------------------
  sf::Event event;
  int r = ROW, c = COL, hexa_r = BOX_R;
  while (window.isOpen()) {

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }

      if (event.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
          std::cout << "Right" << std::endl;
          hm.initialize(r, ++c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Left) {
          std::cout << "Left" << std::endl;
          hm.initialize(r, --c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Up) {
          std::cout << "Up" << std::endl;
          hm.initialize(--r, c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Down) {
          std::cout << "Down" << std::endl;
          hm.initialize(++r, c, hexa_r);
          //} else if (event.key.code == sf::Keyboard::Enter) {
          //  std::cout << "OK" << std::endl;
        } else if (event.key.code == sf::Keyboard::Add) {
          std::cout << "+" << std::endl;
          hm.initialize(r, c, ++hexa_r);
        } else if (event.key.code == sf::Keyboard::Subtract) {
          std::cout << "-" << std::endl;
          hm.initialize(r, c, --hexa_r);
        }
        hm.update();
      }

      if (event.type == sf::Event::MouseButtonPressed) {

        // sf::Event::MouseButtonPressed and sf::Event::MouseButtonReleased
        //  left, right, middle (wheel), extra #1 and extra #2 (side buttons)
        // std::cout << "[MOUSE] ";

        if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "RIGHT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
        }

        if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "LEFT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
          sf::Vector2u coords =
              hm.PointToCoord(event.mouseButton.x, event.mouseButton.y);
          std::cout << "=>" << coords.x << "," << coords.y << std::endl;
          int r_click = coords.x, c_click = coords.y;
          if ((r_click >= 0 && r_click < hm.get_n_row()) &&
              (c_click >= 0 && c_click < hm.get_n_col())) {
            std::cout << "!" << std::endl;
            // hm.change_color(r_click, c_click, sf::Color(0, 0, 0));
            hm.hex_toggle_transparency(r_click, c_click);
            he.entity_toggle_transparency(r_click, c_click);
          }
        }
      }

      // if (event.type == sf::Event::MouseWheelEvent) {
      //}
    }

    // DRAW : start -------------------------------------------------------

    window.clear();    // clear the screen (not necessary)
    window.draw(bg);   // background
    window.draw(hm);   // hexa map
    window.draw(he);   // entities
    window.draw(text); // fps counter

    // DRAW : end   -------------------------------------------------------
    window.display();

    // performance measurement
    // time_curr = clock.getElapsedTime();
    // fps = 1.0f / (time_curr.asSeconds() - time_prev.asSeconds()); // the
    // asSeconds returns a float time_prev = time_curr;

    frame++;
    if (clock.getElapsedTime().asSeconds() > 1.f) {
      clock.restart();
      text.setString(std::to_string(frame));
      text.setPosition(config.window_width - text.getLocalBounds().width - 10,
                       0);
      frame = 0;
    }
  }
}
