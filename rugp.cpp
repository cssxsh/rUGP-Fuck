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

CStringX& CStringX::operator=(const LPCSTR pszSrc)
{
    using LPSet = CStringX& (__thiscall *)(CStringX*, LPCSTR);
    const auto mfc = GetMfc();
    auto proc = static_cast<LPSet>(nullptr);
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(860)));
        if (proc != nullptr) proc(this, pszSrc);
        break;
    case 0x0C00:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1517)));
        if (proc != nullptr) proc(this, pszSrc);
        break;
    case 0x0E00:
        proc = reinterpret_cast<LPSet>(GetProcAddress(mfc.native, MAKEINTRESOURCE(1526)));
        if (proc != nullptr) proc(this, pszSrc);
        break;
    default:
        break;
    }

    return *this;
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

    return nullptr;
}

CRio::REG& CRio::FetchLibrarySupport()
{
    const auto name = "?RegistLibrarySupportRio@@YAXAAUAFX_EXTENSION_MODULE@@@Z";
    auto& address = reinterpret_cast<REG&>(cache[name]);
    if (address != nullptr) return address;
    const auto UnivUI = GetModuleHandleA("UnivUI");
    if (UnivUI == nullptr) return address = nullptr;
    return address = reinterpret_cast<REG>(GetProcAddress(UnivUI, name));
}

CRio::IS_MULTIPLE& CRio::FetchIsMultiple()
{
    const auto name = "?IsDBCS@@YAHD@Z";
    auto& address = reinterpret_cast<IS_MULTIPLE&>(cache[name]);
    if (address != nullptr) return address;
    const auto GMfc = GetModuleHandleA("GMfc");
    if (GMfc == nullptr) return address = nullptr;
    return address = reinterpret_cast<IS_MULTIPLE>(GetProcAddress(GMfc, name));
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

    return nullptr;
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
            if (address != nullptr) return address;
        }
        break;
    case 0x0C00:
    case 0x0E00:
        // @see FetchDrawFont2
    default:
        break;
    }

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
        break;
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
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO public: int * __thiscall CS5i::DrawFont(int *, short, short, struct tagRBDY const *, struct SQRBDY *, unsigned int, class CFontContext const *)
    default:
        break;
    }

    return address = nullptr;
}

CS5i* CS5i::Match(LPVOID const part) // NOLINT(*-misplaced-const)
{
    const auto vtbl = GetVisualTable();
    const auto start = static_cast<CRio_vtbl**>(part);
    for (auto offset = start; start - offset < 0x0400; offset--)
    {
        if (IsBadReadPtr(part, sizeof(CRio_vtbl*))) break;
        if (*offset != vtbl) continue;
        return reinterpret_cast<CS5i*>(offset);
    }

    return nullptr;
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
        return address;
    }

    return nullptr;
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

    return address = nullptr;
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
        // TODO protected: int __thiscall COceanNode::IsDerivedFrom(struct CRioRTC const *) const
    default:
        break;
    }

    return FALSE;
}

CRio* COceanNode::FetchRef()
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
}

DWORD COceanNode::GetAddress() const
{
    const auto globals = CUuiGlobals::GetGlobal();
    if (globals == nullptr) return m_dwResAddr;
    return m_dwResAddr % globals->m_dwResOffset;
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
                const auto address = reinterpret_cast<LPBYTE>(is_root);
                // cmp     ecx, offset ...
                return *reinterpret_cast<const COceanNode**>(address + 0x04);
            }
            proc = reinterpret_cast<LPGetRoot>(GetProcAddress(UnivUI, MAKEINTRESOURCE(500)));
            if (proc != nullptr) return proc();
        }
        break;
    case 0x0E00:
        // TODO public: static class COceanNode * __cdecl COceanNode::GetRoot(void)
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
    default:
        break;
    }

    return nullptr;
}

COceanNode::LPGetMotherOcean& COceanNode::FetchGetMotherOcean()
{
    const auto name = "?GetMotherOcean@@YA?AV?$CRef@VCObjectOcean@@VCObjectOcean_ome@@VTObjectOcean@@@@XZ";
    auto& address = reinterpret_cast<LPGetMotherOcean&>(cache[name]);
    if (address != nullptr) return address;
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            address = reinterpret_cast<LPGetMotherOcean>(GetProcAddress(UnivUI, name));
            if (address != nullptr) return address;
            address = reinterpret_cast<LPGetMotherOcean>(GetProcAddress(UnivUI, MAKEINTRESOURCE(499)));
            if (address != nullptr) return address;
        }
        break;
    case 0x0E00:
        // TODO class CRef<class CObjectOcean, class CObjectOcean_ome, class TObjectOcean> __cdecl GetMotherOcean(void)
    default:
        break;
    }

    return address = nullptr;
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

    return nullptr;
}

std::string CRioMsg::ToMsgString()
{
    using LPToMsgString = LPVOID (__thiscall *)(CRioMsg*, LPVOID);
    const auto name = "?ToMsgString@CRioMsg@@QAE?AVCProfile@@XZ";
    auto& proc = reinterpret_cast<LPToMsgString&>(cache[name]);
    const auto build = [&proc, this]
    {
        LPCSTR buffer[0x02];
        proc(this, buffer);
        const auto result = std::string(*buffer);
        using LPDestructor = void (__thiscall *)(LPVOID);
        const auto GMfc = GetModuleHandleA("GMfc");
        const auto destructor = reinterpret_cast<LPDestructor>(GetProcAddress(GMfc, "??1CProfile@@QAE@XZ"));
        destructor(buffer);
        return result;
    };
    if (proc != nullptr) return build();
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
    case 0x0C00:
        {
            const auto UnivUI = GetModuleHandleA("UnivUI");
            proc = reinterpret_cast<LPToMsgString>(GetProcAddress(UnivUI, name));
            if (proc != nullptr) return build();
            proc = reinterpret_cast<LPToMsgString>(GetProcAddress(UnivUI, MAKEINTRESOURCE(750)));
            if (proc != nullptr) return build();
        }
        break;
    case 0x0E00:
        // TODO public: class CProfile __thiscall CRioMsg::ToMsgString(void)
    default:
        break;
    }

    return "";
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

    return nullptr;
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

    return nullptr;
}

CVmCommand* CCommandRef::GetNextCommand()
{
    using LPGetNextCommand = CVmCommand*(__thiscall *)(CCommandRef*);
    const auto clazz = this->GetRuntimeClass();
    const auto name = "?GetNextCommand@" + std::string(clazz->m_lpszClassName) + "@@UBEPAVCVmCommand@@XZ";
    auto& proc = reinterpret_cast<LPGetNextCommand&>(cache[name]);
    if (proc != nullptr) return proc(this);
    const auto vtbl = *reinterpret_cast<FARPROC* const*>(this);
    const auto mfc = GetMfc();
    switch (mfc.version)
    {
    case 0x0600:
        proc = reinterpret_cast<LPGetNextCommand>(vtbl[0x000B]);
        return proc(this);
    case 0x0C00:
        proc = reinterpret_cast<LPGetNextCommand>(vtbl[0x000C]);
        return proc(this);
    default:
        // TODO ?GetNextCommand@CCommandRef@@UBEPAVCVmCommand@@XZ
        break;
    }

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

    if (m_pNext != nullptr)
    {
        // The memory is continuous by CHeap.
        return reinterpret_cast<int>(m_pNext) - reinterpret_cast<int>(this) - clazz->m_nObjectSize;
    }

    return 0;
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

    return nullptr;
}
