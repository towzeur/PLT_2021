#include "../render.h"
#include <string>

using namespace render;

TileSet::TileSet(TileSetID newID, std::string env) {

  id = newID;

  // if (id == TileSetID::HUD)
  // {
  // 	cellWidth = 32;
  // 	cellHeight = 32;
  // 	resourceFile = (env == "test") ? "../../../res/32x32map.png" :
  // "res/32x32map.png";
  // }

  if (id == TileSetID::MAP) {
    cellWidth = 10;
    cellHeight = 10;
    resourceFile = (env == "test") ? "../../../res/texture/tileset.png"
                                   : "res/texture/tileset.png";
  }

  textureTileset.loadFromFile(resourceFile);
}

const int TileSet::getTileSetID() { return id; }

const int TileSet::getCellWidth() { return cellWidth; }

const int TileSet::getCellHeight() { return cellHeight; }

const std::string TileSet::getImageFile() { return resourceFile; }

sf::Texture &TileSet::getTexture() {
  sf::Texture &refTexture = textureTileset;
  return refTexture;
}
