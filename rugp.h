#ifndef RUGP_H
#define RUGP_H

#include "stdafx.h"

struct MFC_MODULE;

class CStringX;
class GMfc;
class CProfile;
class CWinRegistry;

class CObjectEx;
class CRio;

class CVisual;
class CRip;
class CS5i;
class CS5RFont;
class CEditData;

class CUI;
class CImgBox;

class CDatabase;

class CObjectOcean;
class CrelicUnitedGameProject;
class CObjectArcMan;
class CProcessOcean;

class CPmArchive;
class COceanNode;
class COceanHashTable;
class CRef;
class CrUGP;
class CUuiGlobals;
class CFontContext;
class CRioMsg;
class CVmVar;
class CInstallSource;
class CRegistryCache;

class CCommandRef;
class CVmCommand;
class CVmMsg;
class CVmGenericMsg;
class CVmVarObj;

struct CMemberInfo;
struct CMsgRTC;
struct ProfileInfo;

struct CObject_vtbl;
struct CRio_vtbl;

template <typename T, int SIZE = 0x11>
struct HashBucket;

struct MFC_MODULE
{
    HMODULE native;
    int version;
};

MFC_MODULE GetMfc();

class CStringX
{
    LPSTR m_pszData = nullptr;

public:
    // ReSharper disable CppNonExplicitConvertingConstructor
    CStringX(const CStringX&);
    CStringX(LPCSTR); // NOLINT(*-explicit-constructor)
    CStringX();
    // ReSharper restore CppNonExplicitConvertingConstructor
    ~CStringX();

    CStringX& operator=(LPCSTR);
    CStringX& operator=(const CStringX&);
    // ReSharper disable CppNonExplicitConversionOperator
    operator CStringA&(); // NOLINT(*-explicit-constructor)
    operator LPCSTR() const; // NOLINT(*-explicit-constructor)
    // ReSharper restore CppNonExplicitConversionOperator

    void FormatV(_Printf_format_string_ LPCSTR, va_list);

    static CStringX FormatX(_Printf_format_string_ LPCSTR, ...);

protected:
    template <class T>
    CStringX(const T*, CStringX* (__thiscall *)(const T*, CStringX*));
    template <class T>
    CStringX(const T*, LPCSTR, LPCSTR, CStringX* (__thiscall *)(const T*, CStringX*, LPCSTR, LPCSTR));

public:
    static CStringX Fetch(
        const CVmVar*,
        CStringX* (__thiscall *)(const CVmVar*, CStringX*));
    static CStringX Fetch(
        const CProfile*,
        LPCSTR,
        LPCSTR,
        CStringX* (__thiscall *)(const CProfile*, CStringX*, LPCSTR, LPCSTR));
};

class GMfc final
{
public:
    using LPIsMBCS = BOOL (__cdecl *)(CHAR);

    static LPIsMBCS& FetchIsMBCS();
};

class CProfile
{
    LPSTR m_pszData = nullptr;
    DWORD field_0004 = 0;

public:
    explicit CProfile(CStringX&);
    CProfile(const CProfile&);
    CProfile();
    ~CProfile();

    CProfile& operator=(const CProfile&);
    CStringX operator[](LPCSTR) const;
    // ReSharper disable CppNonExplicitConversionOperator
    operator LPCSTR() const; // NOLINT(*-explicit-constructor)
    // ReSharper restore CppNonExplicitConversionOperator

    class Iterator final
    {
    protected:
        const CProfile* m_profile;
        LPCSTR m_pos;

    public:
        explicit Iterator(const CProfile* profile, LPCSTR pos);
        std::pair<CStringX, CStringX> operator*() const;
        Iterator& operator++();
        Iterator operator++(int count);
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;

protected:
    LPCSTR EnumKeyValue(LPCSTR, CStringX&, CStringX&) const;

    template <class T>
    CProfile(const T*, CProfile* (__thiscall *)(const T*, CProfile*));

public:
    static CProfile Fetch(const CRioMsg*, CProfile* (__thiscall *)(const CRioMsg*, CProfile*));
};

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

    using LPLibrarySupport = void (__cdecl *)(AFX_EXTENSION_MODULE&);
    using LPDestructor = void (__thiscall *)(CRio*);
    using LPSerialize = void (__thiscall *)(CRio*, CPmArchive*);

    LPDestructor& FetchDestructor() const;
    LPSerialize& FetchSerialize() const;

    static LPLibrarySupport& FetchLibrarySupport();
    static LPDestructor& FetchDestructor(const CRuntimeClass*);
    static LPSerialize& FetchSerialize(const CRuntimeClass*);

protected:
    static const CRio_vtbl* FindVisualTable(const CRuntimeClass*);
    static LPDestructor FindDestructor(const CRio_vtbl*);
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

    class Part final
    {
    public:
        // ReSharper disable CppNonExplicitConversionOperator
        operator CS5i&(); // NOLINT(*-explicit-constructor)
        // ReSharper restore CppNonExplicitConversionOperator
    };

    using LPDrawFont1 = int (__thiscall *)(Part*, SHORT, SHORT, WORD*, WORD*, UINT, CFontContext*);
    using LPDrawFont2 = LPINT (__thiscall *)(Part*, LPINT, SHORT, SHORT, WORD*, WORD*, UINT, CFontContext*);

    static LPDrawFont1& FetchDrawFont1();
    static LPDrawFont2& FetchDrawFont2();

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

class CEditData : public CVisual
{
public:
    DECLARE_DYNAMIC_RIO(CEditData)

    CStringX& FetchText();
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

    using LPDrawFont = int (__thiscall *)(CImgBox*, SHORT, SHORT, UINT, CFontContext*);
    using LPDrawSingleLineText = LPCSTR (__thiscall *)(CImgBox*, SHORT, SHORT, LPCSTR, CFontContext*);
    using LPDrawSzText = void (__thiscall *)(CImgBox*, SHORT, SHORT, LPCSTR, CFontContext*);

    int DrawFont(SHORT, SHORT, UINT, CFontContext*);
    LPCSTR DrawSingleLineText(SHORT, SHORT, LPCSTR, CFontContext*);
    void DrawSzText(SHORT, SHORT, LPCSTR, CFontContext*);

    static LPDrawFont& FetchDrawFont();
    static LPDrawSingleLineText& FetchDrawSingleLineText();
    static LPDrawSzText& FetchDrawSzText();
};

class CDatabase : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CDatabase)

    using LPInitializeDatabase = void (__thiscall *)(CDatabase*);
    using LPRead = CStringX* (__thiscall *)(const CDatabase*, CStringX*, LPCSTR, LPCSTR);
    using LPWrite = void (__thiscall *)(CDatabase*, LPCSTR, LPCSTR);
    using LPIsKeyExist = BOOL (__thiscall *)(CDatabase*, LPCSTR);

    static LPInitializeDatabase& FetchInitialize();
    static LPRead& FetchRead();
    static LPWrite& FetchWrite();
    static LPIsKeyExist& FetchIsExist();
};

class CObjectOcean : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CObjectOcean)
};

class CrelicUnitedGameProject : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_RIO(CrelicUnitedGameProject)

    CDatabase* GetGameProfile();

    static CrelicUnitedGameProject* GetGlobal();
};

class CObjectArcMan : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_RIO(CObjectArcMan)

    CInstallSource* GetSourceObject(INT_PTR);

    static CObjectArcMan* GetGlobal();
};

class CProcessOcean : public CObjectOcean
{
public:
    DECLARE_DYNAMIC_RIO(CProcessOcean)

    using LPBeginProcess = UINT (__thiscall *)(CProcessOcean*, CView*);

    static LPBeginProcess& FetchBeginProcess();
};

class CPmArchive
{
protected:
    ~CPmArchive();

public:
    virtual LONG Seek(LONG, UINT) = 0;

    const CArchive* GetNative() const;

    static CPmArchive* CreateLoadFilePmArchive(LPCSTR);
    static CPmArchive* CreateSaveFilePmArchive(LPCSTR);
    static void DestroyPmArchive(CPmArchive*);
};

class COceanNode
{
public:
    struct POS
    {
        const COceanNode* m_pNode = nullptr;
        INT m_nIndex = 0;
    };

    CRio* m_pObject;
    COceanNode* m_pNext;
    CStringX m_strName;
    COceanNode* m_pParent;
    COceanHashTable* m_pChildren;
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
    using LPGetLocalFullPathName = CStringX* (__thiscall *)(const COceanNode*, CStringX*);

    BOOL IsDerivedFrom(const CRuntimeClass*) const;
    CRio* Fetch() const;
    void ReleaseRef();
    const COceanNode* FindChildrenTypeOf(const CRuntimeClass*) const;
    const COceanNode* FindParentTypeOf(const CRuntimeClass*) const;
    const COceanNode* GetNextAssocRef(POS&, CStringX&) const;
    BOOL AccessChildNodes() const;
    UINT_PTR GetAddress() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();

    static LPGetLocalFullPathName& FetchGetLocalFullPathName();

    class Iterator final
    {
    protected:
        const COceanNode* m_ptr;
        std::map<const COceanNode*, POS> m_record;

    public:
        explicit Iterator(const COceanNode* node);
        const COceanNode* operator*() const;
        Iterator& operator++();
        Iterator operator++(int count);
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    static Iterator end();
};

class COceanHashTable
{
public:
    UINT m_nCount;
    const COceanNode* m_arrBucket[0x0C];
};

class CRef
{
public:
    COceanNode* m_pNode;

    // ReSharper disable CppNonExplicitConvertingConstructor
    CRef(const CRef&);
    CRef(COceanNode*); // NOLINT(*-explicit-constructor)
    CRef();
    // ReSharper restore CppNonExplicitConvertingConstructor
    ~CRef();

    CRef& operator=(COceanNode*);
    // ReSharper disable CppNonExplicitConversionOperator
    template <class T>
    operator T*() const; // NOLINT(*-explicit-constructor)
    // ReSharper restore CppNonExplicitConversionOperator

protected:
    template <class C, typename P>
    CRef(const C*, const P*, CRef* (__thiscall *)(const C*, CRef*, const P*));

public:
    static CRef Fetch(
        const COceanNode*,
        const CRuntimeClass*,
        CRef* (__thiscall *)(const COceanNode*, CRef*, const CRuntimeClass*));
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
    CUuiGlobals();

public:
    DWORD m_dwSchema;
    FARPROC field_0004;
    CStringX m_strInstallDriver;
    CStringX m_strGameFolder;
    DWORD field_0010;
    DWORD field_0014;
    DWORD field_0018;
    FARPROC m_pfnInstallHandler; // CustomInstallHandler
    CStringX m_strGameName;
    DWORD m_dwFlags;
    DWORD field_0028;
    class CBootTracer* m_pBootTracer;
    DWORD m_dwResKeyA;
    DWORD m_dwResKeyB;
    DWORD field_0038;
    UINT m_nInstallType;

    using LPStep = void (__thiscall *)(CBootTracer*, INT_PTR);

    static CUuiGlobals* GetGlobal();

    static LPStep& FetchStep();
};

class CFontContext
{
public:
    COceanNode* m_pAttr;
    DWORD field_0004;
    DWORD field_0008;
    DWORD field_000C;
};

class CRioMsg
{
public:
    const CMsgRTC* m_pRTC;
    CObjectEx* m_pObj;

    CProfile ToMsgString() const;

    static CRioMsg* FromMsgString(LPCSTR);
};

class CVmVar
{
public:
    DWORD m_pValue;

    CStringX ToSerialString() const;

    void FromSerialString(LPCSTR);
};

class CInstallSource
{
public:
    CStringX& FetchName();
    CStringX& FetchSource();
    CStringX& FetchTarget();
};

class CRegistryCache
{
protected:
    const ProfileInfo* m_pProfileInfo;
    DWORD field_0x0008;
    DWORD field_0x000C;
    DWORD m_dwFlags;

    CRegistryCache();
    ~CRegistryCache();

    virtual void ReadRegistryToCache(CWinRegistry*) = 0;
    virtual void WriteRegistryFromCache(CWinRegistry*) = 0;

public:
    LPINT FetchInt(LPCSTR, LPCSTR);
    CStringX* FetchString(LPCSTR, LPCSTR);

    static CRegistryCache* GetGlobal();
};

class CCommandRef : public CRio
{
public:
    DECLARE_DYNAMIC_RIO(CCommandRef)

    using LPGetNextCommand = CVmCommand* (__thiscall *)(CCommandRef*);

    CVmCommand* GetNextCommand();

    static LPGetNextCommand& FetchGetNextCommand(const CRuntimeClass*);

protected:
    static LPGetNextCommand FindGetNextCommand(const CRio_vtbl*);
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
    CHAR m_pVariableArea[];
};

class CVmGenericMsg : public CVmCommand
{
public:
    struct Param
    {
        CMemberInfo* m_pMemberInfo;
        COceanNode* m_pNode;
    };

    DECLARE_DYNAMIC_EX(CVmGenericMsg)

    CRioMsg* m_pMsg;
    CVmVar field_0010;
    const CMsgRTC* m_pRTC;
    INT m_nCount;
    Param m_pVariableArea[];
};

class CVmCall : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmCall)

    CRef m_refRsa;
    INT m_nCount;
    BYTE m_pVariableArea[];
};

class CVmVarObj : public CRio
{
public:
    DECLARE_DYNAMIC_EX(CVmGenericMsg)

    const CRuntimeClass* m_pBasicTypeRTC; // CBasicTypeRTC
    CVmVar m_Variable;
};

struct CMemberInfo
{
    LPCSTR m_lpszName;
    const CRuntimeClass* m_pRTC;
    int m_nOffset;
};

struct CMsgRTC
{
    LPCSTR m_lpszClassName;
    CMemberInfo* m_pParams;
    short m_nObjectSize;
    WORD m_wSchema;
    CMsgRTC* m_pNextClass;

    static const HashBucket<CMsgRTC>* GetRegister();
};

struct ProfileInfo
{
    int m_nOffset;
    DWORD m_dwSchema;
    LPCSTR m_lpszKey;
    LPCSTR m_lpszSubKey;
    int m_nType;
};

struct CObject_vtbl
{
    CRuntimeClass* (__thiscall *GetRuntimeClass)(CObject*);
    void (__thiscall *Destructor)(CObject*, DWORD);
    void (__thiscall *Serialize)(CObject*, CArchive*);
    void (__thiscall *AssertValid)(CObject*);
    void (__thiscall *Dump)(CObject*, CDumpContext*);

    // ReSharper disable CppNonExplicitConversionOperator
    operator FARPROC const*() const; // NOLINT(*-explicit-constructor)
    // ReSharper restore CppNonExplicitConversionOperator
};

struct CRio_vtbl : CObject_vtbl
{
    void (__thiscall *Serialize)(CRio*, CPmArchive*);
};

template <class T, int SIZE>
struct HashBucket
{
    const T* m_arr[SIZE];
};

#endif // RUGP_H
