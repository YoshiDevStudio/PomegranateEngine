#pragma once

#include <Windows.h>
#include <source_location>
#include <iostream>
#include <sstream>
#include <string>

#include "Time_Utils.h"
#include "DLL_Build.h"

//Can print primitive types, strings, and memory addresses
class DLL_API Log
{
public:
    enum MessageType
    {
        Error,
        Warning,
        Info,
        Verbose
    };

    static void LogMessage(const std::string msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());
    static void LogMessage(const void* msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());
    static void LogMessage(const char* msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());
    static void LogMessage(const int msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());
    static void LogMessage(const float msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());
    static void LogMessage(const double msg, MessageType msgType = MessageType::Info, std::source_location location = std::source_location::current());

private:
    static void ProcessMsg(std::string msg, MessageType msgType, std::source_location location);
	static void DebugError(std::string msg, std::source_location location);
	static void DebugWarning(std::string msg, std::source_location location);
	static void DebugInfo(std::string msg, std::source_location location);
	static void DebugVerbose(std::string msg, std::source_location location);
};

void SetTextColor(unsigned short color);