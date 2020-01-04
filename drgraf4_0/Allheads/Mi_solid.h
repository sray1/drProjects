 // mI_Solid.h : header file
//
#ifndef _MI_SOLID_H 
#define _MI_SOLID_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_Patch.h"
#include "DrNode.h"
#include "DrFE2D.h"
#include "DrSolid.h"
#include "DListMgr.h"
#include "glb_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Solid : public CMI_Patch
{
public:

	CMI_Solid();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Solid)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
//	virtual int	 	Post_Solid(CDrObject* pObject);
    //////////////////////////////////////////////
	virtual int 	LBDownInit_SPost(){return 0;}; 
	virtual int 	LBUpSolidPost();
	////////////////////////////////////////////// 
	virtual int 	LBDownInit_SEdit(){return 0;}; 
	virtual int 	LBUpSolidEdit(){return 0;};
	////////////////////////////////////////////// 
	virtual int 	LBDownInit_SMove(){return 0;}; 
	virtual int 	LBUpSolidMove(){return 0;};
	/////////////////////////////////////////////// 
	virtual int 	LBDownInit_SInsert(UINT nType); 
	virtual int 	LBUpInit_SInsert(enum PATCHTYPE kind); 
	virtual int 	LBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView,UINT nView); 
	virtual int 	RBUp_SMeshInsert(enum PATCHTYPE kind,CView* pView); 
	virtual int 	LBUp_SExtrudeInsert(CView* pView); 
	virtual int 	LBUp_SRotateInsert(CView* pView); 
	virtual int 	LBUp_SLoftInsert(CView* pView); 
	virtual int 	LBUp_SSweepInsert(CView* pView); 
	virtual int 	LBUp_SDuctInsert(CView* pView); 
    				
		
protected:

	int 		PostNodes_FWD();
	int 		PostMeshInfo_FWD();
	void 		CalcCentroid(pWORLD pC,UINT ix0,UINT ix1,UINT ix2,UINT ix3);
	int 		SubDivide_FWD(CString& PolyID,UINT ix0,UINT ix1,UINT ix2,UINT ix3);
	void 		ValidateSubDiv(void);
	CDrNode* 	PostNode(CString& Nid,WORLD Pt,BOOL bCNode);
	CDrFE2D* 	MakePoly_3(CString& PolyID,int ix0,int ix1,int ix2);
	CDrFE2D* 	MakePoly_4(CString& PolyID,int ix0,int ix1,int ix2,int ix3);
	CDrNode* 	PostPoly(CDrFE2D* pPoly,int* index,int nEnds);
	CDrSolid* 	Post_GetInfo();
	////////////////////////////////////////////////////////////
	void		BlockCopy(HUGEBLK p1, HUGEBLK p2, HUGESIZE size)
				{
					if( p1 && p2 )
					HUGECOPY(p1, p2, size);
				};
	void 		FillCNodesLOCAL(CDListMgr* pCurveCNodeList,
						pWORLD pIn,int nMaxCNodes,
						BOOL bSave,BOOL bLoft);
	int 		InsertMeshInfo(BOOL bLoft);
    /////////////////////////////////////////////
	int 		S_Mesh(); 
	int 		S_Extrude(); 
	int 		S_Rotate(); 
	int 		S_Loft(); 
	int 		S_Sweep(); 
	int 		S_Duct(); 
    ////////////////////////////////////////
	void		UnitAxisFromEndNodes(int nType);
	//////////////////////////////////////////////////// Mesh
	CDrSolid* 	S_Mesh_GetInfo(int nButton);
	int 		S_Mesh_GenerateCNodes(enum PATCHTYPE kind);
	//////////////////////////////////////////////////// Extrude
	CDrSolid* 	S_Extrude_GetInfo();
	int 		S_Extrude_GenerateCNodes();
	//////////////////////////////////////////////////// Rotate
	CDrSolid* 	S_Rotate_GetInfo();
	int			S_Rotate_GenerateCNodes();
	//////////////////////////////////////////////////// Loft
	CDrSolid* 	S_Loft_GetInfo();
	int			S_Loft_GenerateCNodes();
	//////////////////////////////////////////////////// Sweep
	CDrSolid* 	S_Sweep_GetInfo();
	int			S_Sweep_GenerateCNodes();
	//////////////////////////////////////////////////// Duct
	CDrSolid* 	S_Duct_GetInfo();
	int 		S_Duct_GenerateCNodes();
	/////////////////////////////////////////////////// Memory						
	pWORLD 	FixMem(long nOut)
				{
					pWORLD pOut;
					return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
				};
	
	void 	FreeMem(pWORLD pOut)
			{
				if(pOut) 
					delete[] pOut;
			};
	/////////////////////////
		          

protected:  
// Attributes

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
//Operations
public:

	~CMI_Solid();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Solid)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
