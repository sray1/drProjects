// Rotate.cpp : implementation file
//


#include "stdafx.h"

#include "math.h"
#include "XForm.h"

#include "drgraf.h"
//#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "DrFE1D.h"
#include "DrLabel.h"
///////////////////// dialogMgr
#include "CreMDlgM.h"
#include "Mlg_SpnC.h"
////////////////////
#include "MI_Gang0.h"
#include "MI_Gang1.h"
////////////////////
#include "MI_1SPN.h" 

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
IMPLEMENT_SERIAL(CMI_1SPN,CMI_0SPN,1)
/////////////////////////////////////////////////////////////////////////////
CMI_1SPN::CMI_1SPN()
{
	m_pContextCur = NULL;
	m_pContextPat = NULL;
	m_pContextSol = NULL;
}

CMI_1SPN::~CMI_1SPN()
{
}

int CMI_1SPN::SpawnCurveShowingDlg(CDrMesh1D* pNewCurve,CDrMesh1D* pOldCurve, 
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
			AfxMessageBox("ERROR:CMI_1SPN::CSpawn\nILLEGAL nContextType");
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
		{
			nResult = SpawnCurveCopyOff(&Mat);
/*
			GetCDoneList()->InsertObject(m_pDrCurve);	// done with this one
			////////////////////////////////// Connected Curves  
			CDListMgr* pList = m_pDrCurve->GetCurveList();
			if(pList)
			{
				if(!pList->IsEmpty())
				{
					nResult = SpawnCurveListCopyOff(pList, &Mat);
					if(nResult<0)
						return nResult;
				}
			}
*/
		}
		else
			nResult = SpawnCurve(pOldCurve,&Mat);
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
			nResult = SpawnCurveCopyOff(&Mat);
/*
			GetCDoneList()->InsertObject(m_pDrCurve);	// done with this one
			////////////////////////////////// Connected Curves  
			CDListMgr* pList = m_pDrCurve->GetCurveList();
			if(pList)
			{
				if(!pList->IsEmpty())
				{
					nResult = SpawnCurveListCopyOff(pList, &Mat);
					if(nResult<0)
						return nResult;
				}
			}
*/
		}
		else
			nResult = SpawnCurve(pOldCurve,&Mat);
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
	 
int CMI_1SPN::GetInfoFromDlg(CDrMesh1D* pNewCurve, CDrMesh1D* pOldCurve)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CCreMDlgM* 	pCurMgr;
	CString		Cid = pNewCurve->GetObjectID();
	CString		ParentID = pOldCurve->GetObjectID(); 
	///////////////////////////////////////////////////
	if (pCurMgr->DoModal_Spawn_C(pNewCurve,&Cid,&ParentID) == IDCANCEL)
		return -2; 
	/////////
	return 0;
}
	 
int CMI_1SPN::SpawnCurve(CDrMesh1D* pOldMESH1D, pMATRIX pXFMat)
{
	CDListMgr NodeDoneList;
	////////////
	int nResult;
    /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// FE0D 
	pList = m_pDrCurve->GetFE0DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListinCurve(pList, pXFMat, FALSE);
			if(nResult<0)
				return -1;
			////////////////////////////// Reciprocate
			ReciprocateCurveNodes(pList);
		}
	}
	/////////////////////////////////////////////////////////// CNODE ??????? 
	pList = m_pDrCurve->GetNodeList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnNodeListinCurve(pList, pXFMat, TRUE);//  TRUE:Control Node
			if(nResult<0)
				return -1;
			////////////////////////////// Reciprocate
			ReciprocateCurveNodes(pList);
		}
	}
	/////////////////////////////////////////////////////////// FE1D
	// Regen with the help of newly Xformed FE0Ds
	CMI_Gang1 Gang1;
	nResult = Gang1.Regen_MESH1D_Elements((CDrObject*)m_pDrCurve,(CDrObject*)pOldMESH1D);
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1SPN::SpawnMESH1D\nFE1DList Regen Problem!");
		return -1;
	}
	/////////////////////////////
	return 0;
}

int CMI_1SPN::SpawnNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode)
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
													bCNode,m_pDrCurve,MESH1D);
		///////////////////////////////////// in Curve 
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
			///////////////////////////////////// in Curve 	
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
					nResult = MI_Gang0.ReciprocateElemMeshList(pNewNode, m_pDrCurve, MESH1D);
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
			//		NOTE:
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
/*
int CMI_1SPN::SpawnFE1DListinCurve(CDListMgr* pFillList, pMATRIX pXFMat)
{
	int nResult = -1;  // FOR NOW
	if(nResult<0)
		AfxMessageBox("CMI_1SPN::SpawnFE1DListinCurve\nNOT IMPLEMENTED YET");
    ///////////////////////////// 
	return nResult;
}
*/	 
int CMI_1SPN::SpawnCurveCopyOff(pMATRIX pXFMat)
{
#ifdef _DEBUG
		CString ObjID = m_pDrCurve->GetObjectID();
		CString strBum;
//		if(ObjID == "C5")
//			strBum = "Bum String C5";
#endif
	/////////////////////////
	int nResult;
    /////////////////////////////////////////////////////////////////////////// 
	CDListMgr*	pList;
	/////////////////////////////////////////////////////////// FE0D 
	pList = m_pDrCurve->GetFE0DList();
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
	pList = m_pDrCurve->GetFE1DList();
	if(pList)
	{
		if(!pList->IsEmpty())
		{
			nResult = SpawnFE1DListCopyOff(pList, pXFMat);
			if(nResult<0)
				return nResult;
		}
	}
	/////////
	return 0;
}
	 
int CMI_1SPN::SpawnFE1DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
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
		CDrFE1D* pParentElem	= (CDrFE1D*)(pFillList->GetObject( s));
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
	 		
int CMI_1SPN::SpawnCurveListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat)
{
	if(pFillList->IsEmpty())
		return 0;
	////////////////////////
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	/////////////////////////////////////////////////////////////////// XForm 
	int			nMaxNodes;
	int s;
	/////////////////////////////////////////////////////////////////// XForm 
	nMaxNodes		 	= pFillList->GetCount();
	////////////////////////////////////////// 	
	for ( s = 0; s<nMaxNodes; s++)
	{
		CDrMesh1D* pCurve = (CDrMesh1D*)pFillList->GetObject( s);
		if(GetCDoneList()->GetObjectIndex(pCurve) >=0) // already done
			continue;
		/////////////////////////////////////////////////////////////////  XForm
		CDrMesh1D* pTempCurve = m_pDrCurve;
		m_pDrCurve = pCurve;
		pObjectMgr->ShowObject_On_Off(pCurve,MESH1D,FALSE);
		/////////
		nResult = SpawnCurveCopyOff(pXFMat);
		if(nResult<0)
			return nResult;
		///////////////////
		pObjectMgr->ShowObject_On_Off(pCurve,MESH1D,TRUE);
		m_pDrCurve = pTempCurve;
		GetCDoneList()->InsertObject(pCurve);
		////////
	}
	/////////
	return 0;
}

void CMI_1SPN::ReciprocateCurveNodes(CDListMgr* pList)
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
		index = pNewNode->GetMs1List()->GetObjectIndex(m_pDrCurve);
		if(index<0)
			pNewNode->GetMs1List()->InsertObject(m_pDrCurve);
		////////
	}
}
	 		
int CMI_1SPN::SpawnCurveWithoutDlg(CDrMesh1D* pNewCurve,CDrMesh1D* pOldCurve,pMATRIX pXFMat,
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
		case MESH1D:
			m_pContextCur	= (CDrMesh1D*)pContextObj;
			CurveID			= m_pContextCur->GetObjectID();  	
			break;
		case MESH2D:
			m_pContextPat	= (CDrMesh2D*)pContextObj;
			PatchID			= m_pContextPat->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		case MESH3D:
			m_pContextSol	= (CDrMesh3D*)pContextObj;
			SolidID			= m_pContextSol->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		case MBJ3D:
			m_pContextO3D	= (CDrMbj3D*)pContextObj;
			Obj3DID			= m_pContextO3D->GetObjectID();  	
			CurveID			= pOldCurve->GetObjectID();  	
			break;
		default:
			AfxMessageBox("ERROR:CMI_1SPN::SpawnCurveWithoutDlg\nILLEGAL nContextType");
			return -1;
	}
	/////////////////////////////
	if(*pCid == "")
	{
		char buf[50];
		int nLastNum = pObjectMgr->GetLastObjectNo(MESH1D);		// internal
		sprintf(buf,"%d",nLastNum);
		(*pCid) = "_C";
		(*pCid)	+= buf;
		pObjectMgr->BumpLastObjectNo(MESH1D);		// bump it
	}
	////////////////////////////////////////////////////////////////// CREATE	
	m_pDrCurve = pNewCurve;
	///////////////////////
	if(m_pDrCurve != pOldCurve)	// Copy ON
	{	
		/////////////////////
//		MESH1DPROC	CProc;
//		CProc		= pOldCurve->GetCurveType_S();
		//////////////////////////
//		m_pDrCurve->SetCurveType_S(CProc);	// New Curve
		nResult = FillSpawnedCurveDlgDataBase(m_pDrCurve,*pCid, CurveID);
		if(nResult<0)
			return nResult;
	}
    ////////////////////////////////////////
	if(!pBool->IsSpawnOn())
	{
		nResult = SpawnCurveCopyOff(pXFMat);
/*
		GetCDoneList()->InsertObject(m_pDrCurve);
		/////////////////////////////////////////////////////////// Connected Curves  
		CDListMgr* pList = m_pDrCurve->GetCurveList();
		if(pList)
		{
			if(!pList->IsEmpty())
			{
				nResult = SpawnCurveListCopyOff(pList, pXFMat);
				if(nResult<0)
					return nResult;
			}
		}
*/
	}
	else
		nResult = SpawnCurve(pOldCurve, pXFMat);
	////////////////////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();											
	///////////////////
	return 0;
}

int CMI_1SPN::FillSpawnedCurveDlgDataBase(CDrMesh1D* pDrCurve,CString& Cid,CString& ParentCid)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////
	CMlg_SpnC	Dlg_SpnC;		
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

void CMI_1SPN::Serialize(CArchive& ar)
{

	CMI_0SPN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_1SPN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_1SPN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
