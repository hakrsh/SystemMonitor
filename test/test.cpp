#include <iostream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "system.h"

int main() {
  // Process a(1);
  System sys;
  // // std::cout << "a ram: " << std::stoi(a.Ram()) << "\n";
  std::cout << sys.Processes().size()<<"\n";
  // for (auto &i : sys.Processes()) std::cout << i.Pid() << "\n";
  std::cout << LinuxParser::UpTime(3438) << "\n";
}