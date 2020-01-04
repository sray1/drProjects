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
#include "Dlg_SpnP.h"
#include "RegenPat.h"
#include "MI_LSupp.h"
#include "MI_StaL.h"
////////////////////
#include "MI_PSPN.h" 

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
IMPLEMENT_SERIAL(CMI_PSPN,CMI_CSPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_PSPN::CMI_PSPN()
{
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_PSPN::~CMI_PSPN()
{
}

int CMI_PSPN::SpawnPatchShowingDlg(CDrPatch* pNewPatch,CDrPatch* pOldPatch, 
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
		case PATCH:
			m_pContextPat = (CDrPatch*)pContextObj;
			break;
		case SOLID:
			m_pContextSol = (CDrSolid*)pContextObj;
			break;
		case OBJ3D:
			m_pContextO3D = (CDrObj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_PSPN::PSpawn\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrPatch = pNewPatch;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	nResult = GetInfoFromDlg(m_pDrPatch,pOldPatch);                  	// 
	if(nResult<0)
		return nResult;//
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrPatch)
	{
		; // do nothing
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Patch Spawning Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
*/
	}	
	else
		return -1;	// Cancel
	///////////////////////////////// Spawn Patches
	MATRIX Mat;
	///////////
	if(m_pDrPatch->IsInstanced())
	{
		CMatObj* pMatObj	= m_pDrPatch->GetMatObj();
		Mat					= *(pMatObj->GetMatrix());
	    ////////////////////////////////////////
		if(!pBool->IsSpawnOn())
			nResult = SpawnPatchCopyOff(&Mat);
		else
			nResult = SpawnPatch(&Mat);
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
			nResult = SpawnPatchCopyOff(&Mat);
		else
			nResult = SpawnPatch(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	///////////////////////////// make it Unposted 
	m_pDrPatch->SetPosted(FALSE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrPatch->Calc_3DBoundsLocal();
	/////////
	return 0;		 
}			
	 
int CMI_PSPN::GetInfoFromDlg(CDrPatch* pNewPatch,CDrPatch* pOldPatch)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreODlgM* 	pMPatMgr;
	CString		Cid = pNewPatch->GetObjectID();
	CString		ParentID = pOldPatch->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMPatMgr->DoModal_Spawn_P(pNewPatch,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_PSPN::SpawnPatch(pMATRIX pXFMat)
{
	int			nResult = 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInPatch(pXFMat);
	/////////////////////////////////////////////////////////// Node Spawn : FromID_T
	CDrNode* pOldNode;
	//////////////////
	pOldNode = m_pDrPatch->GetFromIDNode_T();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinPatch(pOldNode,pNewNode,pXFMat);
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
		m_pDrPatch->SetFromIDNode_T(pNewNode);
	}
	/////////////////////////////////////////////////////////// Node Spawn : ToID_T
	pOldNode = m_pDrPatch->GetToIDNode_T();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinPatch(pOldNode,pNewNode,pXFMat);
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
		m_pDrPatch->SetToIDNode_T(pNewNode);
	}
	/////////////////////////////
	/////////////////////////////////
	// todo: after changing to String in DrPatch.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_PSPN::SpawnListsInPatch(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrPatch->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListInPatch(pList,pXFMat);
		if(nResult<0)
			return -1;
		///////////////////////////////////////////////////////// COONs:Remove Duplicate Corner Nodes
		/////////////////////////////////////////////////////////// INODE HANDLE
		// Last One ADDITIONAL COPY HANDLE Node 
		// for m_nInputType = CIRCLE_BY_ROT
		// for m_nInputType = CIRCLE_BY_NO3 with !m_bArc
		////////////////////////////////////////////////////
		if	(
				(m_pDrPatch->GetPatchProc() == PP_COONS) || 
				(m_pDrPatch->GetPatchProc() == PP_COONSTRI) ||
				(m_pDrPatch->GetPatchProc() == PP_COONSQUAD) 
			)
		{
			CDListMgr* pDListMgr;
			pDListMgr = pObjectMgr->GetObjectList(NODE);
			int nNodeIndex,nLabelIndex;
			///////////////////
			CDrLabel* pDrLabel;
			CDrNode* pIstHeadNode;
			CDrNode* pLastTailNode;
			CDrNode* pCurrHeadNode;
			CDrNode* pCurrTailNode;
			CDrCurve* pNewCurve;
			///
			pNewCurve	= (CDrCurve*)pList->GetObject(0);
			///
			pIstHeadNode	= (CDrNode*)((pNewCurve->GetINodeList())->GetHead());	// Ist Curve
			pLastTailNode	= (CDrNode*)((pNewCurve->GetINodeList())->GetTail());
			/////////////////////////////////////////// if, Circular
			int		nInputType	= pNewCurve->GetInputType();
			BOOL	bArc		= pNewCurve->IsArcType();
			//
			if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
				pLastTailNode	= (CDrNode*)pNewCurve->GetVNodeList()->GetHead();
			/////////////////////////////////////////////////////////////////////
			//	When the Nodes are deleted from Database, the nodes DELETE all
			//	Curves,Patches etc connected in CurveList,PatchList of them.
			//	If we temporarily change item levels to LEVEL_GRAPA, Nodes will
			//	NOT DELETE them. Then switch back
			/////////////////////////////////////////////////////////////////////
			pINT pnLevelType = new int[nMaxCurves];
			int c;
			for ( c = 0; c<nMaxCurves; c++)
			{
				pNewCurve = (CDrCurve*)pList->GetObject( c);
				*(pnLevelType+c) = pNewCurve->GetLevelType();		// save Temporarily
				pNewCurve->SetLevelType(LEVEL_GRAPA);				// switch Temporarily

			}
			/////////////////////////////////////////////////////////////////////
			for ( c = 1; c<nMaxCurves; c++)
			{
				pNewCurve = (CDrCurve*)pList->GetObject( c);
				///
				pCurrHeadNode	= (CDrNode*)((pNewCurve->GetINodeList())->GetHead());
				pCurrTailNode	= (CDrNode*)((pNewCurve->GetINodeList())->GetTail());
				/////////////////////////////////////////// if, Circular
				nInputType	= pNewCurve->GetInputType();
				bArc		= pNewCurve->IsArcType();
				//
				if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
					pCurrTailNode	= (CDrNode*)pNewCurve->GetVNodeList()->GetHead();
				///////////////////////////////////////// delete
				pDListMgr	= pObjectMgr->GetObjectList(NODE);
				nNodeIndex	= pDListMgr->GetObjectIndex(pCurrHeadNode);
				//
				pDrLabel	= (CDrLabel*)((pCurrHeadNode->GetLabelList())->GetHead()); 
				pDListMgr	= pObjectMgr->GetObjectList(LABEL);
				nLabelIndex = pDListMgr->GetObjectIndex(pDrLabel);
				if(nLabelIndex>=0)
				{
					POSITION pos = pDListMgr->FindIndex(nLabelIndex);
					pDListMgr->RemoveAt(pos);
//					pObjectMgr->DeleteFromDataBase(nLabelIndex, LABEL);
				}
				if(nNodeIndex>=0)
					pObjectMgr->DeleteFromDataBase(nNodeIndex, NODE);
				///////////////////////////////////////// insert at Head
				(pNewCurve->GetINodeList())->AddHead(pLastTailNode); 
				///////////////////////////////////////// Reciprocate
				(pLastTailNode->GetCurveList())->InsertObject(pNewCurve); 
				///////////////////////////////////////// Update
				pLastTailNode = pCurrTailNode;
				///////////////////////////////////////// Last Curve
				if( (c+1) == nMaxCurves)
				{
					///////////////////////////////////////// delete
					pDListMgr	= pObjectMgr->GetObjectList(NODE);
					nNodeIndex	= pDListMgr->GetObjectIndex(pCurrTailNode);
					//
					pDrLabel	= (CDrLabel*)((pCurrTailNode->GetLabelList())->GetHead()); 
					pDListMgr	= pObjectMgr->GetObjectList(LABEL);
					nLabelIndex = pDListMgr->GetObjectIndex(pDrLabel); 
					if(nNodeIndex>=0)
						pObjectMgr->DeleteFromDataBase(nNodeIndex, NODE);
					if(nLabelIndex>=0)
					{
						POSITION pos = pDListMgr->FindIndex(nLabelIndex);
						pDListMgr->RemoveAt(pos);
					}
					///////////////////////////////////////// insert at Tail	IstCurve Head
					if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
						(pNewCurve->GetVNodeList())->AddHead(pIstHeadNode); 
					else
						(pNewCurve->GetINodeList())->AddTail(pIstHeadNode); 
					///////////////////////////////////////// Reciprocate
					(pIstHeadNode->GetCurveList())->InsertObject(pNewCurve); 
				}
			}
			/////////////////////////////////////////////////////////////////////
			for ( c = 0; c<nMaxCurves; c++)
			{
				pNewCurve = (CDrCurve*)pList->GetObject( c);
				pNewCurve->SetLevelType(*(pnLevelType+c));			// switch back

			}
			/////////////////////////////////////////////////////////////////////
			delete pnLevelType;
		}
		////////////////////////////// Reciprocate
		ReciprocatePatchCurves(pList);
	}
	///////////////////////////////////////////////////////////////// NodeLists
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrPatch->GetCNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocatePatchNodes(pList);
	}
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrPatch->GetCN_BSList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocatePatchNodes(pList);
	}
	/////////////////////////////////////////////////////////// INode
    pList = m_pDrPatch->GetINodeList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocatePatchNodes(pList);
	}
	/////////////////////////////////////////////////////////// VNode
//	 Stores Handle Nodes,
    pList = m_pDrPatch->GetVNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocatePatchNodes(pList);
	}
	/////////////////////////////////////////////////////////// Elem
//	Center for Circle_By_Rot/Circle_By_3No w/o Arc
    pList = m_pDrPatch->GetElemList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateCurveNodes(pList);
	}
	/////////////////////////////////////////////////////////// Node
    pList = m_pDrPatch->GetNodeList();
	if(pList)
	{
		nResult = SpawnNodeListinPatch(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocatePatchNodes(pList);
	}
	/////////////////////////////////////////////////////////// Support
	if(!(m_pDrPatch->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
		if(m_pDrPatch->GetPatSubType() == PS_QUADRILAT)
			nResult = MI_LSupp.CreatePatchBased_4(m_pDrPatch,m_pDrPatch->GetSuppCardList());
		else
		if(m_pDrPatch->GetPatSubType() == PS_TRIANGLE)
			nResult = MI_LSupp.CreatePatchBased_3(m_pDrPatch,m_pDrPatch->GetSuppCardList());
	}
	/////////////////////////////////////////////////////////// StaticLoad
	if(!(m_pDrPatch->GetStaLList()->IsEmpty()))
	{
		CMI_StaL MI_StaL;
		if(m_pDrPatch->GetPatSubType() == PS_QUADRILAT)
			nResult = MI_StaL.CreatePatchBased_4(m_pDrPatch,m_pDrPatch->GetStaLCardList());
		else
		if(m_pDrPatch->GetPatSubType() == PS_TRIANGLE)
			nResult = MI_StaL.CreatePatchBased_3(m_pDrPatch,m_pDrPatch->GetStaLCardList());
	}
	//////////////////////////////////////////////////////////////// Triangle List 
	CString Cid = m_pDrPatch->GetParentID();
	////
	SpawnTriangleList(Cid, pXFMat);
	/////////////////
	return 0;
}

int CMI_PSPN::SpawnNodeListinPatch(CDListMgr* pFillList, pMATRIX pXFMat)
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
		nResult = SpawnNodeinPatch(pOldNode,pNewNode,pXFMat);
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

int CMI_PSPN::SpawnNodeinPatch(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat)
{
	/////////////////////////////////////////////////////////// Data
	BOOL bCNode		= pOldNode->IsControlNode();
	CString NewNID	= pNewNode->GetObjectID(); 
	///////////////////////////////////////// Get ID
	int nResult = SpawnNodeWithoutDlg(pNewNode,pOldNode,pXFMat,&NewNID,
												bCNode,m_pDrPatch,PATCH);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return -1;
	////////////
	return 0;
}

int CMI_PSPN::SpawnTriangleList(CString Cid, pMATRIX pXFMat)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	int index;
	CDrPatch* pOldPatch;
	/////////
	index = pObjectMgr->GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
		pOldPatch = (CDrPatch*)(pDListMgr->GetObject(index));
	else
		pOldPatch = NULL;
		////////////////
	if(pOldPatch)
	{
		CDListMgr* pOldList = pOldPatch->GetTriangleList();
		if(pOldList->IsEmpty() )
			return 0;
		////////////////////////
		CDListMgr* pNewList = m_pDrPatch->GetTriangleList();
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
	 		
int CMI_PSPN::SpawnCurveListInPatch(CDListMgr* pFillList, pMATRIX pXFMat)
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
															m_pDrPatch,PATCH);
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
		/////////////////////// Put CurvIDs in Patch
		m_pDrPatch->SetCurveID(NewCID,s);
		////////////////
		pFillList->InsertObject(pNewCurve); //CurveList 
		////////
	}				
	///////////////////////////////////////////////////////// Empty it
	TempList.RemoveAll();
	/////////
	return 0;
}
	 
int CMI_PSPN::SpawnPatchCopyOff(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInPatchCopyOff(pXFMat);
	//////////
	CDrNode* pOldNode;
	////////////////////////////////////////////////////////////////// Node Spawn : FromID_T
	pOldNode = m_pDrPatch->GetFromIDNode_T();
	if(pOldNode)
	{
		nResult = SpawnNodeCopyOff(pOldNode,  pXFMat, TRUE);
		///////////////////////
		if(nResult<0)
			return nResult;
	}
	////////////////////////////////////////////////////////////////// Node Spawn : ToID_T
	pOldNode = m_pDrPatch->GetToIDNode_T();
	if(pOldNode)
	{
		nResult = SpawnNodeCopyOff(pOldNode,  pXFMat, TRUE);
		///////////////////////
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////
	// todo: after changing to String in DrPatch.h
//	WORLD		m_Center_T;	// Circle
	///////////////////////////////
	return 0;
}

int CMI_PSPN::SpawnListsInPatchCopyOff(pMATRIX pXFMat)
{
	////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////
	CDListMgr*	pList;
	int			nResult;
	///////////////////////////////////////////////////////////////// CurveList
    pList			= m_pDrPatch->GetCurveList();
	int nMaxCurves	= pList->GetCount();
	//////////
	if(pList && (nMaxCurves>0))
	{
		nResult = SpawnCurveListCopyOff(pList,pXFMat);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrPatch->GetCNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrPatch->GetCN_BSList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// INode
    pList = m_pDrPatch->GetINodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// VNode
    pList = m_pDrPatch->GetVNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// Node
    pList = m_pDrPatch->GetNodeList();
	if(pList && (!pList->IsEmpty() )  )
	{
		nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////////////////////// Support etc.
	if(!(m_pDrPatch->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
		if(m_pDrPatch->GetPatSubType() == PS_QUADRILAT)
			MI_LSupp.RegenPatchBased_4(m_pDrPatch);
		else
		if(m_pDrPatch->GetPatSubType() == PS_TRIANGLE)
			MI_LSupp.RegenPatchBased_3(m_pDrPatch);
	}
	/////////////////////////////////////////////////////////// Static Load, if any
	if(!(m_pDrPatch->GetStaLList()->IsEmpty()))
	{
		CMI_StaL MI_StaL;
		if(m_pDrPatch->GetPatSubType() == PS_QUADRILAT)
			MI_StaL.RegenPatchBased_4(m_pDrPatch);
		else
		if(m_pDrPatch->GetPatSubType() == PS_TRIANGLE)
			MI_StaL.RegenPatchBased_3(m_pDrPatch);
	}
	///////////////////////////////////////////////
	if(nResult<0)
		return nResult;
	/////////////////
	return 0;
}

int CMI_PSPN::SpawnPatchListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrPatch* pPatch = (CDrPatch*)pFillList->GetObject( s);
		if(GetPDoneList()->GetObjectIndex(pPatch) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrPatch* pTempPatch = m_pDrPatch;
		m_pDrPatch = pPatch;
		pObjectMgr->ShowObject_On_Off(pPatch,PATCH,FALSE);
		/////////
		nResult = SpawnPatchCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pPatch,PATCH,TRUE);
		m_pDrPatch = pTempPatch;
		GetPDoneList()->InsertObject(pPatch);
		////////
	}				
	/////////
	return 0;
}
	 		
void CMI_PSPN::ReciprocatePatchNodes(CDListMgr* pList)
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
		pNewNode->GetPatchList()->InsertObject(m_pDrPatch);
		////////
	}
}

void CMI_PSPN::ReciprocatePatchCurves(CDListMgr* pList)
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
		pNewCurve->GetPatchList()->InsertObject(m_pDrPatch);
		////////
	}
}
	 		
int CMI_PSPN::SpawnPatchWithoutDlg(CDrPatch* pNewPatch,CDrPatch* pOldPatch,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		PatchID="",SolidID="",Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case PATCH:
			m_pContextPat	= (CDrPatch*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			break;
		case SOLID:
			m_pContextSol	= (CDrSolid*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			PatchID			= pOldPatch->GetObjectID();  	
			break;
		case OBJ3D:
			m_pContextO3D	= (CDrObj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			PatchID			= pOldPatch->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_PSPN::SpawnPatchWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
		pObjectMgr->SetObjInfoID(*pCid,PATCH);
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrPatch = pNewPatch;
	/////////////////////
	if(m_pDrPatch != pOldPatch)	// Copy ON
	{	
		PATCHPROC	PProc;
		PProc		= pOldPatch->GetPatchProc();
		//////////////////////////
		m_pDrPatch->SetPatchProc(PProc);	// New Patch
		nResult = FillSpawnedPatchDlgDataBase(m_pDrPatch,*pCid, PatchID);
		if(nResult<0)
			return nResult;
	}
    ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
	{
		nResult = SpawnPatchCopyOff(pXFMat);
	}
	else
		nResult = SpawnPatch(pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrPatch->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_PSPN::FillSpawnedPatchDlgDataBase(CDrPatch* pDrPatch,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnP	Dlg_SpnP;		
	////////////////////////////////////
	Dlg_SpnP.m_SpawnID		= Cid;
	Dlg_SpnP.m_bInstanced 	= FALSE;
	Dlg_SpnP.m_CID		 	= ParentCid;
	Dlg_SpnP.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnP.SetInfoForDataBase(pDrPatch);
	///////////////
    return 0;
}

void CMI_PSPN::Serialize(CArchive& ar)
{

	CMI_CSPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_PSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_PSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
