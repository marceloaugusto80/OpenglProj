#include "stdafx.h"
#include "Logger.h"


void Logger::Print(const char * format, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, format);
		_vsnprintf_s(buffer, sizeof(buffer), format, args);
	va_end(args);

#ifdef _WIN32
	OutputDebugStringA(buffer);
	OutputDebugStringA("\n");
#else
	std::cout << buffer << std::endl;
#endif

}
