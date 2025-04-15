#ifndef RUGP_7_H
#define RUGP_7_H

#include "stdafx.h"
#include <map>
#include <string>

extern "C" {
__declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);
}

class CObjectEx;
class CRio;

class CVisual;
class CRip;

class CObjectOcean;
class CStaticOceanRoot;
class CrelicUnitedGameProject;
class CObjectArcMan;
class CProcessOcean;

class CPolymorphicArchive;
class COceanNode;
class COceanHashTable;
class CrUGP;
class CUuiGlobals;

class CCommandRef;
class CVmCommand;

class CObjectProxy;

#define DECLARE_DYNAMIC_MOCK(class_name) \
protected: \
    static inline CRuntimeClass* PASCAL _GetBaseClass() \
    { return CRuntimeClass::FromName(#class_name)->m_pfnGetBaseClass(); } \
public: \
    static inline CRuntimeClass* PASCAL GetThisClass() \
    { return CRuntimeClass::FromName(#class_name); } \
    virtual CRuntimeClass* GetRuntimeClass() const;

class CObjectEx : public CObject
{
public:
    DECLARE_DYNAMIC_MOCK(CObjectEx)

    virtual void Serialize(CPolymorphicArchive*) = 0;
};

class CRio : public CObject
{
public:
    DECLARE_DYNAMIC_MOCK(CRio)

    COceanNode* m_pNode;
    WORD m_wStyle;

    virtual LRESULT QueryInterface(LPCSTR, LPVOID&) = 0;
    virtual DWORD AddRef() = 0;
    virtual DWORD Release() = 0;
    virtual BOOL NewObjectConstruct(LPCSTR) = 0;
    virtual BOOL _(DWORD) = 0;
    virtual void SerializeUserCondition(CPolymorphicArchive*) = 0;
};

class CVisual : public CRio
{
public:
    DECLARE_DYNAMIC_MOCK(CVisual)
};

class CRip : public CVisual
{
public:
    DECLARE_DYNAMIC_MOCK(CRip)
};

class CCommandRef : public CRio
{
public:
    DECLARE_DYNAMIC_MOCK(CCommandRef)

    virtual CVmCommand* GetNextCommand() = 0;
    virtual BOOL GetNumberOfMessages(int&, int&) = 0;
};

class CVmCommand : public CObjectEx
{
public:
    DECLARE_DYNAMIC_MOCK(CVmCommand)

    CVmCommand* m_pNext;
    DWORD m_dwFlags;

    virtual CVmCommand* _(DWORD) = 0; // CCharVoiceOcean
    virtual CVmCommand* ExecCommand() = 0;
    virtual int AfterCreateOffsetToPtr(LPBYTE) = 0;
    virtual int GetVariableAreaSize() const = 0;
    virtual CVmCommand* _(const COceanNode*, DWORD) = 0; // CParseBgBox
};

class CObjectOcean : public CRio
{
public:
    DECLARE_DYNAMIC_MOCK(CObjectOcean)
};

class CStaticOceanRoot : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_MOCK(CStaticOceanRoot)
};

class CrelicUnitedGameProject : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_MOCK(CrelicUnitedGameProject)

    // CDatabase* GetGameProfile();
    //
    // static CrelicUnitedGameProject* GetGlobal();
};

class CObjectArcMan : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_MOCK(CObjectArcMan)

    // CInstallSource* GetSourceObject(INT_PTR);
    //
    // static CObjectArcMan* GetGlobal();
};

class CProcessOcean : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_MOCK(CProcessOcean)

    // using LPBeginProcess = UINT (__thiscall *)(CProcessOcean*, CView*);
    //
    // static LPBeginProcess& FetchBeginProcess();
};

class CPolymorphicArchive
{
public:
    DWORD m_dwFlags;
    CArchive m_native;

    virtual LONG Seek(LONG, UINT) = 0;

    const CArchive* GetNative() const;

    static CPolymorphicArchive* __fastcall CreateLoadFileArchive(LPCTSTR);
    static CPolymorphicArchive* __fastcall CreateSaveFileArchive(LPCTSTR);
    static void __fastcall DestroyArchive(CPolymorphicArchive*);

protected:
    CPolymorphicArchive();
    ~CPolymorphicArchive();
};

class COceanNode
{
public:
    const CRio* m_pObject;
    const COceanNode* m_pNext;
    CString m_strName;
    const COceanNode* m_pParent;
    const COceanHashTable* m_pChildren;
    const CRuntimeClass* m_pRTC;
    UINT m_nRefCount;
    DWORD m_dwFlags;
    UINT_PTR m_dwResAddr;
    UINT_PTR m_dwResSize;
    DWORD field_0028;

protected:
    COceanNode();
    ~COceanNode();

public:
    BOOL IsDerivedFrom(const CRuntimeClass*) const;
    CRio* Fetch() const;
    BOOL AccessChildNodes() const;
    UINT_PTR GetAddress() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();

    class Iterator final
    {
    protected:
        const COceanNode* m_current;
        const COceanNode* m_root;

    public:
        explicit Iterator(const COceanNode* node);
        const COceanNode* operator*() const;
        Iterator& operator++();
        Iterator operator++(int count);
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    static Iterator end();
};

class COceanHashTable
{
public:
    UINT m_nCount;
    const COceanNode* m_arrBucket[0x0C];
};

class CrUGP final
{
public:
    TCHAR m_strVersion[0x20];
    CString p_strPlatform;
    CString field_0x0044;
    DWORD m_dwFlags;

    static const CrUGP* GetGlobal();

protected:
    CrUGP();
};

class CUuiGlobals
{
public:
    DWORD m_dwSchema;
    FARPROC field_0004;
    CString m_strInstallDriver;
    CString m_strGameFolder;
    DWORD field_0010;
    DWORD field_0014;
    DWORD field_0018;
    FARPROC m_pfnInstallHandler; // CustomInstallHandler
    CString m_strGameName;
    DWORD m_dwFlags;
    DWORD field_0028;
    LPVOID m_pBootTracer;
    DWORD m_dwResKeyA;
    DWORD m_dwResKeyB;
    DWORD field_0038;
    UINT m_nInstallType;

    static const CUuiGlobals* GetGlobal();

protected:
    CUuiGlobals();
};

class CObjectProxy final
{
public:
    static void AttachHook();
    static void DetachHook();

protected:
    static std::map<std::string, FARPROC> PROC_CACHE;

    static CString __fastcall GetPatchFilePath(const COceanNode* node);

    using SerializeProc = void (__thiscall *)(CRio*, CPolymorphicArchive*);
    static SerializeProc& FetchSerialize(CRuntimeClass*);
    static std::remove_pointer_t<SerializeProc> HookSerialize;

    using GetNextCommandProc = CVmCommand* (__thiscall *)(CCommandRef*);
    static GetNextCommandProc& FetchGetNextCommand(CRuntimeClass*);
    static std::remove_pointer_t<GetNextCommandProc> HookGetNextCommand;
};

#endif // RUGP_7_H
