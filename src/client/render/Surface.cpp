#include "Surface.h"
#include "../render.h"
#include "state.h"
#include <iostream>

using namespace render;

bool Surface::load(const std::string &tileset, sf::Vector2u tileSize,
                   state::Board &board, unsigned int nb_col,
                   unsigned int nb_row, int surfaceNb) {

  int x_offset = 30;
  int y_offset = 30;
  sf::Vector2u size(tileSize.x * zoom, tileSize.y * zoom);
  std::vector<std::unique_ptr<state::Cell>> &cells = board.getCells();
  state::Cell cell;
  int tileNumber;
  int playerId;
  state::Entity entity;
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
      odd_offset = size.x / 2;
    for (unsigned int j = 0; j < nb_col; ++j) {

      std::unique_ptr<state::Cell> &cell = cells[i * nb_row + j];

      if (surfaceNb == 0) {
        if (!cell->isAccessible()) {
          tileNumber = 0;
        } else {
          playerId = cell->getPlayerId();
          if (playerId == 0) {
            tileNumber = 1;
          } else if (playerId == 1) {
            tileNumber = 2;
          } else if (playerId == 2) {
            tileNumber = 3;
          } else if (playerId == 3) {
            tileNumber = 4;
          } else if (playerId == 4) {
            tileNumber = 5;
          } else if (playerId == 5) {
            tileNumber = 6;
          } else if (playerId == 6) {
            tileNumber = 7;
          }
        }
      } else if (surfaceNb == 1) {
        if (!cell->isAccessible()) {
          tileNumber = 0;
        } else {
          entity = cell->getEntity();
          if (entity.isEmpty()) {
            tileNumber = 0;
          } else if (entity.isSoldier()) {
            if (entity.getSubTypeId() == 1) {
              tileNumber = 9;
            } else if (entity.getSubTypeId() == 2) {
              tileNumber = 8;
            } else if (entity.getSubTypeId() == 3) {
              tileNumber = 7;
            } else if (entity.getSubTypeId() == 4) {
              tileNumber = 6;
            }
          } else if (entity.isFacility()) {
            if (entity.getSubTypeId() == 1) {
              tileNumber = 2;
            } else if (entity.getSubTypeId() == 2) {
              tileNumber = 1;
            } else if (entity.getSubTypeId() == 3) {
              tileNumber = 5;
            }
          } else if (entity.isTree()) {
            if (entity.getSubTypeId() == 1) {
              tileNumber = 3;
            } else if (entity.getSubTypeId() == 2) {
              tileNumber = 4;
            }
          }
        }
      } else {
        std::cout << "Error surfaceNb" << std::endl;
        exit(EXIT_FAILURE);
      }

      // get a pointer to the current tile's hexagone
      sf::Vertex *hex = &m_vertices[(i + j * nb_col) * 3 * 4];

      // set hex position
      hex[0].position =
          sf::Vector2f(x_offset + odd_offset + size.x + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[1].position =
          sf::Vector2f(x_offset + odd_offset + size.x / 2 + size.x * j,
                       y_offset + 0 + size.y * 3 / 4 * i);
      hex[2].position =
          sf::Vector2f(x_offset + odd_offset + 0 + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[3].position =
          sf::Vector2f(x_offset + odd_offset + 0 + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[4].position =
          sf::Vector2f(x_offset + odd_offset + 0 + size.x * j,
                       y_offset + size.y * 3 / 4 + size.y * 3 / 4 * i);
      hex[5].position =
          sf::Vector2f(x_offset + odd_offset + size.x / 2 + size.x * j,
                       y_offset + size.y + size.y * 3 / 4 * i);
      hex[6].position =
          sf::Vector2f(x_offset + odd_offset + size.x / 2 + size.x * j,
                       y_offset + size.y + size.y * 3 / 4 * i);
      hex[7].position =
          sf::Vector2f(x_offset + odd_offset + size.x + size.x * j,
                       y_offset + size.y * 3 / 4 + size.y * 3 / 4 * i);
      hex[8].position =
          sf::Vector2f(x_offset + odd_offset + size.x + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[9].position =
          sf::Vector2f(x_offset + odd_offset + size.x + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[10].position =
          sf::Vector2f(x_offset + odd_offset + 0 + size.x * j,
                       y_offset + size.y / 4 + size.y * 3 / 4 * i);
      hex[11].position =
          sf::Vector2f(x_offset + odd_offset + size.x / 2 + size.x * j,
                       y_offset + size.y + size.y * 3 / 4 * i);

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
