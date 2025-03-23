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
struct CObjectEx_vtbl;
struct CCommandRef_vtbl;

template <typename F>
using HookProc = F (CALLBACK*)(F, F);

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

    static void __cdecl LibrarySupport(AFX_EXTENSION_MODULE&);

    static FARPROC HookLibrarySupport(HookProc<REG>, REG);
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

    using LPDrawSzText = void (__thiscall *)(CS5i*, DWORD, DWORD, LPBYTE, COceanNode**);
    using LPDrawSzTextClip = void (__thiscall *)(CS5i*, DWORD, DWORD, LPBYTE, COceanNode**, WORD*);
    using LPDrawFont = DWORD (__thiscall *)(CS5i*, DWORD, DWORD, WORD*, WORD*, UINT, COceanNode**);

    DWORD DrawFont(DWORD, DWORD, WORD*, WORD*, UINT, COceanNode**);

    static FARPROC HookDrawSzText(HookProc<LPDrawSzText>, LPDrawSzText);
    static FARPROC HookDrawSzTextClip(HookProc<LPDrawSzTextClip>, LPDrawSzTextClip);
    static FARPROC HookDrawFont(HookProc<LPDrawFont>, LPDrawFont);

protected:
    static const CObjectEx_vtbl* GetVisualTable();
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

    using LPDrawSzText = void (__thiscall *)(CImgBox*, DWORD, DWORD, LPBYTE, COceanNode**);
    using LPDrawFont = DWORD (__thiscall *)(CImgBox*, DWORD, DWORD, UINT, COceanNode**);

    DWORD DrawFont(DWORD, DWORD, UINT, COceanNode**);

    static FARPROC HookDrawSzText(HookProc<LPDrawSzText>, LPDrawSzText);
};

class CMessBox : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CMessBox)

    using LPAttachTextCore = void (__thiscall *)(CMessBox*, LPBYTE);

    static FARPROC HookAttachTextCore(HookProc<LPAttachTextCore>, LPAttachTextCore);

protected:
    static const CObjectEx_vtbl* GetVisualTable();
};

class CPmArchive
{
protected:
    ~CPmArchive() = default;

public:
    virtual LONG Seek(LONG, UINT) = 0;

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
    using GET = COceanNode** (__cdecl *)(COceanNode**);

    BOOL IsDerivedFrom(const CRuntimeClass*) const;
    CRio* Fetch() const;
    DWORD GetAddress() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();
    static const COceanNode* GetMotherOcean();

    static FARPROC HookGetMotherOcean(HookProc<GET>, GET);
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

struct CObjectEx_vtbl : CObject_vtbl
{
    void (__thiscall *Serialize)(CObjectEx*, CPmArchive*);
};

struct CCommandRef_vtbl
{
    CVmCommand* (__thiscall *GetNextCommand)(CCommandRef*);
};

#endif // RUGP_H
