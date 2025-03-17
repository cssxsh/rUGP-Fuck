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

CString GetUUID(const COceanNode* node);

CString GetGameUUID();

CString GetGameName();

cJSON* LoadTextData();

void SaveTextData(const cJSON*);

class CObjectProxy final
{
public:
    const CRuntimeClass* m_pClass;
    const CObject_vtbl* m_pVTBL = nullptr;
    void (__thiscall *m_pfnSerialize)(CObjectEx*, CPmArchive*) = nullptr;
    CObject* (WINAPI *m_pfnCreateObject)() = nullptr;
    CVmCommand* (__thiscall *m_pfnGetNextCommand)(CCommandRef*) = nullptr;

    explicit CObjectProxy(const CRuntimeClass* pClass);

    static BOOL LoadFromModule(LPCSTR lpszModuleName);
    static void AttachHook();
    static void DetachHook();

protected:
    static std::map<std::string, CObjectProxy*> REF_MAP;
    static std::map<std::string, CVmCommand*> COMMAND_MAP;
    static AFX_EXTENSION_MODULE* TEMP_MODULE;

    static const CObject_vtbl* FASTCALL FindVirtualTable(const CRuntimeClass* rtc, FARPROC ctor);

    static void WINAPIV HookSupportRio(AFX_EXTENSION_MODULE&);

    static void FASTCALL HookSerialize(CObjectEx* ecx, DWORD edx, CPmArchive* archive);

    static CVmCommand* FASTCALL HookGetNextCommand(CCommandRef* ecx, DWORD edx);

    static CVmCommand* FASTCALL Merge(const CVmCommand* ecx, cJSON* edx);
};

#endif // PLUGIN_H
