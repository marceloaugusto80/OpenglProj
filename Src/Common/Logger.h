#pragma once

namespace Logger
{

	void Print(const char* format, ...);

}

#define PRINT(MESSAGE) Logger::Print("%s:%i: %s", __FILE__, __LINE__, MESSAGE)
#define PRINTF(FORMAT, ARGS) Logger::Print(FORMAT, ARGS)
