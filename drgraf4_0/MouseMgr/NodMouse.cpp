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
#include "MsObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
//#include "Def_Lims.h"                    
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_MouseAct.h" // Mouse Action                   
#include "Def_CuPS.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MNodMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h" 	
///////////////////// specials
#include "Def_Spec.h"
#include "Obj3DMnu.h"
#include "PatchMnu.h"
#include "HitNet.h"
#include "DrPen.h"
#include "Layer.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "mouse.h"
#include "DListMgr.h"
/////////////////////
#include "MI_GangN.h" 
//092798#include "MI_Gang0.h" 
////////////////////// 
#include "CommRsrc.h"
#include "Dlg_NodI.h"
//////////////////////
#include "NodMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_INCREMENT	0	// 1 Object Refernce Node           
#define MAX_INFO_DIRECTION	2	// 1 Object Refernce Node/2 Nodes( for Axis)           
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CNodMouse,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodMouse::CNodMouse()
{

	///////////////////////////
	m_CurrentNodeID		= "1";
	m_CurrentNodeIDOld	= "1";
	////////////////////////////
	m_pNodInDlg			= NULL;                                                                                
	m_bDoModalDone		= FALSE;
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
	///////////////////////////////////////////
	m_bRefreshOn		= FALSE;
 	/////////////////////////////////////////// Node 
	m_bAnchorCNode		= FALSE;
	m_ThirdCoord		= 0.0;
	/////////////////////////////////////////// NodIDlg
	m_bCorINodeOpDone	= FALSE;
	m_bCNode			= FALSE;
	////////
	m_bAdvanced			= FALSE;
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;			// for Advance
}

CNodMouse::~CNodMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pNodInDlg)
	{
		if(m_pNodInDlg->m_hWnd)
			m_pNodInDlg->DestroyWindow();
		///////////////////
		delete m_pNodInDlg;                                                                                
		///////////////////
	}
}

void CNodMouse::Init_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		m_bCNode = FALSE;
	else
		m_bCNode = TRUE;
	/////////////////////////////////////////////////////////
	C3DMath Math3D;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////// Node
	m_pSpawnedNode		= NULL;
	m_pCurrentNode		= NULL;
	Math3D.Set3DPts(&m_wLoc,0.0,0.0,0.0);
	//////////
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;
	/////////////////////////////////////////// Dlg_NodI 
	m_SpawnedNodeID	= m_CurrentNodeID;
//	m_CurrentNodeID		= "";			// because of m_CurrentNodeID snafu when m_bAdvanced = 0
	m_ObjID			= m_SpawnedNodeID;
	///
	m_X				= m_wLoc.x;
	m_Y				= m_wLoc.y;
	m_Z				= m_wLoc.z;
	m_NID			= m_CurrentNodeID;
	m_bDirect		= FALSE;		// Forcing Mouse Search of Node	
	m_bDominant		= FALSE;
	m_bDirection	= FALSE;
	m_bIncrement	= TRUE;
	/////////////////////////////////////////// Spawning Info.
	m_RefPtID		= "";
	Math3D.Set3DPts(&m_wRefPt,0.0,0.0,0.0);
	m_FromID		= "";
	Math3D.Set3DPts(&m_wFrom,0.0,0.0,0.0);
	m_ToID			= "";
	Math3D.Set3DPts(&m_wTo,0.0,0.0,0.0);

	Math3D.Set3DPts(&m_wInc,0.0,0.0,0.0);
	Math3D.Set3DPts(&m_wFin,0.0,0.0,0.0);
	///////////////////////
}

void CNodMouse::Terminate_NOD(BOOL bError)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedNode)
		{
			delete m_pSpawnedNode;
			m_pSpawnedNode = NULL;
		}
	}
	///////////////////////////
}

void CNodMouse::InitDlgIn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pNodInDlg		= new CDlg_NodI(pWnd,m_bAdvanced);
	/////////////
}
	
void CNodMouse::SizeRectDlgIn(CRect& BoxRect)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cyHScroll	= ::GetSystemMetrics(SM_CYHSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cxEdge		= ::GetSystemMetrics(SM_CXEDGE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	///////////////////////////////
	CRect clientRect;
	pWnd->GetClientRect(&clientRect);
	pWnd->ClientToScreen(&clientRect);
	////////////////
	CRect FrameRect;
	pWnd->GetWindowRect(&FrameRect);
	/////////////////////////////////////////////////////////////// ...InBox 
	int Boxwidth  		= BoxRect.Width();
	int Boxheight 		= BoxRect.Height();
	/////////////////////////////////////// 
	BoxRect.bottom	= FrameRect.bottom	- cyHScroll- cyEdge; //
	BoxRect.top		= BoxRect.bottom - Boxheight; //
	BoxRect.left	= clientRect.left + (clientRect.Width() - Boxwidth)/2;  
	BoxRect.right	= BoxRect.left + Boxwidth;
	////////////////////////////////
	return;
}

void CNodMouse::PreLeftDown(CPoint point)
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

CDrObject* CNodMouse::GetObjectFromID(CString& ID, int nObjType)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	int index = pObjectMgr->GetObjectIndexfromKey(nObjType,ID,1);
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(nObjType);
	return (CDrObject*)(pDListMgr->GetObject(index));
}

void CNodMouse::SetMouseWICFromNode(CDrNode* pDrNode,LPOINT3* pMouseWIC)
//void CNodMouse::SetMouseWICFromNode(CString& NID,LPOINT3* pMouseWIC)
{
//	CDrNode* pDrNode = (CDrNode*)GetObjectFromID(NID, NODE);
	pMouseWIC->x = pDrNode->GetNodeCard()->x;								  	
	pMouseWIC->y = pDrNode->GetNodeCard()->y;								  	
	pMouseWIC->z = pDrNode->GetNodeCard()->z;								  	
}
	
void CNodMouse:: ElementLeftDown_NOD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType; 
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		case INODE:
		case CNODE:
		//////////////////////////////////////////////////
		default:
			break;
	}  

}
	
void CNodMouse::PreLeftUp(CPoint point)
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

int CNodMouse::ShowNode(CString* pID,BOOL bnid_c,int nHowMany)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
//	 nHowmany			// Used as an afterthought for creating Node anyway
						// in GangN.CreateNode
						// even if same coords node exists already !!!
						// when nHowmany == -12345
						// Use nNodeIndex of CreateNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
//	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	if(m_nActiveTool == MCNODE)
		pObjectMgr->SetActiveObjectType(FE0D); 
	else
		pObjectMgr->SetActiveObjectType(NODE);                   
	////////////////////
/*
	if(m_bDialogOn)
	{
		CMNodMgr* pMNodMgr;
		int i;
		/////////////////////////////////////////////////////////////// Using MNodMgr 
		LPOINT3 MouseWIC = GetMouseWIC();
		pID = &m_CurrentNodeID;
		if (pMNodMgr->DoModal_Node(bnid_c,m_nView,&MouseWIC,pID,nHowMany) == IDCANCEL)
			return -1;
		////////////////////////////////////////////////////////// pNode
	   	if(( i= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1)) <0)
   		{
			AfxMessageBox("ERROR:\nCNodMouse::ShowNode\nNo Node Index\nInternal Problem");
   			return -1;
   		}	
 		CDListMgr* pDListMgr = pObjectMgr->GetObjectList(NODE);
		m_pCurrentNode = (CDrNode*)pDListMgr->GetObject(i);
	}
	else
	{
*/
	/////////////////////////////////////////////////////////////// Using GangN
	WORLD wPt;
	LPOINT3 MouseWIC = GetMouseWIC();
	///////////////////////////
	WICtoWOP(&MouseWIC,&wPt);	// actually DOUBLE (ie bGen = FALSE in CreateNode below)
	///////////////////////////
	int nNodeIndex = nHowMany;
	int nLabelIndex= 0;
	CMI_GangN GangN;
/*092798
	CMI_Gang0 Gang0;
	////////////////////////////////
	if(m_nActiveTool == MCNODE)
		m_pCurrentNode = Gang0.CreateFE0D(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,FALSE,
											nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	else
092798*/
	if(m_nActiveTool == MCNODE)
	{
		AfxMessageBox(
		"ERROR:\nCNodMouse::ShowNode\nShould NOT be here\nm_nActiveTool == MCNODE");
		return -1;
	}
//092798	m_pCurrentNode = GangN.CreateNode(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,FALSE,
//092798										nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	m_pCurrentNode = GangN.CreateNode(*pID,m_pCurrentLabel, wPt, bnid_c,FALSE,
								nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
	m_pCurrentNode->SetCategory(CA_ELEMENT);
	////////////////////////////////////////////////////////////////////// Show
//	pObjectMgr->SetActiveObjectIndex(nLabelIndex);		    // set Active Index for Label									
//	pObjectMgr->SetActiveObjectType(LABEL);					// set Active ObjectType									
//	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nLabelIndex,LABEL);
	//////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectIndex(nNodeIndex);	// set Active Index
	///
	if(bnid_c)
	{
		if(pWnd->GetCurrentIGenID() == MCNODE)
			pObjectMgr->ShowObject_On_Off(m_pCurrentNode,MCNODE,TRUE);
//		{
//			pObjectMgr->SetActiveObjectType(MCNODE);		    // set Active Type
//			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,MCNODE);
//		}
		else
			pObjectMgr->ShowObject_On_Off(m_pCurrentNode,CNODE,TRUE);
//		{
//			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type
//			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,CNODE);
//		}
	}
	else
			pObjectMgr->ShowObject_On_Off(m_pCurrentNode,NODE,TRUE);
//	{
//		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type
//		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nNodeIndex,NODE);
//	}
	///////////////////////////////
	return 0;
}	 

void CNodMouse::PostLeft()
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

void CNodMouse::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
	{
		pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
	}
	///////////////////////////////////////// make sure Dlg is Open
	if(!(GetNodInDlg()->m_hWnd))
		pWnd->SendMessage(ID_ACTIVE_NODIN,IDOK);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	CDListMgr* pDListMgr = NULL;
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// No Node
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
	if(pWnd->GetCurrentIGenID() == CNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	else
	if(pWnd->GetCurrentIGenID() == MCNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(MCNODE);
	///
	if(!pDListMgr || pDListMgr->GetCount()<=0)
		return;
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_NOD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CNodMouse::UpdateNDlg_TRUE()
{
	//////////////////////////////////
	m_pNodInDlg->UpdateData(TRUE); // from screen
	////////////
	m_CurrentNodeID = m_pNodInDlg->m_ObjID;
//	m_CurrentSupID	= m_pNodInDlg->m_SID;
	m_ThirdCoord	= m_pNodInDlg->m_dCoord;
	/////////////////////////////////////
}
			
void CNodMouse::UpdateNDlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString str; 
	///////////////////////////////////////////////////////////// Advanced Option
	GetNodInDlg()->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
	GetNodInDlg()->m_ObjID		= m_CurrentNodeID;
	GetNodInDlg()->m_dCoord		= m_ThirdCoord;
	////////////////////////////////////////////// CurrStat
	str = "Ready for Selection@";
	if(m_nActiveTool == INODE)
	{
		str += "An Input Node";
		m_pNodInDlg->SetWindowText("INPUT Node");
	}
	else
	if(m_nActiveTool == CNODE || m_nActiveTool == MCNODE)
	{
		str += "A Control Node";
		m_pNodInDlg->SetWindowText("CONTROL Node");
	}
	///
	pWnd->SetstrCurrID(str);
	pWnd->UpdateCurrStat(str);
	////////////
	m_pNodInDlg->UpdateData(FALSE); // to screen
	////////////////////////////
}
			
int CNodMouse::LeftUp_NODE(CPoint point,BOOL bCNode)
{
	////////////////////////////////////////////////////////////////////// Node Input
	if(	m_nActiveTool == INODE || m_nActiveTool == NODE ||
		m_nActiveTool == CNODE || m_nActiveTool == MCNODE )
	{
		return LeftUp_NODE_NodeContext(point,bCNode);
	}
	else
	{
		AfxMessageBox("This Routine Should NOT be Called");
		return -1;
	}
}
			
int CNodMouse::LeftUp_NODE_NodeContext(CPoint point,BOOL bCNode)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for creating Node anyway
						// in GangN.CreateNode
						// even if same coords node exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	///
	CDListMgr* pDListMgr = pObjectMgr->GetObjectList(pWnd->GetCurrentIGenID());		
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString*	pID;
	CString		ID;
	CDrNode*	pDrNode;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	////////////////////////////////////////////////////////////////// Blank NodeID
	pID = &m_CurrentNodeID;
	if(*pID == "")
	{
		AfxMessageBox("Input ERROR:\nNodeID is Blank!\nPlease Type in Node ID",MB_OK|MB_ICONEXCLAMATION);
		/////////
		return -1;
	}
	///////////////////////
	int			j;
	BOOL		bNew	= TRUE;
	////////////////////////////////////////////////////////////////// ERROR:User Selected Same ID
	pList = pObjectMgr->
		GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());
//	pList	= pObjectMgr->GetObjectList(m_nActiveTool);
	if(m_nActiveTool == MCNODE)
	{
//092798		index	= pList->GetObjectIndex(FE0D, *pID);
		AfxMessageBox(
		"ERROR:\nCNodMouse::LeftUp_NODE_NodeContext\nShould NOT be here\nm_nActiveTool == MCNODE");
		return -1;
	}
	else
		index	= pList->GetObjectIndex(NODE, *pID);
	///
	if(index>=0)						// User selected pID
	{
		pDrNode = (CDrNode*)(pList->GetObject(index));
		ShowNodeInfo_SameID(pDrNode);
		/////////
		return -1;
	}
	///////////////////////////////////////////// See if any Existing Node Hit w/ same Coords
//092798	nResult = LeftUp_Node_Accept_NodeContext(point,bCNode,m_nActiveTool == MCNODE);
	nResult = LeftUp_Node_Accept_NodeContext(point,bCNode,LEVEL_GRAPA);
	/////////////////////////////////////////////   
	switch(nResult)
	{
		case -2:		// cancel
			return nResult;
		case 0:			// Hit or Not , Create NEW anyway (m_wLoc Set)
			bNew = TRUE;
			nAnyway	= -12345;	// Create Anyway
			break;
		default:		// Error
			return -1;
	}					
	//////////////////////////////////
	if(!bNew)
	{
		///
		m_CurrentNodeID			= m_pCurrentNode->GetObjectID();
		m_CurrentNodeIDOld		= m_pCurrentNode->GetObjectID();
		m_AnchorNodeID			= m_CurrentNodeIDOld;
		m_bAnchorCNode			= bCNode;
		/////////////////////////////////////////////
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////// New Node
	if(!m_bAutoAcceptOn)
	{
		/////////////////////////////////////////////////
		CString*	str		= new CString;
		char*		buf		= str->GetBuffer(BUFF_SIZE);
		//////////////////////////
		WORLD wPt;
		WORtoWOP(&m_wLoc,&wPt);	// to Physical
		//////////////////////////////
		j = sprintf(buf,
			"***** New Node Selection: *****\nNodeID = %s\nCoordinates:\n\tX = %f\n\tY = %f\n\tZ = %f ",
			*pID,wPt.x,wPt.y,wPt.z);
		j += sprintf(buf+j,"\n\nAccept This New Node?");
		////////////////////////////
		int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////
		if(nResult == IDNO)
			return -2;
		//////////////
		delete str;
	}
	//////////////////////////////////
	if(ShowNode(pID,bCNode,nAnyway)<0)	// Create & Show
	{
		AfxMessageBox("ERROR:\nCNodMouse::LeftUp_Node_NodeCotext\nShowNode Problem");
		return -1;
	}
/*	removed to leftUp_Node
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld	= *pID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= bCNode;
	/////////////
	pObjectMgr->SetNodeInfoID(m_CurrentNodeID,bCNode,(UINT)m_nActiveTool);		
	////////////
*/
	return 0;
}

int CNodMouse::LeftUp_Node_Accept_NodeContext(CPoint point,BOOL bCNode,BOOL bMNode)
{
	int nResult = 0; // Create Anyway
	/////////////////////////////////
	// multiple search fr same coord
	///////////////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr = pObjectMgr->
		GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());
//	CDListMgr* pDListMgr = pObjectMgr->GetObjectList(m_nActiveTool);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
	int			index;
	////////////////////////////////////
//	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
//	double		dTol		= pHitNet->GetSearchDet(); 
//	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////// Using GangN
	LPOINT3 MouseWIC = GetMouseWIC();
	///
	WICtoWOR(&MouseWIC,&m_wLoc);	
	//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
	index = IsObjectHit(m_nActiveTool,point,0); // first check projected on current View
	//////////////////////////////////////////////////// Create Anyway
	if(index<0)						
		return 0;	
	/////////////////////////////////////////////////////////////// Now, Right One w/ Third Coord
	WORLD wPt;
	WORtoWOP(&m_wLoc,&wPt);	// actually physical (ie bGen = FALSE in CreateNode below)
	///////////////////////////
	CMI_GangN GangN;
//	int nNodeIndex = GangN.CompareNodeCoords(pDListMgr,wPt,bCNode,FALSE,bMNode);
	int nNodeIndex = GangN.CompareNodeCoords(pDListMgr,wPt,bCNode,FALSE);
	/////////////
	if(nNodeIndex>=0)	// already Exist
	{
		pDrNode	= (CDrNode*)pDListMgr->GetObject(nNodeIndex);
		///////
		m_wLoc = *(pDrNode->GetLocalPos());
		//////////////////////////////
		nResult = ShowNodeInfo_SameCoords_NodeContext(pDrNode);
		/////////////
		if(nResult == IDYES)	// Create New Node Anyway
			//////////////////////////////////////////////////////// Create Anyway
			return 0;	
		else
		if(nResult == IDNO)		// Do Not Create New Node
			//////////////////////////////////////////////////////// Cancel
			return -2;
			/////////
	}						// end for loop
	//////////////
	return 0;	// Create Anyway
	/////////
}
	
int CNodMouse::ShowNodeInfo_SameID(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** ERROR: A Node with same ID Exists! *****\n");
	j = ShowNodeInfo(pDrNode, buf, j);
	j += sprintf(buf+j,
		"Please Input a Distinct Node ID");
	////////////////////////////
	nResult = AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
	///////////////
	delete str;
	return nResult;
}

int CNodMouse::ShowNodeInfo_SameCoords_NodeContext(CDrNode* pDrNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	int nResult;
	//////////////////////////////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////
	dTol 	= ((double)(dTol))/dWorldBase*dMapFactor;
	pObjectMgr->DStoSC(&dTol);
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node with same Coords Exists! ****\n");
	j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
	j = ShowNodeInfo(pDrNode, buf, j);
	////////////////////////////
	j += sprintf(buf+j,
		"\n\nYES:\t\tCreate New Node Anyway");
	j += sprintf(buf+j,
		"\nNO:\t\tDo Not Create New Node\n");
	j += sprintf(buf+j,"\n***To set Sievesize, Adjust NetSize in Spec Menu***\n");
	nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}
void CNodMouse::UpdateADlg_TRUE()
{
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	GetNodInDlg()->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_bDirect		= GetNodInDlg()->m_bDirect;	
	m_bDominant		= GetNodInDlg()->m_bDominant;
	m_bIncrement	= GetNodInDlg()->m_bIncrement;
	m_bDirection	= GetNodInDlg()->m_bDirection;
	//////
	m_SpawnedNodeID	= GetNodInDlg()->m_ObjID;
	m_ObjID			= m_SpawnedNodeID;
	//////////////////////////////////
	m_X				= GetNodInDlg()->m_X;
	m_Y				= GetNodInDlg()->m_Y;
	m_Z				= GetNodInDlg()->m_Z;
	m_NID			= m_CurrentNodeID;
	m_dLength		= GetNodInDlg()->m_Z;
	////////////////////////
}			

void CNodMouse::UpdateDlg_TRUE_ADVANCE()
{
	UpdateADlg_TRUE();
	/////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:		// m_RotPt ( Grab Pt.)
			//////////
			m_bDirect	= GetNodInDlg()->m_bDirect;	// both for Translation & Rotation & Reflection
			m_bDominant	= GetNodInDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wRefPt.x	= m_X;
					m_wRefPt.y	= m_Y;
					m_wRefPt.z	= m_Z;		// also for other Coord
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		case 1:		// FromID or Coords for FromPt.			// Angle In or Reference Line 
			m_bDirect		= GetNodInDlg()->m_bDirect;	// 
			m_bDominant		= GetNodInDlg()->m_bDominant;
			m_bIncrement	= GetNodInDlg()->m_bIncrement;	// 
			//////////////
			if(m_bIncrement)						// Increment			
			{
				m_X			= GetNodInDlg()->m_X;
				m_Y			= GetNodInDlg()->m_Y;
				m_Z			= GetNodInDlg()->m_Z;
				/////////////////////////
				m_wInc.x	= m_X;
				m_wInc.y	= m_Y;
				m_wInc.z	= m_Z;		// also for other Coord
				////////
				return;
			}
			else								// Parallel
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wFrom.x = m_X;
					m_wFrom.y = m_Y;
					m_wFrom.z = m_Z;
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		case 2:		// ToID or Coords for ToPt.				// Reference Line
			if(m_bIncrement)
				break;
			//////
			m_bDirect	= GetNodInDlg()->m_bDirect;	// 
			m_bDominant	= GetNodInDlg()->m_bDominant;
			///////
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetNodInDlg()->m_X;
					m_Y = GetNodInDlg()->m_Y;
					m_Z = GetNodInDlg()->m_Z;
					/////////////////////////
					m_wTo.x = m_X;
					m_wTo.y = m_Y;
					m_wTo.z = m_Z;
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetNodInDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		default:
			break;
	}
}

void CNodMouse::UpdateADlg_FALSE()
{
	m_bDlgExpect = FALSE;
	////////////////////////////////////////////////////////////
	//		m_bDirect = FALSE implies m_bDominant = FALSE
	////////////////////////////////////////////////////////////	
	//	if:
	//		1. m_bDirect = TRUE & m_bDominant = FALSE:
	//		/////////////////////////////////////
	//			Node Third Coord from DialogBox
	//			Node Other Two Coord from Mouse Click
	////////////////////////////////////////////////////////////	
	//		2. m_bDirect = TRUE & m_bDominant = TRUE:
	//		/////////////////////////////////////
	//			Node ALL Coord from DialogBox
	////////////////////////////////////////////////////////////
	//		3. m_bDirect = FALSE & m_bDominant = FALSE:
	//		/////////////////////////////////////
	//			Node Obtained from Mouse Search
	////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DIRECT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("");
	GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
	///////
//	GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
	///////
	GetNodInDlg()->GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
	GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
	//////////////////////////////////////////
	if(m_bAdvanced)
	{
		GetNodInDlg()->m_ObjID			= m_ObjID;
		GetNodInDlg()->m_NID			= m_CurrentNodeID;
		GetNodInDlg()->m_X				= m_X;
		GetNodInDlg()->m_Y				= m_Y;
		GetNodInDlg()->m_Z				= m_Z;
		///////////////////
		GetNodInDlg()->GetDlgItem(IDC_DIRECT)->SetWindowText("Direct");
		GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
		GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->SetWindowText("Direction");
		GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(TRUE);
		GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->SetWindowText("Increment");
		GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(TRUE);
		///////////////////
		if(m_nInfoDone>=1)
		{
			GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText("Ref. Node");
		}


		/////////
		if((m_nInfoDone >=3) && m_bDirection)	// for Length Input in Direction
		{
//			GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Length");
			GetNodInDlg()->GetDlgItem(IDC_OTHER)->EnableWindow(TRUE);
			GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("value");
			GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
		}
	}
}

void CNodMouse::UpdateDlg_FALSE_ADVANCE()
{
	///////////////////
	UpdateADlg_FALSE();
	///////////////////
	if(!m_bAdvanced)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	strCurr = "Advanced Node Creation: ";
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:		// Reference Node
			////////////////////////////
			if(GetNodInDlg()->m_bDirect)
			{
				////////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					////////////////////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Reference Node Coords. in Dialog Box";
					///////
					GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Reference Node Coords.";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Reference Node or Control Node";
			break;
		case 1:			// Either Incremental Coord Value (Direct) or Direction Cosine Nodes 	
			//////
			if(GetNodInDlg()->m_bIncrement)	// Incremental
			{
				m_bDirect	= TRUE;
				m_bDominant = TRUE;			// force DialogBox
				GetNodInDlg()->m_bDirect	= m_bDirect;
				GetNodInDlg()->m_bDominant	= m_bDominant;
				////////////////////
				m_bDlgExpect = TRUE;
				///
				GetNodInDlg()->GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
				GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
//				GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
//				GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
				//////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				GetNodInDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText(""); // Grab At
				/////
				strCurr += "TYPE in@Incremental Coords in Dialog Box";
				///////
				GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("values");
				GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("DX");
				GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("DY");
				GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("DZ");
				GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
				GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			}
			else	// Not Direct Coords, So Axis Nodes
			{
				//////////////////
				if(GetNodInDlg()->m_bDirect)
				{
					////////////////////
					GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
					/////
					if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
					{
						m_bDominant = TRUE;
						////////////////////////
						m_bDlgExpect = TRUE;
						////////////////////
						strCurr += "TYPE in@Axis Node_From Coords in Dialog Box";
						///////
						GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
						GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
						GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
						GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
						GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
						GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
					}
					else
					{
						strCurr += "CLICK in@Axis Node_From Coords.";
						///////
						GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
						GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
					}
				}
				else	// Node Input
					strCurr += "CLICK in@Axis_defining Ist Node or CNode";
					///////
			}
			break;
		case 2:
			GetNodInDlg()->GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE); // Now On
			if(m_bIncrement)
			{
				strCurr = "Ready with other Info.?@Click Right Button";
				break;
			}
			//////////////////
			if(GetNodInDlg()->m_bDirect)
			{
				////////////////////
				GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetNodInDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDominant = TRUE;
					m_bDirect	= TRUE;
					////////////////////////
					m_bDlgExpect = TRUE;
					////////////////////
					strCurr += "TYPE in@Axis Node_To Coords in Dialog Box";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					GetNodInDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetNodInDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetNodInDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetNodInDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Axis Node_To Coords.";
					///////
					GetNodInDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetNodInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else	// Node Input
				strCurr += "CLICK in@Axis_defining 2nd Node or CNode";
				///////
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			GetNodInDlg()->GetDlgItem(IDC_DIRECT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
			GetNodInDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(TRUE);
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	GetNodInDlg()->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CNodMouse::LeftUp_GetNode(POINT point, BOOL bCNode)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_Node_Accept(point,bCNode,FALSE);	// FALSE = NOT Parent
	/////////////////////////////////////////////   
	if(nResult>=0)									// Hit(0)
		m_wLoc 	= *(m_pCurrentNode->GetLocalPos());
	else											// (-1)Not Hit or
													// or Cancel(-2)	
	{
		m_pCurrentNode = NULL;
		//////////////////////
		if(m_ProbLim == PDL_TWO) 
			m_ThirdCoord = 0.0;
		////////////////////////
		LPOINT3 MouseWIC;
		//////////
		LPOINT Lpoint;
		Lpoint.x = (long)point.x;
		Lpoint.y = (long)point.y;
		////////////////////
		LOGtoWIC(&MouseWIC,&Lpoint);
		////////
		m_wLoc.x 	= (double)(MouseWIC.x);
		m_wLoc.y 	= (double)(MouseWIC.y);
		m_wLoc.z 	= (double)(MouseWIC.z);
	}
	/////////
	return nResult;	
}

int CNodMouse::LeftUp_GetNode_ADVANCE(POINT point, BOOL bCNode)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	int nResult = LeftUp_GetNode(point, bCNode);
	///////////////////
	if(nResult == -2)
		return nResult; // Cancel
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:
				m_RefPtID	= m_pCurrentNode->GetObjectID();
				m_wRefPt	= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wRefPt,&m_wRefPt);// change to physical like in Dlg Input
				break;
			case 1:
				if(m_bIncrement)
					return -1;
				//////////////
				m_FromID		= m_pCurrentNode->GetObjectID();
				m_wFrom		= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wFrom,&m_wFrom);// change to physical like in Dlg Input
				break;
			case 2:
				if(m_bIncrement)
					return -1;
				//////////////
				m_ToID		= m_pCurrentNode->GetObjectID();
				m_wTo			= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wTo,&m_wTo);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else	// find from Mouse Coord & Third Coord anyway
	if(m_bCorINodeOpDone)
	{
		///////
		switch(m_nInfoDone)
		{
			case 0:
				m_RefPtID	= "";
				m_wRefPt	= m_wLoc;
				WORtoWOP(&m_wRefPt,&m_wRefPt);// change to physical like in Dlg Input
				break;
			case 1:
				m_FromID		= "";
				m_wFrom		= m_wLoc;
				WORtoWOP(&m_wFrom,&m_wFrom);// change to physical like in Dlg Input
				break;
			case 2:
				m_ToID		= "";
				m_wTo			= m_wLoc;
				WORtoWOP(&m_wTo,&m_wTo);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	// NO Hit
	///////////////////////////////////////// From & To Same,INADMISSIBLE
	if(m_nInfoDone == 2)	// To Node
	{
		C3DMath	Math3D;
		///////////////
		if(Math3D.AreSame_WORLD(&m_wFrom,&m_wTo,pHitNet->GetDblRatio()))
   		{
			AfxMessageBox("Degenerate Reference Line:\nSame Node More than Once!");
			m_nInfoDone--;
			return -2;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CNodMouse::LeftUp_ADVANCE_NOD(POINT point)
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bCNode;
	/////////////////////////////////////////////////////////
	int nActiveToolSave = m_nActiveTool;
	////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		bCNode = FALSE;
	else
		bCNode = TRUE;
	///
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	////////////////////////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Ref Node	
			m_bCorINodeOpDone = FALSE;
			//////////////////////
			m_nActiveTool = CNODE;
			if(pWnd->IsMeshMode())
				m_nActiveTool = MCNODE;
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE/MCNODE
			m_nActiveTool = nActiveToolSave;
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			//////////////////////
			m_nActiveTool = INODE;
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
			m_nActiveTool = nActiveToolSave;
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 1://		// From Direction if Not Increment
			if(m_bIncrement)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			//////////////////////
			m_nActiveTool = CNODE;
			if(pWnd->IsMeshMode())
				m_nActiveTool = MCNODE;
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE/MCNODE
			m_nActiveTool = nActiveToolSave;
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			//////////////////////
			m_nActiveTool = INODE;
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
			m_nActiveTool = nActiveToolSave;
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2://		// To Rot Direction
			if(m_bIncrement)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			//////////////////////
			m_nActiveTool = CNODE;
			if(pWnd->IsMeshMode())
				m_nActiveTool = MCNODE;
			nResult = LeftUp_GetNode_ADVANCE(point,TRUE);		// try CNODE/MCNODE
			m_nActiveTool = nActiveToolSave;
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			//////////////////////
			m_nActiveTool = INODE;
			nResult = LeftUp_GetNode_ADVANCE(point,FALSE);		// try INODE
			m_nActiveTool = nActiveToolSave;
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		default:
			break;
	}
	return -1;
}

void CNodMouse::ElementLeftUp_NOD(CPoint point)
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
	BOOL bCNode;
	///////////////////
	switch(m_nActiveTool) 
	{
		
		case INODE:

			bCNode = FALSE;
			if(!m_bAdvanced)
			{
				m_nNodeDone = 0;
				////////////////
				UpdateNDlg_TRUE();
//				LeftUp_NODE(point,FALSE);		// FALSE = Not CNODE
				/////////////////////////////
				if(LeftUp_NODE(point,bCNode)<0)
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
					break;
				}
			}
			else
			{
				if(m_bIncrement)
				{
					if(m_nInfoDone > MAX_INFO_INCREMENT)
						return;
				}
				else
				{
					if(m_nInfoDone > MAX_INFO_DIRECTION)
						return;
				}
				////////////////
				UpdateDlg_TRUE_ADVANCE();
				//////////////////
				if(!(m_bDirect && m_bDominant) )
				{
					if(LeftUp_ADVANCE_NOD(point)<0)
					{
						Terminate_NOD(TRUE);
						return;
					}
				}
				/////////////
				m_nInfoDone++;
				UpdateDlg_FALSE_ADVANCE();
				///////
				return;
			}

				
		case MCNODE:				
		case CNODE:				

				
			bCNode = TRUE;
			if(!m_bAdvanced)
			{
				m_nCNodeDone = 0;
				////////////////
				UpdateNDlg_TRUE();
				/////////////////////////////
				if(LeftUp_NODE(point,bCNode)<0)
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
					break;
				}
			}
			else
			{
				if(m_bIncrement)
				{
					if(m_nInfoDone > MAX_INFO_INCREMENT)
						return;
				}
				else
				{
					if(m_nInfoDone > MAX_INFO_DIRECTION)
						return;
				}
				////////////////
				UpdateDlg_TRUE_ADVANCE();
				//////////////////
				if(!(m_bDirect && m_bDominant) )
				{
					if(LeftUp_ADVANCE_NOD(point)<0)
					{
						Terminate_NOD(TRUE);
						return;
					}
				}
				/////////////
				m_nInfoDone++;
				UpdateDlg_FALSE_ADVANCE();
				///////
				return;
			}
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld	= m_CurrentNodeID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= bCNode;
	/////////////
	pObjectMgr->SetNodeInfoID(m_CurrentNodeID,bCNode,(UINT)m_nActiveTool);		
	////////////
	m_SpawnedNodeID = m_CurrentNodeID; 
	m_ObjID			= m_SpawnedNodeID;
	///////////////////
	UpdateNDlg_FALSE();
	////////////
	return;
}	

int CNodMouse::LeftUp_Node_Accept(CPoint point,BOOL bCNode,BOOL bParent)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr = pObjectMgr->
		GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());
//	CDListMgr* pDListMgr = pObjectMgr->GetObjectList(m_nActiveTool);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
	index = IsObjectHit(m_nActiveTool,point,0);
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		pObjectMgr->ShowObject_On_Off(pDrNode,m_nActiveTool,TRUE);
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
				nResult = ShowNotParentNodeInfo(pDrNode);
				/////////////
				if(nResult == IDYES)
					//////////////////////////////////////////////////////// Accept Old
					break;
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					index = IsObjectHit(m_nActiveTool,point,startIndex);
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						pObjectMgr->ShowObject_On_Off(pDrNode,m_nActiveTool,TRUE);
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
		return -1;	// Not Hit
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentNode = pDrNode;
	/////////
	return 0;
	/////////
}

int CNodMouse::ShowNotParentNodeInfo(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node Hit ****\n");
	j = ShowNodeInfo(pDrNode, buf, j);
	////////////////////////////
	j += sprintf(buf+j,
		"\n\nYES:\t\tAccept This Node");
	//////////////////////////
	if(m_ProbLim == PDL_TWO)
	{
		j += sprintf(buf+j,
			"\nNO:\t\tCancel Selection Process");
		nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		////////////////////
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
	///////////////
	delete str;
	return nResult;
}

void CNodMouse::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{  
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CMouseMgr*	pMouseMgr	= pWnd->GetMouseMgr(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		drad		= pHitNet->GetSearchDet();
	///
	drad 	= ((double)(drad))/dWorldBase;
	pObjectMgr->DStoSC(&drad);
	///
	int			rad = (int)drad;	// in Pixels now 
	/////////////////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////// LOG: Log/DEScaled
   	m_pdc->DPtoLP(&point);     
	LPOINT LpLOG;
	LpLOG.x = (long)point.x;
	LpLOG.y = (long)point.y;
   	m_pdc->LPtoDP(&point);     
    /////////////////////////////////////////////
    if(!m_bDragging)  // not currently dragging 
    {
/*		
 
   	//////////////////////////////      ***** START FROM HERE *****
   	CPen    Pen;
	CPen*   PtrOldPen;
	//////////////////////////////
	m_pdc->SetBkMode(TRANSPARENT);
	//////////////////////////////	
	// Create Black Pen 1 Pixel wide;
	int one = 2;
	COLORREF crColor = RGB(255,255,0); 
	CBrush* pOldBr;
	pOldBr = (CBrush*)(m_pdc->SelectStockObject(HOLLOW_BRUSH));
	Pen.CreatePen ((int)PS_SOLID,one,crColor);
	PtrOldPen = m_pdc->SelectObject(&Pen);
	///////////////////////////
	m_MouseLOG = point;              // Device
	POINT MouseLOC;
	/////////////////////////	
	m_pdc->SetROP2 (R2_NOT); 
	
	MouseLOC = m_MouseOldLOG;        // Device
	m_pdc->DPtoLP(&MouseLOC);
	///
	CRect Rect;
	Rect.left = MouseLOC.x - rad;
	Rect.right = MouseLOC.x + rad;
	Rect.top = MouseLOC.y + rad;
	Rect.bottom = MouseLOC.y - rad;
	Rect.NormalizeRect();
	//
	m_pdc->Ellipse (&Rect);
	////////////////////////	  
//	m_pdc->SetROP2 (R2_COPYPEN);

	MouseLOC = m_MouseLOG;      // Device
	m_pdc->DPtoLP(&MouseLOC);
	///
	Rect.left = MouseLOC.x - rad;
	Rect.right = MouseLOC.x + rad;
	Rect.top = MouseLOC.y + rad;
	Rect.bottom = MouseLOC.y - rad;
	Rect.NormalizeRect();
	//
	m_pdc->Ellipse (&Rect);
	///////////////////////
	m_MouseOldLOG = m_MouseLOG;
	///////////////////////////
   	m_pdc->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
   	m_pdc->SelectObject(pOldBr);   
	//////////////////////////////////////
*/
		//////////////////////////////////////
//090998		LPOINT3 MouseOldTempWIC = GetMouseOldWIC();
//090998	    LPOINT3 MouseTempWIC 	= GetMouseWIC();
   		SetMouseOldWIC(GetMouseWIC());
   		LPOINT3 MouseWIC;
    	///////////////////////  LOG :DEScaled
//090998    	LOGtoWIC2(&MouseWIC,&LpLOG,&MouseTempWIC); //LOG/Scaled WIC
    	LOGtoWIC(&MouseWIC,&LpLOG); //LOG/Scaled WIC
    	////////////////////                 
    	SetMouseWIC(MouseWIC);
    	///////////////////////////
//    	pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
		pMouseMgr->SetStatusMouseWIC(MouseWIC);
		////////////////////////////
		///////////////////// recover MouseWIC changed for statusbar update 
//090998	    SetMouseOldWIC(MouseOldTempWIC);
//090998	    SetMouseWIC(MouseTempWIC);

		return;
    }	
   	//////////////////////////////      ***** START FROM HERE *****
   	CPen    Pen;
	CPen*   PtrOldPen;
	//////////////////////////////
	m_pdc->SetBkMode(TRANSPARENT);
	//////////////////////////////	
	// Create Black Pen 1 Pixel wide;
	int one = 2;
	COLORREF crColor = RGB(0,0,0);  
	Pen.CreatePen ((int)PS_SOLID,one,crColor);
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

void CNodMouse::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_NOD(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CNodMouse::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////
//	CMNodMgr* pMNodMgr;
	//////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		case INODE:
			break;
		case CNODE:
			break;
		////////////////////////////////////////////////// 
		default:
			break;
	}  
}

int CNodMouse::RightUp_Premature()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////// 
	int		nAnswer = IDOK;
	BOOL	bPreMature = FALSE;
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	
	if(m_bIncrement && m_nInfoDone<MAX_INFO_INCREMENT)
		bPreMature = TRUE;
	if(!m_bIncrement && m_nInfoDone<MAX_INFO_DIRECTION)
		bPreMature = TRUE;
	//////////////// PreMature
	if(bPreMature)
		return -1;
	////////
	return 0;
}	

int CNodMouse::ShowInputInfo_NOD()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Node Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Node ID = %s\n\n",m_ObjID); // 
	/////////////////////////////////////
	if(m_RefPtID !="")
		j += sprintf( buf + j, "\n\nReference Node ID = %s\n",m_RefPtID); // Ref Node
	else
		j += sprintf( buf + j, "\n\nReference Coords:\n");
	//
	j += sprintf( buf + j, "\n\tX\t= %f",m_wRefPt.x);
	j += sprintf( buf + j, "\n\tY\t= %f",m_wRefPt.y);
	j += sprintf( buf + j, "\n\tZ\t= %f",m_wRefPt.z);
	////
	if(m_bIncrement)
	{
		j += sprintf( buf + j, "\n\nIncrements:\n"); // 
		j += sprintf( buf + j, "\n\tX\t= %f",m_wInc.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wInc.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wInc.z);
	}
	else
	{
		//////////////////////////////////////////////////////////// Reference Line
		if(m_FromID != "")
			j += sprintf( buf + j, "\n\nAxis_From Node ID = %s\n",m_FromID); // 
		else
			j += sprintf( buf + j, "\n\nAxis_From Coords:\n");
		//
		j += sprintf( buf + j, "\n\tX\t= %f",m_wFrom.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wFrom.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wFrom.z);
		///
		if(m_ToID != "")
			j += sprintf( buf + j, "\n\nAxis_To Node ID = %s\n",m_ToID); // 
		else
			j += sprintf( buf + j, "\n\nAxis_To Coords:\n");
		//
		j += sprintf( buf + j, "\n\tX\t= %f",m_wTo.x);
		j += sprintf( buf + j, "\n\tY\t= %f",m_wTo.y);
		j += sprintf( buf + j, "\n\tZ\t= %f",m_wTo.z);
		///////////////////////////////////////////////////////////////////// Length
		j += sprintf( buf + j, "\n\tLength  = %f",m_dLength);
	}
	///////////////////////////////////////////////////////////////////// Final Coords
	j += sprintf( buf + j, "\n\nFinal Coords: \n"); // 
	//
	j += sprintf( buf + j, "\n\tX\t= %f",m_wFin.x);
	j += sprintf( buf + j, "\n\tY\t= %f",m_wFin.y);
	j += sprintf( buf + j, "\n\tZ\t= %f",m_wFin.z);
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

int CNodMouse::ShowNodeInfo(CDrNode* pDrNode, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	ID = pDrNode->GetObjectID();
	//////////////////////////////
	int j = jStart;
	/////////////////////////////// Coords
	WORLD Loc = *(pDrNode->GetLocalPos());
	WORtoWOP(&Loc,&Loc);	// to Physical
	//////////////////////////////
	j += sprintf(buf+j,
		"\nExisting NodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
				ID,Loc.x,Loc.y,Loc.z);
	///
	if(pDrNode->IsControlNode())
		j += sprintf(buf+j,"\n\t**** This is a Control Node ****\n");
	else
		j += sprintf(buf+j,"\n\t**** This is an Input Node ****\n");
	/////////
	return j;
}

int CNodMouse::ResolveReference_Direction()
{
	///////////////////////////////////////////
	WORLD Axis;
	int nResult = UnitAxisFromEndNodes(&Axis);
	if(nResult<0)
		return -1;
	///////////////////////////////////////////
	m_wFin.x = m_wRefPt.x + m_dLength * Axis.x;
	m_wFin.y = m_wRefPt.y + m_dLength * Axis.y;
	m_wFin.z = m_wRefPt.z + m_dLength * Axis.z;
	/////////
	return 0;
}

int CNodMouse::ResolveReference_Coords()
{
	///////////////////////////////////////////
	m_wFin.x = m_wRefPt.x + m_wInc.x;
	m_wFin.y = m_wRefPt.y + m_wInc.y;
	m_wFin.z = m_wRefPt.z + m_wInc.z;
	/////////
	return 0;
}

int CNodMouse::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&m_wTo, &m_wFrom, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return 0;
}

int CNodMouse::RightUp_NotAutoAccept()
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
*/
	int nAnswer;
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		nAnswer = ShowInputInfo_NOD();
		if(nAnswer<0)
			return -1;
		//////////////
		if(nAnswer == IDCANCEL)
		{
			CString* str = new CString;
			char* buf	= str->GetBuffer(BUFF_SIZE);
			sprintf(buf,"Do You Want to Delete\nCurrent Node %s to Start Allover");
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

void CNodMouse::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	if(!m_bAdvanced)
		return;
	////////////////
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		m_bCNode = FALSE;
	else
		m_bCNode = TRUE;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Update Info
	UpdateADlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	if(m_bIncrement)
		ResolveReference_Coords();
	else
		ResolveReference_Direction();
	/////////////////////////////////
	if(RightUp_NotAutoAccept()<0)
	{
		Terminate_NOD(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	int nAnyway	= -12345;	// Create Anyway
	////////////////////////////////////////
	LPOINT3 MouseWIC;
	WOPtoWIC(&MouseWIC,&m_wFin);
	SetMouseWIC(MouseWIC);
	////////////////////////////////////////
	switch(m_nActiveTool) 
	{

		case INODE:
						
	
			/////////////////////////////
			if(ShowNode(&m_ObjID,FALSE,nAnyway)<0)
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
				UpdateADlg_FALSE();
				break;
			}
			///////////////////	
			break;


		case MCNODE:
		case CNODE:
						
			
			/////////////////////////////
			if(ShowNode(&m_ObjID,TRUE,nAnyway)<0)
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
				UpdateADlg_FALSE();
				break;
			}
			///////////////////	
			break;

			
		
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	////////////////////////// Set NodeID
	m_CurrentNodeIDOld	= m_ObjID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	m_bAnchorCNode		= m_bCNode;
	/////////////
	pObjectMgr->SetNodeInfoID(m_CurrentNodeID,m_bCNode,(UINT)m_nActiveTool);		
	////////////
	m_SpawnedNodeID = m_CurrentNodeID; 
	//////////////////////////
	m_ObjID = m_SpawnedNodeID; 
	///////////////////////////////////////////////////////////// Advanced Option
	GetNodInDlg()->GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
	//////////////////////////
	UpdateADlg_FALSE();
	GetNodInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////////////////////////////////
	strCur = "Ready for Another Node Creation. CLICK ON@";
	strCur += "A Reference Node or Control Node";
	///
	pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);
	////////////
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CNodMouse::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID == NODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Creation@";
	else
	if(IGenID == INODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Input Node Creation@";
	else
	if(IGenID == CNODE || IGenID == MCNODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Control Node Creation@";
	else
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Create
		case COP_CREATE:
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

//					pWnd->SetMouseBoxType(ELEMDIMBOX);
					str = "ELEMENT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// EDim0/EDim1...
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID	= NODE;
								strCur += "Select Node Type";	break;
						case INODE:			str = "Input@NODE";		ID	= INODE;
								strCur += "Click in an Input Node";	break;
						case CNODE:			str = "Control@NODE";	ID = CNODE;
								strCur += "Click in a Control Node";	break;
//092798						case MCNODE:		str = "Control@NODE";	ID = MCNODE;
//								strCur += "Click in a Control Node";	break;
						default:			str = "UNKNOWN@NODE";	ID = UNONE;
					}
					pWnd->SetstrIGenID(str);
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
				//////////////////
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
}
	
void CNodMouse::ModeLessOff_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetNodInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_NODIN,IDOK);
}

void CNodMouse::ModeLessOn_NOD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	if((m_nActiveTool == INODE) ||(m_nActiveTool == CNODE) ||(m_nActiveTool == MCNODE))
	{
//		if(!(GetNodInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_NODIN,IDOK);
	}
}

long CNodMouse::CreateorActivateNodIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
//	CString strCurr;
	/////////////////////////////////////////////////////////
	if(	(pWnd->GetCurrentIGenID() != INODE) && (pWnd->GetCurrentIGenID() != CNODE)
											&& (pWnd->GetCurrentIGenID() != MCNODE) )
		return 0L;
	////////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
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
//		m_uCurrentProcessType = ;
//		pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
		////////
		UINT nType = pWnd->GetCurrentIGenID();
		if(nType == CNODE || nType == MCNODE)
			m_bAnchorCNode	= TRUE;
		else
			m_bAnchorCNode	= FALSE;
		////////////
		pObjectMgr->SetNodeInfoID(m_CurrentNodeID,m_bAnchorCNode,nType);
		////
	}
	else
	{
		GetNodInDlg()->SetActiveWindow();
		/////////////////////////////////
		Terminate_NOD(FALSE);
		Init_NOD();
		////////////////////////////////////// override
		UINT nObjType = pWnd->GetCurrentIGenID();
		if(nObjType == CNODE || nObjType == MCNODE)
			m_bAnchorCNode	= TRUE;
		else
			m_bAnchorCNode	= FALSE;
		/////////////////////////////
		char buf[50];
		int nLastNum;
		nLastNum	= pObjectMgr->GetLastInputNo(nObjType);		// internal
		sprintf(buf,"%d",nLastNum);
		///////////////
		m_CurrentNodeID	= "";
		if(nObjType == CNODE)
			m_CurrentNodeID = "CN_";
		else
		if(nObjType == MCNODE)
			m_CurrentNodeID = "MC_";
		m_CurrentNodeID	+= buf;
		///////////////////
		UpdateNDlg_FALSE();
		///////////////////
	}
	/////////////////////////////////////////////////////////////////
//	CDListMgr* pDListMgr;
	/////////////
	m_CurrentNodeIDOld	= m_CurrentNodeID;
	m_AnchorNodeID		= m_CurrentNodeIDOld;
	/////////////////////////////////////////
	UpdateADlg_FALSE();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(GetNodInDlg()->m_hWnd)
	{
		ResetVuBasedVars_NodDlg();
		GetNodInDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetNodInDlg()->m_ObjID		= GetCurrentNodeID();
//	GetNodInDlg()->m_SID		= GetCurrentSupID();
	GetNodInDlg()->m_nViewNum	= pWnd->GetActiveViewNumber();
	GetNodInDlg()->m_bnid_C		= FALSE;
//	GetNodInDlg()->m_dCoord		= GetCurrentThirdCoord();
	GetNodInDlg()->m_Z			= GetCurrentThirdCoord();
	////////////////////////////////
	GetNodInDlg()->UpdateData(FALSE);
	////////////////////////////////
	return 0L;

}
 
void CNodMouse::ResetVuBasedVars_NodDlg()
{
	////////////////////////////////////////////////////////////////// Set Info
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(GetNodInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetNodInDlg()->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		SwitchThirdCoordHeading(pCtl,
			(UINT)(pWnd->GetActiveViewNumber()) );
	}
}
	 
long CNodMouse::CancelNodIn(UINT wParam, long lParam)
{
	
	GetNodInDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodMouse::GoodByeNodIn(UINT wParam, long lParam)
{
	
	GetNodInDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodMouse::UpdateNodIn(UINT wParam, long lParam)
{

	BOOL bAdvancedOld	= m_bAdvanced;
	GetNodInDlg()->UpdateData(TRUE);
	m_bAdvanced = GetNodInDlg()->m_bAdvanced;
	/////////////////////////////////////////////////////////////
	if(!m_bAdvanced)
	{
		GetNodInDlg()->UpdateData(TRUE);
		///////////////////////////////// Reset data in ElMouse
		SetCurrentNodeID(GetNodInDlg()->m_ObjID);
		LPOINT3 MouseWIC = GetNodInDlg()->m_MouseWIC; 
		SetMouseWIC(MouseWIC);
		///////////////////////////////////////
		SetCurrentThirdCoord(GetNodInDlg()->m_dCoord);
		if(bAdvancedOld)
			///////////////////
			UpdateNDlg_FALSE();
			//////////
		return 0L;
	}
	///////////////////////////////////////////////////////////// Advanced Option
	GetNodInDlg()->GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
	////////////////////
	if(m_nInfoDone == 0)
		Init_NOD();
	/////////////////////////
	UpdateDlg_TRUE_ADVANCE();
	///////////////////////// 
	if(m_bDlgExpect)
		m_nInfoDone++;
	//////////////////////////
	UpdateDlg_FALSE_ADVANCE();
	//////////
	return 0L;
}
	
void CNodMouse::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE bDialogOn,bElementMode,bDragOn,bDragging,bRefreshOn; 
	WORD nActiveObject,nActiveTool,nNodeDone;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodMouse:    Storing\n");	
		
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
		TRACE(" NodMouse:    Loading\n");	

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
	//////////////////
}

///////////////////////////////////////////////////////// element serializer
void CNodMouse::SerializeNode(CArchive& ar)
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
///////////////////////////////////// end of Module //////////////////////		
/*	
	///////////////////////////////////////////////////////////TEMPORARY
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
    /////////////////////////////////////////////////////////////////////
	CMNodMgr* pMNodMgr;
	CString nID;
	pMNodMgr->DoModal_Node(m_nView,&MouseWIC,&nID);
	pMNodMgr->DoModal_Pipe();
	/////////////////////////
	CDDlgMgr* pDDlgMgr;
	pDDlgMgr->DoModal_Label_Insert();
	pDDlgMgr->DoModal_Label_Edit();
	/////////////////////////////////////////////////////////////////////
*/


