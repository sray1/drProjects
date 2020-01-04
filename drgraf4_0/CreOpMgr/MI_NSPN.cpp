// Rotate.cpp : implementation file
//


#include "stdafx.h"

#include "math.h"
#include "XForm.h"

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrLinSup.h"
///////////////////// Label
#include "DrLabel.h"
///////////////////// dialogMgr
#include "CreODlgM.h"
#include "Mi_GangN.h"
#include "Dlg_SpnN.h"
#include "RegenNod.h"
#include "MI_LSupp.h"
#include "MI_StaL.h"
////////////////////
#include "MI_NSPN.h" 

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
IMPLEMENT_SERIAL(CMI_NSPN,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_NSPN::CMI_NSPN()
{
	m_pContextNod = NULL;
	m_pContextCur = NULL;
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_NSPN::~CMI_NSPN()
{
}

CDrNode* CMI_NSPN::SimilarNode_AddToDataBase(CDrNode* pOldNode,int& nActiveIndex)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	CDrNode* pNewNode;
	//////////////////
	BOOL bCNode	= pOldNode->IsControlNode();
	if(bCNode)
		pNewNode	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,CNODE));
	else
		pNewNode	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,NODE));
	///
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pNewNode,CNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(pNewNode,NODE,FALSE);
	///////////////////								// TRUE = Internally Generated
	if(!pNewNode)
		return (CDrNode*)NULL;//
	else
		pNewNode->SetControlNode(bCNode);
	////////////////////////////////////
	CString	NewNID;
	UINT nType = bCNode?CNODE:NODE;
	pObjectMgr->SetNodeInfoID(NewNID,bCNode,(UINT)nType);
	pNewNode->SetObjectID(NewNID);
	(pNewNode->GetNodeCard())->id = NewNID;
	//////
	return pNewNode;
}

int CMI_NSPN::SimilarNode_DeleteFromDataBase(int& nActiveIndex,BOOL bCNode)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////// Delete
	if(bCNode)
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CNODE);
	else
		pObjectMgr->DeleteFromDataBase(nActiveIndex, NODE);
	//////////////////////////
	return nResult;//
}
	
int CMI_NSPN::SpawnNodeShowingDlg(CDrNode* pNewNode,CDrNode* pOldNode, 
									CDrObject* pContextObj, UINT nContextType) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////////////////////////////
	switch(nContextType)
	{
		case NODE:
			m_pContextNod = (CDrNode*)pContextObj;
			break;
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
			AfxMessageBox("ERROR:CMI_NSPN::CSpawn\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrNode = pNewNode;
	////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	int nResult = GetInfoFromDlg(m_pDrNode,pOldNode);
	if(nResult<0)
		return nResult;// error or cancel
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrNode)
	{
		; // do nothing
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
				
		sprintf(buf,"Got All Node Spawning Info");
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
*/
	}	
	else
		return -1;	// error
	///////////////////////////////// Spawn Node
	MATRIX Mat;
	///////////
	if(m_pDrNode->IsInstanced())
	{
		CMatObj* pMatObj	= m_pDrNode->GetMatObj();
		Mat					= *(pMatObj->GetMatrix());
	    ////////////////////////////////////////
		if(pNewNode == pOldNode)
		{
			BOOL bCNode = pNewNode->IsControlNode();
			nResult = SpawnNodeCopyOff(pNewNode, &Mat, bCNode);
		}
		else
			nResult = SpawnNode(&Mat);
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
		if(pNewNode == pOldNode)
		{
			BOOL bCNode = pNewNode->IsControlNode();
			nResult = SpawnNodeCopyOff(pNewNode, &Mat, bCNode);
		}
		else
			nResult = SpawnNode(&Mat);
		////////////////////
		if(nResult<0)
			return -1;
		/////////////////////
	}
	///////////////////////////// make it Unposted 
	m_pDrNode->SetPosted(FALSE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrNode->Calc_3DBoundsLocal();
	/////////
	return 0;
}			
	 
int CMI_NSPN::GetInfoFromDlg(CDrNode* pNewNode, CDrNode* pOldNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreODlgM 	NodMgr;
	CString		Cid = pNewNode->GetObjectID();
	CString		ParentID = pOldNode->GetObjectID(); 
	///////////////////////////////////////////////////
	if (NodMgr.DoModal_Spawn_N(pNewNode,pOldNode,&Cid,&ParentID) == IDCANCEL)
		return -2; 
	/////////
	return 0;
}
	 
int CMI_NSPN::SpawnNodeListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////
	int nResult = 0;
	C3DMath			Math3D;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewNID;
	int s;
	/////////////////////////////////////////////////////////// Data
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrNode* pParentNode	= (CDrNode*)(pFillList->GetObject( s));
		BOOL	 bCNode			= pParentNode->IsControlNode();
		/////////////
		nResult = SpawnNodeCopyOff(pParentNode, pXFMat, bCNode);
		if(nResult <0)
			return nResult;
	}				
	////////////
	return nResult;
}	 

int CMI_NSPN::SpawnNodeCopyOff(CDrNode* pParentNode, pMATRIX pXFMat, BOOL bCNode)
{
	int nResult = 0;
	////////////////
	C3DMath			Math3D;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// XForm 
	CString		NewNID;
	//////////////////////////////////////////////////////////// already done
	if(m_pNDoneList->GetObjectIndex(pParentNode) >=0)
		return nResult;
	/////////////////////////////////////////////////////////////// Not ready
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,CNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,NODE,FALSE);
	/////////////////
	nResult = TransformNodeCoords(pParentNode, pXFMat);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return nResult;
	/////////////////////////////////////////////////////////// Support/Static Load etc.
	CRegenNod RegenNod;
	nResult = RegenNod.UpdateNode(pParentNode);
	///////////////////////////////////////////////
	if(nResult<0)
		return nResult;
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);
	/////////////////////////////////////////////////////////////// Ready
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,CNODE,TRUE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,NODE,TRUE);
	/////////////////////////////////////////
	m_pNDoneList->InsertObject(pParentNode);
	////////////
	return nResult;
}	 
	 
int CMI_NSPN::TransformNodeCoords(CDrNode* pNode, pMATRIX pXFMat)
{
	/////////////////////////////////////////////////////////////////// XForm 
	CXForm	XForm(TRUE);
	////////////////////
	WORLD	LocalPos;
	///////////////////////////////////////// Get Coords		
	LocalPos	= *(pNode->GetLocalPos());
	///////////////////////////////////////// Transform
	XForm.Transform(&LocalPos,&LocalPos,pXFMat);
	///////////////////////////////////////// Set it
	pNode->SetLocalPos(LocalPos);
    /////////////////////////////
	(pNode->GetNodeCard())->x = (long)LocalPos.x;	
	(pNode->GetNodeCard())->y = (long)LocalPos.y;	
	(pNode->GetNodeCard())->z = (long)LocalPos.z;
	/////////
	return 0;
}

int CMI_NSPN::SpawnNode(pMATRIX pXFMat)
{
	int nResult = 0;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	BOOL bCNode = m_pDrNode->IsControlNode(); 
	/////////////////////////////////////////////////////////////// Not ready
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(m_pDrNode,CNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(m_pDrNode,NODE,FALSE);
	/////////////////////////////////////////////////////////////////// XForm 
	TransformNodeCoords(m_pDrNode, pXFMat);
	/////////////////////////////////////////////////////////// Support
	if(!(m_pDrNode->GetSuppList()->IsEmpty()))
	{
		CMI_LSupp MI_LSupp;
		MI_LSupp.RegenNodeBased(m_pDrNode);
	}
	/////////////////////////////////////////////////////////// StaticLoad
	if(!(m_pDrNode->GetStaLList()->IsEmpty()))
	{
		CMI_StaL MI_StaL;
		MI_StaL.RegenNodeBased(m_pDrNode);
	}
	/////////////////////////////
	///////////////////////////////////////////////
	if(nResult<0)
		return nResult;
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);
	/////////////////////////////////////////////////////////////// Not ready
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(m_pDrNode,CNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(m_pDrNode,NODE,FALSE);
	////////////
	return nResult;
}
	 		
int CMI_NSPN::SpawnNodeWithoutDlg(CDrNode* pNewNode,CDrNode* pOldNode,pMATRIX pXFMat,
						CString* pNid,BOOL bCNode,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		NodeID = "",CurveID = "",PatchID="",SolidID="",Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case NODE:
			m_pContextNod	= (CDrNode*)pContextObj;
			NodeID			= m_pContextNod->GetObjectID();  	
			break;
		case CURVE:
			m_pContextCur	= (CDrCurve*)pContextObj;
			CurveID			= m_pContextCur->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		case PATCH:
			m_pContextPat	= (CDrPatch*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		case SOLID:
			m_pContextSol	= (CDrSolid*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
		case OBJ3D:
			m_pContextO3D	= (CDrObj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_NSPN::SpawnNodeWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pNid == "")
	{
		UINT nType;
		/////////////
		if(bCNode)
			nType = CNODE;
		else
			nType = NODE;
		////////////
		pObjectMgr->SetNodeInfoID(*pNid,bCNode,nType);
	}
	////////////////////////////////////////////////////////////////// Fill it
	m_pDrNode	= pNewNode;
	///////////////////////
	if(m_pDrNode != pOldNode)	// Copy ON
	{	
		//////////////////////////
		(m_pDrNode->GetNodeCard())->bnid_c 	= bCNode;
		nResult = FillSpawnedNodeDlgDataBase(m_pDrNode,*pNid,pOldNode,NodeID);
		if(nResult<0)
			return nResult;
		nResult = SpawnNode(pXFMat);
	}
    ////////////////////////////////////////
	else
		nResult = SpawnNodeCopyOff(pNewNode, pXFMat, bCNode);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrNode->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_NSPN::FillSpawnedNodeDlgDataBase(CDrNode* pDrNode,CString& Cid,
											CDrNode* pParentNode,CString& ParentCid)
{
	// Since Control Nodes are Privately Listed, we need to supply
	// pOldNode to the Dlg Database	
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CDlg_SpnN	Dlg_SpnN;		
	/////////////////////////////////////////////////////////////////////////// Fill
	Dlg_SpnN.m_SpawnID		= Cid;			// NewID
	Dlg_SpnN.m_bInstanced 	= FALSE;
	Dlg_SpnN.m_pParent	 	= pParentNode;	// OldID
	Dlg_SpnN.m_CID		 	= ParentCid;	// OldID
	Dlg_SpnN.m_pMatObj 		= NULL;
	///////////////////////////////////////
	Dlg_SpnN.SetInfoForDataBase(pDrNode);	// NewNode
	///////////////
    return 0;
}

void CMI_NSPN::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_NSPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_NSPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
