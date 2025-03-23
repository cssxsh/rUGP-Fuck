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

void CRio::LibrarySupport(AFX_EXTENSION_MODULE& module)
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto proc = reinterpret_cast<REG>(cache[name]);
    if (proc != nullptr) return proc(module);
    const auto UnivUI = GetModuleHandleA("UnivUI");
    if (UnivUI == nullptr) return;
    proc = reinterpret_cast<REG>(cache[name] = GetProcAddress(UnivUI, name));
    if (proc != nullptr) return proc(module);
}

FARPROC CRio::HookLibrarySupport(const HookProc<REG> callback, const REG hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto proc = reinterpret_cast<REG>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto UnivUI = GetModuleHandleA("UnivUI");
    if (UnivUI == nullptr) return nullptr;
    proc = reinterpret_cast<REG>(cache[name] = GetProcAddress(UnivUI, name));
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
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

const CRuntimeClass* CRip::GetClassCRip()
{
    const auto name = "?classCRip@CRip@@2UCRioRTC@@A";
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
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(845)));
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
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(851)));
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

DWORD CS5i::DrawFont(
    const DWORD x, const DWORD y, WORD* const rect, WORD* const out, const UINT uChar, COceanNode** const node)
{
    const auto name = "?DrawFont@CS5i@@QAEHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto proc = reinterpret_cast<LPDrawFont>(cache[name]);
    if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return proc(this, x, y, rect, out, uChar, node);
            const auto start = reinterpret_cast<WORD* const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                if (**offset != 0xFF6Au) continue;
                proc = reinterpret_cast<LPDrawFont>(*(offset - 0x00));
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

FARPROC CS5i::HookDrawSzText(
    const HookProc<LPDrawSzText> callback, const LPDrawSzText hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawSzText@CS5i@@QAEXFFPBDPBVCFontContext@@@Z";
    auto proc = reinterpret_cast<LPDrawSzText>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawSzText>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            const auto start = reinterpret_cast<WORD* const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                if (**offset != 0xFF6Au) continue;
                proc = reinterpret_cast<LPDrawSzText>(*(offset - 0x02));
                break;
            }
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CS5i::DrawSzText(short, short, char const *, class CFontContext const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

FARPROC CS5i::HookDrawSzTextClip(
    const HookProc<LPDrawSzTextClip> callback, const LPDrawSzTextClip hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawSzTextClip@CS5i@@QAEXFFPBDPBVCFontContext@@PBUtagRBDY@@@Z";
    auto proc = reinterpret_cast<LPDrawSzTextClip>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawSzTextClip>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            const auto start = reinterpret_cast<WORD* const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                if (**offset != 0xFF6Au) continue;
                proc = reinterpret_cast<LPDrawSzTextClip>(*(offset - 0x01));
                break;
            }
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CS5i::DrawSzTextClip(short, short, char const *, class CFontContext const *, struct tagRBDY const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

FARPROC CS5i::HookDrawFont(
    const HookProc<LPDrawFont> callback, const LPDrawFont hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawFont@CS5i@@QAEHFFPBUtagRBDY@@PAUSQRBDY@@IPBVCFontContext@@@Z";
    auto proc = reinterpret_cast<LPDrawFont>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPDrawFont>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            const auto start = reinterpret_cast<WORD* const*>(GetVisualTable());
            if (start == nullptr) break;
            for (auto offset = start; start - offset < 0x0400; offset--)
            {
                if (**offset != 0xFF6Au) continue;
                proc = reinterpret_cast<LPDrawFont>(*(offset - 0x00));
                break;
            }
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
        }
        break;
    case 0x0E00:
        // TODO public: int __thiscall CS5i::DrawFont(short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CObjectEx_vtbl* CS5i::GetVisualTable()
{
    const auto name = "??_7CS5i@@6BCVisual@@@";
    auto address = reinterpret_cast<CObjectEx_vtbl*>(cache[name]);
    if (address != nullptr) return address;
    const auto clazz = GetClassCS5i();
    if (clazz->m_pfnCreateObject == nullptr) return nullptr;
    auto start = reinterpret_cast<DWORD>(clazz->m_pfnCreateObject);
    auto ctor = static_cast<FARPROC>(nullptr);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
        // call    ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
        const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
        ctor = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        break;
    }
    start = reinterpret_cast<DWORD>(ctor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     dword ptr [*], ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0xC7) continue;
        address = *reinterpret_cast<CObjectEx_vtbl**>(offset + 0x02);
        if (IsBadReadPtr(address, sizeof(CObject_vtbl))) continue;
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(address->GetRuntimeClass))) continue;
        const auto get = reinterpret_cast<DWORD>(address->GetRuntimeClass);
        // mov     eax, ...
        const auto rtc = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
        if (clazz != rtc) continue;
        cache[name] = reinterpret_cast<FARPROC>(address);
        break;
    }

    return address;
}

const CRuntimeClass* CUI::GetClassCUI()
{
    const auto name = "?classCUI@CUI@@2UCRioRTC@@A";
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(rvmm, MAKEINTRESOURCE(639)));
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
    auto address = reinterpret_cast<CRuntimeClass*>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(rvmm, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(rvmm, MAKEINTRESOURCE(613)));
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

DWORD CImgBox::DrawFont(const DWORD x, const DWORD y, const UINT uChar, COceanNode** node)
{
    const auto name = "?DrawSzText@CImgBox@@QAEXFFPBDPAVCFontContext@@@Z";
    auto proc = reinterpret_cast<LPDrawFont>(cache[name]);
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
            proc = reinterpret_cast<LPDrawFont>(cache[name] = GetProcAddress(rvmm, MAKEINTRESOURCE(251)));
            if (proc != nullptr) return proc(this, x, y, uChar, node);
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CImgBox::DrawSzText(short, short, char const *, class CFontContext *)
        return 0;
    default:
        break;
    }

    return 0;
}

FARPROC CImgBox::HookDrawSzText(
    const HookProc<LPDrawSzText> callback, const LPDrawSzText hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?DrawSzText@CImgBox@@QAEXFFPBDPAVCFontContext@@@Z";
    auto proc = reinterpret_cast<LPDrawSzText>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto rvmm = GetModuleHandleA("rvmm");
            proc = reinterpret_cast<LPDrawSzText>(GetProcAddress(rvmm, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            proc = reinterpret_cast<LPDrawSzText>(cache[name] = GetProcAddress(rvmm, MAKEINTRESOURCE(265)));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CImgBox::DrawSzText(short, short, char const *, class CFontContext *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CRuntimeClass* CMessBox::GetClassCMessBox()
{
    const auto name = "?classCMessBox@CMessBox@@2UCRioRTC@@A";
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
            address = reinterpret_cast<CRuntimeClass*>(cache[name] = GetProcAddress(Vm60, MAKEINTRESOURCE(173)));
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

FARPROC CMessBox::HookAttachTextCore(
    const HookProc<LPAttachTextCore> callback, const LPAttachTextCore hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?AttachTextCore@CMessBox@@QAEXPBD@Z";
    auto proc = reinterpret_cast<LPAttachTextCore>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto Vm60 = GetModuleHandleA("Vm60");
            proc = reinterpret_cast<LPAttachTextCore>(GetProcAddress(Vm60, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            const auto clazz = GetClassCMessBox();
            const auto vtbl = GetVisualTable();
            if (vtbl == nullptr) break;
            auto temp = static_cast<FARPROC>(nullptr);
            // TODO ?AttachInstructionText@CMessBox@@UAEXPBDVTRio@@1K@Z
            switch (clazz->m_wSchema)
            {
            case 0xE000000Fu:
                temp = reinterpret_cast<const FARPROC*>(vtbl)[0x0064];
                break;
            case 0xE0000011u:
                temp = reinterpret_cast<const FARPROC*>(vtbl)[0x0077];
            default:
                break;
            }
            if (temp == nullptr) break;
            const auto start = reinterpret_cast<DWORD>(temp);
            auto count = 0;
            for (auto offset = start; offset - start < 0x4000; offset++)
            {
                // align 10h
                if (*reinterpret_cast<const WORD*>(offset) != 0x9090u &&
                    *reinterpret_cast<const WORD*>(offset) != 0xCCCCu)
                    continue;
                while (*reinterpret_cast<const BYTE*>(offset) == 0x90u ||
                    *reinterpret_cast<const BYTE*>(offset) == 0xCCu)
                    offset++;
                if (++count != 2) continue;
                proc = reinterpret_cast<LPAttachTextCore>(offset);
                break;
            }
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
        }
        break;
    case 0x0E00:
        // TODO public: void __thiscall CMessBox::AttachTextCore(char const *)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

const CObjectEx_vtbl* CMessBox::GetVisualTable()
{
    const auto name = "??_7CMessBox@@6B@";
    auto address = reinterpret_cast<CObjectEx_vtbl*>(cache[name]);
    if (address != nullptr) return address;
    const auto clazz = GetClassCMessBox();
    if (clazz->m_pfnCreateObject == nullptr) return nullptr;
    auto start = reinterpret_cast<DWORD>(clazz->m_pfnCreateObject);
    auto ctor = static_cast<FARPROC>(nullptr);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     ecx, ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0x8B) continue;
        // call    ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x02) != 0xE8) continue;
        const auto jump = *reinterpret_cast<const INT*>(offset + 0x03);
        ctor = reinterpret_cast<FARPROC>(offset + 0x07 + jump);
        break;
    }
    start = reinterpret_cast<DWORD>(ctor);
    for (auto offset = start; offset - start < 0x0400; offset++)
    {
        // mov     dword ptr [*], ...
        if (*reinterpret_cast<const BYTE*>(offset + 0x00) != 0xC7) continue;
        address = *reinterpret_cast<CObjectEx_vtbl**>(offset + 0x02);
        if (IsBadReadPtr(address, sizeof(CObject_vtbl))) continue;
        if (IsBadCodePtr(reinterpret_cast<FARPROC>(address->GetRuntimeClass))) continue;
        const auto get = reinterpret_cast<DWORD>(address->GetRuntimeClass);
        // mov     eax, ...
        const auto rtc = *reinterpret_cast<const CRuntimeClass* const*>(get + 0x01);
        if (clazz != rtc) continue;
        cache[name] = reinterpret_cast<FARPROC>(address);
        break;
    }

    return address;
}

CPmArchive* CPmArchive::CreateLoadFilePmArchive(const LPCSTR path)
{
    using LPLoadFilePmArchive = CPmArchive* (__cdecl *)(LPCSTR path);
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
    using LPSaveFilePmArchive = CPmArchive* (__cdecl *)(LPCSTR path, SIZE_T);
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
    using LPIsDerivedFrom = BOOL (__thiscall *)(const COceanNode*, const CRuntimeClass*);
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
    using LPGetPointer = CRio* (__thiscall *)(const COceanNode*);
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
    using LPGetRoot = COceanNode* (__cdecl *)();
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

const COceanNode* COceanNode::GetMotherOcean()
{
    const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
    auto proc = reinterpret_cast<GET>(cache[name]);
    auto temp = static_cast<COceanNode*>(nullptr);
    if (proc != nullptr) return *proc(&temp);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<GET>(cache[name] = GetProcAddress(UnivUI, name));
            if (proc != nullptr) return *proc(&temp);
            proc = reinterpret_cast<GET>(cache[name] = GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (proc != nullptr) return *proc(&temp);
        }
        break;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean,class CObjectOcean_ome,class TObjectOcean> __cdecl GetMotherOcean(void)
        return nullptr;
    default:
        break;
    }

    return nullptr;
}

FARPROC COceanNode::HookGetMotherOcean(const HookProc<GET> callback, const GET hook) // NOLINT(*-misplaced-const)
{
    const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
    auto proc = reinterpret_cast<GET>(cache[name]);
    if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
            proc = reinterpret_cast<GET>(GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (proc != nullptr) return cache[name] = reinterpret_cast<FARPROC>(callback(proc, hook));
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

int CVmCommand::GetVariableAreaSize() const
{
    // TODO ?GetValiableAreaSize@CVmCommand@@UAEHXZ
    using GetVariableAreaSize = int (__thiscall *)(const CVmCommand*);
    const auto name = "?GetValiableAreaSize@" + std::string(this->GetRuntimeClass()->m_lpszClassName) + "@@UAEHXZ";
    auto proc = reinterpret_cast<GetVariableAreaSize>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto vtbl = *reinterpret_cast<FARPROC* const*>(this);
    const auto index = (this->GetRuntimeClass()->m_wSchema & 0xFFFF) > 0x000E ? 0x09 : 0x07;
    proc = reinterpret_cast<GetVariableAreaSize>(cache[name] = vtbl[index]);
    return proc(this);
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
