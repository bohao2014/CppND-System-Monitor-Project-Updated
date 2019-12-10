#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stoi;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, string_tmp, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> string_tmp >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() //{ return 0.0; }
{
  string line;
  string key;
  string value;
  int memTotal{0};
  int memAvailable{0};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && (!memTotal || !memAvailable)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = stoi(value);          
        } else if (key == "MemAvailable:") {
          memAvailable = stoi(value);
        }        
      }
    }
  }
  return memTotal == 0? 0 : 1-float(memAvailable)/float(memTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()// { return 0; }
{
  	string uptimeStr;
  	string line;
  	std::ifstream stream(kProcDirectory + kUptimeFilename);
  	if (stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream linestream(line);
    	linestream >> uptimeStr;
  	}
  	long uptime = std::stol(uptimeStr);
  	return uptime;
}
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) //{ return 0; }
{
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  string line;
  string value;
  long activeJiff = 0;
  int count = 0;
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value && count < 18) {
      ++ count;
      if (count >= 14 && count <= 17) {
        activeJiff += std::stol(value);
      } 
    }
  }
  return activeJiff;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), (line.begin()+13 < line.end()) ? line.begin()+13 : line.end(), ' ', '_');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return stoi(value);
        }
      }
    }
  }
  return 0;
}
  
// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) //{ return string(); }
{
  //string ret;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) //{ return string(); }
{
  string ret;
  string line;
  string key;
  string value;
  int ramInt = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && ramInt == 0) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          std::replace(value.begin(), value.end(), '_', ' ');
          ramInt = stoi(value);
          break;
        }
      }
    }
  }
  ret = to_string((ramInt+512)/1024);
  return ret;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) //{ return string(); }
{
  string line;
  string key;
  string uid;
  bool isUidFound = false;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && isUidFound == false) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "Uid:") {          
          linestream >> uid;
          isUidFound = true;
          break;
        }
      }
    }
  }
  
  string username, right, value;
  bool isUsernameFound = false;
  
  std::ifstream filestream2(kPasswordPath);
  if (filestream2.is_open()) {
    while (std::getline(filestream2, line) && isUsernameFound == false) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> right >> value) {
        if (value == uid) {          
          isUsernameFound = true;
          break;
        }
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) //{ return 0; }
{
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  string line;
  string value;
  long int ret = 0;
  int count = 0;
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      ++ count;
      if (count == 22) {
        ret = stol(value)/sysconf(_SC_CLK_TCK);
        break;
      }
    }
  }
  return ret;
}