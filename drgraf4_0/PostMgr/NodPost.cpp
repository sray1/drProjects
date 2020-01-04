// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include <stdlib.h>	// _itoa

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
//#include "P_NodMgr.h"  
///////////////////// IGens
#include "Def_IGen.h"
///////////////////// Elems
#include "Def_Elem.h"
//////////////////////
#include "NodPost.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_BALLJOINT		1	// 1 Object        
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CNodPost,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodPost::CNodPost()
{

	m_strParentType		= "";
	m_ObjType			= UNONE;
	m_bCNode			= FALSE;
	m_bMNode			= FALSE;
	///////////////////////////////////////////// 
	m_pPost0DDlg		= NULL;
	////////////////////////////
	m_bAutoAcceptOn		= FALSE;
  	m_bDialogOn    		= FALSE;
	m_bDragOn      		= FALSE;
	m_bDragging	   		= FALSE;
	/////////////////////////////////////////// Node 
    m_pCurrentNode		= NULL;
	///////////////////////////////////////////
	m_bRefreshOn		= FALSE;
}

CNodPost::~CNodPost()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pPost0DDlg->m_hWnd)
		m_pPost0DDlg->DestroyWindow();
	///////////////////
	delete m_pPost0DDlg; 
	///////////////////
}

int CNodPost::UpdateSceneView(CString& ObjID,UINT nObjType)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	int nActiveIndex; 
	CDListMgr* pObjList;
	///////////////////////////////////////////////////////// 
	pObjList = pObjectMgr->GetObjectList(nObjType);
	nActiveIndex = pObjList->GetObjectIndex(nObjType,ObjID);
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(nObjType);		    // set Active Index									
	pMsObjMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,nObjType);
	///////////////////////////////
	return 0;
}
	
void CNodPost::SizeRectDlgIn(CRect& BoxRect)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	///////////////////////////////
	CRect FrameRect;
	pWnd->GetWindowRect(&FrameRect);
	/////////////////////////////////////////////////////////////// ...InBox 
	int Boxwidth  		= BoxRect.Width();
	int Boxheight 		= BoxRect.Height();
	///////////////////////////////////////
	BoxRect.top    = 1 + FrameRect.top + cyEdge + cyCapSize;   //		
	BoxRect.bottom = BoxRect.top	+ Boxheight; //
	BoxRect.right  = FrameRect.right - cxBorder;
	BoxRect.left   = BoxRect.right	- Boxwidth;
	////////////////////////////////
	return;
}

void CNodPost::InitDlgIn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pPost0DDlg	= new CDlg_FE0I(pWnd);
	/////////////////////////////////////////////////////////////////// Init
}

void CNodPost::Init_NOD()
{
	C3DMath Math3D;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	/////////////////////////////
	if(m_ObjType == BALLJOINT)
		pMsObjMgr->SetElemInfoID(m_PostedID,BALLJOINT);
	/////////////////////////////////////////// Node
	m_pPostedNode		= NULL;
	m_strParentType		= "";
	m_ParentID			= "";
	m_pCurrentNode		= NULL;
	//////////
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;
	/////////////////////////////////////////// Dlg_FE0I 
}

void CNodPost::Terminate_NOD(BOOL bError)
{
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pPostedNode)
		{
			delete m_pPostedNode;
			m_pPostedNode = NULL;
		}
		///////////////////////////
	}
}
	
void CNodPost::ElementLeftDown_NOD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		case BALLJOINT:
			break;
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

int CNodPost::ShowNodeToPost(CDrNode* pDrNode, BOOL bToBePosted)
{
	//  ISOCURVES todo
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////////////////////////////////////////////////////// Show Curve to Post
	pDrNode->SetToBePosted(bToBePosted);
	//////////////////////////////
	pObjList = pObjectMgr->GetObjectList(NODE);
	nActiveIndex = pObjList->GetObjectIndex(NODE,pDrNode->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	///////////////////////////////
	return 0;
}	 

int CNodPost::Post_BALLJOINT(CDrNode* pDrNode)		
{
	/////////////////////////////////////////////////////////
	//			Called from IGenID = NODE Only
	//				pDrNode can Only be MNode
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////// GetInfo		todo
	return 0;
}
	
void CNodPost::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////////////////////// No Node
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_NOD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CNodPost::UpdateDlg_TRUE_NOD()
{
	/////////////////////////////////////////////////////
//	m_pPost0DDlg->UpdateData(TRUE); // from screen
	////////////////////////////// todo Dlg Items
	////////////////////////
}			

void CNodPost::UpdateDlg_FALSE_NOD()
{
	////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////// todo Dlg Items
	////////////////////////////////////////////////////////////
//	GetPost0DDlg()->GetDlgItem(IDD_PID)->EnableWindow(FALSE);
//	GetPost0DDlg()->GetDlgItem(IDD_MID)->EnableWindow(FALSE);
//	GetPost0DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(FALSE);
	//////////////////////////////////////
}

void CNodPost::UpdateDlg_FALSE_NOD_0()
{
	///////////////////
	UpdateDlg_FALSE_NOD();
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_ObjType)
	{
		case BALLJOINT:
			strCurr = "Generating BALL Joints@Click ON A " + m_strParentType;
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	m_pPost0DDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CNodPost::UpdateDlg_FALSE_BALLJOINT()
{
	if(m_ObjType != BALLJOINT)
		return;
	///////////////////
	UpdateDlg_FALSE_NOD();
	UpdateDlg_FALSE_NOD_0();
	///////////////////
//	GetPost0DDlg()->GetDlgItem(IDD_FE0_IN)->SetWindowText("BALL JOINT Posting Info");
	////////////////////////////////////////////////
	m_pPost0DDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CNodPost::LeftUp_NODE(CPoint point,BOOL bCNode,BOOL bMNode)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	index = IsObjectHit(NODE,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Node Hit
	//////////////////////////////////////////////////// Check if CNODE required
	pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
	if(
		((!pDrNode->IsControlNode()) && bCNode) ||
		((pDrNode->IsControlNode()) && !bCNode)	
	)		
		index = -1;					// No Hit
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Node Hit
	//////////////////////////////////////////////////// Check if MNODE required
	pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
	if(
		((!pDrNode->IsMeshNode()) && bMNode) ||
		((pDrNode->IsMeshNode()) && !bMNode)	
	)		
		index = -1;					// No Hit
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Node Hit
	////////////////////////////////////////////////////
	pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
	ID					= pDrNode->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(NODE);
	nActiveIndex = pList->GetObjectIndex(NODE, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	int nResult;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		/////////////
		for(;;)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			/////////////
			int j;
			/////////////////////////////// Coords
			WORLD Loc = *(pDrNode->GetLocalPos());
			WORtoWOP(&Loc,&Loc);	// to Physical
			//////////////////////////////
			j = sprintf(buf,"***** A Node Hit ****\n");
			j += sprintf(buf+j,"with Mouse Coordinates (with %f Tolerance):",dTol);
			j += sprintf(buf+j,"\nExisting NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
				ID,Loc.x,Loc.y,Loc.z);
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\t\tPost This Node");
			//////////////////////////
			if(m_ProbLim == PDL_TWO)
			{
				j += sprintf(buf+j,
					"\nNO:\t\tCancel Selection Process");
				nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
				if(nResult == IDNO)
				{
					delete str;
					return -2;			// cancel: stop Searching
				}
			}
			if(m_ProbLim == PDL_THREE)
			{
				j += sprintf(buf+j,
					"\nNO:\t\tFind Next Node with same Trace");
				j += sprintf(buf+j,
					"\nCANCEL:\t\tCancel Selection Process");
				nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			}
			/////////////
			if(nResult == IDYES)
			{
				//////////////////////////////////////////////////////// Accept Old
				delete str;
				break;
			}
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(NODE,point,startIndex);
				//////////////////////////////////////////////////// Check if CNODE required
				if(index>=0)	
				{
					CDrNode* pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
					if(
						((!pDrNode->IsControlNode()) && bCNode) ||
						((pDrNode->IsControlNode()) && !bCNode)	
					)		
						index = -1;					// No Hit
				}
				//////////////////////////////////////////////////// Check if MNODE required
				if(index>=0)	
				{
					CDrNode* pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
					if(
						((!pDrNode->IsMeshNode()) && bMNode) ||
						((pDrNode->IsMeshNode()) && !bMNode)	
					)		
						index = -1;					// No Hit
				}
				/////////////////////////////////////////////////////////////// Right Type
				if(index>=0)
				{
					pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
					ID		= pDrNode->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(NODE);
					nActiveIndex = pList->GetObjectIndex(NODE, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
				{
					////////////////
					delete str;
					return -2;
				}
				/////////
			}
			else				// Cancel
			{
				//////////////////////////////////////////////////////// Do Nothing
				delete str;
				return -2;
			}
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept 
	m_pCurrentNode = pDrNode;
	//////////
	return 0;
}

void CNodPost::ElementLeftUp_NOD(CPoint point)
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
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	///////////////////
	switch(m_nActiveTool) 
	{

		case BALLJOINT:
				
			if(m_nInfoDone > MAX_INFO_BALLJOINT)
				return;
			////////////////
			UpdateDlg_TRUE_NOD();
			//////////////////
			if(LeftUp_NODE(point,FALSE,TRUE)<0)		// FALSE = Not CNODE// TRUE = MNODE
			////////////////////
			{
				Terminate_NOD(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_NOD();
			///////
			return;
		//////////////////////////////////////////////////
		default:  
			return;
	} 
}	

void CNodPost::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
  	/////////////////////////////////////////////////////////
//	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
    /////////////////////////////  ELement Dialog On/Off Check
    POINT Logpoint;
    m_pdc->DPtoLP(&point);
    Logpoint.x = point.x;
    Logpoint.y = point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    if(m_Gener == FORWARD)
		ElementLeftUp_NOD(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}
void CNodPost::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CMouseMgr* pMouseMgr	= pWnd->GetMouseMgr(); 
	////////////////////////// LOG: Log/DEScaled
   	m_pdc->DPtoLP(&point);     
	LPOINT LpLOG;
	LpLOG.x = (long)point.x;
	LpLOG.y = (long)point.y;
   	m_pdc->LPtoDP(&point);
    /////////////////////////////////////////////
    if(!m_bDragging)  // not currently dragging 
    { 
    
		//////////////////////////////////////
		LPOINT3 MouseOldTempWIC = GetMouseOldWIC();
	    LPOINT3 MouseTempWIC 	= GetMouseWIC();
   		SetMouseOldWIC(MouseTempWIC);
   		LPOINT3 MouseWIC;
    	///////////////////////  LOG :DEScaled
    	LOGtoWIC2(&MouseWIC,&LpLOG,&MouseTempWIC); //LOG/Scaled WIC
    	////////////////////                 
    	SetMouseWIC(MouseWIC);
    	///////////////////////////
//    	pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
		pMouseMgr->SetStatusMouseWIC(MouseWIC);
		////////////////////////////
		///////////////////// recover MouseWIC changed for statusbar update 
	    SetMouseOldWIC(MouseOldTempWIC);
	    SetMouseWIC(MouseTempWIC);

		return;
    }	
}

void CNodPost::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();

	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////  ELement Dialog On/Off Check
	m_bDialogOn     = pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	/////////////////////////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		case BALLJOINT:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CNodPost::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature_NOD()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	////////////////////////////////////////////////// Update Info
	UpdateDlg_TRUE_NOD();
	/////////////////
	if(RightUp_NotAutoAccept_NOD()<0)
	{
		Terminate_NOD(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{
	
		/////////////////////////////////// 0D
		case BALLJOINT:				//
			
			//////////////////
			if(Post_BALLJOINT(m_pCurrentNode)<0)
			////////////////
			{
				Terminate_NOD(TRUE);
				return;
			}
			else
			{
				Terminate_NOD(FALSE);
				Init_NOD();
				/////////////////////////
				UpdateDlg_FALSE_BALLJOINT();
				break;
			}
			///////////////////	
			break;

		//////////////	
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	char buf[50];
	pObjectMgr->BumpLastInputNo(BALLJOINT);						// bump it
    m_LastNum	= pObjectMgr->GetLastInputNo(BALLJOINT);		// internal
	sprintf(buf,"%d",m_LastNum);
	m_PostedID	= "";
	m_PostedID	+= buf;
	////////////////////////////////////////////////////////////////////////
}

int CNodPost::RightUp_Premature_NOD()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////// 
	int		nAnswer		= IDOK;
	BOOL	bPreMature	= FALSE;
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	switch(m_ObjType)
	{
		case BALLJOINT:

			if(m_nInfoDone<MAX_INFO_BALLJOINT)
				bPreMature = TRUE;
			break;

		default:
			break;
	}
	//////////////// PreMature
	if(bPreMature)
		return -1;
	////////
	return 0;
}	

int CNodPost::RightUp_NotAutoAccept_NOD()
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
*/
	////////////////////////////////////////////////////// 
	int nAnswer = IDOK;
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		switch(m_ObjType)
		{
			case BALLJOINT:

				nAnswer = ShowInputInfo_BALLJOINT();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			default:
				break;
		}
		/////////////////////////
		if(nAnswer == IDCANCEL)
		{
			CString* str = new CString;
			char* buf	= str->GetBuffer(BUFF_SIZE);
			sprintf(buf,"Do You Want to Delete\nCurrent Posted %s to Start Allover",m_strParentType);
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////////////////
			if(nAnswer == IDYES)		//delete
			{
				/////////////////////////////////////// Reset
				m_nInfoDone		= 0;	// 
				m_bDone			= TRUE;	// 
				/////////////////////////////////////
				return -1;
			}
		}
		/////////////////////
		return 0; 
	}
	/////////
	return 0;
}

int CNodPost::ShowInputInfo_BALLJOINT()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** BALL JOINT Info ******");
	/////////////////////////////////////////////////////////////////////
	if(j>BUFF_SIZE)
	{
		sprintf( buf, "Internal Error:\nIncrease buffer to %d",j);
		AfxMessageBox(*str);
		delete str;
		return -1;
	}	 
	///////////////////////////////////////////////////////////////	
	int nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	//////
	return nAnswer;
}

/////////////////////////////////////////////////////////////////////////////
void CNodPost::ModeLessOff_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetPost0DDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_FE0IN,IDOK);
}

void CNodPost::ModeLessOn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
	m_ObjType = aTool;
	////////////////////////////
//		if(!(GetCreOpDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_FE0IN);	// pWnd will dispatch to right place
												// based on IGenID

}

/////////////////////////////////////////////////////////////////////////////
long CNodPost::CreateorActivatePost_NOD(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= NODE;
	m_strParentType = "Node";
	/////////////////////////////////////////////////////////
	GetPost0DDlg()->m_ObjType = m_ObjType;
	///////////////////////////////////////
	if(GetPost0DDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetPost0DDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetPost0DDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetPost0DDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
		Init_NOD();

	}
	else
	{
		GetPost0DDlg()->SetActiveWindow();
		GetPost0DDlg()->m_ObjType = m_ObjType;
	}
	////////////////
	switch(m_ObjType)
	{
		case BALLJOINT:
			//////////////////////////////
			UpdateDlg_FALSE_BALLJOINT();
			////
			break;
			////
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if CreODlg Open
	if(GetPost0DDlg()->m_hWnd)
	{
/*
		CStatic* pCtl;
		pCtl = (CStatic*)(GetPost1DDlg()->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW12)
			pCtl->SetWindowText("Z");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW23)
			pCtl->SetWindowText("X");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEW31)
			pCtl->SetWindowText("Y");
		else
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_CREOP,IDOK);
			return 0L;
		}
*/

	}

	return 0L;
}
	 
long CNodPost::GoodByePost_NOD(UINT wParam, long lParam)
{
	
	GetPost0DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodPost::CancelPost_NOD(UINT wParam, long lParam)
{
	
	GetPost0DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodPost::UpdatePost_NOD(UINT wParam, long lParam)
{

	GetPost0DDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	UpdateDlg_TRUE_NOD();
	////////////////
	switch(m_ObjType)
	{
		case BALLJOINT:

			//////////////////////////////
			UpdateDlg_FALSE_BALLJOINT();
			////
			break;
		default:
			break;
	}
	//////////
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CNodPost::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString str,strCur;
	UINT ID;
	///////////////////////////////////
	if(IGenID != NODE)
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	//////////////////////////////////////////// PostID
	UINT PostID = pWnd->GetCurrentPostID();
	//////////////////////////////////////////// TaskID
	strCur = "Ready for ";
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case GOP_POST:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "POST";
			pWnd->SetstrOperID(str);
			/////////////////////////////
			switch(IGenID)
			{
				/////////
				case NODE:
					str = "NODE";
					pWnd->SetstrIGenID(str);
					///////////////////////////////////// .
					switch(CntlID)
					{
						//////////////////////////////////////// Elements:0D
						case EDIM_0:

							switch(PostID)
							{
								case INODE:			str = "ILLEGAL@Selection";			ID = UNONE;
									strCur += "A Node Can Not be Posted@as a Node";	break;
								case CNODE:			str = "ILLEGAL@Selection";			ID = UNONE;
									strCur += "A Control Node Can Not be Posted@as a Control Node";	break;
								case BALLJOINT:			str = "BALL@JOINT";				ID = BALLJOINT;
									strCur += "BALL JOINT Posting@CLICK ON a Node";	break;

								
								default:			str = "UNKNOWN";	ID = UNONE;		break;
							}
							break;
						default:
						///////////////////////////// String
						str = "DON'T KNOW";
						pWnd->SetstrOperID(str);
						///////////////////////////////////// 
						ID	= UNONE;
						strCur = "UNKNOWN Posting Option";
						pWnd->SetstrCurrID(strCur);
						break;
						//////////////////////////////////////////////////////////////
					}
					//////////////////////////////////////////// PostType
					m_ObjType = PostID;
					////////////////////////////////////////////////// 
					pWnd->SetstrCntlID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);

					return ID;
				//////////////////
				default:			str = "UNKNOWN";	ID = UNONE;		break;
			}
		}
	}
	return UNONE;
}

void CNodPost::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodPost:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" NodPost:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		
