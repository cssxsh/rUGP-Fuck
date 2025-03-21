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

        printf("MFC Version %s\n", GetMfcVersion());
        printf("rUGP System Version %s\n", GetRugpVersion());
        printf("cJSON Version %s\n", cJSON_Version());
        printf("Detours Version %x\n", DETOURS_VERSION);
        printf("\n");
        wprintf(L"CommandLine %s\n", GetCommandLineW());
        printf("\n");

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
            printf("CreateMergeDirectory Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            Win32Hook::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Win32Hook::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            CObjectProxy::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("CObjectProxy::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            COceanTreeIterator::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("COceanTreeIterator::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        break;
    case DLL_PROCESS_DETACH:
        __try
        {
            COceanTreeIterator::DetachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("COceanTreeIterator::DetachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            CObjectProxy::DetachHook();
            CObjectProxy::Clear();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("CObjectProxy::DetachHook: 0x%08X\n\n", GetExceptionCode());
        }

        __try
        {
            Win32Hook::DetachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Win32Hook::DetachHook Fail: 0x%08X\n\n", GetExceptionCode());
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
                    const auto clone = static_cast<CVmMsg*>(malloc(size));
                    memcpy(clone, message, size); // NOLINT(*-undefined-memory-manipulation)
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
    if (std::strcmp(m_pClass->m_lpszClassName, "CResourceClipOnlyRegion") == 0) return;

    const auto mfc = GetMfc();
    for (auto clazz = pClass;
         clazz != nullptr;
         clazz = clazz->m_pfnGetBaseClass ? clazz->m_pfnGetBaseClass() : nullptr)
    {
        switch (*reinterpret_cast<const DWORD*>(clazz->m_lpszClassName))
        {
        case 0x6D6F4343u: // CCommandRef
            if (clazz != CCommandRef::GetClassCCommandRef()) continue;
            {
                auto vtbl = reinterpret_cast<DWORD>(m_pVTBL);
                switch (mfc.version)
                {
                case 0x0600:
                    vtbl += 0x002C;
                    break;
                case 0x0C00:
                    vtbl += 0x0030;
                    break;
                default:
                    break;
                }
                m_pfnGetNextCommand = reinterpret_cast<const CCommandRef_vtbl*>(vtbl)->GetNextCommand;
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
            return;
        case 0x73695643u: // CVisual
            if (clazz != CVisual::GetClassCVisual()) continue;
            {
                // CRip, CRip007, CRip008
                if (*reinterpret_cast<const DWORD*>(clazz->m_lpszClassName) != 0x6F695243u) continue;
                m_pfnSerialize = reinterpret_cast<const CVisual_vtbl*>(m_pVTBL)->Serialize;
            }
            return;
        default:
            break;
        }
    }
}

BOOL CObjectProxy::LoadFromModule(LPCSTR const lpszModuleName)
{
    const auto hModule = GetModuleHandleA(lpszModuleName);
    if (hModule == nullptr) return FALSE;
    const auto proc = GetProcAddress(hModule, "PluginThisLibrary");
    if (proc == nullptr) return FALSE;

    auto reg = GetProcAddress(hModule, "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z");
    if (reg != nullptr)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&reinterpret_cast<PVOID&>(reg), HookSupportRio);
        DetourTransactionCommit();
    }
    auto module = reinterpret_cast<const AFX_EXTENSION_MODULE*>(proc());
    if (reg != nullptr)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&reinterpret_cast<PVOID&>(reg), HookSupportRio);
        DetourTransactionCommit();
        module = TEMP_MODULE;
    }
    if (module == nullptr) return FALSE;
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
        if (ref->m_pfnGetNextCommand != nullptr)
        {
            printf("DetourAttach: %s::GetNextCommand\n", ref->m_pClass->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
            printf("DetourAttach: %s::~%s\n", ref->m_pClass->m_lpszClassName, ref->m_pClass->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnDestructor), HookDestructor);
        }

        if (ref->m_pfnSerialize != nullptr)
        {
            printf("DetourAttach: %s::Serialize\n", ref->m_pClass->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnSerialize), HookSerialize);
        }
    }
    DetourTransactionCommit();
}

void CObjectProxy::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : REF_MAP)
    {
        const auto ref = pair.second;
        if (ref->m_pfnGetNextCommand != nullptr)
        {
            printf("DetourDetach: %s::GetNextCommand\n", ref->m_pClass->m_lpszClassName);
            DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
        }

        if (ref->m_pfnSerialize != nullptr)
        {
            printf("DetourDetach: %s::Serialize\n", ref->m_pClass->m_lpszClassName);
            DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnSerialize), HookSerialize);
        }
    }
    DetourTransactionCommit();
}

const CObject_vtbl* __fastcall CObjectProxy::FindVirtualTable( // NOLINT(*-no-recursion)
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
    for (const auto& pair : COMMAND_MAP)
    {
        auto p = pair.second;
        while (p != nullptr)
        {
            const auto command = p;
            p = p->m_pNext;
            free(command);
        }
    }
    COMMAND_MAP.clear();

    for (const auto& pair : REF_MAP)
    {
        delete pair.second;
    }
    REF_MAP.clear();
}

void CObjectProxy::HookSupportRio(AFX_EXTENSION_MODULE& module)
{
    TEMP_MODULE = &module;
}

void CObjectProxy::HookDestructor(CRio* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = Unicode(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    const auto ref = REF_MAP[name];
    wprintf(L"Hook %s::~%s(this=%s)\n", name, name, uuid.c_str());
    free(name);

    auto cache = COMMAND_MAP[uuid];
    while (cache != nullptr)
    {
        const auto command = cache;
        cache = cache->m_pNext;
        free(command);
    }

    return ref->m_pfnDestructor(ecx);
}

void __thiscall CObjectProxy::HookSerialize(CVisual* const ecx, CPmArchive* const archive)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = Unicode(ecx->GetRuntimeClass()->m_lpszClassName, CP_SHIFT_JIS);
    const auto ref = REF_MAP[name];
    wprintf(L"Hook %s::Serialize(this=%s)\n", name, uuid.c_str());
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

CVmCommand* __thiscall CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
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

std::map<std::wstring, CObjectProxy*> CObjectProxy::REF_MAP;

std::map<std::wstring, CVmCommand*> CObjectProxy::COMMAND_MAP;

AFX_EXTENSION_MODULE* CObjectProxy::TEMP_MODULE;

COceanTreeIterator::COceanTreeIterator(const COceanNode* const root)
{
    m_pNode = root;
    m_nLevel = root ? 1 : 0;
}

DWORD COceanTreeIterator::Level() const
{
    return m_nLevel;
}

const COceanNode* COceanTreeIterator::Next()
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

void COceanTreeIterator::AttachHook()
{
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
            const auto UnivUI = GetModuleHandleA("UnivUI");
            GetMotherOcean = reinterpret_cast<LPGetMotherOcean>(GetProcAddress(UnivUI, name));
            if (GetMotherOcean != nullptr) break;
            GetMotherOcean = reinterpret_cast<LPGetMotherOcean>(GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (GetMotherOcean != nullptr) break;
        }
        return;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean,class CObjectOcean_ome,class TObjectOcean> __cdecl GetMotherOcean(void)
        return;
    default:
        break;
    }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&reinterpret_cast<PVOID&>(GetMotherOcean), reinterpret_cast<PVOID>(GetMotherOceanHook));
    DetourTransactionCommit();
}

void COceanTreeIterator::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&reinterpret_cast<PVOID&>(GetMotherOcean), reinterpret_cast<PVOID>(GetMotherOceanHook));
    DetourTransactionCommit();

    GetMotherOcean = nullptr;
}

COceanTreeIterator::LPGetMotherOcean COceanTreeIterator::GetMotherOcean = nullptr;

COceanNode** __cdecl COceanTreeIterator::GetMotherOceanHook(COceanNode** const pNode)
{
    GetMotherOcean(pNode);
    const auto root = *pNode;
    auto iterator = COceanTreeIterator(root);
    for (auto node = iterator.Next(); node != nullptr; node = iterator.Next())
    {
        // TODO ...
    }

    return pNode;
}
