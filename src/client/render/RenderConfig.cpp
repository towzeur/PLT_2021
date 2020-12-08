#include "RenderConfig.h"

#include "json/json.h" // Json
#include <fstream>
#include <iostream>

using namespace render;

RenderConfig::RenderConfig() {}

void RenderConfig::load(std::string skin_name) {

  std::string tmp;
  Json::Value node;

  // ---------------------------------------------------------------------------
  // construct the relative path from the skin name
  // ---------------------------------------------------------------------------
  std::ostringstream stream;
  stream << "res/skins/";
  stream << skin_name;
  stream << ".json";
  std::string rpath_skin = utils::Utils::resolveRelative(stream.str());

  // ---------------------------------------------------------------------------
  // open the file
  // ---------------------------------------------------------------------------
  std::ifstream ifs;
  ifs.open(rpath_skin);
  if (!ifs.is_open()) {
    std::cout << "can't open skin : " << rpath_skin << std::endl;
    exit(1);
  }

  // ---------------------------------------------------------------------------
  // parse json
  // ---------------------------------------------------------------------------
  Json::Value root;

  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    exit(1);
  }
  // std::cout << root << std::endl;

  // ---------------------------------------------------------------------------
  // parse
  // ---------------------------------------------------------------------------

  name = root["Name"].asString();

  // ======== window ========
  window_width = root["window_width"].asInt();
  window_height = root["window_height"].asInt();
  window_icon = sf::Image{};
  tmp = utils::Utils::resolveRelative(root["window_icon_path"].asString());
  if (!window_icon.loadFromFile(tmp)) {
    // Error handling...
    std::cout << "[ERROR] window_icon_path" << std::endl;
    exit(1);
  }

  // ======== entity ========
  entity_width = root["entity_width"].asInt();
  entity_height = root["entity_height"].asInt();
  entity_frames = root["entity_frames"].asInt();
  tmp = utils::Utils::resolveRelative(root["entity_tileset_path"].asString());
  if (!entity_tileset.loadFromFile(tmp)) {
    std::cout << "[ERROR] entity_tileset_path" << std::endl;
    exit(1);
  }

  // ======== background ========
  node = root["background"];
  background_color = utils::Utils::stringToColor(node["color"].asString());
  background_enable = node["enable"].asBool();
  // background_image = sf::Image{};
  tmp = utils::Utils::resolveRelative(node["image_path"].asString());
  if (!background_image.loadFromFile(tmp)) {
    std::cout << "[ERROR] background_image_path" << std::endl;
    exit(1);
  }
  background_animated = node["animated"].asBool();
  background_fps = node["fps"].asInt();

  // ======== fps ========
  tmp = utils::Utils::resolveRelative(root["fps_path"].asString());
  if (!fps_font.loadFromFile(tmp)) {
    std::cout << "[ERROR] fps_path" << std::endl;
    exit(1);
  }

  // ======== HexaMap ========
  hexamap_outline_color =
      utils::Utils::stringToColor(root["hexamap_outline_color"].asString());

  // ========  territory_tooltips ========

  node = root["territory_tooltips"];
  territory_tooltips_width = node["width"].asInt();
  territory_tooltips_height = node["height"].asInt();
  territory_tooltips_margin_x = node["margin_x"].asInt();
  territory_tooltips_margin_y = node["margin_y"].asInt();
}
