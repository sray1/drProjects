 // CMI_LWt.h : header file
//
#ifndef _MI_LWT_H 
#define _MI_LWT_H 


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
class CMI_LWt : public CMI_GangS
{
public:

	CMI_LWt();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_LWt)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	CDrLWt*		CreateNodeBased(CString& LoadID, CDrNode* pNode,
					double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased);
	CDrLWt*		CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
					double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased);

    				
		
protected:

	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForBase(CDrLWt* pStaL);
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
	BOOL		m_GravMul;


//Operations
public:

	~CMI_LWt();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_LWt)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
