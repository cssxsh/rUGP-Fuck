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
    static decltype(CreateWindowExA)* pfnCreateWindowExA;

    static decltype(SetWindowTextA)* pfnSetWindowTextA;

    static decltype(CreatePropertySheetPageA)* pfnCreatePropertySheetPageA;

    static decltype(PropertySheetA)* pfnPropertySheetA;

    static decltype(CreateDialogParamA)* pfnCreateDialogParamA;

    static decltype(CreateDialogIndirectParamA)* pfnCreateDialogIndirectParamA;

    static decltype(DialogBoxParamA)* pfnDialogBoxParamA;

    static decltype(DialogBoxIndirectParamA)* pfnDialogBoxIndirectParamA;

    static decltype(SetDlgItemTextA)* pfnSetDlgItemTextA;

    static decltype(SendDlgItemMessageA)* pfnSendDlgItemMessageA;

    static decltype(AppendMenuA)* pfnAppendMenuA;

    static decltype(MessageBoxA)* pfnMessageBoxA;

    static decltype(MessageBoxExA)* pfnMessageBoxExA;

    static decltype(CreateFontA)* pfnCreateFontA;

    static decltype(CreateFontIndirectA)* pfnCreateFontIndirectA;

    static decltype(EnumFontFamiliesExA)* pfnEnumFontFamiliesExA;

    static decltype(EnumFontFamiliesA)* pfnEnumFontFamiliesA;

    static decltype(EnumFontsA)* pfnEnumFontsA;

    static decltype(GetGlyphOutlineA)* pfnGetGlyphOutlineA;

    static decltype(CreateWindowExA) HookCreateWindowExA;

    static decltype(SetWindowTextA) HookSetWindowTextA;

    static decltype(CreatePropertySheetPageA) HookCreatePropertySheetPageA;

    static decltype(PropertySheetA) HookPropertySheetA;

    static decltype(CreateDialogParamA) HookCreateDialogParamA;

    static decltype(CreateDialogIndirectParamA) HookCreateDialogIndirectParamA;

    static decltype(DialogBoxParamA) HookDialogBoxParamA;

    static decltype(DialogBoxIndirectParamA) HookDialogBoxIndirectParamA;

    static decltype(SetDlgItemTextA) HookSetDlgItemTextA;

    static decltype(SendDlgItemMessageA) HookSendDlgItemMessageA;

    static decltype(AppendMenuA) HookAppendMenuA;

    static decltype(MessageBoxA) HookMessageBoxA;

    static decltype(MessageBoxExA) HookMessageBoxExA;

    static decltype(CreateFontA) HookCreateFontA;

    static decltype(CreateFontIndirectA) HookCreateFontIndirectA;

    static decltype(EnumFontFamiliesExA) HookEnumFontFamiliesExA;

    static decltype(EnumFontFamiliesA) HookEnumFontFamiliesA;

    static decltype(EnumFontsA) HookEnumFontsA;

    static decltype(GetGlyphOutlineA) HookGetGlyphOutlineA;

private:
    struct HookEnumFontContext
    {
        FONTENUMPROCA lpProc;
        LPARAM lParam;
    };

    static std::remove_pointer_t<FONTENUMPROCW> HookEnumFontCallback;
};

#endif // HOOK_H
