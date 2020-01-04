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
#include "Mi_Gang3.h"
#include "Mlg_SpnS.h"
////////////////////
#include "MI_3SPN.h" 

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
IMPLEMENT_SERIAL(CMI_3SPN,CMI_2SPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_3SPN::CMI_3SPN()
{
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_3SPN::~CMI_3SPN()
{
}

int CMI_3SPN::SpawnSolidShowingDlg(CDrMesh3D* pNewSolid,CDrMesh3D* pOldSolid, 
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
		case MESH3D:
			m_pContextSol = (CDrMesh3D*)pContextObj;
			break;
		case MBJ3D:
			m_pContextO3D = (CDrMbj3D*)pContextObj;
			break;
		default:
			AfxMessageBox("ERROR:CMI_3SPN::SSpawn\nILLEGAL nContextType");
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
	///////////////////////////////// Spawn Solides
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
			nResult = SpawnSolid(pOldSolid, &Mat);
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
			nResult = SpawnSolid(pOldSolid, &Mat);
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
	 
int CMI_3SPN::GetInfoFromDlg(CDrMesh3D* pNewSolid,CDrMesh3D* pOldSolid)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreMDlgM* 	pMSolMgr;
	CString		Cid = pNewSolid->GetObjectID();
	CString		ParentID = pOldSolid->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pMSolMgr->DoModal_Spawn_S(pNewSolid,&Cid,ParentID) == IDCANCEL)
		return -2; 
	//////////
	return 0;
}
	 
int CMI_3SPN::SpawnSolid(CDrMesh3D* pOldMESH3D, pMATRIX pXFMat)
{
	CDListMgr*	pFE0DList;
	int			nResult;
	/////////////////////////////////////////////////////////// FE0D/MNode
    pFE0DList = m_pDrSolid->GetFE0DList();
	/////////////////////////////////////////// Fill with Old FE0Ds
	pFE0DList->RemoveAll();
	pFE0DList->AddTail(pOldMESH3D->GetFE0DList());
	///
	if(pFE0DList->IsEmpty())
	{
		AfxMessageBox("Internal ERROR:\nCMI_3SPN::SpawnSolid\npFE0DList->IsEmpty()!");
		return -1;
	}
	/////////////////////////
	nResult = SpawnNodeListinSolid(pFE0DList, pXFMat, FALSE);	// MNode/FE0D
	///////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_3SPN::SpawnSolid\nFE0DList Regen Problem!");
		return -1;
	}
	////////////////////////////// Reciprocate
	ReciprocateSolidNodes(pFE0DList);
	/////////////////////////////////////////////////////////// CNode
	if(!(pOldMESH3D->GetNodeList()->IsEmpty()) )
	{
	    pFE0DList = m_pDrSolid->GetNodeList();
		/////////////////////////////////////////// Fill with Old CNodes
		pFE0DList->RemoveAll();
		pFE0DList->AddTail(pOldMESH3D->GetNodeList());
		///
		if(pFE0DList->IsEmpty())
		{
			AfxMessageBox("Internal ERROR:\nCMI_3SPN::SpawnSolid\npFE0DList->IsEmpty()!");
			return -1;
		}
		/////////////////////////
		nResult = SpawnNodeListinSolid(pFE0DList, pXFMat, TRUE);	// bCNode = TRUE
		///////
		if(nResult<0)
		{
			AfxMessageBox("Internal ERROR:\nCMI_3SPN::SpawnSolid\nFE0DList Regen Problem!");
			return -1;
		}
		////////////////////////////// Reciprocate
		ReciprocateSolidNodes(pFE0DList);
	}
	/////////////////////////////////////////////////////////// FE1D/FE2D
	CMI_Gang3 Gang3;
	nResult = Gang3.Regen_MESH3D_Elements((CDrObject*)m_pDrSolid,(CDrObject*)pOldMESH3D);
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_3SPN::SpawnSolid\nFE1DList Regen Problem!");
		return -1;
	}
	////////////
	return 0;
}

int CMI_3SPN::SpawnNodeListinSolid(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
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
		/////////////////////////////////////////////////////////////////  New
		CDrFE0D NewNode;
		///////////////////////////////////////// Get ID
		NewNID = "";	// force it to create a name
		int nResult = SpawnNodeWithoutDlg(&NewNode,pOldNode,pXFMat,&NewNID,
													bCNode,m_pDrSolid,MESH3D);
		///////////////////////////////////// in Solid 
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
			///////////////////////////////////// in Solid 	
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
					nResult = MI_Gang0.ReciprocateElemMeshList(pNewNode, m_pDrSolid, MESH3D);
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
			//			Solid in which case we don't want to spawn more
			//			than once. This is Taken care of later in MI_PSPN
			/////////////////////////////////////////////////////////////////
			WORLD LocalPos = *(NewNode.GetLocalPos());
			///////////////////////////////////// in THE List 
			pNewNode = Gang0.CreateFE0D(NewNID,pLabel, LocalPos, bCNode, TRUE, FALSE,
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

int CMI_3SPN::SpawnSolidCopyOff(pMATRIX pXFMat)
{
#ifdef _DEBUG
		CString ObjID = m_pDrSolid->GetObjectID();
		CString strBum;
//		if(ObjID == "C5")
//			strBum = "Bum String C5";
#endif
	/////////////////////////
	int nResult;
    /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// FE0D 
	pList = m_pDrSolid->GetFE0DList();
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
	pList = m_pDrSolid->GetFE1DList();
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
	pList = m_pDrSolid->GetFE2DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnFE2DListCopyOff(pList, pXFMat);
			if(nResult<0)
				return nResult;
		}
	}
	/////////////////////////////////////////////////////////// FE3D 
	pList = m_pDrSolid->GetFE3DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnFE3DListCopyOff(pList, pXFMat);
			if(nResult<0)
				return nResult;
		}
	}
	/////////
	return 0;
}

int CMI_3SPN::SpawnFE3DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
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
		CDrFE3D* pParentElem	= (CDrFE3D*)(pFillList->GetObject( s));
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
	}				
	////////////
	return nResult;
}	 

int CMI_3SPN::SpawnSolidListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = 0;
	////////////////
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pDListMgr 	= pObjectMgr->GetObjectList(MESH3D);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	CString		NewCID;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrMesh3D* pSolid = (CDrMesh3D*)pFillList->GetObject( s);
		if(GetPDoneList()->GetObjectIndex(pSolid) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrMesh3D* pTempSolid = m_pDrSolid;
		m_pDrSolid = pSolid;
		pObjectMgr->ShowObject_On_Off(pSolid,MESH3D,FALSE);
		/////////
		nResult = SpawnSolidCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pSolid,MESH3D,TRUE);
		m_pDrSolid = pTempSolid;
		GetPDoneList()->InsertObject(pSolid);
		////////
	}				
	/////////
	return 0;
}
	 		
void CMI_3SPN::ReciprocateSolidNodes(CDListMgr* pList)
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
		index = pNewNode->GetMs3List()->GetObjectIndex(m_pDrSolid);
		if(index<0)
			pNewNode->GetMs3List()->InsertObject(m_pDrSolid);
		////////
	}
}
	 		
int CMI_3SPN::SpawnSolidWithoutDlg(CDrMesh3D* pNewSolid,CDrMesh3D* pOldSolid,pMATRIX pXFMat,
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
		case MESH3D:
			m_pContextSol	= (CDrMesh3D*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			SolidID			= pOldSolid->GetObjectID();  	
			break;
		case MBJ3D:
			m_pContextO3D	= (CDrMbj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			SolidID			= pOldSolid->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_3SPN::SpawnSolidWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
	{
/*
		char buf[50];
		int nLastNum = pObjectMgr->GetLastObjectNo(MESH3D);		// internal
		sprintf(buf,"%d",nLastNum);
		(*pCid) = "_P";
		(*pCid)	+= buf;
		pObjectMgr->BumpLastObjectNo(MESH3D);		// bump it
*/
		/////////////////////////////
		CMI_Gang0 Gang0;
		CString strID;
		//////////////
		Gang0.SetElemInfoID(strID,MESH3D);		
		*pCid = strID;
	}
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrSolid = pNewSolid;
	/////////////////////
	if(m_pDrSolid != pOldSolid)	// Copy ON
	{	
		//////////////////////////
		nResult = FillSpawnedSolidDlgDataBase(m_pDrSolid,*pCid, SolidID);
		if(nResult<0)
			return nResult;
	}
    ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
	{
		nResult = SpawnSolidCopyOff(pXFMat);
	}
	else
		nResult = SpawnSolid(pOldSolid, pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_3SPN::FillSpawnedSolidDlgDataBase(CDrMesh3D* pDrSolid,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnS	Dlg_SpnS;		
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

void CMI_3SPN::Serialize(CArchive& ar)
{

	CMI_1SPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_3SPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_3SPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
