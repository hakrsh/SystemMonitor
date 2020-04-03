#include "system.h"

#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
bool Compare(Process& a, Process& b) {
  return std::stoi(a.Ram()) > std::stoi(b.Ram());
  // return !(a < b);
}
vector<Process>& System::Processes() {
  for (auto pid : LinuxParser::Pids()) {
    Process p(pid);
    System::processes_.push_back(p);
  }
  std::sort(System::processes_.begin(), System::processes_.end(), Compare);
  System::processes_.erase(
      std::unique(System::processes_.begin(), System::processes_.end()),
      System::processes_.end());
  return System::processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }