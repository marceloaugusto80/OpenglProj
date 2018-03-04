#pragma once

#include <string>

namespace Base64
{
	std::string Encode(unsigned char const*, unsigned int len);
	std::string Decode(std::string const& s);
}

