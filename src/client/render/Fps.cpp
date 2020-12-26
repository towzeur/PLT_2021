#include "Fps.h"

using namespace render;

Fps::Fps(RenderConfig &conf) : conf(conf) {

  text.setFont(conf.fps_font);
  text.setString("60");
  text.setCharacterSize(30); // in pixel !
  text.setFillColor(sf::Color::Yellow);
  // text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

void Fps::update() {
  if (clk.getElapsedTime().asSeconds() > 1.f) {
    int w = text.getLocalBounds().width;
    int h = text.getLocalBounds().height;
    int x = conf.window_size.x - w - 10; // config.window_right_panel_width
    int y = 0;

    text.setString(std::to_string(frames));
    text.setPosition(x, y);

    clk.restart();
    frames = 0;
  }
  frames++;
}

void Fps::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (conf.fps_enable) {
    target.draw(text);
  }
}
