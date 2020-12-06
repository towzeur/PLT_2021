#include "HexaEntity.h"

#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace render;

HexaEntity::HexaEntity(RenderConfig &conf, HexaMap &hm) : conf(conf), hm(hm) {}

HexaEntity::~HexaEntity() {}

void HexaEntity::initialize() {

  int n_row, n_col, w, h, w_2, h_2;
  n_row = hm.get_n_row();
  n_col = hm.get_n_col();
  w = conf.entity_width - 2;
  h = conf.entity_height - 2;
  w_2 = w / 2.f;
  h_2 = h / 2.f;

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(4 * n_row * n_col);

  sf::Vector2i hc;
  for (int r = 0; r < n_row; ++r) {
    for (int c = 0; c < n_col; ++c) {

      hc = hm.get_hexa_center(r, c);
      sf::Vertex *quad = &m_vertices[4 * (r * n_col + c)];

      // define its 4 corners
      int dy = -7;
      quad[0].position = sf::Vector2f(hc.x - w_2, hc.y - h_2 + dy);
      quad[1].position = sf::Vector2f(hc.x + w_2, hc.y - h_2 + dy);
      quad[2].position = sf::Vector2f(hc.x + w_2, hc.y + h_2 + dy);
      quad[3].position = sf::Vector2f(hc.x - w_2, hc.y + h_2 + dy);

      entity_show(r, c);
      entity_set(r, c, 0);
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

void HexaEntity::entity_set(int r, int c, int entity_type) {
  int n_row, n_col, w, h, w_2, h_2;
  n_row = hm.get_n_row();
  n_col = hm.get_n_col();
  w = conf.entity_width - 2;
  h = conf.entity_height - 2;
  w_2 = w / 2.f;
  h_2 = h / 2.f;

  int i0 = 4 * (r * n_col + c);
  sf::Vertex *quad = &m_vertices[i0];

  // top left
  quad[0].texCoords.x = 0 * (conf.entity_width) + 1;
  quad[0].texCoords.y = (entity_type) * (conf.entity_height - 1) + 1;

  // top right
  quad[1].texCoords.x = quad[0].texCoords.x + w;
  quad[1].texCoords.y = quad[0].texCoords.y;

  // down right
  quad[2].texCoords.x = quad[0].texCoords.x + w;
  quad[2].texCoords.y = quad[0].texCoords.y + h;

  // down left
  quad[3].texCoords.x = quad[0].texCoords.x;
  quad[3].texCoords.y = quad[0].texCoords.y + h;
}

void HexaEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform(); // apply the transform
  states.texture = &conf.entity_tileset;
  //&m_tileset;        // apply the tileset texture
  target.draw(m_vertices, states); // draw the vertex array
}