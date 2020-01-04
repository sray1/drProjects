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
///////////////////////////////////////////////////////////////////////////////////////////
// if NODE_SPAWN: Object Grab Node Same As Node
//////////////////////////////////////////////
#define	DEFAULT_AXIS		3	// Z-Axis for especially 2D Problem and for 3D
								// Later it will be obtained from Document Default		todo
////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_INFO_XLATE		3	// 1 Object/1 Object Grab Node/2 Nodes( for direction)        
#define MAX_INFO_ROTATE		6	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_ROT_LINE	3	// 1 Object/1 Object Grab Node/2 Nodes( for Axis)           
#define MAX_INFO_SCALE		1	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg)           
#define MAX_INFO_REFLECT	4	// 1 Object/1 Object Grab Node/	3 Nodes ( defining Plane or
								//			1 Node on Plane + 2 Nodes for Normal        
#define MAX_INFO_SHEAR		1	// 1 Object/1 Object Grab Node/None but 3 Coords(from Dlg) 
#define MAX_INFO_SPAWN		0	// 1 Object   
#define MAX_INFO_STITCH		1	// Atleast Two Objects   
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
		case COP_TRANSLATE:				// 

			m_CreOp = COP_TRANSLATE;
			LeftDown_NODE();
			return;

		case COP_ROTATE: 

			m_CreOp = COP_ROTATE;
			LeftDown_NODE();
			return;

		case COP_SCALE: 

			m_CreOp = COP_SCALE;
			LeftDown_NODE();
			return;

		case COP_REFLECT: 

			m_CreOp = COP_REFLECT;
			LeftDown_NODE();
			return;

		case COP_SHEAR: 

			m_CreOp = COP_SHEAR;
			LeftDown_NODE();
			return;

		////////////////////////////////////////////////// SPAWN	
		case COP_SPAWN:				// 

			m_CreOp	= COP_SPAWN;
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

void CNodCreOp::UpdateDlg_TRUE_ROTATE()
{
	UpdateDlg_TRUE();
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	if(m_CreOp != COP_ROTATE)
		return;
	////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:			// pick up TargetNode
			m_XfType	= XT_XFORMS;
			m_bNoRot	= FALSE;
			////////////////////
			break;
		case 1:		// m_RotPt ( Grab Pt.)
			if(m_bOrigin)
			{
				m_X = 0.0;
				m_Y = 0.0;
				m_Z = 0.0;
				/////////////////////////
				m_wRotPt.x	= m_X;
				m_wRotPt.y	= m_Y;
				m_wRotPt.z	= m_Z;		// also for other Coord
				/////
				break;
			}
			//////////
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
					m_wRotPt.x	= m_X;
					m_wRotPt.y	= m_Y;
					m_wRotPt.z	= m_Z;		// also for other Coord
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
		case 2:		// FromID or Coords for FromPt.			// Angle In or Reference Line 
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			m_bAngleIn	= GetCreOpDlg()->m_bAngleIn;	//
			m_bAxis		= GetCreOpDlg()->m_bAxis;
			//////////////
			if(m_bAngleIn)						// Angle In			
			{
				m_X			= GetCreOpDlg()->m_X;
				m_Y			= GetCreOpDlg()->m_Y;
				m_Z			= GetCreOpDlg()->m_Z;
				/////////////////////////
				m_wRot.x	= m_X;
				m_wRot.y	= m_Y;
				m_wRot.z	= m_Z;		// also for other Coord
				////////
				return;
			}
			else								// Parallel
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					//01/15/98
					if(m_bAxis)	
					{
						/////////////////////////
						m_wFrom_R.x		= m_wRotPt.x;
						m_wFrom_R.y		= m_wRotPt.y;
						m_wFrom_R.z		= m_wRotPt.z;
						m_wTo_R.x		= m_wFrom_R.x;
						m_wTo_R.y		= m_wFrom_R.y;
						m_wTo_R.z		= m_wFrom_R.z;
						//
						switch(m_nAxis)
						{
							case 1:	m_bNegative?m_wTo_R.x += -1.0:m_wTo_R.x += 1.0;	break;
							case 2:	m_bNegative?m_wTo_R.y += -1.0:m_wTo_R.y += 1.0;	break;
							case 3:	m_bNegative?m_wTo_R.z += -1.0:m_wTo_R.z += 1.0;	break;
							default:
								{
									AfxMessageBox("Internal ERROR:\nCNodCreOM::UpdateDlg_TRUE_ROTATE()\nm_nAxis !=1,2or3");
									return;
								}
						}
						///////
						return;
					}
					/////////////////////////
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wFrom_R.x = m_X;
					m_wFrom_R.y = m_Y;
					m_wFrom_R.z = m_Z;
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
		case 3:		// ToID or Coords for ToPt.				// Reference Line
			if(m_bAngleIn)
				break;
			//////////////
			if(m_bAxis)
			{
				m_wRot.z	= GetCreOpDlg()->m_Z;			// Rotation about Axis
				////////
				return;
			}
			//////
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			///////
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wTo_R.x = m_X;
					m_wTo_R.y = m_Y;
					m_wTo_R.z = m_Z;
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
		case 4:		// FromID or Coords for FromPt.			// Target Line
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				break;
			//////
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			//////////////
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wFrom_T.x = m_X;
					m_wFrom_T.y = m_Y;
					m_wFrom_T.z = m_Z;
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
		case 5:		// ToID or Coords for ToPt.				// Target Line
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				break;
			//////
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			if(m_bDirect)
			{
				if(m_bDominant)
				{
					m_X = GetCreOpDlg()->m_X;
					m_Y = GetCreOpDlg()->m_Y;
					m_Z = GetCreOpDlg()->m_Z;
					/////////////////////////
					m_wTo_T.x = m_X;
					m_wTo_T.y = m_Y;
					m_wTo_T.z = m_Z;
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

void CNodCreOp::UpdateDlg_TRUE_SCALE()
{
	UpdateDlg_TRUE();
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	if(m_CreOp != COP_SCALE)
		return;
	////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:			// pick up TargetNode
			m_XfType	= XT_XFORMS;
			m_bNoScale	= FALSE;
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
					m_wScalePt.x	= m_X;
					m_wScalePt.y	= m_Y;
					m_wScalePt.z	= m_Z;		// also for other Coord
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
		case 2:		// m_Scale Values
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// 
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			///////////
			m_X = GetCreOpDlg()->m_X;
			m_Y = GetCreOpDlg()->m_Y;
			m_Z = GetCreOpDlg()->m_Z;
			/////////////////////////
			m_wScale.x	= m_X;
			m_wScale.y	= m_Y;
			m_wScale.z	= m_Z;		// also for other Coord
			//////
			break;
		default:
			break;
	}
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

void CNodCreOp::UpdateDlg_TRUE_SHEAR()
{
	UpdateDlg_TRUE();
	/////////////////////////////////////////////////////
	//		FOR NODE, GRAB NODE = TARGET NODE
	//		SO case 1 below should be taken out,
	//		we kept it for CURVE, PATCH & SOLID		todo
	/////////////////////////////////////////////////////
	if(m_CreOp != COP_SHEAR)
		return;
	////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:			// pick up TargetNode
			m_XfType	= XT_XFORMS;
			m_bNoShear	= FALSE;
			////////////////////
			break;
		case 1:		// m_ShearPt ( Grab Pt.)
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
					m_wShearPt.x	= m_X;
					m_wShearPt.y	= m_Y;
					m_wShearPt.z	= m_Z;		// also for other Coord
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
		case 2:		// m_Scale Values
			m_bDirect	= GetCreOpDlg()->m_bDirect;	// both for Translation & Rotation & Reflection
			m_bDominant	= GetCreOpDlg()->m_bDominant;
			///////////
			m_X = GetCreOpDlg()->m_X;
			m_Y = GetCreOpDlg()->m_Y;
			m_Z = GetCreOpDlg()->m_Z;
			/////////////////////////
			m_wShear.x	= m_X;
			m_wShear.y	= m_Y;
			m_wShear.z	= m_Z;		// also for other Coord
			//////
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

void CNodCreOp::UpdateDlg_FALSE_XLATE()
{
	if(m_CreOp != COP_TRANSLATE)
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

void CNodCreOp::UpdateDlg_FALSE_ROTATE()
{
	if(m_CreOp != COP_ROTATE)
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
		strCurr = "Spawn by Rotation: ";
	///////////////////
	switch(m_nInfoDone)
	{
		case 1:		// Grab Node	NOT NEEDED FOR NODE:It is here for copy to CURVE
					//				and PATCH and SOLID
			//////
			if(GetCreOpDlg()->m_bDirCos)
				break;
			////////////////////////////
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
					strCurr += "TYPE in@Rotate_About Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Rotate_About Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Rotate_About Node";
			break;
		case 2:			// Either Rotation Value (Direct) or Direction Cosine Nodes 	
			GetCreOpDlg()->GetDlgItem(IDC_DIRCOS)->EnableWindow(FALSE); // Origin Always False Now On
			//////
			if(GetCreOpDlg()->m_bAngleIn)	// Angle In
			{
				m_bDirect	= TRUE;
				m_bDominant = TRUE;			// force DialogBox
				GetCreOpDlg()->m_bDirect	= m_bDirect;
				GetCreOpDlg()->m_bDominant	= m_bDominant;
				////////////////////
				m_bDlgExpect = TRUE;
				///
				GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE);
				GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
				GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
				//////////
				m_bOrigin = FALSE;
				GetCreOpDlg()->m_bDirCos	= m_bOrigin;
				//////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				GetCreOpDlg()->GetDlgItem(IDC_TRANHEAD)->SetWindowText(""); // Grab At
				/////
				strCurr += "TYPE in@Rotations in Dialog Box";
				///////
				GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Angles(Deg)");
				GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
				GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
				GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
				GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			}
			else	// Not Direct Angle, So Parallel
			{
				//////////////////
				if(GetCreOpDlg()->m_bDirect)
				{
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
					/////
					if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
					{
						m_bDominant = TRUE;
						m_bOrigin	= m_bDirect;
						////////////////////////
						m_bDlgExpect = TRUE;
						////////////////////
						GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
						//
						if(m_SpnType == SPN_ROT_ABT_LINE)
							strCurr = "TYPE in Line_Node_1 Coords. or SELECT@a Rotation Axis in Dialog Box";
						else
						if(m_SpnType == SPN_ROT_REF_2_TAR)
							strCurr = "TYPE in Ref_Node_1 Coords. or SELECT@a Rotation Axis in Dialog Box";
						///////
						GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
						GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
						GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
						GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
						GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
						GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
						//
						GetCreOpDlg()->GetDlgItem(IDC_AXIS)->SetWindowText("Axis");
						GetCreOpDlg()->GetDlgItem(IDC_AXIS)->EnableWindow(TRUE);

					}
					else
					{
						//
						if(m_SpnType == SPN_ROT_ABT_LINE)
							strCurr += "CLICK in@Line_Node_1 Coords.";
						else
						if(m_SpnType == SPN_ROT_REF_2_TAR)
							strCurr += "CLICK in@Ref_Node_1 Coords.";
						///////
						GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
						GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
					}
				}
				else	// Node Input
				{
					//
					if(m_SpnType == SPN_ROT_ABT_LINE)
						strCurr += "CLICK On@Rotation_Line_defining Ist Node";
					else
					if(m_SpnType == SPN_ROT_REF_2_TAR)
						strCurr += "CLICK On@Reference_Line_defining Ist Node";
					///////
				}
			}
			break;
		case 3:
			GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE); // Now On
			if(m_bAngleIn || m_bAxis)
			{
				strCurr = "Ready with other Info.?@Click Right Button";
				/////////////////////////////////////////////////////// Enable Z-coord DlgItem
				if(m_bAxis)
				{
					GetCreOpDlg()->GetDlgItem(IDC_AXIS)->SetWindowText("");
					GetCreOpDlg()->GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
					////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Degree");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Angle");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->SetWindowText("");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->SetWindowText("");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->SetFocus();
				}					
				break;
			}
			//////////////////
			if(GetCreOpDlg()->m_bDirect)
			{
				////////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDominant = TRUE;
					m_bDirect	= TRUE;
					////////////////////////
					m_bDlgExpect = TRUE;
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					//
					if(m_SpnType == SPN_ROT_ABT_LINE)
						strCurr += "TYPE in@Line_Node_2 Coords in Dialog Box";
					else
					if(m_SpnType == SPN_ROT_REF_2_TAR)
						strCurr += "TYPE in@Ref_Node_2 Coords in Dialog Box";
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
					//
					if(m_SpnType == SPN_ROT_ABT_LINE)
						strCurr += "CLICK in@Line_Node_2 Coords.";
					else
					if(m_SpnType == SPN_ROT_REF_2_TAR)
						strCurr += "CLICK in@Ref_Node_2 Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else	// Node Input
			{
				//
				if(m_SpnType == SPN_ROT_ABT_LINE)
					strCurr += "CLICK in@Rotation_Line_defining 2nd Node";
				else
				if(m_SpnType == SPN_ROT_REF_2_TAR)
					strCurr += "CLICK in@Reference_Line_defining 2nd Node";
				///////
			}
			///////
			break;
		case 4:
			GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE); // Now On
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE)
			{
				strCurr = "Ready with other Info.?@Click Right Button";
				break;
			}
			//////////////////
			if(GetCreOpDlg()->m_bDirect)
			{
				////////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDominant = TRUE;
					m_bDirect	= TRUE;
					////////////////////////
					m_bDlgExpect = TRUE;
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Target_Node_1 Coords in Dialog Box";
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
					strCurr += "CLICK in@Target_Node_1 Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else	// Node Input
				strCurr += "CLICK in@Target_Line_defining Ist Node";
				///////
			break;
		case 5:
			GetCreOpDlg()->GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE); // Now On
			if(m_bAngleIn)
			{
				strCurr = "Ready with other Info.?@Click Right Button";
				break;
			}
			//////////////////
			if(GetCreOpDlg()->m_bDirect)
			{
				////////////////////
				GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
				/////
				if(GetCreOpDlg()->m_bDominant) // Dialog Input Dominant over Mouse
				{
					m_bDominant = TRUE;
					m_bDirect	= TRUE;
					////////////////////////
					m_bDlgExpect = TRUE;
					////////////////////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Target_Node_2 Coords in Dialog Box";
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
					strCurr += "CLICK in@Target_Node_2 Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else	// Node Input
				strCurr += "CLICK in@Target_Line_defining 2nd Node";
				///////
			break;
		case 6:
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

void CNodCreOp::UpdateDlg_FALSE_SCALE()
{
	if(m_CreOp != COP_SCALE)
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
		strCurr = "Spawn by Scaling: ";
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
					strCurr += "TYPE in@Scale_About Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Scale_About Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Scale_About Node";
			break;
		case 2:			
			//////
			m_bDirect	= TRUE;
			m_bDominant = TRUE;			// force DialogBox
			GetCreOpDlg()->m_bDirect	= m_bDirect;
			GetCreOpDlg()->m_bDominant	= m_bDominant;
			////////////////////
			m_bDlgExpect = TRUE;
			//////////////////
			GetCreOpDlg()->m_bDirect	= TRUE;	// Force type in Scale
			GetCreOpDlg()->m_bDominant	= TRUE;	// Force type in Scale
			GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
			GetCreOpDlg()->GetDlgItem(IDC_DOMINANT)->EnableWindow(FALSE);
			//////////////////
			GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
			/////
			strCurr += "TYPE in@Scale Factors in Dialog Box";
			///////
			GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("ScaleFactors");
			GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
			GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
			GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
			GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
//			m_bDirect	= FALSE;
//			m_bDominant = FALSE;			// force DialogBox
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

void CNodCreOp::UpdateDlg_FALSE_SHEAR()
{
	// NOT APPLICABLE FOR  Node & Curve
	////////////////////////////////////
	if(m_CreOp != COP_SHEAR)
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
		strCurr = "Spawn by Shearing: ";
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
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coords");
					strCurr += "TYPE in@Shear_About Node Coords. in Dialog Box";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
					GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
					GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
				}
				else
				{
					strCurr += "CLICK in@Shear_About Node Coords.";
					///////
					GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("Coord");
					GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Third");
				}
			}
			else
				strCurr += "CLICK On@ A Shear_About Node";
			break;
		case 2:			
			//////
			m_bDirect	= TRUE;
			m_bDominant = TRUE;			// force DialogBox
			GetCreOpDlg()->m_bDirect	= m_bDirect;
			GetCreOpDlg()->m_bDominant	= m_bDominant;
			//////////////////
			GetCreOpDlg()->m_bDirect	= TRUE;	// Force type in Scale
			GetCreOpDlg()->m_bDominant	= TRUE;	// Force type in Scale
			GetCreOpDlg()->GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
			//////////////////
			GetCreOpDlg()->GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
			/////
			strCurr += "TYPE in@Shear Factors in Dialog Box";
			///////
			GetCreOpDlg()->GetDlgItem(IDC_COORDHEAD)->SetWindowText("ScaleFactors");
			GetCreOpDlg()->GetDlgItem(IDC_XHEAD)->SetWindowText("X");
			GetCreOpDlg()->GetDlgItem(IDC_YHEAD)->SetWindowText("Y");
			GetCreOpDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			GetCreOpDlg()->GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
			GetCreOpDlg()->GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			break;
		case 3:
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

int CNodCreOp::LeftUp_GetNode_ROTATE(POINT point, BOOL bCNode)
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
				if(m_bOrigin)
				{
					m_RotPtID	= "";	// Origin
					m_wRotPt.x	= 0.0;
					m_wRotPt.y	= 0.0;
					m_wRotPt.z	= 0.0;
				}
				else
				{
					m_RotPtID	= m_pCurrentNode->GetObjectID();
					m_wRotPt	= *(m_pCurrentNode->GetLocalPos());
				}
				///
				WORtoWOP(&m_wRotPt,&m_wRotPt);// change to physical like in Dlg Input
				break;
			case 2:
				if(m_bAngleIn)
					return -1;
				//////////////
				m_FromID_R		= m_pCurrentNode->GetObjectID();
				m_wFrom_R		= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wFrom_R,&m_wFrom_R);// change to physical like in Dlg Input
				break;
			case 3:
				if(m_bAngleIn || m_bAxis)
					return -1;
				//////////////
				m_ToID_R		= m_pCurrentNode->GetObjectID();
				m_wTo_R			= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wTo_R,&m_wTo_R);// change to physical like in Dlg Input
				break;
			case 4:
				if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
					return -1;
				//////////////
				m_FromID_T		= m_pCurrentNode->GetObjectID();
				m_wFrom_T		= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wFrom_T,&m_wFrom_T);// change to physical like in Dlg Input
				break;
			case 5:
				if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
					return -1;
				//////////////
				m_ToID_T		= m_pCurrentNode->GetObjectID();
				m_wTo_T			= *(m_pCurrentNode->GetLocalPos());
				WORtoWOP(&m_wTo_T,&m_wTo_T);// change to physical like in Dlg Input
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
				m_RotPtID	= "";
				m_wRotPt	= m_wLoc;
				WORtoWOP(&m_wRotPt,&m_wRotPt);// change to physical like in Dlg Input
				break;
			case 2:
				m_FromID_R		= "";
				m_wFrom_R		= m_wLoc;
				WORtoWOP(&m_wFrom_R,&m_wFrom_R);// change to physical like in Dlg Input
				break;
			case 3:
				m_ToID_R		= "";
				m_wTo_R			= m_wLoc;
				WORtoWOP(&m_wTo_R,&m_wTo_R);// change to physical like in Dlg Input
				break;
			case 4:
				m_FromID_T		= "";
				m_wFrom_T		= m_wLoc;
				WORtoWOP(&m_wFrom_R,&m_wFrom_R);// change to physical like in Dlg Input
				break;
			case 5:
				m_ToID_T		= "";
				m_wTo_T			= m_wLoc;
				WORtoWOP(&m_wTo_R,&m_wTo_R);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	// NO Hit
	///////////////////////////////////////// From & To Same,INADMISSIBLE
	if(m_nInfoDone == 3)	// To Node
	{
		C3DMath	Math3D;
		///////////////
		if(Math3D.AreSame_WORLD(&m_wFrom_R,&m_wTo_R,pHitNet->GetDblRatio()))
   		{
			if( m_SpnType == SPN_ROT_ABT_LINE)
				AfxMessageBox("Degenerate Rotation Line:\nSame Node More than Once!");
			else
			if( m_SpnType == SPN_ROT_ABT_LINE)
				AfxMessageBox("Degenerate Reference Line:\nSame Node More than Once!");
			m_nInfoDone--;
			return -2;
		}
	}
	///////////////////////////////////////// From & To Same,INADMISSIBLE
	if(m_nInfoDone == 5)	// To Node
	{
		C3DMath	Math3D;
		///////////////
		if(Math3D.AreSame_WORLD(&m_wFrom_T,&m_wTo_T,pHitNet->GetDblRatio()))
   		{
			AfxMessageBox("Degenerate Target Line:\nSame Node More than Once!");
			m_nInfoDone--;
			return -2;
		}
	}
	//////////////////////////////////////
	return 0;
}

int CNodCreOp::LeftUp_GetNode_SCALE(POINT point, BOOL bCNode)
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
				m_ScalePtID		= m_pCurrentNode->GetObjectID();
				m_wScalePt		= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wScalePt,&m_wScalePt);// change to physical like in Dlg Input
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
				m_ScalePtID	= "";
				m_wScalePt	= m_wLoc;
				WORtoWOP(&m_wScalePt,&m_wScalePt);// change to physical like in Dlg Input
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	// NO Hit
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

int CNodCreOp::LeftUp_GetNode_SHEAR(POINT point, BOOL bCNode)
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
				m_ShearPtID	= m_pCurrentNode->GetObjectID();
				m_wShearPt	= *(m_pCurrentNode->GetLocalPos());
				///
				WORtoWOP(&m_wShearPt,&m_wShearPt);// change to physical like in Dlg Input
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
				m_ShearPtID	= "";
				m_wShearPt	= m_wLoc;
				break;
			default:
				return -1;
		}
	}
	else
		return nResult;	//NO Hit
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

int CNodCreOp::LeftUp_ROTATE_NOD(POINT point)
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
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 3://		// To Rot Direction
			if(m_bAngleIn || m_bAxis)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 4://		// From Rot Direction if Not AngleIn
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 5://		// To Rot Direction
			if(m_bAngleIn || m_SpnType == SPN_ROT_ABT_LINE || m_bAxis)
				return -1;
			//////////////
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_ROTATE(point,FALSE);		// try INODE
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

int CNodCreOp::LeftUp_SCALE_NOD(POINT point)
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
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SCALE(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SCALE(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
		case 2:		// Force Dialog entry
			return -2;
		default:
			break;
	}
	return -1;
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

int CNodCreOp::LeftUp_SHEAR_NOD(POINT point)
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
			m_bCorINodeOpDone = FALSE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,TRUE);		// try CNODE
			if(nResult == 0 || nResult == -2)
				return nResult;
			//
			m_bCorINodeOpDone = TRUE;
			///
			nResult = LeftUp_GetNode_SHEAR(point,FALSE);	// try INODE
			if(nResult < 0)
				return nResult;
			//
			return 0;
			////////
		case 2:		// Force Dialog entry
			return -2;
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

		case COP_ROTATE: 

			if(m_bAngleIn || m_bAxis)
			{
				if(m_nInfoDone > 2)
					return;
			}
			else
			{
				switch(m_SpnType)
				{
					case SPN_ROT_REF_2_TAR: 
						if(m_nInfoDone > MAX_INFO_ROTATE)
							return;
						break;
					case SPN_ROT_ABT_LINE: 
						if(m_nInfoDone > MAX_INFO_ROT_LINE)
							return;
						break;
					default:
						AfxMessageBox(
							"Internal ERROR:\nCNodCreOp::ElementLeftUp_NOD\nINVALID m_SpnType");
						return;

				}
			}
			////////////////
			UpdateDlg_TRUE_ROTATE();
			//////////////////
			if((m_nInfoDone == 1) && (m_bOrigin))
				///////
				m_nInfoDone++;
			else
			//////////////////////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_ROTATE_NOD(point)<0)
				{
					Terminate_NOD(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_ROTATE();
			///////
			return;

		case COP_SCALE: 

			if(m_nInfoDone > MAX_INFO_SCALE)
				return;
			////////////////
			UpdateDlg_TRUE_SCALE();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_SCALE_NOD(point)<0)
				{
					Terminate_NOD(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_SCALE();
			///////
			return;

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

		case COP_SHEAR:

			if(m_nInfoDone > MAX_INFO_SHEAR)
				return;
			////////////////
			UpdateDlg_TRUE_SHEAR();
			//////////////////
			if(!(m_bDirect && m_bDominant) )
			{
				if(LeftUp_SHEAR_NOD(point)<0)
				{
					Terminate_NOD(TRUE);
					return;
				}
			}
			/////////////
			m_nInfoDone++;
				UpdateDlg_FALSE_SHEAR();
				///////
				return;
		////////////////////////////////////////////////// SPAWN	
		case COP_SPAWN:				// 
			///////		
			if(LeftUp_NSPAWN(point)<0)
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
//				UpdateDlg_FALSE_SPAWN();
				break;
			}
			///////////////////	
			break;
		////////////////////////////////////////////////// STITCH	
		case COP_STITCH:				// 
			///////		
//			LeftUp_NSTITCH(point);
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
		//////////////////////////////////////////////////// 
		//													Virtual Nodes cannot be edited/Moved
		if(pDrNode->IsVirtual())
			return -1;
		////////////////////////
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
		AfxMessageBox("ERROR:\nCNodCreOp::LeftUp_NSpawn\nShowNodeToSpawn Problem");
		return -1;
	}
	////////////////////////////
	strCurr = "Ready for Spawning a Node@";
	strCurr += "Click on a NODE to Spawn";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////
	if(nResult == -2)		// Cancel
		return -2;
	///
	return 0;
}

int CNodCreOp::ShowNodeToSpawn(CDrNode* pParentNode,BOOL bUsingDlg)	// COPY ON
{
	int				nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
    /////////////////////////////////////////////////////////////////////////// NO New Object
	if(!pBool->IsSpawnOn())
	{
		/////////////////////////////////////////////////////////// XForm : Prep
		m_NDoneList.RemoveAll();
		m_CDoneList.RemoveAll();
		m_PDoneList.RemoveAll();
		m_SDoneList.RemoveAll();
		m_ODoneList.RemoveAll();
		////////////////////////
		nResult = ShowNodeToSpawnCopyOff(pParentNode,bUsingDlg);
		////////////////////////
		return nResult;
	}
	/////////////////////////////////////////////////////////////////////////// New Object
//	CDListMgr* pList;
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	BOOL bCNode	= pParentNode->IsControlNode();
	if(bCNode)
		m_pSpawnedNode	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,CNODE));
	else
		m_pSpawnedNode	= (CDrNode*)(pObjectMgr->AddToDataBase(nActiveIndex,NODE));
	///
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(m_pSpawnedNode,CNODE,FALSE);	// not ready yet
	else
		pObjectMgr->ShowObject_On_Off(m_pSpawnedNode,NODE,FALSE);
	///////////////////								// TRUE = Internally Generated
	if(!m_pSpawnedNode)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		//////////////////////////
		return -1;//
	}
	/////////////////////////////////////////////////////////////// Using CMI_NSPN
	CMI_NSPN MI_NSPN;
	//////////////////////////////////////////////
	if(bUsingDlg)
	{
		m_pSpawnedNode->SetObjectID(m_ObjID);
		///
		nResult = MI_NSPN.SpawnNodeShowingDlg(m_pSpawnedNode,pParentNode,pParentNode, NODE);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_NSPN.SpawnNodeWithoutDlg(m_pSpawnedNode,pParentNode,pXFMat,&m_SpawnedID,
												bCNode,pParentNode,NODE); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		if(bCNode)
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CNODE);
		else
			pObjectMgr->DeleteFromDataBase(nActiveIndex, NODE);
		m_pSpawnedNode	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////////////// Label
	int nLabelIndex;
	CMI_GangN GangN;
	CDrLabel* pLabel = GangN.CreateNodeLabel(m_pSpawnedNode, nLabelIndex,LEVEL_GRAPA);//
	/////////////////////////////////////// Reciprocate
	m_pSpawnedNode->GetLabelList()->AddTail(pLabel);
	///////////////////////////////////////////////////////////////////
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(m_pSpawnedNode,CNODE,TRUE);	// ready
	else
		pObjectMgr->ShowObject_On_Off(m_pSpawnedNode,NODE,TRUE);
	///////////////////////////////
	return 0;
}	 

int CNodCreOp::ShowNodeToSpawnCopyOff(CDrNode* pParentNode,BOOL bUsingDlg)
{
	int	nResult;
	int index;
	///////////////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
//	CDListMgr* pList;
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	///////////////////
	pObjectMgr->SetActiveObjectType(NODE);
	/////////////////////////////////////////////
	if(!(pParentNode->GetCurveList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Node-dependent CURVES
		nResult = NodeDependent_SpawnConnectedObjects_CopyOff(pParentNode,bUsingDlg,CURVE);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	/////////////////////////////////////////////
	if(!(pParentNode->GetPatchList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Node-dependent PATCHES
		nResult = NodeDependent_SpawnConnectedObjects_CopyOff(pParentNode,bUsingDlg,PATCH);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	/////////////////////////////////////////////
	if(!(pParentNode->GetSolidList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Node-dependent SOLIDS
		nResult = NodeDependent_SpawnConnectedObjects_CopyOff(pParentNode,bUsingDlg,SOLID);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	/////////////////////////////////////////////
	if(!(pParentNode->GetObj3DList())->IsEmpty())
	{
		/////////////////////////////////////////////////////////// XForm Node-dependent OBJ3DS
		nResult = NodeDependent_SpawnConnectedObjects_CopyOff(pParentNode,bUsingDlg,OBJ3D);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
	}
	/////////////////////////////////////////////
	index = m_NDoneList.GetObjectIndex(pParentNode);
	if(index<0)	// not done yet
	{
		/////////////////////////////////////////////////////////// XForm Current Node
		nResult = NodeSpawnCopyOff(pParentNode,bUsingDlg);
		///
		if(nResult == -1)
			goto ERRORHANDLER;
		/////////////////////
		m_NDoneList.InsertObject(pParentNode);
	}
	///////////////////////////////
	return 0;

ERRORHANDLER:
	AfxMessageBox("Internal ERROR\nCNodCreOp::ShowNodeToSpawnCopyOff");
	/////////////////////////////////////// Reset
	m_nInfoDone		= 0;
	m_bDone			= TRUE;	// 
	//////////////////////////
	m_pSpawnedNode	= NULL;
	//////////////////////////
	return nResult;//
	////////
}

int CNodCreOp::NodeSpawnCopyOff(CDrNode* pParentNode,BOOL bUsingDlg)
{
	int nResult;
	C3DMath		Math3D;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	/////////////////////////////////////////////////
	BOOL	bCNode = pParentNode->IsControlNode();
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,CNODE,FALSE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,NODE,FALSE);
	///////////////////////////////
	CDrNode* pSpawnedNode = pParentNode;
	/////////////////////////////////////
	CMI_NSPN MI_NSPN;
	///
	MI_NSPN.SetNDoneList(&m_NDoneList);
	MI_NSPN.SetCDoneList(&m_CDoneList);
	MI_NSPN.SetPDoneList(&m_PDoneList);
	MI_NSPN.SetSDoneList(&m_SDoneList);
	MI_NSPN.SetODoneList(&m_ODoneList);
	//////////////////////////////////////
	m_ObjID = pParentNode->GetObjectID();
	//////////////////////////////////////////////
	if(bUsingDlg)
	{
		///
		nResult = MI_NSPN.SpawnNodeShowingDlg((CDrNode*)pSpawnedNode,pParentNode,pParentNode,NODE);
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		////
		nResult = MI_NSPN.SpawnNodeWithoutDlg(pSpawnedNode,pParentNode,pXFMat,&m_ObjID,
												bCNode,pParentNode,NODE); 
	}
	if(nResult<0)
	{
		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		////////////////////////// Delete
		m_pSpawnedNode	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(pParentNode,CNODE,TRUE);
	else
		pObjectMgr->ShowObject_On_Off(pParentNode,NODE,TRUE);
	//////////////////////
	return nResult;
}

int CNodCreOp::NodeDependent_SpawnConnectedObjects_CopyOff(CDrNode* pCurrentNode,BOOL bUsingDlg,
																					UINT nObjType)
{
	/////////////////////////////////////////////////////////// XForm Node-dependent OBJECTS
	int nResult = 0;
	////////////////
	CDListMgr* pList;
	int i,nCount;
	//////////////////////////////////////////////// Objects
	switch(nObjType)
	{
		case CURVE:
			pList	= pCurrentNode->GetCurveList();
			break;
		case PATCH:
			pList	= pCurrentNode->GetPatchList();
			break;
		case SOLID:
			pList	= pCurrentNode->GetSolidList();
			break;
		case OBJ3D:
			pList	= pCurrentNode->GetObj3DList();
			break;
		default:
			nResult = -1;
			return nResult;
	}
	///
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CObject* pObject	= pList->GetObject(i);
#ifdef _DEBUG
		CString ObjID = ((CDrObject*)pObject)->GetObjectID();
#endif
		////////////////
		if(pObject)
		{
			switch(nObjType)
			{
				case CURVE:
					nResult = CurTopo_SpawnConnectedCurves_CopyOff((CDrCurve*)pObject,bUsingDlg);
					break;
				case PATCH:
					nResult = PatTopo_SpawnConnectedPatches_CopyOff((CDrPatch*)pObject,bUsingDlg);
					break;
				case SOLID:
					nResult = SolTopo_SpawnConnectedSolids_CopyOff((CDrSolid*)pObject,bUsingDlg);
					break;
				case OBJ3D:
					nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff((CDrObj3D*)pObject,bUsingDlg);
					break;
				default:
					nResult = -1;
					return nResult;
			}
			///
			if(nResult == -1)
			{
				AfxMessageBox(
					"Internal ERROR\nCNodCreOp::NodeDependent_SpawnConnectedObjects_CopyOff");
				return nResult;
			}
		}
	}
	/////////////////////
	return nResult;
}

int CNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff(CDrCurve* pCurrentCurve,BOOL bUsingDlg)
{
#ifdef _DEBUG
		CString ObjID = pCurrentCurve->GetObjectID();
		CString strBum;
		if(ObjID == "C5")
			strBum = "Bum String C5";
#endif
	// Walk the graph connected to the given curve
	////////////////
	int nResult = 0;
	CDListMgr* pList;
	int i,nCount;
	////////////////
	int index	= m_CDoneList.GetObjectIndex(pCurrentCurve);
	if(index<0) // NOT DONE yet
	{
		/////////////////////////////////////////////////////////// Spawn Curve(All Lists)
		nResult = ShowObjectToSpawnCopyOff((CDrObject*)pCurrentCurve,bUsingDlg,CURVE);
		if(nResult == -1)
		{
			AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_2");
			return nResult;
		}
		m_CDoneList.InsertObject(pCurrentCurve);
	}
	/////////////////////////////////////////////////////////// XForm Connecting CURVES
	pList	= pCurrentCurve->GetCurveList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrCurve* pCurve	= (CDrCurve*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pCurve->GetObjectID();
		CString strBum;
		if(ObjID == "C5")
			strBum = "Bum String C5";
#endif
		int index			= m_CDoneList.GetObjectIndex(pCurve);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// recursion
			int nResult = CurTopo_SpawnConnectedCurves_CopyOff(pCurve,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_3");
				return nResult;
			}
			m_CDoneList.InsertObject(pCurve);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting PATCHES
	pList	= pCurrentCurve->GetPatchList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrPatch* pObject	= (CDrPatch*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_PDoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = PatTopo_SpawnConnectedPatches_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_4");
				return nResult;
			}
			m_PDoneList.InsertObject(pObject);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting SOLIDS
	pList	= pCurrentCurve->GetSolidList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrSolid* pObject	= (CDrSolid*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_SDoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = SolTopo_SpawnConnectedSolids_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_5");
				return nResult;
			}
			m_SDoneList.InsertObject(pObject);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting OBJ3DS
	pList	= pCurrentCurve->GetObj3DList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrObj3D* pObject	= (CDrObj3D*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_ODoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_6");
				return nResult;
			}
			m_ODoneList.InsertObject(pObject);
		}
	}
	///////
	return nResult;
}

int CNodCreOp::PatTopo_SpawnConnectedPatches_CopyOff(CDrPatch* pCurrentPatch,BOOL bUsingDlg)
{
#ifdef _DEBUG
		CString ObjID = pCurrentPatch->GetObjectID();
#endif
	// Walk the graph connected to the given patch
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////
	int nResult = 0;
	CDListMgr* pList;
	int i,nCount;
	////////////////
	int index	= m_PDoneList.GetObjectIndex(pCurrentPatch);
	if(index<0) // NOT DONE yet
	{
		/////////////////////////////////////////////////////////// Spawn Patch(rest of Lists)
		pObjectMgr->ShowObject_On_Off(pCurrentPatch,PATCH,FALSE);
		nResult = ShowObjectToSpawnCopyOff((CDrObject*)pCurrentPatch,bUsingDlg,PATCH);
		if(nResult == -1)
		{
			AfxMessageBox("Internal ERROR\nCNodCreOp::PatTopo_SpawnConnectedPatches_CopyOff_2");
			return nResult;
		}
		pObjectMgr->ShowObject_On_Off(pCurrentPatch,PATCH,TRUE);
		m_PDoneList.InsertObject(pCurrentPatch);
	}
	/////////////////////////////////////////////////////////// XForm Connecting PATCHES
	pList	= pCurrentPatch->GetPatchList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrPatch* pPatch	= (CDrPatch*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pPatch->GetObjectID();
#endif
		int index			= m_PDoneList.GetObjectIndex(pPatch);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// recursion
			int nResult = PatTopo_SpawnConnectedPatches_CopyOff(pPatch,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::PatTopo_SpawnConnectedPatches_CopyOff_3");
				return nResult;
			}
			m_PDoneList.InsertObject(pPatch);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting SOLIDS
	pList	= pCurrentPatch->GetSolidList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrSolid* pObject	= (CDrSolid*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_SDoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = SolTopo_SpawnConnectedSolids_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::PatTopo_SpawnConnectedPatches_CopyOff_5");
				return nResult;
			}
			m_SDoneList.InsertObject(pObject);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting OBJ3DS
	pList	= pCurrentPatch->GetObj3DList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrObj3D* pObject	= (CDrObj3D*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_ODoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::PatTopo_SpawnConnectedPatches_CopyOff_6");
				return nResult;
			}
		m_ODoneList.InsertObject(pObject);
		}
	}
	///////
	return nResult;
}

int CNodCreOp::SolTopo_SpawnConnectedSolids_CopyOff(CDrSolid* pCurrentSolid,BOOL bUsingDlg)
{
#ifdef _DEBUG
		CString ObjID = pCurrentSolid->GetObjectID();
#endif
	// Walk the graph connected to the given Solid
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////
	int nResult = 0;
	CDListMgr* pList;
	int i,nCount;
	////////////////
	int index	= m_SDoneList.GetObjectIndex(pCurrentSolid);
	if(index<0) // NOT DONE yet
	{
		/////////////////////////////////////////////////////////// Spawn Solid(rest of Lists)
		pObjectMgr->ShowObject_On_Off(pCurrentSolid,SOLID,FALSE);
		nResult = ShowObjectToSpawnCopyOff((CDrObject*)pCurrentSolid,bUsingDlg,SOLID);
		if(nResult == -1)
		{
			AfxMessageBox("Internal ERROR\nCNodCreOp::SolTopo_SpawnConnectedSolids_CopyOff_2");
			return nResult;
		}
		pObjectMgr->ShowObject_On_Off(pCurrentSolid,SOLID,TRUE);
		m_SDoneList.InsertObject(pCurrentSolid);
	}
	/////////////////////////////////////////////////////////// XForm Connecting SOLIDS
	pList	= pCurrentSolid->GetSolidList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrSolid* pSolid	= (CDrSolid*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pSolid->GetObjectID();
#endif
		int index			= m_SDoneList.GetObjectIndex(pSolid);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// recursion
			int nResult = SolTopo_SpawnConnectedSolids_CopyOff(pSolid,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::SolTopo_SpawnConnectedSolids_CopyOff_3");
				return nResult;
			}
			m_SDoneList.InsertObject(pSolid);
		}
	}
	/////////////////////////////////////////////////////////// XForm Connecting OBJ3DS
	pList	= pCurrentSolid->GetObj3DList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrObj3D* pObject	= (CDrObj3D*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObject->GetObjectID();
#endif
		int index			= m_ODoneList.GetObjectIndex(pObject);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// 
			int nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff(pObject,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::SolTopo_SpawnConnectedSolids_CopyOff_6");
				return nResult;
			}
			m_ODoneList.InsertObject(pObject);
		}
	}
	///////
	return nResult;
}

int CNodCreOp::O3DTopo_SpawnConnectedObj3Ds_CopyOff(CDrObj3D* pCurrentObj3D,BOOL bUsingDlg)
{
#ifdef _DEBUG
		CString ObjID = pCurrentObj3D->GetObjectID();
#endif
	// Walk the graph connected to the given Obj3D
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////
	int nResult = 0;
	CDListMgr* pList;
	int i,nCount;
	////////////////
	int index	= m_ODoneList.GetObjectIndex(pCurrentObj3D);
	if(index<0) // NOT DONE yet
	{
		/////////////////////////////////////////////////////////// Spawn Obj3D(rest of Lists)
		pObjectMgr->ShowObject_On_Off(pCurrentObj3D,OBJ3D,FALSE);
		nResult = ShowObjectToSpawnCopyOff((CDrObject*)pCurrentObj3D,bUsingDlg,OBJ3D);
		if(nResult == -1)
		{
			AfxMessageBox("Internal ERROR\nCNodCreOp::O3DTopo_SpawnConnectedSolids_CopyOff_2");
			return nResult;
		}
		pObjectMgr->ShowObject_On_Off(pCurrentObj3D,OBJ3D,TRUE);
		m_ODoneList.InsertObject(pCurrentObj3D);
	}
	/////////////////////////////////////////////////////////// XForm Connecting OBJ3DS
	pList	= pCurrentObj3D->GetObj3DList(); 
	nCount	= pList->GetCount();
	///////////
	for(i=0;i<nCount;i++)
	{
		CDrObj3D* pObj3D	= (CDrObj3D*)(pList->GetObject(i));
#ifdef _DEBUG
		CString ObjID = pObj3D->GetObjectID();
#endif
		int index			= m_ODoneList.GetObjectIndex(pObj3D);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// recursion
			int nResult = O3DTopo_SpawnConnectedObj3Ds_CopyOff(pObj3D,bUsingDlg);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::O3DTopo_SpawnConnectedObj3Ds_CopyOff_3");
				return nResult;
			}
			m_ODoneList.InsertObject(pObj3D);
		}
	}
	///////
	return nResult;
}

int CNodCreOp::ShowObjectToSpawnCopyOff(CDrObject* pParentObject,BOOL bUsingDlg,UINT nObjType)
{
	int				nResult;
	C3DMath			Math3D;
	///////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(nObjType);
	///////////////////////////////
	CDrObject* pSpawnedObject = pParentObject;
	//////////////////////////////////////// Dont Show, not quite ready
	pObjectMgr->ShowObject_On_Off(pParentObject,nObjType,FALSE);
	//////////////////////////////////////// Spawn
	CMI_OSPN MI_OSPN;
	///
	MI_OSPN.SetNDoneList(&m_NDoneList);
	MI_OSPN.SetCDoneList(&m_CDoneList);
	MI_OSPN.SetPDoneList(&m_PDoneList);
	MI_OSPN.SetSDoneList(&m_SDoneList);
	MI_OSPN.SetODoneList(&m_ODoneList);
	///
//	pSpawnedObject->SetObjectID(m_ObjID);
	///
	if(bUsingDlg)
	{
		/////////////////
		switch(nObjType)
		{
			case CURVE:
				nResult = MI_OSPN.SpawnCurveShowingDlg
							((CDrCurve*)pSpawnedObject,(CDrCurve*)pParentObject,
							(CDrCurve*)pParentObject, nObjType);
				break;
			case PATCH:
				nResult = MI_OSPN.SpawnPatchShowingDlg
							((CDrPatch*)pSpawnedObject,(CDrPatch*)pParentObject,
							(CDrPatch*)pParentObject, nObjType);
				break;
			case SOLID:
				nResult = MI_OSPN.SpawnSolidShowingDlg
							((CDrSolid*)pSpawnedObject,(CDrSolid*)pParentObject,
							(CDrSolid*)pParentObject, nObjType);
				break;
			case OBJ3D:
				nResult = MI_OSPN.SpawnObj3DShowingDlg
							((CDrObj3D*)pSpawnedObject,(CDrObj3D*)pParentObject,
							(CDrObj3D*)pParentObject, nObjType);
				break;
			default:
				nResult = -1;
				return nResult;
		}
		///
	}
	else
	{
		pMATRIX	pXFMat	= m_pMatObj->GetMatrix();
		CString	SpawnID	= m_ObjID;
		/////////////////
		switch(nObjType)
		{
			case CURVE:
				nResult = MI_OSPN.SpawnCurveWithoutDlg
							((CDrCurve*)pSpawnedObject,(CDrCurve*)pParentObject,
							pXFMat,&m_SpawnedID,(CDrCurve*)pParentObject, nObjType);
				break;
			case PATCH:
				nResult = MI_OSPN.SpawnPatchWithoutDlg
							((CDrPatch*)pSpawnedObject,(CDrPatch*)pParentObject,
							pXFMat,&m_SpawnedID,(CDrPatch*)pParentObject, nObjType);
				break;
			case SOLID:
				nResult = MI_OSPN.SpawnSolidWithoutDlg
							((CDrSolid*)pSpawnedObject,(CDrSolid*)pParentObject,
							pXFMat,&m_SpawnedID,(CDrSolid*)pParentObject, nObjType);
				break;
			case OBJ3D:
				nResult = MI_OSPN.SpawnObj3DWithoutDlg
							((CDrObj3D*)pSpawnedObject,(CDrObj3D*)pParentObject,
							pXFMat,&m_SpawnedID,(CDrObj3D*)pParentObject, nObjType);
				break;
			default:
				nResult = -1;
				return nResult;
		}
	}
	///
	if(nResult<0)
	{

		/////////////////////////////////////// Reset
		m_nInfoDone		= 0;
		m_bDone			= TRUE;	// 
		//////////////////////////
		m_pSpawnedCurve	= NULL;
		//////////////////////////
		return nResult;//
	}
	/////////////////////////////////////////////////////////// Refresh RectInvalid Erase
	pObjectMgr->ShowObject_On_Off(pParentObject,nObjType,TRUE);
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

		case COP_ROTATE:

			if(m_SpnType == SPN_ROT_ABT_LINE)
			{
				if(m_nInfoDone<MAX_INFO_ROT_LINE)
					bPreMature = TRUE;
			}
			else
			if(m_SpnType == SPN_ROT_REF_2_TAR)
			{
				if(m_nInfoDone<MAX_INFO_ROTATE)
					bPreMature = TRUE;
			}
			break;

		case COP_SCALE:

			if(m_nInfoDone<MAX_INFO_SCALE)
				bPreMature = TRUE;
			break;

		case COP_REFLECT:

			if(m_nInfoDone<MAX_INFO_REFLECT)
				bPreMature = TRUE;
			break;

		case COP_SHEAR:

			if(m_nInfoDone<MAX_INFO_SHEAR)
				bPreMature = TRUE;
			break;


		case COP_SPAWN:

			if(m_nInfoDone<MAX_INFO_SPAWN)
				bPreMature = TRUE;
			break;


		case COP_STITCH:

			if(m_nInfoDone<MAX_INFO_STITCH)
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

int CNodCreOp::ShowInputInfo_ROTATE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Rotation Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Rotated %s ID = %s\n\n",m_strParentType,m_ObjID); // 
	/////////////////////////////////////
	if(m_bOrigin)
		j += sprintf( buf + j, "\nTo be Rotated About Origin"); // Grab Node
	else
	{
		if(m_RotPtID !="")
			j += sprintf( buf + j, "\nRotate_About Node ID = %s\n",m_RotPtID); // Grab Node
		else
			j += sprintf( buf + j, "\nRotation__About Coords:\n");
	}
	//
	j += sprintf( buf + j, "\n\tX  = %f",m_wRotPt.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wRotPt.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wRotPt.z);
	////
	if(m_bAngleIn)
	{
		j += sprintf( buf + j, "\n\nRotation Values:\n"); // 
		j += sprintf( buf + j, "\n\tabout X-Axis = %f (Degrees)",m_wRot.x);
		j += sprintf( buf + j, "\n\tabout Y-Axis = %f (Degrees)",m_wRot.y);
		j += sprintf( buf + j, "\n\tabout Z-Axis = %f (Degrees)",m_wRot.z);
	}
	else
	{
		//12/29/97
		//////////////////////////////////////////////////////////// Reference Line
		if(m_FromID_R != "")
		{
			if(m_SpnType == SPN_ROT_ABT_LINE)
				j += sprintf( buf + j, "\nRotation Axis Line_From Node ID = %s",m_FromID_R); //
			else
			if(m_SpnType == SPN_ROT_REF_2_TAR)
				j += sprintf( buf + j, "\nReference Line_From Node ID = %s",m_FromID_R); //
		}
		else
		{
			if(m_SpnType == SPN_ROT_ABT_LINE)
				j += sprintf( buf + j, "\nRotation Axis Line_From Coords:");
			else
			if(m_SpnType == SPN_ROT_REF_2_TAR)
				j += sprintf( buf + j, "\nReference Line_From Coords:");
		}
		//
		j += sprintf( buf + j, "\n\tX  = %f",m_wFrom_R.x);
		j += sprintf( buf + j, "\n\tY  = %f",m_wFrom_R.y);
		j += sprintf( buf + j, "\n\tZ  = %f",m_wFrom_R.z);
		///
		if(m_ToID_R != "")
		{
			if(m_SpnType == SPN_ROT_ABT_LINE)
				j += sprintf( buf + j, "\nRotation Axis Line_To Node ID = %s",m_ToID_R); //
			else
			if(m_SpnType == SPN_ROT_REF_2_TAR)
				j += sprintf( buf + j, "\nReference Line_To Node ID = %s",m_ToID_R); //
		}
		else
		{
			if(m_SpnType == SPN_ROT_ABT_LINE)
				j += sprintf( buf + j, "\nRotation Axis Line_To Coords:");
			else
			if(m_SpnType == SPN_ROT_REF_2_TAR)
				j += sprintf( buf + j, "\nReference Line_To Coords:");
		}
		//
		j += sprintf( buf + j, "\n\tX  = %f",m_wTo_R.x);
		j += sprintf( buf + j, "\n\tY  = %f",m_wTo_R.y);
		j += sprintf( buf + j, "\n\tZ  = %f",m_wTo_R.z);
		//////////////////////////////////////////////////////////// Target Line
		if(m_SpnType == SPN_ROT_REF_2_TAR)
		{
			if(m_FromID_T != "")
				j += sprintf( buf + j, "\n\nTarget Line_From Node ID = %s",m_FromID_T); // 
			else
				j += sprintf( buf + j, "\nTarget Line_From Coords:");
			//
			j += sprintf( buf + j, "\n\tX  = %f",m_wFrom_T.x);
			j += sprintf( buf + j, "\n\tY  = %f",m_wFrom_T.y);
			j += sprintf( buf + j, "\n\tZ  = %f",m_wFrom_T.z);
			///
			if(m_ToID_T != "")
				j += sprintf( buf + j, "\n\nTarget Line_To Node ID = %s",m_ToID_T); // 
			else
				j += sprintf( buf + j, "\nTarget Line_To Coords:");
			j += sprintf( buf + j, "\n\tX  = %f",m_wTo_T.x);
			j += sprintf( buf + j, "\n\tY  = %f",m_wTo_T.y);
			j += sprintf( buf + j, "\n\tZ  = %f",m_wTo_T.z);
		}
	}
	///////////////////////////////////////////////////////////////////// Net Rotation
	if(m_bAngleIn)
	{
		j += sprintf( buf + j, "\n\nNet Rotation: "); // 
		//
		j += sprintf( buf + j, "\n\tAbout X_Axis  = %f",m_wRot.x);
		j += sprintf( buf + j, "\n\tAbout Y_Axis  = %f",m_wRot.y);
		j += sprintf( buf + j, "\n\tAbout Z_Axis  = %f",m_wRot.z);
	}
	else
	{
		j += sprintf( buf + j, "\n\nRotation Axis Direction Cosines: "); 
		// 
		j += sprintf( buf + j, "\n\tX_Component  = %f",m_wDir.x);
		j += sprintf( buf + j, "\n\tY_Component  = %f",m_wDir.y);
		j += sprintf( buf + j, "\n\tZ_Component  = %f",m_wDir.z);
		//
		j += sprintf( buf + j, "\n\nRotation About the Axis  = %f",m_wRot.z);
	}
	//12/29/97 end
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

int CNodCreOp::ShowInputInfo_SCALE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Scaling Info ******");
	///
	j += sprintf( buf + j, "\n\nNew Scaled %s ID = %s\n\n",m_strParentType,m_ObjID); // 
	/////////////////////////////////////
	if(m_ScalePtID !="")
		j += sprintf( buf + j, "\n\nScale_About Node ID = %s\n",m_ScalePtID); // Grab Node
	else
		j += sprintf( buf + j, "\n\nScale_About Coords:\n");
	j += sprintf( buf + j, "\n\tX  = %f",m_wScalePt.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wScalePt.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wScalePt.z);
	////
	j += sprintf( buf + j, "\n\nScale Factors:\n");
	j += sprintf( buf + j, "\n\tX  = %f",m_wScale.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wScale.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wScale.z);
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

int CNodCreOp::ShowInputInfo_SHEAR()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Shearing Info ******");
	j += sprintf( buf + j, "\n\nNew Sheared %s ID = %s\n\n",m_strParentType,m_ObjID); // 
	///
	if(m_ShearPtID !="")
		j += sprintf( buf + j, "\n\nShear_About Node ID = %s\n",m_ScalePtID); // Grab Node
	else
	{
		j += sprintf( buf + j, "\n\nShear_About Coords:\n");
		j += sprintf( buf + j, "\n\tX  = %f",m_wShearPt.x);
		j += sprintf( buf + j, "\n\tY  = %f",m_wShearPt.y);
		j += sprintf( buf + j, "\n\tZ  = %f",m_wShearPt.z);
	}
	////
	j += sprintf( buf + j, "\n\nShear Factors:\n");
	j += sprintf( buf + j, "\n\tX  = %f",m_wShear.x);
	j += sprintf( buf + j, "\n\tY  = %f",m_wShear.y);
	j += sprintf( buf + j, "\n\tZ  = %f",m_wShear.z);
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


			case COP_ROTATE:

				nAnswer = ShowInputInfo_ROTATE();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case COP_SCALE:

				nAnswer = ShowInputInfo_SCALE();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case COP_REFLECT:


				nAnswer = ShowInputInfo_REFLECT();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case COP_SHEAR:

				nAnswer = ShowInputInfo_SHEAR();
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

			
		case COP_ROTATE:
						
			
			SetUpLocalM_ROTATE();
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
				UpdateDlg_FALSE_ROTATE();
				break;
			}
			///////////////////	
			break;
		
		case COP_SCALE:
						
			
			SetUpLocalM_SCALE();
			/////////////////////////////
			if(ShowNodeToSpawn(m_pParentNode,FALSE)<0)
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
				UpdateDlg_FALSE_SCALE();
				break;
			}
			///////////////////	
			break;
		
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
		
		case COP_SHEAR:
						
			
			SetUpLocalM_SHEAR();
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
				UpdateDlg_FALSE_SHEAR();
				break;
			}
			///////////////////	
			break;
		

		
		case N_COP_STITCH:
		
			//////////////////////////// 	
			return;



		case N_COP_SPAWN:
		
			//////////////////////////// 	
			return;
		
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
	//	Axis is Saved in m_wDir 
	//		for both SPN_ROT_ABT_LINE and SPN_ROT_REF_2_TAR
	//	Rotation about the Axis is saved in m_wRot.x for RADIAN
	//	Rotation about the Axis is saved in m_wRot.z for DEGREE
	//	m_wRot.y = 9999. Signals Axial Rotation Save
	/////////////////
	C3DMath	Math3D;
	CXForm	XForm;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////
//	WORLD LocFrom,LocTo;
	double One80byPi	= 180./acos(-1.0);
	////////////////////////////////////////////// Find Rotation Axis
	if(m_SpnType == SPN_ROT_REF_2_TAR)
	{
		WORLD Line_R,Line_T,Axis;
		Math3D.Sub3DPts(&m_wTo_R,&m_wFrom_R,&Line_R);
		Math3D.Sub3DPts(&m_wTo_T,&m_wFrom_T,&Line_T);
		Math3D.Normalize(&Line_R,&Line_R);
		Math3D.Normalize(&Line_T,&Line_T);
		Math3D.Cross3DPts(&Line_R,&Line_T,&Axis);
		///////////////////////////////////////// save
		m_wDir.x = Axis.x;
		m_wDir.y = Axis.y;
		m_wDir.z = Axis.z;
		////////////////////////////////////////////// Find Angle about Rotation Axis
		double dAng			= acos(Math3D.Dot3DPts(&Line_R,&Line_T));
		///////////////////////////////////////// save
		m_wRot.x			= dAng;
		m_wRot.z			= dAng * One80byPi;
		m_wRot.y			= 9999.;
	}
	else
	if(m_SpnType == SPN_ROT_ABT_LINE)
	{
		WORLD Axis;
		Math3D.Sub3DPts(&m_wTo_R,&m_wFrom_R,&Axis);
		Math3D.Normalize(&Axis,&Axis);
		///////////////////////////////////////// save
		m_wDir.x = Axis.x;
		m_wDir.y = Axis.y;
		m_wDir.z = Axis.z;
		///////////////////////////////////////// Angle
		// already input & saved in m_wRot.z in dgree 
		///////////////////////////////////////// save in radian
		m_wRot.x			= m_wRot.z/One80byPi;
	}
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

void CNodCreOp::SetUpLocalM_ROTATE()
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////CenterPt Coordinates
	WOPtoWOR(&m_wRotPt,&m_wRotPt);	// World
//	WOPtoWOR(&m_wRot,&m_wRot);		// World	SHOULD NOT
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM,M;			// to translate by CenterPT
	pMATRIX pTM = &TM;
	pMATRIX pM = &M;
	Math3D.GetIdentityMATRIX(pTM);
	Math3D.GetIdentityMATRIX(pM);
	/////////////////////////////////////////////////////////////////////////
	// Tran*Rotate*-Tran
	{
		//////////////////////////////////////////////////////////////////// 
		XForm.Translate(pTM,-m_wRotPt.x,-m_wRotPt.y,-m_wRotPt.z,XF_REPLACE);
		if(m_bAngleIn)
		{
			XForm.Rotate_Y(pM, m_wRot.y, XF_REPLACE );
			XForm.Rotate_X(pM, m_wRot.x, XF_PREMULT );
			XForm.Rotate_Z(pM, m_wRot.z, XF_PREMULT );
		}
		else
		{
			// in CalcRotationFromFromTo():
			//	Axis is Saved in m_wDir
			//	Rotation about the Axis is saved in m_wRot.x for RADIAN
			//	Rotation about the Axis is saved in m_wRot.z for DEGREE
			//	m_wRot.y = 9999. Signals Axial Rotation Save
			////////////////////////////////////////////// Find Matrix
			WORLD p0;
			Math3D.Set3DPts(&p0,0.0,0.0,0.0);
			XForm.RotateAboutLineMATRIX(pM,&p0,&m_wDir,m_wRot.x,XF_REPLACE); // angle in Radian
			//////////////////////////////////////////////////////////// 
		}
		////////////////////////////////////////////////////
		Math3D.F_MultMATRIX(pM,pTM,pM);
		//////////////////////////////
		Math3D.GetIdentityMATRIX(pTM);
		XForm.Translate(pTM,m_wRotPt.x,m_wRotPt.y,m_wRotPt.z,XF_REPLACE);
		////////////////////////////////////////////////////
		Math3D.F_MultMATRIX(pTM,pM,pM);
	}
	/////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	//					Fill Up Mat Matrix
	//////////////////////////////////////////////////////////
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_XFORMS);
	m_pMatObj->SetCreOp(COP_ROTATE);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	/////////////////////////////////// Grab Node
	m_pMatObj->SetRotPtID(m_RotPtID);	
	m_pMatObj->SetRotPt(m_wRotPt);	
	/////////////////////////////////// Rotation
	m_pMatObj->SetAngleIn(m_bAngleIn);
	m_pMatObj->SetDirCos(m_bOrigin);
	m_pMatObj->SetDirCosDirect(m_wDir);
	m_pMatObj->SetFromID(m_FromID_R);
	m_pMatObj->SetFromPt(m_wFrom_R);
	m_pMatObj->SetToID(m_ToID_R);
	m_pMatObj->SetToPt(m_wTo_R);			// same as m_wTran
	m_pMatObj->SetRotation(m_wRot);
	////////////////////////////////
	m_pMatObj->SetNoRot(TRUE);
	m_pMatObj->SetNoTran(FALSE);
	m_pMatObj->SetNoScale(FALSE);
	m_pMatObj->SetNoShear(FALSE);
	////////////////////////////////
	return;
}

void CNodCreOp::SetUpLocalM_SCALE()
{
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////CenterPt Coordinates
	WOPtoWOR(&m_wScalePt,&m_wScalePt);	// World
//	WOPtoWOR(&m_wScale,&m_wScale);		// World SHOULD NOT
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM,M;			// to translate by CenterPT
	pMATRIX pTM = &TM;
	pMATRIX pM = &M;
	Math3D.GetIdentityMATRIX(pTM);
	Math3D.GetIdentityMATRIX(pM);
	/////////////////////////////////////////////////////////////////////////
	if(pWnd->GetCurrentIGenID() == NODE)	// just Scale
	{
		XForm.Scale(pM,m_wScale.x,m_wScale.y,m_wScale.z, XF_REPLACE );
	}
	else		// Tran*Scale*-Tran
	{
		///////////////////////////////////////////////////////// 
		XForm.Translate(pTM,-m_wScalePt.x,-m_wScalePt.y,-m_wScalePt.z,XF_REPLACE);
		XForm.Scale(pM,m_wScale.x,m_wScale.y,m_wScale.z, XF_REPLACE );
		////////////////////////////////////////////////////
		Math3D.F_MultMATRIX(pM,pTM,pM);
		//////////////////////////////
		Math3D.GetIdentityMATRIX(pTM);
		XForm.Translate(pTM,m_wScalePt.x,m_wScalePt.y,m_wScalePt.z,XF_REPLACE);
		////////////////////////////////////////////////////
		Math3D.F_MultMATRIX(pTM,pM,pM);
	}
	/////////////////////////////////////////////////////////////////////////////
	//					Fill Up Mat Matrix
	//////////////////////////////////////////////////////////
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_XFORMS);
	m_pMatObj->SetCreOp(COP_SCALE);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	/////////////////////////////////// Grab Node
	m_pMatObj->SetRotPtID(m_ScalePtID);	
	m_pMatObj->SetRotPt(m_wScalePt);	
	///////////////////////////////////
	m_pMatObj->SetScale(m_wScale);
	////////////////////////////////
	m_pMatObj->SetNoRot(FALSE);
	m_pMatObj->SetNoTran(FALSE);
	m_pMatObj->SetNoScale(TRUE);
	m_pMatObj->SetNoShear(FALSE);
	////////////////////////////////
	return;
}
void CNodCreOp::SetUpLocalM_REFLECT()
{
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////CenterPt Coordinates
	WOPtoWOR(&(m_wSymm[0]),&(m_wSymm[0]));	// World
	WOPtoWOR(&(m_wSymm[1]),&(m_wSymm[1]));	// World
	WOPtoWOR(&(m_wSymm[2]),&(m_wSymm[2]));	// World
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX M;			// to translate by CenterPT
	pMATRIX pM = &M;
	Math3D.GetIdentityMATRIX(pM);
	///////////////////////////////////////////////////////// 
	FormLocalM_Symm(pM);
	//////////////////////////////////////////////////////////
	//					Fill Up Mat Matrix
	//////////////////////////////////////////////////////////
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_SYMMETRIC);
	m_pMatObj->SetSpawnType(m_SpnType);
	m_pMatObj->SetCreOp(COP_REFLECT);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetRotPtID(m_SymmPtID[0]);	
	m_pMatObj->SetRotPt(m_wSymm[0]);	
	m_pMatObj->SetInstanced_Prof(TRUE);
	m_pMatObj->SetFromID(m_SymmPtID[1]);
	m_pMatObj->SetFromPt(m_wSymm[1]);
	m_pMatObj->SetToID(m_SymmPtID[2]);
	m_pMatObj->SetToPt(m_wSymm[2]);			// same as m_wTran
	////////////////////////////////
}

void CNodCreOp::FormLocalM_Symm(pMATRIX pM)
{
/*
	////////////////////////////////////////////////////////////
	//	PLANE: Ax+By+Cz+D=0  or r.N = p
	//
	//		Given:
	//			r = (x,y,z) = Radius Vector (Pt. on the Plane)
	//			N = (A,B,C) = Normal
	//			p = -D		= Distance of the Plane from a
	//							parallel plane thro' Origin
	//		Find:
	//	Local Matrix:
	//	
	//			Ra'	= [I - 2*n*nTrans]Ra + (2*p)n
	//
	//
	//	LOCAL MATRIX: in Homogeneous Coords
	//
	//			1-2*(A**2)		 -2*A*B		 -2*A*C		|	2*p*A
	//			 -2*A*B  		1-2*(B**2)	 -2*B*C		|	2*p*B
	//			 -2*A*C  		 -2*B*C		1-2*(C**2)	|	2*p*C
	//			-------------------------------------------------
	//				0				0			0		|     1	
	//	
	//////////////////////////////////////////////////////////////
*/	
	C3DMath	Math3D;
	CXForm	XForm;
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	////////////////////////////////////////Point on the Plane
	WORLD LocR;
	int index;
	/////////////////////////////////////////////
	index = pDListMgr->GetObjectIndex(NODE,	m_SymmPtID[0]);
	if(index<0)			// Center is Origin
		LocR = m_wSymm[0];
	else
	{	
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////
		LocR = *(pNode->GetLocalPos());
	}				    
	//////////////////////////////////////// Unit Normal to the Plane
	WORLD Normal;
	if(m_SpnType == SPN_SYMM_N)
		GetUnitNormal_Symm_N(&Normal);
	else
	if(m_SpnType == SPN_SYMM_3)
		GetUnitNormal_Symm_3(&Normal);
	//////////////////////////////////////// p = rdotn
	double p = Math3D.Dot3DPts(&LocR,&Normal);
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	XForm.Reflect(pM,Normal,p);
	///////////////////////////////
	return;
}

void CNodCreOp::GetUnitNormal_Symm_N(pWORLD pNormal) 
{
/*
	/////////////////
	if(m_FromID == "")
   	{
   		AfxMessageBox("Please Select a Point(NodeID) to define the Normal");
 		GetDlgItem(IDC_CNODE_FROM)->SetFocus();
  		return;
   	}
	if(m_ToID == "")
   	{
   		AfxMessageBox("Please Select a Point(NodeID) to define the Normal");
 		GetDlgItem(IDC_CNODE_TO)->SetFocus();
  		return;
   	}
	if(m_FromID == m_ToID)
   	{
   		AfxMessageBox("Normal Undefined!\nSelect distinct Nodes");
		GetDlgItem(IDC_CNODE_FROM)->SetFocus();
		//////////////////
		UpdateData(FALSE);
		//////////////////
		return;
	}
*/
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////////////	
	double One80byPi = 180./acos(-1.0);
	///////////////////////////////////
	WORLD LocFrom,LocTo;
	int index;
	CString Nid;
	//////////////
	CDrNode* pNode;
	///////////////
	if((index= pObjectMgr->GetObjectIndexfromKey(NODE,m_SymmPtID[1],1)) >0)
	{
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocFrom 	= *(pNode->GetLocalPos());			    
		///////////////
	}
	else
		LocFrom = m_wSymm[1];
	/////////////////////////
	if((index= pObjectMgr->GetObjectIndexfromKey(NODE,m_SymmPtID[2],1)) >0)
	{
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocTo 	= *(pNode->GetLocalPos());			    
	}
	else
		LocTo = m_wSymm[2];
	////////////////////////////////////// Find Unit Axis
	Math3D.Sub3DPts(&LocTo, &LocFrom, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;	
}

void CNodCreOp::GetUnitNormal_Symm_3(pWORLD pNormal) 
{
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////////////	
	WORLD	Loc[3];
	WORLD	a;
	WORLD	b;
	int index;
	CString Nid;
	//////////////
	CDrNode* pNode;
	///////////////
	for(int i=0;i<3;i++)
	{
	    //////////
		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,m_SymmPtID[i],1)) <0)
			Loc[i] = m_wSymm[i];
		else
		{
			////////////	
			pNode = (CDrNode*)pDListMgr->GetObject(index);
			//////////////////////////////// scale etc
			Loc[i] 	= *(pNode->GetLocalPos());			    
			///////////////
		}
	}
	////////////////////////////////////// Find Unit Normal
	Math3D.Sub3DPts(&(Loc[1]), &(Loc[0]), &a);
	Math3D.Sub3DPts(&(Loc[2]), &(Loc[0]), &b);
	Math3D.Cross3DPts(&a,&b,pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;	
}

void CNodCreOp::SetUpLocalM_SHEAR()
{
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////CenterPt Coordinates
	WOPtoWOR(&m_wShearPt,&m_wShearPt);	// World
	WOPtoWOR(&m_wShear,&m_wShear);		// World
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM,M;			// to translate by CenterPT
	pMATRIX pTM = &TM;
	pMATRIX pM = &M;
	Math3D.GetIdentityMATRIX(pTM);
	Math3D.GetIdentityMATRIX(pM);
	///////////////////////////////////////////////////////// 
	XForm.Translate(pTM,-m_wShearPt.x,-m_wShearPt.y,-m_wShearPt.z,XF_REPLACE);
	XForm.Shear_X(pM,m_wShear.y,m_wShear.z, XF_REPLACE );
	XForm.Shear_Y(pM,m_wShear.x,m_wShear.z, XF_PREMULT );
	XForm.Shear_Z(pM,m_wShear.x,m_wShear.y, XF_PREMULT );
	////////////////////////////////////////////////////
	Math3D.F_MultMATRIX(pM,pTM,pM);
	//////////////////////////////////////////////////////////
	//					Fill Up Mat Matrix
	//////////////////////////////////////////////////////////
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_XFORMS);
	m_pMatObj->SetCreOp(COP_SHEAR);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	/////////////////////////////////// Grab Node
	m_pMatObj->SetRotPtID(m_ShearPtID);	
	m_pMatObj->SetRotPt(m_wShearPt);	
	///////////////////////////////////
	m_pMatObj->SetShear(m_wShear);
	////////////////////////////////
	m_pMatObj->SetNoRot(FALSE);
	m_pMatObj->SetNoTran(FALSE);
	m_pMatObj->SetNoScale(FALSE);
	m_pMatObj->SetNoShear(TRUE);
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
				case COP_ROTATE:
					///////////////////////////// String
					str = "ROTATE";
					pWnd->SetstrOperID(str);
					///////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case INODE:			str = "Input@NODE";		ID = OperID;
							strCur += "Click on an Input Node to Rotate";	break;
						case CNODE:			str = "Control@NODE";	ID = OperID;
							strCur += "Click on a Control Node to Rotate";	break;
					}			
					break;
				//////////////////////////////////////////// Create
				case COP_SCALE:
					///////////////////////////// String
					str = "SCALE";
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
				case COP_REFLECT:
					///////////////////////////// String
					str = "REFLECT";
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
				case COP_SHEAR:
					///////////////////////////// String
					str = "SHEAR";
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
				case COP_SPAWN:

					Init_NOD();	// No Modeless Dlg, so Init Here
					///////////////////////////// String
					str = "SPAWN";
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
		case COP_TRANSLATE:
			//////////////////////////////
			UpdateDlg_FALSE_XLATE();
			////
			break;
		case COP_ROTATE:
			//////////////////////////////
			UpdateDlg_FALSE_ROTATE();
			////
			break;
		case COP_SCALE:
			//////////////////////////////
			UpdateDlg_FALSE_SCALE();
			////
			break;
		case COP_REFLECT:
			//////////////////////////////
			UpdateDlg_FALSE_REFLECT();
			////
			break;
		case COP_SHEAR:
			//////////////////////////////
			UpdateDlg_FALSE_SHEAR();
			////
			break;
		case COP_SPAWN:
			//////////////////////////////
//			UpdateDlg_FALSE_SPAWN();
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
		case COP_TRANSLATE:

			UpdateDlg_TRUE_XLATE();
			////////////////////////////
			if(m_bDirect && m_bDominant)	// expecting Translation Value from DlgBox
			{
				if(m_bDlgExpect)
					m_nInfoDone++;
			}
			//////////////////////////////
			UpdateDlg_FALSE_XLATE();
			////
			break;
		case COP_ROTATE:

			UpdateDlg_TRUE_ROTATE();
			////////////////////////////
			if(m_nInfoDone == 1 && m_bOrigin)
			{
				m_nInfoDone++;
				//////////////////////////////
				UpdateDlg_FALSE_ROTATE();
				//
				break;
			}
			////////////////////////////// Stet Default: AngleIn
			if(m_nInfoDone >= 2)
			{
				//////////////////
				if(!m_bAngleIn)
				{
					if(m_bDirect && m_bDominant)	// expecting Rotation or DirCos Value from DlgBox
					{
						if(m_bDlgExpect)
							m_nInfoDone++;
					}
				}
				else
				if(m_bDlgExpect)
					m_nInfoDone++;
				
			}
			//////////////////////////////
			UpdateDlg_FALSE_ROTATE();
			////
			break;
		case COP_SCALE:

			UpdateDlg_TRUE_SCALE();
			////////////////////////////
			if(m_bDirect && m_bDominant)	// expecting Scale Value from DlgBox
			{
				if(m_bDlgExpect)
					m_nInfoDone++;
			}
			//////////////////////////////
			UpdateDlg_FALSE_SCALE();
			////
			break;
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
		case COP_SHEAR:

			UpdateDlg_TRUE_SHEAR();
			////////////////////////////
			if(m_bDirect && m_bDominant)	// expecting Shear Value from DlgBox
			{
				if(m_bDlgExpect)
					m_nInfoDone++;
			}
			//////////////////////////////
			UpdateDlg_FALSE_SHEAR();
			////
			break;
		case COP_SPAWN:
			//////////////////////////////
//			UpdateDlg_FALSE_SPAWN();
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

