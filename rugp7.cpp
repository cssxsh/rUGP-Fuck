#include "rugp7.h"
#include <map>
#include <string>
#include <vcruntime_typeinfo.h>
#include <dbghelp.h>
#include <detours/detours.h>

#ifdef _DBGHELP_
#pragma comment(lib, "dbghelp.lib")
#endif // _DBGHELP_

static HMODULE Ages7 = nullptr;

static DWORD Timestamp = 0;

static HMODULE Ages3ResT = nullptr;

const AFX_EXTENSION_MODULE* PluginThisLibrary()
{
    if (!Ages3ResT) return nullptr;
    const auto proc = GetProcAddress(Ages3ResT, "PluginThisLibrary");
    return reinterpret_cast<decltype(PluginThisLibrary)*>(proc)();
}

BOOL PluginThisLibrary_Ages3Res()
{
    if (!Ages3ResT) return FALSE;
    const auto proc = GetProcAddress(Ages3ResT, "PluginThisLibrary_Ages3Res");
    CreateDirectory(CUuiGlobals::GetGlobal()->m_strGameName, nullptr);
    CObjectProxy::AttachHook();
    return reinterpret_cast<decltype(PluginThisLibrary_Ages3Res)*>(proc)();
}

BOOL APIENTRY DllMain(HINSTANCE /*hInstance*/, const DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        if (IsDebuggerPresent()) setvbuf(stdout, nullptr, _IONBF, 0);
        Ages7 = GetModuleHandle(nullptr);
        Ages3ResT = LoadLibrary(L"Ages3ResT");
        Timestamp = GetTimestampForLoadedLibrary(Ages7);
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
            wprintf(L"DetourAttach: %hs::Serialize\n", clazz->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(FetchRipSerialize(clazz)), &HookRipSerialize);
        }
        if (clazz->IsDerivedFrom(CCommandRef_RTC))
        {
            wprintf(L"DetourAttach: %hs::GetNextCommand\n", clazz->m_lpszClassName);
            DetourAttach(&reinterpret_cast<PVOID&>(FetchGetNextCommand(clazz)), &HookGetNextCommand);
        }
    }
    wprintf(L"DetourAttach: CProcessOcean::GetNextCommand\n");
    DetourAttach(&reinterpret_cast<PVOID&>(FetchBeginProcess()), &HookBeginProcess);
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
            wprintf(L"DetourDetach: %hs::Serialize\n", clazz->m_lpszClassName);
            DetourDetach(&reinterpret_cast<PVOID&>(FetchRipSerialize(clazz)), &HookRipSerialize);
        }
        if (clazz->IsDerivedFrom(CCommandRef_RTC))
        {
            wprintf(L"DetourDetach: %hs::GetNextCommand\n", clazz->m_lpszClassName);
            DetourDetach(&reinterpret_cast<PVOID&>(FetchGetNextCommand(clazz)), &HookGetNextCommand);
        }
    }
    wprintf(L"DetourDetach: CProcessOcean::GetNextCommand\n");
    DetourDetach(&reinterpret_cast<PVOID&>(FetchBeginProcess()), &HookBeginProcess);
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

CObjectProxy::CRipSerializeProc& CObjectProxy::FetchRipSerialize(CRuntimeClass* const clazz)
{
    const auto name = "?Serialize@" + std::string(clazz->m_lpszClassName) + "@@UAEXAAVCPmArchive@@@Z";
    auto& proc = reinterpret_cast<CRipSerializeProc&>(PROC_CACHE[name]);
    if (proc != nullptr) return proc;
    // ??_7CRip@@6B@
    const auto impl = clazz->CreateObject();
    const auto vtbl = *reinterpret_cast<FARPROC**>(impl);
    proc = reinterpret_cast<CRipSerializeProc>(vtbl[0x05]);
    delete impl;
    return proc;
}

void CObjectProxy::HookRipSerialize(CRip* const ecx, CPolymorphicArchive* const archive)
{
    const auto Serialize = FetchRipSerialize(ecx->GetRuntimeClass());
    Serialize(ecx, archive);
    if (ecx->m_pNode->m_dwResAddr == 0x00000000u) return;
    const auto path = GetPatchFilePath(ecx->m_pNode);
    const auto save = CPolymorphicArchive::CreateSaveFileArchive(path);
    save->m_native.SerializeClass(ecx->GetRuntimeClass());
    Serialize(ecx, save);
    CPolymorphicArchive::DestroyArchive(save);
}

CObjectProxy::GetNextCommandProc& CObjectProxy::FetchGetNextCommand(CRuntimeClass* const clazz)
{
    const auto name = "?GetNextCommand@" + std::string(clazz->m_lpszClassName) + "@@UBEPAVCVmCommand@@XZ";
    auto& proc = reinterpret_cast<GetNextCommandProc&>(PROC_CACHE[name]);
    if (proc != nullptr) return proc;
    // ??_7CCommandRef@@6B@
    const auto impl = clazz->CreateObject();
    const auto vtbl = *reinterpret_cast<FARPROC**>(impl);
    proc = reinterpret_cast<GetNextCommandProc>(vtbl[0x0C]);
    delete impl;
    return proc;
}

CVmCommand* CObjectProxy::HookGetNextCommand(CCommandRef* const ecx)
{
    const auto GetNextCommand = FetchGetNextCommand(ecx->GetRuntimeClass());
    const auto value = GetNextCommand(ecx);
    for (auto command = value; command != nullptr; command = command->m_pNext)
    {
        const auto clazz = command->GetRuntimeClass();
        // char key[0x20];
        // sprintf(key, "%08X:%s", command->GetIndex(), clazz->m_lpszClassName);
        switch (*reinterpret_cast<const DWORD*>(clazz->m_lpszClassName + 0x03))
        {
        // CVmMsg
        case 0x0067734Du:
            // Merge(reinterpret_cast<CVmMsg*&>(command), context[key]);
            __debugbreak();
            break;
        // CVmGenericMsg
        case 0x656E6547:
            // Merge(reinterpret_cast<CVmGenericMsg*&>(command), context[key]);
            break;
        // CVmCall
        case 0x6C6C6143:
            // Merge(reinterpret_cast<CVmCall*&>(command), context[key]);
            break;
        default:
            break;
        }
    }
    return value;
}

CObjectProxy::BeginProcessProc& CObjectProxy::FetchBeginProcess()
{
    const auto name = "?BeginProcess@CProcessOcean@@QAEIPAVCVmmView@@@Z";
    auto& proc = reinterpret_cast<BeginProcessProc&>(PROC_CACHE[name]);
    if (proc != nullptr) return proc;
    // ??_7CProcessOcean@@6B@
    const auto impl = CProcessOcean::GetThisClass()->CreateObject();
    const auto vtbl = *reinterpret_cast<FARPROC**>(impl);
    delete impl;
    return proc = reinterpret_cast<BeginProcessProc>(vtbl[0x10]);
}

UINT CObjectProxy::HookBeginProcess(CProcessOcean* const ecx, CAgesWndThunk* const thunk, DWORD const dwFlags)
{
    const auto BeginProcess = FetchBeginProcess();
    // ??_7CAgesWndThunk@@6B@
    // ??_7CSystem6View@@6B@
    // thunk->m_pView;
    return BeginProcess(ecx, thunk, dwFlags);
}

CPolymorphicArchive* CPolymorphicArchive::CreateLoadFileArchive(LPCTSTR const path)
{
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(Ages7, 0x005C2FD0u)(path);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(Ages7, 0x005B2E00u)(path);
    default:
        break;
    }
    __debugbreak();
    throw;
}

CPolymorphicArchive* CPolymorphicArchive::CreateSaveFileArchive(LPCTSTR const path)
{
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(Ages7, 0x005C3080u)(path);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(CreateSaveFileArchive)*>(Ages7, 0x005B2EB0u)(path);
    default:
        break;
    }
    __debugbreak();
    throw;
}

void CPolymorphicArchive::DestroyArchive(CPolymorphicArchive* archive)
{
    if (archive == nullptr) return;
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<decltype(DestroyArchive)*>(Ages7, 0x005C3270u)(archive);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<decltype(DestroyArchive)*>(Ages7, 0x005B30A0u)(archive);
    default:
        break;
    }
    __debugbreak();
    throw;
}

BOOL COceanNode::IsDerivedFrom(const CRuntimeClass* rtc) const
{
    return m_pRTC != nullptr && m_pRTC->IsDerivedFrom(rtc);
}

CRio* COceanNode::Fetch() const
{
    using FetchProc = CRio* (__thiscall *)(const COceanNode*);
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<FetchProc>(Ages7, 0x005DAA30u)(this);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<FetchProc>(Ages7, 0x005C93B0u)(this);
    default:
        break;
    }
    __debugbreak();
    throw;
}

BOOL COceanNode::AccessChildNodes() const
{
    if (m_pChildren == nullptr) return TRUE;
    if (m_dwFlags & 0x00800000u) return FALSE;
    using AccessProc = INT (__thiscall *)(const COceanNode*);
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<AccessProc>(Ages7, 0x005DA200u)(this) > 0;
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<AccessProc>(Ages7, 0x005C8B50u)(this) > 0;
    default:
        break;
    }
    __debugbreak();
    throw;
}

UINT_PTR COceanNode::GetAddress() const
{
    return m_dwResAddr % CUuiGlobals::GetGlobal()->m_dwResKeyA;
}

const COceanNode* COceanNode::GetRoot()
{
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<COceanNode*>(Ages7, 0x006E22FCu);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<COceanNode*>(Ages7, 0x006AEECCu);
    default:
        break;
    }
    __debugbreak();
    throw;
}

const COceanNode* COceanNode::GetNull()
{
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<COceanNode*>(Ages7, 0x006E13B4u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<COceanNode*>(Ages7, 0x006AEE84u);
    default:
        break;
    }
    __debugbreak();
    throw;
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
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<CrUGP*>(Ages7, 0x006E2658u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<CrUGP*>(Ages7, 0x006AF230u);
    default:
        break;
    }
    __debugbreak();
    throw;
}

const CUuiGlobals* CUuiGlobals::GetGlobal()
{
    switch (Timestamp)
    {
    // 2016-09-30 19:18:43
    case 0x57EE4A13u:
        return GetProcAddress<CUuiGlobals*>(Ages7, 0x006E13E0u);
    // 2019-12-08 23:00:39
    case 0x5DED1017u:
        return GetProcAddress<CUuiGlobals*>(Ages7, 0x006ADF80u);
    default:
        break;
    }
    __debugbreak();
    throw;
}
