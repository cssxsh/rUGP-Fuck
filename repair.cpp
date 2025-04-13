#include "repair.h"
#include "proxy.h"
#include <detours/detours.h>

static HMODULE winmm = nullptr;

static FARPROC ReadProfileString = nullptr;

static void WINAPI AttachHook();

static void WINAPI DetachHook();

static LPSTR& __fastcall HookReadProfileString(CCommandLineInfo*, DWORD, LPSTR&, LPCSTR, LPCSTR);

BOOL APIENTRY DllMain(HINSTANCE /*hInstance*/, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
            TCHAR path[MAX_PATH] = {};
            GetSystemDirectory(path, sizeof(path));
            lstrcat(path, TEXT("\\winmm.dll"));
            winmm = LoadLibrary(path);
        }
        if (winmm != nullptr) WinmmProxy(winmm);
        AttachHook();
        break;
    case DLL_PROCESS_DETACH:
        DetachHook();
        if (winmm == nullptr) FreeLibrary(winmm);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }

    return TRUE;
}

void WINAPI AttachHook()
{
    const auto GMfc = GetModuleHandleA("GMfc");
    if (GMfc == nullptr) return;
    // public: class CString __thiscall CCommandLineInfoSg::ReadProfileString(LPCSTR, LPCSTR)
    ReadProfileString = GetProcAddress(GMfc, "?ReadProfileString@CCommandLineInfoSg@@QAE?AVCString@@PBD0@Z");
    if (ReadProfileString == nullptr) return;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&reinterpret_cast<PVOID&>(ReadProfileString), HookReadProfileString);
    DetourTransactionCommit();
}

void WINAPI DetachHook()
{
    if (ReadProfileString == nullptr) return;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&reinterpret_cast<PVOID&>(ReadProfileString), HookReadProfileString);
    DetourTransactionCommit();
}

LPSTR& __fastcall HookReadProfileString(
    CCommandLineInfo* ecx,
    const DWORD edx,
    LPSTR& result,
    const LPCSTR key,
    const LPCSTR value)
{
    reinterpret_cast<decltype(HookReadProfileString)*>(ReadProfileString)(ecx, edx, result, key, value);
    if (strcmp(key, "UGPAPP") != 0) return result;
    auto software = static_cast<HKEY>(nullptr);
    auto status = ERROR_SUCCESS;
    status = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\relic UGP Applications", 0, KEY_READ, &software);
    if (status != ERROR_SUCCESS) return result;
    auto temp = static_cast<HKEY>(nullptr);
    status = RegOpenKeyExA(software, result, 0, KEY_READ, &temp);
    if (status == ERROR_SUCCESS) return RegCloseKey(temp), RegCloseKey(software), result;
    const auto unicode = Unicode(result, CP_SHIFT_JIS);
    status = RegOpenKeyExW(software, unicode, 0, KEY_READ, &temp);
    if (status == ERROR_SUCCESS)
    {
        RegCloseKey(temp);
        const auto ansi = Ansi(unicode, CP_ACP);
        strcpy(result, ansi);
        free(ansi);
    }
    free(unicode);
    RegCloseKey(software);
    return result;
}
