#include "RenderConfig.h"

#include "json/json.h"
#include <fstream>
#include <iostream>

using namespace render;

RenderConfig::RenderConfig() {}

RenderConfig::~RenderConfig() {}

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
  node = root["window"];
  // window_width = node["width"].asInt();
  // window_height = node["height"].asInt();
  window_size = sf::Vector2u(node["width"].asInt(), node["height"].asInt());
  window_icon = sf::Image{};
  tmp = utils::Utils::resolveRelative(node["icon_path"].asString());
  if (!window_icon.loadFromFile(tmp)) {
    // Error handling...
    std::cout << "[ERROR] window_icon_path" << std::endl;
    exit(1);
  }
  window_menu_height = node["menu_height"].asInt();
  window_right_panel_width = node["right_panel_width"].asInt();

  // ======== entity ========
  node = root["entity"];
  entity_width = node["width"].asInt();
  entity_height = node["height"].asInt();
  entity_frames = node["frames"].asInt();
  tmp = utils::Utils::resolveRelative(node["tileset_path"].asString());
  if (!entity_tileset.loadFromFile(tmp)) {
    std::cout << "[ERROR] entity_tileset_path" << std::endl;
    exit(1);
  }
  entity_fps = node["fps"].asInt();

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
  node = root["fps_counter"];
  fps_enable = node["enable"].asBool();
  tmp = utils::Utils::resolveRelative(node["font_path"].asString());
  if (!fps_font.loadFromFile(tmp)) {
    std::cout << "[ERROR] fps_path" << std::endl;
    exit(1);
  }

  // ======== HexaMap ========
  node = root["hexamap"];
  hexamap_n_row = node["n_row"].asInt();
  hexamap_n_col = node["n_col"].asInt();
  hexamap_hexa_r = node["hexa_r"].asInt();
  hexamap_outline_color =
      utils::Utils::stringToColor(node["outline_color"].asString());
  node = node["colors"];
  for (unsigned int i = 0; i < node.size(); ++i)
    hexamap_colors.push_back(utils::Utils::stringToColor(node[i].asString()));

  // ========  territory_tooltips ========
  node = root["territory_tooltips"];
  territory_tooltips_width = node["width"].asInt();
  territory_tooltips_height = node["height"].asInt();
  territory_tooltips_margin_x = node["margin_x"].asInt();
  territory_tooltips_margin_y = node["margin_y"].asInt();
}
