#include "RightPanel.h"
#include "Render.h"
#include "RenderConfig.h"
#include "TerritoryInfo.h"
#include <TGUI/TGUI.hpp>

using namespace render;

RightPanel::RightPanel() {}

RightPanel::RightPanel(Render *r) : r(r) {
  std::shared_ptr<RenderConfig> conf = r->getConfig();
  padding_x = conf->window_right_panel_padding;
  padding_y = conf->window_right_panel_padding;
  width = conf->window_right_panel_width;
  height = conf->window_size.y - conf->window_menu_height;
  absolute_x = conf->window_size.x - width;
  absolute_y = conf->window_menu_height;
}

void RightPanel::init() {
  tgui::Gui *gui = r->getGui();
  tgui::Theme::Ptr theme = r->getTheme();
  std::shared_ptr<RenderConfig> conf = r->getConfig();

  // ---------------------------------------------------------------------------
  // LAYOUT
  // ---------------------------------------------------------------------------
  // tgui::VerticalLayout::Ptr layout = tgui::VerticalLayout::create();
  this->layout = tgui::Panel::create();
  layout->setBackgroundColor(sf::Color(0, 0, 0, 150));
  layout->setSize(width, height);
  layout->setPosition(absolute_x, absolute_y);
  gui->add(layout);

  // ---------------------------------------------------------------------------
  // territory information
  // ---------------------------------------------------------------------------

  TerritoryInfo t_info(r);
  t_info.init(padding_x, 90, width - 2 * padding_x);
  // t_info.update(10, 4, 2, 14);
  // t_info.hide();
  // t_info.show();
  t_info.reset();

  // ---------------------------------------------------------------------------
  // BUTTON
  // ---------------------------------------------------------------------------

  // tgui::TextBox::Ptr tbox = tgui::TextBox::create();
  // tbox->setPosition(10, 90);
  // tbox->setTextSize(10);
  // tbox->setText("hello");
  // layout->add(tbox);

  // btn end turn

  // btn buy soldier
  tgui::Button::Ptr btn_soldier = theme->load("button");
  int btn_soldier_x = 50;
  int btn_soldier_y = 200;
  btn_soldier->setPosition(btn_soldier_x, btn_soldier_y);
  btn_soldier->setSize(conf->entity_width, conf->entity_height);
  std::shared_ptr<tgui::ButtonRenderer> br = btn_soldier->getRenderer();
  sf::IntRect partRect =
      sf::IntRect(1, 7 * (conf->entity_height - 1) + 1, conf->entity_width - 2,
                  conf->entity_height - 2);

  tgui::Texture texture(conf->entity_tileset, partRect);
  br->setNormalTexture(texture);
  br->setHoverTexture(texture);
  // br->setDownTexture(texture);
  br->setFocusTexture(texture);
  // btn_soldier->connect("pressed",
  //                     [&]() { this->window->setMouseCursorVisible(false); });
  layout->add(btn_soldier);

  sf::Texture t_peasant;
  t_peasant.loadFromFile(conf->entity_tileset_path, partRect);
  sf::Image i_peasant = t_peasant.copyToImage();

  // sf::Sprite sprite(textureCursorNormal);
  // sf::Texture textureCursorHover;
  // textureCursorHover.loadFromFile("CursorHover.png");
  // window->setMouseCursorVisible(false);

  // ---------------------------------------------------------------------------
  // BUTTON : end of turn
  // ---------------------------------------------------------------------------
  tgui::Button::Ptr button = theme->load("button");
  // button->setFont(conf->window_right_panel_font);
  button->setText("End of Turn");
  button->setSize(width - 2 * padding_x, 50);
  button->setPosition(padding_x, height - padding_y - button->getSize().y);
  auto fp2 = std::bind(&Render::handle_endturn, r);
  button->connect("pressed", fp2);
  // button->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
  // button->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  layout->add(button);
}

tgui::Panel::Ptr RightPanel::getLayout() { return layout; }
