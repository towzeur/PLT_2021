#include "Fps.h"

using namespace render;

Fps::Fps() {}

Fps::Fps(RenderConfig *conf) : conf(conf) {

  text.setFont(conf->fps_font);
  text.setString("60");
  text.setCharacterSize(30); // in pixel !
  text.setFillColor(sf::Color::Yellow);
  // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  // update it the first time
  update();
}

void Fps::update() {
  if (clk.getElapsedTime().asSeconds() > 1.f) {
    text.setString(std::to_string(frames));

    int w = text.getLocalBounds().width;
    int h = text.getLocalBounds().height;
    int x = conf->window_size.x - w - conf->window_right_panel_padding;
    int y = 0; // conf->window_menu_height;
    text.setPosition(x, y);

    clk.restart();
    frames = 0;
  }
  frames++;
}

void Fps::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (conf->fps_enable) {
    target.draw(text);
  }
}
