#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

class ClipboardViewer
{
public:
	explicit ClipboardViewer();
	virtual ~ClipboardViewer() = default;

	void onClipboardUpdate();
	void handleHotkey(int hotkeyId);

private:
	const unsigned int LIMIT = 9;

	void showHistory() const;
	void adjustStackIfLimitAchieved();
	void addOnHistory(const std::string& text);
	void setClipboardText(const std::string& text) const;

	std::vector<std::string> stack;
};

