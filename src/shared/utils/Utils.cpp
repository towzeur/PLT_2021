#include <boost/filesystem.hpp>
#include <iostream>

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
 *  #include <boost/filesystem.hpp>
 *
 * usage:
 *  std::string rp_font_fps =
 *    utils::Utils::resolveRelative("res/fonts/Square.ttf");
 *
 * @param target
 * @return std::string
 */

std::string Utils::resolveRelative(std::string target) {
  std::string root_dir = Utils::getRootDir();
  boost::filesystem::path path = boost::filesystem::current_path();

  // std::cout << "[DEBUG] path : " << path << std::endl;

  std::string out;

  int distance = -1;
  for (auto it = path.end(); it != path.begin(); --it, ++distance) {
    // std::cout << "[DEBUG] : " << *it << std::endl;

    if ((it->string()).compare(root_dir) == 0) {
      // std::cout << "FOUND !" << distance << std::endl;

      std::string out;
      // prepend with relative parent cd
      const std::string input = "../";
      for (int i = 0; i < distance; ++i)
        out.append(input);
      // std::cout << "out : " << out << std::endl;
      // append the target
      out.append(target);
      // return the resolved path
      return out;
    }
  }

  return std::string();
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