// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
#include "MSolMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
//////////////////////
#include "SolDel.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSolDel,CPatDel,1)
/////////////////////////////////////////////////////////////////////////////
CSolDel::CSolDel()
{

	/////////////////////////////////////////// 
    m_pCurrentSolid		= NULL;
}

CSolDel::~CSolDel()
{
}
	
void CSolDel:: ElementLeftDown_SOL()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case S_DELETE:				// SOLID 
		////////////////////////////////////////////////// MOVE	
		default:
			break;
	}  

}
	
int CSolDel::ShowSolidToDelete(CDrSolid* pDrSolid, BOOL bToBeDeleted)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);
	////////////////////////////////////////////////////////////////////// Show Solid to Delete
	pDrSolid->SetToBeDeleted(bToBeDeleted);
	//////////////////////////////
	pObjList = pObjectMgr->GetObjectList(SOLID);
	nActiveIndex = pObjList->GetObjectIndex(SOLID,pDrSolid->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);
	/////////////
	int i;
	POSITION pos;
	////////////////////////////////////////////////////////////////////// Show Dependent LinSupports
	CDListMgr*	pSupList;
	int			nSupCount;
	//////////////////////////////////////////////// Curves
	pSupList	= pDrSolid->GetSuppList(); 
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
	pStLList	= pDrSolid->GetStaLList(); 
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

int CSolDel::MarkSolid_Delete(CDrSolid* pDrSolid)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);                   
	////////////////////////////////////////////////////////////////////// Solid to Delete
	pDrSolid->SetDeleted(TRUE);
//	CDrLabel* pDrLabel = (CDrLabel*)(pDrNode->GetLabelList()->GetHead());
//	pDrLabel->SetDeleted(TRUE);
	/////////////
	int i;
	POSITION pos;
	////////////////////////////////////////////////////////////////////// Dependent LinSup
	CDListMgr* pSupList;
	int nSupCount;
	//////////////////////////////////////////////// LinSups
	pSupList	= pDrSolid->GetSuppList(); 
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
	pStLList	= pDrSolid->GetStaLList(); 
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
	
void CSolDel::OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_SOL();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CSolDel::LeftUp_Solid(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrSolid*	pDrSolid;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Solid Hit
	index = IsObjectHit(SOLID,point,0);
	////////////////////////////////////////////////////
	if(index>=0)						
	{
		/////////////
		pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
		ID			= pDrSolid->GetObjectID();
		/////////////////////////////////////////
		pList = pObjectMgr->GetObjectList(SOLID);
		nActiveIndex = pList->GetObjectIndex(SOLID, ID);;
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);
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
				nResult = ShowSolidInfo(pDrSolid);
				/////////////
				if(nResult == IDYES)
					//////////////////////////////////////////////////////// Accept Old
					break;
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					index = IsObjectHit(SOLID,point,startIndex);
					if(index>=0)
					{
						pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
						ID		= pDrSolid->GetObjectID();
						///////////////////////////////////////// 
						pList = pObjectMgr->GetObjectList(SOLID);
						nActiveIndex = pList->GetObjectIndex(SOLID, ID);;
						pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
						pObjectMgr->SetActiveObjectType(SOLID);		    // set Active Index									
						pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,SOLID);
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
	m_pCurrentSolid = pDrSolid;
	if(ShowSolidToDelete(pDrSolid,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCSolDel::LeftUp_Solid\nShowSolidToDelete Problem");
		return -1;
	}
	//////////////////////////////////////////////////////////////////// Warning
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	//////////////////////////////
	j = sprintf(buf		,"				***** WARNING !!! ****\n\n");
	j += sprintf(buf+j	,"		   Solid %s is About to be DELETED\n");
	j += sprintf(buf+j	,"     This Will DELETE Affected Objects Shown\n\n\n",ID);
	////////////////////////////
	j += sprintf(buf+j,  "		YES:\t\tDelete This Solid\n");
	j += sprintf(buf+j,"		NO:\t\tCancel Deletion Process");
	int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	delete str;
	///////////
	if(nResult == IDYES)
		//////////////////////////////////////////////////////// Delete
		MarkSolid_Delete(pDrSolid);
	else
	{
		//////////////////////////////////////////////////////// Show Normal/Cancel
		ShowSolidToDelete(pDrSolid,FALSE);
		return -2;
	}
	//////////
	return 0;
}

void CSolDel::ElementLeftUp_SOL(CPoint point)
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
		
		case S_DELETE:				// SOLID 

			////////////////////
			LeftUp_Solid(point);	
			////////////////////
			return;
/*
		////////////////////////////////////////////////// MOVE	
		case S_MOVE:				// SOLID 
			///////		
			m_MI_Solid.LBUpSolidMove();
			return;
*/		
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CSolDel::OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSolDel::OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SOL(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	
}

void CSolDel::OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CSolDel::ShowSolidInfo(CDrSolid* pDrSolid)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrSolid->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	SOLIDPROC 		SolProc		= pDrSolid->GetSolidProc();
	SOLSUBTYPE 		SolSubType	= pDrSolid->GetSolSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Solid Hit ****\n");
	//////////////////////////////////////
	switch(SolProc)
	{
		case SP_EXTRUDE:

			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Extruded Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Extruded Type\n",*pID);

			////

		case SP_ROTATE:

			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Rotated Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Rotated Type\n",*pID);

			////

		case SP_LOFT2:

			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Lofted Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Lofted Type\n",*pID);

			////

		case SP_DUCT:

			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Ducted Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Ducted Type\n",*pID);

			////

		case SP_SWEEP:

			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Sweeping Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Sweeping Type\n",*pID);

			////

		case SP_COONS:
			//////////////////////////////////////////////////// Show Solid
			if(SolSubType == SS_TETRA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nTetraHedral Coons Type\n",*pID);
			else
			if(SolSubType == SS_PENTA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nPentaHedral Coons Type\n",*pID);
			else
			if(SolSubType == SS_HEXA)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nHexaHedral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tEdit This Existing Solid");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Solid with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CSolDel::OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CSolDel::ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID)
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
						case SOLID:			str	= "SOLID";		ID	= S_DELETE;
								strCur += "Click on a Solid";	break;
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
				case SOLID:				return S_MOVE;
				case SOLID:				return S_POST;
				case SOLID:				return S_UNPOST;
				case SOLID:				return S_UNDELETE;
*/
}
	
void CSolDel::Serialize(CArchive& ar)
{

	CCurDel::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SolDel:    Storing\n");	
		

	}
	else
	{
		TRACE(" SolDel:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		

