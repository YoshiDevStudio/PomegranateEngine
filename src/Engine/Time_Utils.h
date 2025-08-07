#pragma once

#include <time.h>
#include <string>

class Time
{
public:
	static std::string GetLocalTime();
	static float deltaTime;
};