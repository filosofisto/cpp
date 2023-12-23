#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "ClipboardWrapper.h"
#include "ClipboardException.h"

typedef struct data
{
	bool valid;
	std::string content;
} ClipboardItem;

class ClipboardViewer
{
public:
	explicit ClipboardViewer();
	virtual ~ClipboardViewer() = default;

	void onClipboardUpdate();
	void handleHotkey(int hotkeyId);

private:
	const unsigned int LIMIT = 9;
	const std::string NON_VALID_CONTENT = "*** CURRENT CLIPBOARD CONTENT IS NOT A TEXT ***";

	void showHistory() const;
	void adjustStackIfLimitAchieved();
	void addOnHistory(const std::string& text);
	void setClipboardText(const std::string& text);
	void replaceCurrentClipboardWithInvalid();
	void replaceCurrentClipboardWith(const std::string& text);
	bool isCurrentClipboardValid() const;
	void clearHistory();

	std::vector<ClipboardItem> stack;
	ClipboardWrapper clipboard;
};

