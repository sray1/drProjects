 // CMI_D_R.h : header file
//
#ifndef _MI_D_R_H 
#define _MI_D_R_H 


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
class CMI_D_R : public CMI_GangS
{
public:

	CMI_D_R();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_D_R)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	CDrD_R*		CreateNodeBased(CString& LoadID, CDrNode* pNode,
					double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
					CString& aNid, UINT StaLBased);
	CDrD_R*		CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
					double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
					CString& aNid, UINT StaLBased);

    				
		
protected:

	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForBase(CDrD_R* pStaL);
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

	~CMI_D_R();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_D_R)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
