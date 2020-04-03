#include "processor.h"

#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<float> cpu;
  for (auto &i : LinuxParser::CpuUtilization()) cpu.push_back(stof(i));
  // float user, nice, sys, idle, iowait, irq, softirq, guest, guest_nice;
  float sys;
  // user = cpu[0];
  // nice = cpu[1];
  sys = cpu[2];
  // idle = cpu[3];
  // iowait = cpu[4];
  // irq = cpu[5];
  // softirq = cpu[6];
//   steal = cpu[7];
  // guest = cpu[8];
  // guest_nice = cpu[9];

  // float usertime = user - guest;
  // float nicetime = nice - guest_nice;
  // float idelealltime = idle + iowait;
  // float sysalltime = sys + irq + softirq;
  // float virtalltime = guest + guest_nice;

  // return usertime + nicetime + idelealltime + sysalltime + virtalltime;

  return sys / LinuxParser::Jiffies();
}