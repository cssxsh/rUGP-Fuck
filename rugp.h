#ifndef RUGP_H
#define RUGP_H

#include <stdafx.h>

struct MFC_MODULE;

class CObjectEx;
class CRio;

class CVisual;
class CRip;
class CS5i;

class CUI;
class CImgBox;
class CMessBox;

class CPmArchive;
class COceanNode;

class CCommandRef;
class CVmCommand;
class CVmMsg;

struct CObject_vtbl;
struct CRio_vtbl;

template <typename F>
using HookCallback = void (CALLBACK*)(F&, F);

struct MFC_MODULE
{
    HMODULE native;
    int version;
    BOOL unicode;
};

MFC_MODULE GetMfc();

LPCSTR GetMfcVersion();

LPCSTR GetRugpVersion();

#define DECLARE_DYNAMIC_EX(class_name) \
public: \
    static const CRuntimeClass* GetClass##class_name(); \
    virtual CRuntimeClass* GetRuntimeClass() const;

class CObjectEx : public CObject
{
public:
    DECLARE_DYNAMIC_EX(CObjectEx)

    virtual void Serialize(CPmArchive&) = 0;
};

#define DECLARE_DYNAMIC_RIO(class_name) \
public: \
    static const CRuntimeClass* GetClass##class_name(); \
    virtual CRuntimeClass* GetRuntimeClass() const;

class CRio : public CObjectEx
{
public:
    DECLARE_DYNAMIC_RIO(CRio)

    COceanNode* m_pNode;
    WORD m_wStyle;

    // virtual LRESULT QueryInterface(LPCSTR, LPVOID*) = 0;
    // virtual DWORD AddRef() = 0;
    // virtual DWORD Release() = 0;
    // virtual BOOL NewObjectConstruct(LPCSTR) = 0;
    // virtual void SerializeUserCondition(CPmArchive&) = 0;

    using REG = void (__cdecl *)(AFX_EXTENSION_MODULE&);
    using IS_MULTIPLE = BOOL (__cdecl *)(char);
    using CHARACTER_BYTE_SIZE = int (__thiscall *)(CRio*, LPCSTR);

    static void __cdecl LibrarySupport(AFX_EXTENSION_MODULE&);

    static void HookLibrarySupport(HookCallback<REG>, REG);
    static void HookIsMultiple(HookCallback<IS_MULTIPLE>, IS_MULTIPLE);
};

class CVisual : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CVisual)
};

class CRip : public CVisual
{
public:
    DECLARE_DYNAMIC_RIO(CRip)
};

class CS5i : public CVisual
{
public:
    DECLARE_DYNAMIC_RIO(CS5i)

    using LPDrawFont = int (__thiscall *)(CS5i*, DWORD, DWORD, WORD*, WORD*, UINT, COceanNode**);

    int DrawFont(DWORD, DWORD, WORD*, WORD*, UINT, COceanNode**);

    static void HookDrawFont(HookCallback<LPDrawFont>, LPDrawFont);

protected:
    static const CRio_vtbl* GetVisualTable();
};

class CUI : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CUI)
};

class CImgBox : public CUI
{
public:
    DECLARE_DYNAMIC_RIO(CImgBox)

    using LPDrawFont = int (__thiscall *)(CImgBox*, DWORD, DWORD, UINT, COceanNode**);

    int DrawFont(DWORD, DWORD, UINT, COceanNode**);

    static void HookDrawFont(HookCallback<LPDrawFont>, LPDrawFont);
};

class CMessBox : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CMessBox)

    using LPStore = void (__thiscall *)(LPVOID, LPCVOID, SIZE_T);
    using LPLoad = void (__thiscall *)(LPVOID, LPVOID, SIZE_T);

    static LPStore& GetStore();
    static LPLoad& GetLoad();

    static void HookAttachTextCore(HookCallback<FARPROC>, CHARACTER_BYTE_SIZE);

protected:
    static FARPROC IS;
    static FARPROC SINGLE;
    static FARPROC MULTIPLE;
    static CHARACTER_BYTE_SIZE SIZE;

    static void EbxToEsi();
    static void EbpToEbx();
    static void EsiToEbx();


    static FARPROC GetAttachTextCore();
    static FARPROC GetAttachInstructionText();

    static const CRio_vtbl* GetVisualTable();
};

class CPmArchive
{
protected:
    ~CPmArchive() = default;

public:
    virtual LONG Seek(LONG, UINT) = 0;

    const CArchive* GetNative();

    static CPmArchive* CreateLoadFilePmArchive(LPCSTR path);
    static CPmArchive* CreateSaveFilePmArchive(LPCSTR path);
    static void DestroyPmArchive(CPmArchive*);
};

class COceanNode
{
public:
    struct POS
    {
        BOOL m_bNext;
        INT m_nIndex;
    };

    struct Children
    {
        UINT m_nCount;
        COceanNode* m_pBucket[0x0C];
    };

    CRio* m_pObject;
    COceanNode* m_pNext;
    CString m_strName;
    COceanNode* m_pParent;
    Children* m_pChildren;
    CRuntimeClass* m_pRTC;
    UINT m_nRefCount;
    DWORD m_dwFlags;
    DWORD m_dwResAddr;
    DWORD m_dwResSize;
    DWORD field_0028;
    DWORD field_002C; // CObject

protected:
    ~COceanNode() = default;

public:
    using RELEASE = void (__thiscall *)(COceanNode*);
    using GET = COceanNode** (__cdecl *)(COceanNode**);

    BOOL IsDerivedFrom(const CRuntimeClass*) const;
    CRio* Fetch() const;
    void Release();
    DWORD GetAddress() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();
    static const COceanNode* GetMotherOcean();

    static void HookRelease(HookCallback<RELEASE>, RELEASE);
    static void HookGetMotherOcean(HookCallback<GET>, GET);
};

class CCommandRef : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CCommandRef)

    // virtual CVmCommand* GetNextCommand() = 0;
};

class CVmCommand : public CObjectEx
{
public:
    DECLARE_DYNAMIC_EX(CVmCommand)

    CVmCommand* m_pNext;
    DWORD m_dwFlags;

    int GetVariableAreaSize() const;
};

class CVmMsg : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmMsg)

    COceanNode* m_pMessBoxNode; // CMessBox
    COceanNode* m_pCRioNode; // COptimizedObs
    CHAR m_area[];
};

struct CObject_vtbl
{
    CRuntimeClass* (__thiscall *GetRuntimeClass)(CObject*);
    void (__thiscall *Destructor)(CObject*, DWORD);
    void (__thiscall *Serialize)(CObject*, CArchive*);
    void (__thiscall *AssertValid)(CObject*);
    void (__thiscall *Dump)(CObject*, CDumpContext*);
};

struct CRio_vtbl : CObject_vtbl
{
    void (__thiscall *Serialize)(CRio*, CPmArchive*);
};

#endif // RUGP_H
