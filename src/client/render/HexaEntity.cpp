#include "HexaEntity.h"

#include <iostream>
#include <math.h> // sqrt
#include <time.h> // time

using namespace render;

HexaEntity::HexaEntity(RenderConfig &conf) : conf(conf) {

  int hexa_w_2 = conf.hexamap_hexa_r;
  int hexa_h_2 = sqrt(conf.hexamap_hexa_r * conf.hexamap_hexa_r * 3. / 4.);
  int w = conf.entity_width - 2;
  int h = conf.entity_height - 2;
  int w_2 = w / 2.f;
  int h_2 = h / 2.f;

  // setup the vertex array
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(4 * conf.hexamap_n_row * conf.hexamap_n_col);

  sf::Vector2i hc;
  for (int r = 0; r < conf.hexamap_n_row; ++r) {
    for (int c = 0; c < conf.hexamap_n_col; ++c) {

      // compute the center
      int offset = ((c % 2) == 1) ? hexa_h_2 : 0;
      sf::Vector2f hc(hexa_w_2 * (1 + c * 3. / 2.),
                      hexa_h_2 * (1 + r * 2) + offset);

      sf::Vertex *quad = &m_vertices[4 * (r * conf.hexamap_n_col + c)];

      // define its 4 corners
      int dy = -7;
      quad[0].position = sf::Vector2f(hc.x - w_2, hc.y - h_2 + dy);
      quad[1].position = sf::Vector2f(hc.x + w_2, hc.y - h_2 + dy);
      quad[2].position = sf::Vector2f(hc.x + w_2, hc.y + h_2 + dy);
      quad[3].position = sf::Vector2f(hc.x - w_2, hc.y + h_2 + dy);

      // define it as transparent tile
      // top left
      quad[0].texCoords.x = 0 * (conf.entity_width) + 1;
      quad[0].texCoords.y = (0) * (conf.entity_height - 1) + 1;
      // top right
      quad[1].texCoords.x = quad[0].texCoords.x + w;
      quad[1].texCoords.y = quad[0].texCoords.y;
      // down right
      quad[2].texCoords.x = quad[0].texCoords.x + w;
      quad[2].texCoords.y = quad[0].texCoords.y + h;
      // down left
      quad[3].texCoords.x = quad[0].texCoords.x;
      quad[3].texCoords.y = quad[0].texCoords.y + h;

      entity_set(r, c, 0);
    }
  }
}

HexaEntity::~HexaEntity() {}

void HexaEntity::entity_set_transparency(int r, int c, int a) {
  sf::Vertex *quad = &m_vertices[4 * (r * conf.hexamap_n_col + c)];
  for (int i = 0; i < 4; ++i) {
    quad[i].color.a = a;
  }
}

void HexaEntity::entity_hide(int r, int c) { entity_set_transparency(r, c, 0); }

void HexaEntity::entity_show(int r, int c) {
  entity_set_transparency(r, c, 255);
}

void HexaEntity::entity_toggle_transparency(int r, int c) {
  if (m_vertices[4 * (r * conf.hexamap_n_col + c)].color.a == 0) {
    entity_show(r, c);
  } else {
    entity_hide(r, c);
  }
}

void HexaEntity::entity_set(int r, int c, int entity_type) {
  int w, h;
  w = conf.entity_width - 2;
  h = conf.entity_height - 2;

  sf::Vertex *quad = &m_vertices[4 * (r * conf.hexamap_n_col + c)];

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

void HexaEntity::update() {
  int w = conf.entity_width - 2;

  if (clk.getElapsedTime().asSeconds() > (1. / conf.entity_fps)) {
    clk.restart();

    sf::Vertex *quad;
    for (int r = 0; r < conf.hexamap_n_row; ++r) {
      for (int c = 0; c < conf.hexamap_n_col; ++c) {
        quad = &m_vertices[4 * (r * conf.hexamap_n_col + c)];
        quad[0].texCoords.x = i_frame * (conf.entity_width - 1) + 1;
        quad[1].texCoords.x = quad[0].texCoords.x + w;
        quad[2].texCoords.x = quad[0].texCoords.x + w;
        quad[3].texCoords.x = quad[0].texCoords.x;
      }
    }
    // update frame
    i_frame = (i_frame + 1) % conf.entity_frames;
  }
}

void HexaEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();    // apply the transform
  states.texture = &conf.entity_tileset; // apply the texture
  target.draw(m_vertices, states);       // draw the vertex array
}
