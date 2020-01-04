// CElemInfo.h : header file
//
#ifndef _ELEMINFO_H
#define _ELEMINFO_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
///////////////////// 
#define		MAX_INFOLIST		10	
/////////////////////////////////////////////////////////////////////////////
// CElemInfo
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CElemInfo : public CDrObject
{
// Construction
public:  
	CElemInfo();

	DECLARE_SERIAL(CElemInfo)


protected: 
public:
// Implementation
public:
	
	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	/////////////////////////////////////////////////////////////////////// hitnet
	virtual CDListMgr*			GetInfoList(int i){return &(m_InfoList[i]);};
	////////////////////////
	virtual	void 		ReadDefault();
	virtual	void 		Init();
	

protected: 

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	///////////////////////////////////////// ElemInfo
	//	0 = PropertyList
	//	1 = MaterialList
	//	2 = ReleaseList
	//	3 = SIIDList
	CDListMgr	m_InfoList[MAX_INFOLIST];
	///////////////////////////////////// Master Numbers


protected: 

public:
	virtual ~CElemInfo(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CElemInfo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
