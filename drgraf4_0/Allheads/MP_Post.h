 // ELMouse.h : header file
//
#ifndef _MP_POST_H 
#define _MP_POST_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h" 
#include "DrNode.h"
#include "DrFE2D.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMP_Post : public CMI_GangP
{
public:

	CMP_Post();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Post)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
    //////////////////////////////////////////////
	CDrPatch* 	GoDoIt();
    				
		
protected:

	CDrPatch* 	GetInfo();
	int 		PostNodes_FWD();
	int 		PostMeshInfo_FWD();
	void 		CalcCentroid(pWORLD pC,UINT ix0,UINT ix1,UINT ix2,UINT ix3);
	int 		SubDivide_FWD(CString& PolyID,UINT ix0,UINT ix1,UINT ix2,UINT ix3);
	void 		ValidateSubDiv(void);
//	CDrNode* 	PostNode(CString& Nid,WORLD Pt,BOOL bCNode);
	CDrFE2D* 	MakePoly_3(CString& PolyID,int ix0,int ix1,int ix2);
	CDrFE2D* 	MakePoly_4(CString& PolyID,int ix0,int ix1,int ix2,int ix3);
	CDrNode* 	PostPoly(CDrFE2D* pPoly,int index[],int nEnds);
		          

protected:  
// Attributes
/*
	double		m_Ratio;
	
	PATCHTYPE	m_PatchType;           	// P_MESH,P_EXTRUDE etc
	CURVEPROC	m_CurveType_S;         	// CU_BEZIER etc
	CURVEPROC	m_CurveType_T;         	// CU_BEZIER etc
	//////////////////////////////////// ControlNodes Draw
	int			m_nSegs_SCon;
	int			m_nSegs_TCon;
	int			m_nOut_SCon;
	int			m_nOut_TCon;
	long		m_nOutCon;
	/////////////////////////////////////////// Mesh
	BOOL		m_bDirtyPatch; //True: Indivual Elements NOT SAVED yet    
	CDrPatch* 	m_pDrPatch;
	CString 	m_CurrentPatchID;
	int			m_nMaxPatchCNodes;
	int			m_nMaxPatchCNodes_S;
	int			m_nMaxPatchCNodes_T;
	////////////////////////////////
	BOOL		m_bClosed_S;
	BOOL		m_bClosed_T;
	int			m_nSegs_S;
	int			m_nSegs_T;
	int			m_nOut_S;
	int			m_nOut_T;
	int 		m_nCubicPatches_S;
	int 		m_nCubicPatches_T;
	//////////////////////////////// Memory Curve/Patch
	CDListMgr* 	m_pCNodeList;
	pWORLD		m_pIn_S[4];
	pWORLD		m_pOut;
	long		m_nOut;
*/
    /////////////////////////////////////////// Posting
	SUBDIV		m_nSubDiv;
	ORIENT 		m_nOrient;
	CDListMgr*	m_pNodeList; 
	CDListMgr*	m_pElemList; 
	////////////////////////
//Operations
public:

	~CMP_Post();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Post)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
