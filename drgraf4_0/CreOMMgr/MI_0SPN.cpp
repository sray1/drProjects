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
#include "Def_Elem.h"
///////////////////// Label
#include "DrLabel.h"
///////////////////// dialogMgr
#include "CreMDlgM.h"
#include "Mi_Gang0.h"
#include "Mlg_SpnN.h"
////////////////////
#include "MI_0SPN.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define MIN_CNODES_MESH1D	4
#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_0SPN,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CMI_0SPN::CMI_0SPN()
{
	m_pContextNod = NULL;
	m_pContextCur = NULL;
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_0SPN::~CMI_0SPN()
{
}


int CMI_0SPN::SpawnNodeShowingDlg(CDrFE0D* pNewNode,CDrFE0D* pOldNode, 
									CDrObject* pContextObj, UINT nContextType) 
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////////////////////////////
	switch(nContextType)
	{
		case FE0D:
			m_pContextNod = (CDrFE0D*)pContextObj;
			break;
		case MESH1D:
			m_pContextCur = (CDrMesh1D*)pContextObj;
			break;
		case MESH2D:
			m_pContextPat = (CDrMesh2D*)pContextObj;
			break;
		case MESH3D:
			m_pContextSol = (CDrMesh3D*)pContextObj;
			break;
		case MBJ3D:
			m_pContextO3D = (CDrMbj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_0SPN::CSpawn\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////
	m_pDrNode = pNewNode;
	////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	nResult = GetInfoFromDlg(m_pDrNode,pOldNode);
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
		if(!pBool->IsSpawnOn())
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
		if(!pBool->IsSpawnOn())
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
	 
int CMI_0SPN::GetInfoFromDlg(CDrFE0D* pNewNode, CDrFE0D* pOldNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreMDlgM* 	pNodMgr;
	CString		Cid = pNewNode->GetObjectID();
	CString		ParentID = pOldNode->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pNodMgr->DoModal_Spawn_N(pNewNode,pOldNode,&Cid,&ParentID) == IDCANCEL)
		return -2; 
	/////////
	return 0;
}
	 
int CMI_0SPN::SpawnNodeListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
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
		CDrFE0D* pParentNode	= (CDrFE0D*)(pFillList->GetObject( s));
		BOOL	 bCNode			= pParentNode->IsControlNode();
		/////////////
		nResult = SpawnNodeCopyOff(pParentNode, pXFMat, bCNode);
		if(nResult <0)
			return nResult;
	}				
	////////////
	return nResult;
}	 

int CMI_0SPN::SpawnNodeCopyOff(CDrFE0D* pParentNode, pMATRIX pXFMat, BOOL bCNode)
{
	int nResult = 0;
	C3DMath			Math3D;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// XForm 
	CString		NewNID;
	//////////////////////////////////////////////////////////// already done
	if(m_pNDoneList->GetObjectIndex(pParentNode) >=0)
		return nResult;
	///////////////////
	pObjectMgr->SetActiveObjectType(FE0D);
	/////////////////////////////////////////////////////////////// Refresh RectInvalid Erase
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,MCNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,FE0D,FALSE);
	/////////////////
	nResult = TransformNodeCoords(pParentNode, pXFMat);
	///////////////////////////////////// in Curve 
	if(nResult<0)
		return nResult;
	/////////////////////////////////////////
	m_pNDoneList->InsertObject(pParentNode);
	/////////////////////////////////////////////////////////// Control RectBound
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,MCNODE,TRUE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,FE0D,TRUE);
	////////////
	return nResult;
}	 
	 
int CMI_0SPN::TransformNodeCoords(CDrFE0D* pNode, pMATRIX pXFMat)
{
	CDrFE0D* pTempNode = m_pDrNode;
	//////////////////
	m_pDrNode = pNode;
	SpawnNode(pXFMat);
	//////////////////
	m_pDrNode = pTempNode;
	/////////
	return 0;
}

int CMI_0SPN::SpawnNode(pMATRIX pXFMat)
{
	CXForm	XForm(TRUE);
	////////////////////
	WORLD	LocalPos;
	///////////////////////////////////////// Get Coords		
	LocalPos	= *(m_pDrNode->GetLocalPos());
	///////////////////////////////////////// Transform
	XForm.Transform(&LocalPos,&LocalPos,pXFMat);
	///////////////////////////////////////// Set it
	m_pDrNode->SetLocalPos(LocalPos);
    /////////////////////////////
	(m_pDrNode->GetNodeCard())->x = (long)LocalPos.x;	
	(m_pDrNode->GetNodeCard())->y = (long)LocalPos.y;	
	(m_pDrNode->GetNodeCard())->z = (long)LocalPos.z;
	/////////////////////////////////////////////
	return 0;
}
	 		
int CMI_0SPN::SpawnNodeWithoutDlg(CDrFE0D* pNewNode,CDrFE0D* pOldNode,pMATRIX pXFMat,
						CString* pNid,BOOL bCNode,CDrObject* pContextObj,UINT nContextType)
{
	int nResult = 0;
	BOOL bMNode = pOldNode->IsMeshNode();
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////
	CString		NodeID = "",CurveID = "",PatchID="",SolidID="",Obj3DID="";
	//////////////////////////////////////////////////////////////// Name
	switch(nContextType)
	{
		case FE0D:
			m_pContextNod	= (CDrFE0D*)pContextObj;
			NodeID			= m_pContextNod->GetObjectID();  	
			break;
		case MESH1D:
			m_pContextCur	= (CDrMesh1D*)pContextObj;
			CurveID			= m_pContextCur->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		case MESH2D:
			m_pContextPat	= (CDrMesh2D*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		case MESH3D:
			m_pContextSol	= (CDrMesh3D*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
		case MBJ3D:
			m_pContextO3D	= (CDrMbj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			NodeID			= pOldNode->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_0SPN::SpawnNodeWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pNid == "")
	{
		/////////////////////////////
		CMI_Gang0 Gang0;
		CString strID;
		//////////////
		if(bCNode)
		{
			Gang0.SetElemInfoID(strID,MCNODE);		
			strID = "MC_" + strID;
		}
		else
		if(bMNode)
			Gang0.SetElemInfoID(strID,MNODE);		
		else
			Gang0.SetElemInfoID(strID,FE0D);		
		///////////		
		(*pNid)	+= strID;
	}
	////////////////////////////////////////////////////////////////// Fill it
	m_pDrNode = pNewNode;
	///////////////////////
	if(m_pDrNode != pOldNode)	// Copy ON
	{	
		//////////////////////////
		(m_pDrNode->GetNodeCard())->bnid_c 	= bCNode;
		m_pDrNode->SetMeshNode(bMNode);
		nResult = FillSpawnedNodeDlgDataBase(m_pDrNode,*pNid,pOldNode,NodeID);
		if(nResult<0)
			return nResult;
	}
    ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
	{
		nResult = SpawnNodeCopyOff(pNewNode, pXFMat, bCNode);
	}
	else
		nResult = SpawnNode(pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrNode->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_0SPN::FillSpawnedNodeDlgDataBase(CDrFE0D* pDrNode,CString& Cid,
											CDrFE0D* pParentNode,CString& ParentCid)
{
	// Since Control Nodes are Privately Listed, we need to supply
	// pOldNode to the Dlg Database	
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnN	Dlg_SpnN;		
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

void CMI_0SPN::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_0SPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_0SPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
