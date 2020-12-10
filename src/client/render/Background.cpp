#include "Background.h"

using namespace render;

Background::Background(RenderConfig &conf) : conf(conf) {

  i_frame = 0;

  if (conf.background_enable) {
    // init the texture
    texture = sf::Texture();
    texture.setRepeated(true); // set this to fill the background

    if (conf.background_animated) {
      unsigned int width = conf.background_image.getSize().x;
      unsigned int height = conf.background_image.getSize().y;
      nb_frames = width / height;

      // create frames
      frames = new sf::Image[nb_frames];
      for (int i = 0; i < nb_frames; ++i) {
        frames[i].create(height, height);
        frames[i].copy(conf.background_image, 0, 0,
                       sf::IntRect(i * height, 0, height, height), true);
      }

      texture.loadFromImage(frames[5]);

    } else { // static bg (no tileset)
      texture.loadFromImage(conf.background_image);
    }

    // init the sprite
    sprite = sf::Sprite(
        texture, sf::IntRect(0, 0, conf.window_width, conf.window_height));
  }
}

Background::~Background() {
  if (frames) {
    delete frames;
  }
}

void Background::update() {
  if (conf.background_animated) {

    if (clk.getElapsedTime().asSeconds() > (1. / conf.background_fps)) {
      clk.restart();

      texture.update(frames[i_frame]);
      i_frame = (i_frame + 1) % nb_frames;
    }
  }
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (conf.background_enable) {
    states.transform *= getTransform();
    target.draw(sprite, states);
  } else {
    target.clear(conf.background_color);
  }
}