#pragma once

#define LOG_ERROR(x) Log::LogMessage(x, Log::MessageType::Error);
#define LOG_WARNING(x) Log::LogMessage(x, Log::MessageType::Warning);
#define LOG(x) Log::LogMessage(x, Log::MessageType::Info);
#define LOG_VERBOSE(x) Log::LogMessage(x, Log::MessageType::Verbose);

#include "Log.h"
#include "Event.h"
#include "Input.h"
#include "Window.h"
#include "Entity.h"
#include "File.h"