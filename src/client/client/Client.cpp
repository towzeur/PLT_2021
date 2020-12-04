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
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 580;

// =============================================================================
// CLIENT
// =============================================================================

Client::Client() {}

void Client::run() {

  utils::PathUtils path_u = utils::PathUtils();
  std::string rp_background =
      path_u.resolveRelative("res/texture/skins/background.bmp");
  std::string rp_font_fps = path_u.resolveRelative("res/fonts/Square.ttf");
  std::string rp_skins =
      path_u.resolveRelative("res/texture/skins/medieval.png");

  // ---------------------------------------------------------------------------
  //                                  JSON
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  //                                  JSON
  // ---------------------------------------------------------------------------

  Json::Value root;
  std::ifstream ifs;
  ifs.open(path_u.resolveRelative("res/texture/medieval.json"));

  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    return;
  }
  std::cout << root << std::endl;

  const std::string name = root["Name"].asString();
  const int age = root["Age"].asInt();

  bool bg_enable = root["background_enable"].asBool();

  sf::Color bg_color =
      utils::SfmlUtils::string_to_color(root["background_color"].asString());

  // ---------------------------------------------------------------------------
  //                                WINDOWS
  // ---------------------------------------------------------------------------

  srand(time(NULL));

  std::cout << "HELLO WORLD" << std::endl;
  std::cout << std::endl;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window({WIDTH, HEIGHT}, "Hexagons", sf::Style::Default,
                          settings);
  // window.setVerticalSyncEnabled(true);

  // view
  // sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
  // window.setView(view);
  // view.setRotation(20.f);

  // set window's icon
  auto image = sf::Image{};
  if (!image.loadFromFile(path_u.resolveRelative("res/icons/220x220w.png"))) {
    // Error handling...
  }
  window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

  // ---------------------------------------------------------------------------
  //                                BACKGROUND
  // ---------------------------------------------------------------------------

  sf::Texture texture;
  sf::Sprite bg_sprite;
  if (bg_enable) {
    if (!texture.loadFromFile(rp_background)) {
      // error...
      exit(1);
    }
    texture.setRepeated(true);
    bg_sprite = sf::Sprite(texture, sf::IntRect(0, 0, WIDTH, HEIGHT));
  }

  // ---------------------------------------------------------------------------
  //                                    FPS
  // ---------------------------------------------------------------------------

  int frame = 0;
  sf::Clock clock;
  sf::Time time_curr; //, time_prev = clock.getElapsedTime();

  sf::Font font;
  if (!font.loadFromFile(rp_font_fps))
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

  render::HexaMap hm = render::HexaMap(ROW, COL, BOX_R);
  hm.initialize();
  hm.update();
  // window.setSize(sf::Vector2u(hm.width, hm.height));

  int r = ROW, c = COL, hexa_r = BOX_R;

  // ---------------------------------------------------------------------------
  //                              ENTITTY
  // ---------------------------------------------------------------------------

  int entity_width = 20, entity_height = 30;
  render::HexaEntity he = render::HexaEntity(hm, 20, 30, rp_skins);
  he.initialize();
  he.update();

  /*
  // 10 entity : rand() % 10,
  // Declare and load a texture
  int entity_width = 20, entity_height = 30;
  sf::Texture entities_textures;
  if (!entities_textures.loadFromFile(rp_skins)) {
    exit(1);
  }

  int i_entity = rand() % 10;
  int x_e, y_e, w_e, h_e;
  x_e = 0 * (entity_width) + 1;
  y_e = (i_entity) * (entity_height - 1) + 1;
  w_e = entity_width - 2;
  h_e = entity_height - 2;
  sf::Sprite entity_sprite(entities_textures, sf::IntRect(x_e, y_e, w_e, h_e));
  int xc_e, yc_e;
  sf::Vector2i hc = hm.get_hexa_center(rand() % ROW, rand() % COL);
  xc_e = hc.x - entity_width / 2.;
  yc_e = hc.y - entity_height / 2.;
  entity_sprite.setPosition(xc_e, yc_e);
  */

  // ---------------------------------------------------------------------------
  //                              GAME LOOP
  // ---------------------------------------------------------------------------
  sf::Event event;
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
          }
        }
      }

      // if (event.type == sf::Event::MouseWheelEvent) {
      //}
    }

    // DRAW : start -------------------------------------------------------

    window.clear(bg_color); // clear the screen
    if (bg_enable)
      window.draw(bg_sprite); // background
    window.draw(hm);          // hexa map
    window.draw(he);          // entities
    window.draw(text);        // fps counter

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
      text.setPosition(WIDTH - text.getLocalBounds().width - 10, 0);
      frame = 0;
    }
  }
}
