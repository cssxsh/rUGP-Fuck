#ifndef HOOK_H
#define HOOK_H

#include "stdafx.h"

#ifdef _PRSHT_H_
#pragma comment(lib, "comctl32.lib")
#endif // _PRSHT_H_

class Win32Hook final
{
public:
    static void AttachHook();

    static void DetachHook();

protected:
    using LPCreateWindowExA = HWND (WINAPI *)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
                                              int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                              HINSTANCE hInstance, LPVOID lpParam);
    static LPCreateWindowExA pfnCreateWindowExA;

    using LPCreateMDIWindowA = HWND (WINAPI *)(LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
                                               int X, int Y, int nWidth, int nHeight, HWND hWndParent,
                                               HINSTANCE hInstance, LPARAM lParam);
    static LPCreateMDIWindowA pfnCreateMDIWindowA;

    using LPSetWindowTextA = BOOL (WINAPI *)(HWND hWnd, LPCSTR lpString);
    static LPSetWindowTextA pfnSetWindowTextA;

    using LPCreatePropertySheetPageA = HPROPSHEETPAGE (WINAPI *)(LPCPROPSHEETPAGEA lpPropSheetPage);
    static LPCreatePropertySheetPageA pfnCreatePropertySheetPageA;

    using LPPropertySheetA = int (WINAPI *)(LPCPROPSHEETHEADERA);
    static LPPropertySheetA pfnPropertySheetA;

    using LPCreateDialogParamA = HWND (WINAPI *)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                                 DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPCreateDialogParamA pfnCreateDialogParamA;

    using LPCreateDialogIndirectParamA = HWND (WINAPI *)(HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate,
                                                         HWND hWndParent,
                                                         DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPCreateDialogIndirectParamA pfnCreateDialogIndirectParamA;

    using LPDialogBoxParamA = int (WINAPI *)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                             DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPDialogBoxParamA pfnDialogBoxParamA;

    using LPDialogBoxIndirectParamA = int (WINAPI *)(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate,
                                                     HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPDialogBoxIndirectParamA pfnDialogBoxIndirectParamA;

    using LPSetDlgItemTextA = int (WINAPI *)(HWND hDlg, int nIDDlgItem, LPCSTR lpString);
    static LPSetDlgItemTextA pfnSetDlgItemTextA;

    using LPMessageBoxA = int (WINAPI *)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
    static LPMessageBoxA pfnMessageBoxA;

    using LPMessageBoxExA = int (WINAPI *)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId);
    static LPMessageBoxExA pfnMessageBoxExA;

    using LPCreateFontA = HFONT (WINAPI *)(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight,
                                           DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut,
                                           DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality,
                                           DWORD iPitchAndFamily, LPCSTR pszFaceName);
    static LPCreateFontA pfnCreateFontA;

    using LPCreateFontIndirectA = HFONT (WINAPI *)(const LOGFONTA* lpLogFont);
    static LPCreateFontIndirectA pfnCreateFontIndirectA;

    using LPEnumFontFamiliesExA = int (WINAPI *)(HDC hdc, LPLOGFONTA lpLogFont, FONTENUMPROCA lpProc,
                                                 LPARAM lParam, DWORD dwFlags);
    static LPEnumFontFamiliesExA pfnEnumFontFamiliesExA;

    using LPEnumFontFamiliesA = int (WINAPI *)(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);
    static LPEnumFontFamiliesA pfnEnumFontFamiliesA;

    using LPEnumFontsA = int (WINAPI *)(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);
    static LPEnumFontsA pfnEnumFontsA;

    using LPGetGlyphOutlineA = DWORD (WINAPI *)(HDC hdc, UINT uChar, UINT fuFormat,
                                                LPGLYPHMETRICS lpgm, DWORD cjBuffer, LPVOID pvBuffer,
                                                const MAT2* lpmat2);
    static LPGetGlyphOutlineA pfnGetGlyphOutlineA;

    static HWND WINAPI HookCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
                                           int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                           HINSTANCE hInstance, LPVOID lpParam);

    static HWND WINAPI HookCreateMDIWindowA(LPSTR lpClassName, LPSTR lpWindowName, DWORD dwStyle,
                                            int X, int Y, int nWidth, int nHeight, HWND hWndParent,
                                            HINSTANCE hInstance, LPARAM lParam);

    static BOOL WINAPI HookSetWindowTextA(HWND hWnd, LPCSTR lpString);

    static HPROPSHEETPAGE WINAPI HookCreatePropertySheetPageA(LPCPROPSHEETPAGEA lpPropSheetPage);

    static int WINAPI HookPropertySheetA(LPCPROPSHEETHEADERA);

    static HWND WINAPI HookCreateDialogParamA(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                              DLGPROC lpDialogFunc, LPARAM dwInitParam);

    static HWND WINAPI HookCreateDialogIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent,
                                                      DLGPROC lpDialogFunc, LPARAM dwInitParam);

    static int WINAPI HookDialogBoxParamA(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                          DLGPROC lpDialogFunc, LPARAM dwInitParam);

    static int WINAPI HookDialogBoxIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent,
                                                  DLGPROC lpDialogFunc, LPARAM dwInitParam);

    static BOOL WINAPI HookSetDlgItemTextA(HWND hDlg, int nIDDlgItem, LPCSTR lpString);

    static int WINAPI HookMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

    static int WINAPI HookMessageBoxExA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId);

    static HFONT WINAPI HookCreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight,
                                        DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut,
                                        DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality,
                                        DWORD iPitchAndFamily, LPCSTR pszFaceName);

    static HFONT WINAPI HookCreateFontIndirectA(const LOGFONTA* lpLogFont);

    struct HookEnumFontCallback
    {
        FONTENUMPROCA lpProc;
        LPARAM lParam;
    };

    static int WINAPI HookEnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam,
                                              DWORD dwFlags);

    static int WINAPI HookEnumFontFamiliesA(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);

    static int WINAPI HookEnumFontsA(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);

    static int CALLBACK HookEnumFontsCallback(const LOGFONTW* lpLogFont, const TEXTMETRICW* lpTextMetric,
                                              DWORD dwFontType,
                                              LPARAM lParam);

    static DWORD WINAPI HookGetGlyphOutlineA(HDC hdc, UINT uChar, UINT fuFormat,
                                             LPGLYPHMETRICS lpgm, DWORD cjBuffer, LPVOID pvBuffer,
                                             const MAT2* lpmat2);
};

#endif // HOOK_H
