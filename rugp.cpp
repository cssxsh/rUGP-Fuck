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
    using LPAfxInitExtensionModule = BOOL (AFXAPI *)(AFX_EXTENSION_MODULE&, HMODULE);
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
    using LPAfxTermExtensionModule = void (AFXAPI *)(AFX_EXTENSION_MODULE&, BOOL);
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
    using LPIsDerivedFrom = BOOL (__thiscall *)(const CRuntimeClass*, const CRuntimeClass*);
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
    using LPIsKindOf = BOOL (__thiscall *)(const CObject*, const CRuntimeClass*);
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
    auto& version = reinterpret_cast<LPCSTR&>(reinterpret_cast<DWORD&>(cache[name]));
    if (version != nullptr) return version;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, name));
            if (version != nullptr) return version;
            version = reinterpret_cast<LPCSTR>(GetProcAddress(rvmm, MAKEINTRESOURCE(596)));
            if (version != nullptr) return version;
        }
        break;
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            version = reinterpret_cast<LPCSTR>(GetProcAddress(UnivUI, name));
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
        return nullptr;
    default:
        break;
    }

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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

void CRio::LibrarySupport(AFX_EXTENSION_MODULE& module)
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto& proc = reinterpret_cast<REG&>(cache[name]);
    if (proc != nullptr) return proc(module);
    const auto UnivUI = GetModuleHandleA("UnivUI");
    proc = reinterpret_cast<REG>(GetProcAddress(UnivUI, name));
    if (proc != nullptr) return proc(module);
}

void CRio::HookLibrarySupport(const HookCallback<REG> callback, const REG hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto& proc = reinterpret_cast<REG&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto UnivUI = GetModuleHandleA("UnivUI");
    proc = reinterpret_cast<REG>(GetProcAddress(UnivUI, name));
    if (proc != nullptr) return callback(proc, hook);
}

void CRio::HookIsMultiple(const HookCallback<IS_MULTIPLE> callback, const IS_MULTIPLE hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?IsDBCS@@YAHD@Z";
    auto& proc = reinterpret_cast<IS_MULTIPLE&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto GMfc = GetModuleHandleA("GMfc");
    proc = reinterpret_cast<IS_MULTIPLE>(GetProcAddress(GMfc, name));
    if (proc != nullptr) return callback(proc, hook);
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
        return nullptr;
    default:
        break;
    }

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
        return nullptr;
    default:
        break;
    }

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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

int CS5i::DrawFont(
    const DWORD x, const DWORD y, WORD* const rect, WORD* const out, const UINT uChar, COceanNode** const node)
{
    const auto name = "?DrawFont@CS5i@@QAEHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto& proc = reinterpret_cast<LPDrawFont&>(cache[name]);
    if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
            const auto start = reinterpret_cast<FARPROC const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                const auto address = reinterpret_cast<LPBYTE>(*offset);
                // push    0FFFFFFFFh
                if (address[0x00] != 0x6Au) continue;
                if (address[0x01] != 0xFFu) continue;
                proc = reinterpret_cast<LPDrawFont>(address);
                break;
            }
            if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
        }
        break;
    case 0x0C00:
        {
            const auto start = reinterpret_cast<FARPROC const*>(GetVisualTable());
            if (start == nullptr) break;
            auto r4 = 0;
            for (auto offset = start; offset - start < 0x0400; offset++)
            {
                if (reinterpret_cast<LPBYTE>(*offset)[0x00] == 0x00u) r4++;
                if (r4 != 0x03) continue;
                const auto address = reinterpret_cast<LPBYTE>(*(offset - 0x02));
                // push    ebp
                if (address[0x00] != 0x55u) continue;
                // push    ebp
                if (address[0x01] != 0x8Bu) continue;
                if (address[0x02] != 0xECu) continue;
                // push    0FFFFFFFFh
                if (address[0x03] != 0x6Au) continue;
                if (address[0x04] != 0xFFu) continue;
                proc = reinterpret_cast<LPDrawFont>(address);
                break;
            }
            if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CS5i::DrawFont(short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)
        return 0;
    default:
        break;
    }

    return 0;
}

void CS5i::HookDrawFont(
    const HookCallback<LPDrawFont> callback, const LPDrawFont hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawFont@CS5i@@QAEHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto& proc = reinterpret_cast<LPDrawFont&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return callback(proc, hook);
            const auto start = reinterpret_cast<FARPROC const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                const auto address = reinterpret_cast<LPBYTE>(*offset);
                // push    0FFFFFFFFh
                if (address[0x00] != 0x6Au) continue;
                if (address[0x01] != 0xFFu) continue;
                proc = reinterpret_cast<LPDrawFont>(address);
                break;
            }
            if (proc != nullptr) return callback(proc, hook);
        }
        break;
    case 0x0C00:
        {
            const auto start = reinterpret_cast<FARPROC const*>(GetVisualTable());
            if (start == nullptr) break;
            auto r4 = 0;
            for (auto offset = start; offset - start < 0x0400; offset++)
            {
                if (reinterpret_cast<LPBYTE>(*offset)[0x00] == 0x00u) r4++;
                if (r4 != 0x03) continue;
                const auto address = reinterpret_cast<LPBYTE>(*(offset - 0x02));
                // push    ebp
                if (address[0x00] != 0x55u) continue;
                // push    ebp
                if (address[0x01] != 0x8Bu) continue;
                if (address[0x02] != 0xECu) continue;
                // push    0FFFFFFFFh
                if (address[0x03] != 0x6Au) continue;
                if (address[0x04] != 0xFFu) continue;
                proc = reinterpret_cast<LPDrawFont>(address);
                break;
            }
            if (proc != nullptr) return callback(proc, hook);
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CS5i::DrawFont(short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)
    default:
        break;
    }
}

const CRio_vtbl* CS5i::GetVisualTable()
{
    const auto name = "??_7CS5i@@6BCVisual@@@";
    auto& address = reinterpret_cast<CRio_vtbl*&>(cache[name]);
    if (address != nullptr) return address;
    const auto clazz = GetClassCS5i();
    if (clazz->m_pfnCreateObject == nullptr) return nullptr;
    auto start = reinterpret_cast<LPBYTE>(clazz->m_pfnCreateObject);
    auto ctor = static_cast<FARPROC>(nullptr);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (offset[0x00] != 0x8B) continue;
        // call    ...
        if (offset[0x02] != 0xE8) continue;
        const auto jump = *reinterpret_cast<int*>(offset + 0x03);
        ctor = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        break;
    }
    start = reinterpret_cast<LPBYTE>(ctor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     dword ptr [*], ...
        if (offset[0x00] != 0xC7) continue;
        const auto vtbl = *reinterpret_cast<CRio_vtbl**>(offset + 0x02);
        if (IsBadReadPtr(vtbl, sizeof(CObject_vtbl))) continue;
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(vtbl->GetRuntimeClass))) continue;
        const auto get = reinterpret_cast<DWORD>(vtbl->GetRuntimeClass);
        // mov     eax, ...
        const auto rtc = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
        if (clazz != rtc) continue;
        address = vtbl;
        break;
    }

    return address;
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
        return nullptr;
    default:
        break;
    }

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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

int CImgBox::DrawFont(
    const DWORD x, const DWORD y, const UINT uChar, COceanNode** const node)
{
    const auto name = "?DrawFont@CImgBox@@QAEHFFIPAVCFontContext@@@Z";
    auto& proc = reinterpret_cast<LPDrawFont&>(cache[name]);
    if (proc != nullptr) return proc(this, x, y, uChar, node);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, name));
            if (proc != nullptr) return proc(this, x, y, uChar, node);
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, MAKEINTRESOURCE(251)));
            if (proc != nullptr) return proc(this, x, y, uChar, node);
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CImgBox::DrawFont(short,short,unsigned int,class CFontContext *)
        return 0;
    default:
        break;
    }

    return 0;
}

void CImgBox::HookDrawFont(
    const HookCallback<LPDrawFont> callback, const LPDrawFont hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawFont@CImgBox@@QAEHFFIPAVCFontContext@@@Z";
    auto& proc = reinterpret_cast<LPDrawFont&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, name));
            if (proc != nullptr) return callback(proc, hook);
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(rvmm, MAKEINTRESOURCE(251)));
            if (proc != nullptr) return callback(proc, hook);
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CImgBox::DrawFont(short,short,unsigned int,class CFontContext *)
    default:
        break;
    }
}

const CRuntimeClass* CMessBox::GetClassCMessBox()
{
    const auto name = "?classCMessBox@CMessBox@@2UCRioRTC@@A";
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
            address = reinterpret_cast<CRuntimeClass*>(GetProcAddress(Vm60, MAKEINTRESOURCE(173)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: static struct CRioRTC CMessBox::classCMessBox
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

void CMessBox::HookAttachTextCore(
    const HookCallback<FARPROC> callback, const CHARACTER_BYTE_SIZE hook) // NOLINT(*-misplaced-const)
{
    const auto address = GetAttachTextCore();
    if (address == nullptr) return;
    const auto clazz = GetClassCMessBox();
    switch (clazz->m_wSchema)
    {
    case 0xE000000Au:
    case 0xE000000Cu:
        if (IS == nullptr)
        {
            auto start = reinterpret_cast<LPBYTE>(address);
            // push    esi
            // call    ...
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0x56u) continue;
                if (offset[0x01] != 0xFFu) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<LPBYTE>(address)) return;
            const auto l0 = start;
            // jz      ...
            const auto l1 = l0 + 0x12 + *reinterpret_cast<int*>(l0 + 0x0E);
            // cmp     ebx, 8179h
            const auto l2 = l0 + 0x1C;

            IS = reinterpret_cast<FARPROC>(l0);
            SINGLE = reinterpret_cast<FARPROC>(l1);
            MULTIPLE = reinterpret_cast<FARPROC>(l2);
        }
        callback(IS, reinterpret_cast<FARPROC>(EbxToEsi));
        break;
    case 0xE000000Fu:
        if (IS == nullptr)
        {
            auto start = reinterpret_cast<LPBYTE>(address);
            // mov     al, bl
            // xor     al, 20h
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0x8Au) continue;
                if (offset[0x01] != 0xC3u) continue;
                if (offset[0x02] != 0x34u) continue;
                if (offset[0x03] != 0x20u) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<LPBYTE>(address)) return;
            const auto l0 = start;
            // ja      ...
            const auto l1 = l0 + 0x0E + *reinterpret_cast<int*>(l0 + 0x0A);
            // cmp     ebx, 8179h
            const auto l2 = l0 + 0x19;

            IS = reinterpret_cast<FARPROC>(l0);
            SINGLE = reinterpret_cast<FARPROC>(l1);
            MULTIPLE = reinterpret_cast<FARPROC>(l2);
        }
        callback(IS, reinterpret_cast<FARPROC>(EbpToEbx));
        break;
    case 0xE0000011u:
        if (IS == nullptr)
        {
            auto start = reinterpret_cast<LPBYTE>(address);
            // mov     al, bl
            // xor     al, 20h
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0x8Au) continue;
                if (offset[0x01] != 0xC3u) continue;
                if (offset[0x02] != 0x34u) continue;
                if (offset[0x03] != 0x20u) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<LPBYTE>(address)) return;
            const auto l0 = start;
            // ja      ...
            const auto l1 = l0 + 0x0E + *reinterpret_cast<int*>(l0 + 0x0A);
            // cmp     ...
            const auto l2 = l0 + 0x17;

            IS = reinterpret_cast<FARPROC>(l0);
            SINGLE = reinterpret_cast<FARPROC>(l1);
            MULTIPLE = reinterpret_cast<FARPROC>(l2);
        }
        callback(IS, reinterpret_cast<FARPROC>(EsiToEbx));
        break;
    default:
        return;
    }
    if (SIZE == nullptr)
    {
        // Attach
        SIZE = hook;
    }
    else
    {
        // Detach
        SIZE = nullptr;
    }
}

FARPROC CMessBox::IS;

FARPROC CMessBox::SINGLE;

FARPROC CMessBox::MULTIPLE;

CRio::CHARACTER_BYTE_SIZE CMessBox::SIZE;

__declspec(naked) void CMessBox::EbxToEsi()
{
    __asm mov ecx, ebx;
    __asm dec ecx;
    __asm push ecx;
    __asm mov ecx, edi;
    __asm call CMessBox::SIZE;
    __asm dec eax;
    __asm test eax, eax;
    __asm jz end;
loc:
    __asm xor ecx, ecx;
    __asm mov cl, [ebx];
    __asm inc ebx;
    __asm shl esi, 8;
    __asm or esi, ecx;
    __asm dec eax;
    __asm test eax, eax;
    __asm jnz loc;
    __asm jmp CMessBox::MULTIPLE;
end:
    __asm jmp CMessBox::SINGLE;
}

__declspec(naked) void CMessBox::EbpToEbx()
{
    __asm mov ecx, ebp;
    __asm dec ecx;
    __asm push ecx;
    __asm mov ecx, esi;
    __asm call CMessBox::SIZE;
    __asm dec eax;
    __asm test eax, eax;
    __asm jz end;
loc:
    __asm xor ecx, ecx;
    __asm mov cl, [ebp];
    __asm inc ebp;
    __asm shl ebx, 8;
    __asm or ebx, ecx;
    __asm dec eax;
    __asm test eax, eax;
    __asm jnz loc;
    __asm jmp CMessBox::MULTIPLE;
end:
    __asm jmp CMessBox::SINGLE;
}

__declspec(naked) void CMessBox::EsiToEbx()
{
    __asm mov ecx, esi;
    __asm dec ecx;
    __asm push ecx;
    __asm mov ecx, edx;
    __asm call CMessBox::SIZE;
    __asm dec eax;
    __asm test eax, eax;
    __asm jz end;
loc:
    __asm xor ecx, ecx;
    __asm mov cl, [esi];
    __asm inc esi;
    __asm shl ebx, 8;
    __asm or ebx, ecx;
    __asm dec eax;
    __asm test eax, eax;
    __asm jnz loc;
    __asm jmp CMessBox::MULTIPLE;
end:
    __asm jmp CMessBox::SINGLE;
}

CMessBox::LPStore& CMessBox::GetStore()
{
    const auto name = "?Store@CHeapHistoryPtr@@QAEXPBXK@Z";
    auto& address = reinterpret_cast<LPStore&>(cache[name]);
    if (address != nullptr) return address;
    const auto Vm60 = GetModuleHandleA("Vm60");
    address = reinterpret_cast<LPStore>(GetProcAddress(Vm60, name));
    if (address != nullptr) return address;
    const auto pfn_AttachTextCore = GetAttachTextCore();
    if (pfn_AttachTextCore == nullptr) return address;
    const auto clazz = GetClassCMessBox();
    switch (clazz->m_wSchema)
    {
    case 0xE000000Au:
    case 0xE000000Cu:
        {
            auto start = reinterpret_cast<LPBYTE>(pfn_AttachTextCore);
            // push    esi
            // call    ...
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0x56u) continue;
                if (offset[0x01] != 0xFFu) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<LPBYTE>(pfn_AttachTextCore)) break;
            // jz      ...
            start = start + 0x12 + *reinterpret_cast<int*>(start + 0x0E);
            // call    ...
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0xE8u) continue;
                address = reinterpret_cast<LPStore>(offset + 0x05 + *reinterpret_cast<int*>(offset + 0x01));
                break;
            }
        }
        break;
    case 0xE000000Fu:
    case 0xE0000011u:
        {
            auto start = reinterpret_cast<LPBYTE>(pfn_AttachTextCore);
            // mov     al, bl
            // xor     al, 20h
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0x8Au) continue;
                if (offset[0x01] != 0xC3u) continue;
                if (offset[0x02] != 0x34u) continue;
                if (offset[0x03] != 0x20u) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<LPBYTE>(pfn_AttachTextCore)) break;
            // ja      ...
            start = start + 0x0E + *reinterpret_cast<int*>(start + 0x0A);
            // call    ...
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                if (offset[0x00] != 0xE8u) continue;
                address = reinterpret_cast<LPStore>(offset + 0x05 + *reinterpret_cast<int*>(offset + 0x01));
                break;
            }
        }
        break;
    default:
        break;
    }

    return address;
}

CMessBox::LPLoad& CMessBox::GetLoad()
{
    const auto name = "?Load@CHeapHistoryPtr@@QAEXPAXK@Z";
    auto& address = reinterpret_cast<LPLoad&>(cache[name]);
    if (address != nullptr) return address;
    const auto Vm60 = GetModuleHandleA("Vm60");
    address = reinterpret_cast<LPLoad>(GetProcAddress(Vm60, name));
    if (address != nullptr) return address;
    const auto pfn_Store = GetStore();
    if (pfn_Store == nullptr) return address;
    const auto start = reinterpret_cast<LPBYTE>(pfn_Store);
    // push    ebx
    // push    ebp
    for (auto offset = start; start - offset < 0x1000; offset--)
    {
        if (offset[0x00] != 0x53u) continue;
        if (offset[0x01] != 0x55u) continue;
        address = reinterpret_cast<LPLoad>(offset);
        break;
    }

    return address;
}

FARPROC CMessBox::GetAttachTextCore()
{
    const auto name = "?AttachTextCore@CMessBox@@QAEXPBD@Z";
    auto& address = cache[name];
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = GetProcAddress(Vm60, name);
            if (address != nullptr) return address;
            const auto pfn_AttachInstructionText = GetAttachInstructionText();
            if (pfn_AttachInstructionText == nullptr) return nullptr;
            auto start = reinterpret_cast<DWORD>(pfn_AttachInstructionText);
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                // indirect table for switch statement
                if (*reinterpret_cast<const DWORD*>(offset + 0x00) != 0x03020100u) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<DWORD>(pfn_AttachInstructionText)) return nullptr;
            for (auto offset = start; start - offset < 0x1000; offset--)
            {
                // mov     large fs:0, esp
                if (*reinterpret_cast<const DWORD*>(offset + 0x00) != 0x00258964u) continue;
                address = reinterpret_cast<FARPROC>(offset - 0x000E);
                break;
            }
            return address;
        }
    case 0x0C00:
        {
            const auto pfn_AttachInstructionText = GetAttachInstructionText();
            if (pfn_AttachInstructionText == nullptr) return address;
            auto start = reinterpret_cast<DWORD>(pfn_AttachInstructionText);
            for (auto offset = start; offset - start < 0x1000; offset++)
            {
                // indirect table for switch statement
                if (*reinterpret_cast<const DWORD*>(offset + 0x00) != 0x03020100u) continue;
                start = offset;
                break;
            }
            if (start == reinterpret_cast<DWORD>(pfn_AttachInstructionText)) return nullptr;
            for (auto offset = start; start - offset < 0x1000; offset--)
            {
                // mov     large fs:0, eax
                if (*reinterpret_cast<const DWORD*>(offset + 0x00) != 0x0000A364u) continue;
                address = reinterpret_cast<FARPROC>(offset - 0x0022);
                break;
            }
            return address;
        }
    case 0x0E00:
        // TODO public: void __thiscall CMessBox::AttachTextCore(char const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

FARPROC CMessBox::GetAttachInstructionText()
{
    const auto name = "?AttachInstructionText@CMessBox@@UAEXPBDVTRio@@1K@Z";
    auto& address = cache[name];
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            address = GetProcAddress(Vm60, name);
            if (address != nullptr) return address;
            const auto clazz = GetClassCMessBox();
            const auto vtbl = GetVisualTable();
            if (vtbl == nullptr) return nullptr;
            switch (clazz->m_wSchema)
            {
            case 0xE000000Au:
                address = reinterpret_cast<const FARPROC*>(vtbl)[0x0060];
                if (address != nullptr) return address;
                break;
            case 0xE000000Cu:
                address = reinterpret_cast<const FARPROC*>(vtbl)[0x005E];
                if (address != nullptr) return address;
                break;
            case 0xE000000Fu:
                address = reinterpret_cast<const FARPROC*>(vtbl)[0x0064];
                if (address != nullptr) return address;
                break;
            case 0xE0000011u:
                address = reinterpret_cast<const FARPROC*>(vtbl)[0x0077];
                if (address != nullptr) return address;
                break;
            default:
                // TODO public: virtual void __thiscall CMessBox::AttachInstructionText(char const *, class TRio, class TRio, unsigned long)
                break;
            }
        }
        break;
    case 0x0E00:
        // TODO public: virtual void __thiscall CMessBox::AttachInstructionText(char const *, class TRio, class TRio, unsigned long)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRio_vtbl* CMessBox::GetVisualTable()
{
    const auto name = "??_7CMessBox@@6B@";
    auto& address = reinterpret_cast<CRio_vtbl*&>(cache[name]);
    if (address != nullptr) return address;
    const auto clazz = GetClassCMessBox();
    if (clazz->m_pfnCreateObject == nullptr) return nullptr;
    auto start = reinterpret_cast<LPBYTE>(clazz->m_pfnCreateObject);
    auto ctor = static_cast<FARPROC>(nullptr);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (offset[0x00] != 0x8B) continue;
        // call    ...
        if (offset[0x02] != 0xE8) continue;
        const auto jump = *reinterpret_cast<int*>(offset + 0x03);
        ctor = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        break;
    }
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
        const auto rtc = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
        if (clazz != rtc) continue;
        address = vtbl;
        break;
    }

    return address;
}

const CArchive* CPmArchive::GetNative()
{
    const auto seek = *reinterpret_cast<const FARPROC**>(this)[0x0000];
    return reinterpret_cast<CArchive*>(reinterpret_cast<DWORD>(this) + reinterpret_cast<BYTE*>(seek)[0x0006]);
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
        return nullptr;
    default:
        break;
    }

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
        return nullptr;
    default:
        break;
    }

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
        // TODO protected: int __thiscall COceanNode::IsDerivedFrom(struct CRioRTC const *)const
        return FALSE;
    default:
        break;
    }

    return FALSE;
}

CRio* COceanNode::Fetch() const
{
    using LPGetPointer = CRio* (__thiscall *)(const COceanNode*);
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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

void COceanNode::Release()
{
    const auto name = "?_ReleaseRef@COceanNode@@QAEXX";
    auto& proc = reinterpret_cast<RELEASE&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<RELEASE>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this);
            proc = reinterpret_cast<RELEASE>(GetProcAddress(UnivUI, MAKEINTRESOURCE(73)));
            if (proc != nullptr) return proc(this);
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall COceanNode::_ReleaseRef(void)
    default:
        break;
    }
}

DWORD COceanNode::GetAddress() const
{
    return m_dwResAddr % 0xA2FB6AD1u;
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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const COceanNode* COceanNode::GetMotherOcean()
{
    const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
    auto& proc = reinterpret_cast<GET&>(cache[name]);
    auto temp = static_cast<COceanNode*>(nullptr);
    if (proc != nullptr) return *proc(&temp);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return *proc(&temp);
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (proc != nullptr) return *proc(&temp);
        }
        break;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean, class CObjectOcean_ome, class TObjectOcean> __cdecl GetMotherOcean(void)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

void COceanNode::HookRelease(const HookCallback<RELEASE> callback, const RELEASE hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?_ReleaseRef@COceanNode@@QAEXXZ";
    auto& proc = reinterpret_cast<RELEASE&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<RELEASE>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return callback(proc, hook);
            proc = reinterpret_cast<RELEASE>(GetProcAddress(UnivUI, MAKEINTRESOURCE(73)));
            if (proc != nullptr) return callback(proc, hook);
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall COceanNode::_ReleaseRef(void)
    default:
        break;
    }
}

void COceanNode::HookGetMotherOcean(const HookCallback<GET> callback, const GET hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
    auto& proc = reinterpret_cast<GET&>(cache[name]);
    if (proc != nullptr) return callback(proc, hook);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return callback(proc, hook);
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (proc != nullptr) return callback(proc, hook);
        }
        break;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean, class CObjectOcean_ome, class TObjectOcean> __cdecl GetMotherOcean(void)
    default:
        break;
    }
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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

int CVmCommand::GetVariableAreaSize() const
{
    using LPGetVariableAreaSize = int (__thiscall *)(const CVmCommand*);
    const auto name = "?GetValiableAreaSize@" + std::string(this->GetRuntimeClass()->m_lpszClassName) + "@@UAEHXZ";
    auto& proc = reinterpret_cast<LPGetVariableAreaSize&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto vtbl = *reinterpret_cast<FARPROC* const*>(this);
    switch (this->GetRuntimeClass()->m_wSchema)
    {
    case 0xA000000Cu:
    case 0xA000000Du:
    case 0xA000000Eu:
        proc = reinterpret_cast<LPGetVariableAreaSize>(vtbl[0x0007]);
        break;
    case 0xA0000011u:
    case 0xA0000012u:
    case 0xA0000013u:
    case 0xA0000014u:
    case 0xA0000015u:
        proc = reinterpret_cast<LPGetVariableAreaSize>(vtbl[0x0009]);
        break;
    default:
        // TODO ?GetValiableAreaSize@CVmCommand@@UAEHXZ
        return 0;
    }
    return proc(this);
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
        return nullptr;
    default:
        break;
    }

    return nullptr;
}
