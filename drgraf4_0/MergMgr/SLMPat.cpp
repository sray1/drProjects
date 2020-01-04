// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
/////////////////////
#include "MP_Xtrud.h"
#include "MP_Rotat.h"
#include "MP_Loft2.h"
#include "MP_CoonP.h"
#include "MP_CooP3.h"
#include "MP_Duct.h"
#include "MP_Sweep.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
//////////////////////
#include "MSTLMgr.h" 
//////////////////////
#include "SLEPat.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLEPat,CSLECur,1)
/////////////////////////////////////////////////////////////////////////////
CSLEPat::CSLEPat()
{
}

CSLEPat::~CSLEPat()
{
}

void CSLEPat::GetObjectInfo(CSLEObj* pObject)
{
	
	CSLECur::GetObjectInfo(pObject);
	///////////////////////////////////   
	CSLEPat* pAdd = (CSLEPat*) pObject;
	////////////////////////////////////////////////////////////////////// Patch
	pAdd->m_pView				= m_pView;
	////////////////////////////////////////
	if(!(m_CurveList.IsEmpty()) )
		pAdd->m_CurveList.AddTail(&m_CurveList ); 
	if(!(m_LatchList.IsEmpty()) )
		pAdd->m_LatchList.AddTail(&m_LatchList ); 
	/////////
    for(int i = 0; i<6; i++)              // for solid later 
    {
		pAdd->m_pCurrentSPatchT[i]		 = m_pCurrentSPatchT[i];	// Iso or NonIso Patch
		pAdd->m_pCurrentSPatchR[i]		 = m_pCurrentSPatchR[i];	// Iso or NonIso Patch
	}
	/////////
	if(!(m_CurveListT.IsEmpty()) )
		pAdd->m_CurveListT.AddTail(&m_CurveListT ); 
	if(!(m_CurveListR.IsEmpty()) )
		pAdd->m_CurveListR.AddTail(&m_CurveListR ); 
	/////////
	pAdd->m_Len_T				 = m_Len_T;
	pAdd->m_Len_R				 = m_Len_R;
	pAdd->m_FromID_T				 = m_FromID_T; 
	pAdd->m_FromID_R				 = m_FromID_R; 
	pAdd->m_ToID_T				 = m_ToID_T; 
	pAdd->m_ToID_R				 = m_ToID_R; 
}

void CSLEPat::SetObjectInfo(CSLEObj* pObject)
{
	
	CSLECur::SetObjectInfo(pObject);
	///////////////////////////////////   
	CSLEPat* pAdd = (CSLEPat*) pObject;
	////////////////////////////////////////////////////////////////////// Patch
	m_pView				= pAdd->m_pView;
	////////////////////////////////////////
	if(!(pAdd->m_CurveList.IsEmpty()) )
		m_CurveList.AddTail(&(pAdd->m_CurveList) ); 
	if(!(pAdd->m_LatchList.IsEmpty()) )
		m_LatchList.AddTail(&(pAdd->m_LatchList) ); 
	/////////
    for(int i = 0; i<6; i++)              // for solid later 
    {
		m_pCurrentSPatchT[i]		 = pAdd->m_pCurrentSPatchT[i];	// Iso or NonIso Patch
		m_pCurrentSPatchR[i]		 = pAdd->m_pCurrentSPatchR[i];	// Iso or NonIso Patch
	}
	/////////
	if(!(pAdd->m_CurveListT.IsEmpty()) )
		m_CurveListT.AddTail(&(pAdd->m_CurveListT) ); 
	if(!(pAdd->m_CurveListR.IsEmpty()) )
		m_CurveListR.AddTail(&(pAdd->m_CurveListR) ); 
	/////////
	m_Len_T				 = pAdd->m_Len_T;
	m_Len_R				 = pAdd->m_Len_R;
	m_FromID_T			 = pAdd->m_FromID_T; 
	m_FromID_R			 = pAdd->m_FromID_R; 
	m_ToID_T			 = pAdd->m_ToID_T; 
	m_ToID_R			 = pAdd->m_ToID_R; 
}

int CSLEPat::ShowPatchStaticLoad(CDrPatch* pCurrentPatch,CString* pID,int nHowMany)
{
	///////////////////////////////////////////////////////////////////////
//	 nHowmany			// Used as an afterthought for Updating Static anyway
						// in CMI_LSupp.CreatePatchStatic
						// even if same coords Patch exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowPatch to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(STATICLOAD);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_StaL	Static;
	CDrStatic*	pCurrentStaL; 
	STALCARD	stLCard;
	/////////////////////////
	if(m_bIso || m_bNonIso)
	{
		/////////////////////////
		m_cid_Iso		= pCurrentPatch->GetObjectID();	// this staLcard IsoParametric(Non-Iso) to this Curve
		/////////
		if(m_bTx ||m_bTy ||m_bTz )
			m_cid_ParentT	= m_pCurrentSPatchT[0]->GetObjectID();	// this staLcard part of this Curve of Category CA_FORCE
																// this is m_CID in Iso-Generated Curve
																// this is m_CID in NonIso Input
		if(m_bRx ||m_bRy ||m_bRz )
			m_cid_ParentR	= m_pCurrentSPatchR[0]->GetObjectID();	// this staLcard part of this Curve of Category CA_FORCE
																// this is m_CID in Iso-Generated Curve
																// this is m_CID in NonIso Input
		/////////////////////////
		/////////////////////////
		FillStLCard(stLCard,pID);
		//////////////
		if(pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
			pCurrentStaL = Static.CreatePatchBased_4(m_StaLProc,stLCard,pCurrentPatch,
								TRUE,m_pCurrentSPatchT[0],m_pCurrentSPatchR[0],PATCH);	// TRUE = NonUniform
		if(pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
			pCurrentStaL = Static.CreatePatchBased_3(m_StaLProc,stLCard,pCurrentPatch,
								TRUE,m_pCurrentSPatchT[0],m_pCurrentSPatchR[0],PATCH);	// TRUE = NonUniform
	}
	else
	{
		m_cid_Iso		= "";
		m_cid_ParentT	= "";
		m_cid_ParentR	= "";
		/////////////////////////
		FillStLCard(stLCard,pID);
		//////////////
		if(pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
			pCurrentStaL = Static.CreatePatchBased_4(m_StaLProc,stLCard,pCurrentPatch,
								FALSE,(CDrPatch*)NULL,(CDrPatch*)NULL,PATCH);	// FALSE = Uniform
		if(pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
			pCurrentStaL = Static.CreatePatchBased_3(m_StaLProc,stLCard,pCurrentPatch,
								FALSE,(CDrPatch*)NULL,(CDrPatch*)NULL,PATCH);	// FALSE = Uniform
	}
	////////////////////////////////////////////////////////////////////// Show
	int nActiveIndex = pObjectMgr->GetActiveObjectIndex();	// Get Active Index									
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(STATICLOAD);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,STATICLOAD);
	///////////////////////////////
	return 0;
}



			
void CSLEPat::RemoveMostListsFromPatch(CDrPatch* pAdd)
{
	//m_ElperSegList and LatchList donot remove	 
	/////////////////////////////////////// RemoveList
	if(!(pAdd->GetLabelList()->IsEmpty())	)
		pAdd->GetLabelList()->RemoveAll(); 
	if(!(pAdd->GetSolidList()->IsEmpty())	)
		pAdd->GetSolidList()->RemoveAll(); 
	if(!(pAdd->GetENodeList()->IsEmpty())	)
		pAdd->GetENodeList()->RemoveAll(); 
	if(!(pAdd->GetINodeList()->IsEmpty())	)
		pAdd->GetINodeList()->RemoveAll(); 
	if(!(pAdd->GetCNodeList()->IsEmpty())	)
		pAdd->GetCNodeList()->RemoveAll(); 
	if(!(pAdd->GetCN_BSList()->IsEmpty())	)
		pAdd->GetCN_BSList()->RemoveAll(); 
	if(!(pAdd->GetNodeList()->IsEmpty())	)
		pAdd->GetNodeList()->RemoveAll(); 
	if(!(pAdd->GetElemList()->IsEmpty())	)
		pAdd->GetElemList()->RemoveAll();
	if(!(pAdd->GetCurveList()->IsEmpty())	)
		pAdd->GetCurveList()->RemoveAll(); 
	if(!(pAdd->GetObj3DList()->IsEmpty())	)
		pAdd->GetObj3DList()->RemoveAll(); 
//	if(!(pAdd->GetPProfList()->IsEmpty())	)
//		pAdd->GetPProfList()->RemoveAll(); 
	//////////////////////////////////////
	return;
}
			


int CSLEPat::ShowInfo_PatchStaticLoad(CDrPatch* pDrPatch, char* buf, int jStart
																	,CString& CurrentStLID)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrPatch->GetStaLList();
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrStatic*	pDrStatic;
	STALCARD	stLCard;
	POSITION	pos;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		pos			= pList->FindIndex(i);
		pDrStatic	= (CDrStatic*)pList->GetAt(pos);
		////
		if(pDrStatic)
			stLCard = *(pDrStatic->GetStaLCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSLEPat::FillInfo_PatchStaticLoad\npDrStatic=NULL"); 
			return -2;
		}
		/////////////////////////////////////////
		if(stLCard.load_id != CurrentStLID)
			continue;
		////////////////////////////////////////////////////// Same LID
		CString		Cid;
		Cid = pDrPatch->GetObjectID();
		/////////////////////////////////////////
		switch (stLCard.StaLProc)
		{
			case STL_FORCE:
			case STL_DISPLACE:	// fall thro'
				j	= FillInfo_6(Cid, stLCard, buf, j);	
				break;
			case STL_PRESSURE:
			case STL_THERMAL:
			case STL_LUMPWT:	// fall thro'
				j	= FillInfo_3(Cid, stLCard, buf, j);	
				break;
			default:
				break;
		}
	}
	//////////
	return j;
}


int CSLEPat::Get_Values_Iso_Pat_Curve(CDrCurve* pCurveIsoTo,int indexCT,int indexCR,int IndexSkipNode,
											STALPROC StaLProc,CString& CurrentStPID,BOOL bLastCurve)
{
	/////////////////////////////////////////////// Iso
	Get_Values_Iso_Cur(pCurveIsoTo,StaLProc,IndexSkipNode,bLastCurve);	
	/////////////////////////////////////////////// Curve Name
	CString strPat_Cur = pCurveIsoTo->GetObjectID();
	strPat_Cur += (CurrentStPID + "_PC"); // P =Pat/C=Cur 
	////////////////////////////////////////////
	if(m_bTx ||m_bTy ||m_bTz)
	{
		strPat_Cur	+= "_T"; // T =Translation 	
		Generate_IsoCurveControls(pCurveIsoTo,indexCT,&strPat_Cur,TRUE);// TRUE = Translation
	}
		//////////////
	if(m_bRx ||m_bRy ||m_bRz)
	{
		strPat_Cur	+= "_R"; // R =Rotation 	
		Generate_IsoCurveControls(pCurveIsoTo,indexCR,&strPat_Cur,FALSE);// FALSE = Rotation
	}
	//////////////
	return 0;
}

int CSLEPat::Get_Values_NonIso_Pat(STALPROC StaLProc)
{
	AfxMessageBox("Get_Values_NonIso_Pat\nNOT IMPLEMENTED YET");
	return -1;
}
			
int CSLEPat::Get_Values_Iso_Pat(CDrPatch* pPatch,STALPROC StaLProc,CString& CurrentStPID)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	int nResult;
	////////////////////////////////////////////////////////////////// Initialize
	for(int i=0;i<4;i++)
	{
		if(m_pCurrentSCurveT[i])
			m_pCurrentSCurveT[i] = NULL;
		if(m_pCurrentSCurveR[i])
			m_pCurrentSCurveR[i] = NULL;
	}
	if(!m_CurveList.IsEmpty())
		m_CurveList.RemoveAll();
	if(!m_CurveListT.IsEmpty())
		m_CurveListT.RemoveAll();
	if(!m_CurveListR.IsEmpty())
		m_CurveListR.RemoveAll();
	if(!m_NodeList.IsEmpty())
		m_NodeList.RemoveAll();
	if(!m_NodeListT.IsEmpty())
		m_NodeListT.RemoveAll();
	if(!m_NodeListR.IsEmpty())
		m_NodeListR.RemoveAll();
	//////////////////////////////////////////////////////////////////
	PATCHPROC PatchProc = pPatch->GetPatchProc();	// How was it Generated?
	///////////////////
	switch(PatchProc) 
	{
		
		///////////////////////////////////////////////////// Patches Insert
		case PP_EXTRUDE:

			nResult = Get_Values_Iso_EXTRUDE_Type2(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_ROTATE: 

			Get_Values_Iso_ROTATE(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_LOFT2: 

			Get_Values_Iso_LOFT2(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_DUCT: 

			Get_Values_Iso_DUCT(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_SWEEP:

			Get_Values_Iso_SWEEP(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_LOFT3:		// COONS:		// 
		case PP_LOFT4:
			
			Get_Values_Iso_COONS(pPatch, StaLProc,CurrentStPID);
			//////////////////////////////////////
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_TENSOR:
		case PP_COONS:
		case PP_GORDON:		// GORDONS
		case PP_FLAT:
		case PP_SPAWN:		// Spawn
		case PP_STITCH:		// Stitch
		case PP_LOFTMANY:	
			return -1;

		//////////////////////////////////////////////////
		default:  
			break;
	}
	return 0;
}

int CSLEPat::Get_Values_IsoNod_AnyProc(CString& NodeID,
									STALPROC StaLProc,CString& CurrentStPID,CString& strProc) 
{									
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pDListMgr;
	int nResult,index;
	CDrNode*	pNodeIsoTo;
	/////////////////////////////////////	
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	index		= pDListMgr->GetObjectIndex(NODE, NodeID);
	if(index<0)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		j = sprintf(buf,"CSLEPat::Get_Values_IsoNod_AnyProc\n%s\n%s NodeIndex<0!",strProc,NodeID);
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
		return -1;
	}
	//////////
	pNodeIsoTo	= (CDrNode*)(pDListMgr->GetObject(index));
	if(!pNodeIsoTo)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		j = sprintf(buf,"CSLEPat::Get_Values_IsoNod_AnyProc\n%s\n%s NodePtr = NULL!",strProc,NodeID);
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
		return -1;
	}
	//////////////////////////////////////////// Get Info 
	CString strID;
	strID = CurrentStPID + "_NP";
	nResult = Get_Values_Iso_Node(pNodeIsoTo,StaLProc,strID);
	///////////////
	return nResult;
}


int CSLEPat::Get_Values_IsoCur_AnyProc(CString& CurveID,int iT,int iR,int IndexSkipNode,
					STALPROC StaLProc,CString& CurrentStPID,CString& strProc,BOOL bLastCurve)
{									
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pDListMgr;
	int nResult,index;
	CDrCurve*	pCurveIsoTo;
	///////////////////////////////////////////////////////////////////////// Curve
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	index		= pDListMgr->GetObjectIndex(CURVE, CurveID);
	if(index<0)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		j = sprintf(buf,"CSLEPat::Get_Values_IsoCur_AnyProc\n%s\n%s CurveIndex<0!",strProc,CurveID);
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
		return -1;
	}
	pCurveIsoTo	= (CDrCurve*)(pDListMgr->GetObject(index));
	if(!pCurveIsoTo)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		j = sprintf(buf,"CSLEPat::Get_Values_IsoCur_AnyProc\n%s\n%s CurvePtr = NULL!",strProc,CurveID);
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
		return -1;
	}
	///////////////////////////////////////////////////////////// Get Info 
	CString strID;
	strID = "_" + CurrentStPID;
	nResult = Get_Values_Iso_Pat_Curve(pCurveIsoTo,iT,iR,IndexSkipNode,StaLProc,strID,bLastCurve);
	///////
	return nResult;
}

int CSLEPat::Get_Values_Iso_EXTRUDE_Type1(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	CString strProc = "Get_Values_Iso_EXTRUDE_Type1";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			NodeID,CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////////////////////////////////// Curve
	CurveID	= pPatchIsoTo->GetCurveID(0);
	/////////////////////////////////////
	strCurr = "Ready for Extrusion@";
	strCurr += ("Curve Iso To " + CurveID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoCur_AnyProc(CurveID,0,0,IndexSkipNode,StaLProc,strID,strProc,FALSE);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save in Lists
	if(m_pCurrentSCurveT[0])
		m_CurveListT.AddTail(m_pCurrentSCurveT[0]);
	if(m_pCurrentSCurveR[0])
		m_CurveListR.AddTail(m_pCurrentSCurveR[0]);
	///////////////////////////////////////////////////////////////////////// From ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetFromID_T();
	/////////////////////////////////////
	strCurr = "Ready for Extrusion@";
	strCurr += "Generate: From Node";
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_FromID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_FromID_R = m_pSNodeR->GetObjectID(); 
	///////////////////////////////////////////////////////////////////////// To ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetToID_T();
	/////////////////////////////////////
	strCurr = "Ready for Extrusion@";
	strCurr += "Generate: To Node";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_ToID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_ToID_R = m_pSNodeR->GetObjectID(); 
	///////////////////////////////////////////////////////////////////////// Length (T & R)
/*
	CString wID = "Lengths"
	nResult = Get_Values_Iso_WORLD(wID,pSWorldT,pSWorldR,StaLProc);
	if( nResult <0) //  - 2 = Cancel
		return nResult;
	/////////////////////
	m_Length_T = *pSWorldT; 
	m_Length_R = *pSWorldR;
*/
	//////////
	return 0;

}

int CSLEPat::Get_Values_Iso_EXTRUDE_Type2(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																CString& CurrentStPID)
{
	CString strProc = "Get_Values_Iso_EXTRUDE_Type2";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			NodeID,CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////////////////////////////////// Curve
	CurveID	= pPatchIsoTo->GetCurveID(0);
	/////////////////////////////////////
	strCurr = "Ready for Extrusion@";
	strCurr += ("Curve Iso To " + CurveID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoCur_AnyProc(CurveID,0,0,IndexSkipNode,StaLProc,strID,strProc,FALSE);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save in Lists
	if(m_pCurrentSCurveT[0])
		m_CurveListT.AddTail(m_pCurrentSCurveT[0]);
	if(m_pCurrentSCurveR[0])
		m_CurveListR.AddTail(m_pCurrentSCurveR[0]);
	///////////////////////////////////////////////////////////////////////// Length (T & R)
	CString wID = "Extru.Len";
	/////////////////////////////////////
	strCurr = "Ready for Generating@";
	strCurr += "Extrusion Vectors";
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_Iso_WORLD(wID,m_Len_T,m_Len_R,StaLProc);
	if( nResult <0) //  - 2 = Cancel
		return nResult;
	/////////
	return 0;

}
int CSLEPat::Get_Values_Iso_ROTATE(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	///////////////////////////////
	//	case 1:	CurveTo Rotate;
	//	case 2:	Axis Node From
	//	case 3:	Axis Node To;
	///////////////////////////////
	CString strProc = "Get_Values_Iso_ROTATE_Type2";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			NodeID,CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////////////////////////////////// Curve
	CurveID	= pPatchIsoTo->GetCurveID(0);
	/////////////////////////////////////
	strCurr = "Ready for Rotation@";
	strCurr += ("Curve Iso To " + CurveID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoCur_AnyProc(CurveID,0,0,IndexSkipNode,StaLProc,strID,strProc,FALSE);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save in Lists
	if(m_pCurrentSCurveT[0])
		m_CurveListT.AddTail(m_pCurrentSCurveT[0]);
	if(m_pCurrentSCurveR[0])
		m_CurveListR.AddTail(m_pCurrentSCurveR[0]);
	///////////////////////////////////////////////////////////////////////// From ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetFromID_T();
	/////////////////////////////////////
	strCurr = "Ready for Rot. Axis@";
	strCurr += "Generate: From Node";
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_FromID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_FromID_R = m_pSNodeR->GetObjectID(); 
	///////////////////////////////////////////////////////////////////////// To ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetToID_T();
	/////////////////////////////////////
	strCurr = "Ready for Rot. Axis@";
	strCurr += "Generate: To Node";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_ToID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_ToID_R = m_pSNodeR->GetObjectID(); 
	/////////
	return 0;

}

int CSLEPat::Get_Values_Iso_LOFT2(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	CString strProc = "Get_Values_Iso_LOFT2";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////////////////////////////////// Curve_1
	CurveID	= pPatchIsoTo->GetCurveID(0);
	/////////////////////////////////////
	strCurr = "Ready for Lofting From@";
	strCurr += ("Curve Iso To " + CurveID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoCur_AnyProc(CurveID,0,0,IndexSkipNode,StaLProc,strID,strProc,FALSE);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	///////////////////////////////////////////////////////////////////////// Curve_2
	CurveID	= pPatchIsoTo->GetCurveID(1);
	/////////////////////////////////////
	strCurr = "Ready for Lofting To@";
	strCurr += ("Curve Iso To " + CurveID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoCur_AnyProc(CurveID,1,1,IndexSkipNode,StaLProc,strID,strProc,FALSE);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	///////////////////////////////////////////////////////////////////////// Save in Lists
	for(int i=0;i<2;i++)
	{
		if(m_pCurrentSCurveT[i])
			m_CurveListT.AddTail(m_pCurrentSCurveT[i]);
		if(m_pCurrentSCurveR[i])
			m_CurveListR.AddTail(m_pCurrentSCurveR[i]);
	}
	////////////////////////////////////////////////
	return 0;

}

int CSLEPat::Get_Values_Iso_COONS(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	CString strProc = "Get_Values_Iso_COONS";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*		pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CString			CurveID;
	int				nResult;
	int				IndexSkipNode = -1;
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////
	int nCur = 3;
	if(pPatchIsoTo->GetPatchProc() == PP_LOFT4)
		nCur = 4;
	/////////////
	for(int i=0;i<nCur;i++)
	{
		CurveID	= pPatchIsoTo->GetCurveID(i);
		/////////////////////////////////////
		strCurr = "Ready for Coons Patch@";
		strCurr += ("Curve Iso To " + CurveID);
		//////
		pWnd->UpdateCurrStat(strCurr);
		////////////////////////////////////////////////////// Set Skip Index for 2nd Curve Onward
		if(i>0)
		{
			IndexSkipNode = 0;
			////////////////////////////////////////////////// if Backward, then Last
			CURVELATCH cLatch = pPatchIsoTo->GetCurveLatch(i);
			if(cLatch == CL_BACKWARD)
			{
				int index			= pDListMgr->GetObjectIndex(CURVE, CurveID);
				CDrCurve * pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
				
				IndexSkipNode = pDrCurve->GetINodeList()->GetCount() - 1; //last Node
			}
		}	
		//////////////////////////////////////
		nResult = Get_Values_IsoCur_AnyProc(CurveID,i,i,IndexSkipNode,StaLProc,strID,strProc,(i==nCur-1));
		///////
		if( nResult<0)// -2 = Cancel 
			return nResult;
		/////////////////////////////////////////////// Save in Lists
		if(m_pCurrentSCurveT[i])
			m_CurveListT.AddTail(m_pCurrentSCurveT[i]);
		if(m_pCurrentSCurveR[i])
			m_CurveListR.AddTail(m_pCurrentSCurveR[i]);
	}
	////////////////////////////////////////////////
	return 0;
}

int CSLEPat::Get_Values_Iso_DUCT(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	//////////////////////////////////////////////////
	//		case 0: "Cross Sectional Curve";
	//		case 1: "Spine Curve";
	//		case 2: "Twist Curve";
	//		case 3:	"Anchor Node";
	//////////////////////////////////////////////////
	CString strProc = "Get_Values_Iso_DUCT";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			NodeID,CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////
	int nCur = 3;
	/////////////
	for(int i=0;i<nCur;i++)
	{
		CurveID	= pPatchIsoTo->GetCurveID(i);
		/////////////////////////////////////
		strCurr = "Ready for Ducting@";
		strCurr += ("Curve Iso To " + CurveID);
		//////
		pWnd->UpdateCurrStat(strCurr);
		//////////////////////////////////////
		nResult = Get_Values_IsoCur_AnyProc(CurveID,i,i,IndexSkipNode,StaLProc,strID,strProc,FALSE);
		///////
		if( nResult<0)// -2 = Cancel 
			return nResult;
		/////////////////////////////////////////////// Save in Lists
		if(m_pCurrentSCurveT[i])
			m_CurveListT.AddTail(m_pCurrentSCurveT[i]);
		if(m_pCurrentSCurveR[i])
			m_CurveListR.AddTail(m_pCurrentSCurveR[i]);
	}
	///////////////////////////////////////////////////////////////////////// Anchor Node ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetFromID_T(); //used for AnchorID
	/////////////////////////////////////
	strCurr = "Ready for Ducting@";
	strCurr += "Anchor Node";
	strCurr += ("Anchor Vector at Node " + NodeID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_FromID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_FromID_R = m_pSNodeR->GetObjectID(); 
	/////////
	return 0;
}

int CSLEPat::Get_Values_Iso_SWEEP(CDrPatch* pPatchIsoTo, STALPROC StaLProc
																,CString& CurrentStPID)
{
	//////////////////////////////////////////////////
	//		case 0: "Cross Sectional Curve";
	//		case 1: "Spine Curve";
	//		case 2: "Twist Curve";
	//		case 3: "Radial Distribution Curve"
	//		case 4:	"Anchor Node";
	//////////////////////////////////////////////////
	CString strProc = "Get_Values_Iso_SWEEP";
	////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////
	CDrGrafDoc*		pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr*		pObjectMgr 	= pDoc->GetObjectMgr();
	CString			NodeID,CurveID;
	int				nResult;
	int				IndexSkipNode = -1; 
	//////////////////////////////////////////// naming
	CString strID = pPatchIsoTo->GetObjectID();
	strID += "_" + CurrentStPID;
	///////////////////////////////////////////
	int nCur = 4;
	/////////////
	for(int i=0;i<nCur;i++)
	{
		CurveID	= pPatchIsoTo->GetCurveID(i);
		/////////////////////////////////////
		strCurr = "Ready for Sweeping@";
		strCurr += ("Curve Iso To " + CurveID);
		//////
		pWnd->UpdateCurrStat(strCurr);
		//////////////////////////////////////
		nResult = Get_Values_IsoCur_AnyProc(CurveID,i,i,IndexSkipNode,StaLProc,strID,strProc,FALSE);
		///////
		if( nResult<0)// -2 = Cancel 
			return nResult;
		/////////////////////////////////////////////// Save in Lists
		if(m_pCurrentSCurveT[i])
			m_CurveListT.AddTail(m_pCurrentSCurveT[i]);
		if(m_pCurrentSCurveR[i])
			m_CurveListR.AddTail(m_pCurrentSCurveR[i]);
	}
	///////////////////////////////////////////////////////////////////////// Anchor Node ID
	m_pSNodeT = NULL; 
	m_pSNodeR = NULL; 
	NodeID = pPatchIsoTo->GetFromID_T(); //used for AnchorID
	/////////////////////////////////////
	strCurr = "Ready for Sweeping@";
	strCurr += "Anchor Node";
	strCurr += ("Anchor Vector at Node " + NodeID);
	//////
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////
	nResult = Get_Values_IsoNod_AnyProc(NodeID,StaLProc,strID,strProc);
	///////
	if( nResult<0)// -2 = Cancel 
		return nResult;
	////////////////////////////////////////////// Save
	if(m_pSNodeT)
		m_FromID_T = m_pSNodeT->GetObjectID(); 
	if(m_pSNodeR)
		m_FromID_R = m_pSNodeR->GetObjectID(); 
	/////////
	return 0;
}

int CSLEPat::Generate_IsoPatchControls(CDrPatch* pPatchIsoTo,CString* pID,BOOL bTran)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	int nResult;
	//////////////////////////////////////////////////////////////////
	PATCHPROC PatchProc = pPatchIsoTo->GetPatchProc();	// How was it Generated?
	//////////////////////////////////////////////
	CString strID;
	strID = *pID + "_" + pPatchIsoTo->GetObjectID();
	/////
	nResult = SetUp_IsoPatchControls(pPatchIsoTo,0,&strID,bTran);	// TRUE = Translation
	if(nResult<0)
		return nResult;
	///////////////////
	WORLD		wLen;
	CDrPatch*	pCurrentSPatch;
	///////////////////////////
	if(bTran)
		pCurrentSPatch = m_pCurrentSPatchT[0];
	else
		pCurrentSPatch = m_pCurrentSPatchR[0];
	///////////////////
	switch(PatchProc) 
	{
		
		///////////////////////////////////////////////////// Patches Insert
		case PP_EXTRUDE:

			wLen = m_Len_T;
			if(!bTran)
			wLen = m_Len_R;
			///////////////////////////////////// Save
			pCurrentSPatch->SetWorldLength_T(wLen);
			///////////////////
			nResult = Generate_IsoControls_EXTRUDE(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_ROTATE: 

			///////////////////
			nResult = Generate_IsoControls_ROTATE(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_LOFT2: 

			///////////////////
			nResult = Generate_IsoControls_LOFT2(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_DUCT: 

			///////////////////
			nResult = Generate_IsoControls_DUCT(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_SWEEP:

			///////////////////
			nResult = Generate_IsoControls_SWEEP(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_LOFT3:		// COONS:		// 
		case PP_LOFT4:
			
			///////////////////
			nResult = Generate_IsoControls_COONS(pCurrentSPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_TENSOR:
		case PP_COONS:
		case PP_GORDON:		// GORDONS
		case PP_FLAT:
		case PP_SPAWN:		// Spawn
		case PP_STITCH:		// Stitch
		case PP_LOFTMANY:	
			return -1;

		//////////////////////////////////////////////////
		default:  
			break;
	}
	///////////
	return -1;
}	

int CSLEPat::SetUp_IsoPatchControls(CDrPatch* pPatchIsoTo,int indexP,CString* pID,BOOL bTran)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int			nActiveIndex;
	//////////////////////////////////////////////////////////////////
	CDrPatch* pCurrentSPatch; 
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
// 	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	////////////////////////////////////////////////////// Add to DataBase, if not Existing
	///////////////////////////////////////// delete, if Same Category & Add
	pList = pObjectMgr->GetObjectList(PATCH);
	nActiveIndex = pList->GetObjectIndex(PATCH, *pID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
		pCurrentSPatch = (CDrPatch*)NULL;
	}
	pCurrentSPatch	= (CDrPatch*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,PATCH));
	pCurrentSPatch->SetShow(FALSE);	// not quite ready
	///////////////////////////////////////////////////////// SetIso Tag
	pCurrentSPatch->SetIso(TRUE);	
	///////////////////////////////////////////////////////// OverRide Category 
	CATEGORY	cat;
	///////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:		cat		= CA_FORCE;		break;
		case STL_DISPLACE:	cat		= CA_DISPLACE;	break;
		case STL_PRESSURE:	cat		= CA_PRESSURE;	break;
		case STL_THERMAL:	cat		= CA_THERMAL;	break;
		case STL_LUMPWT:	cat		= CA_LUMPWT;	break;
		default:break;
	}
	////////////////////////////////
	pCurrentSPatch->SetCategory(cat);
	if(bTran)
	{
		pCurrentSPatch->SetSubCat(SC_TRAN);
		m_pCurrentSPatchT[indexP] = pCurrentSPatch;
	}
	else
	{
		pCurrentSPatch->SetSubCat(SC_ROT);
		m_pCurrentSPatchR[indexP] = pCurrentSPatch;
	}
	//////////////////////////////////////////////////////////////////////// Clone
	pCurrentSPatch->SetObjectInfo(pPatchIsoTo);
	pCurrentSPatch->SetShow(FALSE);	// Cloning might have changed it!
	pCurrentSPatch->SetIso(TRUE);
	CString id;
	id = pPatchIsoTo->GetObjectID(); 
	pCurrentSPatch->SetIsoToID(id);
	////////////////////////////////// Reset ID
	pCurrentSPatch->SetObjectID(*pID);
	//////////////
	RemoveMostListsFromPatch(pCurrentSPatch);				//
	/////////////////////////////////////////////////////////////// Fill Input Curves
	m_CurveList.RemoveAll();
	if(bTran)
	{
		m_CurveList.AddTail(&m_CurveListT);	// copy Translational
	}
	else
	{
		m_CurveList.AddTail(&m_CurveListR);	// copy Rotational
	}
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	m_NodeList.RemoveAll();
	if(bTran)
	{
		m_NodeList.AddTail(&m_NodeListT);	// copy Translational
	}
	else
	{
		m_NodeList.AddTail(&m_NodeListR);	// copy Rotational
	}
	//////////////////////////////////
	return 0;
}

int CSLEPat::Generate_IsoControls_EXTRUDE(CDrPatch* pCurrentSPatch,CString* pID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////////////////// Set up
	m_LatchList.RemoveAll();
	m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(0));
	//////////
	int m_nMesh					= pCurrentSPatch->GetMaxOutSeg_T();	// Number of Output Segments
	m_ElSegList.RemoveAll();
	m_ElSegList.AddTail(m_nMesh);
	//////////
	WORLD		wLen			= pCurrentSPatch->GetWorldLength_T();
	double		Ratio			= pCurrentSPatch->GetRatio_T();		
	//////////////////////////////////////////////////////////////// Fill Info
	CMP_Xtrud	MP_Xtrud;
	int nResult = MP_Xtrud.SetInfoBase_Type2(*pID,pCurrentSPatch,&m_CurveList,&m_LatchList,
							&m_NodeList,&m_ElSegList,wLen,Ratio,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Do It
	nResult = MP_Xtrud.GoDoIt(pCurrentSPatch);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CSLEPat::Generate_IsoControls_ROTATE(CDrPatch* pCurrentSPatch,CString* pID)
{
	AfxMessageBox("CSLEPat::Generate_IsoControls_ROTATE\nNOT IMPLEMENTED YET");
	return -1;
}

int CSLEPat::Generate_IsoControls_LOFT2(CDrPatch* pCurrentSPatch,CString* pID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////////////////// Set up
	m_LatchList.RemoveAll();
	m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(0));
	m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(1));
	//////////
	int m_nMesh					= pCurrentSPatch->GetMaxOutSeg_T();	// Number of Output Segments
	m_ElSegList.RemoveAll();
	m_ElSegList.AddTail(m_nMesh);
	//////////
	double		Ratio			= pCurrentSPatch->GetRatio_T();		
	//////////////////////////////////////////////////////////////// Fill Info
	CMP_Loft2	MP_Loft2;
	int nResult = MP_Loft2.SetInfoBase(*pID,pCurrentSPatch,&m_CurveList,&m_LatchList,
							&m_ElSegList,Ratio,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Do It
	nResult = MP_Loft2.GoDoIt(pCurrentSPatch);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CSLEPat::Generate_IsoControls_DUCT(CDrPatch* pCurrentSPatch,CString* pID)
{
	//////////////////////////////////////////////////////////////////////////////
	// Currently(03/05/97):
	//		WE DONOT ALLOW DIFFERENT TWISTMULT, TWISTSTART, SCALEMULT, SCALESTART
	//						FOR DIFFERENT COMPONENTS in:X,Y AND Z
	//							USING VALUES FROM pPatchToIso
	//		SINCE WE PACK FORCES ETC. IN X,Y AND Z DIRECTIONS IN SINGLE PATCH
	//			WE CANNOT ALLOW ANY INPUT BUT TO USE pPatchToIso VALUES
	//		IN LATER VERSION:
	//			WE WILL USE wTwistMult (WORLD) variables for input
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	int i,nResult;
	//////////////////////////////////////////////////////////////// Set up
	m_LatchList.RemoveAll();
	////////////////////////
	for(i=0;i<3;i++)
	{
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(0));
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(1));
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(2));
	}
	//////////
	double		dTwistMult		= pCurrentSPatch->GetTwistMult_T();
	BOOL		bIncrement		= pCurrentSPatch->IsIncTwist_T();		
	double		dTwistStart		= pCurrentSPatch->GetTwistStart_T();		
	////////////////////////////////////////////////// Fill Info
	CMP_Duct	MP_Duct;
	nResult = MP_Duct.SetInfoBase(*pID,pCurrentSPatch,&m_CurveList,&m_NodeList,
							&m_LatchList,dTwistMult,bIncrement,dTwistStart,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Do It
	nResult = MP_Duct.GoDoIt(pCurrentSPatch);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CSLEPat::Generate_IsoControls_SWEEP(CDrPatch* pCurrentSPatch,CString* pID)
{
	//////////////////////////////////////////////////////////////////////////////
	// Currently(03/05/97):
	//		WE DONOT ALLOW DIFFERENT TWISTMULT, TWISTSTART, SCALEMULT, SCALESTART
	//						FOR DIFFERENT COMPONENTS in:X,Y AND Z
	//							USING VALUES FROM pPatchToIso
	//		SINCE WE PACK FORCES ETC. IN X,Y AND Z DIRECTIONS IN SINGLE PATCH
	//			WE CANNOT ALLOW ANY INPUT BUT TO USE pPatchToIso VALUES 
	//		IN LATER VERSION:
	//			WE WILL USE wTwistMult (WORLD) variables for input
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	int i,nResult;
	//////////////////////////////////////////////////////////////// Set up
	m_LatchList.RemoveAll();
	////////////////////////
	for(i=0;i<4;i++)
	{
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(0));
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(1));
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(2));
	}
	//////////
	double		dTwistMult		= pCurrentSPatch->GetTwistMult_T();
	BOOL		bIncrement		= pCurrentSPatch->IsIncTwist_T();		
	double		dTwistStart		= pCurrentSPatch->GetTwistStart_T();		
	double		dRadiusMult		= pCurrentSPatch->GetScaleMult_T();
	BOOL		bIncRad			= pCurrentSPatch->IsIncScale_T();		
	double		dRadStart		= pCurrentSPatch->GetScaleStart_T();		
	////////////////////////////////////////////////// Fill Info
	CMP_Sweep	MP_Sweep;
	nResult = MP_Sweep.SetInfoBase(*pID,pCurrentSPatch,&m_CurveList,&m_NodeList,
							&m_LatchList,dTwistMult,bIncrement,dTwistStart,
							dRadiusMult,bIncRad,dRadStart,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Do It
	nResult = MP_Sweep.GoDoIt(pCurrentSPatch);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CSLEPat::Generate_IsoControls_COONS(CDrPatch* pCurrentSPatch,CString* pID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	int i;
	//////////////////////////////////////////////////////////////// Set up
	PATCHPROC ppKind = pCurrentSPatch->GetPatchProc();
	//////////////////////////////////////////////////
	m_LatchList.RemoveAll();
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_LOFT3) && (i>2))
			continue;
		m_LatchList.AddTail(pCurrentSPatch->GetCurveLatch(i));
	}
	////////////////////////////////////////////////////
	CString		PatCurveID[4];
	CURVELATCH	PatCurveLatch[4];
	POSITION	pos;
	//////////////////////////////////////////////////// Fill Arrays
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_LOFT3) && (i>2))
			continue;
		//////////////////////////////////////////////////////////// ID
		CDrCurve* pDrCurve	= (CDrCurve*)(m_CurveList.GetObject(i) );
		PatCurveID[i] = pDrCurve->GetObjectID();
		//////////////////////////////////////////////////////////// Latch
		pos					= m_LatchList.FindIndex(i);
		PatCurveLatch[i]	= m_LatchList.GetAt(pos);
		////////////////
	}
	////////////////////////// Triangular Patch
	if(ppKind == PP_LOFT3)
	{
		CMP_CooP3	MP_CoonP;
		/////////////////////
		int nResult = MP_CoonP.GoDoIt(*pID,pCurrentSPatch,PatCurveID,
										PatCurveLatch);
		//////////////
		if(nResult<0)
			return -1;
	}
	else
	////////////////////////// Quadrilateral Patch
	if(ppKind == PP_LOFT4)
	{	
		CMP_CoonP	MP_CoonP;
		/////////
		int nResult = MP_CoonP.GoDoIt(*pID,pCurrentSPatch,PatCurveID,
										PatCurveLatch);
		//////////////
		if(nResult<0)
			return -1;
	}
	//////////////////////////////////////////////////////////
	return 0;
}

void CSLEPat::Serialize(CArchive& ar)
{

	CSLECur::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDPat:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDPat:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


