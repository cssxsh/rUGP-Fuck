#include "stdafx.h"
#include <detours/detours.h>
#include "hook.h"

void Win32Hook::AttachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
#define ATTACH(function) \
        if (pfn##function == nullptr) \
        { \
            pfn##function = &function; \
            wprintf(L"DetourAttach: " #function "\n"); \
            DetourAttach(&reinterpret_cast<PVOID&>(pfn##function), reinterpret_cast<PVOID>(&Hook##function)); \
        }
    ATTACH(CreateWindowExA)
    ATTACH(SetWindowTextA)
    ATTACH(SendMessageA)
    ATTACH(CreatePropertySheetPageA)
    ATTACH(PropertySheetA)
    ATTACH(CreateDialogParamA)
    ATTACH(CreateDialogIndirectParamA)
    ATTACH(DialogBoxParamA)
    ATTACH(DialogBoxIndirectParamA)
    ATTACH(SetDlgItemTextA)
    ATTACH(SendDlgItemMessageA)
    ATTACH(AppendMenuA)
    ATTACH(MessageBoxA)
    ATTACH(MessageBoxExA)
    ATTACH(CreateFontA)
    ATTACH(CreateFontIndirectA)
    ATTACH(EnumFontFamiliesA)
    ATTACH(EnumFontFamiliesExA)
    ATTACH(EnumFontsA)
    ATTACH(GetGlyphOutlineA)
#undef ATTACH
    DetourTransactionCommit();
}

void Win32Hook::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
#define DETACH(function) \
        if (pfn##function != nullptr) \
        { \
            wprintf(L"DetourDetach: " #function "\n"); \
            DetourDetach(&reinterpret_cast<PVOID&>(pfn##function), reinterpret_cast<PVOID>(&Hook##function)); \
            pfn##function = nullptr; \
        }
    DETACH(CreateWindowExA)
    DETACH(SetWindowTextA)
    DETACH(SendMessageA)
    DETACH(CreatePropertySheetPageA)
    DETACH(PropertySheetA)
    DETACH(CreateDialogParamA)
    DETACH(CreateDialogIndirectParamA)
    DETACH(DialogBoxParamA)
    DETACH(DialogBoxIndirectParamA)
    DETACH(SetDlgItemTextA)
    DETACH(SendDlgItemMessageA)
    DETACH(AppendMenuA)
    DETACH(MessageBoxA)
    DETACH(MessageBoxExA)
    DETACH(CreateFontA)
    DETACH(CreateFontIndirectA)
    DETACH(EnumFontFamiliesA)
    DETACH(EnumFontFamiliesExA)
    DETACH(EnumFontsA)
    DETACH(GetGlyphOutlineA)
#undef DETACH
    DetourTransactionCommit();
}

#define DETOUR(function) \
    decltype(function)* Win32Hook::pfn##function = nullptr;
DETOUR(CreateWindowExA)
DETOUR(SetWindowTextA)
DETOUR(SendMessageA)
DETOUR(CreatePropertySheetPageA)
DETOUR(PropertySheetA)
DETOUR(CreateDialogParamA)
DETOUR(CreateDialogIndirectParamA)
DETOUR(DialogBoxParamA)
DETOUR(DialogBoxIndirectParamA)
DETOUR(SetDlgItemTextA)
DETOUR(SendDlgItemMessageA)
DETOUR(AppendMenuA)
DETOUR(MessageBoxA)
DETOUR(MessageBoxExA)
DETOUR(CreateFontA)
DETOUR(CreateFontIndirectA)
DETOUR(EnumFontFamiliesA)
DETOUR(EnumFontFamiliesExA)
DETOUR(EnumFontsA)
DETOUR(GetGlyphOutlineA)
#undef DETOUR

HWND WINAPI Win32Hook::HookCreateWindowExA(
    const DWORD dwExStyle,
    const LPCSTR lpClassName,
    const LPCSTR lpWindowName,
    const DWORD dwStyle,
    const int X,
    const int Y,
    const int nWidth,
    const int nHeight,
    const HWND hWndParent, // NOLINT(*-misplaced-const)
    const HMENU hMenu, // NOLINT(*-misplaced-const)
    const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
    const LPVOID lpParam) // NOLINT(*-misplaced-const)
{
    const auto uuid = Unicode(lpClassName, CP_SHIFT_JIS);
    const auto title = Unicode(lpWindowName, CP_SHIFT_JIS);
    wprintf(L"Hook CreateWindowExA(lpClassName=%s, lpWindowName=%s, dwStyle=%08X)\n", uuid, title, dwStyle);
    const auto result = CreateWindowExW(
        dwExStyle, uuid, title, dwStyle,
        X, Y, nWidth, nHeight,
        hWndParent, hMenu, hInstance,
        lpParam);
    free(uuid);
    free(title);
    return result;
}

BOOL WINAPI Win32Hook::HookSetWindowTextA(
    const HWND hWnd, // NOLINT(*-misplaced-const)
    const LPCSTR lpString)
{
    auto cp = CP_SHIFT_JIS;
    switch (*reinterpret_cast<const DWORD*>(lpString))
    {
    // 標準
    case 0xCA9CCB98u:
        cp = CP_GB18030;
        break;
    default:
        break;
    }
    const auto unicode = Unicode(lpString, cp);
    wprintf(L"Hook SetWindowTextA(hWnd=0x%p, lpString=%s)\n", hWnd, unicode);
    const auto result = SetWindowTextW(hWnd, unicode);
    free(unicode);
    return result;
}

LRESULT Win32Hook::HookSendMessageA(
    const HWND hWnd, // NOLINT(*-misplaced-const)
    const UINT Msg,
    const WPARAM wParam,
    const LPARAM lParam)
{
    switch (Msg)
    {
    case LB_ADDSTRING:
        {
            const auto unicode = Unicode(reinterpret_cast<LPCSTR>(lParam), CP_GB18030);
            wprintf(L"Hook SendMessageA(hWnd=0x%p, Msg=LB_ADDSTRING, lParam=%s)\n", hWnd, unicode);
            const auto result = SendMessageW(hWnd, Msg, wParam, reinterpret_cast<LPARAM>(unicode));
            free(unicode);
            return result;
        }
    case CB_ADDSTRING:
        {
            const auto unicode = Unicode(reinterpret_cast<LPCSTR>(lParam), CP_SHIFT_JIS);
            wprintf(L"Hook SendMessageA(hWnd=0x%p, Msg=CB_ADDSTRING, lParam=%s)\n", hWnd, unicode);
            const auto result = SendMessageW(hWnd, Msg, wParam, reinterpret_cast<LPARAM>(unicode));
            free(unicode);
            return result;
        }
    default:
        // TODO SendMessageW
        return pfnSendMessageA(hWnd, Msg, wParam, lParam);
    }
}

HPROPSHEETPAGE WINAPI Win32Hook::HookCreatePropertySheetPageA(
    const LPCPROPSHEETPAGEA lpPropSheetPage)
{
    auto header = PROPSHEETPAGEW{};
    memcpy(&header, lpPropSheetPage, lpPropSheetPage->dwSize);
    header.pszTitle = Unicode(lpPropSheetPage->pszTitle, CP_SHIFT_JIS);
    const auto result = CreatePropertySheetPageW(&header);
    free(const_cast<LPWSTR&>(header.pszTitle));
    return result;
}

INT_PTR WINAPI Win32Hook::HookPropertySheetA(
    const LPCPROPSHEETHEADERA lpPropSheetHeader)
{
    auto header = PROPSHEETHEADERW{};
    memcpy(&header, lpPropSheetHeader, lpPropSheetHeader->dwSize);
    header.pszCaption = Unicode(lpPropSheetHeader->pszCaption, CP_SHIFT_JIS);
    const auto result = PropertySheetW(&header);
    free(const_cast<LPWSTR&>(header.pszCaption));
    return result;
}

HWND WINAPI Win32Hook::HookCreateDialogParamA(
    const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
    const LPCSTR lpTemplateName,
    const HWND hWndParent, // NOLINT(*-misplaced-const)
    const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
    const LPARAM dwInitParam)
{
    if (IS_INTRESOURCE(lpTemplateName))
    {
        const auto id = reinterpret_cast<DWORD>(lpTemplateName);
        wprintf(L"Hook CreateDialogParamA(lpTemplateName=MAKEINTRESOURCEA(%d), hWndParent=0x%p)\n", id, hWndParent);
        return CreateDialogParamW(
            hInstance,
            reinterpret_cast<LPCWSTR>(lpTemplateName),
            hWndParent,
            lpDialogFunc,
            dwInitParam);
    }

    const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
    wprintf(L"Hook CreateDialogParamA(lpTemplateName=%s, hWndParent=0x%p)\n", unicode, hWndParent);
    const auto result = CreateDialogParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
    free(unicode);
    return result;
}

HWND WINAPI Win32Hook::HookCreateDialogIndirectParamA(
    const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
    const LPCDLGTEMPLATEA lpTemplate,
    const HWND hWndParent, // NOLINT(*-misplaced-const)
    const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
    const LPARAM dwInitParam)
{
    wprintf(L"Hook CreateDialogIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

INT_PTR WINAPI Win32Hook::HookDialogBoxParamA(
    const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
    const LPCSTR lpTemplateName,
    const HWND hWndParent, // NOLINT(*-misplaced-const)
    const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
    const LPARAM dwInitParam)
{
    if (IS_INTRESOURCE(lpTemplateName))
    {
        const auto id = reinterpret_cast<DWORD>(lpTemplateName);
        wprintf(L"Hook DialogBoxParamA(lpTemplateName=MAKEINTRESOURCEA(%d), hWndParent=0x%p)\n", id, hWndParent);
        return DialogBoxParamW(
            hInstance,
            reinterpret_cast<LPCWSTR>(lpTemplateName),
            hWndParent,
            lpDialogFunc,
            dwInitParam);
    }

    const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
    wprintf(L"Hook DialogBoxParamA(lpTemplateName=%s, hWndParent=0x%p)\n", unicode, hWndParent);
    const auto result = DialogBoxParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
    free(unicode);
    return result;
}

INT_PTR WINAPI Win32Hook::HookDialogBoxIndirectParamA(
    const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
    const LPCDLGTEMPLATEA hDialogTemplate, // NOLINT(*-misplaced-const)
    const HWND hWndParent, // NOLINT(*-misplaced-const)
    const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
    const LPARAM dwInitParam)
{
    wprintf(L"Hook DialogBoxIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

BOOL WINAPI Win32Hook::HookSetDlgItemTextA(
    const HWND hDlg, // NOLINT(*-misplaced-const)
    const int nIDDlgItem,
    const LPCSTR lpString)
{
    const auto unicode = Unicode(lpString, CP_SHIFT_JIS);
    wprintf(L"Hook SetDlgItemTextA(hDlg=0x%p, nIDDlgItem=%d, lpString=%s)\n", hDlg, nIDDlgItem, unicode);
    const auto result = SetDlgItemTextW(hDlg, nIDDlgItem, unicode);
    free(unicode);
    return result;
}

LRESULT Win32Hook::HookSendDlgItemMessageA(
    const HWND hDlg, // NOLINT(*-misplaced-const)
    const int nIDDlgItem,
    const UINT Msg,
    const WPARAM wParam,
    const LPARAM lParam)
{
    switch (Msg)
    {
    case LB_ADDSTRING:
    case CB_ADDSTRING:
        {
            const auto unicode = Unicode(reinterpret_cast<LPCSTR>(lParam), CP_SHIFT_JIS);
            wprintf(L"Hook SendDlgItemMessageA(hDlg=0x%p, nIDDlgItem=%d, lParam=%s)\n", hDlg, nIDDlgItem, unicode);
            const auto result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, reinterpret_cast<LPARAM>(unicode));
            free(unicode);
            return result;
        }
    case CBEM_INSERTITEMA:
        {
            const auto pszText = reinterpret_cast<PCOMBOBOXEXITEMA>(lParam)->pszText;
            const auto unicode = Unicode(pszText, CP_SHIFT_JIS);
            wprintf(L"Hook SendDlgItemMessageA(hDlg=0x%p, nIDDlgItem=%d, pszText=%s)\n", hDlg, nIDDlgItem, unicode);
            reinterpret_cast<PCOMBOBOXEXITEMW>(lParam)->pszText = unicode;
            const auto result = SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam);
            reinterpret_cast<PCOMBOBOXEXITEMA>(lParam)->pszText = pszText;
            free(unicode);
            return result;
        }
    default:
        return SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam);
    }
}

BOOL Win32Hook::HookAppendMenuA(
    const HMENU hMenu, // NOLINT(*-misplaced-const)
    const UINT uFlags,
    const UINT_PTR uIDNewItem,
    const LPCSTR lpNewItem)
{
    if (uFlags & MF_BITMAP) return AppendMenuW(hMenu, uFlags, uIDNewItem, reinterpret_cast<LPCWSTR>(lpNewItem));
    if (uFlags & MF_OWNERDRAW) return AppendMenuW(hMenu, uFlags, uIDNewItem, reinterpret_cast<LPCWSTR>(lpNewItem));
    const auto unicode = Unicode(lpNewItem, CP_SHIFT_JIS);
    wprintf(L"Hook AppendMenuA(hMenu=0x%p, uIDNewItem=%d, lpNewItem=%s)\n", hMenu, uIDNewItem, unicode);
    const auto result = AppendMenuW(hMenu, uFlags, uIDNewItem, unicode);
    free(unicode);
    return result;
}

int WINAPI Win32Hook::HookMessageBoxA(
    const HWND hWnd, // NOLINT(*-misplaced-const)
    const LPCSTR lpText,
    const LPCSTR lpCaption,
    const UINT uType)
{
    const auto text = Unicode(lpText, CP_SHIFT_JIS);
    const auto caption = Unicode(lpCaption, CP_SHIFT_JIS);
    wprintf(L"Hook MessageBoxA(lpCaption=%s, lpText=%s)\n", caption, text);
    const auto result = MessageBoxW(hWnd, text, caption, uType);
    free(text);
    free(caption);
    return result;
}

int WINAPI Win32Hook::HookMessageBoxExA(
    const HWND hWnd, // NOLINT(*-misplaced-const)
    const LPCSTR lpText,
    const LPCSTR lpCaption,
    const UINT uType,
    const WORD wLanguageId)
{
    const auto text = Unicode(lpText, CP_SHIFT_JIS);
    const auto caption = Unicode(lpCaption, CP_SHIFT_JIS);
    wprintf(L"Hook MessageBoxExA(lpCaption=%s, lpText=%s)\n", caption, text);
    const auto result = MessageBoxExW(hWnd, text, caption, uType, wLanguageId);
    free(text);
    free(caption);
    return result;
}

HFONT WINAPI Win32Hook::HookCreateFontA(
    const int cHeight,
    const int cWidth,
    const int cEscapement,
    const int cOrientation,
    const int cWeight,
    const DWORD bItalic,
    const DWORD bUnderline,
    const DWORD bStrikeOut,
    const DWORD iCharSet,
    const DWORD iOutPrecision,
    const DWORD iClipPrecision,
    const DWORD iQuality,
    const DWORD iPitchAndFamily,
    const LPCSTR pszFaceName)
{
    auto cp = CP_ACP;
    switch (*reinterpret_cast<const DWORD*>(pszFaceName))
    {
    // ＭＳ
    case 0x72826C82u:
    // FOT-
    case 0x2D544F46u:
        cp = CP_SHIFT_JIS;
        break;
    default:
        break;
    }
    const auto unicode = Unicode(pszFaceName, cp);
    wprintf(L"Hook CreateFontA(iCharSet=0x%X, pszFaceName=%s)\n", iCharSet, unicode);
    const auto result = CreateFontW(
        cHeight, cWidth, cEscapement, cOrientation, cWeight,
        bItalic, bUnderline, bStrikeOut,
        GB2312_CHARSET, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily,
        unicode);
    free(unicode);
    return result;
}

HFONT WINAPI Win32Hook::HookCreateFontIndirectA(
    const LOGFONTA* lpLogFont)
{
    auto font = LOGFONTW
    {
        lpLogFont->lfHeight,
        lpLogFont->lfWidth,
        lpLogFont->lfEscapement,
        lpLogFont->lfOrientation,
        lpLogFont->lfWeight,
        lpLogFont->lfItalic,
        lpLogFont->lfUnderline,
        lpLogFont->lfStrikeOut,
        lpLogFont->lfCharSet,
        lpLogFont->lfOutPrecision,
        lpLogFont->lfClipPrecision,
        lpLogFont->lfQuality,
        lpLogFont->lfPitchAndFamily
    };
    auto cp = CP_ACP;
    switch (*reinterpret_cast<const DWORD*>(lpLogFont->lfFaceName))
    {
    // ＭＳ
    case 0x72826C82u:
    // FOT-
    case 0x2D544F46u:
        cp = CP_SHIFT_JIS;
        break;
    default:
        break;
    }
    const auto unicode = Unicode(lpLogFont->lfFaceName, cp);
    wcscpy(font.lfFaceName, unicode);
    free(unicode);
    wprintf(L"Hook CreateFontIndirectA(lfCharSet=0x%X, lfFaceName=%s)\n", font.lfCharSet, font.lfFaceName);
    font.lfCharSet = GB2312_CHARSET;
    return CreateFontIndirectW(&font);
}

int WINAPI Win32Hook::HookEnumFontFamiliesA(
    const HDC hdc, // NOLINT(*-misplaced-const)
    const LPCSTR lpLogFont,
    const FONTENUMPROCA lpProc,
    const LPARAM lParam)
{
    const auto context = HookEnumFontContext{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    wprintf(L"Hook EnumFontFamiliesA(lpLogFont=%s)\n", unicode);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontCallback, reinterpret_cast<LPARAM>(&context));
    free(unicode);
    return result;
}

int WINAPI Win32Hook::HookEnumFontFamiliesExA(
    const HDC hdc, // NOLINT(*-misplaced-const)
    const LPLOGFONTA lpLogFont, // NOLINT(*-misplaced-const)
    const FONTENUMPROCA lpProc,
    const LPARAM lParam,
    const DWORD dwFlags)
{
    const auto context = HookEnumFontContext{lpProc, lParam};
    auto font = LOGFONTW
    {
        lpLogFont->lfHeight,
        lpLogFont->lfWidth,
        lpLogFont->lfEscapement,
        lpLogFont->lfOrientation,
        lpLogFont->lfWeight,
        lpLogFont->lfItalic,
        lpLogFont->lfUnderline,
        lpLogFont->lfStrikeOut,
        lpLogFont->lfCharSet,
        lpLogFont->lfOutPrecision,
        lpLogFont->lfClipPrecision,
        lpLogFont->lfQuality,
        lpLogFont->lfPitchAndFamily
    };
    const auto unicode = Unicode(lpLogFont->lfFaceName, CP_SHIFT_JIS);;
    wcscpy(font.lfFaceName, unicode);
    free(unicode);
    wprintf(L"Hook EnumFontFamiliesExA(lfCharSet=0x%X, lfFaceName=%s)\n", font.lfCharSet, font.lfFaceName);
    font.lfCharSet = GB2312_CHARSET;
    return EnumFontFamiliesExW(hdc, &font, &HookEnumFontCallback, reinterpret_cast<LPARAM>(&context), dwFlags);
}

int WINAPI Win32Hook::HookEnumFontsA(
    const HDC hdc, // NOLINT(*-misplaced-const)
    const LPCSTR lpLogFont,
    const FONTENUMPROCA lpProc,
    const LPARAM lParam)
{
    const auto context = HookEnumFontContext{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    wprintf(L"Hook EnumFontsA(lpLogFont=%s)\n", unicode);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontCallback, reinterpret_cast<LPARAM>(&context));
    free(unicode);
    return result;
}

DWORD WINAPI Win32Hook::HookGetGlyphOutlineA(
    const HDC hdc, // NOLINT(*-misplaced-const)
    const UINT uChar,
    const UINT fuFormat,
    const LPGLYPHMETRICS lpgm, // NOLINT(*-misplaced-const)
    const DWORD cjBuffer,
    const LPVOID pvBuffer, // NOLINT(*-misplaced-const)
    const MAT2* lpmat2)
{
    wprintf(L"Hook GetGlyphOutlineA(hdc=0x%p, uChar=0x%08X)\n", hdc, uChar);
    UINT unicode = uChar;
    if (uChar <= 0x000000FF)
    {
        char buffer[1];
        buffer[0] = static_cast<char>((uChar & 0x000000FFu) >> 0x00);
        MultiByteToWideChar(CP_GB18030, 0, buffer, -1, reinterpret_cast<LPWSTR>(&unicode), 1);
    }
    else if (uChar <= 0x0000FFFF)
    {
        char buffer[2];
        buffer[0] = static_cast<char>((uChar & 0x0000FF00u) >> 0x08);
        buffer[1] = static_cast<char>((uChar & 0x000000FFu) >> 0x00);
        MultiByteToWideChar(CP_GB18030, 0, buffer, -1, reinterpret_cast<LPWSTR>(&unicode), 1);
    }
    else
    {
        char buffer[4];
        buffer[0] = static_cast<char>((uChar & 0xFF000000u) >> 0x18);
        buffer[1] = static_cast<char>((uChar & 0x00FF0000u) >> 0x10);
        buffer[2] = static_cast<char>((uChar & 0x0000FF00u) >> 0x08);
        buffer[3] = static_cast<char>((uChar & 0x000000FFu) >> 0x00);
        MultiByteToWideChar(CP_GB18030, 0, buffer, -1, reinterpret_cast<LPWSTR>(&unicode), 1);
    }
    return GetGlyphOutlineW(hdc, unicode, fuFormat, lpgm, cjBuffer, pvBuffer, lpmat2);
}

int CALLBACK Win32Hook::HookEnumFontCallback(
    const LOGFONTW* lpLogFont,
    const TEXTMETRICW* lpTextMetric,
    const DWORD dwFontType,
    const LPARAM lParam)
{
    const auto context = reinterpret_cast<HookEnumFontContext*>(lParam);
    auto font = LOGFONTA
    {
        lpLogFont->lfHeight,
        lpLogFont->lfWidth,
        lpLogFont->lfEscapement,
        lpLogFont->lfOrientation,
        lpLogFont->lfWeight,
        lpLogFont->lfItalic,
        lpLogFont->lfUnderline,
        lpLogFont->lfStrikeOut,
        lpLogFont->lfCharSet,
        lpLogFont->lfOutPrecision,
        lpLogFont->lfClipPrecision,
        lpLogFont->lfQuality,
        lpLogFont->lfPitchAndFamily
    };
    const auto ansi = Ansi(lpLogFont->lfFaceName, CP_GB18030);
    strcpy(font.lfFaceName, ansi);
    free(ansi);
    const auto metric = TEXTMETRICA
    {
        lpTextMetric->tmHeight,
        lpTextMetric->tmAscent,
        lpTextMetric->tmDescent,
        lpTextMetric->tmInternalLeading,
        lpTextMetric->tmExternalLeading,
        lpTextMetric->tmAveCharWidth,
        lpTextMetric->tmMaxCharWidth,
        lpTextMetric->tmWeight,
        lpTextMetric->tmOverhang,
        lpTextMetric->tmDigitizedAspectX,
        lpTextMetric->tmDigitizedAspectY,
        '\0',
        '\0',
        '\0',
        '\0',
        lpTextMetric->tmItalic,
        lpTextMetric->tmUnderlined,
        lpTextMetric->tmStruckOut,
        lpTextMetric->tmPitchAndFamily,
        lpTextMetric->tmCharSet
    };
    return context->lpProc(&font, &metric, dwFontType, context->lParam);
}
