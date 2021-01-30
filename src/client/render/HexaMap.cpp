#include "HexaMap.h"

#include <iostream>
#include <math.h> // sqrt

using namespace render;

HexaMap::HexaMap() {}

HexaMap::HexaMap(RenderConfig *conf) : conf(conf) {

  // Set-up
  // 8 : double quad 2*4
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(8 * conf->hexamap_n_row * conf->hexamap_n_col);

  // 12: 6 lines * 2 (points / line)
  m_vertices_2.setPrimitiveType(sf::Lines);
  m_vertices_2.resize(12 * conf->hexamap_n_row * conf->hexamap_n_col);

  // compute some values
  int hexa_w_2 = conf->hexamap_hexa_r;
  int hexa_h_2 = sqrt(hexa_w_2 * hexa_w_2 * 3. / 4.);

  /**
   * precompute offset
   *        2 _____ 1
   *         /  |  \
   *        /   |   \
   *     3 (----|----) 0
   *        \   |   /
   *       4 \__|__/ 5
   */
  sf::Vector2f hexa_offsets[6] = {
      sf::Vector2f(hexa_w_2, 0),
      sf::Vector2f(+hexa_w_2 / 2, +hexa_h_2),
      sf::Vector2f(-hexa_w_2 / 2, +hexa_h_2),
      sf::Vector2f(-hexa_w_2, 0),
      sf::Vector2f(-hexa_w_2 / 2, -hexa_h_2),
      sf::Vector2f(+hexa_w_2 / 2, -hexa_h_2),
  };

  // default color
  sf::Color default_col;
  if (conf->hexamap_colors.size())
    default_col = conf->hexamap_colors[0];
  else
    default_col = sf::Color::White;

  // fill vertex array
  for (int r = 0; r < conf->hexamap_n_row; ++r) {
    for (int c = 0; c < conf->hexamap_n_col; ++c) {

      // compute the center
      int offset = ((c % 2) == 1) ? hexa_h_2 : 0;
      sf::Vector2f hc(hexa_w_2 * (1 + c * 3. / 2.),
                      hexa_h_2 * (1 + r * 2) + offset);

      // set hexa's plain (filled) vertex
      int idx = 8 * (r * conf->hexamap_n_col + c);
      for (int i = 0; i < 4; ++i) {
        // upper rectangle
        int i_q0 = idx + i;
        m_vertices[i_q0].position = hc + hexa_offsets[i];
        m_vertices[i_q0].color = default_col; // default : config[0]
        m_vertices[i_q0].color.a = 0;         // default : transparent

        // lower rectangle
        int i_q1 = i_q0 + 4;
        m_vertices[i_q1].position = hc + hexa_offsets[(i + 3) % 6];
        m_vertices[i_q1].color = default_col; // default : config[0]
        m_vertices[i_q1].color.a = 0;         // default : transparent
      }

      // set hexa's outline vertex
      int idx_2 = 12 * (r * conf->hexamap_n_col + c);
      for (int i = 0; i < 6; ++i) {
        int i0 = idx_2 + 2 * i;
        int i1 = i0 + 1;
        // start
        m_vertices_2[i0].position = hc + hexa_offsets[i];
        m_vertices_2[i0].color = conf->hexamap_outline_color;
        m_vertices_2[i0].color.a = 0; // default : transparent

        // end
        m_vertices_2[i1].position = hc + hexa_offsets[(i + 1) % 6];
        m_vertices_2[i1].color = conf->hexamap_outline_color;
        m_vertices_2[i1].color.a = 0; // default : transparent
      }
    }
  }
}

HexaMap::~HexaMap() {
  // if (hexa_centers_x)
  //  delete hexa_centers_x;
  // if (hexa_centers_y)
  //  delete hexa_centers_y;
}

void HexaMap::hex_set_player(int r, int c, int player_id) {
  sf::Color col;
  if (player_id < (int)conf->hexamap_colors.size()) {
    col = sf::Color::Red; // throw error
  }
  col = conf->hexamap_colors[player_id];
  hex_set_color(r, c, col);
  hex_show(r, c);
}

void HexaMap::hex_set_color(int r, int c, sf::Color col) {
  int idx = 8 * (r * conf->hexamap_n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color = col;
  }
}

void HexaMap::hex_set_transparency(int r, int c, int a) {
  // hide the plain hexa
  int idx = 8 * (r * conf->hexamap_n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color.a = a;
  }
  // hide hexa's black outline
  int idx_2 = 12 * (r * conf->hexamap_n_col + c);
  for (int i = 0; i < 12; i++) {
    m_vertices_2[idx_2 + i].color.a = a;
  }
}
void HexaMap::hex_hide(int r, int c) { hex_set_transparency(r, c, 0); }

void HexaMap::hex_show(int r, int c) { hex_set_transparency(r, c, 255); }

void HexaMap::hex_toggle_transparency(int r, int c) {
  if (m_vertices[8 * (r * conf->hexamap_n_col + c)].color.a == 0) {
    hex_show(r, c);
  } else {
    hex_hide(r, c);
  }
}

void HexaMap::update() {}

/**
 * @brief branch-less coord in pixel coordinate to hexagonal coordinate
 *
 * @param x abscissa of the point (in pixel)
 * @param y ordinate of the point (in pixel)
 * @return sf::Vector2u
 */
sf::Vector2i HexaMap::PointToCoord(double x, double y) {

  const sf::Vector2f &offset = getPosition();
  if (x < offset.x || x >= (offset.x + get_width()))
    return sf::Vector2i(-1, -1);

  if (y < offset.y || y >= (offset.y + get_height()))
    return sf::Vector2i(-1, -1);

  // apply the offset
  x = x - offset.x;
  y = y - offset.y;

  // swap x and y for column-odd ; hexagon_h2=hexagon_w2; hexagon_w=>hexagon_w
  y = (y - get_hexa_h_2()) / (2 * get_hexa_h_2());
  double t1 = x / conf->hexamap_hexa_r;
  double t2 = floor(y + t1);
  int r = floor((floor(t1 - y) + t2) / 3.f);
  int q = floor((floor(2 * y + 1) + t2) / 3.f) - r;

  // cube to offset (q-odd)
  int cube_x = r, cube_z = q; // cube_y = -r - q
  int col = cube_x;
  int row = cube_z + (cube_x - (cube_x & 1)) / 2;

  return sf::Vector2i(row, col);
}

/**
 * @brief
 *
 * width = (hexagon_w / 4.f) * (nc > 0) + (nc * hexagon_w * 3.f / 4.f);
 *       = (hexagon_h / 4.) * ( (nc > 0) + 3 * nc )
 *
 * @return int
 */
int HexaMap::get_width() {
  return (get_hexa_w_2() / 2.) * (conf->hexamap_n_col > 0) +
         conf->hexamap_n_col * (get_hexa_w_2() * 3. / 2.);
}

/**
 * @brief
 *
 * height = (hexagon_h / 2.f) * (nc > 0) + (nr * hexagon_h);
 *
 *
 * @return int
 */
int HexaMap::get_height() {
  return get_hexa_h_2() * (conf->hexamap_n_col > 0) +
         (conf->hexamap_n_row * 2 * get_hexa_h_2());
}

int HexaMap::get_hexa_w_2() { return conf->hexamap_hexa_r; }

int HexaMap::get_hexa_h_2() {
  return sqrt(conf->hexamap_hexa_r * conf->hexamap_hexa_r * 3. / 4.);
}

sf::Vector2f HexaMap::get_hexa_center(int r, int c) {
  // compute some values
  int hexa_w_2 = get_hexa_w_2();
  int hexa_h_2 = get_hexa_h_2();
  int offset = ((c % 2) == 1) ? hexa_h_2 : 0;
  return sf::Vector2f(hexa_w_2 * (1 + c * 3. / 2.),
                      hexa_h_2 * (1 + r * 2) + offset);
}

void HexaMap::draw(sf::RenderTarget &target,
                   sf::RenderStates states) const { // const {
  states.transform *= getTransform();               // apply the transform
  states.texture = &m_tileset;                      // apply the tileset texture
  target.draw(m_vertices, states);                  // draw the fill
  target.draw(m_vertices_2, states);                // draw the outline
}
