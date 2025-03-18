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

CPmArchive* CPmArchive::CreateLoadPmArchive(CFile* file, const SIZE_T size)
{
    const auto name = "?CreateLoadPmArchive@CPmArchive@@SAPAV1@PAVCFile@@K@Z";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(399)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateLoadPmArchive(class CFile *,unsigned long)
        return nullptr;
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
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(file, size);
            proc = reinterpret_cast<LPCreatePmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(410)));
            if (proc != nullptr) return proc(file, size);
        }
        break;
    case 0x0E00:
        // TODO public: static class CPmArchive * __cdecl CPmArchive::CreateSavePmArchive(class CFile *,unsigned long)
        return nullptr;
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
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(archive, bFlag);
            proc = reinterpret_cast<LPDestroyPmArchive>(GetProcAddress(UnivUI, MAKEINTRESOURCE(426)));
            if (proc != nullptr) return proc(archive, bFlag);
        }
        break;
    case 0x0E00:
        // TODO public: static void __cdecl CPmArchive::DestroyPmArchive(class CPmArchive *,int)
    default:
        break;
    }
}

CRio* COceanNode::Fetch() const
{
    const auto name = "?__GetPointer@COceanNode@@QBEPAVCRio@@XZ";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPFetch>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<LPFetch>(GetProcAddress(UnivUI, MAKEINTRESOURCE(75)));
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

const COceanNode* COceanNode::GetRoot()
{
    const auto name = "?GetRoot@COceanNode@@SAPAV1@XZ";
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            auto proc = reinterpret_cast<LPGetNode>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc();
            proc = reinterpret_cast<LPGetNode>(GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
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
