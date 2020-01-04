// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h>
#include <float.h>		// DBL_MIN

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "Def_IGen.h"                    
#include "Def_Elem.h"                    
///////////////////// dialogMgr
#include "MNodMgr.h"  
////////////////////// 
#include "MI_GangN.h" 
#include "MI_NSPN.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "NodCreOp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// if NODE_SPAWN: Object Grab Node Same As Node
//////////////////////////////////////////////
#define MAX_INFO_XLATE		3	// 1 Object/1 Object Grab Node/2 Nodes( for direction)        
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CNodCreOp,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CNodCreOp::CNodCreOp()
{
	m_bCorINodeOpDone	= FALSE;
	m_bCNode			= FALSE;
	////////
	m_bDoModalDone		= FALSE;
	///////////////////////////////////////////////
	m_bDragging			= FALSE;
	///////////////////////////////////////////// 
	m_pCreOpDlg			= NULL;
}

CNodCreOp::~CNodCreOp()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pCreOpDlg->m_hWnd)
		m_pCreOpDlg->DestroyWindow();
	///////////////////
	delete m_pCreOpDlg; 
	///////////////////
}

void CNodCreOp::Init_NOD()
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
	/////////////////////////////
	char buf[50];
	if(m_bCNode)
	{
		pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedID	= "CN_";
		m_SpawnedID	+= buf;
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedID	= "";
		m_SpawnedID	+= buf;
	}
	/////////////////////////////////////////// Node
	m_pParentNode		= NULL;
	m_ParentID			= "";
	m_pSpawnedNode		= NULL;
	m_pCurrentNode		= NULL;
	m_CurrentNodeID		= "";
	Math3D.Set3DPts(&m_wLoc,0.0,0.0,0.0);
	//////////
	m_bDone				= TRUE;;		// for dragging
	m_nInfoDone			= 0;
	/////////////////////////////////////////// Dlg_CrOI 
	m_ObjID			= m_SpawnedID;
	m_X				= m_wLoc.x;
	m_Y				= m_wLoc.y;
	m_Z				= m_wLoc.z;
	m_NID			= m_CurrentNodeID;
	m_bDirect		= FALSE;		// Forcing Mouse Search of Node	
	m_bDominant		= FALSE;
	m_bAngleIn		= FALSE;
	/////////////////////////////////////////// Spawning Info.
	///////////////////////////////// XLate
	m_bCoordIn		= FALSE;
	m_TranPtID		= "";
	Math3D.Set3DPts(&m_wTranPt,0.0,0.0,0.0);
	Math3D.Set3DPts(&m_wTran,0.0,0.0,0.0);
/*
	m_FromID		= "";
	Math3D.Set3DPts(&m_wFrom,0.0,0.0,0.0);
	m_ToID			= "";
	Math3D.Set3DPts(&m_wTo,0.0,0.0,0.0);
*/
}

void CNodCreOp::Terminate_NOD(BOOL bError)
{
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pSpawnedNode)
		{
			delete m_pSpawnedNode;
			m_pSpawnedNode = NULL;
		}
	}
	/////////////
	if(m_pMatObj)
	{
		delete m_pMatObj;
		m_pMatObj = NULL;
	}
	///////////////////////////
}

void CNodCreOp::InitDlgIn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pCreOpDlg		= new CDlg_CrOI(pWnd);
	/////////////////////////////////////////////////////////////////// Init
}
	
int CNodCreOp::LeftDown_NODE()
{
	return 0;
}
	
void CNodCreOp::SizeRectDlgIn(CRect& BoxRect)
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

void CNodCreOp:: ElementLeftDown_NOD()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType;
	////////////////////////
	m_bDone	= FALSE;
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// PATCH
		case COP_TRANSLATE:				// 

			m_CreOp = COP_TRANSLATE;
			LeftDown_NODE();
			return;
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

void CNodCreOp::OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(m_bDone)			// Reset
		m_nInfoDone		= 0;
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// No Node
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	else
	if(pWnd->GetCurrentIGenID() == CNODE)
		pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	///
	if(pDListMgr->GetCount()<=0)
		return;
	/////////////////////////////////////////////////////////////////
    if(m_Gener == FORWARD)
		ElementLeftDown_NOD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CNodCreOp::UpdateDlg_TRUE()
{
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	m_pCreOpDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_bDirect	= GetCreOpDlg()->m_bDirect;	
	m_bDominant = GetCreOpDlg()->m_bDominant;
	m_bAngleIn	= GetCreOpDlg()->m_bAngleIn;
	m_bOrigin	= GetCreOpDlg()->m_bDirCos;
	//////
	m_SpawnedID	= GetCreOpDlg()->m_ObjID;
	m_ObjID		= m_SpawnedID;
	m_X			= GetCreOpDlg()->m_X;
	m_Y			= GetCreOpDlg()->m_Y;
	m_Z			= GetCreOpDlg()->m_Z;
	m_NID		= m_CurrentNodeID;
	////////////////////////
}			

void CNodCreOp::UpdateDlg_TRUE_XLATE()
{
	UpdateDlg_TRUE();
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	if(m_CreOp != COP_TRANSLATE)
		return;
	////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:			// pick up TargetNode
			m_XfType	= XT_XFORMS;
			m_bNoTran	= FALSE;
			////////////////////
			break;
		case 1:		// m_RotPt ( Grab Pt.)
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// both for Translation & Rotation & Reflection
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wTranPt.x	= m_X;
					m_wTranPt.y	= m_Y;
					m_wTranPt.z	= m_Z;		// also for other Coord
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetCreOpDlg()->m_Z;
					m_ThirdCoord	= m_Z;
				}
			}
			else
				;// Hit Node; 
			break;
		case 2:
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			m_bCoordIn	= m_bDirect;	// 
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X			= GetCreOpDlg()->m_X;
					m_Y			= GetCreOpDlg()->m_Y;
					m_Z			= GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wTran.x	= m_X;
					m_wTran.y	= m_Y;
					m_wTran.z	= m_Z;
				}
				else
				{
					// Need Clicking Pt. for x & y
					m_Z				= GetCreOpDlg()->m_Z;
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


void CNodCreOp::UpdateDlg_FALSE()
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
	//////////////////////////////////////////
	if(m_nInfoDone <= 0)
	{
		GetCreOpDlg()->m_bDirect	= m_bDirect;
		GetCreOpDlg()->m_bDominant	= m_bDominant;
		GetCreOpDlg()->m_bAngleIn	= m_bAngleIn;
		GetCreOpDlg()->m_bDirCos	= m_bOrigin;
	}
	GetCreOpDlg()->m_CreOp		= m_CreOp;
	GetCreOpDlg()->m_ObjID		= m_SpawnedID;
	GetCreOpDlg()->m_NID		= m_CurrentNodeID;
	GetCreOpDlg()->m_X			= m_X;
	GetCreOpDlg()->m_Y			= m_Y;
	GetCreOpDlg()->m_Z			= m_Z;
	////////////////////////////////////////////////////////////
	GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
	//////////////////////////////////////
	if(m_nInfoDone>=1)
	{
//		GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
		GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->SetWindowText("Direct");
		GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(TRUE);
		GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
		GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
	}
}

void CNodCreOp::UpdateDlg_FALSE_0()
{
	///////////////////
	UpdateDlg_FALSE();
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_CreOp)
	{
		case COP_TRANSLATE:
			strCurr = "Spawn by Translation: Click On@A " + m_strParentType + " To Translate";
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	m_pCreOpDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CNodCreOp::UpdateDlg_FALSE_XLATE()
{
	if(m_CreOp != COP_TRANSLATE)
		return;
	///////////////////
	UpdateDlg_FALSE();
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	if(m_nInfoDone == 0)
		UpdateDlg_FALSE_0();
	else
		strCurr = "Spawn by Translation: ";
	///////////////////
	switch(m_nInfoDone)
	{
		case 1:		// Grab Node	NOT NEEDED FOR NODE:It is here for copy to CURVE
					//				and PATCH and SOLID
			//////
			if(GetCreOpDlg()->m_bDirect)
			{
				////////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Translate_Grab Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Translate_Grab Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Translate_Grab Node";
			break;
		case 2:			// Translation Values
			//////
			if(GetCreOpDlg()->m_bDirect)
			{
				m_bCoordIn	= TRUE;
				////////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "Type in@Translate_To Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "Click in@Translate_To Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "Click On@ A Translate_To Node";
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
			GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
			GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(TRUE);
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	m_pCreOpDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CNodCreOp::LeftUp_GetNode(POINT point, BOOL bCNode)
{
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_nInfoDone == 0)
		nResult = LeftUp_Node_Accept(point,bCNode,TRUE);	// TRUE = Parent
	else
		nResult = LeftUp_Node_Accept(point,bCNode,FALSE);	// FALSE = NOT Parent
	/////////////////////////////////////////////   
	if(nResult>=0)									// Hit(0)
		m_wLoc 	= *(m_pCurrentNode->GetLocalPos());
	else											// Not Hit(-1) or Cancel(-2)	
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

int CNodCreOp::LeftUp_GetNode_Parent(POINT point, BOOL bCNode)
{
	int nResult = LeftUp_GetNode(point, bCNode);
	///////////////////
	if(nResult == -2)
		return nResult; // Cancel
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 0:	// 
				m_pParentNode	= m_pCurrentNode;
				m_ParentID		= m_pParentNode->GetObjectID();
				break;
			default:
				return -1;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CNodCreOp::LeftUp_GetNode_XLATE(POINT point, BOOL bCNode)
{
	int nResult = LeftUp_GetNode(point, bCNode);
	///////////////////
	if(nResult == -2)
		return nResult; // Cancel
	///////
	if(nResult>=0)	// Hit
	{
		switch(m_nInfoDone)
		{
			case 1:	// Grab Node
				m_TranPtID		= m_pCurrentNode->GetObjectID();
				m_wTranPt		= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wTranPt,&m_wTranPt);// change to physical like in Dlg Input

				break;
			case 2:	// To Node
				m_ToID_R		= m_pCurrentNode->GetObjectID();
				m_wTo_R			= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wTo_R,&m_wTo_R);// change to physical like in Dlg Input
				/////////////////////////
				m_wTran		= m_wTo_R;
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
			case 0:	// 
				return -1;
			case 1:
				m_TranPtID	= "";
				m_wTranPt	= m_wLoc;
				WORtoWOP(&m_wTranPt,&m_wTranPt);// change to physical like in Dlg Input
				break;
			case 2:
				m_ToID_R	= "";
				m_wTo_R		= m_wLoc;
				WORtoWOP(&m_wTo_R,&m_wTo_R);// change to physical like in Dlg Input
				/////////////////////////
				m_wTran		= m_wTo_R;
				break;
			default:
				return -1;
		}
	}
	else
		return nResult; // NO Hit
	//////////////////////////////////////
	return 0;
}

int CNodCreOp::LeftUp_TRANSLATE_NOD(POINT point)
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bCNode;
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		bCNode = FALSE;
	else
		bCNode = TRUE;
	///
//	if(m_bDirect && m_bDominant)
//		return -1;	// Should Not be Here
	///////////////////
	int nResult;
	switch(m_nInfoDone)
	{
		case 0://	Parent Node
			nResult = LeftUp_GetNode_Parent(point,bCNode);
			return nResult;
			
		case 1://	Grab Node	
		case 2://	To Node
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_XLATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_XLATE(point,FALSE);	// try INODE
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

void CNodCreOp::ElementLeftUp_NOD(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	///////////////////
	switch(m_nActiveTool) 
	{
		///////////////////////////////////////////////////// Patches Insert
		case COP_TRANSLATE:

			if(m_nInfoDone > MAX_INFO_XLATE)
				return;
			////////////////
			UpdateDlg_TRUE_XLATE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_TRANSLATE_NOD(point)<0)
				{
					Terminate_NOD(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_XLATE();
			///////
			return;

		//////////////////////////////////////////////////
		default:  
			return;
	} 
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	j = sprintf(buf,"***** Please Note ****\n");
	j += sprintf(buf+j,"\nIf you are trying to Hit a Node or\n");
	j += sprintf(buf+j,"\nClick in for Coordinates, Please UnCheck\n");
	j += sprintf(buf+j,"\nthe Dominant Button in the Dialog Box\n");
	//////
	AfxMessageBox(*str);
	delete str;
	///////////
	m_nInfoDone--;
}	

int CNodCreOp::LeftUp_Node_Accept(CPoint point,BOOL bCNode,BOOL bParent)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	if(bCNode)
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	else
		pDListMgr	= pObjectMgr->GetObjectList(NODE);
	///
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
	//////////////////////////////////////////////////// Check if CorrectType Node/CNode/MNode
	WORLD		wLoc;
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_ProbLim == PDL_TWO)
	{		
		if(bCNode)
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(NODE,point,0);
	}
	else
	if(m_ProbLim == PDL_THREE)
	{
		LPOINT3 MouseWIC;
		//////////
	    LPOINT Lpoint;
	    Lpoint.x = (long)point.x;
	    Lpoint.y = (long)point.y;
	    ////////////////////
	    LOGtoWIC(&MouseWIC,&Lpoint);
		////////
   		wLoc.x 	= (double)(MouseWIC.x);
   		wLoc.y 	= (double)(MouseWIC.y);
   		wLoc.z 	= (double)(MouseWIC.z);
		////////////////
		if(bCNode)
			index = IsObjectHit(CNODE,&wLoc,0);
		else
			index = IsObjectHit(NODE,&wLoc,0);
		///
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
		{
			pList = pObjectMgr->GetObjectList(CNODE);
			nActiveIndex = pList->GetObjectIndex(CNODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
		}
		else
		{
			pList = pObjectMgr->GetObjectList(NODE);
			nActiveIndex = pList->GetObjectIndex(NODE, ID);
			pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
			pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
			pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
		}
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
				if(bParent)
					nResult = ShowParentNodeInfo(pDrNode);
				else
					nResult = ShowNotParentNodeInfo(pDrNode);
				/////////////
				if(nResult == IDYES)
					//////////////////////////////////////////////////////// Accept Old
					break;
				else
				if(nResult == IDNO)
				{
					//////////////////////////////////////////////////////// Retry
					if(m_ProbLim == PDL_TWO)
					{		
						if(bCNode)
							index = IsObjectHit(CNODE,point,0);
						else
							index = IsObjectHit(NODE,point,0);
					}
					else
					if(m_ProbLim == PDL_THREE)
					{
						////////////////
						if(bCNode)
							index = IsObjectHit(CNODE,&wLoc,0);
						else
							index = IsObjectHit(NODE,&wLoc,0);
						///
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
						if(bCNode)
						{
							pList = pObjectMgr->GetObjectList(CNODE);
							nActiveIndex = pList->GetObjectIndex(CNODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
						}
						else
						{
							pList = pObjectMgr->GetObjectList(NODE);
							nActiveIndex = pList->GetObjectIndex(NODE, ID);
							pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
							pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
							pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
						}
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

int CNodCreOp::ShowNodeInfo(CDrNode* pDrNode, char* buf, int jStart)
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
		j += sprintf(buf+j,"\nThis is a Control Node\n");
	else
		j += sprintf(buf+j,"\nThis is an Input Node\n");
	/////////
	return j;
}
	
int CNodCreOp::ShowParentNodeInfo(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node_To_Spawn Hit ****\n");
	j = ShowNodeInfo(pDrNode, buf, j);
	////////////////////////////
	j += sprintf(buf+j,
		"\n\nYES:\t\tSpawn This Node");
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
	
int CNodCreOp::ShowNotParentNodeInfo(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	j = sprintf(buf,"***** A Node_To_Spawn Hit ****\n");
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

int CNodCreOp::LeftUp_NSPAWN(CPoint point)
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bCNode;
	CString strCurr;
	/////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		bCNode = FALSE;
	else
		bCNode = TRUE;
	///
	int nResult;
	////////////
	nResult = LeftUp_GetNode_Parent(point,bCNode);
	///
	if(nResult<0)
		return nResult;
	////////////////////////////////////////
	nResult = ShowNodeToSpawn(m_pParentNode,TRUE); // TRUE = With Dlg
	///////////
	if( nResult == -1)		// 
	{
		AfxMessageBox("ERROR:\nCCurMouse::LeftUp_NSpawn\nShowNodeToSpawn Problem");
		return -1;
	}
	////////////////////////////
	strCurr = "Ready for Spawning a Node@";
	strCurr += "Click on a NODE to Spawn";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////
	if(nResult == -2)		// Cancel
		return -2;
	///
	return 0;
}

int CNodCreOp::ShowNodeToSpawn(CDrNode* pParentNode,BOOL bUsingDlg)
{
	C3DMath			Math3D;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pList;
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);
	/////////////////////////////////////////////////////////////// Using CMI_NSPN
	CDrNode SpawnedNode;
	CDrNode* pSpawnedNode = &SpawnedNode;
	/////////////////////////////////////
	CMI_NSPN MI_NSPN;
	int nResult;
	BOOL	bCNode	= pParentNode->IsControlNode();
	//////////////////////////////////////////////
	if(bUsingDlg)
	{
		pSpawnedNode->SetObjectID(m_ObjID);
		(pSpawnedNode->GetNodeCard())->id = m_ObjID;
		///
		nResult = MI_NSPN.SpawnNodeShowingDlg(pSpawnedNode,pParentNode,pParentNode, NODE);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_NSPN.SpawnNodeWithoutDlg(pSpawnedNode,pParentNode,pXFMat,&m_SpawnedID,
												bCNode,pParentNode,NODE); 
	}
	if(nResult<0)
	{

		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		//////////////////////////
		m_pSpawnedNode	= NULL;
		//////////////////////////
		return nResult;//
	}
	///////////////////////////////////////////////////////////
	CDrLabel*	pLabel;
	int nNodeIndex,nLabelIndex;
	BOOL bGen	= TRUE;
	BOOL bMNode = FALSE;
	WORLD Pt	= *(pSpawnedNode->GetLocalPos());
	/////////////////////////// Create Anyway
	nNodeIndex = -12345;
	CMI_GangN GangN;
	m_pSpawnedNode = GangN.CreateNode(m_SpawnedID,pLabel,Pt,bCNode,bGen,bMNode,
															nNodeIndex,nLabelIndex);
													// TRUE = Internally Generated
	(m_pSpawnedNode->GetNodeCard())->bnid_c = bCNode;
	//////////////////////////////////////////////////////////////////////////////
/*
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	//////////////
	m_SpawnedID = pSpawnedNode->GetObjectID();
	///////////////
	m_pSpawnedNode	= (CDrNode*)(pObjectMgr->AddToDataBase(m_SpawnedID,nActiveIndex,NODE));
	m_pSpawnedNode->SetShow(FALSE);	// not quite ready
	////////////////////////////////////////////////// Transfer Data
	m_pSpawnedNode->SetObjectInfo(pSpawnedNode);
	////////////////////////////////////////////////// Create NodeLabel
*/
	if(bUsingDlg && (pSpawnedNode->GetMatObj()) )
	{
		Math3D.BlockCopy(	(HUGEBLK)(pSpawnedNode->GetMatObj()),
							(HUGEBLK)(m_pSpawnedNode->GetMatObj()), sizeof(CMatObj) );
		delete pSpawnedNode->GetMatObj();
		pSpawnedNode->SetMatObj((CMatObj*)NULL);
	}
	else
	if(!bUsingDlg && m_pMatObj)
	{
		Math3D.BlockCopy(	(HUGEBLK)(m_pMatObj),
							(HUGEBLK)(m_pSpawnedNode->GetMatObj()), sizeof(CMatObj) );
		delete m_pMatObj;
		m_pMatObj = NULL;
	}
	/////////////////////////////////////////////////////////// Control RectBound
	m_pSpawnedNode->SetDirty(TRUE);
	m_pSpawnedNode->SetShow(TRUE);
	/////////////////////////////////////////////
	int nActiveIndex;
	/////////////////
	CString ID		= m_pSpawnedNode->GetObjectID();
	///
	if(bCNode)
	{
		pList = pObjectMgr->GetObjectList(CNODE);
		nActiveIndex = pList->GetObjectIndex(CNODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(CNODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CNODE);
	}
	else
	{
		pList = pObjectMgr->GetObjectList(NODE);
		nActiveIndex = pList->GetObjectIndex(NODE, ID);
		pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
		pObjectMgr->SetActiveObjectType(NODE);		    // set Active Type									
		pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,NODE);
	}
	///////////////////////////////
	return 0;
}	 

void CNodCreOp::OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CNodCreOp::OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	////////////////////////////////
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

void CNodCreOp::OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case NODE:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

int CNodCreOp::RightUp_Premature()
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
	switch(m_CreOp)
	{
		case COP_TRANSLATE:

			if(m_nInfoDone<MAX_INFO_XLATE)
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

int CNodCreOp::ShowInputInfo_XLATE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Translation Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Translated %s ID = %s\n\n",m_strParentType,m_ObjID); // 
	/////////////////////////////////////
	if(m_TranPtID !="")
		j += sprintf( buf + j, "\n\nTranslate_About Node ID = %s\n",m_TranPtID); // Grab Node
	else
		j += sprintf( buf + j, "\n\nTranslate_About Coords:\n");
	//
	j += sprintf( buf + j, "\n\tX  = %f",m_wTranPt.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wTranPt.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wTranPt.z);
	////
	if(m_ToID_R !="")
		j += sprintf( buf + j, "\n\nTranslate_To Node ID = %s\n",m_ToID_R); // 
	else
		j += sprintf( buf + j, "\n\nTranslate_To Coords:\n");
	//
	j += sprintf( buf + j, "\n\tX  = %f",m_wTran.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wTran.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wTran.z);
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


int CNodCreOp::RightUp_NotAutoAccept()
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
	///////////////////
	if(m_CreOp == COP_ROTATE)
	{
		/////////////////////////// Calc Rot
		if(!m_bAngleIn)
			CalcRotationFromFromTo();
		/////////////////////////////////
	}
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		switch(m_CreOp)
		{
			case COP_TRANSLATE:

				nAnswer = ShowInputInfo_XLATE();
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
			sprintf(buf,"Do You Want to Delete\nCurrent Spawned %s to Start Allover",m_strParentType);
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

void CNodCreOp::OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(pWnd->GetCurrentIGenID() == NODE ||pWnd->GetCurrentIGenID() == INODE )
		m_bCNode = FALSE;
	else
		m_bCNode = TRUE;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Update Info
	UpdateDlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	if(RightUp_NotAutoAccept()<0)
	{
		Terminate_NOD(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{

		case COP_TRANSLATE:
						
			
			SetUpLocalM_XLATE();
			/////////////////////////////
			if(ShowNodeToSpawn(m_pParentNode,FALSE)<0)		 //FALSE = NoDlg
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
				UpdateDlg_FALSE_XLATE();
				break;
			}
			///////////////////	
			break;

			
		
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	char buf[50];
	if(m_bCNode)
	{
		pObjectMgr->BumpLastInputNo(CNODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(CNODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedID	= "CN_";
		m_SpawnedID	+= buf;
	}
	else
	{
		pObjectMgr->BumpLastInputNo(NODE);		// bump it
	    m_LastNum	= pObjectMgr->GetLastInputNo(NODE);		// internal
		sprintf(buf,"%d",m_LastNum);
		m_SpawnedID	= "";
		m_SpawnedID	+= buf;
	}
	////////////////////////////////////////////////////////////////////////
}

int CNodCreOp::CalcRotationFromDirCos(WORLD wDir) 
{
	C3DMath	Math3D;
	/////////////////////////////////////////////////	
	double One80byPi = 180./acos(-1.0);
	////////////////////////////////////// Find Angles
	WORLD Angles = wDir;
	///////////////////
	m_wRot.x = acos(Angles.x) * One80byPi;
	m_wRot.y = acos(Angles.y) * One80byPi;
	m_wRot.z = acos(Angles.z) * One80byPi;
	////////////////
	return 0;	
}

int CNodCreOp::CalcRotationFromFromTo() 
{
	/////////////////
/*
	if(m_FromID_R == m_ToID_R)
	{
		//////////////
		m_wRot.x = 0;
		m_wRot.y = 0;
		m_wRot.z = 0;
		//////////////
		return 0;
	}
*/
	C3DMath	Math3D;
	CXForm	XForm;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////
//	WORLD LocFrom,LocTo;
	////////////////////////////////////// Find Angles
	WORLD Angle_R,Angle_T;
	Math3D.Sub3DPts(&m_wTo_R,&m_wFrom_R,&Angle_R);
	Math3D.Sub3DPts(&m_wTo_T,&m_wFrom_T,&Angle_T);

/*

	///////////////////////////////////////////////////////////////
	//					Matrix in Short way, But 
	//					do not fit SetUpLocalM
	//					demand of 3 Angles
	///////////////////////////////////////////////////////////////
	////////////////////////////////////////////// Matrices
	MATRIX M_R,M_T;
	pMATRIX pM_R = &M_R;
	pMATRIX pM_T = &M_T;
	//
	Math3D.GetIdentityMatrix(pM_R);
	Math3D.GetIdentityMatrix(pM_T);
	////////////////////////////////////////////// Reference to Z-Axis
	XForm.RotateToNewZMATRIX(&Angle_R, pM_R,XF_REPLACE); // to Reference as NewZ
	Math3D.TransposeMATRIX(pM_R);	// NewZ as Reference
	////////////////////////////////////////////// Z-Axis to Target
	XForm.RotateToNewZMATRIX(&Angle_T, pM_T,XF_REPLACE);
	////////////////
	Math3D.F_MultMATRIX(pM_T,pM_R,&m_MAT);
	/////////
*/
	/////////////////////////////////////////////////	
	double One80byPi = 180./acos(-1.0);
	//////////////////////////////////////////
	Math3D.Normalize(&Angle_R,&Angle_R);
	Math3D.Normalize(&Angle_T,&Angle_T);
	///////////////////////////////////////////////////////////////
	//					Angles in Long way 
	//					to fit SetUpLocalM
	//					demand of 3 Angles
	///////////////////////////////////////////////////////////////
	MATRIX Mat;
	pMATRIX pM = &Mat;
	double dRx,dRy,dRz;
	WORLD Proj_R,Proj_T,wDir;
	///////////////////////////////////// RotY
	Proj_R.y	= 0.0;
	Proj_R.x	= Angle_R.x;
	Proj_R.z	= Angle_R.z;
	//
	Proj_T.y	= 0.0;
	Proj_T.x	= Angle_T.x;
	Proj_T.z	= Angle_T.z;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.y		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRy = acos(wDir.y) * One80byPi;
	////////////////
	Math3D.GetIdentityMATRIX(pM);
	XForm.Rotate_Y(pM, dRy, XF_REPLACE );
	XForm.Transform(&Angle_R, &Angle_R, pM);
	Math3D.Normalize(&Angle_R,&Angle_R);
	///////////////////////////////////// RotX
	Proj_R.x	= 0.0;
	Proj_R.y	= Angle_R.y;
	Proj_R.z	= Angle_R.z;
	//
	Proj_T.x	= 0.0;
	Proj_T.y	= Angle_T.y;
	Proj_T.z	= Angle_T.z;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.x		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRx = acos(wDir.x) * One80byPi;
	////////////////
	Math3D.GetIdentityMATRIX(pM);
	XForm.Rotate_X(pM, dRx, XF_REPLACE );
	XForm.Transform(&Angle_R, &Angle_R, pM);
	Math3D.Normalize(&Angle_R,&Angle_R);
	///////////////////////////////////// RotZ
	Proj_R.z	= 0.0;
	Proj_R.x	= Angle_R.x;
	Proj_R.y	= Angle_R.y;
	//
	Proj_T.z	= 0.0;
	Proj_T.x	= Angle_T.x;
	Proj_T.y	= Angle_T.y;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.z		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRz = acos(wDir.z) * One80byPi;
	///////////////////////////////////// Angle in Degrees
	m_wRot.x = dRx;
	m_wRot.y = dRy;
	m_wRot.z = dRz;
//	CalcRotationFromDirCos(wDir); 
	////////////////
	return 0;	
}

void CNodCreOp::SetUpLocalM_XLATE()
{
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////CenterPt Coordinates
	WOPtoWOR(&m_wTranPt,&m_wTranPt);	// World
	WOPtoWOR(&m_wTran,&m_wTran);		// World
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM,M;			// to translate by CenterPT
	pMATRIX pTM = &TM;
	pMATRIX pM = &M;
	Math3D.GetIdentityMATRIX(pTM);
	Math3D.GetIdentityMATRIX(pM);
	///////////////////////////////////////////////////////// 
	XForm.Translate(pTM,-m_wTranPt.x,-m_wTranPt.y,-m_wTranPt.z,XF_REPLACE);
	XForm.Translate(pM,m_wTran.x,m_wTran.y,m_wTran.z,XF_REPLACE);
	////////////////////////////////////////////////////
	Math3D.F_MultMATRIX(pM,pTM,pM);
	//////////////////////////////////////////////////////////
	//					Fill Up Mat Matrix
	//////////////////////////////////////////////////////////
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_XFORMS);
	m_pMatObj->SetCreOp(COP_TRANSLATE);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	/////////////////////////////////// Grab Node
	m_pMatObj->SetRotPtID(m_TranPtID);	
	m_pMatObj->SetRotPt(m_wTranPt);	
	/////////////////////////////////// Translation To
	m_pMatObj->SetTranPtID(m_TranPtID);
	m_pMatObj->SetFromID(m_FromID_R);
	m_pMatObj->SetFromPt(m_wFrom_R);
	m_pMatObj->SetToID(m_ToID_R);
	m_pMatObj->SetToPt(m_wTo_R);			// same as m_wTran
	m_pMatObj->SetTranslation(m_wTran);
	m_pMatObj->SetCoordIn(m_bCoordIn);
	////////////////////////////////
	m_pMatObj->SetNoRot(FALSE);
	m_pMatObj->SetNoTran(TRUE);
	m_pMatObj->SetNoScale(FALSE);
	m_pMatObj->SetNoShear(FALSE);
	////////////////////////////////
	return;
}

/////////////////////////////////////////////////////////////////////////////////////// 
UINT CNodCreOp::ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	///////////////////////////////////
	if(IGenID == NODE ||IGenID == INODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Spawning an Input Node@";
	else
	if(IGenID == NODE ||IGenID == CNODE)
		//////////////////////////////////////////// TaskID
		strCur = "Ready for Spawning a Control Node@";
	else
	{
		str = "UNKNOWN";	ID	= UNONE;
		pWnd->SetstrIGenID(str);
		////////////////////////
		return UNONE;
	}
	/////////////////////////////
	switch(CntlID)
	{
		//////////////////////////////////////// Elements
		case ELEMENT:
//					pWnd->SetMouseBoxType(ELEMDIMBOX);
			str = "ELEMENT";
			pWnd->SetIGenBoxStatus(TRUE);
			pWnd->SetCntlBoxStatus(FALSE);
			pWnd->SetDrawBoxStatus(FALSE);
			///////////
			pWnd->SetstrCntlID(str);
			////////////////////////
			switch(OperID)
			{
				//////////////////////////////////////////// Create
				case COP_TRANSLATE:
					///////////////////////////// String
					str = "TRANSLATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case INODE:			str = "Input@NODE";		ID = OperID;
							strCur += "Click on an Input Node to Translate";	break;
						case CNODE:			str = "Control@NODE";	ID = OperID;
							strCur += "Click on a Control Node to Translate";	break;
					}			
					break;
				//////////////////////////////////////////// Create
				default:
					///////////////////////////// String
					str = "DON'T KNOW";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					ID	= UNONE;
					strCur = "UNKNOWN Spawing Option";
					pWnd->SetstrCurrID(strCur);
					break;
			}
			////////////////////////////////////////////////// Overriding everyID above
			ID = OperID;		// afterthought
			//////////////////////////////////////////// CreOp
			m_CreOp = OperID;
			////////////////////////////////////////////////// 
			pWnd->SetstrIGenID(str);
			pWnd->SetstrCurrID(strCur);
			//////////
			return ID;

		default:
			break;
	}
	return UNONE;
}
	
void CNodCreOp::ModeLessOff()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetCreOpDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_CREIN,IDOK);
}

void CNodCreOp::ModeLessOn()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
	m_CreOp = aTool;
	/////////////////////////////////////////
	if(aTool == COP_REFLECT)
	{
		CMNodMgr* pMNodMgr;
		/////////////////////////////////////////////////////////////// Using MNodMgr
		if(!m_bDoModalDone)
		{		
			if(pMNodMgr->DoModal_SymmetryType(m_SpnType) == IDCANCEL)
			{
				///////////////////////////////////// Reset TaskID
				pWnd->SendMessage(ID_RESET_MODELESS,0);
				return;
			}
			m_bDoModalDone = TRUE;
		}
	}
	////////////////////////////
//		if(!(GetCreOpDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_CREIN);	// pWnd will dispatch to right place
												// based on IGenID

}

long CNodCreOp::CreateorActivateCreOp_NOD(UINT wParam, long lParam)
{
	/////////////////////////////////////////// Parent Info
	m_ParentType	= NODE;
	m_strParentType = "Node";
	/////////////////////////////////////////////////////////
	GetCreOpDlg()->m_CreOp = m_CreOp;
	///////////////////////////////////////
	if(GetCreOpDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetCreOpDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetCreOpDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetCreOpDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////
		Init_NOD();

	}
	else
	{
		GetCreOpDlg()->SetActiveWindow();
		GetCreOpDlg()->m_CreOp = m_CreOp;
	}
	////////////////
	switch(m_CreOp)
	{
		case COP_TRANSLATE:
			//////////////////////////////
			UpdateDlg_FALSE_XLATE();
			////
			break;
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if CreODlg Open
	if(GetCreOpDlg()->m_hWnd)
	{
/*
		CStatic* pCtl;
		pCtl = (CStatic*)(GetCreOpDlg()->GetDlgItem(IDC_OTHER));
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
	 
long CNodCreOp::GoodByeCreOp_NOD(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodCreOp::CancelCreOp_NOD(UINT wParam, long lParam)
{
	
	GetCreOpDlg()->DestroyWindow();
	////////////////
	{
		Terminate_NOD(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CNodCreOp::UpdateCreOp(UINT wParam, long lParam)
{

	GetCreOpDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	UpdateDlg_TRUE();
	////////////////////////////
	if(m_bDirect && m_bDominant)	// expecting Translation Value from DlgBox
	{
		if(m_bDlgExpect)
			m_nInfoDone++;
	}
	//////////////////////////////
	UpdateDlg_FALSE_XLATE();
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

