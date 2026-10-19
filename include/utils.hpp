#pragma once

#include <string>
#include <string_view>

std::string getValue(const std::string &filePath, const std::string_view target,
                     const bool onlyNum);
