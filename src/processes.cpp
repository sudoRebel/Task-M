#include "processes.hpp"
#include "utils.hpp"
#include <algorithm>
#include <filesystem>
#include <utility> // std::move

namespace fs = std::filesystem;

std::vector<ProcessInfo> getProcesses() {
  std::vector<ProcessInfo> processList;
  fs::path dir{"/proc/"};
  if (!fs::exists(dir) || !fs::is_directory(dir)) {
    return processList;
  }

  for (fs::directory_entry dirEntry : fs::directory_iterator(dir)) {
    if (!dirEntry.is_directory())
      continue;

    std::string pidStr = dirEntry.path().filename();
    std::string statusPath = dirEntry.path() / "status";

    bool isNumber = std::all_of(pidStr.begin(), pidStr.end(), ::isdigit);
    if (!isNumber)
      continue;
    try {
      ProcessInfo proc;
      proc.pid = std::stoi(pidStr);
      proc.ppid = std::stoi(getValue(statusPath, "PPid:", true));
      proc.vm_rss = std::stoull(getValue(statusPath, "VmRSS:", true));
      proc.vm_size = std::stoull(getValue(statusPath, "VmSize:", true));
      proc.name = getValue(statusPath, "Name:", false);

      processList.push_back(std::move(proc));
    } catch (...) {
      continue;
    }
  }

  return processList;
};
