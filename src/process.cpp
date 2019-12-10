#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stol;

//constructor
Process::Process(int pidIn) : pid(pidIn) 
{
  ram = LinuxParser::Ram(pid);
  cpuUtil = CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() //{ return 0; }
{
  long activeJiff = LinuxParser::ActiveJiffies(pid);
  long upJiff = LinuxParser::UpTime(pid)*long(sysconf(_SC_CLK_TCK));
  long sysUpJiff = LinuxParser::UpTime()*long(sysconf(_SC_CLK_TCK));
  cpuUtil = float(activeJiff)/float(sysUpJiff - upJiff);
  return cpuUtil;
}

// TODO: Return the command that generated this process
string Process::Command() //{ return string(); }
{
   //commond got cut from first '-', dont know why 
  command = LinuxParser::Command(pid); 
  return command;
}

// TODO: Return this process's memory utilization
string Process::Ram() //{ return string(); }
{
  ram = LinuxParser::Ram(pid);
  return ram;
}

// TODO: Return the user (name) that generated this process
string Process::User() //{ return string(); }
{
  user = LinuxParser::User(pid);
  return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() //{ return 0; }
{
  upTime = LinuxParser::UpTime(pid);
  return upTime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const //{ return true; }
{
  return this->cpuUtil > a.cpuUtil;
  //return true;
}