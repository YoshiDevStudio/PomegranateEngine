#include "Time_Utils.h"

float Time::deltaTime;
std::string Time::GetLocalTime()
{
	time_t currentTime = time(NULL);
	tm* tmLocal = localtime(&currentTime);
	if (tmLocal->tm_hour > 12)
		tmLocal->tm_hour = tmLocal->tm_hour - 12;
	std::string s = std::to_string(tmLocal->tm_hour) + ":" + std::to_string(tmLocal->tm_min) + ":" + std::to_string(tmLocal->tm_sec);
	return s;
}