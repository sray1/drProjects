// CPatchMnu.h : header file
//
#ifndef _PATCHMNU_H_
#define _PATCHMNU_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#define MAX_PATCHMNU	1000
/////////////////////////////////////////////////////////////////////////////
// CPatchMnu
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPatchMnu : public CDrObject
{
// Construction
public:  
	CPatchMnu();

	DECLARE_SERIAL(CPatchMnu)


protected: 
public:
// Implementation
public:
	
	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void 	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	///////////////////////////////////////////////////// PatchMnu
	virtual UINT 	GetCurrentPatchMnu(){return m_nCurrentPatchMnu;};
	virtual void	SetCurrentPatchMnu(UINT nCurrentPatchMnu)
						{m_nCurrentPatchMnu = nCurrentPatchMnu;};	
	virtual UINT 	GetCurrentPatchMnuOld(){return m_nCurrentPatchMnuOld;};
	virtual void	SetCurrentPatchMnuOld(UINT nCurrentPatchMnu)
						{m_nCurrentPatchMnuOld = nCurrentPatchMnu;};	
	virtual UINT 	GetCurrentPatchMnuDefault(){return m_nCurrentPatchMnuDefault;};
	virtual void	SetCurrentPatchMnuDefault(UINT nCurrentPatchMnu)
						{m_nCurrentPatchMnuDefault = nCurrentPatchMnu;};
				//////////////////////////////////////////////		
    virtual CString GetPatchMnuInfo(UINT i);
    virtual void	SetPatchMnuInfo(UINT i,UINT nType);
    			//////////////////////////////// 
	virtual CString	GetPatchMnuID(UINT i){return m_ID[i];};
	virtual void 	SetPatchMnuID(CString nID,UINT i)
					{
						m_ID[i] = nID;
					}
	virtual CString	GetCurrentID(){return m_CurrentID;};
	virtual void 	SetCurrentID(CString nID){m_CurrentID = nID;};
	
	virtual void	GetPatchMnuIDArray(CString nID[]);
	virtual void 	SetPatchMnuIDArray(CString nID[]);
	
	virtual void 	GetPatchMnuArray(UINT nPatchMnu[][2]);
	virtual void 	SetPatchMnuArray(UINT nPatchMnu[][2]);
	virtual void 	GetPatchMnuOldArray(UINT nPatchMnu[][2]);
	virtual void 	SetPatchMnuOldArray(UINT nPatchMnu[][2]);
	virtual void 	GetPatchMnuDefaultArray(UINT nPatchMnu[][2]);
	virtual void 	SetPatchMnuDefaultArray(UINT nPatchMnu[][2]); 
	////////////////////////
	virtual	void 		ReadDefaultPatchMnu();
	virtual	void 		InitPatchMnu();

protected: 

	int		m_nElemType;	
	int		m_nObjectType;
	long	m_nObjectNo;
    /////////////////////////////////////////// PatchMnu
    CString	m_ID[MAX_PATCHMNU];
    UINT	m_nPatchMnu[MAX_PATCHMNU][2];       // Working
    UINT	m_nPatchMnuOld[MAX_PATCHMNU][2];    // Old For Edit 
    UINT	m_nPatchMnuDefault[MAX_PATCHMNU][2];    // Default Setting from/to INI
    CString m_CurrentID;
	UINT	m_nCurrentPatchMnu;
    UINT	m_nCurrentPatchMnuOld;
    UINT	m_nCurrentPatchMnuDefault;
    CString	m_IDDefault;

protected: 

public:
	virtual ~CPatchMnu(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CPatchMnu)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
