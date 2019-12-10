#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
//string Format::ElapsedTime(long seconds[[maybe_unused]]) { return string(); }
string Format::ElapsedTime(long seconds)
{
  	string hour, min, sec;
	hour = to_string(seconds/3600);
	min = to_string(seconds%3600/60);
	sec = to_string(seconds%60);
	if(hour.size() == 1)
		hour = "0" + hour;
	if(min.size() == 1)
		min = "0" + min;
	if(sec.size() == 1)
		sec = "0" + sec;
	return hour + ":" + min + ":" + sec;
}