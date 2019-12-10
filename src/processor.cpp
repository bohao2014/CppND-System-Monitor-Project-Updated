#include "processor.h"
#include "linux_parser.h"
#include <iostream>

using std::string;
using std::stoi;
using std::stof;

Processor::Processor()
{
  cpuUtil = Utilization();
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() //{ return 0.0; }
{
  string line;
  string key;
  //user    nice   system  idle  iowait irq   softirq  steal  guest  guest_nice
  string user, nice, sys, idle, iowait, irq, softirq, steal, guest, guest_nice;
  int count = 0;
  int idleAry[2] = {0};
  int nonIdleAry[2] = {0};
  int totalAry[2] = {0};
  while (count < 2){
  	std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  	if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
      	std::istringstream linestream(line);
      	while (linestream >> key) {
        	if (key == "cpu") {
            //linestream >> key >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
            linestream >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
            idleAry[count] = stoi(idle) + stoi(iowait);
            nonIdleAry[count] = stoi(user) + stoi(nice) + stoi(sys) + stoi(irq) + stoi(softirq) + stoi(steal);
            totalAry[count] = idleAry[count] + nonIdleAry[count];   
            count ++;
          	break;
          }
        }
      }
    }
  }

//# differentiate: actual value minus the previous one
  int totald = totalAry[1] - totalAry[0];
  int idled = idleAry[1] - idleAry[0];
  float ret = 0.0;
 
  /* 
  if (totald > 0 && count == 2)
  {
  	ret = float(totald - idled)/float(totald);
    //ret = float(nonIdleAry[1])/float(totalAry[1]);
    ret = 0.3;
  }
  */
  //return 0.1;
  if (count > 0)
  {
    ret = (stof(user) + stof(nice) + stof(sys) + stof(irq) + stof(softirq) + stof(steal))
          / (stof(idle) + stof(iowait) + stof(user) + stof(nice) + stof(sys) + stof(irq) + stof(softirq) + stof(steal));
  }
  //std::cout << count << std::endl;
  return ret;
}