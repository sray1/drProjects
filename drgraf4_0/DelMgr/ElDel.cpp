// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "glb_Objs.h"                    
#include "glb_Mous.h"                    
#include "glb_CuPS.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MDlgMgr.h"  
#include "EDlgMgr.h"  
#include "EDl2Mgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Glb_Elem.h"
#include "DrNode.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
//#include "DrPipe.h"
//#include "DrPlate.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h" 	
///////////////////// specials
#include "Def_Spec.h"
#include "Obj3DMnu.h"
#include "PatchMnu.h"
#include "DrPen.h"
#include "Layer.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "mouse.h"
#include "DListMgr.h"
/////////////////////
#include "MI_GangS.h" 
#include "MI_CProf.h" 
#include "MI_CSPN.h" 
#include "MI_PSPN.h" 
#include "MI_SSPN.h"
////////////////////// 
#include "Dlg_NodI.h"
#include "Dlg_LQCI.h"
#include "Dlg_CrcI.h"
#include "Dlg_Co4I.h"
#include "Dlg_CDlg.h"
//////////////////////
#include "elmouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MIN_NODES_CURVE		2        
#define MIN_CURVES_PATCH	3        
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
#define MAX_NODES_FE1D		2
#define MAX_NODES_FE2D		4
////////////////////////////////////
IMPLEMENT_SERIAL(CELMouse,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CELMouse::CELMouse()
{

	if(!m_ElSegList.IsEmpty())
		m_ElSegList.RemoveAll();
	if(!m_NodeList.IsEmpty())
		m_NodeList.RemoveAll();
	////////////////////////////
	m_pNodInDlg	= NULL;                                                                                
	m_pLQCInDlg	= NULL;                                                                                
	m_pCrcInDlg	= NULL;                                                                                
	m_pCr2InDlg	= NULL;                                                                                
	m_pCo4InDlg	= NULL;                                                                                
	////////////////////////////
	m_bAutoAcceptOn		= FALSE;
  	m_bDialogOn    		= FALSE;
  	m_bElementMode 		= FALSE;
	m_bDragOn      		= FALSE;
	m_bDragging	   		= FALSE;
	m_nNodeDone    		= 0;
	m_nCNodeDone   		= 0;
	//////////////////////// Set according to WIC: TOBEDONE
	m_AnchorNodeLOG.x 	= 0;
	m_AnchorNodeLOG.y 	= 0; 
	//////////////////////////////////////
	m_MouseLOG 			= m_AnchorNodeLOG;
	m_MouseOldLOG 		= m_MouseLOG;
	/////////////////////////////////////////// Node 
    m_pCurrentNode		= NULL;
    m_CurrentPipeID 	= "BLANK";
	///////////////////////////////////////////
	m_bRefreshOn		= FALSE;
 	/////////////////////////////////////////// Node 
    m_LastNodeNum		= 0;		// internal
	m_CurrentNodeID		= "N0";
	m_CurrentSupID		= "";
	m_CurrentLoadID		= "";
//	m_CurrentNodeIDOld	= "N0";
	m_CurrentNodeIDOld	= "";
	m_AnchorNodeID		= "N0";
	m_ThirdCoord		= 0.0;
 	/////////////////////////////////////////// Curve 
    m_LastCurveNum		= 0;		// internal
	m_CurrentCurveType	= CP_LINEAR;
	m_CurrentCurveID	= "C0";
	m_CurrentCurveIDOld	= "";
	m_bCurveDone		= TRUE;		// for dragging
	m_nCirMaxNode		= 3;		// = 3
	m_ElPerSeg			= 1;
	m_Ratio				= 1.0;
	m_bClosed			= FALSE;
	m_bAdvanceOn		= FALSE;
	/////////////////////////////////////////// Circle
	m_SegAngle			= 120.;
	m_bAutoSeg			= TRUE;
	m_dAngSpec			= 0.;
	m_bArc				= TRUE;
	m_dAng				= 90.;
	m_FromID			= "";
	m_ToID				= "";
 	/////////////////////////////////////////// Patch 
	m_nCurveDone		= 0;
    m_LastPatchNum		= 0;		// internal
	m_CurrentPatchType	= PP_LOFT4;
	m_CurrentPatSubType	= PS_QUADRILAT;
	m_CurrentPatchID	= "P0";
	m_bPatchDone		= TRUE;		// for dragging
	for(int i=0;i<4;i++)
	{
		m_PatCurveID[i]			= "";
		m_PatCurveLatch[i]	= CL_FORWARD;
		m_PatCurveElem[i]		= 0;
	}
	/////////////////////////////////////////// Solid

}

CELMouse::~CELMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pNodInDlg->m_hWnd)
		m_pNodInDlg->DestroyWindow();
	/////////////////////////////////
	if(m_pLQCInDlg->m_hWnd)
		m_pLQCInDlg->DestroyWindow();
	if(m_pCrcInDlg->m_hWnd)
		m_pCrcInDlg->DestroyWindow();
	if(m_pCr2InDlg->m_hWnd)
		m_pCr2InDlg->DestroyWindow();
	if(m_pCo4InDlg->m_hWnd)
		m_pCo4InDlg->DestroyWindow();
	///////////////////
	delete m_pNodInDlg;                                                                                
	delete m_pLQCInDlg; 
	delete m_pCrcInDlg; 
	delete m_pCr2InDlg; 
	delete m_pCo4InDlg; 
	///////////////////
}

void CELMouse::InitDlgIn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pNodInDlg		= new CDlg_NodI(pWnd);                                                                                
	m_pLQCInDlg		= new CDlg_LQCI(pWnd); 
	m_pCrcInDlg		= new CDlg_CrcI(pWnd); 
	m_pCr2InDlg		= new CDlg_Cr2I(pWnd); 
	m_pCo4InDlg		= new CDlg_Co4I(pWnd); 
}
	
void CELMouse::SizeRectDlgIn(CRect& BoxRect)
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

void CELMouse::PreLeftDown(CPoint point)
{ 

	LPOINT3 MouseWIC;
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////END TEMPORARY
	if(!m_nNodeDone || !m_bDragOn) 
	{
		///////////////////////////////////////
	    MouseWIC = GetMouseWIC();
	    SetMouseOldWIC(MouseWIC);
	    /////////////////////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);                 
	    SetMouseWIC(MouseWIC);
	 }
   
}

CDrObject* CELMouse::GetObjectFromID(CString& ID, int nObjType)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	int index = pObjectMgr->GetObjectIndexfromKey(nObjType,ID,1);
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(nObjType);
	return (CDrObject*)(pDListMgr->GetObject(index));
}

void CELMouse::SetMouseWICFromNode(CString& NID,LPOINT3* pMouseWIC)
{
	CDrNode* pDrNode = (CDrNode*)GetObjectFromID(NID, NODE);
	pMouseWIC->x = pDrNode->GetNodeCard()->x;								  	
	pMouseWIC->y = pDrNode->GetNodeCard()->y;								  	
	pMouseWIC->z = pDrNode->GetNodeCard()->z;								  	
}
	
int CELMouse::LeftDown_CURVE()
{
	
	///////////////////////////////////////////////////////// Disable BLine
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_DISABLED);
	/////////////////////////////////////////////////////////////////////////////
	if( m_nNodeDone >0)   // 2nd time Onward for LeftDown
	{
		//////////////////////////////////// reset mouse to AnchorNode
									  // in case intercepted
		CString NID = GetAnchorNodeID();
		LPOINT3 MouseWIC;
		SetMouseWICFromNode(NID,&MouseWIC);
		SetMouseOldWIC(GetMouseWIC());
		SetMouseWIC(MouseWIC);
		//////////////////////////////////// DragOn
		if(m_bDragOn)
		{   
			//////////////////////
			PostLeft();
			//////////////////////
			m_bDragging =TRUE; 
			m_pView->SetCapture(); 
/*
			///////////// Width/Height TOBEDONE at OnSize
			RECT Rect;
			Rect.left  = 0;
			Rect.top   = 0;
			Rect.right = m_nClientWidth;
			Rect.bottom= m_nClientHeight;
			ClientToScreen(&Rect);
			ClipCursor(&Rect);
*/
			return 0;
		}
		else
		{
			////////////////////////
			UpdateCDlg_FALSE();
			////////////////////////
		}
	}	             
	return 0;
}
	
int CELMouse::LeftDown_PATCH()
{
	return 0;
}
	
void CELMouse:: ElementLeftDown()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType; 
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		case NODE:
		case CNODE:
		////////////////////////////////////////////////// OBJ3D	
		case OBJ3D:
//					m_MI_Obj3D.LBDownInit_OInsert();					
			return;
		////////////////////////////////////////////////// CURVE	
		case C_CIRCLE:	
			m_bCurveDone = FALSE;
			if(m_bSingleSegOn == TRUE)
			{ 
				pBool->ToggleSingleSegOn();
				m_bSingleSegOn	= FALSE;
			}		
			m_CurrentCurveType = CP_CIRCLE;
			LeftDown_CURVE();
			return;

		case C_ELLIPSE:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_ELLIPSE;
			LeftDown_CURVE();
			return;

		case C_PARABOLA:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_PARABOLA;
			LeftDown_CURVE();
			return;

		case C_LINEAR:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_LINEAR;
			LeftDown_CURVE();
			return;

		case C_QUADRATIC:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_QUADRATIC;
			LeftDown_CURVE();
			return;

		case C_BSPLINE:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_BSPLINE;
			LeftDown_CURVE();
			return;

		case C_BEZIER:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_BEZIER;
			LeftDown_CURVE();
			return;

		case C_NURB:
			m_bCurveDone = FALSE;
			m_CurrentCurveType = CP_NURB;
			LeftDown_CURVE();
			return;
	
		////////////////////////////////////////////////// PATCH
		case P_COONS:
		case P_EXTRUDE:				// 
		case P_ROTATE: 
		case P_LOFT: 
		case P_DUCT: 
		case P_SWEEP: 

			LeftDown_PATCH();
			return;

		////////////////////////////////////////////////// SOLID
		case S_COONS:
		case S_EXTRUDE:				// 
		case S_ROTATE: 
		case S_LOFT: 
		case S_DUCT: 
		case S_SWEEP: 
			return;
/*
		////////////////////////////////////////////////// POST	
		case C_POST:				// CURVE
			///////		
			m_MI_Sol_I.LBDownInit_CPost();
			return;

  */
		case P_POST:				// PATCH 
			///////		
			m_MI_Pat_P.LBDownInit_PPost();
			return;
		
/*		 
		case S_POST:				// SOLID 
			///////		
			m_MI_Sol_I.LBDownInit_SPost();
			return;
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// CURVE
			///////		
			m_MI_Sol_I.LBDownInit_CEdit();
			return;
		
		 
		case P_EDIT:				// PATCH 
			///////		
			m_MI_Sol_I.LBDownInit_PEdit();
			return;
		
		 
		case S_EDIT:				// SOLID 
			///////		
			m_MI_Sol_I.LBDownInit_SEdit();
			return;
		
		////////////////////////////////////////////////// MOVE	
		case C_MOVE:				// CURVE
			///////		
			m_MI_Sol_I.LBDownInit_CMove();
			return;
		
		 
		case P_MOVE:				// PATCH 
			///////		
			m_MI_Sol_I.LBDownInit_PMove();
			return;
		
		 
		case S_MOVE:				// SOLID 
			///////		
			m_MI_Sol_I.LBDownInit_SMove();
			return;
		
*/		
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
void CELMouse::PreLeftUp(CPoint point)
{
	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////////////////////////
    LPOINT3 MouseWIC = GetMouseWIC();
    SetMouseOldWIC(MouseWIC);
	//////////////
    LPOINT Lpoint;
    m_pdc->DPtoLP(&point);
    Lpoint.x = (long)point.x;
    Lpoint.y = (long)point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    LOGtoWIC(&MouseWIC,&Lpoint);    // Log/Scaled             
    SetMouseWIC(MouseWIC);
}

int CELMouse::ShowNode(CString* pID,BOOL bnid_c,int nHowMany)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
//	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////
/*
	if(m_bDialogOn)
	{
		CEDl2Mgr* pEDlgMgr;
		int i;
		/////////////////////////////////////////////////////////////// Using EDlgMgr 
		LPOINT3 MouseWIC = GetMouseWIC();
		pID = &m_CurrentNodeID;
		if (pEDlgMgr->DoModal_Node(bnid_c,m_nView,&MouseWIC,pID,nHowMany) == IDCANCEL)
			return -1;
		////////////////////////////////////////////////////////// pNode
	   	if(( i= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1)) <0)
   		{
			AfxMessageBox("ERROR:\nCELMouse::ShowNode\nNo Node Index\nInternal Problem");
   			return -1;
   		}	
 		CDListMgr* pDListMgr = pObjectMgr->GetObjectList(NODE);
		m_pCurrentNode = (CDrNode*)pDListMgr->GetObject(i);
	}
	else
	{
*/
	/////////////////////////////////////////////////////////////// Using GangS
	WORLD wPt;
	LPOINT3 MouseWIC = GetMouseWIC();
	///////////////////////////
	WICtoWOR(&MouseWIC,&wPt);
	///////////////////////////
	int nNodeIndex,nLabelIndex;
	CMI_GangS GangS;
	m_pCurrentNode = GangS.CreateNode(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,FALSE,
										nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	////////////////////////////////////////////////////////////////////// Show
//	int nActiveIndex = pObjectMgr->GetActiveObjectIndex();		    // Get Active Index									
	pObjectMgr->SetActiveObjectIndex(nNodeIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,NODE);
	//////////////////////////////////////////////////////////
//	m_pCurrentLabel = GangS.CreateNodeLabel(m_pCurrentNode, nActiveIndex);// 
	pObjectMgr->SetActiveObjectIndex(nLabelIndex);		    // set Active Index for Label									
	pObjectMgr->SetActiveObjectType(LABEL);					// set Active ObjectType									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nLabelIndex,LABEL);
	/////////////////////////////////////////////////////////////////// restore ObjectType/Index
//	pObjectMgr->SetActiveObjectType(nTypeOld);             
//	pObjectMgr->SetActiveObjectIndex(nActiveIndexOld);		// set Active Index for Calling Object									
	///////////////////////////////
	return 0;
}	 

int CELMouse::ShowCurve(CString* pID,BOOL bFinal)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
// 	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////// Add to DataBase, if not Existing
	///////////////////////////////////////// delete & Add
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		m_pCurrentCurve = (CDrCurve*)NULL;
	}
	m_pCurrentCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,CURVE));
	m_pCurrentCurve->SetShow(FALSE);	// not quite ready
	///////////////////////////////////////// Get rid of Old CNodes & INodes
	if(!(m_pCurrentCurve->GetCNodeList()->IsEmpty())  )
		m_pCurrentCurve->GetCNodeList()->RemoveAll();
	if(!(m_pCurrentCurve->GetINodeList()->IsEmpty())  )
		m_pCurrentCurve->GetINodeList()->RemoveAll();
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	m_pCurrentCurve->GetINodeList()->AddTail(&m_NodeList);	// copy
	///////////////////////////////////////////////////////
	m_pCurrentCurve->SetRatio_S(m_Ratio);
	m_pCurrentCurve->SetClosed_S(m_bClosed);
	/////////////////////////////////////////////////////////////// Using GangS
	CMI_GangS GangS;
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_nType)
			{
				
				case CIRCLE_BY_ROT:

					m_pCurrentCurve = GangS.CreateCircleByRot(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_nType,m_dAng,m_FromID,m_ToID,m_SegAngle);

					break;
				
				case CIRCLE_BY_NO3:

					m_pCurrentCurve = GangS.CreateCircleBy3Node(
						*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
						&m_ElSegList,m_nType,m_SegAngle,m_dAngSpec,m_bArc);

					break;
				
				default:

					break;

			}
			break;
				
		default:

			m_pCurrentCurve = GangS.CreateCurve(*pID,m_pCurrentCurve,&m_NodeList,m_CurrentCurveType,
											&m_ElSegList,m_bAdvanceOn,bFinal);
	}
////////////////////////////////////////////////////////////////////// Debug
#ifdef _DEBUG 
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		int j;
		/////////////////////////
		j  = sprintf(buf,"CELMouse::ShowCurve\nAfter CreateCurve\nBefore UpdateViews:\n");
		j += sprintf(buf+j,"Nodes in the CNodeList:\n\t");
		//////////////////////////////
		pList = m_pCurrentCurve->GetCNodeList();
		////////////////////////////////////////
		for (POSITION posI = pList->GetHeadPosition( );posI !=NULL;)
		{
			////
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(posI);
			j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
		}
		sprintf( buf + j-2, ";");
		/////////////////////////	
		AfxMessageBox(*str);
		/////
		delete str;
*/
#endif
////////////////////////////////////////////////////////////////////// Debug End
	////////////////////////////////////////////////////////////////////// Show
	m_pCurrentCurve->SetDirty(TRUE);
	m_pCurrentCurve->SetShow(TRUE);	
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
	//////////////////////////////////////////////////////////////////// restore ObjectType/Index
//	pObjectMgr->SetActiveObjectType(nTypeOld);             
//	pObjectMgr->SetActiveObjectIndex(nActiveIndexOld);		// set Active Index for Calling Object									
	///////////////////////////////
	return 0;
}	 

void CELMouse::PostLeft()
{	
	/////////////////////////////// get New MouseWIndowCoord.
	LPOINT3 MouseWIC = GetMouseWIC();
	/////////////////////////////// Set MouseLOGoords.
	LPOINT L_AnchorNodeLOG;
	WICtoLOG(&MouseWIC,&L_AnchorNodeLOG);  // LOG/DEScaled LOG
	m_AnchorNodeLOG.x = (int) L_AnchorNodeLOG.x;
	m_AnchorNodeLOG.y = (int) L_AnchorNodeLOG.y;
	m_pdc->LPtoDP(&m_AnchorNodeLOG);
	//////////////////////////////
	m_MouseLOG    = m_AnchorNodeLOG;
	m_MouseOldLOG = m_MouseLOG;
	///////////////////////////// Set Cursor Position 
	POINT CurLoc = m_MouseLOG;
//	pWnd->ClientToScreen(&CurLoc);
	m_pView->ClientToScreen(&CurLoc);
	::SetCursorPos(CurLoc.x,CurLoc.y); 
	//////////////////////////////////
}

void CELMouse::OnEBoxLButtonDown(CClientDC* pdc,CView* pView,GENERATE gener,
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
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
	if(!m_bBLineOn && m_bCurveDone)			// Reset
		m_nNodeDone = 0;
		////////////////
/*
	if(m_bCurveDone)						// Reset
	{
		////////////////
		if(!m_ElSegList.IsEmpty())
			m_ElSegList.RemoveAll();
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
	}
*/
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CELMouse::UpdateNDlg_TRUE()
{
	//////////////////////////////////
	m_pNodInDlg->UpdateData(TRUE); // from screen
	////////////
	m_CurrentNodeID = m_pNodInDlg->m_NID;
	m_CurrentSupID	= m_pNodInDlg->m_SID;
	m_ThirdCoord	= m_pNodInDlg->m_dCoord;
	/////////////////////////////////////
}
			
void CELMouse::UpdateNDlg_FALSE()
{
	//////////////////////////////////
	m_pNodInDlg->m_NID		= m_CurrentNodeID;
	m_pNodInDlg->m_SID		= m_CurrentSupID;
	m_pNodInDlg->m_dCoord	= m_ThirdCoord;
	////////////
	m_pNodInDlg->UpdateData(FALSE); // to screen
	////////////////////////////
}
			
int CELMouse::LeftUp_NODE(BOOL bCNode)
{
	CString* pID;
	char buf[30];
	//////////////////////////////////
	pID = &m_CurrentNodeID; 
	if(ShowNode(pID,bCNode,0)<0)
	{
		AfxMessageBox("ERROR:\nCELMouse::LeftUp_Node\nShowNode Problem");
		return -1;
	}
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld = *pID;
	if(*pID == m_CurrentNodeID)
	{		
		m_LastNodeNum++;		// internal
		sprintf(buf,"%d",m_LastNodeNum);
		m_CurrentNodeID	= "N";
		m_CurrentNodeID	+= buf;
	}
	////////////////////////////
	return 0;
}

void CELMouse::UpdateCDlg_TRUE()
{
	//////////////////////////////////
	if
		(
			m_CurrentCurveType == CP_LINEAR	||	m_CurrentCurveType == CP_QUADRATIC	||
			m_CurrentCurveType == CP_BEZIER	||
			m_CurrentCurveType == CP_BSPLINE||	m_CurrentCurveType == CP_NURB
		)
	{
		m_pLQCInDlg->UpdateData(TRUE); // from screen
		//////////////////////////////
		m_CurrentCurveID	= m_pLQCInDlg->m_CID;
		m_CurrentNodeID		= m_pLQCInDlg->m_NID;
		m_CurrentSupID		= m_pLQCInDlg->m_SID;
		m_ElPerSeg			= m_pLQCInDlg->m_nElperSeg;
		m_Ratio				= m_pLQCInDlg->m_dRatio;
		m_bClosed			= m_pLQCInDlg->m_bClosed;
		m_bAdvanceOn		= m_pLQCInDlg->m_bAdvanceOn;
		////////////////////////////////////////////////
		if(m_bClosed)
			m_bAdvanceOn = FALSE;
		/////////////////////////
	}
	else
	if
		(
			m_CurrentCurveType == CP_CIRCLE	
		)
	{
		if(m_nType == CIRCLE_BY_NO3)
		{
			m_pCrcInDlg->UpdateData(TRUE); // from screen
			//////////////////////////////
			m_CurrentCurveID	= m_pCrcInDlg->m_CurveID;
			m_CurrentNodeID		= m_pCrcInDlg->m_NID;
			m_ElPerSeg			= m_pCrcInDlg->m_nMesh;
			m_Ratio				= m_pCrcInDlg->m_Ratio;
			m_bClosed			= m_pCrcInDlg->m_bClosed;
			m_SegAngle			= m_pCrcInDlg->m_SegAngle;
			m_bAutoSeg			= m_pCrcInDlg->m_bAutoSeg;
			m_dAngSpec			= m_pCrcInDlg->m_dAngSpec;
			m_bArc				= m_pCrcInDlg->m_bArc;
		}
		else
		if(m_nType == CIRCLE_BY_ROT)
		{
			m_pCr2InDlg->UpdateData(TRUE); // from screen
			//////////////////////////////
			m_CurrentCurveID	= m_pCr2InDlg->m_CurveID;
			m_ElPerSeg			= m_pCr2InDlg->m_nMesh;
			m_Ratio				= m_pCr2InDlg->m_Ratio;
			m_dAng				= m_pCr2InDlg->m_dAng;
			m_FromID			= m_pCr2InDlg->m_FromID;
			m_ToID				= m_pCr2InDlg->m_ToID;
			m_CurrentNodeID		= m_pCr2InDlg->m_NodeID;
			m_SegAngle			= m_pCr2InDlg->m_SegAngle;
			m_bAutoSeg			= m_pCr2InDlg->m_bAutoSeg;
		}
	}
}			

void CELMouse::UpdateCDlg_FALSE()
{
	//////////////////////////////////
	if
		(
			m_CurrentCurveType == CP_LINEAR		||	m_CurrentCurveType == CP_QUADRATIC	||
			m_CurrentCurveType == CP_BEZIER		||
			m_CurrentCurveType == CP_BSPLINE	||	m_CurrentCurveType == CP_NURB
		)
	{
		m_pLQCInDlg->m_CID			= m_CurrentCurveID;
		m_pLQCInDlg->m_NID			= m_CurrentNodeID;
		m_pLQCInDlg->m_SID			= m_CurrentSupID;
		m_pLQCInDlg->m_nElperSeg	= m_ElPerSeg;
		m_pLQCInDlg->m_dRatio		= m_Ratio;
		m_pLQCInDlg->m_bClosed		= m_bClosed;
		m_pLQCInDlg->m_bAdvanceOn	= m_bAdvanceOn;
		//////////////////////////////////////
		if(m_nNodeDone>=1)
			m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		if(m_CurrentCurveType == CP_LINEAR)
			m_pLQCInDlg->GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
		if(m_CurrentCurveType == CP_LINEAR || m_bClosed == TRUE)
			m_pLQCInDlg->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
		//////////////////////////////
		m_pLQCInDlg->UpdateData(FALSE); // To screen
	}
	else
	if
		(
			m_CurrentCurveType == CP_CIRCLE	
		)
	{
		if(m_nType == CIRCLE_BY_NO3)
		{
			m_pCrcInDlg->m_CurveID		= m_CurrentCurveID;
			m_pCrcInDlg->m_NID			= m_CurrentNodeID;
			m_pCrcInDlg->m_nMesh		= m_ElPerSeg;
			m_pCrcInDlg->m_Ratio		= m_Ratio;
			m_pCrcInDlg->m_bClosed		= m_bClosed;
			m_pCrcInDlg->m_SegAngle		= m_SegAngle;
			m_pCrcInDlg->m_bAutoSeg		= m_bAutoSeg;
			m_pCrcInDlg->m_dAngSpec		= m_dAngSpec;
			m_pCrcInDlg->m_bArc			= m_bArc;
			//////////////////////////////////////
			if(m_nNodeDone>=1)
				m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////////////////////////////
			m_pCrcInDlg->UpdateData(FALSE); // To screen
		}
		else
		if(m_nType == CIRCLE_BY_ROT)
		{
			m_pCr2InDlg->m_CurveID		= m_CurrentCurveID;
			m_pCr2InDlg->m_nMesh		= m_ElPerSeg;
			m_pCr2InDlg->m_Ratio		= m_Ratio;
			m_pCr2InDlg->m_dAng			= m_dAng;
			m_pCr2InDlg->m_FromID		= m_FromID;
			m_pCr2InDlg->m_ToID			= m_ToID;
			m_pCr2InDlg->m_NodeID		= m_CurrentNodeID;
			m_pCr2InDlg->m_SegAngle		= m_SegAngle;
			m_pCr2InDlg->m_bAutoSeg		= m_bAutoSeg;
			
			
			//////////////////////////////////////
			if(m_nNodeDone>=1)
				m_pCr2InDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////////////////////////////
			m_pCr2InDlg->UpdateData(FALSE); // To screen
		}
	}
}			

int CELMouse::LeftUp_CURVE(CPoint point)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString* pID;
	CString ID;
	CDrNode* pDrNode;
	int nActiveIndex;
	///////////////////////////////////////////// See if any Existing Node Hit
	int index = IsObjectHit(NODE,point,0);
	if(index>=0)
	{
		pDrNode				= (CDrNode*)pDListMgr->GetObject(index);
		ID					= pDrNode->GetObjectID();
		/////////////////////////////////////////
		pList = pObjectMgr->GetObjectList(NODE);
		nActiveIndex = pList->GetObjectIndex(NODE, ID);;
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Index									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		//////////////////////////////////////////////////////////////// MultipleSearch
		int startIndex = index+1;
		/////////////////////////
		if(!m_bAutoAcceptOn)
		{
			for(;;)
			{
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				int j;
				/////////////////////////////// Coords
				WORLD wLoc = *(pDrNode->GetLocalPos());
				WORtoWOP(&wLoc,&wLoc);	// to Physical
				//////////////////////////////
				j = sprintf(buf,
					"Node %s with Coordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f ",
					ID,wLoc.x,wLoc.y,wLoc.z);
				j += sprintf(buf+j,
					"\nCancel: Find Next Matching Node");
				j += sprintf(buf+j,
					"\nOK:     Accept This Node");
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION);
				/////////////
				if(nResult == IDOK)
				{
					delete str;
					break;
				}
				else
				{
					//////////////////////////////////////////////////////// Retry
					index = IsObjectHit(NODE,point,startIndex);
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
						m_nNodeDone--;
						delete str;
						return 0;
					}
					/////////
				}
			}
		}
		CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
		m_pCurrentNode			= (CDrNode*)pDListMgr->GetObject(index);
//		m_CurrentNodeID			= m_pCurrentNode->GetObjectID();
		m_CurrentNodeIDOld		= m_pCurrentNode->GetObjectID();
		m_AnchorNodeID			= m_CurrentNodeIDOld;
		/////////////////////////////////////////////
	}
	else
	{
		///////////////////
		LeftUp_NODE(FALSE);
		///////////////////
	}
	//////////////////////////////////
	m_NodeList.InsertObject(m_pCurrentNode);
	//////////////////////////////////////////////////// Show Curve
	if(m_CurrentCurveType == CP_CIRCLE)
	{
		if(
			(m_nType == CIRCLE_BY_NO3) && (m_nNodeDone == 3) ||
			(m_nType == CIRCLE_BY_ROT) && (m_nNodeDone == 1) 
		)
		{
			pID = &m_CurrentCurveID;
			m_ElSegList.AddTail(m_ElPerSeg);
			//////////////////////////
			if(ShowCurve(pID,FALSE)<0)		// FALSE = Not Final
			{
				AfxMessageBox("ERROR:\nCELMouse::LeftUp_CURVE\nShowCurve Problem");
				return -1;
			}
		}
	}
	else
	if(m_nNodeDone >1)
	{		
		pID = &m_CurrentCurveID;
		m_ElSegList.AddTail(m_ElPerSeg);
		//////////////////////////
		if(ShowCurve(pID,FALSE)<0)		// FALSE = Not Final
		{
			AfxMessageBox("ERROR:\nCELMouse::LeftUp_CURVE\nShowCurve Problem");
			return -1;
		}
	}
	/////////////////////////////////////// Set Anchor
	SetAnchorNodeID(m_CurrentNodeIDOld );
	//////////////////////////////////////
	return 0;
}

void CELMouse::UpdatePDlg_TRUE()
{
	//////////////////////////////////
	CString	sLat[4];
	/////////////////
	m_pCo4InDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_CurrentPatchID	= GetCo4InDlg()->m_PatchID;
	m_PatCurveID[0]		= GetCo4InDlg()->m_CID_1;
	m_PatCurveID[1]		= GetCo4InDlg()->m_CID_2;
	m_PatCurveID[2]		= GetCo4InDlg()->m_CID_3;
	m_PatCurveID[3]		= GetCo4InDlg()->m_CID_4;
	m_PatCurveElem[0]	= GetCo4InDlg()->m_TotEl_1;
	m_PatCurveElem[1]	= GetCo4InDlg()->m_TotEl_2;
	m_PatCurveElem[2]	= GetCo4InDlg()->m_TotEl_3;
	sLat[0]				= GetCo4InDlg()->m_Orient_1;
	sLat[1]				= GetCo4InDlg()->m_Orient_2;
	sLat[2]				= GetCo4InDlg()->m_Orient_3;
	sLat[3]				= GetCo4InDlg()->m_Orient_4;
	//////////////////////////////////////
	int i;
	for(i=0;i<4;i++)
	{
		m_PatCurveLatch[i] = CL_FORWARD;
		/////////////////////////
		if(sLat[i] == "BACKWARD")
			m_PatCurveLatch[i] = CL_BACKWARD;
	}
	//////////////////////////////////////
	if(m_nCurveDone>=1)
		m_pCo4InDlg->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
	//////////////////////////////
}			

void CELMouse::UpdatePDlg_FALSE()
{
	//////////////////////////////////
	CString	sLat[4];
	/////////////////
	GetCo4InDlg()->m_PatchID	= m_CurrentPatchID;
	GetCo4InDlg()->m_CID_1		= m_PatCurveID[0];
	GetCo4InDlg()->m_CID_2		= m_PatCurveID[1];
	GetCo4InDlg()->m_CID_3		= m_PatCurveID[2];
	GetCo4InDlg()->m_CID_4		= m_PatCurveID[3];
	GetCo4InDlg()->m_TotEl_1	= m_PatCurveElem[0];
	GetCo4InDlg()->m_TotEl_2	= m_PatCurveElem[1];
	GetCo4InDlg()->m_TotEl_3	= m_PatCurveElem[2];
	GetCo4InDlg()->m_TotEl_4	= m_PatCurveElem[3];
	//////////////////////////////////////
	int i;
	for(i=0;i<4;i++)
	{
		sLat[i] = "FORWARD";
		/////////////////////////
		if(m_PatCurveLatch[i] == CL_BACKWARD)
			sLat[i] = "BACKWARD";
	}
	GetCo4InDlg()->m_Orient_1 = sLat[0];
	GetCo4InDlg()->m_Orient_2 = sLat[1];
	GetCo4InDlg()->m_Orient_3 = sLat[2];
	GetCo4InDlg()->m_Orient_4 = sLat[3];
	////////////////////////////////////////////////
	m_pCo4InDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CELMouse::LeftUp_Coons(POINT point)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	CDrCurve* pDrCurve;
//	COLORREF OldColor,NewColor;
//	UINT nWidth;
//	UINT nStyle;	
	int nActiveIndex;
	CDListMgr* pList;
	///////////////////////////////////////////// See if any Existing Curve Hit
	int index = IsObjectHit(CURVE,point,0);
	if(index>=0)
	{
		pDrCurve				= (CDrCurve*)pDListMgr->GetObject(index);
		ID						= pDrCurve->GetObjectID();
		///////////////////////////////////////// Check if matches previous curves,INADMISSIBLE
		if(m_nCurveDone>1)
		{
			for(int i=0;i<m_nCurveDone;i++)
			{
				if(m_PatCurveID[i] == ID)
				{
					AfxMessageBox("Degenerate Patch:\nSame Curve More than Once!");
					m_nCurveDone--;
					return -1;
				}
			}
		}
/*
		////////////////////////////////////////// Color Change Curve
		pDrCurve->GetPenInfo(nWidth,OldColor,nStyle);
		/////////////////////////////
		NewColor = pDrPen->GetColor(); 
		pDrCurve->SetPenInfo(1,NewColor,PS_DASH);
*/
		/////////////////////////////////////////
		pList = pObjectMgr->GetObjectList(CURVE);
		nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
		pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
		/////////////////////
	}
	else
	{
		m_nCurveDone--;
		return 0;
	}
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		for(;;)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			/////////////////////////////// total elems
			int nIn		= pDrCurve->GetMaxINodes_S();
			int nElems	= pDrCurve->GetMaxOutPts_S();
			pList		= pDrCurve->GetINodeList();
			//////////////////////////////
			j = sprintf(buf,
				"Curve %s contains:\n\t%d Interpolation Nodes\n\t%d Elements",
				ID,nIn,nElems);
			j += sprintf(buf+j,"Nodes:\n");
			//////////////////////////////
			for (POSITION posI = pList->GetHeadPosition( );posI !=NULL;)
			{
				////
				CDrNode* pNode = (CDrNode*)pList->GetNextObject(posI);
				j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
			}
			sprintf( buf + j-2, ";");
			/////////////////////////	
			j += sprintf(buf+j,"\n\nCancel: Find Next Matching Curve\n");
			j += sprintf(buf+j,    "OK:     Accept This Curve");
			////////////////////////////
			int nResult = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION);
			/////////////
			if(nResult == IDOK)
			{
				delete str;
				break;
			}
			else
			{
				//////////////////////////////////////////////////////// restore Old Color/OldCurve
//				pDrCurve->SetPenInfo(nWidth,OldColor,nStyle);
				////////////////////////////////
				index = IsObjectHit(CURVE,point,startIndex);
				if(index>=0)
				{
					pDrCurve				= (CDrCurve*)pDListMgr->GetObject(index);
					ID						= pDrCurve->GetObjectID();
					///////////////////////////////////////// Check if matches previous curves,INADMISSIBLE
					if(m_nCurveDone>1)
					{
						for(int i=0;i<m_nCurveDone;i++)
						{
							if(m_PatCurveID[i] == ID)
							{
								AfxMessageBox("Degenerate Patch:\nSame Curve More than Once!");
								////////////////
								m_nCurveDone--;
								delete str;
								return 0;
							}
						}
					}
/*
					////////////////////////////////////////// Color Change Curve
					pDrCurve->GetPenInfo(nWidth,OldColor,nStyle);
					/////////////////////////////
					NewColor = pDrPen->GetColor(); 
					pDrCurve->SetPenInfo(1,NewColor,PS_DASH); //cpen
*/
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(CURVE);
					nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
					////////////////////////////////////////
					pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
					ID			= pDrCurve->GetObjectID();
					startIndex  = index+1;
					/////////////////////
				}
				else
				{
					////////////////
					m_nCurveDone--;
					delete str;
					return 0;
				}
				/////////
			}
		}
	}
	//////////////////////////////////////////////////////// Compatibility Check
	BOOL bClosed;
	////////////////////////////////////// All must be OPEN
	bClosed		= pDrCurve->IsClosed_S();
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",ID);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		////////////////
		m_nCurveDone--;
		//////////////////// 
		return 0;
	}
	///////////////////////////////////////////////////// find Latch
	if(	m_nCurveDone == 1)
	{
		///////////////////////////////////////////////// progress
		m_pCurPatCurve					= pDrCurve;
		m_pOldPatCurve					= m_pCurPatCurve;
		m_PatCurveID[m_nCurveDone-1]	= ID;
		m_PatCurveElem[m_nCurveDone-1]	= pDrCurve->GetMaxOutPts_S() - 1;
		m_PatCurveLatch[m_nCurveDone-1]	= CL_FORWARD;
		/////////////////////////////////////////////////
		return 0;
	}
	///////////////////////////////////////////////////////////////// Check CONNECTIVITY
	C3DMath Math3D;
	///////////////
	CDListMgr*	pINList;
	WORLD		LocalPosOld,LocalPosB,LocalPosE,LocalPos;
	CDrNode*	pNode_Old;
	CDrNode*	pNode_Beg;
	CDrNode*	pNode_End;
	CURVELATCH	OldLat,NewLat;
	//////////////////////////////////////////////////////// Curve Old
 	pINList		= m_pOldPatCurve->GetINodeList();
	/////////////
	OldLat		= m_PatCurveLatch[m_nCurveDone-2];
	pNode_Old	= (CDrNode*)pINList->GetTail();
	if(OldLat == CL_BACKWARD) 
		pNode_Old	= (CDrNode*)pINList->GetHead();
	////////////////////////////
	LocalPosOld = *(pNode_Old->GetLocalPos());
	//////////////////////////////////////////////////////// Curve New
 	pINList		= pDrCurve->GetINodeList(); 
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	/////////////
	LocalPosB	= *(pNode_Beg->GetLocalPos());
	LocalPosE	= *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Do Check
	BOOL bDisJoint = TRUE;
	double dLen;
	//////////////////////
	Math3D.Sub3DPts(&LocalPosOld,&LocalPosB,&LocalPos);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosOld)) * fabs(Math3D.Len3DPts(&LocalPosB)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPos)/dLen) < .01)	// 1%
	{
		bDisJoint	= FALSE;
		NewLat		= CL_FORWARD;
	}
	else
	{
		//////////////////////////////////////// try with Other End
		Math3D.Sub3DPts(&LocalPosOld,&LocalPosE,&LocalPos);
		dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosOld)) * fabs(Math3D.Len3DPts(&LocalPosE)) ); 
		if( fabs(Math3D.Len3DPts(&LocalPos)/dLen) < .01)	// 1%
		{
			bDisJoint	= FALSE;
			NewLat		= CL_BACKWARD;
		}
	}
	/////////////
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,
			"ComPatibility Problem!\nCurve_%d(End) & Curve_%d(Begin) DisJoint!\nCURVES MUST MEET",
			m_nCurveDone-1,m_nCurveDone);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		////////////////
		m_nCurveDone--;
		///////
		return 0;
	}
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurPatCurve					= pDrCurve;
	m_pOldPatCurve					= m_pCurPatCurve;
	m_PatCurveID[m_nCurveDone-1]	= ID;
	m_PatCurveElem[m_nCurveDone-1]	= pDrCurve->GetMaxOutPts_S() - 1;
	m_PatCurveLatch[m_nCurveDone-1]	= NewLat;
	/////////////////////////////////////////////////
	return 0;
}

void CELMouse::ElementLeftUp(CPoint point)
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
		
		case NODE:
				
			m_nNodeDone = 0;
			////////////////
			UpdateNDlg_TRUE();
			LeftUp_NODE(FALSE);		// FALSE = Not CNODE
			UpdateNDlg_FALSE();
			///////
			return;

				
		case CNODE:				

			m_nCNodeDone = 0;
			////////////////
			UpdateNDlg_TRUE();
			LeftUp_NODE(TRUE);		// TRUE = CNODE;
			UpdateNDlg_FALSE();
			///////
			return;


		case FE1D:
/*										
					if(!ShowNode(pID,FALSE,1))
					{
						m_nNodeDone++;
						SetCurrentNodeID(*pID);
					}
					else                             // cancelled
*/
						return;	
					////////////////////////////////
					if(m_nNodeDone == MAX_NODES_FE1D)
					{         
						m_nNodeDone = 1;   // Reset  
						///////////////////////////// Put NodePair in PipeList/draw 
						CString nid[2];
						nid[0] = GetAnchorNodeID();
						nid[1] = GetCurrentNodeID(); 
//						CDrFE1D Pipe;
						if(PutEndIdsInPipeList(nid,2)<0)
						{
							m_nNodeDone--;
							return;
						}
						//////////////////////////////////////
						if(m_bDialogOn)             // Show FE1D PropDlg/draw 
						{
							////////////////////
							CEDlgMgr*	pEDlgMgr;
							/////////////////////////////////////////
							if (pEDlgMgr->DoModal_Pipe(0) == IDCANCEL)
								return;
							/////////////////////////////////////////	
						}
					}
					/////////////////////////////////////// Set Anchor
					SetAnchorNodeID(m_CurrentNodeIDOld );
					/////////////////////////////////////
					return;
		///////////////////////////////////////////////////// CURVEs Insert
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_PARABOLA:
		case C_LINEAR:
		case C_QUADRATIC:
		case C_BSPLINE:
		case C_BEZIER:
		case C_NURB:

			m_nNodeDone++;
			////////////////
			UpdateCDlg_TRUE();
			////////////////////
			LeftUp_CURVE(point);	
			////////////////////
//			UpdateCDlg_FALSE();
			//////////////////////////////////// Circle 
			if(m_nActiveTool == C_CIRCLE)
			{
				if(
					((m_nType == CIRCLE_BY_ROT) && (m_nNodeDone == 1)) || 
					((m_nType == CIRCLE_BY_NO3) && (m_nNodeDone == 3)) 
				)	
				bRightOn = TRUE;
			}
			//////////////////////////////////// If Single Line, Get RightButton Done
			else
			{
				if(m_nNodeDone>=2 && m_bSingleSegOn)
					bRightOn = TRUE;
			}
			////////////////////////
			if(bRightOn)
			{
				////////////////////
//				UpdateCDlg_TRUE();
				RightUp_CURVE();
//				UpdateCDlg_FALSE();
				////////////////////
			}
			UpdateCDlg_FALSE();
			///////
			return;
	
		///////////////////////////////////////////////////// Patches Insert
		case P_EXTRUDE:
		case P_ROTATE: 
		case P_LOFT: 
		case P_DUCT: 
		case P_SWEEP:
				return;

		case P_COONS:		// 
			

			m_nCurveDone++;
			////////////////
			if(m_nCurveDone > 4)
			{
				AfxMessageBox("Maximum of 4 Curves Allowed\n Please Use Right Button");
				m_nCurveDone--;
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			LeftUp_Coons(point);	
			UpdatePDlg_FALSE();
			///////
			return;
		///////////////////////////////////////////////////// SOLIDes Insert
		case S_COONS:
		case S_EXTRUDE:
		case S_ROTATE: 
		case S_LOFT: 
		case S_DUCT: 
		case S_SWEEP: 
			return;
		////////////////////////////////////////////////// POST
/*
		case C_POST:				// CURVE
			///////		
			m_MI_Solid.LBUpCurvePost();
			return;
*/		
		 
		case P_POST:				// PATCH 
			///////		
			m_MI_Pat_P.LBUpPatchPost();
			return;
/*		
		
		 
		case S_POST:				// SOLID 
			///////		
			m_MI_Solid.LBUpSolidPost();
			return;
		
		////////////////////////////////////////////////// EDIT	
		case C_EDIT:				// CURVE
			///////		
			m_MI_Solid.LBUpCurveEdit();
			return;
		
		 
		case P_EDIT:				// PATCH 
			///////		
			m_MI_Solid.LBUpPatchEdit();
			return;
		
		
		 
		case S_EDIT:				// SOLID 
			///////		
			m_MI_Solid.LBUpSolidEdit();
			return;
		
		////////////////////////////////////////////////// MOVE	
		case C_MOVE:				// CURVE
			///////		
			m_MI_Solid.LBUpCurveMove();
			return;
		
		 
		case P_MOVE:				// PATCH 
			///////		
			m_MI_Solid.LBUpPatchMove();
			return;
		
		
		 
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

void CELMouse::OnEBoxMouseMove(CClientDC* pdc,CView* pView,GENERATE gener,
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
   	//////////////////////////////      ***** START FROM HERE *****
   	CPen    Pen;
	CPen*   PtrOldPen;
	//////////////////////////////
	m_pdc->SetBkMode(TRANSPARENT);
	//////////////////////////////	
	// Create Black Pen 2 Pixel wide;
	int two = 2;
	COLORREF crColor = 0x000000;  
	Pen.CreatePen ((int)PS_SOLID,two,crColor);
	PtrOldPen = m_pdc->SelectObject(&Pen);
	///////////////////////////
	m_MouseLOG = point;              // Device
	POINT MouseLOC;
	/////////////////////////	
	m_pdc->SetROP2 (R2_NOT); 
	
	MouseLOC = m_AnchorNodeLOG;      // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->MoveTo (MouseLOC);

	MouseLOC = m_MouseOldLOG;        // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->LineTo (MouseLOC);
	////////////////////////	  
//	m_pdc->SetROP2 (R2_COPYPEN);

	MouseLOC = m_AnchorNodeLOG;      // Device
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->MoveTo (MouseLOC);

	MouseLOC = m_MouseLOG;
	m_pdc->DPtoLP(&MouseLOC);
	m_pdc->LineTo (MouseLOC);

	m_MouseOldLOG = m_MouseLOG;
	///////////////////////////
   	m_pdc->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
	//////////////////////////////////////
    LPOINT3 MouseWIC = GetMouseWIC();
    SetMouseOldWIC(MouseWIC);
   	///////////////////////
   	LOGtoWIC(&MouseWIC,&LpLOG); //LOG/Scaled WIC
   	////////////////////                 
    SetMouseWIC(MouseWIC);
    ///////////////////////////
//  pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
	pMouseMgr->SetStatusMouseWIC(MouseWIC);
	//////////////////////////////////////////////    
}

void CELMouse::OnEBoxLButtonUp(CClientDC* pdc,CView* pView,GENERATE gener,
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
    if(m_bDragging)  // not currently dragging
    {
		m_bDragging = FALSE; 
		::ReleaseCapture();
		//	ClipCursor(NULL);				TOBEDONE 
	}	
	///////////////////////////////////////////////////////// 
	PreLeftUp(point);
    /////////////////////////////  ELement Dialog On/Off Check
    POINT Logpoint;
    m_pdc->DPtoLP(&point);
    Logpoint.x = point.x;
    Logpoint.y = point.y;
    m_pdc->LPtoDP(&point);							
    ////////////////////
    if(m_Gener == FORWARD)
		ElementLeftUp(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CELMouse::OnEBoxRButtonDown(CClientDC* pdc,CView* pView,GENERATE gener,
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
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
	/////////////////////////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////
//	CEDlgMgr* pEDlgMgr;
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
/*		
		case INSERT:
		
			switch(m_nActiveObject)
			{
				case FE1D:
					break;
				
		    }
            break;
*/			
		////////////////////////////////////////////////// Curve	
		case C_CIRCLE:
						
			
			if(m_MI_Sol_I.RBDown_CInsert(CP_CIRCLE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_ELLIPSE:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_ELLIPSE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_PARABOLA:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_PARABOLA,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_LINEAR:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_LINEAR,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_QUADRATIC:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_QUADRATIC,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_BEZIER:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_BEZIER,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_BSPLINE:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_BSPLINE,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case C_NURB:
						
			if(m_MI_Sol_I.RBDown_CInsert(CP_NURB,m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

int CELMouse::RightUp_CURVE()
{
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	////////////////////////////////////////////////////////////////// 
	CString* pID;
//	char buf[30];
	int nAnswer = IDOK;
	//////////////////////////////////////////////////// Acceptance Not Automatic
	pID			= &m_CurrentCurveID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////////////////////////////////////
	switch(m_CurrentCurveType)
	{
		case CP_CIRCLE:

			switch(m_nType)
			{
				
				case CIRCLE_BY_ROT:

					if(m_nNodeDone != 1)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Circle",m_nNodeDone);
						j += sprintf(buf+j,"Exactly 1 Node Needed\n");
						j += sprintf(buf+j,"Do You want to Continue to Get the Node ?");
						/////////////////////////	
						nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
					}
					break;
				
				case CIRCLE_BY_NO3:

					if(m_nNodeDone != 3)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Circle",m_nNodeDone);
						j += sprintf(buf+j,"Exactly 3 Node Needed\n");
						j += sprintf(buf+j,"Do You want to Continue to Get More Node(s) ?");
						/////////////////////////	
						nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
					}
					break;
				
				default:

					break;

			}
			break;
				
		default:

			if(m_nNodeDone<2)
			{
				////////////////////
				j = sprintf(buf,"ERROR:\n\t%d Nodes Input to generate the Curve",m_nNodeDone);
				j += sprintf(buf+j,"Minimum of 2 Nodes Needed\n");
				j += sprintf(buf+j,"Do You want to Continue to Get More Node(s) ?");
				/////////////////////////	
				nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			}
	}
	delete str;
	/////////////////////////
	if(nAnswer == IDNO)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Do You Want to Delete\nCurrent Curve to Start Allover");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			///////////////////////////////////////// delete
			pList = pObjectMgr->GetObjectList(CURVE);
			int nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
			//////////////////////////////////////////////////// Reset
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			/////////////////////////////////////// Reset
			m_nNodeDone	= 0;	// 
			m_bCurveDone	= TRUE;	// 
			//////////////////////////
			m_pCurrentCurve = NULL;
			m_nNodeDone		= 0;	// 
			m_bCurveDone	= TRUE;	//   
			m_ElSegList.RemoveAll();
			m_NodeList.RemoveAll();
			/////////////////// reset
			if(m_nActiveTool == C_CIRCLE)
			{
				if(m_nType == CIRCLE_BY_NO3)
				{
					if(m_pCrcInDlg->GetSafeHwnd())
						m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
				}
				else
				if(m_nType == CIRCLE_BY_ROT)
				{
					if(m_pCr2InDlg->GetSafeHwnd())
						m_pCr2InDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
				}
			}
			else
			{
				if(m_pLQCInDlg->GetSafeHwnd())
					m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			}
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
		}
		delete str;
		///////////
	}
	else
	if(nAnswer == IDYES)		//continue to get more info
		////////
		return 0;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	if(!m_bAutoAcceptOn)
	{
		if(!(m_NodeList.IsEmpty()))
		{
			/////////////////////////////// total elems
			int nElems = 0;
			if(!(m_ElSegList.IsEmpty()))
			{
				for (POSITION posI = m_ElSegList.GetHeadPosition( );posI !=NULL;)
				{
					////
					nElems += m_ElSegList.GetNext(posI); 
				}
			}
			//////////////////////////////
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			int j;
			//////////////////////////////////////
			switch(m_CurrentCurveType)
			{
				case CP_CIRCLE:

					switch(m_nType)
					{
				
						case CIRCLE_BY_ROT:

							j = sprintf(buf,"Circle %s contains:\n\t%d Node to Rotate\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							j += sprintf(buf+j,"\t%s and %s are Axis Nodes\n",m_FromID,m_ToID);
							if(m_dAng == 360.)
								j += sprintf(buf+j,"\tClosed Circle\n");
							else
								j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAng);
							break;
				
						case CIRCLE_BY_NO3:

							j = sprintf(buf,"Circle %s contains:\n\t%d Interpolation Nodes\n\t%d Elements\n",
								*pID,m_NodeList.GetCount(),nElems);
							if(m_bClosed)
								j += sprintf(buf+j,"\tClosed Circle\n");
							else
							{
								if(m_bArc)
									j += sprintf(buf+j,"\tArc upto 3rd Node\n");
								else
									j += sprintf(buf+j,"\t%f is Angle of Rotation\n",m_dAngSpec);
							}
							break;
				
						default:

							break;

					}
					break;

				default:

					//////
					j = sprintf(buf,"Curve %s contains:\n\t%d Interpolation Nodes\n\t%d Elements\n",
					*pID,m_NodeList.GetCount(),nElems);
			}
			/////////////////////////
			j += sprintf(buf+j,"Nodes:\n");
			//////////////////////////////
			for (POSITION posI = m_NodeList.GetHeadPosition( );posI !=NULL;)
			{
				////
				CDrNode* pNode = (CDrNode*)m_NodeList.GetNextObject(posI);
				j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
			}
			sprintf( buf + j-2, ";");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
			/////////////////////////
			if(nAnswer == IDCANCEL)
			{
				if(m_nActiveTool == C_CIRCLE)
					sprintf(buf,"Do You Want to Delete\nCurrent Circle to Start Allover");
				else
					sprintf(buf,"Do You Want to Delete\nCurrent Curve to Start Allover");
				/////////////////////////	
				nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
				/////////////////////////
				if(nAnswer == IDYES)		//delete
				{
					///////////////////////////////////////// delete
					pList = pObjectMgr->GetObjectList(CURVE);
					int nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
					//////////////////////////////////////////////////// Reset
					pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
					////////////////////////// Reset 
					m_pCurrentCurve = NULL;
					m_nNodeDone		= 0;	// 
					m_bCurveDone	= TRUE;	//   
					m_ElSegList.RemoveAll();
					m_NodeList.RemoveAll();
					//////////////////////////////////////////////////////////// reset
					switch(m_CurrentCurveType)
					{
						case CP_CIRCLE:

							switch(m_nType)
							{
				
								case CIRCLE_BY_ROT:

									if(m_pCr2InDlg->GetSafeHwnd())
										m_pCr2InDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
									break;
				
								case CIRCLE_BY_NO3:

									if(m_pCrcInDlg->GetSafeHwnd())
										m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
									break;
				
								default:

									break;

							}
							break;

						default:

							//////
							if(m_pLQCInDlg->GetSafeHwnd())
								m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
					}
					///////////////////////
					pDoc->UpdateAllViews(NULL);
					pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
					///////////////////////////
					return 0;
				}
			}
			/////////////////////
			str->ReleaseBuffer();
			delete str;
		}
	}
	/////////////////////////////////////////////////////////////////////// Show NewCurve
	if(ShowCurve(pID,TRUE)<0)		// TRUE = Final
	{
		AfxMessageBox("ERROR:\nCELMouse::RightUp_CURVE\nShowCurve Problem");
		return -1;
	}
	/////////////////////////////////////// Set CurveID
	if(*pID == m_CurrentCurveID)
	{		
		char buf[30];
		/////////////
		m_CurrentCurveIDOld	= m_CurrentCurveID;
		m_LastCurveNum++;		// internal
		sprintf(buf,"%d",m_LastCurveNum);
		m_CurrentCurveID	= "C";
		m_CurrentCurveID	+= buf;
	}
	//////////////////////////////////////////////////////
	CDrNode* pNHead;
	CDrNode* pNTail;
	pNHead = (CDrNode*)(m_NodeList.GetHead());// Ist INode
	pNTail = (CDrNode*)(m_NodeList.GetTail());// End INode
	/////////////////////////////////////////////////////////// BLine
	if(m_bBLineOn)			
	{
		m_nNodeDone = 1;
		/////////////////////////////////////
		m_bCurveDone	= TRUE;	//
		//////////////////////////////////// Retain Only Tails Wrong! 11/20/96
//		int nESeg	= m_ElSegList.GetTail();
		m_ElSegList.RemoveAll();
		m_NodeList.RemoveAll();
//		m_ElSegList.AddTail(nESeg);
		///////////////////////////
		CDrNode* pN;
		////////////
		switch(m_CurrentCurveType)
		{
			case CP_CIRCLE:

				switch(m_nType)
				{
				
					case CIRCLE_BY_ROT:

						if(m_bClosed)	
							pN	= pNHead;// Ist INode
						else
							pN	= (CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail());// end CNode

						break;
				
					case CIRCLE_BY_NO3:

						if(m_bClosed)	
							pN	= pNHead;// Ist INode
						else
						{
							if(m_bArc)
								pN	= pNHead;// end INode
							else
								pN	= (CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail());// end CNode
						}
						break;
				
					default:

						break;

				}
				break;


			default:

				pN	= pNTail;
		}
		m_NodeList.AddTail(pN);
		///////////////////////
	}
	else
	{
		m_nNodeDone = 0;
		/////////////////////////////////////
		m_bCurveDone	= TRUE;	//
		//////////////////////////////////// Retain None
		m_ElSegList.RemoveAll();
		m_NodeList.RemoveAll();
	}
	//////////////////////////////////////////////////////////// reset
	SetAnchorNodeID(m_CurrentNodeIDOld);
	CString strLastNodeID;
	////////////////////////////////////
	switch(m_CurrentCurveType)
	{

		case CP_CIRCLE:

			switch(m_nType)
			{
				
				case CIRCLE_BY_ROT:

				if(m_bClosed)	
					strLastNodeID = pNHead->GetObjectID();
				else
					strLastNodeID = 
						((CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail()))->GetObjectID();// end CNode
				///////////////////////////////////////
				if(m_pCr2InDlg->GetSafeHwnd())
					m_pCr2InDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);

				break;
				
				case CIRCLE_BY_NO3:

					if(m_bClosed)	
						strLastNodeID = pNHead->GetObjectID();
					else
					{
						if(m_bArc)
							strLastNodeID = pNHead->GetObjectID();
						else
							strLastNodeID = 
								((CDrNode*)(m_pCurrentCurve->GetCNodeList()->GetTail()))->GetObjectID();// end CNode
					}
					///////////////////////////////////////
					if(m_pCrcInDlg->GetSafeHwnd())
						m_pCrcInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);

					break;
			
				default:

					break;

			}
			break;


		default:

			strLastNodeID = pNTail->GetObjectID();
//			strLastNodeID = m_CurrentNodeID;
			//////
			if(m_pLQCInDlg->GetSafeHwnd())
					m_pLQCInDlg->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	}
	///////////////////////
	m_CurrentNodeIDOld = strLastNodeID;
	///////////////////
	pWnd->GetMenu()->EnableMenuItem(IDM_OPTION_BLINEON,MF_BYCOMMAND|MF_ENABLED);
	///////////////
	return 0;
}


int CELMouse::RightUp_PATCH()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
	////////////////////////////////////////////////////// Add to DataBase
	CString* pID;
	char	 buf[30];
	int i;
	int nAnswer = IDOK;
	////////////////////////////////
	pID			= &m_CurrentPatchID; 
	//////////////////////////////////////////////////// Check Adequate Curve,or cancel
	if(m_nCurveDone<3)
	{
		nAnswer = AfxMessageBox(
			"Minimum of 3 Curves Needed\n Do You want to Continue to Get More Curves ?",
				MB_YESNO|MB_ICONQUESTION );
		/////////////////////////
		if(nAnswer == IDNO)
		{
			CString* str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			////////////////////
			sprintf(buf,"Do You Want to Delete\nCurrent Patch to Start Allover");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			/////////////////////////
			if(nAnswer == IDYES)		//delete
			{
				///////////////////////////////////////// delete
				pList = pObjectMgr->GetObjectList(PATCH);
				int nActiveIndex = pList->GetObjectIndex(PATCH, *pID);
				//////////////////////////////////////////////////// Reset
				pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
				/////////////////////////////////////// Reset
				m_nCurveDone	= 0;	// 
				m_bPatchDone	= TRUE;	// 
				//////////////////////////
				m_pCurrentPatch = NULL;
				for(int i=0;i<4;i++)
				{
					m_PatCurveID[i]		= "";
					m_PatCurveLatch[i]	= CL_FORWARD;
					m_PatCurveElem[i]	= 0;
				}
				/////////////////// reset
				if(m_pCo4InDlg->GetSafeHwnd())
					m_pCo4InDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
				/////////////////////////////////////
				pDoc->UpdateAllViews(NULL);
				///////////////////////////
			}
			delete str;
			///////////
		}
		////////
		return 0;
	}	
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j;
		//////////
		j = sprintf(buf,"Patch %s contains %d Curves:\n",*pID,m_nCurveDone);
		for(i=0;i<m_nCurveDone;i++)
		{
		   j += sprintf( buf + j, "%s, ",m_PatCurveID[i]);
		}
		sprintf( buf + j-2, ";");

		if(j>BUFF_SIZE)
		{
			sprintf( buf, "Internal Error:\nIncrease buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		///////////////////////////////////////////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
		/////////////////////////
		if(nAnswer == IDCANCEL)
		{
			sprintf(buf,"Do You Want to Delete\nCurrent Patch to Start Allover");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			/////////////////////////
			if(nAnswer == IDYES)		//delete
			{
				///////////////////////////////////////// delete
				pList = pObjectMgr->GetObjectList(PATCH);
				int nActiveIndex = pList->GetObjectIndex(PATCH, *pID);
				//////////////////////////////////////////////////// Reset
				pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
				/////////////////////////////////////// Reset
				m_nCurveDone	= 0;	// 
				m_bPatchDone	= TRUE;	// 
				//////////////////////////
				for(int i=0;i<4;i++)
				{
					m_PatCurveID[i]		= "";
					m_PatCurveLatch[i]	= CL_FORWARD;
					m_PatCurveElem[i]	= 0;
				}
				/////////////////////////////////////
				pDoc->UpdateAllViews(NULL);
				///////////////////////////
				delete str;
				///////////
				return 0;
			}
		}
		/////////////////////
		delete str;
	}
	//////////////////////////////////////////////////// Show NewPatch
	int nActiveIndex;
	///////////////////////////
	m_pCurrentPatch	= (CDrPatch*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,PATCH));
	m_pCurrentPatch->SetShow(FALSE);	// not quite ready
	//////////////////////////////////////////////////// Show Patch after Checking
													  // Element Compatibility
	if(m_MI_Sol_I.RBUpCoonInsert(
							m_CurrentPatchType, 
							m_CurrentPatchID,		
							m_pCurrentPatch,
							m_PatCurveID,
							m_PatCurveLatch,
							m_pView
							) <0)
	{
		/////////////////////////////////////// Reset
		m_nCurveDone	= 0;	// 
		m_bPatchDone	= TRUE;	// 
		//////////////////////////
		for(int i=0;i<4;i++)
		{
			m_PatCurveID[i]		= "";
			m_PatCurveLatch[i]	= CL_FORWARD;
			m_PatCurveElem[i]	= 0;
		}
		/////////////////// reset
		if(m_pCo4InDlg->GetSafeHwnd())
		m_pCo4InDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
		/////////////////////////////////////
		return -1; 
	}
	/////////////////////////////////////// Set PatchID
	if(*pID == m_CurrentPatchID)
	{		
		m_LastPatchNum++;		// internal
		sprintf(buf,"%d",m_LastPatchNum);
		m_CurrentPatchID	= "P";
		m_CurrentPatchID	+= buf;
	}
	/////////////////////////////////////// Reset
 	//////////////////////////////////
	m_nCurveDone	= 0;	// 
	m_bPatchDone	= TRUE;	//   
	//////////////////////////
	for( i=0;i<4;i++)
	{
		m_PatCurveID[i]		= "";
		m_PatCurveLatch[i]	= CL_FORWARD;
		m_PatCurveElem[i]	= 0;
	}
	/////////////////// reset
	if(m_pCo4InDlg->GetSafeHwnd())
		m_pCo4InDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	/////////////////////////////////////
	return 0;
}

void CELMouse::OnEBoxRButtonUp(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CMI_CProf	MI_CProf;
	CMI_CSPN	MI_CSPN;
	CMI_PSPN	MI_PSPN;
	CMI_SSPN	MI_SSPN;
	/////////////////////
	CString ID;
	CString* pID = &ID;
	CEDlgMgr* pEDlgMgr;
//	int nMeshType;
	////////////////////
	switch(m_nActiveTool) 
	{

		case NODE:
				
        	m_nNodeDone = 0;
			ShowNode(pID,FALSE,0);
			return;

				
		case CNODE:				

			m_nCNodeDone = 0;
			ShowNode(pID,TRUE,0);
			return;


		case FE1D:
										
					/////////////////////////////////////////
					if (pEDlgMgr->DoModal_Pipe(0) == IDCANCEL)
					return;
					////////////////////////////////////////
			break;	
		///////////////////////////////////////////////////// CURVEs INSERT
		case C_LINEAR:
		case C_QUADRATIC:
		case C_CIRCLE:
		case C_ELLIPSE:
		case C_PARABOLA:
		case C_BEZIER:
		case C_BSPLINE:
		case C_NURB:

			if(m_bDialogOn)
			{
				CDlg_CDlg	dlg;
				dlg.DoModal();
			}
			else
			{
				////////////////////
				UpdateCDlg_TRUE();
				RightUp_CURVE();
				UpdateCDlg_FALSE();
				///////////////////	
			}
			return;

		
		
		case C_STITCH:
		
			if(MI_CProf.RBUp_CProfile(m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;



		case C_SPAWN:
		
			if(MI_CSPN.RBUp_CSpawn(m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		///////////////////////////////////////////////////// PATCHes Insert
		case P_COONS:
						
			//////////////////////////////
			if(m_nCurveDone == 3)
				m_CurrentPatchType	= PP_LOFT3;
			else
			if(m_nCurveDone == 4)
				m_CurrentPatchType	= PP_LOFT4;
			////////////////////
			UpdatePDlg_TRUE();
			RightUp_PATCH();
			UpdatePDlg_FALSE();
			///////////////////	
			return;

			
		case P_EXTRUDE:
						
			if(m_MI_Sol_I.RBUpExtrudeInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case P_ROTATE:
						
			if(m_MI_Sol_I.RBUpRotateInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case P_LOFT:
						
			if(m_MI_Sol_I.RBUpLoft2Insert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case P_DUCT:
						
			if(m_MI_Sol_I.RBUpDuctInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case P_SWEEP:
						
			if(m_MI_Sol_I.RBUpSweepInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;



		case P_SPAWN:
		
			if(MI_PSPN.RBUp_PSpawn(m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		///////////////////////////////////////////////////// SOLIDes Insert
		case S_COONS:
						
			if(m_MI_Sol_I.RBUp_SCoonInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case S_EXTRUDE:
						
			if(m_MI_Sol_I.RBUp_SExtrudeInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case S_ROTATE:
						
			if(m_MI_Sol_I.RBUp_SRotateInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case S_LOFT:
						
			if(m_MI_Sol_I.RBUp_SLoft2Insert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case S_DUCT:
						
			if(m_MI_Sol_I.RBUp_SDuctInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;
		
		case S_SWEEP:
						
			if(m_MI_Sol_I.RBUp_SSweepInsert(m_pView) <0)
				return; 
			//////////////////////////// 	
			return;



		case S_SPAWN:
		
			if(MI_SSPN.RBUp_SSpawn(m_pView,m_nView) <0)
				return; 
			//////////////////////////// 	
			return;
		/////////////////////////////////////////////////// POST

		case P_POST:				// PATCH 
			///////		
			m_MI_Pat_P.LBUpPatchPost();
			return;
		
		
		
		
		
		default:  
			break;
	} 

}
int	CELMouse::IsObjectHit(int nObjectType,POINT point, int startIndex)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	////////////////// Return >=0 ->index (Yes Hit)
	//////////////////         <0 -> No Hit
	if(nObjectType == LABEL)
		return -1;
	////////////////////////////////////////////////////////
	pDListMgr = pObjectMgr->GetObjectList(nObjectType);
	////////////////////////////////////////////////
	if(pDListMgr->GetSpecificObjectCount(nObjectType) <= 0)
		return -1;
	///////////////////////////////////////////////////
	CHitNet* pHitNet = (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	int nNet = pHitNet->GetSearchNet();
	////////////////////////////////
	BOOL bYes;			
	int i=-1;
	int nCount = pDListMgr->GetCount();
	///////////////////////////////////
	for (POSITION pos = pDListMgr->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		////////////////
		i++;
		if(i<startIndex)
			continue;
		//////////////////////////////////////// Transform & Project
		((CDrawView*)m_pView)->GetObjectReadyforRender(m_pdc,pObject,nObjectType);
		/////////////////////
		bYes = pObject->IsObjectHit(nNet,point);	// all else
		if(bYes)
			return i;				
	}	
	return -1;
}

int CELMouse::PutEndIdsInPipeList(CString nid[],int nEnds)
{
	///////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	//////////////////////////////////////////////////////////// 
   	if(nid[0] == nid[1])       
   	{
		AfxMessageBox("Pipe has same Node IDs at both ends\n ZERO Length !!");
   		return -1;
	}			
    ////////////////////////////////////////
    CDListMgr* pDListMgr;
    /////////////////////////////////////////////////////////////////////////////// Add	
	int nActiveIndex;
    CDrFE1D* pAddPipe 	= (CDrFE1D*)(pObjectMgr->AddToDataBase(nActiveIndex,FE1D));
	//////////////////
	int index,nIdLen,nRepeat;
	CString EndNids;  
	////////////////	
	nIdLen  = nid[0].GetLength();
	nRepeat = COMBO_NIDJ_LOC - (nIdLen + 1);   // no. of Blank Spaces 
	CString blank(' ',nRepeat);
	EndNids = nid[0] + blank + nid[1]; 
	/////////////////////////////////////////// already exists
   	if(( index = pObjectMgr->GetObjectIndexfromKey(FE1D,EndNids,1))>=0)       
   	{
		AfxMessageBox("Pipe with these NodeIDs Already Exists !!");
   		return -1;
	}			
	else                                         // new Pipe
	{		
		/////////////////////////////////////////////////
		pAddPipe->SetObjectType((int)FE1D);
		pAddPipe->SetLevelType((int)LEVEL_GRAPA);
		pAddPipe->SetElemType((int)ELEM_OBJECT);              // globals.h
	    ///////////////////////////////// Set Info & Create
		(pAddPipe->GetPipeCard())->nid_i= nid[0];
		(pAddPipe->GetPipeCard())->nid_j= nid[1];
		/////////////////////////////////
//    	pAddPipe->SetObjectType((int)FE1D);          		//  
//    	pAddPipe->SetElemType((int)ELEM_OBJECT);          //  
		///////////////////////////////// store node pointers
//        CDrFE1D* pPipe;
//   		if(( index = GetObjectIndexfromKey(FE1D,EndNids,1))>=0)       
//			pPipe = (CDrFE1D*)pDListMgr->GetObject(index);
		//////////////////////////////////////////////////////////// Pen & Layer
		pAddPipe->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),
												pDrPen->GetStyle());
		pAddPipe->SetLayer(pLayer->GetCurrentLayer());
		///////////////////////////////////////////////////// store node pointers 
		pDListMgr = pObjectMgr->GetObjectList(NODE);
   		for(int i=0;i<nEnds;i++)
    	{
			if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
			{
				CDrNode* pDrNode = (CDrNode*)pDListMgr->GetObject(index);
  				pAddPipe->GetNodeList()->AddTail(pDrNode);
				//////////////////////////////// save Current Pipe Pointer in Nodes
				pDrNode->GetElemList()->InsertObject(pAddPipe);
			}			
	
  		}	
		////////////////////////////////////////////////////////////////////////////////													    
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
		pObjectMgr->SetActiveObjectType(FE1D);		    // set Active Index									
        ////////////////////////////////////////////////////////// Invalidate
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,FE1D);
		//////////////////////////////////////////////////////////
		
	}			    		
	return 0; 
}
int CELMouse::PutEndIdsInPlateList(CString nid[],int nEnds)
{
	///////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	CPatchMnu* pPatchMnu	= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	CObj3DMnu* pObj3DMnu	= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	/////////////////////////////////////////////////////////////////
	static char NodeEnds[] = {'I','J','K','L'};
	CString str;
	char buf[100];
	for (int i = 0;i<nEnds-1;i++)
	{
		for(int j = i+1;j<nEnds;j++)
		{	 
			if(nid[i] == nid[j])
			{
				sprintf(buf,"Node IDs for End: %c & End: %c must be different!!",
								NodeEnds[i],NodeEnds[j]);
				str = buf;
				AfxMessageBox(str);
   				return -1;
   			}
   		}
   	}
   	/////////////////////		 
	int index;
	CString EndNids;  
	///////////////////////////////////////////// EndNids
	CString blank(' ');
	EndNids	= nid[0]; 	
	for ( i=1; i < nEnds; i++)
		EndNids += blank + nid[i]; 
	/////////////////////////////////////////// already exists
   	if(( index = pObjectMgr->GetObjectIndexfromKey(FE2D,EndNids,1))>=0)       
   	{
		AfxMessageBox("Plate with these NodeIDs Already Exists !!");
   		return -1;
	}
	////////////////////////////////////////////////////////////////////// Object List
    CDListMgr* pDListMgr;
	/////////////////////////////////////////////////////////////////////////// add
 	int nActiveIndex;
    CDrFE2D* pAddObject	= (CDrFE2D*)(pObjectMgr->AddToDataBase(nActiveIndex,FE2D));
	/////////////////////////////////////////////////////////////
	pAddObject->SetObjectType((int)FE2D);
	pAddObject->SetLevelType((int)LEVEL_GRAPA);
	pAddObject->SetElemType((int)ELEM_OBJECT);              // globals.h
	////////////////////////////////////////////////////////////////////////////////													    
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(FE2D);		    // set Active Index									
	pAddObject->SetObjectType((int)FE2D);
	pAddObject->SetElemType((int)EL3D_OBJECT);              // globals.h
    ///////////////////////////////// Set Info & Create
	for (i=0; i < nEnds; i++)
		(pAddObject->GetPlatCard())->nid[i]= nid[i];
	//////////////////////////////////////////////////////////// Pen & Layer
	pAddObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),
											pDrPen->GetStyle());
	pAddObject->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////////////////////////////////// store node pointers 
	pDListMgr = pObjectMgr->GetObjectList(NODE);
    for(i=0;i<nEnds;i++)
    {
		if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
		{
			CDrNode* pDrNode = (CDrNode*)pDListMgr->GetObject(index);
  			pAddObject->GetNodeList()->InsertObject(pDrNode);
			//////////////////////////////// save Current Plate Pointer in Nodes
			pDrNode->GetElemList()->InsertObject(pAddObject);
		}			
	
  	}
    ////////////////////////////////////////////////////////// Invalidate
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(FE2D);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,FE2D);
	////////////////////////////////////////////////////////// 
/*		
	/////////////////////////////////////////////////////////////////////// Obj3D/Patch
	if(PutObjectinPatch(pAddObject, nid,nEnds) <0)
	{
		AfxMessageBox("CouldNot Put in Patch!!");
		return -1;
	}
*/		
	//////////////////////////////////////////////////////////
    return 0;
}
    
int CELMouse::PutObjectinPatch(CDrObject* pAddObject,CString nid[],int nEnds)
{
	///////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	CPatchMnu* pPatchMnu	= (CPatchMnu*)pObjectMgr->GetSpecObject(PATCHMNU);
	CObj3DMnu* pObj3DMnu	= (CObj3DMnu*)pObjectMgr->GetSpecObject(OBJ3DMNU);
	/////////////////////////////////////////////////////////////////////// Obj3D/Patch
	CString strPatchID	= pPatchMnu->GetCurrentID();
	CString strObj3DID	= pObj3DMnu->GetCurrentID();
    ////////////////////////////////////////////////////////////////////// Obj3D
    CDListMgr* pDListMgr  = pObjectMgr->GetObjectList(OBJ3D);
    ///////////////////////
    CDrObj3D*	pDrObj3D;
    int index,i;
    if((index = pDListMgr->GetObjectIndex(OBJ3D,strObj3DID) ) >=0)   // exists already
		pDrObj3D = (CDrObj3D*)(pDListMgr->GetObject(index));
	else
	{
    	CNewObjs* pNewObjs;
    	pDrObj3D = (CDrObj3D*)(pNewObjs->NewObject(OBJ3D));   // New
    	//////////////////////////////////////////////////////// Fill Info
		pDrObj3D->SetObjectType((int)OBJ3D);
		pDrObj3D->SetElemType((int)EL3D_OBJECT);              // globals.h
    	pDrObj3D->SetObjectID(strObj3DID);
		pDrObj3D->SetLayer(pLayer->GetCurrentLayer());
    	/////////////////////
    	pDListMgr->InsertObject(pDrObj3D);
    	/////////////////////
    }	 
	////////////////////////////////////////////////////////////////////// Patch 
	if(pDrObj3D)
	{
    	CDListMgr* pPatchList;
    	//////////////////////
	    CDrPatch*	pDrPatch;
    	if((index = pPatchList->GetObjectIndex(PATCH,strPatchID) ) >=0)
    	{	
			pDrPatch = (CDrPatch*)pPatchList->GetObject(index);
    	}	
		else
		{
    		CNewObjs* pNewObjs;
    		pDrPatch = (CDrPatch*)(pNewObjs->NewObject(PATCH));   // New
    		//////////////////////////////////////////////////////// Fill Info
			pDrPatch->SetObjectType((int)PATCH);
			pDrPatch->SetElemType((int)EL3D_OBJECT);              // globals.h
    		pDrPatch->SetObjectID(strPatchID);
			pDrPatch->SetLayer(pLayer->GetCurrentLayer());
    		/////////////////////
    		pPatchList->InsertObject(pDrPatch);
    		/////////////////////
    	}	 
		////////////////////////////////////////////////////////////////////// save in Patch
    	if((index = pPatchList->GetObjectIndex(PATCH,strPatchID) ) >=0)
    	{
			pDrPatch = (CDrPatch*)pPatchList->GetObject(index);
			///////////////////////////////////////////////////// PolyList
			CDListMgr* pPolyList = pDrPatch->GetElemList();
			if(pPolyList)
			{
				if((pPolyList->GetObjectIndex(pAddObject) ) <0) // new
					pPolyList->InsertObject(pAddObject); 
			}		
			///////////////////////////////////////////////////// NodeList
			CDListMgr* pNodeList = pDrPatch->GetNodeList();
			if(pNodeList)
			{
				CDrNode* pDrNode; 
	       		for(i=0;i<nEnds;i++)
 	      		{
					if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
  						pDrNode = (CDrNode*)(pObjectMgr->GetObjectList(NODE)->GetObject(index)); // Object List
  					else
  					{
  						AfxMessageBox("Internal at ObjectinPatch.586");
  						return -1;
  					}		
					if((pNodeList->GetObjectIndex(pDrNode) ) <0) // new in NodeList 
						pNodeList->InsertObject(pDrNode);
				}
			}			
	  	}
	}	  		
	//////////////////////////////////////
	else
	{
		AfxMessageBox("Internal Problem: PutObjectinPatch.ObjMgr.596"); 
		return -1;
	}	
	return 0; 
} 
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CELMouse::ReSetToolID(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case CREATE:
		{
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "CREATE";
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

					pWnd->SetMouseBoxType(ELEMDIMBOX);
					str = "ELEMENT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// EDim0/EDim1...
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NODE;			break;
						case CNODE:			str = "CNODE";		ID = CNODE;			break;

						case CURVE:			str = "CURVE";		ID = CURVE;			break;
						case C_CIRCLE:		str = "CIRCLE";		ID = C_CIRCLE;		break;
						case C_ELLIPSE:		str = "ELLIPSE";	ID = C_ELLIPSE;		break;
						case C_PARABOLA:	str = "PARABOLA";	ID = C_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR";		ID = C_LINEAR;		break;
						case C_QUADRATIC:	str = "QUADRATIC";	ID = C_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC";		ID = C_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE";	ID = C_HERMITE;		break;
						case C_BEZIER:		str = "BEZIER";		ID = C_BEZIER;		break;
						case C_BSPLINE:		str = "BSPLINE";	ID = C_BSPLINE;		break;
						case C_NURB:		str = "NURB";		ID = C_NURB;		break;
						case C_STITCH:		str = "C_STITCH";	ID = C_STITCH;		break;
						case C_SPAWN:		str = "C_SPAWN";	ID = C_SPAWN;		break;

						case PATCH:			str = "PATCH";		ID = PATCH; 		break;
						case SOLID:			str = "SOLID";		ID = SOLID;			break;
						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				//////////////////
/*
				case DISPLACE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "DISPLACE";
					pWnd->SetstrCntlID(str);
					////////////////// Displacement
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_DIS_NODE;		break;
						case CNODE:			str = "CNODE";		ID = NSL_DIS_CNODE;		break;

						case CURVE:			str = "CURVE";		ID = CSL_DISPLACE;		break;
						case C_CIRCLE:		str = "CIRCLE";		ID = CSL_DIS_CIRCLE;	break;
						case C_ELLIPSE:		str = "ELLIPSE";	ID = CSL_DIS_ELLIPSE;	break;
						case C_PARABOLA:	str = "PARABOLA";	ID = CSL_DIS_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR";		ID = CSL_DIS_LINEAR;	break;
						case C_QUADRATIC:	str = "QUADRATIC";	ID = CSL_DIS_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC";		ID = CSL_DIS_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE";	ID = CSL_DIS_HERMITE;	break;
						case C_BEZIER:		str = "BEZIER";		ID = CSL_DIS_BEZIER;	break;
						case C_BSPLINE:		str = "BSPLINE";	ID = CSL_DIS_BSPLINE;	break;
						case C_NURB:		str = "NURB";		ID = CSL_DIS_NURB;		break;
						case C_STITCH:		str = "C_STITCH";	ID = CSL_DIS_STITCH;	break;
						case C_SPAWN:		str = "C_SPAWN";	ID = CSL_DIS_SPAWN;		break;

						case PATCH:			str = "PATCH";		ID = PSL_DISPLACE; 		break;
						case SOLID:			str = "SOLID";		ID = SSL_DISPLACE;		break;
						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				//////////////////
				case PRESSURE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "PRESSURE";
					pWnd->SetstrCntlID(str);
					////////////////// Pressure
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_PRS_NODE;		break;
						case CNODE:			str = "CNODE";		ID = NSL_PRS_CNODE;		break;

						case CURVE:			str = "CURVE";		ID = CSL_PRESSURE;		break;
						case C_CIRCLE:		str = "CIRCLE";		ID = CSL_PRS_CIRCLE;	break;
						case C_ELLIPSE:		str = "ELLIPSE";	ID = CSL_PRS_ELLIPSE;	break;
						case C_PARABOLA:	str = "PARABOLA";	ID = CSL_PRS_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR";		ID = CSL_PRS_LINEAR;	break;
						case C_QUADRATIC:	str = "QUADRATIC";	ID = CSL_PRS_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC";		ID = CSL_PRS_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE";	ID = CSL_PRS_HERMITE;	break;
						case C_BEZIER:		str = "BEZIER";		ID = CSL_PRS_BEZIER;	break;
						case C_BSPLINE:		str = "BSPLINE";	ID = CSL_PRS_BSPLINE;	break;
						case C_NURB:		str = "NURB";		ID = CSL_PRS_NURB;		break;
						case C_STITCH:		str = "C_STITCH";	ID = CSL_PRS_STITCH;	break;
						case C_SPAWN:		str = "C_SPAWN";	ID = CSL_PRS_SPAWN;		break;

						case PATCH:			str = "PATCH";		ID = PSL_PRESSURE; 		break;
						case SOLID:			str = "SOLID";		ID = SSL_PRESSURE;		break;
						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				////////////////// 
				case THERMAL:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "THERMAL";
					pWnd->SetstrCntlID(str);
					////////////////// Thermal
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_THR_NODE;		break;
						case CNODE:			str = "CNODE";		ID = NSL_THR_CNODE;		break;

						case CURVE:			str = "CURVE";		ID = CSL_THERMAL;		break;
						case C_CIRCLE:		str = "CIRCLE";		ID = CSL_THR_CIRCLE;	break;
						case C_ELLIPSE:		str = "ELLIPSE";	ID = CSL_THR_ELLIPSE;	break;
						case C_PARABOLA:	str = "PARABOLA";	ID = CSL_THR_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR";		ID = CSL_THR_LINEAR;	break;
						case C_QUADRATIC:	str = "QUADRATIC";	ID = CSL_THR_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC";		ID = CSL_THR_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE";	ID = CSL_THR_HERMITE;	break;
						case C_BEZIER:		str = "BEZIER";		ID = CSL_THR_BEZIER;	break;
						case C_BSPLINE:		str = "BSPLINE";	ID = CSL_THR_BSPLINE;	break;
						case C_NURB:		str = "NURB";		ID = CSL_THR_NURB;		break;
						case C_STITCH:		str = "C_STITCH";	ID = CSL_THR_STITCH;	break;
						case C_SPAWN:		str = "C_SPAWN";	ID = CSL_THR_SPAWN;		break;

						case PATCH:			str = "PATCH";		ID = PSL_THERMAL; 		break;
						case SOLID:			str = "SOLID";		ID = SSL_THERMAL;		break;
						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					return ID;
				////////////////// 
				case LUMPWT:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "LUMPWT";
					pWnd->SetstrCntlID(str);
					////////////////// LumpWt
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_LWT_NODE;		break;
						case CNODE:			str = "CNODE";		ID = NSL_LWT_CNODE;		break;

						case CURVE:			str = "CURVE";		ID = CSL_LUMPWT;		break;
						case C_CIRCLE:		str = "CIRCLE";		ID = CSL_LWT_CIRCLE;	break;
						case C_ELLIPSE:		str = "ELLIPSE";	ID = CSL_LWT_ELLIPSE;	break;
						case C_PARABOLA:	str = "PARABOLA";	ID = CSL_LWT_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR";		ID = CSL_LWT_LINEAR;	break;
						case C_QUADRATIC:	str = "QUADRATIC";	ID = CSL_LWT_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC";		ID = CSL_LWT_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE";	ID = CSL_LWT_HERMITE;	break;
						case C_BEZIER:		str = "BEZIER";		ID = CSL_LWT_BEZIER;	break;
						case C_BSPLINE:		str = "BSPLINE";	ID = CSL_LWT_BSPLINE;	break;
						case C_NURB:		str = "NURB";		ID = CSL_LWT_NURB;		break;
						case C_STITCH:		str = "C_STITCH";	ID = CSL_LWT_STITCH;	break;
						case C_SPAWN:		str = "C_SPAWN";	ID = CSL_LWT_SPAWN;		break;

						case PATCH:			str = "PATCH";		ID = PSL_LUMPWT; 		break;
						case SOLID:			str = "SOLID";		ID = SSL_LUMPWT;		break;
						default:			str = "UNKNOWN";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					return ID;
*/
				/////////
				default:					str = "UNKNOWN";	ID = UNONE;
					pWnd->SetstrIGenID(str);
					return ID;
			}
			pWnd->SetstrCntlID(str);
			return ID;
		////////
		default:							str = "UNKNOWN";	ID = UNONE;
		}
		pWnd->SetstrOperID(str);
		return ID;
	}
		/*		SAVE FOLLOWING :  TODO		
		//////////////////////////////////////////// Edit
		case EDIT:
		{
			switch(CntlID)
			{
				//////////////////////////////////////// Mesh
				case ELEMENT:
				/////////////
					switch(IGenID)
					{
						case NODE:				return N_EDIT;
						case CURVE:				return C_EDIT;
						case PATCH:				return P_EDIT;
						case SOLID:				return S_EDIT;
						default:				return NONE;
					}
				//////////////////////////////////////// StaticLoad
				case FORCE:
				/////////////
					switch(IGenID)
					{
						case NODE:				return NSL_EDIT_FOR;
						case CURVE:				return CSL_EDIT_FOR;
						case PATCH:				return PSL_EDIT_FOR;
						case SOLID:				return SSL_EDIT_FOR;
						default:				return NONE;
					}
				case DISPLACE:
				/////////////
					switch(IGenID)
					{
						case NODE:				return NSL_EDIT_DIS;
						case CURVE:				return CSL_EDIT_DIS;
						case PATCH:				return PSL_EDIT_DIS;
						case SOLID:				return SSL_EDIT_DIS;
						default:				return NONE;
					}
				case PRESSURE:
				/////////////
					switch(IGenID)
					{
						case NODE:				return NSL_EDIT_PRS;
						case CURVE:				return CSL_EDIT_PRS;
						case PATCH:				return PSL_EDIT_PRS;
						case SOLID:				return SSL_EDIT_PRS;
						default:				return NONE;
					}
				case THERMAL:
				/////////////
					switch(IGenID)
					{
						case NODE:				return NSL_EDIT_THR;
						case CURVE:				return CSL_EDIT_THR;
						case PATCH:				return PSL_EDIT_THR;
						case SOLID:				return SSL_EDIT_THR;
						default:				return NONE;
					}
		case LUMPWT:
				/////////////
					switch(IGenID)
					{
						case NODE:				return NSL_EDIT_LWT;
						case CURVE:				return CSL_EDIT_LWT;
						case PATCH:				return PSL_EDIT_LWT;
						case SOLID:				return SSL_EDIT_LWT;
						default:				return NONE;
					}

		

						case CURVE:				return C_MOVE;
				case CURVE:				return C_POST;
				case CURVE:				return C_UNPOST;
				case CURVE:				return C_DELETE;
				case PATCH:				return P_MOVE;
				case PATCH:				return P_POST;
				case PATCH:				return P_UNPOST;
				case PATCH:				return P_DELETE;
				case SOLID:				return S_MOVE;
				case SOLID:				return S_POST;
				case SOLID:				return S_UNPOST;
				case SOLID:				return S_DELETE;
//////////////////////////////
				//////////////////////////////////////// StaticLoad
				case FORCE:
				case C_ROTATE:
				case C_XLATE:
				case C_SCALE:
				case C_SHEAR:
				case C_OPER:
				case C_SUPP:
				case C_STAL:
				case C_DYNL:
				case C_SPEL:
				////////////////
				case P_ROTATE_B:
				case P_XLATE:
				case P_SCALE:
				case P_SHEAR:
				case P_OPER:
				case P_SUPP:
				case P_STAL:
				case P_DYNL:
				case P_SPEL:
				////////////////
				case S_ROTATE_B:
				case S_XLATE:
				case S_SCALE:
				case S_SHEAR:
				case S_OPER:
				case S_SUPP:
				case S_STAL:
				case S_DYNL:
				case S_SPEL:

		}

*/
}
	
void CELMouse::ModeLessOff()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
	if(GetCrcInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
	if(GetCr2InDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CR2IN,IDOK);
	if(GetCo4InDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CO4IN,IDOK);
	if(GetNodInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
}

void CELMouse::ModeLessOn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
	if
	(	
		(aTool == NODE) ||(aTool == CNODE)
	)
	{
		if(GetLQCInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
		if(GetCrcInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
		if(GetCr2InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CR2IN,IDOK);
		if(GetCo4InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CO4IN,IDOK);
		if(!(GetNodInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_NODIN,IDOK);
		/////////////////////////////////////// Other Coords
		if(GetNodInDlg()->m_hWnd)
		{
			CStatic* pCtl;
			pCtl = (CStatic*)GetNodInDlg()->GetDlgItem(IDC_OTHER);
			if(pWnd->GetActiveViewNumber() == VIEW12)
				pCtl->SetWindowText("Z");
			else
			if(pWnd->GetActiveViewNumber() == VIEW23)
				pCtl->SetWindowText("X");
			else
			if(pWnd->GetActiveViewNumber() == VIEW31)
				pCtl->SetWindowText("Y");
		}
	}
	else
	if
	(
		(aTool == C_LINEAR)		||	(aTool == C_QUADRATIC)	||
		(aTool == C_PARABOLA)	||	(aTool == C_BSPLINE)		||		     
		(aTool == C_NURB)		||	(aTool == C_BEZIER)				     
	)
	{
		if(!(GetLQCInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_LQCIN,IDOK);
		if(GetCrcInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
		if(GetCr2InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CR2IN,IDOK);
		if(GetCo4InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CO4IN,IDOK);
		if(GetNodInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
	}
	else
	if
	(	(aTool == C_CIRCLE)		||	(aTool == C_ELLIPSE)		)
	{
		CMDlgMgr* pMDlgMgr;
		/////////////////////////////////////////////////////////////// Using EDlgMgr
		pMDlgMgr->DoModal_CIRCLE_Type(m_nType);
		///////////////////////////////////////
		if(GetLQCInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
		if(GetCo4InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CO4IN,IDOK);
		if(GetNodInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
		if(m_nType == CIRCLE_BY_NO3)
		{
			if(GetCr2InDlg()->m_hWnd)
				pWnd->SendMessage(ID_GOODBYE_CR2IN,IDOK);
			if(!(GetCrcInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_CRCIN,IDOK);
		}
		else
		if(m_nType == CIRCLE_BY_ROT)
		{
			if(GetCrcInDlg()->m_hWnd)
				pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
			if(!(GetCr2InDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_CR2IN,IDOK);
		}
	}
	else
	if(aTool == P_COONS)
	{
		if(GetLQCInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_LQCIN,IDOK);
		if(GetCrcInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CRCIN,IDOK);
		if(GetCr2InDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_CR2IN,IDOK);
		if(!(GetCo4InDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_CO4IN,IDOK);
		if(GetNodInDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
	}

}

long CELMouse::CreateorActivateNodIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetNodInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetNodInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetNodInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetNodInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
		GetNodInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(GetNodInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetNodInDlg()->GetDlgItem(IDC_OTHER));
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
			pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetNodInDlg()->m_NID		= GetCurrentNodeID();
	GetNodInDlg()->m_SID		= GetCurrentSupID();
	GetNodInDlg()->m_nViewNum	= pWnd->GetActiveViewNumber();
	GetNodInDlg()->m_bnid_C		= FALSE;
	GetNodInDlg()->m_dCoord		= GetCurrentThirdCoord();
	////////////////////////////////
	GetNodInDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;
}
	 
long CELMouse::GoodByeNodIn(UINT wParam, long lParam)
{
	
	if(GetNodInDlg()->m_hWnd)
		GetNodInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CELMouse::UpdateNodIn(UINT wParam, long lParam)
{

	GetNodInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	SetCurrentNodeID(GetNodInDlg()->m_NID);
	SetCurrentSupID(GetNodInDlg()->m_SID);
//	SetCurrentLoadID(Lid);
	SetMouseWIC(GetNodInDlg()->m_MouseWIC);
	SetCurrentThirdCoord(GetNodInDlg()->m_dCoord);
	//////////
	return 0L;
}
	
long CELMouse::CreateorActivateLQCIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetLQCInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetLQCInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetLQCInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetLQCInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
		GetLQCInDlg()->SetActiveWindow();
	////////////////////////////////////////////////////////////////// Set ID
	GetLQCInDlg()->m_CID		= GetCurrentCurveID();
	GetLQCInDlg()->m_NID		= GetCurrentNodeID();
	GetLQCInDlg()->m_SID		= GetCurrentSupID();
	GetLQCInDlg()->m_nElperSeg	= GetCurrentElPerSeg();
	GetLQCInDlg()->m_dRatio		= GetCurrentRatio();
	GetLQCInDlg()->m_bClosed	= IsClosed();
	GetLQCInDlg()->m_bAdvanceOn	= IsAdvanceOn();
	////////////////////////////////
	GetLQCInDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;
}
	 
long CELMouse::GoodByeLQCIn(UINT wParam, long lParam)
{
	
	if(GetLQCInDlg()->m_hWnd)
		GetLQCInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CELMouse::UpdateLQCIn(UINT wParam, long lParam)
{

	GetLQCInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	SetCurrentCurveID(GetLQCInDlg()->m_CID);
	SetCurrentNodeID(GetLQCInDlg()->m_NID);
	SetCurrentSupID(GetLQCInDlg()->m_SID);
	SetCurrentElPerSeg(GetLQCInDlg()->m_nElperSeg);
	SetCurrentRatio(GetLQCInDlg()->m_dRatio);
	SetClosed(GetLQCInDlg()->m_bClosed);
	SetAdvanceOn(GetLQCInDlg()->m_bAdvanceOn);
	//////////
	return 0L;
}

long CELMouse::CreateorActivateCrcIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetCrcInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCrcInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCrcInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCrcInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
		GetCrcInDlg()->SetActiveWindow();
	////////////////////////////////////////////////////////////////// Set ID
	GetCrcInDlg()->m_CurveID	= m_CurrentCurveID;
	GetCrcInDlg()->m_NID		= m_CurrentNodeID;
	GetCrcInDlg()->m_nMesh		= m_ElPerSeg;
	GetCrcInDlg()->m_Ratio		= m_Ratio;
	GetCrcInDlg()->m_bClosed	= m_bClosed;
	GetCrcInDlg()->m_SegAngle	= m_SegAngle;
	GetCrcInDlg()->m_bAutoSeg	= m_bAutoSeg;
	GetCrcInDlg()->m_dAngSpec	= m_dAngSpec;
	GetCrcInDlg()->m_bArc		= m_bArc;
	////////////////////////////////
	GetCrcInDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;
}
	 
long CELMouse::GoodByeCrcIn(UINT wParam, long lParam)
{
	
	GetCrcInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CELMouse::UpdateCrcIn(UINT wParam, long lParam)
{

	GetCrcInDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	m_CurrentCurveID	= GetCrcInDlg()->m_CurveID;
	m_CurrentNodeID		= GetCrcInDlg()->m_NID;
	m_ElPerSeg			= GetCrcInDlg()->m_nMesh;
	m_Ratio				= GetCrcInDlg()->m_Ratio;
	m_bClosed			= GetCrcInDlg()->m_bClosed;
	m_SegAngle			= GetCrcInDlg()->m_SegAngle;
	m_bAutoSeg			= GetCrcInDlg()->m_bAutoSeg;
	m_dAngSpec			= GetCrcInDlg()->m_dAngSpec;
	m_bArc				= GetCrcInDlg()->m_bArc;
	//////////
	return 0L;
}

long CELMouse::CreateorActivateCr2In(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetCr2InDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCr2InDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCr2InDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCr2InDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
		GetCr2InDlg()->SetActiveWindow();
	////////////////////////////////////////////////////////////////// Set ID
	GetCr2InDlg()->m_CurveID	= m_CurrentCurveID;
	GetCr2InDlg()->m_nMesh		= m_ElPerSeg;
	GetCr2InDlg()->m_Ratio		= m_Ratio;
	GetCr2InDlg()->m_dAng		= m_dAng;
	GetCr2InDlg()->m_FromID		= m_FromID;
	GetCr2InDlg()->m_ToID		= m_ToID;
	GetCr2InDlg()->m_NodeID		= m_CurrentNodeID;
	GetCr2InDlg()->m_SegAngle	= m_SegAngle;
	GetCr2InDlg()->m_bAutoSeg	= m_bAutoSeg;
	////////////////////////////////
	GetCr2InDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;
}
	 
long CELMouse::GoodByeCr2In(UINT wParam, long lParam)
{
	
	GetCr2InDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CELMouse::UpdateCr2In(UINT wParam, long lParam)
{

	GetCr2InDlg()->UpdateData(TRUE);
	///////////////////////////////// Reset data in ElMouse
	m_CurrentCurveID	= GetCr2InDlg()->m_CurveID;
	m_ElPerSeg			= GetCr2InDlg()->m_nMesh;
	m_Ratio				= GetCr2InDlg()->m_Ratio;
	m_dAng				= GetCr2InDlg()->m_dAng;
	m_FromID			= GetCr2InDlg()->m_FromID;
	m_ToID				= GetCr2InDlg()->m_ToID;
	m_CurrentNodeID		= GetCr2InDlg()->m_NodeID;
	m_SegAngle			= GetCr2InDlg()->m_SegAngle;
	m_bAutoSeg			= GetCr2InDlg()->m_bAutoSeg;
	//////////
	return 0L;
}

long CELMouse::CreateorActivateCo4In(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetCo4InDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCo4InDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCo4InDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCo4InDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
		GetCo4InDlg()->SetActiveWindow();
	////////////////////////////////////////////////////////////////// Set ID
	CString Pid = GetCurrentPatchID();
	////////////
	CString PCid[4];
	CURVELATCH CLat[4];
	CString sLat[4];
	int Elem[4];
	////////////
	for(int i=0;i<4;i++)
	{
		PCid[i] = GetPatCurveID(i);
		CLat[i] = GetPatCurveLat(i);
		Elem[i] = GetPatCurveElem(i);
	}
	//////////////////////////////////////
	for(i=0;i<4;i++)
	{
		sLat[i] = "FORWARD";
		/////////////////////////
		if(CLat[i] == CL_BACKWARD)
			sLat[i] = "BACKWARD";
	}
	////////////
	GetCo4InDlg()->m_PatchID	= Pid;
	GetCo4InDlg()->m_CID_1		= PCid[0];
	GetCo4InDlg()->m_CID_2		= PCid[1];
	GetCo4InDlg()->m_CID_3		= PCid[2];
	GetCo4InDlg()->m_CID_4		= PCid[3];
	GetCo4InDlg()->m_TotEl_1	= Elem[0];
	GetCo4InDlg()->m_TotEl_2	= Elem[1];
	GetCo4InDlg()->m_TotEl_3	= Elem[2];
	GetCo4InDlg()->m_TotEl_4	= Elem[3];
	GetCo4InDlg()->m_Orient_1	= sLat[0];
	GetCo4InDlg()->m_Orient_2	= sLat[1];
	GetCo4InDlg()->m_Orient_3	= sLat[2];
	GetCo4InDlg()->m_Orient_4	= sLat[3];
	////////////////////////////////
	GetCo4InDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;
}
	 
long CELMouse::GoodByeCo4In(UINT wParam, long lParam)
{
	
	GetCo4InDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CELMouse::UpdateCo4In(UINT wParam, long lParam)
{

	GetCo4InDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	CString Pid = GetCo4InDlg()->m_PatchID;
	///////////
	CString PCid[4];
	CURVELATCH CLat[4];
	CString sLat[4];
	int Elem[4];
	//////////////////////////////////////
	PCid[0] = GetCo4InDlg()->m_CID_1;
	PCid[1] = GetCo4InDlg()->m_CID_2;
	PCid[2] = GetCo4InDlg()->m_CID_3;
	PCid[3] = GetCo4InDlg()->m_CID_4;
	Elem[0] = GetCo4InDlg()->m_TotEl_1;
	Elem[1] = GetCo4InDlg()->m_TotEl_2;
	Elem[2] = GetCo4InDlg()->m_TotEl_3;
	Elem[3] = GetCo4InDlg()->m_TotEl_4;
	sLat[0] = GetCo4InDlg()->m_Orient_1;
	sLat[1] = GetCo4InDlg()->m_Orient_2;
	sLat[2] = GetCo4InDlg()->m_Orient_3;
	sLat[3] = GetCo4InDlg()->m_Orient_4;
	//////////////////////////////////////
	int i;
	for(i=0;i<4;i++)
	{
		CLat[i] = CL_FORWARD;
		/////////////////////////
		if(sLat[i] == "BACKWARD")
			CLat[i] = CL_BACKWARD;
	}
	///////////////////////////////// Reset data in ElMouse
	SetCurrentPatchID(Pid);
	for(i=0;i<4;i++)
	{
		SetCurrentPatCurveID(PCid[i],i);
		SetPatCurveLat(CLat[i],i);
		SetPatCurveElem(Elem[i],i);
	}
	//////////
	return 0L;
}
void CELMouse::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" ELMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////
		ar	<</*BOOL*/	(BYTE)m_bDialogOn 
			<</*BOOL*/	(BYTE)m_bElementMode 
			<</*int*/	(WORD)m_nActiveObject 
			<</*int*/	(WORD)m_nActiveTool 
			<</*BOOL*/	(BYTE)m_bDragOn 
			<</*BOOL*/	(BYTE)m_bDragging 
			<</*BOOL*/	(BYTE)m_bRefreshOn 
			<</*int*/	(WORD)m_nNodeDone;
 			//////////////////////////////

	}
	else
	{
		TRACE(" ELMouse:    Loading\n");	

			/////////////////////////////////////////////////
		ar	>>/*BOOL*/	bDialogOn 
			>>/*BOOL*/	bElementMode 
			>>/*int*/	nActiveObject 
			>>/*int*/	nActiveTool 
			>>/*BOOL*/	bDragOn 
			>>/*BOOL*/	bDragging 
			>>/*BOOL*/	bRefreshOn 
			>>/*int*/	nNodeDone;
 		//////////////////////////////
		m_bDialogOn		= (BOOL)bDialogOn;
		m_bElementMode	= (BOOL)bElementMode;
		m_nActiveObject	= (int)nActiveObject;
		m_nActiveTool	= (int)nActiveTool;
		m_bDragOn		= (BOOL)bDragOn;
		m_bDragging		= (BOOL)bDragging;
		m_bRefreshOn	= (BOOL)bRefreshOn;
		m_nNodeDone		= (int)nNodeDone;
	
	}        
	///////////////////////////////////// 
	SerializeNode(ar);      
	SerializePipe(ar);
	//////////////////
}

///////////////////////////////////////////////////////// element serializer
void CELMouse::SerializeNode(CArchive& ar)
{ 
	///////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentNodeID
			<<	m_AnchorNodeID;
	}
	///////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>	m_CurrentNodeID
			>>	m_AnchorNodeID;
	}
				    				
}
void CELMouse::SerializePipe(CArchive& ar)
{ 
	//////////////////////////////////////////////////// STORING				
	if (ar.IsStoring())
	{
		ar	<<	m_CurrentPipeID;
	}
	//////////////////////////////////////////////////// LOADING				
	else
	{
		ar	>>m_CurrentPipeID;
	}
					    				
}
///////////////////////////////////// end of Module //////////////////////		
/*	
	///////////////////////////////////////////////////////////TEMPORARY
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
    /////////////////////////////////////////////////////////////////////
	CEDlgMgr* pEDlgMgr;
	CString nID;
	pEDlgMgr->DoModal_Node(m_nView,&MouseWIC,&nID);
	pEDlgMgr->DoModal_Pipe();
	/////////////////////////
	CDDlgMgr* pDDlgMgr;
	pDDlgMgr->DoModal_Label_Insert();
	pDDlgMgr->DoModal_Label_Edit();
	/////////////////////////////////////////////////////////////////////
*/


