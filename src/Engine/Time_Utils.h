#pragma once

#include <time.h>
#include <chrono>
#include <string>

#include "DLL_Build.h"

class DLL_API Time
{
public:
	static std::string GetLocalTime();
	static std::string GetLocalTimeMS();
	
	static float deltaTime;
	static float timeElapsed;
};