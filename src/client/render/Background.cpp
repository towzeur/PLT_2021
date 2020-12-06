#include "Background.h"

using namespace render;

Background::Background(RenderConfig &conf) : conf(conf) {

  conf.bg_texture.setRepeated(true);
  // bg_sprite = sf::Sprite(texture, sf::IntRect(0, 0, WIDTH, HEIGHT));
}

Background::~Background() {}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (conf.bg_enable) {
    sf::Sprite s(conf.bg_texture,
                 sf::IntRect(0, 0, conf.window_width, conf.window_height));
    states.transform *= getTransform();
    // states.texture = &conf.bg_texture;
    target.draw(s, states);

  } else {
    target.clear(conf.bg_color);
  }
}