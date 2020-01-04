// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include <time.h>
#include <stdlib.h>	// _itoa

#include "CalcTime.h"

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// Application dialogMgr
//#include "ADlgMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Elems
#include "Def_Elem.h"
#include "DrFE2D.h"
//////////////////////
#include "MI_GangN.h"	// for INODE and CNODE
#include "MI_GangC.h" 
#include "MI_GangP.h" 
#include "MI_Gang2.h"	// Root 
#include "MI_Qang2.h"	// for Quad Patch 
#include "MI_Tang2.h"	// for Tri	Patch 
//////////////////////
#include "PatPost.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_INODE		0	// 1 Object        
#define MAX_INFO_CNODE		0	// 1 Object        
#define MAX_INFO_CURVE		0	// 1 Object        
#define MAX_INFO_TRUSS		1	// 1 Object        
#define MAX_INFO_BEAM		1	// 1 Object        
#define MAX_INFO_PIPE		1	// 1 Object        
#define MAX_INFO_ELBOW		1	// 1 Object        
#define MAX_INFO_TR_XX		1	// 1 Object        
//#define MAX_INFO_TR_3		0	// 1 Object        
//#define MAX_INFO_TR_6		0	// 1 Object        
//#define MAX_INFO_TR_9		0	// 1 Object        
//#define MAX_INFO_TR_10	0	// 1 Object        
#define MAX_INFO_QU_XX		1	// 1 Object        
//#define MAX_INFO_QU_4		0	// 1 Object        
//#define MAX_INFO_QU_8		0	// 1 Object        
//#define MAX_INFO_QU_9		0	// 1 Object        
//#define MAX_INFO_QU_12	0	// 1 Object        
//#define MAX_INFO_QU_16	0	// 1 Object        
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CPatPost,CCurPost,1)
/////////////////////////////////////////////////////////////////////////////
CPatPost::CPatPost()
{
	m_Orient			= "ClockWise";		// for Now
	m_pPost2DDlg		= NULL;
	/////////////////////////////////////////// 
    m_pCurrentPatch		= NULL;
}

CPatPost::~CPatPost()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == EDIM_1)
	{
		/////////////////////////////////// Modeless Dialogs
		if(m_pPost1DDlg->m_hWnd)
			m_pPost1DDlg->DestroyWindow();
		///////////////////
		delete m_pPost1DDlg; 
		///////////////////
	}
	////////////////////////////
	if(CntlID == EDIM_2)
	{
		/////////////////////////////////// Modeless Dialogs
		if(m_pPost2DDlg->m_hWnd)
			m_pPost2DDlg->DestroyWindow();
		///////////////////
		delete m_pPost2DDlg; 
		///////////////////
	}
}

void CPatPost::InitDlgIn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
//	int CntlID	= pWnd->GetCurrentCntlID();
	///
//	if(CntlID == EDIM_1)
//		m_pPost1DDlg	= new CDlg_FE1I(pWnd);
	////////////////////////////
//	if(CntlID == EDIM_2)
		m_pPost2DDlg	= new CDlg_FE2I(pWnd);
}

void CPatPost::Init_PAT()
{
	Init_CUR();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	/////////////////////////////
	pMsObjMgr->SetElemInfoID(m_PostedID,MESH2D);
	/////////////////////////////////////////// Node
	m_pMesh2D			= NULL;
	m_ParentID			= "";
	m_pCurrentPatch		= NULL;
	/////////////////////////////////////////// Dlg_FE2I 
	m_rid_K				= "";
	m_rid_L				= "";
	m_RefRule			= "AUTO";
	m_Thick				= 1.0;
	/////////////////////////////////////////// 

}

void CPatPost::Terminate_PAT(BOOL bError)
{
//	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pMesh2D)
		{
			delete m_pMesh2D;
			m_pMesh2D = NULL;
		}
		///////////////////////////
	}
}

void CPatPost::ElementLeftDown_PAT()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
	switch(m_nActiveTool) 
	{
		
		//////////////////////////////////////// Elements:0D
		case INODE:				// 
			break;

		case CNODE:				// 
			break;

		//////////////////////////////////////// Elements:1D
		case TRUSS:				// 
			break;

		case BEAM:				// 
			break;

		case PIPE:				// 
			break;

		case ELBOW:				// 
			break;

		//////////////////////////////////////////////////
		default:
			break;
	}  

}

int CPatPost::ShowPatchToPost(CDrPatch* pDrPatch, BOOL bToBePosted)
{
	//  ISOPATVES todo
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
//	CDListMgr*	pObjList;
//	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);                   
	////////////////////////////////////////////////////////////////////// Show Patch to Post
	pDrPatch->SetToBePosted(bToBePosted);
	//////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrPatch,PATCH,TRUE);
//	pObjList = pObjectMgr->GetObjectList(PATCH);
//	nActiveIndex = pObjList->GetObjectIndex(PATCH,pDrPatch->GetObjectID());
//	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
//	pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
//	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
	///////////////////////////////
	return 0;
}	 

int CPatPost::MarkPatch_Post(CDrPatch* pDrPatch)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);                   
	////////////////////////////////////////////////////////////////////// Patch to Post
	pDrPatch->SetPosted(TRUE);
	///////////////////////////////
	return 0;
}	 
	
void CPatPost::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(pDListMgr->GetCount()<=0 )
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

void CPatPost::UpdateDlg_TRUE_PAT()
{
	static CString RQs[] 	= {	"AUTO","SHORT DIAG","INTERSECT DIAG","CENTROID",
								"MIDCEN SHORT"};
	static CString RTs[] 	= {	"AUTO","CENTROID","MIDCEN"};
	/////////////////////////////////////////////////////
	m_pPost2DDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_matID			= GetPost2DDlg()->m_matID;
	m_propID		= GetPost2DDlg()->m_propID;
	m_rid_I			= GetPost2DDlg()->m_rid_I;
	m_rid_J			= GetPost2DDlg()->m_rid_J;
	m_rid_K			= GetPost2DDlg()->m_rid_K;
	m_rid_L			= GetPost2DDlg()->m_rid_L;
	m_RefTemp		= GetPost2DDlg()->m_RefTemp;
	m_RefRule		= GetPost2DDlg()->m_RefRule;
	m_Thick			= GetPost2DDlg()->m_dThk;
	m_ObjType		= GetPost2DDlg()->m_ObjType;
	////////////////////////////////////////////
	if(m_pCurrentPatch)
	{
		if(m_pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
		{
			if(m_RefRule == "AUTO")
				m_Ref_Quad = RQ_AUTO;			// RQ_SHORTDIAG iff NonCoPlanar		1 Quad or 2 Tri
			else			
			if(m_RefRule == "Quadrilateral")
				m_Ref_Quad = RQ_NOREF;			// leave alone						1 Quad
			else			
			if(m_RefRule == "SHORT DIAG")
				m_Ref_Quad = RQ_SHORTDIAG;		// shorter Diag						2 Tri
			else			
			if(m_RefRule == "INTERSECT DIAG")
				m_Ref_Quad = RQ_INTERSECT;		// IntersectionDiag					4 Tri
			else			
			if(m_RefRule == "CENTROID")
				m_Ref_Quad = RQ_CENTROID;		// Centroid							4 Tri
			else			
			if(m_RefRule == "MIDCEN SHORT")
				m_Ref_Quad = RQ_MIDCENSHORT;	// MidPtCentroidShortDiag			8 Tri
			//////////////
		}
		else
		if(m_pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
		{
			if(m_RefRule == "AUTO")
				m_Ref_Tri = RT_AUTO;			//									1 Tri
			else			
			if(m_RefRule == "Triangle")
				m_Ref_Tri = RT_NOREF;			// leave alone						1 tri
			else			
			if(m_RefRule == "CENTROID")
				m_Ref_Tri = RT_CENTROID;		// Centroid							3 Tri
			else			
			if(m_RefRule == "MIDCEN")
				m_Ref_Tri = RT_MIDCEN;	// MidPtCentroid							4 Tri
			//////////////
		}
	}			
}

void CPatPost::UpdateDlg_FALSE_PAT()
{
	////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////////
	GetPost2DDlg()->m_matID			= m_matID;
	GetPost2DDlg()->m_propID		= m_propID;
	GetPost2DDlg()->m_rid_I			= m_rid_I;
	GetPost2DDlg()->m_rid_J			= m_rid_J;
	GetPost2DDlg()->m_rid_K			= m_rid_K;
	GetPost2DDlg()->m_rid_L			= m_rid_L;
	GetPost2DDlg()->m_RefRule		= m_RefRule;
	GetPost2DDlg()->m_RefTemp		= m_RefTemp;
	GetPost2DDlg()->m_dThk			= m_Thick;
	GetPost2DDlg()->m_ObjType		= m_ObjType;
	////////////////////////////////////////////////////////////
	GetPost2DDlg()->GetDlgItem(IDC_RELHEAD)->SetWindowText("");
	GetPost2DDlg()->GetDlgItem(IDC_RELHEAD2)->SetWindowText("");
	GetPost2DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDD_RID_K)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDD_RID_L)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDD_PID)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDD_MID)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDC_REFRULE)->EnableWindow(FALSE);
	GetPost2DDlg()->GetDlgItem(IDC_THKNESS)->EnableWindow(FALSE);
	//////////////////////////////////////
}

void CPatPost::UpdateDlg_FALSE_PAT_0()
{
	///////////////////
	UpdateDlg_FALSE_PAT();
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_ObjType)
	{
		case INODE:
			strCurr = "Generating INPUT NODEs@Click ON A " + m_strParentType;
			break;
		case CNODE:
			strCurr = "Generating CONTROL NODEs@Click ON A " + m_strParentType;
			break;
		case TRUSS:
			strCurr = "Generating TRUSS Elements@Click ON A " + m_strParentType;
			break;
		case BEAM:
			strCurr = "Generating BEAM Elements@Click ON A " + m_strParentType;
			break;
		case PIPE:
			strCurr = "Generating PIPE Elements@Click ON A " + m_strParentType;
			break;
		case ELBOW:
			strCurr = "Generating ELBOW Elements@Click ON A " + m_strParentType;
			break;
		////////////////////////////////////////////////////////////////////////// Quads
		case QU_4:
			strCurr = "Generating 4-Node Quads@Click ON A " + m_strParentType;
			break;
		case QU_8:
			strCurr = "Generating 8-Node Quads@Click ON A " + m_strParentType;
			break;
		case QU_9:
			strCurr = "Generating 9-Node Quads@Click ON A " + m_strParentType;
			break;
		case QU_12:
			strCurr = "Generating 12-Node Quads@Click ON A " + m_strParentType;
			break;
		case QU_16:
			strCurr = "Generating 16-Node Quads@Click ON A " + m_strParentType;
			break;
		////////////////////////////////////////////////////////////////////////// Tris
		case TR_3:
			strCurr = "Generating 3-Node Triangles@Click ON A " + m_strParentType;
			break;
		case TR_6:
			strCurr = "Generating 6-Node Triangles@Click ON A " + m_strParentType;
			break;
		case TR_9:
			strCurr = "Generating 9-Node Triangles@Click ON A " + m_strParentType;
			break;
		case TR_10:
			strCurr = "Generating 10-Node Triangles@Click ON A " + m_strParentType;
			break;
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	m_pPost2DDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CPatPost::UpdateDlg_FALSE_TRI()
{
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			///////////////////
			UpdateDlg_FALSE_PAT();
			UpdateDlg_FALSE_PAT_0();
			///////////////////
			GetPost2DDlg()->SetWindowText("Triangle Posting Info");
			///
			GetPost2DDlg()->GetDlgItem(IDC_RELHEAD)->SetWindowText("Release");
			GetPost2DDlg()->GetDlgItem(IDC_RELHEAD2)->SetWindowText("Release");
			GetPost2DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_RID_K)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDC_THKNESS)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost2DDlg->UpdateData(FALSE); // To screen
			////////////////////////////////////////////////
			return;
		case 1:
			///////////////////
			strCurr = "If Ready with Other Info.,@Click Right Mouse Button";
			/////////////////////////////////////////////// CurrStat: Show
			pWnd->GetCurrStat()->SetText(strCurr);
			pWnd->GetCurrStat()->Invalidate();
			pWnd->GetCurrStat()->UpdateWindow();
			///////
			return;
		default:
			break;
	}
	////////
	return;
}

void CPatPost::UpdateDlg_FALSE_QUAD()
{
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			///////////////////
			UpdateDlg_FALSE_PAT();
			UpdateDlg_FALSE_PAT_0();
			///////////////////
			GetPost2DDlg()->SetWindowText("Quadrilateral Posting Info");
			///
			GetPost2DDlg()->GetDlgItem(IDC_RELHEAD)->SetWindowText("Release");
			GetPost2DDlg()->GetDlgItem(IDC_RELHEAD2)->SetWindowText("Release");
			GetPost2DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_RID_K)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_RID_L)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			GetPost2DDlg()->GetDlgItem(IDC_THKNESS)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost2DDlg->UpdateData(FALSE); // To screen
			////////////////////////////////////////////////
			return;
		case 1:
			GetPost2DDlg()->GetDlgItem(IDC_REFRULE)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost2DDlg->UpdateData(FALSE); // To screen
			////////////////////////////////////////////////
			strCurr = "If Ready with Other Info.,@Click Right Mouse Button";
			/////////////////////////////////////////////// CurrStat: Show
			pWnd->GetCurrStat()->SetText(strCurr);
			pWnd->GetCurrStat()->Invalidate();
			pWnd->GetCurrStat()->UpdateWindow();
			///////
			return;

		default:
			break;
	}
	////////
	return;
}

int CPatPost::LeftUp_PATCH(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
//	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrPatch*	pDrPatch;
//	int			nActiveIndex,index;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Patch Hit
	index = IsObjectHit(PATCH,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Patch Hit
	////////////////////////////////////////////////////
	pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
	ID			= pDrPatch->GetObjectID();
	//////////////////////////////////////////////////// Check for RightType
	if(m_bQuadSelect)
	{
		if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
			return -1;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrPatch,PATCH,TRUE);
//	pList = pObjectMgr->GetObjectList(PATCH);
//	nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
//	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
//	pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Type									
//	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
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
			CMI_Tang2 Gang2;
			nResult = Gang2.ShowPatchInfo(pDrPatch);
			/////////////
			if(nResult == IDYES)
			{
				//////////////////////////////////////////////////////// Accept Old
				break;
			}
			else
			if(nResult == IDNO)
			{
				//////////////////////////////////////////////////////// Retry
				index = IsObjectHit(PATCH,point,startIndex);
				if(index>=0)
				{
					pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
					ID			= pDrPatch->GetObjectID();
					///////////////////////////////////////// 
					pObjectMgr->ShowObject_On_Off(pDrPatch,PATCH,TRUE);
//					pList = pObjectMgr->GetObjectList(PATCH);
//					nActiveIndex = pList->GetObjectIndex(PATCH, ID);;
//					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
//					pObjectMgr->SetActiveObjectType(PATCH);		    // set Active Index									
//					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PATCH);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
				{
					////////////////
					return -2;
				}
				/////////
			}
			else				// Cancel
			{
				//////////////////////////////////////////////////////// Do Nothing
				return -2;
			}
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, show Properties
	m_pCurrentPatch = pDrPatch;
	///////////////////////////
	if(ShowPatchToPost(pDrPatch,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCPatPost::LeftUp_Patch\nShowPatchToPost Problem");
		return -1;
	}
	//////////
	return 0;
}

void CPatPost::ElementLeftUp_PAT(CPoint point)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	//////////////////////////////////////////////////////////////////
//	char buf[20];
	CString Nid;
	BOOL bRightOn = FALSE;
	////////////////////////////////// IGenID
	UINT IGenID = pWnd->GetCurrentIGenID();
	/////////////////////
	m_bQuadSelect = FALSE;						// Select Any Type Patch
	/////////////////////
	switch(m_nActiveTool) 
	{
		///////////////////////////////////////////////////////////////////////////// 0D
		case INODE:				//
			
			if(m_nInfoDone > MAX_INFO_INODE)
				return;
			////////////////
//			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
//			m_nInfoDone++;
//			UpdateDlg_FALSE_CUR();
			///////
			//////////////////
			if(Post_IorCNODE(m_pCurrentPatch,FALSE)<0)// FALSE = NOT CNode
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
//				UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			return;

		case CNODE:				//
			
			if(m_nInfoDone > MAX_INFO_CNODE)
				return;
			////////////////
//			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
//			m_nInfoDone++;
//			UpdateDlg_FALSE_CUR();
			///////
			//////////////////
			if(Post_IorCNODE(m_pCurrentPatch,TRUE)<0)// TRUE = YES CNode
			////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			else
			{
				Terminate_PAT(FALSE);
				Init_PAT();
				/////////////////////////
//				UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			return;

		///////////////////////////////////////////////////////////////////////////// 1D
		case CURVE:	
			
				return;		// todo
		///////////////
		case TRUSS:				
			
			if(m_nInfoDone >= MAX_INFO_TRUSS)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_TRUSS();
			///////
			return;

		case BEAM:				// 
			
			if(m_nInfoDone >= MAX_INFO_BEAM)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_BEAM();
			///////
			return;

		case PIPE:				//
			
			if(m_nInfoDone >= MAX_INFO_PIPE)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_PIPE();
			///////
			return;

		case ELBOW:				// 
			
			if(m_nInfoDone >= MAX_INFO_ELBOW)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_ELBOW();
			///////
			return;
		///////////////////////////////////////////////////////////////////////////// TRI
		case TR_3:	
		case TR_6:	
		case TR_9:	
		case TR_10:	if(m_nInfoDone >= MAX_INFO_TR_XX)	return;

			////////////////
			UpdateDlg_TRUE_PAT();
			//////////////////
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			////////////////////////////////////////// Fill Up Refinement Rule in Dlg
			FillDlgRefinementRules();
			///////////////////////////
			UpdateDlg_FALSE_TRI();
			///////
			return;

		///////////////////////////////////////////////////////////////////////////// QUAD
		case QU_4:	
		case QU_8:	
		case QU_9:	
		case QU_12:	
		case QU_16:	if(m_nInfoDone >= MAX_INFO_QU_XX)	return;

			////////////////
			UpdateDlg_TRUE_PAT();
			//////////////////
			m_bQuadSelect = TRUE;		// Accept Only Quad-Patches
			///
			if(LeftUp_PATCH(point)<0)	
			////////////////////
			{
				Terminate_PAT(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			////////////////////////////////////////// Fill Up Refinement Rule in Dlg
			FillDlgRefinementRules();
			//////////////////////////////////////////////////
			UpdateDlg_FALSE_QUAD();
			///////
			return;

		default:  
			return;
	} 
}	

void CPatPost::FillDlgRefinementRules()
{
	if(m_pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
	{
		////////////////////////////////////////// Fill Up Refinement Rule
		GetPost2DDlg()->m_bQuad = FALSE;	
		GetPost2DDlg()->FillRefRule();
		///
	}
	else
	if(m_pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
	{
		////////////////////////////////////////// Fill Up Refinement Rule
		GetPost2DDlg()->m_bQuad = TRUE;	
		GetPost2DDlg()->FillRefRule();
		///
	}
	///////
	return;
}

void CPatPost::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
	/////////////////////////
	
}

int CPatPost::Post_IorCNODE(CDrPatch* pPatch, BOOL bCNode)		
{
	int nResult;		
	//////////////////////////////////////////// Output memory
	int nOut		= (int)pPatch->GetLongOutPts();
	/////////////////////////////////////////////////////////
	CMI_GangP GangP;
	////////////////////////////////
	pWORLD	pOut	= GangP.FixMem(nOut);
	pDOUBLE pOutWts = GangP.FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	GangP.SetbBack(FALSE);
	GangP.FillMeshNodesPatch(pPatch,pOut,pOutWts);
	///////////////////////////////////////////////////////// Post IorCNodes / NO Reciprocation
	CMI_Qang2 Qang2;
	CMI_Tang2 Tang2;
	///
	if(pPatch->GetPatSubType() == PS_QUADRILAT)
		nResult = Qang2.Post_PatchNodes_IorC_4(pPatch, pOut,nOut,bCNode);
	else
	if(pPatch->GetPatSubType() == PS_TRIANGLE)
		nResult = Tang2.Post_PatchNodes_IorC_3(pPatch, pOut,nOut,bCNode);
	////////////////////////
	GangP.FreeMem(pOut);
	GangP.FreeMemD(pOutWts);
	////////////////////////
	if(nResult<0)
		return nResult;
	/////////
	return 0;
}

int CPatPost::Post_CURVE(CDrPatch* pDrPatch)		
{
	return -1;	//todo
	///////////////////////////////////////////////////////////
	int nResult;		
	//////////////////////////////////////////// Output memory
	int nOut		= (int)pDrPatch->GetLongOutPts();
	/////////////////////////////////////////////////////////
	CMI_GangP GangP;
	////////////////////////////////
	pWORLD	pOut	= GangP.FixMem(nOut);
	pDOUBLE pOutWts = GangP.FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	GangP.SetbBack(FALSE);
	GangP.FillMeshNodesPatch(pDrPatch,pOut,pOutWts);
	///////////////////////////////////////////////////////// Post IorCNodes / NO Reciprocation
	CMI_Qang2 Qang2;
	CMI_Tang2 Tang2;
	///
	if(pDrPatch->GetPatSubType() == PS_QUADRILAT)
		nResult = Qang2.Post_PatchCurves_4(pDrPatch,pOut,pOutWts,nOut);
	else
	if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
		nResult = Tang2.Post_PatchCurves_3(pDrPatch,pOut,pOutWts,nOut);
	////////////////////////
	GangP.FreeMem(pOut);
	GangP.FreeMemD(pOutWts);
	////////////////////////
	if(nResult<0)
		return nResult;
	/////////
	return 0;
}

int CPatPost::GenPost_PatchEdges()		
{
	//		THIS ROUTINE IS NOT NECESSARY : 10/04/97
	/////////////////////////////////////////////////////
	//			FILLING EDGELIST IN MESH 
	//		DEFINING POSITIVE EDGE DEFINITION
	////////////////////////////////////////////
	int nResult;		
	//////////////////////////
	CMI_Qang2 Qang2;
	CMI_Tang2 Tang2;
	////////////////
	CDrPatch* pDrPatch = m_pMesh2D->GetGenObj();
	/////////////////////////////////////////////
	if(pDrPatch->GetPatSubType() == PS_QUADRILAT)
		nResult = Qang2.Post_PatchEdges_FE1D_4(m_pMesh2D);
	else
	if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
		nResult = Tang2.Post_PatchEdges_FE1D_3(m_pMesh2D);
	///////
	if(nResult<0)
		return nResult;
	///////
	return 0;
}

int CPatPost::GenPost_PatchNodes(CDrPatch* pDrPatch,BOOL bMNode,BOOL bAnyWay)		
{
	int nResult;		
	//////////////////////////////////////////// Output memory
	int nOut = (int)pDrPatch->GetLongOutPts();
	////////////////
	CMI_GangP GangP;
	////////////////////////////////
	pWORLD	pOut	= GangP.FixMem(nOut);
	pDOUBLE pOutWts = GangP.FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	GangP.SetbBack(FALSE);
	GangP.FillMeshNodesPatch(pDrPatch,pOut,pOutWts);
	///////////////////////////////////////////////////////// Post MNodes 
//	CString LineID = pDrPatch->GetObjectID();
//	m_pMesh2D->SetObjectID(LineID);
	//////////////////////////
	BOOL bCNode = FALSE;		
	CMI_Qang2 Qang2;
	CMI_Tang2 Tang2;
	////////////////////////
	BOOL bReverseST = FALSE;
	///
	if(pDrPatch->GetPatSubType() == PS_QUADRILAT)
	{
		int nOut_S		= (int)pDrPatch->GetOut_S();
		int nOut_T		= (int)pDrPatch->GetOut_T();
		//////////////////////////////////////////// BandMinimized Numbering
		if(nOut_T < nOut_S)
			bReverseST = TRUE;
		///////
		nResult = Qang2.Post_PatchNodes_FE0D_4(m_pMesh2D,MESH2D,pOut,nOut_S,nOut_T,bCNode,
								bMNode,bAnyWay,bReverseST);	//TRUE=MNode/FALSE=VERTEX
	}
	else
	if(pDrPatch->GetPatSubType() == PS_TRIANGLE)
		nResult = Tang2.Post_PatchNodes_FE0D_3(m_pMesh2D,MESH2D,pDrPatch,pOut,bCNode,
								bMNode,bAnyWay);	//TRUE=MNode/FALSE=VERTEX
	////////////////////////
	GangP.FreeMem(pOut);
	GangP.FreeMemD(pOutWts);
	///////
	if(nResult<0)
		return nResult;
	////////////////////////////////////// Save Mesh Info
	m_pMesh2D->SetReversed_ST(bReverseST);
	///////
	return 0;
}

int CPatPost::Pre_Common_2D(CDrPatch* pDrPatch,int& nActiveIndex)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	///
	int nResult;		
	///////////////////////////////////////////////////////// Create Mesh
	m_pMesh2D	= (CDrMesh2D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH2D));
	if(!m_pMesh2D)
	{
		AfxMessageBox("Internal ERROR:\nCPatPost::Pre_Common_2D\nm_pMesh2D == NULL");
		return -1;
	}
	//////////////////////////////////////////////
	m_pMesh2D->SetDirty(FALSE);	// Posted Type
	m_pMesh2D->SetShow(FALSE);	// not quite ready
	m_pMesh2D->SetGenObj(pDrPatch);
	m_pMesh2D->SetRefQuad(m_Ref_Quad);
	m_pMesh2D->SetRefTri(m_Ref_Tri);
	m_pMesh2D->SetObjectID(m_PostedID);
	///
	if(m_Orient == "ClockWise")
		m_pMesh2D->SetOrient(OT_CLOCKWISE);
	else
		m_pMesh2D->SetOrient(OT_ANTICLOCK);
	//////////////////////////////////////////////
	m_line_id	= m_pMesh2D->GetObjectID();
	/////////////////////////////////////// Genetics
	m_GenObjType	= MESH2D;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
	m_pGenObj		= m_pMesh2D;
	/////////////////////////////////////// 
	return nResult;
}

int CPatPost::Post_Common_2D(CDrPatch* pDrPatch,int nActiveIndex, int nResult)
{		
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///
	if(nResult<0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex,MESH2D);
		return nResult;
	}
	else
	{
		////////////////////////////////////////////////// History & Reciprocate
		//	(Need Later for Support & Load Post)
		//  For Each Node: New SupportID & LoadID
		//	will be generated based on whether
		//	 the Support is Skewed, tangent etc
		//////////////////////////////////////////////////
		m_pMesh2D->GetPatchList()->InsertObject(pDrPatch);
		pDrPatch->GetElemList()->InsertObject(m_pMesh2D);
		m_pMesh2D->SetShow(TRUE);	// Now Ready
		m_pMesh2D->SetPosted(TRUE);	// Posted Patch
		///
		CString MeshID = m_pMesh2D->GetObjectID(); 
		UpdateSceneView(MeshID,MESH2D);
		///
	}
	/////////
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
int CPatPost::PrePost_Patch(CDrPatch* pDrPatch,CObject* pGang2,BOOL b1D)		
{
	//		2D ELEMENT POSTING
	///////////////////////////////
	int nResult;
	////////////////////////////////////////////////// Post Mesh & Vertices
	nResult = GenPost_Mesh_Vertices(pDrPatch,TRUE,TRUE);
	//////////////
	if(nResult<0)
		return -1;
/****************************************************************************
	////////////////////////////////////////////////// Post Edges
	nResult = GenPost_PatchEdges();
	//////////////
	if(nResult<0)
		return -1;
*/
	////////////////////////////////////////////////// Transfer Data
	if(b1D)
		nResult = FillData_Patch_1D(pGang2);	// for 1D Elements:Truss etc
	else
		nResult = FillData_Patch_2D(pGang2);	// for 2D Elements:Qu_4 etc
	//////////////
	if(nResult<0)
		return -1;
	/////////
	return 0;
}

int CPatPost::GenPost_Mesh_Vertices(CDrPatch* pDrPatch,BOOL bMNode,BOOL bAnyWay)		
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	//	bMNode	= FALSE -> just FE0D( i.e. Vertices)
	//	bAnyWay = TRUE  -> create Nodes Anyway, e.g. crack modeling
	///////////////////////////////////////////////////////////////
	int nResult,nActiveIndex;
	//////////////		
#ifdef _DEBUG
	CCalcTime	CalcTime;
	CalcTime.StartClock();
#endif
	////////////////////////////////////////////////// Post Mesh
	nResult = Pre_Common_2D(pDrPatch,nActiveIndex);
	//////////////
	if(nResult<0)
		return -1;
	//////////////
#ifdef _DEBUG
	/////////////////////
	CalcTime.StopClock();
	CString strCalc;
	sprintf(strCalc.GetBuffer(150),"CPatPost::GenPost_Mesh_Vertices\n");
	CalcTime.OutComment(strCalc);
	strCalc.ReleaseBuffer();
	sprintf(strCalc.GetBuffer(150),"Pre_Common_2D:PostMesh");
	CalcTime.OutDuration(strCalc);
	//////////////		
	CalcTime.StartClock();
#endif
	////////////////////////////////////////////////// Post Vertices
	nResult = GenPost_PatchNodes(pDrPatch,bMNode,bAnyWay); 		
	//////////////
	if(nResult<0)
		return -1;
	//////////////
#ifdef _DEBUG
	CalcTime.StopClock();
	sprintf(strCalc.GetBuffer(150),"GenPost_PatchNodes:PostNodes");
	CalcTime.OutDuration(strCalc);
#endif
	/////////
	return 0;
}

int CPatPost::FillData_Patch_1D(CObject* pGang2)		
{
	CMI_Gang2* pGang = (CMI_Gang2*)pGang2;
	////////////////////////////////////////////////////////////////////// Members
 	pGang->SetElNumID(m_ElNumID);			
 	pGang->SetElTypeID(m_ElTypeID);	
	pGang->Setline_id(m_line_id);
 	pGang->Setrid(m_rid_I,0);
 	pGang->Setrid(m_rid_J,1);
 	pGang->Setpid(m_propID);
 	pGang->Setmid(m_matID);
	//////////////////////////////////
	pGang->SetElNum(m_ElNum);			
	pGang->SetElTypeNum(m_ElTypeNum);	
	pGang->Setline_no(m_line_no);		
	pGang->Setrel(m_rel_I,0);			
	pGang->Setrel(m_rel_J,1);			
	pGang->Setprop(m_prop);		
	pGang->Setmat(m_mat);
	//////////////////////////////////
	pGang->Setnumseg(m_numseg);		
	pGang->SetRefTemp(m_RefTemp);
	pGang->SetOnBndry(TRUE);
	//////////////////////////////////
//	pGang->SetElDegree(m_ElDegree);		// will be done in Gang2
	////////////////////////////////////////////////////////////////////// helper
//	pNewObj->SetCenter(POINT ptCenter);
	/////////
	return 0;
}

int CPatPost::FillData_Patch_2D(CObject* pGang2)		
{
	CMI_Gang2* pGang = (CMI_Gang2*)pGang2;
	////////////////////////////////////////////////////////////////////// Members
 	pGang->SetElNumID(m_ElNumID);			
 	pGang->SetElTypeID(m_ElTypeID);	
	pGang->Setline_id(m_line_id);
 	pGang->Setrid(m_rid_I,0);
 	pGang->Setrid(m_rid_J,1);
 	pGang->Setrid(m_rid_K,2);
 	pGang->Setrid(m_rid_L,3);
 	pGang->Setpid(m_propID);
 	pGang->Setmid(m_matID);
	//////////////////////////////////
	pGang->SetElNum(m_ElNum);			
	pGang->SetElTypeNum(m_ElTypeNum);	
	pGang->Setline_no(m_line_no);		
	pGang->Setrel(m_rel_I,0);			
	pGang->Setrel(m_rel_J,1);			
	pGang->Setrel(m_rel_K,2);			
	pGang->Setrel(m_rel_L,3);			
	pGang->Setprop(m_prop);		
	pGang->Setmat(m_mat);
	//////////////////////////////////
	pGang->Setnumseg(m_numseg);		
	pGang->SetRefTemp(m_RefTemp);
	pGang->SetThick(m_Thick);
	pGang->SetOnBndry(TRUE);
	//////////////////////////////////
//	pGang->SetElDegree(m_ElDegree);		// will be done in Gang2
	////////////////////////////////////////////////////////////////////// helper
//	pNewObj->SetCenter(POINT ptCenter);
	/////////
	return 0;
}
////////////////////////////////////////////////////////////////////////
void CPatPost::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatPost::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case PATCH:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CPatPost::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
#ifdef _DEBUG
	CCalcTime	CalcTime;
	CString		strCalc;
#endif

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
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature_PAT()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	////////////////////////////////////////////////// Update Info
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == EDIM_1 && m_nActiveTool != CURVE)
		UpdateDlg_TRUE_CUR();
	////////////////////////////
	if(CntlID == EDIM_2)
		UpdateDlg_TRUE_PAT();
	/////////////////
	if(RightUp_NotAutoAccept_PAT()<0)
	{
		Terminate_PAT(TRUE);
		return;
	}
	///////////////////////////////////////////////////// Do it
	CMI_Qang2	Qang2;
	CMI_Tang2	Tang2;
	int			nResult,nActiveIndex;
	BOOL		b1D = FALSE;
	//////////////////
	switch(m_nActiveTool) 
	{
	
		/////////////////////////////////// 0D
		case INODE:				//
			
			return;			// IGNORE Everything Below
			//////////////////
			if(Post_IorCNODE(m_pCurrentPatch,FALSE)<0)// FALSE = NOT CNode
			////////////////
			{	Terminate_PAT(TRUE);	return;	}
			else
			{	Terminate_PAT(FALSE);	Init_PAT();	// UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			break;

		case CNODE:				//
			
			return;			// IGNORE Everything Below
			//////////////////
			if(Post_IorCNODE(m_pCurrentPatch,TRUE)<0)// TRUE = CNode
			////////////////
			{	Terminate_PAT(TRUE);	return;	}
			else
			{	Terminate_PAT(FALSE);	Init_PAT();	// UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			break;
			
		/////////////////////////////////// 1D
		case CURVE:				// 
			
			//////////////////
			if(Post_CURVE(m_pCurrentPatch)<0)
			////////////////
			{	Terminate_PAT(TRUE);	return;	}
			else
			{	Terminate_PAT(FALSE);	Init_PAT();	// UpdateDlg_FALSE_CURVE();	
				break;
			}
			///////////////////	
			break;
			
		////////////////////////////////////////////////////////////// 1D
		case TRUSS:				// 
		case BEAM:				// 
		case PIPE:				//
		case ELBOW:				// 
			b1D = TRUE;			// fall thro'
		////////////////////////////////////////////////////////////// 2D
		case TR_3:
		case TR_6:
		case TR_9:
		case TR_10:	
		
			/////////////////////////////////////////////////// Triangular Patch
			if(m_pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
			{
				if(PrePost_Patch(m_pCurrentPatch,(CObject*)&Tang2,b1D)<0)
				{	Terminate_PAT(TRUE);	return;	}
#ifdef _DEBUG
	CalcTime.StartClock();
#endif
				//////////////////
				if(Tang2.Post_Patch_TRIANGLES(m_pMesh2D,m_pCurrentPatch,
													MESH2D,m_nActiveTool)<0)
				////////////////
				{Terminate_PAT(TRUE);	return;	}
				else
				{
	//////////////
#ifdef _DEBUG
	CalcTime.StopClock();
	sprintf(strCalc.GetBuffer(150),"CPatPost::OnEBoxRButtonUp_PAT");
	CalcTime.OutComment(strCalc);
	strCalc.ReleaseBuffer();
	sprintf(strCalc.GetBuffer(150),"Post_Patch_TRIANGLES\nTakes %8.4f seconds.");
	CalcTime.OutDuration(strCalc);
#endif
	//////////////		
					////////////////////////
					nResult = 0;	// nActiveIndex not needed below
					nResult = Post_Common_2D(m_pCurrentPatch,nActiveIndex,nResult);
					//////////////
					if(nResult<0)
						{Terminate_PAT(TRUE);	return;	}
					/////////
					Terminate_PAT(FALSE);	Init_PAT();	UpdateDlg_FALSE_TRI();
					break;
				}
				///////////////////	
				break;
				///
			}
			/////////////////////////////////////////////////// Quadrilateral Patch
			else
			if(m_pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
			{
				if(PrePost_Patch(m_pCurrentPatch,(CObject*)&Qang2,b1D)<0)
				{	Terminate_PAT(TRUE);	return;	}
#ifdef _DEBUG
	CalcTime.StartClock();
#endif
				//////////////////
				if(Qang2.Post_Patch_QUADRILATS(m_pMesh2D,m_pCurrentPatch,
													MESH2D,m_nActiveTool)<0)
				////////////////
				{Terminate_PAT(TRUE);	return;	}
				else
				{
	//////////////
#ifdef _DEBUG
	CalcTime.StopClock();
	sprintf(strCalc.GetBuffer(150),"CPatPost::OnEBoxRButtonUp_PAT");
	CalcTime.OutComment(strCalc);
	strCalc.ReleaseBuffer();
	sprintf(strCalc.GetBuffer(150),"Post_Patch_QUADRILATS");
	CalcTime.OutDuration(strCalc);
#endif
	//////////////		
					////////////////////////
					nResult = 0;	// nActiveIndex not needed below
					nResult = Post_Common_2D(m_pCurrentPatch,nActiveIndex,nResult);
					//////////////
					if(nResult<0)
						{Terminate_PAT(TRUE);	return;	}
					/////////
					Terminate_PAT(FALSE);	Init_PAT();	UpdateDlg_FALSE_QUAD();
					break;
				}
				///////////////////	
				break;
				///
			}
			//////////
			break;
		////
		case QU_4:	
		case QU_8:
		case QU_9:
		case QU_12:
		case QU_16:
		
			if(PrePost_Patch(m_pCurrentPatch,(CObject*)&Qang2,b1D)<0)
			{	Terminate_PAT(TRUE);	return;	}
#ifdef _DEBUG
	CalcTime.StartClock();
#endif
			//////////////////
			if(Qang2.Post_Patch_QUADRILATS(m_pMesh2D,m_pCurrentPatch,MESH2D,m_nActiveTool)<0)
			////////////////
			{	Terminate_PAT(TRUE);	return;	}
			else
			{
	//////////////
#ifdef _DEBUG
	CalcTime.StopClock();
	sprintf(strCalc.GetBuffer(150),"CPatPost::OnEBoxRButtonUp_PAT");
	CalcTime.OutComment(strCalc);
	strCalc.ReleaseBuffer();
	sprintf(strCalc.GetBuffer(150),"Post_Patch_QUADRILATS");
	CalcTime.OutDuration(strCalc);
#endif
	//////////////		
				////////////////////////
				nResult = 0;	// nActiveIndex not needed below
				nResult = Post_Common_2D(m_pCurrentPatch,nActiveIndex,nResult);
				//////////////
				if(nResult<0)
					{Terminate_PAT(TRUE);	return;	}
				/////////
				Terminate_PAT(FALSE);	Init_PAT();	UpdateDlg_FALSE_QUAD();
				break;
			}
			///////////////////	
			break;
		////////////////////////////////////////////////////////////// 
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	pMsObjMgr->SetElemInfoID(m_PostedID,MESH2D);
	////////////////////////////////////////////////////////////////////////
}

int CPatPost::RightUp_Premature_PAT()
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
	switch(m_ObjType)
	{
		////////////////////////////////////////////////////////////////////// 0D
		case INODE:	if(m_nInfoDone<MAX_INFO_INODE)	bPreMature = TRUE;	break;
		case CNODE: if(m_nInfoDone<MAX_INFO_CNODE)	bPreMature = TRUE;	break;
		////////////////////////////////////////////////////////////////////// 1D
		case CURVE:	if(m_nInfoDone<MAX_INFO_CURVE)	bPreMature = TRUE;	break;
		///
		case TRUSS:	if(m_nInfoDone<MAX_INFO_TRUSS)	bPreMature = TRUE;	break;
		case BEAM:	if(m_nInfoDone<MAX_INFO_BEAM)	bPreMature = TRUE;	break;
		case PIPE:	if(m_nInfoDone<MAX_INFO_PIPE)	bPreMature = TRUE;	break;
		case ELBOW:	if(m_nInfoDone<MAX_INFO_ELBOW)	bPreMature = TRUE;	break;
		////////////////////////////////////////////////////////////////////// 2D
/*
		case TR_3:	if(m_nInfoDone<MAX_INFO_TR_3)	bPreMature = TRUE;	break;
		case TR_6:	if(m_nInfoDone<MAX_INFO_TR_6)	bPreMature = TRUE;	break;
		case TR_9:	if(m_nInfoDone<MAX_INFO_TR_9)	bPreMature = TRUE;	break;
		case TR_10:	if(m_nInfoDone<MAX_INFO_TR_10)	bPreMature = TRUE;	break;
*/
		case TR_3:	
		case TR_6:	
		case TR_9:	
		case TR_10:	if(m_nInfoDone<MAX_INFO_TR_XX)	bPreMature = TRUE;	break;
		////
/*
		case QU_4:	if(m_nInfoDone<MAX_INFO_QU_4)	bPreMature = TRUE;	break;
		case QU_8:	if(m_nInfoDone<MAX_INFO_QU_8)	bPreMature = TRUE;	break;
		case QU_9:	if(m_nInfoDone<MAX_INFO_QU_9)	bPreMature = TRUE;	break;
		case QU_12:	if(m_nInfoDone<MAX_INFO_QU_12)	bPreMature = TRUE;	break;
		case QU_16:	if(m_nInfoDone<MAX_INFO_QU_16)	bPreMature = TRUE;	break;
*/
		case QU_4:	
		case QU_8:	
		case QU_9:	
		case QU_12:	
		case QU_16:	if(m_nInfoDone<MAX_INFO_QU_XX)	bPreMature = TRUE;	break;
		////////////////////////////////////////////////////////////////////// 
		default:
			break;
	}
	//////////////// PreMature
	if(bPreMature)
		return -1;
	////////
	return 0;
}	

int CPatPost::RightUp_NotAutoAccept_PAT()
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
			////////////////////////////////////////////////////////////// 0D
			case INODE:	// nAnswer = ShowInputInfo_INODE();			break;
			case CNODE:	// nAnswer = ShowInputInfo_CNODE();
				break;
			////////////////////////////////////////////////////////////// 1D
			case CURVE:	// nAnswer = ShowInputInfo_CURVE();
				break;
			///
			case TRUSS:	nAnswer = ShowInputInfo_TRUSS();			break;
			case BEAM:	nAnswer = ShowInputInfo_BEAM();				break;
			case PIPE:	nAnswer = ShowInputInfo_PIPE();				break;
			case ELBOW:	nAnswer = ShowInputInfo_ELBOW();			break;
			////////////////////////////////////////////////////////////// 2D
			case TR_3:	// fall thro'
			case TR_6:
			case TR_9:
			case TR_10:	nAnswer = ShowInputInfo_QUADorTRI(FALSE);	break;
			////
			case QU_4:	// fall thro'
			case QU_8:
			case QU_9:
			case QU_12:
			case QU_16:	nAnswer = ShowInputInfo_QUADorTRI(TRUE);	break;
			////////////////////////////////////////////////////////////// 
			default:
				break;
		}
		/////////////////////////
		if(nAnswer<0)
			return -1;
		//////////////
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

int CPatPost::ShowInputInfo_QUADorTRI(BOOL bQuad)
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** Element Info ******\n\n");
	///
	j += sprintf( buf + j, "Element Type = \t%s\n\n",m_ElTypeID); // 
	j += sprintf( buf + j, "Orientation = \t%s\n",m_Orient); // 
	j += sprintf( buf + j, "Property ID = \t%s\n",m_propID); // 
	j += sprintf( buf + j, "Material ID = \t%s\n",m_matID); // 
	j += sprintf( buf + j, "Release ID_I = \t%s\n",m_rid_I); // 
	j += sprintf( buf + j, "Release ID_J = \t%s\n",m_rid_J); // 
	j += sprintf( buf + j, "Release ID_K = \t%s\n",m_rid_K); // 
	if(bQuad)
		j += sprintf( buf + j, "Release ID_L = \t%s\n",m_rid_L); // 
	//
	j += sprintf( buf + j, "Ambient Temp. = \t%f\n",m_RefTemp); // 
	j += sprintf( buf + j, "Thickness = \t%f\n",m_Thick); // 
	j += sprintf( buf + j, "Refinement Rule = \t%s\n",m_RefRule); // 
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
void CPatPost::ModeLessOff_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == EDIM_0)
		return;
	///
	if(CntlID == EDIM_1)
	{
		if(m_ObjType == CURVE)
			return;
		//////////////////////////
		if(GetPost1DDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_FE1IN,IDOK);
	}
	///
	if(CntlID == EDIM_2)
	{
		if(GetPost2DDlg()->m_hWnd)
			pWnd->SendMessage(ID_GOODBYE_FE2IN,IDOK);
	}
}

void CPatPost::ModeLessOn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	int CntlID	= pWnd->GetCurrentCntlID();
	/////////////////////////////////////////////////////////////////////////
	m_ObjType = aTool;
	////////////////////////////
		pWnd->SendMessage(ID_ACTIVE_FE2IN);	// pWnd will dispatch to right place
												// based on IGenID

}

long CPatPost::CreateorActivatePost_PAT(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(m_ObjType == INODE || m_ObjType == CNODE || m_ObjType == CURVE)
	{
		Init_PAT();
		return 0L;
	}
	/////////////////////////////////////////// Parent Info
	m_ParentType	= PATCH;
	m_strParentType = "Patch";
	///////////////////////////////////////////////////////// EDIM_1D
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == EDIM_0)
		return 0L;
	///
	if(CntlID == EDIM_1)
	{
		/////////////////////////////////////////////////////////
		GetPost1DDlg()->m_ObjType = m_ObjType;
		///////////////////////////////////////
		if(GetPost1DDlg()->GetSafeHwnd() ==0)	// not created already
		{
			GetPost1DDlg()->Create();
			CRect BoxRect;
			CWnd  wndTopMost;
			GetPost1DDlg()->GetWindowRect(&BoxRect);
			SizeRectDlgIn(BoxRect);
			//////////////////////////////////////////////////////////////
			GetPost1DDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
	                       BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
			//////////////////////////////////////////////////////////////
			Init_PAT();
			///////////
		}
		else
		{
			GetPost1DDlg()->SetActiveWindow();
			GetPost1DDlg()->m_ObjType = m_ObjType;
		}
	}
	///
	if(CntlID == EDIM_2)
	{
		/////////////////////////////////////////////////////////
		GetPost2DDlg()->m_ObjType = m_ObjType;
		///////////////////////////////////////
		if(GetPost2DDlg()->GetSafeHwnd() ==0)	// not created already
		{
			GetPost2DDlg()->Create();
			CRect BoxRect;
			CWnd  wndTopMost;
			GetPost2DDlg()->GetWindowRect(&BoxRect);
			SizeRectDlgIn(BoxRect);
			//////////////////////////////////////////////////////////////
			GetPost2DDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
	                       BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
			//////////////////////////////////////////////////////////////
			Init_PAT();
			///////////
		}
		else
		{
			GetPost2DDlg()->SetActiveWindow();
			GetPost2DDlg()->m_ObjType = m_ObjType;
		}
	}
	////////////////
	switch(m_ObjType)
	{
		////////////////////////////////////////////////// 0D
		case INODE://	UpdateDlg_FALSE_INODE();	break;
		case CNODE://	UpdateDlg_FALSE_CNODE();	break;
		////////////////////////////////////////////////// 1D
//		case CURVE:		UpdateDlg_FALSE_CURVE();	break;
		///
		case TRUSS:		UpdateDlg_FALSE_TRUSS();	break;
		case BEAM:		UpdateDlg_FALSE_BEAM();		break;
		case PIPE:		UpdateDlg_FALSE_PIPE();		break;
		case ELBOW:		UpdateDlg_FALSE_ELBOW();	break;
		////////////////////////////////////////////////// 2D
		case TR_3:
		case TR_6:
		case TR_9:
		case TR_10:		UpdateDlg_FALSE_TRI();	break;
		////
		case QU_4:
		case QU_8:
		case QU_9:
		case QU_12:
		case QU_16:		UpdateDlg_FALSE_QUAD();	break;
		////////////////////////////////////////////////// 
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if CreODlg Open
	if(GetPost2DDlg()->m_hWnd)
	{
/*
		CStatic* pCtl;
		pCtl = (CStatic*)(GetPost2DDlg()->GetDlgItem(IDC_OTHER));
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
	 
long CPatPost::GoodByePost_PAT(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == CURVE)
		return 0L;
	////////////////////
	if(CntlID == EDIM_1)
		GetPost1DDlg()->DestroyWindow();
	////////////////////////////
	if(CntlID == EDIM_2)
		GetPost2DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_PAT(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CPatPost::CancelPost_PAT(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == CURVE)
		return 0L;
	////////////////////
	if(CntlID == EDIM_1)
		GetPost1DDlg()->DestroyWindow();
	////////////////////////////
	if(CntlID == EDIM_2)
		GetPost2DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_PAT(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CPatPost::UpdatePost_PAT(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int CntlID	= pWnd->GetCurrentCntlID();
	///
	if(CntlID == CURVE)
		return 0L;
	////////////////////
	if(CntlID == EDIM_1)
	{
		GetPost1DDlg()->UpdateData(TRUE);
		UpdateDlg_TRUE_CUR();
	}
	////////////////////////////
	if(CntlID == EDIM_2)
	{
		GetPost2DDlg()->UpdateData(TRUE);
		UpdateDlg_TRUE_PAT();
	}
	//////////////////////////////////////
	switch(m_ObjType)
	{
		////////////////////////////////////////////////// 0D
		case INODE://	UpdateDlg_FALSE_INODE();	break;
		case CNODE://	UpdateDlg_FALSE_CNODE();	break;
		////////////////////////////////////////////////// 1D
//		case CURVE:		UpdateDlg_FALSE_CURVE();	break;
		///
		case TRUSS:		UpdateDlg_FALSE_TRUSS();	break;
		case BEAM:		UpdateDlg_FALSE_BEAM();		break;
		case PIPE:		UpdateDlg_FALSE_PIPE();		break;
		case ELBOW:		UpdateDlg_FALSE_ELBOW();	break;
		////////////////////////////////////////////////// 2D
		case TR_3:		
		case TR_6:		
		case TR_9:	
		case TR_10:		UpdateDlg_FALSE_TRI();		break;
		////
		case QU_4:	
		case QU_8:	
		case QU_9:
		case QU_12:	
		case QU_16:		UpdateDlg_FALSE_QUAD();	break;
		////////////////////////////////////////////////// 
		default:
			break;
	}
	//////////
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CPatPost::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString str,strCur;
	UINT ID;
	///////////////////////////////////
	if(IGenID != PATCH)
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
				case PATCH:
					str = "PATCH";
					pWnd->SetstrIGenID(str);
					///////////////////////////////////// .
					switch(CntlID)
					{
						//////////////////////////////////////// Elements:0D
						case EDIM_0:

							switch(PostID)
							{
								case INODE:			str = "Input@NODE";				ID = INODE;
									strCur += "Input NODE Posting@CLICK ON a Patch";	break;

								case CNODE:			str = "Control@NODE";			ID = CNODE;
									strCur += "Control NODE Posting@CLICK ON a Patch";	break;

								case BALLJOINT:			str = "BALL@JOINT";			ID = BALLJOINT;
									strCur += "BALL JOINT Posting@CLICK ON a Patch";	break;
								
								default:			str = "UNKNOWN";	ID = UNONE;		break;
							}
							break;
						//////////////////////////////////////// Elements:1D
						case EDIM_1:

							switch(PostID)
							{
								case CURVE:			str = "CURVE";			ID = CURVE;
									strCur += "CURVE Posting@CLICK ON a Patch";	break;

								case TRUSS:			str = "TRUSS";			ID = TRUSS;
									strCur += "TRUSS Posting@CLICK ON a Patch";	break;

								case BEAM:			str = "BEAM";			ID = BEAM;
									strCur += "BEAM Posting@CLICK ON a Patch";	break;

								case PIPE:			str = "PIPE";			ID = PIPE;
									strCur += "PIPE Posting@CLICK ON a Patch";	break;

								case ELBOW:			str = "ELBOW";			ID = ELBOW;
									strCur += "ELBOW Posting@CLICK ON a Patch";	break;

								default:			str = "UNKNOWN";	ID = UNONE;		break;
							}
							break;
						//////////////////////////////////////// Elements:2D
						case EDIM_2:

							switch(PostID)
							{
								case TR_3:			str = "3-Node@TRIANGLE";	ID = TR_3;
									strCur += "3-Node Triangle Posting@CLICK ON a Patch";	break;

								case TR_6:			str = "6-Node@TRIANGLE";	ID = TR_6;
									strCur += "6-Node Triangle Posting@CLICK ON a Patch";	break;

								case TR_9:			str = "9-Node@TRIANGLE";	ID = TR_9;
									strCur += "9-Node Triangle Posting@CLICK ON a Patch";	break;

								case TR_10:			str = "10-Node@TRIANGLE";	ID = TR_10;
									strCur += "10-Node Triangle Posting@CLICK ON a Patch";	break;

								case QU_4:			str = "4-Node@QUADRILAT";	ID = QU_4;
									strCur += "4-Node Quadrilateral Posting@CLICK ON a Patch";	break;

								case QU_8:			str = "8-Node@QUADRILAT";	ID = QU_8;
									strCur += "8-Node Quadrilateral Posting@CLICK ON a Patch";	break;

								case QU_9:			str = "9-Node@QUADRILAT";	ID = QU_9;
									strCur += "9-Node Quadrilateral Posting@CLICK ON a Patch";	break;

								case QU_12:			str = "12-Node@QUADRILAT";	ID = QU_12;
									strCur += "12-Node Quadrilateral Posting@CLICK ON a Patch";	break;

								case QU_16:			str = "16-Node@QUADRILAT";	ID = QU_16;
									strCur += "16-Node Quadrilateral Posting@CLICK ON a Patch";	break;

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
	

void CPatPost::Serialize(CArchive& ar)
{

	CCurPost::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatPost:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatPost:    Loading\n");	

	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


