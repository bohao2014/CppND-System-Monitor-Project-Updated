#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System()
{
    operatingSystem = LinuxParser::OperatingSystem();
    kernel = LinuxParser::Kernel();
  	//upTime = 123;
   	upTime = LinuxParser::UpTime();
  	totalProcesses = LinuxParser::TotalProcesses();
    runningProcesses = LinuxParser::RunningProcesses();
  	memUtil = LinuxParser::MemoryUtilization();
    cpu_ = Processor();
}

// TODO: Return the system's CPU
Processor& System::Cpu()
{
  cpu_ = Processor();
  return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() //{ return processes_; }
{
  vector<int> pidVec = LinuxParser::Pids();
  vector<Process> process;
  for (auto pid : pidVec)
  {
    process.push_back(Process(pid));
  }
  processes_ = process;
  std::sort(processes_.begin(),processes_.end());
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization()// { return 0.0; }
{
  memUtil = LinuxParser::MemoryUtilization();
  return memUtil;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { return operatingSystem; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses()
{
  runningProcesses = LinuxParser::RunningProcesses();
  return runningProcesses; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() 
{ 
  totalProcesses = LinuxParser::TotalProcesses(); 
  return totalProcesses; 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime()
{
  upTime = LinuxParser::UpTime();
  return upTime; 
}