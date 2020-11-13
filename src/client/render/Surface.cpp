#include "Surface.h"

using namespace render;

bool Surface::load(const std::string &tileset, sf::Vector2u tileSize,
                   unsigned int *level, unsigned int nb_col,
                   unsigned int nb_row) {
  // load the tileset texture
  if (!m_tileset.loadFromFile(tileset))
    return false;

  // resize the vertex array to fit the level size
  m_vertices.setPrimitiveType(sf::Triangles);
  m_vertices.resize(nb_col * nb_row * 3 * 4);

  // populate the vertex array, with one hexagon per tile
  for (unsigned int i = 0; i < nb_row; ++i) {
    unsigned int odd_offset = 0;

    if (i % 2 == 0)
      odd_offset = tileSize.x / 2;

    for (unsigned int j = 0; j < nb_col; ++j) {

      if (level[i * nb_row + j] == 9)
        continue;

      else {
        // get the current tile type
        int tileNumber = level[i * nb_row + j];

        // get a pointer to the current tile's hexagone
        sf::Vertex *hex = &m_vertices[(i + j * nb_col) * 3 * 4];

        // set hex position
        hex[0].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                       tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[1].position =
            sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                         0 + tileSize.y * 3 / 4 * i);
        hex[2].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                       tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[3].position = sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                                       tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[4].position =
            sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                         tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
        hex[5].position =
            sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                         tileSize.y + tileSize.y * 3 / 4 * i);
        hex[6].position =
            sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                         tileSize.y + tileSize.y * 3 / 4 * i);
        hex[7].position =
            sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                         tileSize.y * 3 / 4 + tileSize.y * 3 / 4 * i);
        hex[8].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                       tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[9].position = sf::Vector2f(odd_offset + tileSize.x + tileSize.x * j,
                                       tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[10].position =
            sf::Vector2f(odd_offset + 0 + tileSize.x * j,
                         tileSize.y / 4 + tileSize.y * 3 / 4 * i);
        hex[11].position =
            sf::Vector2f(odd_offset + tileSize.x / 2 + tileSize.x * j,
                         tileSize.y + tileSize.y * 3 / 4 * i);

        // texture coord
        hex[0].texCoords =
            sf::Vector2f(tileSize.x + tileSize.x * tileNumber, tileSize.y / 4);
        hex[1].texCoords =
            sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber, 0);
        hex[2].texCoords =
            sf::Vector2f(0 + tileSize.x * tileNumber, tileSize.y / 4);
        hex[3].texCoords =
            sf::Vector2f(0 + tileSize.x * tileNumber, tileSize.y / 4);
        hex[4].texCoords =
            sf::Vector2f(0 + tileSize.x * tileNumber, tileSize.y * 3 / 4);
        hex[5].texCoords =
            sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber, tileSize.y);
        hex[6].texCoords =
            sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber, tileSize.y);
        hex[7].texCoords = sf::Vector2f(tileSize.x + tileSize.x * tileNumber,
                                        tileSize.y * 3 / 4);
        hex[8].texCoords =
            sf::Vector2f(tileSize.x + tileSize.x * tileNumber, tileSize.y / 4);
        hex[9].texCoords =
            sf::Vector2f(tileSize.x + tileSize.x * tileNumber, tileSize.y / 4);
        hex[10].texCoords =
            sf::Vector2f(0 + tileSize.x * tileNumber, tileSize.y / 4);
        hex[11].texCoords =
            sf::Vector2f(tileSize.x / 2 + tileSize.x * tileNumber, tileSize.y);
      }
    }
  }
  return true;
}

void Surface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &m_tileset;

  // draw the vertex array
  target.draw(m_vertices, states);
}
