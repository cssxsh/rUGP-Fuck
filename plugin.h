#ifndef PLUGIN_H
#define PLUGIN_H

#include "stdafx.h"
#include <string>
#include <map>
#include "rugp.h"

extern "C" {
__declspec(dllexport) const AFX_EXTENSION_MODULE* PluginThisLibrary();
__declspec(dllexport) LPCSTR WINAPIV GetPluginString(DWORD param1, DWORD param2);
__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
}

std::wstring WINAPI UnicodeX(LPCSTR lpText, UINT nCodePage);

std::string WINAPI AnsiX(LPCWSTR lpText, UINT nCodePage);

std::string WINAPI AnsiX(LPCSTR lpText, UINT from, UINT to);

std::wstring GetUUID(const COceanNode* node);

std::wstring GetFilePath(const COceanNode* node);

std::wstring GetGameName();

struct CodePatchRecord
{
    SIZE_T block_size;
    BYTE origin[];
};

class StructuredException final : public std::exception
{
public:
    const UINT Code;
    const EXCEPTION_POINTERS* ExceptionPointers;

    StructuredException(UINT u, const EXCEPTION_POINTERS* pExp);

    static void __cdecl Trans(UINT, EXCEPTION_POINTERS*);

private:
    static LPCSTR __fastcall message(const EXCEPTION_POINTERS*);
};

class CObjectProxy final
{
public:
    static BOOL LoadFromModule(LPCSTR lpszModuleName);
    static void AttachHook();
    static void DetachHook();
    static void AttachCharacterPatch(LPCSTR lpszModuleName);
    static void Clear();

protected:
    static std::map<std::wstring, const CRuntimeClass*> RTC_MAP;
    static std::map<std::wstring, CVmCommand*> COMMAND_MAP;
    static std::map<HMODULE, const AFX_EXTENSION_MODULE*> MODULE_MAP;
    static std::map<LPVOID, CodePatchRecord*> PATCH_CACHE;
    static std::map<WORD, UINT> CHARACTER_MAP;
    static std::map<UINT, LPVOID> FONT_CACHE;

    static void __fastcall AttachCharacterSplit(LPBYTE address, LPCSTR lpszModuleName);
    static CVmCommand* __fastcall Fetch(const CVmCommand* ecx, Json::Value& edx);
    static void __fastcall Merge(CVmMsg*& message, Json::Value& text);
    static void __fastcall Merge(CVmGenericMsg*& generic, Json::Value& obj);
    static int __stdcall CharacterByteSize(LPCSTR);

    static void __cdecl HookSupportRio(AFX_EXTENSION_MODULE& module);
    static void __thiscall HookDestructor(CRio* ecx);
    static void __thiscall HookSerialize(CRio* ecx, CPmArchive*);
    static CVmCommand* __thiscall HookGetNextCommand(CCommandRef* ecx);

    static BOOL __cdecl HookIsMBCS(CHAR);
    static int __thiscall HookDrawFont1(LPVOID ecx, SHORT, SHORT, WORD*, WORD*, UINT, CFontContext*);
    static LPINT __thiscall HookDrawFont2(LPVOID ecx, LPINT, SHORT, SHORT, WORD*, WORD*, UINT, CFontContext*);
    static LPVOID __thiscall HookGetCachedFont(CS5RFont* ecx, UINT, COceanNode*);
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
