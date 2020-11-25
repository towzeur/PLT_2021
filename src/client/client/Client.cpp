#include "Client.h"

//#include <SFML/Graphics.hpp>
#include <iostream>
//#include <math.h> // sin and cos
//#include <stdlib.h> // srand, rand
//#include <time.h>   // time
//#include <vector>

using namespace client;

const unsigned int ROW = 22;
const unsigned int COL = 30;
const unsigned int BOX_R = 14;
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 580;

Client::Client() {}

void Client::run() {

  std::cout << "HELLO WORLD" << std::endl;
  std::cout << std::endl;

  sf::ContextSettings settings;
  // settings.antialiasingLevel = 8;

  sf::RenderWindow window({WIDTH, HEIGHT}, "Hexagons", sf::Style::Default,
                          settings);
  // window.setVerticalSyncEnabled(true);

  // view
  // sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
  // window.setView(view);
  // view.setRotation(20.f);

  // ---------------------------------------------------------------------------
  //                                BACKGROUND
  // ---------------------------------------------------------------------------
  sf::Texture texture;
  if (!texture.loadFromFile("res/texture/skins/background.bmp")) {
    // error...
    exit(1);
  }
  texture.setRepeated(true);

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));

  // ---------------------------------------------------------------------------
  //                                    FPS
  // ---------------------------------------------------------------------------
  int frame = 0;
  sf::Clock clock;
  sf::Time time_curr; //, time_prev = clock.getElapsedTime();

  sf::Font font;
  if (!font.loadFromFile("res/fonts/Square.ttf"))
    return;

  sf::Text text;
  text.setFont(font);
  text.setString("60");
  // sf::FloatRect blabla = text.getLocalBounds();
  text.setPosition(WIDTH - text.getLocalBounds().width - 10, 0);
  text.setCharacterSize(30); // in pixel !
  text.setFillColor(sf::Color::Yellow);
  // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  // ---------------------------------------------------------------------------

  render::HexaMap hm = render::HexaMap(ROW, COL, BOX_R);
  hm.initialize();
  hm.update();
  // window.setSize(sf::Vector2u(hm.width, hm.height));

  int r = ROW, c = COL, hexa_r = BOX_R;

  /* -------------------------------------------------- */

  while (window.isOpen()) {
    // event loop
    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {

      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        // std::cout << "[KEY] ";

        if (event.key.code == sf::Keyboard::Right) {
          std::cout << "Right" << std::endl;
          hm.initialize(r, ++c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Left) {
          std::cout << "Left" << std::endl;
          hm.initialize(r, --c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Up) {
          std::cout << "Up" << std::endl;
          hm.initialize(--r, c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Down) {
          std::cout << "Down" << std::endl;
          hm.initialize(++r, c, hexa_r);
          hm.update();
          //} else if (event.key.code == sf::Keyboard::Enter) {
          //  std::cout << "OK" << std::endl;
        } else if (event.key.code == sf::Keyboard::Add) {
          std::cout << "+" << std::endl;
          hm.initialize(r, c, ++hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Subtract) {
          std::cout << "-" << std::endl;
          hm.initialize(r, c, --hexa_r);
          hm.update();
        }

        else
          // std::cout << std::endl;
          break;

      case sf::Event::MouseButtonPressed:
        // sf::Event::MouseButtonPressed and sf::Event::MouseButtonReleased
        //  left, right, middle (wheel), extra #1 and extra #2 (side buttons)
        // std::cout << "[MOUSE] ";
        if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "RIGHT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
        } else if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "LEFT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
          sf::Vector2u coords =
              hm.PointToCoord(event.mouseButton.x, event.mouseButton.y);
          std::cout << "=>" << coords.x << "," << coords.y << std::endl;
          unsigned int r_click = coords.x, c_click = coords.y;
          if ((r_click >= 0 && r_click < hm.getN_row()) &&
              (c_click >= 0 && c_click < hm.getN_col())) {
            std::cout << "!" << std::endl;
            hm.change_color(r_click, c_click, sf::Color(0, 0, 0));
          }
        } else
          // std::cout << std::endl;
          break;

        /*
        case sf::Event::MouseWheelEvent:
            break;
        */

      default:
        break;
      }
    }

    // hm.update();
    /*
    hm.change_color(
        rand() % r,
        rand() % c,

        sf::Color(
            rand() % 255,
            rand() % 255,
            rand() % 255
        )

       (rand() % 2) ? sf::Color::Black : sf::Color::White
    );
    */

    window.clear(sf::Color::Red);
    // DRAW : start -------------------------------------------------------

    window.draw(sprite); // background
    window.draw(hm);
    window.draw(text);
    // hm.draw_grid(window);

    // DRAW : end   -------------------------------------------------------
    window.display();

    // performance measurement
    // time_curr = clock.getElapsedTime();
    // fps = 1.0f / (time_curr.asSeconds() - time_prev.asSeconds()); // the
    // asSeconds returns a float time_prev = time_curr;

    frame++;
    if (clock.getElapsedTime().asSeconds() > 1.f) {
      clock.restart();

      // std::cout << "[FPS] " << floor(frame) << std::endl; // flooring it will
      // make the frame rate a rounded number

      text.setString(std::to_string(frame));
      text.setPosition(WIDTH - text.getLocalBounds().width - 10, 0);
      frame = 0;
    }
  }

  std::cout << std::endl;
}
