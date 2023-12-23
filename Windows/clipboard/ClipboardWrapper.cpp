#include "ClipboardWrapper.h"
#include "ClipBoardException.h"

const std::string ClipboardWrapper::currentText()
{
    if (!opened) throw ClipboardException("Clipboard not open");

    HANDLE hClipboardData = GetClipboardData(CF_TEXT);

    if (hClipboardData != nullptr) {
        char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
        GlobalUnlock(hClipboardData);

        if (pszText != nullptr) {    
            return std::string{ pszText };
        }
        else {
            throw ClipboardException("Error on read text type on clipboard");
        }
    }
    else {
        throw ClipboardException("No text type on clipboard");
    }
}

bool ClipboardWrapper::isText() const
{
    if (!opened) throw ClipboardException("Clipboard not open");

    HANDLE hClipboardData = GetClipboardData(CF_TEXT);

    return (hClipboardData != nullptr);
}

bool ClipboardWrapper::isOpened() const
{
    return opened;
}

void ClipboardWrapper::set(const std::string& text)
{
    if (!opened) throw ClipboardException("Clipboard not open");

    clear();

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
            throw ClipboardException("Error locking memory for clipboard text");
        }
    }
    else {
        throw ClipboardException("Error allocating memory for clipboard text.");
    }
}

void ClipboardWrapper::clear() const
{
    if (!opened) throw ClipboardException("Clipboard not open");

    EmptyClipboard();
}

bool ClipboardWrapper::open()
{
    if (opened) throw ClipboardException("Clipboard already opened");

    if (OpenClipboard(nullptr)) {
        opened = true;
    }

    return opened;
}

void ClipboardWrapper::close()
{
    if (!opened) throw ClipboardException("Clipboard not open");

    CloseClipboard();
    opened = false;
}
