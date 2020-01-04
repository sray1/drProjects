// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
//#include "Def_Eror.h" // Mouse Action ERROR
//#include "Def_Cond.h" // Mouse Action Condition
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
//#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_MouseAct.h" // Mouse Action                   
#include "Def_CuPS.h"                    
#include "Str_BlendEnd.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MPatMgr.h"  
#include "BasePage.h"
#include "CommRsrc.h"	// IDC_ADVANCED
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
//#include "DrFE1D.h"
//#include "DrFE2D.h"
#include "DrCurve.h"
#include "DrPatch.h"
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
#include "Loft_Com.h"	// Loft Curve Compatibility
#include "MI_GangP.h" 
/*
//	Moved to CreOMgr Dll   01/14/98 
#include "MI_PSPN.h" 
//	Moved to CreOMgr Dll   01/14/98 end
*/
//////////////////////
#include "PatMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_EXTRUDE	3	// 1 Curves/2 Nodes        
#define MAX_INFO_ROTATE		3	// 1 Curves/2 Nodes           
#define MIN_INFO_TENSOR		4	// 4 Nodes Minimum(2 in U Dir/2 in V Dir) before Rt. Button           
#define MIN_INFO_GORDON		4	// 4 Curves Minimum(2 in U Dir/2 in V Dir) before Rt. Button           
#define MIN_INFO_LOFT		2	// 2 Curves Minimum before Rt. Button           
#define MAX_INFO_DUCT		3	// 2 Curves/1 Node        
#define MAX_INFO_SWEEP		3	// 2 Curves/1 Node    
#define MAX_INFO_COONS		4	// 3 or 4 Curves  
///////      
#define MIN_CURVES_PATCH	3        
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
#define MAX_NODES_FE2D		4
///////////////////////////////
/*
#define MA_OK				0
#define MA_ERROR			-1
#define MA_CANCEL			-2
#define MA_GETMOREINFO		-3
*/
////////////////////////////////////
IMPLEMENT_SERIAL(CPatMouse,CCurMouse,1)
/////////////////////////////////////////////////////////////////////////////
CPatMouse::CPatMouse()
{
	m_bEndCondMode		= FALSE;
	m_bEditMode			= FALSE;		// TRUE:User Checking/FALSE:DataInputting
	m_bCornerMode		= FALSE;			// needed for Twist
	/////////////////////////////////////// Reset
	m_bCurveDone		= TRUE;	// 
	m_bPatchDone		= TRUE;	// 
	//////////////////////////////
	m_nNodeDone_U		= 0;	// Tensor Product
	m_nCurveDone_U		= 0;	// Gordon Surface
 	/////////////////////////////////////////// Patch 
	m_nInfoDone			= 0;
	m_nCurveDone		= 0;
	m_nNodeDone			= 0;
	m_nNodes_U			= 0;
	m_nNodes_V			= 0;
	////////////////////////////////////////////
	m_pCornerTwist		= new WORLD[2][2];	// it is full,if TW_USER
	m_PatProc			= PP_SPAWN;	//	arbitrarily other than options offered,
											//	setso it will be created
	/////////////////////////////
	m_nExtruType		= 1;
}

CPatMouse::~CPatMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(GetPatSheet())
	{
		if(GetPatSheet()->m_hWnd)
			GetPatSheet()->DestroyWindow();
		///////////////////
		delete GetPatSheet(); 
		delete [] m_pCornerTwist;
		///////////////////
	}
}

void CPatMouse::InitDlgIn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pPatInSheet = new CSheet_PATI("Tensor Product Patch",pWnd,PP_TENSOR);
	GetPatSheet()->m_PatProc = m_PatProc;	//	arbitrarily other than options offered,
											//	setso it will be created
	/////////////////////////////////////////////////
//	pObjectMgr->SetObjInfoID(m_CurrentPatchID,PATCH);
//	ResetVariables_PAT();
}

int CPatMouse::Terminate_PAT(BOOL bError)
{
	/////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////
	strCurr = "Please Click On START:@To Select An Operation";
	pWnd->SetActiveToolType(UNONE);
	pWnd->SetActiveObjectType(UNONE);
	/////////////////////////////////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	strCurr = "UNKNOWN";
	pWnd->SetstrCntlID(strCurr);
	pWnd->SetCurrentCntlID(UNONE);
	pWnd->SetstrIGenID(strCurr);
	pWnd->SetCurrentIGenID(UNONE);
	strCurr = "START";
	pWnd->SetstrOperID(strCurr);
	pWnd->SetCurrentOperID(UNONE);
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
	//
	m_PatProc = (PATCHPROC)PP_SPAWN; // something other than Procs Offered!
	GetPatSheet()->m_PatProc = m_PatProc;	// so it will be created
	GetPatSheet()->DestroyWindow();
	////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	///////////////////////////////////////// delete
	if(bError)
	{
		pList = pObjectMgr->GetObjectList(PATCH);
		nActiveIndex = pList->GetObjectIndex(PATCH, m_CurrentPatchID);
		if(nActiveIndex>=0)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
			m_pCurrentPatch = (CDrPatch*)NULL;
		}
	}
	/////////////////////////////////////// Reset
//	ResetVariables_PAT();
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
/*
	/////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////
	if(!bError) // 
	{
		/////////////////////////////////////// 
		strCurr = "Please Click On START:@To Select An Operation";
		pWnd->SetActiveToolType(UNONE);
		pWnd->SetActiveObjectType(UNONE);
		/////////////////////////////////
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		strCurr = "UNKNOWN";
		pWnd->SetstrCntlID(strCurr);
		pWnd->SetCurrentCntlID(UNONE);
		pWnd->SetstrIGenID(strCurr);
		pWnd->SetCurrentIGenID(UNONE);
		strCurr = "START";
		pWnd->SetstrOperID(strCurr);
		pWnd->SetCurrentOperID(UNONE);
		pWnd->SendMessage(ID_UPDATE_STATCNTLS);
		//
		m_PatProc = (PATCHPROC)PP_SPAWN; // something other than Procs Offered!
		GetPatSheet()->m_PatProc = m_PatProc;	// so it will be created
		GetPatSheet()->DestroyWindow();
		/////////
		return 0;
	}
	////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(PATCH);
	///////////////////////////////////////// delete
	pList = pObjectMgr->GetObjectList(PATCH);
	nActiveIndex = pList->GetObjectIndex(PATCH, m_CurrentPatchID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
		m_pCurrentPatch = (CDrPatch*)NULL;
	}
	/////////////////////////////////////// Reset
//	ResetVariables_PAT();
	/////////////////// reset
	if(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetSafeHwnd())
	{
		((CBasePage*)(GetPatSheet()->GetActivePage()))->
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	}
	/////////////////////////////////////
	if(m_PatProc == PP_LOFT ||m_PatProc == PP_TENSOR ||m_PatProc == PP_GORDON)
	{
		if(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetSafeHwnd())
		{
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
				GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
		}
		/////////////////////////////////////// 
		strCurr = "Please Click On START:@To Select An Operation";
		pWnd->SetActiveToolType(UNONE);
		pWnd->SetActiveObjectType(UNONE);
		/////////////////////////////////
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		//
		strCurr = "UNKNOWN";
		pWnd->SetstrCntlID(strCurr);
		pWnd->SetCurrentCntlID(UNONE);
		//
		strCurr = "UNKNOWN";
		pWnd->SetstrIGenID(strCurr);
		pWnd->SetCurrentIGenID(UNONE);
		//
		strCurr = "START";
		pWnd->SetstrOperID(strCurr);
		pWnd->SetCurrentOperID(UNONE);
		pWnd->SendMessage(ID_UPDATE_STATCNTLS);
		//
		m_PatProc = (PATCHPROC)PP_SPAWN; // something other than Procs Offered!
		GetPatSheet()->m_PatProc = m_PatProc;	// so it will be created
		GetPatSheet()->DestroyWindow();
	}
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
*/
}
	
void CPatMouse::ResetVariables_PAT()
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////
	m_bGenCur			= FALSE;
	/////////////////////////////////////// Set PatchID
	pObjectMgr->
		SetObjInfoID(m_CurrentPatchID,PATCH);
	////////////////////////////
	m_bAllSame			= TRUE;
	m_bEndCondMode		= FALSE;
	m_bEditMode			= FALSE;		// TRUE:User Checking/FALSE:DataInputting
	m_bU				= TRUE;				// TRUE:U_Dir/FALSE:V_Dir
	m_bCornerMode		= FALSE;			// needed for Twist
//	TWIST					m_TwistMethod[2][2];
	/////////////////////////////////////// Reset
	m_bCurveDone		= TRUE;	// 
	m_bPatchDone		= TRUE;	// 
	//////////////////////////////
	m_nNodeDone_U		= 0;	// Tensor Product
	m_nCurveDone_U		= 0;	// Gordon Surface
	////////////////////////////
//	((CBasePage*)(GetPatSheet()->GetActivePage()))			= NULL;                                                                                
 	/////////////////////////////////////////// Patch 
	m_nInfoDone			= 0;
	m_nCurveDone		= 0;
	m_nNodeDone			= 0;
    m_LastPatchNum		= 0;		// internal
//	m_PatProc			= PP_COONSQUAD;
	m_PatSubType		= PS_QUADRILAT;
	/////////////////////////////
//	m_PatProc			= PP_COONS;
	m_nTotElems			= 1;
	m_bAxis				= FALSE;
	m_nAxis				= 2;
	m_dAngSpec			= 90.;
	m_bNegative			= FALSE;
	m_SegAngle			= 120.;
	m_bAutoSeg			= TRUE;
	m_nExtruType		= 1;
	m_dLen				= 1.;
	m_FromID			= "";
	m_ToID				= "";
	//
	m_CurrentNodeID		= "";
	///
	m_nTwistType		= 1;
	m_nScaleType		= 1;
	m_bTwist			= TRUE;// Twist or Radius
	/////////
	m_pTwist			= NULL;
	m_nMaxTwist			= -1;
	m_bIncrement		= FALSE;
	m_TwistStart		= 0.0;
	m_TwistMult			= 0.0;
	/////////
	m_pScale			= NULL;
	m_nMaxScale			= -1;
	m_bIncScale			= FALSE;
	m_ScaleStart		= 0.0;
	m_ScaleMult			= 0.0;
	/////////////////////////////////////////////
	for(int i=0;i<2;i++)
		m_TwistMethod		= TW_ZERO;
	///
//	m_nNodes_U			= 0;
//	m_nNodes_V			= 0;
	m_Ratio_U			= 1.0;
	m_Ratio_V			= 1.0;
	m_ElPerSeg_V		= 1;
	//////////////////////////
	m_pBlendCurve	= NULL;
	m_pBlendCurve_U	= NULL;
	m_pBlendCurve_V	= NULL;
	m_pCurrentPatch = NULL;
	m_pCornerTwist	= NULL;
	//////////////////////////
	m_CurveList.RemoveAll();
	m_NodeList.RemoveAll();
	m_ElSegList.RemoveAll();
	m_LatchList.RemoveAll();
	/////////////////// Tensor/Gordon
	m_CurveList_U.RemoveAll();
	m_ElSegList_U.RemoveAll();
	m_LatchList_U.RemoveAll();
	m_EndList_U.RemoveAll();	// if(bClosed_U or Linear_U,Circle_U,
								// parabola_U) EndList_U Empty
	//
	m_CurveList_V.RemoveAll();
	m_ElSegList_V.RemoveAll();
	m_LatchList_V.RemoveAll();
	m_EndList_V.RemoveAll();	// if(bClosed_V or Linear_V,Circle_V,
								// parabola_V) EndList_V Empty
	/////////////////// reset
}

int CPatMouse::LeftDown_PATCH()
{
	return MA_OK;
}

int CPatMouse::ShowPatch(CString* pID)
{

	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	PATCHPROC		PatProcOld;
	//////////////////////////////////////////////////////////////////// Show NewPatch
	int nActiveIndex,nResult;
	///////////////////////////
	m_pCurrentPatch	= (CDrPatch*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,PATCH));
	m_pCurrentPatch->SetShow(FALSE);	// not quite ready
	//////////////////////////////////////////////////// Fill Mesh
	if(m_PatProc != PP_LOFT && m_PatProc != PP_TENSOR && m_PatProc != PP_GORDON) 
							// for lofting,Tensor & Gordon list is already filled
	{
		m_ElSegList.RemoveAll();
		m_ElSegList.AddTail(m_ElPerSeg);
		if(m_PatProc == PP_ROTATE)
			m_ElSegList.AddTail(m_nTotElems);	// it is Actually # of BezierSegments
	}
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	//////////////////////////////////////////////////////////////  Posting Dimension
	int nMeshElemDim;
	switch(pWnd->GetCurrentCntlID())
	{
		case EDIM_0: 
			nMeshElemDim = 0;	// Node(0D)
			break;
		case EDIM_1: 
			nMeshElemDim = 1;	// Grid(1D)
			break;
		default:
			nMeshElemDim = 2;	// plate, etc(2D)
	}
	m_pCurrentPatch->SetMeshElemDim(nMeshElemDim);					// 1D or 2D 
	////////////////////////////////////////////////////////////////////// Show
	switch(m_PatProc)
	{
		case PP_EXTRUDE:

			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpExtrudeInsert(
							m_bGenCur,
							m_nExtruType,
											// 1 = Given: Extrusion Direction Nodes
											// 2 = Given: 3 Lenths (wLen) to Extrude to
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_CurveList,	// given Curves always taken as U-dir
							&m_LatchList,
							m_ElSegList,
							m_wLen,
							m_dLen,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpRotateInsert(
							m_bGenCur,
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_CurveList,	// given Curves always taken as U-dir
							&m_LatchList,
							m_ElSegList,
							m_dAngSpec,
							m_Ratio,
							m_bAxis,
							m_nAxis,
							m_bNegative,
							m_pView
							) <0)
				nResult = -1;
			////
			break;

		case PP_LOFT:
			//////////////////////////////////////////////////// Show Patch
			////////////////////////////// OverRide PatProc for COONS Only
			PatProcOld = m_PatProc;
			/////////
/*
			if(m_nCurveDone == MIN_INFO_LOFT)
			{
				m_PatProc	= PP_LOFT2;
				//////////////////////////////////////////////////// Show Patch
				if(m_MI_Pat_I.RBUpLoft2Insert(
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_LatchList,
							&m_ElSegList,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			}
			else
			{
*/
				m_PatProc	= PP_LOFTX;
				//////////////////////////////////////////////////// Show Patch
				if(m_MI_Pat_I.RBUpLoftXInsert(
							m_bGenCur,
							m_pBlendCurve_U,
							m_bAdvanced,
							m_pCornerTwist,	// it is full,if TW_USER
							m_TwistMethod,
							////////////////
							1/*nCurDir*/,	// Curve Direction:1=U/2=V
							////////////////
							m_CurrentPatchID,		
							m_pCurrentPatch,
							//////////////////
							m_nNodes_U,
							m_nNodes_V,
							&m_NodeList,	// Tensor Product Nodes
							////////////////
							&m_CurveList_U,
							&m_LatchList_U,
							////////////////
//							m_ElSegList_V,
							m_ElSegList,
							m_pBlendCurve_V,
//							m_Ratio_V,
							m_Ratio,
							&m_EndList_V,	// if(bClosed_V or Linear_V,Circle_V,
											// parabola_V) EndList_V Empty
							////////////////
							m_pView
							) <0)
				nResult = -1;
/*
			}
*/
			////////////////////////////// Reset PatProc for COONS Only
			m_PatProc = PatProcOld;
			////
			break;


		case PP_TENSOR:
			//////////////////////////////////////////////////// Temporary
			Temp_FillOtherInfo_Tensor();
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpTensorInsert(
							m_bGenCur,
							m_bAdvanced,
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// Tensor Product Nodes
							////////////////
							m_pCornerTwist,	// it is full,if TW_USER
							m_TwistMethod,
							////////////////
							m_nNodes_U,
							m_ElSegList_U,
							m_Ratio_U,
							m_pBlendCurve_U,
							&m_EndList_U,	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
							////////////////
							m_nNodes_V,
							m_ElSegList_V,
							m_Ratio_V,
							m_pBlendCurve_V,
							&m_EndList_V,	// if(bClosed_V or Linear_V,Circle_V,
											// parabola_V) EndList_V Empty
							////////////////
							m_pView
							) <0)
				nResult = -1;
			////
			break;


		case PP_GORDON:
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpGordonInsert(
							m_bAdvanced,
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// Tensor Product Nodes
							////////////////
							m_pCornerTwist,	// it is full,if TW_USER
							m_TwistMethod,
							////////////////
							m_nNodes_U,
							&m_CurveList_U,	// must be supplied
							&m_LatchList_U, // must be supplied
							m_ElSegList_U,
							m_Ratio_U,
							m_pBlendCurve_U,
							&m_EndList_U,	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
							////////////////
							m_nNodes_V,
							&m_CurveList_V,	// must be supplied
							&m_LatchList_V,	// must be supplied
							m_ElSegList_V,
							m_Ratio_V,
							m_pBlendCurve_V,
							&m_EndList_V,	// if(bClosed_V or Linear_V,Circle_V,
											// parabola_V) EndList_V Empty
							////////////////
							m_pView
							) <0)
				nResult = -1;
			////
			break;


		case PP_DUCT:
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpDuctInsert(
							m_bGenCur,
							m_nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,
							&m_CurveList,
							&m_LatchList,
							&m_TwistList,	// Distrib,if nDuctType = 1
							m_TwistMult,
							m_bIncrement,
							m_TwistStart,
							m_pView
							) <0)
				nResult = -1;
			////
			break;

		case PP_SWEEP:
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpSweepInsert(
							m_bGenCur,
							m_nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
							m_nScaleType,
										// 1 = Given: Scale Distribution
										// 2 = Given: Scale Increments etc
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,
							&m_CurveList,
							&m_LatchList,
							&m_TwistList,	// Distrib,if nDuctType = 1
							m_TwistMult,
							m_bIncrement,
							m_TwistStart,
							&m_ScaleList,	// Distrib,if nDuctType = 1
							m_ScaleMult,
							m_bIncScale,
							m_ScaleStart,
							m_pView
							) <0)
				nResult = -1;
			////
			break;

		case PP_COONS:
			//////////////////////////////////////////////////// Show Patch
			////////////////////////////// OverRide PatProc for COONS Only
			PatProcOld = m_PatProc;
			/////////
			if(m_nCurveDone == 3)
//				m_PatProc	= PP_LOFT3;
				m_PatProc	= PP_COONSTRI;
			else
			if(m_nCurveDone == 4)
//				m_PatProc	= PP_LOFT4;
				m_PatProc	= PP_COONSQUAD;
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpCoonInsert(
							m_bGenCur,
							m_PatProc, 
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_LatchList,
							m_pView
							) <0)
				nResult = -1;
			////////////////////////////// Reset PatProc for COONS Only
			m_PatProc = PatProcOld;
			////
			break;

		default:
			break;
	}
	if(nResult<0)
		return MA_ERROR;
	/////////////////////////////////////////////////////////// Update Patch Topology
	nResult = PatTopo_Update(m_pCurrentPatch,&m_CurveList,&m_NodeList);
	if(nResult<0)
		return MA_ERROR;
	/////////////////////////////////////
	return MA_OK;
	////
}

void CPatMouse::Temp_FillOtherInfo_Tensor()
{
	/////////////////
	m_Ratio_U	= 1.;
	m_Ratio_V	= 1.;
	////////////////////////////////////////////////////
	int nCount_U,nCount_V;
	//////////////////////////////////
	nCount_U = m_ElSegList_U.GetCount(); //is it picking up anything
	if(m_pBlendCurve_U->IsClosed_S())	
		m_ElSegList_U.AddTail(m_nLastElems_U);
	//////////////////////////////////
	nCount_V = m_ElSegList_V.GetCount(); //is it picking up anything
	if(m_pBlendCurve_V->IsClosed_S())	
		m_ElSegList_U.AddTail(m_nLastElems_V);
	////////////////
}

int CPatMouse::PatTopo_Update(CDrPatch* pCurrentPatch,CDListMgr* pCurrentCurList,
										CDListMgr* pCurrentNodList/*m_NodeList*/)
{
	////////////////
	int nResult = 0;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////// Bndry Curve of Current Patch 
	int i,nCount;
	///////////////////
	nCount = pCurrentCurList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrCurve* pCurve	= (CDrCurve*)(pCurrentCurList->GetObject(i));
		////////////////
		if(!pCurve)
		{
			AfxMessageBox(
				"Internal ERROR:\nCPatMouse::PatTopo_Update\n!pCurve");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pPatList = pCurve->GetPatchList();
		///
		nResult = PatTopo_ConnectObjects(pCurrentPatch,pPatList);
		if(nResult<0)
			return nResult;
		///
	}
	/////////////////////////////////////////////////////////// Node_dependent Connection
	nCount = pCurrentNodList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrNode* pNode	= (CDrNode*)(pCurrentNodList->GetObject(i));
		////////////////
		if(!pNode)
		{
			AfxMessageBox(
				"Internal ERROR:\nCPatMouse::PatTopo_Update\n!pNode");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pPatList = pNode->GetPatchList();
		///
		nResult = PatTopo_ConnectObjects(pCurrentPatch,pPatList);
		if(nResult<0)
			return nResult;
		///
	}
	//////////////
	return nResult;
}

int CPatMouse::PatTopo_ConnectObjects(CDrPatch* pCurrentObject,CDListMgr* pList)
{
	int nResult = 0;
	////////////////
	CDListMgr*	pObjObjList;
	int j,nCount,index;
	///////////////////
	nCount = pList->GetCount();
	///
	for(j=0;j<nCount;j++)	
	{
		CDrPatch* pObject	= (CDrPatch*)(pList->GetObject(j));
		////////////////
		if(!pObject)
		{
			AfxMessageBox(
				"Internal ERROR:\nCPatMouse::PatTopo_ConnectObjects\n!pObject");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		if(pObject != pCurrentObject)	// EXIST in other Patch
		{
			pObjObjList = pCurrentObject->GetPatchList();
			///
			index = pObjObjList->GetObjectIndex(pObject);
			if(index<0)		// not in the list yet
			pObjObjList->InsertObject(pObject);
			////////////////////////////////////// Reciprocate Patch, if necessary
			pObjObjList = pObject->GetPatchList();
			index = pObjObjList->GetObjectIndex(pCurrentObject);
			if(index<0)		// not in the list yet
				pObjObjList->InsertObject(pCurrentObject);
		}
	}
	///////////////
	return nResult;
}			

int CPatMouse:: ElementLeftDown_PAT()
{	
	int nResult;
	////////////////
	CMPatMgr MPatMgr;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType;
	////////////////////////
	m_bPatchDone	= FALSE;
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// PATCH
		case P_COONS:

			m_PatProc = PP_COONS;
			break;

		case P_EXTRUDE:				// 

			m_PatProc = PP_EXTRUDE;
			break;

		case P_ROTATE: 

			m_PatProc = PP_ROTATE;
			break;

		case P_LOFT: 

			m_bU		= FALSE;
			m_PatProc	= PP_LOFT;
			break;

		case P_TENSOR: 

			m_PatProc = PP_TENSOR;
			break;

		case P_GORDON: 

			m_PatProc = PP_GORDON;
			break;

		case P_DUCT: 

			m_PatProc = PP_DUCT;
			m_bTwist  = TRUE;
			break;

		case P_SWEEP: 

			m_PatProc = PP_SWEEP;
			m_bTwist  = TRUE;
			if(m_nInfoDone == 3)
				m_bTwist  = FALSE;
			break;
		//////////////////////////////////////////////////
		default:
			break;
	}  
	///////////////////////////
	nResult = LeftDown_PATCH();
	return nResult;
}

void CPatMouse::OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	////////////////////////////////////
	if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
	{
		pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
		/////////////////////
		ResetVariables_PAT();
		m_bPatchDone		= FALSE;	  // 
	}
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////// 
   	m_bDragOn 		= pBool->IsDragOn();
	m_bDialogOn		= pBool->IsDialogOn();
	m_bAutoAcceptOn	= pBool->IsAutoAcceptOn();
	m_bSingleSegOn	= pBool->IsSingleSegOn();
	m_bBLineOn		= pBool->IsBLineOn();
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	///////////////////////////////////////// make sure Dlg is Open
	if( !(((CBasePage*)(GetPatSheet()->GetActivePage()))->m_hWnd) )
		pWnd->SendMessage(ID_ACTIVE_PATIN,IDOK);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
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

int CPatMouse::UpdatePDlg_TRUE()
{
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_bGenCur           = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve;
//	m_PatProc			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc;
	m_CurrentPatchID	= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID;
	m_CurrentCurveID	= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID;
	m_CurrentNodeID		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_NID;
	m_ThirdCoord		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dCoord;
	m_ElPerSeg			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh;
	m_Ratio				= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio;
	m_ElPerSeg_V		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh_V;
	m_Ratio_V			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio_V;
	m_Orient			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Orient;
	m_bClosed			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bClosed;
	///
	m_dLen				= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dLen;
	m_nExtruType		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nExtruType;
	m_wLen				= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_wLen;
	///////////////////////////////////////////////////////////////////////////////////
	////
	m_nTotElems			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nTotElems;
	m_bAxis				= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAxis;
	m_nAxis				= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nAxis;
	m_dAngSpec			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dAngSpec;
	m_bNegative			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bNegative;
	m_SegAngle			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle;
	m_bAutoSeg			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg;
	///////////////////////////////////////////////////// List Inclusion, If Any
	switch(m_PatProc)
	{
		case PP_EXTRUDE:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
			}
			break;

		case PP_ROTATE:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
			}
			break;

		case PP_LOFT:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				default:
					break;
			}
			break;

		case PP_TENSOR:
			switch(m_nInfoDone)
			{
				case 0:
				default:
					break;
			}
			break;

		case PP_GORDON:
			switch(m_nInfoDone)
			{
				case 0:
				default:
					break;
			}
			break;

		case PP_COONS:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					break;
			}
			break;

		case PP_DUCT:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
			}
			break;
		case PP_SWEEP:
			switch(m_nInfoDone)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	/////////////
	return MA_OK;
}			

int CPatMouse::UpdatePDlg_FALSE()
{
	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	if(m_bCNode)
		pObjectMgr->SetNodeInfoID(m_CurrentNodeID,m_bCNode,pWnd->IsMeshMode());		
	//////////////////////////////////////
	if(!m_bEndCondMode && !m_bCornerMode)
	{
		if(m_nInfoDone>=1)
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
				GetDlgItem(IDC_PID)->EnableWindow(TRUE);
		//////////////////////////////
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= m_CurrentCurveID;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_NID		= m_CurrentNodeID;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dCoord	= m_ThirdCoord;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh_V	= m_ElPerSeg_V;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio_V	= m_Ratio_V;
//		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Orient		= m_Orient;
		/////
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
		if(m_bTwist)
		{
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
		}
		else
		{
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement	= m_bIncScale;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart	= m_ScaleStart;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult		= m_ScaleMult;
		}
		/////
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAxis		= m_bAxis;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nAxis		= m_nAxis;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bNegative	= m_bNegative;
	}
	///////////////////////////////
	switch(m_PatProc)
	{
		case PP_EXTRUDE:

			nResult = UpdatePDlg_FALSE_EXTRUDE();
			break;

		case PP_ROTATE:

			nResult = UpdatePDlg_FALSE_ROTATE();
			break;

		case PP_LOFT:

			nResult = UpdatePDlg_FALSE_LOFT();
			break;

		case PP_TENSOR:

			nResult = UpdatePDlg_FALSE_TENSOR();
			break;

		case PP_GORDON:

			nResult = UpdatePDlg_FALSE_GORDON();
			break;

		case PP_COONS:

			nResult = UpdatePDlg_FALSE_COONS();
			break;

		case PP_DUCT:

			nResult = UpdatePDlg_FALSE_DUCT();
			break;

		case PP_SWEEP:

			nResult = UpdatePDlg_FALSE_SWEEP();
			break;

		default:
			return MA_CANCEL;
	}
	if(nResult == MA_ERROR || nResult == MA_CANCEL)
		return nResult;
	////////////////////////////////////////////////
	if(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetSafeHwnd())
		((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
	return MA_OK;
}

int CPatMouse::UpdateTwistDlg_TRUE()
{
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(TRUE); // From screen
	////////////////////////////////////////////////
	m_bAllSame = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAllSame;
	///
	if(m_bAllSame)	// Tangent Done
	{
		m_TwistMethod = ((CBasePage*)(GetPatSheet()->GetActivePage()))->
							m_TwistMethod[0][0];
		//////////////////
		m_bCornerMode = FALSE;
	}
	/////////////
	return MA_OK;
}

int CPatMouse::UpdateEndDlg_TRUE()
{
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(TRUE); // From screen
	////////////////////////////////////////////////
	m_bAllSame = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAllSame;
	/////////////
	return MA_OK;
}

int CPatMouse::UpdateEndDlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->m_indexNode_I	= m_indexNode_I;
	((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bU			= m_bU;
	/////////////////////////////////////////////////////
	if(m_bU)
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nOrder		= m_nBlendOrder_U;
	else
		((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nOrder		= m_nBlendOrder_V;
	///////////////////////////////
	switch(m_PatProc)
	{
		case PP_LOFT:

//			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Loft Patch: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Loft Patch: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Loft Patch: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
							GetPatSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetPatSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetPatSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Loft Patch: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;

		case PP_TENSOR:

//			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Tensor Product Patch: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Tensor Product Patch: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Tensor Product Patch: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
							GetPatSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetPatSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetPatSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Tensor Product Patch: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;


		case PP_GORDON:

			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Gordon Patch: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Gordon Patch: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Gordon Patch: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
							GetPatSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetPatSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetPatSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Gordon Patch: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;


		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	/////////////
	return MA_OK;
}

int CPatMouse::UpdateTwistDlg_FALSE()
{
	CDrGrafFrame*	pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	CString*		pstrNode;
	char*			buf;		
	///////////////////////////////////////////////////////////////////////
	int i,j;
	////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->m_indexNode_I	= m_indexNode_I;
	///////////////////////////////
	switch(m_PatProc)
	{
		case PP_LOFT:
		case PP_TENSOR:
		case PP_GORDON:

			///////////////////
			switch(m_nTwistDone)
			{
				case 0:	// fall thro'
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pCornerTwist	= m_pCornerTwist;
					///
					for(i=0;i<2;i++)
						for(j=0;j<2;j++)
							((CBasePage*)(GetPatSheet()->GetActivePage()))->
									m_TwistMethod[i][j]	= m_TwistMethod;
				default:

					if(m_nTwistDone<4)
					{	
						((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nCornerI		= m_nCornerI;
						((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nCornerJ		= m_nCornerJ;
						/////
						((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlgForTwist();
						/////
						pstrNode	= new CString;
						buf			= pstrNode->GetBuffer(BUFF_SIZE);
						sprintf(buf,"Corner# %d of 4",m_nTwistDone+1);
						//////////////////
						if(m_PatProc == PP_LOFT)
							strCurr = "Loft Patch: Provide Twists at the ";
						else
						if(m_PatProc == PP_TENSOR)
							strCurr = "Tensor Product: Provide Twists at the ";
						else
						if(m_PatProc == PP_GORDON)
							strCurr = "Gordon Patch: Provide Twists at the ";
						strCurr += buf;
						strCurr +="@Done with it? Please Click On Update Button";
						delete pstrNode;
					}
					else
					{
						// Later we will Activate EditMode here by opening both Tensor
						// and EndCondPage
						m_bCornerMode	= FALSE;
						((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bCornerMode = m_bCornerMode;
						/////
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
							GetPatSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetPatSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetPatSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCPatMouse::UpdateTwistDlg_FALSE()\n!GetPatSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						if(m_PatProc == PP_LOFT)
							strCurr = "Loft Patch: ";
						else
						if(m_PatProc == PP_TENSOR)
							strCurr = "Tensor Product Patch: ";
						else
						if(m_PatProc == PP_GORDON)
							strCurr = "Gordon Patch: ";
						strCurr +="@Ready with other Info.? Click Right Button";
						/////////////////////////////////////////////// CurrStat: Show
						pWnd->SetstrCurrID(strCurr);
						pWnd->UpdateCurrStat(strCurr);
						//////////
						return MA_OK;
					}
					break;
			}
			break;


		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	/////////////
	return MA_OK;
}
	
int CPatMouse::LeftUp_Pat_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
{
	///////////////////////////////////////////////////////////////////////
	//	bDistinct		=		TRUE	-> Should Not be in m_NODELIST
	//							FALSE	-> DONT CARE
	//	bNoOtherType	=		TRUE	-> Should Not be other than Type dictated by bCNode
	//							FALSE	-> DONT CARE
	///////////////////////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////// See if any Existing Node Hit w/ same Coords
	m_bCorINodeOpDone = FALSE;
	BOOL bControl	  = FALSE;
	if(bCNode)
		bControl = TRUE;
	////////////////////
SEARCH:
	nResult = LeftUp_Node_Accept_OtherContext(point,bControl,pWnd->IsMeshMode(),
						m_bCorINodeOpDone,m_bAutoAcceptOn,&m_pCurrentNode);
	/////////////////////////////////////////////   
	//	MA_CREATENEW	// Create Anyway
	//	MA_ACCEPTOLD	// Accept Old	
	//	MA_ACCEPTNEW	// Accept New	
	//	MA_NOHIT		// No Hit	
	//	MA_CANCEL		// Cancel Process
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
			nResult = OldNode_N_Update_PATContext(m_pCurrentNode->IsControlNode(),bDistinct); // right type
				return nResult;

		case MA_NOHIT:			// NoHit
			if(!bNoOtherType)
			{
				if(!m_bCorINodeOpDone)	// Not Final
				{
					m_bCorINodeOpDone = TRUE;	// try Final
					bControl = TRUE;
					if(bCNode)
						bControl = FALSE;	// other type
					goto SEARCH;
				}
			}
			else
				; // fall thro for NEW NODE

		case MA_CREATENEW:			// Hit or Not , Create NEW anyway (m_wLoc Set)
			nResult = NewNode_N_Update_OtherContext(point,bCNode); // desired Type
			/////////////////////////
			return nResult;
			/////////
		case MA_CANCEL:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}					
}

int CPatMouse::OldNode_N_Update_PATContext(BOOL bCNode,BOOL bDistinct)
{
	///
	if(bDistinct)
	{
		/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
		if(m_nNodeDone>1)
		{
			////////////////////////////////////////////////// already exists
			if(m_NodeList.GetObjectIndex(m_pCurrentNode) >=0)
			{
				m_pCurrentNode = NULL;
				if(m_nActiveTool == P_EXTRUDE)
					AfxMessageBox("ERROR:\nDegenerate Extrusion Direction:\nSame Node More than Once!");
				if(m_nActiveTool == P_ROTATE)
					AfxMessageBox("ERROR:\nDegenerate Rotation Axis:\nSame Node More than Once!");
				return MA_CANCEL;
			}
		}
	}
	/////////////////////
	m_NodeList.InsertObject(m_pCurrentNode);
	/////////////////////////
	UpdateforOldNode(bCNode);
	/////////////
	return MA_OK;
}

int CPatMouse::LeftUp_EXTRUDE_PAT(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////
	switch(m_nInfoDone)
	{
		case 1:	m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				///////
				return 0;
		case 2:	// fall thro'
		case 3:	m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;
		default:break;
	}
	return -1;
}

int CPatMouse::LeftUp_ROTATE_PAT(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////
	switch(m_nInfoDone)
	{
		case 1:	m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				///////
				return 0;
		case 2:	// fall thro'
		case 3:	m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;
		default:break;
	}
	return -1;
}

int CPatMouse::LeftUp_LOFT_PAT(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				else
				{
					CLoft_Compat LC;
					////////////////////////////////////////////////////////// Check Compatibility
					BOOL bResult;
					if(m_CurveList.GetCount()<=1)
						bResult = TRUE;
					else
						bResult = LC.AreCurvesCompatible(&m_CurveList,&m_LatchList);
					////////////
					if(!bResult)
					{
						////////////////////////////////
						int j;
						CString* pstrNode;
						pstrNode	= new CString;
						LPTSTR buf	= pstrNode->GetBuffer(BUFF_SIZE);
						j = sprintf(buf,   "			*** DATA ERROR ***          \n");
						j += sprintf(buf+j,"Last Curve is Not Compatible with Others\n");
						j += sprintf(buf+j,"Incompatibility could be due to:\n");
						j += sprintf(buf+j,"\tNot All Closed or Open\n");
						j += sprintf(buf+j,"\tNot All having same Number of Bezier Segments\n");
						j += sprintf(buf+j,"\tLatch Option for the Curve may be wrong\n");
						j += sprintf(buf+j,"\tNot All having same Number of Elements per Segment\n");
						//////
						AfxMessageBox(*pstrNode);
						//////////////////
						delete pstrNode;
						///////////////////////// do not accept
						m_nCurveDone--;
						m_CurveList.RemoveTail();
						m_LatchList.RemoveTail();
						////////////////
						return MA_NOHIT;
					}
					//////////////////////////////////////// Update ElSeglist for Tensor Product
					if(m_nCurveDone>1)	// start saving from 2nd Curve of each row
						m_ElSegList_V.AddTail(m_ElPerSeg);
					/////////
					return 0;
				}
	}
	return MA_NOHIT;
}

int CPatMouse::LeftUp_TENSOR_PAT(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,FALSE,TRUE,TRUE);
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nNodeDone--;
					return nResult;
				}
				else
				{
					//////////////////////////////////////// Update ElSeglist for Tensor Product
					if((m_nNodeDone>1) && (m_nNodeDone <= m_nNodes_U))	// start saving from 2nd Node of each row
						m_ElSegList_U.AddTail(m_ElPerSeg);
					else
					if((m_nNodeDone % m_nNodes_U) == 1)	// start saving from 2nd Node of each row
					{
						if(m_nNodeDone>1)
							m_ElSegList_V.AddTail(m_ElPerSeg_V);
					}
					/////////
					return 0;
				}
	}
	return MA_NOHIT;
}

int CPatMouse::LeftUp_GORDON_PAT(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				else
				{
					CLoft_Compat LC;
					////////////////////////////////////////////////////////// Check Compatibility
					BOOL bResult;
					if(m_CurveList.GetCount()<=1)
						bResult = TRUE;
					else
						bResult = LC.AreCurvesCompatible(&m_CurveList,&m_LatchList);
					////////////
					if(!bResult)
					{
						////////////////////////////////
						int j;
						CString* pstrNode;
						pstrNode	= new CString;
						LPTSTR buf	= pstrNode->GetBuffer(BUFF_SIZE);
						j = sprintf(buf,   "			*** DATA ERROR ***          \n");
						j += sprintf(buf+j,"Last Curve is Not Compatible with Others\n");
						j += sprintf(buf+j,"Incompatibility could be due to:\n");
						j += sprintf(buf+j,"\tNot All Closed or Open\n");
						j += sprintf(buf+j,"\tNot All having same Number of Bezier Segments\n");
						j += sprintf(buf+j,"\tLatch Option for the Curve may be wrong\n");
						j += sprintf(buf+j,"\tNot All having same Number of Elements per Segment\n");
						//////
						AfxMessageBox(*pstrNode);
						//////////////////
						delete pstrNode;
						///////////////////////// do not accept
						m_nCurveDone--;
						m_CurveList.RemoveTail();
						m_LatchList.RemoveTail();
						////////////////
						return MA_NOHIT;
					}
					//////////////////////////////////////// Copy ElSeglist
					if(m_nInfoDone == 1)	//
					{
						CDrCurve* pCurve = (CDrCurve*)(m_CurveList.GetHead());
						m_ElSegList_U.AddTail(pCurve->GetElperSegList_S());
					}
					else
					if(m_nInfoDone == (m_nCurves_U + 1))	//
					{
						CDrCurve* pCurve = (CDrCurve*)m_CurveList.GetHead();
						m_ElSegList_V.AddTail(pCurve->GetElperSegList_S());
					}
					/////////
					return 0;
				}
	}
	return -1;
}

int CPatMouse::LeftUp_DUCT_PAT(POINT point)
{
	int nResult =0;
	///////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'	// XSection Curve
		case 2:	m_nCurveDone++;	// Spine Curve
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				if(m_nInfoDone>2)
				{
					pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				}
				///////
				return 0;
		case 3:	m_nNodeDone++;	// Anchor Node
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;
		default:break;
	}
	return -1;
}

int CPatMouse::LeftUp_SWEEP_PAT(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'	// XSection Curve
		case 2:	m_nCurveDone++;	// Spine Curve
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				if(m_nInfoDone>2)
				{
					pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				}
				///////
				return 0;
		case 3:	m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;
		default:break;
	}
	return -1;
}

int CPatMouse::LeftUp_COONS_PAT(POINT point)
{
	int nResult = 0;
	////////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		case 2:	// fall thro'
		case 3:	// fall thro'
		case 4:	m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nCurveDone--;
					return nResult;
				}
				return 0;
		default:break;
	}
	return -1;
}

int CPatMouse::LeftUp_Curve_Accept_OtherContext(CPoint point)
{
	int nResult = -2;
	//	nResult = -2	// Cancel	
	/////////////////////////////////
	// multiple search fr same coord
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	////////////////////////////////////////////////////////////////// Blank NodeID
	CDListMgr* pDListMgr;
	///
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pDrCurve;
	int			index;
	///////////////////////////////////////////// See if any Existing Curve Hit
	index = IsObjectHit(CURVE,point,0);
	/////////////////////////////////////////////////////////////// 
	if(index<0)						
		//////////////// Not Hit
		return MA_NOHIT;
	////////////////////////////////
	pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	/////////////////////////
	for(;;)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		/////////////
		int j;
		//////////////////////////////
		j = sprintf(buf,"***** A Curve Hit ****\n");
		j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
		j = ShowCurveInfo(pDrCurve, buf, j);
		////////////////////////////
		j += sprintf(buf+j,
			"\n\nYES:\t\tAccept This Existing Curve");
		j += sprintf(buf+j,
			"\nNO:\t\tFind Next Matching Curve");
		j += sprintf(buf+j,
			"\nCANCEL:\t\tCancel Selection Process");
		////////////////////////////
		if(!m_bAutoAcceptOn)
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
		else
			nResult = IDYES;
//		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
		/////////////
		delete str;
		if(nResult == IDYES)
		{
			///////////////// Accept Old
			m_pCurrentCurve = pDrCurve;
			return MA_ACCEPTOLD;
		}
		else
		if(nResult == IDNO)
		{
			//////////////////////////////////////////////////////// Retry
			index = IsObjectHit(CURVE,point,startIndex);
			/////////////////////////////////////////////////////////////// Right Type
			if(index>=0)
			{
				pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
				ID			= pDrCurve->GetObjectID();
				////////////////////////////////////////
				startIndex  = index+1;
				/////////////////////
			}
			else
			{
				CString* str = new CString;
				char* buf = str->GetBuffer(BUFF_SIZE);
				/////////////
				int j;
				//////////////////////////////
				j = sprintf(buf,"***** No More Curve Found ****\n");
				j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
				/////////////
				delete str;
				nResult = IDNO;
				//////////////// Cancel
				return MA_CANCEL;
			}
		}
	}	// end for Loop			
	//////////////// MA_NOHIT
	return MA_NOHIT;
}

int CPatMouse::ShowCurveInfo(CDrCurve* pDrCurve, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	//////////////////////////////
	int j = jStart;
	/////////////////////////////// total elems
	ID						= pDrCurve->GetObjectID();
	int nIn					= pDrCurve->GetMaxINodes_S();
	int nElems				= pDrCurve->GetMaxOutPts_S();
	CDListMgr* pList		= pDrCurve->GetINodeList();
	//////////////////////////////
	j += sprintf(buf+j,
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
	sprintf( buf + j-2, "; ");
	/////////
	return j;
}

int CPatMouse::LeftUp_Pat_Curve(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	///////////////////////////////////////////// See if any Existing Curve Hit
	nResult = LeftUp_Curve_Accept_OtherContext(point);
	/////////////////////////////////////////////   
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentCurve->GetObjectID();
			///////////////////////////////////////// matches previous Curve in m_CurveList,INADMISSIBLE
			if(m_nCurveDone>1)
			{
				/////////////////////////////////////////// already exists
   				if((m_CurveList.GetObjectIndex(CURVE,ID) ) >=0)
				{
					BOOL bError = FALSE;
					////////////////////
/*011899
					if(m_nCurveDone>2)
					{	
						if((m_PatProc == PP_COONS) ||(m_PatProc == PP_LOFT) )
							bError = TRUE;
					}
					else
					if(m_nCurveDone>1)
					{
*/					
						if(
							(m_PatProc == PP_COONS) ||(m_PatProc == PP_LOFT) ||
							(m_PatProc == PP_DUCT) ||(m_PatProc == PP_SWEEP) ||
							(m_PatProc == PP_GORDON)
							)
							bError = TRUE;
//					}
					//////////////////
					if(bError)
					{
						AfxMessageBox("Degenerate Patch:\nSame Curve More than Once!");
						return MA_NOHIT;
					}
				}
				/////////////////////////////////////////// Update ElpersegList
				if(m_PatProc == PP_LOFT || m_PatProc == PP_GORDON) // for lofting & Gordon 
					m_ElSegList.AddTail(m_ElPerSeg);
				///////////////////////////////////////////
			}
			/////////////////////////////////////////////
			break;
		case MA_NOHIT:			// Hit Not 
			return MA_NOHIT;
		case MA_CANCEL:		// Cancel
			return MA_CANCEL;
		default:		// Error
			return MA_ERROR;
	}
	///////////////////////////////////////////////// Check COONS Compatibility
	CURVELATCH	NewLat = CL_FORWARD;
	if(m_Orient == "BACKWARD")
		NewLat = CL_BACKWARD;
	//////////////////////////
	if(	m_nCurveDone > 1 && m_PatProc == PP_COONS)	// NOT IST curve
	{
		nResult = CheckCompatibility_COONS_Curve(m_pCurrentCurve,NewLat);
		///
		if(nResult<0)
			return nResult;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurPatCurve					= m_pCurrentCurve;
	m_pOldPatCurve					= m_pCurPatCurve;
	m_CurveList.InsertObject(m_pCurPatCurve);
	///
	m_Orient	= "FORWARD";
	if(NewLat == CL_BACKWARD)
		m_Orient = "BACKWARD";
	m_LatchList.AddTail(NewLat);
	/////////
	return MA_OK;
}

int CPatMouse::CheckCompatibility_COONS_Curve(CDrCurve* pDrCurve,CURVELATCH& NewLat)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////// Compatibility Check for Coons
	BOOL bClosed;
	////////////////////////////////////// All must be OPEN
	bClosed		= pDrCurve->IsClosed_S();
	if(bClosed)
	{
		CString ID = pDrCurve->GetObjectID();
		///
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		/////////////
		int j;
		//////////////////////////////
		j = sprintf(buf,"%s Curve MUST BE OPEN",ID);
		AfxMessageBox(*str,MB_ICONQUESTION);
		delete str;
		/////////// 
		return MA_CANCEL;
	}
	///////////////////////////////////////////////////// find Latch
	///////////////////////////////////////////////////// Check CONNECTIVITY
	C3DMath Math3D;
	///////////////
	POSITION	pos;
	CDListMgr*	pCNList;
	WORLD		LocalPosOld,LocalPosB,LocalPosE,LocalPos;
	CDrNode*	pNode_Old;
	CDrNode*	pNode_Beg;
	CDrNode*	pNode_End;
	CURVELATCH	OldLat;
	int			nInputType;
	BOOL		bArc;
	//////////////////////////////////////////////////////// Curve Old
	nInputType	= m_pOldPatCurve->GetInputType();
	bArc		= m_pOldPatCurve->IsArcType();
	//
	pos			= m_LatchList.FindIndex(m_nCurveDone-2);
	OldLat		= m_LatchList.GetAt(pos);
 	pCNList		= m_pOldPatCurve->GetCNodeList();
	pNode_Old	= (CDrNode*)pCNList->GetTail();
	if(OldLat == CL_BACKWARD) 
		pNode_Old	= (CDrNode*)pCNList->GetHead();
/*
	/////////////////////////////////////////////////////////// INODE HANDLE
	// Last One ADDITIONAL COPY HANDLE Node 
	// for m_nInputType = CIRCLE_BY_ROT
	// for m_nInputType = CIRCLE_BY_NO3 with !m_bArc
	////////////////////////////////////////////////////
	else
	if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
	{
 		pINList		= m_pOldPatCurve->GetElemList(); // Auxiliary at End
		pNode_Old	= (CDrNode*)pINList->GetHead();
	}
*/
	/////////////
//	OldLat		= m_PatCurveLatch[m_nCurveDone-2];
	////////////////////////////
	LocalPosOld = *(pNode_Old->GetLocalPos());
	//////////////////////////////////////////////////////// Curve New
	pCNList		= pDrCurve->GetCNodeList();
	pNode_Beg	= (CDrNode*)pCNList->GetHead();
	LocalPosB	= *(pNode_Beg->GetLocalPos());
	///////////////////////////////////////////
/*
	nInputType	= pDrCurve->GetInputType();
	bArc		= pDrCurve->IsArcType();
	//
	if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
	{
 		pINList		= pDrCurve->GetElemList(); // Auxiliary at End
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	else
*/
		pNode_End	= (CDrNode*)pCNList->GetTail();
	//
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
		///////
		return MA_CANCEL;
	}
	/////////////////////////////////////////// End Coons Compatibility
	return MA_OK;
}

int CPatMouse::ElementLeftUp_PAT(CPoint point)
{                          
	int nResult;
	////////////
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
		
		///////////////////////////////////////////////////// Patches Insert
		case P_EXTRUDE:

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_EXTRUDE)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_EXTRUDE_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;

		case P_ROTATE: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_ROTATE)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdatePDlg_TRUE();
			////////
			if((m_nInfoDone == 3) && m_bAxis)
			{
				m_nInfoDone++;
				m_nNodeDone++;
			}
			else
			{
				//////////////////
				nResult = LeftUp_ROTATE_PAT(point);
				//
				if(nResult<0 || nResult == MA_NOHIT )
				{
					m_nInfoDone--;
					return MA_OK;
				}
			}	
			nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;

		case P_LOFT: 

			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > m_nCurves_U)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_LOFT_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdatePDlg_FALSE();
			///////////////////////////////////////
			if(m_nInfoDone == m_nCurves_U )	// CurveInfoDone,
														// Get ready for EndCond
														// If m_nOrder_U or m_nOrder_V
														// appropriate
			{
				m_bAdvanced = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
				//////////////////////////////////////////////////////////////////// Tensor Product Compatible
				m_LatchList_U.AddTail(&m_LatchList);
				m_LatchList.RemoveAll();
				m_CurveList_U.AddTail(&m_CurveList);
				m_CurveList.RemoveAll();
				////////////////////
				nResult =
				CreateDataNodeList(&m_NodeList,&m_CurveList_U,&m_LatchList_U,m_nNodes_U,m_nNodes_V);
				///////////////////
				if(nResult == MA_ERROR)
					return MA_ERROR;
				//////////////////////////////////////////////////
				nResult = IsEndCondNeeded_LOFT(m_bEndCondMode,
					m_nEndTanNeeded_U,m_nEndTanNeeded_V);	// get BlendingInfo & 
															// Decide for EndCond
				if(m_bEndCondMode)
				{
					/////////////////////
					m_nEndCondDone = 0;
					TENSOREndDlgUpdate_PAT();
					///////////////////////////////// Create To Activate Dlg Only
					SwitchToEndCondDlg();
					GetPatSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					nResult = UpdateEndDlg_FALSE();

				}
				else
					///
					nResult = UpdatePDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;


		case P_TENSOR: 

			/////////////////
			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > (m_nNodes_U*m_nNodes_V))
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdatePDlg_TRUE();
			if(LeftUp_TENSOR_PAT(point)<0)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			///////////////////////////////////////
			if(m_nInfoDone == (m_nNodes_U*m_nNodes_V) )	// NodeInfoDone,
														// Get ready for EndCond
														// If m_nOrder_U or m_nOrder_V
														// appropriate
			{
				m_bAdvanced = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
				//////////////////////////////////////////////////
				nResult = IsEndCondNeeded_TENSOR(m_bEndCondMode,
					m_nEndTanNeeded_U,m_nEndTanNeeded_V);	// get BlendingInfo & 
															// Decide for EndCond
				if(m_bEndCondMode)
				{
					/////////////////////
					m_nEndCondDone = 0;
					TENSOREndDlgUpdate_PAT();
					///////////////////////////////// Create To Activate Dlg Only
					SwitchToEndCondDlg();
					GetPatSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					nResult = UpdateEndDlg_FALSE();

				}
				else
					///
					nResult = UpdatePDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;


		case P_GORDON: 

			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > (m_nCurves_U+m_nCurves_V))
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_GORDON_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}
			nResult = UpdatePDlg_FALSE();
			///////////////////////////////////////
			if(m_nInfoDone == m_nCurves_U )	// U_CurveInfoDone,
			{
				//////////////////////////////////////////////////////////////////// Tensor Product Compatible
				m_LatchList_U.AddTail(&m_LatchList);
				m_LatchList.RemoveAll();
				m_CurveList_U.AddTail(&m_CurveList);
				m_CurveList.RemoveAll();
				////////////////////
				m_nCurveDone_U	= m_nCurveDone;
				m_nCurveDone	= 0;
			}
			else
			if(m_nInfoDone == m_nCurves_U+m_nCurves_V )	// ALL_CurveInfoDone,
			{
				m_bAdvanced = ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
				//////////////////////////////////////////////////////////////////// Tensor Product Compatible
				m_LatchList_V.AddTail(&m_LatchList);
				m_LatchList.RemoveAll();
				m_CurveList_V.AddTail(&m_CurveList);
				m_CurveList.RemoveAll();
				/////////////////////////////////////////////////////////////////
				nResult = CheckCompatibility_GORDON_Curve(
								&m_CurveList_U,&m_LatchList_U,&m_CurveList_V,&m_LatchList_V);
				///
				if(nResult == MA_ERROR)
					return MA_ERROR;
				////////////////////
				m_nNodes_U = m_nCurves_V; 
				m_nNodes_V = m_nCurves_U; 
				//////
				nResult =
				CreateDataNodeList(&m_NodeList,&m_CurveList_U,&m_LatchList_U,m_nNodes_U,m_nNodes_V);
				///////////////////
				if(nResult == MA_ERROR)
					return MA_ERROR;
				//////////////////////////////////////////////////
				nResult = IsEndCondNeeded_GORDON(m_bEndCondMode,
					&m_CurveList_U,&m_CurveList_V);			// get BlendingInfo & 
															// Decide for EndCond
				if(m_bEndCondMode)	// Only Twist; tangents come from Curve ends
				{
					/////////////////////
					m_nEndCondDone = 0;
					GORDONEndDlgUpdate_PAT();
/*
					///////////////////////////////// Create To Activate Dlg Only
					SwitchToEndCondDlg();
					GetPatSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					UpdateEndDlg_FALSE();
*/

				}
				else
					///
					nResult = UpdatePDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;



		case P_DUCT: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_DUCT)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_DUCT_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;

		case P_SWEEP:

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_SWEEP)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_SWEEP_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			//////
			if(m_nInfoDone == MAX_INFO_SWEEP-2)	// Get Ready for Radial Curve
				m_bTwist = FALSE;
			//////
			nResult = UpdatePDlg_FALSE();
			////////////////
			return MA_OK;

		case P_COONS:		// 
			

			m_nInfoDone++;
			////////////////
			if(m_nCurveDone > MAX_INFO_COONS)
			{
				m_nCurveDone--;
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdatePDlg_TRUE();
			//////////////////
			nResult = LeftUp_COONS_PAT(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdatePDlg_FALSE();
			///////
			return MA_OK;
	
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	/////////////
	return MA_OK;
}

int CPatMouse::CheckCompatibility_GORDON_Curve(	
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pLatchList_V)
{
	return MA_OK;
}

int CPatMouse::CreateDataNodeList(CDListMgr* pNodeList,CDListMgr* pCurveList,
								  CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
									int& nNodes_U,int& nNodes_V)
{
	// Compare and Pick Bezier Jn. Pt. CNodes as Data Nodes
	////////////////////////////////////////////////////////
	int k=0,m;
	nNodes_V = pCurveList->GetCount();
	//////////////////////////////////
	POSITION	pos,posL;
	CDListMgr*	pCNodeList;
	BOOL		bCompareBKward = FALSE;
	CURVELATCH	LatchOld;
	int			nSegBZ,nSegBZOld;
	int			nDegree;
	BOOL		bClosed,bClosedOld;
	int			nNodes_UOld;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (pos = pCurveList->GetFirstObjectPos(),posL = pLatchList_U->GetHeadPosition();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pCurve)
			return MA_ERROR;
		CURVELATCH Latch	= pLatchList_U->GetNext(posL);  
		pCNodeList			= pCurve->GetCNodeList();
   	 	///////////////////////////////////////////// InputNodes
		bClosed				= pCurve->IsClosed_S();
		nDegree				= pCurve->GetOrder_S() - 1;
		nSegBZ 				= pCurve->GetMaxBezSegments_S();
		////////
		if(k == 0)
		{
			bClosedOld	= bClosed;
			nSegBZOld	= nSegBZ;
			LatchOld	= Latch;
		}
		else
		if(nSegBZ != nSegBZOld )
		{
			AfxMessageBox("INPUT ERROR:\nCurves DO Not Have SAME Number of\nBezier Segments!!");
			Terminate_PAT(TRUE);
			return MA_ERROR;
		}
		if(bClosed != bClosedOld )
		{
			AfxMessageBox("INPUT ERROR:\nCurves Need to be\nAll Closed or All Open!!");
			Terminate_PAT(TRUE);
			return MA_ERROR;
		}
		/////////////////////////////////////////////////
		nNodes_U = 0;
		bCompareBKward = (LatchOld == Latch)? FALSE:TRUE;
		///////////////////////////////////////////// go over the list
		if(bCompareBKward)
		{
			m = pCNodeList->GetCount(); 
			for (POSITION posI = pCNodeList->GetTailPosition();posI !=NULL;)
			{
				m--;
				/////////////////
				CDrNode* pNode = (CDrNode*)pCNodeList->GetPrev(posI);
				if(!pNode)
					return MA_ERROR;
				////
				if(m%nDegree !=0)	// not a Jn. Pt.
					continue;
				///////////////////////////////
				nNodes_U++;
				pNodeList->InsertObject(pNode);
			}
		}
		else
		{
			m = -1; 
			for (POSITION posI = pCNodeList->GetFirstObjectPos();posI !=NULL;)
			{
				m++;
				/////////////////
				CDrNode* pNode = (CDrNode*)pCNodeList->GetNextObject(posI);
				if(!pNode)
					return MA_ERROR;
				////
				if(m%nDegree !=0)	// not a Jn. Pt.
					continue;
				///////////////////////////////
				nNodes_U++;
				pNodeList->InsertObject(pNode);
			}
		}
		////
		if(k == 0)
		{
			nNodes_UOld = nNodes_U;
			k++;
		}
		////////////////////////////
		if(nNodes_U != nNodes_UOld )
		{
			AfxMessageBox("Internal ERROR:\nCPatMouse::CreateDataNodeList\nnNodes_U != nNodes_UOld");
			Terminate_PAT(TRUE);
			return MA_ERROR;
		}

	}
	////////////
	return MA_OK;
}
/*
int CPatMouse::CreateDataNodeList(CDListMgr* pNodeList,CDListMgr* pCurveList,
								  CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
									int& nNodes_U,int& nNodes_V)
{
	////////////////////////////////////////////////////////
	int k=0;
	nNodes_V = pCurveList->GetCount();
	//////////////////////////////////
	POSITION pos,posL;
	CDListMgr* pINodeList;
	BOOL bCompareBKward = FALSE;
	CURVELATCH LatchOld;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (pos = pCurveList->GetFirstObjectPos(),posL = pLatchList_U->GetHeadPosition();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pCurve)
			return MA_ERROR;
		CURVELATCH Latch = pLatchList_U->GetNext(posL);  
   	 	///////////////////////////////////////////// InputNodes
		pINodeList = pCurve->GetINodeList();
		if(k == 0)
		{
			nNodes_U = pINodeList->GetCount();
			LatchOld = Latch;
			////
			k++;
		}
		else
		if(nNodes_U != (pINodeList->GetCount()) )
		{
			AfxMessageBox("INPUT ERROR:\nCurves DO Not Have SAME Number of\nBezier Segments!!");
			Terminate_PAT(TRUE);
			return MA_ERROR;
		}
		/////////////////////////////////////////////////
		bCompareBKward = (LatchOld == Latch)? FALSE:TRUE;
		///////////////////////////////////////////// go over the list
		if(bCompareBKward)
		{
			for (POSITION posI = pINodeList->GetTailPosition();posI !=NULL;)
			{
				CDrNode* pNode = (CDrNode*)pINodeList->GetPrev(posI);
				if(!pNode)
					return MA_ERROR;
				///////////////////////////////
				pNodeList->InsertObject(pNode);
			}
		}
		else
		{
			for (POSITION posI = pINodeList->GetFirstObjectPos();posI !=NULL;)
			{
				CDrNode* pNode = (CDrNode*)pINodeList->GetNextObject(posI);
				if(!pNode)
					return MA_ERROR;
				///////////////////////////////
				pNodeList->InsertObject(pNode);
			}
		}
	}
	////////////
	return MA_OK;
}
*/	
int CPatMouse::TENSORTwistDlgUpdate_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	if(m_bAllSame)	// Twist Done
	{
		m_nTwistDone	= 4;
		m_bCornerMode	= FALSE;
		m_bEditMode		= TRUE;
		///////
		return MA_OK;
	}
	///////////////////////////////////////////////////////////////////////
	switch(m_nTwistDone)
	{
		case 0:
			m_bCornerMode	= TRUE;
			m_TwistMethod	= TW_ZERO;
			////////
			m_indexNode_I	= 0;
			m_nCornerI		= 0;
			m_nCornerJ		= 0;
			break;
		case 1:
			m_indexNode_I	= m_nNodes_U-1;
			m_nCornerI		= 1;
			m_nCornerJ		= 0;
			break;
		case 2:
			m_indexNode_I	= m_nNodes_U*(m_nNodes_V-1);
			m_nCornerI		= 0;
			m_nCornerJ		= 1;
			break;
		case 3:
			m_indexNode_I	= m_nNodes_U*m_nNodes_V - 1;
			m_nCornerI		= 1;
			m_nCornerJ		= 1;
			break;
		default:
			m_nTwistDone	= 4;
			m_bCornerMode	= FALSE;
			m_bEditMode		= TRUE;
			///////
			return MA_OK;
		}
	////////////////////////////////////////////////////// Activate
	CDrNode* pDrNode = (CDrNode*)(m_NodeList.GetObject(m_indexNode_I) );
	pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
	/////////////////////////////////////////////////
	return MA_OK;
}
	
int CPatMouse::TENSOREndDlgUpdate_PAT()
{
	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////
	CDrCurve*					pBlendCurve; 
	CList<BLENDEND,BLENDEND>*	pEndList;	// if(bClosed_V or Linear_V,Circle_V,
	CURVEPROC CurveType;
	BOOL bClosed;
	int nNodes;
	///
	if(m_bAllSame)
	{
		if(m_bU)
			m_nEndCondDone	= m_nEndTanNeeded_U;
		else
			m_nEndCondDone	= m_nEndTanNeeded_U + m_nEndTanNeeded_V;
	}
	///
	if(m_nEndCondDone == (m_nEndTanNeeded_U + m_nEndTanNeeded_V))
	{
		m_bEndCondMode	= FALSE;
		///////////////////////////////////////////////////////////// No Twist Needed
		if(m_nEndTanNeeded_U == 0)
		{
			pBlendCurve		= m_pBlendCurve_U;
			m_nBlendOrder_U = pBlendCurve->GetOrder_S();
			pEndList		= &m_EndList_U;
			nNodes			= m_nNodes_V;
		}
		else
		if(m_nEndTanNeeded_V == 0)
		{
			pBlendCurve		= m_pBlendCurve_V;
			m_nBlendOrder_V = pBlendCurve->GetOrder_S();
			pEndList		= &m_EndList_V;
			nNodes			= m_nNodes_U;
		}
		//////////////////////////////////
		CurveType		= pBlendCurve->GetCurveType_S();
		bClosed			= pBlendCurve->IsClosed_S(); 
		/////////////////////////////////////////////////// Fill up
		if(	bClosed ||
			(CurveType == CP_LINEAR)	||	// upto order 2 
			(CurveType == CP_CIRCLE)	|| 
			(CurveType == CP_PARABOLA)	||
			(CurveType == CP_ELLIPSE)
		)
		{
			BLENDEND blendEnd;
			blendEnd.m_BCL	= BC_AUTO;
			blendEnd.m_BCR	= BC_AUTO;
			blendEnd.m_TanL.v[0] = -99999.;
			blendEnd.m_TanR.v[0] = -99999.;
			//////////////////////////////////
			for(int i=0;i<nNodes;i++)
				pEndList->AddTail(blendEnd);
			/////////////
			return MA_OK;
		}
		////////////////////////
		m_bCornerMode	= TRUE;
		m_nTwistDone	= 0;
		TENSORTwistDlgUpdate_PAT();
		nResult = UpdateTwistDlg_FALSE();
		///////
		return MA_OK;
	}
	///////////////////////////////////////////////////////////////////////
	m_bU = (m_nEndCondDone<m_nEndTanNeeded_U)?TRUE:FALSE;
	if(m_bU)
	{
		m_indexNode_I = m_nNodes_U*m_nEndCondDone;		// index in NodeList
	}		
	else
	{
		int nEndCondDone_V = m_nEndCondDone - m_nEndTanNeeded_U;   
		m_indexNode_I = nEndCondDone_V;					// index in NodeList
		//////////////////////////////////////////
	}
	////////////////////////////////////////////////////// Activate
	CDrNode* pDrNode = (CDrNode*)(m_NodeList.GetObject(m_indexNode_I) );
	pObjectMgr->ShowObject_On_Off(pDrNode,NODE,TRUE);
	/////////////////////////////////////////////////
	return MA_OK;
}

int CPatMouse::IsEndCondNeeded_LOFT(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V)
{
	int nResult,i;
	BOOL bNeeded_U = FALSE;	// always
	BOOL bNeeded_V = TRUE;
	/////////////////////////////////
	nResult = GetBlendInfo_LOFT();
	/////////////////////////////////
	if(nResult != MA_OK)
		return nResult;
	////////////////////////////////////////////////
	m_nBlendOrder_V = m_pBlendCurve_V->GetOrder_S();
	/////////////////////////////////////////////////////////////////////////////
	if(!m_bAdvanced)
	{
		//////////////////////////////////////////////////// Default (Left BC);
		BLENDEND BlendEnd;
		BlendEnd.m_BCL = BC_BESSEL;	// Left has precedence over right
		//////////////////////////////////////////// U-Curves
		if(m_nBlendOrder_U<=3)	// upto Quadratic
			BlendEnd.m_TanR.v[0] = -99999.;
		else					// Cubic upwards
			BlendEnd.m_BCR = BC_BESSEL;
		///////////////////////////
		for(i=0;i<m_nNodes_V/*Curves_U*/;i++)
			m_EndList_U.AddTail(BlendEnd);
		//////////////////////////////////////////// V-Curves
		if(m_nBlendOrder_V<=3)	// upto Quadratic
			BlendEnd.m_TanR.v[0] = -99999.;
		else					// Cubic upwards
			BlendEnd.m_BCR = BC_BESSEL;
		for(i=0;i<m_nNodes_U;i++)
			m_EndList_V.AddTail(BlendEnd);
		////////////////////////////////////////////
		bEndCondMode	= FALSE;
		nEndTanNeeded_U	= 0;
		nEndTanNeeded_V	= 0;
		/////////////
		return MA_OK;
	}
	///////////////
	CURVEPROC CurveType;
	BOOL bClosed;
	////////////////////////////////////////////////////////////////////////
	bNeeded_U		= FALSE;
	nEndTanNeeded_U	= 0;
	////////////////////////////////////////////////////////////////////////
	CurveType		= m_pBlendCurve_V->GetCurveType_S();
	bClosed			= m_pBlendCurve_V->IsClosed_S(); 
	m_nBlendOrder_V = m_pBlendCurve_V->GetOrder_S();
	///
	if(	bClosed ||
		(CurveType == CP_LINEAR)	||	// upto order 2 
		(CurveType == CP_CIRCLE)	|| 
		(CurveType == CP_PARABOLA)	||
		(CurveType == CP_ELLIPSE)
		)
	{
		bNeeded_V		= FALSE;
		nEndTanNeeded_V	= 0;
	}
	else
		nEndTanNeeded_V	= m_nNodes_U;	// number of V-directional Curves
	/////////////////////////////////
	if(bNeeded_U || bNeeded_V)
	{
		m_bAllSame		= FALSE;
		bEndCondMode	= TRUE;
	}
	/////////////
	return MA_OK;
}

int CPatMouse::GetBlendInfo_LOFT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMPatMgr MPatMgr;
	/////
	m_pBlendCurve_V = new CDrCurve;	// private
	///////////////////////////////////////// V-dir
	if(m_nNodes_V>2)	// need blending info
	{
		/////////////////////////////////////// CurrStat: Show
		strCurr = "Loft Patch: Please Select @V-directional Blending Info";
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		/////////////////////////////////////// GetBlending Info.
		int nCurves = m_nNodes_U/*# V-Curves*/;
		//
		if(MPatMgr.DoModal_Patch_TensorBlend(m_pBlendCurve_V,m_nNodes_U/*# V-Curves*/,2/*dir*/) == IDCANCEL)
		{
			delete m_pBlendCurve_V;
			m_pBlendCurve_V = NULL;
			Terminate_PAT(TRUE);
			return MA_CANCEL;
		}
		else
		{
			if(m_pBlendCurve_V->IsClosed_S())
				m_nLastElems_V = m_pBlendCurve_V->GetElperSegList_S()->GetHead();	// Closing Elems
		}
	}
	else
	{
		m_pBlendCurve_V->SetCurveType_S(CP_LINEAR);
		m_pBlendCurve_V->SetOrder_S(2);	// Linear	
		m_pBlendCurve_V->SetClosed_S(FALSE);
		m_pBlendCurve_V->SetnDim_S(3);
	}
	/////////////
	return MA_OK;
}

int CPatMouse::IsEndCondNeeded_TENSOR(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V)
{
	int nResult,i;
	BOOL bNeeded_U = TRUE;
	BOOL bNeeded_V = TRUE;
	/////////////////////////////////
	nResult = GetBlendInfo_TENSOR();
	/////////////////////////////////
	if(nResult != MA_OK)
		return nResult;
	////////////////////////////////////////////////
	m_nBlendOrder_U = m_pBlendCurve_U->GetOrder_S();
	m_nBlendOrder_V = m_pBlendCurve_V->GetOrder_S();
	/////////////////////////////////////////////////////////////////////////////
	if(!m_bAdvanced)
	{
		//////////////////////////////////////////////////// Default (Left BC);
		BLENDEND BlendEnd;
		BlendEnd.m_BCL = BC_BESSEL;	// Left has precedence over right
		//////////////////////////////////////////// U-Curves
		if(m_nBlendOrder_U<=3)	// upto Quadratic
			BlendEnd.m_TanR.v[0] = -99999.;
		else					// Cubic upwards
			BlendEnd.m_BCR = BC_BESSEL;
		///////////////////////////
		for(i=0;i<m_nNodes_V/*Curves_U*/;i++)
			m_EndList_U.AddTail(BlendEnd);
		//////////////////////////////////////////// V-Curves
		if(m_nBlendOrder_V<=3)	// upto Quadratic
			BlendEnd.m_TanR.v[0] = -99999.;
		else					// Cubic upwards
			BlendEnd.m_BCR = BC_BESSEL;
		for(i=0;i<m_nNodes_U;i++)
			m_EndList_V.AddTail(BlendEnd);
		////////////////////////////////////////////
		bEndCondMode	= FALSE;
		nEndTanNeeded_U	= 0;
		nEndTanNeeded_V	= 0;
		/////////////
		return MA_OK;
	}
	///////////////
	CURVEPROC CurveType;
	BOOL bClosed;
	////////////////////////////////////////////////////////////////////////
	CurveType		= m_pBlendCurve_U->GetCurveType_S();
	bClosed			= m_pBlendCurve_U->IsClosed_S(); 
	///
	if(	bClosed ||
		(CurveType == CP_LINEAR)	||	// upto order 2   
		(CurveType == CP_CIRCLE)	|| 
		(CurveType == CP_PARABOLA)	||
		(CurveType == CP_ELLIPSE)
		)
	{
		bNeeded_U		= FALSE;
		nEndTanNeeded_U	= 0;
	}
	else
		nEndTanNeeded_U	= m_nNodes_V;	// number of U-directional Curves
	////////////////////////////////////////////////////////////////////////
	CurveType		= m_pBlendCurve_V->GetCurveType_S();
	bClosed			= m_pBlendCurve_V->IsClosed_S(); 
	m_nBlendOrder_V = m_pBlendCurve_V->GetOrder_S();
	///
	if(	bClosed ||
		(CurveType == CP_LINEAR)	||	// upto order 2 
		(CurveType == CP_CIRCLE)	|| 
		(CurveType == CP_PARABOLA)	||
		(CurveType == CP_ELLIPSE)
		)
	{
		bNeeded_V		= FALSE;
		nEndTanNeeded_V	= 0;
	}
	else
		nEndTanNeeded_V	= m_nNodes_U;	// number of V-directional Curves
	/////////////////////////////////
	if(bNeeded_U || bNeeded_V)
	{
		m_bAllSame		= FALSE;
		bEndCondMode	= TRUE;
	}
	/////////////
	return MA_OK;
}

int CPatMouse::GetBlendInfo_TENSOR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMPatMgr MPatMgr;
	/////////////////////
	m_pBlendCurve_U = new CDrCurve;	// private
	///////////////////////////////////////// U-dir
	if(m_nNodes_U>2)	// need blending info
	{
		/////////////////////////////////////// CurrStat: Show
		strCurr = "Tensor Product Patch: Please Select @U-directional Blending Info";
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		/////////////////////////////////////// GetBlending Info
		int nCurves = m_nNodes_V/*# U-Curves*/;
		//	
		if(MPatMgr.DoModal_Patch_TensorBlend(m_pBlendCurve_U,nCurves,1/*dir*/) == IDCANCEL)
		{
			delete m_pBlendCurve_U;
			m_pBlendCurve_U = NULL;
			Terminate_PAT(TRUE);
			return MA_CANCEL;
		}
		else
		{
			if(m_pBlendCurve_U->IsClosed_S())
				m_nLastElems_U = m_pBlendCurve_U->GetElperSegList_S()->GetHead();	// Closing Elems
		}
	}
	else
	{
		m_pBlendCurve_U->SetCurveType_S(CP_LINEAR);
		m_pBlendCurve_U->SetOrder_S(2);	// Linear	
		m_pBlendCurve_U->SetClosed_S(FALSE);
		m_pBlendCurve_U->SetnDim_S(3);
	}
	/////
	m_pBlendCurve_V = new CDrCurve;	// private
	///////////////////////////////////////// V-dir
	if(m_nNodes_V>2)	// need blending info
	{
		/////////////////////////////////////// CurrStat: Show
		strCurr = "Tensor Product Patch: Please Select @V-directional Blending Info";
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		/////////////////////////////////////// GetBlending Info.
		int nCurves = m_nNodes_U/*# V-Curves*/;
		//
		if(MPatMgr.DoModal_Patch_TensorBlend(m_pBlendCurve_V,m_nNodes_U/*# V-Curves*/,2/*dir*/) == IDCANCEL)
		{
			delete m_pBlendCurve_V;
			m_pBlendCurve_V = NULL;
			Terminate_PAT(TRUE);
			return MA_CANCEL;
		}
		else
		{
			if(m_pBlendCurve_V->IsClosed_S())
				m_nLastElems_V = m_pBlendCurve_V->GetElperSegList_S()->GetHead();	// Closing Elems
		}
	}
	else
	{
		m_pBlendCurve_V->SetCurveType_S(CP_LINEAR);
		m_pBlendCurve_V->SetOrder_S(2);	// Linear	
		m_pBlendCurve_V->SetClosed_S(FALSE);
		m_pBlendCurve_V->SetnDim_S(3);
	}
	/////////////
	return MA_OK;
}
	
int CPatMouse::GORDONEndDlgUpdate_PAT()
{
	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	m_bEndCondMode	= FALSE;
	////////////////////////
	m_bCornerMode	= TRUE;
	m_nTwistDone	= 0;
	/////////////////
	if(m_bCornerMode)
	{	
		if(m_nTwistDone == 0)
		/////////////////////////////////////////////// Create for Title
		SwitchToEndCondDlg();
		((CBasePage*)(GetPatSheet()->GetActivePage()))->ResetDlgForTwist();
		////
		strCurr = "Gordon Patch: Provide Twists";
		strCurr +="@Done with it? Please Click On Update Button";
	}
	///////////////////////////
	TENSORTwistDlgUpdate_PAT();
	nResult = UpdateTwistDlg_FALSE();
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
	return MA_OK;
}

int CPatMouse::IsEndCondNeeded_GORDON(BOOL& bEndCondMode,
						CDListMgr* pCurveList_U,CDListMgr* pCurveList_V)
{
	int nResult,i;
	BOOL bNeeded_U = TRUE;
	BOOL bNeeded_V = TRUE;
	/////////////////////////////////
	nResult = GetBlendInfo_GORDON();
	/////////////////////////////////
	if(nResult != MA_OK)
		return nResult;
	//////////////////////////////////////////////// set
	m_nBlendOrder_U = m_pBlendCurve_U->GetOrder_S();
	m_nBlendOrder_V = m_pBlendCurve_V->GetOrder_S();
	/////////////////////////////////////////////////////////////////////////////
	CURVEPROC CurveType;
	BOOL bClosed;
	////////////////////////////////////////////////////////////////////////
	CurveType		= m_pBlendCurve_U->GetCurveType_S();
	bClosed			= ((CDrCurve*)pCurveList_U->GetHead())->IsClosed_S(); 
	///
	if(	bClosed ||
		(CurveType == CP_LINEAR)	||	// upto order 2   
		(CurveType == CP_CIRCLE)	|| 
		(CurveType == CP_PARABOLA)	||
		(CurveType == CP_ELLIPSE)
		)
	{
		bNeeded_U		= FALSE;
	}
	////////////////////////////
	{
		BLENDEND BlendEnd;
		POSITION pos;
		CDrCurve* pCurve;
		//////////////////////////////////////////// U-Curves
		for(i=0;i<m_nCurves_U;i++)
		{
			pos		= pCurveList_U->FindIndex(i);
			pCurve	= (CDrCurve*)pCurveList_U->GetAt(pos);
			///
			BlendEnd.m_BCL	= pCurve->GetBCL_S();
			BlendEnd.m_TanL	= pCurve->GetTanL_S();
			BlendEnd.m_BCR	= pCurve->GetBCR_S();
			BlendEnd.m_TanR	= pCurve->GetTanR_S();
			//////////////////////////////
			m_EndList_U.AddTail(BlendEnd);
		}
	}
	////////////////////////////////////////////////////////////////////////
	CurveType		= m_pBlendCurve_V->GetCurveType_S();
	bClosed			= ((CDrCurve*)pCurveList_V->GetHead())->IsClosed_S(); 
	///
	if(	bClosed ||
		(CurveType == CP_LINEAR)	||	// upto order 2 
		(CurveType == CP_CIRCLE)	|| 
		(CurveType == CP_PARABOLA)	||
		(CurveType == CP_ELLIPSE)
		)
	{
		bNeeded_V		= FALSE;
	}
	////////////////////////////
	{
		BLENDEND BlendEnd;
		POSITION pos;
		CDrCurve* pCurve;
		//////////////////////////////////////////// V-Curves
		for(i=0;i<m_nCurves_V;i++)
		{
			pos		= pCurveList_V->FindIndex(i);
			pCurve	= (CDrCurve*)pCurveList_V->GetAt(pos);
			///
			BlendEnd.m_BCL	= pCurve->GetBCL_S();
			BlendEnd.m_TanL	= pCurve->GetTanL_S();
			BlendEnd.m_BCR	= pCurve->GetBCR_S();
			BlendEnd.m_TanR	= pCurve->GetTanR_S();
			//////////////////////////////
			m_EndList_V.AddTail(BlendEnd);
		}
		////////////////////////////////////////////
	}
	/////////////////////////////////
	if(!m_bAdvanced)
		bEndCondMode	= FALSE;
	else
	if(bNeeded_U || bNeeded_V)
	{
		m_bAllSame		= FALSE;
		bEndCondMode	= TRUE;
	}
	/////////////
	return MA_OK;
}

int CPatMouse::GetBlendInfo_GORDON()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMPatMgr MPatMgr;
	/////////////////////
	m_pBlendCurve_U = new CDrCurve;	// private
	///////////////////////////////////////// U-dir
	if(m_nCurves_U>2)	// need blending info
	{
		/////////////////////////////////////// CurrStat: Show
		strCurr = "Gordon Patch: Please Select @U-directional Blending Info";
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		/////////////////////////////////////// GetBlending Info
		if(MPatMgr.DoModal_Patch_TensorBlend(m_pBlendCurve_U,m_nCurves_U,1/*dir*/) == IDCANCEL)
		{
			delete m_pBlendCurve_U;
			m_pBlendCurve_U = NULL;
			Terminate_PAT(TRUE);
			return MA_CANCEL;
		}
/*	//	DoModal_Patch_TensorBlend should Disable bClose and Elem Windows
		else
		{
			if(m_pBlendCurve_U->IsClosed_S())
				m_nLastElems_U = m_pBlendCurve_U->GetElperSegList()->GetHead();	// Closing Elems
		}
*/
	}
	else
	{
		m_pBlendCurve_U->SetCurveType_S(CP_LINEAR);
		m_pBlendCurve_U->SetOrder_S(2);	// Linear	
		m_pBlendCurve_U->SetClosed_S(FALSE);
		m_pBlendCurve_U->SetnDim_S(3);
	}
	/////
	m_pBlendCurve_V = new CDrCurve;	// private
	///////////////////////////////////////// V-dir
	if(m_nCurves_V>2)	// need blending info
	{
		/////////////////////////////////////// CurrStat: Show
		strCurr = "Gordon Patch: Please Select @V-directional Blending Info";
		pWnd->SetstrCurrID(strCurr);
		pWnd->UpdateCurrStat(strCurr);
		/////////////////////////////////////// GetBlending Info.
		if(MPatMgr.DoModal_Patch_TensorBlend(m_pBlendCurve_V,m_nCurves_V,2/*dir*/) == IDCANCEL)
		{
			delete m_pBlendCurve_V;
			m_pBlendCurve_V = NULL;
			Terminate_PAT(TRUE);
			return MA_CANCEL;
		}
/*	//	DoModal_Patch_TensorBlend should Disable bClose and Elem Windows
		else
		{
			if(m_pBlendCurve_V->IsClosed_S())
				m_nLastElems_V = m_pBlendCurve_V->GetElperSegList()->GetHead();	// Closing Elems
		}
*/
	}
	else
	{
		m_pBlendCurve_V->SetCurveType_S(CP_LINEAR);
		m_pBlendCurve_V->SetOrder_S(2);	// Linear	
		m_pBlendCurve_V->SetClosed_S(FALSE);
		m_pBlendCurve_V->SetnDim_S(3);
	}
	/////////////
	return MA_OK;
}

int CPatMouse::SwitchToEndCondDlg()
{
	///////////////////////////////////////
	if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
		GetPatSheet()->DestroyWindow();
	///////////////////////////////////////// Set right page
	GetPatSheet()->m_PatProc = m_PatProc;
	GetPatSheet()->SetEndCondMode(m_bEndCondMode);
	///////////////////////////////////////// Create
	if(GetPatSheet()->SetProcPage() != MA_OK) 
	{
		AfxMessageBox(
			"Internal ERROR:\nCPatMouse::SwitchToEndCondDlg\n!GetPatSheet()->Create()");
		return MA_ERROR;
	}
	////////////
	return MA_OK;
}

int CPatMouse::ShowPatchInfo(CDrPatch* pDrPatch)
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
	j = sprintf(buf,"***** A Patch Hit To Spawn ****\n");
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

		case PP_LOFT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Lofting\n",*pID);
			break;

		case PP_TENSOR:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Tensor Product\n",*pID);
			break;

		case PP_GORDON:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Patch %s\nGenerated by Gordon Method\n",*pID);
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
		"\nYES:\t\tSpawn This Patch");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Patch with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	///
	if(!m_bAutoAcceptOn)
		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	else
		nResult = IDYES;
//	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CPatMouse::OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CPatMouse::OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_PAT(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CPatMouse::OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
									UINT nFlags, CPoint point)
{ 
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
/*
	/////////////////////////////////////////////////////////
	if(pWnd->GetMouseMgr()->IsCurrentProcessDone() )
		return;
	/////////////////////////////////
*/
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
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

int CPatMouse::RightUp_Premature_PAT()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////////////////////////////// Add to DataBase
	CString*	pID;
	CString		str;
	int		nAnswer = IDOK;
	BOOL	bPremature = FALSE;
	////////////////////////////////
	pID			= &m_CurrentPatchID; 
	//////////////////////////////////////////////////// Check Adequate Curve,or cancel
	switch(m_PatProc)
	{
		case PP_EXTRUDE:

			if(m_nInfoDone<3)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Curve & 2 CNodes Needed";
			}
			break;

		case PP_ROTATE:

			if(m_nInfoDone<3)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Curve & 2 CNodes Needed";
			}
			break;

		case PP_LOFT:

			if(m_nInfoDone<MIN_INFO_LOFT)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Curves Needed";
			}
			break;

		case PP_TENSOR:

			if(m_nInfoDone<MIN_INFO_TENSOR)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Nodes Needed in Each Direction";
			}
			break;

		case PP_GORDON:

			if(m_nInfoDone<MIN_INFO_GORDON)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Curves Needed in Each Direction";
			}
			break;

		case PP_DUCT:

			if(m_nInfoDone<4)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Curves & 1 CNode and\nTwist Info Needed";
			}
			break;

		case PP_SWEEP:

			if(m_nInfoDone<5)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Curves & 1 CNode,\nTwist and Scaling Info Needed";
			}
			break;

		case PP_COONS:

			if(m_nInfoDone<3)
			{
				bPremature = TRUE;
				str = "Minimum of 3 Curves Needed";
			}
			break;

		default:
			break;
	}
	//////////////////////////////////////////////////////// OK
	if(!bPremature)
		return MA_OK;
	//////////////////////////////////////////////////////// ReConfirm: Don't Continue
	str += "\n Do You want to Continue to Get More Info. ?";
	nAnswer = AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION );
	/////////////////////////
	if(nAnswer == IDNO)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Are You Sure You Want to\nDelete Current Patch?");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		delete str;
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			Terminate_PAT(TRUE);
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
			return MA_CANCEL;
		}
		///////////
	}
	////////
	return MA_GETMOREINFO;
}	

int CPatMouse::RightUp_NotAutoAccept_PAT()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDrCurve*	pDrCurve;
	CDrNode*	pDrNode;
	////////////////////////////////////////////////////// Add to DataBase
	CString* pID;
	int i;
	int nAnswer = IDOK;
	////////////////////////////////
	pID			= &m_CurrentPatchID; 
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j;
		//////////
		pDrCurve = (CDrCurve*)(m_CurveList.GetObject(0) );	//Head
		//////////////////////////////////////////////////// Check Adequate Curve,or cancel
		switch(m_PatProc)
		{
			case PP_COONS:


				j = sprintf(buf,"Patch %s contains\n\t%d Coons Curves:\n",
					*pID,m_nCurveDone);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s Curve_%d\n",pDrCurve->GetObjectID(),i+1);
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_EXTRUDE:

				j = sprintf(buf,"Patch %s contains\n\tExtrusion Curve:\t%s",
					*pID,pDrCurve->GetObjectID());

				j += sprintf(buf + j,"\n\t%d Direction Nodes:\t",m_nNodeDone);
				for(i=0;i<m_nNodeDone;i++)
				{
					pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
					j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_ROTATE:

				j = sprintf(buf,"Patch %s contains\n\tRotational Curve:\t%s",
					*pID,pDrCurve->GetObjectID());

				j += sprintf(buf + j,"\n\t%d Axis Nodes:\t",m_nNodeDone);
				for(i=0;i<m_nNodeDone;i++)
				{
					pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
					j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_LOFT:

				j = sprintf(buf,"Patch %s contains\n\t%d Lofting Curves:\n",
					*pID,m_nCurveDone);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s ,",pDrCurve->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_TENSOR:

				j = sprintf(buf,"Patch %s consists of\n\t%d Nodes by %d Nodes:\n",
					*pID,m_nNodes_U,m_nNodes_V);

				for(i=0;i<m_nNodeDone;i++)
				{
					pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s ,",pDrNode->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_GORDON:

				j = sprintf(buf,"Patch %s consists of\n\t%d Curves by %d Curves:\n",
					*pID,m_nCurves_U,m_nCurves_V);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s ,",pDrCurve->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_DUCT:

				j = sprintf(buf,"Patch %s contains\n\t%d Ducting Curves && %d Anchor Node:\n",
					*pID,m_nCurveDone,m_nNodeDone);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					switch(i)
					{
						case 0:
							j += sprintf( buf + j, "\t%s CrossSectional Curve",pDrCurve->GetObjectID());
							break;
						case 1:
							j += sprintf( buf + j, "\t%s Spine Curve",pDrCurve->GetObjectID());
							break;
						default:
							break;
					}
				}
				pDrNode = (CDrNode*)(m_NodeList.GetObject(0) );
				j += sprintf( buf + j, "\n\t%s Anchor Node",pDrNode->GetObjectID());
				/////////////////////////
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case PP_SWEEP:

				j = sprintf(buf,"Patch %s contains\n\t%d Sweeping Curves && %d Anchor Node:\n",
					*pID,m_nCurveDone,m_nNodeDone);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					switch(i)
					{
						case 0:
							j += sprintf( buf + j, "\t%s CrossSectional Curve",pDrCurve->GetObjectID());
							break;
						case 1:
							j += sprintf( buf + j, "\t%s Spine Curve",pDrCurve->GetObjectID());
							break;
							break;
						default:
							break;
					}
				}
				pDrNode = (CDrNode*)(m_NodeList.GetObject(0) );
				j += sprintf( buf + j, "\n\t%s Anchor Node",pDrNode->GetObjectID());
				/////////////////////////
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			default:
				break;
		}
		/////////////////////////////////////////////////////////////////////
		if(j>BUFF_SIZE)
		{
			sprintf( buf, "Internal Error:\nIncrease buffer to %d",j);
			AfxMessageBox(*str);
			delete str;
			return MA_ERROR;
		}	 
		///////////////////////////////////////////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
		delete str;
		/////////////////////////
		if(nAnswer == IDCANCEL)
		{
			str = new CString;
			char* buf = str->GetBuffer(BUFF_SIZE);
			sprintf(buf,"Are You Sure You Want to\nDelete Current Patch?");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////////////////
			if(nAnswer == IDYES)
				return MA_CANCEL;		// cancel
		}
		else
			/////////////////////
			return MA_OK; 
	}
	/////////
	return MA_OK;	// autoaccept!
}

void CPatMouse::OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////////////
	int nResult = MA_OK;
	////////////////////
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	////////////////////////////////
	m_Gener					= gener;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////
	CString ID;
	CString* pID = &ID;
	///////////////////////////////////////////////////////// Update Info
	nResult = UpdatePDlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	nResult = RightUp_Premature_PAT();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_PAT(TRUE);return;
		case MA_CANCEL:Terminate_PAT(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	///////////////////////////////////////////////////////// Not Auto Accept
	nResult = RightUp_NotAutoAccept_PAT();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_PAT(TRUE);return;
		case MA_CANCEL:Terminate_PAT(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	////////////////////////////////////////////////////// Create & Show Patch
	nResult = ShowPatch(&m_CurrentPatchID);
	///////////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_PAT(TRUE);return;
		case MA_CANCEL:Terminate_PAT(TRUE);return;
	}
	/////////////////////////////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	m_bPatchDone	= TRUE;	  //
	m_nInfoDone		= 0;
	////////////////////////////////
	strCurr = "At Your Service!";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	/////////////////////////////////////// Reset: watch out! m_CurrentPatchID is also reset
	nResult = 
		AfxMessageBox("Do You Want to Continue\nwith the Same Procedure",MB_YESNO|MB_ICONQUESTION);
	if(nResult == IDYES)
	{
		/////////////////////
//		ResetVariables_PAT();
		/////////
		nResult = UpdatePDlg_FALSE();
		/////////
	}
	else
		Terminate_PAT(FALSE);
}


int CPatMouse::PutEndIdsInPlateList(CString nid[],int nEnds)
{
/*
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
	AfxMessageBox("ERROR:\nCPatMouse::PutEndIdsInPlateList\nSHOULD NOT BE USED");
	return -1; 
}
    
int CPatMouse::PutObjectinPatch(CDrObject* pAddObject,CString nid[],int nEnds)
{
/*
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
*/	
	return -1; 
} 
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CPatMouse::ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Creation@";
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
						case PATCH:			str = "PATCH";					ID = PATCH;
								strCur += "Select a Patch Type";	break;
						case P_TENSOR:		str = "Tensor Product@PATCH";	ID = P_TENSOR; 
								strCur += "A Tensor Product Patch";	break;
						case P_GORDON:		str = "Gordons@PATCH";			ID = P_GORDON;
								strCur += "A Gordons Patch";	break;
						case P_COONS:		str = "Coons@PATCH";			ID = P_COONS;
								strCur += "A Coons Patch";	break;
						case P_ROTATE:		str = "Rotational@PATCH";		ID = P_ROTATE; 
								strCur += "A Patch by Rotation";	break;
						case P_LOFT:		str = "Lofted@PATCH";			ID = P_LOFT; 
								strCur += "A Patch by Lofting";	break;
						case P_EXTRUDE:		str = "Extruded@PATCH";			ID = P_EXTRUDE; 
								strCur += "A Patch by Extrusion";	break;
						case P_DUCT:		str = "Ducted@PATCH";			ID = P_DUCT; 
								strCur += "A Patch by Ducting";	break;
						case P_SWEEP:		str = "Swept@PATCH";			ID = P_SWEEP; 
								strCur += "A Patch by Sweeping";	break;
						case P_FLATPLATE:	str = "Flat@PATCH";				ID = P_FLATPLATE;
								strCur += "A Patch by Tessalation";	break;
						default:			str = "UNKNOWN@PATCH";			ID = UNONE;
							break;
					}
					pWnd->SetstrIGenID(str);
//					pWnd->SendMessage(ID_UPDATE_STATCNTLS); // this one is needed for IGenID
					////////////////////////
					pWnd->SetstrCurrID(strCur);
					//////////
					return ID;
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
	
void CPatMouse::ModeLessOff_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetPatSheet()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_PATIN,IDOK);
}

void CPatMouse::ModeLessOn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
		switch(aTool)
		{
			case P_EXTRUDE:
				m_PatProc = PP_EXTRUDE;
				break;

			case P_ROTATE:
				m_PatProc = PP_ROTATE;
				break;

			case P_LOFT:
				m_PatProc = PP_LOFT;
				break;

			case P_TENSOR:
				m_PatProc = PP_TENSOR;
				break;

			case P_GORDON:
				m_PatProc = PP_GORDON;
				break;

			case P_COONS:
				m_PatProc = PP_COONS;
				break;

			case P_DUCT:
				m_PatProc = PP_DUCT;
				break;
			case P_SWEEP:
				m_PatProc = PP_SWEEP;
				break;
			default:
				break;
		}
		/////////////////////////////////////// Reset
//		ResetVariables_PAT();
		////////////////////////////
//		if(!(((CBasePage*)(GetPatSheet()->GetActivePage()))->m_hWnd))

			pWnd->SendMessage(ID_ACTIVE_PATIN,IDOK);
/*
	}
*/
}

long CPatMouse::CreateorActivatePatIn(UINT wParam, long lParam)
{
	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	PATCHPROC patProc = GetPatSheet()->m_PatProc; 
	if(GetPatSheet()->m_PatProc != m_PatProc)
	{
		GetPatSheet()->m_PatProc = m_PatProc;
		///////////////////////////////////////
		if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
			GetPatSheet()->DestroyWindow();
		///////////////////////////////////////// Set right page
		GetPatSheet()->m_PatProc = m_PatProc;
		GetPatSheet()->SetEndCondMode(m_bEndCondMode);
		///////////////////////////////////////// Create
		if(GetPatSheet()->SetProcPage() != MA_OK) 
		{
			AfxMessageBox(
				"Internal ERROR:\nCPatMouse::CreateorActivatePatIn\n!GetPatSheet()->Create()");
			return MA_ERROR;
		}
	}
	///////////////////////// Show Dlg and prepare
	nResult = UpdatePDlg_FALSE();
	if(nResult == MA_ERROR || nResult == MA_CANCEL)
		return 0L;
	///////////////////////////////////////////////////////////////// if PatDlg Open
	if(((CBasePage*)(GetPatSheet()->GetActivePage()))->m_hWnd)
	{
		ResetVuBasedVars_PatDlg();
	}
	////////////////////////////////
	return 0L;
}
 
void CPatMouse::ResetVuBasedVars_PatDlg()
{
	if(	m_PatProc == PP_LOFT ||m_PatProc == PP_GORDON ||m_PatProc == PP_COONS ||
		m_bEndCondMode || m_bCornerMode || m_bEditMode)	// for Loft/Tensor/Gordon End Condition
														// doNothing
		return;
	////////////////////////////////////////////////////////////////// Set Info
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(((CBasePage*)(GetPatSheet()->GetActivePage()))->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		SwitchThirdCoordHeading(pCtl,
			(UINT)(pWnd->GetActiveViewNumber()) );
	}
}
	 
long CPatMouse::GoodByePatIn(UINT wParam, long lParam)
{
	
	GetPatSheet()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CPatMouse::CancelPatIn(UINT wParam, long lParam)
{
	
	GetPatSheet()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CPatMouse::UpdatePatIn(UINT wParam, long lParam)
{
	int nResult;
	////////////
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(TRUE);
	//////////////////////////////////////
	if(m_bEndCondMode)	// End Tangents
	{
		m_nEndCondDone++;
		///
		nResult = UpdateEndDlg_TRUE();
		TENSOREndDlgUpdate_PAT();
		/////////////////////////////////
		nResult = UpdateEndDlg_FALSE();
		///
		return 0L;
	}
	else
	if(m_bCornerMode)	// Twist
	{
		m_nTwistDone++;
		///
		nResult = UpdateTwistDlg_TRUE();
		TENSORTwistDlgUpdate_PAT();
		/////////////////////////////////
		nResult = UpdateTwistDlg_FALSE();
		///
		return 0L;
	}
	//////////////////
	nResult = UpdatePDlg_TRUE();
	//////////////////////////// Special for Pat by Revolution
	if((m_PatProc == PP_ROTATE) && (m_nInfoDone == 2) & m_bAxis)
	{
		nResult = ProcessPatRotAxis();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_PAT(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdatePDlg_FALSE();
		}
	}
	else
	if(((m_PatProc == PP_DUCT)||(m_PatProc == PP_SWEEP)) && (m_nInfoDone == 3))
	{
		nResult = ProcessPatTwist_DUCT_SWEEP();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_PAT(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdatePDlg_FALSE();
		}
	}
	else
	if((m_PatProc == PP_SWEEP) && (m_nInfoDone == 4))
	{
		nResult = ProcessPatScale_SWEEP();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_PAT(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdatePDlg_FALSE();
		}
	}
	//////////
	return 0L;
}
	 
int CPatMouse::ProcessPatTwist_DUCT_SWEEP()
{
	// Twist Distribution
	//////////////////////
	int i;
	//////////////////////////////////
	m_bTwist			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist;
	if(!m_bTwist)
		return MA_ERROR;
	////////////////////
	m_nMaxTwist			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMaxTwist;
	m_pTwist			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pTwist;
	m_bIncrement		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement;
	m_TwistStart		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart;
	m_TwistMult			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult;
	///////////
	m_nTwistType		= (m_bIncrement)?2:1;
	///////////
	if(m_nTwistType == 1 && m_pTwist)
	{
		m_TwistList.RemoveAll();
		//////////////////////////
		for(i=0;i<m_nMaxTwist;i++)
			m_TwistList.AddTail(m_pTwist[i] * m_TwistMult);
		//////////////////////////
		delete [] m_pTwist;
		m_pTwist = NULL;
	}
	/////////////
	return MA_OK;
}

int CPatMouse::ProcessPatScale_SWEEP()
{
	// Radius Distribution
	//////////////////////
	int i;
	//////////////////////////////////
	m_bTwist			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist;
	if(m_bTwist)
		return MA_ERROR;
	////////////////////
	m_nMaxScale			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMaxTwist;
	m_pScale			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pTwist;
	m_bIncScale			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement;
	m_ScaleStart		= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart;
	m_ScaleMult			= ((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult;
	///////////
	m_nScaleType		= (m_bIncrement)?2:1;
	///////////
	if(m_nScaleType == 1 && m_pScale)
	{
		m_ScaleList.RemoveAll();
		//////////////////////////
		for(i=0;i<m_nMaxScale;i++)
			m_ScaleList.AddTail(m_pScale[i] * m_ScaleMult);
		//////////////////////////
		delete [] m_pScale;
		m_pScale = NULL;
	}
	/////////////
	return MA_OK;
}	

int CPatMouse::ProcessPatRotAxis()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// Patch_by_Rot with Axis
	WORLD LocPos_From,LocaPos_To;
	POSITION pos;
	CDrNode* pNode;
	CDrLabel* pLabel;
	CMI_GangN GangN;
	CString ToID;
	/////////////////////////// Generate ToID Node
	int nNodeIndex = -12345; // Create Anyway
	int nLabelIndex= 0;
	////////////////
	m_ElSegList.RemoveAll();
	m_ElSegList.AddTail(m_ElPerSeg);
	m_ElSegList.AddTail(m_nTotElems);	// it is Actually # of BezierSegments
	///////////////////////////////// Create ToID anyway
	pos		= m_NodeList.FindIndex( 0 );
	pNode	= (CDrNode*)(m_NodeList.GetAt(pos));
	LocPos_From	= *(pNode->GetLocalPos());
	///
	LocaPos_To.x = LocPos_From.x;
	LocaPos_To.y = LocPos_From.y;
	LocaPos_To.z = LocPos_From.z;
	//
	switch(m_nAxis)
	{
		case 1:	m_bNegative?LocaPos_To.x += -1.0:LocaPos_To.x += 1.0;	break;
		case 2:	m_bNegative?LocaPos_To.y += -1.0:LocaPos_To.y += 1.0;	break;
		case 3:	m_bNegative?LocaPos_To.z += -1.0:LocaPos_To.z += 1.0;	break;
		default:
		{
			AfxMessageBox("Internal ERROR:\nCPatMouse::ProcessPatRotAxis()\nm_nAxis !=1,2or3");
				return MA_ERROR;
		}
	}
	////////////
	pObjectMgr->SetNodeInfoID(ToID,TRUE,CNODE);
	////
	pNode = GangN.CreateNode(ToID,pLabel,LocaPos_To,TRUE,TRUE,
						nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
	pNode->SetCategory(CA_ELEMENT);
	pNode->SetShow(FALSE);	// only for Internal Use
	//////////////////////////////////////////////// save
	m_NodeList.AddTail(pNode);
	//////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_EXTRUDE()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Extrusion: Click in@A Curve To Extrude";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nExtruType= m_nExtruType;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dLen		= m_dLen;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_wLen		= m_wLen;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			////////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->
																SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			/////
			break;
		case 1:
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Extrusion: Click in@Ist (C)Node defining Extrusion Direction";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Click in 2nd (C)Node defining Extrusion Dirn.@or Select Extrusion Type 2 from DialogBox";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node To");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_ROTATE()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Rotation: Click in@A Curve To Rotate";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAxis		= m_bAxis;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nAxis		= m_nAxis;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bNegative	= m_bNegative;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			////////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->
																SetWindowText("Rotnl.Curve");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
 			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_X)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Y)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Z)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NEGATIVE)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Rotation: Click in@Ist (C)Node defining Rotation Axis";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Click in 2nd (C)Node defining Rotation Axis@or Select An Axis of Rotation from DialogBox";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node To");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			///
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_X)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Y)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Z)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NEGATIVE)->
																		EnableWindow(TRUE);
			///////
			break;
		case 3:
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bClosed	= m_bClosed;
			if(m_bClosed)
				m_dAngSpec = 360.;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
			/////
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			/////
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_LOFT()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Loft Patch:@Provide Number of Curves";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_LoftCurveCount(m_nCurves_U) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
				return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone = FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Curve# %d of %d Total Curves",
				m_nInfoDone+1,m_nCurves_U);
			//////////////////
			strCurr = "Loft Patch: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:	// fall thro'		
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<m_nCurves_U)
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Curve# %d of %d Total Curves",
					m_nInfoDone+1,m_nCurves_U);
				//////////////////
				strCurr = "Loft Patch: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Loft Patch: Provide B.C. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Loft Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	//////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_TENSOR()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Tensor Product Patch:@Provide Number of Nodes";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_TensorNodeCount(m_nNodes_U,m_nNodes_V) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
					return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_NID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh_V	= m_ElPerSeg_V;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio_V	= m_Ratio_V;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("NODE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Node# %d of %d Total Nodes(%dX%d)",
				m_nInfoDone+1,(m_nNodes_U*m_nNodes_V),m_nNodes_U,m_nNodes_V);
			//////////////////
			strCurr = "Tensor Product: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		default:
			if(m_nInfoDone<(m_nNodes_U*m_nNodes_V))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Node# %d of %d Total Nodes(%dX%d)",
					m_nInfoDone+1,(m_nNodes_U*m_nNodes_V),m_nNodes_U,m_nNodes_V);
				//////////////////
				strCurr = "Tensor Product: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Tensor Product: Provide B.C. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Tensor Product Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_GORDON()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Gordon Patch:@Provide Number of Curves";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_GordonCurveCount(m_nCurves_U,m_nCurves_V) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
				return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Curve# %d of %d Total Curves(%dX%d)",
				m_nInfoDone+1,(m_nCurves_U+m_nCurves_V),m_nCurves_U,m_nCurves_V);
			//////////////////
			strCurr = "Gordon: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:	// fall thro'		
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<(m_nCurves_U+m_nCurves_V))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Curve# %d of %d Total Curves(%dX%d)",
				m_nInfoDone+1,(m_nCurves_U+m_nCurves_V),m_nCurves_U,m_nCurves_V);
				//////////////////
				strCurr = "Gordon: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Gordon Patch: Provide Twist Info. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Gordon Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	//////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_COONS()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Coons Method:@Click in The First Curve";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			////////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->
																	SetWindowText("Ist Curve");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
 			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
				////////////////////////////////
			break;
		case 1:
			strCurr = "Patch by Coons Method:@Click in The 2nd Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("2nd Curve");
			break;
		case 2:
			strCurr += "Patch by Coons Method:@Click in The 3rd Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("3rd Curve");
			break;
		case 3:
			strCurr = "Quadrilateral: Select Last Curve@ Triangle: Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Last Curve");
			break;
		case 4:
			strCurr = "Quadrilateral Patch:@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	/////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_DUCT()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//
	CDrCurve*	pSpineCurve;
	CDListMgr*	pCNList;
	BOOL		bClosed;
	int			nBZSegs;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:	// XSectional Curve
			strCurr = "Patch by Ducting:@Click in Cross Sectional Curve";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
			if(m_bTwist)
			{
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
			}
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve		= m_bGenCur;
			////////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. CurveID");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
 			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:	// Spine Curve
			strCurr = "Patch by Ducting:@Click in Spine Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine CurveID");
			break;
		case 2:	// Anchor Node
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Ducting:@Click in Anchor Node";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:	// Twist Distrib
			strCurr = "Patch by Ducting: Provide in Dialog Box@Twist Distribution Factor Info.";
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxTwist	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxTwist>0 && !m_pTwist)
				m_pTwist = new double[m_nMaxTwist]; // deleted at UpdatePDlg_TRUE 
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxTwist;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pTwist	= m_pTwist;
			/////
			break;
		case 4:
			strCurr = "Patch by Ducting: Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
 																	EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																	EnableWindow(FALSE);
			/////
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	/////////////
	return MA_OK;
}

int CPatMouse::UpdatePDlg_FALSE_SWEEP()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//
	CDrCurve*	pSpineCurve;
	CDListMgr*	pCNList;
	BOOL		bClosed;
	int			nBZSegs;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr += "Patch by Sweeping:@Click in Cross Sectional Curve";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
			if(m_bTwist)
			{
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
				((CBasePage*)(GetPatSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
			}
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bGenBCurve		= m_bGenCur;
			////////////////////////////////
//			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_TWISTGROUP)->
//																SetWindowText("Twist");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. CurveID");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
 			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:
			strCurr += "Patch by Sweeping:@Click in Spine Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine Curve");
			break;
		case 2:	// Anchor Node
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Sweeping:@Click in Anchor Node";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:	// Twist Distrib
			strCurr = "Patch by Sweeping: Provide in Dialog Box@Twist Distribution Factor Info.";
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxTwist	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxTwist>0 && !m_pTwist)
				m_pTwist = new double[m_nMaxTwist]; // deleted at UpdatePDlg_TRUE 
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxTwist;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pTwist	= m_pTwist;
			/////
			break;
		case 4:	// Scale Distrib
			strCurr = "Patch by Sweeping: Provide in Dialog Box@Radial Scale Distribution Factor Info.";
			/////
			m_bTwist	= FALSE;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
//			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_TWISTGROUP)->
//																SetWindowText("Radial Scale");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxScale	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxScale>0 && !m_pScale)
				m_pScale = new double[m_nMaxScale]; // deleted at UpdatePDlg_TRUE 
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxScale;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_pTwist	= m_pScale;
			/////
			break;
		case 5:
			strCurr = "Patch by Sweeping: Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
 																	EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																	EnableWindow(FALSE);
			/////
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	//////////////
	return MA_OK;
}
////////////////////////////////////////
void CPatMouse::Serialize(CArchive& ar)
{

	CCurMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" PatMouse:    Storing\n");	
		

	}
	else
	{
		TRACE(" PatMouse:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		
