#include <iostream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "system.h"

int main() {
  // Process a(1);
  // System sys;
  // // std::cout << "a ram: " << std::stoi(a.Ram()) << "\n";
  // for (auto p : sys.Processes()) {
  //   // std::cout << std::stoi(p.Ram()) << " ";
  //   // std::cout << (std::stoi(p.Ram()) < std::stoi(a.Ram())) << "\n";
  //   if(p < a) std::cout << "yupkiipp" << "\n";
  // }

  std::cout << LinuxParser::UpTime(3347) << "\n";
}