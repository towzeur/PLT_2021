#include "Background.h"

using namespace render;

Background::Background() {}

Background::~Background() {}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform(); // apply the transform
  states.texture = &m_tileset;        // apply the tileset texture
  target.draw(m_vertices, states);    // draw the vertex array
}