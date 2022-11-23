#include <main.hh>
#include <internals/winapi.hh>

namespace syndicate::winapi
{
    HANDLE hMainThread;
    HHOOK hKeyboardHook;

    bool unload(size_t msDelay)
    {
        DWORD exitCode;

        if (!GetExitCodeThread(hMainThread, &exitCode))
            return false;
        else if (exitCode == STILL_ACTIVE)
            return PostThreadMessageA(GetThreadId(hMainThread), WM_QUIT, msDelay, 0);

        return false;
    }

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        LPKBDLLHOOKSTRUCT pKeyStruct{ reinterpret_cast<LPKBDLLHOOKSTRUCT>(lParam) };

        onKey(pKeyStruct->vkCode, (pKeyStruct->flags & LLKHF_UP) == 0);
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    DWORD WINAPI MainThreadProc(LPVOID lpParameter)
    {
        HINSTANCE hinstDLL{ reinterpret_cast<HINSTANCE>(lpParameter) };

        hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinstDLL, NULL);
        init();

        MSG messageBuffer;
        while (GetMessageA(&messageBuffer, NULL, NULL, NULL));
        Sleep(messageBuffer.wParam);

        deinit();
        UnhookWindowsHookEx(hKeyboardHook);

        FreeLibraryAndExitThread(hinstDLL, 0);
    }

}

using namespace syndicate::winapi;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hinstDLL);
            hMainThread = CreateThread(NULL, 0, MainThreadProc, hinstDLL, 0, NULL);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            unload();
            break;
        }
    }

    return TRUE;
}
