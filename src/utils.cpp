#include "utils.hpp"
#include <fstream>

std::string getValue(const std::string &filePath, const std::string_view target,
                     const bool onlyNum) {
  std::ifstream file(filePath);
  if (!file.is_open())
    return "";

  std::string line;
  size_t targetLen = (target.length());
  while (std::getline(file, line)) {
    if (line.starts_with(target) && std::isspace(line[targetLen])) {
      line = line.substr(targetLen + 1);
      if (onlyNum) {
        std::string numbers;
        for (char c : line) {
          if (std::isdigit(c) || (std::isspace(c) && !numbers.empty())) {
            numbers += c;
          }
        }
        return numbers;
      }
      return line;
    }
  }
  return "";
}
