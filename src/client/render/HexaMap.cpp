#include "HexaMap.h"

#include <iostream>
#include <math.h> // sin and cos

using namespace render;

HexaMap::HexaMap(unsigned int nr, unsigned int nc, float hr) {
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

void HexaMap::initialize() { initialize(n_row, n_col, hexagon_r); }

void HexaMap::initialize(unsigned int nr, unsigned int nc, float hr) {
  n_row = nr;
  n_col = nc;
  hexagon_r = hr;
  // std::cout << "1 *********************" << std::endl;

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(8 * n_row * n_col); // 8 : double quad 2*4

  hexagon_w2 = hexagon_r;
  hexagon_w = 2 * hexagon_w2;

  hexagon_h2 = sqrt(hexagon_r * hexagon_r * 3.f / 4.f);
  hexagon_h = 2 * hexagon_h2;

  hexa_centers_x = new int[n_col];
  for (unsigned int c = 0; c < n_col; c++)
    hexa_centers_x[c] = c * (hexagon_w * 3.0 / 4.0) + hexagon_w2;

  hexa_centers_y = new int[n_row];
  for (unsigned int r = 0; r < n_row; r++)
    hexa_centers_y[r] = (hexagon_h * r) + hexagon_h2;

  std::cout << std::endl;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  width = (hexagon_w / 4.f) * (nc > 0) + (nc * hexagon_w * 3.f / 4.f);
  height = (hexagon_h / 2.f) * (nc > 0) + (nr * hexagon_h);

  std::cout << "debug* width=" << width << std::endl;
  std::cout << "debug* height=" << height << std::endl;

  // sf::FloatRect tmp = m_vertices.getBounds();
  // std::cout << "debug*** width=" << tmp.width << std::endl;
  // std::cout << "debug*** height=" << tmp.height<< std::endl;
  // std::cout << "2 *********************" << std::endl;

  this->initialized = true;
}

void HexaMap::fill_vertex(int r, int c, sf::Color col) {
  sf::Vector2i hc = get_hexa_center(r, c);
  int idx = 8 * (r * n_col + c);

  // first quad (up)
  m_vertices[idx + 0].position = sf::Vector2f(hc.x + hexagon_w2, hc.y);
  m_vertices[idx + 1].position =
      sf::Vector2f(hc.x + 0.5 * hexagon_w2, hc.y + hexagon_h2);
  m_vertices[idx + 2].position =
      sf::Vector2f(hc.x - 0.5 * hexagon_w2, hc.y + hexagon_h2);
  m_vertices[idx + 3].position = sf::Vector2f(hc.x - hexagon_w2, hc.y);
  // second quad (top)
  m_vertices[idx + 4].position = m_vertices[idx + 3].position;
  m_vertices[idx + 5].position =
      sf::Vector2f(hc.x - 0.5 * hexagon_w2, hc.y - hexagon_h2);
  m_vertices[idx + 6].position =
      sf::Vector2f(hc.x + 0.5 * hexagon_w2, hc.y - hexagon_h2);
  m_vertices[idx + 7].position = m_vertices[idx + 0].position;

  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color = col;
  }
}

void HexaMap::hex_set_color(int r, int c, sf::Color col) {
  int idx = 8 * (r * n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color = col;
  }
}

void HexaMap::hex_set_transparency(int r, int c, int a) {
  int idx = 8 * (r * n_col + c);
  for (int i = 0; i < 8; i++) {
    m_vertices[idx + i].color.a = a;
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

  for (unsigned int c = 0; c < n_col; c++) {
    for (unsigned int r = 0; r < n_row; r++) {

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
  target.draw(m_vertices, states);                  // draw the vertex array
}

unsigned int HexaMap::getN_row() { return n_row; }

unsigned int HexaMap::getN_col() { return n_col; }

sf::Vector2i HexaMap::get_hexa_center(int r, int c) {
  int offset = ((c % 2) == 1) ? hexagon_h2 : 0;
  int xc = hexa_centers_x[c];
  int yc = hexa_centers_y[r] + offset;
  return sf::Vector2i(xc, yc);
}