#ifndef RUGP_H
#define RUGP_H

#include <stdafx.h>

struct MFC_MODULE;

class CObjectEx;
class CRio;

class CRioMsg;
struct CMemberInfo;
struct CRuntimeClassMsg;

class CPmArchive;
class COceanNode;

class CCommandRef;
class CVmCommand;
class CVmSync;
class CVmImage;
class CVmRet;
class CVmSound;
class CVmMsg;
class CVmCall;
class CVmGenericMsg;
class CVmLabel;
class CVmFlagOp;
class CVmBlt;
class CVmJump;

struct CObject_vtbl;
struct CObjectEx_vtbl;
struct CCommandRef_vtbl;

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
};

class CRioMsg
{
public:
    CRuntimeClassMsg* m_pRTC;
    DWORD field_0004;
    CPmArchive* m_pArchive;
    COceanNode* m_pNode;
    DWORD field_0010;
};

struct CMemberInfo
{
    LPCSTR m_lpszName;
    CRuntimeClass* m_pRTC;
    DWORD m_dwOffset;
};

struct CRuntimeClassMsg
{
    LPCSTR m_lpszClassName;
    CMemberInfo* m_pParamArray;
    SIZE_T m_nSizeOfMsg;
    DWORD m_dwFlags;
    CRuntimeClassMsg* m_pNext;
};

class CPmArchive
{
protected:
    ~CPmArchive() = default;

    typedef CPmArchive* (WINAPIV *LPCreatePmArchive)(CFile*, SIZE_T);
    typedef void (WINAPIV *LPDestroyPmArchive)(CPmArchive*, BOOL);

public:
    virtual LONG Seek(LONG, UINT) = 0;

    static CPmArchive* WINAPIV CreateLoadPmArchive(CFile*, SIZE_T = 0x00010000);
    static CPmArchive* WINAPIV CreateSavePmArchive(CFile*, SIZE_T = 0x00010000);
    static void WINAPIV DestroyPmArchive(CPmArchive*, BOOL);
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

    typedef CRio* (__thiscall *LPFetch)(const COceanNode*);
    typedef COceanNode* (WINAPIV *LPGetNode)();

public:
    CRio* Fetch() const;

    static const COceanNode* GetRoot();
    static const COceanNode* GetNull();
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
};

class CVmSync : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmSync)

    COceanNode* m_pNode; // CRio
    DWORD field_0010; // BYTE
    DWORD field_0014;
};

class CVmImage : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmImage)

    WORD field_000C;
    WORD field_000E;
    DWORD field_0010; // CVmVar*
    DWORD field_0014; // CVmVar*
    DWORD field_0018; // BYTE
};

class CVmRet : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmRet)
};

class CVmSound : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmSound)

    COceanNode* m_pPmSoundNode; // CPmSound
    DWORD field_0010;
    DWORD field_0014;
};

class CVmMsg : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmMsg)

    COceanNode* m_pMessBoxNode; // CMessBox
    COceanNode* m_pCRioNode; // COptimizedObs
    CHAR m_area[];
};

class CVmCall : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmCall)

    COceanNode* m_pRsaNode; // CRsa
    DWORD m_nCount;
    DWORD m_area[];
};

class CVmGenericMsg : public CVmCommand
{
public:
    struct Part
    {
        CMemberInfo* m_pMemberInfo;
        COceanNode* m_pNode;
    };

    DECLARE_DYNAMIC_EX(CVmGenericMsg)

    CRioMsg* m_pMSG;
    DWORD field_0010; // CVmVar
    DWORD field_0014;
    DWORD m_nCount;
    Part m_area[];
};

class CVmLabel : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmLabel)

    COceanNode* m_pCLabelNode; // CLabel
};

class CVmFlagOp : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmFlagOp)

    DWORD field_000C; // CVmVar
    DWORD field_0010; // CVmVar
    COceanNode* m_pCCommandRefNode; // CCommandRef
    WORD field_001C;
};

class CVmBlt : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmBlt)

    DWORD field_000C; // Position
    DWORD field_0010; // CVmVar
    DWORD field_0014; // CVmVar
};

class CVmJump : public CVmCommand
{
public:
    DECLARE_DYNAMIC_EX(CVmJump)

    COceanNode* m_pCCommandRefNode; // CCommandRef
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
