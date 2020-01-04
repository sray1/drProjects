 // CMI_F_M.h : header file
//
#ifndef _MI_F_M_H 
#define _MI_F_M_H 


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
class CMI_F_M : public CMI_GangS
{
public:

	CMI_F_M();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_F_M)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	CDrF_M*		CreateNodeBased(CString& LoadID, CDrNode* pNode,
					double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
					CString& aNid, UINT StaLBased);
	CDrF_M*		CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
					double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
					CString& aNid, BOOL bTangent, UINT StaLBased);

    				
		
protected:

	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForBase(CDrF_M* pStaL);
	/////////////////////////
		          

protected:  
// Attributes

	

	BOOL		m_bReciproDone;
	///////////////////////////
	CDrNode*	m_pNode;
	CDrCurve*	m_pCurve;
	CDrPatch*	m_pPatch;
	CDrSolid*	m_pSolid;
	///////////////////////
	UINT		m_StaLBased; // NodeBased,CurveBased etc.
	///////////////////////
	WORLD		m_NodePos;
	BOOL		m_bCurveTan;
	WORLD		m_CurveTan;
	//////////////////////////////////// Posting LinSup
	CString		m_LoadID;
	CString		m_aNid;
	WORLD		m_F[2];


//Operations
public:

	~CMI_F_M();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_F_M)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
