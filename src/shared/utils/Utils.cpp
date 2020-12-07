#include <iostream>
#include <unistd.h>

#include "Utils.h"

using namespace utils;

Utils::Utils() {}

/**
 * @brief find the relative path to the target
 *
 * /!\ - target must be relative to ROOT_DIR
 *     - target must be within (-r) ROOT_DIR
 *
 * dependance:
 *  #include <unistd.h> // get_current_dir_name()
 *
 * usage:
 *  std::string rp_font_fps =
 *    utils::Utils::resolveRelative("res/fonts/Square.ttf");
 *
 * @param target
 * @return std::string
 */
std::string Utils::resolveRelative(std::string target) {
  std::string out;
  std::string path = get_current_dir_name();
  std::string root_dir = Utils::getRootDir();
  // std::cout << "[DEBUG] path : " << path << std::endl;

  size_t found = path.find(root_dir);
  // std::cout << "[DEBUG] found : " << found << std::endl;
  if (found != std::string::npos) {

    std::string sub_path = path.substr(found + root_dir.size());
    // std::cout << "[DEBUG] substr : " << sub_path << std::endl;

    // assert that only 1 root_dir was present in the path
    if (sub_path.find(root_dir) != std::string::npos) {
      exit(1);
    }

    // cout how many '/' are present
    for (size_t i = 0; i < sub_path.size(); ++i) {
      if (path[i] == '/')
        out.append("../");
    }
    out.append(target);
  } else {
    exit(1);
  }
  // std::cout << "[DEBUG] resolved path : " << out << std::endl;
  return out;
}

const std::string Utils::getRootDir() { return "PLT_2021"; }

/**
 * @brief convert a color string to a sf::Color
 *
 * ie:
 *  "#4080C8"
 *  r : 40 (16) = 64
 *  g : 80 (16) = 128
 *  b : c8 (16) = 200
 *
 *  => sf:Color(r, g, b)
 *
 * @param str_color
 * @return sf::Color
 */
sf::Color Utils::stringToColor(std::string str_color) {
  sf::Color out(0, 0, 0);
  if (str_color.size() == 7) {
    unsigned int x = std::stoul(str_color.substr(1), nullptr, 16);
    out.b = (sf::Uint8)(x)&0xFF;
    out.g = (sf::Uint8)(x >> 8) & 0xFF;
    out.r = (sf::Uint8)(x >> 16) & 0xFF;
  }
  return out;
}