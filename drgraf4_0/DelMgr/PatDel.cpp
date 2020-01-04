// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "MPatMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
//////////////////////
#include "PatDel.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CPatDel,CCurDel,1)
/////////////////////////////////////////////////////////////////////////////
CPatDel::CPatDel()
{

	/////////////////////////////////////////// 
    m_pCurrentPatch		= NULL;
}

CPatDel::~CPatDel()
{
}
	
void CPatDel:: ElementLeftDown_PAT()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case P_DELETE:				// PATCH 
		////////////////////////////////////////////////// MOVE	
		default:
			break;
	}  

}
	
int CPatDel::ShowPatchToDelete(CDrPatch* pDrPatch, BOOL bToBeDeleted)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	////////////////////////////////////////////////////////////////////// Show Patch to Delete
	pDrPatch->SetToBeDeleted(bToBeDeleted);
	//////////////////////////////
	pObjList = pObjectMgr->GetObjectList(PATCH);
	nActiveIndex = pObjList->GetObjectIndex(PATCH,pDrPatch->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
	////////////////////////////////////////////////////////////////////// Show Dependent Solids
	CDListMgr* pSolList;
	int i,nSolCount;
	POSITION pos;
	//////////////////////////////////////////////// Solids
	pSolList	= pDrPatch->GetSolidList(); 
	nSolCount	= pSolList->GetCount();
	///////////
	for(i=0;i<nSolCount;i++)
	{
		pos					= pSolList->FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(SOLID);
			nActiveIndex = pObjList->GetObjectIndex(SOLID,pDrSolid->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent LinSupports
	CDListMgr*	pSupList;
	int			nSupCount;
	//////////////////////////////////////////////// Curves
	pSupList	= pDrPatch->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos						= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		////////////////
		if(pDrLinSup)
		{
			pDrLinSup->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(LIN_SUPPORT);
			nActiveIndex = pObjList->GetObjectIndex(LIN_SUPPORT,pDrLinSup->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(LIN_SUPPORT);	    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,LIN_SUPPORT);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Static
	CDListMgr*	pStLList;
	int			nStLCount;
	//////////////////////////////////////////////// Curves
	pStLList	= pDrPatch->GetStaLList(); 
	nStLCount	= pStLList->GetCount();
	///////////
	for(i=0;i<nStLCount;i++)
	{
		pos						= pStLList->FindIndex(i);
		CDrStatic* pDrStatic	= (CDrStatic*)(pStLList->GetAt(pos));
		////////////////
		if(pDrStatic)
		{
			pDrStatic->SetToBeDeleted(bToBeDeleted);
			/////////////////////////////
			pObjList = pObjectMgr->GetObjectList(STATICLOAD);
			nActiveIndex = pObjList->GetObjectIndex(STATICLOAD,pDrStatic->GetObjectID());
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(STATICLOAD);	    // set Active Index									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,STATICLOAD);

		}
	}
	///////////////////////////////
	return 0;
}	 

int CPatDel::MarkPatch_Delete(CDrPatch* pDrPatch)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);                   
	////////////////////////////////////////////////////////////////////// Patch to Delete
	pDrPatch->SetDeleted(TRUE);
//	CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
//	pDrLabel->SetDeleted(TRUE);
	////////////////////////////////////////////////////////////////////// Dependent Solids
	CDListMgr* pSolList;
	int i,nSolCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pSolList	= pDrPatch->GetSolidList(); 
	nSolCount	= pSolList->GetCount();
	///////////
	for(i=0;i<nSolCount;i++)
	{
		pos					= pSolList->FindIndex(i);
		CDrSolid* pDrSolid	= (CDrSolid*)(pSolList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrSolid->IsDeleted())
			continue;
		////////////////
		if(pDrSolid)
		{
			pDrSolid->SetShow(FALSE);
			pDrSolid->SetDeleted(TRUE);
			pDrSolid->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr* pSupList;
	int nSupCount;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrPatch->GetSuppList(); 
	nSupCount	= pSupList->GetCount();
	///////////
	for(i=0;i<nSupCount;i++)
	{
		pos					= pSupList->FindIndex(i);
		CDrLinSup* pDrLinSup	= (CDrLinSup*)(pSupList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrLinSup->IsDeleted())
			continue;
		////////////////
		if(pDrLinSup)
		{
			pDrLinSup->SetShow(FALSE);
			pDrLinSup->SetDeleted(TRUE);
			pDrLinSup->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Show Dependent Static
	CDListMgr*	pStLList;
	int			nStLCount;
	//////////////////////////////////////////////// Curves
	pStLList	= pDrPatch->GetStaLList(); 
	nStLCount	= pStLList->GetCount();
	///////////
	for(i=0;i<nStLCount;i++)
	{
		pos						= pStLList->FindIndex(i);
		CDrStatic* pDrStatic	= (CDrStatic*)(pStLList->GetAt(pos));
		//////////////////////////////////////////////////////// if Marked Deleted: Continue
		if(pDrStatic->IsDeleted())
			continue;
		////////////////
		if(pDrStatic)
		{
			pDrStatic->SetShow(FALSE);
			pDrStatic->SetDeleted(TRUE);
			pDrStatic->SetShow(TRUE);

		}
	}
	////////////////////////////////////////////////////////////////////// Update ShowStuff
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 
	
void CPatDel::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	CDListMgr* pDListMgr;
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_PAT();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CPatDel::LeftUp_Patch(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrPatch*	pDrPatch;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	index = IsObjectHit(PATCH,point,0);
	////////////////////////////////////////////////////
	if(index>=0)						
	{
		/////////////
		pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
		ID			= pDrPatch->GetObjectID();
		/////////////////////////////////////////
		pList = pObjectMgr->GetObjectList(PATCH);
		nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
		//////////////////////////////////////////////////////////////// MultipleSearch
		int startIndex = index+1;
		int nResult;
		/////////////////////////
		if(!m_bAutoAcceptOn)
		{
			/////////////
			for(;;)
			{
				//////////////////////////////
				nResult = ShowPatchInfo(pDrPatch);
				/////////////
				if(nResult == IDYES)
					//////////////////////////////////////////////////////// Accept Old
					break;
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					index = IsObjectHit(PATCH,point,startIndex);
					if(index>=0)
					{
						pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
						ID		= pDrPatch->GetObjectID();
						///////////////////////////////////////// 
						pList = pObjectMgr->GetObjectList(PATCH);
						nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
						pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
						pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
						pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
						////////////////////////////////////////
						startIndex  = index+1;
						/////////////////////
					}
					else
						////////////////
						return -2;
					/////////
				}
				else				// Cancel
					//////////////////////////////////////////////////////// Do Nothing
					return -2;
			}						// end for loop
			///////////////////////////////////////
		}				// end !AutoAccept loop
	}			// end Index loop
	else
		return 0;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentPatch = pDrPatch;
	if(ShowPatchToDelete(pDrPatch,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCPatDel::LeftUp_Patch\nShowPatchToDelete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   Patch %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Patch\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkPatch_Delete(pDrPatch);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		ShowPatchToDelete(pDrPatch,FALSE);
		return -2;
	}
	//////////
	return 0;
}

void CPatDel::ElementLeftUp_PAT(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	/////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	///////////////////
	switch(m_nActiveTool) 
	{
		
		case P_DELETE:				// PATCH 

			////////////////////
			LeftUp_Patch(point);	
			////////////////////
			return;
/*
		////////////////////////////////////////////////// MOVE	
		case P_MOVE:				// PATCH 
			///////		
			m_MI_Solid.LBUpPatchMove();
			return;
*/		
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CPatDel::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////////////// do nothing for now
	return;
}

void CPatDel::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
    /////////////////////////////  ELement Dialog On/Off Check
    POINT Logpoint;
    m_pdc->DPtoLP(&point);
    Logpoint.x = point.x;
    Logpoint.y = point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    if(m_Gener == FORWARD)
		ElementLeftUp_PAT(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	
}

void CPatDel::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{ 
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	///////////////////////////////// do nothing
	return;
}

int CPatDel::ShowPatchInfo(CDrPatch* pDrPatch)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrPatch->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	PATCHPROC 		PatProc		= pDrPatch->GetPatchProc();
	PATSUBTYPE 		PatSubType	= pDrPatch->GetPatSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Patch Hit ****\n");
	//////////////////////////////////////
	switch(PatProc)
	{
		case PP_EXTRUDE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Extrusion\n",*pID);
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s was Generated by Rotation\n",*pID);
			break;

		case PP_LOFT2:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Lofting\n",*pID);
			break;

		case PP_DUCT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Ducting\n",*pID);
			break;

		case PP_SWEEP:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by\nSweeping\n",*pID);
			break;

		case PP_COONS:
			//////////////////////////////////////////////////// Show Patch
			if(PatSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nTriangular Coons Type\n",*pID);
			else
			if(PatSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Patch %s\nQuadrilateral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tEdit This Existing Patch");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Patch with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CPatDel::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	//////////////////////////////// do nothing Op
	return;
}

/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CPatDel::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Deleting@";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_DELETE:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "DELETE";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(CntlID)
			{
				//////////////////////////////////////// Elements
				case ELEMENT:
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:

//					pWnd->SetMouseBoxType(ELEMDIMBOX);
					str = "ELEMENT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// EDim0/EDim1...
					switch(IGenID)
					{
						/////////
						case PATCH:			str	= "PATCH";		ID	= P_DELETE;
								strCur += "Click on a Patch";	break;
						default:			str = "UNKNOWN";	ID	= UNONE;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
			}
		}
	}
	return UNONE;
/*
				case PATCH:				return P_MOVE;
				case PATCH:				return P_POST;
				case PATCH:				return P_UNPOST;
				case PATCH:				return P_UNDELETE;
*/
}
	
void CPatDel::Serialize(CArchive& ar)
{

	CCurDel::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatDel:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatDel:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		

