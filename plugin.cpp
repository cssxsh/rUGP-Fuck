#include <stdafx.h>
#include <detours.h>
#include <cJSON.h>
#include <clocale>
#include <fstream>
#include "plugin.h"
#include "rugp.h"
#include "hook.h"

static BOOL CreateMergeDirectory();

static CVmCommand* __fastcall Merge(const CVmCommand* ecx, cJSON* edx);

static AFX_EXTENSION_MODULE R514783_PLUGIN = {FALSE, nullptr};

// ReSharper disable once CppParameterMayBeConst
BOOL WINAPI DllMain(HINSTANCE hInstance, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        SetConsoleTitleA("r514783 Plugin Debug Console");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        setlocale(LC_ALL, ".UTF8");
        freopen("CON", "w", stdout);

        wprintf(L"MFC Version %hs\n", GetMfcVersion());
        wprintf(L"rUGP System Version %hs\n", GetRugpVersion());
        wprintf(L"cJSON Version %hs\n", cJSON_Version());
        wprintf(L"Detours Version %x\n", DETOURS_VERSION);
        wprintf(L"\n");
        wprintf(L"CommandLine %s\n", GetCommandLineW());
        wprintf(L"\n");

        AfxInitExtensionModule(R514783_PLUGIN, hInstance);

        CObjectProxy::LoadFromModule("UnivUI");
        CObjectProxy::LoadFromModule("rvmm");
        CObjectProxy::LoadFromModule("Vm60");

        __try
        {
            CreateMergeDirectory();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"CreateMergeDirectory Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            Win32Hook::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"Win32Hook::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            CObjectProxy::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"CObjectProxy::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            COceanTree::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"COceanTreeIterator::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        break;
    case DLL_PROCESS_DETACH:
        __try
        {
            COceanTree::DetachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"COceanTreeIterator::DetachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            CObjectProxy::DetachHook();
            CObjectProxy::Clear();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"CObjectProxy::DetachHook: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            Win32Hook::DetachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            wprintf(L"Win32Hook::DetachHook Fail: 0x%08X\n\n", GetExceptionCode());
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

LPCSTR WINAPIV GetPluginString(const DWORD /*param1*/, const DWORD /*param2*/)
{
    return "Fuck rUGP! Version 0.1.0\r\n"
        "\tThis is unofficial plugin.\r\n"
        "\t(c)2024-2025 CssXsh All rights reserved.\r\n"
        "\r\n";
}

std::wstring GetUUID(const COceanNode* const node)
{
    wchar_t buffer[MAX_PATH];
    const auto name = Unicode(node->m_pRTC ? node->m_pRTC->m_lpszClassName : nullptr, CP_SHIFT_JIS);
    swprintf(buffer, MAX_PATH, L"%s@%08X", name, node->GetAddress());
    free(name);
    return buffer;
}

std::wstring GetFilePath(const COceanNode* const node)
{
    wchar_t buffer[MAX_PATH];
    const auto format = Unicode(node->m_pRTC ? node->m_pRTC->m_lpszClassName : "bin", CP_SHIFT_JIS);
    const auto suffix = format[0] == L'C' ? format + 1 : format;
    for (auto c = suffix; *c != L'\0'; c++) *c = towlower(*c);
    swprintf(buffer, MAX_PATH, L"./%s/%08X.%s", GetGameName().c_str(), node->GetAddress(), suffix);
    free(format);
    return buffer;
}

std::wstring GetGameName()
{
    const auto command = GetCommandLineW();
    const auto l = wcsrchr(command, '\\') + 1;
    const auto r = wcschr(l, '}');
    return {l, r};
}

template <typename F>
void CALLBACK DetourAttachCallback(F& from, const F to)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&reinterpret_cast<PVOID&>(from), reinterpret_cast<PVOID>(to));
    DetourTransactionCommit();
}

template <typename F>
void CALLBACK DetourDetachCallback(F& from, const F to)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&reinterpret_cast<PVOID&>(from), reinterpret_cast<PVOID>(to));
    DetourTransactionCommit();
}

BOOL CreateMergeDirectory()
{
    const auto name = GetGameName();
    return CreateDirectoryW(name.c_str(), nullptr);
}

CVmCommand* __fastcall Merge(const CVmCommand* const ecx, cJSON* const edx) // NOLINT(*-no-recursion)
{
    const auto pClassCVmMsg = CVmMsg::GetClassCVmMsg();
    auto result = static_cast<CVmCommand*>(nullptr);
    auto prev = static_cast<CVmCommand*>(nullptr);
    auto next = static_cast<CVmCommand*>(nullptr);
    for (auto command = ecx; command != nullptr; command = command->m_pNext)
    {
        char name[MAX_PATH];
        sprintf(name, "%08X:%s", command->m_dwFlags & 0x000FFFFF, command->GetRuntimeClass()->m_lpszClassName);
        switch (*reinterpret_cast<const DWORD*>(command->GetRuntimeClass()->m_lpszClassName))
        {
        case 0x4D6D5643u: // CVmMsg
            if (command->GetRuntimeClass() != pClassCVmMsg) continue;
            {
                auto text = cJSON_GetObjectItem(edx, name);
                if (cJSON_IsString(text))
                {
                    const auto value = cJSON_GetStringValue(text, CP_SHIFT_JIS);
                    // const auto value = cJSON_GetStringValue(text, CP_GB2312);
                    const auto size = pClassCVmMsg->m_nObjectSize + (strlen(value) + 0x04 & ~0x03);
                    const auto clone = static_cast<CVmMsg*>(malloc(size));
                    memcpy(clone, command, pClassCVmMsg->m_nObjectSize); // NOLINT(*-undefined-memory-manipulation)
                    memcpy(clone->m_area, value, strlen(value) + 0x04 & ~0x03);
                    cJSON_free(value);
                    next = clone;
                }
                else
                {
                    const auto message = reinterpret_cast<const CVmMsg*>(command);
                    text = cJSON_CreateString(message->m_area, CP_SHIFT_JIS);
                    cJSON_AddItemToObject(edx, name, text);
                    const auto size = pClassCVmMsg->m_nObjectSize + (strlen(message->m_area) + 0x04 & ~0x03);
                    // const auto unicode = Unicode(message->m_area, CP_SHIFT_JIS);
                    // const auto ansi = Ansi(unicode, CP_GB2312);
                    // const auto size = pClassCVmMsg->m_nObjectSize + (strlen(ansi) + 0x04 & ~0x03);
                    const auto clone = static_cast<CVmMsg*>(malloc(size));
                    memcpy(clone, message, size); // NOLINT(*-undefined-memory-manipulation)
                    // free(ansi);
                    // free(unicode);
                    next = clone;
                }
            }
            break;
        default:
            {
                cJSON_AddItemToObject(edx, name, cJSON_CreateNull());
                const auto size = command->GetRuntimeClass()->m_nObjectSize + command->GetVariableAreaSize();
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

CObjectProxy::CObjectProxy(const CRuntimeClass* const pClass)
{
    m_pClass = pClass;
    m_pfnCreateObject = m_pClass->m_pfnCreateObject;
    if (m_pfnCreateObject == nullptr) return;
    m_pVTBL = FindVirtualTable(m_pClass, reinterpret_cast<FARPROC>(m_pfnCreateObject));
    if (m_pVTBL == nullptr) return;
    if (strcmp(m_pClass->m_lpszClassName, "CResourceClipOnlyRegion") == 0) return;

    const auto mfc = GetMfc();
    if (pClass->IsDerivedFrom(CCommandRef::GetClassCCommandRef()))
    {
        const auto vtbl = reinterpret_cast<const FARPROC*>(m_pVTBL);
        switch (mfc.version)
        {
        case 0x0600:
            m_pfnGetNextCommand = reinterpret_cast<CVmCommand*(__thiscall *)(CCommandRef*)>(vtbl[0x000B]);
            break;
        case 0x0C00:
            m_pfnGetNextCommand = reinterpret_cast<CVmCommand*(__thiscall *)(CCommandRef*)>(vtbl[0x000C]);
        default:
            // TODO ?GetNextCommand@CCommandRef@@UBEPAVCVmCommand@@XZ
            m_pfnGetNextCommand = nullptr;
            break;
        }
        //
        const auto start = reinterpret_cast<DWORD>(m_pVTBL->Destructor);
        for (auto offset = start; offset - start < 0x0400; offset++)
        {
            // mov     ecx, ...
            if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
            // call    ...
            if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
            const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
            const auto next = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
            if (IsBadCodePtr(next)) continue;
            m_pfnDestructor = reinterpret_cast<void(__thiscall *)(CRio*)>(next);
            break;
        }
    }

    if (pClass->IsDerivedFrom(CRip::GetClassCRip()))
    {
        m_pfnSerialize = reinterpret_cast<const CObjectEx_vtbl*>(m_pVTBL)->Serialize;
    }
}

BOOL CObjectProxy::LoadFromModule(LPCSTR const lpszModuleName)
{
    const auto hModule = GetModuleHandleA(lpszModuleName);
    if (hModule == nullptr) return FALSE;
    const auto proc = GetProcAddress(hModule, "PluginThisLibrary");
    if (proc == nullptr) return FALSE;

    MODULE_MAP[hModule] = nullptr;
    CRio::HookLibrarySupport(DetourAttachCallback<CRio::REG>, HookSupportRio);
    auto module = reinterpret_cast<const AFX_EXTENSION_MODULE*>(proc());
    CRio::HookLibrarySupport(DetourDetachCallback<CRio::REG>, HookSupportRio);
    if (MODULE_MAP[hModule] != nullptr) module = MODULE_MAP[hModule];
    else MODULE_MAP[hModule] = module;
    for (auto clazz = module->pFirstSharedClass; clazz != nullptr; clazz = clazz->m_pNextClass)
    {
        const auto name = Unicode(clazz->m_lpszClassName, CP_SHIFT_JIS);
        REF_MAP[name] = new CObjectProxy(clazz);
        free(name);
    }

    return TRUE;
}

void CObjectProxy::AttachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : REF_MAP)
    {
        const auto ref = pair.second;
        const auto name = Unicode(ref->m_pClass->m_lpszClassName, CP_SHIFT_JIS);

        if (ref->m_pfnGetNextCommand != nullptr)
        {
            wprintf(L"DetourAttach: %s::GetNextCommand\n", name);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
            wprintf(L"DetourAttach: %s::~%s\n", name, name);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnDestructor), HookDestructor);
        }

        if (ref->m_pfnSerialize != nullptr)
        {
            wprintf(L"DetourAttach: %s::Serialize\n", name);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnSerialize), HookSerialize);
        }

        free(name);
    }
    DetourTransactionCommit();

    // wprintf(L"DetourAttach: CS5i::DrawSzText\n");
    // CS5i::HookDrawSzText(AttachDetourHook<CS5i::LPDrawSzText>, HookDrawSzText);
    // wprintf(L"DetourAttach: CS5i::DrawSzTextClip\n");
    // CS5i::HookDrawSzTextClip(AttachDetourHook<CS5i::LPDrawSzTextClip>, HookDrawSzTextClip);

    // wprintf(L"DetourAttach: CImgBox::DrawSzText\n");
    // CImgBox::HookDrawSzText(AttachDetourHook<CImgBox::LPDrawSzText>, HookDrawSzText);

    wprintf(L"DetourAttach: CMessBox::AttachTextCore\n");
    CMessBox::HookAttachTextCore(DetourAttachCallback<FARPROC>, reinterpret_cast<FARPROC>(HookCharacterByteSize));
}

void CObjectProxy::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : REF_MAP)
    {
        const auto ref = pair.second;
        const auto name = Unicode(ref->m_pClass->m_lpszClassName, CP_SHIFT_JIS);

        if (ref->m_pfnGetNextCommand != nullptr)
        {
            wprintf(L"DetourDetach: %s::GetNextCommand\n", name);
            DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
            wprintf(L"DetourDetach: %s::~%s\n", name, name);
            DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnDestructor), HookDestructor);
        }

        if (ref->m_pfnSerialize != nullptr)
        {
            wprintf(L"DetourDetach: %s::Serialize\n", name);
            DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnSerialize), HookSerialize);
        }

        free(name);
    }
    DetourTransactionCommit();
}

const CObject_vtbl* CObjectProxy::FindVirtualTable( // NOLINT(*-no-recursion)
    const CRuntimeClass* const rtc, FARPROC const ctor) // NOLINT(*-misplaced-const)
{
    if (IsBadCodePtr(ctor)) return nullptr;
    const auto module = DetourGetContainingModule(const_cast<CRuntimeClass*>(rtc));
    if (DetourGetContainingModule(ctor) != module) return nullptr;
    const auto start = reinterpret_cast<DWORD>(ctor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     dword ptr [*], ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0xC7) continue;
        const auto address = *reinterpret_cast<const CObject_vtbl* const*>(offset + 0x02);
        if (IsBadReadPtr(address, sizeof(CObject_vtbl))) continue;
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(address->GetRuntimeClass))) continue;
        const auto get = reinterpret_cast<DWORD>(address->GetRuntimeClass);
        // mov     eax, ...
        const auto clazz = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
        if (rtc == clazz) return address;
    }
    if (ctor != reinterpret_cast<FARPROC>(rtc->m_pfnCreateObject)) return nullptr;
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
        // call    ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
        const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
        const auto next = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        const auto vtbl = FindVirtualTable(rtc, next);
        if (vtbl != nullptr) return vtbl;
    }

    return nullptr;
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

    for (auto& pair : REF_MAP)
    {
        const auto p = pair.second;
        pair.second = nullptr;
        delete p;
    }
    REF_MAP.clear();
}

void CObjectProxy::HookSupportRio(AFX_EXTENSION_MODULE& module)
{
    CRio::LibrarySupport(module);
    MODULE_MAP[DetourGetContainingModule(&module)] = &module;
}

void CObjectProxy::HookDestructor(CRio* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = Unicode(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    const auto ref = REF_MAP[name];
    wprintf(L"Hook %s::~%s(this=%s)\n", name, name, uuid.c_str());
    free(name);

    auto cache = COMMAND_MAP[uuid];
    COMMAND_MAP[uuid] = nullptr;
    while (cache != nullptr)
    {
        const auto command = cache;
        cache = cache->m_pNext;
        free(command);
    }

    return ref->m_pfnDestructor(ecx);
}

void CObjectProxy::HookSerialize(CVisual* const ecx, CPmArchive* const archive)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = Unicode(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    const auto ref = REF_MAP[name];
    wprintf(L"Hook %s::Serialize(this=%s, file=0x%p)\n", name, uuid.c_str(), archive->GetNative()->GetFile()->m_hFile);
    free(name);
    if (ecx->m_pNode->m_dwResAddr == 0x00000000) return ref->m_pfnSerialize(ecx, archive);

    const auto path = GetFilePath(ecx->m_pNode);
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
        const auto ansi = Ansi(path.c_str(), CP_ACP);
        const auto load = CPmArchive::CreateLoadFilePmArchive(ansi);
        free(ansi);
        ref->m_pfnSerialize(ecx, load);
        CPmArchive::DestroyPmArchive(load);
    }
    else
    {
        ref->m_pfnSerialize(ecx, archive);
        const auto ansi = Ansi(path.c_str(), CP_ACP);
        const auto save = CPmArchive::CreateSaveFilePmArchive(ansi);
        free(ansi);
        ref->m_pfnSerialize(ecx, save);
        CPmArchive::DestroyPmArchive(save);
    }
}

CVmCommand* CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto cache = COMMAND_MAP[uuid];
    if (cache != nullptr) return cache;
    const auto name = Unicode(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    const auto ref = REF_MAP[name];
    wprintf(L"Hook %s::GetNextCommand(this=%s)\n", name, uuid.c_str());
    free(name);
    auto value = ref->m_pfnGetNextCommand(ecx);

    const auto path = GetFilePath(ecx->m_pNode) + L".json";
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
        const auto patch = cJSON_ParseWithLength(buffer, size);
        value = Merge(value, patch);
        free(buffer);
        cJSON_free(patch);
    }
    else
    {
        const auto patch = cJSON_CreateObject();
        value = Merge(value, patch);
        const auto buffer = cJSON_Print(patch);
        WriteFile(hFile, buffer, strlen(buffer), nullptr, nullptr);
        CloseHandle(hFile);
        cJSON_free(buffer);
        cJSON_free(patch);
    }

    COMMAND_MAP[uuid] = value;

    return value;
}

void CObjectProxy::HookDrawSzText(
    CS5i* const ecx, DWORD const x0, DWORD const y0, LPCSTR const text, COceanNode** const context)
{
    WORD body[4];
    body[0] = *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>(ecx) + 0x24);
    body[1] = *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>(ecx) + 0x26);
    body[2] = *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>(ecx) + 0x28);
    body[3] = *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>(ecx) + 0x2A);

    HookDrawSzTextClip(ecx, x0, y0, text, context, body);
}

void CObjectProxy::HookDrawSzTextClip(
    CS5i* const ecx, DWORD const x0, DWORD const y0, LPCSTR const text, COceanNode** const context, WORD* const body)
{
    auto x = x0;
    auto y = y0;
    for (auto ptr = text; *ptr != '\0'; ++ptr)
    {
        auto uChar = static_cast<UINT>(*ptr); // NOLINT(*-str34-c)
        if (uChar == '\n')
        {
            x = x0;
            y += *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>((*context)->Fetch()) + 0x60);
        }
        else
        {
            if (uChar >= 0xC0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xE0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xF0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xF8u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xFCu) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            WORD temp[2];
            x += ecx->DrawFont(x, y, body, temp, uChar, context);
        }
    }
}

void CObjectProxy::HookDrawSzText(
    CImgBox* const ecx, DWORD const x0, DWORD const y0, LPCSTR const text, COceanNode** const context)
{
    auto x = x0;
    auto y = y0;
    for (auto ptr = text; *ptr != '\0'; ++ptr)
    {
        auto uChar = static_cast<UINT>(*ptr); // NOLINT(*-str34-c)
        if (uChar == '\n')
        {
            x = x0;
            y += *reinterpret_cast<WORD*>(reinterpret_cast<DWORD>((*context)->Fetch()) + 0x60);
        }
        else
        {
            if (uChar >= 0xC0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xE0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xF0u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xF8u) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            if (uChar >= 0xFCu) uChar = (uChar << 0x08) | reinterpret_cast<UINT>(++ptr);
            x += ecx->DrawFont(x, y, uChar, context);
        }
    }
}

int CObjectProxy::HookCharacterByteSize(
    CRio* const ecx, LPCSTR const text)
{
    // if ((text[0x0000] & 0x80) == 0x00) return 1;
    // if ((text[0x0000] & 0xE0) == 0xC0) return 2;
    // if ((text[0x0000] & 0xF0) == 0xE0) return 3;
    // if ((text[0x0000] & 0xF8) == 0xF0) return 4;
    // const auto unicode = Unicode(text, CP_SHIFT_JIS);
    // free(unicode);
    return (text[0x0000] ^ 0x20) + 0x5F <= 0x3Bu ? 0x02 : 0x01;
}

std::map<std::wstring, CObjectProxy*> CObjectProxy::REF_MAP;

std::map<std::wstring, CVmCommand*> CObjectProxy::COMMAND_MAP;

std::map<HMODULE, const AFX_EXTENSION_MODULE*> CObjectProxy::MODULE_MAP;

void COceanTree::AttachHook()
{
    COceanNode::HookGetMotherOcean(DetourAttachCallback<COceanNode::GET>, HookGetMotherOcean);
}

void COceanTree::DetachHook()
{
    COceanNode::HookGetMotherOcean(DetourDetachCallback<COceanNode::GET>, HookGetMotherOcean);
}

COceanNode** COceanTree::HookGetMotherOcean(COceanNode** pNode)
{
    wprintf(L"Hook GetMotherOcean()\n");
    *pNode = const_cast<COceanNode*>(COceanNode::GetMotherOcean());
    const auto root = *pNode;
    auto iterator = Iterator(root);
    for (auto node = iterator.Next(); node != nullptr; node = iterator.Next())
    {
        // TODO ...
    }

    return pNode;
}

COceanTree::Iterator::Iterator(const COceanNode* const root)
{
    m_pNode = root;
    m_nLevel = root ? 1 : 0;
}

DWORD COceanTree::Iterator::Level() const
{
    return m_nLevel;
}

const COceanNode* COceanTree::Iterator::Next()
{
    const auto node = m_pNode;
    if (node == nullptr) return nullptr;
    constexpr auto empty = COceanNode::Children();
    const auto null = COceanNode::GetNull();

    for (auto root = m_pNode; root && m_nLevel; root = root->m_pParent, m_nLevel--)
    {
        auto mask = static_cast<WORD>(0x0000);
        const auto visited = m_pVisited[root];

        mask = static_cast<WORD>(0x0001);
        for (const auto child : (root->m_pChildren ? root->m_pChildren : &empty)->m_pBucket)
        {
            if (child == nullptr) continue;
            if (child == null) continue;
            mask <<= 0x01;
            if (visited & mask) continue;
            m_pNode = child;
            m_nLevel++;
            m_pVisited[root] = visited | mask;

            return node;
        }

        if (root->m_pNext == nullptr) continue;
        if (root->m_pNext == null) continue;
        mask = static_cast<WORD>(0x8000);
        if (visited & mask) continue;
        m_pNode = root->m_pNext;
        m_pVisited[root] = visited | mask;

        return node;
    }

    m_pNode = nullptr;
    m_nLevel = 0;
    return nullptr;
}
