#pragma once

#include <cstdint> // uintx_t
#include <string>
#include <sys/types.h> // pid_t
#include <vector>

struct ProcessInfo {
  pid_t pid = 0;                // Process ID
  pid_t ppid = 0;               // Parent Process ID
  uint64_t vm_size = 0;         // Virtual memory size in KB
  uint64_t vm_rss = 0;          // Resident set size (physical memory) in KB
  std::string name = "unknown"; // Executable/Process name
};

std::vector<ProcessInfo> getProcesses();
