#include "HexaEntity.h"

#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace render;

HexaEntity::HexaEntity(RenderConfig &conf, HexaMap &hm) : conf(conf), hm(hm) {}

HexaEntity::~HexaEntity() {}

void HexaEntity::initialize() {

  const int n_row = hm.get_n_row(), n_col = hm.get_n_col();

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(4 * n_row * n_col);

  int x0, y0, w, h;

  w = conf.entity_width - 2;
  h = conf.entity_height - 2;
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

      hc = hm.get_hexa_center(r, c);

      int i0 = 4 * (r * n_col + c);
      sf::Vertex *quad = &m_vertices[i0];
      // std::cout << hc.x << " | " << hc.y << std::endl;

      // define its 4 corners
      quad[0].position = sf::Vector2f(hc.x - w_2, hc.y - h_2);
      quad[1].position = sf::Vector2f(hc.x + w_2, hc.y - h_2);
      quad[2].position = sf::Vector2f(hc.x + w_2, hc.y + h_2);
      quad[3].position = sf::Vector2f(hc.x - w_2, hc.y + h_2);

      entity_show(r, c);

      // define its 4 texture coordinates
      // -------------------------------------------
      int i_entity = 0, x0, y0, x1, y1, x2, y2, x3, y3;
      if (rand() % 2) {
        i_entity = rand() % 10;
      }
      // top left
      x0 = 0 * (conf.entity_width) + 1;
      y0 = (i_entity) * (conf.entity_height - 1) + 1;
      // top right
      x1 = x0 + w;
      y1 = y0;
      // down right
      x2 = x0 + w;
      y2 = y0 + h;
      // down left
      x3 = x0;
      y3 = y0 + h;

      quad[0].texCoords = sf::Vector2f(x0, y0);
      quad[1].texCoords = sf::Vector2f(x1, y1);
      quad[2].texCoords = sf::Vector2f(x2, y2);
      quad[3].texCoords = sf::Vector2f(x3, y3);
    }
  }
}

void HexaEntity::update() {}

void HexaEntity::entity_set_transparency(int r, int c, int a) {
  sf::Vertex *quad = &m_vertices[4 * (r * hm.get_n_col() + c)];
  for (int i = 0; i < 4; ++i) {
    quad[i].color.a = a;
  }
}

void HexaEntity::entity_hide(int r, int c) { entity_set_transparency(r, c, 0); }

void HexaEntity::entity_show(int r, int c) {
  entity_set_transparency(r, c, 255);
}

void HexaEntity::entity_toggle_transparency(int r, int c) {
  if (m_vertices[4 * (r * hm.get_n_col() + c)].color.a == 0) {
    entity_show(r, c);
  } else {
    entity_hide(r, c);
  }
}

void HexaEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform(); // apply the transform
  states.texture = &conf.entity_tileset;
  //&m_tileset;        // apply the tileset texture
  target.draw(m_vertices, states); // draw the vertex array
}