#include "Log.h"


void Log::LogMessage(const std::string msg, MessageType msgType, std::source_location location)
{
	ProcessMsg(msg, msgType, location);
}

void Log::LogMessage(const void* msg, MessageType msgType, std::source_location location)
{
	std::stringstream ss;
	ss << msg;
	std::string sMsg = ss.str();
	ProcessMsg(sMsg, msgType, location);
}

void Log::LogMessage(const char* msg, MessageType msgType, std::source_location location)
{
	std::string sMsg(msg);
	ProcessMsg(sMsg, msgType, location);
}

void Log::LogMessage(const int msg, MessageType msgType, std::source_location location)
{
	std::string sMsg = std::to_string(msg);
	ProcessMsg(sMsg, msgType, location);
}

void Log::LogMessage(const float msg, MessageType msgType, std::source_location location)
{
	std::string sMsg = std::to_string(msg);
	ProcessMsg(sMsg, msgType, location);
}

void Log::LogMessage(const double msg, MessageType msgType, std::source_location location)
{
	std::string sMsg = std::to_string(msg);
	ProcessMsg(sMsg, msgType, location);
}


void Log::ProcessMsg(std::string msg, MessageType msgType, std::source_location location)
{
	switch (msgType)
	{
	case MessageType::Error:
		DebugError(msg, location);
		break;
	case MessageType::Warning:
		DebugWarning(msg, location);
		break;
	case MessageType::Info:
		DebugInfo(msg, location);
		break;
	case MessageType::Verbose:
		DebugVerbose(msg, location);
	}
}

void Log::DebugError(std::string msg, std::source_location location)
{
	//change text color to red: 4
	SetTextColor(4);
	std::cout << "[" << Time::GetLocalTime() << "] [" << location.function_name() << ":(" << location.line() << ":" << location.column()
		<< ")" << "] [" << msg << "]" << std::endl;
	//change text color back to white: 7
	SetTextColor(7);
}
void Log::DebugWarning(std::string msg, std::source_location location)
{
	//change text color to yellow: 6
	SetTextColor(6);
	std::cout << "[" << Time::GetLocalTime() << "] [" << location.function_name() << ":(" << location.line() << ":" << location.column()
		<< ")" << "] [" << msg << "]" << std::endl;
	//change text color back to white: 7
	SetTextColor(7);
}
void Log::DebugInfo(std::string msg, std::source_location location)
{
	std::cout << "[" << Time::GetLocalTime() << "] [" << location.function_name() << ":(" << location.line() << ":" << location.column()
		<< ")" << "] [" << msg << "]" << std::endl;
}
void Log::DebugVerbose(std::string msg, std::source_location location)
{
	//change text color to light blue: 3
	SetTextColor(3);
	std::cout << "[" << Time::GetLocalTime() << "] [" << location.function_name() << ":(" << location.line() << ":" << location.column()
		<< ")" << "] [" << msg << "]" << std::endl;
	//change text color back to white: 7
	SetTextColor(7);
}

void SetTextColor(unsigned short color)
{

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}