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
class CrUGP;
class CUuiGlobals;
class CFontContext;

class CCommandRef;
class CVmCommand;
class CVmMsg;

struct CObject_vtbl;
struct CRio_vtbl;


struct MFC_MODULE
{
    HMODULE native;
    int version;
    BOOL unicode;
};

MFC_MODULE GetMfc();

LPCSTR GetMfcVersion();

LPCSTR GetCUuiGlobals();

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

    static REG& FetchLibrarySupport();
    static IS_MULTIPLE& FetchIsMultiple();
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

    using LPDrawFont1 = int (__thiscall *)(LPVOID, DWORD, DWORD, WORD*, WORD*, UINT, CFontContext*);
    using LPDrawFont2 = void (__thiscall *)(LPVOID, LPINT, DWORD, DWORD, WORD*, WORD*, UINT, CFontContext*);

    static LPDrawFont1& FetchDrawFont1();
    static LPDrawFont2& FetchDrawFont2();

    static CS5i* Match(LPVOID part);

protected:
    static const CRio_vtbl* GetVisualTable();
};

class CS5RFont : public CVisual
{
public:
    DECLARE_DYNAMIC_RIO(CS5RFont)

    using LPGetFont = LPVOID (__thiscall *)(CS5RFont*, UINT, COceanNode*);

    LPVOID GetCachedFont(UINT, COceanNode*);
    LPVOID CreateNewFont(UINT, COceanNode*);

    static LPGetFont& FetchGetCachedFont();
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

    using LPDrawFont = int (__thiscall *)(CImgBox*, DWORD, DWORD, UINT, CFontContext*);

    int DrawFont(DWORD, DWORD, UINT, CFontContext*);

    static LPDrawFont& FetchDrawFont();
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
    using LPGetMotherOcean = COceanNode** (__cdecl *)(COceanNode**);

    BOOL IsDerivedFrom(const CRuntimeClass*) const;
    CRio* FetchRef();
    void ReleaseRef();
    DWORD GetAddress() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();

    static LPGetMotherOcean& FetchGetMotherOcean();
};

class CrUGP
{
public:
    LPCSTR GetVersion() const;

    static CrUGP* GetGlobal();

protected:
    CHAR version[];
};

class CUuiGlobals
{
public:
    UINT m_dwSchema;
    LPVOID field_0004;
    CString field_0008;
    CString m_strGameFolder;
    DWORD field_0010;
    DWORD field_0014;
    DWORD field_0018;
    DWORD field_001C;
    CString m_strGameName;
    DWORD m_dwFlags;
    DWORD field_0028;
    CNoTrackObject* field_002C; // CBootTracer
    DWORD m_dwResOffset;
    DWORD field_0034;
    DWORD field_0038;
    DWORD field_003C;

    static CUuiGlobals* GetGlobal();
};

class CFontContext
{
public:
    COceanNode* m_pAttr;
    DWORD field_0004;
    DWORD field_0008;
    DWORD field_000C;
};

class CCommandRef : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CCommandRef)

    CVmCommand* GetNextCommand();
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
