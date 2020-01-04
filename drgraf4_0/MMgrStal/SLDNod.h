 // ELMouse.h : header file
//
#ifndef _SLD_NOD_H 
#define _SLD_NOD_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SLDObj.h" 
/////////////////////
#include "DrNode.h" 	
#include "DrLabel.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CSLDNod : public CSLDObj
{
public:

	CSLDNod();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDNod)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual	void		GetObjectInfo(CSLDObj* pObject);
	virtual	void		SetObjectInfo(CSLDObj* pObject);
	/////////////////////////////////////////////////////////////////////////////// NodeStatic
			int			ShowInfo_NodeStaticLoad(CDrNode* pDrNode, char* buf, int jStart
																		,CString& CurrentStLID);
			int			ShowNodeStaticLoad(CDrNode* pN,CString* pID);
			/////////////////////////////////////////// Node
			void		SetCurrentNode(CDrNode* pN){m_pCurrentNode = pN;};
			void		SetCurrentLabel(CDrLabel* pN){m_pCurrentLabel = pN;};

protected:




protected:  
// Attributes

	/////////////////////////////////////////// Node
	CDrNode*	m_pCurrentNode;
	CDrLabel*	m_pCurrentLabel;

//Operations
public:

	~CSLDNod();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDNod)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
