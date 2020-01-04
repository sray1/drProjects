 // CMI_Prs.h : header file
//
#ifndef _MI_PRS_H 
#define _MI_PRS_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "drcurve.h"
#include "drNode.h"
#include "DrF_M.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "MI_GangS.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Prs : public CMI_GangS
{
public:

	CMI_Prs();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Prs)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	CDrPrs*		CreateNodeBased(CString& LoadID, CDrNode* pNode,
					double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased);
	CDrPrs*		CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
					double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased);

    				
		
protected:

	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForBase(CDrPrs* pStaL);
	/////////////////////////
		          

protected:  
// Attributes

	

	CDrNode*	m_pNode;
	CDrCurve*	m_pCurve;
	CDrPatch*	m_pPatch;
	CDrSolid*	m_pSolid;
	///////////////////////
	UINT		m_StaLBased; // NodeBased,CurveBased etc.
	///////////////////////
	WORLD		m_NodePos;
	//////////////////////////////////// Posting LinSup
	CString		m_LoadID;
	CString		m_aNid;
	WORLD		m_F[2];


//Operations
public:

	~CMI_Prs();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Prs)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
