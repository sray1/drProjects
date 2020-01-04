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
#include "PatEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CPatEdit,CCurEdit,1)
/////////////////////////////////////////////////////////////////////////////
CPatEdit::CPatEdit()
{

	/////////////////////////////////////////// 
    m_pCurrentPatch		= NULL;
}

CPatEdit::~CPatEdit()
{
}
	
void CPatEdit:: ElementLeftDown_PAT()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case P_EDIT:				// PATCH 
		////////////////////////////////////////////////// MOVE	
		default:
			break;
	}  

}
	
int CPatEdit::ShowPatchToEdit(CDrPatch* pDrPatch)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	/////////////////////////////////////////////////////////////// Using MPatMgr TODO
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	/////////////////////////////// Msg
	j = sprintf(buf,"***** Please Note ****\n");
	j += sprintf(buf+j,"\n\nPatches can not be edited directly\n");
	j += sprintf(buf+j,"You may delete and rebuild a Patch\n");
	j += sprintf(buf+j,"However, you have the option of\n");
	j += sprintf(buf+j,"modifying a Patch by editng the Nodes\n");
	j += sprintf(buf+j,"making up the Patch \n");
	/////////////
	AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
	delete str;
	return -2;
	////////////////////
//	CMPatMgr* pMPatMgr;
//	if (pMPatMgr->DoModal_ShowPatchToEdit(pDrPatch) == -2)
//		return -2;
	////////////////////////////////////////////////////////////////////// Update Everything
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 

void CPatEdit::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
//	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
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

int CPatEdit::LeftUp_Patch(CPoint point)
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
	/////////////////////////////
	int nResult = ShowPatchToEdit(pDrPatch);
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCPatEdit::LeftUp_Node\nShowPatchToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

void CPatEdit::ElementLeftUp_PAT(CPoint point)
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
	///////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// EDIT	
		case P_EDIT:				// PATCH 

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

void CPatEdit::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatEdit::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatEdit::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CPatEdit::ShowPatchInfo(CDrPatch* pDrPatch)
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
		"\nYES:\t\tEdit This Patch");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Patch with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CPatEdit::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CPatEdit::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Editing a Patch@";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_EDIT:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "EDIT";
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
						case PATCH:			str	= "PATCH";		ID	= P_EDIT;
								strCur += "Click on a Patch";	break;
						default:			str = "UNKNOWN";	ID	= UNONE;	break;
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
				case PATCH:				return P_DELETE;
*/
}
	
void CPatEdit::Serialize(CArchive& ar)
{

	CCurEdit::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatEdit:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatEdit:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		

