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
        wprintf(L"DetourAttach: CreateWindowExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateWindowExA), HookCreateWindowExA);
    }
    if (pfnCreateMDIWindowA == nullptr)
    {
        pfnCreateMDIWindowA = CreateMDIWindowA;
        wprintf(L"DetourAttach: CreateMDIWindowA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateMDIWindowA), HookCreateMDIWindowA);
    }
    if (pfnSetWindowTextA == nullptr)
    {
        pfnSetWindowTextA = SetWindowTextA;
        wprintf(L"DetourAttach: SetWindowTextA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnSetWindowTextA), HookSetWindowTextA);
    }
    if (pfnCreatePropertySheetPageA == nullptr)
    {
        pfnCreatePropertySheetPageA = CreatePropertySheetPageA;
        wprintf(L"DetourAttach: CreatePropertySheetPageA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreatePropertySheetPageA), HookCreatePropertySheetPageA);
    }
    if (pfnPropertySheetA == nullptr)
    {
        pfnPropertySheetA = PropertySheetA;
        wprintf(L"DetourAttach: PropertySheetA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnPropertySheetA), HookPropertySheetA);
    }
    if (pfnCreateDialogParamA == nullptr)
    {
        pfnCreateDialogParamA = CreateDialogParamA;
        wprintf(L"DetourAttach: CreateDialogParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateDialogParamA), HookCreateDialogParamA);
    }
    if (pfnCreateDialogIndirectParamA == nullptr)
    {
        pfnCreateDialogIndirectParamA = CreateDialogIndirectParamA;
        wprintf(L"DetourAttach: CreateDialogIndirectParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateDialogIndirectParamA), HookCreateDialogIndirectParamA);
    }
    if (pfnDialogBoxParamA == nullptr)
    {
        pfnDialogBoxParamA = DialogBoxParamA;
        wprintf(L"DetourAttach: DialogBoxParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnDialogBoxParamA), HookDialogBoxParamA);
    }
    if (pfnDialogBoxIndirectParamA == nullptr)
    {
        pfnDialogBoxIndirectParamA = DialogBoxIndirectParamA;
        wprintf(L"DetourAttach: DialogBoxIndirectParamA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnDialogBoxIndirectParamA), HookDialogBoxIndirectParamA);
    }
    if (pfnSetDlgItemTextA == nullptr)
    {
        pfnSetDlgItemTextA = SetDlgItemTextA;
        wprintf(L"DetourAttach: SetDlgItemTextA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnSetDlgItemTextA), HookSetDlgItemTextA);
    }
    if (pfnMessageBoxA == nullptr)
    {
        pfnMessageBoxA = MessageBoxA;
        wprintf(L"DetourAttach: MessageBoxA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnMessageBoxA), HookMessageBoxA);
    }
    if (pfnMessageBoxExA == nullptr)
    {
        pfnMessageBoxExA = MessageBoxExA;
        wprintf(L"DetourAttach: MessageBoxExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnMessageBoxExA), HookMessageBoxExA);
    }
    if (pfnCreateFontA == nullptr)
    {
        pfnCreateFontA = CreateFontA;
        wprintf(L"DetourAttach: CreateFontA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateFontA), HookCreateFontA);
    }
    if (pfnCreateFontIndirectA == nullptr)
    {
        pfnCreateFontIndirectA = CreateFontIndirectA;
        wprintf(L"DetourAttach: CreateFontIndirectA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnCreateFontIndirectA), HookCreateFontIndirectA);
    }
    if (pfnEnumFontFamiliesExA == nullptr)
    {
        pfnEnumFontFamiliesExA = EnumFontFamiliesExA;
        wprintf(L"DetourAttach: EnumFontFamiliesExA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesExA), HookEnumFontFamiliesExA);
    }
    if (pfnEnumFontFamiliesA == nullptr)
    {
        pfnEnumFontFamiliesA = EnumFontFamiliesA;
        wprintf(L"DetourAttach: EnumFontFamiliesA\n");
        DetourAttach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesA), HookEnumFontFamiliesA);
    }
    if (pfnEnumFontsA == nullptr)
    {
        pfnEnumFontsA = EnumFontsA;
        wprintf(L"DetourAttach: EnumFontsA\n");
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
        wprintf(L"DetourDetach: CreateWindowExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateWindowExA), HookCreateWindowExA);
    }
    if (pfnCreateMDIWindowA != nullptr)
    {
        wprintf(L"DetourDetach: CreateMDIWindowA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateMDIWindowA), HookCreateMDIWindowA);
    }
    if (pfnSetWindowTextA != nullptr)
    {
        wprintf(L"DetourDetach: SetWindowTextA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnSetWindowTextA), HookSetWindowTextA);
    }
    if (pfnCreatePropertySheetPageA != nullptr)
    {
        wprintf(L"DetourDetach: CreatePropertySheetPageA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreatePropertySheetPageA), HookCreatePropertySheetPageA);
    }
    if (pfnPropertySheetA != nullptr)
    {
        wprintf(L"DetourDetach: PropertySheetA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnPropertySheetA), HookPropertySheetA);
    }
    if (pfnCreateDialogParamA != nullptr)
    {
        wprintf(L"DetourDetach: CreateDialogParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateDialogParamA), HookCreateDialogParamA);
    }
    if (pfnCreateDialogIndirectParamA != nullptr)
    {
        wprintf(L"DetourDetach: CreateDialogIndirectParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateDialogIndirectParamA), HookCreateDialogIndirectParamA);
    }
    if (pfnDialogBoxParamA != nullptr)
    {
        pfnDialogBoxParamA = DialogBoxParamA;
        wprintf(L"DetourDetach: DialogBoxParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnDialogBoxParamA), HookDialogBoxParamA);
    }
    if (pfnDialogBoxIndirectParamA != nullptr)
    {
        pfnDialogBoxIndirectParamA = DialogBoxIndirectParamA;
        wprintf(L"DetourDetach: DialogBoxIndirectParamA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnDialogBoxIndirectParamA), HookDialogBoxIndirectParamA);
    }
    if (pfnSetDlgItemTextA != nullptr)
    {
        pfnSetDlgItemTextA = SetDlgItemTextA;
        wprintf(L"DetourDetach: SetDlgItemTextA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnSetDlgItemTextA), HookSetDlgItemTextA);
    }
    if (pfnMessageBoxA != nullptr)
    {
        wprintf(L"DetourDetach: MessageBoxA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnMessageBoxA), HookMessageBoxA);
    }
    if (pfnMessageBoxExA != nullptr)
    {
        wprintf(L"DetourDetach: MessageBoxExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnMessageBoxExA), HookMessageBoxExA);
    }
    if (pfnCreateFontA != nullptr)
    {
        wprintf(L"DetourDetach: CreateFontA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateFontA), HookCreateFontA);
    }
    if (pfnCreateFontIndirectA != nullptr)
    {
        wprintf(L"DetourDetach: CreateFontIndirectA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnCreateFontIndirectA), HookCreateFontIndirectA);
    }
    if (pfnEnumFontFamiliesExA != nullptr)
    {
        wprintf(L"DetourDetach: EnumFontFamiliesExA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesExA), HookEnumFontFamiliesExA);
    }
    if (pfnEnumFontFamiliesA != nullptr)
    {
        wprintf(L"DetourDetach: EnumFontFamiliesA\n");
        DetourDetach(&reinterpret_cast<PVOID&>(pfnEnumFontFamiliesA), HookEnumFontFamiliesA);
    }
    if (pfnEnumFontsA != nullptr)
    {
        wprintf(L"DetourDetach: EnumFontsA\n");
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

HWND WINAPI Win32Hook::HookCreateWindowExA(const DWORD dwExStyle,
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
    const auto result = CreateWindowExW(dwExStyle, uuid, title, dwStyle,
                                        X, Y, nWidth, nHeight,
                                        hWndParent, hMenu, hInstance,
                                        lpParam);
    free(uuid);
    free(title);
    return result;
}

HWND Win32Hook::HookCreateMDIWindowA(const LPSTR lpClassName, // NOLINT(*-misplaced-const)
                                     const LPSTR lpWindowName, // NOLINT(*-misplaced-const)
                                     const DWORD dwStyle,
                                     const int X,
                                     const int Y,
                                     const int nWidth,
                                     const int nHeight,
                                     const HWND hWndParent, // NOLINT(*-misplaced-const)
                                     const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
                                     const LPARAM lParam)
{
    const auto uuid = Unicode(lpClassName, CP_SHIFT_JIS);
    const auto title = Unicode(lpWindowName, CP_SHIFT_JIS);
    wprintf(L"Hook CreateMDIWindowA(lpClassName=%s, lpWindowName=%s, dwStyle=%08X)\n", uuid, title, dwStyle);
    const auto result = CreateMDIWindowW(uuid, title, dwStyle,
                                         X, Y, nWidth, nHeight,
                                         hWndParent, hInstance,
                                         lParam);
    free(uuid);
    free(title);
    return result;
}

BOOL WINAPI Win32Hook::HookSetWindowTextA(const HWND hWnd, // NOLINT(*-misplaced-const)
                                          const LPCSTR lpString)
{
    const auto unicode = Unicode(lpString, CP_SHIFT_JIS);
    wprintf(L"Hook SetWindowTextA(hWnd=0x%p, lpString=%s)\n", hWnd, unicode);
    const auto result = SetWindowTextW(hWnd, unicode);
    free(unicode);
    return result;
}

HPROPSHEETPAGE Win32Hook::HookCreatePropertySheetPageA(const LPCPROPSHEETPAGEA lpPropSheetPage)
{
    const auto title = lpPropSheetPage->pszTitle;
    const auto unicode = Unicode(title, CP_SHIFT_JIS);
    wprintf(L"Hook CreatePropertySheetPageA(pszTitle=%s)\n", unicode);
    const_cast<LPSTR&>(lpPropSheetPage->pszTitle) = Ansi(unicode, CP_ACP);
    free(unicode);
    const auto result = pfnCreatePropertySheetPageA(lpPropSheetPage);
    free(const_cast<LPSTR&>(lpPropSheetPage->pszTitle));
    const_cast<LPCSTR&>(lpPropSheetPage->pszTitle) = title;
    return result;
}

int Win32Hook::HookPropertySheetA(const LPCPROPSHEETHEADERA lpPropSheetHeader)
{
    const auto caption = lpPropSheetHeader->pszCaption;
    const auto unicode = Unicode(caption, CP_SHIFT_JIS);
    wprintf(L"Hook PropertySheetA(pszCaption=%s)\n", unicode);
    const_cast<LPSTR&>(lpPropSheetHeader->pszCaption) = Ansi(unicode, CP_ACP);
    free(unicode);
    const auto result = pfnPropertySheetA(lpPropSheetHeader);
    free(const_cast<LPSTR&>(lpPropSheetHeader->pszCaption));
    const_cast<LPCSTR&>(lpPropSheetHeader->pszCaption) = caption;
    return result;
}

HWND WINAPI Win32Hook::HookCreateDialogParamA(const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
                                              const LPCSTR lpTemplateName,
                                              const HWND hWndParent, // NOLINT(*-misplaced-const)
                                              const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
                                              const LPARAM dwInitParam)
{
    if (IS_INTRESOURCE(lpTemplateName))
    {
        const auto id = reinterpret_cast<DWORD>(lpTemplateName);
        wprintf(L"Hook CreateDialogParamA(lpTemplateName=MAKEINTRESOURCEA(%d)\n", id);
        return CreateDialogParamW(hInstance, MAKEINTRESOURCEW(lpTemplateName), hWndParent, lpDialogFunc, dwInitParam);
    }

    const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
    wprintf(L"Hook CreateDialogParamA(lpTemplateName=%s, hWndParent=0x%p)\n", unicode, hWndParent);
    const auto result = CreateDialogParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
    free(unicode);
    return result;
}

HWND Win32Hook::HookCreateDialogIndirectParamA(const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
                                               const LPCDLGTEMPLATEA lpTemplate,
                                               const HWND hWndParent, // NOLINT(*-misplaced-const)
                                               const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
                                               const LPARAM dwInitParam)
{
    wprintf(L"Hook CreateDialogIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

int Win32Hook::HookDialogBoxParamA(const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
                                   const LPCSTR lpTemplateName,
                                   const HWND hWndParent, // NOLINT(*-misplaced-const)
                                   const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
                                   const LPARAM dwInitParam)
{
    if (IS_INTRESOURCE(lpTemplateName))
    {
        const auto id = reinterpret_cast<DWORD>(lpTemplateName);
        wprintf(L"Hook DialogBoxParamA(lpTemplateName=MAKEINTRESOURCEA(%d)\n", id);
        return DialogBoxParamW(hInstance, MAKEINTRESOURCEW(lpTemplateName), hWndParent, lpDialogFunc, dwInitParam);
    }

    const auto unicode = Unicode(lpTemplateName, CP_SHIFT_JIS);
    wprintf(L"Hook DialogBoxParamA(lpTemplateName=%s, hWndParent=0x%p)\n", unicode, hWndParent);
    const auto result = DialogBoxParamW(hInstance, unicode, hWndParent, lpDialogFunc, dwInitParam);
    free(unicode);
    return result;
}

int Win32Hook::HookDialogBoxIndirectParamA(const HINSTANCE hInstance, // NOLINT(*-misplaced-const)
                                           const LPCDLGTEMPLATEA hDialogTemplate, // NOLINT(*-misplaced-const)
                                           const HWND hWndParent, // NOLINT(*-misplaced-const)
                                           const DLGPROC lpDialogFunc, // NOLINT(*-misplaced-const)
                                           const LPARAM dwInitParam)
{
    wprintf(L"Hook DialogBoxIndirectParamA(hWndParent=0x%p)\n", hWndParent);
    return DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

BOOL Win32Hook::HookSetDlgItemTextA(const HWND hDlg, // NOLINT(*-misplaced-const)
                                    const int nIDDlgItem,
                                    const LPCSTR lpString)
{
    const auto unicode = Unicode(lpString, CP_SHIFT_JIS);
    wprintf(L"Hook SetDlgItemTextA(hDlg=0x%p, nIDDlgItem=%d, lpString=%s)\n", hDlg, nIDDlgItem, unicode);
    const auto result = SetDlgItemTextW(hDlg, nIDDlgItem, unicode);
    free(unicode);
    return result;
}

int WINAPI Win32Hook::HookMessageBoxA(const HWND hWnd, // NOLINT(*-misplaced-const)
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

int WINAPI Win32Hook::HookMessageBoxExA(const HWND hWnd, // NOLINT(*-misplaced-const)
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

HFONT WINAPI Win32Hook::HookCreateFontA(const int cHeight,
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
    const auto unicode = Unicode(pszFaceName, CP_SHIFT_JIS);
    wprintf(L"Hook CreateFontA(iCharSet=0x%X, pszFaceName=%s)\n", iCharSet, unicode);
    const auto result = CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight,
                                    bItalic, bUnderline, bStrikeOut,
                                    iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily,
                                    unicode);
    free(unicode);
    return result;
}

HFONT WINAPI Win32Hook::HookCreateFontIndirectA(const LOGFONTA* lpLogFont)
{
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
    wprintf(L"Hook CreateFontIndirectA(lfCharSet=0x%X, lfFaceName=%s)\n", lpLogFont->lfCharSet, unicode);
    wcscpy(LogFont.lfFaceName, unicode);
    free(unicode);
    return CreateFontIndirectW(&LogFont);
}

int WINAPI Win32Hook::HookEnumFontFamiliesExA(const HDC hdc, // NOLINT(*-misplaced-const)
                                              const LPLOGFONTA lpLogFont, // NOLINT(*-misplaced-const)
                                              const FONTENUMPROCA lpProc,
                                              const LPARAM lParam,
                                              const DWORD dwFlags)
{
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
    wprintf(L"Hook EnumFontFamiliesExA(lfCharSet=0x%X, lfFaceName=%s)\n", lpLogFont->lfCharSet, unicode);
    wcscpy(LogFont.lfFaceName, unicode);
    free(unicode);
    const auto result = EnumFontFamiliesExW(hdc, &LogFont, &HookEnumFontsCallback,
                                            reinterpret_cast<LPARAM>(&callback), dwFlags);
    return result;
}

int Win32Hook::HookEnumFontFamiliesA(const HDC hdc, // NOLINT(*-misplaced-const)
                                     const LPCSTR lpLogFont,
                                     const FONTENUMPROCA lpProc,
                                     const LPARAM lParam)
{
    const auto callback = HookEnumFontCallback{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    wprintf(L"Hook EnumFontFamiliesA(lpLogFont=%s)\n", unicode);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontsCallback, reinterpret_cast<LPARAM>(&callback));
    free(unicode);
    return result;
}

int Win32Hook::HookEnumFontsA(const HDC hdc, // NOLINT(*-misplaced-const)
                              const LPCSTR lpLogFont,
                              const FONTENUMPROCA lpProc,
                              const LPARAM lParam)
{
    const auto callback = HookEnumFontCallback{lpProc, lParam};
    const auto unicode = Unicode(lpLogFont, CP_SHIFT_JIS);
    wprintf(L"Hook EnumFontsA(lpLogFont=%s)\n", unicode);
    const auto result = EnumFontFamiliesW(hdc, unicode, &HookEnumFontsCallback, reinterpret_cast<LPARAM>(&callback));
    free(unicode);
    return result;
}

int Win32Hook::HookEnumFontsCallback(const LOGFONTW* lpLogFont,
                                     const TEXTMETRICW* lpTextMetric,
                                     const DWORD dwFontType,
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
