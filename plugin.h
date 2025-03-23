#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdafx.h>
#include <string>
#include <map>
#include "rugp.h"

#ifdef _DETOURS_H_
#pragma comment(lib, "detours.lib")
#endif // _DETOURS_H_

#ifdef cJSON__h
#pragma comment(lib, "cjson.lib")

inline cJSON* cJSON_CreateString(const LPCSTR string, const UINT nCodePage)
{
    if (nCodePage == CP_UTF8) return cJSON_CreateString(string);
    const auto unicode = Unicode(string, nCodePage);
    const auto buffer = Ansi(unicode, CP_UTF8);
    free(unicode);
    return cJSON_CreateString(buffer);
}

inline LPSTR cJSON_GetStringValue(const cJSON* const item, const UINT nCodePage)
{
    if (nCodePage == CP_UTF8) return cJSON_GetStringValue(item);
    const auto string = cJSON_GetStringValue(item);
    const auto unicode = Unicode(string, CP_UTF8);
    const auto size = WideCharToMultiByte(nCodePage, 0, unicode, -1, nullptr, 0, nullptr, nullptr);
    const auto buffer = static_cast<LPSTR>(cJSON_malloc(size));
    WideCharToMultiByte(nCodePage, 0, unicode, -1, buffer, size, nullptr, nullptr);
    free(unicode);
    return buffer;
}

#endif // cJSON__h

extern "C" {
__declspec(dllexport) const AFX_EXTENSION_MODULE* PluginThisLibrary();
__declspec(dllexport) LPCSTR WINAPIV GetPluginString(DWORD param1, DWORD param2);
__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
}

std::wstring GetUUID(const COceanNode* node);

std::wstring GetFilePath(const COceanNode* node);

std::wstring GetGameName();

template <typename F>
void CALLBACK DetourAttachCallback(F&, F);

template <typename F>
void CALLBACK DetourDetachCallback(F&, F);

class CObjectProxy final
{
public:
    const CRuntimeClass* m_pClass;
    const CObject_vtbl* m_pVTBL = nullptr;
    CObject* (__stdcall *m_pfnCreateObject)() = nullptr;
    void (__thiscall *m_pfnDestructor)(CRio*) = nullptr;
    void (__thiscall *m_pfnSerialize)(CObjectEx*, CPmArchive*) = nullptr;
    CVmCommand* (__thiscall *m_pfnGetNextCommand)(CCommandRef*) = nullptr;

    explicit CObjectProxy(const CRuntimeClass* pClass);

    static BOOL LoadFromModule(LPCSTR lpszModuleName);
    static void AttachHook();
    static void DetachHook();
    static void Clear();

protected:
    static std::map<std::wstring, CObjectProxy*> REF_MAP;
    static std::map<std::wstring, CVmCommand*> COMMAND_MAP;
    static std::map<HMODULE, const AFX_EXTENSION_MODULE*> MODULE_MAP;

    static const CObject_vtbl* __fastcall FindVirtualTable(const CRuntimeClass* rtc, FARPROC ctor);

    static void __cdecl HookSupportRio(AFX_EXTENSION_MODULE& module);
    static void __thiscall HookDestructor(CRio* ecx);
    static void __thiscall HookSerialize(CVisual* ecx, CPmArchive* archive);
    static CVmCommand* __thiscall HookGetNextCommand(CCommandRef* ecx);

    static void __thiscall HookDrawSzText(CS5i* ecx, DWORD, DWORD, LPCSTR, COceanNode**);
    static void __thiscall HookDrawSzTextClip(CS5i* ecx, DWORD, DWORD, LPCSTR, COceanNode**, WORD*);

    static void __thiscall HookDrawSzText(CImgBox* ecx, DWORD, DWORD, LPCSTR, COceanNode**);

    static int __thiscall HookCharacterByteSize(CRio* ecx, LPCSTR);
};

class COceanTree final
{
public:
    static void AttachHook();
    static void DetachHook();

protected:
    static COceanNode** __cdecl HookGetMotherOcean(COceanNode** pNode);

    class Iterator final
    {
    public:
        explicit Iterator(const COceanNode* root = COceanNode::GetRoot());
        DWORD Level() const;
        const COceanNode* Next();

        static void AttachHook();
        static void DetachHook();

    protected:
        const COceanNode* m_pNode;
        DWORD m_nLevel;
        std::map<const COceanNode*, WORD> m_pVisited;
    };
};

#endif // PLUGIN_H
