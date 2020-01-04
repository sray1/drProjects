// CObj3DMnu.h : header file
//
#ifndef _OBJ3DMNU_H_
#define _OBJ3DMNU_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
/////////////////////
#define MAX_OBJ3DMNU	1000
/////////////////////////////////////////////////////////////////////////////
// CObj3DMnu
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CObj3DMnu : public CDrObject
{
// Construction
public:  
	CObj3DMnu();

	DECLARE_SERIAL(CObj3DMnu)


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
	///////////////////////////////////////////////////// Obj3DMnu
	virtual UINT 	GetCurrentObj3DMnu(){return m_nCurrentObj3DMnu;};
	virtual void	SetCurrentObj3DMnu(UINT nCurrentObj3DMnu)
						{m_nCurrentObj3DMnu = nCurrentObj3DMnu;};	
	virtual UINT 	GetCurrentObj3DMnuOld(){return m_nCurrentObj3DMnuOld;};
	virtual void	SetCurrentObj3DMnuOld(UINT nCurrentObj3DMnu)
						{m_nCurrentObj3DMnuOld = nCurrentObj3DMnu;};	
	virtual UINT 	GetCurrentObj3DMnuDefault(){return m_nCurrentObj3DMnuDefault;};
	virtual void	SetCurrentObj3DMnuDefault(UINT nCurrentObj3DMnu)
						{m_nCurrentObj3DMnuDefault = nCurrentObj3DMnu;};
				//////////////////////////////////////////////		
    virtual CString GetObj3DMnuInfo(UINT i);
    virtual void	SetObj3DMnuInfo(UINT i,UINT nType);
    			//////////////////////////////// 
	virtual CString	GetObj3DMnuID(UINT i){return m_ID[i];};
	virtual void 	SetObj3DMnuID(CString nID,UINT i)
					{
						m_ID[i] = nID;
					}
	virtual CString	GetCurrentID(){return m_CurrentID;};
	virtual void 	SetCurrentID(CString nID){m_CurrentID = nID;};
	
	virtual void	GetObj3DMnuIDArray(CString nID[]);
	virtual void 	SetObj3DMnuIDArray(CString nID[]);
	
	virtual void 	GetObj3DMnuArray(UINT nObj3DMnu[][2]);
	virtual void 	SetObj3DMnuArray(UINT nObj3DMnu[][2]);
	virtual void 	GetObj3DMnuOldArray(UINT nObj3DMnu[][2]);
	virtual void 	SetObj3DMnuOldArray(UINT nObj3DMnu[][2]);
	virtual void 	GetObj3DMnuDefaultArray(UINT nObj3DMnu[][2]);
	virtual void 	SetObj3DMnuDefaultArray(UINT nObj3DMnu[][2]); 
	////////////////////////
	virtual	void 		ReadDefaultObj3DMnu();
	virtual	void 		InitObj3DMnu();

protected: 

	int		m_nElemType;	
	int		m_nObjectType;
	long	m_nObjectNo;
    /////////////////////////////////////////// Obj3DMnu
    CString	m_ID[MAX_OBJ3DMNU];
    UINT	m_nObj3DMnu[MAX_OBJ3DMNU][2];       // Working
    UINT	m_nObj3DMnuOld[MAX_OBJ3DMNU][2];    // Old For Edit 
    UINT	m_nObj3DMnuDefault[MAX_OBJ3DMNU][2];    // Default Setting from/to INI
    CString m_CurrentID;
	UINT	m_nCurrentObj3DMnu;
    UINT	m_nCurrentObj3DMnuOld;
    UINT	m_nCurrentObj3DMnuDefault;
    CString	m_IDDefault;

protected: 

public:
	virtual ~CObj3DMnu(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CObj3DMnu)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
