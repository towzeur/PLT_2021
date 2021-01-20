#include "Client.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "state/Entity.h"
#include "utils/Utils.h"

using namespace client;

void handle_menu_click(sf::String menu_name) {
  std::cout << "menu clicked : " << menu_name.toAnsiString() << std::endl;
  if (menu_name == "Load") {
  } else if (menu_name == "Save") {
  } else if (menu_name == "Exit") {
  } else if (menu_name == "Copy") {
  } else if (menu_name == "Paste") {
  } else if (menu_name == "About") {
  }
}

// =============================================================================
// CLIENT
// =============================================================================

Client::Client() {}

void Client::run() {
  std::cout << "HELLO WORLD" << std::endl;
  srand(time(NULL));

  render::RenderConfig config = render::RenderConfig();
  config.load("medieval");

  // ---------------------------------------------------------------------------
  //                                WINDOWS
  // ---------------------------------------------------------------------------

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
  // Titlebar   = 1 << 0
  // Resize     = 1 << 1
  // Close      = 1 << 2
  // Fullscreen = 1 << 3
  // Default = Titlebar | Resize | Close
  sf::RenderWindow window({config.window_size.x, config.window_size.y},
                          "Hexagons", style, settings);

  window.setVerticalSyncEnabled(true);

  // center the window
  window.setPosition(sf::Vector2i(
      (sf::VideoMode::getDesktopMode().width - window.getSize().x) / 2,
      (sf::VideoMode::getDesktopMode().height - window.getSize().y) / 2));

  // set window's icon
  window.setIcon(config.window_icon.getSize().x, config.window_icon.getSize().y,
                 config.window_icon.getPixelsPtr());

  // ---------------------------------------------------------------------------
  //                                   TGUI
  // ---------------------------------------------------------------------------

  tgui::Gui gui(window);

  const sf::String &tgui_theme =
      utils::Utils::resolveRelative("res/tgui/widgets/Black.txt");
  tgui::Theme::Ptr theme = tgui::Theme::create(tgui_theme);

  tgui::MenuBar::Ptr menu = theme->load("MenuBar");
  menu->setSize(config.window_size.x, config.window_menu_height);

  // canvas_w = config.window_size.x - config.window_right_panel_width;
  // canvas_h = config.window_size.y - config.window_menu_height;

  const std::string &tgui_font =
      // const sf::String &tgui_font =
      utils::Utils::resolveRelative("res/fonts/Segoe_UI.ttf");
  menu->setFont(tgui_font);
  menu->addMenu("File");
  menu->addMenuItem("File", "Load");
  menu->addMenuItem("File", "Save");
  menu->addMenuItem("File", "Exit");
  menu->addMenu("Moves");
  menu->addMenuItem("Moves", "Copy");
  menu->addMenuItem("Moves", "Paste");
  menu->addMenu("Help");
  menu->addMenuItem("Help", "About");
  // Signals: MenuItemClicked
  // Optional parameter sf::String: name of the item on which you clicked
  // Optional parameter std::vector<sf::String>: Which menu was open, followed
  // by which item you clicked on Uses Callback member 'text' (menu item name)
  // and index' (index of the open menu)
  //
  // signalNames	Name of the signal, or multiple names split by spaces
  // func	The function to connect
  // args	The arguments that should be bound to the function
  menu->connect("MenuItemClicked", handle_menu_click);

  gui.add(menu);

  // tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
  tgui::Panel::Ptr layout = tgui::Panel::create();
  layout->setBackgroundColor(sf::Color(0, 0, 0, 150));
  layout->setSize(140.f, config.window_size.y - config.window_menu_height);
  layout->setPosition(config.window_size.x - config.window_right_panel_width,
                      config.window_menu_height);
  gui.add(layout);

  tgui::Label::Ptr label = theme->load("Label");
  label->setText("TEST 1");
  label->setTextSize(10);
  // label->setPosition(10, 90);
  label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
  label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  layout->add(label);

  tgui::Button::Ptr button = theme->load("button");
  button->setPosition(10, config.window_size.y - 50 * 1.5 -
                              config.window_right_panel_padding);
  button->setSize(config.window_right_panel_width -
                      2 * config.window_right_panel_padding,
                  50);
  button->setText("Fin de Tour");
  button->connect("pressed",
                  [=]() { std::cout << "button - end turn" << std::endl; });
  // button->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
  // button->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  layout->add(button);

  // ---------------------------------------------------------------------------
  //                                BACKGROUND
  // ---------------------------------------------------------------------------

  render::Background bg = render::Background(&config);

  // ---------------------------------------------------------------------------
  //                                    FPS
  // ---------------------------------------------------------------------------

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

  render::HexaMap hm = render::HexaMap(&config);
  std::cout << "hexamap width " << hm.get_width() << std::endl;
  std::cout << "hexamap height " << hm.get_height() << std::endl;

  int map_full_width = config.window_size.x - config.window_right_panel_width;
  int map_full_height = config.window_size.y - config.window_menu_height;
  int map_offset_x = 0 + (map_full_width - hm.get_width()) / 2;
  int map_offset_y =
      config.window_menu_height + (map_full_height - hm.get_height()) / 2;
  hm.setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              ENTITTY
  // ---------------------------------------------------------------------------

  render::HexaEntity he = render::HexaEntity(&config);
  he.setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              FPS
  // ---------------------------------------------------------------------------

  render::Fps fps = render::Fps(&config);

  // ---------------------------------------------------------------------------
  //                              init map
  // ---------------------------------------------------------------------------

  /*
  for (int r = 0; r < config.hexamap_n_row; ++r) {
    for (int c = 0; c < config.hexamap_n_col; ++c) {
      he.entity_set(r, c, rand() % 11);
      hm.hex_set_color(r, c, config.hexamap_colors[rand() % 6]);

      if (rand() % 2) {
        hm.hex_show(r, c);
        he.entity_set(r, c, rand() % 10);
        he.entity_show(r, c);
      } else {
        hm.hex_hide(r, c);
        he.entity_set(r, c, 0);
        he.entity_hide(r, c);
      }
    }
  }
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
          // hm.initialize(r, ++c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Left) {
          std::cout << "Left" << std::endl;
          // hm.initialize(r, --c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Up) {
          std::cout << "Up" << std::endl;
          // hm.initialize(--r, c, hexa_r);
        } else if (event.key.code == sf::Keyboard::Down) {
          std::cout << "Down" << std::endl;
          // hm.initialize(++r, c, hexa_r);
          //} else if (event.key.code == sf::Keyboard::Enter) {
          //  std::cout << "OK" << std::endl;
        } else if (event.key.code == sf::Keyboard::Add) {
          std::cout << "+" << std::endl;
          // hm.initialize(r, c, ++hexa_r);
        } else if (event.key.code == sf::Keyboard::Subtract) {
          std::cout << "-" << std::endl;
          // hm.initialize(r, c, --hexa_r);
        }
        // hm.update();
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
          sf::Vector2i pos;
          std::cout << "LEFT (" << event.mouseButton.x << ", ";
          std::cout << event.mouseButton.y << ")" << std::endl;
          // convert pixel to position(row, col)

          pos = hm.PointToCoord(event.mouseButton.x, event.mouseButton.y);
          std::cout << "=>" << pos.x << "," << pos.y << std::endl;

          if ((pos.x >= 0 && pos.x < config.hexamap_n_row) &&
              (pos.y >= 0 && pos.y < config.hexamap_n_col)) {
            // hm.change_color(r_click, c_click, sf::Color(0, 0, 0));
            hm.hex_toggle_transparency(pos.x, pos.y);
            he.entity_toggle_transparency(pos.x, pos.y);
          }
        }
      }

      // Pass the event to all the widgets
      gui.handleEvent(event);
    }

    window.clear(); // clear the screen (not necessary)
    // DRAW : start -------------------------------------------------------
    window.draw(bg); // background
    window.draw(hm); // hexa map
    window.draw(he); // entities
    gui.draw();
    window.draw(fps); // fps

    // DRAW : end   -------------------------------------------------------
    window.display();

    he.update();
    bg.update();
    fps.update();
  }
}
