 // ELMouse.h : header file
//
#ifndef _SLDE_NOD_H 
#define _SLDE_NOD_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SLDeObj.h" 
/////////////////////
#include "DrNode.h" 	
#include "DrLabel.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSLDeNod : public CSLDeObj
{
public:

	CSLDeNod();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDeNod)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual	void		GetObjectInfo(CSLEObj* pObject);
	virtual	void		SetObjectInfo(CSLEObj* pObject);
	/////////////////////////////////////////////////////////////////////////////// NodeStatic
			int			ShowInfo_NodeStaticLoad(CDrNode* pDrNode, char* buf, int jStart,
																		CDrStatic* pDrStatic);
			int 		ShowNodeStaticLoad(CString* pID,int nHowMany);

protected:




protected:  
// Attributes

	/////////////////////////////////////////// Node
	CDrNode*	m_pCurrentNode;
	CDrLabel*	m_pCurrentLabel;

//Operations
public:

	~CSLDeNod();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDeNod)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
