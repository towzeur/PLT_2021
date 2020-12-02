#include "HexaMap.h"

#include <iostream>
#include <math.h> // sin and cos

using namespace render;

HexaMap::HexaMap(int nr, int nc, float hr) {
  n_row = nr;
  n_col = nc;
  hexagon_r = hr;

  COLOR_MAP[0] = sf::Color(187, 153, 221);
  COLOR_MAP[1] = sf::Color(221, 153, 187);
  COLOR_MAP[2] = sf::Color(153, 187, 221);

  COLOR_MAP_SLAY[0] = sf::Color(0, 255, 0);   // light green
  COLOR_MAP_SLAY[1] = sf::Color(192, 192, 0); //
  COLOR_MAP_SLAY[2] = sf::Color(0, 128, 0);   // green
  COLOR_MAP_SLAY[3] = sf::Color(255, 255, 0); // yellow
  COLOR_MAP_SLAY[4] = sf::Color(0, 192, 0);   //
  COLOR_MAP_SLAY[5] = sf::Color(128, 128, 0); // brown
}

HexaMap::~HexaMap() {
  if (hexa_centers_x)
    delete hexa_centers_x;
  if (hexa_centers_y)
    delete hexa_centers_y;
}

void HexaMap::initialize() { initialize(n_row, n_col, hexagon_r); }

void HexaMap::initialize(int nr, int nc, float hr) {
  n_row = nr;
  n_col = nc;
  hexagon_r = hr;

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(8 * n_row * n_col); // 8 : double quad 2*4

  m_vertices_2.setPrimitiveType(sf::Lines);
  m_vertices_2.resize(12 * n_row * n_col); // 12: 6 lines * 2 (points / line)

  hexagon_w2 = hexagon_r;
  hexagon_w = 2 * hexagon_w2;

  hexagon_h2 = sqrt(hexagon_r * hexagon_r * 3.f / 4.f);
  hexagon_h = 2 * hexagon_h2;

  hexa_centers_x = new int[n_col];
  for (int c = 0; c < n_col; c++)
    hexa_centers_x[c] = c * (hexagon_w * 3.0 / 4.0) + hexagon_w2;

  hexa_centers_y = new int[n_row];
  for (int r = 0; r < n_row; r++)
    hexa_centers_y[r] = (hexagon_h * r) + hexagon_h2;

  /**
   *        2 _____ 1
   *         /  |  \
   *        /   |   \
   *     3 (----|----) 0
   *        \   |   /
   *       4 \__|__/ 5
   */
  hexa_offsets[0] = sf::Vector2i(hexagon_w2, 0);
  hexa_offsets[1] = sf::Vector2i(+hexagon_w2 / 2, +hexagon_h2);
  hexa_offsets[2] = sf::Vector2i(-hexagon_w2 / 2, +hexagon_h2);
  hexa_offsets[3] = sf::Vector2i(-hexagon_w2, 0);
  hexa_offsets[4] = sf::Vector2i(-hexagon_w2 / 2, -hexagon_h2);
  hexa_offsets[5] = sf::Vector2i(+hexagon_w2 / 2, -hexagon_h2);

  for (int i = 0; i < 6; ++i) {
    std::cout << i << ' ' << hexa_offsets[i].x << ' ' << hexa_offsets[i].y
              << std::endl;
  }

  width = (hexagon_w / 4.f) * (nc > 0) + (nc * hexagon_w * 3.f / 4.f);
  height = (hexagon_h / 2.f) * (nc > 0) + (nr * hexagon_h);

  this->initialized = true;
}

/**
 * @brief

 * @param r
 * @param c
 * @param col
 */
void HexaMap::fill_vertex(int r, int c, sf::Color col) {
  sf::Vector2i hc = get_hexa_center(r, c);

  // set hexa's plain (filled) vertex
  int idx = 8 * (r * n_col + c);
  for (int i = 0; i < 4; ++i) {
    // upper rectangle
    int i_q0 = idx + i;
    m_vertices[i_q0].position.x = hc.x + hexa_offsets[i].x;
    m_vertices[i_q0].position.y = hc.y + hexa_offsets[i].y;
    m_vertices[i_q0].color = col;

    // lower rectangle
    int i_q1 = i_q0 + 4;
    m_vertices[i_q1].position.x = hc.x + hexa_offsets[(i + 3) % 6].x;
    m_vertices[i_q1].position.y = hc.y + hexa_offsets[(i + 3) % 6].y;
    m_vertices[i_q1].color = col;
  }

  // set hexa's outline vertex
  int idx_2 = 12 * (r * n_col + c);
  for (int i = 0; i < 6; ++i) {
    int i0 = idx_2 + 2 * i;
    int i1 = i0 + 1;
    // start
    m_vertices_2[i0].position.x = hc.x + hexa_offsets[i].x;
    m_vertices_2[i0].position.y = hc.y + hexa_offsets[i].y;
    m_vertices_2[i0].color = sf::Color::Black;
    // end
    m_vertices_2[i1].position.x = hc.x + hexa_offsets[(i + 1) % 6].x;
    m_vertices_2[i1].position.y = hc.y + hexa_offsets[(i + 1) % 6].y;
    m_vertices_2[i1].color = sf::Color::Black;
  }
}

void HexaMap::hex_set_color(int r, int c, sf::Color col) {
  int idx = 8 * (r * n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color = col;
  }
}

void HexaMap::hex_set_transparency(int r, int c, int a) {
  // hide the plain hexa
  int idx = 8 * (r * n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color.a = a;
  }
  // hide hexa's black outline
  int idx_2 = 12 * (r * n_col + c);
  for (int i = 0; i < 12; i++) {
    m_vertices_2[idx_2 + i].color.a = a;
  }
}
void HexaMap::hex_hide(int r, int c) { hex_set_transparency(r, c, 0); }

void HexaMap::hex_show(int r, int c) { hex_set_transparency(r, c, 255); }

void HexaMap::hex_toggle_transparency(int r, int c) {
  if (m_vertices[8 * (r * n_col + c)].color.a == 0) {
    hex_show(r, c);
  } else {
    hex_hide(r, c);
  }
}

void HexaMap::update() {
  if (!initialized)
    initialize();

  sf::Color color;
  int ci = 0;

  for (int c = 0; c < n_col; c++) {
    for (int r = 0; r < n_row; r++) {

      // color = COLOR_MAP[(ci++)%3];
      /*
      color = sf::Color(
          rand() % 256 + 1,
          rand() % 256 + 1,
          rand() % 256 + 1
      );
      */
      color = COLOR_MAP_SLAY[(ci++) % 6];
      // color = sf::Color::White;
      // color = (((c+r*n_col)%2)==0) ?  sf::Color::Blue : sf::Color::Red;
      fill_vertex(r, c, color);
    }
  }
}

sf::Vector2u HexaMap::PointToCoord(double x, double y) {
  // swap x and y for column-odd ; hexagon_h2=hexagon_w2; hexagon_w=>hexagon_w
  y = (y - hexagon_h2) / hexagon_h;
  double t1 = x / hexagon_r;
  double t2 = floor(y + t1);
  int r = floor((floor(t1 - y) + t2) / 3.f);
  int q = floor((floor(2 * y + 1) + t2) / 3.f) - r;

  // cube to offset (q-odd)
  int cube_x = r, cube_z = q; // cube_y = -r - q
  int col = cube_x;
  int row = cube_z + (cube_x - (cube_x & 1)) / 2;
  return sf::Vector2u(row, col);
}

void HexaMap::draw(sf::RenderTarget &target,
                   sf::RenderStates states) const { // const {
  states.transform *= getTransform();               // apply the transform
  states.texture = &m_tileset;                      // apply the tileset texture

  target.draw(m_vertices, states);   // draw the vertex array
  target.draw(m_vertices_2, states); // draw the vertex array
}

int HexaMap::get_n_row() { return n_row; }

int HexaMap::get_n_col() { return n_col; }

sf::Vector2i HexaMap::get_hexa_center(int r, int c) {
  int offset = ((c % 2) == 1) ? hexagon_h2 : 0;
  int xc = hexa_centers_x[c];
  int yc = hexa_centers_y[r] + offset;
  return sf::Vector2i(xc, yc);
}