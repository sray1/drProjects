 // ELMouse.h : header file
//
#ifndef _MI_CPROF_H 
#define _MI_CPROF_H 

                    
#include "DrProf_C.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "MI_Cur_I.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_CProf : public CMI_Cur_I
{
public:

	CMI_CProf();
	DECLARE_DYNAMIC(CMI_CProf)


// Attributes 

// Operations
public:

// Implementation
public:
 
    virtual int 	RBUp_CProfile(CView* pView,UINT nView); 
    				
		
protected:

	CDrProf_C* 		PR_GetInfo();
	int 			InsertProfileInfo();
	///////////////////////////////////////////////////////////////////// DataInfo
	int 			Generate_CurveDataInfo();
	BOOL 			IsClosed();
	int 			FillProfileCurveINodes();
	int 			FillMeshNodes(CDrCurve* pDrCurve, pWORLD pOut, pDOUBLE pOutWts );
	int 			SaveMeshAsNewINodes(pWORLD pMNodes,	int nMNodes, int nCur, BOOL bLast);
	void 			SetInfoForDataBase(CDrCurve* pDrObject);
	///////////////////////////////////////////////////////////////////// ControlInfo
	//////////////////////////////////////////////////// Degree Elevate
	int 			Generate_CurveControlInfo();
	BOOL 			IsRational();
	int 			GetTopDegree();
	int 			GetNumberOfCNodes(int nDegree);
	int 			GetCNodeCoords(CDrCurve* pCurve, pWORLD pConOld);
	int 			Elevate_Profile(pWORLD pCon_BZ, pDOUBLE pWts_BZ, int nDegree);
	int 			Elevate_Curve
						(
							pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
							pWORLD pConNew, pDOUBLE pWtsNew,int nSeg_BZ
						);
	int 			Elevate_BezSeg(
							pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
							pWORLD pConNew, pDOUBLE pWtsNew
						);
	int 			DegreeElevate(pWORLD Con_BZ, pDOUBLE Wts_BZ, int nDegree, 
							 pWORLD NewCon_BZ, pDOUBLE NewWts_BZ);
	int 			PostNewCNodes(pWORLD pCon_BZ, int nCon);
	CDrNode* 		PostNode(CString& Nid,WORLD Pt,BOOL bCNode);
	//////////////////////////////////////////////////////////////////// Reparametrize
	
protected:
	
	CDrProf_C*	m_pDrProf;
	CString		m_CurveID;
    //////////////////////
	BOOL		m_bUnifOT;
	//////////////////////
	pDOUBLE		m_pOVal;
	pINT		m_pOSeg;
	////////////////////
    
//Operations
public:

	~CMI_CProf();
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_CProf)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

/////////////////////////////////////////////////////////////////////////////
#endif
