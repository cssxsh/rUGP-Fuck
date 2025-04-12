#include "repair.h"
#include <detours/detours.h>

static HMODULE winmm = nullptr;

static FARPROC ReadProfileString = nullptr;

static void WINAPI AttachHook();

static void WINAPI DetachHook();

static LPSTR& __fastcall HookReadProfileString(CCommandLineInfo*, DWORD, LPSTR&, LPCSTR, LPCSTR);

BOOL WINAPI DllMain(HINSTANCE /*hInstance*/, const DWORD dwReason, LPVOID /*lpReserved*/)
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
        GetCommandLineA();
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

void WINAPI WinmmProxy(const HMODULE winmm)
{
    /* Installable driver support */
    IMPLEMENT_PROXY(winmm, CloseDriver)
    IMPLEMENT_PROXY(winmm, OpenDriver)
    IMPLEMENT_PROXY(winmm, SendDriverMessage)
    IMPLEMENT_PROXY(winmm, DrvGetModuleHandle)
    IMPLEMENT_PROXY(winmm, GetDriverModuleHandle)
    IMPLEMENT_PROXY(winmm, DefDriverProc)
    /* Sound support */
    IMPLEMENT_PROXY(winmm, sndPlaySoundA)
    IMPLEMENT_PROXY(winmm, sndPlaySoundW)
    IMPLEMENT_PROXY(winmm, PlaySoundA)
    IMPLEMENT_PROXY(winmm, PlaySoundW)
    /* Waveform audio support */
    IMPLEMENT_PROXY(winmm, waveOutGetNumDevs)
    IMPLEMENT_PROXY(winmm, waveOutGetDevCapsA)
    IMPLEMENT_PROXY(winmm, waveOutGetDevCapsW)
    IMPLEMENT_PROXY(winmm, waveOutGetVolume)
    IMPLEMENT_PROXY(winmm, waveOutSetVolume)
    IMPLEMENT_PROXY(winmm, waveOutGetErrorTextA)
    IMPLEMENT_PROXY(winmm, waveOutGetErrorTextW)
    IMPLEMENT_PROXY(winmm, waveOutOpen)
    IMPLEMENT_PROXY(winmm, waveOutClose)
    IMPLEMENT_PROXY(winmm, waveOutPrepareHeader)
    IMPLEMENT_PROXY(winmm, waveOutUnprepareHeader)
    IMPLEMENT_PROXY(winmm, waveOutWrite)
    IMPLEMENT_PROXY(winmm, waveOutPause)
    IMPLEMENT_PROXY(winmm, waveOutRestart)
    IMPLEMENT_PROXY(winmm, waveOutReset)
    IMPLEMENT_PROXY(winmm, waveOutBreakLoop)
    IMPLEMENT_PROXY(winmm, waveOutGetPosition)
    IMPLEMENT_PROXY(winmm, waveOutGetPitch)
    IMPLEMENT_PROXY(winmm, waveOutSetPitch)
    IMPLEMENT_PROXY(winmm, waveOutGetPlaybackRate)
    IMPLEMENT_PROXY(winmm, waveOutSetPlaybackRate)
    IMPLEMENT_PROXY(winmm, waveOutGetID)
    IMPLEMENT_PROXY(winmm, waveOutMessage)
    IMPLEMENT_PROXY(winmm, waveInGetNumDevs)
    IMPLEMENT_PROXY(winmm, waveInGetDevCapsA)
    IMPLEMENT_PROXY(winmm, waveInGetDevCapsW)
    IMPLEMENT_PROXY(winmm, waveInGetErrorTextA)
    IMPLEMENT_PROXY(winmm, waveInGetErrorTextW)
    IMPLEMENT_PROXY(winmm, waveInOpen)
    IMPLEMENT_PROXY(winmm, waveInClose)
    IMPLEMENT_PROXY(winmm, waveInPrepareHeader)
    IMPLEMENT_PROXY(winmm, waveInUnprepareHeader)
    IMPLEMENT_PROXY(winmm, waveInAddBuffer)
    IMPLEMENT_PROXY(winmm, waveInStart)
    IMPLEMENT_PROXY(winmm, waveInStop)
    IMPLEMENT_PROXY(winmm, waveInReset)
    IMPLEMENT_PROXY(winmm, waveInGetPosition)
    IMPLEMENT_PROXY(winmm, waveInGetID)
    IMPLEMENT_PROXY(winmm, waveInMessage)
    /* MIDI audio support */
    IMPLEMENT_PROXY(winmm, midiOutGetNumDevs)
    IMPLEMENT_PROXY(winmm, midiStreamOpen)
    IMPLEMENT_PROXY(winmm, midiStreamClose)
    IMPLEMENT_PROXY(winmm, midiStreamProperty)
    IMPLEMENT_PROXY(winmm, midiStreamPosition)
    IMPLEMENT_PROXY(winmm, midiStreamOut)
    IMPLEMENT_PROXY(winmm, midiStreamPause)
    IMPLEMENT_PROXY(winmm, midiStreamRestart)
    IMPLEMENT_PROXY(winmm, midiStreamStop)
    IMPLEMENT_PROXY(winmm, midiConnect)
    IMPLEMENT_PROXY(winmm, midiDisconnect)
    IMPLEMENT_PROXY(winmm, midiOutGetDevCapsA)
    IMPLEMENT_PROXY(winmm, midiOutGetDevCapsW)
    IMPLEMENT_PROXY(winmm, midiOutGetVolume)
    IMPLEMENT_PROXY(winmm, midiOutSetVolume)
    IMPLEMENT_PROXY(winmm, midiOutGetErrorTextA)
    IMPLEMENT_PROXY(winmm, midiOutGetErrorTextW)
    IMPLEMENT_PROXY(winmm, midiOutOpen)
    IMPLEMENT_PROXY(winmm, midiOutClose)
    IMPLEMENT_PROXY(winmm, midiOutPrepareHeader)
    IMPLEMENT_PROXY(winmm, midiOutUnprepareHeader)
    IMPLEMENT_PROXY(winmm, midiOutShortMsg)
    IMPLEMENT_PROXY(winmm, midiOutLongMsg)
    IMPLEMENT_PROXY(winmm, midiOutReset)
    IMPLEMENT_PROXY(winmm, midiOutCachePatches)
    IMPLEMENT_PROXY(winmm, midiOutCacheDrumPatches)
    IMPLEMENT_PROXY(winmm, midiOutGetID)
    IMPLEMENT_PROXY(winmm, midiOutMessage)
    IMPLEMENT_PROXY(winmm, midiInGetNumDevs)
    IMPLEMENT_PROXY(winmm, midiInGetDevCapsA)
    IMPLEMENT_PROXY(winmm, midiInGetDevCapsW)
    IMPLEMENT_PROXY(winmm, midiInGetErrorTextA)
    IMPLEMENT_PROXY(winmm, midiInGetErrorTextW)
    IMPLEMENT_PROXY(winmm, midiInOpen)
    IMPLEMENT_PROXY(winmm, midiInClose)
    IMPLEMENT_PROXY(winmm, midiInPrepareHeader)
    IMPLEMENT_PROXY(winmm, midiInUnprepareHeader)
    IMPLEMENT_PROXY(winmm, midiInAddBuffer)
    IMPLEMENT_PROXY(winmm, midiInStart)
    IMPLEMENT_PROXY(winmm, midiInStop)
    IMPLEMENT_PROXY(winmm, midiInReset)
    IMPLEMENT_PROXY(winmm, midiInGetID)
    IMPLEMENT_PROXY(winmm, midiInMessage)
    /* Auxiliary audio support */
    IMPLEMENT_PROXY(winmm, auxGetNumDevs)
    IMPLEMENT_PROXY(winmm, auxGetDevCapsA)
    IMPLEMENT_PROXY(winmm, auxGetDevCapsW)
    IMPLEMENT_PROXY(winmm, auxSetVolume)
    IMPLEMENT_PROXY(winmm, auxGetVolume)
    IMPLEMENT_PROXY(winmm, auxOutMessage)
    /* Mixer support */
    IMPLEMENT_PROXY(winmm, mixerGetNumDevs)
    IMPLEMENT_PROXY(winmm, mixerGetDevCapsA)
    IMPLEMENT_PROXY(winmm, mixerGetDevCapsW)
    IMPLEMENT_PROXY(winmm, mixerOpen)
    IMPLEMENT_PROXY(winmm, mixerClose)
    IMPLEMENT_PROXY(winmm, mixerMessage)
    IMPLEMENT_PROXY(winmm, mixerGetLineInfoA)
    IMPLEMENT_PROXY(winmm, mixerGetLineInfoW)
    IMPLEMENT_PROXY(winmm, mixerGetID)
    IMPLEMENT_PROXY(winmm, mixerGetLineControlsA)
    IMPLEMENT_PROXY(winmm, mixerGetLineControlsW)
    IMPLEMENT_PROXY(winmm, mixerGetControlDetailsA)
    IMPLEMENT_PROXY(winmm, mixerGetControlDetailsW)
    IMPLEMENT_PROXY(winmm, mixerSetControlDetails)
    /* Timer support */
    IMPLEMENT_PROXY(winmm, timeGetSystemTime)
    IMPLEMENT_PROXY(winmm, timeGetTime)
    IMPLEMENT_PROXY(winmm, timeGetDevCaps)
    IMPLEMENT_PROXY(winmm, timeBeginPeriod)
    IMPLEMENT_PROXY(winmm, timeEndPeriod)
    /* Joystick support */
    IMPLEMENT_PROXY(winmm, joyGetPosEx)
    IMPLEMENT_PROXY(winmm, joyGetNumDevs)
    IMPLEMENT_PROXY(winmm, joyGetDevCapsA)
    IMPLEMENT_PROXY(winmm, joyGetDevCapsW)
    IMPLEMENT_PROXY(winmm, joyGetPos)
    IMPLEMENT_PROXY(winmm, joyGetThreshold)
    IMPLEMENT_PROXY(winmm, joyReleaseCapture)
    IMPLEMENT_PROXY(winmm, joySetCapture)
    IMPLEMENT_PROXY(winmm, joySetThreshold)
    IMPLEMENT_PROXY(winmm, joyConfigChanged)
    /* MCI support */
    IMPLEMENT_PROXY(winmm, mciSendCommandA)
    IMPLEMENT_PROXY(winmm, mciSendCommandW)
    IMPLEMENT_PROXY(winmm, mciSendStringA)
    IMPLEMENT_PROXY(winmm, mciSendStringW)
    IMPLEMENT_PROXY(winmm, mciGetDeviceIDA)
    IMPLEMENT_PROXY(winmm, mciGetDeviceIDW)
    IMPLEMENT_PROXY(winmm, mciGetDeviceIDFromElementIDA)
    IMPLEMENT_PROXY(winmm, mciGetDeviceIDFromElementIDW)
    IMPLEMENT_PROXY(winmm, mciGetErrorStringA)
    IMPLEMENT_PROXY(winmm, mciGetErrorStringW)
    IMPLEMENT_PROXY(winmm, mciSetYieldProc)
    IMPLEMENT_PROXY(winmm, mciGetCreatorTask)
    IMPLEMENT_PROXY(winmm, mciGetYieldProc)
    /* Multimedia File I/O support */
    IMPLEMENT_PROXY(winmm, mmioStringToFOURCCA)
    IMPLEMENT_PROXY(winmm, mmioStringToFOURCCW)
    IMPLEMENT_PROXY(winmm, mmioInstallIOProcA)
    IMPLEMENT_PROXY(winmm, mmioInstallIOProcW)
    IMPLEMENT_PROXY(winmm, mmioOpenA)
    IMPLEMENT_PROXY(winmm, mmioOpenW)
    IMPLEMENT_PROXY(winmm, mmioRenameA)
    IMPLEMENT_PROXY(winmm, mmioRenameW)
    IMPLEMENT_PROXY(winmm, mmioClose)
    IMPLEMENT_PROXY(winmm, mmioRead)
    IMPLEMENT_PROXY(winmm, mmioWrite)
    IMPLEMENT_PROXY(winmm, mmioSeek)
    IMPLEMENT_PROXY(winmm, mmioGetInfo)
    IMPLEMENT_PROXY(winmm, mmioSetInfo)
    IMPLEMENT_PROXY(winmm, mmioSetBuffer)
    IMPLEMENT_PROXY(winmm, mmioFlush)
    IMPLEMENT_PROXY(winmm, mmioAdvance)
    IMPLEMENT_PROXY(winmm, mmioSendMessage)
    IMPLEMENT_PROXY(winmm, mmioDescend)
    IMPLEMENT_PROXY(winmm, mmioAscend)
    IMPLEMENT_PROXY(winmm, mmioCreateChunk)
}
