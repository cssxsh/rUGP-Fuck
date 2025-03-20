#include <stdafx.h>
#include "rugp.h"

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

LPCSTR GetRugpVersion()
{
    const auto name = "?_GLOBAL_rUGP@@3VCrUGP@@A";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            auto version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto version = reinterpret_cast<LPCSTR>(GetProcAddress(UnivUI, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(UnivUI, MAKEINTRESOURCE(1100)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(837)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(843)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(867)));
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
    typedef CPmArchive* (__cdecl *LPCreateLoadFilePmArchive)(LPCSTR path);
    const auto name = "?CreateLoadFilePmArchive@CPmArchive@@SAPAV1@PBD@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPCreateLoadFilePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path);
            proc = reinterpret_cast<LPCreateLoadFilePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(396)));
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
    typedef CPmArchive* (__cdecl *LPCreateSaveFilePmArchive)(LPCSTR path, SIZE_T);
    const auto name = "?CreateSaveFilePmArchive@CPmArchive@@SAPAV1@PBDK@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPCreateSaveFilePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(path, 0x00010000);
            proc = reinterpret_cast<LPCreateSaveFilePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(406)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, FALSE);
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, rtc);
            proc = reinterpret_cast<LPIsDerivedFrom>(GetProcAddress(UnivUI, MAKEINTRESOURCE(74)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPGetPointer>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<LPGetPointer>(GetProcAddress(UnivUI, MAKEINTRESOURCE(75)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            const auto is_root = GetProcAddress(UnivUI, "?IsRoot@COceanNode@@QBE_NXZ");
            if (is_root != nullptr)
            {
                const auto address = reinterpret_cast<DWORD>(is_root);
                return *reinterpret_cast<const COceanNode**>(address + 0x04);
            }
            proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(784)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("Vm60");
            auto address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(168)));
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
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("Vm60");
            auto address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(193)));
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
