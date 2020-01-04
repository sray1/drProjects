// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h> 

#include "3DMath.h"
#include "XForm.h"

#include "Def_Objs.h"
#include "Def_View.h"
#include "Def_Type.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
///////////////////// dialogMgr
//#include "EDl2Mgr.h"  
///////////////////// cards
#include "Def_Card.h"
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
///////////////////// Support
#include "Def_Supp.h"
#include "DrLinSup.h"
///////////////////// specials
#include "Def_Spec.h"
#include "HitNet.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
/////////////////////
#include "MI_LSupp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_LSupp,CMI_GangS,1)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////
#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
/////////////////////////////////////////////////////////////////////////////
CMI_LSupp::CMI_LSupp()
{
	m_bCurveTan		= FALSE;
	m_bPatchNor		= FALSE;
	////////////////////////
	m_bPatchTan		= FALSE;
}

CMI_LSupp::~CMI_LSupp()
{
}	

//////////////////////////////////////////////////////////////////////////// Poting Helper
int CMI_LSupp::CreatePatchBased_3(CDrPatch* pPatch,CList<SUPPCARD,SUPPCARD>* pCardList)
{
	UINT SuppBased	= PATCH;
	CList<SUPPCARD,SUPPCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	long nOut			= pPatch->GetLongOutPts();
	BOOL bLinSpr		= pPatch->IsLinSpr();
	BOOL bLinSnu		= pPatch->IsLinSnu();
	CDListMgr*	pList	= pPatch->GetSuppList();
	////////////////////////////////
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	m_PatSubType = pPatch->GetPatSubType(); 
	FillMeshNodesPatch(pPatch,pOut,pOutWts);
	///////////////////////////////////////////////////////////////////
//	CString strCurORPat = SupCard.ID_CP;
	//////////////////////////////////////////// Generate Tangents, if Needed
	m_bCurveTan	= IsTangentNeeded(pCardList);				
	//////////////////////////////////////////// Generate Patch Tangents, if Needed
	m_bPatchTan	= IsPatchTangentNeeded(pCardList);
	///////////			
	pWORLD	pOutPatchTan_S = NULL;
	pWORLD	pOutPatchTan_T = NULL;
	///////////////
	if(m_bPatchTan)
	{
		pOutPatchTan_S	= FixMem(nOut);
		pOutPatchTan_T	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsPatch(pPatch,pOutPatchTan_S,pOutPatchTan_T);
		/////////////////////
	}
	//////////////////////////////////////////// Generate Patch Normals, if Needed
	m_bPatchNor	= IsPatchTangentNeeded(pCardList);
	pWORLD	pOutPatchNor = NULL;
	/////////////////////
	if(m_bPatchNor)
	{
		pOutPatchNor	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshNormalsPatch(pPatch,pOutPatchNor);
		/////////////////////
	}
	///////////////////////////////////////////////////////////////////// LOOP:StaLCardList
	for (POSITION posI = pCardList->GetHeadPosition( );posI !=NULL;)
	{
		SUPPCARD SupCard = pCardList->GetNext(posI);
		////////////////////
		m_SuppBased	= PATCH;
		m_pPatch	= pPatch;
		m_SuppCard	= SupCard;
		m_SuppProc	= SupCard.SuppProc;
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldLinSup(m_SuppProc, pList);
		if(nResult<0)
				return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(SupCard);
		//////////////////////////////////////////////////////// Loop Over All Triangles
		CDrLinSup* pAdd;
	   ////////////////////////////////////////////////////////////////// Create
		CDListMgr* pTriList = m_pPatch->GetTriangleList();
		if(pTriList->IsEmpty() )
			return MA_ERROR;
		////////////////////////
		int nTriangle	= pTriList->GetCount();
		////////////////////////////////// Save PatchInfo
		// Each Output Triangle should be all the Output Pts.
		// this will require redundancy but simplify,So
		////////////////////////////////////////////////////
		int nStartCount = pPatch->GetSuppList()->GetCount();
		m_SuppCard.nStartIndex = nStartCount;
		/////////////////////////////////////////////////////////////////// LOOP: Triangle List
		int index = -1;
		///////////
		for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
		{
			CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
			/////////////////////////////////////////////// get info
			int nType		= pTri->GetType();
			int iOutGlo		= pTri->GetiOutGlo();
			int jOutGlo		= pTri->GetjOutGlo();
			/////////////////////////////////////////////////////////////////// Bot & Top Triangle
			index++;
			////
			if(nType == 1)
				pAdd = TRIANGLE_1(pOut,pOutPatchNor,pOutPatchTan_S,pOutPatchTan_T,
													SupCard,iOutGlo,jOutGlo);
			else
			if(nType == 2)
				pAdd = TRIANGLE_2(pOut,pOutPatchNor,pOutPatchTan_S,pOutPatchTan_T,
													SupCard,iOutGlo,jOutGlo);
			else
			{
				//////////////////
				AfxMessageBox("CMI_LSupp::CreatePatchBased_3\nnType !==1 or 2");
				return MA_ERROR;
			}
		}										///////////////////////////// end LIST
		////////////////////////////////////////// SAVE StaLCard
		m_SuppCard.nTotal = pPatch->GetSuppList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_SuppCard);
	}
	/////////////////////////////////////// Update StaLCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(pOutPatchTan_S)
		FreeMem(pOutPatchTan_S);
	if(pOutPatchTan_T)
		FreeMem(pOutPatchTan_T);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return MA_OK;
}

CDrLinSup*  CMI_LSupp::TRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,
								  pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
								  SUPPCARD& supCard,int iOutGlo_ST,int jOutGlo_ST)
{ 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////
	CDrLinSup* pAdd = NULL;
	///////////////////////
	int i,j,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= m_pPatch->GetOut_S();
	int nOutSeg_S	= m_pPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			m_NodePos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
			if( IsDuplicated(m_NodePos,m_SuppProc) )
				continue;
			///////////////////////////////////////////////////////////////////////// Add
			pAdd = new CDrLinSup;
			////////////////////////////
			pAdd->SetNodPos(m_NodePos);
			(pAdd->GetSuppCard())->SuppProc	= m_SuppProc;
			///////////////////////////////////////////// init Raw Support Data
			pAdd->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+L1);
			///
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+L1);
				m_PatchTan_T	= *(pOutPatchTan_T+L1);
			}
			///////////////// Set Quick Search Info
			pAdd->SetTriangle(TRUE);
			pAdd->SetCreate_i(iOut);
			pAdd->SetCreate_j(jOut);
			pAdd->SetCreateBase(m_SuppBased);
			///////////////////////////
			SetInfoForLinSupBase(pAdd,supCard);	
			///////
		}
	}
	return pAdd;
}									

CDrLinSup*  CMI_LSupp::TRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,
								  pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
								  SUPPCARD& supCard,int iOutGlo_ST,int jOutGlo_ST)
{ 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////
	CDrLinSup* pAdd = NULL;
	///////////////////////
	int i,j,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= m_pPatch->GetOut_S();
	int nOutSeg_S	= m_pPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			m_NodePos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
			if( IsDuplicated(m_NodePos,m_SuppProc) )
				continue;
			///////////////////////////////////////////////////////////////////////// Add
			pAdd = new CDrLinSup;
			////////////////////////////
			pAdd->SetNodPos(m_NodePos);
			(pAdd->GetSuppCard())->SuppProc	= m_SuppProc;
			///////////////////////////////////////////// init Raw Support Data
			pAdd->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+L1);
			///
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+L1);
				m_PatchTan_T	= *(pOutPatchTan_T+L1);
			}
			///////////////// Set Quick Search Info
			pAdd->SetTriangle(TRUE);
			pAdd->SetCreate_i(iOut);
			pAdd->SetCreate_j(jOut);
			pAdd->SetCreateBase(m_SuppBased);
			///////////////////////////
			SetInfoForLinSupBase(pAdd,supCard);	
			///////
		}
	}
	return pAdd;
}									

int CMI_LSupp::UpdateFixedDirSkewMatrix(SUPPCARD& SupCard)
{
	C3DMath	Math3D;
	CXForm	XForm;
	///////////////////////////////////////////////////////// Fixed Skewed direction
	if(SupCard.jcType == JC_X_FIXEDDIR)		
	{
		WORLD	NewX;
		pWORLD	pNewX = &NewX;
		//////////////////////
		Math3D.Set3DPts(pNewX, SupCard.SkewDir.x, SupCard.SkewDir.y, SupCard.SkewDir.z);
		/////////////////////////////////// Rotate to NewX
		XForm.RotateToNewXMATRIX(pNewX, &m_SkewDirMat,XF_REPLACE);
	}
	////////////
	return MA_OK;
}

BOOL CMI_LSupp::IsPatchTangentNeeded(CList<SUPPCARD,SUPPCARD>* pSuppCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pSuppCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		SUPPCARD SuppCard = pSuppCardList->GetNext(posI);
		if( SuppCard.jcType == JC_I_TAN_PATCH)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

int CMI_LSupp::CreatePatchBased_4(CDrPatch* pPatch,CList<SUPPCARD,SUPPCARD>* pCardList)
{
	UINT SuppBased	= PATCH;
	CList<SUPPCARD,SUPPCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S	= pPatch->IsClosed_S();
	BOOL bClosed_T	= pPatch->IsClosed_T();
	long nOut		= pPatch->GetLongOutPts();
//	BOOL bLinSpr		= pPatch->IsLinSpr();
//	BOOL bLinSnu		= pPatch->IsLinSnu();
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	m_PatSubType = pPatch->GetPatSubType(); 
	FillMeshNodesPatch(pPatch,pOut,pOutWts);
	//////////////////////////////////////////// Generate Tangents, if Needed
	m_bCurveTan	= IsTangentNeeded(pCardList);				
	//////////////////////////////////////////// Generate Patch Tangents, if Needed
	m_bPatchTan	= IsPatchTangentNeeded(pCardList);
	///////////			
	pWORLD	pOutPatchTan_S = NULL;
	pWORLD	pOutPatchTan_T = NULL;
	///////////////
	if(m_bPatchTan)
	{
		pOutPatchTan_S	= FixMem(nOut);
		pOutPatchTan_T	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsPatch(pPatch,pOutPatchTan_S,pOutPatchTan_T);
		/////////////////////
	}
	//////////////////////////////////////////// Generate Patch Normals, if Needed
	m_bPatchNor	= IsPatchTangentNeeded(pCardList);
	pWORLD	pOutPatchNor;
	///////////////////////////
	if(m_bPatchNor)
	{
		pOutPatchNor	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshNormalsPatch(pPatch,pOutPatchNor);
		/////////////////////
	}
	///////////////////////////////////////////////////////////////////// LOOP:StaLCardList
	for (POSITION posI = pCardList->GetHeadPosition( );posI !=NULL;)
	{
		SUPPCARD SupCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_SuppCard	= SupCard; 
		m_SuppBased	= PATCH;
		m_pPatch	= pPatch;
		m_SuppProc	= SupCard.SuppProc;
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldLinSup(m_SuppProc, pPatch->GetSuppList());
		if(nResult<0)
				return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(SupCard);
		////////////////////////////////////////////////////
		int nStartCount		= pPatch->GetSuppList()->GetCount();
		m_SuppCard.nStartIndex = nStartCount;
		//////////////////////////////////////////////////// Loop Over MeshPts
		LoopOver_Patch_4_Pts(pPatch,SupCard,pOut,
			pOutPatchTan_S,pOutPatchTan_T,pOutPatchNor,nOut);
		////////////////////////////////////////// SAVE StaLCard
		m_SuppCard.nTotal = pPatch->GetSuppList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_SuppCard);
	}
	/////////////////////////////////////// Update StaLCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(pOutPatchTan_S)
		FreeMem(pOutPatchTan_S);
	if(pOutPatchTan_T)
		FreeMem(pOutPatchTan_T);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return MA_OK;
}

int CMI_LSupp::LoopOver_Patch_4_Pts(CDrPatch* pPatch,SUPPCARD& SupCard,
					pWORLD pOut,pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
					pWORLD pOutPatchNor,int nOut)
{
	m_pPatch	= pPatch;
	m_SuppCard	= SupCard;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,j;
	int k		= -1;
	////////////////////////////
	BOOL bClosed		= pPatch->IsClosed_S();
	CDListMgr* pList	= pPatch->GetSuppList();
	////////////////////////////////
	m_SuppBased			= PATCH;
	m_SuppProc			= SupCard.SuppProc;
	m_SuppCard			= SupCard;
	//////////////////////////////////////////////////////// Closed?
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	int nOut_T			= pPatch->GetOut_T();
	//
	int nOutCreate_S	= nOut_S;
	if(bClosed_S)
		nOutCreate_S--;
	int nOutCreate_T	= nOut_T;
	if(bClosed_T)
		nOutCreate_T--;
	////////////////////////////////////////////////////
	int nStartCount = pPatch->GetSuppList()->GetCount();
	m_SuppCard.nStartIndex = nStartCount;
	//////////////////////////////////////////////////////// 
	int nNodPossBeg_S	= SupCard.nNodPos_S_Beg;
	int nNodPossEnd_S	= SupCard.nNodPos_S_End;
	int nNodPossBeg_T	= SupCard.nNodPos_T_Beg;
	int nNodPossEnd_T	= SupCard.nNodPos_T_End;
	//////////////////////////////////////////////
	for(i=nNodPossBeg_S;i<nNodPossEnd_S;i++)	// necessary for Curve_Profile
											// for single Curve:	nNodPossBeg=0
											//						nNodPossEnd=nMaxBezSeg
	{
		for(j=nNodPossBeg_T;j<nNodPossEnd_T;j++)
		{
			k++;
			m_NodePos	= *(pOut+k);
			//////////////////////////////////////////////////////// Duplicate
			if( IsDuplicated(m_NodePos,m_SuppProc) )
				continue;
			///////////////////////////////////////////////////////////////////////// Add
			CDrLinSup* pAdd = new CDrLinSup;
			///////////////// Set Quick Search Info
			pAdd->SetCreate_i(i);
			pAdd->SetCreate_j(j);
			pAdd->SetCreateBase(m_SuppBased);
			pAdd->SetNodPos(m_NodePos);
			///////////////////////////////////////////////////////////////////
			(pAdd->GetSuppCard())->SuppProc	= m_SuppProc;
			///////////////////////////////////////////// init Raw Support Data
			pAdd->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+k);
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+k);
				m_PatchTan_T	= *(pOutPatchTan_T+k);
			}
			///////////////////////////
			SetInfoForLinSupBase(pAdd,SupCard);	
			////////////////////////////////////// save Private
			pPatch->GetSuppList()->InsertObject(pAdd);		
			///////	
		}		
	}
	/////////////////////
    return MA_OK;
}

BOOL CMI_LSupp::IsTangentNeeded(CList<SUPPCARD,SUPPCARD>* pStaLCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pStaLCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		SUPPCARD SupCard = pStaLCardList->GetNext(posI);
		if( SupCard.jcType == JC_X_TAN_CURVE)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

BOOL CMI_LSupp::IsNormalNeeded(CList<SUPPCARD,SUPPCARD>* pStaLCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pStaLCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		SUPPCARD SupCard = pStaLCardList->GetNext(posI);
		if( SupCard.jcType == JC_Z_NOR_PATCH)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

int CMI_LSupp::LoopOver_CurvePts(CDrCurve* pCurve,SUPPCARD& SupCard,
							pWORLD pOut,pWORLD pOutCurveTan,int nOut)
{
	m_pCurve	= pCurve;
	m_SuppCard	= SupCard;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i;
	int nVal = -1;
	////////////////////////////
	BOOL bClosed		= pCurve->IsClosed_S();
	CDListMgr* pList	= pCurve->GetSuppList();
	////////////////////////////////
	m_SuppBased			= CURVE;
	m_SuppProc			= SupCard.SuppProc;
	//////////////////////////////////////////////////////// Closed?
	int nOutCreate		= nOut;
	if(bClosed)
		nOutCreate--;
	//////////////////////////////////////////////////////// 
	int nNodPossBeg		= SupCard.nNodPos_S_Beg;
	int nNodPossEnd		= SupCard.nNodPos_S_End;
	//////////////////////////////////////////////
	for(i=nNodPossBeg;i<nNodPossEnd;i++)	// necessary for Curve_Profile
											// for single Curve:	nNodPossBeg=0
											//						nNodPossEnd=nMaxBezSeg
	{
		/////////////////////////
		m_NodePos	= *(pOut+i);
		/////////////////////////////// Add
		CDrLinSup* pAdd = new CDrLinSup;
		///////////////// Set Quick Search Info
		pAdd->SetCreate_i(i);
		pAdd->SetCreateBase(m_SuppBased);
		pAdd->SetNodPos(m_NodePos);
		//////////////////////////////////////////////////////// Duplicate
		if( IsDuplicated(m_NodePos,m_SuppProc) )
			continue;
		///////////////////////////////////////////////////////////////////
		(pAdd->GetSuppCard())->SuppProc	= m_SuppProc;
		///////////////////////////////////////////// init Raw Support Data
		pAdd->InitRawData(m_SuppProc);
		/////////////////////
		if(m_bCurveTan)
			m_CurveTan	= *(pOutCurveTan+i);
		///////////////////////////
		SetInfoForLinSupBase(pAdd,m_SuppCard);	
		////////////////////////////////////// save Private
		pCurve->GetSuppList()->InsertObject(pAdd);		
	}
	//////////////////
	return MA_OK;
}

int CMI_LSupp::CreateCurveBased(CDrCurve* pCurve,CList<SUPPCARD,SUPPCARD>* pCardList)
{
	UINT SuppBased	= CURVE;
	CList<SUPPCARD,SUPPCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	//////////////////////////////////////////// Output memory
	int nOut			= pCurve->GetLongOutPts();
	BOOL bClosed		= pCurve->IsClosed_S();
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	//////////////////////////////////////////// Generate Tangents, if Needed
	m_bCurveTan	= IsTangentNeeded(pCardList);
	pWORLD	pOutCurveTan;
	///////////////////////////
	if(m_bCurveTan)
	{
		int nOutTan		= nOut;
		if(bClosed)
			nOutTan--;
		pOutCurveTan	= FixMem(nOutTan);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsCurve(pCurve,pOutCurveTan,nOutTan);
		/////////////////////
	}
	//////////////////////////////////////////// Generate Normals, if Needed
	m_bPatchNor	= IsNormalNeeded(pCardList);				
	///////////////////////////////////////////////////////////////////// LOOP:StaLCardList
	for (POSITION posI = pCardList->GetHeadPosition( );posI !=NULL;)
	{
		SUPPCARD SupCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_SuppCard	= SupCard; 
		m_SuppBased	= CURVE;
		m_pCurve	= pCurve;
		m_SuppProc	= SupCard.SuppProc;
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldLinSup(m_SuppProc, pCurve->GetSuppList());
		if(nResult<0)
				return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(SupCard);
		////////////////////////////////////////////////////
		int nStartCount		= pCurve->GetSuppList()->GetCount();
		m_SuppCard.nStartIndex = nStartCount;
		//////////////////////////////////////////////////// Loop Over MeshPts
		LoopOver_CurvePts(pCurve,SupCard,pOut,pOutCurveTan,nOut);
		////////////////////////////////////////// SAVE StaLCard
		m_SuppCard.nTotal = pCurve->GetSuppList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_SuppCard);
	}
	/////////////////////////////////////// Update StaLCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	if(m_bCurveTan)
		FreeMem(pOutCurveTan);
	/////////////////////
    return MA_OK;
}

int CMI_LSupp::CreateNodeBased(CDrNode* pNode,CList<SUPPCARD,SUPPCARD>* pCardList)
{
	UINT SuppBased	= NODE;
	CList<SUPPCARD,SUPPCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	CDrLinSup* pAdd;
	CString strCurORPat;
	///////////////////////////////////////////////////////////////////////////
	// Remove or Destroy Old One similar to Current Supproc
	////////////////////////////////////////
	CDListMgr* pList = pNode->GetSuppList();
	///////////////////////////////////////////////////////////////////// LOOP:StaLCardList
	for (POSITION posI = pCardList->GetHeadPosition( );posI !=NULL;)
	{
		SUPPCARD SupCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_SuppCard	= SupCard; 
		m_SuppBased	= NODE;
		m_pNode		= pNode;
		m_SuppProc	= SupCard.SuppProc;
		//////////////////////////////////////////////
		int nResult = RemoveOldLinSup(m_SuppProc, pNode->GetSuppList());
		if(nResult<0)
			return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		if(SupCard.jcType == JC_X_FIXEDDIR)		
			UpdateFixedDirSkewMatrix(SupCard);
		///////////////////////////////////////////////////////// Curve Tangential
		else
		if( SupCard.jcType == JC_X_TAN_CURVE)
		{
			m_bCurveTan	= TRUE;
			strCurORPat = SupCard.ID_CP;
			///////////////////
			CDListMgr* pCurveList = pObjectMgr->GetObjectList(CURVE);
			int index = pCurveList->GetObjectIndex(CURVE, strCurORPat);
			if(index<0)
				return MA_ERROR;
			////////////////////////////
			CDrCurve* pCurve = (CDrCurve*)pCurveList->GetObject(index);
			if(!pCurve)
				return MA_ERROR;
			//////////////////////////// GetTangent at Node Location (pNewX)
			WORLD wLocalPos = *(pNode->GetLocalPos());
			if(pCurve->Get_TangentAtaNode(wLocalPos,m_CurveTan,pHitNet->GetDblRatio())<0)
				return MA_ERROR;
			////////////////////////////
			C3DMath	Math3D;
			Math3D.Normalize(&m_CurveTan,&m_CurveTan);
		}
		///////////////////////////////////////////////////////// Patch Normal
		else
		if( SupCard.jcType == JC_Z_NOR_PATCH)
		{		
			m_bPatchNor		= TRUE;				
			strCurORPat = SupCard.ID_CP;
			///////////////////
			CDListMgr* pPatchList = pObjectMgr->GetObjectList(PATCH);
			int index = pPatchList->GetObjectIndex(PATCH, strCurORPat);
			if(index<0)
				return MA_ERROR;
			////////////////////////////
			CDrPatch* pPatch = (CDrPatch*)pPatchList->GetObject(index);
			if(!pPatch)
				return MA_ERROR;
			//////////////////////////// GetNormal at Node Location (pNewX)
			WORLD Tangent_U,Tangent_V;
			WORLD wLocalPos = *(pNode->GetLocalPos());
			//////////////////////////////////////////
			if(pPatch->GetPatSubType() == PS_QUADRILAT)
			{
				if(pPatch->Get_Tan_N_NorAtaNode_4(wLocalPos,Tangent_U,Tangent_V,m_PatchNor
																,pHitNet->GetDblRatio())<0)
					return MA_ERROR;
			}
			else
			if(pPatch->GetPatSubType() == PS_TRIANGLE)
			{
				if(pPatch->Get_Tan_N_NorAtaNode_3(wLocalPos,Tangent_U,Tangent_V,m_PatchNor
																,pHitNet->GetDblRatio())<0)
					return MA_ERROR;
			}
			////////////////////////////
			C3DMath	Math3D;
			Math3D.Normalize(&m_PatchNor,&m_PatchNor);
		}
		///////////////////////////////////////////////////////// Patch Tangent
		else
		if( SupCard.jcType == JC_I_TAN_PATCH)
		{		
			m_bPatchTan		= TRUE;				
			strCurORPat = SupCard.ID_CP;
			///////////////////
			CDListMgr* pPatchList = pObjectMgr->GetObjectList(PATCH);
			int index = pPatchList->GetObjectIndex(PATCH, strCurORPat);
			if(index<0)
				return MA_ERROR;
			////////////////////////////
			CDrPatch* pPatch = (CDrPatch*)pPatchList->GetObject(index);
			if(!pPatch)
				return MA_ERROR;
			//////////////////////////// GetTangent at Node Location (pNewX)
			WORLD wLocalPos = *(pNode->GetLocalPos());
			//////////////////////////////////////////
			if(pPatch->GetPatSubType() == PS_QUADRILAT)
			{
				if(pPatch->Get_Tan_N_NorAtaNode_4(wLocalPos,m_PatchTan_S,m_PatchTan_T,m_PatchNor
																	,pHitNet->GetDblRatio())<0)
					return MA_ERROR;
			}
			else
			if(pPatch->GetPatSubType() == PS_TRIANGLE)
			{
				if(pPatch->Get_Tan_N_NorAtaNode_3(wLocalPos,m_PatchTan_S,m_PatchTan_T,m_PatchNor
																	,pHitNet->GetDblRatio())<0)
					return MA_ERROR;
			}
		}
		//////////////////////////////////////////////////////// fill in
		m_SuppCard	= SupCard;
		m_SuppBased	= SuppBased;
		m_SuppProc	= SupCard.SuppProc;
		m_pNode		= pNode;
		m_NodePos	= *(m_pNode->GetLocalPos());
		//////////////////////////////////////////////////////// Duplicate
		if( IsDuplicated(m_NodePos,m_SuppProc) )
			return MA_ERROR;
		////////////////////////////////////////////////////
		int nStartCount = pNode->GetSuppList()->GetCount();
		m_SuppCard.nStartIndex = nStartCount;
		///////////////////////////////////////////////////////////////////
		pAdd 	= new CDrLinSup;
		///////////////// Set Quick Search Info
		CDListMgr* pNodeList	= pObjectMgr->GetObjectList(NODE);
		int index = pNodeList->GetObjectIndex(pNode); 
		pAdd->SetCreate_i(index);
		pAdd->SetCreateBase(m_SuppBased);
		pAdd->SetNodPos(m_NodePos);
		////////////
		(pAdd->GetSuppCard())->SuppProc	= m_SuppProc;
		///////////////////////////////////////////// init Raw Support Data
		pAdd->InitRawData(m_SuppProc);
		///////////////////////////////////////////// Fill in
		SetInfoForLinSupBase(pAdd,SupCard);	
		////////////////////////////////////// save Private
		pNode->GetSuppList()->InsertObject(pAdd);		
		////////////////////////////////////////// SAVE StaLCard
		m_SuppCard.nTotal = pNode->GetSuppList()->GetCount() - nStartCount;  
		TempCardList.AddTail(m_SuppCard);
	}
	/////////////////////////////////////// Update SuppCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////
    return MA_OK;
}

BOOL CMI_LSupp::IsDuplicated(WORLD& CurrentNodPos, SUPPPROC CurrentSuppProc)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	C3DMath		Math3D;
	CDListMgr*	pList;
	WORLD		NodPos;
	/////////////////////////////////////////////////////////
	switch(m_SuppBased)
	{
		case NODE:
			pList = m_pNode->GetSuppList();
			////////
			break;
			
		case CURVE:
			pList = m_pCurve->GetSuppList();
			////////
			break;

		case PATCH:
			pList = m_pPatch->GetSuppList();
			////////
			break;

		case SOLID:
			pList = m_pSolid->GetSuppList();
			////////
			break;

		default:
			return TRUE;
	}
	//////////////////////////////////////////// Check
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrLinSup* pSupp 	= (CDrLinSup*)pList->GetNextObject(pos);
		////
		if( (pSupp->GetSuppCard())->SuppProc != CurrentSuppProc)
			continue;
		///////////////////////
		NodPos = *(pSupp->GetNodPos());
		///////////////////////////////
		if(Math3D.AreSame_WORLD(&NodPos,&CurrentNodPos,pHitNet->GetDblRatio()))
			return TRUE;
	}
	////////////////////////
	return FALSE;
}

void CMI_LSupp::SetSupportID(CDrLinSup* pSupp,char* buf,int jStart)
{
	int j = jStart;
	int ic,jc,kc;
	/////////////
/*
	switch((pSupp->GetSuppCard())->SuppProc)
	{
		case SUP_RIGID:
			j += sprintf(buf+j,"RIG_");
			break;
		case SUP_LINSPR:
			j += sprintf(buf+j,"LSP_");
			break;
		case SUP_LINSNU:
			j += sprintf(buf+j,"LSN_");
			break;
	}
*/
	j += sprintf(buf+j,"%s",pSupp->GetObjectID());
	//////////////////////////
	switch(pSupp->GetCreateBase())
	{
		case NODE:
		///////////////////////////////////////////////// 
//			j += sprintf(buf+j,"N_%s",m_pNode->GetObjectID());
			break;
		case CURVE:
		///////////////////////////////////////////////// 
			ic = pSupp->GetCreate_i();
//			j += sprintf(buf+j,"%s_%d",m_pCurve->GetObjectID(),ic);
			j += sprintf(buf+j,"_%d",ic);
			break;
		case PATCH:
		///////////////////////////////////////////////// 
			ic = pSupp->GetCreate_i();
			jc = pSupp->GetCreate_j();
//			j += sprintf(buf+j,"%s_%d_%d",m_pPatch->GetObjectID(),ic,jc);
			j += sprintf(buf+j,"_%d_%d",ic,jc);
			break;
		case SOLID:
		///////////////////////////////////////////////// 
			ic = pSupp->GetCreate_i();
			jc = pSupp->GetCreate_j();
			kc = pSupp->GetCreate_k();
//			j += sprintf(buf+j,"%s_%d_%d_%d",m_pSolid->GetObjectID(),ic,jc,kc);
			j += sprintf(buf+j,"_%d_%d_%d",ic,jc,kc);
			break;
		default:
			j += sprintf(buf+j,"");
			break;
	}
}

void CMI_LSupp::SetInfoForLinSupBase(CDrLinSup* pSupp,SUPPCARD supCard)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Node
	LONG  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////
	pSupp->SetObjectType((int)LIN_SUPPORT);
	pSupp->SetElemType((int)ELEM_OBJECT);              // globals.h
    pSupp->SetLevelType((int)LEVEL_GRAPA);								// Kid Level
	pSupp->SetObjectID(m_sup_id);             
	/////////////////////////////////////////////////
//		int			ElNum;                 
//		int			IDNum;
	///////////////////////////////////////////////////////// ID
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	///
	pSupp->SetObjectID(supCard.sup_id);
	SetSupportID(pSupp,buf,0);
	pSupp->SetObjectID(*str);
	(pSupp->GetSuppCard())->sup_id = *str;
	///
	delete str;
	///////////////////////////////////////////////// Kode
	if(m_SuppProc == SUP_RIGID)
	{
		for(int i=0;i<6;i++)
		{
			(pSupp->GetSuppCard())->kode[i] = 1;
			(pSupp->GetSuppCard())->pgap[i] = 0;
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
			(pSupp->GetSuppCard())->kode[i] = supCard.kode[i];
			(pSupp->GetSuppCard())->pgap[i] = supCard.pgap[i];
		}
	}
	//////////////////////////////////////////////////
//	(pSupp->GetSuppCard())->SuppProc 	= m_SuppProc;		// done in Calling Routine
	for(int s=0;s<6;s++)
		(pSupp->GetSuppCard())->stiffness[s] 	= supCard.stiffness[s];
	(pSupp->GetSuppCard())->nid_a 		= supCard.nid_a;
	(pSupp->GetSuppCard())->nid_b 		= supCard.nid_b;
	///////////////////////////////////////////////// Convert Support LocalData to WORLD
//   	WORLD LocalPos,CNodPos;
   	WORLD LocalPos;
	pWORLD pDat;
	int i,j,nPts;
	WORLD Nor_Z,vec_W;
	////////////////////////////////////////////////////////// Skewed Support
	C3DMath	Math3D;
	CXForm	XForm;
	/////////////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat; 
	WORLD NewX;
	pWORLD pNewX = &NewX;
	////////////////////////
	Math3D.GetIdentityMATRIX(pMat);
	////////////////////////
	if(supCard.jcType == JC_X_FIXEDDIR)		// Fixed Skewed direction 
	{
		/////////////////////////////////// Copy  Skew Matrix
		Math3D.BlockCopy((HUGEBLK)(&m_SkewDirMat),(HUGEBLK)(pMat), sizeof(MATRIX) );
	}
	else
	if(supCard.jcType == JC_X_TAN_CURVE)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewXMATRIX(&m_CurveTan, pMat,XF_REPLACE);
	}
	else
	if(supCard.jcType == JC_Z_NOR_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewZ = Normal direction
		XForm.RotateToNewZMATRIX(&m_PatchNor, pMat,XF_REPLACE);

	}
	else
	if(supCard.jcType == JC_I_TAN_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////// Normalize
		Math3D.Normalize(&m_PatchTan_S,&m_PatchTan_S);
		Math3D.Normalize(&m_PatchTan_T,&m_PatchTan_T);
		/////////////////////////////// form Z-Axis
		Math3D.Cross3DPts(&m_PatchTan_S,&m_PatchTan_T,&Nor_Z);
		Math3D.Set3DPts(&vec_W,0.0,0.0,0.0); // homogeneous vector:Ist 3 components
		/////////////////////////////////// Form new Rot Matrix
		Math3D.SetMATRIX(pMat,&m_PatchTan_S,&m_PatchTan_T,&Nor_Z,&vec_W);

	}
	////////////////////////////////////////////////////////// Over All Directions 
	for(i=0;i<6;i++)		
	{
		if
		(
			((pSupp->GetSuppCard())->kode[i] == 0) ||
			(i>0 && (pSupp->GetSuppCard())->SuppProc == SUP_RIGID)
		)
		continue;
		/////////////	// Over Active Directions
		nPts = pSupp->GetnPts(i);
		pDat = pSupp->GetpLoc(i);
		/////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = pDat[j].x;
			LocalPos.y = pDat[j].y;
			LocalPos.z = pDat[j].z;
			/////////////////////////// strip Scale Factor (World Coord)
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
			/////////////////////////////////////////////// Rotate for Skewed Support
			if(supCard.nid_a != "" || m_bCurveTan || m_bPatchNor|| m_bPatchTan)
			{
				/////////////////////////////////// Now Rotate
				XForm.Transform(&LocalPos, &LocalPos, pMat);
			}
    		/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
		}
	}
	////////////////////////////////////////// finally
	pSupp->SetSuppCard(supCard);
	////////////////////////////////////////// 
	pSupp->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pSupp->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

int CMI_LSupp::RemoveOldLinSup(SUPPPROC SuppProc, CDListMgr* pList)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(LIN_SUPPORT);
	////////////////////////////////////////////////////// Current Spring or Snubber?
	int i,j;
	BOOL bLinSprCurrent,bLinSprToRemove;
	switch(SuppProc)
	{
		case SUP_RIGID:
		case SUP_LINSPR:
			bLinSprCurrent = TRUE;
			break;
		case SUP_LINSNU:
			bLinSprCurrent = FALSE;
			break;
		default:
			{
				AfxMessageBox("Internal ERROR:\nCMI_LSupp::CreatePatchLinSup_4\nSuppProc ILLEGAL"); 
				return -1;
			}
	}
	//////////////////////////////////
	int	nCount	= pList->GetCount();
	//////////////////////////////////////////////////////// Remove Old Similar ListItems
	for(i=0; i<nCount;i++)
	{
		////////////////////
		POSITION pos;
		///////////////////////////////////////////////////////
		// Remove or Destroy Old Ones similar to Current Supproc
		///////////////////////////////
		CDrLinSup*	pDrLinSup;
		/////////////////////////////////////////////////////////// 
		pos = pList->FindIndex(nCount-i-1);
		pDrLinSup = (CDrLinSup*)pList->GetAt(pos);
		////
		if(!pDrLinSup)
		{
			AfxMessageBox("Internal ERROR:\nCMI_LSupp::CreatePatchLinSup_4\npDrLinSup=NULL"); 
			return -1;
		}
		///////////////////////////////////////////////// Linear Supports
		SUPPPROC SuppProc_ToRemove = (pDrLinSup->GetSuppCard())->SuppProc;
		////////////////////////////////////////////////////// Current Spring or Snubber?
		switch(SuppProc)
		{
			case SUP_RIGID:
			case SUP_LINSPR:
				bLinSprToRemove = TRUE;
				break;
			case SUP_LINSNU:
				bLinSprToRemove = FALSE;
				break;
			default:
			{
				AfxMessageBox("Internal ERROR:\nCMI_LSupp::CreatePatchLinSup_4\nSuppProc ILLEGAL"); 
				return -1;
			}
		}
		//////////////////////////////////////////////////////
		if(bLinSprToRemove == bLinSprCurrent)
		{
			pList->RemoveAt(pos);
			///////////////////////////////////////////// Delete Sup
			int nSupCount = pDListMgr->GetCount();
			/////////
			CString sup_id_ToRemove = (pDrLinSup->GetSuppCard())->sup_id;
			//////////////////////////////////////////////////////////
			for(j=0; j<nSupCount;j++)
			{
				pos					= pDListMgr->FindIndex(nSupCount-j-1);
				CDrLinSup* pSup		= (CDrLinSup*)pList->GetAt(pos); 
				CString sup_id_j	= (pSup->GetSuppCard())->sup_id;
				////////////////////////////////////////////////
				if(sup_id_ToRemove == sup_id_j)
				{
					pObjectMgr->DeleteFromDataBase(nSupCount-j-1,LIN_SUPPORT);
					break;
				}
				////////////////////////////
			}
		}
	}
	////////////////////////////////////////////////////////
	return 0;
}

int CMI_LSupp::RegenNodeBased(CDrNode* pNode)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<SUPPCARD,SUPPCARD>* pStaLCardList = pNode->GetSuppCardList();
	if(pStaLCardList->IsEmpty())
		return 0;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// SupCard
		SUPPCARD SupCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pNode->GetSuppList();
		int nBeg = SupCard.nStartIndex;
		int nEnd = nBeg + SupCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenNodeBased_DoIt(pNode,SupCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
		////////////////////
		CurList.RemoveAll();
	}
	////////////
	return MA_OK;
}


int CMI_LSupp::RegenNodeBased_DoIt(CDrNode* pNode,SUPPCARD& SupCard,CDListMgr* pList)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CString strCurORPat;
	////////////////////
	m_bCurveTan	= FALSE;
	m_bPatchNor	= FALSE;
	//////////////////////////////////////////// Output memory
	BOOL bLinSpr		= pNode->IsLinSpr();
	BOOL bLinSnu		= pNode->IsLinSnu();
	///////////////////////////////////////////////////////// Fixed Skewed direction
	if(SupCard.jcType == JC_X_FIXEDDIR)		
		UpdateFixedDirSkewMatrix(SupCard);
	///////////////////////////////////////////////////////// Curve Tangential
	else
	if( SupCard.jcType == JC_X_TAN_CURVE)
	{
		m_bCurveTan	= TRUE;
		strCurORPat = SupCard.ID_CP;
		///////////////////
		CDListMgr* pCurveList = pObjectMgr->GetObjectList(CURVE);
		int index = pCurveList->GetObjectIndex(CURVE, strCurORPat);
		if(index<0)
			return MA_ERROR;
		////////////////////////////
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetObject(index);
		if(!pCurve)
			return MA_ERROR;
		//////////////////////////// GetTangent at Node Location (pNewX)
		WORLD wLocalPos = *(pNode->GetLocalPos());
		if(pCurve->Get_TangentAtaNode(wLocalPos,m_CurveTan,pHitNet->GetDblRatio())<0)
			return MA_ERROR;
		////////////////////////////
		C3DMath	Math3D;
		Math3D.Normalize(&m_CurveTan,&m_CurveTan);
	}
	///////////////////////////////////////////////////////// Patch Normal
	else
	if( SupCard.jcType == JC_Z_NOR_PATCH)
	{		
		m_bPatchNor		= TRUE;				
		strCurORPat = SupCard.ID_CP;
		///////////////////
		CDListMgr* pPatchList = pObjectMgr->GetObjectList(PATCH);
		int index = pPatchList->GetObjectIndex(PATCH, strCurORPat);
		if(index<0)
			return MA_ERROR;
		////////////////////////////
		CDrPatch* pPatch = (CDrPatch*)pPatchList->GetObject(index);
		if(!pPatch)
			return MA_ERROR;
		//////////////////////////// GetNormal at Node Location (pNewX)
		WORLD Tangent_U,Tangent_V;
		WORLD wLocalPos = *(pNode->GetLocalPos());
		//////////////////////////////////////////
		if(pPatch->GetPatSubType() == PS_QUADRILAT)
		{
			if(pPatch->Get_Tan_N_NorAtaNode_4(wLocalPos,Tangent_U,Tangent_V,m_PatchNor
															,pHitNet->GetDblRatio())<0)
				return MA_ERROR;
		}
		else
		if(pPatch->GetPatSubType() == PS_TRIANGLE)
		{
			if(pPatch->Get_Tan_N_NorAtaNode_3(wLocalPos,Tangent_U,Tangent_V,m_PatchNor
															,pHitNet->GetDblRatio())<0)
				return MA_ERROR;
		}
		////////////////////////////
		C3DMath	Math3D;
		Math3D.Normalize(&m_PatchNor,&m_PatchNor);
	}
	///////////////////////////////////////////////////////// Patch Tangent
	else
	if( SupCard.jcType == JC_I_TAN_PATCH)
	{		
		m_bPatchTan		= TRUE;				
		strCurORPat = SupCard.ID_CP;
		///////////////////
		CDListMgr* pPatchList = pObjectMgr->GetObjectList(PATCH);
		int index = pPatchList->GetObjectIndex(PATCH, strCurORPat);
		if(index<0)
			return MA_ERROR;
		////////////////////////////
		CDrPatch* pPatch = (CDrPatch*)pPatchList->GetObject(index);
		if(!pPatch)
			return MA_ERROR;
		//////////////////////////// GetNormal at Node Location (pNewX)
		WORLD wLocalPos = *(pNode->GetLocalPos());
		//////////////////////////////////////////
		if(pPatch->GetPatSubType() == PS_QUADRILAT)
		{
			if(pPatch->Get_Tan_N_NorAtaNode_4(wLocalPos,m_PatchTan_S,m_PatchTan_T,m_PatchNor
																,pHitNet->GetDblRatio())<0)
				return MA_ERROR;
		}
		else
		if(pPatch->GetPatSubType() == PS_TRIANGLE)
		{
			if(pPatch->Get_Tan_N_NorAtaNode_3(wLocalPos,m_PatchTan_S,m_PatchTan_T,m_PatchNor
																,pHitNet->GetDblRatio())<0)
				return MA_ERROR;
		}
	}
	//////////////////////////////////////////////////////// fill in
	m_SuppProc	= SupCard.SuppProc;
	m_pNode		= pNode;
	m_NodePos	= *(m_pNode->GetLocalPos());
	//////////////////////////
	POSITION pos;
    CDrLinSup* pSupp;
	//////////////////////////////////////////////
	if(!pList || pList->IsEmpty())
		return 0;
	/////////////////
	int nSupp = pList->GetCount(); 
	/////////////////
	for(int i=0; i<nSupp;i++)
	{
		//////////////////////////////////////////////////////// Duplicate
//		if( IsDuplicated(m_NodePos,m_SuppProc) )
//			continue;
		///////////////////////////////////////////////////////////////////////// pSupp
		pos = pList->FindIndex(i);
	    pSupp = (CDrLinSup*)(pList->GetAt(pos));
		m_SuppBased	= pSupp->GetCreateBase();
		///////////////////////////////////////////// init Raw Support Data
		pSupp->InitRawData(m_SuppProc);
		///
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,FALSE);
		///////////////// Set new position
		pSupp->SetNodPos(m_NodePos);
		///////////////////////////
		RegenInfoForLinSupBase(pSupp,SupCard);	
		///////
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,TRUE);
	}		
	/////////////////////
    return MA_OK;
}

int CMI_LSupp::RegenCurveBased(CDrCurve* pCurve)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<SUPPCARD,SUPPCARD>* pCardList = pCurve->GetSuppCardList();
	if(pCardList->IsEmpty())
		return MA_OK;
	////////////////////////
	UINT SuppBased	= CURVE;
	//////////////////////////////////////////// Output memory
	int nOut			= pCurve->GetLongOutPts();
	BOOL bClosed		= pCurve->IsClosed_S();
	pWORLD	pOut		= FixMem(nOut);
	pDOUBLE pOutWts		= FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	//////////////////////////////////////////// Generate Tangents, if Needed
	m_bCurveTan	= IsTangentNeeded(pCardList);
	pWORLD	pOutCurveTan;
	///////////////////////////
	if(m_bCurveTan)
	{
		int nOutTan		= nOut;
		if(bClosed)
			nOutTan--;
		pOutCurveTan	= FixMem(nOutTan);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsCurve(pCurve,pOutCurveTan,nOutTan);
		/////////////////////
	}
	//////////////////////////////////////////// Generate Normals, if Needed
	m_bPatchNor	= IsNormalNeeded(pCardList);				
	////////////////////////////////////////////////////// do it
	nResult = RegenCurveBased_DoIt(pCurve,pOut,pOutCurveTan,nOut);
	////////
	if(nResult != MA_OK)
		return nResult;
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(m_bCurveTan)
		FreeMem(pOutCurveTan);
	////////////
	return MA_OK;
}

int CMI_LSupp::RegenCurveBased_DoIt(CDrCurve* pCurve,pWORLD pOut,pWORLD pOutCurveTan,int nOut)
{
	m_pCurve	= pCurve;
	////////////////////////////////////////
	CList<SUPPCARD,SUPPCARD>* pCardList = pCurve->GetSuppCardList();
	if(pCardList->IsEmpty())
		return MA_OK;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	//////////////
	CDListMgr* pList = pCurve->GetStaLList();
	POSITION posStatic;
    CDrLinSup* pStatic;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,indexList=-1;
	//////////////////
	for (POSITION posT = pCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// SupCard
		SUPPCARD SupCard	= pCardList->GetNext(posT); 
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(SupCard);
		///////////////////////////////////////////////// prepare List
		m_SuppCard			= SupCard;
		m_SuppProc			= SupCard.SuppProc;
		//////////////////////////////////////////////////////// 
		int nNodPossBeg		= SupCard.nNodPos_S_Beg;
		int nNodPossEnd		= SupCard.nNodPos_S_End;
		//////////////////////////////////////////////
		for(i=nNodPossBeg;i<nNodPossEnd;i++)	// necessary for Curve_Profile
											// for single Curve:	nNodPossBeg=0
											//						nNodPossEnd=nMaxBezSeg
		{
			/////////////////////////
			m_NodePos	= *(pOut+i);
			///////////////////////////////////////////////////////////////////
			indexList++;	// List index Cumulative because some prev. Compo Curve
					// may not have any Load
			posStatic = pList->FindIndex(indexList);
			pStatic = (CDrLinSup*)(pList->GetAt(posStatic));
			m_SuppBased	= pStatic->GetCreateBase();
			///////////////////////////////////////////// init Raw Support Data
			pStatic->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bCurveTan)
				m_CurveTan	= *(pOutCurveTan+i);
			///
			pObjectMgr->ShowObject_On_Off(pStatic,LIN_SUPPORT,FALSE);
			///////////////// Set new position
			pStatic->SetNodPos(m_NodePos);
			///////////////////////////
			RegenInfoForLinSupBase(pStatic,SupCard);	
			///
			pObjectMgr->ShowObject_On_Off(pStatic,LIN_SUPPORT,TRUE);
			///////	
		}
	}
	/////////////////////
    return MA_OK;
}

int CMI_LSupp::RegenPatchBased_3(CDrPatch* pPatch)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<SUPPCARD,SUPPCARD>* pStaLCardList = pPatch->GetSuppCardList();
	if(pStaLCardList->IsEmpty())
		return MA_ERROR;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// SupCard
		SUPPCARD SupCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pPatch->GetSuppList();
		int nBeg = SupCard.nStartIndex;
		int nEnd = nBeg + SupCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenPatchBased_3_DoIt(pPatch,SupCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
	}
	////////////
	return MA_OK;
}

int CMI_LSupp::RegenPatchBased_3_DoIt(CDrPatch* pPatch,SUPPCARD& SupCard,CDListMgr* pList)
{
	////////////////////////
	m_bCurveTan		= FALSE;
	m_bPatchNor		= FALSE;
	m_bReciproDone	= FALSE;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////// SuppList
	if(!pList || pList->IsEmpty())
		return MA_ERROR;
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	long nOut			= pPatch->GetLongOutPts();
	BOOL bLinSpr		= pPatch->IsLinSpr();
	BOOL bLinSnu		= pPatch->IsLinSnu();
	////////////////////////////////
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	m_PatSubType = pPatch->GetPatSubType(); 
	FillMeshNodesPatch(pPatch,pOut,pOutWts);
	//////////////////////////////////////////// Generate Normals, if Needed
	pWORLD	pOutPatchNor;
	pWORLD	pOutPatchTan_S;
	pWORLD	pOutPatchTan_T;
	m_bPatchNor	= SupCard.bNorPat;
	m_bPatchTan	= SupCard.bTanPat;
	///////////////////////////
	if(m_bPatchNor)
	{
		pOutPatchNor	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshNormalsPatch(pPatch,pOutPatchNor);
		/////////////////////
	}
	if(m_bPatchTan)
	{
		pOutPatchTan_S	= FixMem(nOut);
		pOutPatchTan_T	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsPatch(pPatch,pOutPatchTan_S,pOutPatchTan_T);
		/////////////////////
	}
	///////////////////////////////////////////////////////// Fixed Skewed direction
	UpdateFixedDirSkewMatrix(SupCard);
	//////////////////////////////////////////////////////// Loop Over All Triangles
	m_pPatch	= pPatch;
	m_SuppProc	= SupCard.SuppProc;
    ////////////////////////////////////////////////////////////////// Create
	CDListMgr* pTriList = m_pPatch->GetTriangleList();
	if(pTriList->IsEmpty() )
		return 0;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	int index = -1;
	///////////
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		index++;
		////
		if(nType == 1)
			RegenTRIANGLE_1(pOut,pOutPatchNor,pList,pOutPatchTan_S,pOutPatchTan_T,
													iOutGlo,jOutGlo);
		else
		if(nType == 2)
			RegenTRIANGLE_2(pOut,pOutPatchNor,pList,pOutPatchTan_S,pOutPatchTan_T,
													iOutGlo,jOutGlo);
		else
		{
			//////////////////
			AfxMessageBox("CMI_LSupp::RegenPatchBased_3\nnType !==1 or 2");
			return -1;
		}
	}										///////////////////////////// end LIST
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return 0;
   	
}

int CMI_LSupp::RegenTRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
													int iOutGlo_ST,int jOutGlo_ST)
{ 
	POSITION pos;
    CDrLinSup* pSupp;
	/////////////////
	int i,j,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= m_pPatch->GetOut_S();
	int nOutSeg_S	= m_pPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			m_NodePos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
//			if( IsDuplicated(m_NodePos,m_SuppProc) )
//				continue;
			///////////////////////////////////////////////////////////////////////// pSupp
			pos = pList->FindIndex(L1);
			pSupp = (CDrLinSup*)(pList->GetAt(pos));
			m_SuppBased	= pSupp->GetCreateBase();
			////////////////////////////
			pSupp->SetNodPos(m_NodePos);
			///////////////////////////////////////////// init Raw Support Data
			pSupp->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+L1);
			///
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+L1);
				m_PatchTan_T	= *(pOutPatchTan_T+L1);
			}
			///////////////////////////
			RegenInfoForLinSupBase(pSupp,*(pSupp->GetSuppCard()));	
			///////
		}
	}
	return 0;
}									

int CMI_LSupp::RegenTRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
													int iOutGlo_ST,int jOutGlo_ST)
{ 
	POSITION pos;
    CDrLinSup* pSupp;
	/////////////////
	int i,j,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= m_pPatch->GetOut_S();
	int nOutSeg_S	= m_pPatch->GetOutSegUnif_S();			
	//////////////////////////////////////////// 
	for (i=0;i<=nOutSeg_S;i++)
	{
		for (j=0;j<=nOutSeg_S-i;j++)
		{
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
			////
			m_NodePos	= *(pOut+L1);
			//////////////////////////////////////////////////////// Duplicate
//			if( IsDuplicated(m_NodePos,m_SuppProc) )
//				continue;
			///////////////////////////////////////////////////////////////////////// pSupp
			pos = pList->FindIndex(L1);
			pSupp = (CDrLinSup*)(pList->GetAt(pos));
			m_SuppBased	= pSupp->GetCreateBase();
			////////////////////////////
			pSupp->SetNodPos(m_NodePos);
			///////////////////////////////////////////// init Raw Support Data
			pSupp->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+L1);
			///
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+L1);
				m_PatchTan_T	= *(pOutPatchTan_T+L1);
			}
			///////////////////////////
			RegenInfoForLinSupBase(pSupp,*(pSupp->GetSuppCard()));	
			///////
		}
	}
	return 0;
}									

int CMI_LSupp::RegenPatchBased_4(CDrPatch* pPatch)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<SUPPCARD,SUPPCARD>* pStaLCardList = pPatch->GetSuppCardList();
	if(pStaLCardList->IsEmpty())
		return 0;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// SupCard
		SUPPCARD SupCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pPatch->GetSuppList();
		int nBeg = SupCard.nStartIndex;
		int nEnd = nBeg + SupCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenPatchBased_4_DoIt(pPatch,SupCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
	}
	////////////
	return MA_OK;
}

int CMI_LSupp::RegenPatchBased_4_DoIt(CDrPatch* pPatch,SUPPCARD& SupCard,CDListMgr* pList)
{
	////////////////////////
	m_bCurveTan		= FALSE;
	m_bPatchNor		= FALSE;
	m_bReciproDone	= FALSE;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////// SuppList
	if(!pList || pList->IsEmpty())
		return MA_ERROR;
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	int nOut_T			= pPatch->GetOut_T();
	long nOut			= pPatch->GetLongOutPts();
	BOOL bLinSpr		= pPatch->IsLinSpr();
	BOOL bLinSnu		= pPatch->IsLinSnu();
	////////////////////////////////
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	m_PatSubType = pPatch->GetPatSubType(); 
	FillMeshNodesPatch(pPatch,pOut,pOutWts);
	//////////////////////////////////////////// Generate Normals, if Needed
	pWORLD	pOutPatchNor;
	pWORLD	pOutPatchTan_S;
	pWORLD	pOutPatchTan_T;
	m_bPatchNor	= SupCard.bNorPat;
	m_bPatchTan	= SupCard.bTanPat;
	///////////////////////////
	if(m_bPatchNor)
	{
		pOutPatchNor	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshNormalsPatch(pPatch,pOutPatchNor);
		/////////////////////
	}
	if(m_bPatchTan)
	{
		pOutPatchTan_S	= FixMem(nOut);
		pOutPatchTan_T	= FixMem(nOut);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsPatch(pPatch,pOutPatchTan_S,pOutPatchTan_T);
		/////////////////////
	}
	///////////////////////////////////////////////////////// Fixed Skewed direction
	UpdateFixedDirSkewMatrix(SupCard);
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,j;
	int k = -1;
	///////////
	m_pPatch	= pPatch;
	m_SuppProc	= SupCard.SuppProc;
	///////////
	int nOutCreate_S = nOut_S;
	if(bClosed_S)
		nOutCreate_S--;
	int nOutCreate_T = nOut_T;
	if(bClosed_T)
		nOutCreate_T--;
	//////////////////////////
	POSITION pos;
    CDrLinSup* pSupp;
	/////////////////////////////////
	for(j=0; j<nOutCreate_T;j++)
	{
		for(i=0; i<nOutCreate_S;i++)
		{
			k++;
			m_NodePos	= *(pOut+k);
			//////////////////////////////////////////////////////// Duplicate
//			if( IsDuplicated(m_NodePos,m_SuppProc) )
//				continue;
			///////////////////////////////////////////////////////////////////////// pSupp
			pos = pList->FindIndex(k);
			pSupp = (CDrLinSup*)(pList->GetAt(pos));
			m_SuppBased	= pSupp->GetCreateBase();
			///////////////////////////////////////////// init Raw Support Data
			pSupp->InitRawData(m_SuppProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+k);
			///
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+k);
				m_PatchTan_T	= *(pOutPatchTan_T+k);
			}
			///////////////// Set new position
			pSupp->SetNodPos(m_NodePos);
			///////////////////////////
			RegenInfoForLinSupBase(pSupp,*(pSupp->GetSuppCard()));	
			///////
		}		
	}
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return MA_OK;
}

void CMI_LSupp::RegenInfoForLinSupBase(CDrLinSup* pSupp,SUPPCARD supCard)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Node
	LONG  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////////// Convert Support LocalData to WORLD
// 	WORLD LocalPos,CNodPos;
   	WORLD LocalPos;
	pWORLD pDat;
	int i,j,nPts;
	WORLD Nor_Z,vec_W;
	////////////////////////////////////////////////////////// Skewed Support
	C3DMath	Math3D;
	CXForm	XForm;
	/////////////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat; 
	WORLD NewX;
	pWORLD pNewX = &NewX;
	////////////////////////
	Math3D.GetIdentityMATRIX(pMat);
	////////////////////////
	if(supCard.jcType == JC_X_FIXEDDIR)		// Fixed Skewed direction (for Curve and up)
	{
		/////////////////////////////////// Copy  Skew Matrix
		Math3D.BlockCopy((HUGEBLK)(&m_SkewDirMat),(HUGEBLK)(pMat), sizeof(MATRIX) );
	}
	else
	if(supCard.jcType == JC_X_TAN_CURVE)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewXMATRIX(&m_CurveTan, pMat,XF_REPLACE);
	}
	else
	if(supCard.jcType == JC_Z_NOR_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewZ = Normal direction
		XForm.RotateToNewZMATRIX(&m_PatchNor, pMat,XF_REPLACE);
	}
	else
	if(supCard.jcType == JC_I_TAN_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////// Normalize
		Math3D.Normalize(&m_PatchTan_S,&m_PatchTan_S);
		Math3D.Normalize(&m_PatchTan_T,&m_PatchTan_T);
		/////////////////////////////// form Z-Axis
		Math3D.Cross3DPts(&m_PatchTan_S,&m_PatchTan_T,&Nor_Z);
		Math3D.Set3DPts(&vec_W,0.0,0.0,0.0); // homogeneous vector:Ist 3 components
		/////////////////////////////////// Form new Rot Matrix
		Math3D.SetMATRIX(pMat,&m_PatchTan_S,&m_PatchTan_T,&Nor_Z,&vec_W);

	}
	////////////////////////////////////////////////////////// Over All Directions 
	for(i=0;i<6;i++)		
	{
		if
		(
			((pSupp->GetSuppCard())->kode[i] == 0) ||
			(i>0 && (pSupp->GetSuppCard())->SuppProc == SUP_RIGID)
		)
		continue;
		/////////////	// Over Active Directions
		nPts = pSupp->GetnPts(i);
		pDat = pSupp->GetpLoc(i);
		/////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = pDat[j].x;
			LocalPos.y = pDat[j].y;
			LocalPos.z = pDat[j].z;
			/////////////////////////// strip Scale Factor (World Coord)
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
			/////////////////////////////////////////////// Rotate for Skewed Support
			if(supCard.nid_a != "" || m_bCurveTan || m_bPatchNor || m_bPatchTan)
			{
				/////////////////////////////////// Now Rotate
				XForm.Transform(&LocalPos, &LocalPos, pMat);
			}
    		/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
		}
	}
	////////////////////////////////////////// finally
	pSupp->SetSuppCard(supCard);
	//////////////////
	return;
	
} 
/*
int CMI_LSupp::CreateListNodeBased(CDrNode* pObject)
{
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrLinSup* pSupp;
	int index;
	POSITION pos;
	/////////////////
	int nSupp = pObject->GetSuppList()->GetCount();
	//
	for(int i=0; i<nSupp;i++)
	{
		///
		pos		= pObject->GetStaLList()->FindIndex(i); 
		pSupp	= (CDrLinSup*)(pObject->GetSuppList()->GetAt(pos));
		if(!pSupp)
		{
			AfxMessageBox("Internal ERROR\nCMI_LSupp::CreateListCurveBased\n!pSupp");
			return MA_ERROR;
		}
		////
		SUPPCARD supCard	= *(pSupp->GetSuppCard());
		SUPPPROC SuppProc	= supCard.SuppProc;
		UINT SuppBased		= NODE;
		///////////////////////////////////////
		pSupp = CreateNodeBased(SuppProc,supCard,pObject,SuppBased);
		///////
		if(pSupp)
		{
			index = TempList.GetObjectIndex(pSupp); 
			if(index<0) // not yet
				TempList.InsertObject(pSupp);
			/////////// reciprocate
			index = pSupp->GetNodeList()->GetObjectIndex(pObject);
			if(index<0)
				pSupp->GetNodeList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,TRUE);
	}
	////////////////////////////////////////////////////////////// Save
	pObject->GetSuppList()->RemoveAll();
	pObject->GetSuppList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}
/*
int CMI_LSupp::CreateListCurveBased(CDrCurve* pObject)
{
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrLinSup* pSupp;
	int index;
	POSITION pos;
	/////////////////
	int nSupp = pObject->GetSuppList()->GetCount();
	//
	for(int i=0; i<nSupp;i++)
	{
		///
		pos		= pObject->GetStaLList()->FindIndex(i); 
		pSupp	= (CDrLinSup*)(pObject->GetSuppList()->GetAt(pos));
		if(!pSupp)
		{
			AfxMessageBox("Internal ERROR\nCMI_LSupp::CreateListCurveBased\n!pSupp");
			return MA_ERROR;
		}
		////
		SUPPCARD supCard	= *(pSupp->GetSuppCard());
		SUPPPROC SuppProc	= supCard.SuppProc;
		UINT SuppBased		= NODE;
		///////////////////////////
		pSupp = CreateCurveBased(SuppProc,supCard,pObject,SuppBased);
		///////
		if(pSupp)
		{
			index = TempList.GetObjectIndex(pSupp); 
			if(index<0) // not yet
				TempList.InsertObject(pSupp);
			/////////// reciprocate
			index = pSupp->GetCurveList()->GetObjectIndex(pObject);
			if(index<0)
				pSupp->GetCurveList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,TRUE);
	}		
	////////////////////////////////////////////////////////////// Save
	pObject->GetSuppList()->RemoveAll();
	pObject->GetSuppList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}

int CMI_LSupp::CreateListPatchBased(CDrPatch* pObject)
{
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrLinSup* pSupp;
	int index;
	POSITION pos;
	/////////////////
	int nSupp = pObject->GetSuppList()->GetCount();
	//
	for(int i=0; i<nSupp;i++)
	{
		///
		pos		= pObject->GetStaLList()->FindIndex(i); 
		pSupp	= (CDrLinSup*)(pObject->GetSuppList()->GetAt(pos));
		if(!pSupp)
		{
			AfxMessageBox("Internal ERROR\nCMI_LSupp::CreateListCurveBased\n!pSupp");
			return MA_ERROR;
		}
		////
		SUPPCARD supCard	= *(pSupp->GetSuppCard());
		SUPPPROC SuppProc	= supCard.SuppProc;
		UINT SuppBased		= NODE;
		///////////////////////////
		if(pObject->GetPatSubType() == PS_QUADRILAT)
			pSupp = CreatePatchBased_4(SuppProc,supCard,pObject,SuppBased);
		else
		if(pObject->GetPatSubType() == PS_TRIANGLE)
			pSupp = CreatePatchBased_3(SuppProc,supCard,pObject,SuppBased);
		else
			return -1;
		///////
		if(pSupp)
		{
			index = TempList.GetObjectIndex(pSupp); 
			if(index<0) // not yet
				TempList.InsertObject(pSupp);
			/////////// reciprocate
			index = pSupp->GetNodeList()->GetObjectIndex(pObject);
			if(index<0)
				pSupp->GetCurveList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,TRUE);
	}		
	////////////////////////////////////////////////////////////// Save
	pObject->GetSuppList()->RemoveAll();
	pObject->GetSuppList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}
*/
void CMI_LSupp::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_LSupp:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_LSupp:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


