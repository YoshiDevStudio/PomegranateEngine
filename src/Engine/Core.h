#pragma once

#ifdef _DEBUG
    #define LOG_ERROR(x) Log::LogMessage(x, Log::MessageType::Error);
    #define LOG_WARNING(x) Log::LogMessage(x, Log::MessageType::Warning);
    #define LOG(x) Log::LogMessage(x, Log::MessageType::Info);
    #define LOG_VERBOSE(x) Log::LogMessage(x, Log::MessageType::Verbose);
    #include "Log.h"
#else
    #define LOG_ERROR(x)
    #define LOG_WARNING(x)
    #define LOG(x)
    #define LOG_VERBOSE(x)
#endif

#include "DLL_Build.h"

#include <SDL3/SDL.h>
#include "Time_Utils.h"
#include "Event.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Window.h"
#include "File.h"