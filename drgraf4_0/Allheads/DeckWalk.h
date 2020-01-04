// CDeckWalk.h : header file
//
#ifndef _DECKWALK_H_
#define _DECKWALK_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>	// for CList
#include "DrObject.h"
/////////////////////////////////////////////////////////////////////////////
// CDeckWalk
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDeckWalk : public CObject
{
// Construction
public:  
	CDeckWalk(CList<CString,CString>* pDeckList,BOOL bFormatted);
	DECLARE_DYNAMIC(CDeckWalk)
protected: 
public:
// Implementation
public:

	virtual int 	Init(BOOL bNS[]);
	virtual int		DW_MESH();

protected:
					
	int				DW_Mesh3D(CDrObject* pObject);
	int				DW_Mesh2D(CDrObject* pObject);
	int				DW_Mesh1D(CDrObject* pObject);
	int				DW_Mesh0D(CDrObject* pObject);
	int				DW_Mesh3DObjects(CDListMgr* pList,CDrObject* pObject);
	int				DW_Mesh2DObjects(CDListMgr* pList,CDrObject* pObject);
	int				DW_Mesh1DObjects(CDListMgr* pList,CDrObject* pObject);
	int				DW_Mesh0DObjects(CDListMgr* pList,CDrObject* pObject);
	int				DW_ObjectType(CDListMgr* pList,UINT CurrentObjType,UINT CurrentFmt);
	///
	int				DW_MeshVrtxToVrtx(CDListMgr* pListV,CDListMgr* pListE);
	int				DW_MeshNodeToElement(CDListMgr* pListV);
	int				DW_MeshNodeToElementID(CDListMgr* pListV,CDListMgr* pListE,
													CString& strCard,int indexV);
						

protected:


	CList<CString,CString>*	m_pDeckList;
	BOOL					m_bFormatted;
	UINT					m_nCardNo;
	////////////////////////////// NoShow Controls			
	////////////////////////////// StaticLoad
	BOOL		m_bNS_Force;	
	BOOL		m_bNS_Displace;
	BOOL		m_bNS_Pressure;
	BOOL		m_bNS_Thermal;
	BOOL		m_bNS_LumpWt;
	////////////////////////////// Supports
	BOOL		m_bNS_RIGID; 
	BOOL		m_bNS_Lin_Spring; 
	BOOL		m_bNS_Lin_Snubber; 
	BOOL		m_bNS_Non_Spring; 
	BOOL		m_bNS_Non_Snubber; 
	/////////////////////////// Posted	
	BOOL		m_bNS_P_Object;			
	BOOL		m_bNS_P_Solid;	
	BOOL		m_bNS_P_Patch;	
	BOOL		m_bNS_P_Curve;
	/////////////////////////// Misc	
	BOOL		m_bNS_MNode;	
	///////////////////////////////


public:
	virtual ~CDeckWalk(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDeckWalk)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
