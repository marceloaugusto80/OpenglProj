#pragma once

class NonCopyable
{
public:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;
	NonCopyable(const NonCopyable& other) = delete;
	NonCopyable& operator=(const NonCopyable& other) = delete;
};
