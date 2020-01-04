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
//#include "EDlgMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Elems
#include "Def_Elem.h"
#include "DrFE0D.h"
//////////////////////
#include "Po_Pipe.h"
#include "Po_Beam.h"
#include "Po_Truss.h"
#include "Po_Elbow.h"
//////////////////////
#include "MI_GangN.h"	// for INODE and CNODE
#include "MI_GangC.h" 
#include "MI_Gang0.h"	// for FE0D 
#include "MI_Gang1.h" 
//////////////////////
#include "CurPost.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_INODE		0	// 1 Object        
#define MAX_INFO_CNODE		0	// 1 Object        
#define MAX_INFO_TRUSS		0	// 1 Object        
#define MAX_INFO_BEAM		0	// 1 Object        
#define MAX_INFO_PIPE		0	// 1 Object        
#define MAX_INFO_ELBOW		0	// 1 Object        
///////////////////////////////////////////////////////////////////////////////////////////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CCurPost,CNodPost,1)
/////////////////////////////////////////////////////////////////////////////
CCurPost::CCurPost()
{

	m_pPost1DDlg		= NULL;
	/////////////////////////////////////////// 
    m_pCurrentCurve		= NULL;
}

CCurPost::~CCurPost()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pPost1DDlg->m_hWnd)
		m_pPost1DDlg->DestroyWindow();
	///////////////////
	delete m_pPost1DDlg; 
	///////////////////
}

void CCurPost::InitDlgIn_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pPost1DDlg	= new CDlg_FE1I(pWnd);
	/////////////////////////////////////////////////////////////////// Init
}

void CCurPost::Init_CUR()
{
	Init_NOD();
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	/////////////////////////////
	pMsObjMgr->SetElemInfoID(m_PostedID,MESH1D);
	/////////////////////////////////////////// Node
	m_pMesh1D			= NULL;
	m_ParentID			= "";
	m_pCurrentCurve		= NULL;
	/////////////////////////////////////////// Dlg_FE1I 
	m_bValve			= FALSE;
	m_matID				= "";
	m_KNodeID			= ""; // 
	m_propID			= "";
	m_rid_I				= "";
	m_rid_J				= "";
	m_stressID_I		= "";
	m_stressID_J		= "";
	m_RefTemp			= 0.0;
	/////////////////////////////////////////// STitch

}

void CCurPost::Terminate_CUR(BOOL bError)
{
//	Terminate_NOD(bError);
	////
	if(bError)
	{
		/////////////////////////////////////////// 
		if(m_pMesh1D)
		{
			delete m_pMesh1D;
			m_pMesh1D = NULL;
		}
		///////////////////////////
	}
}

void CCurPost::ElementLeftDown_CUR()
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

int CCurPost::ShowCurveToPost(CDrCurve* pDrCurve, BOOL bToBePosted)
{
	//  ISOCURVES todo
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pObjList;
	int			nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);                   
	////////////////////////////////////////////////////////////////////// Show Curve to Post
	pDrCurve->SetToBePosted(bToBePosted);
	//////////////////////////////
	pObjList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pObjList->GetObjectIndex(CURVE,pDrCurve->GetObjectID());
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
	///////////////////////////////
	return 0;
}	 

int CCurPost::MarkCurve_Post(CDrCurve* pDrCurve)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);                   
	////////////////////////////////////////////////////////////////////// Curve to Post
	pDrCurve->SetPosted(TRUE);
	///////////////////////////////
	return 0;
}	 
	
void CCurPost::OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	if(pDListMgr->GetCount()<=0 )
		return;
	/////////////////////////////////////////////////////////////////
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_CUR();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CCurPost::UpdateDlg_TRUE_CUR()
{
	/////////////////////////////////////////////////////
	m_pPost1DDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_KNodeID		= GetPost1DDlg()->m_KNodeID;
	m_bValve		= GetPost1DDlg()->m_bValve;	
	m_matID			= GetPost1DDlg()->m_matID;
	m_propID		= GetPost1DDlg()->m_propID;
	m_rid_I			= GetPost1DDlg()->m_rid_I;
	m_rid_J			= GetPost1DDlg()->m_rid_J;
	m_stressID_I	= GetPost1DDlg()->m_stressID_I;
	m_stressID_J	= GetPost1DDlg()->m_stressID_J;
	m_RefTemp		= GetPost1DDlg()->m_RefTemp;
	m_ObjType		= GetPost1DDlg()->m_ObjType;
	////////////////////////
}			

void CCurPost::UpdateDlg_FALSE_CUR()
{
	////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////////
	GetPost1DDlg()->m_KNodeID		= m_KNodeID;
	GetPost1DDlg()->m_bValve		= m_bValve;	
	GetPost1DDlg()->m_matID			= m_matID;
	GetPost1DDlg()->m_propID		= m_propID;
	GetPost1DDlg()->m_rid_I			= m_rid_I;
	GetPost1DDlg()->m_rid_J			= m_rid_J;
	GetPost1DDlg()->m_stressID_I	= m_stressID_I;
	GetPost1DDlg()->m_stressID_J	= m_stressID_J;
	GetPost1DDlg()->m_RefTemp		= m_RefTemp;
	GetPost1DDlg()->m_ObjType		= m_ObjType;
	////////////////////////////////////////////////////////////
	GetPost1DDlg()->GetDlgItem(IDC_KNODEHEAD)->SetWindowText("");
	GetPost1DDlg()->GetDlgItem(IDC_RELEASEHEAD)->SetWindowText("");
	GetPost1DDlg()->GetDlgItem(IDC_SIHEAD)->SetWindowText("");
	GetPost1DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_I)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_J)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_PID)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_MID)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_VALVE)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDD_BEAM_NID_K)->EnableWindow(FALSE);
	GetPost1DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(FALSE);
	//////////////////////////////////////
}

void CCurPost::UpdateDlg_FALSE_CUR_0()
{
	///////////////////
	UpdateDlg_FALSE_CUR();
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
		default:
			return;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->SetText(strCurr);
	pWnd->GetCurrStat()->Invalidate();
	pWnd->GetCurrStat()->UpdateWindow();
	////////////////////////////////////////////////
	m_pPost1DDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CCurPost::UpdateDlg_FALSE_INODE()
{
	if(m_ObjType != INODE)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
/*
			///////////////////
			UpdateDlg_FALSE_CUR_0();
			///////////////////
			GetPost1DDlg()->SetWindowText("INPUT NODE Posting Info");
			////////////////////////////////////////////////
			m_pPost1DDlg->UpdateData(FALSE); // To screen
			////////////////////////////////////////////////
*/
			return;
		case 1:
			///////////////////
			return;
	}
}

void CCurPost::UpdateDlg_FALSE_CNODE()
{
	if(m_ObjType != CNODE)
		return;
	///////////////////
	UpdateDlg_FALSE_CUR();
	UpdateDlg_FALSE_CUR_0();
	///////////////////
	GetPost1DDlg()->SetWindowText("CONTROL NODE Posting Info");
	////////////////////////////////////////////////
	m_pPost1DDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CCurPost::UpdateDlg_FALSE_1D()
{
	////////////////
	switch(m_nActiveTool)
	{
		case TRUSS:
			//////////////////////////////
			UpdateDlg_FALSE_TRUSS();
			////
			break;
		case BEAM:
			//////////////////////////////
			UpdateDlg_FALSE_BEAM();
			////
			break;
		case PIPE:
			//////////////////////////////
			UpdateDlg_FALSE_PIPE();
			////
			break;
		case ELBOW:
			//////////////////////////////
			UpdateDlg_FALSE_ELBOW();
			////
			break;
		default:
			break;
	}
}
	 

void CCurPost::UpdateDlg_FALSE_TRUSS()
{
	if(m_ObjType != TRUSS)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:

			UpdateDlg_FALSE_CUR();
			UpdateDlg_FALSE_CUR_0();
			///////////////////
			GetPost1DDlg()->SetWindowText("TRUSS Posting Info");
			///
			GetPost1DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost1DDlg->UpdateData(FALSE); // To screen
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
	}
	///////
	return;
}

void CCurPost::UpdateDlg_FALSE_BEAM()
{
	if(m_ObjType != BEAM)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:

			UpdateDlg_FALSE_CUR();
			UpdateDlg_FALSE_CUR_0();
			///////////////////
			GetPost1DDlg()->SetWindowText("BEAM Posting Info");
			///
			GetPost1DDlg()->GetDlgItem(IDC_KNODEHEAD)->SetWindowText("K Node");
			GetPost1DDlg()->GetDlgItem(IDD_BEAM_NID_K)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDC_RELEASEHEAD)->SetWindowText("Release");
			GetPost1DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost1DDlg->UpdateData(FALSE); // To screen
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
	}
	///////
	return;
}

void CCurPost::UpdateDlg_FALSE_PIPE()
{
	if(m_ObjType != PIPE)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:

			///////////////////
			UpdateDlg_FALSE_CUR();
			UpdateDlg_FALSE_CUR_0();
			///////////////////
			GetPost1DDlg()->SetWindowText("PIPE Posting Info");
			///
			GetPost1DDlg()->GetDlgItem(IDC_RELEASEHEAD)->SetWindowText("Release");
			GetPost1DDlg()->GetDlgItem(IDC_SIHEAD)->SetWindowText("Stress Index");
			GetPost1DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_I)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_J)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_VALVE)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost1DDlg->UpdateData(FALSE); // To screen
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
	}
	///////
	return;
}

void CCurPost::UpdateDlg_FALSE_ELBOW()
{
	if(m_ObjType != ELBOW)
		return;
	///////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////////////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:

			///////////////////
			UpdateDlg_FALSE_CUR();
			UpdateDlg_FALSE_CUR_0();
			///////////////////
			GetPost1DDlg()->SetWindowText("ELBOW Posting Info");
			///
			GetPost1DDlg()->GetDlgItem(IDC_RELEASEHEAD)->SetWindowText("Release");
			GetPost1DDlg()->GetDlgItem(IDC_SIHEAD)->SetWindowText("Stress Index");
			GetPost1DDlg()->GetDlgItem(IDD_RID_I)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_RID_J)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_I)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PIPE_STRESS_ID_J)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_PID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDD_MID)->EnableWindow(TRUE);
			GetPost1DDlg()->GetDlgItem(IDC_REFTEMP)->EnableWindow(TRUE);
			////////////////////////////////////////////////
			m_pPost1DDlg->UpdateData(FALSE); // To screen
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
	}
	///////
	return;
}

int CCurPost::LeftUp_CURVE(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pDrCurve;
	int			nActiveIndex,index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(CURVE,point,0);
	////////////////////////////////////////////////////
	if(index<0)
		return -1; // No Curve Hit
	////////////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	/////////////////////////////////////////
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);	// set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
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
			CMI_Gang1 Gang1;
			nResult = Gang1.ShowCurveInfo(pDrCurve);
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
				index = IsObjectHit(CURVE,point,startIndex);
				if(index>=0)
				{
					pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
					ID			= pDrCurve->GetObjectID();
					///////////////////////////////////////// 
					pList = pObjectMgr->GetObjectList(CURVE);
					nActiveIndex = pList->GetObjectIndex(CURVE, ID);;
					pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
					pObjectMgr->SetActiveObjectType(CURVE);		    // set Active Index									
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,CURVE);
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
	m_pCurrentCurve = pDrCurve;
	///////////////////////////
	if(ShowCurveToPost(pDrCurve,TRUE)<0)
	{
		AfxMessageBox("ERROR:\nCCurPost::LeftUp_Curve\nShowCurveToPost Problem");
		return -1;
	}
	//////////
	return 0;
}

void CCurPost::ElementLeftUp_CUR(CPoint point)
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
	switch(m_nActiveTool) 
	{
		/////////////////////////////////// 0D
		case INODE:				//
			
			if(m_nInfoDone > MAX_INFO_INODE)
				return;
			////////////////
//			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
//			m_nInfoDone++;
//			UpdateDlg_FALSE_CUR();
			///////
			//////////////////
			if(Post_IorCNODE(m_pCurrentCurve,FALSE)<0)// FALSE = NOT CNode
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
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
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
//			m_nInfoDone++;
//			UpdateDlg_FALSE_CUR();
			///////
			//////////////////
			if(Post_IorCNODE(m_pCurrentCurve,TRUE)<0)// TRUE = YES CNode
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
//				UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			return;

		/////////////////////////////////// 1D
		case TRUSS:				// fall thro'
			
			if(m_nInfoDone > MAX_INFO_TRUSS)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_TRUSS();
			///////
			return;

		case BEAM:				// 
			
			if(m_nInfoDone > MAX_INFO_BEAM)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_BEAM();
			///////
			return;

		case PIPE:				//
			
			if(m_nInfoDone > MAX_INFO_PIPE)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_PIPE();
			///////
			return;

		case ELBOW:				// 
			
			if(m_nInfoDone > MAX_INFO_ELBOW)
				return;
			////////////////
			UpdateDlg_TRUE_CUR();
			//////////////////
			if(LeftUp_CURVE(point)<0)	
			////////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			/////////////
			m_nInfoDone++;
			UpdateDlg_FALSE_ELBOW();
			///////
			return;

		//////////////////////////////////////////////////
		default:  
			return;
	} 
}	

void CCurPost::OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_CUR(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////////////
	
}

int CCurPost::Post_IorCNODE(CDrCurve* pCurve, BOOL bCNode)		
{
	int nResult;		
	//////////////////////////////////////////// Output memory
	int nOut		= pCurve->GetLongOutPts();
	/////////////////////////////////////////////////////////
	CMI_GangC GangC;
	////////////////////////////////
	pWORLD	pOut	= GangC.FixMem(nOut);
	pDOUBLE pOutWts = GangC.FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	GangC.SetbBack(FALSE);
	GangC.FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	///////////////////////////////////////////////////////// Post IorCNodes / NO Reciprocation
	CMI_Gang1 Gang1;
	nResult = Gang1.Post_CurveNodes_IorC(pCurve,pOut,nOut,bCNode);
	////////////////////////
	GangC.FreeMem(pOut);
	GangC.FreeMemD(pOutWts);
	////////////////////////
	if(nResult<0)
		return nResult;
	/////////
	return 0;
}

int CCurPost::PrePost_Curve(CDrCurve* pDrCurve,CObject* pGang1,BOOL b0D)		
{
	//		1D ELEMENT POSTING
	///////////////////////////////
	int nResult;
	////////////////////////////////////////////////// Post Mesh & Vertices
	nResult = GenPost_Mesh_Vertices(pDrCurve,TRUE,TRUE);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Transfer Data
	if(b0D)
		nResult = FillData_Curve_0D(pGang1);	// for 0D Elements:BallJoint etc
	else
		nResult = FillData_Curve_1D(pGang1);	// for 1D Elements:Truss etc
	//////////////
	if(nResult<0)
		return -1;
	/////////
	return 0;
}

int CCurPost::GenPost_Mesh_Vertices(CDrCurve* pDrCurve,BOOL bMNode,BOOL bAnyWay)		
{
	///////////////////////////////////////////////////////////////
	//	bMNode	= FALSE -> just FE0D( i.e. Vertices)
	//	bAnyWay = TRUE  -> create Nodes Anyway, e.g. crack modeling
	///////////////////////////////////////////////////////////////
	int nResult,nActiveIndex;
	////////////////////////////////////////////////// Post Mesh
	nResult = Pre_Common_1D(pDrCurve,nActiveIndex);
	//////////////
	if(nResult<0)
		return -1;
	///////////////////////////////////////////////////////// Post Nodes
	CMI_Gang1 Gang1;
	nResult = Gang1.GenPost_CurveNodes(m_pMesh1D,pDrCurve,bMNode,bAnyWay); 		
	//////////////
	if(nResult<0)
		return -1;
	/////////
	return 0;
}

int CCurPost::Pre_Common_1D(CDrCurve* pDrCurve,int& nActiveIndex)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pObjectMgr 	= pDoc->GetMsObjMgr();
	///
	int nResult;		
	///////////////////////////////////////////////////////// Create Mesh
	m_pMesh1D	= (CDrMesh1D*)(pObjectMgr->AddToDataBase(nActiveIndex,MESH1D));
	if(!m_pMesh1D)
	{
		AfxMessageBox("Internal ERROR:\nCurPost::Pre_Common_1D\nm_pMesh1D == NULL");
		return -1;
	}
	//////////////////////////////////////////////
	m_pMesh1D->SetDirty(FALSE);	// Posted Type
	m_pMesh1D->SetShow(FALSE);	// not quite ready
	m_pMesh1D->SetGenObj(pDrCurve);
	m_pMesh1D->SetObjectID(m_PostedID);
	//////////////////////////////////////////////
	m_line_id	= m_pMesh1D->GetObjectID();
	/////////////////////////////////////// Genetics
	m_GenObjType	= MESH1D;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
	m_pGenObj		= m_pMesh1D;
	/////////////////////////////////////// 
	return nResult;
}

int CCurPost::Post_Common_1D(CDrCurve* pDrCurve,int nActiveIndex, int nResult)
{		
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///
	if(nResult<0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex,MESH1D);
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
		m_pMesh1D->GetCurveList()->InsertObject(pDrCurve);
		pDrCurve->GetElemList()->InsertObject(m_pMesh1D);
		m_pMesh1D->SetShow(TRUE);	// Now Ready
		m_pMesh1D->SetPosted(TRUE);	// Posted Curve
		///
		CString MeshID = m_pMesh1D->GetObjectID(); 
		UpdateSceneView(MeshID,MESH1D);
		///
	}
	/////////
	return 0;
}

int CCurPost::FillData_Curve_0D(CObject* pGang1)		
{
	CMI_Gang1* pGang = (CMI_Gang1*)pGang1;
	//////
	return -1; // todo
}

int CCurPost::FillData_Curve_1D(CObject* pGang1)		
{
	CMI_Gang1* pGang = (CMI_Gang1*)pGang1;
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

void CCurPost::OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CCurPost::OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case CURVE:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

void CCurPost::OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
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
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Is Enough Info?
	if(RightUp_Premature_CUR()<0)
		return;
	///////////////////////////////////////////////////////// Not Auto Accept
	////////////////////////////////////////////////// Update Info
	UpdateDlg_TRUE_CUR();
	/////////////////
	if(RightUp_NotAutoAccept_CUR()<0)
	{
		Terminate_CUR(TRUE);
		return;
	}
	//////////////////////
	CMI_Gang1	Gang1;
	int			nResult,nActiveIndex;
	BOOL		b0D = FALSE;
	///////////////////////////////////////////////////// Show Spawned Node 
	switch(m_nActiveTool) 
	{
	
		/////////////////////////////////// 0D
		case INODE:				//
			
			return;			// IGNORE Everything Below
			//////////////////
			if(Post_IorCNODE(m_pCurrentCurve,FALSE)<0)// FALSE = NOT CNode
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_INODE();
				break;
			}
			///////////////////	
			break;

		case CNODE:				//
			
			return;			// IGNORE Everything Below
			//////////////////
			if(Post_IorCNODE(m_pCurrentCurve,TRUE)<0)// TRUE = CNode
			////////////////
			{
				Terminate_CUR(TRUE);
				return;
			}
			else
			{
				Terminate_CUR(FALSE);
				Init_CUR();
				/////////////////////////
				UpdateDlg_FALSE_CNODE();
				break;
			}
			///////////////////	
			break;
			
		/////////////////////////////////// 1D
		case TRUSS:				// 
		case BEAM:				// 
		case PIPE:				//
		case ELBOW:				//
			
			if(PrePost_Curve(m_pCurrentCurve,(CObject*)&Gang1,b0D)<0)
			{	Terminate_CUR(TRUE);	return;	}
			//////////////////
			if(Gang1.Post_Curve_Elements(m_pMesh1D,m_pCurrentCurve,MESH1D,m_nActiveTool)<0)
			////////////////
			{	Terminate_CUR(TRUE);	return;	}
			else
			{
				////////////////////////
				nResult = 0;	// nActiveIndex not needed below
				nResult = Post_Common_1D(m_pCurrentCurve,nActiveIndex,nResult);
				//////////////
				if(nResult<0)
					{Terminate_CUR(TRUE);	return;	}
				/////////
				Terminate_CUR(FALSE);	Init_CUR();	UpdateDlg_FALSE_1D();
				break;
			}
			///////////////////	
			break;
		//////////////	
		default:  
			return;
	} 
	////////////////////////////////////////////////////////////////////////
	pMsObjMgr->SetElemInfoID(m_PostedID,MESH1D);
	////////////////////////////////////////////////////////////////////////
}

int CCurPost::RightUp_Premature_CUR()
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
		case INODE:

			if(m_nInfoDone<MAX_INFO_INODE)
				bPreMature = TRUE;
			break;

		case CNODE:

			if(m_nInfoDone<MAX_INFO_CNODE)
				bPreMature = TRUE;
			break;

		case TRUSS:

			if(m_nInfoDone<MAX_INFO_TRUSS)
				bPreMature = TRUE;
			break;

		case BEAM:

			if(m_nInfoDone<MAX_INFO_BEAM)
				bPreMature = TRUE;
			break;

		case PIPE:

			if(m_nInfoDone<MAX_INFO_PIPE)
				bPreMature = TRUE;
			break;


		case ELBOW:

			if(m_nInfoDone<MAX_INFO_ELBOW)
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

int CCurPost::RightUp_NotAutoAccept_CUR()
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
			case INODE:

				nAnswer = ShowInputInfo_INODE();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case CNODE:

				nAnswer = ShowInputInfo_CNODE();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case TRUSS:

				nAnswer = ShowInputInfo_TRUSS();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case BEAM:


				nAnswer = ShowInputInfo_BEAM();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case PIPE:

				nAnswer = ShowInputInfo_PIPE();
				if(nAnswer<0)
					return -1;
				//////////////
				break;


			case ELBOW:

				nAnswer = ShowInputInfo_ELBOW();
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

int CCurPost::ShowInputInfo_INODE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** INPUT NODE Info ******");
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

int CCurPost::ShowInputInfo_CNODE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** CONTROL NODE Info ******");
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

int CCurPost::ShowInputInfo_TRUSS()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** TRUSS Info ******\n\n");
	///
	j += sprintf( buf + j, "Property ID = \t%s\n",m_propID); // 
	j += sprintf( buf + j, "Material ID = \t%s\n",m_matID); // 
	j += sprintf( buf + j, "Ambient Temp. = \t%f\n",m_RefTemp); // 
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

int CCurPost::ShowInputInfo_BEAM()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** BEAM Info ******\n\n");
	///
	j += sprintf( buf + j, "K-Node ID = \t%s\n",m_KNodeID); // 
	j += sprintf( buf + j, "Property ID = \t%s\n",m_propID); // 
	j += sprintf( buf + j, "Material ID = \t%s\n",m_matID); // 
	j += sprintf( buf + j, "Release ID_I = \t%s\n",m_rid_I); // 
	j += sprintf( buf + j, "Release ID_J = \t%s\n",m_rid_J); // 
	j += sprintf( buf + j, "Ambient Temp. = \t%f\n",m_RefTemp); // 
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

int CCurPost::ShowInputInfo_PIPE()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** PIPE Info ******\n\n");
	///
	j += sprintf( buf + j, "Property ID = \t%s\n",m_propID); // 
	j += sprintf( buf + j, "Material ID = \t%s\n",m_matID); // 
	j += sprintf( buf + j, "Release ID_I = \t%s\n",m_rid_I); // 
	j += sprintf( buf + j, "Release ID_J = \t%s\n",m_rid_J); // 
	j += sprintf( buf + j, "StressIndex_I = \t%s\n",m_stressID_I); // 
	j += sprintf( buf + j, "StressIndex_J = \t%s\n",m_stressID_J); // 
	j += sprintf( buf + j, "Ambient Temp. = \t%f\n",m_RefTemp); // 
	if(m_bValve)
		j += sprintf( buf + j, "\n\nA Valve is Modeled as PIPE\n"); // 
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

int CCurPost::ShowInputInfo_ELBOW()
{
	///////////////////////////////////////////////////////////// show Info
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	//////////
	j = sprintf(buf,"***** ELBOW Info ******\n\n");
	///
	j += sprintf( buf + j, "Property ID = \t%s\n",m_propID); // 
	j += sprintf( buf + j, "Material ID = \t%s\n",m_matID); // 
	j += sprintf( buf + j, "Release ID_I = \t%s\n",m_rid_I); // 
	j += sprintf( buf + j, "Release ID_J = \t%s\n",m_rid_J); // 
	j += sprintf( buf + j, "StressIndex_I = \t%s\n",m_stressID_I); // 
	j += sprintf( buf + j, "StressIndex_J = \t%s\n",m_stressID_J); // 
	j += sprintf( buf + j, "Ambient Temp. = \t%f\n",m_RefTemp); //
	///
/*							todo
	CString		m_CCID;
	CString		m_TIID;
	CString		m_CAID;
	CString		m_CBID;
*/
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
void CCurPost::ModeLessOff_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetPost1DDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_FE1IN,IDOK);
}

void CCurPost::ModeLessOn_CUR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
	m_ObjType = aTool;
	////////////////////////////
//		if(!(GetCreOpDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_FE1IN);	// pWnd will dispatch to right place
												// based on IGenID

}

long CCurPost::CreateorActivatePost_CUR(UINT wParam, long lParam)
{
	if(m_ObjType == INODE || m_ObjType == CNODE)
	{
		Init_CUR();
		return 0L;
	}
	/////////////////////////////////////////// Parent Info
	m_ParentType	= CURVE;
	m_strParentType = "Curve";
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
		Init_CUR();

	}
	else
	{
		GetPost1DDlg()->SetActiveWindow();
		GetPost1DDlg()->m_ObjType = m_ObjType;
	}
	////////////////
	switch(m_ObjType)
	{
		case INODE:
			//////////////////////////////
			UpdateDlg_FALSE_INODE();
			////
			break;
		case CNODE:
			//////////////////////////////
			UpdateDlg_FALSE_CNODE();
			////
			break;
		case TRUSS:
			//////////////////////////////
			UpdateDlg_FALSE_TRUSS();
			////
			break;
		case BEAM:
			//////////////////////////////
			UpdateDlg_FALSE_BEAM();
			////
			break;
		case PIPE:
			//////////////////////////////
			UpdateDlg_FALSE_PIPE();
			////
			break;
		case ELBOW:
			//////////////////////////////
			UpdateDlg_FALSE_ELBOW();
			////
			break;
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if CreODlg Open
	if(GetPost1DDlg()->m_hWnd)
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
	 
long CCurPost::GoodByePost_CUR(UINT wParam, long lParam)
{
	
	GetPost1DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_CUR(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CCurPost::CancelPost_CUR(UINT wParam, long lParam)
{
	
	GetPost1DDlg()->DestroyWindow();
	////////////////
	{
		Terminate_CUR(FALSE);
		return 0L;
	}
	//////////
	return 0L;
}
	 
long CCurPost::UpdatePost_CUR(UINT wParam, long lParam)
{

	GetPost1DDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	UpdateDlg_TRUE_CUR();
	////////////////
	switch(m_ObjType)
	{
		case INODE:

			//////////////////////////////
//			UpdateDlg_FALSE_INODE();
			////
			break;
		case CNODE:

			//////////////////////////////
//			UpdateDlg_FALSE_CNODE();
			////
			break;
		case TRUSS:

			//////////////////////////////
			UpdateDlg_FALSE_TRUSS();
			////
			break;
		case BEAM:

			//////////////////////////////
			UpdateDlg_FALSE_BEAM();
			////
			break;
		case PIPE:

			//////////////////////////////
			UpdateDlg_FALSE_PIPE();
			////
			break;
		case ELBOW:
			//////////////////////////////
			UpdateDlg_FALSE_ELBOW();
			////
			break;
		default:
			break;
	}
	//////////
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CCurPost::ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString str,strCur;
	UINT ID;
	///////////////////////////////////
	if(IGenID != CURVE)
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
				case CURVE:
					str = "CURVE";
					pWnd->SetstrIGenID(str);
					///////////////////////////////////// .
					switch(CntlID)
					{
						//////////////////////////////////////// Elements:0D
						case EDIM_0:

							switch(PostID)
							{
								case INODE:			str = "Input@NODE";				ID = INODE;
									strCur += "Input NODE Posting@CLICK ON a Curve";	break;

								case CNODE:			str = "Control@NODE";			ID = CNODE;
									strCur += "Control NODE Posting@CLICK ON a Curve";	break;

								case BALLJOINT:			str = "BALL@JOINT";			ID = BALLJOINT;
									strCur += "BALL JOINT Posting@CLICK ON a Curve";	break;
								
								default:			str = "UNKNOWN";	ID = UNONE;		break;
							}
							break;
						//////////////////////////////////////// Elements:1D
						case EDIM_1:

							switch(PostID)
							{
								case TRUSS:			str = "TRUSS";			ID = TRUSS;
									strCur += "TRUSS Posting@CLICK ON a Curve";	break;

								case BEAM:			str = "BEAM";			ID = BEAM;
									strCur += "BEAM Posting@CLICK ON a Curve";	break;

								case PIPE:			str = "PIPE";			ID = PIPE;
									strCur += "PIPE Posting@CLICK ON a Curve";	break;

								case ELBOW:			str = "ELBOW";			ID = ELBOW;
									strCur += "ELBOW Posting@CLICK ON a Curve";	break;

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
	

void CCurPost::Serialize(CArchive& ar)
{

	CNodPost::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CurPost:    Storing\n");	
		

	}
	else
	{
		TRACE(" CurPost:    Loading\n");	

	
	}        
	//////////////////
}

///////////////////////////////////// end of Module //////////////////////		


