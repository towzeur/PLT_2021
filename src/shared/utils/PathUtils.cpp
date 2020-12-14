#include <iostream>
#include <unistd.h>

#include <boost/filesystem.hpp>

#include "PathUtils.h"

using namespace utils;
using namespace boost::filesystem;


PathUtils::PathUtils() {}

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
 *  std::string rp_font_fps = resolve("res/fonts/Square.ttf");
 *
 * @param target
 * @return std::string
 */
std::string PathUtils::resolveRelative(std::string target) {
  /*std::string out;
  std::string path = boost::filesystem::path().string();
  std::cout << "[DEBUG] path : " << path << std::endl;

  size_t found = path.find(ROOT_DIR);
  std::cout << "[DEBUG] found : " << found << std::endl;
  if (found != std::string::npos) {

    std::string sub_path = path.substr(found + ROOT_DIR.size());
    std::cout << "[DEBUG] substr : " << sub_path << std::endl;

    // assert that only 1 ROOT_DIR was present in the path
    if (sub_path.find(ROOT_DIR) != std::string::npos) {
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
  std::cout << "[DEBUG] resolved path : " << out << std::endl;
  return out;*/
}