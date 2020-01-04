 // ELMouse.h : header file
//
#ifndef _MI_CUR_I_H 
#define _MI_CUR_I_H 

                    
#include "In_Crcle.h"
#include "Inter_C1.h"
#include "Inter_C2.h"
#include "Inter_C3.h"
 
#include "drcurve.h"
#include "drNode.h"
#include "DListMgr.h"
#include "glb_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Cur_I : public CObject
{
public:

	CMI_Cur_I();
	DECLARE_SERIAL(CMI_Cur_I)


// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual int 	Post_Curve(CDrObject* pObject);
    ///////////////////////////////////////////////////// Curve
	virtual CString	GetCurrentINodeID(){return m_CurrentINodeID;};
    virtual void    SetCurrentINodeID(CString CurrentNodeID)
    				{
    					m_CurrentINodeID = CurrentNodeID;
    				};
    /////////////////////////////////////////////
    virtual int 	LBDownInit_CPost(){return 0;}; 
    virtual int 	LBUpCurvePost(){return 0;};
    
    virtual int 	LBDownInit_CEdit(){return 0;}; 
    virtual int 	LBUpCurveEdit(){return 0;}; 
    virtual int 	LBDownInit_CMove(){return 0;}; 
    virtual int 	LBUpCurveMove(){return 0;}; 
	///////////////////////////////////////////// 
    virtual int 	LBDownInit_CInsert(UINT nType); 
    virtual int 	LBUpInit_CInsert(enum CURVETYPE kind); 
    virtual int 	RBDown_CInsert(enum CURVETYPE kind,CView* pView,UINT nView); 
    virtual int 	LBUp_CInsert(enum CURVETYPE kind,CView* pView,UINT nView); 
    virtual int 	RBUp_CInsert(enum CURVETYPE kind,CView* pView,UINT nView); 
    				
		
protected:


	/////////////////
	int 		SetUpINodes(CDListMgr* pList,pWORLD inData,int nData);
	/////////////////////////////////////////////////////////////////// Circle
	int 		Circle_PrepInterpolation(CIn_Circle* pIn_Circle);
	int 		InterPolate_Circle();
	int 		Circle_PostInterpolation(CIn_Circle* pIn_Circle);
	int 		Compute_Phi_Si_Theta(pWORLD Data, pDOUBLE phi, pDOUBLE si, 
									pDOUBLE theta);
	int 		NumberOfDataAndCons(double theta, BOOL bClosed,
									pINT nDatNew, pINT nConBZ, pINT nConBS);
	/////////////////////////////////////////////////////////////////// Linear
	int 		C1_SetMemory();
	int 		C1_PrepInterpolation(CInter_C1* pInter_C1);
	int 		InterPolate_C1();
	int 		C1_PostInterpolation(CInter_C1* pInter_C1);
	/////////////////////////////////////////////////////////////////// Qudaratic
	int 		C2_SetMemory();
	int 		C2_PrepInterpolation(CInter_C2* pInter_C2);
	int 		InterPolate_C2();
	int 		C2_PostInterpolation(CInter_C2* pInter_C2);
	/////////////////////////////////////////////////////////////////// Cubic
	int 		C3_SetMemory();
	int 		C3_PrepInterpolation(CInter_C3* pInter_C3);
	int 		InterPolate_C3();
	int 		C3_PostInterpolation(CInter_C3* pInter_C3);
	/////////////////////////////////////////////////////////////////// Post
	CDrNode* 	PostNode(CString& Nid,WORLD Pt,BOOL bCNode);
	//////////////////////////////////////////////////////// Curve/Patch
	int 		PostNodes_FWD();
	int 		InsertAllInfo(int nOrder);
	void 		SaveINode(CDListMgr* pList,CString* pID);
	CDrCurve* 	C_GetInfo(enum CURVETYPE kind,int nButton);
	/////////////////////////////////////////////////// Memory						
	pWORLD 		FixMem(long nOut)
				{
					pWORLD pOut;
					return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
				};
	
	void 		FreeMem(pWORLD pOut){delete[] pOut;};
		          

protected:  
// Attributes
protected:


 	/////////////////////////////////////////// INode     
	int		    m_nINodeDone;		// for Curve & Patch
	CString 	m_CurrentINodeID;
	/////////////////////////////////////////// Curve
	int			m_nMaxCurveCNodes;
	int			m_nMaxCurveINodes;
	//////////////////////////////
	CDrCurve* 	m_pDrCurve;
	int			m_nSegsOut;				// for Uniform Output
	////////////////////////
	CDListMgr*	m_pCNodeList;
	CDListMgr*	m_pINodeList;
	CURVETYPE	m_CurveType;
	BOOL		m_bClosed_S;
	int			m_nOrder_S;				// k
	int			m_nDegree_S;			// k -1
	int			m_nData_S;				// GIVEN: # of Data 
	int			m_nSeg_DT_S;			// L
	int			m_nSeg_BS_S;			// n
	int			m_nCon_BS_S; 			// n + 1: #of Spline Controls
	int			m_nMKnots_S;			// n + k + 1 = Total
	int			m_nKnots_S;				// n - k + 3 = distinct
	int			m_nCon_BZ_S;			// (k-1) * L + 1  = m_nMaxCurveCNodes 		
	int 		m_nDim_S;
	WEIGHT		m_WtType_S;
	KNOT		m_KnotType_S;
	BOUNDARY	m_BCL;
	BOUNDARY	m_BCR;
	VECTOR		m_TanL;
	VECTOR		m_TanR;
	//////////////////////////////////////////////////////////// Circle
	double		m_phi; 
	double		m_si; 
	double		m_theta;
	int			m_nDatNew_S;			// Adjusted# of Data for Conics(Circle) 
	//////////////////////////////////////////////////////////// Memory
	int			m_MemErr;
	pDOUBLE		m_pMKnot_S;
	pDOUBLE		m_pKnot_S;
	pDOUBLE		m_pWts_DT_S;
	pDOUBLE		m_pWts_BS_S;
	pDOUBLE		m_pWts_BZ_S;
	pWORLD 		m_pData;
	pWORLD 		m_pCon_BS_S;
	pWORLD 		m_pCon_BZ_S;
    /////////////////////////////////////////// Next
    pWORLD		m_pOut;	// = m_pCon_BZ_S: Bezier

//Operations
public:

	~CMI_Cur_I();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Cur_I)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

/////////////////////////////////////////////////////////////////////////////
#endif
