#include <Windows.h>
#include <string>
#include <iostream>

std::string getClipboardText()
{
	if (!OpenClipboard(NULL)) {
		return ">> Error to open clipboard <<";
	}

	HANDLE hClipboardData = GetClipboardData(CF_TEXT);
	if (hClipboardData == nullptr) {
		CloseClipboard();
		return ">> Error to read clipboard as CF_TEXT <<";
	}

	char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
	if (pszText == nullptr) {
		CloseClipboard();
		return ">> Error to convert handler to char* <<";
	}

	std::string clipboardText{ pszText };

	GlobalUnlock(hClipboardData);
	CloseClipboard();

	return clipboardText;
}

//int main()
//{
//	std::string clipboardText = getClipboardText();
//
//	if (!clipboardText.empty()) {
//		std::cout << clipboardText << std::endl;
//	}
//	else {
//		std::cout << ">> No Text Data on Clipboard <<" << std::endl;
//	}
//
//	return EXIT_SUCCESS;
//}