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
#include "NewObjs.h"
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
#include "MI_GangP.h" 
/*
//	Moved to CreOMgr Dll   01/14/98 
#include "MI_PSPN.h" 
//	Moved to CreOMgr Dll   01/14/98 end
*/
////////////////////// 
#include "MPatMgr.h"	// for Dlgs
#include "Dlg_PatI.h"
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
#define MAX_INFO_DUCT		4	// 3 Curves/1 Node        
#define MAX_INFO_SWEEP		5	// 4 Curves/1 Node    
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
	ResetVariables();
}

CPatMouse::~CPatMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pPatInDlg)
	{
		if(m_pPatInDlg->m_hWnd)
			m_pPatInDlg->DestroyWindow();
		///////////////////
		delete m_pPatInDlg; 
		///////////////////
	}
}

void CPatMouse::InitDlgIn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pPatInDlg		= new CDlg_PatI(pWnd,m_PatProc);
}

int CPatMouse::Terminate_PAT(BOOL bError)
{
	if(!bError) // return for now
		return 0;
	/////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
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
	ResetVariables();
	/////////////////// reset
	if(m_pPatInDlg->GetSafeHwnd())
		m_pPatInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
}
	
void CPatMouse::ResetVariables()
{
	/////////////////////////////////////// Reset
	m_bPatchDone		= TRUE;	// 
	m_nNodeDone_U		= TRUE; // Tensor Product
	m_nCurveDone_U		= TRUE;	// Gordon Surface
	////////////////////////////
//	m_pPatInDlg			= NULL;                                                                                
 	/////////////////////////////////////////// Patch 
	m_nInfoDone			= 0;
	m_nCurveDone		= 0;
	m_nNodeDone			= 0;
    m_LastPatchNum		= 0;		// internal
	m_PatProc			= PP_COONSQUAD;
	m_PatSubType		= PS_QUADRILAT;
	m_CurrentPatchID	= "P0";
	/////////////////////////////
	m_PatProc			= PP_COONS;
	m_SegAngle			= 120.;
	m_bAutoSeg			= TRUE;
	m_dAngSpec			= 0.;
	m_dLen				= 1.;
	m_FromID			= "";
	m_ToID				= "";
	//
	m_CurrentNodeID		= "";
	///
	m_bTwist			= TRUE;// Twist or Radius
	m_bIncrement		= FALSE;
	m_TwistStart		= 0.0;
	m_RadiusMult		= 0.0;
	m_bIncRad			= FALSE;
	m_RadStart			= 0.0;
	m_TwistMult			= 0.0;
	m_dLen				= 1.0;
	///////////////////////////////////////////// 
	m_TwistMethod		= TW_ZERO;
	m_nNodes_U			= 0;
	m_nNodes_V			= 0;
	m_Ratio_U			= 1.0;
	m_Ratio_V			= 1.0;
	//////////////////////////
	m_pBlendCurve	= NULL;
	m_pBlendCurve_U	= NULL;
	m_pBlendCurve_V	= NULL;
	m_pCurrentPatch = NULL;
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
	return 0;
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
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_LatchList,
							&m_NodeList,
							&m_ElSegList,
							m_dLen,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			break;

		case PP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpRotateInsert(
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_LatchList,
							&m_NodeList,
							&m_ElSegList,
							m_dLen,
							m_Ratio,
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
				m_PatProc	= PP_LOFTX;
				//////////////////////////////////////////////////// Show Patch
				if(m_MI_Pat_I.RBUpLoftXInsert(
							1/*nCurDir*/,	// Curve Direction:1=U/2=V
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_LatchList,
							&m_ElSegList,
							m_pBlendCurve,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			}
			////////////////////////////// Reset PatProc for COONS Only
			m_PatProc = PatProcOld;
			////
			break;


		case PP_TENSOR:
			//////////////////////////////////////////////////// Temporary
			Temp_FillOtherInfo_Tensor();
			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Pat_I.RBUpTensorInsert(
							FALSE,
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// Tensor Product Nodes
							////////////////
							m_CornerTwist,	// it is full,if TW_USER
							m_TwistMethod,
							////////////////
							m_nNodes_U,
							m_ElSegList_U,
							m_Ratio_U,
							&m_CurveList_U,	// empty
							&m_LatchList_U, // empty
							m_pBlendCurve_U,
							&m_EndList_U,	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
							////////////////
							m_nNodes_V,
							m_ElSegList_V,
							m_Ratio_V,
							&m_CurveList_V,	// empty
							&m_LatchList_V,	// empty
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
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_NodeList,	// Tensor Product Nodes
							////////////////
							m_CornerTwist,	// it is full,if TW_USER
							m_TwistMethod,
							////////////////
							m_nNodes_U,
							m_ElSegList_U,
							m_Ratio_U,
							&m_CurveList_U,	// must be supplied
							&m_LatchList_U, // must be supplied
							m_pBlendCurve_U,
							&m_EndList_U,	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
							////////////////
							m_nNodes_V,
							m_ElSegList_V,
							m_Ratio_V,
							&m_CurveList_V,	// must be supplied
							&m_LatchList_V,	// must be supplied
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
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_NodeList,
							&m_LatchList,
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
							m_CurrentPatchID,		
							m_pCurrentPatch,
							&m_CurveList,
							&m_NodeList,
							&m_LatchList,
							m_TwistMult,
							m_bIncrement,
							m_TwistStart,
							m_RadiusMult,
							m_bIncRad,
							m_RadStart,
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
	int i;
	////////////////
//	m_nNodes_U,
//	m_nNodes_V,
//	m_ElSegList_U,
	/////////////////
	m_Ratio_U	= 1.;
	m_Ratio_V	= 1.;
	////////////////////////////////////////////////////
	BLENDEND BlendEnd;
	BlendEnd.m_BCL = BC_BESSEL;
	BlendEnd.m_BCR = BC_BESSEL;
	///////////////////////////
	for(i=0;i<m_nNodes_V/*Curves_U*/;i++)
		m_EndList_U.AddTail(BlendEnd);
	for(i=0;i<m_nNodes_U;i++)
		m_EndList_V.AddTail(BlendEnd);
	////////////////////////////////////////////////////
	int nElems = 5;
	int nCount_U,nCount_V;
	m_ElSegList_U.RemoveAll();
	m_ElSegList_V.RemoveAll();
	///////////////
	nCount_U = m_ElSegList_U.GetCount(); //is it picking up anything
	//
	nCount_U = m_nNodes_U-1;
	if(m_nNodes_U>2)
		nCount_U = (m_pBlendCurve_U->IsClosed_S())?m_nNodes_U:m_nNodes_U-1;	
	for(i=0;i<nCount_U;i++)
		m_ElSegList_U.AddTail(nElems);
	//////////////////////////////////
	nCount_V = m_nNodes_V-1;
	if(m_nNodes_V>2)
		nCount_V = (m_pBlendCurve_V->IsClosed_S())?m_nNodes_V:m_nNodes_V-1;	
	for(i=0;i<nCount_V;i++)
		m_ElSegList_V.AddTail(nElems);
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

void CPatMouse:: ElementLeftDown_PAT()
{	
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
			LeftDown_PATCH();
			return;

		case P_EXTRUDE:				// 

			m_PatProc = PP_EXTRUDE;
			LeftDown_PATCH();
			return;

		case P_ROTATE: 

			m_PatProc = PP_ROTATE;
			LeftDown_PATCH();
			return;

		case P_LOFT: 

			m_PatProc = PP_LOFT;
			LeftDown_PATCH();
			return;

		case P_TENSOR: 

			m_PatProc = PP_TENSOR;
			LeftDown_PATCH();
			return;

		case P_GORDON: 

			m_PatProc = PP_GORDON;
			LeftDown_PATCH();
			return;

		case P_DUCT: 

			m_PatProc = PP_DUCT;
			m_bTwist  = TRUE;
			LeftDown_PATCH();
			return;

		case P_SWEEP: 

			m_PatProc = PP_SWEEP;
			m_bTwist  = TRUE;
			if(m_nCurveDone == 3)
				m_bTwist  = FALSE;
			LeftDown_PATCH();
			return;
		//////////////////////////////////////////////////
		default:
			break;
	}  

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
	if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
	{
		pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
		////////////////////////////////
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
	////////////////////////////////////
	if(m_bPatchDone)			// Reset
		ResetVariables();
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	///////////////////////////////////////// make sure Dlg is Open
	if( !(GetPatInDlg()->m_hWnd) )
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

void CPatMouse::UpdatePDlg_TRUE()
{
	//////////////////////////////////
	m_pPatInDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
//	m_PatProc			= GetPatInDlg()->m_PatProc;
	m_CurrentPatchID	= GetPatInDlg()->m_PID;
	m_CurrentCurveID	= GetPatInDlg()->m_CID;
	m_CurrentNodeID		= GetPatInDlg()->m_NID;
	m_ThirdCoord		= GetPatInDlg()->m_dCoord;
	m_ElPerSeg			= GetPatInDlg()->m_nMesh;
	m_Ratio				= GetPatInDlg()->m_Ratio;
	m_Orient			= GetPatInDlg()->m_Orient;
	m_bClosed			= GetPatInDlg()->m_bClosed;
	m_dLen				= GetPatInDlg()->m_dLen;
	////
	m_bTwist			= GetPatInDlg()->m_bTwist;
	if(m_bTwist)
	{
		m_bIncrement		= GetPatInDlg()->m_bIncrement;
		m_TwistStart		= GetPatInDlg()->m_TwistStart;
		m_TwistMult			= GetPatInDlg()->m_TwistMult;
	}
	else
	{
		m_bIncRad			= GetPatInDlg()->m_bIncrement;
		m_RadStart			= GetPatInDlg()->m_TwistStart;
		m_RadiusMult		= GetPatInDlg()->m_TwistMult;
	}
	////
	m_SegAngle			= GetPatInDlg()->m_SegAngle;
	m_bAutoSeg			= GetPatInDlg()->m_bAutoSeg;
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
}			

void CPatMouse::UpdatePDlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	if(m_bCNode)
		pObjectMgr->SetNodeInfoID(m_CurrentNodeID,m_bCNode,pWnd->IsMeshMode());		
	//////////////////////////////////////
	if(m_nInfoDone>=1)
		m_pPatInDlg->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
	//////////////////////////////
	GetPatInDlg()->m_PatProc	= m_PatProc;
	GetPatInDlg()->m_PID		= m_CurrentPatchID;
	GetPatInDlg()->m_CID		= m_CurrentCurveID;
	GetPatInDlg()->m_NID		= m_CurrentNodeID;
	GetPatInDlg()->m_dCoord		= m_ThirdCoord;
	GetPatInDlg()->m_nMesh		= m_ElPerSeg;
	GetPatInDlg()->m_Ratio		= m_Ratio;
//	GetPatInDlg()->m_Orient		= m_Orient;
	/////
//moved to PP_ROTATION
//	GetPatInDlg()->m_bClosed	= m_bClosed;
//	if(m_bClosed)
//		m_dLen = 360.;
//	GetPatInDlg()->m_dLen		= m_dLen;
	/////
	GetPatInDlg()->m_bTwist		= m_bTwist;
	if(m_bTwist)
	{
		GetPatInDlg()->m_bIncrement	= m_bIncrement;
		GetPatInDlg()->m_TwistStart	= m_TwistStart;
		GetPatInDlg()->m_TwistMult	= m_TwistMult;
	}
	else
	{
		GetPatInDlg()->m_bIncrement	= m_bIncRad;
		GetPatInDlg()->m_TwistStart	= m_RadStart;
		GetPatInDlg()->m_TwistMult	= m_RadiusMult;
	}
	/////
	GetPatInDlg()->m_SegAngle	= m_SegAngle;
	GetPatInDlg()->m_bAutoSeg	= m_bAutoSeg;
	///////////////////////////////
	switch(m_PatProc)
	{
		case PP_EXTRUDE:

			switch(m_nInfoDone)
			{
				case 0:
					strCurr = "Patch by Extrusion: Click in@A Curve To Extrude";
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Extrn. Curve");
					if(m_Orient == "FORWARD")
 						((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
					else
					if(m_Orient == "BACKWARD")
 						((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
					break;
				case 1:
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Extrusion: Click in@Ist (C)Node defining Extrusion Direction";
					GetPatInDlg()->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 2:
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Extrusion: Click in@2nd (C)Node defining Extrusion Direction";
					GetPatInDlg()->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node To");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 3:
					strCurr = "Ready with other Info.?@Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
					break;
				default:
					break;
			}
			break;


		case PP_ROTATE:

			/////
			GetPatInDlg()->m_bClosed	= m_bClosed;
			if(m_bClosed)
				m_dLen = 360.;
			GetPatInDlg()->m_dLen		= m_dLen;
			/////
			switch(m_nInfoDone)
			{
				case 0:
					strCurr = "Patch by Rotation: Click in@A Curve To Rotate";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Rotnl. Curve");
					if(m_Orient == "FORWARD")
 						((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
					else
					if(m_Orient == "BACKWARD")
 						((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
					break;
				case 1:
					//////
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Rotation: Click in@Ist (C)Node defining Rotation Axis";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 2:
					//////
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Rotation: Click in@2nd (C)Node defining Rotation Axis";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node To");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 3:
					strCurr = "Ready with other Info.?@Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
					break;
				default:
					break;
			}
			break;


		case PP_LOFT:

			if(m_Orient == "FORWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:	// need minimum of 2
				case 1:
					strCurr = "Lofted Patch: Click in Another Curve To Loft";
					break;
				default:
					strCurr = "Lofted Patch: Click in Another Curve To Loft";
					strCurr +="@Or Ready with other Info.? Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Curve");
//					m_pPatInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					break;
			}
			break;


		case PP_TENSOR:

			((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:	// need minimum of 2
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("NODE");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					///
					break;
				default:
					if(m_nInfoDone<(m_nNodes_U*m_nNodes_V))
						strCurr = "Tensor Product Patch: Click in Another Node";
					else
					{
						strCurr = "Tensor Product Patch: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;


		case PP_GORDON:

			if(m_Orient == "FORWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:	// need minimum of 2
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Curve");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
					//////
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
					///
				case 1:
					strCurr = "Gordon Patch: Click in Another Curve";
					break;
				default:
					strCurr = "Gordon Patch: Click in Another Curve";
					strCurr +="@Or Ready with other Info.? Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Curve");
//					m_pPatInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					break;
			}
			break;


		case PP_COONS:

			if(m_Orient == "FORWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:
					strCurr = "Patch by Coons Method:@Click in The First Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Ist Curve");
					break;
				case 1:
					strCurr = "Patch by Coons Method:@Click in The 2nd Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("2nd Curve");
					break;
				case 2:
					strCurr += "Patch by Coons Method:@Click in The 3rd Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("3rd Curve");
					break;
				case 3:
					strCurr = "Quadrilateral: Select Last Curve@ Triangle: Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Last Curve");
					break;
				case 4:
					strCurr = "Quadrilateral Patch:@Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					break;
				default:
					break;
			}
			break;

		case PP_DUCT:

			if(m_Orient == "FORWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:
					strCurr = "Patch by Ducting:@Click in Cross Sectional Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. CurveID");
					break;
				case 1:
					strCurr = "Patch by Ducting:@Click in Spine Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine CurveID");
					break;
				case 2:
					strCurr = "Patch by Ducting:@Click in Twist Distribution Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Twist CurveID");
					break;
				case 3:
					//////
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Ducting:@Click in Anchor Node";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 4:
					strCurr = "Ready with other Info.?@Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
					break;
				default:
					break;
			}
			break;

			
			case PP_SWEEP:

			if(m_Orient == "FORWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
 				((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			///////////////////
			switch(m_nInfoDone)
			{
				case 0:
					strCurr += "Patch by Sweeping:@Click in Cross Sectional Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Curve");
					break;
				case 1:
					strCurr += "Patch by Sweeping:@Click in Spine Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine Curve");
					break;
				case 2:
					strCurr = "Patch by Sweeping:@Click in Twist Distribution Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Twist Curve");
					break;
				case 3:
					strCurr = "Patch by Sweeping:@Click in Radial Distribution Curve";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Radius Curve");
					break;
				case 4:
					//////
					GetPatInDlg()->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					GetPatInDlg()->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					//////
					GetPatInDlg()->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
					GetPatInDlg()->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
					//////
					strCurr = "Patch by Sweeping:@Click in Anchor Node";
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
					GetPatInDlg()->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
					break;
				case 5:
					strCurr = "Ready with other Info.?@Click Right Button";
					m_pPatInDlg->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
					m_pPatInDlg->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
					m_pPatInDlg->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
					break;
				default:
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
	m_pPatInDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
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
			/////////
			if(nResult != MA_OK)
				return nResult;
			//////////////////////////////////////// Update ElSeglist for Tensor Product
			if(m_PatProc == PP_TENSOR)
			{
				if((m_nNodeDone>1) && (m_nNodeDone % m_nNodes_U))	// start saving from 2nd Node of each row
										// ie. for each segment thereon
					m_ElSegList_U.AddTail(m_ElPerSeg);
			}
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
	//////////////////////////////////////// Update ElSeglist for Tensor Product
	if(m_PatProc == PP_TENSOR)
	{
		if((m_nNodeDone>1) && (m_nNodeDone % m_nNodes_U))	// start saving from 2nd Node of each row
															// ie. for each segment thereon
			m_ElSegList_U.AddTail(m_ElPerSeg);
	}
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
				if(nResult <0)		// Cancel
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
				if(nResult <0)		// Cancel
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
				if(nResult <0)		// Cancel
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
				if(nResult <0)		// Cancel
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
				if(nResult <0)		// Cancel
				{
					m_nCurveDone--;
					return nResult;
				}
				return 0;
	}
	return -1;
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
				if(nResult <0)		// Cancel
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;
	}
	return -1;
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
				if(nResult <0)		// Cancel
				{
					m_nCurveDone--;
					return nResult;
				}
				return 0;
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
		case 1:	// fall thro'
		case 2:	// fall thro'
		case 3:	m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0)		// Cancel
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
		case 4:	m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0)		// Cancel
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
		case 1:	// fall thro'
		case 2:	// fall thro'
		case 3:	// fall thro'
		case 4:	m_nCurveDone++;
				nResult = LeftUp_Pat_Curve(point);	//
				//
				if(nResult <0)		// Cancel
				{
					m_nCurveDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				if(m_nInfoDone>3)
				{
					pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				}
				///////
				return 0;
		case 5:	m_nNodeDone++;
				nResult = LeftUp_Pat_Node(point,TRUE,TRUE,FALSE);
				if(nResult <0)		// Cancel
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
				if(nResult <0)		// Cancel
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
	//	nResult = 1		// Accept Old	
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
	//////////////// Cancel
	return -2;
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
	CDListMgr*	pINList;
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
 	pINList		= m_pOldPatCurve->GetINodeList();
	pNode_Old	= (CDrNode*)pINList->GetTail();
	if(OldLat == CL_BACKWARD) 
		pNode_Old	= (CDrNode*)pINList->GetHead();
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
	/////////////
//	OldLat		= m_PatCurveLatch[m_nCurveDone-2];
	////////////////////////////
	LocalPosOld = *(pNode_Old->GetLocalPos());
	//////////////////////////////////////////////////////// Curve New
	pINList		= pDrCurve->GetINodeList();
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	LocalPosB	= *(pNode_Beg->GetLocalPos());
	///////////////////////////////////////////
	nInputType	= pDrCurve->GetInputType();
	bArc		= pDrCurve->IsArcType();
	//
	if(	(nInputType == CIRCLE_BY_ROT) || ((nInputType == CIRCLE_BY_NO3) && !bArc)  ) 
	{
 		pINList		= pDrCurve->GetElemList(); // Auxiliary at End
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	else
		pNode_End	= (CDrNode*)pINList->GetTail();
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

void CPatMouse::ElementLeftUp_PAT(CPoint point)
{                          

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
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_EXTRUDE_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_ROTATE: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_ROTATE)
			{
				m_nInfoDone--;
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_ROTATE_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_LOFT: 

			m_nInfoDone++;
/*
			if(m_nInfoDone > MAX_INFO_LOFT)
			{
				m_nInfoDone--;
				return;
			}
*/
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_LOFT_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_TENSOR: 

			m_nInfoDone++;
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_TENSOR_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;


		case P_GORDON: 

			m_nInfoDone++;
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_GORDON_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_DUCT: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_DUCT)
			{
				m_nInfoDone--;
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_DUCT_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_SWEEP:

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_SWEEP)
			{
				m_nInfoDone--;
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_SWEEP_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			//////
			if(m_nInfoDone == MAX_INFO_SWEEP-2)	// Get Ready for Radial Curve
				m_bTwist = FALSE;
			//////
			UpdatePDlg_FALSE();
			////////////////
			return;

		case P_COONS:		// 
			

			m_nInfoDone++;
			////////////////
			if(m_nCurveDone > MAX_INFO_COONS)
			{
				m_nCurveDone--;
				m_nInfoDone--;
				return;
			}
			////////////////
			UpdatePDlg_TRUE();
			if(LeftUp_COONS_PAT(point)<0)
			{
				m_nInfoDone--;
				return;
			}		
			UpdatePDlg_FALSE();
			///////
			return;
	
		//////////////////////////////////////////////////
		default:  
			break;
	} 
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
	CDListMgr*	pList;
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
				str = "Minimum of 3 Curves & 1 CNode Needed";
			}
			break;

		case PP_SWEEP:

			if(m_nInfoDone<3)
			{
				bPremature = TRUE;
				str = "Minimum of 4 Curves & 1 CNode Needed";
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
			///////////////////////////////////////// delete
			pList = pObjectMgr->GetObjectList(PATCH);
			int nActiveIndex = pList->GetObjectIndex(PATCH, *pID);
			//////////////////////////////////////////////////// Reset
			pObjectMgr->DeleteFromDataBase(nActiveIndex, PATCH);
			/////////////////////////////////////// Reset
//			if(m_bPatchDone)			// Reset
			ResetVariables();
			/////////////////// reset
			if(m_pPatInDlg->GetSafeHwnd())
				m_pPatInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
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
						case 2:
							j += sprintf( buf + j, "\t%s Twist Curve",pDrCurve->GetObjectID());
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
						case 2:
							j += sprintf( buf + j, "\t%s Twist Curve",pDrCurve->GetObjectID());
						case 3:
							j += sprintf( buf + j, "\t%s Radial Scale Curve",pDrCurve->GetObjectID());
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
	int nResult = MA_OK;
	////////////////////
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
	///////////////////////////////////////////////////////// Update Info
	UpdatePDlg_TRUE();
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
	///////////////////////////////////////////////////// Show Patch 
	CMPatMgr MPatMgr;
	/////////////////////
	switch(m_nActiveTool) 
	{

		case P_LOFT:

			if(m_nCurveDone>2)	// need blending info
			{
				/////////////////////////////////////// GetBlending Info.
				m_pBlendCurve = new CDrCurve;	// private
				/////////////////////////////
				if(MPatMgr.DoModal_Patch_LoftX(m_pBlendCurve,m_nCurveDone) == IDCANCEL)
				{
					delete m_pBlendCurve;
					m_pBlendCurve = NULL;
					Terminate_PAT(TRUE);
					return;
				}
				else
				{
					///////////////
					if(m_pBlendCurve->IsClosed_S())
						m_ElSegList.AddTail(m_pBlendCurve->GetElperSegList());	// Closing Elems
				}
			}

		case P_TENSOR:

			m_pBlendCurve_U = new CDrCurve;	// private
			///////////////////////////////////////// U-dir
			if(m_nNodes_U>2)	// need blending info
			{
				/////////////////////////////////////// GetBlending Info.
				if(MPatMgr.DoModal_Patch_LoftX(m_pBlendCurve_U,m_nCurves_U) == IDCANCEL)
				{
					delete m_pBlendCurve_U;
					m_pBlendCurve_U = NULL;
					Terminate_PAT(TRUE);
					return;
				}
				else
				{
					///////////////
					if(m_pBlendCurve_U->IsClosed_S())
						m_ElSegList_U.AddTail(m_pBlendCurve_U->GetElperSegList());	// Closing Elems
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
				/////////////////////////////////////// GetBlending Info.
				if(MPatMgr.DoModal_Patch_LoftX(m_pBlendCurve_V,m_nCurves_V) == IDCANCEL)
				{
					delete m_pBlendCurve_V;
					m_pBlendCurve_V = NULL;
					Terminate_PAT(TRUE);
					return;
				}
				else
				{
					///////////////
					if(m_pBlendCurve_V->IsClosed_S())
						m_ElSegList_V.AddTail(m_pBlendCurve_V->GetElperSegList());	// Closing Elems
				}
			}
			else
			{
				m_pBlendCurve_V->SetCurveType_S(CP_LINEAR);
				m_pBlendCurve_V->SetOrder_S(2);	// Linear	
				m_pBlendCurve_V->SetClosed_S(FALSE);
				m_pBlendCurve_V->SetnDim_S(3);
			}
			/////////
			break;

		case P_GORDON:

			///////////////////////////////////////// U-dir
			if(m_nCurves_U>2)	// need blending info
			{
				/////////////////////////////////////// GetBlending Info.
				m_pBlendCurve_U = new CDrCurve;	// private
				/////////////////////////////
				if(MPatMgr.DoModal_Patch_LoftX(m_pBlendCurve_U,m_nCurves_U) == IDCANCEL)
				{
					delete m_pBlendCurve_U;
					m_pBlendCurve_U = NULL;
					Terminate_PAT(TRUE);
					return;
				}
				else
				{
					///////////////
					if(m_pBlendCurve_U->IsClosed_S())
						m_ElSegList_U.AddTail(m_pBlendCurve_U->GetElperSegList());	// Closing Elems
				}
			}
			///////////////////////////////////////// V-dir
			if(m_nCurves_V>2)	// need blending info
			{
				/////////////////////////////////////// GetBlending Info.
				m_pBlendCurve_V = new CDrCurve;	// private
				/////////////////////////////
				if(MPatMgr.DoModal_Patch_LoftX(m_pBlendCurve_V,m_nCurves_V) == IDCANCEL)
				{
					delete m_pBlendCurve_V;
					m_pBlendCurve_V = NULL;
					Terminate_PAT(TRUE);
					return;
				}
				else
				{
					///////////////
					if(m_pBlendCurve_V->IsClosed_S())
						m_ElSegList_V.AddTail(m_pBlendCurve_V->GetElperSegList());	// Closing Elems
				}
			}
			/////////
			break;
		/////////////
		case P_COONS:	// fall thro
		case P_EXTRUDE:
		case P_ROTATE:
		case P_DUCT:
		case P_SWEEP:
						
			break;
		
		default:  
			return;
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
	/////////////////////////////////////// Set PatchID
	*pID = m_pCurrentPatch->GetObjectID(); 
	if(*pID == m_CurrentPatchID)
		pObjectMgr->SetObjInfoID(m_CurrentPatchID,PATCH);
	/////////////////////////////////////// Reset
	if(m_bPatchDone)			// Reset
		ResetVariables();
	/////////////////// reset
	if(m_pPatInDlg->GetSafeHwnd())
		m_pPatInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	/////////
	UpdatePDlg_FALSE();
	/////////

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
	if(GetPatInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_PATIN,IDOK);
}

void CPatMouse::ModeLessOn_PAT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CMPatMgr MPatMgr;
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
/*	if
	(
		(aTool == P_COONS)		||	(aTool == P_EXTRUDE)	||
		(aTool == P_ROTATE)		||	(aTool == P_LOFT)		||		     
		(aTool == P_TENSOR)		||	(aTool == P_GORDON)		||		     
		(aTool == P_DUCT)		||	(aTool == P_SWEEP)				     
	)
	{
*/
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
				/////////////////////////////////////// GetMatrix Info.
				if(MPatMgr.DoModal_Patch_TensorNodeCount(m_nNodes_U,m_nNodes_V) == IDCANCEL)
				{
					Terminate_PAT(TRUE);
					return;
				}
				////////////////////////
				break;

			case P_GORDON:
				m_PatProc = PP_GORDON;
				/////////////////////////////////////// GetMatrix Info.
				if(MPatMgr.DoModal_Patch_GordonCurveCount(m_nCurves_U,m_nCurves_V) == IDCANCEL)
				{
					Terminate_PAT(TRUE);
					return;
				}
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
		////////////////////////////
//		if(!(GetPatInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_PATIN,IDOK);
/*
	}
*/
}

long CPatMouse::CreateorActivatePatIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	GetPatInDlg()->m_PatProc = m_PatProc;
	///////////////////////////////////////
	if(GetPatInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetPatInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetPatInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetPatInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
	{
		GetPatInDlg()->SetActiveWindow();
		GetPatInDlg()->m_PatProc = m_PatProc;
		GetPatInDlg()->ResetDlg();
	}
	///////////////////////// CurrStat: Show
	switch(m_PatProc)
	{
		case PP_EXTRUDE:
			//////////////////////////////
			strCurr = "Patch by Extrusion: Click in@A Curve To Extrude";
			////
			break;
		case PP_ROTATE:
			//////////////////////////////
			strCurr = "Patch by Rotation: Click in@A Curve To Rotate";
			////
			break;
		case PP_LOFT:
			//////////////////////////////
			strCurr = "Patch by Lofting: Click in@A Curve To Loft";
			////
			break;
		case PP_TENSOR:
			//////////////////////////////
			strCurr = "Patch by Tensor Product: Click in@A Node";
			////
			break;
		case PP_GORDON:
			//////////////////////////////
			strCurr = "Patch by Gordon Method: Click in@A Curve";
			////
			break;
		case PP_DUCT:
			//////////////////////////////
			strCurr = "Patch by Ducting: Click in@A CrossSection Curve";
			////
			break;
		case PP_SWEEP:
			//////////////////////////////
			strCurr = "Patch by Sweeping: Click in@A CrossSection Curve";
			////
			break;
		case PP_COONS:
			//////////////////////////////
			strCurr = "Patch by Coons Method: Click in@First Curve";
			////
			break;
		default:
			break;
	}
	///////////////////////////////////////////////////////////////// if PatDlg Open
	if(GetPatInDlg()->m_hWnd)
	{
		ResetVuBasedVars_NodDlg();
	}
	////////////////////////////////////////////////////////////////// Set Info
	GetPatInDlg()->m_PatProc	= m_PatProc;
	GetPatInDlg()->m_PID		= m_CurrentPatchID;
	GetPatInDlg()->m_CID		= m_CurrentCurveID;
//	GetPatInDlg()->m_CID		= m_CurrentCurveID;
	GetPatInDlg()->m_CID		= "";
//	GetPatInDlg()->m_NID		= m_CurrentNodeID;
	GetPatInDlg()->m_NID		= "";
	GetPatInDlg()->m_nMesh		= m_ElPerSeg;
	GetPatInDlg()->m_Ratio		= m_Ratio;
	//////
//	GetPatInDlg()->m_Orient		= m_Orient;
	if(m_Orient == "FORWARD")
		((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(GetPatInDlg()->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	//////
	GetPatInDlg()->m_bClosed	= m_bClosed;
	GetPatInDlg()->m_dLen		= m_dLen;
	/////
	GetPatInDlg()->m_bTwist		= m_bTwist;
	if(m_bTwist)
	{
		GetPatInDlg()->m_bIncrement	= m_bIncrement;
		GetPatInDlg()->m_TwistStart	= m_TwistStart;
		GetPatInDlg()->m_TwistMult	= m_TwistMult;
	}
	else
	{
		GetPatInDlg()->m_bIncrement	= m_bIncRad;
		GetPatInDlg()->m_TwistStart	= m_RadStart;
		GetPatInDlg()->m_TwistMult	= m_RadiusMult;
	}
	/////
	GetPatInDlg()->m_SegAngle	= m_SegAngle;
	GetPatInDlg()->m_bAutoSeg	= m_bAutoSeg;
	////////////////////////////////
	GetPatInDlg()->UpdateData(FALSE);
	/////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
 
void CPatMouse::ResetVuBasedVars_PatDlg()
{
	////////////////////////////////////////////////////////////////// Set Info
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(GetPatInDlg()->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(GetPatInDlg()->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		SwitchThirdCoordHeading(pCtl,
			(UINT)(pWnd->GetActiveViewNumber()) );
	}
}
	 
long CPatMouse::GoodByePatIn(UINT wParam, long lParam)
{
	
	GetPatInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CPatMouse::CancelPatIn(UINT wParam, long lParam)
{
	
	GetPatInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CPatMouse::UpdatePatIn(UINT wParam, long lParam)
{

	GetPatInDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	UpdatePDlg_TRUE();
	//////////
	return 0L;
}
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

