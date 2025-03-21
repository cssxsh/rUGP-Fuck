#include <stdafx.h>
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

    return nullptr;
}

BOOL AFXAPI AfxInitExtensionModule(AFX_EXTENSION_MODULE& extension, const HMODULE hMod)
{
    cache.clear();
    typedef BOOL (AFXAPI *LPAfxInitExtensionModule)(AFX_EXTENSION_MODULE&, HMODULE);
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

    return FALSE;
}

void AFXAPI AfxTermExtensionModule(AFX_EXTENSION_MODULE& extension, const BOOL bAll)
{
    typedef void (AFXAPI *LPAfxTermExtensionModule)(AFX_EXTENSION_MODULE&, BOOL);
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
}

BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass* pBaseClass) const
{
    const auto name = "?IsDerivedFrom@CRuntimeClass@@QBEHPBU1@@Z";
    typedef BOOL (__thiscall *LPIsDerivedFrom)(const CRuntimeClass*, const CRuntimeClass*);
    const auto mfc = GetMfc();
    auto proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(mfc.native, name));
    if (proc != nullptr) return proc(this, pBaseClass);
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

    return FALSE;
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
    const auto name = "?IsKindOf@CObject@@QBEHPBUCRuntimeClass@@@Z";
    typedef BOOL (__thiscall *LPIsKindOf)(const CObject*, const CRuntimeClass*);
    const auto mfc = GetMfc();
    auto proc = reinterpret_cast<LPIsKindOf>(GetProcAddress(mfc.native, name));
    if (proc != nullptr) return proc(this, pClass);
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

    return FALSE;
}

LPCSTR GetRugpVersion()
{
    const auto name = "?_GLOBAL_rUGP@@3VCrUGP@@A";
    auto version = reinterpret_cast<LPCSTR>(cache[name]);
    if (version != nullptr) return version;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            version = reinterpret_cast<LPCSTR>(cache[name] = GetProcAddress(rvmm, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(cache[name] = GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            version = reinterpret_cast<LPCSTR>(cache[name] = GetProcAddress(UnivUI, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(1100)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0E00:
        // TODO class CrUGP _GLOBAL_rUGP
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CObjectEx::GetClassCObjectEx()
{
    const auto name = "?classCObjEx@CObjEx@@2UCRtcEx@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(837)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CObjEx::classCObjEx
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CRio::GetClassCRio()
{
    const auto name = "?classCRio@CRio@@2UCRioRTC@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(843)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CRio::classCRio
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CVisual::GetClassCVisual()
{
    const auto name = "?classCVisual@CVisual@@2UCRioRTC@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(867)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CVisual::classCVisual
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

CPmArchive* CPmArchive::CreateLoadFilePmArchive(const LPCSTR path)
{
    typedef CPmArchive* (__cdecl *LPLoadFilePmArchive)(LPCSTR path);
    const auto name = "?CreateLoadFilePmArchive@CPmArchive@@SAPAV1@PBD@Z";
    auto proc = reinterpret_cast<LPLoadFilePmArchive>(cache[name]);
    if (proc != nullptr) return proc(path);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPLoadFilePmArchive>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path);
            proc = reinterpret_cast<LPLoadFilePmArchive>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(396)));
            if (proc != nullptr) return proc(path);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateLoadFilePmArchive(char const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

CPmArchive* CPmArchive::CreateSaveFilePmArchive(const LPCSTR path)
{
    typedef CPmArchive* (__cdecl *LPSaveFilePmArchive)(LPCSTR path, SIZE_T);
    const auto name = "?CreateSaveFilePmArchive@CPmArchive@@SAPAV1@PBDK@Z";
    auto proc = reinterpret_cast<LPSaveFilePmArchive>(cache[name]);
    if (proc != nullptr) return proc(path, 0x00010000);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPSaveFilePmArchive>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path, 0x00010000);
            proc = reinterpret_cast<LPSaveFilePmArchive>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(406)));
            if (proc != nullptr) return proc(path, 0x00010000);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateSaveFilePmArchive(char const *,unsigned long)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

void CPmArchive::DestroyPmArchive(CPmArchive* archive)
{
    if (archive == nullptr) return;
    typedef void (__cdecl *LPDestroyPmArchive)(CPmArchive*, BOOL);
    const auto name = "?DestroyPmArchive@CPmArchive@@SAXPAV1@H@Z";
    auto proc = reinterpret_cast<LPDestroyPmArchive>(cache[name]);
    if (proc != nullptr) return proc(archive, FALSE);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDestroyPmArchive>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, FALSE);
            proc = reinterpret_cast<LPDestroyPmArchive>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
            if (proc != nullptr) return proc(archive, FALSE);
        }
        break;
    case 0x0E00:
        // TODO public: static void __cdecl CPmArchive::DestroyPmArchive(class CPmArchive *,int)
    default:
        break;
    }
}

BOOL COceanNode::IsDerivedFrom(const CRuntimeClass* rtc) const
{
    typedef BOOL (__thiscall *LPIsDerivedFrom)(const COceanNode*, const CRuntimeClass*);
    const auto name = "?IsDerivedFrom@COceanNode@@IBEHPBUCRioRTC@@@Z";
    auto proc = reinterpret_cast<LPIsDerivedFrom>(cache[name]);
    if (proc != nullptr) return proc(this, rtc);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPIsDerivedFrom>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, rtc);
            proc = reinterpret_cast<LPIsDerivedFrom>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(74)));
            if (proc != nullptr) return proc(this, rtc);
        }
        break;
    case 0x0E00:
        // TODO protected: int __thiscall COceanNode::IsDerivedFrom(struct CRioRTC const *)const
        return FALSE;
    default:
        break;
    }
    return FALSE;
}

CRio* COceanNode::Fetch() const
{
    typedef CRio* (__thiscall *LPGetPointer)(const COceanNode*);
    const auto name = "?__GetPointer@COceanNode@@QBEPAVCRio@@XZ";
    auto proc = reinterpret_cast<LPGetPointer>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetPointer>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<LPGetPointer>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(75)));
            if (proc != nullptr) return proc(this);
        }
        break;
    case 0x0E00:
        // TODO public: class CRio * __thiscall COceanNode::__GetPointer(void)const
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

DWORD COceanNode::GetAddress() const
{
    return m_dwResAddr % 0xA2FB6AD1u;
}

const COceanNode* COceanNode::GetRoot()
{
    typedef COceanNode* (__cdecl *LPGetRoot)();
    const auto name = "?GetRoot@COceanNode@@SAPAV1@XZ";
    auto proc = reinterpret_cast<LPGetRoot>(cache[name]);
    if (proc != nullptr) return proc();
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPGetRoot>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            const auto is_root = GetProcAddress(UnivUI, "?IsRoot@COceanNode@@QBE_NXZ");
            if (is_root != nullptr)
            {
                const auto address = reinterpret_cast<DWORD>(is_root);
                return *reinterpret_cast<const COceanNode**>(address + 0x04);
            }
            proc = reinterpret_cast<LPGetRoot>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
            if (proc != nullptr) return proc();
        }
        break;
    case 0x0E00:
        // TODO public: static class COceanNode * __cdecl COceanNode::GetRoot(void)
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

const COceanNode* COceanNode::GetNull()
{
    const auto name = "?_GLOBAL_EnNull@@3VCNullEntry@@A";
    auto address = reinterpret_cast<COceanNode*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<COceanNode*>(cache[name] = GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<COceanNode*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(784)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO class CNullEntry _GLOBAL_EnNull
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CCommandRef::GetClassCCommandRef()
{
    const auto name = "?classCCommandRef@CCommandRef@@2UCRioRTC@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(Vm60, MAKEINTRESOURCE(168)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CCommandRef::classCCommandRef
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CVmMsg::GetClassCVmMsg()
{
    const auto name = "?classCVmMsg@CVmMsg@@2UCRtcEx@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(Vm60, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(Vm60, MAKEINTRESOURCE(193)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRtcEx CVmMsg::classCVmMsg
        return nullptr;
    default:
        break;
    }

    return nullptr;
}
