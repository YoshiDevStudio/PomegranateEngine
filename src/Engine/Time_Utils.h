#pragma once

#include <time.h>
#include <chrono>
#include <string>

class Time
{
public:
	static std::string GetLocalTime();
	static std::string GetLocalTimeMS();
	
	static float deltaTime;
	static float timeElapsed;
};