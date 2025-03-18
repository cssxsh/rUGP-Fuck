#include <stdafx.h>
#include <detours.h>
#include <cJSON.h>
#include "plugin.h"
#include "rugp.h"
#include "hook.h"

cJSON* LoadTextData();

void SaveTextData(const cJSON*);

CVmCommand* FASTCALL Merge(const CVmCommand* ecx, const cJSON* edx);

static AFX_EXTENSION_MODULE R514783_PLUGIN = {FALSE, nullptr};

static cJSON* TRANSLATION_DATA = nullptr;

// ReSharper disable once CppParameterMayBeConst
BOOL WINAPI DllMain(HINSTANCE hInstance, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        AfxInitExtensionModule(R514783_PLUGIN, hInstance);

        AllocConsole();
        SetConsoleTitleA("r514783 Plugin Debug Console");
        SetConsoleCP(CP_SHIFT_JIS);
        SetConsoleOutputCP(CP_SHIFT_JIS);
        freopen("CON", "w", stdout);

        printf("MFC Version %s\n", GetMfcVersion());
        printf("rUGP System Version %s\n", GetRugpVersion());
        printf("cJSON Version %s\n", cJSON_Version());
        printf("Detours Version %x\n", DETOURS_VERSION);
        printf("\n");

        CObjectProxy::LoadFromModule("UnivUI");
        CObjectProxy::LoadFromModule("rvmm");
        CObjectProxy::LoadFromModule("Vm60");

        __try
        {
            TRANSLATION_DATA = LoadTextData();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("cJSON_Parse Fail: 0x%08X\n\n", GetExceptionCode());
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

        break;
    case DLL_PROCESS_DETACH:
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

        __try
        {
            SaveTextData(TRANSLATION_DATA);
            cJSON_free(TRANSLATION_DATA);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("cJSON_Print Fail: 0x%08X\n\n", GetExceptionCode());
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
    //
    // CreateThread(nullptr, 0, ConsoleThreadFunction, nullptr, 0, nullptr);

    return &R514783_PLUGIN;
}

LPCSTR WINAPIV GetPluginString(const DWORD /*param1*/, const DWORD /*param2*/)
{
    return "Fuck rUGP! Version 0.1.0\r\n"
        "\tThis is unofficial plugin.\r\n"
        "\t(c)2024-2025 CssXsh All rights reserved.\r\n"
        "\r\n";
}

CString GetUUID(const COceanNode* node)
{
    auto path = CString();
    if (node == nullptr || node->m_pRTC == nullptr) return path;
    path.Format("%s@%08X", node->m_pRTC->m_lpszClassName, node->m_dwResAddr % 0xA2FB6AD1u);
    return path;
}

CString GetGameUUID()
{
    const auto command = GetCommandLineA();
    const auto l = strchr(command, '{');
    const auto r = strchr(l, '}');
    return {l + 1, static_cast<int>(reinterpret_cast<DWORD>(r) - reinterpret_cast<DWORD>(l) - 1)};
}

CString GetGameName()
{
    const auto uuid = GetGameUUID();
    return uuid.Right(uuid.GetLength() - uuid.Find('\\') - 1);
}

cJSON* LoadTextData()
{
    CFile json(GetGameName() + ".json", CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate);
    const auto buffer = static_cast<LPSTR>(malloc(json.GetLength()));
    const auto data = json.Read(buffer, json.GetLength())
                          ? cJSON_Parse(buffer)
                          : cJSON_CreateObject();
    free(buffer);

    return data;
}

void SaveTextData(const cJSON*)
{
    const auto buffer = cJSON_Print(TRANSLATION_DATA);
    CFile json(GetGameName() + ".json", CFile::modeReadWrite);
    json.Write(buffer, strlen(buffer));
    cJSON_free(buffer);
}

CVmCommand* FASTCALL Merge(const CVmCommand* ecx, cJSON* edx) // NOLINT(*-no-recursion)
{
    const auto pClassCVmMsg = CVmMsg::GetClassCVmMsg();
    auto result = static_cast<CVmCommand*>(nullptr);
    auto name = CString();
    name.Format("%08X:%s", ecx->m_dwFlags & 0x000FFFFF, ecx->GetRuntimeClass()->m_lpszClassName);
    // printf("Merge %s\n", static_cast<LPCSTR>(name));
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
        // cJSON_AddItemToObject(edx, name, cJSON_CreateNull());
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

    if (m_pfnCreateObject)
    {
        m_pVTBL = FindVirtualTable(m_pClass, reinterpret_cast<FARPROC>(m_pfnCreateObject));
    }

    if (m_pVTBL == nullptr) return;
    m_pfnSerialize = reinterpret_cast<const CObjectEx_vtbl*>(m_pVTBL)->Serialize;

    if (std::strcmp(m_pClass->m_lpszClassName, "CResourceClipOnlyRegion") == 0) return;
    const auto mfc = GetMfc();
    for (auto clazz = pClass;
         clazz != nullptr;
         clazz = clazz->m_pfnGetBaseClass ? clazz->m_pfnGetBaseClass() : nullptr)
    {
        if (clazz != CCommandRef::GetClassCCommandRef()) continue;
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
        break;
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
    for (const auto& ref : REF_MAP)
    {
        if (ref.second->m_pfnGetNextCommand)
        {
            printf("DetourAttach: %s::GetNextCommand\n", ref.second->m_pClass->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(ref.second->m_pfnGetNextCommand), HookGetNextCommand);
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
    COMMAND_MAP.clear();
}

const CObject_vtbl* FASTCALL CObjectProxy::FindVirtualTable( // NOLINT(*-no-recursion)
    const CRuntimeClass* const rtc, const FARPROC ctor, const int depth)
{
    if (depth >= 3) return nullptr;
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
    for (auto offset = reinterpret_cast<DWORD>(ctor); offset - reinterpret_cast<DWORD>(ctor) < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
        // call    ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
        const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
        const auto next = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        const auto vtbl = FindVirtualTable(rtc, next, depth + 1);
        if (vtbl != nullptr) return vtbl;
    }

    return nullptr;
}

void CObjectProxy::HookSupportRio(AFX_EXTENSION_MODULE& module)
{
    TEMP_MODULE = &module;
}

void FASTCALL CObjectProxy::HookSerialize(CObjectEx* const ecx, DWORD /*edx*/, CPmArchive* const archive)
{
    const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
    REF_MAP[name]->m_pfnSerialize(ecx, archive);
}

CVmCommand* FASTCALL CObjectProxy::HookGetNextCommand(CCommandRef* const ecx, DWORD /*edx*/)
{
    const auto uuid = GetUUID(ecx->m_pNode);
    const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
    auto value = COMMAND_MAP[static_cast<LPCSTR>(uuid)];
    if (value != nullptr) return value;
    printf("Hook %s::GetNextCommand(this=%s)\n", name, static_cast<LPCSTR>(uuid));
    value = REF_MAP[name]->m_pfnGetNextCommand(ecx);

    if (!cJSON_HasObjectItem(TRANSLATION_DATA, uuid)) cJSON_AddObjectToObject(TRANSLATION_DATA, uuid);
    value = Merge(value, cJSON_GetObjectItem(TRANSLATION_DATA, uuid));
    COMMAND_MAP[static_cast<LPCSTR>(uuid)] = value;

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
