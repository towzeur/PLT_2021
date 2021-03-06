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

#include "utils/Utils.h"

using namespace render;

Render::Render() {}

void Render::init(std::string configName) {
  // std::cout << "HELLO WORLD" << std::endl;
  srand(time(NULL));
  running = true;
  config.load(configName); // load the config

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
  window = new sf::RenderWindow({config.window_size.x, config.window_size.y},
                                "Hexagons", style, settings);

  // set the Vsync
  window->setVerticalSyncEnabled(true);

  // center the window
  window->setPosition(sf::Vector2i(
      (sf::VideoMode::getDesktopMode().width - window->getSize().x) / 2,
      (sf::VideoMode::getDesktopMode().height - window->getSize().y) / 2));

  // set window's icon
  window->setIcon(config.window_icon.getSize().x,
                  config.window_icon.getSize().y,
                  config.window_icon.getPixelsPtr());

  // ---------------------------------------------------------------------------
  //                                   TGUI
  // ---------------------------------------------------------------------------

  // init the tgui::Gui
  gui = new tgui::Gui(*window);

  // set the theme
  const sf::String &tgui_theme =
      utils::Utils::resolveRelative("res/tgui/widgets/Black.txt");
  tgui::Theme::Ptr theme = tgui::Theme::create(tgui_theme);

  // create a menu bar
  tgui::MenuBar::Ptr menu = theme->load("MenuBar");
  menu->setSize(config.window_size.x, config.window_menu_height);

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

  // tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
  tgui::Panel::Ptr layout = tgui::Panel::create();
  layout->setBackgroundColor(sf::Color(0, 0, 0, 150));
  layout->setSize(140.f, config.window_size.y - config.window_menu_height);
  layout->setPosition(config.window_size.x - config.window_right_panel_width,
                      config.window_menu_height);
  gui->add(layout);

  // *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
  // territory information

  const std::string &tgui_font_2 =
      // const sf::String &tgui_font =
      utils::Utils::resolveRelative("res/fonts/RobotoMono-SemiBold.ttf");

  tgui::Label::Ptr label = theme->load("Label");
  std::string label_string = "Savings\nIncome\nWages\nBalance";
  label->setText(label_string);
  label->setTextSize(14);
  label->setPosition(config.territory_tooltips_margin_x, 90);
  label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
  label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  label->setFont(tgui_font_2);
  layout->add(label);

  tgui::Label::Ptr label_2 = theme->load("Label");
  std::string label_string_2 = "8\n+2\n0\n10";
  label_2->setText(label_string_2);
  label_2->setTextSize(14);
  label_2->setPosition(
      config.territory_tooltips_width - config.territory_tooltips_margin_x, 90);
  label_2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
  label_2->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  label_2->setFont(tgui_font_2);
  layout->add(label_2);

  // *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

  // tgui::TextBox::Ptr tbox = tgui::TextBox::create();
  // tbox->setPosition(10, 90);
  // tbox->setTextSize(10);
  // tbox->setText("hello");
  // layout->add(tbox);

  // btn end turn
  tgui::Button::Ptr button = theme->load("button");
  button->setPosition(10, config.window_size.y - 50 * 1.5 -
                              config.window_right_panel_padding);
  button->setSize(config.window_right_panel_width -
                      2 * config.window_right_panel_padding,
                  50);
  button->setText("End of Turn");

  // btn buy soldier
  tgui::Button::Ptr btn_soldier = theme->load("button");
  int btn_soldier_x = 50;
  int btn_soldier_y = 200;
  btn_soldier->setPosition(btn_soldier_x, btn_soldier_y);
  btn_soldier->setSize(config.entity_width, config.entity_height);
  std::shared_ptr<tgui::ButtonRenderer> br = btn_soldier->getRenderer();
  sf::IntRect partRect =
      sf::IntRect(1, 7 * (config.entity_height - 1) + 1,
                  config.entity_width - 2, config.entity_height - 2);

  tgui::Texture texture(config.entity_tileset, partRect);
  br->setNormalTexture(texture);
  br->setHoverTexture(texture);
  // br->setDownTexture(texture);
  br->setFocusTexture(texture);
  btn_soldier->connect("pressed",
                       [&]() { this->window->setMouseCursorVisible(false); });
  layout->add(btn_soldier);

  sf::Texture t_peasant;
  t_peasant.loadFromFile(config.entity_tileset_path, partRect);
  sf::Image i_peasant = t_peasant.copyToImage();

  // sf::Sprite sprite(textureCursorNormal);
  // sf::Texture textureCursorHover;
  // textureCursorHover.loadFromFile("CursorHover.png");
  window->setMouseCursorVisible(false);

  // btn buy castle
  auto fp2 = std::bind(&Render::handle_endturn, this);
  button->connect("pressed", fp2);
  // button->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
  // button->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  layout->add(button);

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

  bg = new Background(&config);

  // ---------------------------------------------------------------------------
  //                               HEXA MAP
  // ---------------------------------------------------------------------------

  // render::HexaMap hm = render::HexaMap(config);
  hm = new HexaMap(&config);
  // std::cout << "hexamap width " << hm->get_width() << std::endl;
  // std::cout << "hexamap height " << hm->get_height() << std::endl;
  int map_full_width = config.window_size.x - config.window_right_panel_width;
  int map_full_height = config.window_size.y - config.window_menu_height;
  int map_offset_x = 0 + (map_full_width - hm->get_width()) / 2;
  int map_offset_y =
      config.window_menu_height + (map_full_height - hm->get_height()) / 2;
  hm->setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              ENTITTY
  // ---------------------------------------------------------------------------

  he = new HexaEntity(&config);
  he->setPosition(map_offset_x, map_offset_y);

  // ---------------------------------------------------------------------------
  //                              FPS
  // ---------------------------------------------------------------------------

  fps = new Fps(&config);
}

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
  if (event.type == sf::Event::KeyPressed) {

    if (event.key.code == sf::Keyboard::Right) {
      std::cout << "Right" << std::endl;

    } else if (event.key.code == sf::Keyboard::Left) {
      std::cout << "Left" << std::endl;

    } else if (event.key.code == sf::Keyboard::Up) {
      std::cout << "Up" << std::endl;

    } else if (event.key.code == sf::Keyboard::Down) {
      std::cout << "Down" << std::endl;

    } else if (event.key.code == sf::Keyboard::Add) {
      std::cout << "+" << std::endl;
      // hm->initialize(r, c, ++hexa_r);
    } else if (event.key.code == sf::Keyboard::Subtract) {
      std::cout << "-" << std::endl;
    }
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

    if ((pos.x >= 0 && pos.x < config.hexamap_n_row) &&
        (pos.y >= 0 && pos.y < config.hexamap_n_col)) {
      this->handle_map(pos);
    }
  }
}

void Render::display_map(state::State &s) {
  state::Board &b = s.getBoard();

  std::shared_ptr<state::Cell> cell;
  state::AccessibleCell *acell;
  state::Entity entity;

  for (int r = 0; r < config.hexamap_n_row; ++r) {
    for (int c = 0; c < config.hexamap_n_col; ++c) {
      cell = b.get(r, c);

      if (cell->isAccessible()) { // accessible
        acell = cell->castAccessible();
        hm->hex_set_player(r, c, acell->getPlayerId());

        std::cout << entity.getEntityTypeId() << " ";

        entity = acell->getEntity();
        he->entity_set(r, c, entity.getEntitySubTypeId());
        he->entity_show(r, c);

      } else { // inaccessible
        hm->hex_hide(r, c);
        he->entity_hide(r, c);
      }
    }
    printf("\n");
  }
}