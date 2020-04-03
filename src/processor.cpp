#include "processor.h"

#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<float> values;
  for (auto &i : LinuxParser::CpuUtilization()) values.push_back(stof(i));
  // float user, nice, sys, idle, iowait, irq, softirq, guest, guest_nice;
  // float sys;
  // user = cpu[0];
  // nice = cpu[1];
  // sys = cpu[2];
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

  // return sys / LinuxParser::Jiffies();
double user = values[0];
  double nice = values[1];
  double system = values[2];
  double idle = values[3];
  double iowait = values[4];
  double irq = values[5];
  double softirq = values[6];
  double steal = values[7];

  double PrevIdle = previdle + previowait;
  double Idle = idle + iowait;

  double PrevNonIdle =
      prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
  double NonIdle = user + nice + system + irq + softirq + steal;

  double PrevTotal = PrevIdle + PrevNonIdle;
  double Total = Idle + NonIdle;

  double totald = Total - PrevTotal;

  double idled = Idle - PrevIdle;

  double CPU_Percentage = (totald - idled) / totald;
  return CPU_Percentage;

}