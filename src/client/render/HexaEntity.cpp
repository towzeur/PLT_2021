#include "HexaEntity.h"

#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace render;

HexaEntity::HexaEntity(HexaMap &hm, int ew, int eh)
    : hm(hm), entity_width(ew), entity_height(eh) {}

HexaEntity::~HexaEntity() {}

void HexaEntity::initialize(std::string tileset_path) {

  const int n_row = hm.get_n_row(), n_col = hm.get_n_col();

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(4 * n_row * n_col);

  // load the tileset texture
  if (!m_tileset.loadFromFile(tileset_path)) {
    exit(1);
  }

  int x0, y0, w, h;

  w = entity_width - 2;
  h = entity_height - 2;
  /*
  // top left
  x0 = 0 * (entity_width) + 1;
  y0 = (i_entity) * (entity_height - 1) + 1;
  // top right
  x1 = x0 + w;
  y1 = y0;
  // down right
  x2 = x0 + w;
  y2 = y0 + h;
  // down left
  x3 = x0;
  y3 = y0 + h;
  */

  sf::Vector2i hc;
  int w_2 = w / 2.f, h_2 = h / 2.f;

  srand(time(NULL));

  for (int r = 0; r < n_row; ++r) {
    for (int c = 0; c < n_col; ++c) {

      int i0 = 4 * (r * n_col + c);
      hc = hm.get_hexa_center(r, c);
      // std::cout << hc.x << " | " << hc.y << std::endl;

      // define its 4 corners
      m_vertices[i0 + 0].position = sf::Vector2f(hc.x - w_2, hc.y - h_2);
      m_vertices[i0 + 1].position = sf::Vector2f(hc.x + w_2, hc.y - h_2);
      m_vertices[i0 + 2].position = sf::Vector2f(hc.x + w_2, hc.y + h_2);
      m_vertices[i0 + 3].position = sf::Vector2f(hc.x - w_2, hc.y + h_2);

      int a = (rand() % 2) ? 0 : 255;
      for (int ai = 0; ai < 4; ++ai) {
        m_vertices[i0 + ai].color.a = a;
      }

      // define its 4 texture coordinates
      m_vertices[i0 + 0].texCoords = sf::Vector2f(1, 1);
      m_vertices[i0 + 1].texCoords = sf::Vector2f(18, 1);
      m_vertices[i0 + 2].texCoords = sf::Vector2f(18, 28);
      m_vertices[i0 + 3].texCoords = sf::Vector2f(1, 28);
    }
  }
}

void HexaEntity::update() {}

void HexaEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform(); // apply the transform
  states.texture = &m_tileset;        // apply the tileset texture
  target.draw(m_vertices, states);    // draw the vertex array
}