// Rotate.cpp : implementation file
//


#include "stdafx.h"

#include "math.h"
#include "XForm.h"

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
///////////////////// elements
#include "DrLabel.h"
///////////////////// dialogMgr
#include "CreODlgM.h"
#include "Mi_GangN.h"
#include "Dlg_SpnO.h"
////////////////////
#include "MI_OSPN.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define MIN_CNODES_CURVE	4
#define	NUM_LEN				12 
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_OSPN,CMI_SSPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_OSPN::CMI_OSPN()
{
	m_pContextO3D = NULL;
}

CMI_OSPN::~CMI_OSPN()
{
}

int CMI_OSPN::SpawnObj3DShowingDlg(CDrObj3D* pNewObj3D,CDrObj3D* pOldObj3D, 
									CDrObject* pContextObj, UINT nContextType)  
{

	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////////////////////////////
	switch(nContextType)
	{
		case OBJ3D:
			m_pContextO3D = (CDrObj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_OSPN::SpawnObj3DShowingDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrObj3D = pNewObj3D;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	nResult = GetInfoFromDlg(m_pDrObj3D,pOldObj3D);                  	// 
	if(nResult<0)
		return nResult;//
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrObj3D)
	{
		; // do nothing
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Obj3D Spawning Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
*/
	}	
	else
		return -1;	// Cancel
	///////////////////////////////// Spawn Obj3Ds
	MATRIX Mat;
	///////////
	if(m_pDrObj3D->IsInstanced())
	{
		CMatObj* pMatObj	= m_pDrObj3D->GetMatObj();
		Mat					= *(pMatObj->GetMatrix());
	    ////////////////////////////////////////
		if(!pBool->IsSpawnOn())
			nResult = SpawnObj3DCopyOff(&Mat);
		else
			nResult = SpawnObj3D(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	else
	{
		MATRIX Mat;
		C3DMath Math3D;
		Math3D.GetIdentityMATRIX(&Mat);
	    ////////////////////////////////////////
		if(!pBool->IsSpawnOn())
			nResult = SpawnObj3DCopyOff(&Mat);
		else
			nResult = SpawnObj3D(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	///////////////////////////// make it Unposted 
	m_pDrObj3D->SetPosted(FALSE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrObj3D->Calc_3DBoundsLocal();
	/////////
	return 0;		 
}			
	 
int CMI_OSPN::GetInfoFromDlg(CDrObj3D* pNewObj3D,CDrObj3D* pOldObj3D)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreODlgM* 	pMO3DMgr;
	CString		Cid = pNewObj3D->GetObjectID();
	CString		ParentID = pOldObj3D->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMO3DMgr->DoModal_Spawn_O(pNewObj3D,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_OSPN::SpawnObj3D(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CString		Cid;
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInObj3D(pXFMat);
	/////////////////////////////////
	// todo: after changing to String in DrObj3D.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_OSPN::SpawnListsInObj3D(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
/*
	///////////////////////////////////////////////////////////////// Obj3DList
    pList			= m_pDrObj3D->GetObj3DList();
	int nMaxObj3Ds	= pList->GetCount();
	//////////
	if(pList && (nMaxObj3Ds>0))
	{
		nResult = SpawnObj3DListInObj3D(pList,pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DObj3Ds(pList);
	}
*/
	///////////////////////////////////////////////////////////////// SolidList
    pList			= m_pDrObj3D->GetSolidList();
	int nMaxSolids	= pList->GetCount();
	//////////
	if(pList && (nMaxSolids>0))
	{
		nResult = SpawnSolidListInObj3D(pList,pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DSolids(pList);
	}
	///////////////////////////////////////////////////////////////// PatchList
    pList			= m_pDrObj3D->GetPatchList();
	int nMaxPatches	= pList->GetCount();
	//////////
	if(pList && (nMaxPatches>0))
	{
		nResult = SpawnPatchListInObj3D(pList,pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DPatches(pList);
	}
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrObj3D->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListInObj3D(pList,pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DCurves(pList);
	}
	///////////////////////////////////////////////////////////////// NodeLists
    pList = m_pDrObj3D->GetNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinObj3D(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DNodes(pList);
	}
	/////////////////
	return 0;
}

int CMI_OSPN::SpawnNodeListinObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CDListMgr* pTempList = new CDListMgr;
	pTempList->RemoveAll();
	////////////////////////////////////////////////// copy
	pTempList->AddTail(pFillList);
	////////////////////////////////////////////////// Empty it
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes,nActiveIndex;
	CString		NewNID;
	int s;
	/////////////////////////////////////////////////////////// Data
	nMaxNodes		 	= pTempList->GetCount();
	////////////////////////////////////////// 	
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrNode* pOldNode = (CDrNode*)pTempList->RemoveHead();
		/////////////////
		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		BOOL bCNode = pNewNode->IsControlNode(); 
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinObj3D(pOldNode,pNewNode,pXFMat);
		/////////////////////////////////////////////////////
		if(nResult<0)
		{
			/////
			SimilarNode_DeleteFromDataBase(nActiveIndex,bCNode);
			///////////////
			return nResult;
		}
		/////////////////////////////////////////////////////////////////// Label
		int nLabelIndex;
		CMI_GangN GangN;
		CDrLabel* pLabel = GangN.CreateNodeLabel(pNewNode, nLabelIndex,LEVEL_GRAPA);//
		/////////////////////////////////////// Reciprocate
		pNewNode->GetLabelList()->AddTail(pLabel);
		///////////////////////////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pNewNode,CNODE,TRUE);	// ready
		else
			pObjectMgr->ShowObject_On_Off(pNewNode,NODE,TRUE);
		//////////////
		pFillList->InsertObject(pNewNode); //NodeList 

	}				
	///////////////////////////////////////////////////////// Empty it
	delete pTempList;
	////////////
	return 0;
}

int CMI_OSPN::SpawnNodeinObj3D(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat)
{
	/////////////////////////////////////////////////////////// Data
	BOOL bCNode		= pOldNode->IsControlNode();
	CString NewNID	= pNewNode->GetObjectID(); 
	///////////////////////////////////////// Get ID
	int nResult = SpawnNodeWithoutDlg(pNewNode,pOldNode,pXFMat,&NewNID,
												bCNode,m_pDrObj3D,OBJ3D);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return -1;
	////////////
	return 0;
}
	 		
int CMI_OSPN::SpawnCurveListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	TempList.AddTail(pFillList);
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= TempList.GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrCurve* pOldCurve = (CDrCurve*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrCurve* pNewCurve = (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
		///////////////////////
		m_pDrCurve = pNewCurve;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnCurveWithoutDlg(pNewCurve,pOldCurve,pXFMat,&NewCID,
															m_pDrObj3D,OBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(CURVE);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewCurve);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			return -1;
		}
		////////////////
		pFillList->InsertObject(pNewCurve); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 		
int CMI_OSPN::SpawnPatchListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	TempList.AddTail(pFillList);
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= TempList.GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrPatch* pOldPatch = (CDrPatch*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrPatch* pNewPatch = (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
		///////////////////////
		m_pDrPatch = pNewPatch;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnPatchWithoutDlg(pNewPatch,pOldPatch,pXFMat,&NewCID,
															m_pDrObj3D,OBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(PATCH);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewPatch);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
			return -1;
		}
		////////////////
		pFillList->InsertObject(pNewPatch); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 		
int CMI_OSPN::SpawnSolidListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	TempList.AddTail(pFillList);
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= TempList.GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrSolid* pOldSolid = (CDrSolid*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrSolid* pNewSolid = (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
		///////////////////////
		m_pDrSolid = pNewSolid;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnSolidWithoutDlg(pNewSolid,pOldSolid,pXFMat,&NewCID,
															m_pDrObj3D,OBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(SOLID);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewSolid);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, SOLID);
			return -1;
		}
		////////////////
		pFillList->InsertObject(pNewSolid); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 		
int CMI_OSPN::SpawnObj3DListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	TempList.AddTail(pFillList);
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= TempList.GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrObj3D* pOldObj3D = (CDrObj3D*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrObj3D* pNewObj3D = (CDrObj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,OBJ3D));
		///////////////////////
		CMI_OSPN MI_OSPN;
		MI_OSPN.SetpDrObj3D(pNewObj3D);
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = MI_OSPN.SpawnObj3DWithoutDlg(pNewObj3D,pOldObj3D,pXFMat,&NewCID,
															m_pDrObj3D,OBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(OBJ3D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewObj3D);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, OBJ3D);
			return -1;
		}
		////////////////
		pFillList->InsertObject(pNewObj3D); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 
int CMI_OSPN::SpawnObj3DCopyOff(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CString		Cid;
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInObj3DCopyOff(pXFMat);
	/////////////////////////////////
	// todo: after changing to String in DrObj3D.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_OSPN::SpawnListsInObj3DCopyOff(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
/*
	///////////////////////////////////////////////////////////////// Obj3DList
    pList			= m_pDrObj3D->GetObj3DList();
	int nMaxObj3Ds	= pList->GetCount();
	//////////
	if(pList && (nMaxObj3Ds>0))
	{
		nResult = SpawnObj3DListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
*/
	///////////////////////////////////////////////////////////////// SolidList
    pList			= m_pDrObj3D->GetSolidList();
	int nMaxSolids	= pList->GetCount();
	//////////
	if(pList && (nMaxSolids>0))
	{
		nResult = SpawnSolidListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// PatchList
    pList			= m_pDrObj3D->GetPatchList();
	int nMaxPatches	= pList->GetCount();
	//////////
	if(pList && (nMaxPatches>0))
	{
		nResult = SpawnPatchListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrObj3D->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// NodeLists
    pList = m_pDrObj3D->GetNodeList();
	if(pList)
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return -1;
	}
	/////////////////
	return 0;
}

int CMI_OSPN::SpawnObj3DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(OBJ3D);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrObj3D* pSolid = (CDrObj3D*)pFillList->GetObject( s);
		if(GetODoneList()->GetObjectIndex(pSolid) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrObj3D* pTempSolid = m_pDrObj3D;
		m_pDrObj3D = pSolid;
		pObjectMgr->ShowObject_On_Off(pSolid,OBJ3D,FALSE);
		/////////
		nResult = SpawnObj3DCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pSolid,OBJ3D,TRUE);
		m_pDrObj3D = pTempSolid;
		GetODoneList()->InsertObject(pSolid);
		////////
	}				
	/////////
	return 0;
}

void CMI_OSPN::ReciprocateObj3DNodes(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxNodes;
	nMaxNodes = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrNode* pNewNode	= (CDrNode*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewNode->GetObj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_OSPN::ReciprocateObj3DCurves(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrCurve* pNewCurve	= (CDrCurve*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewCurve->GetObj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_OSPN::ReciprocateObj3DPatches(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrPatch* pNewPatch	= (CDrPatch*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewPatch->GetObj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_OSPN::ReciprocateObj3DSolids(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrSolid* pNewSolid	= (CDrSolid*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewSolid->GetObj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_OSPN::ReciprocateObj3DObj3Ds(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrObj3D* pNewObj3D	= (CDrObj3D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewObj3D->GetObj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}
	 		
int CMI_OSPN::SpawnObj3DWithoutDlg(CDrObj3D* pNewObj3D,CDrObj3D* pOldObj3D,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case OBJ3D:
			m_pContextO3D	= (CDrObj3D*)pContextObj;
			Obj3DID			= pOldObj3D->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_OSPN::SpawnObj3DWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
		pObjectMgr->SetObjInfoID(*pCid,OBJ3D);
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrObj3D = pNewObj3D;
	//////////////////////////
	if(m_pDrObj3D != pOldObj3D)	// Copy ON
	{	
		nResult = FillSpawnedObj3DDlgDataBase(m_pDrObj3D,*pCid, Obj3DID);
		if(nResult<0)
			return nResult;
	}
   ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
		nResult = SpawnObj3DCopyOff(pXFMat);
	else
		nResult = SpawnObj3D(pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrObj3D->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_OSPN::FillSpawnedObj3DDlgDataBase(CDrObj3D* pDrObj3D,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnO	Dlg_SpnO;		
	////////////////////////////////////
	Dlg_SpnO.m_SpawnID		= Cid;
	Dlg_SpnO.m_bInstanced 	= FALSE;
	Dlg_SpnO.m_CID		 	= ParentCid;
	Dlg_SpnO.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnO.SetInfoForDataBase(pDrObj3D);
	///////////////
    return 0;
}

void CMI_OSPN::Serialize(CArchive& ar)
{

	CMI_CSPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_OSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_OSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////