#include "rugp7.h"
#include <map>
#include <string>
#include <vcruntime_typeinfo.h>
#include <dbghelp.h>
#include <detours/detours.h>

#ifdef _DBGHELP_
#pragma comment(lib, "dbghelp.lib")
#endif // _DBGHELP_

static HMODULE Ages3ResT = nullptr;

const AFX_EXTENSION_MODULE* PluginThisLibrary()
{
    if (!Ages3ResT) return nullptr;
    const auto proc = GetProcAddress(Ages3ResT, "PluginThisLibrary");
    CreateDirectory(CUuiGlobals::GetGlobal()->m_strGameName, nullptr);
    return reinterpret_cast<decltype(PluginThisLibrary)*>(proc)();
}

BOOL PluginThisLibrary_Ages3Res()
{
    if (!Ages3ResT) return FALSE;
    const auto proc = GetProcAddress(Ages3ResT, "PluginThisLibrary_Ages3Res");
    CObjectProxy::AttachHook();
    return reinterpret_cast<decltype(PluginThisLibrary_Ages3Res)*>(proc)();
}

BOOL APIENTRY DllMain(HINSTANCE /*hInstance*/, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        Ages3ResT = LoadLibrary(L"Ages3ResT");
        break;
    case DLL_PROCESS_DETACH:
        CObjectProxy::DetachHook();
        FreeLibrary(Ages3ResT);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }

    return TRUE;
}

template <typename F>
static F GetProcAddress(HMODULE hModule, UINT_PTR const offset)
{
    const auto address = reinterpret_cast<LPBYTE>(hModule) + offset - 0x00400000u;
    return reinterpret_cast<F>(address);
}

void CObjectProxy::AttachHook()
{
    // fix: CResourceClipOnlyRegion
    CRuntimeClass::FromName("CResourceClipOnlyRegion")->m_pfnGetBaseClass =
        CRuntimeClass::FromName("CLoopGlidScrollSelectRegion")->m_pfnGetBaseClass;
    auto list = AfxGetAppModuleState()->m_classList;
    const auto CRip_RTC = CRip::GetThisClass();
    const auto CCommandRef_RTC = CCommandRef::GetThisClass();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (auto clazz = list.GetHead(); clazz != nullptr; clazz = list.GetNext(clazz))
    {
        if (clazz->m_pfnCreateObject == nullptr) continue;
        if (clazz->IsDerivedFrom(CRip_RTC))
        {
            DetourAttach(&reinterpret_cast<PVOID&>(FetchSerialize(clazz)), &HookSerialize);
        }
        if (clazz->IsDerivedFrom(CCommandRef_RTC))
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
    const auto CCommandRef_RTC = CCommandRef::GetThisClass();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    for (auto clazz = list.GetHead(); clazz != nullptr; clazz = list.GetNext(clazz))
    {
        if (clazz->m_pfnCreateObject == nullptr) continue;
        if (clazz->IsDerivedFrom(CRip_RTC))
        {
            DetourDetach(&reinterpret_cast<PVOID&>(FetchSerialize(clazz)), &HookSerialize);
        }
        if (clazz->IsDerivedFrom(CCommandRef_RTC))
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
        CUuiGlobals::GetGlobal()->m_strGameName.GetString(),
        node->GetAddress(),
        format.GetString());
    return path;
}

CObjectProxy::SerializeProc& CObjectProxy::FetchSerialize(CRuntimeClass* const clazz)
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
    if (ecx->m_pNode->m_dwResAddr == 0x00000000u) return;
    const auto path = GetPatchFilePath(ecx->m_pNode);
    const auto save = CPolymorphicArchive::CreateSaveFileArchive(path);
    save->m_native.SerializeClass(ecx->GetRuntimeClass());
    FetchSerialize(ecx->GetRuntimeClass())(ecx, save);
    CPolymorphicArchive::DestroyArchive(save);
}

CObjectProxy::GetNextCommandProc& CObjectProxy::FetchGetNextCommand(CRuntimeClass* const clazz)
{
    const auto name = "?GetNextCommand@" + std::string(clazz->m_lpszClassName) + "@@UBEPAVCVmCommand@@XZ";
    auto& proc = reinterpret_cast<GetNextCommandProc&>(PROC_CACHE[name]);
    if (proc != nullptr) return proc;
    if (clazz->m_pfnCreateObject == nullptr) return proc;
    if (!clazz->IsDerivedFrom(CCommandRef::GetThisClass())) return proc;
    const auto impl = clazz->CreateObject();
    const auto vtbl = *reinterpret_cast<FARPROC**>(impl);
    proc = reinterpret_cast<GetNextCommandProc>(vtbl[0x06]);
    delete impl;
    return proc;
}

CVmCommand* CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
{
    return FetchGetNextCommand(ecx->GetRuntimeClass())(ecx);
}

CPolymorphicArchive* CPolymorphicArchive::CreateLoadFileArchive(LPCTSTR const path)
{
    const auto module = GetModuleHandle(nullptr);
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(module, 0x005C2FD0u)(path);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(module, 0x005B2E00u)(path);
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
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(module, 0x005C3080u)(path);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(module, 0x005B2EB0u)(path);
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
        return GetProcAddress<decltype(DestroyArchive)*>(module, 0x005C3270u)(archive);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(DestroyArchive)*>(module, 0x005B30A0u)(archive);
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
        return GetProcAddress<FetchProc>(module, 0x005DAA30u)(this);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<FetchProc>(module, 0x005C93B0u)(this);
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
        return GetProcAddress<AccessProc>(module, 0x005DA200u)(this) > 0;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<AccessProc>(module, 0x005C8B50u)(this) > 0;
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
    switch (GetTimestampForLoadedLibrary(module))
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<COceanNode*>(module, 0x006E22FCu);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<COceanNode*>(module, 0x006AEECCu);
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
        return GetProcAddress<COceanNode*>(module, 0x006E13B4u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<COceanNode*>(module, 0x006AEE84u);
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
        return GetProcAddress<CrUGP*>(module, 0x006E2658u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<CrUGP*>(module, 0x006AF230u);
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
        return GetProcAddress<CUuiGlobals*>(module, 0x006E13E0u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<CUuiGlobals*>(module, 0x006ADF80u);
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}
