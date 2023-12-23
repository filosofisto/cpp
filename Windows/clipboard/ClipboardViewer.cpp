#include "ClipboardViewer.h"

ClipboardViewer::ClipboardViewer()
{
    onClipboardUpdate();
}

void ClipboardViewer::onClipboardUpdate()
{
    try {
         clipboard.open();

        if (clipboard.isText()) {
            const std::string text = clipboard.currentText();
            
            if (isCurrentClipboardValid()) {
                // Normal case: Check if need to adjust the history buffer and add it on the history
                adjustStackIfLimitAchieved();
                addOnHistory(text);
               
            }
            else {
                // Special case: If current clipboard data is not text then simply replace it by the new text
                 replaceCurrentClipboardWith(text);
            }
        }
        else {
            // No Text added to clipboard:
            //      If current clipboard is TEXT:
            //          add on clipboard the NO_TEXT item to history
            //      else (* It means already exist a Non Text on clipboard, so to avoid polute the history with no text data just replace the current one with NO_TEXT *)
            if (isCurrentClipboardValid()) {
                adjustStackIfLimitAchieved();
                addOnHistory(std::string{ });
            }

            replaceCurrentClipboardWithInvalid();
        }

        showHistory();
    }
    catch (const ClipboardException& e) {
        std::cerr << "Error on process clipboard update: " << e.what() << "\n";
    }
        
    clipboard.close();
}

void ClipboardViewer::handleHotkey(int hotkeyId)
{
    // Ctrl+Alt+0 clear the history cache
    if (hotkeyId == 0) {
        clearHistory();
        return;
    }

    // Ctrl+Alt+N where there is no N position in the cache must be ignored
    if (hotkeyId > stack.size()) return;

    // Set the position in the history the current clipboard
    setClipboardText(stack[hotkeyId - 1].content);
}

void ClipboardViewer::registerHotKeys(HWND hwnd)
{
    for (int i = 0; i <= 9; ++i) {
        if (i == 1) continue; // Ignore Ctrl+Alt+1
        if (!RegisterHotKey(hwnd, i, MOD_ALT | MOD_CONTROL, '0' + i)) {
            throw ClipboardException("Error registering hotkey");
        }
    }
}

void ClipboardViewer::unregisterHotKeys(HWND hwnd)
{
    // Unregister hotkeys
    for (int i = 0; i <= 9; ++i) {
        if (i == 1) continue; // Ignore Ctrl+Alt+1
        UnregisterHotKey(hwnd, i);
    }
}

void ClipboardViewer::showHistory() const
{
    system("cls");
    unsigned int index = 0;

    std::cout << "------------------------------| Clipboard History |------------------------------\n";
    std::cout << "Ctrl+Alt+2 ... Ctrl+Alt+9: Copy items from history to clipboard\n";
    std::cout << "Ctrl+Alt+0     Clear history (reset to the current clipboard content\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    for (auto& str : stack) {
        index++;
        std::cout << "[" << index << "]:" << (index == 1 ? " Current clipboard content" : "") << "\n";
        std::cout << str.content << "\n";
        std::cout << "---------------------------------------------------------------------------------\n";
    }
}

void ClipboardViewer::adjustStackIfLimitAchieved()
{
    if (!isCurrentClipboardValid()) return;

    while (stack.size() >= LIMIT) {
        stack.pop_back();
    }
}

void ClipboardViewer::addOnHistory(const std::string& text)
{
    stack.insert(stack.begin(), ClipboardItem{true, text});
}

void ClipboardViewer::setClipboardText(const std::string& text)
{
    try {
        clipboard.open();
        clipboard.set(text);
    }
    catch (const ClipboardException& e) {
        std::cerr << "Error on try to set text on clipboard: " << e.what() << "\n";
    }

    clipboard.close();
}

void ClipboardViewer::replaceCurrentClipboardWithInvalid()
{
    stack[0] = ClipboardItem{ false, NON_VALID_CONTENT };
}

void ClipboardViewer::replaceCurrentClipboardWith(const std::string& text)
{
    if (!stack.empty()) {
        stack[0] = ClipboardItem{ true, text };
    }
    else {
        addOnHistory(text);
    }
}

bool ClipboardViewer::isCurrentClipboardValid() const
{
    return !stack.empty() && stack[0].valid;
}

void ClipboardViewer::clearHistory()
{
    stack.clear();
    onClipboardUpdate();
}
