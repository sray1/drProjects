 // CMI_StaL.h : header file
//
#ifndef _MI_STAL_H 
#define _MI_STAL_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "Str_StaL.h"
#include "Ext_StaL.h"
#include "drcurve.h"
#include "drNode.h"
#include "DrStatic.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "MI_GangS.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_StaL : public CMI_GangS
{
public:

	CMI_StaL();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_StaL)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	int			CreateNodeBased(CDrNode* pNode,CList<STALCARD,STALCARD>* pCardList);
	int			CreateCurveBased(CDrCurve* pCurve,CList<STALCARD,STALCARD>* pCardList);
	int			CreatePatchBased_4(CDrPatch* pPatch,CList<STALCARD,STALCARD>* pCardList);
	int			CreatePatchBased_3(CDrPatch* pPatch,CList<STALCARD,STALCARD>* pCardList);
	//////////////////////
	int			RegenNodeBased(CDrNode* pNode);
	int			RegenCurveBased(CDrCurve* pCurve);
	int			RegenPatchBased_4(CDrPatch* pPatch);
	int			RegenPatchBased_3(CDrPatch* pPatch);
	////////////////////////////////////////////////
// 	int			CreateListNodeBased(CDrNode* pObject);
//	int			CreateListCurveBased(CDrCurve* pObject);
//	int			CreateListPatchBased(CDrPatch* pObject);

    				
		
protected:

	int			RegenNodeBased_DoIt(CDrNode* pNode,STALCARD& StLCard,CDListMgr* pList);
	///
	int			SetMaxVal_Cur(CDrCurve* pCurve,STALCARD& StLCard);
	int			RegenCurveBased_DoIt(CDrCurve* pCurve,pWORLD pOut,pWORLD pOutCurveTan,int nOut);
	///
	int			RegenPatchBased_4_DoIt(CDrPatch* pPatch,STALCARD& StLCard,CDListMgr* pList);
	///
	int			RegenPatchBased_3_DoIt(CDrPatch* pPatch,STALCARD& StLCard,CDListMgr* pList);
	///////////////////////////////////////////////////////////////////////////////////
	int			RegenTRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
								pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
								int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR);
	int			RegenTRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
								pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
								int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR);
	void		RegenInfoForStaticBase(CDrStatic* pStatic,STALCARD StLCard);
	/////////////////////////////////////////////////////////////////////////
	BOOL		IsDuplicated(WORLD& CurrentNodPos, STALPROC CurrentStaLProc);
	int			RemoveOldStatic(STALCARD StLCard, CDListMgr* pList);
	////////////////////////////////////////////////// Triangular Patch
	CDrStatic*  TRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,
						pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
						STALCARD& StLCard,int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR);
	CDrStatic*  TRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,
						pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
						STALCARD& StLCard,int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR);
	int			FillUp_Val_Pat_3(CDrPatch* pPatch,STALCARD& StLCard,BOOL* bT, BOOL* bR);
	////////////////////////////////////////////////// Quadrangular Patch
	BOOL		IsPatchTangentNeeded(CList<STALCARD,STALCARD>* pStaLCardList);
	int			LoopOver_Patch_4_Pts(CDrPatch* pPatch,STALCARD& StLCard,
							pWORLD pOut,pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
							pWORLD pOutPatchNor,int nOut);
	CDrPatch*	GetNonUniformLoadPatch(CString& id);
	int			FillUp_ValList_Pat_4(CDrPatch* pPatch,STALCARD& StLCard);
	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForStaticBase(CDrStatic* pStatic,STALCARD StLCard);
	////////////////////////////////////////////////// Curve Helper
	BOOL		IsTangentNeeded(CList<STALCARD,STALCARD>* pStaLCardList);
	BOOL		IsNormalNeeded(CList<STALCARD,STALCARD>* pStaLCardList);
	int			LoopOver_CurvePts(CDrCurve* pCurve,STALCARD& StLCard,
								pWORLD pOut,pWORLD pOutCurveTan,int nOut);
	CDrCurve*	GetNonUniformLoadCurve(CString& id);
	int			FillUp_ValList_Cur(CDrCurve* pCurve,STALCARD& StLCard);
	/////////////////////////////////////////////////// Memory						
	void		SetStaticID(CDrStatic* pStatic,char* buf,int jStart);
	int			UpdateFixedDirSkewMatrix(STALCARD& StLCard);

	

protected:  
// Attributes


	/////////////////////////// Triangle
	pWORLD		m_pOutTr;
	pWORLD		m_pOutRo;
	///////////////////////////
	MATRIX		m_SkewDirMat;
	CList<double,double>	m_ValueList;
	BOOL		m_bReciproDone;
	///////////////////////////
	CDrNode*	m_pNode;
	CDrCurve*	m_pCurve;
	CDrPatch*	m_pPatch;
	CDrSolid*	m_pSolid;
	///////////////////////
	UINT		m_StaLBased; // NodeBased,CurveBased etc.
	STALPROC	m_StaLProc;
	STALCARD	m_StaLCard;
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
	double		m_dMax[6];
	BOOL		m_bNonUniform;


//Operations
public:

	~CMI_StaL();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_StaL)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
