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
#include "SolEdit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSolEdit,CPatEdit,1)
/////////////////////////////////////////////////////////////////////////////
CSolEdit::CSolEdit()
{

	/////////////////////////////////////////// 
    m_pCurrentSolid		= NULL;

}

CSolEdit::~CSolEdit()
{
}

void CSolEdit:: ElementLeftDown_SOL()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// SOLID
		case S_EDIT:				// SOLID 
		////////////////////////////////////////////////// MOVE	
		default:
			break;
	}  

}
	
int CSolEdit::ShowSolidToEdit(CDrSolid* pDrSolid)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);
	/////////////////////////////////////////////////////////////// Using MSolMgr TODO
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	/////////////
	int j;
	/////////////////////////////// Msg
	j = sprintf(buf,"***** Please Note ****\n");
	j += sprintf(buf+j,"\n\nSolids can not be edited directly\n");
	j += sprintf(buf+j,"You may delete and rebuild a Solid\n");
	j += sprintf(buf+j,"However, you have the option of\n");
	j += sprintf(buf+j,"modifying a Solid by editng the Nodes\n");
	j += sprintf(buf+j,"making up the Solid \n");
	/////////////
	AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
	delete str;
	return -2;
	////////////////////
//	CMSolMgr* pMSolMgr;
//	if (pMSolMgr->DoModal_ShowSolidToEdit(pDrSolid) == -2)
//		return -2;
	////////////////////////////////////////////////////////////////////// Update Everything
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 
	
void CSolEdit::OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CSolEdit::LeftUp_Solid(CPoint point)
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
	///////////////////////////////////////////// See if any Existing Node Hit
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
	/////////////////////////////
	int nResult = ShowSolidToEdit(pDrSolid);
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCSolEdit::LeftUp_Node\nShowSolidToEdit Problem");
		return -1;
	}
	else
	if(nResult == -2)		// Cancel
		return -2;
	////////////////////////////
	return 0;
}

void CSolEdit::ElementLeftUp_SOL(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
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
		case S_EDIT:				// SOLID 

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

void CSolEdit::OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSolEdit::OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSolEdit::OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

int CSolEdit::ShowSolidInfo(CDrSolid* pDrSolid)
{
	int nResult = 1;	// temporarily set
/*
	CString ID;
	CString* pID = &ID;
	ID = pDrSolid->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	SOLIDPROC 		PatProc		= pDrSolid->GetSolidProc();
	PATSUBTYPE 		PatSubType	= pDrSolid->GetPatSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Solid Hit ****\n");
	//////////////////////////////////////
	switch(PatProc)
	{
		case PP_EXTRUDE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Extrusion\n",*pID);
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Rotation\n",*pID);
			break;

		case PP_LOFT2:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\n",*pID);
			break;

		case PP_DUCT:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Ducting\n",*pID);
			break;

		case PP_SWEEP:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by\nSweeping\n",*pID);
			break;

		case PP_COONS:
			//////////////////////////////////////////////////// Show Solid
			if(PatSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nTriangular Coons Type\n",*pID);
			else
			if(PatSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nQuadrilateral Coons Type\n",*pID);

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
*/
	return nResult;
}

void CSolEdit::OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
UINT CSolEdit::ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Editing a Solid@";
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
						case SOLID:			str = "SOLID";		ID = S_EDIT;
								strCur += "Click on a Solid";	break;
						default:			str = "UNKNOWN";	ID = UNONE;		break;
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
}
	
void CSolEdit::Serialize(CArchive& ar)
{

	CPatEdit::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SolEdit:    Storing\n");	
		

	}
	else
	{
		TRACE(" SolEdit:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


