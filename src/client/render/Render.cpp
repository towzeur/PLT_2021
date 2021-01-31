#include <cstdlib>
#include <fstream>
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Render.h"

#include "state/AccessibleCell.h"
#include "state/Board.h"
#include "state/Cell.h"
#include "state/Entity.h"
#include "state/State.h"

#include "engine.h"
#include "utils/Utils.h"

using namespace render;

Render::Render() {}

void Render::init(std::string configName) {
  // std::cout << "HELLO WORLD" << std::endl;
  srand(time(NULL));
  running = true;

  // ---------------------------------------------------------------------------
  //                                CONFIG
  // ---------------------------------------------------------------------------
  config = std::make_shared<RenderConfig>();
  config->load(configName); // load the config

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
  window = new sf::RenderWindow({config->window_size.x, config->window_size.y},
                                "Hexagons", style, settings);

  // set the Vsync
  window->setVerticalSyncEnabled(true);

  // center the window
  window->setPosition(sf::Vector2i(
      (sf::VideoMode::getDesktopMode().width - window->getSize().x) / 2,
      (sf::VideoMode::getDesktopMode().height - window->getSize().y) / 2));

  // set window's icon
  window->setIcon(config->window_icon.getSize().x,
                  config->window_icon.getSize().y,
                  config->window_icon.getPixelsPtr());

  // ---------------------------------------------------------------------------
  //                                   TGUI
  // ---------------------------------------------------------------------------

  // init the tgui::Gui
  gui = new tgui::Gui(*window);

  // set the theme
  const sf::String &tgui_theme =
      utils::Utils::resolveRelative("res/tgui/widgets/Black.txt");
  theme = tgui::Theme::create(tgui_theme); // tgui::Theme::Ptr

  // create a menu bar
  tgui::MenuBar::Ptr menu = theme->load("MenuBar");
  menu->setSize(config->window_size.x, config->window_menu_height);

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
  auto fp = std::bind(&Render::handle_menu, this, std::placeholders::_1);
  menu->connect("MenuItemClicked", fp);
  gui->add(menu);

  // RightPanel rpanel(this);
  rpanel = std::make_shared<RightPanel>(this);
  rpanel->init();

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
  //                                BACKGROUND
  // ---------------------------------------------------------------------------

  bg = new Background(config.get());

  // ---------------------------------------------------------------------------
  //                               HEXA MAP
  // ---------------------------------------------------------------------------

  // render::HexaMap hm = render::HexaMap(config);
  hm = new HexaMap(config.get());
  // std::cout << "hexamap width " << hm->get_width() << std::endl;
  // std::cout << "hexamap height " << hm->get_height() << std::endl;
  int map_full_width = config->window_size.x - config->window_right_panel_width;
  int map_full_height = config->window_size.y - config->window_menu_height;
  int map_offset_x = 0 + (map_full_width - hm->get_width()) / 2;
  int map_offset_y =
      config->window_menu_height + (map_full_height - hm->get_height()) / 2;
  hm->setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              ENTITTY
  // ---------------------------------------------------------------------------

  he = new HexaEntity(config.get());
  he->setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              FPS
  // ---------------------------------------------------------------------------

  fps = new Fps(config.get());
}

/**
 * @brief run the Render (while loop)
 *
 */
void Render::run() {
  // ---------------------------------------------------------------------------
  //                              GAME LOOP
  // ---------------------------------------------------------------------------
  sf::Event event;
  while (window->isOpen() && running) {

    // events loop processing
    while (window->pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window->close();
        break;
      }

      // update the view to the new size of the window
      if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window->setView(sf::View(visibleArea));
      }

      // Pass the event to all the widgets
      if (gui->handleEvent(event))
        continue;

      if (event.type == sf::Event::KeyPressed)
        this->handle_keypressed(event);

      if (event.type == sf::Event::MouseButtonPressed)
        this->handle_mousebuttonpressed(event);
    }

    window->clear(); // clear the screen (not necessary)
    // DRAW : start ------------------------------------------------------------
    window->draw(*bg); // background
    window->draw(*hm); // hexa map
    window->draw(*he); // entities
    gui->draw();
    window->draw(*fps); // fps
    // DRAW : end   ------------------------------------------------------------
    window->display();

    he->update();
    bg->update();
    fps->update();
  }
}

void Render::handle_map(sf::Vector2i &pos) {
  printf("handle pos !\n");
  hm->hex_toggle_transparency(pos.x, pos.y);
  he->entity_toggle_transparency(pos.x, pos.y);

  engine::ActionSelectTerritory action(0, pos.x, pos.y);
  Json::Value ser = action.serialize();
  std::cout << ser << std::endl;

  toEngine(ser);
}

void Render::handle_menu(sf::String menu_name) {
  std::cout << "menu clicked : " << menu_name.toAnsiString() << std::endl;
  if (menu_name == "Load") {
  } else if (menu_name == "Save") {
  } else if (menu_name == "Exit") {
    this->running = false;
  } else if (menu_name == "Copy") {
  } else if (menu_name == "Paste") {
  } else if (menu_name == "About") {
  }
}

void Render::handle_endturn() { std::cout << "button - end turn" << std::endl; }

void Render::handle_keypressed(sf::Event &event) {
  if (event.type != sf::Event::KeyPressed)
    return;

  switch (event.key.code) {
  case sf::Keyboard::Right:
    std::cout << "Right" << std::endl;
    break;

  case sf::Keyboard::Left:
    std::cout << "Left" << std::endl;
    break;

  case sf::Keyboard::Up:
    std::cout << "Up" << std::endl;
    break;

  case sf::Keyboard::Down:
    std::cout << "Down" << std::endl;
    break;

  case sf::Keyboard::Add:
    std::cout << "+" << std::endl;
    break;

  case sf::Keyboard::Subtract:
    std::cout << "-" << std::endl;
    break;

  default:
    break;
  }
}

void Render::handle_mousebuttonpressed(sf::Event &event) {
  // sf::Event::MouseButtonPressed and sf::Event::MouseButtonReleased
  //  left, right, middle (wheel), extra #1 and extra #2 (side buttons)
  // std::cout << "[MOUSE] ";

  if (event.mouseButton.button == sf::Mouse::Right) {
    std::cout << "RIGHT (" << event.mouseButton.x << ", " << event.mouseButton.y
              << ")" << std::endl;
  }

  if (event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2i pos;
    std::cout << "LEFT (" << event.mouseButton.x << ", ";
    std::cout << event.mouseButton.y << ")" << std::endl;
    // convert pixel to position(row, col)

    pos = hm->PointToCoord(event.mouseButton.x, event.mouseButton.y);
    std::cout << "=>" << pos.x << "," << pos.y << std::endl;

    if ((pos.x >= 0 && pos.x < config->hexamap_n_row) &&
        (pos.y >= 0 && pos.y < config->hexamap_n_col)) {
      this->handle_map(pos);
    }
  }
}

void Render::display_map(state::State &s) {
  state::Board &b = s.getBoard();
  std::shared_ptr<state::Cell> cell;
  state::AccessibleCell *acell;

  for (int r = 0; r < config->hexamap_n_row; ++r) {
    for (int c = 0; c < config->hexamap_n_col; ++c) {
      cell = b.get(r, c);

      if (cell->isAccessible()) { // accessible
        acell = cell->castAccessible();
        state::Entity &entity = acell->getEntity();
        // std::cout << entity.getEntityTypeId() << " ";
        hm->hex_set_player(r, c, acell->getPlayerId());
        he->entity_set(r, c, entity.getEntitySubTypeId());
        he->entity_show(r, c);

      } else { // inaccessible
        hm->hex_hide(r, c);
        he->entity_hide(r, c);
      }
    }
    // std::cout << std::endl;
  }
}

/**
 * @brief
 *
 * @param e
 */
void Render::bind(engine::Engine &e) { this->eng = &e; }

void Render::toEngine(Json::Value &ser) {
  if (!eng)
    return;
  eng->processAction(ser);
}

tgui::Gui *Render::getGui() { return gui; }

tgui::Theme::Ptr Render::getTheme() { return theme; }

std::shared_ptr<RenderConfig> Render::getConfig() { return config; }

std::shared_ptr<RightPanel> Render::getPanel() { return rpanel; }
