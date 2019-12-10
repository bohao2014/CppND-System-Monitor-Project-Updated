#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <fstream>
#include <string>

class Processor {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float cpuUtil;
};

#endif