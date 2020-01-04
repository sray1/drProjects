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
#include "CreMDlgM.h"
//#include "Mi_GangS.h"
#include "Mlg_SpnO.h"
////////////////////
#include "MI_MSPN.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define MIN_CFE0DS_MESH1D	4
#define	NUM_LEN				12 
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_MSPN,CMI_3SPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_MSPN::CMI_MSPN()
{
	m_pContextO3D = NULL;
}

CMI_MSPN::~CMI_MSPN()
{
}

int CMI_MSPN::SpawnObj3DShowingDlg(CDrMbj3D* pNewObj3D,CDrMbj3D* pOldObj3D, 
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
		case MBJ3D:
			m_pContextO3D = (CDrMbj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_MSPN::SpawnObj3DShowingDlg\nILLEGAL nContextType");
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
	 
int CMI_MSPN::GetInfoFromDlg(CDrMbj3D* pNewObj3D,CDrMbj3D* pOldObj3D)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreMDlgM* 	pMO3DMgr;
	CString		Cid = pNewObj3D->GetObjectID();
	CString		ParentID = pOldObj3D->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMO3DMgr->DoModal_Spawn_O(pNewObj3D,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_MSPN::SpawnObj3D(pMATRIX pXFMat)
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

int CMI_MSPN::SpawnListsInObj3D(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
/*
	///////////////////////////////////////////////////////////////// Obj3DList
    pList			= m_pDrObj3D->GetMbj3DList();
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
	///////////////////////////////////////////////////////////////// Mesh3DList
    pList			= m_pDrObj3D->GetMs3List();
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
	///////////////////////////////////////////////////////////////// Mesh2DList
    pList			= m_pDrObj3D->GetMs2List();
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
	///////////////////////////////////////////////////////////////// Mesh1DList
    pList			= m_pDrObj3D->GetMs1List();
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
	///////////////////////////////////////////////////////////////// Mesh0DList
    pList = m_pDrObj3D->GetNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinObj3D(pList, pXFMat, FALSE);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateObj3DNodes(pList);
	}
	/////////////////
	return 0;
}

int CMI_MSPN::SpawnNodeListinObj3D(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	////////////////////////////////////////////////// copy
	POSITION pos = pFillList->GetFirstObjectPos();
	for (;pos !=NULL;)
		TempList.AddTail(pFillList->GetNextObject( pos));
	////////////////////////////////////////////////// Empty it
	pFillList->RemoveAll();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewNID;
	int s;
	/////////////////////////////////////////////////////////// Data
	nMaxNodes		 	= TempList.GetCount();
	////////////////////////////////////////// 	
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrFE0D* pOldNode = (CDrFE0D*)TempList.GetObject( s);
		//////////////////////////////////////////////////////////////////////
		//		CONTROL Nodes are Private
		//////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////  New
		int			nActiveIndex;
		CDrFE0D*	pNewNode;
		/////////////////////
		if(bCNode)
		{
			CNewObjs NewObjs;
			pNewNode = (CDrFE0D*)(NewObjs.NewObject(FE0D));
		}
		else
			pNewNode = (CDrFE0D*)(pObjectMgr->AddToDataBase(nActiveIndex,FE0D));
		/////////////////////
		m_pDrNode = pNewNode;
		///////////////////////////////////////// Get ID
		NewNID = "";	// force it to create a name
		int nResult = SpawnNodeWithoutDlg(pNewNode,pOldNode,pXFMat,&NewNID,
													bCNode,m_pDrObj3D,MBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(FE0D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewNode);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, FE0D);
			return -1;
		}
		//////////////
		pFillList->InsertObject(pNewNode); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	////////////
	return 0;
}
	 		
int CMI_MSPN::SpawnCurveListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	////////////////////////////////////////////////// copy
	POSITION pos = pFillList->GetFirstObjectPos();
	for (;pos !=NULL;)
		TempList.AddTail(pFillList->GetNextObject( pos));
	////////////////////////////////////////////////// Empty it
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
		CDrMesh1D* pOldCurve = (CDrMesh1D*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrMesh1D* pNewCurve = (CDrMesh1D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH1D));
		///////////////////////
		m_pDrCurve = pNewCurve;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnCurveWithoutDlg(pNewCurve,pOldCurve,pXFMat,&NewCID,
															m_pDrObj3D,MBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(MESH1D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewCurve);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, MESH1D);
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
	 		
int CMI_MSPN::SpawnPatchListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH2D);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	////////////////////////////////////////////////// copy
	POSITION pos = pFillList->GetFirstObjectPos();
	for (;pos !=NULL;)
		TempList.AddTail(pFillList->GetNextObject( pos));
	////////////////////////////////////////////////// Empty it
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
		CDrMesh2D* pOldPatch = (CDrMesh2D*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrMesh2D* pNewPatch = (CDrMesh2D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH2D));
		///////////////////////
		m_pDrPatch = pNewPatch;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnPatchWithoutDlg(pNewPatch,pOldPatch,pXFMat,&NewCID,
															m_pDrObj3D,MBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(MESH2D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewPatch);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, MESH2D);
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
	 		
int CMI_MSPN::SpawnSolidListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH3D);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	////////////////////////////////////////////////// copy
	POSITION pos = pFillList->GetFirstObjectPos();
	for (;pos !=NULL;)
		TempList.AddTail(pFillList->GetNextObject( pos));
	////////////////////////////////////////////////// Empty it
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
		CDrMesh3D* pOldSolid = (CDrMesh3D*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrMesh3D* pNewSolid = (CDrMesh3D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH3D));
		///////////////////////
		m_pDrSolid = pNewSolid;
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = SpawnSolidWithoutDlg(pNewSolid,pOldSolid,pXFMat,&NewCID,
															m_pDrObj3D,MBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(MESH3D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewSolid);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, MESH3D);
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
	 		
int CMI_MSPN::SpawnObj3DListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MBJ3D);
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	////////////////////////////////////////////////// copy
	POSITION pos = pFillList->GetFirstObjectPos();
	for (;pos !=NULL;)
		TempList.AddTail(pFillList->GetNextObject( pos));
	////////////////////////////////////////////////// Empty it
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
		CDrMbj3D* pOldObj3D = (CDrMbj3D*)TempList.GetObject( s);
		/////////////////////////////////////////////////////////////////  New
		int nActiveIndex;
		CDrMbj3D* pNewObj3D = (CDrMbj3D*)(pObjectMgr->AddToDataBase(nActiveIndex,MBJ3D));
		///////////////////////
		CMI_MSPN MI_OSPN;
		MI_OSPN.SetpDrObj3D(pNewObj3D);
		///////////////////////////////////////// Get ID
		NewCID = "";	// force it to create a name
		int nResult = MI_OSPN.SpawnObj3DWithoutDlg(pNewObj3D,pOldObj3D,pXFMat,&NewCID,
															m_pDrObj3D,MBJ3D);
		///////////////////////////////////// in Curve 
		if(nResult<0)
		{
			///////////////////////////////////////// delete
			pDListMgr = pObjectMgr->GetObjectList(MBJ3D);
			nActiveIndex = pDListMgr->GetObjectIndex(pNewObj3D);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex, MBJ3D);
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
	 
int CMI_MSPN::SpawnObj3DCopyOff(pMATRIX pXFMat)
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

int CMI_MSPN::SpawnListsInObj3DCopyOff(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
	///////////////////////////////////////////////////////////////// Obj3DList
    pList			= m_pDrObj3D->GetMbj3DList();
	int nMaxObj3Ds	= pList->GetCount();
	//////////
	if(pList && (nMaxObj3Ds>0))
	{
		nResult = SpawnObj3DListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// Mesh3DList
    pList			= m_pDrObj3D->GetMs3List();
	int nMaxSolids	= pList->GetCount();
	//////////
	if(pList && (nMaxSolids>0))
	{
		nResult = SpawnSolidListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// Mesh2DList
    pList			= m_pDrObj3D->GetMs2List();
	int nMaxPatches	= pList->GetCount();
	//////////
	if(pList && (nMaxPatches>0))
	{
		nResult = SpawnPatchListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// Mesh1DList
    pList			= m_pDrObj3D->GetMs1List();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	///////////////////////////////////////////////////////////////// NodeLists
    pList = m_pDrObj3D->GetFE0DList();
	if(pList)
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return -1;
	}
	/////////////////
	return 0;
}

int CMI_MSPN::SpawnObj3DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MBJ3D);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrMbj3D* pSolid = (CDrMbj3D*)pFillList->GetObject( s);
		if(GetODoneList()->GetObjectIndex(pSolid) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrMbj3D* pTempSolid = m_pDrObj3D;
		m_pDrObj3D = pSolid;
		pObjectMgr->ShowObject_On_Off(pSolid,MBJ3D,FALSE);
		/////////
		nResult = SpawnObj3DCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pSolid,MBJ3D,TRUE);
		m_pDrObj3D = pTempSolid;
		GetODoneList()->InsertObject(pSolid);
		////////
	}				
	/////////
	return 0;
}

void CMI_MSPN::ReciprocateObj3DNodes(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxNodes,index;
	nMaxNodes = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrFE0D* pNewNode	= (CDrFE0D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		index = pNewNode->GetMbj3DList()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewNode->GetMbj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_MSPN::ReciprocateObj3DCurves(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves,index;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrMesh1D* pNewCurve	= (CDrMesh1D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		index = pNewCurve->GetMbj3DList()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewCurve->GetMbj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_MSPN::ReciprocateObj3DPatches(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves,index;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrMesh2D* pNewPatch	= (CDrMesh2D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		index = pNewPatch->GetMbj3DList()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewPatch->GetMbj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_MSPN::ReciprocateObj3DSolids(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves,index;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrMesh3D* pNewSolid	= (CDrMesh3D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		index = pNewSolid->GetMbj3DList()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewSolid->GetMbj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}

void CMI_MSPN::ReciprocateObj3DObj3Ds(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxCurves,index;
	nMaxCurves = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxCurves; s++)
	{
		CDrMbj3D* pNewObj3D	= (CDrMbj3D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		index = pNewObj3D->GetMbj3DList()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewObj3D->GetMbj3DList()->InsertObject(m_pDrObj3D);
		////////
	}
}
	 		
int CMI_MSPN::SpawnObj3DWithoutDlg(CDrMbj3D* pNewObj3D,CDrMbj3D* pOldObj3D,pMATRIX pXFMat,
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
		case MBJ3D:
			m_pContextO3D	= (CDrMbj3D*)pContextObj;
			Obj3DID			= pOldObj3D->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_MSPN::SpawnObj3DWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
	{
		char buf[50];
		int nLastNum = pObjectMgr->GetLastObjectNo(MBJ3D);		// internal
		sprintf(buf,"%d",nLastNum);
		(*pCid) = "_O";
		(*pCid)	+= buf;
		pObjectMgr->BumpLastObjectNo(MBJ3D);		// bump it
	}
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

int CMI_MSPN::FillSpawnedObj3DDlgDataBase(CDrMbj3D* pDrObj3D,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnO	Dlg_SpnO;		
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

void CMI_MSPN::Serialize(CArchive& ar)
{

	CMI_3SPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_MSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_MSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
