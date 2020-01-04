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
#include "Mi_Gang0.h"
#include "Mi_Gang2.h"
#include "Mlg_SpnP.h"
////////////////////
#include "MI_2SPN.h" 

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
IMPLEMENT_SERIAL(CMI_2SPN,CMI_1SPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_2SPN::CMI_2SPN()
{
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_2SPN::~CMI_2SPN()
{
}

int CMI_2SPN::SpawnPatchShowingDlg(CDrMesh2D* pNewPatch,CDrMesh2D* pOldPatch, 
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
			AfxMessageBox("ERROR:CMI_2SPN::PSpawn\nILLEGAL nContextType");
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
			nResult = SpawnPatch(pOldPatch, &Mat);
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
			nResult = SpawnPatch(pOldPatch, &Mat);
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
	 
int CMI_2SPN::GetInfoFromDlg(CDrMesh2D* pNewPatch,CDrMesh2D* pOldPatch)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreMDlgM* 	pMPatMgr;
	CString		Cid = pNewPatch->GetObjectID();
	CString		ParentID = pOldPatch->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMPatMgr->DoModal_Spawn_P(pNewPatch,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_2SPN::SpawnPatch(CDrMesh2D* pOldMESH2D, pMATRIX pXFMat)
{
	CDListMgr*	pFE0DList;
	int			nResult;
	/////////////////////////////////////////////////////////// FE0D/MNode
    pFE0DList = m_pDrPatch->GetFE0DList();
	/////////////////////////////////////////// Fill with Old FE0Ds
	pFE0DList->RemoveAll();
	pFE0DList->AddTail(pOldMESH2D->GetFE0DList());
	///
	if(pFE0DList->IsEmpty())
	{
		AfxMessageBox("Internal ERROR:\nCMI_2SPN::SpawnPatch\npFE0DList->IsEmpty()!");
		return -1;
	}
	/////////////////////////
	nResult = SpawnNodeListinPatch(pFE0DList, pXFMat, FALSE);	// MNode/FE0D
	///////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_2SPN::SpawnPatch\nFE0DList Regen Problem!");
		return -1;
	}
	////////////////////////////// Reciprocate
	ReciprocatePatchNodes(pFE0DList);
	/////////////////////////////////////////////////////////// FE1D/FE2D
	CMI_Gang2 Gang2;
	nResult = Gang2.Regen_MESH2D_Elements((CDrObject*)m_pDrPatch,(CDrObject*)pOldMESH2D);
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_2SPN::SpawnPatch\nFE1DList Regen Problem!");
		return -1;
	}
	////////////
	return 0;
}

int CMI_2SPN::SpawnNodeListinPatch(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
																	//	This bCNode is ignored
{
	if(pFillList->IsEmpty())
		return 0;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CDListMgr TempList;
	TempList.RemoveAll();
	////////////////////////////////////////////////// copy
	TempList.AddTail(pFillList);
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
		BOOL bCNode = pOldNode->IsControlNode();
		BOOL bMNode = pOldNode->IsMeshNode();
		/////////////////////////////////////////////////////////////////  New
		CDrFE0D NewNode;
		///////////////////////////////////////// Get ID
		NewNID = "";	// force it to create a name
		int nResult = SpawnNodeWithoutDlg(&NewNode,pOldNode,pXFMat,&NewNID,
													bCNode,m_pDrPatch,MESH2D);
		///////////////////////////////////// in Patch 
		if(nResult<0)
			return nResult;
		///////////////////////////////////////////////////////////////
		CDrFE0D*	pNewNode;
		BOOL		bFinal = TRUE;;
		CMI_Gang0	Gang0;
		CDrLabel*	pLabel;
		int			nNodeIndex = -12345;	//Create Anyway
		int			nLabelIndex= 0;
		///////////////////////////////
		if(bCNode)		// Control Node
		{
			////////////////////////////
			WORLD LocalPos = *(NewNode.GetLocalPos());
			///////////////////////////////////// in THE List 
			pNewNode = Gang0.PostFE0D(NewNID,LocalPos,TRUE,FALSE);	// Create DrCNode
			if(!pNewNode)	// Create DrCNode
				return -1;
			///////////////////////////////////// in Patch 	
			pNewNode->SetLevelType((int)LEVEL_KIDDO);          // private
			//////////
			if(bFinal)
			{
				//////////////////////////////////////////// if New Node Change Level/Reciprocate
				if(pNewNode->GetObjectID() == NewNID)
				{
					//////////////////////////////////////// Reciprocate
//					pNewNode->GetMs1List()->InsertObject(m_pDrCurve);
					CMI_Gang0 MI_Gang0;
					nResult = MI_Gang0.ReciprocateElemMeshList(pNewNode, m_pDrPatch, MESH2D);
					///////////////////////////////////// in Curve 
					if(nResult<0)
					{
						AfxMessageBox("Internal ERROR\nCMI_1SPN::SpawnNodeListinCurve\nReciprocate");
						return nResult;
					}
					////////
				}
			}
		}
		else		// Input Nodes
		{

			/////////////////////////////////////////////////////////////////
			//		NOTE: ????????????????????
			//			Input Nodes in Curve could be the corner Node of a
			//			Patch in which case we don't want to spawn more
			//			than once. This is Taken care of later in MI_PSPN
			/////////////////////////////////////////////////////////////////
			WORLD LocalPos = *(NewNode.GetLocalPos());
			///////////////////////////////////// in THE List 
			pNewNode = Gang0.CreateFE0D(NewNID,pLabel, LocalPos, bCNode, TRUE, bMNode,
									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
			pNewNode->SetLevelType((int)LEVEL_GRAPA); // OverRide
			pNewNode->SetCategory(CA_ELEMENT);
			//////////////////////////////////////// Reciprocate
//			pNewNode->GetCurveList()->InsertObject(m_pDrCurve);	// done later
			///////////////////////////////////////////
			//	Need To FinishObject for RectBound 
			////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->ShowObject_On_Off(pNewNode,FE0D,TRUE);
/*
			pObjectMgr->SetActiveObjectIndex(nLabelIndex);		    // set Active Index for Label									
			pObjectMgr->SetActiveObjectType(LABEL);					// set Active ObjectType									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nLabelIndex,LABEL);
			//////////////////////////////////////////////////////////
			pObjectMgr->SetActiveObjectIndex(nNodeIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(FE0D);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,FE0D);
*/

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

int CMI_2SPN::SpawnPatchCopyOff(pMATRIX pXFMat)
{
#ifdef _DEBUG
		CString ObjID = m_pDrPatch->GetObjectID();
		CString strBum;
//		if(ObjID == "C5")
//			strBum = "Bum String C5";
#endif
	/////////////////////////
	int nResult;
    /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// FE0D 
	pList = m_pDrPatch->GetFE0DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// FE1D 
	pList = m_pDrPatch->GetFE1DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnFE1DListCopyOff(pList, pXFMat);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// FE2D 
	pList = m_pDrPatch->GetFE2DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnFE2DListCopyOff(pList, pXFMat);
			if(nResult<0)
				return nResult;
		}
	}
	/////////
	return 0;
}

int CMI_2SPN::SpawnFE2DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
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
		CDrFE2D* pParentElem	= (CDrFE2D*)(pFillList->GetObject( s));
		/////////////
		CDListMgr* pList = pParentElem->GetFE0DList();
		if(pList)
		{
			if(!pList->IsEmpty())
			{
				nResult = SpawnNodeListCopyOff(pList, pXFMat, FALSE);
				if(nResult<0)
					return nResult;
			}
		}
		/////////////////////////////////////////////////////////// Centroid etc 
		pList = pParentElem->GetNodeList();
		if(pList)
		{
			if(!pList->IsEmpty())
			{
				nResult = SpawnNodeListCopyOff(pList, pXFMat, TRUE);
				if(nResult<0)
					return nResult;
			}
		}
	}				
	////////////
	return nResult;
}	 

int CMI_2SPN::SpawnPatchListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pDListMgr 	= pObjectMgr->GetObjectList(MESH2D);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrMesh2D* pPatch = (CDrMesh2D*)pFillList->GetObject( s);
		if(GetPDoneList()->GetObjectIndex(pPatch) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrMesh2D* pTempPatch = m_pDrPatch;
		m_pDrPatch = pPatch;
		pObjectMgr->ShowObject_On_Off(pPatch,MESH2D,FALSE);
		/////////
		nResult = SpawnPatchCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pPatch,MESH2D,TRUE);
		m_pDrPatch = pTempPatch;
		GetPDoneList()->InsertObject(pPatch);
		////////
	}				
	/////////
	return 0;
}
	 		
void CMI_2SPN::ReciprocatePatchNodes(CDListMgr* pList)
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
		index = pNewNode->GetMs2List()->GetObjectIndex(m_pDrPatch);
		if(index<0)
			pNewNode->GetMs2List()->InsertObject(m_pDrPatch);
		////////
	}
}
	 		
int CMI_2SPN::SpawnPatchWithoutDlg(CDrMesh2D* pNewPatch,CDrMesh2D* pOldPatch,pMATRIX pXFMat,
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
		case MESH2D:
			m_pContextPat	= (CDrMesh2D*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			break;
		case MESH3D:
			m_pContextSol	= (CDrMesh3D*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			PatchID			= pOldPatch->GetObjectID();  	
			break;
		case MBJ3D:
			m_pContextO3D	= (CDrMbj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			PatchID			= pOldPatch->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_2SPN::SpawnPatchWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
	{
/*
		char buf[50];
		int nLastNum = pObjectMgr->GetLastObjectNo(MESH2D);		// internal
		sprintf(buf,"%d",nLastNum);
		(*pCid) = "_P";
		(*pCid)	+= buf;
		pObjectMgr->BumpLastObjectNo(MESH2D);		// bump it
*/
		/////////////////////////////
		CMI_Gang0 Gang0;
		CString strID;
		//////////////
		Gang0.SetElemInfoID(strID,MESH2D);		
		*pCid = strID;
	}
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrPatch = pNewPatch;
	/////////////////////
	if(m_pDrPatch != pOldPatch)	// Copy ON
	{	
		//////////////////////////
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
		nResult = SpawnPatch(pOldPatch, pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrPatch->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_2SPN::FillSpawnedPatchDlgDataBase(CDrMesh2D* pDrPatch,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnP	Dlg_SpnP;		
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

void CMI_2SPN::Serialize(CArchive& ar)
{

	CMI_1SPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_2SPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_2SPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
