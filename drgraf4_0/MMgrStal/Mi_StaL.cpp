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
///////////////////// Labels
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// StaticLoad
#include "Def_Supp.h"	// for Joint Coords
#include "Def_StaL.h"
#include "DrStatic.h"
///////////////////// specials
#include "Def_Spec.h"
#include "HitNet.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
/////////////////////
#include "MI_StaL.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_StaL,CMI_GangS,1)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////
#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
/////////////////////////////////////////////////////////////////////////////
CMI_StaL::CMI_StaL()
{
	m_bCurveTan	= FALSE;
	m_bPatchNor	= FALSE;
	m_bPatchTan	= FALSE;
	////////////////////
	m_pOutTr	= NULL;
	m_pOutRo	= NULL;
}

CMI_StaL::~CMI_StaL()
{
	if(m_pOutTr)
		FreeMem(m_pOutTr);
	if(m_pOutRo)
		FreeMem(m_pOutRo);

}	

//////////////////////////////////////////////////////////////////////////// Poting Helper
int CMI_StaL::CreatePatchBased_3(CDrPatch* pPatch,CList<STALCARD,STALCARD>* pCardList)
{
	UINT StaLBased	= PATCH;
	CList<STALCARD,STALCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	long nOut			= pPatch->GetLongOutPts();
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
		STALCARD StLCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_StaLCard	= StLCard; 
		m_StaLBased	= PATCH;
		m_pPatch	= pPatch;
		m_StaLProc	= StLCard.StaLProc;
		//////////////////////////////////////////// Generate, if NonUniform
		BOOL	bT = FALSE;
		BOOL	bR = FALSE;
		m_bNonUniform	= !(StLCard.bUniform);
		if(m_bNonUniform)
			//////////////////
			FillUp_Val_Pat_3(pPatch,StLCard,&bT,&bR);
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldStatic(StLCard, pPatch->GetStaLList());
		if(nResult<0)
			return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(StLCard);
		//////////////////////////////////////////////////////// Loop Over All Triangles
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
		int nStartCount = pPatch->GetStaLList()->GetCount();
		m_StaLCard.nStartIndex = nStartCount;
		/////////////////////////////////////////////////////////////////// LOOP: Triangle List
		int index = -1;
		CDrStatic* pAdd;
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
									StLCard,iOutGlo,jOutGlo,bT,bR);
			else
			if(nType == 2)
				pAdd = TRIANGLE_2(pOut,pOutPatchNor,pOutPatchTan_S,pOutPatchTan_T,
									StLCard,iOutGlo,jOutGlo,bT,bR);
			else
			{
				//////////////////
				AfxMessageBox("CMI_StaL::CreatePatchBased_3\nnType !==1 or 2");
				return MA_ERROR;
			}
			///////////////// Set Quick Search Info
			pAdd->SetTriangle(TRUE);
			pAdd->SetCreate_i(index);
			pAdd->SetCreateBase(m_StaLBased);
		}										///////////////////////////// end LIST
		////////////////////////////////////////// SAVE StaLCard
		m_StaLCard.nTotal = pPatch->GetStaLList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_StaLCard);
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
	 
int CMI_StaL::FillUp_Val_Pat_3(CDrPatch* pPatch,STALCARD& StLCard,BOOL* bT, BOOL* bR)
{
	CDrPatch* pPatchT = GetNonUniformLoadPatch(StLCard.cid_ParentT);
	CDrPatch* pPatchR = GetNonUniformLoadPatch(StLCard.cid_ParentR);
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////////////// 
	double	Fx,Fy,Fz,Mx,My,Mz;
	int		nOut_S,nOut_T;
	long	nOut,nOutTr,nOutRo;
	pWORLD	pOutTr,pOutRo;
	pDOUBLE	pOutWtsTr,pOutWtsRo;
	*bT = FALSE;
	*bR = FALSE;
	///////////////
	BOOL bClosed_S	= pPatch->IsClosed_S();
	BOOL bClosed_T	= pPatch->IsClosed_T();
	nOut_S			= pPatch->GetOut_S();
	nOut_T			= pPatch->GetOut_T();
	nOut			= pPatch->GetLongOutPts();
	///////////////////////////////////////////////// Kode
	int i;
	//////
	for(i=0;i<3;i++)
	{
		if(StLCard.kode[i])
			*bT = TRUE;
	}
	for(i=3;i<6;i++)
	{
		if(StLCard.kode[i])
			*bR = TRUE;
	}
	///////////////////////////////////
	if(*bT)
	{
		nOutTr	= pPatchT->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutTr)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Pat3\nnOut != nOutTr");
			return -1;
		}
		////////////////////////////// Memory
		pOutTr	= FixMem(nOutTr);
		pOutWtsTr	= FixMemD(nOutTr);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesPatch(pPatchT,pOutTr,pOutWtsTr);
		//////////////////
	}
	///////////////////////////////////
	if(*bR)
	{
		nOutRo	= pPatchR->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutRo)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Pat\nnOut != nOutRo");
			return -1;
		}
		////////////////////////////// Memory
		pOutRo	= FixMem(nOutRo);
		pOutWtsRo	= FixMemD(nOutRo);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesPatch(pPatchR,pOutRo,pOutWtsRo);
		//////////////////
	}
	//////////////////////////////////////////////////////// Max for Scaling Drawing
	for(i=0;i<6;i++)
		m_dMax[i] = 0.0;
	//////////////////////////////////////////////////////// Scale & GetMax
	for(i=0; i<nOut;i++)
	{
		////
		Fx = Fy = Fz = Mx = My = Mz = 0.0;
		////////////////////////////////// Tran
		if(*bT)
		{
			Fx				= ((double)((pOutTr+i)->x))/dWorldBase*dMapFactor;
			(pOutTr+i)->x	= Fx;
			if(fabs(Fx)>m_dMax[0])
				m_dMax[0] = fabs(Fx);
			/////////////////////////
			Fy				= ((double)((pOutTr+i)->y))/dWorldBase*dMapFactor;
			(pOutTr+i)->y	= Fy;
			if(fabs(Fy)>m_dMax[1])
				m_dMax[1] = fabs(Fy);
			/////////////////////////
			Fz	= ((double)((pOutTr+i)->z))/dWorldBase*dMapFactor;
			(pOutTr+i)->z	= Fz;
			if(fabs(Fz)>m_dMax[2])
				m_dMax[2] = fabs(Fz);
			/////////////////////////
			}
		if(*bR)
		{
			Mx	= ((double)((pOutRo+i)->x))/dWorldBase*dMapFactor;
			(pOutRo+i)->x	= Mx;
			if(fabs(Mx)>m_dMax[3])
				m_dMax[3] = fabs(Mx);
			/////////////////////////
			My	= ((double)((pOutRo+i)->y))/dWorldBase*dMapFactor;
			(pOutRo+i)->y	= My;
			if(fabs(My)>m_dMax[4])
				m_dMax[4] = fabs(My);
			/////////////////////////
			Mz	= ((double)((pOutRo+i)->z))/dWorldBase*dMapFactor;
			(pOutRo+i)->z	= Mz;
			if(fabs(Mz)>m_dMax[5])
				m_dMax[5] = fabs(Mz);
			/////////////////////////
		}
	}
	//////////////////////////// Memory
	if(*bT)
	{
//		FreeMem(pOutTr);	// not yet
		m_pOutTr = pOutTr;
		FreeMemD(pOutWtsTr);
	}
	if(*bR)
	{
//		FreeMem(pOutRo);	// not yet
		m_pOutRo = pOutRo;
		FreeMemD(pOutWtsRo);
	}
	/////////
	return 0;
}	

CDrStatic*  CMI_StaL::TRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,
				pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
				STALCARD& StLCard,int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR)
{ 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////
	CDrStatic* pAdd = NULL;
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
			if( IsDuplicated(m_NodePos,m_StaLProc) )
				continue;
			//////////////////////////// new
			pAdd = new CDrStatic;
			////////////////////////////
			pAdd->SetNodPos(m_NodePos);
			///////////////////////////////////////////// Update StaLCard.value[6],NonUniform
			if(m_bNonUniform)
			{
				if(bT)
				{
					m_StaLCard.value[0] = (m_pOutTr+L1)->x;
					m_StaLCard.value[1] = (m_pOutTr+L1)->y;
					m_StaLCard.value[2] = (m_pOutTr+L1)->z;
				}
				if(bR)
				{
					m_StaLCard.value[3] = (m_pOutRo+L1)->x;
					m_StaLCard.value[4] = (m_pOutRo+L1)->y;
					m_StaLCard.value[5] = (m_pOutRo+L1)->z;
				}
			}
			/////////////////////////////////////////////
			(pAdd->GetStaLCard())->StaLProc	= m_StaLProc;
			///////////////////////////////////////////// init Raw Static Data
			pAdd->InitRawData(m_StaLProc);
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
			SetInfoForStaticBase(pAdd,m_StaLCard);	
			////////////////////////////////////// save Private
			m_pPatch->GetStaLList()->InsertObject(pAdd);		
			///////	
		}
	}
	return pAdd;
}									

CDrStatic*  CMI_StaL::TRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,
				pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
				STALCARD& StLCard,int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR)
{ 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////
	CDrStatic* pAdd = NULL;
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
			if( IsDuplicated(m_NodePos,m_StaLProc) )
				continue;
			///////////////////// Add
			pAdd = new CDrStatic;
			////////////////////////////
			pAdd->SetNodPos(m_NodePos);
			///////////////////////////////////////////// Update StaLCard.value[6],NonUniform
			if(m_bNonUniform)
			{
				if(bT)
				{
					m_StaLCard.value[0] = (m_pOutTr+L1)->x;
					m_StaLCard.value[1] = (m_pOutTr+L1)->y;
					m_StaLCard.value[2] = (m_pOutTr+L1)->z;
				}
				if(bR)
				{
					m_StaLCard.value[3] = (m_pOutRo+L1)->x;
					m_StaLCard.value[4] = (m_pOutRo+L1)->y;
					m_StaLCard.value[5] = (m_pOutRo+L1)->z;
				}
			}
			/////////////////////////////////////////////
			(pAdd->GetStaLCard())->StaLProc	= m_StaLProc;
			///////////////////////////////////////////// init Raw Support Data
			pAdd->InitRawData(m_StaLProc);
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
			SetInfoForStaticBase(pAdd,m_StaLCard);	
			////////////////////////////////////// save Private
			m_pPatch->GetStaLList()->InsertObject(pAdd);		
			///////	
		}
	}
	return pAdd;
}									

int CMI_StaL::UpdateFixedDirSkewMatrix(STALCARD& StLCard)
{
	C3DMath	Math3D;
	CXForm	XForm;
	///////////////////////////////////////////////////////// Fixed Skewed direction
	if(StLCard.jcType == JC_X_FIXEDDIR)		
	{
		WORLD	NewX;
		pWORLD	pNewX = &NewX;
		//////////////////////
		Math3D.Set3DPts(pNewX, StLCard.SkewDir.x, StLCard.SkewDir.y, StLCard.SkewDir.z);
		/////////////////////////////////// Rotate to NewX
		XForm.RotateToNewXMATRIX(pNewX, &m_SkewDirMat,XF_REPLACE);
	}
	////////////
	return MA_OK;
}

BOOL CMI_StaL::IsPatchTangentNeeded(CList<STALCARD,STALCARD>* pStaLCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pStaLCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		STALCARD StLCard = pStaLCardList->GetNext(posI);
		if( StLCard.jcType == JC_I_TAN_PATCH)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

int CMI_StaL::CreatePatchBased_4(CDrPatch* pPatch,CList<STALCARD,STALCARD>* pCardList)
{
	UINT StaLBased	= PATCH;
	CList<STALCARD,STALCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
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
		STALCARD StLCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_StaLCard	= StLCard; 
		m_StaLBased	= PATCH;
		m_pPatch	= pPatch;
		m_StaLProc	= StLCard.StaLProc;
		//////////////////////////////////////////// Generate, if NonUniform
		m_bNonUniform	= !(StLCard.bUniform);
		if(m_bNonUniform)
			//////////////////
			FillUp_ValList_Pat_4(pPatch,StLCard);
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldStatic(StLCard, pPatch->GetStaLList());
		if(nResult<0)
			return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(StLCard);
		///////////////////////////////
		int nStartCount		= pPatch->GetStaLList()->GetCount();
		m_StaLCard.nStartIndex = nStartCount;
		//////////////////////////////////////////////////// Loop Over MeshPts
		LoopOver_Patch_4_Pts(pPatch,StLCard,pOut,
			pOutPatchTan_S,pOutPatchTan_T,pOutPatchNor,nOut);
		////////////////////////////////////////// SAVE StaLCard
		m_StaLCard.nTotal = pPatch->GetStaLList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_StaLCard);
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

int CMI_StaL::LoopOver_Patch_4_Pts(CDrPatch* pPatch,STALCARD& StLCard,
					pWORLD pOut,pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
					pWORLD pOutPatchNor,int nOut)
{
	m_pPatch	= pPatch;
	m_StaLCard	= StLCard;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,j,m;
	int k		= -1;
	int nVal	= -1;
	////////////////////////////
	BOOL bClosed		= pPatch->IsClosed_S();
	CDListMgr* pList	= pPatch->GetStaLList();
	////////////////////////////////
	m_StaLBased			= PATCH;
	m_StaLProc			= StLCard.StaLProc;
	m_StaLCard			= StLCard;
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
	int nStartCount = pPatch->GetStaLList()->GetCount();
	m_StaLCard.nStartIndex = nStartCount;
	//////////////////////////////////////////////////////// 
	int nNodPossBeg_S	= StLCard.nNodPos_S_Beg;
	int nNodPossEnd_S	= StLCard.nNodPos_S_End;
	int nNodPossBeg_T	= StLCard.nNodPos_T_Beg;
	int nNodPossEnd_T	= StLCard.nNodPos_T_End;
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
			if( IsDuplicated(m_NodePos,m_StaLProc) )
				continue;
			///////////////////////////////////////////////////////////////////////// Add
			CDrStatic* pAdd = new CDrStatic;
			///////////////// Set Quick Search Info
			pAdd->SetCreate_i(i);
			pAdd->SetCreate_j(j);
			pAdd->SetCreateBase(m_StaLBased);
			pAdd->SetNodPos(m_NodePos);
			///////////////////////////////////////////// Update StaLCard.value[6],NonUniform
			if(!(StLCard.bUniform))
			{
				for(m=0;m<6;m++)
				{
					nVal++;
					POSITION pos;
					///////
					pos = m_ValueList.FindIndex(nVal);
					m_StaLCard.value[m] = m_ValueList.GetAt(pos);
				}
			}
			///////////////////////////////////////////////////////////////////
			(pAdd->GetStaLCard())->StaLProc	= m_StaLProc;
			///////////////////////////////////////////// init Raw Support Data
			pAdd->InitRawData(m_StaLProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+k);
			if(m_bPatchTan)
			{
				m_PatchTan_S	= *(pOutPatchTan_S+k);
				m_PatchTan_T	= *(pOutPatchTan_T+k);
			}
			///////////////////////////
			SetInfoForStaticBase(pAdd,m_StaLCard);	
			////////////////////////////////////// save Private
			pPatch->GetStaLList()->InsertObject(pAdd);		
			///////	
		}		
	}
	/////////////////////
    return MA_OK;
}

CDrPatch* CMI_StaL::GetNonUniformLoadPatch(CString& id)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pPatList		= pObjectMgr->GetObjectList(PATCH);
	////////////////////////////////
	if(id !="")
	{
		int index = pPatList->GetObjectIndex(PATCH, id);
		if(index>=0)
			return (CDrPatch*)pPatList->GetObject(index);
	}
	////////
	return (CDrPatch*)NULL;
}

int CMI_StaL::FillUp_ValList_Pat_4(CDrPatch* pPatch,STALCARD& StLCard)
{
	CDrPatch* pPatchT = GetNonUniformLoadPatch(StLCard.cid_ParentT);
	CDrPatch* pPatchR = GetNonUniformLoadPatch(StLCard.cid_ParentR);
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////////////// 
	double	Fx,Fy,Fz,Mx,My,Mz;
	int		nOut_S,nOut_T;
	long	nOut,nOutTr,nOutRo;
	BOOL	bT = FALSE;
	BOOL	bR = FALSE;
	pWORLD	pOutTr,pOutRo;
	pDOUBLE	pOutWtsTr,pOutWtsRo;
	///////////////
	BOOL bClosed_S	= pPatch->IsClosed_S();
	BOOL bClosed_T	= pPatch->IsClosed_T();
	nOut_S			= pPatch->GetOut_S();
	nOut_T			= pPatch->GetOut_T();
	nOut			= pPatch->GetLongOutPts();
	//////////////////////////////////
	m_ValueList.RemoveAll();
	///////////////////////////////////////////////// Kode
	int i,j;
	//////
	for(i=0;i<3;i++)
	{
		if(StLCard.kode[i])
			bT = TRUE;
	}
	for(i=3;i<6;i++)
	{
		if(StLCard.kode[i])
			bR = TRUE;
	}
	///////////////////////////////////
	if(bT)
	{
		nOutTr	= pPatchT->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutTr)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Pat\nnOut != nOutTr");
			return -1;
		}
		////////////////////////////// Memory
		pOutTr		= FixMem(nOutTr);
		pOutWtsTr	= FixMemD(nOutTr);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesPatch(pPatchT,pOutTr,pOutWtsTr);
		//////////////////
	}
	///////////////////////////////////
	if(bR)
	{
		nOutRo	= pPatchR->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutRo)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Pat\nnOut != nOutRo");
			return -1;
		}
		////////////////////////////// Memory
		pOutRo		= FixMem(nOutRo);
		pOutWtsRo	= FixMemD(nOutRo);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesPatch(pPatchR,pOutRo,pOutWtsRo);
		//////////////////
	}
	//////////////////////////////////////////////////////// Max for Scaling Drawing
	for(i=0;i<6;i++)
		m_dMax[i] = 0.0;
	//////////////////////////////////////
	int nOutCreate_S = nOut_S;
	if(bClosed_S)
		nOutCreate_S--;
	int nOutCreate_T = nOut_T;
	if(bClosed_T)
		nOutCreate_T--;
	/////////////////////
	m_ValueList.RemoveAll();
	///////////
	int k = -1;
	//////////////////////////////////////////////////////// Fillup
	for(j=0; j<nOutCreate_T;j++)
	{
		for(i=0; i<nOutCreate_S;i++)
		{
			k++;
			////
			Fx = Fy = Fz = Mx = My = Mz = 0.0;
			////////////////////////////////// Tran
			if(bT)
			{
				Fx	= ((double)((pOutTr+k)->x))/dWorldBase*dMapFactor;
				if(fabs(Fx)>m_dMax[0])
					m_dMax[0] = fabs(Fx);
				/////////////////////////
				Fy	= ((double)((pOutTr+k)->y))/dWorldBase*dMapFactor;
				if(fabs(Fy)>m_dMax[1])
					m_dMax[1] = fabs(Fy);
				/////////////////////////
				Fz	= ((double)((pOutTr+k)->z))/dWorldBase*dMapFactor;
				if(fabs(Fz)>m_dMax[2])
					m_dMax[2] = fabs(Fz);
				/////////////////////////
			}
			if(bR)
			{
				Mx	= ((double)((pOutRo+k)->x))/dWorldBase*dMapFactor;
				if(fabs(Mx)>m_dMax[3])
					m_dMax[3] = fabs(Mx);
				/////////////////////////
				My	= ((double)((pOutRo+k)->y))/dWorldBase*dMapFactor;
				if(fabs(My)>m_dMax[4])
					m_dMax[4] = fabs(My);
				/////////////////////////
				Mz	= ((double)((pOutRo+k)->z))/dWorldBase*dMapFactor;
				if(fabs(Mz)>m_dMax[5])
					m_dMax[5] = fabs(Mz);
				/////////////////////////
			}
			////////////////////////
			m_ValueList.AddTail(Fx);
			m_ValueList.AddTail(Fy);
			m_ValueList.AddTail(Fz);
			m_ValueList.AddTail(Mx);
			m_ValueList.AddTail(My);
			m_ValueList.AddTail(Mz);
			////////////////////////
		}
	}
	//////////////////////////// Memory
	if(bT)
	{
		FreeMem(pOutTr);
		FreeMemD(pOutWtsTr);
	}
	if(bR)
	{
		FreeMem(pOutRo);
		FreeMemD(pOutWtsRo);
	}
	/////////
	return 0;
}	

BOOL CMI_StaL::IsTangentNeeded(CList<STALCARD,STALCARD>* pStaLCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pStaLCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		STALCARD StLCard = pStaLCardList->GetNext(posI);
		if( StLCard.jcType == JC_X_TAN_CURVE)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

BOOL CMI_StaL::IsNormalNeeded(CList<STALCARD,STALCARD>* pStaLCardList)
{
	BOOL bNeeded = FALSE;
	for (POSITION posI = pStaLCardList->GetHeadPosition( );posI !=NULL;)
	{
		////
		STALCARD StLCard = pStaLCardList->GetNext(posI);
		if( StLCard.jcType == JC_Z_NOR_PATCH)
		{
			bNeeded	= TRUE;
			break;
		}		
	}
	////////
	return bNeeded;
}

int CMI_StaL::LoopOver_CurvePts(CDrCurve* pCurve,STALCARD& StLCard,
							pWORLD pOut,pWORLD pOutCurveTan,int nOut)
{
	m_pCurve	= pCurve;
	m_StaLCard	= StLCard;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,k;
	int nVal = -1;
	////////////////////////////
	BOOL bClosed		= pCurve->IsClosed_S();
	CDListMgr* pList	= pCurve->GetStaLList();
	////////////////////////////////
	m_StaLBased			= CURVE;
	m_StaLProc			= StLCard.StaLProc;
	//////////////////////////////////////////////////////// Closed?
	int nOutCreate		= nOut;
	if(bClosed)
		nOutCreate--;
	//////////////////////////////////////////////////////// 
	int nNodPossBeg		= StLCard.nNodPos_S_Beg;
	int nNodPossEnd		= StLCard.nNodPos_S_End;
	//////////////////////////////////////////////
	for(i=nNodPossBeg;i<nNodPossEnd;i++)	// necessary for Curve_Profile
											// for single Curve:	nNodPossBeg=0
											//						nNodPossEnd=nMaxBezSeg
	{
		/////////////////////////
		m_NodePos	= *(pOut+i);
		/////////////////////////////// Add
		CDrStatic* pAdd = new CDrStatic;
		///////////////// Set Quick Search Info
		pAdd->SetCreate_i(i);
		pAdd->SetCreateBase(m_StaLBased);
		pAdd->SetNodPos(m_NodePos);
		///////////////////////////////////////////// Update StaLCard.value[6],NonUniform
		if(!(StLCard.bUniform))
		{
			for(k=0;k<6;k++)
			{
				nVal++;
				POSITION pos;
				///////
				pos = m_ValueList.FindIndex(nVal);
				m_StaLCard.value[k] = m_ValueList.GetAt(pos);
			}
		}
		///////////////////////////////////////////////////////////////////
		(pAdd->GetStaLCard())->StaLProc	= m_StaLProc;
		///////////////////////////////////////////// init Raw Support Data
		pAdd->InitRawData(m_StaLProc);
		/////////////////////
		if(m_bCurveTan)
			m_CurveTan	= *(pOutCurveTan+i);
		///////////////////////////
		SetInfoForStaticBase(pAdd,m_StaLCard);	
		////////////////////////////////////// save Private
		pCurve->GetStaLList()->InsertObject(pAdd);		
	}
	//////////////////
	return MA_OK;
}

CDrCurve* CMI_StaL::GetNonUniformLoadCurve(CString& id)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pCurList		= pObjectMgr->GetObjectList(CURVE);
	////////////////////////////////
	if(id !="")
	{
		int index = pCurList->GetObjectIndex(CURVE, id);
		if(index>=0)
			return (CDrCurve*)pCurList->GetObject(index);
	}
	////////
	return (CDrCurve*)NULL;
}

int CMI_StaL::CreateCurveBased(CDrCurve* pCurve,CList<STALCARD,STALCARD>* pCardList)
{
	UINT StaLBased	= CURVE;
	CList<STALCARD,STALCARD> TempCardList;
	TempCardList.RemoveAll();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	//////////////////////////////////////////// Output memory
	int nOut		= pCurve->GetLongOutPts();
	BOOL bClosed	= pCurve->IsClosed_S();
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
		STALCARD StLCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_StaLCard	= StLCard; 
		m_StaLBased	= CURVE;
		m_pCurve	= pCurve;
		m_StaLProc	= StLCard.StaLProc;
		//////////////////////////////////////////// Generate, if NonUniform
		m_bNonUniform	= !(StLCard.bUniform);
		if(m_bNonUniform)
			//////////////////
			FillUp_ValList_Cur(pCurve,StLCard);
		///////////////////////////////////////////////////////////////// Replace, if needed
		int nResult = RemoveOldStatic(StLCard, pCurve->GetStaLList());
		if(nResult<0)
			return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(StLCard);
		////////////////////////////////////////////////////
		int nStartCount		= pCurve->GetStaLList()->GetCount();
		m_StaLCard.nStartIndex = nStartCount;
		//////////////////////////////////////////////////// Loop Over MeshPts
		LoopOver_CurvePts(pCurve,StLCard,pOut,pOutCurveTan,nOut);
		////////////////////////////////////////// SAVE StaLCard
		m_StaLCard.nTotal = pCurve->GetStaLList()->GetCount() - nStartCount; 
		//// replace
		TempCardList.AddTail(m_StaLCard);
	}
	/////////////////////////////////////// Update StaLCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(m_bCurveTan)
		FreeMem(pOutCurveTan);
	/////////////////////
    return MA_OK;
}
	 
int CMI_StaL::FillUp_ValList_Cur(CDrCurve* pCurve,STALCARD& StLCard)
{
	CDrCurve* pCurveT = GetNonUniformLoadCurve(StLCard.cid_ParentT);
	CDrCurve* pCurveR = GetNonUniformLoadCurve(StLCard.cid_ParentR);
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////////////// 
	double	Fx,Fy,Fz,Mx,My,Mz;
	int		nOut,nOutT,nOutR;
	BOOL	bT = FALSE;
	BOOL	bR = FALSE;
	pWORLD	pOutT,pOutR;
	pDOUBLE	pOutWtsT,pOutWtsR;
	///////////////
	BOOL bClosed	= pCurve->IsClosed_S();
	nOut			= pCurve->GetLongOutPts();
	//////////////////////////////////
	m_ValueList.RemoveAll();
	///////////////////////////////////////////////// Kode
	int i;
	//////
	for(i=0;i<3;i++)
	{
		if(StLCard.kode[i])
			bT = TRUE;
	}
	for(i=3;i<6;i++)
	{
		if(StLCard.kode[i])
			bR = TRUE;
	}
	///////////////////////////////////
	if(bT)
	{
		nOutT	= pCurveT->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutT)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Cur\nnOut != nOutT");
			return -1;
		}
		////////////////////////////// Memory
		pOutT		= FixMem(nOutT);
		pOutWtsT	= FixMemD(nOutT);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesCurve(pCurveT,pOutT,pOutWtsT,nOutT);
		//////////////////
	}
	///////////////////////////////////
	if(bR)
	{
		nOutR	= pCurveR->GetLongOutPts();
		/////////////////////////////////// Compatibility
		if(nOut != nOutR)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::FillUp_ValList_Cur\nnOut != nOutR");
			return -1;
		}
		////////////////////////////// Memory
		pOutR		= FixMem(nOutR);
		pOutWtsR	= FixMemD(nOutR);
		//////////////////////////////////////////// Now Generate
		m_bBack = FALSE;
		FillMeshNodesCurve(pCurveR,pOutR,pOutWtsR,nOutR);
		//////////////////
	}
	//////////////////////////////////////////////////////// Max for Scaling Drawing
	for(i=0;i<6;i++)
		m_dMax[i] = 0.0;
	//////////////////////////////////////////////////////// Fillup
	int nOutCreate = nOut;
	if(bClosed)
		nOutCreate--;
	/////////////////////
	m_ValueList.RemoveAll();
	////////////////////////
	for(i=0; i<nOutCreate;i++)
	{
		Fx = Fy = Fz = Mx = My = Mz = 0.0;
		////////////////////////////////// Tran
		if(bT)
		{
			Fx	= ((double)((pOutT+i)->x))/dWorldBase*dMapFactor;
			if(fabs(Fx)>m_dMax[0])
				m_dMax[0] = fabs(Fx);
			/////////////////////////
			Fy	= ((double)((pOutT+i)->y))/dWorldBase*dMapFactor;
			if(fabs(Fy)>m_dMax[1])
				m_dMax[1] = fabs(Fy);
			/////////////////////////
			Fz	= ((double)((pOutT+i)->z))/dWorldBase*dMapFactor;
			if(fabs(Fz)>m_dMax[2])
				m_dMax[2] = fabs(Fz);
			/////////////////////////
		}
		if(bR)
		{
			Mx	= ((double)((pOutR+i)->x))/dWorldBase*dMapFactor;
			if(fabs(Mx)>m_dMax[3])
				m_dMax[3] = fabs(Mx);
			/////////////////////////
			My	= ((double)((pOutR+i)->y))/dWorldBase*dMapFactor;
			if(fabs(My)>m_dMax[4])
				m_dMax[4] = fabs(My);
			/////////////////////////
			Mz	= ((double)((pOutR+i)->z))/dWorldBase*dMapFactor;
			if(fabs(Mz)>m_dMax[5])
				m_dMax[5] = fabs(Mz);
			/////////////////////////
		}
		////////////////////////
		m_ValueList.AddTail(Fx);
		m_ValueList.AddTail(Fy);
		m_ValueList.AddTail(Fz);
		m_ValueList.AddTail(Mx);
		m_ValueList.AddTail(My);
		m_ValueList.AddTail(Mz);
		////////////////////////
	}
	//////////////////////////// Memory
	if(bT)
	{
		FreeMem(pOutT);
		FreeMemD(pOutWtsT);
	}
	if(bR)
	{
		FreeMem(pOutR);
		FreeMemD(pOutWtsR);
	}
	/////////
	return 0;
}	

int CMI_StaL::CreateNodeBased(CDrNode* pNode,CList<STALCARD,STALCARD>* pCardList)
{
	UINT StaLBased	= NODE;
	CList<STALCARD,STALCARD> TempCardList;
	TempCardList.RemoveAll();
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	CDrStatic* pAdd;
	CString strCurORPat;
	///////////////////////////////////////////////////////////////////////////
	// Remove or Destroy Old One similar to Current LoadID
	////////////////////////////////////////
	CDListMgr* pList = pNode->GetStaLList();
	///////////////////////////////////////////////////////////////////// LOOP:StaLCardList
	for (POSITION posI = pCardList->GetHeadPosition( );posI !=NULL;)
	{
		STALCARD StLCard = pCardList->GetNext(posI);
		///////////////////////////////
		m_StaLCard	= StLCard; 
		m_StaLBased	= NODE;
		m_pNode		= pNode;
		m_StaLProc	= StLCard.StaLProc;
		//////////////////////////////////////////////
		int nResult = RemoveOldStatic(StLCard, pList);
		if(nResult<0)
			return MA_ERROR;
		///////////////////////////////////////////////////////// Fixed Skewed direction
		if(StLCard.jcType == JC_X_FIXEDDIR)		
			UpdateFixedDirSkewMatrix(StLCard);
		///////////////////////////////////////////////////////// Curve Tangential
		else
		if( StLCard.jcType == JC_X_TAN_CURVE)
		{
			m_bCurveTan	= TRUE;
			strCurORPat = StLCard.ID_CP;
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
		if( StLCard.jcType == JC_Z_NOR_PATCH)
		{		
			m_bPatchNor		= TRUE;				
//			strCurORPat = StLCard.ID_CP;
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
		if( StLCard.jcType == JC_I_TAN_PATCH)
		{		
			m_bPatchTan		= TRUE;				
//			strCurORPat = StLCard.ID_CP;
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
		/////////////////////
		m_bNonUniform	= !(StLCard.bUniform);
		m_StaLCard	= StLCard;
		m_StaLBased	= StaLBased;
		m_StaLProc	= StLCard.StaLProc;
		m_pNode		= pNode;
		m_NodePos	= *(m_pNode->GetLocalPos());
		//////////////////////////////////////////////////////// Duplicate
		if( IsDuplicated(m_NodePos,m_StaLProc) )
			return MA_OK;
		////////////////////////////////////////////////////
		int nStartCount = pNode->GetStaLList()->GetCount();
		m_StaLCard.nStartIndex = nStartCount;
		///////////////////////////////////////////////////////////////////
		pAdd 	= new CDrStatic;
		///////////////// Set Quick Search Info
		CDListMgr* pNodeList	= pObjectMgr->GetObjectList(NODE);
		int index = pNodeList->GetObjectIndex(pNode); 
		pAdd->SetCreate_i(index);
		pAdd->SetCreateBase(m_StaLBased);
		pAdd->SetNodPos(m_NodePos);
		////////////
		(pAdd->GetStaLCard())->StaLProc	= m_StaLProc;
		///////////////////////////////////////////// init Raw Static Data
		pAdd->InitRawData(m_StaLProc);
		///////////////////////////////////////
		SetInfoForStaticBase(pAdd,m_StaLCard);	
		////////////////////////////////////// save Private
		pNode->GetStaLList()->InsertObject(pAdd);		
		////////////////////////////////////////// SAVE StaLCard
		m_StaLCard.nTotal = pNode->GetStaLList()->GetCount() - nStartCount;  
		TempCardList.AddTail(m_StaLCard);
	}
	/////////////////////////////////////// Update StaLCard with newInfo
	pCardList->RemoveAll();
	pCardList->AddTail(&TempCardList);
	TempCardList.RemoveAll();
	/////////////////////
    return MA_OK;
}

BOOL CMI_StaL::IsDuplicated(WORLD& CurrentNodPos, STALPROC CurrentStaLProc)
{
	/////////////////////////////////////////////////////////
	// Has to be same Coords, same StaLProc & same LoadID
	/////////////////////////////////////////////////////////
	C3DMath		Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CDListMgr*	pList;
	WORLD		NodPos;
	/////////////////////////////////////////////////////////
	switch(m_StaLBased)
	{
		case NODE:
			pList = m_pNode->GetStaLList();
			////////
			break;
			
		case CURVE:
			pList = m_pCurve->GetStaLList();
			////////
			break;

		case PATCH:
			pList = m_pPatch->GetStaLList();
			////////
			break;

		case SOLID:
			pList = m_pSolid->GetStaLList();
			////////
			break;

		default:
			return TRUE;
	}
	////////////////////////////////////////////
	CString Currentload_id = m_StaLCard.load_id;
	//////////////////////////////////////////// Check
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrStatic* pStaL 		= (CDrStatic*)pList->GetNextObject(pos);
		CString  load_id_Dup	= (pStaL->GetStaLCard())->load_id;
		////
		if( ((pStaL->GetStaLCard())->StaLProc != CurrentStaLProc) ||
			(load_id_Dup != Currentload_id)								)
			continue;
		///////////////////////
		NodPos = *(pStaL->GetNodPos());
		///////////////////////////////
		if(Math3D.AreSame_WORLD(&NodPos,&CurrentNodPos,pHitNet->GetDblRatio()))
			return TRUE;
	}
	////////////////////////
	return FALSE;
}

void CMI_StaL::SetStaticID(CDrStatic* pStatic,char* buf,int jStart)
{
	int j = jStart;
	int ic,jc,kc;
	/////////////
	j += sprintf(buf+j,"%s",pStatic->GetObjectID());
	//////////////////////////
	switch(pStatic->GetCreateBase())
	{
		case NODE:
		///////////////////////////////////////////////// 
//			j += sprintf(buf+j,"N_%s",m_pNode->GetObjectID());
			break;
		case CURVE:
		///////////////////////////////////////////////// 
			ic = pStatic->GetCreate_i();
//			j += sprintf(buf+j,"%s_%d",m_pCurve->GetObjectID(),ic);
			j += sprintf(buf+j,"_%d",ic);
			break;
		case PATCH:
		///////////////////////////////////////////////// 
			ic = pStatic->GetCreate_i();
			jc = pStatic->GetCreate_j();
//			j += sprintf(buf+j,"%s_%d_%d",m_pPatch->GetObjectID(),ic,jc);
			j += sprintf(buf+j,"_%d_%d",ic,jc);
			break;
		case SOLID:
		///////////////////////////////////////////////// 
			ic = pStatic->GetCreate_i();
			jc = pStatic->GetCreate_j();
			kc = pStatic->GetCreate_k();
//			j += sprintf(buf+j,"%s_%d_%d_%d",m_pSolid->GetObjectID(),ic,jc,kc);
			j += sprintf(buf+j,"_%d_%d_%d",ic,jc,kc);
			break;
		default:
			j += sprintf(buf+j,"");
			break;
	}
}

void CMI_StaL::SetInfoForStaticBase(CDrStatic* pStatic,STALCARD StLCard)
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
	pStatic->SetObjectType((int)STATICLOAD);
	pStatic->SetElemType((int)STAL_OBJECT);              // globals.h
    pStatic->SetLevelType((int)LEVEL_KIDDO);			// Kid Level
	pStatic->SetObjectID(StLCard.load_id);             
	/////////////////////////////////////////////////
//		int			ElNum;                 
//		int			IDNum;
	///////////////////////////////////////////////////////// ID
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	///
	pStatic->SetObjectID(StLCard.load_id);
	SetStaticID(pStatic,buf,0);
	pStatic->SetObjectID(*str);
	(pStatic->GetStaLCard())->load_id = *str;
	///
	delete str;
	///////////////////////////////////////////////// Kode
	int i;
	//////
	for(i=0;i<6;i++)
	{
		(pStatic->GetStaLCard())->kode[i] = StLCard.kode[i];
		(pStatic->GetStaLCard())->value[i] = StLCard.value[i];
	}
	//////////////////////////////////////////////////
	(pStatic->GetStaLCard())->load_id		= StLCard.load_id;
//	(pSupp->GetSuppCard())->StaLProc 	= m_StaLProc;		// done in Calling Routine
	(pStatic->GetStaLCard())->nid_a 		= StLCard.nid_a;
	(pStatic->GetStaLCard())->nid_b 		= StLCard.nid_b;
	///////////////////////////////////////////////// Convert Support LocalData to WORLD
//   	WORLD LocalPos,CNodPos;
   	WORLD LocalPos;
	pWORLD pDat;
	CString text;
	char* pBuf;
	CDrNode*	pLabelNode;
	CDrLabel*	pLabel; 
	///////////////////////
	double dScale;
	int j,nPts,nActiveIndexSave;
	int nNodeIndex = -12345/*Create Anyway*/, nForceLabelIndex;
	WORLD Nor_Z,vec_W;
	/////////////////////////////////////// Matrices
	C3DMath	Math3D;
	CXForm	XForm;
	/////////////////////
	MATRIX Rot;				// for +ve or -ve
	pMATRIX pRot = &Rot; 
	MATRIX Mat;					// skewed
	pMATRIX pMat = &Mat; 
	WORLD NewX;
	pWORLD pNewX = &NewX;	// 
	////////////////////////
	Math3D.GetIdentityMATRIX(pMat);
	Math3D.GetIdentityMATRIX(pRot);
	/////////////////////
	if(StLCard.jcType == JC_X_FIXEDDIR)		// Fixed Skewed direction 
	{
		/////////////////////////////////// Copy  Skew Matrix
		Math3D.BlockCopy((HUGEBLK)(&m_SkewDirMat),(HUGEBLK)(pMat), sizeof(MATRIX) );
	}
	else
	if(StLCard.jcType == JC_X_TAN_CURVE)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewXMATRIX(&m_CurveTan, pMat,XF_REPLACE);
	}
	else
	if(StLCard.jcType == JC_Z_NOR_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewZMATRIX(&m_PatchNor, pMat,XF_REPLACE);

	}
	else
	if(StLCard.jcType == JC_I_TAN_PATCH)
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
	/////////////////////////////////////////////////////////// ///////// LOOP over Compos
	CString	 tagT,tagR;
	///////////////////
	switch(StLCard.StaLProc)
	{
		case STL_FORCE:		tagT = "F";	tagR = "M";		break;
		case STL_DISPLACE:	tagT = "D";	tagR = "R";		break;
		case STL_PRESSURE:	tagT = "P";	tagR = "X";		break;
		case STL_THERMAL:	tagT = "T";	tagR = "X";		break;
		case STL_LUMPWT:	tagT = "W";	tagR = "X";		break;
		default:break;
	}
	/////////////////////////////
	for(i=0;i<6;i++)		
	{
		if( StLCard.kode[i] == 0)
			continue;
		/////////////////////////////////////////// Over Active Direction
		pBuf = text.GetBuffer(30);
		/////////////
		switch(i)
		{
			case 0:
				if(StLCard.value[i]<0)
					XForm.Rotate_Z(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sx=%.f",tagT,StLCard.value[i]);
				////
				break;
			case 1:
				if(StLCard.value[i]<0)
					XForm.Rotate_X(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sy=%.f",tagT,StLCard.value[i]);
				////
				break;
			case 2:
				if(StLCard.value[i]<0)
					XForm.Rotate_Y(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sz=%.f",tagT,StLCard.value[i]);
				////
				break;

			case 3:
				if(StLCard.value[i]<0)
					XForm.Rotate_Z(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sx=%.f",tagR,StLCard.value[i]);
				////
				break;
			case 4:
				if(StLCard.value[i]<0)
					XForm.Rotate_X(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sy=%.f",tagR,StLCard.value[i]);
				////
				break;
			case 5:
				if(StLCard.value[i]<0)
					XForm.Rotate_Y(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sz=%.f",tagR,StLCard.value[i]);
				////
				break;

			default:
				break;
		}
		text.ReleaseBuffer();
		///////////////////////////////////// Default Scale
		dScale = 1.0;
		if(m_bNonUniform)
			dScale = (fabs(StLCard.value[i]))/m_dMax[i];
		///////////////////////////////////// Over Active One
		nPts = pStatic->GetnPts(i);
		pDat = pStatic->GetpLoc(i);
		///////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = dScale * pDat[j].x;
			LocalPos.y = dScale * pDat[j].y;
			LocalPos.z = dScale * pDat[j].z;
			/////////////////////////// strip Scale Factor (World Coord)
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
 			/////////////////////////////////////////////// Positive or Negative
 			XForm.Transform(&LocalPos, &LocalPos, pRot);
			/////////////////////////////////////////////// Rotate for Skewed Support
			if(StLCard.nid_a != "" || m_bCurveTan || m_bPatchNor|| m_bPatchTan)
			{
				/////////////////////////////////// Now Rotate
				XForm.Transform(&LocalPos, &LocalPos, pMat);
			}
   			/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
			///////////////////////////////////////////////////////////// Label:CreateCNode
			if(j == nPts-1)	// last pt. for text
			{
				nActiveIndexSave = pObjectMgr->GetActiveObjectIndex();	// Save Active Index									
				//////////////////////////////////////////////////////
				LocalPos.x = pDat[j].x;
				LocalPos.y = pDat[j].y;
				LocalPos.z = pDat[j].z;
				///
//				Mouse.WORtoWOP(&LocalPos,&LocalPos);
				///////////////////////////////////////////
   				LocalPos.x	= ((double)(LocalPos.x))/dWorldBase*dMapFactor;
   				LocalPos.y	= ((double)(LocalPos.y))/dWorldBase*dMapFactor;
   				LocalPos.z	= ((double)(LocalPos.z))/dWorldBase*dMapFactor;
 				//////////////////////// World Coord
				pObjectMgr->DStoSC(&LocalPos.x);
				pObjectMgr->DStoSC(&LocalPos.y);
				pObjectMgr->DStoSC(&LocalPos.z);
				//////////////////////////////////////// 
				pLabelNode	= CreateNode(text,pLabel,LocalPos, TRUE,FALSE,
								nNodeIndex, nForceLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
				pLabel		= (CDrLabel*)((pLabelNode->GetLabelList())->GetTail());
				////////////////////////////////////////////////////////// Reciprocate
				pStatic->SetLabelNode(pLabelNode);
				pStatic->SetLabelPtr(pLabel);
				///////////////////////////////////
				pLabel->SetContextObj(CO_FORCE);
				///////////////////////////////////////////////////
				pObjectMgr->SetActiveObjectIndex(nActiveIndexSave);		// Restore Active Index									
			}
		}
	}
	////////////////////////////////////////// finally
	pStatic->SetStaLCard(StLCard);
	////////////////////////////////////////// 
	pStatic->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pStatic->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

int CMI_StaL::RemoveOldStatic(STALCARD StLCard, CDListMgr* pList)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	////////////////////////////////////////////////////// 
	int i,j;
	//////////////////////////////////
	int	nCount	= pList->GetCount();
	//////////////////////////////////////////////////////// Remove Old Similar ListItems
	for(i=0; i<nCount;i++)
	{
		////////////////////
		POSITION pos;
		///////////////////////////////////////////////////////
		// Remove or Destroy Old Ones similar to Current StLProc & load_id
		///////////////////////////////
		CDrStatic*	pDrStatic;
		/////////////////////////////////////////////////////////// 
		pos = pList->FindIndex(nCount-i-1);
		pDrStatic = (CDrStatic*)pList->GetAt(pos);
		////
		if(!pDrStatic)
		{
			AfxMessageBox("Internal ERROR:\nCMI_StaL::RemoveOldStatic\npDrStatic=NULL"); 
			return -1;
		}
		///////////////////////////////////////////////// Current Proc & LoadID
		STALPROC StaLProc_ToRemove	= (pDrStatic->GetStaLCard())->StaLProc;
		CString  load_id_ToRemove	= (pDrStatic->GetStaLCard())->load_id;
		//////////////////////////////////////////////
		if((load_id_ToRemove != StLCard.load_id) || 
			(StaLProc_ToRemove != StLCard.StaLProc) )
			continue;
		//////////////////////////////////////////////////////
		pList->RemoveAt(pos);
		///////////////////////////////////////////// Delete StL
		int nStLCount = pDListMgr->GetCount();
		//////////////////////////////////////////////////////////
		for(j=0; j<nStLCount;j++)
		{
			pos					= pDListMgr->FindIndex(nStLCount-j-1);
			CDrStatic* pStL		= (CDrStatic*)pList->GetAt(pos); 
			CString load_id_j	= (pStL->GetStaLCard())->load_id;
			STALPROC StaLProc_j	= (pStL->GetStaLCard())->StaLProc;
			////////////////////////////////////////////////
			if((load_id_ToRemove == load_id_j) && (StaLProc_ToRemove == StaLProc_j) )
			{
				pObjectMgr->DeleteFromDataBase(nStLCount-j-1,STATICLOAD);
				break;
			}
			////////////////////////////
		}
	}
	////////////////////////////////////////////////////////
	return 0;
}

int CMI_StaL::RegenNodeBased(CDrNode* pNode)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<STALCARD,STALCARD>* pStaLCardList = pNode->GetStaLCardList();
	if(pStaLCardList->IsEmpty())
		return 0;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// StLCard
		STALCARD StLCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pNode->GetStaLList();
		int nBeg = StLCard.nStartIndex;
		int nEnd = nBeg + StLCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenNodeBased_DoIt(pNode,StLCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
		////////////////////
		CurList.RemoveAll();
	}
	////////////
	return MA_OK;
}

int CMI_StaL::RegenNodeBased_DoIt(CDrNode* pNode,STALCARD& StLCard,CDListMgr* pList)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CString strCurORPat;
	////////////////////
	m_bCurveTan		= FALSE;
	m_bReciproDone	= FALSE;
	m_bNonUniform	= FALSE;
	///////////////////////////////////////////////////////// Fixed Skewed direction
	if(StLCard.jcType == JC_X_FIXEDDIR)		
		UpdateFixedDirSkewMatrix(StLCard);
	///////////////////////////////////////////////////////// Curve Tangential
	else
	if( StLCard.jcType == JC_X_TAN_CURVE)
	{
		m_bCurveTan	= TRUE;
		strCurORPat = StLCard.ID_CP;
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
	if( StLCard.jcType == JC_Z_NOR_PATCH)
	{		
		m_bPatchNor		= TRUE;				
		strCurORPat = StLCard.ID_CP;
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
	if( StLCard.jcType == JC_I_TAN_PATCH)
	{		
		m_bPatchTan		= TRUE;				
		strCurORPat = StLCard.ID_CP;
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
	/////////////////////
	m_StaLProc	= StLCard.StaLProc;
	m_pNode		= pNode;
	m_NodePos	= *(m_pNode->GetLocalPos());
	//////////////////////////
	POSITION pos;
    CDrStatic* pStatic;
	//////////////////////////////////////////////
	if(!pList || pList->IsEmpty())
		return 0;
	/////////////////
	int nStatic = pList->GetCount(); 
	//////////////////////////////////////////////
	for(int i=0; i<nStatic;i++)
	{
		//////////////////////////////////////////////////////// Duplicate
//			if( IsDuplicated(m_NodePos,m_StaLProc) )
//				return -1;
		/////////////////////////////////////////////////////////////////////////// Add Always
		pos = pList->FindIndex(i);
	    pStatic = (CDrStatic*)(pList->GetAt(pos));
		m_StaLBased	= pStatic->GetCreateBase();
		///////////////////////////////////////////// init Raw Support Data
		pStatic->InitRawData(m_StaLProc);
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,FALSE);
		///////////////// Set new position
		pStatic->SetNodPos(m_NodePos);
		///////////////////////////
		RegenInfoForStaticBase(pStatic,StLCard);	
		///////
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
	}		
	/////////
    return MA_OK;
}

int CMI_StaL::RegenCurveBased(CDrCurve* pCurve)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<STALCARD,STALCARD>* pCardList = pCurve->GetStaLCardList();
	if(pCardList->IsEmpty())
		return MA_OK;
	////////////////////////
	UINT StaLBased	= CURVE;
	//////////////////////////////////////////// Output memory
	int nOut		= pCurve->GetLongOutPts();
	BOOL bClosed	= pCurve->IsClosed_S();
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

int CMI_StaL::SetMaxVal_Cur(CDrCurve* pCurve,STALCARD& StLCard)
{
	//////////////
	CDListMgr* pList = pCurve->GetStaLList();
	POSITION posStatic;
    CDrStatic* pStatic;
	//////////////////////////////////////////////////////////////////// 
	double	Fx,Fy,Fz,Mx,My,Mz;
	int		i,indexList=-1;
	BOOL	bT = FALSE;
	BOOL	bR = FALSE;
	//////////////////////////////////////////////////////// Max for Scaling Drawing
	for(i=0;i<6;i++)
		m_dMax[i] = 0.0;
	//////////////////////////////////////////////////////// 
	int nNodPossBeg		= StLCard.nNodPos_S_Beg;
	int nNodPossEnd		= StLCard.nNodPos_S_End;
	//////////////////////////////////////////////////////// Go Over All Static w/ same Card
	for(i=nNodPossBeg;i<nNodPossEnd;i++)	// necessary for Curve_Profile
											// for single Curve:	nNodPossBeg=0
											//						nNodPossEnd=nMaxBezSeg
	{
		///////////////////////////////////////////////////////////////////
		indexList++;	// List index Cumulative because some prev. Compo Curve
						// may not have any Load
		posStatic = pList->FindIndex(indexList);
		pStatic = (CDrStatic*)(pList->GetAt(posStatic));
		////////////////////////////////// Tran
		Fx	= pStatic->GetStaLCard()->value[0];
		if(fabs(Fx)>m_dMax[0])
			m_dMax[0] = fabs(Fx);
		/////////////////////////
		Fy	= pStatic->GetStaLCard()->value[1];
		if(fabs(Fy)>m_dMax[1])
			m_dMax[1] = fabs(Fy);
		/////////////////////////
		Fz	= pStatic->GetStaLCard()->value[2];
		if(fabs(Fz)>m_dMax[2])
			m_dMax[2] = fabs(Fz);
		/////////////////////////
		Mx	= pStatic->GetStaLCard()->value[3];
		if(fabs(Mx)>m_dMax[3])
			m_dMax[3] = fabs(Mx);
		/////////////////////////
		My	= pStatic->GetStaLCard()->value[4];
		if(fabs(My)>m_dMax[4])
			m_dMax[4] = fabs(My);
		/////////////////////////
		Mz	= pStatic->GetStaLCard()->value[5];
		if(fabs(Mz)>m_dMax[5])
			m_dMax[5] = fabs(Mz);
		/////////////////////////
	}
	/////////
	return 0;
}	


int CMI_StaL::RegenCurveBased_DoIt(CDrCurve* pCurve,pWORLD pOut,pWORLD pOutCurveTan,int nOut)
{
	m_pCurve	= pCurve;
	////////////////////////////////////////
	CList<STALCARD,STALCARD>* pCardList = pCurve->GetStaLCardList();
	if(pCardList->IsEmpty())
		return MA_OK;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(STATICLOAD);
	//////////////
	CDListMgr* pList = pCurve->GetStaLList();
	POSITION posStatic;
    CDrStatic* pStatic;
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,indexList=-1;
	//////////////////
	for (POSITION posT = pCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// StLCard
		STALCARD StLCard	= pCardList->GetNext(posT); 
		///////////////////////////////////////////////////////// Fixed Skewed direction
		UpdateFixedDirSkewMatrix(StLCard);
		///////////////////////////////////////////////// prepare List
		m_StaLCard			= StLCard;
		m_StaLProc			= StLCard.StaLProc;
		///////////////////////////////////////////////// Create Max Values for Scaling the Drawing
		SetMaxVal_Cur(pCurve,StLCard);
		//////////////////////////////////////////////////////// 
		int nNodPossBeg		= StLCard.nNodPos_S_Beg;
		int nNodPossEnd		= StLCard.nNodPos_S_End;
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
			pStatic = (CDrStatic*)(pList->GetAt(posStatic));
			m_StaLBased	= pStatic->GetCreateBase();
			///////////////////////////////////////////// init Raw Support Data
			pStatic->InitRawData(m_StaLProc);
			/////////////////////
			if(m_bCurveTan)
				m_CurveTan	= *(pOutCurveTan+i);
			///
			pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,FALSE);
			///////////////// Set new position
			pStatic->SetNodPos(m_NodePos);
			///////////////////////////
			RegenInfoForStaticBase(pStatic,StLCard);	
			///
			pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
			///////	
		}
	}
	/////////////////////
    return MA_OK;
}

int CMI_StaL::RegenPatchBased_3(CDrPatch* pPatch)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<STALCARD,STALCARD>* pStaLCardList = pPatch->GetStaLCardList();
	if(pStaLCardList->IsEmpty())
		return MA_ERROR;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// StLCard
		STALCARD StLCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pPatch->GetStaLList();
		int nBeg = StLCard.nStartIndex;
		int nEnd = nBeg + StLCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenPatchBased_3_DoIt(pPatch,StLCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
	}
	////////////
	return MA_OK;
}

int CMI_StaL::RegenPatchBased_3_DoIt(CDrPatch* pPatch,STALCARD& StLCard,CDListMgr* pList)
{
	////////////////////////
	m_bCurveTan		= FALSE;
	m_bPatchNor		= FALSE;
	m_bReciproDone	= FALSE;
	m_bNonUniform	= FALSE;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////
	if(!pList || pList->IsEmpty())
		return MA_ERROR;
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	long nOut			= pPatch->GetLongOutPts();
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
	m_bPatchNor	= StLCard.bNorPat;
	m_bPatchTan	= StLCard.bTanPat;
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
	//////////////////////////////////////////// Generate, if NonUniform
	BOOL	bT = FALSE;
	BOOL	bR = FALSE;
//	if(bNonUniform)
//		FillUp_Val_Pat_3(pPatch,pPatchT,pPatchR,StLCard,&bT,&bR);
	///////////////////////////////////////////////////////////////// Replace, if needed
//	int nResult = RemoveOldStatic(StLCard, pList);
//	if(nResult<0)
//		return (CDrStatic*)NULL;
	///////////////////////////////////////////////////////// Fixed Skewed direction
	UpdateFixedDirSkewMatrix(StLCard);
	//////////////////////////////////////////////////////// Loop Over All Triangles
	m_pPatch	= pPatch;
    ////////////////////////////////////////////////////////////////// Create
	CDListMgr* pTriList = m_pPatch->GetTriangleList();
	if(pTriList->IsEmpty() )
		return MA_ERROR;
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
											iOutGlo,jOutGlo,bT,bR);
		else
		if(nType == 2)
			RegenTRIANGLE_2(pOut,pOutPatchNor,pList,pOutPatchTan_S,pOutPatchTan_T,
											iOutGlo,jOutGlo,bT,bR);
		else
		{
			//////////////////
			AfxMessageBox("CMI_StaL::RegenPatchBased_3\nnType !==1 or 2");
			return MA_ERROR;
		}
	}										///////////////////////////// end LIST
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return MA_OK;
   	
}

int CMI_StaL::RegenTRIANGLE_1(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
									int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR)
{ 
	POSITION posStatic;
    CDrStatic* pStatic;
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
//			if( IsDuplicated(m_NodePos,m_StaLProc) )
//				continue;
			///////////////////////////////////////////////////////////////////////// Add
			posStatic	= pList->FindIndex(L1);
			pStatic		= (CDrStatic*)(pList->GetAt(posStatic));
			m_StaLBased	= pStatic->GetCreateBase();
			////////////////////////////
			pStatic->SetNodPos(m_NodePos);
			pStatic->InitRawData(m_StaLProc);
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
			RegenInfoForStaticBase(pStatic,*(pStatic->GetStaLCard()));	
			///////
		}
	}
	return MA_OK;
}									

int CMI_StaL::RegenTRIANGLE_2(pWORLD pOut,pWORLD pOutPatchNor,CDListMgr* pList,
									pWORLD pOutPatchTan_S,pWORLD pOutPatchTan_T,
									int iOutGlo_ST,int jOutGlo_ST,BOOL bT,BOOL bR)
{ 
	POSITION posStatic;
    CDrStatic* pStatic;
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
//			if( IsDuplicated(m_NodePos,m_StaLProc) )
//				continue;
			///////////////////////////////////////////////////////////////////////// Add
			posStatic	= pList->FindIndex(L1);
			pStatic		= (CDrStatic*)(pList->GetAt(posStatic));
			m_StaLBased	= pStatic->GetCreateBase();
			////////////////////////////
			pStatic->SetNodPos(m_NodePos);
			pStatic->InitRawData(m_StaLProc);
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
			RegenInfoForStaticBase(pStatic,*(pStatic->GetStaLCard()));	
			///////
		}
	}
	return MA_OK;
}									

int CMI_StaL::RegenPatchBased_4(CDrPatch* pPatch)
{
	int nResult = MA_OK;
	////////////////////////////////////////
	CList<STALCARD,STALCARD>* pStaLCardList = pPatch->GetStaLCardList();
	if(pStaLCardList->IsEmpty())
		return 0;
	/////////////////////////////////////////////////////////////////////// Loop
	CDListMgr CurList;
	//////////////////
	for (POSITION posT = pStaLCardList->GetHeadPosition();posT !=NULL;)
	{
		////////////////////////////////////////////////////// StLCard
		STALCARD StLCard	= pStaLCardList->GetNext(posT); 
		///////////////////////////////////////////////// prepare List
		CDListMgr* pStaLList	= pPatch->GetStaLList();
		int nBeg = StLCard.nStartIndex;
		int nEnd = nBeg + StLCard.nTotal;
		/////////////////////////////////
		CurList.RemoveAll();
		///
		for(int i=nBeg;i<nEnd;i++)
		{
			POSITION pos = pStaLList->FindIndex(i);
			CurList.InsertObject(pStaLList->GetAt(pos));
		}
		////////////////////////////////////////////////////// do it
		nResult = RegenPatchBased_4_DoIt(pPatch,StLCard,&CurList);
		////////
		if(nResult != MA_OK)
			return nResult;
	}
	////////////
	return MA_OK;
}

int CMI_StaL::RegenPatchBased_4_DoIt(CDrPatch* pPatch,STALCARD& StLCard,CDListMgr* pList)
{
	////////////////////////
	m_bCurveTan		= FALSE;
	m_bPatchNor		= FALSE;
	m_bReciproDone	= FALSE;
	m_bNonUniform	= FALSE;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////
	if(!pList || pList->IsEmpty())
		return MA_ERROR;
	//////////////////////////////////////////// Output memory
	BOOL bClosed_S		= pPatch->IsClosed_S();
	BOOL bClosed_T		= pPatch->IsClosed_T();
	int nOut_S			= pPatch->GetOut_S();
	int nOut_T			= pPatch->GetOut_T();
	long nOut			= pPatch->GetLongOutPts();
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
	m_bPatchNor	= StLCard.bNorPat;
	m_bPatchTan	= StLCard.bTanPat;
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
	//////////////////////////////////////////// Generate, if NonUniform
//	if(bNonUniform)
//		FillUp_ValList_Pat_4(pPatch,pPatchT,pPatchR,StLCard);
	///////////////////////////////////////////////////////////////// Replace, if needed
//	int nResult = RemoveOldStatic(StLCard, pList);
//	if(nResult<0)
//		return -1;
	///////////////////////////////////////////////////////// Fixed Skewed direction
	UpdateFixedDirSkewMatrix(StLCard);
	//////////////////////////////////////////////////////// Loop Over MeshPts
	int i,j;
	int k		= -1;
	int nVal	= -1;
	///////////
	m_pPatch	= pPatch;
	//////////////////////////////////////////////////////// Closed?
	int nOutCreate_S = nOut_S;
	if(bClosed_S)
		nOutCreate_S--;
	int nOutCreate_T = nOut_T;
	if(bClosed_T)
		nOutCreate_T--;
	//////////////////////////
	POSITION posStatic;
    CDrStatic* pStatic;
	///////////////////////////////////////////////////////////////////
	for(j=0; j<nOutCreate_T;j++)
	{
		for(i=0; i<nOutCreate_S;i++)
		{
			k++;
			m_NodePos	= *(pOut+k);
			//////////////////////////////////////////////////////// Duplicate
//			if( IsDuplicated(m_NodePos,m_StaLProc) )
//				continue;
			/////////////////////////////////////////////////
			posStatic = pList->FindIndex(k);
			pStatic = (CDrStatic*)(pList->GetAt(posStatic));
			m_StaLBased			= pStatic->GetCreateBase();
			STALCARD StLCard	= *(pStatic->GetStaLCard()); 
			m_StaLProc			= StLCard.StaLProc;
			///////////////////////////////////////////// init Raw Support Data
			pStatic->InitRawData(m_StaLProc);
			/////////////////////
			if(m_bPatchNor)
				m_PatchNor	= *(pOutPatchNor+k);
			///////////////// Set new position
			pStatic->SetNodPos(m_NodePos);
			///////////////////////////
			RegenInfoForStaticBase(pStatic,StLCard);	
			///////	
		}		
	}
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	if(m_bPatchNor)
		FreeMem(pOutPatchNor);
	/////////////////////
    return MA_OK;
}

void CMI_StaL::RegenInfoForStaticBase(CDrStatic* pStatic,STALCARD StLCard)
{
	STALCARD* pStaLCard = pStatic->GetStaLCard();
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
//   	WORLD LocalPos,CNodPos;
   	WORLD LocalPos;
	pWORLD pDat;
	CString text;
	char* pBuf;
	CDrNode*	pLabelNode;
	///////////////////////
	double dScale;
	int j,nPts;
	WORLD Nor_Z,vec_W;
	/////////////////////////////////////// Matrices
	C3DMath	Math3D;
	CXForm	XForm;
	/////////////////////
	MATRIX Rot;				// for +ve or -ve
	pMATRIX pRot = &Rot; 
	MATRIX Mat;					// skewed
	pMATRIX pMat = &Mat; 
	WORLD NewX;
	pWORLD pNewX = &NewX;	// 
	////////////////////////
	Math3D.GetIdentityMATRIX(pMat);
	Math3D.GetIdentityMATRIX(pRot);
	/////////////////////
	if(StLCard.jcType == JC_X_FIXEDDIR)		// Fixed Skewed direction 
	{
		/////////////////////////////////// Copy  Skew Matrix
		Math3D.BlockCopy((HUGEBLK)(&m_SkewDirMat),(HUGEBLK)(pMat), sizeof(MATRIX) );
	}
	else
	if(StLCard.jcType == JC_X_TAN_CURVE)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewXMATRIX(&m_CurveTan, pMat,XF_REPLACE);
	}
	else
	if(StLCard.jcType == JC_Z_NOR_PATCH)
	{
		/////////////////////
		Math3D.GetIdentityMATRIX(pMat);
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewZMATRIX(&m_PatchNor, pMat,XF_REPLACE);
	}
	else
	if(StLCard.jcType == JC_I_TAN_PATCH)
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
	/////////////////////////////////////////////////////////// ///////// LOOP over Compos
	CString	 tagT,tagR;
	///////////////////
	switch(StLCard.StaLProc)
	{
		case STL_FORCE:		tagT = "F";	tagR = "M";		break;
		case STL_DISPLACE:	tagT = "D";	tagR = "R";		break;
		case STL_PRESSURE:	tagT = "P";	tagR = "X";		break;
		case STL_THERMAL:	tagT = "T";	tagR = "X";		break;
		case STL_LUMPWT:	tagT = "W";	tagR = "X";		break;
		default:break;
	}
	/////////////////////////////
	for(int i=0;i<6;i++)		
	{
		if( StLCard.kode[i] == 0)
			continue;
		/////////////////////////////////////////// Over Active Direction
		pBuf = text.GetBuffer(30);
		/////////////
		switch(i)
		{
			case 0:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_Z(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sx=%.f",tagT,pStaLCard->value[i]);
				////
				break;
			case 1:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_X(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sy=%.f",tagT,pStaLCard->value[i]);
				////
				break;
			case 2:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_Y(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sz=%.f",tagT,pStaLCard->value[i]);
				////
				break;

			case 3:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_Z(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sx=%.f",tagR,pStaLCard->value[i]);
				////
				break;
			case 4:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_X(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sy=%.f",tagR,pStaLCard->value[i]);
				////
				break;
			case 5:
				if(pStaLCard->value[i]<0)
					XForm.Rotate_Y(pRot,180.,XF_REPLACE);
				//////////////
				sprintf(pBuf,"%sz=%.f",tagR,pStaLCard->value[i]);
				////
				break;

			default:
				break;
		}
		text.ReleaseBuffer();
		///////////////////////////////////// Default Scale
		dScale = 1.0;
		if(!StLCard.bUniform)
			dScale = (fabs(pStaLCard->value[i]))/m_dMax[i];
		///////////////////////////////////// Over Active One
		nPts = pStatic->GetnPts(i);
		pDat = pStatic->GetpLoc(i);
		///////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = dScale * pDat[j].x;
			LocalPos.y = dScale * pDat[j].y;
			LocalPos.z = dScale * pDat[j].z;
			/////////////////////////// strip Scale Factor (World Coord)
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
 			/////////////////////////////////////////////// Positive or Negative
 			XForm.Transform(&LocalPos, &LocalPos, pRot);
			/////////////////////////////////////////////// Rotate for Skewed Load
			if(StLCard.nid_a != "" || m_bCurveTan || m_bPatchNor || m_bPatchTan)
			{
				/////////////////////////////////// Now Rotate
				XForm.Transform(&LocalPos, &LocalPos, pMat);
			}
   			/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
			///////////////////////////////////////////////////////////// update label Node
			if(j == nPts-1)	// last pt. for text
			{
				//////////////////////////////////////////////////////
				LocalPos.x = pDat[j].x;
				LocalPos.y = pDat[j].y;
				LocalPos.z = pDat[j].z;
				/////////////////////////////////////////////// update label Node
				pLabelNode = pStatic->GetLabelNode();
				pLabelNode->SetLocalPos(LocalPos);
				(pLabelNode->GetNodeCard())->x = (long)LocalPos.x;
				(pLabelNode->GetNodeCard())->y = (long)LocalPos.y;
				(pLabelNode->GetNodeCard())->z = (long)LocalPos.z;
				/////
			}
		}
	}
	////////////////////////////////////////// finally
//	pStatic->SetStaLCard(StLCard);
	//////////////////
	return;
	
} 
/*
int CMI_StaL::CreateListNodeBased(CDrNode* pObject)
{
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrStatic* pStatic;
	int index;
	POSITION pos;
	/////////////////
	int nStatic = pObject->GetStaLList()->GetCount();
	//
	for(int i=0; i<nStatic;i++)
	{
		///
		pos		= pObject->GetStaLList()->FindIndex(i); 
		pStatic = (CDrStatic*)(pObject->GetStaLList()->GetAt(pos));
		if(!pStatic)
		{
			AfxMessageBox("Internal ERROR\nCMI_StaL::CreateListNodeBased\n!pStatic");
			return MA_ERROR;
		}
		////
		STALCARD StLCard	= *(pStatic->GetStaLCard());
		STALPROC StaLProc	= StLCard.StaLProc;
		UINT StaLBased		= NODE;
		///////////////////////////////////////////////
		pStatic = CreateNodeBased(StaLProc,StLCard,pObject,StaLBased);
		///////
		if(pStatic)
		{
			index = TempList.GetObjectIndex(pStatic); 
			if(index<0) // not yet
				TempList.InsertObject(pStatic);
			/////////// reciprocate
			index = pStatic->GetNodeList()->GetObjectIndex(pObject);
			if(index<0)
				pStatic->GetNodeList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
	}		
	////////////////////////////////////////////////////////////// Save
	pObject->GetStaLList()->RemoveAll();
	pObject->GetStaLList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}

int CMI_StaL::CreateListCurveBased(CDrCurve* pObject)
{
	m_pDrCurve = pObject;
	/////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrStatic* pStatic;
	int index;
	POSITION pos;
	/////////////////
	int nStatic = pObject->GetStaLList()->GetCount();
	//
	for(int i=0; i<nStatic;i++)
	{
		///
		pos = pObject->GetStaLList()->FindIndex(i); 
		pStatic = (CDrStatic*)(pObject->GetStaLList()->GetAt(pos));
		if(!pStatic)
		{
			AfxMessageBox("Internal ERROR\nCMI_StaL::CreateListCurveBased\n!pStatic");
			return MA_ERROR;
		}
		////
		STALCARD StLCard	= *(pStatic->GetStaLCard());
		STALPROC StaLProc	= StLCard.StaLProc;
		UINT StaLBased		= CURVE;
		///////////////////////////////////////////////
		CDrCurve* pCurveT = NULL;
		CDrCurve* pCurveR = NULL;
		///
		CDListMgr* pList;
		//
		BOOL bIso		= StLCard.bIso;
		BOOL bNonIso	= StLCard.bNonIso;
		BOOL bNonUniform = (bIso || bNonIso)?TRUE:FALSE;
		////
		if(bNonUniform)
		{
			CString	Cid_T = StLCard.cid_ParentT;	// this staLcard part of this Curve of Category CA_FORCE
			pList = pObjectMgr->GetObjectList(CURVE);
			index = pList->GetObjectIndex(CURVE,Cid_T);
			if(index>=0)
				pCurveT = (CDrCurve*)pList->GetObject(index);
			//
			CString	Cid_R = StLCard.cid_ParentR;	// this staLcard part of this Curve of Category CA_FORCE
			pList = pObjectMgr->GetObjectList(CURVE);
			index = pList->GetObjectIndex(CURVE,Cid_R);
			if(index>=0)
				pCurveR = (CDrCurve*)pList->GetObject(index);
		}
		///////////////////////////
//		CreateCurveBased(StaLProc,StLCard,pObject,bNonUniform,
//									pCurveT,pCurveR,StaLBased);
		///////
		if(pStatic)
		{
			index = TempList.GetObjectIndex(pStatic); 
			if(index<0) // not yet
				TempList.InsertObject(pStatic);
			/////////// reciprocate
			index = pStatic->GetCurveList()->GetObjectIndex(pObject);
			if(index<0)
				pStatic->GetCurveList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
	}		
	////////////////////////////////////////////////////////////// Save
	pObject->GetStaLList()->RemoveAll();
	pObject->GetStaLList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}

int CMI_StaL::CreateListPatchBased(CDrPatch* pObject)
{
	m_pDrPatch = pObject;
	/////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrStatic* pStatic;
	int index;
	POSITION pos;
	/////////////////
	int nStatic = pObject->GetStaLList()->GetCount();
	//
	for(int i=0; i<nStatic;i++)
	{
		///
		pos = pObject->GetStaLList()->FindIndex(i); 
		pStatic = (CDrStatic*)(pObject->GetStaLList()->GetAt(pos));
		if(!pStatic)
		{
			AfxMessageBox("Internal ERROR\nCMI_StaL::CreateListPatchBased\n!pStatic");
			return MA_ERROR;
		}
		////
		STALCARD StLCard	= *(pStatic->GetStaLCard());
		STALPROC StaLProc	= StLCard.StaLProc;
		UINT StaLBased		= PATCH;
		///////////////////////////////////////////////
		CDrPatch* pPatchT = NULL;
		CDrPatch* pPatchR = NULL;
		///
		CDListMgr* pList;
		//
		BOOL bIso		= StLCard.bIso;
		BOOL bNonIso	= StLCard.bNonIso;
		BOOL bNonUniform = (bIso || bNonIso)?TRUE:FALSE;
		////
		if(bNonUniform)
		{
			CString	Cid_T = StLCard.cid_ParentT;	// this staLcard part of this Curve of Category CA_FORCE
			pList = pObjectMgr->GetObjectList(PATCH);
			index = pList->GetObjectIndex(PATCH,Cid_T);
			if(index>=0)
				pPatchT = (CDrPatch*)pList->GetObject(index);
			//
			CString	Cid_R = StLCard.cid_ParentR;	// this staLcard part of this Curve of Category CA_FORCE
			pList = pObjectMgr->GetObjectList(PATCH);
			index = pList->GetObjectIndex(PATCH,Cid_R);
			if(index>=0)
				pPatchR = (CDrPatch*)pList->GetObject(index);
		}
		///////////////////////////
		if(pObject->GetPatSubType() == PS_QUADRILAT)
			pStatic = CreatePatchBased_4(StaLProc,StLCard,pObject,bNonUniform,
													pPatchT,pPatchR,StaLBased);
		else
		if(pObject->GetPatSubType() == PS_TRIANGLE)
			pStatic = CreatePatchBased_3(StaLProc,StLCard,pObject,bNonUniform,
													pPatchT,pPatchR,StaLBased);
		else
			return -1;
		///////
		if(pStatic)
		{
			index = TempList.GetObjectIndex(pStatic); 
			if(index<0) // not yet
				TempList.InsertObject(pStatic);
			/////////// reciprocate
			index = pStatic->GetPatchList()->GetObjectIndex(pObject);
			if(index<0)
				pStatic->GetPatchList()->InsertObject(pObject);
		}
		else
			return -1;
		//////////////
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
	}		
	////////////////////////////////////////////////////////////// Save
	pObject->GetStaLList()->RemoveAll();
	pObject->GetStaLList()->AddTail(&TempList);
	TempList.RemoveAll();
	/////////////////////
    return 0;
}
*/

void CMI_StaL::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_StaL:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_StaL:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


