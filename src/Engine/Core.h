#pragma once

#ifdef BUILD_DLL
    #define DLL_API __declspec(dllexport)
#else
    #define DLL_API __declspec(dllimport)
#endif

#ifdef _DEBUG
    #define LOG_ERROR(x) Log::LogMessage(x, Log::MessageType::Error);
    #define LOG_WARNING(x) Log::LogMessage(x, Log::MessageType::Warning);
    #define LOG(x) Log::LogMessage(x, Log::MessageType::Info);
    #define LOG_VERBOSE(x) Log::LogMessage(x, Log::MessageType::Verbose);
#else
    #define LOG_ERROR(x)
    #define LOG_WARNING(x)
    #define LOG(x)
    #define LOG_VERBOSE(x)
#endif

#include <SDL3/SDL.h>
#include "Log.h"
#include "Event.h"
#include "Input.h"
#include "Window.h"
#include "Entity.h"
#include "File.h"