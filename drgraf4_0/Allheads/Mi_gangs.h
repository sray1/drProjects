 // ELMouse.h : header file
//
#ifndef _MI_GANGS_H 
#define _MI_GANGS_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_GangS : public CMI_GangP
{
public:

	CMI_GangS();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_GangS)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 

/*
//	Moved to CreOMgr Dll   01/14/98 
	CDrSolid*	PostSolid(CString& Cid,CString& OldID,SOLIDPROC PProc);
//	Moved to CreOMgr Dll   01/14/98 end
*/
	void		GetInfo_Patch(CDrPatch* pDrPatch);
    void		GetInfo_Patch_3(CDrPatch* pDrPatch);
	////////////////////////////////////////
//	void		UnitAxisFromEndNodes(int nType);
	//////////////////////////////////////////////////////////////////////////////
//	int 		PatchNodesSaveAsCNodes(CDListMgr* pListTemp,int tIndex);
	void 		FillCNodesLOCAL_Solid(CDListMgr* pCurveCNodeList,pDOUBLE pWts_S,
						pWORLD pIn,pDOUBLE pInWts,int nMaxCNodes,
						BOOL bSave,BOOL bLoft);
//	int			FillMeshNodesPatch(CDrPatch* pDrPatch, pWORLD pOut, pDOUBLE pOutWts );
	int 		InsertMeshInfo_Solid(BOOL bLoft);
	int 		InsertMeshInfo_Solid_3();
	int			InsertPentaHedrons(CDrSolid* pSolid);
	int			InsertPentaHedrons();



protected:  
// Attributes

	CString		m_SolidID;
	BOOL		m_bGenBCur;
	BOOL		m_bGenBPat;
	SOLSUBTYPE	m_SolSubType;
	CDListMgr* 	m_pPenList;		// PentaHedron list in Solid
	CDListMgr* 	m_pTriList;		// from Triangular Patch
	/////////////////////////
	SOLIDPROC	m_SolidProc;
	////////////////////////
	pDOUBLE		m_pWts_BZ_ST;
	/////////////////////////
	SOLIDTYPE	m_SolidType;           	// S_MESH,S_EXTRUDE etc
	CURVEPROC	m_CurveType_R;         	// CU_BEZIER etc
	//////////////////////////////////// ControlNodes Draw
	int			m_nOrder_R;
	int			m_nDim_R;
	int			m_nSegs_RCon;
	int			m_nOut_STCon;
	int			m_nOut_RCon;
	/////////////////////////////////////////// Mesh
	BOOL		m_bDirtySolid; //True: Indivual Elements NOT SAVED yet    
	CDrSolid* 	m_pDrSolid;
	CString 	m_CurrentSolidID;
	int			m_nMaxSolidCNodes_S;
	int			m_nMaxSolidCNodes_T;
	int			m_nMaxSolidCNodes_ST;
	int			m_nMaxSolidCNodes_R;
	int			m_nMaxSolidCNodes;
	////////////////////////////////
	BOOL		m_bClosed_R;
	int			m_nSegs_R;
	int			m_nOut_ST;
	int			m_nOut_R;
	int 		m_nPatches_R;	// formerly: m_nCubicPatches_R;
	//////////////////////////////// Memory Curve/Patch
	int			m_nBezSeg_R;
	pINT		m_pNum_t_ST;
	pINT		m_pNum_t_R;
	pDOUBLE		m_pDis_t_R;
	pINT		m_pNum_t_Ex_ST;
	pINT		m_pNum_t_Ex_R;	// for rotation:Circle
	/////////////////////////////////////////// Extrude
	double		m_Ratio_R;
	BOOL		m_bUnifOT_R;
	int			m_nMaxOSeg_R;
	/////////////////////////////////////////// Rotate
	pDOUBLE		m_pDisAng_R;//	Angle Distribution for 
							//	each Bez Patch in degrees
	BOOL		m_bAxis_R;
	int			m_nAxis_R;
	BOOL		m_bNegative_R;
	CIRCLETYPE	m_CircleType_R;
	double		m_dAng_1_R;
	double		m_dAng_2_R;
	////////////////////////

	
//Operations
public:

	~CMI_GangS();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_GangS)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
