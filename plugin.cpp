#include "stdafx.h"
#include <detours/detours.h>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include "plugin.h"
#include "rugp.h"
#include "hook.h"

static AFX_EXTENSION_MODULE R514783_PLUGIN = {FALSE, nullptr};

// ReSharper disable once CppParameterMayBeConst
BOOL WINAPI DllMain(HINSTANCE hInstance, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        _set_se_translator(&StructuredException::Trans);
        AllocConsole();
        SetConsoleTitleA("r514783 Plugin Debug Console");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        setlocale(LC_ALL, ".UTF8");
        freopen("CON", "w", stdout);

        wprintf(L"MFC Version %hs\n", GetMfcVersion());
        wprintf(L"rUGP System Version %hs\n", CrUGP::GetGlobal()->GetVersion());
        wprintf(L"JsonCpp Version %hs\n", JSONCPP_VERSION_STRING);
        wprintf(L"Detours Version %x\n", DETOURS_VERSION);
        wprintf(L"\n");
        wprintf(L"CommandLine %s\n", GetCommandLineW());
        wprintf(L"\n");

        AfxInitExtensionModule(R514783_PLUGIN, hInstance);

        try
        {
            CreateDirectoryW(GetGameName().c_str(), nullptr);
        }
        catch (StructuredException& se)
        {
            wprintf(L"CreateMergeDirectory Fail: %hs\n", se.what());
        }

        try
        {
            Win32Hook::AttachHook();
        }
        catch (StructuredException& se)
        {
            wprintf(L"Win32Hook::AttachHook Fail: %hs\n", se.what());
        }

        try
        {
            CObjectProxy::LoadFromModule("UnivUI");
            CObjectProxy::LoadFromModule("rvmm");
            CObjectProxy::LoadFromModule("Vm60");
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::LoadFromModule Fail: %hs\n", se.what());
        }

        try
        {
            CObjectProxy::AttachHook();
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::AttachHook Fail: %hs\n", se.what());
        }

        try
        {
            CObjectProxy::AttachCharacterPatch("GMfc");
            CObjectProxy::AttachCharacterPatch("UnivUI");
            CObjectProxy::AttachCharacterPatch("rvmm");
            CObjectProxy::AttachCharacterPatch("Vm60");
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::AttachCharacterPatch Fail: %hs\n", se.what());
        }

        break;
    case DLL_PROCESS_DETACH:
        try
        {
            CObjectProxy::DetachCharacterPatch();
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::DetachCharacterPatch Fail: %hs\n", se.what());
        }

        try
        {
            CObjectProxy::DetachHook();
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::DetachHook Fail: %hs\n", se.what());
        }

        try
        {
            CObjectProxy::Clear();
        }
        catch (StructuredException& se)
        {
            wprintf(L"CObjectProxy::Clear %hs\n", se.what());
        }

        try
        {
            Win32Hook::DetachHook();
        }
        catch (StructuredException& se)
        {
            wprintf(L"Win32Hook::DetachHook Fail: %hs\n", se.what());
        }

        FreeConsole();

        AfxTermExtensionModule(R514783_PLUGIN, FALSE);

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }

    return TRUE;
}

const AFX_EXTENSION_MODULE* PluginThisLibrary()
{
    // CObjectProxy::LoadFromModule("riooor.rpo");
    // CObjectProxy::LoadFromModule("age_classic.rpo");

    return &R514783_PLUGIN;
}

LPCSTR WINAPIV GetPluginString()
{
    return "Fuck rUGP! Version 0.1.0\r\n"
        "\tThis is unofficial plugin.\r\n"
        "\t(c)2024-2025 CssXsh All rights reserved.\r\n"
        "\r\n";
}

std::wstring WINAPI UnicodeX(const LPCSTR lpText, const UINT nCodePage)
{
    const auto native = Unicode(lpText, nCodePage);
    if (native == nullptr) return L"(null)";
    const auto result = std::wstring(native);
    free(native);
    return result;
}

std::string WINAPI AnsiX(const LPCWSTR lpText, const UINT nCodePage)
{
    const auto native = Ansi(lpText, nCodePage);
    if (native == nullptr) return "(null)";
    const auto result = std::string(native);
    free(native);
    return result;
}

std::string WINAPI AnsiX(const LPCSTR lpText, const UINT from, const UINT to)
{
    const auto unicode = Unicode(lpText, from);
    if (unicode == nullptr) return "(null)";
    const auto native = Ansi(unicode, to);
    free(unicode);
    if (native == nullptr) return "(null)";
    const auto result = std::string(native);
    free(native);
    return result;
}

std::wstring GetUUID(const COceanNode* const node)
{
    wchar_t buffer[MAX_PATH];
    const auto name = UnicodeX(node->m_pRTC ? node->m_pRTC->m_lpszClassName : nullptr, CP_SHIFT_JIS);
    swprintf(buffer, MAX_PATH, L"%s@%08X", name.c_str(), node->GetAddress());
    return buffer;
}

std::wstring GetGameName()
{
    const auto command = GetCommandLineW();
    const auto l = wcsrchr(command, L'\\') + 1;
    const auto r = wcschr(l, L'}');
    return {l, r};
}

StructuredException::StructuredException(const UINT u, const EXCEPTION_POINTERS* pExp) : m_pExceptionPointers(pExp)
{
    const auto data = reinterpret_cast<__std_exception_data*>(this);
    const auto record = pExp->ExceptionRecord;
    const auto module = DetourGetContainingModule(record->ExceptionAddress);
    char filename[MAX_PATH];
    GetModuleFileNameA(module, filename, MAX_PATH);
    const auto buffer = static_cast<LPSTR>(malloc(0x0100));
    sprintf(buffer, "StructuredException 0x%08X at address 0x%p module %s",
            u, record->ExceptionAddress, strrchr(filename, '\\') + 1);
    const __std_exception_data temp = { buffer, true };
    __std_exception_copy(&temp, data);
    free(buffer);
}

void StructuredException::Trans(UINT const u, PEXCEPTION_POINTERS const pExp) // NOLINT(*-misplaced-const)
{
    throw StructuredException(u, pExp);
}

BOOL CObjectProxy::LoadFromModule(LPCSTR const lpszModuleName)
{
    const auto hModule = GetModuleHandleA(lpszModuleName);
    if (hModule == nullptr) return FALSE;
    const auto proc = GetProcAddress(hModule, "PluginThisLibrary");
    if (proc == nullptr) return FALSE;

    auto& module = MODULE_MAP[hModule] = nullptr;
    if (CRio::FetchLibrarySupport() != nullptr)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&reinterpret_cast<PVOID&>(CRio::FetchLibrarySupport()), &HookSupportRio);
        DetourTransactionCommit();
        reinterpret_cast<const AFX_EXTENSION_MODULE*>(proc());
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&reinterpret_cast<PVOID&>(CRio::FetchLibrarySupport()), &HookSupportRio);
        DetourTransactionCommit();
    }
    else
    {
        module = reinterpret_cast<const AFX_EXTENSION_MODULE*>(proc());
    }
    if (module == nullptr) return FALSE;
    for (auto clazz = module->pFirstSharedClass; clazz != nullptr; clazz = clazz->m_pNextClass)
    {
        const auto name = UnicodeX(clazz->m_lpszClassName, CP_SHIFT_JIS);
        RTC_MAP[name] = clazz;
    }

    return TRUE;
}

void CObjectProxy::AttachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : RTC_MAP)
    {
        const auto clazz = pair.second;
        if (clazz->m_pfnCreateObject == nullptr) continue;
        // fix: CResourceClipOnlyRegion
        if (clazz->m_pfnGetBaseClass() == clazz) continue;
        const auto name = UnicodeX(clazz->m_lpszClassName, CP_SHIFT_JIS);

        if (clazz->IsDerivedFrom(CCommandRef::GetClassCCommandRef()))
        {
            wprintf(L"DetourAttach: %s::GetNextCommand\n", name.c_str());
            DetourAttach(&reinterpret_cast<PVOID&>(CCommandRef::FetchGetNextCommand(clazz)), &HookGetNextCommand);
            wprintf(L"DetourAttach: %s::~%s\n", name.c_str(), name.c_str());
            DetourAttach(&reinterpret_cast<PVOID&>(CRio::FetchDestructor(clazz)), &HookDestructor);
        }

        if (clazz->IsDerivedFrom(CRip::GetClassCRip()))
        {
            wprintf(L"DetourAttach: %s::Serialize\n", name.c_str());
            DetourAttach(&reinterpret_cast<PVOID&>(CRio::FetchSerialize(clazz)), &HookSerialize);
        }
    }
    if (COceanNode::FetchGetLocalFullPathName())
    {
        DetourAttach(&reinterpret_cast<PVOID&>(COceanNode::FetchGetLocalFullPathName()), &HookGetLocalFullPathName);
    }
    if (CS5i::FetchDrawFont1())
    {
        wprintf(L"DetourAttach: CS5i::DrawFont\n");
        DetourAttach(&reinterpret_cast<PVOID&>(CS5i::FetchDrawFont1()), &HookDrawFont1);
    }
    if (CS5i::FetchDrawFont2())
    {
        wprintf(L"DetourAttach: CS5i::DrawFont\n");
        DetourAttach(&reinterpret_cast<PVOID&>(CS5i::FetchDrawFont2()), &HookDrawFont2);
    }
    if (CS5RFont::FetchGetCachedFont())
    {
        wprintf(L"DetourAttach: CS5RFont::GetCachedFont\n");
        DetourAttach(&reinterpret_cast<PVOID&>(CS5RFont::FetchGetCachedFont()), &HookGetCachedFont);
    }
    if (GMfc::FetchIsMBCS())
    {
        wprintf(L"DetourAttach: IsDBCS\n");
        DetourAttach(&reinterpret_cast<PVOID&>(GMfc::FetchIsMBCS()), &HookIsMBCS);
    }
    if (CUuiGlobals::FetchStep())
    {
        wprintf(L"DetourAttach: CBootTracer::Step\n");
        DetourAttach(&reinterpret_cast<PVOID&>(CUuiGlobals::FetchStep()), &HookStep);
    }
    if (CProcessOcean::FetchBeginProcess())
    {
        wprintf(L"DetourAttach: CProcessOcean::BeginProcess\n");
        DetourAttach(&reinterpret_cast<PVOID&>(CProcessOcean::FetchBeginProcess()), &HookBeginProcess);
    }
    DetourTransactionCommit();
}

void CObjectProxy::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : RTC_MAP)
    {
        const auto clazz = pair.second;
        if (clazz->m_pfnCreateObject == nullptr) continue;
        // fix: CResourceClipOnlyRegion
        if (clazz->m_pfnGetBaseClass() == clazz) continue;
        const auto name = UnicodeX(clazz->m_lpszClassName, CP_SHIFT_JIS);

        if (clazz->IsDerivedFrom(CCommandRef::GetClassCCommandRef()))
        {
            wprintf(L"DetourDetach: %s::GetNextCommand\n", name.c_str());
            DetourDetach(&reinterpret_cast<PVOID&>(CCommandRef::FetchGetNextCommand(clazz)), &HookGetNextCommand);
            wprintf(L"DetourDetach: %s::~%s\n", name.c_str(), name.c_str());
            DetourDetach(&reinterpret_cast<PVOID&>(CRio::FetchDestructor(clazz)), &HookDestructor);
        }

        if (clazz->IsDerivedFrom(CRip::GetClassCRip()))
        {
            wprintf(L"DetourDetach: %s::Serialize\n", name.c_str());
            DetourDetach(&reinterpret_cast<PVOID&>(CRio::FetchSerialize(clazz)), &HookSerialize);
        }
    }
    if (CS5i::FetchDrawFont1())
    {
        wprintf(L"DetourDetach: CS5i::DrawFont\n");
        DetourDetach(&reinterpret_cast<PVOID&>(CS5i::FetchDrawFont1()), &HookDrawFont1);
    }
    if (CS5i::FetchDrawFont2())
    {
        wprintf(L"DetourDetach: CS5i::DrawFont\n");
        DetourDetach(&reinterpret_cast<PVOID&>(CS5i::FetchDrawFont2()), &HookDrawFont2);
    }
    if (CS5RFont::FetchGetCachedFont())
    {
        wprintf(L"DetourDetach: CS5RFont::GetCachedFont\n");
        DetourDetach(&reinterpret_cast<PVOID&>(CS5RFont::FetchGetCachedFont()), &HookGetCachedFont);
    }
    if (GMfc::FetchIsMBCS())
    {
        wprintf(L"DetourDetach: IsDBCS\n");
        DetourDetach(&reinterpret_cast<PVOID&>(GMfc::FetchIsMBCS()), &HookIsMBCS);
    }
    DetourTransactionCommit();
}

void CObjectProxy::Clear()
{
    for (auto& pair : COMMAND_MAP)
    {
        auto p = pair.second;
        pair.second = nullptr;
        while (p != nullptr)
        {
            const auto command = p;
            p = p->m_pNext;
            free(command);
        }
    }
    COMMAND_MAP.clear();
    RTC_MAP.clear();
    MODULE_MAP.clear();

    CHARACTER_MAP.clear();

    for (auto& pair : FONT_CACHE)
    {
        const auto record = pair.second;
        pair.second = nullptr;

        free(record);
    }
    FONT_CACHE.clear();
}

void CObjectProxy::AttachCharacterPatch(LPCSTR const lpszModuleName)
{
    const auto hModule = GetModuleHandleA(lpszModuleName);
    if (hModule == nullptr) return;
    const auto start = reinterpret_cast<LPBYTE>(hModule) + 0x00001000;
    const auto end = reinterpret_cast<LPBYTE>(hModule) + DetourGetModuleSize(hModule);
    const auto replace = [hModule, lpszModuleName](LPBYTE const offset, UINT const nChar) // NOLINT(*-misplaced-const)
    {
        const auto address = reinterpret_cast<LPDWORD>(offset);
        if (offset[0x04] == 0x00u) return;
        const auto diff = 0x10000000u - reinterpret_cast<DWORD>(hModule);
        wprintf(L"Attach CharacterPatch 0x%p at %hs\n", offset + diff, lpszModuleName);
        const auto record = static_cast<CodePatchRecord*>(malloc(sizeof(CodePatchRecord) + sizeof(DWORD)));
        record->block_size = sizeof(DWORD);
        memcpy(record->codes, address, record->block_size);
        auto protect = static_cast<DWORD>(PAGE_EXECUTE_READWRITE);
        VirtualProtect(address, record->block_size, protect, &protect);
        *address = nChar;
        VirtualProtect(address, record->block_size, protect, &protect);
        PATCH_CACHE[address] = record;
    };
    for (auto offset = start; offset < end; offset++)
    {
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(offset))) break;
        if (IsBadReadPtr(offset, sizeof(DWORD))) continue;
        switch (*reinterpret_cast<const DWORD*>(offset))
        {
        // add     al, 5Fh
        // cmp     al, 3Bh
        case 0x3B3C5F04u:
            {
                const auto address = offset + 0x00;
                const auto diff = 0x10000000u - reinterpret_cast<DWORD>(hModule);
                wprintf(L"Attach CharacterPatch 0x%p at %hs\n", address + diff, lpszModuleName);
                const auto record = static_cast<CodePatchRecord*>(malloc(sizeof(CodePatchRecord) + 0x04));
                record->block_size = 0x04;
                memcpy(record->codes, address, record->block_size);
                auto protect = static_cast<DWORD>(PAGE_EXECUTE_READWRITE);
                VirtualProtect(address, record->block_size, protect, &protect);
                address[0x00] = 0x34u;
                address[0x01] = 0xA0u;
                address[0x03] = 0x7Eu;
                VirtualProtect(address, record->block_size, protect, &protect);
                PATCH_CACHE[address] = record;
                AttachCharacterSplit(address + record->block_size, lpszModuleName);
            }
            break;
        // add     cl, 5Fh
        // cmp     cl, 3Bh
        case 0x3BF9805Fu:
        // add     dl, 5Fh
        // cmp     dl, 3Bh
        case 0x3BFA805Fu:
        // add     bl, 5Fh
        // cmp     bl, 3Bh
        case 0x3BFB805Fu:
            {
                const auto address = offset - 0x02;
                if (address[0x00] != 0x80u || (address[0x01] & 0xC0) != 0xC0u) continue;
                const auto diff = 0x10000000u - reinterpret_cast<DWORD>(hModule);
                wprintf(L"Attach CharacterPatch 0x%p at %hs\n", address + diff, lpszModuleName);
                const auto record = static_cast<CodePatchRecord*>(malloc(sizeof(CodePatchRecord) + 0x06));
                record->block_size = 0x06;
                memcpy(record->codes, address, record->block_size);
                auto protect = static_cast<DWORD>(PAGE_EXECUTE_READWRITE);
                VirtualProtect(address, record->block_size, protect, &protect);
                address[0x01] = address[0x01] ^ 0x30u;
                address[0x02] = 0xA0u;
                address[0x05] = 0x7Eu;
                VirtualProtect(address, record->block_size, protect, &protect);
                PATCH_CACHE[address] = record;
                AttachCharacterSplit(address + record->block_size, lpszModuleName);
            }
            break;
        // push    esi
        // call    ds:__imp_?IsDBCS@@YAHD@Z
        // add     esp, 4
        // test    eax, eax
        case 0x8504C483u:
            {
                const auto address = offset - 0x07;
                if (IsBadCodePtr(reinterpret_cast<FARPROC>(address))) continue;
                if (address[0x01] != 0xFFu || address[0x02] != 0x15u) continue;
                if (IsBadCodePtr(*reinterpret_cast<FARPROC*>(address + 0x03))) continue;
                const auto proc = **reinterpret_cast<FARPROC**>(address + 0x03);
                if (proc != reinterpret_cast<FARPROC>(GMfc::FetchIsMBCS())) continue;
                AttachCharacterSplit(address + 0x0Cu, lpszModuleName);
            }
            break;
        // 0xA1A1
        case 0x00008140u:
            replace(offset, 0x0000A1A1u);
            break;
        // 0xA1B8
        case 0x00008175u:
            replace(offset, 0x0000A1B8u);
            break;
        // 0xA1B9
        case 0x00008176u:
            replace(offset, 0x0000A1B9u);
            break;
        // 0xA1BE
        case 0x00008179u:
            replace(offset, 0x0000A1BEu);
            break;
        // 0xA1BF
        case 0x0000817Au:
            replace(offset, 0x0000A1BFu);
            break;
        // 0xA844
        case 0x0000815Cu:
            replace(offset, 0x0000A844u);
            break;
        // 0xA9A4
        case 0x0000849Fu:
            replace(offset, 0x0000A9A4u);
            break;
        default:
            break;
        }
    }
}

void CObjectProxy::DetachCharacterPatch()
{
    for (auto& pair : PATCH_CACHE)
    {
        const auto address = pair.first;
        const auto record = pair.second;
        pair.second = nullptr;

        if (IS_INTRESOURCE(record->target))
        {
            auto protect = static_cast<DWORD>(PAGE_EXECUTE_READWRITE);
            VirtualProtect(address, record->block_size, protect, &protect);
            memcpy(address, record->codes, record->block_size);
            VirtualProtect(address, record->block_size, protect, &protect);
            free(record);
        }
        else
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(&reinterpret_cast<PVOID&>(record->target), record->codes);
            DetourTransactionCommit();
            VirtualFree(record, 0, MEM_RELEASE);
        }
    }
    PATCH_CACHE.clear();
}

void CObjectProxy::AttachCharacterSplit(LPBYTE const address, LPCSTR const lpszModuleName) // NOLINT(*-misplaced-const)
{
    if (strcmp(lpszModuleName, "GMfc") == 0) return;
    const auto module = DetourGetContainingModule(address);
    const auto offset = 0x10000000u - reinterpret_cast<DWORD>(module);
    auto start = static_cast<LPBYTE>(nullptr);
    auto end = static_cast<LPBYTE>(nullptr);
    switch (address[0x00])
    {
    // ja      ...
    case 0x0Fu:
        start = address + 0x06;
        end = start + *reinterpret_cast<int*>(address + 0x02);
        break;
    // jz      short ...
    case 0x74u:
    // ja      short ...
    case 0x77u:
        start = address + 0x02;
        end = start + *reinterpret_cast<char*>(address + 0x01);
        break;
    // jbe     short ...
    case 0x76u:
        end = address + 0x02;
        start = end + *reinterpret_cast<char*>(address + 0x01);
        break;
    default:
        wprintf(L"Attach CharacterSplit Error 0x%p at %hs\n", address + offset, lpszModuleName);
        return;
    }
    // jmp     ...
    if (start[0x01] == 0xEBu || start[0x01] == 0xE9u) end = start + 0x01;
    else if (start[0x05] == 0xEBu) end = start + 0x05;
    // cmp     ..., ...
    for (auto pos = start; pos < end; pos++)
    {
        switch (pos[0x00])
        {
        case 0x81u:
            if (pos[0x04] != 0x00u) continue;
            if (pos[0x05] != 0x00u) continue;
            break;
        case 0x3Du:
            if (pos[0x03] != 0x00u) continue;
            if (pos[0x04] != 0x00u) continue;
            break;
        default:
            continue;
        }
        end = pos;
        break;
    }
    if (start > end && start[0x0B] == 0x81u) end = start + 0x0B;
    // mov     ..., [ebp+...]
    if (start[0x00] == 0x8Bu && (start[0x01] & 0x45u) == 0x45u) start += 0x03;
    // mov     ..., [esp+...]
    if (start[0x00] == 0x8Bu && start[0x02] == 0x24u) start += 0x04;
    // mov     [ebp+...], ...
    if (end - start == 0x0C && start[0x09] == 0x89u) end = start + 0x09;
    // mov     [esp+...], ...
    if (end - start == 0x0E && start[0x0A] == 0x89u) end = start + 0x0A;
    // test    ..., ...
    if (start[0x00] == 0x85u) end = start + 0x00;
    else if (start[0x04] == 0x85u) end = start + 0x04;
    else if (start[0x09] == 0x85u) end = start + 0x09;

    switch (reinterpret_cast<DWORD>(start) + offset)
    {
    // 5.81.03   UnivUI .text:1002A2BE ?x2C@CUser@@UBE_NPBD@Z
    case 0x1002A2BEu:
    // 5.95.05   UnivUI .text:1002BA4E ?x2C@CUser@@UBE_NPBD@Z
    case 0x1002BA4Eu:
    // 6.23.02   UnivUI .text:10025C68 ?GetSwitch@CRioRTC@@QBEHPBD@Z
    case 0x10025C68u:
    // 6.23.02   UnivUI .text:100363F6 ?x2C@CUser@@UBE_NPBD@Z
    case 0x100363F6u:
        if (strcmp(lpszModuleName, "UnivUI") == 0) return;
        break;
    // 5.60.32   Vm60   .text:10011467 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x10011467u:
    // 5.73.01   Vm60   .text:10013CE6 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x10013CE6u:
    // 5.80.20EC Vm60   .text:100146B6 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x100146B6u:
    // 5.81.03   Vm60   .text:10014906 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x10014906u:
    // 5.95.05   Vm60   .text:10016526 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x10016526u:
    // 6.23.02   Vm60   .text:1001C4D2 ?PrefetchNameTag@CMessBox@@IAE?AVCString@@PAE@Z
    case 0x1001C4D2u:
    // 6.23.02   Vm60   .text:10023317 ?AttachInstructionText@CMessBox@@UAEXPBDVTRio@@1K@Z
    case 0x10023317u:
    // 6.23.02   Vm60   .text:100C0341 ?ExecCommand@CVmMsg@@UAEPAVCVmCommand@@XZ
    case 0x100C0341u:
    // 6.23.02   Vm60   .text:100C0375 ?ExecCommand@CVmMsg@@UAEPAVCVmCommand@@XZ
    case 0x100C0375u:
        if (strcmp(lpszModuleName, "Vm60") == 0) return;
        break;
    default:
        if (start[0x00] == 0x8Au && start[0x02] == 0x01u &&
            start[0x03] == 0x8Au && start[0x05] == 0x01u &&
            start[0x06] == 0x3Au)
        {
            // mov     .., [...+1]
            // mov     .., [...+1]
            // cmp     .., ..
            return;
        }
        if (start[0x00] == 0x8Au && start[0x02] == 0x01u &&
            (start[0x03] & 0xF8u) == 0x40u &&
            start[0x04] == 0x3Au && start[0x06] == 0x01u)
        {
            // mov     .., [...+1]
            // inc     ...
            // cmp     .., [...+1]
            return;
        }
        if (start[0x00] == 0x8Au &&
            start[0x02] == 0x88u &&
            (start[0x04] & 0xF8u) == 0x40u)
        {
            // mov     .., [...]
            // mov     [...], ..
            // inc     ...
            return;
        }
        break;
    }

    const auto attach = [start, end](BYTE const tmp)
    {
        auto& record = PATCH_CACHE[end];
        if (record != nullptr) return;
        record = static_cast<CodePatchRecord*>(VirtualAlloc(
            nullptr,
            sizeof(CodePatchRecord) + 0x0040,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_EXECUTE_READWRITE));
        auto& hook = record->target = end;
        const auto codes = record->codes;
        memset(codes, 0xCCu, 0x0040);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&hook, codes);
        DetourTransactionCommit();
        auto index = 0x00;
        // cmp     @tmp, 0x39
        codes[index++] = 0x83, codes[index++] = 0xF8 | tmp, codes[index++] = 0x39;
        // ja      ...
        codes[index++] = 0x0F, codes[index++] = 0x87;
        *reinterpret_cast<int*>(codes + index) =
            reinterpret_cast<int>(hook) - reinterpret_cast<int>(codes + index + 0x04);
        index += 0x04;
        // action
        memcpy(codes + index, start, end - start);
        index += end - start;
        // action
        memcpy(codes + index, start, end - start);
        index += end - start;
        // jmp     ...
        codes[index++] = 0xE9;
        *reinterpret_cast<int*>(codes + index) =
            reinterpret_cast<int>(hook) - reinterpret_cast<int>(codes + index + 0x04);
        VirtualProtect(codes, 0x0040, PAGE_EXECUTE_READ, nullptr);
    };

    const auto attach_ = [start, end](BYTE const tmp)
    {
        auto& record = PATCH_CACHE[end];
        if (record != nullptr) return;
        record = static_cast<CodePatchRecord*>(VirtualAlloc(
            nullptr,
            sizeof(CodePatchRecord) + 0x0040,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_EXECUTE_READWRITE));
        auto& hook = reinterpret_cast<PVOID&>(record->target) = end;
        const auto codes = record->codes;
        memset(codes, 0xCCu, 0x0040);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&hook, codes);
        DetourTransactionCommit();
        auto index = 0x00;
        // cmp     @tmp, 0x39
        codes[index++] = 0x83, codes[index++] = 0xF8 | tmp, codes[index++] = 0x39;
        // ja      ...
        codes[index++] = 0x0F, codes[index++] = 0x87;
        *reinterpret_cast<int*>(codes + index) =
            reinterpret_cast<int>(hook) - reinterpret_cast<int>(codes + index + 0x04);
        index += 0x04;
        // action
        memcpy(codes + index, start, end - start);
        codes[index + 0x01] = 0xB7;
        codes[index + 0x03] = 0x02;
        codes[index + 0x06] = 0x10;
        codes[index + 0x0C] = 0x04;
        index += end - start;
        // jmp     ...
        codes[index++] = 0xE9;
        *reinterpret_cast<int*>(codes + index) =
            reinterpret_cast<int>(hook) - reinterpret_cast<int>(codes + index + 0x04);
        VirtualProtect(codes, 0x0040, PAGE_EXECUTE_READ, nullptr);
    };

    switch (end - start)
    {
    case 0x00:
        return;
    case 0x01:
    case 0x04:
        // inc     ...
        if ((end[-0x01] & 0xF8u) == 0x40u) return;
        break;
    case 0x09:
    case 0x0A:
    case 0x0B:
        if (end[-0x06] == 0xC1u && end[-0x04] == 0x08u &&
            (end[-0x01] & 0xF8u) == 0x40u)
        {
            // shl     ..., 8
            // or      ..., ...
            // inc     ...
            wprintf(L"Attach CharacterSplit 0x%p at %hs\n", address + offset, lpszModuleName);
            attach((end[-0x03] == 0x0B ? end[-0x02] : end[-0x02] >> 0x03) & 0x07);
            return;
        }
        if (end[-0x08] == 0xC1u && end[-0x06] == 0x08u &&
            (end[-0x01] & 0xF8u) == 0x40u)
        {
            // shl     ..., 8
            // mov     .., [...]
            // or      ..., ...
            // inc     ...
            wprintf(L"Attach CharacterSplit 0x%p at %hs\n", address + offset, lpszModuleName);
            attach((end[-0x03] == 0x0B ? end[-0x02] : end[-0x02] >> 0x03) & 0x07);
            return;
        }
        if (end[-0x05] == 0xC1u && end[-0x03] == 0x08u &&
            (end[-0x06] & 0xF8u) == 0x40u)
        {
            // movzx   ..., byte ptr [...]
            // inc     ...
            // shl     ..., 8
            // or      ..., ...
            wprintf(L"Attach CharacterSplit 0x%p at %hs\n", address + offset, lpszModuleName);
            attach((end[-0x02] == 0x0B ? end[-0x01] : end[-0x01] >> 0x03) & 0x07);
            return;
        }
        break;
    case 0x10:
        if (start[0x01] == 0xB6u && start[0x03] == 0x01u &&
            start[0x06] == 0x08u &&
            start[0x0C] == 0x02u)
        {
            // movzx   ..., byte ptr [...+1]
            // shl     ..., 8
            // or      ..., ...
            // mov     [ebp+...], 2
            wprintf(L"Attach CharacterSplit 0x%p at %hs\n", address + offset, lpszModuleName);
            attach_((start[0x07] == 0x0B ? end[0x08] : end[0x08] >> 0x03) & 0x07);
            return;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    wprintf(L"Attach CharacterSplit Fail 0x%p ~ 0x%p at %hs\n", start + offset, end + offset, lpszModuleName);
}

int CObjectProxy::CharacterByteSize(LPCSTR const text)
{
    // GB18030
    if ((text[0x0000] & 0x80u) == 0x00u) return 1;
    if ((text[0x0001] & 0xC0u) == 0x00u) return 4;
    return 2;
}

std::wstring CObjectProxy::GetPatchFilePath(const COceanNode* const node)
{
    wchar_t buffer[MAX_PATH];
    auto format = UnicodeX(node->m_pRTC ? node->m_pRTC->m_lpszClassName : "bin", CP_SHIFT_JIS);
    if (format[0] == L'C') format.erase(0, 1);
    for (auto& ch : format) ch = towlower(ch);
    swprintf(buffer, MAX_PATH, L"./%s/%08X.%s", GetGameName().c_str(), node->GetAddress(), format.c_str());
    return buffer;
}

CVmCommand* CObjectProxy::Fetch(const CVmCommand* const ecx, Json::Value& edx)
{
    auto result = static_cast<CVmCommand*>(nullptr);
    auto prev = static_cast<CVmCommand*>(nullptr);
    auto next = static_cast<CVmCommand*>(nullptr);
    for (auto command = ecx; command != nullptr; command = command->m_pNext)
    {
        const auto pClass = command->GetRuntimeClass();
        char name[0x20];
        sprintf(name, "%08X:%s", command->m_dwFlags & 0x000FFFFF, pClass->m_lpszClassName);
        next = const_cast<CVmCommand*>(command);
        switch (*reinterpret_cast<const DWORD*>(pClass->m_lpszClassName + 0x03))
        {
        // CVmMsg
        case 0x0067734Du:
            {
                auto& message = reinterpret_cast<CVmMsg*&>(next);
                Merge(message, edx[name]);
                // cache 4 bytes character
                for (auto lpsz = message->m_pVariableArea; *lpsz != '\0'; lpsz += CharacterByteSize(lpsz))
                {
                    if (static_cast<BYTE>(lpsz[0x00]) < 0x81u || static_cast<BYTE>(lpsz[0x01]) > 0x39u) continue;
                    const auto uChar = 0u
                        | static_cast<BYTE>(lpsz[0x00]) << 0x18
                        | static_cast<BYTE>(lpsz[0x01]) << 0x10
                        | static_cast<BYTE>(lpsz[0x02]) << 0x08
                        | static_cast<BYTE>(lpsz[0x03]) << 0x00;
                    CHARACTER_MAP[uChar & 0xFFFFu] = uChar;
                }
            }
            break;
        // CVmGenericMsg
        case 0x656E6547:
            {
                auto& generic = reinterpret_cast<CVmGenericMsg*&>(next);
                Merge(generic, edx[name]);
            }
            break;
        // CVmCall
        case 0x6C6C6143:
            {
                auto& call = reinterpret_cast<CVmCall*&>(next);
                Merge(call, edx[name]);
            }
            break;
        default:
            {
                edx[name] = Json::Value(Json::nullValue);
                const auto size = pClass->m_nObjectSize + command->GetVariableAreaSize();
                const auto clone = static_cast<CVmCommand*>(malloc(size));
                memcpy(clone, command, size); // NOLINT(*-undefined-memory-manipulation)
                next = clone;
            }
            break;
        }

        prev == nullptr ? (result = next) : (prev->m_pNext = next);
        prev = next;
    }

    return result;
}

void CObjectProxy::Merge(CVmMsg*& message, Json::Value& text)
{
    const auto pClass = message->GetRuntimeClass();
    if (!text.isString()) text = AnsiX(message->m_pVariableArea, CP_SHIFT_JIS, CP_UTF8);
    const auto ansi = AnsiX(text.asCString(), CP_UTF8, CP_GB18030);
    const auto size = pClass->m_nObjectSize + (ansi.length() + 0x04 & ~0x03);
    const auto clone = static_cast<CVmMsg*>(malloc(size));
    memcpy(clone, message, pClass->m_nObjectSize); // NOLINT(*-undefined-memory-manipulation)
    memcpy(clone->m_pVariableArea, ansi.c_str(), ansi.length() + 0x04 & ~0x03);
    message = clone;
}

void CObjectProxy::Merge(CVmGenericMsg*& generic, Json::Value& obj)
{
    const auto pClass = generic->GetRuntimeClass();
    if (!obj.isObject()) obj = Json::Value(Json::objectValue);
    obj["#type"] = AnsiX(generic->m_pMsg->m_pRTC->m_lpszClassName, CP_SHIFT_JIS, CP_UTF8);
    const auto size = pClass->m_nObjectSize + generic->GetVariableAreaSize();
    const auto clone = static_cast<CVmGenericMsg*>(malloc(size));
    memcpy(clone, generic, size); // NOLINT(*-undefined-memory-manipulation)
    generic = clone;

    const auto params = generic->m_pMsg->m_pRTC->m_pParams;
    if (params == nullptr) return;
    auto map = std::map<std::wstring, CMemberInfo*>();
    for (auto member = params; member->m_lpszName != nullptr; member++)
    {
        map[UnicodeX(member->m_lpszName, CP_SHIFT_JIS)] = member;
        const auto key = AnsiX(member->m_lpszName, CP_SHIFT_JIS, CP_UTF8) + ":" +
            AnsiX(member->m_pRTC->m_lpszClassName, CP_SHIFT_JIS, CP_UTF8);
        const auto address = reinterpret_cast<DWORD>(generic->m_pMsg) + member->m_dwOffset;
        switch (*reinterpret_cast<const DWORD*>(member->m_pRTC->m_lpszClassName))
        {
        // 文字列
        case 0x9A8EB695u:
        // _CString
        case 0x7453435Fu:
            {
                auto& content = *reinterpret_cast<CStringX*>(address);
                obj[key] = AnsiX(content, CP_SHIFT_JIS, CP_UTF8);
                content = AnsiX(content, CP_SHIFT_JIS, CP_GB18030).c_str();
            }
            break;
        // フラグ
        case 0x89837483u:
        // _bool
        case 0x6F6F625Fu:
            obj[key] = *reinterpret_cast<bool*>(address);
            break;
        // １文字
        case 0xB6955082u:
        // _char
        case 0x6168635Fu:
            obj[key] = *reinterpret_cast<char*>(address);
            break;
        // バイト
        case 0x43836F83u:
        // _BYTE
        case 0x5459425Fu:
            obj[key] = *reinterpret_cast<BYTE*>(address);
            break;
        // 短整数
        case 0xAE905A92u:
        // _short
        case 0x6F68735Fu:
            obj[key] = *reinterpret_cast<short*>(address);
            break;
        // 短正整数
        case 0xB3905A92u:
        // _USHORT
        case 0x4853555Fu:
        // _WORD
        case 0x524F575Fu:
            obj[key] = *reinterpret_cast<USHORT*>(address);
            break;
        // 整数
        case 0x9490AE90u:
        // _int
        case 0x746E695Fu:
            obj[key] = *reinterpret_cast<int*>(address);
            break;
        // 正整数
        case 0xAE90B390u:
        // _UINT
        case 0x4E49555Fu:
            obj[key] = *reinterpret_cast<UINT*>(address);
            break;
        // 低精度実数
        case 0xB890E192u:
        // _float
        case 0x6F6C665Fu:
            obj[key] = *reinterpret_cast<float*>(address);
            break;
        // 倍精度実数
        case 0xB8907B94u:
        // _double
        case 0x756F645Fu:
            obj[key] = *reinterpret_cast<double*>(address);
            break;
        // 色
        case 0x00004690u:
        // _VCOLOR
        case 0x4F43565Fu:
            obj[key] = fmt::format("#{:08X}", *reinterpret_cast<DWORD*>(address));
            break;
        // 仮想マシン汎用値
        case 0x7A91BC89u:
        // 基本汎用値
        case 0x7B96EE8Au:
        // _CVmVar
        case 0x6D56435Fu:
            // if (strcmp(member->m_pRTC->m_lpszClassName, "_CVmVar64") == 0) __debugbreak();
            obj[key] = static_cast<LPCSTR>(reinterpret_cast<CVmVar*>(address)->ToSerialString());
            break;
        default:
            if (member->m_pRTC->m_nObjectSize > sizeof(DWORD))
            {
                const auto node = *reinterpret_cast<COceanNode**>(address);
                obj[key] = AnsiX(GetUUID(node).c_str(), CP_UTF8);
                // TODO expand
                // om[key] = Json::Value(Json::objectValue);
                // om[key]["#type"] = AnsiX(node->m_pRTC->m_lpszClassName, CP_SHIFT_JIS, CP_UTF8);
                break;
            }
            __debugbreak();
            obj[key] = Json::Value(Json::nullValue);
            break;
        }
    }
}

void CObjectProxy::Merge(CVmCall*& call, Json::Value& arr)
{
    const auto pClass = call->GetRuntimeClass();
    if (!arr.isArray()) arr = Json::Value(Json::arrayValue);
    const auto size = pClass->m_nObjectSize + call->GetVariableAreaSize();
    const auto clone = static_cast<CVmCall*>(malloc(size));
    memcpy(clone, call, size); // NOLINT(*-undefined-memory-manipulation)
    call = clone;

    arr[0] = AnsiX(GetUUID(call->m_refRsa.m_pNode).c_str(), CP_UTF8);
    if (call->m_nCount == 0) return;
    const auto block_size = call->GetVariableAreaSize() / call->m_nCount;
    for (auto i = 0; i < call->m_nCount; i++)
    {
        auto& param = *reinterpret_cast<CVmVar*>(call->m_pVariableArea + i * block_size);
        if (param.m_pValue == NULL) __debugbreak();
        arr[i + 1] = AnsiX(param.ToSerialString(), CP_SHIFT_JIS, CP_UTF8);
        if ((param.m_pValue & 0x03) != 0x01) continue;
        auto temp = reinterpret_cast<LPCSTR>(param.m_pValue ^ 0x01);
        auto& str = *reinterpret_cast<CStringX*>(&temp);
        str = AnsiX(str, CP_SHIFT_JIS, CP_ACP).c_str();
    }
}

void CObjectProxy::HookSupportRio(AFX_EXTENSION_MODULE& module)
{
    CRio::FetchLibrarySupport()(module);
    MODULE_MAP[module.hModule] = &module;
}

void CObjectProxy::HookDestructor(CRio* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = UnicodeX(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    wprintf(L"Hook %s::~%s(this=%s)\n", name.c_str(), name.c_str(), uuid.c_str());

    auto cache = COMMAND_MAP[uuid];
    COMMAND_MAP[uuid] = nullptr;
    while (cache != nullptr)
    {
        const auto command = cache;
        cache = cache->m_pNext;
        free(command);
    }

    return ecx->FetchDestructor()(ecx);
}

void CObjectProxy::HookSerialize(CRio* const ecx, CPmArchive* const archive)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = UnicodeX(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    if (ecx->m_pNode->m_dwResAddr == 0x00000000) return ecx->FetchSerialize()(ecx, archive);
    wprintf(L"Hook %s::Serialize(this=%s)\n", name.c_str(), uuid.c_str());

    const auto path = GetPatchFilePath(ecx->m_pNode);
    const auto hFile = CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        const auto ansi = AnsiX(path.c_str(), CP_ACP);
        const auto load = CPmArchive::CreateLoadFilePmArchive(ansi.c_str());
        ecx->FetchSerialize()(ecx, load);
        CPmArchive::DestroyPmArchive(load);
    }
    else
    {
        ecx->FetchSerialize()(ecx, archive);
        const auto ansi = AnsiX(path.c_str(), CP_ACP);
        const auto save = CPmArchive::CreateSaveFilePmArchive(ansi.c_str());
        ecx->FetchSerialize()(ecx, save);
        CPmArchive::DestroyPmArchive(save);
    }
}

CVmCommand* CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    auto& cache = COMMAND_MAP[uuid];
    if (cache != nullptr) return cache;
    const auto name = UnicodeX(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    wprintf(L"Hook %s::GetNextCommand(this=%s)\n", name.c_str(), uuid.c_str());
    const auto value = ecx->GetNextCommand();

    const auto path = GetPatchFilePath(ecx->m_pNode) + L".json";
    const auto hFile = CreateFileW(
        path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        nullptr,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (hFile == INVALID_HANDLE_VALUE) return value;
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        const auto size = GetFileSize(hFile, nullptr);
        const auto buffer = static_cast<char*>(malloc(size));
        ReadFile(hFile, buffer, size, nullptr, nullptr);
        CloseHandle(hFile);
        const auto document = std::string(buffer);
        free(buffer);
        auto reader = Json::Reader();
        auto patch = Json::Value(Json::objectValue);
        reader.parse(document, patch, false);
        cache = Fetch(value, patch);
    }
    else
    {
        auto patch = Json::Value(Json::objectValue);
        cache = Fetch(value, patch);
        auto writer = Json::FastWriter();
        const auto text = writer.write(patch);
        WriteFile(hFile, text.c_str(), text.length(), nullptr, nullptr);
        CloseHandle(hFile);
    }

    return cache;
}

CStringX* CObjectProxy::HookGetLocalFullPathName(const COceanNode* node, CStringX* x)
{
    if (node->m_strName[0x01] == ':' && node->m_pRTC == CObjectArcMan::GetClassCObjectArcMan())
    {
        const auto path = fmt::format(
            ".\\{}\\{}",
            AnsiX(GetGameName().c_str(), CP_ACP),
            strrchr(const_cast<COceanNode*>(node)->m_strName, '\\') + 1);
        CopyFileA(node->m_strName, path.c_str(), true);
        const_cast<COceanNode*>(node)->m_strName = path.c_str();
    }
    COceanNode::FetchGetLocalFullPathName()(node, x);
    return x;
}

BOOL CObjectProxy::HookIsMBCS(CHAR const c)
{
    return (c & 0x80u) == 0x80u;
}

int CObjectProxy::HookDrawFont1(
    CS5i::Part* const ecx, // NOLINT(*-misplaced-const)
    SHORT const x, SHORT const y, WORD* const rect, WORD* const out, UINT uChar, CFontContext* const context)
{
    // const auto& s5i = reinterpret_cast<CS5i&>(*ecx);
    if ((uChar & 0xFF00u) != 0x0000u && (uChar & 0x00FFu) <= 0x0039u) uChar = CHARACTER_MAP[uChar];
    if (uChar != '\0') return CS5i::FetchDrawFont1()(ecx, x, y, rect, out, uChar, context);
    return 0;
}

LPINT CObjectProxy::HookDrawFont2(
    CS5i::Part* const ecx, LPINT const width, // NOLINT(*-misplaced-const)
    SHORT const x, SHORT const y, WORD* const rect, WORD* const out, UINT uChar, CFontContext* const context)
{
    // const auto& s5i = reinterpret_cast<CS5i&>(*ecx);
    if ((uChar & 0xFF00u) != 0x0000u && (uChar & 0x00FFu) <= 0x0039u) uChar = CHARACTER_MAP[uChar];
    if (uChar != '\0') return CS5i::FetchDrawFont2()(ecx, width, x, y, rect, out, uChar, context);
    *width = 0;
    return width;
}

LPVOID CObjectProxy::HookGetCachedFont(CS5RFont* ecx, UINT uChar, COceanNode* const node)
{
    if ((uChar & 0xFF00u) != 0x0000u && (uChar & 0x00FFu) <= 0x0039u) uChar = CHARACTER_MAP[uChar];
    if (uChar <= 0xFFFFu) return ecx->GetCachedFont(uChar, node);
    auto& font = FONT_CACHE[uChar];
    if (font == nullptr) font = ecx->CreateNewFont(uChar, node);
    return font;
}

void CObjectProxy::HookStep(CBootTracer* ecx, INT_PTR const index)
{
    wprintf(L"Hook CBootTracer::Step(index=%d)\n", index);
    switch (index)
    {
    case 6:
        if (UnicodeX(CUuiGlobals::GetGlobal()->m_strGameName, CP_ACP) != GetGameName()) __debugbreak();
        break;
    case 7:
        // To skip the installation check
        CUuiGlobals::GetGlobal()->m_nInstallType = 2;
        break;
    default:
        break;
    }
    return CUuiGlobals::FetchStep()(ecx, index);
}

UINT CObjectProxy::HookBeginProcess(CProcessOcean* ecx, CView* view)
{
    // for (const auto node : *const_cast<COceanNode*>(COceanNode::GetRoot()))
    // {
    //     if (node->m_pRTC->IsDerivedFrom(CCommandRef::GetClassCCommandRef()))
    //     {
    //         HookGetNextCommand(reinterpret_cast<CCommandRef*>(node->Fetch()));
    //     }
    // }
    return CProcessOcean::FetchBeginProcess()(ecx, view);
}

std::map<std::wstring, const CRuntimeClass*> CObjectProxy::RTC_MAP;

std::map<std::wstring, CVmCommand*> CObjectProxy::COMMAND_MAP;

std::map<HMODULE, const AFX_EXTENSION_MODULE*> CObjectProxy::MODULE_MAP;

std::map<LPVOID, CodePatchRecord*> CObjectProxy::PATCH_CACHE;

std::map<WORD, UINT> CObjectProxy::CHARACTER_MAP;

std::map<UINT, LPVOID> CObjectProxy::FONT_CACHE;
