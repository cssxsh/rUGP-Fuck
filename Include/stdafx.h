#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifndef _DLL
#pragma error "Only DLL available on rUGP!"
#endif // _DLL

#ifndef _AFXDLL
#define _AFXDLL
#endif // _AFXDLL

#ifndef AFX_COMDAT
#define AFX_COMDAT __declspec(selectany)
#endif // AFX_COMDAT

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC automation classes
#include <afxdtctl.h>       // MFC support for Internet Explorer common controls
#include <afxcmn.h>         // MFC support for Windows common controls.

typedef const BYTE FAR* LPCBYTE;

#ifndef CP_SHIFT_JIS
#define CP_SHIFT_JIS 932
#endif // CP_SHIFT_JIS

#ifndef CP_GB2312
#define CP_GB2312 936
#endif // CP_GB2312

inline LPWSTR WINAPI Unicode(const LPCSTR lpText, const UINT nCodePage)
{
    if (lpText == nullptr) return nullptr;
    const auto length = MultiByteToWideChar(nCodePage, 0, lpText, -1, nullptr, 0);
    const auto unicode = static_cast<LPWSTR>(malloc(length * sizeof(WCHAR)));
    MultiByteToWideChar(nCodePage, 0, lpText, -1, unicode, length);
    return unicode;
}

inline LPSTR WINAPI Ansi(const LPCWSTR lpText, const UINT nCodePage)
{
    if (lpText == nullptr) return nullptr;
    const auto size = WideCharToMultiByte(nCodePage, 0, lpText, -1, nullptr, 0, nullptr, nullptr);
    const auto ansi = static_cast<LPSTR>(malloc(size));
    WideCharToMultiByte(nCodePage, 0, lpText, -1, ansi, size, nullptr, nullptr);
    return ansi;
}

#endif // _STDAFX_H_
