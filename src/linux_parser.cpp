#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::string line, uptime;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::stringstream linestream(line);
    linestream >> uptime;
    return stol(uptime);
  }
  return 0;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string line, t1, t2;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
    while (std::getline(stream, line)) {
      std::stringstream linestream(line);
      linestream >> t1 >> t2;
      if (t1 == "processes") return stoi(t2);
    }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, t1, t2;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
    while (std::getline(stream, line)) {
      std::stringstream linestream(line);
      linestream >> t1 >> t2;
      if (t1 == "procs_running") return stoi(t2);
    }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  std::string line;
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  std::string line, t1, t2;
  if (stream.is_open())
    while (std::getline(stream, line)) {
      std::stringstream linestream(line);
      linestream >> t1 >> t2;
      if (t1 == "VmSize:") return t2;
    }
  return "0";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  std::string line, t1, t2;
  if (stream.is_open())
    while (std::getline(stream, line)) {
      std::stringstream linestream(line);
      linestream >> t1 >> t2;
      if (t1 == "Uid:") return t2;
    }
  return "";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  std::ifstream stream(kPasswordPath);
  std::string line;
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::stringstream linestream(line);
      if (line.find(std::to_string(pid)) != std::string::npos)
        return line.substr(0, line.find(":"));
    }
  }
  return "none";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long up;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.ignore(22) >> up) {
    return up / sysconf(_SC_CLK_TCK);
  }
  return 0;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::string tot, free, _;
    stream >> _ >> tot >> _;
    stream >> _ >> free;
    float mTot, mFree;
    mTot = std::stof(tot);
    mFree = std::stof(free);
    return (mTot - mFree) / mTot;
  }
  return 0.0;
}
// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::string _;
    vector<std::string> time;
    stream >> _;
    for (int i = 0; i < 10; i++) {
      stream >> _;
      time.push_back(_);
    }
    return time;
  }
  return vector<std::string>{};
}
std::vector<std::string> LinuxParser::ReadStat(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::string token;
  std::vector<std::string> stat{};
  if (stream.is_open()) {
    while (stream >> token) stat.push_back(token);
  }
  return stat;
}
float LinuxParser::CpuUtilization(int pid) {
  float utime, cutime, stime, cstime, starttime, total_time, seconds,
      cpu_usage = 0.0;
  auto stat = LinuxParser::ReadStat(pid);
  utime = std::stof(stat[13]);
  stime = std::stof(stat[14]);
  cutime = std::stof(stat[15]);
  cstime = std::stof(stat[16]);
  starttime = std::stof(stat[21]);

  total_time = utime + stime + cutime + cstime;
  seconds = LinuxParser::UpTime() - starttime / sysconf(_SC_CLK_TCK);
  cpu_usage = 100 * ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
  return cpu_usage;
}
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long tot = 0;
  for (auto i : LinuxParser::CpuUtilization()) tot += std::stol(i);
  return tot;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  auto cpu = LinuxParser::ReadStat(pid);
  long tot = 0;
  for (int i = 13; i < 18; i++) tot += std::stol(cpu[i]);
  return tot;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }