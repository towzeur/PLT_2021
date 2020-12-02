#include "SfmlUtils.h"

#include <iostream>
//#include <unistd.h>

using namespace utils;

SfmlUtils::SfmlUtils() {}

/**
 * @brief convert a color string to a sf::Color
 *
 * ie:
 *  "#4080C8"
 *  r : 40 (16) = 64
 *  g : 80 (16) = 128
 *  b : c8 (16) = 200
 *
 *  return sf:Color(r, g, b)
 *
 * @param str_color
 * @return sf::Color
 */
sf::Color SfmlUtils::string_to_color(std::string str_color) {
  sf::Color out(0, 0, 0);
  if (str_color.size() == 7) {
    unsigned int x = std::stoul(str_color.substr(1), nullptr, 16);
    out.b = (sf::Uint8)(x)&0xFF;
    out.g = (sf::Uint8)(x >> 8) & 0xFF;
    out.r = (sf::Uint8)(x >> 16) & 0xFF;
  }
  return out;
}
