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
#include "Mi_GangS.h"
#include "Dlg_SpnS.h"
#include "RegenSol.h"
#include "MI_LSupp.h"
////////////////////
#include "MI_SSPN.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define MIN_CNODES_CURVE	4
#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_SSPN,CMI_PSPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_SSPN::CMI_SSPN()
{
	m_pContextSol = NULL;
}

CMI_SSPN::~CMI_SSPN()
{
}

int CMI_SSPN::SpawnSolidShowingDlg(CDrSolid* pNewSolid,CDrSolid* pOldSolid, 
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
		case SOLID:
			m_pContextSol = (CDrSolid*)pContextObj;
			break;
		case OBJ3D:
			m_pContextO3D = (CDrObj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_SSPN::SSpawn\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrSolid = pNewSolid;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	nResult = GetInfoFromDlg(m_pDrSolid,pOldSolid);                  	// 
	if(nResult<0)
		return nResult;//
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrSolid)
	{
		; // do nothing
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Solid Spawning Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
*/
	}	
	else
		return -1;	// Cancel
	///////////////////////////////// Spawn Solids
	MATRIX Mat;
	///////////
	if(m_pDrSolid->IsInstanced())
	{
		CMatObj* pMatObj	= m_pDrSolid->GetMatObj();
		Mat					= *(pMatObj->GetMatrix());
	    ////////////////////////////////////////
		if(!pBool->IsSpawnOn())
			nResult = SpawnSolidCopyOff(&Mat);
		else
			nResult = SpawnSolid(&Mat);
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
			nResult = SpawnSolidCopyOff(&Mat);
		else
			nResult = SpawnSolid(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	///////////////////////////// make it Unposted 
	m_pDrSolid->SetPosted(FALSE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();
	/////////
	return 0;		 
}			
	 
int CMI_SSPN::GetInfoFromDlg(CDrSolid* pNewSolid,CDrSolid* pOldSolid)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreODlgM* 	pMSolMgr;
	CString		Cid = pNewSolid->GetObjectID();
	CString		ParentID = pOldSolid->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMSolMgr->DoModal_Spawn_S(pNewSolid,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_SSPN::SpawnSolid(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInSolid(pXFMat);
	/////////////////////////////////////////////////////////// Node Spawn : FromID_R
	CDrNode* pOldNode;
	//////////////////
	pOldNode = m_pDrSolid->GetFromIDNode_R();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinSolid(pOldNode,pNewNode,pXFMat);
		/////////////////////////////////////////////////////
		BOOL bCNode = pNewNode->IsControlNode(); 
		if(nResult<0)
		{
			SimilarNode_DeleteFromDataBase(nActiveIndex,bCNode);
			///////////////
			return nResult;
		}
		////////////////////////////////////////////////////////////////////// Show
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pNewNode,CNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pNewNode,NODE,TRUE);
		//////////////
		m_pDrSolid->SetFromIDNode_R(pNewNode);
	}
	/////////////////////////////////////////////////////////// Node Spawn : ToID_R
	pOldNode = m_pDrSolid->GetToIDNode_R();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinSolid(pOldNode,pNewNode,pXFMat);
		/////////////////////////////////////////////////////
		BOOL bCNode = pNewNode->IsControlNode(); 
		if(nResult<0)
		{
			SimilarNode_DeleteFromDataBase(nActiveIndex,bCNode);
			///////////////
			return nResult;
		}
		////////////////////////////////////////////////////////////////////// Show
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pNewNode,CNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pNewNode,NODE,TRUE);
		//////////////
		m_pDrSolid->SetToIDNode_R(pNewNode);
	}
	/////////////////////////////
	/////////////////////////////////
	// todo: after changing to String in DrPatch.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_SSPN::SpawnListsInSolid(pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
	///////////////////////////////////////////////////////////////// PatchList
    pList			= m_pDrSolid->GetPatchList();
	int nMaxPatches	= pList->GetCount();
	//////////
	if(pList && (nMaxPatches>0))
	{
		nResult = SpawnPatchListInSolid(pList,pXFMat);
		if(nResult<0)
			return -1;
/*
		///////////////////////////////////////////////////////// COONs:Remove Duplicate Edge Nodes todo
		//?????????????todo	 Circular Curves:  ?????????????????????????????????
		if	(
				(m_pDrSolid->GetSolidProc() == PP_COONS) || 
				(m_pDrSolid->GetSolidProc() == PP_LOFT3) ||
				(m_pDrSolid->GetSolidProc() == PP_LOFT4) 
			)
*/
		////////////////////////////// Reciprocate
		ReciprocateSolidPatches(pList);
	}
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrSolid->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListInSolid(pList,pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidCurves(pList);
	}
	///////////////////////////////////////////////////////////////// NodeLists
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrSolid->GetCNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pList);
	}
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrSolid->GetCN_BSList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pList);
	}
	/////////////////////////////////////////////////////////// INode
    pList = m_pDrSolid->GetINodeList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pList);
	}
	/////////////////////////////////////////////////////////// VNode
    pList = m_pDrSolid->GetVNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pList);
	}
	/////////////////////////////////////////////////////////// Elem
//	Center for Circle_By_Rot/Circle_By_3No w/o Arc
    pList = m_pDrSolid->GetElemList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateCurveNodes(pList);
	}
	/////////////////////////////////////////////////////////// Node
    pList = m_pDrSolid->GetNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinSolid(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pList);
	}
	/////////////////////////////////////////////////////////// Support
	int nSupp = m_pDrSolid->GetSuppList()->GetCount();
	if(nSupp>0)
	{
		///
		CDrLinSup* pSupp = (CDrLinSup*)(m_pDrSolid->GetSuppList()->GetHead());
		SUPPCARD supCard = *(pSupp->GetSuppCard());
		///
		m_pDrSolid->GetSuppList()->RemoveAll();
		///
		CMI_LSupp MI_LSupp;
//todo		MI_LSupp.CreateListSolidBased(m_pDrSolid,supCard,nSupp);
	}
	//////////////////////////////////////////////////////////////// Penta List 
	CString Cid = m_pDrSolid->GetParentID();
	////
	SpawnPentaList(Cid, pXFMat);
	/////////////////
	return 0;
}

int CMI_SSPN::SpawnNodeListinSolid(CDListMgr* pFillList, pMATRIX pXFMat)
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
		nResult = SpawnNodeinSolid(pOldNode,pNewNode,pXFMat);
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

int CMI_SSPN::SpawnNodeinSolid(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat)
{
	/////////////////////////////////////////////////////////// Data
	BOOL bCNode		= pOldNode->IsControlNode();
	CString NewNID	= pNewNode->GetObjectID(); 
	///////////////////////////////////////// Get ID
	int nResult = SpawnNodeWithoutDlg(pNewNode,pOldNode,pXFMat,&NewNID,
												bCNode,m_pDrSolid,SOLID);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return -1;
	////////////
	return 0;
}

int CMI_SSPN::SpawnPentaList(CString Cid, pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	int index;
	CDrSolid* pOldSolid;
	/////////
	index = pObjectMgr->GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
		pOldSolid = (CDrSolid*)(pDListMgr->GetObject(index));
	else
		pOldSolid = NULL;
		////////////////
	if(pOldSolid)
	{
		CDListMgr* pOldList = pOldSolid->GetPentaList();
		if(pOldList->IsEmpty() )
			return 0;
		////////////////////////
		CDListMgr* pNewList = m_pDrSolid->GetPentaList();
		pNewList->RemoveAll();
		////////////////////////////////////////////////// copy
		POSITION pos = pOldList->GetFirstObjectPos();
		for (;pos !=NULL;)
			pNewList->AddTail(pOldList->GetNextObject( pos));
		///////
	}
	/////////
	return 0;
}
	 		
int CMI_SSPN::SpawnCurveListInSolid(CDListMgr* pFillList, pMATRIX pXFMat)
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
															m_pDrSolid,SOLID);
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
		/////////////////////// Put CurvIDs in Solid
		m_pDrSolid->SetCurveID(NewCID,s);
		////////////////
		pFillList->InsertObject(pNewCurve); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 		
int CMI_SSPN::SpawnPatchListInSolid(CDListMgr* pFillList, pMATRIX pXFMat)
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
															m_pDrSolid,SOLID);
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
		/////////////////////// Put CurvIDs in Solid
		m_pDrSolid->SetCurveID(NewCID,s);
		////////////////
		pFillList->InsertObject(pNewPatch); //CNodeList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 
int CMI_SSPN::SpawnSolidCopyOff(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInSolidCopyOff(pXFMat);
	//////////
	CDrNode* pOldNode;
	////////////////////////////////////////////////////////////////// Node Spawn : FromID_T
	pOldNode = m_pDrSolid->GetFromIDNode_R();
	////////////////
	if(pOldNode)
	{
		nResult = SpawnNodeCopyOff(pOldNode,  pXFMat, TRUE);
		///////////////////////
		if(nResult<0)
			return nResult;
	}
	////////////////////////////////////////////////////////////////// Node Spawn : ToID_T
	pOldNode = m_pDrSolid->GetToIDNode_R();
	////////////////
	if(pOldNode)
	{
		nResult = SpawnNodeCopyOff(pOldNode,  pXFMat, TRUE);
		///////////////////////
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////
	// todo: after changing to String in DrSolid.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_SSPN::SpawnListsInSolidCopyOff(pMATRIX pXFMat)
{
	////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
/*
	///////////////////////////////////////////////////////////////// Connected SolidList
    pList			= m_pDrSolid->GetSolidList();
	int nMaxSolids	= pList->GetCount();
	//////////
	if(pList && (nMaxSolids>0))
	{
		nResult = SpawnSolidListCopyOff(pList,pXFMat);
		if(nResult<0)
			return nResult;
	}
*/
	///////////////////////////////////////////////////////////////// PatchList
    pList			= m_pDrSolid->GetPatchList();
	int nMaxPatches	= pList->GetCount();
	//////////
	if(pList && (nMaxPatches>0))
	{
		nResult = SpawnPatchListCopyOff(pList,pXFMat);
		if(nResult<0)
			return nResult;
	}
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrSolid->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListCopyOff(pList,pXFMat);
		if(nResult<0)
			return -1;
	}
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrSolid->GetCNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrSolid->GetCN_BSList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// INode
    pList = m_pDrSolid->GetINodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// VNode
    pList = m_pDrSolid->GetVNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// Node
    pList = m_pDrSolid->GetNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// Support etc.
	if(!(m_pDrSolid->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
/*todo
		if(m_pDrSolid->GetSolSubType() == PS_QUADRILAT)
			MI_LSupp.RegenPatchBased_4(m_pDrPatch);
		else
		if(m_pDrPatch->GetSolSubType() == PS_TRIANGLE)
			MI_LSupp.RegenPatchBased_3(m_pDrPatch);
*/
	}
	//////////////////////////////////////////////////////////// Static Load, if any
	///////////////////////////////////////////////
	if(nResult<0)
		return nResult;
	/////////////////
	return 0;
}

int CMI_SSPN::SpawnSolidListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrSolid* pSolid = (CDrSolid*)pFillList->GetObject( s);
		if(GetSDoneList()->GetObjectIndex(pSolid) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrSolid* pTempSolid = m_pDrSolid;
		m_pDrSolid = pSolid;
		pObjectMgr->ShowObject_On_Off(pSolid,SOLID,FALSE);
		/////////
		nResult = SpawnSolidCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pSolid,SOLID,TRUE);
		m_pDrSolid = pTempSolid;
		GetSDoneList()->InsertObject(pSolid);
		////////
	}				
	/////////
	return 0;
}
	 		
void CMI_SSPN::ReciprocateSolidNodes(CDListMgr* pList)
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
		pNewNode->GetSolidList()->InsertObject(m_pDrSolid);
		////////
	}
}

void CMI_SSPN::ReciprocateSolidCurves(CDListMgr* pList)
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
		pNewCurve->GetSolidList()->InsertObject(m_pDrSolid);
		////////
	}
}

void CMI_SSPN::ReciprocateSolidPatches(CDListMgr* pList)
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
		pNewPatch->GetSolidList()->InsertObject(m_pDrSolid);
		////////
	}
}
	 		
int CMI_SSPN::SpawnSolidWithoutDlg(CDrSolid* pNewSolid,CDrSolid* pOldSolid,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		SolidID="",Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case SOLID:
			m_pContextSol	= (CDrSolid*)pContextObj;
			SolidID			= pOldSolid->GetObjectID();  	
			break;
		case OBJ3D:
			m_pContextO3D	= (CDrObj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			SolidID			= pOldSolid->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_SSPN::SpawnSolidWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
		pObjectMgr->SetObjInfoID(*pCid,SOLID);
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrSolid = pNewSolid;
	/////////////////////
	if(m_pDrSolid != pOldSolid)	// Copy ON
	{	
		SOLIDPROC	SProc;
		SProc		= pOldSolid->GetSolidProc();
		//////////////////////////
		m_pDrSolid->SetSolidProc(SProc);	// New Solid
		nResult = FillSpawnedSolidDlgDataBase(m_pDrSolid,*pCid, SolidID);
		if(nResult<0)
			return nResult;
	}
    ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
		nResult = SpawnSolidCopyOff(pXFMat);
	else
		nResult = SpawnSolid(pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_SSPN::FillSpawnedSolidDlgDataBase(CDrSolid* pDrSolid,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnS	Dlg_SpnS;		
	////////////////////////////////////
	Dlg_SpnS.m_SpawnID		= Cid;
	Dlg_SpnS.m_bInstanced 	= FALSE;
	Dlg_SpnS.m_CID		 	= ParentCid;
	Dlg_SpnS.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnS.SetInfoForDataBase(pDrSolid);
	///////////////
    return 0;
}

void CMI_SSPN::Serialize(CArchive& ar)
{

	CMI_CSPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_SSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_SSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
