#pragma once
#include <stdexcept>

class ClipboardException: public std::exception
{
public:
	ClipboardException(const char* message): std::exception(message) { }
};

