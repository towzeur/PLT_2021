#include <iostream>
#include <boost/filesystem.hpp>

#include "PathUtils.h"

using namespace utils;


PathUtils::PathUtils() {}

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
 *  std::string rp_font_fps = resolve("res/fonts/Square.ttf");
 *
 * @param target
 * @return std::string
 */
std::string PathUtils::resolveRelative(std::string target) {
  boost::filesystem::path path = boost::filesystem::current_path();
  //std::cout << "[DEBUG] path : " << path << std::endl;

  std::string out;

  int distance = -1;
  for (auto it=path.end(); it != path.begin(); --it, ++distance){
    //std::cout << "[DEBUG] : " << *it << std::endl;

    if ((it->string()).compare("PLT_2021") == 0){
      //std::cout << "FOUND !" << distance << std::endl;

      std::string out;
      // prepend with relative parent cd
      const std::string input = "../";
      for (int i = 0; i < distance; ++i) 
        out.append(input);
      //std::cout << "out : " << out << std::endl;
      // append the target
      out.append(target);
      // return the resolved path
      return out;
    }
  }

  return std::string();
}