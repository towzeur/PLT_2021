#include "RenderConfig.h"

using namespace render;

/*
public:
int entity_width;
int entity_height;
std::string rpath_background;
std::string rpath_font_fps;
std::string rpath_tileset;
*/

public:
RenderConfig::RenderConfig() {}

void RenderConfig::load(std::string skin_name) {

  //
  std::ostringstream stream;
  stream << "res/texture/";
  stream << skin_name;
  stream << ".json";
  std::string rpath_skin = utils::PathUtils::resolveRelative(stream.str());

  // parse json
  Json::Value root;
  std::ifstream ifs;
  ifs.open(rpath_skin);
  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    return;
  }
  std::cout << root << std::endl;

  // get relatives paths
  std::string rpath_background =
      utils::PathUtils::resolveRelative(root["background_path"].asString());
  std::string rpath_font_fps =
      utils::PathUtils::resolveRelative(root["fps_path"].asString());
  std::string rpath_tileset =
      utils::PathUtils::resolveRelative("res/texture/skins/medieval.png");

  const std::string name = root["Name"].asString();
  const int age = root["Age"].asInt();
  bool bg_enable = root["background_enable"].asBool();
  sf::Color bg_color =
      utils::SfmlUtils::string_to_color(root["background_color"].asString());
}
