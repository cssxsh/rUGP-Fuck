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
#define DETOUR(function) \
        static decltype(function)* pfn##function; \
        static decltype(function) Hook##function;
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

private:
    struct HookEnumFontContext
    {
        FONTENUMPROCA lpProc;
        LPARAM lParam;
    };

    static std::remove_pointer_t<FONTENUMPROCW> HookEnumFontCallback;
};

#endif // HOOK_H
