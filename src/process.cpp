#include "process.h"

#include <unistd.h>

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return Process::pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return Process::cpu_; }

// TODO: Return the command that generated this process
string Process::Command() {
  std::string cmd = Process ::command_;
  size_t maxsize = 50;
  if (cmd.size() > maxsize) {
    cmd.resize(maxsize - 3);
    cmd += "...";
  }
  return cmd;
}

// TODO: Return this process's memory utilization
string Process::Ram() { return Process::ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return Process::user_; }

// TODO: Return the age of this process (in seconds)
long Process::UpTime() { return Process::uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) {
  auto r1 = std::stoi(Process::Ram());
  auto r2 = std::stoi(a.Ram());
  // std::cout << r1 << " " << r2 //works
  return r1 < r2;  // but return fails - terminate called after throwing an instance of
                   // 'std::invalid_argument' what(): stoi Aborted
}
