#ifndef RUGP_H
#define RUGP_H

#include <stdafx.h>

class RUGP_MODULE;

class CObjectEx;
struct CRuntimeClassEx;
struct CMemberInfo;

class CPmArchive;

class RUGP_MODULE final
{
public:
    explicit RUGP_MODULE(HINSTANCE hInstance);
    ~RUGP_MODULE();

    const AFX_EXTENSION_MODULE* GetNative() const;
    LPCSTR GetVersion() const;
    LPCSTR GetMfcVersion() const;

    CPmArchive* WINAPIV CreateLoadPmArchive(CFile*, SIZE_T = 0x00010000) const;
    CPmArchive* WINAPIV CreateSavePmArchive(CFile*, SIZE_T = 0x00010000) const;
    void WINAPIV DestroyPmArchive(CPmArchive*, BOOL = FALSE) const;

protected:
    typedef BOOL (AFXAPI *LPAfxInitExtensionModule)(AFX_EXTENSION_MODULE&, HMODULE hMod);
    typedef void (AFXAPI *LPAfxTermExtensionModule)(AFX_EXTENSION_MODULE&, BOOL bAll);
    typedef CPmArchive* (WINAPIV *LPCreatePmArchive)(CFile*, SIZE_T);
    typedef void (WINAPIV *LPDestroyPmArchive)(CPmArchive*, BOOL);

    int fetch();

    HMODULE mfc = nullptr;
    int mfc_version = 0x0000;
    AFX_EXTENSION_MODULE native = {};
};

#define DECLARE_DYNAMIC_EX(class_name) \
public: \
    virtual CRuntimeClass* GetRuntimeClass() const;

class CObjectEx : public CObject
{
public:
    DECLARE_DYNAMIC_EX(CObjectEx)

    virtual void Serialize(CPmArchive&) = 0;
};

struct CRuntimeClassEx : CRuntimeClass
{
    struct Module
    {
        LPCSTR name;
        LPCSTR file;
        LPCSTR version;
    };

    CMemberInfo* m_pMemberInfo;
    void* field_001C; // TODO CRioMsgEntry
    DWORD field_0020;
    const Module* m_pModule;
    CObjectEx* (WINAPIV *m_pfnPlacementCreate)(CObjectEx*);

    explicit CRuntimeClassEx(const CRuntimeClass& clazz) : CRuntimeClass(clazz)
    {
        m_pMemberInfo = nullptr;
        field_001C = nullptr;
        field_0020 = 0;
        m_pModule = nullptr;
        m_pfnPlacementCreate = nullptr;
    }
};

struct CMemberInfo
{
    LPCSTR m_lpszName;
    CRuntimeClass* m_pRTC;
    DWORD m_dwOffset;
};

class CPmArchive
{
protected:
    CPmArchive(CFile*, UINT, INT, LPVOID);
    ~CPmArchive() = default;

public:
     virtual LONG Seek(LONG, UINT) = 0;
};

#endif // RUGP_H
