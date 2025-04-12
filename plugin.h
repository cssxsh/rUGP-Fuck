#ifndef PLUGIN_H
#define PLUGIN_H

#include "stdafx.h"
#include <string>
#include <map>
#include "rugp.h"

extern "C" {
__declspec(dllexport) const AFX_EXTENSION_MODULE* PluginThisLibrary();
__declspec(dllexport) LPCSTR WINAPIV GetPluginString();
__declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
}

std::wstring WINAPI UnicodeX(LPCSTR lpText, UINT nCodePage);

std::string WINAPI AnsiX(LPCWSTR lpText, UINT nCodePage);

std::string WINAPI AnsiX(LPCSTR lpText, UINT from, UINT to);

std::wstring GetUUID(const COceanNode* node);

struct CodePatchRecord
{
    union
    {
        PVOID target;
        SIZE_T block_size;
    };

    BYTE codes[];
};

class StructuredException final : public std::exception
{
public:
    const EXCEPTION_POINTERS* m_pExceptionPointers;

    StructuredException(UINT u, const EXCEPTION_POINTERS* pExp);

    static std::remove_pointer_t<_se_translator_function> Trans;
};

class CObjectProxy final
{
public:
    static BOOL LoadFromModule(LPCSTR lpszModuleName);
    static void AttachHook();
    static void DetachHook();
    static void AttachCharacterPatch(LPCSTR lpszModuleName);
    static void DetachCharacterPatch();
    static void Clear();

protected:
    static std::map<std::wstring, const CRuntimeClass*> RTC_MAP;
    static std::map<std::wstring, CVmCommand*> COMMAND_MAP;
    static std::map<HMODULE, const AFX_EXTENSION_MODULE*> MODULE_MAP;
    static std::map<LPVOID, CodePatchRecord*> PATCH_CACHE;
    static std::map<LPVOID, CodePatchRecord*> SPLIT_CACHE;
    static std::map<WORD, UINT> CHARACTER_MAP;
    static std::map<UINT, LPVOID> FONT_CACHE;

    static void __fastcall AttachCharacterSplit(LPBYTE address, LPCSTR lpszModuleName);
    static CVmCommand* __fastcall Fetch(const CVmCommand* ecx, Json::Value& edx);
    static void __fastcall Merge(CVmMsg*& message, Json::Value& text);
    static void __fastcall Merge(CVmGenericMsg*& generic, Json::Value& obj);
    static void __fastcall Merge(CVmCall*& call, Json::Value& arr);
    static int __fastcall CharacterByteSize(LPCSTR);
    static std::wstring __fastcall GetPatchFilePath(const COceanNode* node);

    static std::remove_pointer_t<CRio::LPLibrarySupport> HookSupportRio;
    static std::remove_pointer_t<CRio::LPDestructor> HookDestructor;
    static std::remove_pointer_t<CRio::LPSerialize> HookSerialize;
    static std::remove_pointer_t<CCommandRef::LPGetNextCommand> HookGetNextCommand;
    static std::remove_pointer_t<COceanNode::LPGetLocalFullPathName> HookGetLocalFullPathName;

    static std::remove_pointer_t<GMfc::LPIsMBCS> HookIsMBCS;
    static std::remove_pointer_t<CDatabase::LPRead> HookRead;
    static std::remove_pointer_t<CDatabase::LPWrite> HookWrite;
    static std::remove_pointer_t<CS5i::LPDrawFont1> HookDrawFont1;
    static std::remove_pointer_t<CS5i::LPDrawFont2> HookDrawFont2;
    static std::remove_pointer_t<CS5RFont::LPGetFont> HookGetCachedFont;

    static std::remove_pointer_t<CUuiGlobals::LPStep> HookStep;
    static std::remove_pointer_t<CProcessOcean::LPBeginProcess> HookBeginProcess;
};

#endif // PLUGIN_H
