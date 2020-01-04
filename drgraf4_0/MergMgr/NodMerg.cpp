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
#include "CreODlgM.h"  
////////////////////// 
#include "MI_GangN.h" 
#include "MI_NSPN.h" 
#include "MI_CSPN.h" 
#include "MI_PSPN.h" 
#include "MI_SSPN.h" 
#include "MI_OSPN.h" 
#include "Dlg_CrOI.h"
//////////////////////
#include "NodCreOp.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_INFO_MERGE		2	// 1 Object/1 Object Grab Node/2 Nodes( for direction)        
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
	if(!m_pCreOpDlg)
		return;
	/////////////////////////////////// Modeless Dialogs
	if(m_pCreOpDlg->m_hWnd)
		m_pCreOpDlg->DestroyWindow();
	///////////////////
	delete m_pCreOpDlg; 
	m_pCreOpDlg	= NULL;
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
//	char buf[50];
	CString strID;
	if(m_bCNode)
		pObjectMgr->SetObjInfoID(m_SpawnedID,CNODE);
	else
		pObjectMgr->SetObjInfoID(m_SpawnedID,NODE);
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
	//12/29/97 
	m_bAxis			= FALSE;			// No-Axis,default
	m_nAxis			= DEFAULT_AXIS;				// default
	m_bNegative		= FALSE;
	//12/29/97 end
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
	///////////////////////////////// Rotate
	m_bAngleIn		= FALSE;
	m_bOrigin		= FALSE;
	m_RotPtID		= "";
	Math3D.Set3DPts(&m_wRotPt,0.0,0.0,0.0);
	m_FromID_R		= "";
	Math3D.Set3DPts(&m_wFrom_R,0.0,0.0,0.0);
	m_ToID_R			= "";
	Math3D.Set3DPts(&m_wTo_R,0.0,0.0,0.0);
	m_FromID_T		= "";
	Math3D.Set3DPts(&m_wFrom_T,0.0,0.0,0.0);
	m_ToID_T			= "";
	Math3D.Set3DPts(&m_wTo_T,0.0,0.0,0.0);

	Math3D.Set3DPts(&m_wRot,0.0,0.0,0.0);
	///////////////////////////////// Scale
	m_ScalePtID		= "";
	Math3D.Set3DPts(&m_wScale,1.0,1.0,1.0);
	///////////////////////////////// Reflect
//	m_bDoModalDone	= FALSE;
	m_SymmPtID[0]	= "";
	m_SymmPtID[1]	= "";
	m_SymmPtID[2]	= "";
	Math3D.Set3DPts(&(m_wSymm[0]),0.0,0.0,0.0);
	Math3D.Set3DPts(&(m_wSymm[1]),0.0,0.0,0.0);
	Math3D.Set3DPts(&(m_wSymm[2]),0.0,0.0,0.0);
	///////////////////////////////// Shear
	m_ShearPtID		= "";
	Math3D.Set3DPts(&m_wShear,0.0,0.0,0.0);
	//////////////////////////
	m_bInstanced	= FALSE;
	m_bNoTran		= TRUE;
	m_bNoRot		= TRUE;
	m_bNoScale		= TRUE;
	m_bNoShear		= TRUE;
	///////////////////////
	m_pMatObj		= NULL;
	m_XfType		= XT_XFORMS;	// in IGen.h
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
		case GOP_MERGE:				// 

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
	//12/29/97 
	m_bAxis		= GetCreOpDlg()->m_bAxis;			// IsAxis
	m_nAxis		= GetCreOpDlg()->m_nAxis;			// Axis: 1=X/2=Y/3=Z
	m_bNegative	= GetCreOpDlg()->m_bNegative;
	//12/29/97 end
	//////
	m_SpawnedID	= GetCreOpDlg()->m_ObjID;
	m_ObjID		= m_SpawnedID;
	m_X			= GetCreOpDlg()->m_X;
	m_Y			= GetCreOpDlg()->m_Y;
	m_Z			= GetCreOpDlg()->m_Z;
	m_NID		= m_CurrentNodeID;
	////////////////////////
}			
void CNodCreOp::UpdateDlg_TRUE_REFLECT()
{
	UpdateDlg_TRUE();
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	if(m_CreOp != COP_REFLECT)
		return;
	////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:			// pick up TargetNode
			m_XfType	= XT_SYMMETRIC;
			////////////////////
			break;
		case 1:		// Ist Point for Plane
			m_bDirect	= GetCreOpDlg()->m_bDirect;	
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wSymm[0].x	= m_X;
					m_wSymm[0].y	= m_Y;
					m_wSymm[0].z	= m_Z;		// also for other Coord
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
		case 2:		// 2nd Point for Plane
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
					m_wSymm[1].x	= m_X;
					m_wSymm[1].y	= m_Y;
					m_wSymm[1].z	= m_Z;		// also for other Coord
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

		case 3:		// 3rd Point for Plane
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// both for Translation & Rotation & Reflection
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					//12/29/97
					if(m_bAxis)	
					{
						/////////////////////////
						m_wSymm[2].x	= m_wSymm[1].x;
						m_wSymm[2].y	= m_wSymm[1].y;
						m_wSymm[2].z	= m_wSymm[1].z;
						//
						switch(m_nAxis)
						{
							case 1:	m_bNegative?m_wSymm[2].x += -1.0:m_wSymm[2].x += 1.0;	break;
							case 2:	m_bNegative?m_wSymm[2].y += -1.0:m_wSymm[2].y += 1.0;	break;
							case 3:	m_bNegative?m_wSymm[2].z += -1.0:m_wSymm[2].z += 1.0;	break;
							default:
								{
									AfxMessageBox("Internal ERROR:\nCNodCreOM::UpdateDlg_TRUE_REFLECT()\nm_nAxis !=1,2or3");
									return;
								}
						}
						///////
						return;
					}
					//12/29/97 end
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wSymm[2].x	= m_X;
					m_wSymm[2].y	= m_Y;
					m_wSymm[2].z	= m_Z;		// also for other Coord
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
		default:		// 
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
	//12/29/97
		GetCreOpDlg()->m_bAxis		= m_bAxis;
		GetCreOpDlg()->m_nAxis		= m_nAxis;
		GetCreOpDlg()->m_bNegative	= m_bNegative;
	//12/29/97 end
	}
	GetCreOpDlg()->m_CreOp		= m_CreOp;
	GetCreOpDlg()->m_ObjID		= m_SpawnedID;
//	GetCreOpDlg()->m_NID		= m_CurrentNodeID;		//12/29/97
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
	//12/29/97 
	GetCreOpDlg()->GetDlgItem(IDC_AXIS)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_NEGATIVE)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_X)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_Y)->SetWindowText("");
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_Z)->SetWindowText("");
	//12/29/97 end
	///
	GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
	//12/29/97
	GetCreOpDlg()->GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
	GetCreOpDlg()->GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
	((CButton*)GetCreOpDlg()->GetDlgItem(IDC_AXIS_X))->SetCheck(FALSE);
	((CButton*)GetCreOpDlg()->GetDlgItem(IDC_AXIS_Y))->SetCheck(FALSE);
	((CButton*)GetCreOpDlg()->GetDlgItem(IDC_AXIS_Z))->SetCheck(FALSE);
	//12/29/97 end
	//////////////////////////////////////
	if(m_nInfoDone>=1)
	{
//		GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
		GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->SetWindowText("Direct");
		GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(TRUE);
		GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->SetWindowText("Dominant");
		GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(TRUE);
	}
	/////////
	if((m_nInfoDone >=1) && (m_CreOp == COP_ROTATE))	// for Angle Input in ROTATION
	{
//		GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
		GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->SetWindowText("Angle");
		GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(TRUE);
		GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->SetWindowText("Origin");
		GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->EnableWindow(TRUE);
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
			GetCreOpDlg()->SetWindowText("Spawn by TRANSLATION");
			strCurr = "Spawn by Translation: Click On@A " + m_strParentType + " To Translate";
			break;
		case COP_ROTATE:
			GetCreOpDlg()->SetWindowText("Spawn by ROTATION");
			strCurr = "Spawn by Rotation: Click On@A " + m_strParentType + " To Rotate";
			break;
		case COP_SCALE:
			GetCreOpDlg()->SetWindowText("Spawn by SCALE");
			strCurr = "Spawn by Scaling: Click On@A " + m_strParentType + " To Scale";
			break;
		case COP_REFLECT:
			GetCreOpDlg()->SetWindowText("Spawn by REFLECTION");
			strCurr = "Spawn by Reflection: Click On@A " + m_strParentType + " To Reflect";
			break;
		case COP_SHEAR:
			GetCreOpDlg()->SetWindowText("Spawn by SHEAR");
			strCurr = "Spawn by Shear: Click On@A " + m_strParentType + " To Shear";
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	m_pCreOpDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}
void CNodCreOp::UpdateDlg_FALSE_REFLECT()
{
	if(m_CreOp != COP_REFLECT)
		return;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	///////////////////
	UpdateDlg_FALSE();
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	if(m_nInfoDone == 0)
		UpdateDlg_FALSE_0();
	else
		strCurr = "Spawn by Reflection: ";
	///////////////////
	switch(m_nInfoDone)
	{
		case 1:			// Reflection Plane Definition: a Point on the plane
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
					strCurr += "TYPE in@Plane_defining Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Plane_defining Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Plane_defining Node";
			break;
		case 2:			// Reflection Plane Definition: 2nd pt. or Ist Pt. for Normal or Normal
						// in Axis direction
			//////
			if(GetCreOpDlg()->m_bDirect)
			{
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					/////////////////////
					if(m_SpnType == SPN_SYMM_3)
						strCurr += "TYPE in@Plane_defining 2rd Node Coords. in Dialog Box";
					else
					if(m_SpnType == SPN_SYMM_N)
						strCurr += "TYPE in@Normal_defining Ist Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					if(m_SpnType == SPN_SYMM_3)
						strCurr += "CLICK in@Plane_defining 2nd Node Coords.";
					else
					if(m_SpnType == SPN_SYMM_N)
						strCurr += "CLICK in@Normal_defining Ist Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
			{
				if(m_SpnType == SPN_SYMM_3)
					strCurr += "CLICK On@Plane_defining 2nd Node";
				else
				if(m_SpnType == SPN_SYMM_N)
					strCurr += "CLICK On@Normal_defining Ist Node";
			}
			break;
		case 3:			// Reflection Plane Definition: 3nd pt. or 2nd Pt. for Normal
			/////////////
			if(GetCreOpDlg()->m_bDirect)
			{
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDlgExpect = TRUE;
					////////////////////
					if(m_SpnType == SPN_SYMM_3)
						strCurr += "TYPE in Plane_defining 3rd Node Coords. or@SELECT an in-Plane Axis in Dialog Box";
					else
					if(m_SpnType == SPN_SYMM_N)
						strCurr += "TYPE in Normal_defining 2nd Node Coords. or@SELECT an Axis for Normal in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
					///12/29/97
					GetCreOpDlg()->GetDlgItem(IDC_AXIS)->SetWindowText("Axis");
					GetCreOpDlg()->GetDlgItem(IDC_AXIS)->EnableWindow(TRUE);
/*
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_X)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_Y)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_Z)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_Y)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_AXIS_Z)->EnableWindow(TRUE);
*/
					//12/29/97 end
				}
				else
				{
					if(m_SpnType == SPN_SYMM_3)
						strCurr += "CLICK in@Plane_defining 3rd Node Coords.";
					else
					if(m_SpnType == SPN_SYMM_N)
						strCurr += "CLICK in@Normal_defining 2nd Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
			{
				if(m_SpnType == SPN_SYMM_3)
					strCurr += "CLICK On@Plane_defining 3rd Node";
				else
				if(m_SpnType == SPN_SYMM_N)
					strCurr += "CLICK On@Normal_defining 2nd Node";
			}
			break;
		case 4:
			strCurr = "Ready with other Info.?@Click Right Button";
			GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
			GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
			////////////////////////////////////////
			if(!pBool->IsSpawnOn())
				GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(FALSE);
			else
				GetCreOpDlg()->GetDlgItem(IDC_OBJID)->EnableWindow(TRUE);
			///////
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
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
	int nResult;
	///////////////////////////////////////////// See if any Existing Node Hit
	nResult = LeftUp_GetNode(point, bCNode);
	///////////////////
	if(nResult < 0)
		return nResult; // Cancel or No Hit
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

int CNodCreOp::LeftUp_GetNode_REFLECT(POINT point, BOOL bCNode)
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
			case 1:
			case 2:
			case 3:
				m_SymmPtID[m_nInfoDone-1]	= m_pCurrentNode->GetObjectID();
				m_wSymm[m_nInfoDone-1]		= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&(m_wSymm[m_nInfoDone-1]),&(m_wSymm[m_nInfoDone-1]));
										// change to physical like in Dlg Input
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
			case 1:
			case 2:
			case 3:
				m_SymmPtID[m_nInfoDone-1]	= "";
				m_wSymm[m_nInfoDone-1]		= m_wLoc;
				WORtoWOP(&(m_wSymm[m_nInfoDone-1]),&(m_wSymm[m_nInfoDone-1]));
										// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	// NO Hit
	///////////////////////////////////////// From & To Same,INADMISSIBLE
	if(m_nInfoDone >1 && (m_SpnType == SPN_SYMM_3))	// 
	{
		C3DMath	Math3D;
		///////////////
		if(Math3D.AreSame_WORLD(&m_wSymm[m_nInfoDone-2],&m_wSymm[m_nInfoDone-1]
														,pHitNet->GetDblRatio()))
   		{
			AfxMessageBox("Degenerate Plane Definition:\nSame Node More than Once!");
			m_nInfoDone--;
			return -2;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CNodCreOp::LeftUp_REFLECT_NOD(POINT point)
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
			
		case 1://	Ist Pt. or Node On Plane	
		case 2://	2nd Pt. or Node On Plane OR Ist Pt. on Normal	
		case 3://	Pt. or Node On Plane OR 2nd Pt. on Normal	
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_REFLECT(point,FALSE);		// try INODE
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
		case COP_REFLECT: 

			if(m_nInfoDone > MAX_INFO_REFLECT)
				return;
			////////////////
			UpdateDlg_TRUE_REFLECT();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_REFLECT_NOD(point)<0)
				{
					Terminate_NOD(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_REFLECT();
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
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrNode*	pDrNode;
//	int			nActiveIndex,index;
	int			index;
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
/*
		if(bCNode)
			index = IsObjectHit(CNODE,&wLoc,0);
		else
			index = IsObjectHit(NODE,&wLoc,0);
		///
*/
		if(bCNode)
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(NODE,point,0);
	}
	/////////////////////////////////////////////////////////////// Right Type
	if(index>=0)						
	{
		/////////////
		pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
		ID		= pDrNode->GetObjectID();
		/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,CNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
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
							index = IsObjectHit(CNODE,point,startIndex);
						else
							index = IsObjectHit(NODE,point,startIndex);
					}
					else
					if(m_ProbLim == PDL_THREE)
					{
/*
						////////////////
						if(bCNode)
							index = IsObjectHit(CNODE,&wLoc,startIndex);
						else
							index = IsObjectHit(NODE,&wLoc,startIndex);
						///
*/
						if(bCNode)
							index = IsObjectHit(CNODE,point,startIndex);
						else
							index = IsObjectHit(NODE,point,startIndex);
					}
					/////////////////////////////////////////////////////////////// Right Type
					if(index>=0)
					{
						pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
						ID		= pDrNode->GetObjectID();
						/////////////////////////////////////////////
		if(bCNode)
			pObjectMgr->ShowObject_On_Off(pDrNode,CNODE,TRUE);
		else
			pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
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
		case COP_REFLECT:

			if(m_nInfoDone<MAX_INFO_REFLECT)
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

int CNodCreOp::ShowInputInfo_REFLECT()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Reflection Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Reflected %s ID = %s\n\n",m_strParentType,m_ObjID); // 
	/////////////////////////////////////
	if(m_SpnType == SPN_SYMM_3)
	{
		///
		if(m_SymmPtID[0] !="")
			j += sprintf( buf + j, "\n\n\tIst Node On the Plane ID = %s\n",m_SymmPtID[0]);
		else
			j += sprintf( buf + j, "\n\n\tIst Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[0].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[0].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[0].z);
		/////////
		if(m_SymmPtID[1] !="")
			j += sprintf( buf + j, "\n\n\t2nd Node On the Plane ID = %s\n",m_SymmPtID[1]);
		else
			j += sprintf( buf + j, "\n\n\t2nd Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[1].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[1].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[1].z);
		/////////
		if(m_SymmPtID[2] !="")
			j += sprintf( buf + j, "\n\n\t3rd Node On the Plane ID = %s\n",m_SymmPtID[2]);
		else
			j += sprintf( buf + j, "\n\n\t3rd Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[2].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[2].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[2].z);
		/////////
	}
	if(m_SpnType == SPN_SYMM_N)
	{
		///
		if(m_SymmPtID[0] !="")
			j += sprintf( buf + j, "\n\n\tIst Node On the Plane ID = %s\n",m_SymmPtID[0]);
		else
			j += sprintf( buf + j, "\n\n\tIst Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[0].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[0].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[0].z);
		/////////
		if(m_SymmPtID[1] !="")
			j += sprintf( buf + j, "\n\n\tInd Node On the Normal ID = %s\n",m_SymmPtID[1]);
		else
			j += sprintf( buf + j, "\n\n\t2nd Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[1].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[1].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[1].z);
		/////////
		if(m_SymmPtID[2] !="")
			j += sprintf( buf + j, "\n\n\t2nd Node On the Normal ID = %s\n",m_SymmPtID[2]);
		else
			j += sprintf( buf + j, "\n\n\t3rd Point On the Plane \n");
		j += sprintf( buf + j, "\n\tX Coord = %f",m_wSymm[2].x);
		j += sprintf( buf + j, "\n\tY Coord = %f",m_wSymm[2].y);
		j += sprintf( buf + j, "\n\tZ Coord = %f",m_wSymm[2].z);
		/////////
	}
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
			case COP_REFLECT:


				nAnswer = ShowInputInfo_REFLECT();
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

		
		case COP_REFLECT:
						
			
			SetUpLocalM_REFLECT();
			/////////////////////////////
			if(ShowNodeToSpawn(m_pParentNode,FALSE)<0) //FALSE = NoDlg
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
				UpdateDlg_FALSE_REFLECT();
				break;
			}
			///////////////////	
			break;
		
		default:  
			return;
	}
	/////////////////////
	if(m_pMatObj)
	{
		delete m_pMatObj;
		m_pMatObj = NULL;
	}
	////////////////////////////////////////////////////////////////////////
	if(m_bCNode)
		pObjectMgr->SetObjInfoID(m_SpawnedID,CNODE);
	else
		pObjectMgr->SetObjInfoID(m_SpawnedID,NODE);
	////////////////////////////////////////////////////////////////////////
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
		strCur = "Ready for Merging Input Nodes@";
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
				//////////////////////////////////////////// Create
				case GOP_MERGE:
					///////////////////////////// String
					str = "MERGE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case INODE:			str = "Input@NODE";		ID = OperID;
							strCur += "Click on an Input Node to Translate";	break;
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
/*
	/////////////////////////////////////////
	if(aTool == COP_REFLECT)
	{
		CCreODlgM* pMNodMgr;
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
	else
	if(aTool == COP_ROTATE)
	{
		CCreODlgM* pMNodMgr;
		/////////////////////////////////////////////////////////////// Using MNodMgr
		if(!m_bDoModalDone)
		{		
			if(pMNodMgr->DoModal_RotationType(m_SpnType) == IDCANCEL)
			{
				///////////////////////////////////// Reset TaskID
				pWnd->SendMessage(ID_RESET_MODELESS,0);
				return;
			}
			m_bDoModalDone = TRUE;
		}
	}
*/
	////////////////////////////
			m_bDoModalDone = TRUE;
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
		case COP_REFLECT:
			//////////////////////////////
			UpdateDlg_FALSE_REFLECT();
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
	////////////////
	switch(m_CreOp)
	{
		case COP_REFLECT:

			UpdateDlg_TRUE_REFLECT();
			////////////////////////////
			if(m_bDirect && m_bDominant)	// expecting Reflection Value from DlgBox
			{
				if(m_bDlgExpect)
					m_nInfoDone++;
			}
			//////////////////////////////
			UpdateDlg_FALSE_REFLECT();
			////
			break;
		default:
			break;
	}
	//////////
	return 0L;
}

void CNodCreOp::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodCreOp:    Storing\n");	
		

	}
	else
	{
		TRACE(" NodCreOp:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		

