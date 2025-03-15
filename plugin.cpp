#include <stdafx.h>
#include <detours.h>
// #include <cJSON.h>
#include "plugin.h"
#include "rugp.h"
#include "hook.h"

static RUGP_MODULE* RUGP;

// ReSharper disable once CppParameterMayBeConst
BOOL WINAPI DllMain(HINSTANCE hInstance, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        SetConsoleTitleA("r514783 Plugin Debug Console");
        SetConsoleCP(CP_SHIFT_JIS);
        SetConsoleOutputCP(CP_SHIFT_JIS);
        freopen("CON", "w", stdout);

        __try
        {
            RUGP = new RUGP_MODULE(hInstance);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("INIT Fail: 0x%08X\n\n", GetExceptionCode());
            return FALSE;
        }
        printf("MFC Version %s\n", RUGP->GetMfcVersion());

        printf("rUGP System Version %s\n", RUGP->GetVersion());
        // printf("cJSON Version %s\n", cJSON_Version());
        printf("Detours Version %x\n", DETOURS_VERSION);
        printf("\n");

        CObjectProxy::LoadFromModule("UnivUI");
        // CObjectProxy::LoadFromModule("rvmm");
        // CObjectProxy::LoadFromModule("Vm60");

        // __try
        // {
        //     CFile json(GetGameName() + ".json", CFile::modeReadWrite | CFile::modeCreate | CFile::modeNoTruncate);
        //     const auto buffer = static_cast<LPSTR>(malloc(json.GetLength()));
        //     TRANSLATION_DATA = json.Read(buffer, json.GetLength())
        //                            ? cJSON_Parse(buffer)
        //                            : cJSON_CreateObject();
        //     free(buffer);
        // }
        // __except (EXCEPTION_EXECUTE_HANDLER)
        // {
        //     printf("cJSON_Parse Fail: 0x%08X\n\n", GetExceptionCode());
        // }

        __try
        {
            Win32Hook::AttachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Win32Hook::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        // __try
        // {
        //     CObjectProxy::AttachHook();
        // }
        // __except (EXCEPTION_EXECUTE_HANDLER)
        // {
        //     printf("CObjectProxy::AttachHook Fail: 0x%08X\n\n", GetExceptionCode());
        // }

        break;
    case DLL_PROCESS_DETACH:
        // __try
        // {
        //     CObjectProxy::DetachHook();
        // }
        // __except (EXCEPTION_EXECUTE_HANDLER)
        // {
        //     printf("CObjectProxy::DetachHook: 0x%08X\n\n", GetExceptionCode());
        // }

        __try
        {
            Win32Hook::DetachHook();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("Win32Hook::DetachHook Fail: 0x%08X\n\n", GetExceptionCode());
        }

        // __try
        // {
        //     const auto buffer = cJSON_Print(TRANSLATION_DATA);
        //     CFile json(GetGameName() + ".json", CFile::modeReadWrite);
        //     json.Write(buffer, strlen(buffer));
        //     cJSON_free(buffer);
        //     cJSON_free(TRANSLATION_DATA);
        // }
        // __except (EXCEPTION_EXECUTE_HANDLER)
        // {
        //     printf("cJSON_Print Fail: 0x%08X\n\n", GetExceptionCode());
        // }

        FreeConsole();

        delete RUGP;

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

    return RUGP->GetNative();
}

LPCSTR WINAPIV GetPluginString(const DWORD /*param1*/, const DWORD /*param2*/)
{
    return "Fuck rUGP! Version 0.1.0\r\n"
        "\tThis is unofficial plugin.\r\n"
        "\t(c)2024-2025 CssXsh All rights reserved.\r\n"
        "\r\n";
}

CObjectProxy::CObjectProxy(const CRuntimeClass* const pClass)
{
    m_pClass = pClass;
    m_pfnCreateObject = m_pClass->m_pfnCreateObject;
    
    // if (m_pClass == &CVisual::classCVisual)
    // {
    //     auto constructor = &CVisual::Constructor;
    //     m_pVTBL = FindVirtualTable(m_pClass, *reinterpret_cast<FARPROC*>(&constructor));
    // }
    //
    // if (m_pVTBL == nullptr && m_pfnCreateObject)
    // {
    //     m_pVTBL = FindVirtualTable(m_pClass, reinterpret_cast<FARPROC>(m_pfnCreateObject));
    // }
    //
    // if (!m_pClass->IsDerivedFrom(&CObjectEx::classCObjectEx)) return;
    // m_pfnPlacementCreate = reinterpret_cast<const CRuntimeClassEx*>(m_pClass)->m_pfnPlacementCreate;
    //
    // if (m_pVTBL == nullptr && m_pfnPlacementCreate)
    // {
    //     m_pVTBL = FindVirtualTable(m_pClass, reinterpret_cast<FARPROC>(m_pfnPlacementCreate));
    // }
    //
    // if (m_pVTBL == nullptr) return;
    // m_pfnSerialize = reinterpret_cast<const CObjectEx_vtbl*>(m_pVTBL)->Serialize;
    //
    // if (m_pClass->IsDerivedFrom(&CCommandRef::classCCommandRef))
    // {
    //     m_pfnGetNextCommand = reinterpret_cast<const CCommandRef_vtbl*>(m_pVTBL)->GetNextCommand;
    // }
}

// LPCSTR CObjectProxy::GetModuleName() const
// {
//     if (m_pClass->IsDerivedFrom(&CObjectEx::classCObjectEx))
//     {
//         const auto rtc = reinterpret_cast<const CRuntimeClassEx*>(this->m_pClass);
//         if (rtc->m_pModule) return rtc->m_pModule->name;
//     }
//     const auto module = DetourGetContainingModule(const_cast<CRuntimeClass*>(m_pClass));
//     if (module == GetModuleHandleA("UnivUI")) return "UnivUI";
//     if (module == GetModuleHandleA("rvmm")) return "rvmm";
//     if (module == GetModuleHandleA("Vm60")) return "Vm60";
//     return nullptr;
// }
//
// LPCSTR CObjectProxy::GetDescription() const
// {
//     return m_pClass->IsDerivedFrom(&CRio::classCRio)
//                ? reinterpret_cast<const CRuntimeClassRio*>(this->m_pClass)->m_lpszDesc
//                : nullptr;
// }

CObjectProxy* CObjectProxy::Find(LPCSTR const lpszClassName)
{
    return ERF_MAP[lpszClassName];
}

BOOL CObjectProxy::LoadFromModule(LPCSTR const lpszModuleName)
{
    const auto hModule = GetModuleHandleA(lpszModuleName);
    if (hModule == nullptr) return FALSE;
    const auto proc = GetProcAddress(hModule, "PluginThisLibrary");
    if (proc == nullptr) return FALSE;
    const auto module = reinterpret_cast<const AFX_EXTENSION_MODULE*>(proc());
    if (module == nullptr) return FALSE;
    for (auto clazz = module->pFirstSharedClass; clazz; clazz = clazz->m_pNextClass)
    {
        ERF_MAP[clazz->m_lpszClassName] = new CObjectProxy(clazz);
    }

    return TRUE;
}

// void CObjectProxy::AttachHook()
// {
//     DetourTransactionBegin();
//     DetourUpdateThread(GetCurrentThread());
//     auto iterator = Iterator();
//     for (auto ref = iterator.Next(); ref; ref = iterator.Next())
//     {
//         if (ref->m_pfnGetNextCommand)
//         {
//             printf("DetourAttach: %s::GetNextCommand\n", ref->m_pClass->m_lpszClassName);
//             DetourAttach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
//         }
//     }
//     DetourTransactionCommit();
// }
//
// void CObjectProxy::DetachHook()
// {
//     DetourTransactionBegin();
//     DetourUpdateThread(GetCurrentThread());
//     auto iterator = Iterator();
//     for (auto ref = iterator.Next(); ref; ref = iterator.Next())
//     {
//         if (ref->m_pfnGetNextCommand)
//         {
//             printf("DetourDetach: %s::GetNextCommand\n", ref->m_pClass->m_lpszClassName);
//             DetourDetach(&reinterpret_cast<PVOID&>(ref->m_pfnGetNextCommand), HookGetNextCommand);
//         }
//     }
//     DetourTransactionCommit();
//
//     for (struct
//          {
//              POSITION pos = COMMAND_MAP.GetStartPosition();
//              CString key = AfxGetEmptyString();
//              CVmCommand* buffer = nullptr;
//          } status
//          ; status.pos
//          ; COMMAND_MAP.GetNextAssoc(status.pos, status.key, reinterpret_cast<LPVOID&>(status.buffer)))
//     {
//         while (status.buffer != nullptr)
//         {
//             const auto command = status.buffer;
//             status.buffer = status.buffer->m_pNext;
//             free(command);
//         }
//     }
// }
//
// const CObject_vtbl* FASTCALL CObjectProxy::FindVirtualTable(const CRuntimeClass* const rtc, const FARPROC ctor)
// {
//     if (IsBadCodePtr(ctor)) return nullptr;
//     const auto module = DetourGetContainingModule(const_cast<CRuntimeClass*>(rtc));
//     if (DetourGetContainingModule(ctor) != module) return nullptr;
//     for (auto offset = reinterpret_cast<DWORD>(ctor); offset - reinterpret_cast<DWORD>(ctor) < 0x0400; offset++)
//     {
//         // mov     dword ptr [*], ...
//         if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0xC7) continue;
//         const auto address = *reinterpret_cast<const CObject_vtbl* const*>(offset + 0x02);
//         if (IsBadReadPtr(address, sizeof(CObject_vtbl))) continue;
//         if (IsBadCodePtr(reinterpret_cast<FARPROC>(address->GetRuntimeClass))) continue;
//         const auto get = reinterpret_cast<DWORD>(address->GetRuntimeClass);
//         // mov     eax, ...
//         const auto clazz = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
//         if (rtc == clazz) return address;
//     }
//     for (auto offset = reinterpret_cast<DWORD>(ctor); offset - reinterpret_cast<DWORD>(ctor) < 0x0400; offset++)
//     {
//         // mov     ecx, ...
//         if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
//         // call    ...
//         if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
//         const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
//         const auto next = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
//         const auto vtbl = FindVirtualTable(rtc, next);
//         if (vtbl != nullptr) return vtbl;
//     }
//
//     return nullptr;
// }
//
// void FASTCALL CObjectProxy::HookSerialize(CObjectEx* const ecx, DWORD /*edx*/, CPmArchive* const archive)
// {
//     const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
//     Find(name)->m_pfnSerialize(ecx, archive);
// }
//
// CVmCommand* FASTCALL CObjectProxy::HookGetNextCommand(CCommandRef* const ecx, DWORD /*edx*/)
// {
//     const auto uuid = GetUUID(ecx->m_pNode);
//     const auto name = ecx->GetRuntimeClass()->m_lpszClassName;
//     auto value = static_cast<CVmCommand*>(nullptr);
//     if (COMMAND_MAP.Lookup(uuid, reinterpret_cast<LPVOID&>(value))) return value;
//     printf("Hook %s::GetNextCommand(this=%s)\n", name, static_cast<LPCSTR>(uuid));
//     value = Find(name)->m_pfnGetNextCommand(ecx);
//     if (cJSON_HasObjectItem(TRANSLATION_DATA, uuid))
//     {
//         value = Merge(value, cJSON_GetObjectItem(TRANSLATION_DATA, uuid));
//         COMMAND_MAP.SetAt(uuid, value);
//     }
//
//     return value;
// }
//
// CVmCommand* FASTCALL CObjectProxy::Merge(const CVmCommand* ecx, const cJSON* edx)
// {
//     auto result = static_cast<CVmCommand*>(nullptr);
//     if (ecx->IsKindOf(&CVmMsg::classCVmMsg))
//     {
//         const auto message = static_cast<const CVmMsg*>(ecx);
//         auto name = CString();
//         name.Format("%08X", message->m_dwFlags & 0x000FFFFF);
//         const auto text = cJSON_GetObjectItem(edx, name);
//         if (cJSON_IsString(text))
//         {
//             const auto value = cJSON_GetStringValue(text, CP_SHIFT_JIS);
//             const auto size = CVmMsg::classCVmMsg.m_nObjectSize + (strlen(value) + 0x04 & ~0x03);
//             const auto clone = static_cast<CVmMsg*>(malloc(size));
//             memcpy(clone, message, CVmMsg::classCVmMsg.m_nObjectSize);
//             memcpy(clone->m_area, value, strlen(value) + 0x04 & ~0x03);
//             cJSON_free(value);
//             result = clone;
//         }
//         else
//         {
//             const auto size = CVmMsg::classCVmMsg.m_nObjectSize + (strlen(message->m_area) + 0x04 & ~0x03);
//             const auto clone = static_cast<CVmMsg*>(malloc(size));
//             memcpy(clone, message, size);
//             result = clone;
//         }
//     }
//     else
//     {
//         // TODO: size calc
//         const auto size = ecx->m_pNext
//                               ? reinterpret_cast<DWORD>(ecx->m_pNext) - reinterpret_cast<DWORD>(ecx)
//                               : CVmMsg::classCVmMsg.m_nObjectSize;
//         const auto clone = static_cast<CVmMsg*>(malloc(size));
//         memcpy(clone, ecx, size);
//
//         result = clone;
//     }
//
//     result->m_pNext = ecx->m_pNext ? Merge(ecx->m_pNext, edx) : nullptr;
//
//     return result;
// }

std::map<LPCSTR, CObjectProxy*> CObjectProxy::ERF_MAP;

// CMapStringToPtr CObjectProxy::COMMAND_MAP;
//
// CObjectProxy::Iterator::Iterator(const CRuntimeClass* pBaseClass)
// {
//     m_pBaseClass = pBaseClass;
//     m_pos = ERF_MAP.GetStartPosition();
// }
//
// BOOL CObjectProxy::Iterator::HasNext() const
// {
//     return m_pos != nullptr;
// }
//
// CObjectProxy* CObjectProxy::Iterator::Next()
// {
//     while (m_pos)
//     {
//         auto key = CString();
//         auto ref = static_cast<CObjectProxy*>(nullptr);
//         ERF_MAP.GetNextAssoc(m_pos, key, reinterpret_cast<void*&>(ref));
//         if (!ref || !ref->m_pClass->IsDerivedFrom(m_pBaseClass)) continue;
//         return ref;
//     }
//
//     return nullptr;
// }