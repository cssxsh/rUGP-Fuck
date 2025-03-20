#ifndef HOOK_H
#define HOOK_H

#include <stdafx.h>

class Win32Hook final
{
public:
    static void AttachHook();

    static void DetachHook();

protected:
    typedef HWND (WINAPI *LPCreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
                                             int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                             HINSTANCE hInstance, LPVOID lpParam);
    static LPCreateWindowExA pfnCreateWindowExA;

    typedef HWND (WINAPI *LPCreateMDIWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle,
                                              int X, int Y, int nWidth, int nHeight, HWND hWndParent,
                                              HINSTANCE hInstance, LPARAM lParam);
    static LPCreateMDIWindowA pfnCreateMDIWindowA;

    typedef BOOL (WINAPI *LPSetWindowTextA)(HWND hWnd, LPCSTR lpString);
    static LPSetWindowTextA pfnSetWindowTextA;

    typedef HPROPSHEETPAGE (WINAPI *LPCreatePropertySheetPageA)(LPCPROPSHEETPAGEA lpPropSheetPage);
    static LPCreatePropertySheetPageA pfnCreatePropertySheetPageA;

    typedef int (WINAPI *LPPropertySheetA)(LPCPROPSHEETHEADERA);
    static LPPropertySheetA pfnPropertySheetA;

    typedef HWND (WINAPI *LPCreateDialogParamA)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                                DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPCreateDialogParamA pfnCreateDialogParamA;

    typedef HWND (WINAPI *LPCreateDialogIndirectParamA)(HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate,
                                                        HWND hWndParent,
                                                        DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPCreateDialogIndirectParamA pfnCreateDialogIndirectParamA;

    typedef int (WINAPI *LPDialogBoxParamA)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                                            DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPDialogBoxParamA pfnDialogBoxParamA;

    typedef int (WINAPI *LPDialogBoxIndirectParamA)(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate,
                                                    HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
    static LPDialogBoxIndirectParamA pfnDialogBoxIndirectParamA;

    typedef int (WINAPI *LPSetDlgItemTextA)(HWND hDlg, int nIDDlgItem, LPCSTR lpString);
    static LPSetDlgItemTextA pfnSetDlgItemTextA;

    typedef int (WINAPI *LPMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
    static LPMessageBoxA pfnMessageBoxA;

    typedef int (WINAPI *LPMessageBoxExA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId);
    static LPMessageBoxExA pfnMessageBoxExA;

    typedef HFONT (WINAPI *LPCreateFontA)(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight,
                                          DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut,
                                          DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality,
                                          DWORD iPitchAndFamily, LPCSTR pszFaceName);
    static LPCreateFontA pfnCreateFontA;

    typedef HFONT (WINAPI *LPCreateFontIndirectA)(const LOGFONTA* lpLogFont);
    static LPCreateFontIndirectA pfnCreateFontIndirectA;

    typedef int (WINAPI *LPEnumFontFamiliesExA)(HDC hdc, LPLOGFONTA lpLogFont, FONTENUMPROCA lpProc,
                                                LPARAM lParam, DWORD dwFlags);
    static LPEnumFontFamiliesExA pfnEnumFontFamiliesExA;

    typedef int (WINAPI *LPEnumFontFamiliesA)(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);
    static LPEnumFontFamiliesA pfnEnumFontFamiliesA;

    typedef int (WINAPI *LPEnumFontsA)(HDC hdc, LPCSTR lpLogFont, FONTENUMPROCA lpProc, LPARAM lParam);
    static LPEnumFontsA pfnEnumFontsA;

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
};

#endif // HOOK_H
