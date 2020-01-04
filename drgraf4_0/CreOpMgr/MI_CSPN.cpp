// Rotate.cpp : implementation file
//


#include "stdafx.h"

#include "math.h"
#include "XForm.h"

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrLabel.h"
///////////////////// dialogMgr
#include "CreODlgM.h"
#include "Dlg_SpnC.h"
////////////////////
#include "MI_GangN.h"
#include "RegenCur.h"
#include "MI_LSupp.h"
#include "MI_StaL.h"
///////////////////// 
#include "MI_CSPN.h" 

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
IMPLEMENT_SERIAL(CMI_CSPN,CMI_NSPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_CSPN::CMI_CSPN()
{
	m_pContextCur = NULL;
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_CSPN::~CMI_CSPN()
{
}

int CMI_CSPN::SpawnCurveShowingDlg(CDrCurve* pNewCurve,CDrCurve* pOldCurve, 
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
		case CURVE:
			m_pContextCur = (CDrCurve*)pContextObj;
			break;
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
			AfxMessageBox("ERROR:CMI_CSPN::CSpawn\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrCurve = pNewCurve;
	////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	nResult = GetInfoFromDlg(m_pDrCurve,pOldCurve);
	if(nResult<0)
		return nResult;// error or cancel
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrCurve)
	{
		; // do nothing
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Curve Spawning Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
*/
	}	
	else
		return -1;	// error
	///////////////////////////////// Spawn Curve
	MATRIX Mat;
	///////////
	if(m_pDrCurve->IsInstanced())
	{
		CMatObj* pMatObj	= m_pDrCurve->GetMatObj();
		Mat					= *(pMatObj->GetMatrix());
	    ////////////////////////////////////////
		if(!pBool->IsSpawnOn())
			nResult = SpawnCurveCopyOff(&Mat);
		else
			nResult = SpawnCurve(&Mat);
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
			nResult = SpawnCurveCopyOff(&Mat);
		else
			nResult = SpawnCurve(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	///////////////////////////// make it Unposted 
	m_pDrCurve->SetPosted(FALSE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();
	/////////
	return 0;		 
}			
	 
int CMI_CSPN::GetInfoFromDlg(CDrCurve* pNewCurve, CDrCurve* pOldCurve)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreODlgM 	CurMgr;
	CString		Cid = pNewCurve->GetObjectID();
	CString		ParentID = pOldCurve->GetObjectID(); 
	///////////////////////////////////////////////////
	if (CurMgr.DoModal_Spawn_C(pNewCurve,&Cid,&ParentID) == IDCANCEL)
		return -2; 
	/////////
	return 0;
}
	 
int CMI_CSPN::SpawnCurve(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////// Lists
	SpawnListsInCurve(pXFMat);
	/////////////////////////////////////////////////////////// FromID (Axis/CirclebyRot)
	CDrNode* pOldNode;
	//////////////////
	pOldNode = m_pDrCurve->GetFromIDNode_S();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinCurve(pOldNode,pNewNode,pXFMat);
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
		m_pDrCurve->SetFromIDNode_S(pNewNode);
	}
	/////////////////////////////////////////////////////////// ToID (Axis/CirclebyRot)
	pOldNode = m_pDrCurve->GetToIDNode_S();
	if(pOldNode)
	{
		int nActiveIndex;

		CDrNode* pNewNode = SimilarNode_AddToDataBase(pOldNode,nActiveIndex);
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinCurve(pOldNode,pNewNode,pXFMat);
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
		m_pDrCurve->SetToIDNode_S(pNewNode);
	}
	/////////////////////////////
	return 0;
}
	 
int CMI_CSPN::SpawnListsInCurve(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
   /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// INode 
	pList = m_pDrCurve->GetINodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
//			nResult = SpawnNodeListinCurve(pList, pXFMat, FALSE);
			nResult = SpawnNodeListinCurve(pList, pXFMat);
			if(nResult<0)
				return -1;
			////////////////////////////// Reciprocate
			ReciprocateCurveNodes(pList);
		}
	}
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrCurve->GetCNodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
//			nResult = SpawnNodeListinCurve(pList, pXFMat, TRUE);
			nResult = SpawnCNodeListinCurve(pList, pXFMat);
//			nResult = SpawnNodeListinCurve(pList, pXFMat);
			if(nResult<0)
				return -1;
		}
			////////////////////////////// Reciprocate
//			ReciprocateCurveNodes(pList);
	}
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrCurve->GetCN_BSList();
	if(pList)
	{
		nResult = SpawnCNodeListinCurve(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
//		ReciprocateCurveNodes(pList);
	}
	/////////////////////////////////////////////////////////// VNode
//	 Stores Handle Nodes,
    pList = m_pDrCurve->GetVNodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
//			nResult = SpawnNodeListinCurve(pList, pXFMat, FALSE);
			nResult = SpawnNodeListinCurve(pList, pXFMat);
			if(nResult<0)
				return -1;
			////////////////////////////// Reciprocate
			ReciprocateCurveNodes(pList);
		}
	}
	/////////////////////////////////////////////////////////// Elem
//	Center for Circle_By_Rot/Circle_By_3No w/o Arc
    pList = m_pDrCurve->GetElemList();
	if(pList)
	{
		nResult = SpawnNodeListinCurve(pList, pXFMat);
		if(nResult<0)
			return -1;
		////////////////////////////// Reciprocate
		ReciprocateCurveNodes(pList);
	}
	/////////////////////////////////////////////////////////// Support
	if(!(m_pDrCurve->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
		MI_LSupp.CreateCurveBased(m_pDrCurve,m_pDrCurve->GetSuppCardList());
	}
	/////////////////////////////////////////////////////////// StaticLoad
	if(!(m_pDrCurve->GetStaLList()->IsEmpty()))
	{
		CMI_StaL MI_StaL;
		MI_StaL.CreateCurveBased(m_pDrCurve,m_pDrCurve->GetStaLCardList());
	}
	/////////////////////////////
	return 0;
}

int CMI_CSPN::SpawnCNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat)
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
	int			nMaxNodes;
	CString		NewNID;
	int s;
	/////////////////////////////////////////////////////////// Data
	nMaxNodes		 	= pTempList->GetCount();
	////////////////////////////////////////// 	
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrNode* pOldNode = (CDrNode*)pTempList->RemoveHead();
		////////////////////////////////////
		CString	NewNID;
		UINT nType = CNODE;
		pObjectMgr->SetNodeInfoID(NewNID,TRUE,(UINT)nType);
		/////////////////
		CDrNode* pNewNode = new CDrNode;
		////////////////////////////////
		pNewNode->SetObjectID(NewNID);
		(pNewNode->GetNodeCard())->id		= NewNID;
		(pNewNode->GetNodeCard())->bnid_c 	= TRUE; 
		/////////////////////////////////////////////////////// Using CMI_NSPN
		nResult = SpawnNodeinCurve(pOldNode,pNewNode,pXFMat);
		/////////////////////////////////////////////////////
		if(nResult<0)
		{
			/////
			AfxMessageBox("Internal ERROR:\nCMI_CSPN::SpawnCNodeListinCurve");
			///////////////
			return nResult;
		}
		//////////////
		pFillList->InsertObject(pNewNode); //NodeList 

	}				
	///////////////////////////////////////////////////////// Empty it
	delete pTempList;
	////////////
	return 0;
}

int CMI_CSPN::SpawnNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat)
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
		nResult = SpawnNodeinCurve(pOldNode,pNewNode,pXFMat);
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
		pObjectMgr->ShowObject_On_Off(pLabel,LABEL,TRUE);	// ready
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

int CMI_CSPN::SpawnNodeinCurve(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat)
{
	/////////////////////////////////////////////////////////// Data
	BOOL bCNode		= pOldNode->IsControlNode();
	CString NewNID	= pNewNode->GetObjectID(); 
	///////////////////////////////////////// Get ID
	int nResult = SpawnNodeWithoutDlg(pNewNode,pOldNode,pXFMat,&NewNID,
												bCNode,m_pDrCurve,CURVE);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return -1;
	////////////
	return 0;
}
	 
int CMI_CSPN::SpawnCurveCopyOff(pMATRIX pXFMat)
{
#ifdef _DEBUG
		CString ObjID = m_pDrCurve->GetObjectID();
		CString strBum;
		if(ObjID == "C5")
			strBum = "Bum String C5";
#endif
	/////////////////////////
	int nResult;
    /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// INode 
	pList = m_pDrCurve->GetINodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// CNode
    pList = m_pDrCurve->GetCNodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
			if(nResult<0)
				return nResult;
		}
	}
/*
	/////////////////////////////////////////////////////////// CN_BS
    pList = m_pDrCurve->GetCN_BSList();
	if(pList)
	{
		nResult = SpawnNodeListinCurve(pList, pXFMat, TRUE,&NodeDoneList);
		if(nResult<0)
			return -1;
	}
*/
	/////////////////////////////////////////////////////////// VNode
    pList = m_pDrCurve->GetVNodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// Elem
//	 01/13/1998 Stores Handle Nodes,
//	Center for Circle_By_Rot/Circle_By_3No w/o Arc
    pList = m_pDrCurve->GetElemList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// Support etc.
	if(!(m_pDrCurve->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
		MI_LSupp.RegenCurveBased(m_pDrCurve);
	}
	/////////////////////////////////////////////////////////// Static Load, if any
	if(!(m_pDrCurve->GetStaLList()->IsEmpty()))
	{
		CMI_StaL MI_StaL;
		MI_StaL.RegenCurveBased(m_pDrCurve);
	}
	///////////////////////////////////////////////
	if(nResult<0)
		return nResult;
	///////////////////
	/////////
	return 0;
}
	 		
int CMI_CSPN::SpawnCurveListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrCurve* pCurve = (CDrCurve*)pFillList->GetObject( s);
		if(GetCDoneList()->GetObjectIndex(pCurve) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrCurve* pTempCurve = m_pDrCurve;
		m_pDrCurve = pCurve;
		pObjectMgr->ShowObject_On_Off(pCurve,CURVE,FALSE);
		/////////
		nResult = SpawnCurveCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pCurve,CURVE,TRUE);
		m_pDrCurve = pTempCurve;
		GetCDoneList()->InsertObject(pCurve);
		////////
	}
	/////////
	return 0;
}

void CMI_CSPN::ReciprocateCurveNodes(CDListMgr* pList)
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
		CDListMgr* pCurveList = pNewNode->GetCurveList();
		int index = pCurveList->GetObjectIndex(m_pDrCurve);
		if(index<0)
			pCurveList->InsertObject(m_pDrCurve);
		////////
	}
}
	 		
int CMI_CSPN::SpawnCurveWithoutDlg(CDrCurve* pNewCurve,CDrCurve* pOldCurve,pMATRIX pXFMat,
						CString* pCid,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		CurveID = "",PatchID="",SolidID="",Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case CURVE:
			m_pContextCur	= (CDrCurve*)pContextObj;
			CurveID			= m_pContextCur->GetObjectID();  	
			break;
		case PATCH:
			m_pContextPat	= (CDrPatch*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		case SOLID:
			m_pContextSol	= (CDrSolid*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		case OBJ3D:
			m_pContextO3D	= (CDrObj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_CSPN::SpawnCurveWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
		pObjectMgr->SetObjInfoID(*pCid,CURVE);
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrCurve = pNewCurve;
	///////////////////////
	if(m_pDrCurve != pOldCurve)	// Copy ON
	{	
		/////////////////////
		CURVEPROC	CProc;
		CProc		= pOldCurve->GetCurveType_S();
		//////////////////////////
		m_pDrCurve->SetCurveType_S(CProc);	// New Curve
		nResult = FillSpawnedCurveDlgDataBase(m_pDrCurve,*pCid, CurveID);
		if(nResult<0)
			return nResult;
		nResult = SpawnCurve(pXFMat);
	}
    ////////////////////////////////////////
//	if(!pBool->IsSpawnOn())
	else
	{
		nResult = SpawnCurveCopyOff(pXFMat);
	}
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_CSPN::FillSpawnedCurveDlgDataBase(CDrCurve* pDrCurve,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnC	Dlg_SpnC;		
	////////////////////////////////////
	Dlg_SpnC.m_SpawnID		= Cid;
	Dlg_SpnC.m_bInstanced 	= FALSE;
	Dlg_SpnC.m_CID		 	= ParentCid;
	Dlg_SpnC.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnC.SetInfoForDataBase(pDrCurve);
	///////////////
    return 0;
}

void CMI_CSPN::Serialize(CArchive& ar)
{

	CMI_NSPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_CSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_CSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
