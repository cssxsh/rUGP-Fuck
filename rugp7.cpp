#include "rugp7.h"
#include "proxy.h"
#include <map>
#include <string>
#include <vcruntime_typeinfo.h>
#include <dbghelp.h>
#include <detours/detours.h>

#ifdef _DBGHELP_
#pragma comment(lib, "dbghelp.lib")
#endif // _DBGHELP_

static const AFX_EXTENSION_MODULE* HookPluginThisLibrary();
static FARPROC GetProcAddress(HMODULE, UINT_PTR);

static HMODULE winmm = nullptr;
static decltype(HookPluginThisLibrary)* PluginThisLibrary = nullptr;

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
        try
        {
            const auto Ages3ResT = GetModuleHandle(TEXT("Ages3ResT"));
            PluginThisLibrary = reinterpret_cast<decltype(HookPluginThisLibrary)*>(
                GetProcAddress(Ages3ResT, "PluginThisLibrary"));
            if (PluginThisLibrary != nullptr)
            {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourAttach(&reinterpret_cast<PVOID&>(PluginThisLibrary), HookPluginThisLibrary);
                DetourTransactionCommit();
            }
        }
        catch (...)
        {
            // ...
        }
        break;
    case DLL_PROCESS_DETACH:
        try
        {
            if (PluginThisLibrary != nullptr)
            {
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                DetourDetach(&reinterpret_cast<PVOID&>(PluginThisLibrary), HookPluginThisLibrary);
                DetourTransactionCommit();
            }
        }
        catch (...)
        {
            // ...
        }
        if (winmm == nullptr) FreeLibrary(winmm);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }

    return TRUE;
}

const AFX_EXTENSION_MODULE* HookPluginThisLibrary()
{
    // fix: CResourceClipOnlyRegion
    {
        CRuntimeClass::FromName("CResourceClipOnlyRegion")->m_pfnGetBaseClass =
            CRuntimeClass::FromName("CLoopGlidScrollSelectRegion")->m_pfnGetBaseClass;
    }

    CreateDirectory(CUuiGlobals::GetGlobal()->m_strGameName, nullptr);
    CObjectProxy::AttachHook();
    return PluginThisLibrary();
}

static FARPROC GetProcAddress(HMODULE const hModule, UINT_PTR const offset)
{
    const auto address = reinterpret_cast<LPBYTE>(hModule) + offset - 0x00400000u;
    // push    ebp
    if (address[0x00] != 0x55u) return nullptr;
    // mov     ebp, esp
    if (address[0x01] != 0x8Bu || address[0x02] != 0xECu) return nullptr;
    return reinterpret_cast<FARPROC>(address);
}

void CObjectProxy::AttachHook()
{
    auto list = AfxGetAppModuleState()->m_classList;
    const auto CRip_RTC = CRip::GetThisClass();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (auto clazz = list.GetHead(); clazz != nullptr; clazz = list.GetNext(clazz))
    {
        if (clazz->m_pfnCreateObject == nullptr) continue;
        if (clazz->IsDerivedFrom(CRip_RTC))
        {
            DetourAttach(&reinterpret_cast<PVOID&>(FetchSerialize(clazz)), &HookSerialize);
        }
    }
    DetourTransactionCommit();
}

void CObjectProxy::DetachHook()
{
    auto list = AfxGetAppModuleState()->m_classList;
    const auto CRip_RTC = CRip::GetThisClass();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (auto clazz = list.GetHead(); clazz != nullptr; clazz = list.GetNext(clazz))
    {
        if (clazz->m_pfnCreateObject == nullptr) continue;
        if (clazz->IsDerivedFrom(CRip_RTC))
        {
            DetourDetach(&reinterpret_cast<PVOID&>(FetchSerialize(clazz)), &HookSerialize);
        }
    }
    DetourTransactionCommit();
}

std::map<std::string, FARPROC> CObjectProxy::PROC_CACHE;

CString CObjectProxy::GetPatchFilePath(const COceanNode* node)
{
    CString format = node->m_pRTC->m_lpszClassName;
    format.TrimLeft(L'C').MakeLower();
    CString path;
    path.Format(
        L"./%s/%08X.%s",
        CUuiGlobals::GetGlobal()->m_strGameName,
        node->GetAddress(),
        format);
    return path;
}

CObjectProxy::SerializeProc& CObjectProxy::FetchSerialize(CRuntimeClass* clazz)
{
    const auto name = "?Serialize@" + std::string(clazz->m_lpszClassName) + "@@UAEXAAVCPmArchive@@@Z";
    auto& proc = reinterpret_cast<SerializeProc&>(PROC_CACHE[name]);
    if (proc != nullptr) return proc;
    if (clazz->m_pfnCreateObject == nullptr) return proc;
    if (!clazz->IsDerivedFrom(CRio::GetThisClass())) return proc;
    const auto impl = clazz->CreateObject();
    const auto vtbl = *reinterpret_cast<FARPROC**>(impl);
    proc = reinterpret_cast<SerializeProc>(vtbl[0x05]);
    delete impl;
    return proc;
}

void CObjectProxy::HookSerialize(CRio* const ecx, CPolymorphicArchive* const archive)
{
    FetchSerialize(ecx->GetRuntimeClass())(ecx, archive);
    if (ecx->m_pNode->m_dwResAddr != 0x00000000u)
    {
        const auto path = GetPatchFilePath(ecx->m_pNode);
        const auto save = CPolymorphicArchive::CreateSaveFileArchive(path);
        FetchSerialize(ecx->GetRuntimeClass())(ecx, save);
        CPolymorphicArchive::DestroyArchive(save);
    }
}

CPolymorphicArchive* CPolymorphicArchive::CreateLoadFileArchive(LPCTSTR const path)
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x005C2FD0 = GetProcAddress(module, 0x005C2FD0u);
            if (x005C2FD0 != nullptr) return reinterpret_cast<decltype(CreateSaveFileArchive)*>(x005C2FD0)(path);
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x005B2E00 = GetProcAddress(module, 0x005B2E00u);
            if (x005B2E00 != nullptr) return reinterpret_cast<decltype(CreateSaveFileArchive)*>(x005B2E00)(path);
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CPolymorphicArchive* CPolymorphicArchive::CreateSaveFileArchive(LPCTSTR const path)
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x005C3080 = GetProcAddress(module, 0x005C3080u);
            if (x005C3080 != nullptr) return reinterpret_cast<decltype(CreateSaveFileArchive)*>(x005C3080)(path);
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x005B2EB0 = GetProcAddress(module, 0x005B2EB0u);
            if (x005B2EB0 != nullptr) return reinterpret_cast<decltype(CreateSaveFileArchive)*>(x005B2EB0)(path);
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

void CPolymorphicArchive::DestroyArchive(CPolymorphicArchive* archive)
{
    if (archive == nullptr) return;
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x005C3270 = GetProcAddress(module, 0x005C3270u);
            if (x005C3270 != nullptr) return reinterpret_cast<decltype(DestroyArchive)*>(x005C3270)(archive);
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x005B30A0 = GetProcAddress(module, 0x005B30A0u);
            if (x005B30A0 != nullptr) return reinterpret_cast<decltype(DestroyArchive)*>(x005B30A0)(archive);
        }
        break;
    default:
        break;
    }
    __debugbreak();
}

BOOL COceanNode::IsDerivedFrom(const CRuntimeClass* rtc) const
{
    return m_pRTC != nullptr && m_pRTC->IsDerivedFrom(rtc);
}

CRio* COceanNode::Fetch() const
{
    using FetchProc = CRio* (__thiscall *)(const COceanNode*);
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x005DAA30 = GetProcAddress(module, 0x005DAA30u);
            if (x005DAA30 != nullptr) return reinterpret_cast<FetchProc>(x005DAA30)(this);
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x005C93B0 = GetProcAddress(module, 0x005C93B0u);
            if (x005C93B0 != nullptr) return reinterpret_cast<FetchProc>(x005C93B0)(this);
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

BOOL COceanNode::AccessChildNodes() const
{
    if (m_pChildren == nullptr) return TRUE;
    if (m_dwFlags & 0x00800000u) return FALSE;
    using AccessProc = INT (__thiscall *)(const COceanNode*);
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x005DA200 = GetProcAddress(module, 0x005DA200u);
            if (x005DA200 != nullptr) return reinterpret_cast<AccessProc>(x005DA200)(this) > 0;
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x005C8B50 = GetProcAddress(module, 0x005C8B50u);
            if (x005C8B50 != nullptr) return reinterpret_cast<AccessProc>(x005C8B50)(this) > 0;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return FALSE;
}

UINT_PTR COceanNode::GetAddress() const
{
    return m_dwResAddr % CUuiGlobals::GetGlobal()->m_dwResKeyA;
}

const COceanNode* COceanNode::GetRoot()
{
    const auto module = GetModuleHandle(nullptr);
    const auto CStaticOceanRoot_RTC = CStaticOceanRoot::GetThisClass();
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x006E22FC = reinterpret_cast<COceanNode*>(reinterpret_cast<LPBYTE>(module) + 0x002E22FCu);
            if (x006E22FC->m_pRTC == CStaticOceanRoot_RTC) return x006E22FC;
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x006AEECC = reinterpret_cast<COceanNode*>(reinterpret_cast<LPBYTE>(module) + 0x002AEECCu);
            if (x006AEECC->m_pRTC == CStaticOceanRoot_RTC) return x006AEECC;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const COceanNode* COceanNode::GetNull()
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x006E13B4 = reinterpret_cast<COceanNode*>(reinterpret_cast<LPBYTE>(module) + 0x002E13B4u);
            if (x006E13B4->m_pParent == x006E13B4) return x006E13B4;
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x006AEE84 = reinterpret_cast<COceanNode*>(reinterpret_cast<LPBYTE>(module) + 0x002AEE84u);
            if (x006AEE84->m_pParent == x006AEE84) return x006AEE84;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

auto COceanNode::begin() const -> Iterator
{
    return Iterator(this);
}

auto COceanNode::end() -> Iterator
{
    return Iterator(GetNull());
}

COceanNode::Iterator::Iterator(const COceanNode* node)
{
    m_current = node;
    m_root = node;
}

auto COceanNode::Iterator::operator*() const -> const COceanNode*
{
    return m_current;
}

auto COceanNode::Iterator::operator++() -> Iterator&
{
    auto table = m_current->m_pChildren;
    if (table != nullptr)
    {
        for (auto index = 0; index < std::size(table->m_arrBucket); index++)
        {
            if (table->m_arrBucket[index] == nullptr) continue;
            m_current = table->m_arrBucket[index];
            return *this;
        }
    }
    if (m_current->m_pNext != nullptr)
    {
        m_current = m_current->m_pNext;
        return *this;
    }
    const auto null = GetNull();
    auto current = m_current;
    m_current = null;
    while (current != nullptr && current != null)
    {
        table = current->m_pParent->m_pChildren;
        if (table == nullptr) break;
        auto flag = false;
        for (auto index = 0; index < std::size(table->m_arrBucket); index++)
        {
            if (flag)
            {
                if (table->m_arrBucket[index] == nullptr) continue;
                m_current = table->m_arrBucket[index];
                return *this;
            }
            for (auto p = table->m_arrBucket[index]; p != nullptr; p = p->m_pNext)
            {
                if (current != p) continue;
                flag = true;
                break;
            }
        }
        if (current == m_root) break;
        current = current->m_pParent;
    }
    return *this;
}

auto COceanNode::Iterator::operator++(int const count) -> Iterator
{
    const Iterator iterator = *this;
    for (auto i = 0; i < count; i++) this->operator++();
    return iterator;
}

auto COceanNode::Iterator::operator!=(const Iterator& other) const -> bool
{
    return m_current != other.m_current;
}

const CrUGP* CrUGP::GetGlobal()
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x006E2658 = reinterpret_cast<CrUGP*>(reinterpret_cast<LPBYTE>(module) + 0x002E2658u);
            if (x006E2658->m_strVersion[0] == L'7') return x006E2658;
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x006AF230 = reinterpret_cast<CrUGP*>(reinterpret_cast<LPBYTE>(module) + 0x002AF230u);
            if (x006AF230->m_strVersion[0] == L'7') return x006AF230;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CUuiGlobals* CUuiGlobals::GetGlobal()
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        {
            const auto x006E13E0 = reinterpret_cast<CUuiGlobals*>(reinterpret_cast<LPBYTE>(module) + 0x002E13E0u);
            if (x006E13E0->m_dwResKeyA == 0xA2FB6AD1u) return x006E13E0;
        }
        break;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        {
            const auto x006ADF80 = reinterpret_cast<CUuiGlobals*>(reinterpret_cast<LPBYTE>(module) + 0x002ADF80u);
            if (x006ADF80->m_dwResKeyA == 0xA2FB6AD1u) return x006ADF80;
        }
        break;
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}
