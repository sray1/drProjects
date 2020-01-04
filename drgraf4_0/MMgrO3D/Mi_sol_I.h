 // MI_Sol_I.h : header file
//
#ifndef _MI_SOL_I_H 
#define _MI_SOL_I_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_Pat_I.h"
#include "DrNode.h"
#include "DrFE2D.h"
#include "DrSolid.h"
#include "DListMgr.h"
#include "glb_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Sol_I : public CMI_Pat_I
{
public:

	CMI_Sol_I();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Sol_I)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
    //////////////////////////////////////////////
	virtual int 	LBDownInit_SInsert(UINT nType); 
	virtual int 	LBUpInit_SInsert(enum PATCHTYPE kind); 
	virtual int 	RBUp_SExtrudeInsert(CView* pView); 
	virtual int 	RBUp_SRotateInsert(CView* pView); 
	virtual int 	RBUp_SLoft2Insert(CView* pView); 
	virtual int 	RBUp_SSweepInsert(CView* pView); 
	virtual int 	RBUp_SDuctInsert(CView* pView); 
	virtual int 	RBUp_SCoonInsert(CView* pView); 
    				
		
protected:

	/////////////////////////
		          

protected:  
// Attributes

	CDrSolid* 	m_pDrSolid;
/*
	SOLIDTYPE	m_SolidType;           	// P_MESH,P_EXTRUDE etc
	//////////////////////////////////// ControlNodes Draw
	int			m_nSegs_STCon;
	int			m_nSegs_RCon;
	int			m_nOut_STCon;
	int			m_nOut_RCon;
	long		m_nOutCon;
	/////////////////////////////////////////// Mesh
	BOOL		m_bDirtySolid; //True: Indivual Elements NOT SAVED yet    
	CDrSolid* 	m_pDrSolid;
	CString 	m_CurrentSolidID;
	long		m_nMaxSolidCNodes;
	int			m_nMaxSolidCNodes_S;
	int			m_nMaxSolidCNodes_T;
	int			m_nMaxSolidCNodes_ST;
	int			m_nMaxSolidCNodes_R;
	////////////////////////////////
	BOOL		m_bClosed_R;
	int			m_nSegs_ST;
	int			m_nSegs_R;
	long		m_nOut_ST;
	int			m_nOut_R;
	int 		m_nCubicSolides_S;
	int 		m_nCubicSolides_T;
	int 		m_nCubicSolides_R;
	/////////////////////////////////////////// Extrude
	CString		m_FromID;
	CString		m_ToID;
	CString		m_CurveID;
	double		m_dLen;
	WORLD		m_vAxis;  
	/////////////////////////////////////////// Rotate
	double		m_dAng_1;
	double		m_dAng_2;
	WORLD 		m_FromPt; // used also for Sweep/Duct Anchor
	WORLD 		m_ToPt;   // used also for Sweep/Duct Anchor
	/////////////////////////////////////////// Loft
    CDListMgr 	m_CNListLoft;//Temporary for Manipulation
	/////////////////////////////////////////// Sweep/Duct
	CString		m_CurveID_S[4];
	//////////////////////////////// Memory Curve/Solid
	CDListMgr* 	m_pCNodeList;
	pWORLD		m_pIn_S[4];
	pWORLD		m_pOut;
	long		m_nOut;
    /////////////////////////////////////////// Posting
	SUBDIV		m_nSubDiv;
	ORIENT 		m_nOrient;
	CDListMgr*	m_pNodeList; 
	CDListMgr*	m_pElemList; 
	////////////////////////
*/
//Operations
public:

	~CMI_Sol_I();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Sol_I)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
