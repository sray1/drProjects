 // CMI_LSupp.h : header file
//
#ifndef _MI_LSUPP_H 
#define _MI_LSUPP_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "Str_Supp.h"
//#include "Ext_Supp.h"
#include "drcurve.h"
#include "drNode.h"
#include "DrLinSup.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "MI_GangS.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_LSupp : public CMI_GangS
{
public:

	CMI_LSupp();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_LSupp)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

 	int			CreateNodeBased(CDrNode* pNode,CList<SUPPCARD,SUPPCARD>* pCardList);
	int			CreateCurveBased(CDrCurve* pCurve,CList<SUPPCARD,SUPPCARD>* pCardList);
 	int			CreatePatchBased_4(CDrPatch* pPatch,CList<SUPPCARD,SUPPCARD>* pCardList);
 	int			CreatePatchBased_3(CDrPatch* pPatch,CList<SUPPCARD,SUPPCARD>* pCardList);
	//////////////////////
	int			RegenNodeBased(CDrNode* pNode);
	int			RegenCurveBased(CDrCurve* pCurve);
	int			RegenPatchBased_4(CDrPatch* pPatch);
	int			RegenPatchBased_3(CDrPatch* pPatch);
	///////////////////////////////////////////////////////
//	int			CreateListNodeBased(CDrNode* pObject);
// 	int			CreateListCurveBased(CDrCurve* pObject);
// 	int			CreateListPatchBased(CDrPatch* pObject);

    				
		
protected:

	int			RegenNodeBased_DoIt(CDrNode* pNode,SUPPCARD& SupCard,CDListMgr* pList);
	int			RegenCurveBased_DoIt(CDrCurve* pCurve,pWORLD pOut,pWORLD pOutCurveTan,int nOut);
	int			RegenPatchBased_4_DoIt(CDrPatch* pPatch,SUPPCARD& SupCard,CDListMgr* pList);
	int			RegenPatchBased_3_DoIt(CDrPatch* pPatch,SUPPCARD& SupCard,CDListMgr* pList);
	///////////////////////////////////////////////////////////////////////////////////
	int			RegenTRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
													int iOutGlo_ST,int jOutGlo_ST);
	int			RegenTRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
													int iOutGlo_ST,int jOutGlo_ST);
	void		RegenInfoForLinSupBase(CDrLinSup* pSupp,SUPPCARD supCard);
	/////////////////////////////////////////////////////////////////////////
	BOOL		IsDuplicated(WORLD& CurrentNodPos, SUPPPROC CurrentSuppProc);
	int			RemoveOldLinSup(SUPPPROC SuppProc, CDListMgr* pList);
	////////////////////////////////////////////////// Triangular Patch
	CDrLinSup*  TRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,
							pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
							SUPPCARD& supCard,int iOutGlo_ST,int jOutGlo_ST);
	CDrLinSup*  TRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,
							pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
							SUPPCARD& supCard,int iOutGlo_ST,int jOutGlo_ST);
	////////////////////////////////////////////////// Posting Helper
	void		SetSupportID(CDrLinSup* pSupp,char* buf,int jStart);
	void		SetInfoForLinSupBase(CDrLinSup* pSupp,SUPPCARD supCard);
	////////////////////////////////////////////////////////////////////////
	BOOL		IsTangentNeeded(CList<SUPPCARD,SUPPCARD>* pStaLCardList);
	BOOL		IsNormalNeeded(CList<SUPPCARD,SUPPCARD>* pStaLCardList);
	int			LoopOver_CurvePts(CDrCurve* pCurve,SUPPCARD& StLCard,
							pWORLD pOut,pWORLD pOutCurveTan,int nOut);
	int			UpdateFixedDirSkewMatrix(SUPPCARD& SupCard);
	BOOL		IsPatchTangentNeeded(CList<SUPPCARD,SUPPCARD>* pSuppCardList);
	int			LoopOver_Patch_4_Pts(CDrPatch* pPatch,SUPPCARD& SupCard,
					pWORLD pOut,pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
					pWORLD pOutPatchNor,int nOut);
		          

protected:  
// Attributes

	
	MATRIX		m_SkewDirMat;
	BOOL		m_bReciproDone;
	///////////////////////////
	CDrNode*	m_pNode;
	CDrCurve*	m_pCurve;
	CDrPatch*	m_pPatch;
	CDrSolid*	m_pSolid;
	///////////////////////
	UINT		m_SuppBased; // NodeBased,CurveBased etc.
	SUPPPROC	m_SuppProc;
	SUPPCARD	m_SuppCard;
	///////////////////////
	WORLD		m_NodePos;
	BOOL		m_bCurveTan;
	WORLD		m_CurveTan;
	BOOL		m_bPatchTan;
	WORLD		m_PatchTan_S;
	WORLD		m_PatchTan_T;
	BOOL		m_bPatchNor;
	WORLD		m_PatchNor;
	/////////////////////// 

//Operations
public:

	~CMI_LSupp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_LSupp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
