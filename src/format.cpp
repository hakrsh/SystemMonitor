#include "format.h"

#include <string>
#include <cmath>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hrs = seconds / 3600;
  int mins = (seconds % 3600) / 60;
  int sec = (seconds % 60);
  return std::to_string(hrs) + ":" + std::to_string(mins) + ":" +
         std::to_string(sec);
}
string Format::ToMb(int ram) {
  ram /= 1024;
  return std::to_string(ram);
}