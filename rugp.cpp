#include <stdafx.h>
#include "rugp.h"

MFC_MODULE GetMfc()
{
    MFC_MODULE module = {};
    module.version = 0x0600;
    module.unicode = FALSE;
    module.native = GetModuleHandleA("MFC42.dll");
    if (module.native != nullptr) return module;
    module.version = 0x0C00;
    module.unicode = FALSE;
    module.native = GetModuleHandleA("MFC120.dll");
    if (module.native != nullptr) return module;
    module.version = 0x0E00;
    module.unicode = TRUE;
    module.native = GetModuleHandleA("MFC140U.dll");
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

LPCSTR GetRugpVersion()
{
    const auto name = "?_GLOBAL_rUGP@@3VCrUGP@@A";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandleA("rvmm.dll");
            auto version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto version = reinterpret_cast<LPCSTR>(GetProcAddress(UnivUI, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(UnivUI, MAKEINTRESOURCE(1100)));
            if (version != nullptr) return version;
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(837)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(837)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(867)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
    default:
        break;
    }

    return nullptr;
}

CPmArchive* CPmArchive::CreateLoadPmArchive(CFile* file, const SIZE_T size)
{
    const auto name = "?CreateLoadPmArchive@CPmArchive@@SAPAV1@PAVCFile@@K@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
    default:
        break;
    }

    return nullptr;
}

CPmArchive* CPmArchive::CreateSavePmArchive(CFile* file, const SIZE_T size)
{
    const auto name = "?CreateSavePmArchive@CPmArchive@@SAPAV1@PAVCFile@@K@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(410)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
    default:
        break;
    }

    return nullptr;
}

void CPmArchive::DestroyPmArchive(CPmArchive* archive, const BOOL bFlag)
{
    if (archive == nullptr) return;
    const auto name = "?DestroyPmArchive@CPmArchive@@SAXPAV1@H@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, bFlag);
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
            if (proc != nullptr) return proc(archive, bFlag);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, bFlag);
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(archive, bFlag);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
    default:
        break;
    }
}

const COceanNode* COceanNode::GetRoot()
{
    const auto name = "?GetRoot@COceanNode@@SAPAV1@XZ";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
            if (proc != nullptr) return proc();
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(784)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<COceanNode*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("Vm60.dll");
            auto address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(168)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
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
        {
            const auto UnivUI = GetModuleHandleA("Vm60.dll");
            auto address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<const CRuntimeClass*>(GetProcAddress(UnivUI, MAKEINTRESOURCE(193)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI.dll");
            auto address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            // TODO
            // proc = reinterpret_cast<LPCreateLoadPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            // if (proc != nullptr) return proc(file, size);
        }
        break;
    // case -0x0E00:
    //     return "14.0 Unicode";
    default:
        break;
    }

    return nullptr;
}
