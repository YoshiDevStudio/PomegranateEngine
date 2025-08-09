#include "Time_Utils.h"

float Time::deltaTime;
float Time::timeElapsed;

//Gets hour, minute, and seconds
std::string Time::GetLocalTime()
{
	time_t currentTime = time(NULL);
	tm* tmLocal = localtime(&currentTime);
	if (tmLocal->tm_hour > 12)
		tmLocal->tm_hour = tmLocal->tm_hour - 12;
	std::string s = std::to_string(tmLocal->tm_hour) + ":" + std::to_string(tmLocal->tm_min) + ":" + std::to_string(tmLocal->tm_sec);
	return s;
}

//Gets amount of milliseconds in current Time
std::string Time::GetLocalTimeMS()
{
	auto now = std::chrono::system_clock::now();
    // Calculate the duration from the epoch to the current time point
    auto duration_since_epoch = now.time_since_epoch();
    // Cast the duration to milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch);
    long long milliseconds_count = milliseconds.count();
    //Gets only the milliseconds part of the current second:
    long long current_second_milliseconds = milliseconds_count % 1000;

	return std::to_string(current_second_milliseconds);
}