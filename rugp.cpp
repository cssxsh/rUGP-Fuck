#include "stdafx.h"
#include <string>
#include <map>
#include "rugp.h"

static std::map<std::string, FARPROC> cache;

MFC_MODULE GetMfc()
{
    MFC_MODULE module = {};
    module.version = 0x0600;
    module.unicode = FALSE;
    module.native = GetModuleHandleA("MFC42");
    if (module.native != nullptr) return module;
    module.version = 0x0C00;
    module.unicode = FALSE;
    module.native = GetModuleHandleA("MFC120");
    if (module.native != nullptr) return module;
    module.version = 0x0E00;
    module.unicode = TRUE;
    module.native = GetModuleHandleA("MFC140U");
    if (module.native != nullptr) return module;
    __debugbreak();
    return {};
}

LPCSTR GetMfcVersion()
{
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        return mfc.unicode ? "6.0 Unicode" : "6.0";
    case 0x0C00:
        return mfc.unicode ? "12.0 Unicode" : "12.0";
    case 0x0E00:
        return mfc.unicode ? "14.0 Unicode" : "14.0";
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

BOOL AFXAPI AfxInitExtensionModule(AFX_EXTENSION_MODULE& extension, const HMODULE hMod)
{
    cache.clear();
    using LPAfxInitExtensionModule = decltype(AfxInitExtensionModule)*;
    const auto name = "?AfxInitExtensionModule@@YGHAAUAFX_EXTENSION_MODULE@@PAUHINSTANCE__@@@Z";
    const auto mfc = GetMfc();
    auto init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc.native, name));
    if (init != nullptr) return init(extension, hMod);
    switch (mfc.version)
    {
    case 0x0600:
        init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1182)));
        if (init != nullptr) return init(extension, hMod);
        break;
    case 0x0C00:
        init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(2221)));
        if (init != nullptr) return init(extension, hMod);
        break;
    case 0x0E00:
        init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(2268)));
        if (init != nullptr) return init(extension, hMod);
        break;
    default:
        break;
    }
    __debugbreak();
    return FALSE;
}

void AFXAPI AfxTermExtensionModule(AFX_EXTENSION_MODULE& extension, const BOOL bAll)
{
    using LPAfxTermExtensionModule = decltype(AfxTermExtensionModule)*;
    const auto name = "?AfxTermExtensionModule@@YGXAAUAFX_EXTENSION_MODULE@@H@Z";
    const auto mfc = GetMfc();
    auto term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc.native, name));
    if (term != nullptr) return term(extension, bAll);
    switch (mfc.version)
    {
    case 0x0600:
        term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1253)));
        if (term != nullptr) return term(extension, bAll);
        break;
    case 0x0C00:
        term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(2328)));
        if (term != nullptr) return term(extension, bAll);
        break;
    case 0x0E00:
        term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc.native, MAKEINTRESOURCE(2374)));
        if (term != nullptr) return term(extension, bAll);
        break;
    default:
        break;
    }
    __debugbreak();
}

CStringX::CStringX(const CStringX& strSrc)
{
    using LPConstructor = CStringX* (__thiscall *)(CStringX*, const CStringX&);
    const auto name = "??0CString@@QAE@ABV0@@Z";
    auto& proc = reinterpret_cast<LPConstructor&>(cache[name]);
    if (proc != nullptr && proc(this, strSrc)) return;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(535)));
        if (proc != nullptr && proc(this, strSrc)) return;
        break;
    case 0x0C00:
    case 0x0E00:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(300)));
        if (proc != nullptr && proc(this, strSrc)) return;
        break;
    default:
        break;
    }
    __debugbreak();
}

CStringX::CStringX(const LPCSTR pszSrc)
{
    using LPConstructor = CStringX* (__thiscall *)(CStringX*, LPCSTR);
    const auto name = "??0CString@@QAE@PBD@Z";
    auto& proc = reinterpret_cast<LPConstructor&>(cache[name]);
    if (proc != nullptr && proc(this, pszSrc)) return;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(537)));
        if (proc != nullptr && proc(this, pszSrc)) return;
        break;
    case 0x0C00:
    case 0x0E00:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(310)));
        if (proc != nullptr && proc(this, pszSrc)) return;
        break;
    default:
        break;
    }
    __debugbreak();
}

CStringX::CStringX()
{
    using LPConstructor = CStringX* (__thiscall *)(CStringX*);
    const auto name = "??0CString@@QAE@XZ";
    auto& proc = reinterpret_cast<LPConstructor&>(cache[name]);
    if (proc != nullptr && proc(this)) return;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(540)));
        if (proc != nullptr && proc(this)) return;
        break;
    case 0x0C00:
    case 0x0E00:
        proc = reinterpret_cast<LPConstructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(316)));
        if (proc != nullptr && proc(this)) return;
        break;
    default:
        break;
    }
    __debugbreak();
}

CStringX::~CStringX()
{
    using LPDestructor = void (__thiscall *)(CStringX*);
    const auto name = "??1CString@@QAE@XZ";
    auto& proc = reinterpret_cast<LPDestructor&>(cache[name]);
    if (proc != nullptr && (proc(this), proc)) return;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPDestructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(800)));
        if (proc != nullptr && (proc(this), proc)) return;
        break;
    case 0x0C00:
        proc = reinterpret_cast<LPDestructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1041)));
        if (proc != nullptr && (proc(this), proc)) return;
        break;
    case 0x0E00:
        proc = reinterpret_cast<LPDestructor>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1044)));
        if (proc != nullptr && (proc(this), proc)) return;
        break;
    default:
        break;
    }
    __debugbreak();
}

CStringX& CStringX::operator=(const LPCSTR pszSrc)
{
    using LPSet = CStringX& (__thiscall *)(CStringX*, LPCSTR);
    const auto name = "??4CString@@QAEABV0@PBD@Z";
    auto& proc = reinterpret_cast<LPSet&>(cache[name]);
    if (proc != nullptr) return proc(this, pszSrc); // NOLINT(*-unconventional-assign-operator)
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(860)));
        if (proc != nullptr) return proc(this, pszSrc); // NOLINT(*-unconventional-assign-operator)
        break;
    case 0x0C00:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1524)));
        if (proc != nullptr) return proc(this, pszSrc); // NOLINT(*-unconventional-assign-operator)
        break;
    case 0x0E00:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1529)));
        if (proc != nullptr) return proc(this, pszSrc); // NOLINT(*-unconventional-assign-operator)
        break;
    default:
        break;
    }
    __debugbreak();
    return *this;
}

CStringX::operator CStringA&()
{
    return *reinterpret_cast<CStringA*>(this);
}

CStringX::operator LPCSTR() const
{
    return *reinterpret_cast<const LPCSTR*>(this);
}

template <class T>
CStringX::CStringX(
    const T* src,
    CStringX* (__thiscall *fetch)(const T*, CStringX*))
{
    if (this != fetch(src, this)) __debugbreak();
    if (m_pszData == nullptr) __debugbreak();
}

template <class T>
CStringX::CStringX(
    const T* src,
    LPCSTR const p1,
    LPCSTR const p2,
    CStringX* (__thiscall *fetch)(const T*, CStringX*, LPCSTR, LPCSTR))
{
    if (this != fetch(src, this, p1, p2)) __debugbreak();
    if (m_pszData == nullptr) __debugbreak();
}

inline CStringX CStringX::Fetch(
    const CVmVar* var,
    CStringX* (__thiscall *fetch)(const CVmVar*, CStringX*))
{
    return {var, fetch};
}

inline CStringX CStringX::Fetch(
    const CProfile* profile,
    LPCSTR const key,
    LPCSTR const value,
    CStringX*(__thiscall *fetch)(const CProfile*, CStringX*, LPCSTR, LPCSTR))
{
    return {profile, key, value, fetch};
}


BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass* pBaseClass) const
{
    using LPIsDerivedFrom = BOOL (__thiscall *)(const CRuntimeClass*, const CRuntimeClass*);
    const auto name = "?IsDerivedFrom@CRuntimeClass@@QBEHPBU1@@Z";
    auto& proc = reinterpret_cast<LPIsDerivedFrom&>(cache[name]);
    if (proc != nullptr) return proc(this, pBaseClass);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(mfc.native, MAKEINTRESOURCE(4045)));
        if (proc != nullptr) return proc(this, pBaseClass);
        break;
    case 0x0C00:
        proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(mfc.native, MAKEINTRESOURCE(8006)));
        if (proc != nullptr) return proc(this, pBaseClass);
        break;
    case 0x0E00:
        proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(mfc.native, MAKEINTRESOURCE(8161)));
        if (proc != nullptr) return proc(this, pBaseClass);
        break;
    default:
        break;
    }
    __debugbreak();
    return FALSE;
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
    using LPIsKindOf = BOOL (__thiscall *)(const CObject*, const CRuntimeClass*);
    const auto name = "?IsKindOf@CObject@@QBEHPBUCRuntimeClass@@@Z";
    auto& proc = reinterpret_cast<LPIsKindOf&>(cache[name]);
    if (proc != nullptr) return proc(this, pClass);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPIsKindOf>(GetProcAddress(mfc.native, MAKEINTRESOURCE(4083)));
        if (proc != nullptr) return proc(this, pClass);
        break;
    case 0x0C00:
        proc = reinterpret_cast<LPIsKindOf>(GetProcAddress(mfc.native, MAKEINTRESOURCE(8070)));
        if (proc != nullptr) return proc(this, pClass);
        break;
    case 0x0E00:
        proc = reinterpret_cast<LPIsKindOf>(GetProcAddress(mfc.native, MAKEINTRESOURCE(8225)));
        if (proc != nullptr) return proc(this, pClass);
        break;
    default:
        break;
    }
    __debugbreak();
    return FALSE;
}

GMfc::LPIsMBCS& GMfc::FetchIsMBCS()
{
    const auto name = "?IsDBCS@@YAHD@Z";
    auto& address = reinterpret_cast<LPIsMBCS&>(cache[name]);
    if (address != nullptr) return address;
    const auto GMfc = GetModuleHandleA("GMfc");
    if (GMfc == nullptr) return address = nullptr;
    return address = reinterpret_cast<LPIsMBCS>(GetProcAddress(GMfc, name));
}

CProfile::CProfile(CStringX& text)
{
    using LPCProfile = CProfile* (__thiscall *)(CProfile*, CStringX&);
    const auto name = "??0CProfile@@QAE@AAVCString@@@Z";
    auto& proc = reinterpret_cast<LPCProfile&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPCProfile>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    proc(this, text);
}

CProfile::CProfile(const CProfile& other)
{
    using LPCProfile = CProfile* (__thiscall *)(CProfile*, const CProfile&);
    const auto name = "??0CProfile@@QAE@ABV0@@Z";
    auto& proc = reinterpret_cast<LPCProfile&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPCProfile>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    proc(this, other);
}

CProfile::CProfile()
{
    using LPCProfile = CProfile* (__thiscall *)(CProfile*);
    const auto name = "??0CProfile@@QAE@XZ";
    auto& proc = reinterpret_cast<LPCProfile&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPCProfile>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    proc(this);
}

CProfile::~CProfile()
{
    using LPCProfile = void (__thiscall *)(CProfile*);
    const auto name = "??1CProfile@@QAE@XZ";
    auto& proc = reinterpret_cast<LPCProfile&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPCProfile>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    proc(this);
}

CProfile& CProfile::operator=(const CProfile& other)
{
    using LPSet = CProfile& (__thiscall *)(CProfile*, const CProfile&);
    const auto name = "??1CProfile@@QAE@XZ";
    auto& proc = reinterpret_cast<LPSet&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPSet>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    proc(this, other);
    return *this;
}

CStringX CProfile::operator[](LPCSTR const key) const
{
    using LPGet = CStringX* (__thiscall *)(const CProfile*, CStringX*, LPCSTR, LPCSTR);
    const auto name = "?ReadProfileString@CProfile@@QBE?AVCString@@PBD0@Z";
    auto& proc = reinterpret_cast<LPGet&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPGet>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    return CStringX::Fetch(this, key, "", proc);
}

CProfile::operator LPCSTR() const
{
    return *reinterpret_cast<const LPCSTR*>(this);
}

LPCSTR CProfile::EnumKeyValue(LPCSTR const pos, CStringX& key, CStringX& value) const
{
    using LPEnum = LPCSTR (__thiscall *)(const CProfile*, LPCSTR, CStringX&, CStringX&);
    const auto name = "?EnumProfile@CProfile@@QBEPBEPBEAAVCString@@1@Z";
    auto& proc = reinterpret_cast<LPEnum&>(cache[name]);
    if (proc == nullptr) proc = reinterpret_cast<LPEnum>(GetProcAddress(GetModuleHandleA("GMfc"), name));
    return proc(this, pos, key, value);
}

auto CProfile::begin() const -> Iterator
{
    return Iterator(this, *this);
}

auto CProfile::end() const -> Iterator
{
    return Iterator(this, nullptr);
}

CProfile::Iterator::Iterator(const CProfile* profile, LPCSTR const pos)
{
    m_profile = profile;
    m_pos = pos;
}

auto CProfile::Iterator::operator*() const -> std::pair<CStringX, CStringX>
{
    std::pair<CStringX, CStringX> result;
    m_profile->EnumKeyValue(m_pos, result.first, result.second);
    return result;
}

auto CProfile::Iterator::operator++() -> Iterator&
{
    if (m_pos == nullptr) return *this;
    std::pair<CStringX, CStringX> result;
    m_pos = m_profile->EnumKeyValue(m_pos, result.first, result.second);
    return *this;
}

auto CProfile::Iterator::operator++(int const count) -> Iterator
{
    const Iterator iterator = *this;
    for (auto i = 0; i < count; i++) this->operator++();
    return iterator;
}

auto CProfile::Iterator::operator!=(const Iterator& other) const -> bool
{
    return (m_profile != other.m_profile) || (m_pos != other.m_pos);
}

template <class T>
CProfile::CProfile(const T* src, CProfile* (__thiscall *fetch)(const T*, CProfile*))
{
    fetch(src, this);
    if (m_pszData == nullptr) __debugbreak();
}

inline CProfile CProfile::Fetch(const CRioMsg* msg, CProfile* (__thiscall *fetch)(const CRioMsg*, CProfile*))
{
    return {msg, fetch};
}

const CRuntimeClass* CObjectEx::GetClassCObjectEx()
{
    const auto name = "?classCObjEx@CObjEx@@2UCRtcEx@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(837)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CObjEx::classCObjEx
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CRio::GetClassCRio()
{
    const auto name = "?classCRio@CRio@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(843)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CRio::classCRio
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CRio::LPDestructor& CRio::FetchDestructor() const
{
    const auto clazz = this->GetRuntimeClass();
    const auto name = "??1" + std::string(clazz->m_lpszClassName) + "@@UAE@XZ";
    auto& address = reinterpret_cast<LPDestructor&>(cache[name]);
    if (address != nullptr) return address;
    return address = FindDestructor(reinterpret_cast<const CRio_vtbl*>(this));
}

CRio::LPSerialize& CRio::FetchSerialize() const
{
    const auto clazz = this->GetRuntimeClass();
    const auto name = "?Serialize@" + std::string(clazz->m_lpszClassName) + "@@UAEXAAVCPmArchive@@@Z";
    auto& address = reinterpret_cast<LPSerialize&>(cache[name]);
    if (address != nullptr) return address;
    return address = reinterpret_cast<const CRio_vtbl*>(this)->Serialize;
}

CRio::LPLibrarySupport& CRio::FetchLibrarySupport()
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto& address = reinterpret_cast<LPLibrarySupport&>(cache[name]);
    if (address != nullptr) return address;
    const auto UnivUI = GetModuleHandleA("UnivUI");
    if (UnivUI == nullptr) return address = nullptr;
    return address = reinterpret_cast<LPLibrarySupport>(GetProcAddress(UnivUI, name));
}

CRio::LPDestructor& CRio::FetchDestructor(const CRuntimeClass* clazz)
{
    const auto name = "??1" + std::string(clazz->m_lpszClassName) + "@@UAE@XZ";
    auto& address = reinterpret_cast<LPDestructor&>(cache[name]);
    if (address != nullptr) return address;
    if (!clazz->IsDerivedFrom(GetClassCRio())) return address = nullptr;
    return address = FindDestructor(FindVisualTable(clazz));
}

CRio::LPSerialize& CRio::FetchSerialize(const CRuntimeClass* clazz)
{
    const auto name = "?Serialize@" + std::string(clazz->m_lpszClassName) + "@@UAEXAAVCPmArchive@@@Z";
    auto& address = reinterpret_cast<LPSerialize&>(cache[name]);
    if (address != nullptr) return address;
    if (!clazz->IsDerivedFrom(GetClassCRio())) return address = nullptr;
    return address = FindVisualTable(clazz)->Serialize;
}

const CRio_vtbl* CRio::FindVisualTable(const CRuntimeClass* clazz)
{
    if (clazz->m_pfnCreateObject == nullptr) return nullptr;
    auto start = reinterpret_cast<LPBYTE>(clazz->m_pfnCreateObject);
    auto ctor = static_cast<FARPROC>(nullptr);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (offset[0x00] != 0x8B) continue;
        // call    ...
        if (offset[0x02] != 0xE8) continue;
        ctor = reinterpret_cast<FARPROC>(offset + 0x07 + *reinterpret_cast<int*>(offset + 0x03));
        break;
    }
    if (ctor == nullptr) return nullptr;
    start = reinterpret_cast<LPBYTE>(ctor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     dword ptr [*], ...
        if (offset[0x00] != 0xC7) continue;
        const auto vtbl = *reinterpret_cast<CRio_vtbl**>(offset + 0x02);
        if (IsBadReadPtr(vtbl, sizeof(CObject_vtbl))) continue;
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(vtbl->GetRuntimeClass))) continue;
        const auto get = reinterpret_cast<LPBYTE>(vtbl->GetRuntimeClass);
        // mov     eax, ...
        if (get[0x00] != 0xB8) continue;
        const auto rtc = *reinterpret_cast<const CRuntimeClass**>(get + 0x01);
        if (clazz != rtc) continue;
        return vtbl;
    }
    __debugbreak();
    return nullptr;
}

CRio::LPDestructor CRio::FindDestructor(const CRio_vtbl* vtbl)
{
    const auto start = reinterpret_cast<LPBYTE>(vtbl->Destructor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (offset[0x00] != 0x8B) continue;
        // call    ...
        if (offset[0x02] != 0xE8) continue;
        const auto jump = *reinterpret_cast<int*>(offset + 0x03);
        const auto next = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        if (IsBadCodePtr(next)) continue;
        return reinterpret_cast<LPDestructor>(next);
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CVisual::GetClassCVisual()
{
    const auto name = "?classCVisual@CVisual@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(867)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CVisual::classCVisual
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CRip::GetClassCRip()
{
    const auto name = "?classCRip@CRip@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(845)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CRip::classCRip
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CS5i::GetClassCS5i()
{
    const auto name = "?classCS5i@CS5i@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(851)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CS5i::classCS5i
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CS5i::Part::operator CS5i&()
{
    const auto vtbl = GetVisualTable();
    const auto clazz = GetClassCS5i();
    const auto start = reinterpret_cast<CRio_vtbl**>(this);
    for (auto offset = start; start - offset < clazz->m_nObjectSize; offset--)
    {
        if (IsBadReadPtr(offset, sizeof(CRio_vtbl*))) break;
        if (*offset != vtbl) continue;
        return *reinterpret_cast<CS5i*>(offset);
    }
    __debugbreak();
    throw std::exception("CS5i::Part no match");
}

CS5i::LPDrawFont1& CS5i::FetchDrawFont1()
{
    const auto name = "?DrawFont@CS5i@@QAEHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto& address = reinterpret_cast<LPDrawFont1&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<LPDrawFont1>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            const auto start = reinterpret_cast<LPBYTE const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                const auto proc = *offset;
                // push    0FFFFFFFFh
                if (proc[0x00] != 0x6Au) continue;
                if (proc[0x01] != 0xFFu) continue;
                address = reinterpret_cast<LPDrawFont1>(proc);
                break;
            }
        }
        return address;
    case 0x0C00:
    case 0x0E00:
        // @see FetchDrawFont2
        return address = nullptr;
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

CS5i::LPDrawFont2& CS5i::FetchDrawFont2()
{
    const auto name = "?DrawFont@CS5i@@QAEXPAHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto& address = reinterpret_cast<LPDrawFont2&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        // @see FetchDrawFont1
        return address = nullptr;
    case 0x0C00:
        {
            const auto start = reinterpret_cast<LPBYTE const*>(GetVisualTable());
            if (start == nullptr) break;
            auto r4 = 0;
            for (auto offset = start; offset - start < 0x0400; offset++)
            {
                if ((*offset)[0x00] == 0x00u) r4++;
                if (r4 != 0x03) continue;
                const auto proc = *(offset - 0x02);
                // push    ebp
                if (proc[0x00] != 0x55u) continue;
                // mov     ebp, esp
                if (proc[0x01] != 0x8Bu) continue;
                if (proc[0x02] != 0xECu) continue;
                // push    0FFFFFFFFh
                if (proc[0x03] != 0x6Au) continue;
                if (proc[0x04] != 0xFFu) continue;
                address = reinterpret_cast<LPDrawFont2>(proc);
                break;
            }
        }
        return address;
    case 0x0E00:
        // TODO public: int * __thiscall CS5i::DrawFont(int *, short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

const CRio_vtbl* CS5i::GetVisualTable()
{
    const auto name = "??_7CS5i@@6BCVisual@@@";
    auto& address = const_cast<const CRio_vtbl*&>(reinterpret_cast<CRio_vtbl*&>(cache[name]));
    if (address != nullptr) return address;
    return address = FindVisualTable(GetClassCS5i());
}

const CRuntimeClass* CS5RFont::GetClassCS5RFont()
{
    const auto name = "?classCS5RFont@CS5RFont@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(850)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CS5RFont::classCS5RFont
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

LPVOID CS5RFont::GetCachedFont(UINT const uChar, COceanNode* const node)
{
    return FetchGetCachedFont()(this, uChar, node);
}

LPVOID CS5RFont::CreateNewFont(UINT const uChar, COceanNode* const node)
{
    const auto name =
        "?CreateNewFont@CS5RFont@@IAEPAUCS5RFontEntry@@IV?$CRef@VCFontAttr@@VCFontAttr_ome@@VTFontAttr@@@@@Z";
    auto& proc = reinterpret_cast<LPGetFont&>(cache[name]);
    if (proc != nullptr) return proc(this, uChar, node);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetFont>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, uChar, node);
            const auto pfn_GetCachedFont = reinterpret_cast<LPBYTE>(GetProcAddress(UnivUI, MAKEINTRESOURCE(472)));
            const auto pfn_GetPointer = reinterpret_cast<LPBYTE>(GetProcAddress(UnivUI, MAKEINTRESOURCE(75)));
            for (auto offset = pfn_GetCachedFont; offset - pfn_GetCachedFont < 0x0400; offset++)
            {
                // call    ...
                if (offset[0x00] != 0xE8u) continue;
                const auto address = offset + 0x05 + *reinterpret_cast<int*>(offset + 0x01);
                if (address == pfn_GetPointer) continue;
                if (IsBadCodePtr(reinterpret_cast<FARPROC>(address))) continue;
                proc = reinterpret_cast<LPGetFont>(address);
                break;
            }
            if (proc != nullptr) return proc(this, uChar, node);
        }
        break;
    case 0x0E00:
        // TODO protected: struct CS5RFontEntry * __thiscall CS5RFont::CreateNewFont(unsigned int, class CRef<class CFontAttr, class CFontAttr_ome, class TFontAttr>)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CS5RFont::LPGetFont& CS5RFont::FetchGetCachedFont()
{
    const auto name =
        "?GetCachedFont@CS5RFont@@QAEPAUCS5RFontEntry@@IV?$CRef@VCFontAttr@@VCFontAttr_ome@@VTFontAttr@@@@@Z";
    auto& address = reinterpret_cast<LPGetFont&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<LPGetFont>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPGetFont>(GetProcAddress(UnivUI, MAKEINTRESOURCE(472)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: struct CS5RFontEntry * __thiscall CS5RFont::GetCachedFont(unsigned int, class CRef<class CFontAttr, class CFontAttr_ome, class TFontAttr>)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

const CRuntimeClass* CEditData::GetClassCEditData()
{
    const auto name = "?classCEditData@CEditData@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(828)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CEditData::classCEditData
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CUI::GetClassCUI()
{
    const auto name = "?classCUI@CUI@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(rvmm, MAKEINTRESOURCE(639)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CUI::classCUI
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CImgBox::GetClassCImgBox()
{
    const auto name = "?classCImgBox@CImgBox@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(rvmm, MAKEINTRESOURCE(613)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CImgBox::classCImgBox
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

int CImgBox::DrawFont(const SHORT x, const SHORT y, const UINT uChar, CFontContext* const context)
{
    return FetchDrawFont()(this, x, y, uChar, context);
}

LPCSTR CImgBox::DrawSingleLineText(const SHORT x, const SHORT y, const LPCSTR text, CFontContext* const context)
{
    return FetchDrawSingleLineText()(this, x, y, text, context);
}

void CImgBox::DrawSzText(const SHORT x, const SHORT y, const LPCSTR text, CFontContext* const context)
{
    return FetchDrawSzText()(this, x, y, text, context);
}

CImgBox::LPDrawFont& CImgBox::FetchDrawFont()
{
    const auto name = "?DrawFont@CImgBox@@QAEHFFIPAVCFontContext@@@Z";
    auto& address = reinterpret_cast<LPDrawFont&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, MAKEINTRESOURCE(251)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CImgBox::DrawFont(short, short, unsigned int, class CFontContext *)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

CImgBox::LPDrawSingleLineText& CImgBox::FetchDrawSingleLineText()
{
    const auto name = "?DrawSingleLineText@CImgBox@@QAEPBDFFPBDPAVCFontContext@@@Z";
    auto& address = reinterpret_cast<LPDrawSingleLineText&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<LPDrawSingleLineText>(GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPDrawSingleLineText>(GetProcAddress(rvmm, MAKEINTRESOURCE(264)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: char const * __thiscall CImgBox::DrawSingleLineText(short, short, char const *, class CFontContext *)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

CImgBox::LPDrawSzText& CImgBox::FetchDrawSzText()
{
    const auto name = "?DrawSzText@CImgBox@@QAEXFFPBDPAVCFontContext@@@Z";
    auto& address = reinterpret_cast<LPDrawSzText&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<LPDrawSzText>(GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPDrawSzText>(GetProcAddress(rvmm, MAKEINTRESOURCE(265)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CImgBox::DrawSzText(short, short, char const *, class CFontContext *)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

const CRuntimeClass* CDatabase::GetClassCDatabase()
{
    const auto name = "?classCStdb@CStdb@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(859)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CStdb::classCStdb
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CObjectOcean::GetClassCObjectOcean()
{
    const auto name = "?classCObjectOcean@CObjectOcean@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(839)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CObjectOcean::classCObjectOcean
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CrelicUnitedGameProject::GetClassCrelicUnitedGameProject()
{
    const auto name = "?classCrelicUnitedGameProject@CrelicUnitedGameProject@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(199)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CrelicUnitedGameProject::classCrelicUnitedGameProject
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CDatabase* CrelicUnitedGameProject::GetGameProfile()
{
    switch (GetClassCrelicUnitedGameProject()->m_nObjectSize)
    {
    case 0x00A8:
    case 0x00CC:
        return *reinterpret_cast<CRef*>(reinterpret_cast<LPBYTE>(this) + 0x0020);
    case 0x00F4:
        return *reinterpret_cast<CRef*>(reinterpret_cast<LPBYTE>(this) + 0x0024);
    default:
        break;
    }
    __debugbreak();
    throw std::exception("CrelicUnitedGameProject::GetGameProfile no match");
}

CrelicUnitedGameProject* CrelicUnitedGameProject::GetGlobal()
{
    const auto name = "?_GLOBAL_rLocalAppOcean@@3V?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@A";
    auto& global = reinterpret_cast<CRef*&>(cache[name]);
    if (global != nullptr) return *global;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            global = reinterpret_cast<CRef*>(GetProcAddress(rvmm, name));
            if (global != nullptr) return *global;
            global = reinterpret_cast<CRef*>(GetProcAddress(rvmm, MAKEINTRESOURCE(595)));
            if (global != nullptr) return *global;
        }
        break;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean,class CObjectOcean_ome,class TObjectOcean> _GLOBAL_rLocalAppOcean
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CObjectArcMan::GetClassCObjectArcMan()
{
    const auto name = "?classCObjectArcMan@CObjectArcMan@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            if (GetProcAddress(UnivUI, "?classCObjectOcean@CObjectOcean@@2UCRioRTC@@A") != nullptr) return nullptr;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(838)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CObjectArcMan::classCObjectArcMan
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CInstallSource* CObjectArcMan::GetSourceObject(INT_PTR const index)
{
    using LPGetSourceObject = CInstallSource* (__thiscall *)(CObjectArcMan*, INT_PTR);
    const auto name = "?GetSourceObject@CObjectArcMan@@QAEPAVCInstallSource@@H@Z";
    auto& proc = reinterpret_cast<LPGetSourceObject&>(cache[name]);
    if (proc != nullptr) return proc(this, index);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetSourceObject>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, index);
            proc = reinterpret_cast<LPGetSourceObject>(GetProcAddress(UnivUI, MAKEINTRESOURCE(546)));
            if (proc != nullptr) return proc(this, index);
        }
        break;
    case 0x0E00:
        // TODO public: class CInstallSource * __thiscall CObjectArcMan::GetSourceObject(int)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CObjectArcMan* CObjectArcMan::GetGlobal()
{
    const auto node = COceanNode::GetRoot()->FindChildrenTypeOf(GetClassCObjectArcMan());
    if (node == nullptr) return nullptr;
    return reinterpret_cast<CObjectArcMan*>(node->Fetch());
}

const CRuntimeClass* CProcessOcean::GetClassCProcessOcean()
{
    const auto name = "?classCProcessOcean@CProcessOcean@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(178)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CProcessOcean::classCProcessOcean
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CProcessOcean::LPBeginProcess& CProcessOcean::FetchBeginProcess()
{
    const auto name = "?BeginProcess@CProcessOcean@@QAEIPAVCVmmView@@@Z";
    auto& address = reinterpret_cast<LPBeginProcess&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<LPBeginProcess>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            const auto clazz = GetClassCProcessOcean();
            const auto vtbl = FindVisualTable(clazz);
            switch (clazz->m_nObjectSize)
            {
            case 0x002C:
                address = *reinterpret_cast<LPBeginProcess*>(reinterpret_cast<DWORD>(vtbl) + 0x38);
                if (address != nullptr) return address;
                break;
            case 0x0030:
                address = *reinterpret_cast<LPBeginProcess*>(reinterpret_cast<DWORD>(vtbl) + 0x3C);
                if (address != nullptr) return address;
                break;
            case 0x0034:
                address = *reinterpret_cast<LPBeginProcess*>(reinterpret_cast<DWORD>(vtbl) + 0x40);
                if (address != nullptr) return address;
                break;
            default:
                break;
            }
        }
        break;
    case 0x0E00:
        // TODO public: unsigned int __thiscall CProcessOcean::BeginProcess(class CVmmView *)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

const CArchive* CPmArchive::GetNative() const
{
    const auto vtbl = *reinterpret_cast<FARPROC* const*>(this);
    const auto start = reinterpret_cast<LPBYTE>(vtbl[0x0000]);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // lea     edi, [esi+4]
        if (offset[0x00] != 0x8Du) continue;
        if (offset[0x01] != 0x7Eu) continue;
        return reinterpret_cast<CArchive*>(reinterpret_cast<DWORD>(this) + offset[0x02]);
    }
    __debugbreak();
    return reinterpret_cast<CArchive*>(reinterpret_cast<DWORD>(this) + 0x08);
}

CPmArchive* CPmArchive::CreateLoadFilePmArchive(const LPCSTR path)
{
    using LPLoadFilePmArchive = CPmArchive* (__cdecl *)(LPCSTR path);
    const auto name = "?CreateLoadFilePmArchive@CPmArchive@@SAPAV1@PBD@Z";
    auto& proc = reinterpret_cast<LPLoadFilePmArchive&>(cache[name]);
    if (proc != nullptr) return proc(path);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPLoadFilePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path);
            proc = reinterpret_cast<LPLoadFilePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(396)));
            if (proc != nullptr) return proc(path);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateLoadFilePmArchive(char const *)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CPmArchive* CPmArchive::CreateSaveFilePmArchive(const LPCSTR path)
{
    using LPSaveFilePmArchive = CPmArchive* (__cdecl *)(LPCSTR path, SIZE_T);
    const auto name = "?CreateSaveFilePmArchive@CPmArchive@@SAPAV1@PBDK@Z";
    auto& proc = reinterpret_cast<LPSaveFilePmArchive&>(cache[name]);
    if (proc != nullptr) return proc(path, 0x00010000);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPSaveFilePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path, 0x00010000);
            proc = reinterpret_cast<LPSaveFilePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(406)));
            if (proc != nullptr) return proc(path, 0x00010000);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateSaveFilePmArchive(char const *, unsigned long)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

void CPmArchive::DestroyPmArchive(CPmArchive* archive)
{
    if (archive == nullptr) return;
    using LPDestroyPmArchive = void (__cdecl *)(CPmArchive*, BOOL);
    const auto name = "?DestroyPmArchive@CPmArchive@@SAXPAV1@H@Z";
    auto& proc = reinterpret_cast<LPDestroyPmArchive&>(cache[name]);
    if (proc != nullptr) return proc(archive, FALSE);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, FALSE);
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
            if (proc != nullptr) return proc(archive, FALSE);
        }
        break;
    case 0x0E00:
        // TODO public: static void __cdecl CPmArchive::DestroyPmArchive(class CPmArchive *, int)
    default:
        break;
    }
    __debugbreak();
}

BOOL COceanNode::IsDerivedFrom(const CRuntimeClass* rtc) const
{
    using LPIsDerivedFrom = BOOL (__thiscall *)(const COceanNode*, const CRuntimeClass*);
    const auto name = "?IsDerivedFrom@COceanNode@@IBEHPBUCRioRTC@@@Z";
    auto& proc = reinterpret_cast<LPIsDerivedFrom&>(cache[name]);
    if (proc != nullptr) return proc(this, rtc);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, rtc);
            proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(UnivUI, MAKEINTRESOURCE(74)));
            if (proc != nullptr) return proc(this, rtc);
        }
        break;
    case 0x0E00:
        // TODO protected: int __thiscall COceanNode::IsDerivedFrom(struct CRioRTC const *) const
    default:
        break;
    }
    __debugbreak();
    return FALSE;
}

CRio* COceanNode::Fetch()
{
    using LPGetPointer = CRio* (__thiscall *)(COceanNode*);
    const auto name = "?__GetPointer@COceanNode@@QBEPAVCRio@@XZ";
    auto& proc = reinterpret_cast<LPGetPointer&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetPointer>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<LPGetPointer>(GetProcAddress(UnivUI, MAKEINTRESOURCE(75)));
            if (proc != nullptr) return proc(this);
        }
        break;
    case 0x0E00:
        // TODO public: class CRio * __thiscall COceanNode::__GetPointer(void) const
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

void COceanNode::ReleaseRef()
{
    using LPReleaseRef = void (__thiscall *)(COceanNode*);
    const auto name = "?_ReleaseRef@COceanNode@@QAEXX";
    auto& proc = reinterpret_cast<LPReleaseRef&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPReleaseRef>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<LPReleaseRef>(GetProcAddress(UnivUI, MAKEINTRESOURCE(73)));
            if (proc != nullptr) return proc(this);
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall COceanNode::_ReleaseRef(void)
    default:
        break;
    }
    __debugbreak();
}

COceanNode* COceanNode::FindChildrenTypeOf(const CRuntimeClass* rtc) const
{
    if (rtc == nullptr) return nullptr;
    using LPFindChildrenTypeOf = CRef* (__thiscall *)(const COceanNode*, CRef*, const CRuntimeClass*);
    const auto name = "?__FindChildrenTypeof@COceanNode@@QBE?AVCRefBase@@PBUCRioRTC@@@Z";
    auto& proc = reinterpret_cast<LPFindChildrenTypeOf&>(cache[name]);
    if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPFindChildrenTypeOf>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
            proc = reinterpret_cast<LPFindChildrenTypeOf>(GetProcAddress(UnivUI, MAKEINTRESOURCE(116)));
            if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
        }
        break;
    case 0x0E00:
        // TODO public: class CRefBase __thiscall COceanNode::__FindChildrenTypeof(struct CRioRTC const *) const
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

COceanNode* COceanNode::FindParentTypeOf(const CRuntimeClass* rtc) const
{
    if (rtc == nullptr) return nullptr;
    using LPFindChildrenTypeOf = CRef* (__thiscall *)(const COceanNode*, CRef*, const CRuntimeClass*);
    const auto name = "?__FindParentTypeof@COceanNode@@QBE?AVCRefBase@@PBUCRioRTC@@@Z";
    auto& proc = reinterpret_cast<LPFindChildrenTypeOf&>(cache[name]);
    if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPFindChildrenTypeOf>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
            proc = reinterpret_cast<LPFindChildrenTypeOf>(GetProcAddress(UnivUI, MAKEINTRESOURCE(115)));
            if (proc != nullptr) return CRef::Fetch(this, rtc, proc).m_pNode;
        }
        break;
    case 0x0E00:
        // TODO public: class CRefBase __thiscall COceanNode::__FindParentTypeof(struct CRioRTC const *) const
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

COceanNode* COceanNode::GetNextAssocRef(POS& pos, CStringX& key) const
{
    using LPGetManageRef = COceanNode* (__thiscall *)(const COceanNode*, POS&, CStringX&);
    const auto name = "?GetNextAssocRef@COceanNode@@QBEPAV1@AAUPOS@1@AAVCString@@@Z";
    auto& proc = reinterpret_cast<LPGetManageRef&>(cache[name]);
    if (proc != nullptr) return proc(this, pos, key);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetManageRef>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, pos, key);
            proc = reinterpret_cast<LPGetManageRef>(GetProcAddress(UnivUI, MAKEINTRESOURCE(125)));
            if (proc != nullptr) return proc(this, pos, key);
        }
        break;
    case 0x0E00:
        // TODO public: class COceanNode * __thiscall COceanNode::GetNextAssocRef(struct COceanNode::POS &, class CString &) const
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

DWORD COceanNode::GetAddress() const
{
    const auto globals = CUuiGlobals::GetGlobal();
    if (globals == nullptr) return m_dwResAddr;
    return m_dwResAddr % globals->m_dwResKeyA;
}

const COceanNode* COceanNode::GetRoot()
{
    using LPGetRoot = COceanNode* (__cdecl *)();
    const auto name = "?GetRoot@COceanNode@@SAPAV1@XZ";
    auto& proc = reinterpret_cast<LPGetRoot&>(cache[name]);
    if (proc != nullptr) return proc();
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            const auto temp = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
            if (temp != nullptr && reinterpret_cast<LPBYTE>(temp)[0x00] == 0xB8u) proc = temp;
            if (proc != nullptr) return proc();
            const auto is_root = GetProcAddress(UnivUI, MAKEINTRESOURCE(114));
            if (is_root == nullptr) break;
            // cmp     ecx, offset ...
            const auto address = reinterpret_cast<LPBYTE>(is_root);
            return *reinterpret_cast<const COceanNode**>(address + 0x04);
        }
    case 0x0E00:
        // TODO public: static class COceanNode * __cdecl COceanNode::GetRoot(void)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const COceanNode* COceanNode::GetNull()
{
    const auto name = "?_GLOBAL_EnNull@@3VCNullEntry@@A";
    auto& address = reinterpret_cast<COceanNode*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(784)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO class CNullEntry _GLOBAL_EnNull
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

COceanNode::LPGetLocalFullPathName& COceanNode::FetchGetLocalFullPathName()
{
    const auto name = "?GetLocalFullPathName@COceanNode@@QBE?AVCString@@XZ";
    auto& address = reinterpret_cast<LPGetLocalFullPathName&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<LPGetLocalFullPathName>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPGetLocalFullPathName>(GetProcAddress(UnivUI, MAKEINTRESOURCE(88)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: class CString __thiscall COceanNode::GetLocalFullPathName(void) const
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

auto COceanNode::begin() -> Iterator
{
    return Iterator(this);
}

auto COceanNode::end() -> Iterator
{
    return Iterator(const_cast<COceanNode*>(GetNull()));
}

COceanNode::Iterator::Iterator(COceanNode* node)
{
    m_ptr = node;
}

auto COceanNode::Iterator::operator*() const -> COceanNode*
{
    return m_ptr;
}

auto COceanNode::Iterator::operator++() -> Iterator&
{
    CStringX name;
    const auto null = GetNull();
    auto current = m_ptr;
    while (current != nullptr && current != null)
    {
        auto& pos = m_record[current];
        m_ptr = current->GetNextAssocRef(pos, name);
        if (m_ptr != nullptr) break;
        m_ptr = current = current->m_pParent;
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
    return m_ptr != other.m_ptr;
}

CRef::CRef(const CRef& refSrc) : CRef(refSrc.m_pNode)
{
    // ...
}

CRef::CRef(COceanNode* const nodeSrc)
{
    m_pNode = nodeSrc;
    InterlockedIncrement(&m_pNode->m_nRefCount);
}

CRef::CRef()
{
    m_pNode = nullptr;
}

CRef::~CRef()
{
    if (m_pNode == nullptr) return;
    m_pNode->ReleaseRef();
}

CRef& CRef::operator=(COceanNode* const nodeSrc)
{
    if (m_pNode != nullptr) m_pNode->ReleaseRef();
    m_pNode = nodeSrc;
    InterlockedIncrement(&m_pNode->m_nRefCount);
    return *this;
}

template <class T>
CRef::operator T*() const
{
    static_assert(std::is_base_of<CRio, T>::value, "T must be derived from CRio");
    if (m_pNode == nullptr) return nullptr;
    return reinterpret_cast<T*>(m_pNode->Fetch());
}

template <class C, typename P>
CRef::CRef(const C* src, const P* p1, CRef* (__thiscall *fetch)(const C*, CRef*, const P*)) : CRef()
{
    if (this != fetch(src, this, p1)) __debugbreak();
}

inline CRef CRef::Fetch(
    const COceanNode* const node,
    const CRuntimeClass* const rtc,
    CRef* (__thiscall *fetch)(const COceanNode*, CRef*, const CRuntimeClass*))
{
    return {node, rtc, fetch};
}

LPCSTR CrUGP::GetVersion() const
{
    return version;
}

CrUGP* CrUGP::GetGlobal()
{
    const auto name = "?_GLOBAL_rUGP@@3VCrUGP@@A";
    auto& global = reinterpret_cast<CrUGP*&>(cache[name]);
    if (global != nullptr) return global;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            global = reinterpret_cast<CrUGP*>(GetProcAddress(rvmm, name));
            if (global != nullptr) return global;
            global = reinterpret_cast<CrUGP*>(GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (global != nullptr) return global;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            global = reinterpret_cast<CrUGP*>(GetProcAddress(UnivUI, name));
            if (global != nullptr) return global;
            global = reinterpret_cast<CrUGP*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(1100)));
            if (global != nullptr) return global;
        }
        break;
    case 0x0E00:
        // TODO class CrUGP _GLOBAL_rUGP
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CUuiGlobals* CUuiGlobals::GetGlobal()
{
    const auto name = "?eUuiGlbs@@3UCUuiGlobals@@A";
    auto& global = reinterpret_cast<CUuiGlobals*&>(cache[name]);
    if (global != nullptr) return global;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            global = reinterpret_cast<CUuiGlobals*>(GetProcAddress(UnivUI, name));
            if (global != nullptr) return global;
            const auto rio = GetProcAddress(UnivUI, "?classCRio@CRio@@2UCRioRTC@@A");
            if (rio != nullptr) break;
            global = reinterpret_cast<CUuiGlobals*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(901)));
            if (global != nullptr) return global;
        }
        break;
    case 0x0E00:
        // TODO struct CUuiGlobals eUuiGlbs
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CUuiGlobals::LPStep& CUuiGlobals::FetchStep()
{
    const auto name = "?Step@CBootTracer@@QAEXH@Z";
    auto& address = reinterpret_cast<LPStep&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<LPStep>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPStep>(GetProcAddress(UnivUI, MAKEINTRESOURCE(730)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CBootTracer::Step(int)
    default:
        break;
    }
    __debugbreak();
    return address = nullptr;
}

CProfile CRioMsg::ToMsgString() const
{
    using LPToMsgString = CProfile* (__thiscall *)(const CRioMsg*, CProfile*);
    const auto name = "?ToMsgString@CRioMsg@@QAE?AVCProfile@@XZ";
    auto& proc = reinterpret_cast<LPToMsgString&>(cache[name]);
    if (proc != nullptr) return CProfile::Fetch(this, proc);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPToMsgString>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return CProfile::Fetch(this, proc);
            proc = reinterpret_cast<LPToMsgString>(GetProcAddress(UnivUI, MAKEINTRESOURCE(750)));
            if (proc != nullptr) return CProfile::Fetch(this, proc);
        }
        break;
    case 0x0E00:
        // TODO public: class CProfile __thiscall CRioMsg::ToMsgString(void)
    default:
        break;
    }
    __debugbreak();
    return {};
}

CRioMsg* CRioMsg::FromMsgString(LPCSTR const text)
{
    using LPFromMsgString = CRioMsg* (__cdecl *)(LPCSTR);
    const auto name = "?FromMsgString@CRioMsg@@SAPAV1@PBD@Z";
    auto& proc = reinterpret_cast<LPFromMsgString&>(cache[name]);
    if (proc != nullptr) return proc(text);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPFromMsgString>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(text);
            proc = reinterpret_cast<LPFromMsgString>(GetProcAddress(UnivUI, MAKEINTRESOURCE(458)));
            if (proc != nullptr) return proc(text);
        }
        break;
    case 0x0E00:
        // TODO public: static class CRioMsg * __cdecl CRioMsg::FromMsgString(char const *)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CStringX CVmVar::ToSerialString() const
{
    using LPToSerialString = CStringX* (__thiscall *)(const CVmVar*, CStringX*);
    const auto name = "?ToSerialString@CVmVar@@QBE?AVCString@@XZ";
    auto& proc = reinterpret_cast<LPToSerialString&>(cache[name]);
    if (proc != nullptr) return CStringX::Fetch(this, proc);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPToSerialString>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return CStringX::Fetch(this, proc);
            proc = reinterpret_cast<LPToSerialString>(GetProcAddress(UnivUI, MAKEINTRESOURCE(754)));
            if (proc != nullptr) return CStringX::Fetch(this, proc);
        }
        break;
    case 0x0E00:
        // TODO public: class CString __thiscall CVmVar::ToSerialString(void) const
    default:
        break;
    }
    __debugbreak();
    return "(null)";
}

void CVmVar::FromSerialString(LPCSTR const text)
{
    using LPFromSerialString = void (__thiscall *)(CVmVar*, LPCSTR);
    const auto name = "?FromSerialString@CVmVar@@QAEXPBD@Z";
    auto& proc = reinterpret_cast<LPFromSerialString&>(cache[name]);
    if (proc != nullptr) return proc(this, text);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPFromSerialString>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, text);
            proc = reinterpret_cast<LPFromSerialString>(GetProcAddress(UnivUI, MAKEINTRESOURCE(462)));
            if (proc != nullptr) return proc(this, text);
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CVmVar::FromSerialString(char const *)
    default:
        break;
    }
    __debugbreak();
}

CStringX& CInstallSource::FetchName()
{
    switch (CObjectArcMan::GetClassCObjectArcMan()->m_nObjectSize)
    {
    case 0x00C0:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0018);
    case 0x00C8:
    case 0x00F0:
    case 0x0104:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0020);
    default:
        break;
    }
    __debugbreak();
    throw std::exception("CInstallSource::FetchName no match");
}

CStringX& CInstallSource::FetchSource()
{
    switch (CObjectArcMan::GetClassCObjectArcMan()->m_nObjectSize)
    {
    case 0x00C0:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0030);
    case 0x00C8:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0040);
    case 0x00F0:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0048);
    case 0x0104:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x004C);
    default:
        break;
    }
    __debugbreak();
    throw std::exception("CInstallSource::FetchSource no match");
}

CStringX& CInstallSource::FetchTarget()
{
    switch (CObjectArcMan::GetClassCObjectArcMan()->m_nObjectSize)
    {
    case 0x00C0:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x005C);
    case 0x00C8:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0068);
    case 0x00F0:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0070);
    case 0x0104:
        return *reinterpret_cast<CStringX*>(reinterpret_cast<LPBYTE>(this) + 0x0078);
    default:
        break;
    }
    __debugbreak();
    throw std::exception("CInstallSource::FetchTarget no match");
}

const CRuntimeClass* CCommandRef::GetClassCCommandRef()
{
    const auto name = "?classCCommandRef@CCommandRef@@2UCRioRTC@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(168)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CCommandRef::classCCommandRef
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

CVmCommand* CCommandRef::GetNextCommand()
{
    const auto clazz = this->GetRuntimeClass();
    const auto name = "?GetNextCommand@" + std::string(clazz->m_lpszClassName) + "@@UBEPAVCVmCommand@@XZ";
    auto& proc = reinterpret_cast<LPGetNextCommand&>(cache[name]);
    if (proc != nullptr) return proc(this);
    proc = FindGetNextCommand(reinterpret_cast<const CRio_vtbl*>(this));
    if (proc != nullptr) return proc(this);
    __debugbreak();
    return nullptr;
}

CCommandRef::LPGetNextCommand& CCommandRef::FetchGetNextCommand(const CRuntimeClass* clazz)
{
    const auto name = "?GetNextCommand@" + std::string(clazz->m_lpszClassName) + "@@UBEPAVCVmCommand@@XZ";
    auto& address = reinterpret_cast<LPGetNextCommand&>(cache[name]);
    if (address != nullptr) return address;
    if (!clazz->IsDerivedFrom(GetClassCCommandRef())) return address = nullptr;
    return address = FindGetNextCommand(FindVisualTable(clazz));
}

CCommandRef::LPGetNextCommand CCommandRef::FindGetNextCommand(const CRio_vtbl* vtbl)
{
    const auto arr = reinterpret_cast<FARPROC* const*>(vtbl);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        return reinterpret_cast<LPGetNextCommand>(arr[0x000B]);
    case 0x0C00:
        return reinterpret_cast<LPGetNextCommand>(arr[0x000C]);
    default:
        // TODO ?GetNextCommand@CCommandRef@@UBEPAVCVmCommand@@XZ
        break;
    }
    __debugbreak();
    return nullptr;
}

int CVmCommand::GetVariableAreaSize() const
{
    using LPGetVariableAreaSize = int (__thiscall *)(const CVmCommand*);
    const auto clazz = this->GetRuntimeClass();
    const auto name = "?GetValiableAreaSize@" + std::string(clazz->m_lpszClassName) + "@@UAEHXZ";
    auto& proc = reinterpret_cast<LPGetVariableAreaSize&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto vtbl = *reinterpret_cast<FARPROC* const*>(this);
    switch (clazz->m_wSchema)
    {
    case 0xA000000Cu:
    case 0xA000000Eu:
        proc = reinterpret_cast<LPGetVariableAreaSize>(vtbl[0x0007]);
        return proc(this);
    case 0xA0000011u:
    case 0xA0000015u:
        proc = reinterpret_cast<LPGetVariableAreaSize>(vtbl[0x0009]);
        return proc(this);
    default:
        // TODO ?GetValiableAreaSize@CVmCommand@@UAEHXZ
        break;
    }
    __debugbreak();
    // The memory is continuous by CHeap.
    if (m_pNext == nullptr) return 0;
    return reinterpret_cast<int>(m_pNext) - reinterpret_cast<int>(this) - clazz->m_nObjectSize;
}

const CRuntimeClass* CVmMsg::GetClassCVmMsg()
{
    const auto name = "?classCVmMsg@CVmMsg@@2UCRtcEx@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(193)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CVmMsg::classCVmMsg
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CVmGenericMsg::GetClassCVmGenericMsg()
{
    const auto name = "?classCVmGenericMsg@CVmGenericMsg@@2UCRtcEx@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(189)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CVmGenericMsg::classCVmMsg
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CVmCall::GetClassCVmCall()
{
    const auto name = "?classCVmCall@CVmCall@@2UCRtcEx@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(186)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CVmCall::classCVmCall
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const CRuntimeClass* CVmVarObj::GetClassCVmGenericMsg()
{
    const auto name = "?classCVmVarObj@CVmVarObj@@2UCRtcEx@@A";
    auto& address = reinterpret_cast<CRuntimeClass*&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(868)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CVmVarObj::classCVmVarObj
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}

const HashBucket<CMsgRTC>* CMsgRTC::GetRegister()
{
    using LPGetTheMsgRtcRegister = const HashBucket<CMsgRTC>*(__cdecl *)();
    const auto name = "?GetTheMsgRtcRegister@@YAPBVCMsgRTCRegister@@XZ";
    auto& proc = reinterpret_cast<LPGetTheMsgRtcRegister&>(cache[name]);
    if (proc != nullptr) return proc();
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetTheMsgRtcRegister>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            proc = reinterpret_cast<LPGetTheMsgRtcRegister>(GetProcAddress(UnivUI, MAKEINTRESOURCE(556)));
            if (proc != nullptr) return proc();
        }
        break;
    case 0x0E00:
        // TODO class CMsgRTCRegister const * __cdecl GetTheMsgRtcRegister(void)
    default:
        break;
    }
    __debugbreak();
    return nullptr;
}
