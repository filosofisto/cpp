#include "ClipboardViewer.h"

void ClipboardViewer::onClipboardUpdate()
{
    if (OpenClipboard(nullptr)) {
        HANDLE hClipboardData = GetClipboardData(CF_TEXT);
        if (hClipboardData != nullptr) {
            char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
            if (pszText != nullptr) {
                adjustStackIfLimitAchieved();
                addOnHistory(std::string{ pszText });
                showHistory();
            }

            GlobalUnlock(hClipboardData);
        }
        CloseClipboard();
    }
}

void ClipboardViewer::handleHotkey(int hotkeyId)
{
    if (hotkeyId > stack.size()) return;

    setClipboardText(stack[hotkeyId - 1]);
}

void ClipboardViewer::showHistory() const
{
    system("cls");
    unsigned int index = 0;

    std::cout << "------------------------------| Clipboard History |------------------------------\n";
    std::cout << "Ctrl+Alt+1 ... Ctrl+Alt+9: Copy items from history to clipboard\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    for (auto& str : stack) {
        index++;
        std::cout << "[" << index << "]:\n";
        std::cout << str << "\n";
        std::cout << "---------------------------------------------------------------------------------\n";
    }
}

void ClipboardViewer::adjustStackIfLimitAchieved()
{
    while (stack.size() >= LIMIT) {
        stack.pop_back();
    }
}

void ClipboardViewer::addOnHistory(const std::string& text)
{
    stack.insert(stack.begin(), text);
}

void ClipboardViewer::setClipboardText(const std::string& text) const
{
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();

        // Allocate global memory for the string
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);

        if (hClipboardData != nullptr) {
            // Lock the memory and copy the string
            char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
            if (pszText != nullptr) {
                strcpy_s(pszText, text.size() + 1, text.c_str());
                GlobalUnlock(hClipboardData);

                // Set clipboard data format (CF_TEXT)
                SetClipboardData(CF_TEXT, hClipboardData);
            }
            else {
                std::cerr << "Error locking memory for clipboard text." << std::endl;
            }
        }
        else {
            std::cerr << "Error allocating memory for clipboard text." << std::endl;
        }

        CloseClipboard();
    }
    else {
        std::cerr << "Error opening the clipboard." << std::endl;
    }
}
