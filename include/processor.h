#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  int previdle	;
  int previowait;
  int prevuser;
  int prevnice;
  int prevsystem;
  int previrq;
  int prevsoftirq;
  int prevsteal;
};

#endif