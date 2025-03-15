#include <stdafx.h>
#include <detours.h>
#include "hook.h"

void Win32Hook::AttachHook()
{
    // TODO: GetGlyphOutlineA
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    if (pfnCreateWindowExA == nullptr)
    {
        pfnCreateWindowExA = CreateWindowExA;
        printf("DetourAttach: CreateWindowExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateWindowExA), HookCreateWindowExA);
    }
    if (pfnCreateMDIWindowA == nullptr)
    {
        pfnCreateMDIWindowA = CreateMDIWindowA;
        printf("DetourAttach: CreateMDIWindowA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateMDIWindowA), HookCreateMDIWindowA);
    }
    if (pfnSetWindowTextA == nullptr)
    {
        pfnSetWindowTextA = SetWindowTextA;
        printf("DetourAttach: SetWindowTextA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnSetWindowTextA), HookSetWindowTextA);
    }
    if (pfnCreatePropertySheetPageA == nullptr)
    {
        pfnCreatePropertySheetPageA = CreatePropertySheetPageA;
        printf("DetourAttach: CreatePropertySheetPageA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreatePropertySheetPageA), HookCreatePropertySheetPageA);
    }
    if (pfnPropertySheetA == nullptr)
    {
        pfnPropertySheetA = PropertySheetA;
        printf("DetourAttach: PropertySheetA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnPropertySheetA), HookPropertySheetA);
    }
    if (pfnCreateDialogParamA == nullptr)
    {
        pfnCreateDialogParamA = CreateDialogParamA;
        printf("DetourAttach: CreateDialogParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateDialogParamA), HookCreateDialogParamA);
    }
    if (pfnCreateDialogIndirectParamA == nullptr)
    {
        pfnCreateDialogIndirectParamA = CreateDialogIndirectParamA;
        printf("DetourAttach: CreateDialogIndirectParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateDialogIndirectParamA), HookCreateDialogIndirectParamA);
    }
    if (pfnDialogBoxParamA == nullptr)
    {
        pfnDialogBoxParamA = DialogBoxParamA;
        printf("DetourAttach: DialogBoxParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnDialogBoxParamA), HookDialogBoxParamA);
    }
    if (pfnDialogBoxIndirectParamA == nullptr)
    {
        pfnDialogBoxIndirectParamA = DialogBoxIndirectParamA;
        printf("DetourAttach: DialogBoxIndirectParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnDialogBoxIndirectParamA), HookDialogBoxIndirectParamA);
    }
    if (pfnSetDlgItemTextA == nullptr)
    {
        pfnSetDlgItemTextA = SetDlgItemTextA;
        printf("DetourAttach: SetDlgItemTextA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnSetDlgItemTextA), HookSetDlgItemTextA);
    }
    if (pfnMessageBoxA == nullptr)
    {
        pfnMessageBoxA = MessageBoxA;
        printf("DetourAttach: MessageBoxA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnMessageBoxA), HookMessageBoxA);
    }
    if (pfnMessageBoxExA == nullptr)
    {
        pfnMessageBoxExA = MessageBoxExA;
        printf("DetourAttach: MessageBoxExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnMessageBoxExA), HookMessageBoxExA);
    }
    if (pfnCreateFontA == nullptr)
    {
        pfnCreateFontA = CreateFontA;
        printf("DetourAttach: CreateFontA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateFontA), HookCreateFontA);
    }
    if (pfnCreateFontIndirectA == nullptr)
    {
        pfnCreateFontIndirectA = CreateFontIndirectA;
        printf("DetourAttach: CreateFontIndirectA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateFontIndirectA), HookCreateFontIndirectA);
    }
    if (pfnEnumFontFamiliesExA == nullptr)
    {
        pfnEnumFontFamiliesExA = EnumFontFamiliesExA;
        printf("DetourAttach: EnumFontFamiliesExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesExA), HookEnumFontFamiliesExA);
    }
    if (pfnEnumFontFamiliesA == nullptr)
    {
        pfnEnumFontFamiliesA = EnumFontFamiliesA;
        printf("DetourAttach: EnumFontFamiliesA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesA), HookEnumFontFamiliesA);
    }
    if (pfnEnumFontsA == nullptr)
    {
        pfnEnumFontsA = EnumFontsA;
        printf("DetourAttach: EnumFontsA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnEnumFontsA), HookEnumFontsA);
    }
    DetourTransactionCommit();
}

void Win32Hook::DetachHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    if (pfnCreateWindowExA != nullptr)
    {
        printf("DetourDetach: CreateWindowExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateWindowExA), HookCreateWindowExA);
    }
    if (pfnCreateMDIWindowA != nullptr)
    {
        printf("DetourDetach: CreateMDIWindowA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateMDIWindowA), HookCreateMDIWindowA);
    }
    if (pfnSetWindowTextA != nullptr)
    {
        printf("DetourDetach: SetWindowTextA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnSetWindowTextA), HookSetWindowTextA);
    }
    if (pfnCreatePropertySheetPageA != nullptr)
    {
        printf("DetourDetach: CreatePropertySheetPageA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreatePropertySheetPageA), HookCreatePropertySheetPageA);
    }
    if (pfnPropertySheetA != nullptr)
    {
        printf("DetourDetach: PropertySheetA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnPropertySheetA), HookPropertySheetA);
    }
    if (pfnCreateDialogParamA != nullptr)
    {
        printf("DetourDetach: CreateDialogParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateDialogParamA), HookCreateDialogParamA);
    }
    if (pfnCreateDialogIndirectParamA != nullptr)
    {
        printf("DetourDetach: CreateDialogIndirectParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateDialogIndirectParamA), HookCreateDialogIndirectParamA);
    }
    if (pfnDialogBoxParamA != nullptr)
    {
        pfnDialogBoxParamA = DialogBoxParamA;
        printf("DetourDetach: DialogBoxParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnDialogBoxParamA), HookDialogBoxParamA);
    }
    if (pfnDialogBoxIndirectParamA != nullptr)
    {
        pfnDialogBoxIndirectParamA = DialogBoxIndirectParamA;
        printf("DetourDetach: DialogBoxIndirectParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnDialogBoxIndirectParamA), HookDialogBoxIndirectParamA);
    }
    if (pfnSetDlgItemTextA != nullptr)
    {
        pfnSetDlgItemTextA = SetDlgItemTextA;
        printf("DetourDetach: SetDlgItemTextA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnSetDlgItemTextA), HookSetDlgItemTextA);
    }
    if (pfnMessageBoxA != nullptr)
    {
        printf("DetourDetach: MessageBoxA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnMessageBoxA), HookMessageBoxA);
    }
    if (pfnMessageBoxExA != nullptr)
    {
        printf("DetourDetach: MessageBoxExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnMessageBoxExA), HookMessageBoxExA);
    }
    if (pfnCreateFontA != nullptr)
    {
        printf("DetourDetach: CreateFontA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateFontA), HookCreateFontA);
    }
    if (pfnCreateFontIndirectA != nullptr)
    {
        printf("DetourDetach: CreateFontIndirectA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateFontIndirectA), HookCreateFontIndirectA);
    }
    if (pfnEnumFontFamiliesExA != nullptr)
    {
        printf("DetourDetach: EnumFontFamiliesExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesExA), HookEnumFontFamiliesExA);
    }
    if (pfnEnumFontFamiliesA != nullptr)
    {
        printf("DetourDetach: EnumFontFamiliesA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesA), HookEnumFontFamiliesA);
    }
    if (pfnEnumFontsA != nullptr)
    {
        printf("DetourDetach: EnumFontsA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnEnumFontsA), HookEnumFontsA);
    }
    DetourTransactionCommit();

    pfnCreateWindowExA = nullptr;
    pfnCreateMDIWindowA = nullptr;
    pfnSetWindowTextA = nullptr;
    pfnCreatePropertySheetPageA = nullptr;
    pfnPropertySheetA = nullptr;
    pfnCreateDialogParamA = nullptr;
    pfnCreateDialogIndirectParamA = nullptr;
    pfnDialogBoxParamA = nullptr;
    pfnDialogBoxIndirectParamA = nullptr;
    pfnSetDlgItemTextA = nullptr;
    pfnMessageBoxA = nullptr;
    pfnMessageBoxExA = nullptr;
    pfnCreateFontA = nullptr;
    pfnCreateFontIndirectA = nullptr;
    pfnEnumFontFamiliesExA = nullptr;
    pfnEnumFontFamiliesA = nullptr;
    pfnEnumFontsA = nullptr;
}

Win32Hook::LPCreateWindowExA Win32Hook::pfnCreateWindowExA = nullptr;

Win32Hook::LPCreateMDIWindowA Win32Hook::pfnCreateMDIWindowA = nullptr;

Win32Hook::LPSetWindowTextA Win32Hook::pfnSetWindowTextA = nullptr;

Win32Hook::LPCreatePropertySheetPageA Win32Hook::pfnCreatePropertySheetPageA = nullptr;

Win32Hook::LPPropertySheetA Win32Hook::pfnPropertySheetA = nullptr;

Win32Hook::LPCreateDialogParamA Win32Hook::pfnCreateDialogParamA = nullptr;

Win32Hook::LPCreateDialogIndirectParamA Win32Hook::pfnCreateDialogIndirectParamA = nullptr;

Win32Hook::LPDialogBoxParamA Win32Hook::pfnDialogBoxParamA = nullptr;

Win32Hook::LPDialogBoxIndirectParamA Win32Hook::pfnDialogBoxIndirectParamA = nullptr;

Win32Hook::LPSetDlgItemTextA Win32Hook::pfnSetDlgItemTextA = nullptr;

Win32Hook::LPMessageBoxA Win32Hook::pfnMessageBoxA = nullptr;

Win32Hook::LPMessageBoxExA Win32Hook::pfnMessageBoxExA = nullptr;

Win32Hook::LPCreateFontA Win32Hook::pfnCreateFontA = nullptr;

Win32Hook::LPCreateFontIndirectA Win32Hook::pfnCreateFontIndirectA = nullptr;

Win32Hook::LPEnumFontFamiliesExA Win32Hook::pfnEnumFontFamiliesExA = nullptr;

Win32Hook::LPEnumFontFamiliesA Win32Hook::pfnEnumFontFamiliesA = nullptr;

Win32Hook::LPEnumFontsA Win32Hook::pfnEnumFontsA = nullptr;

HWND WINAPI Win32Hook::HookCreateWindowExA(const DWORD dwExStyle, const LPCSTR lpClassName, const LPCSTR lpWindowName,
                                           const DWORD dwStyle,
                                           const int X, const int Y, const int nWidth, const int nHeight,
                                           const HWND hWndParent, const HMENU hMenu, const HINSTANCE hInstance,
                                           const LPVOID lpParam)
{
    printf("Hook CreateWindowExA(lpClassName=%s, lpWindowName=%s, dwStyle=%08X)\n", lpClassName, lpWindowName, dwStyle);
    const auto uuid = Unicode(lpClassName, CP_SHIFT_JIS);
    const auto title = Unicode(lpWindowName, CP_SHIFT_JIS);
    const auto result = CreateWindowExW(dwExStyle, uuid, title, dwStyle,
                                        X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    free(uuid);
    free(title);
    return result;
}

HWND Win32Hook::HookCreateMDIWindowA(const LPSTR lpClassName, const LPSTR lpWindowName, const DWORD dwStyle,
                                     const int X, const int Y, const int nWidth, const int nHeight,
                                     const HWND hWndParent, const HINSTANCE hInstance,
                                     const LPARAM lParam)
{
    printf("Hook CreateMDIWindowA(lpClassName=%s, lpWindowName=%s, dwStyle=%08X)\n", lpClassName, lpWindowName,
           dwStyle);
    const auto uuid = Unicode(lpClassName, CP_SHIFT_JIS);
    const auto title = Unicode(lpWindowName, CP_SHIFT_JIS);
    const auto result = CreateMDIWindowW(uuid, title, dwStyle,
                                         X, Y, nWidth, nHeight,
                                         hWndParent, hInstance,
                                         lParam);
    free(uuid);
    free(title);
    return result;
}

BOOL WINAPI Win32Hook::HookSetWindowTextA(const HWND hWnd, const LPCSTR lpString)
{
    printf("Hook SetWindowTextA(hWnd=0x%p, lpString=%s)\n", hWnd, lpString);
    const auto unicode = Unicode(lpString, CP_SHIFT_JIS);
    const auto result = SetWindowTextW(hWnd, unicode);
    free(unicode);
    return result;
}

HPROPSHEETPAGE Win32Hook::HookCreatePropertySheetPageA(const LPCPROPSHEETPAGEA lpPropSheetPage)
{
    printf("Hook CreatePropertySheetPageA(pszTitle=%s)\n", lpPropSheetPage->pszTitle);
    const auto title = lpPropSheetPage->pszTitle;
    const auto unicode = Unicode(title, CP_SHIFT_JIS);
    const_cast<LPSTR&>(lpPropSheetPage->pszTitle) = Ansi(unicode, CP_ACP);
    free(unicode);
    const auto result = pfnCreatePropertySheetPageA(lpPropSheetPage);
    free(const_cast<LPSTR&>(lpPropSheetPage->pszTitle));
    const_cast<LPCSTR&>(lpPropSheetPage->pszTitle) = title;
    return result;
}

int Win32Hook::HookPropertySheetA(const LPCPROPSHEETHEADERA lpPropSheetHeader)
{
    printf("Hook PropertySheetA(pszCaption=%s)\n", lpPropSheetHeader->pszCaption);
    const auto caption = lpPropSheetHeader->pszCaption;
    const auto unicode = Unicode(caption, CP_SHIFT_JIS);
    const_cast<LPSTR&>(lpPropSheetHeader->pszCaption) = Ansi(unicode, CP_ACP);
    free(unicode);
    const auto result = pfnPropertySheetA(lpPropSheetHeader);
    free(const_cast<LPSTR&>(lpPropSheetHeader->pszCaption));
    const_cast<LPCSTR&>(lpPropSheetHeader->pszCaption) = caption;
    return result;
}

HWND WINAPI Win32Hook::HookCreateDialogParamA(const HINSTANCE hInstance, const LPCSTR lpTemplateName,
                                              const HWND hWndParent, const DLGPROC lpDialogFunc,
                                              const LPARAM dwInitParam)
{
    const auto id = reinterpret_cast<DWORD>(lpTemplateName);
    if (id > 0x0000FFFF)
    {
        printf("Hook CreateDialogParamA(lpTemplateName=%s, hWndParent=0x%p)\n", lpTemplateName, hWndParent);
        const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
        const auto result = CreateDialogParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
        free(unicode);
        return result;
    }

    printf("Hook CreateDialogParamA(lpTemplateName=MAKEINTRESOURCEA(%d)\n", id);
    return CreateDialogParamW(hInstance, MAKEINTRESOURCEW(lpTemplateName), hWndParent, lpDialogFunc, dwInitParam);
}

HWND Win32Hook::HookCreateDialogIndirectParamA(const HINSTANCE hInstance, const LPCDLGTEMPLATEA lpTemplate,
                                               const HWND hWndParent, const DLGPROC lpDialogFunc,
                                               const LPARAM dwInitParam)
{
    printf("Hook CreateDialogIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

int Win32Hook::HookDialogBoxParamA(const HINSTANCE hInstance, const LPCSTR lpTemplateName, const HWND hWndParent,
                                   const DLGPROC lpDialogFunc, const LPARAM dwInitParam)
{
    const auto id = reinterpret_cast<DWORD>(lpTemplateName);
    if (id > 0x0000FFFF)
    {
        printf("Hook CreateDialogParamA(lpTemplateName=%s, hWndParent=0x%p)\n", lpTemplateName, hWndParent);
        const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
        const auto result = DialogBoxParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
        free(unicode);
        return result;
    }

    printf("Hook CreateDialogParamA(lpTemplateName=MAKEINTRESOURCEA(%d)\n", id);
    return DialogBoxParamW(hInstance, MAKEINTRESOURCEW(lpTemplateName), hWndParent, lpDialogFunc, dwInitParam);
}

int Win32Hook::HookDialogBoxIndirectParamA(const HINSTANCE hInstance, const LPCDLGTEMPLATEA hDialogTemplate,
                                           const HWND hWndParent, const DLGPROC lpDialogFunc, const LPARAM dwInitParam)
{
    printf("Hook DialogBoxIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

BOOL Win32Hook::HookSetDlgItemTextA(const HWND hDlg, const int nIDDlgItem, const LPCSTR lpString)
{
    printf("Hook SetDlgItemTextA(hDlg=0x%p, nIDDlgItem=%d, lpString=%s)\n", hDlg, nIDDlgItem, lpString);
    const auto unicode = Unicode(lpString, CP_SHIFT_JIS);
    const auto result = SetDlgItemTextW(hDlg, nIDDlgItem, unicode);
    free(unicode);
    return result;
}

int WINAPI Win32Hook::HookMessageBoxA(const HWND hWnd, const LPCSTR lpText, const LPCSTR lpCaption, const UINT uType)
{
    printf("Hook MessageBoxA(lpCaption=%s)\n", lpCaption);
    const auto text = Unicode(lpText, CP_SHIFT_JIS);
    const auto caption = Unicode(lpCaption, CP_SHIFT_JIS);
    const auto result = MessageBoxW(hWnd, text, caption, uType);
    free(text);
    free(caption);
    return result;
}

int WINAPI Win32Hook::HookMessageBoxExA(const HWND hWnd, const LPCSTR lpText, const LPCSTR lpCaption, const UINT uType,
                                        const WORD wLanguageId)
{
    printf("Hook MessageBoxExA(lpCaption=%s)\n", lpCaption);
    const auto text = Unicode(lpText, CP_SHIFT_JIS);
    const auto caption = Unicode(lpCaption, CP_SHIFT_JIS);
    const auto result = MessageBoxExW(hWnd, text, caption, uType, wLanguageId);
    free(text);
    free(caption);
    return result;
}

HFONT WINAPI Win32Hook::HookCreateFontA(const int cHeight, const int cWidth, const int cEscapement,
                                        const int cOrientation, const int cWeight,
                                        const DWORD bItalic, const DWORD bUnderline, const DWORD bStrikeOut,
                                        const DWORD iCharSet, const DWORD iOutPrecision, const DWORD iClipPrecision,
                                        const DWORD iQuality, const DWORD iPitchAndFamily,
                                        const LPCSTR pszFaceName)
{
    printf("Hook CreateFontA(iCharSet=0x%X, pszFaceName=%s)\n", iCharSet, pszFaceName);
    const auto unicode = Unicode(pszFaceName, CP_SHIFT_JIS);
    const auto result = CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight,
                                    bItalic, bUnderline, bStrikeOut,
                                    iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily,
                                    unicode);
    free(unicode);
    return result;
}

HFONT WINAPI Win32Hook::HookCreateFontIndirectA(const LOGFONTA* lpLogFont)
{
    printf("Hook CreateFontIndirectA(lfCharSet=0x%X, lfFaceName=%s)\n", lpLogFont->lfCharSet, lpLogFont->lfFaceName);
    auto LogFont = LOGFONTW
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
    const auto unicode = Unicode(lpLogFont->lfFaceName, CP_SHIFT_JIS);
    wcscpy(LogFont.lfFaceName, unicode);
    free(unicode);
    return CreateFontIndirectW(&LogFont);
}

int WINAPI Win32Hook::HookEnumFontFamiliesExA(const HDC hdc, const LPLOGFONTA lpLogFont, const FONTENUMPROCA lpProc,
                                              const LPARAM lParam, const DWORD dwFlags)
{
    // CB_ADDSTRING
    printf("Hook EnumFontFamiliesExA(lfCharSet=0x%X)\n", lpLogFont->lfCharSet);
    const auto callback = HookEnumFontCallback{lpProc, lParam};
    auto LogFont = LOGFONTW
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
    const auto unicode = Unicode(lpLogFont->lfFaceName, CP_SHIFT_JIS);
    wcscpy(LogFont.lfFaceName, unicode);
    free(unicode);
    const auto result = EnumFontFamiliesExW(hdc, &LogFont, &HookEnumFontsCallback,
                                            reinterpret_cast<DWORD>(&callback), dwFlags);
    return result;
}

int Win32Hook::HookEnumFontFamiliesA(const HDC hdc, const LPCSTR lpLogFont, const FONTENUMPROCA lpProc,
                                     const LPARAM lParam)
{
    printf("Hook EnumFontFamiliesA(lpLogFont=%s)\n", lpLogFont);
    const auto callback = HookEnumFontCallback{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontsCallback, reinterpret_cast<DWORD>(&callback));
    free(unicode);
    return result;
}

int Win32Hook::HookEnumFontsA(const HDC hdc, const LPCSTR lpLogFont, const FONTENUMPROCA lpProc, const LPARAM lParam)
{
    printf("Hook EnumFontsA(lpLogFont=%s)\n", lpLogFont);
    const auto callback = HookEnumFontCallback{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontsCallback, reinterpret_cast<DWORD>(&callback));
    free(unicode);
    return result;
}

int Win32Hook::HookEnumFontsCallback(const LOGFONTW* lpLogFont, const TEXTMETRICW* lpTextMetric, const DWORD dwFontType,
                                     const LPARAM lParam)
{
    const auto callback = reinterpret_cast<HookEnumFontCallback*>(lParam);
    auto LogFont = LOGFONTA
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
    const auto ansi = Ansi(lpLogFont->lfFaceName, CP_ACP);
    strcpy(LogFont.lfFaceName, ansi);
    free(ansi);
    const auto TextMetric = TEXTMETRICA
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
        0,
        0,
        0,
        0,
        lpTextMetric->tmItalic,
        lpTextMetric->tmUnderlined,
        lpTextMetric->tmStruckOut,
        lpTextMetric->tmPitchAndFamily,
        lpTextMetric->tmCharSet
    };
    return callback->lpProc(&LogFont, &TextMetric, dwFontType, callback->lParam);
}
