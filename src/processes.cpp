#include "processes.hpp"
#include "utils.hpp"
#include <algorithm>
#include <filesystem>

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

      pid_t ppid = std::stoi(getValue(statusPath, "PPid:", true));
      proc.ppid = ppid;

      std::string vm_rss = getValue(statusPath, "VmRSS:", true);
      proc.vm_rss = std::stoll(vm_rss);

      std::string vm_size = getValue(statusPath, "VmSize:", true);
      proc.vm_size = std::stoll(vm_size);

      std::string name = getValue(statusPath, "Name:", false);
      proc.name = name;

      processList.push_back(proc);
    } catch (...) {
      continue;
    }
  }

  return processList;
};
