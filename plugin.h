#ifndef PLUGIN_H
#define PLUGIN_H

#ifdef _DETOURS_H_
#pragma comment(lib, "detours.lib")
#endif // _DETOURS_H_

#include <stdafx.h>
#include <map>

extern "C" {
__declspec(dllexport) const AFX_EXTENSION_MODULE* PluginThisLibrary();
__declspec(dllexport) LPCSTR WINAPIV GetPluginString(DWORD param1, DWORD param2);
__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
}

class CObjectProxy final
{
public:
    const CRuntimeClass* m_pClass;
    // const CObject_vtbl* m_pVTBL = nullptr;
    // void (__thiscall *m_pfnSerialize)(CObjectEx*, CPmArchive*) = nullptr;
    CObject* (WINAPI *m_pfnCreateObject)() = nullptr;
    // CRio* (WINAPIV *m_pfnPlacementCreate)(CRio*) = nullptr;
    // CVmCommand* (__thiscall *m_pfnGetNextCommand)(CCommandRef*) = nullptr;
    
    explicit CObjectProxy(const CRuntimeClass* pClass);
    
    // LPCSTR GetModuleName() const;
    //
    // LPCSTR GetDescription() const;
    
    static CObjectProxy* Find(LPCSTR lpszClassName);

    static BOOL LoadFromModule(LPCSTR lpszModuleName);
    
    // static void AttachHook();
    //
    // static void DetachHook();

protected:
    static std::map<LPCSTR, CObjectProxy*> ERF_MAP;
    // static CMapStringToPtr COMMAND_MAP;
    //
    // static const CObject_vtbl* FASTCALL FindVirtualTable(const CRuntimeClass* rtc, FARPROC ctor);
    //
    // static void FASTCALL HookSerialize(CObjectEx* ecx, DWORD edx, CPmArchive* archive);
    //
    // static CVmCommand* FASTCALL HookGetNextCommand(CCommandRef* ecx, DWORD edx);
    //
    // static CVmCommand* FASTCALL Merge(const CVmCommand* ecx, const cJSON* edx);

public:
    // class Iterator final
    // {
    // public:
    //     explicit Iterator(const CRuntimeClass* pBaseClass = &CObject::classCObject);
    //     BOOL HasNext() const;
    //     CObjectProxy* Next();
    //
    // private:
    //     const CRuntimeClass* m_pBaseClass;
    //     POSITION m_pos;
    // };
};

#endif // PLUGIN_H
