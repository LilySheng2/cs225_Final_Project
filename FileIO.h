#pragma once

#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <map>
#include <vector>

/**
 * The base class for different color picking algorithms
 * All color picking classes inherit from this class
 */
namespace FileIO {
  /**
   * Read from the file
   */
  std::map<std::string, std::vector<std::string>>readFromFile(std::string file);
  
};
