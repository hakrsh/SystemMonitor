#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "format.h"
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                   // TODO: See src/process.cpp
  std::string User();          // TODO: See src/process.cpp
  std::string Command();       // TODO: See src/process.cpp
  float CpuUtilization();      // TODO: See src/process.cpp
  std::string Ram();           // TODO: See src/process.cpp
  long UpTime();               // TODO: See src/process.cpp
  bool operator<(Process& a);  // TODO: See src/process.cpp
  bool operator==(Process& a);
  Process(int pid) {
    pid_ = pid;
    user_ = LinuxParser::User(std::stoi(LinuxParser::Uid(pid)));
    command_ = LinuxParser::Command(pid);
    ram_ = Format::ToMb(std::stoi(LinuxParser::Ram(pid)));
    cpu_ = LinuxParser::CpuUtilization(pid);
    uptime_ = LinuxParser::UpTime(pid);
  }
  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user_, command_, ram_;
  float cpu_;
  long uptime_;
};

#endif