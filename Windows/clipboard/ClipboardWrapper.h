#pragma once
#include <string>
#include <Windows.h>

class ClipboardWrapper
{
public:
	ClipboardWrapper() = default;
	virtual ~ClipboardWrapper() = default;

	bool open();
	void close();
	const std::string currentText();
	bool isText() const;
	bool isOpened() const;
	void set(const std::string& text);
	void clear() const;

private:
	bool opened;
};

