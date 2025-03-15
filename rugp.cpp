#include <stdafx.h>
#include "rugp.h"

// ReSharper disable once CppParameterMayBeConst
RUGP_MODULE::RUGP_MODULE(HINSTANCE hInstance)
{
    mfc_version = fetch();
    if (mfc == nullptr) return;
    LPAfxInitExtensionModule init = nullptr;
    switch (mfc_version)
    {
    case 0x0600:
        // ?AfxInitExtensionModule@@YGHAAUAFX_EXTENSION_MODULE@@PAUHINSTANCE__@@@Z @ 1182 NONAME
        init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc, MAKEINTRESOURCE(1182)));
        break;
    case 0x0C00:
        // ?AfxInitExtensionModule@@YGHAAUAFX_EXTENSION_MODULE@@PAUHINSTANCE__@@@Z @ 2221 NONAME
        init = reinterpret_cast<LPAfxInitExtensionModule>(GetProcAddress(mfc, MAKEINTRESOURCE(2221)));
        break;
    default:
        break;
    }
    if (init == nullptr) return;
    init(native, hInstance);
}

RUGP_MODULE::~RUGP_MODULE()
{
    if (mfc == nullptr) return;
    LPAfxTermExtensionModule term = nullptr;
    switch (mfc_version)
    {
    case 0x0600:
        // ?AfxTermExtensionModule@@YGXAAUAFX_EXTENSION_MODULE@@H@Z @ 1253 NONAME
        term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc, MAKEINTRESOURCE(1253)));
        break;
    case 0x0C00:
        // ?AfxTermExtensionModule@@YGXAAUAFX_EXTENSION_MODULE@@H@Z @ 2328 NONAME
        term = reinterpret_cast<LPAfxTermExtensionModule>(GetProcAddress(mfc, MAKEINTRESOURCE(2328)));
        break;
    default:
        break;
    }
    if (term == nullptr) return;
    term(native, FALSE);
}

int RUGP_MODULE::fetch()
{
    mfc = GetModuleHandle("MFC42.dll");
    if (mfc != nullptr) return 0x0600;
    mfc = GetModuleHandle("MFC120.dll");
    if (mfc != nullptr) return 0x0C00;
    mfc = GetModuleHandle("MFC140U.dll");
    if (mfc != nullptr) return -0x0E00;

    return 0x0000;
}

const AFX_EXTENSION_MODULE* RUGP_MODULE::GetNative() const
{
    return &native;
}

LPCSTR RUGP_MODULE::GetVersion() const
{
    const auto name = "?_GLOBAL_rUGP@@3VCrUGP@@A";
    switch (mfc_version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandle("rvmm.dll");
            auto version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
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

LPCSTR RUGP_MODULE::GetMfcVersion() const
{
    switch (mfc_version)
    {
    case 0x0600:
        return "6.0";
    case 0x0C00:
        return "12.0";
    case -0x0E00:
        return "14.0 Unicode";
    default:
        break;
    }

    return nullptr;
}

CPmArchive* RUGP_MODULE::CreateLoadPmArchive(CFile* file, const SIZE_T size) const
{
    const auto name = "?CreateLoadPmArchive@CPmArchive@@SAPAV1@PAVCFile@@K@Z";
    switch (mfc_version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
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

CPmArchive* RUGP_MODULE::CreateSavePmArchive(CFile* file, const SIZE_T size) const
{
    const auto name = "?CreateSavePmArchive@CPmArchive@@SAPAV1@PAVCFile@@K@Z";
    switch (mfc_version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(410)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
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

void RUGP_MODULE::DestroyPmArchive(CPmArchive* archive, const BOOL bFlag) const
{
    if (archive == nullptr) return;
    const auto name = "?DestroyPmArchive@CPmArchive@@SAXPAV1@H@Z";
    switch (mfc_version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
            auto proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, bFlag);
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
            if (proc != nullptr) return proc(archive, bFlag);
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandle("UnivUI.dll");
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