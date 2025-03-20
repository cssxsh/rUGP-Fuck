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

std::string GetUUID(const COceanNode* node)
{
    char buffer[MAX_PATH];
    sprintf(buffer, "%s@%08X", node->m_pRTC ? node->m_pRTC->m_lpszClassName : nullptr, node->GetAddress());
    return buffer;
}

std::string GetFilePath(const COceanNode* node)
{
    // TODO Folder
    char buffer[MAX_PATH];
    sprintf(buffer, "./%s/%08X.%s", GetGameName().c_str(), node->GetAddress(),
            node->m_pRTC ? node->m_pRTC->m_lpszClassName : "bin");
    return buffer;
}

std::string GetGameName()
{
    const auto command = GetCommandLineA();
    const auto l = strrchr(command, '\\') + 1;
    const auto r = strchr(l, '}');
    const auto count = static_cast<std::string::size_type>(reinterpret_cast<DWORD>(r) - reinterpret_cast<DWORD>(l));
    return {l, count};
}

BOOL CreateMergeDirectory()
{
    const auto name = GetGameName();
    return CreateDirectoryA(name.c_str(), nullptr);
}

CVmCommand* __fastcall Merge(const CVmCommand* ecx, cJSON* edx) // NOLINT(*-no-recursion)
{
    const auto pClassCVmMsg = CVmMsg::GetClassCVmMsg();
    auto result = static_cast<CVmCommand*>(nullptr);
    char name[MAX_PATH];
    sprintf(name, "%08X:%s", ecx->m_dwFlags & 0x000FFFFF, ecx->GetRuntimeClass()->m_lpszClassName);
    if (ecx->GetRuntimeClass() == pClassCVmMsg)
    {
        const auto message = reinterpret_cast<const CVmMsg*>(ecx);
        auto text = cJSON_GetObjectItem(edx, name);
        if (cJSON_IsString(text))
        {
            const auto value = cJSON_GetStringValue(text, CP_SHIFT_JIS);
            const auto size = pClassCVmMsg->m_nObjectSize + (strlen(value) + 0x04 & ~0x03);
            const auto clone = static_cast<CVmMsg*>(malloc(size));
            memcpy(clone, message, pClassCVmMsg->m_nObjectSize); // NOLINT(*-undefined-memory-manipulation)
            memcpy(clone->m_area, value, strlen(value) + 0x04 & ~0x03);
            cJSON_free(value);
            result = clone;
        }
        else
        {
            text = cJSON_CreateString(message->m_area, CP_SHIFT_JIS);
            cJSON_AddItemToObject(edx, name, text);
            const auto size = pClassCVmMsg->m_nObjectSize + (strlen(message->m_area) + 0x04 & ~0x03);
            const auto clone = static_cast<CVmMsg*>(malloc(size));
            memcpy(clone, message, size); // NOLINT(*-undefined-memory-manipulation)
            result = clone;
        }
    }
    else
    {
        cJSON_AddItemToObject(edx, name, cJSON_CreateNull());
        // TODO: size calc
        const auto size = ecx->m_pNext
                              ? reinterpret_cast<DWORD>(ecx->m_pNext) - reinterpret_cast<DWORD>(ecx)
                              : pClassCVmMsg->m_nObjectSize;
        const auto clone = static_cast<CVmMsg*>(malloc(size));
        memcpy(clone, ecx, size); // NOLINT(*-undefined-memory-manipulation)

        result = clone;
    }

    result->m_pNext = ecx->m_pNext ? Merge(ecx->m_pNext, edx) : nullptr;

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
        // printf("%s %08X\n", clazz->m_lpszClassName, *reinterpret_cast<const DWORD*>(clazz->m_lpszClassName));
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
            }
            return;
        case 0x73695643u: // CVisual
            if (clazz != CVisual::GetClassCVisual()) continue;
            {
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
        REF_MAP[clazz->m_lpszClassName] = new CObjectProxy(clazz);
    }

    return TRUE;
}

void CObjectProxy::AttachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (const auto& pair : REF_MAP)
    {
        if (pair.second->m_pfnGetNextCommand != nullptr)
        {
            printf("DetourAttach: %s::GetNextCommand\n", pair.second->m_pClass->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(pair.second->m_pfnGetNextCommand), HookGetNextCommand);
        }

        if (pair.second->m_pfnSerialize != nullptr)
        {
            switch (*reinterpret_cast<const DWORD*>(pair.second->m_pClass->m_lpszClassName))
            {
            case 0x70695243u: // CRip, CRip007, CRip008
                printf("DetourAttach: %s::Serialize\n", pair.second->m_pClass->m_lpszClassName);
                DetourAttach(&reinterpret_cast<PVOID&>(pair.second->m_pfnSerialize), HookSerialize);
                break;
            default:
                break;
            }
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
        if (pair.second->m_pfnGetNextCommand)
        {
            printf("DetourDetach: %s::GetNextCommand\n", pair.second->m_pClass->m_lpszClassName);
            DetourDetach(&reinterpret_cast<PVOID&>(pair.second->m_pfnGetNextCommand), HookGetNextCommand);
        }
    }
    DetourTransactionCommit();

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
}

const CObject_vtbl* __fastcall CObjectProxy::FindVirtualTable( // NOLINT(*-no-recursion)
    const CRuntimeClass* const rtc, const FARPROC ctor) // NOLINT(*-misplaced-const)
{
    if (IsBadCodePtr(ctor)) return nullptr;
    const auto module = DetourGetContainingModule(const_cast<CRuntimeClass*>(rtc));
    if (DetourGetContainingModule(ctor) != module) return nullptr;
    for (auto offset = reinterpret_cast<DWORD>(ctor); offset - reinterpret_cast<DWORD>(ctor) < 0x0400; offset++)
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
    for (auto offset = reinterpret_cast<DWORD>(ctor); offset - reinterpret_cast<DWORD>(ctor) < 0x0400; offset++)
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

void CObjectProxy::HookSupportRio(AFX_EXTENSION_MODULE& module)
{
    TEMP_MODULE = &module;
}

void __thiscall CObjectProxy::HookSerialize(CVisual* ecx, CPmArchive* archive)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
    printf("Hook %s::Serialize(this=%s)\n", name, uuid.c_str());

    const auto path = GetFilePath(ecx->m_pNode);
    const auto hFile = CreateFileA(
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
        const auto load = CPmArchive::CreateLoadFilePmArchive(path.c_str());
        REF_MAP[name]->m_pfnSerialize(ecx, load);
        CPmArchive::DestroyPmArchive(load);
    }
    else
    {
        REF_MAP[name]->m_pfnSerialize(ecx, archive);
        const auto save = CPmArchive::CreateSaveFilePmArchive(path.c_str());
        REF_MAP[name]->m_pfnSerialize(ecx, save);
        CPmArchive::DestroyPmArchive(save);
    }
}

CVmCommand* __thiscall CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
    printf("Hook %s::GetNextCommand(this=%s)\n", name, uuid.c_str());
    auto value = REF_MAP[name]->m_pfnGetNextCommand(ecx);

    const auto path = GetFilePath(ecx->m_pNode) + ".json";
    const auto hFile = CreateFileA(
        path.c_str(),
        GENERIC_ALL,
        FILE_SHARE_READ,

        nullptr,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    if (hFile == INVALID_HANDLE_VALUE) return value;
    const auto size = GetFileSize(hFile, nullptr);
    if (size != 0x00000000)
    {
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

    auto p = COMMAND_MAP[uuid];
    while (p != nullptr)
    {
        const auto command = p;
        p = p->m_pNext;
        free(command);
    }
    COMMAND_MAP[uuid] = value;

    return value;
}

std::map<std::string, CObjectProxy*> CObjectProxy::REF_MAP;

std::map<std::string, CVmCommand*> CObjectProxy::COMMAND_MAP;

AFX_EXTENSION_MODULE* CObjectProxy::TEMP_MODULE;

COceanTreeIterator::COceanTreeIterator(const COceanNode* root)
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

COceanNode** __cdecl COceanTreeIterator::GetMotherOceanHook(COceanNode** pNode)
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
