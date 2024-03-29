
#include <windows.h>
#include <iostream>
#include "ClipboardViewer.h"

ClipboardViewer viewer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        if (!AddClipboardFormatListener(hwnd)) {
            std::cerr << "Error adding clipboard format listener. Error code: " << GetLastError() << std::endl;
            return -1;
        }

        viewer.registerHotKeys(hwnd);

        break;

    case WM_DESTROY:
        RemoveClipboardFormatListener(hwnd);

        viewer.unregisterHotKeys(hwnd);

        PostQuitMessage(0);
        break;

    case WM_HOTKEY:
        viewer.handleHotkey(static_cast<int>(wParam));
        break;

    case WM_CLIPBOARDUPDATE:
        viewer.onClipboardUpdate();

        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

int main()
{
    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"ClipboardMonitorClass";

    if (!RegisterClass(&wc)) {
        std::cerr << "Error registering window class." << std::endl;
        return 1;
    }

    // Create a window
    HWND hwnd = CreateWindowEx(0, L"ClipboardMonitorClass", L"Clipboard Monitor Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

    if (hwnd == nullptr) {
        std::cerr << "Error creating window. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


