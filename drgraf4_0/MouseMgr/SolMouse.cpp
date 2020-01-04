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
#include "MSolMgr.h"  
#include "SasePage.h"
#include "CommRsrc.h"	// IDC_ADVANCED
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "DrNode.h"
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
#include "LoftSol_Com.h"	// Loft Curve Compatibility
#include "MI_GangS.h" 
/*
//	Moved to CreOMgr Dll   01/14/98 
#include "MI_SSPN.h" 
//	Moved to CreOMgr Dll   01/14/98 end
*/
////////////////////// 
//#include "Dlg_SolI.h"
//////////////////////
#include "SolMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define MAX_INFO_EXTRUDE	3	// 1 Patches/2 Nodes        
#define MAX_INFO_ROTATE		3	// 1 Patches/2 Nodes           
#define MIN_INFO_TENSOR		4	// 6 Nodes Minimum(2 in U Dir/2 in V Dir/2 in W Dir)           
#define MIN_INFO_GORDON		4	// 6 Patches Minimum(2 in U Dir/2 in V Dir/2 in W Dir)           
#define MIN_INFO_LOFT		2	// 2 Patches Minimum before Rt. Button           
#define MAX_INFO_DUCT		4	// 1 Patch/2 Curves/1 Node        
#define MAX_INFO_SWEEP		5	// 1 Patch/3 Curves/1 Node    
#define MAX_INFO_COONS		4	// 4 or 6 Patches  
///////      
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
///////////////////////////////
/*
#define MA_OK				0
#define MA_ERROR			-1
#define MA_CANCEL			-2
#define MA_GETMOREINFO		-3
*/
////////////////////////////////////
IMPLEMENT_SERIAL(CSolMouse,CSolMouse,1)
/////////////////////////////////////////////////////////////////////////////
CSolMouse::CSolMouse()
{
	m_bEndCondMode		= FALSE;
	m_bEditMode			= FALSE;		// TRUE:User Checking/FALSE:DataInputting
	m_bCornerMode		= FALSE;			// needed for Twist
	/////////////////////////////////////// Reset
	m_bCurveDone		= TRUE;	// 
	m_bPatchDone		= TRUE;	// 
	m_bSolidDone		= TRUE;	// 
	//////////////////////////////
	m_nNodeDone_U		= 0;	// Tensor Product
	m_nCurveDone_U		= 0;	// Gordon Surface
	m_nNodeDone_V		= 0;	// Tensor Product
 	/////////////////////////////////////////// Patch 
	m_nInfoDone			= 0;
	m_nPatchDone		= 0;
	m_nCurveDone		= 0;
	m_nNodeDone			= 0;
	m_nNodes_U			= 0;
	m_nNodes_V			= 0;
	m_nNodes_W			= 0;
	////////////////////////////////////////////
	m_pCornerTwist		= new WORLD[2][2];	// it is full,if TW_USER
	m_SolProc			= SP_SPAWN;	//	arbitrarily other than options offered,
											//	setso it will be created
	/////////////////////////////
	m_nExtruType		= 1;
}

CSolMouse::~CSolMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(GetSolSheet())
	{
		if(GetSolSheet()->m_hWnd)
			GetSolSheet()->DestroyWindow();
		///////////////////
		delete GetSolSheet(); 
		delete [] m_pCornerTwist;
		///////////////////
	}
}

void CSolMouse::InitDlgIn_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pSolInSheet = new CSheet_SOLI("Tensor Product Solid",pWnd,SP_TENSOR);
	GetSolSheet()->m_SolProc = m_SolProc;	//	arbitrarily other than options offered,
											//	setso it will be created
	/////////////////////////////////////////////////
//	pObjectMgr->SetObjInfoID(m_CurrentSolidID,SOLID);
//	ResetVariables_SOL();
}

int CSolMouse::Terminate_SOL(BOOL bError)
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
	m_SolProc = (SOLIDPROC)SP_SPAWN; // something other than Procs Offered!
	GetSolSheet()->m_SolProc = m_SolProc;	// so it will be created
	GetSolSheet()->DestroyWindow();
	////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(SOLID);
	///////////////////////////////////////// delete
	if(bError)
	{
		pList = pObjectMgr->GetObjectList(SOLID);
		nActiveIndex = pList->GetObjectIndex(SOLID, m_CurrentSolidID);
		if(nActiveIndex>=0)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, SOLID);
			m_pCurrentSolid = (CDrSolid*)NULL;
		}
	}
	/////////////////////////////////////// Reset
//	ResetVariables_SOL();
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
}
	
void CSolMouse::ResetVariables_SOL()
{
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	////////////////////////////
	m_bGenCur			= FALSE;
	m_bGenPat			= FALSE;
	/////////////////////////////////////// Set PatchID
	pObjectMgr->
		SetObjInfoID(m_CurrentSolidID,SOLID);
	////////////////////////////
	m_bAllSame			= TRUE;
	m_bEndCondMode		= FALSE;
	m_bEditMode			= FALSE;		// TRUE:User Checking/FALSE:DataInputting
	m_bU				= TRUE;				// TRUE:U_Dir/FALSE:V_Dir
	m_bV				= TRUE;				// TRUE:V_Dir/FALSE:W_Dir
	m_bCornerMode		= FALSE;			// needed for Twist
//	TWIST					m_TwistMethod[2][2];
	/////////////////////////////////////// Reset
	m_bCurveDone		= TRUE;	// 
	m_bPatchDone		= TRUE;	// 
	m_bSolidDone		= TRUE;	// 
	//////////////////////////////
	m_nNodeDone_U		= 0;	// Tensor Product
	m_nNodeDone_V		= 0;	// Tensor Product
	m_nPatchDone_U		= 0;	// Gordon Surface
	m_nPatchDone_V		= 0;	// Gordon Surface
	////////////////////////////
//	((CSasePage*)(GetSolSheet()->GetActivePage()))			= NULL;                                                                                
 	/////////////////////////////////////////// Patch 
	m_nInfoDone			= 0;
	m_nPatchDone		= 0;
	m_nCurveDone		= 0;
	m_nNodeDone			= 0;
    m_LastPatchNum		= 0;		// internal
//	m_SolProc			= SP_COONSHEXA;
	m_SolSubType		= SS_HEXA;
	/////////////////////////////
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
	m_Ratio_W			= 1.0;
	m_ElPerSeg_V		= 1;
	m_ElPerSeg_W		= 1;
	//////////////////////////
	m_pBlendCurve	= NULL;
	m_pBlendCurve_U	= NULL;
	m_pBlendCurve_V	= NULL;
	m_pBlendCurve_W	= NULL;
	m_pCurrentSolid = NULL;
	m_pCornerTwist	= NULL;
	//////////////////////////
	m_PatchList.RemoveAll();
	m_PLatchList.RemoveAll();
	m_CurveList.RemoveAll();
	m_LatchList.RemoveAll();
	//
	m_NodeList.RemoveAll();
	m_ElSegList.RemoveAll();
	/////////////////// Tensor/Gordon
	m_PatchList_U.RemoveAll();
	m_ElSegList_U.RemoveAll();
	m_PLatchList_U.RemoveAll();
	m_EndList_U.RemoveAll();	// if(bClosed_U or Linear_U,Circle_U,
								// parabola_U) EndList_U Empty
	//
	m_PatchList_V.RemoveAll();
	m_ElSegList_V.RemoveAll();
	m_PLatchList_V.RemoveAll();
	m_EndList_V.RemoveAll();	// if(bClosed_V or Linear_V,Circle_V,
								// parabola_V) EndList_V Empty
	//
	m_PatchList_W.RemoveAll();
	m_ElSegList_W.RemoveAll();
	m_PLatchList_W.RemoveAll();
	m_EndList_W.RemoveAll();	// if(bClosed_V or Linear_V,Circle_V,
								// parabola_V) EndList_V Empty
	/////////////////// reset
}

int CSolMouse::LeftDown_SOLID()
{
	return MA_OK;
}

int CSolMouse::ShowSolid(CString* pID)
{

	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	SOLIDPROC		SolProcOld;
	//////////////////////////////////////////////////////////////////// Show NewPatch
	int nActiveIndex,nResult;
	///////////////////////////
	m_pCurrentSolid	= (CDrSolid*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,SOLID));
	m_pCurrentSolid->SetShow(FALSE);	// not quite ready
	//////////////////////////////////////////////////// Fill Mesh
	if(m_SolProc != SP_LOFT && m_SolProc != SP_TENSOR && m_SolProc != SP_GORDON) 
							// for lofting,Tensor & Gordon list is already filled
	{
		m_ElSegList.RemoveAll();
		m_ElSegList.AddTail(m_ElPerSeg);
		if(m_SolProc == SP_ROTATE)
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
		case EDIM_2: 
			nMeshElemDim = 2;	// Grid(2D)
			break;
		default:
			nMeshElemDim = 3;	// Cube, etc(3D)
	}
	m_pCurrentSolid->SetMeshElemDim(nMeshElemDim);					// 1D or 2D or 3D 
	////////////////////////////////////////////////////////////////////// Show
	switch(m_SolProc)
	{
		case SP_EXTRUDE:

			//////////////////////////////////////////////////// Show Patch
			if(m_MI_Sol_I.RBUp_SExtrudeInsert(
							m_PatSubType,
							m_bGenCur,
							m_bGenPat,
							m_nExtruType,
											// 1 = Given: Extrusion Direction Nodes
											// 2 = Given: 3 Lenths (wLen) to Extrude to
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_PatchList,	// given Curves always taken as U-dir
							&m_PLatchList,
							m_ElSegList,
							m_wLen,
							m_dLen,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			break;

		case SP_ROTATE:
			//////////////////////////////////////////////////// Show Solid
			if(m_MI_Sol_I.RBUp_SRotateInsert(
							m_PatSubType,
							m_bGenCur,
							m_bGenPat,
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_PatchList,	// given Curves always taken as U-dir
							&m_PLatchList,
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

		case SP_LOFT2:
			//////////////////////////////////////////////////// Show Solid
			if(m_MI_Sol_I.RBUp_SLoft2Insert(
							m_PatSubType,
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_PatchList,
							&m_PLatchList,
							&m_ElSegList,
							m_Ratio,
							m_pView
							) <0)
				nResult = -1;
			////
			break;

		case SP_DUCT:
			//////////////////////////////////////////////////// Show Solid
			if(m_MI_Sol_I.RBUp_SDuctInsert(
							m_PatSubType,
							m_bGenCur,
							m_bGenPat,
							m_nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_CurveList,	// Spine Curve
							&m_LatchList,
							&m_PatchList,	// XSec. Patch
							&m_PLatchList,
							&m_TwistList,	// Distrib,if nDuctType = 1
							m_TwistMult,
							m_bIncrement,
							m_TwistStart,
							m_pView
							) <0)
				nResult = -1;
			////
			break;

		case SP_SWEEP:
			//////////////////////////////////////////////////// Show Solid
			if(m_MI_Sol_I.RBUp_SSweepInsert(
							m_PatSubType,
							m_bGenCur,
							m_bGenPat,
							m_nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
							m_nScaleType,
										// 1 = Given: Scale Distribution
										// 2 = Given: Scale Increments etc
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_NodeList,	// ist record: pFromIDNode
											// 2nd record: pToIDNode
							&m_CurveList,	// Spine Curve
							&m_LatchList,
							&m_PatchList,	// XSec. Patch
							&m_PLatchList,
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

		case SP_COONS:
			//////////////////////////////////////////////////// Show Solid
			////////////////////////////// OverRide PatProc for COONS Only
			SolProcOld = m_SolProc;
			/////////
			if(m_nPatchDone == 4)
				m_SolProc	= SP_COONSTETRA;
			else
			if(m_nPatchDone == 6)
				m_SolProc	= SP_COONSHEXA;
			//////////////////////////////////////////////////// Show Solid
			if(m_MI_Sol_I.RBUp_SCoonInsert(
							m_SolProc, 
							m_CurrentSolidID,		
							m_pCurrentSolid,
							&m_PatchList,
							&m_PLatchList,
							m_pView
							) <0)
				nResult = -1;
			////////////////////////////// Reset PatProc for COONS Only
			m_SolProc = SolProcOld;
			////
			break;

		default:
			break;
	}
	if(nResult<0)
		return MA_ERROR;
	/////////////////////////////////////////////////////////// Update Patch Topology
	nResult = SolTopo_Update(m_pCurrentSolid,&m_PatchList,&m_CurveList,&m_NodeList);
	if(nResult<0)
		return MA_ERROR;
	/////////////////////////////////////
	return MA_OK;
	////
}

void CSolMouse::Temp_FillOtherInfo_Tensor_SOL()
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

int CSolMouse::SolTopo_Update(CDrSolid* pCurrentSolid,CDListMgr* pCurrentPatList,
						CDListMgr* pCurrentCurList,CDListMgr* pCurrentNodList)
{
	////////////////
	int nResult = 0;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////// Bndry Patches of Current Solid 
	int i,nCount;
	///////////////////
	nCount = pCurrentPatList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrPatch* pPatch	= (CDrPatch*)(pCurrentPatList->GetObject(i));
		////////////////
		if(!pPatch)
		{
			AfxMessageBox(
				"Internal ERROR:\nCSolMouse::SolTopo_Update\n!pPatch");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pSolList = pPatch->GetSolidList();
		///
		nResult = SolTopo_ConnectObjects(pCurrentSolid,pSolList);
		if(nResult<0)
			return nResult;
		///
	}
	/////////////////////////////////////////////////////////// Curve_dependent Connection 
	nCount = pCurrentCurList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrCurve* pCurve	= (CDrCurve*)(pCurrentCurList->GetObject(i));
		////////////////
		if(!pCurve)
		{
			AfxMessageBox(
				"Internal ERROR:\nCSolMouse::SolTopo_Update\n!pCurve");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pSolList = pCurve->GetSolidList();
		///
		nResult = SolTopo_ConnectObjects(pCurrentSolid,pSolList);
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
				"Internal ERROR:\nCSolMouse::SolTopo_Update\n!pNode");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pSolList = pNode->GetSolidList();
		///
		nResult = SolTopo_ConnectObjects(pCurrentSolid,pSolList);
		if(nResult<0)
			return nResult;
		///
	}
	//////////////
	return nResult;
}

int CSolMouse::SolTopo_ConnectObjects(CDrSolid* pCurrentObject,CDListMgr* pList)
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
		CDrSolid* pObject	= (CDrSolid*)(pList->GetObject(j));
		////////////////
		if(!pObject)
		{
			AfxMessageBox(
				"Internal ERROR:\nCSolMouse::SolTopo_ConnectObjects\n!pObject");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		if(pObject != pCurrentObject)	// EXIST in other Solid
		{
			pObjObjList = pCurrentObject->GetSolidList();
			///
			index = pObjObjList->GetObjectIndex(pObject);
			if(index<0)		// not in the list yet
			pObjObjList->InsertObject(pObject);
			////////////////////////////////////// Reciprocate Solid, if necessary
			pObjObjList = pObject->GetSolidList();
			index = pObjObjList->GetObjectIndex(pCurrentObject);
			if(index<0)		// not in the list yet
				pObjObjList->InsertObject(pCurrentObject);
		}
	}
	///////////////
	return nResult;
}			

int CSolMouse:: ElementLeftDown_SOL()
{	
	int nResult;
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
	m_bSolidDone	= FALSE;
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// SOLID
		case S_COONS:

			m_SolProc = SP_COONS;
			break;

		case S_EXTRUDE:				// 

			m_SolProc = SP_EXTRUDE;
			break;

		case S_ROTATE: 

			m_SolProc = SP_ROTATE;
			break;

		case S_LOFT: 

			m_bU		= FALSE;
			m_SolProc	= SP_LOFT;
			break;

		case S_TENSOR: 

			m_SolProc = SP_TENSOR;
			break;

		case S_GORDON: 

			m_SolProc = SP_GORDON;
			break;

		case S_DUCT: 

			m_SolProc = SP_DUCT;
			m_bTwist  = TRUE;
			break;

		case S_SWEEP: 

			m_SolProc = SP_SWEEP;
			m_bTwist  = TRUE;
			if(m_nInfoDone == 3)
				m_bTwist  = FALSE;
			break;
		//////////////////////////////////////////////////
		default:
			break;
	}  
	///////////////////////////
	nResult = LeftDown_SOLID();
	return nResult;
}

void CSolMouse::OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ResetVariables_SOL();
		m_bSolidDone	= FALSE;
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
	if( !(((CSasePage*)(GetSolSheet()->GetActivePage()))->m_hWnd) )
		pWnd->SendMessage(ID_ACTIVE_SOLIN,IDOK);
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
		ElementLeftDown_SOL();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

int CSolMouse::UpdateSDlg_TRUE()
{
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_bGenCur           = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve;
	m_bGenPat           = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch;
//	m_SolProc			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc;
	m_CurrentSolidID	= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID;
	m_CurrentPatchID	= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID;
	m_CurrentCurveID	= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_CID;
	m_CurrentNodeID		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_NID;
	m_ThirdCoord		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dCoord;
	m_ElPerSeg			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh;
	m_Ratio				= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio;
	m_ElPerSeg_V		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_V;
	m_Ratio_V			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_V;
	m_ElPerSeg_W		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_W;
	m_Ratio_W			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_W;
	m_Orient_C			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Orient_C;
	m_Orient_P			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Orient_P;
	m_bClosed			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bClosed;
	///
	m_dLen				= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dLen;
	m_nExtruType		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nExtruType;
	m_wLen				= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_wLen;
	///////////////////////////////////////////////////////////////////////////////////
	////
	m_nTotElems			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nTotElems;
	m_bAxis				= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAxis;
	m_nAxis				= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nAxis;
	m_dAngSpec			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dAngSpec;
	m_bNegative			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bNegative;
	m_SegAngle			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SegAngle;
	m_bAutoSeg			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAutoSeg;
	///////////////////////////////////////////////////// List Inclusion, If Any
	switch(m_SolProc)
	{
		case SP_EXTRUDE:
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

		case SP_ROTATE:
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

		case SP_LOFT:
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

		case SP_TENSOR:
			switch(m_nInfoDone)
			{
				case 0:
				default:
					break;
			}
			break;

		case SP_GORDON:
			switch(m_nInfoDone)
			{
				case 0:
				default:
					break;
			}
			break;

		case SP_COONS:
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

		case SP_DUCT:
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
		case SP_SWEEP:
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

int CSolMouse::UpdateSDlg_FALSE()
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
			((CSasePage*)(GetSolSheet()->GetActivePage()))->
				GetDlgItem(IDC_SID)->EnableWindow(TRUE);
		//////////////////////////////
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_CID		= m_CurrentCurveID;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_NID		= m_CurrentNodeID;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dCoord	= m_ThirdCoord;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_V	= m_ElPerSeg_V;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_V	= m_Ratio_V;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_W	= m_ElPerSeg_W;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_W	= m_Ratio_W;
//		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Orient		= m_Orient;
		/////
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
		if(m_bTwist)
		{
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
		}
		else
		{
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement	= m_bIncScale;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart	= m_ScaleStart;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult		= m_ScaleMult;
		}
		/////
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAxis		= m_bAxis;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nAxis		= m_nAxis;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bNegative	= m_bNegative;
	}
	///////////////////////////////
	switch(m_SolProc)
	{
		case SP_EXTRUDE:

			nResult = UpdateSDlg_FALSE_EXTRUDE();
			break;

		case SP_ROTATE:

			nResult = UpdateSDlg_FALSE_ROTATE();
			break;

		case SP_LOFT:

			nResult = UpdateSDlg_FALSE_LOFT();
			break;

		case SP_TENSOR:

			nResult = UpdateSDlg_FALSE_TENSOR();
			break;

		case SP_GORDON:

			nResult = UpdateSDlg_FALSE_GORDON();
			break;

		case SP_COONS:

			nResult = UpdateSDlg_FALSE_COONS();
			break;

		case SP_DUCT:

			nResult = UpdateSDlg_FALSE_DUCT();
			break;

		case SP_SWEEP:

			nResult = UpdateSDlg_FALSE_SWEEP();
			break;

		default:
			return MA_CANCEL;
	}
	if(nResult == MA_ERROR || nResult == MA_CANCEL)
		return nResult;
	////////////////////////////////////////////////
	if(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetSafeHwnd())
		((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
	////////////////////////////////////////////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
	return MA_OK;
}

int CSolMouse::UpdateTwistDlg_TRUE_SOL()
{
	////////////////////////////////////////////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(TRUE); // From screen
	////////////////////////////////////////////////
	m_bAllSame = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAllSame;
	///
	if(m_bAllSame)	// Tangent Done
	{
		m_TwistMethod = ((CSasePage*)(GetSolSheet()->GetActivePage()))->
							m_TwistMethod[0][0];
		//////////////////
		m_bCornerMode = FALSE;
	}
	/////////////
	return MA_OK;
}

int CSolMouse::UpdateEndDlg_TRUE_SOL()
{
	////////////////////////////////////////////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(TRUE); // From screen
	////////////////////////////////////////////////
	m_bAllSame = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAllSame;
	/////////////
	return MA_OK;
}

int CSolMouse::UpdateEndDlg_FALSE_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////////////////////////////////////////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->m_indexNode_I	= m_indexNode_I;
	((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bU			= m_bU;
	((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bV			= m_bV;
	/////////////////////////////////////////////////////
	if(m_bU)
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nOrder		= m_nBlendOrder_U;
	else
	if(m_bV)
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nOrder		= m_nBlendOrder_V;
	else
		((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nOrder		= m_nBlendOrder_W;
	///////////////////////////////
	switch(m_SolProc)
	{
		case SP_LOFT:

//			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Loft Solid: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Loft Solid: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Loft Solid: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
							GetSolSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetSolSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetSolSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Loft Solid: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;

		case SP_TENSOR:

//			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Tensor Product Solid: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Tensor Product Solid: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Tensor Product Solid: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
							GetSolSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetSolSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetSolSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Tensor Product Solid: ";
						strCurr +="@Ready with other Info.? Click Right Button";
					}
					break;
			}
			break;


		case SP_GORDON:

			///////////////////
			switch(m_nEndCondDone)
			{
				case 0:
					//////
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bEditMode		= m_bEditMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_U		= m_nNodes_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nNode_V		= m_nNodes_V;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pNodeList		= &m_NodeList;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_U	= &m_EndList_U;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pEndList_V	= &m_EndList_V;
					/////////////////////////////////////////////////////////// Now Create
					SwitchToEndCondDlg();
					((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
					/////////////////////
					strCurr = "Gordon Solid: Provide EndConditions";
					strCurr +="@Done with it? Please Click On Update Button";
					break;
				default:

					if(m_bEndCondMode)
					{

						if( (m_nEndCondDone == m_nEndTanNeeded_U) && (m_nEndTanNeeded_V>0) )
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						///
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlg();
						/////
//						m_nEndCondDone<(m_nNodes_U+m_nNodes_V+4/*Tangents and Twists*/))
						strCurr = "Gordon Solid: Provide EndConditions";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					if(m_bCornerMode)
					{	
						if(m_nTwistDone == 0)
							/////////////////////////////////////////////// Create for Title
							SwitchToEndCondDlg();
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlgForTwist();
						////
						strCurr = "Gordon Solid: Provide Twists";
						strCurr +="@Done with it? Please Click On Update Button";
					}
					else
					{
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
							GetSolSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetSolSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetSolSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						strCurr = "Gordon Solid: ";
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
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	/////////////
	return MA_OK;
}

int CSolMouse::UpdateTwistDlg_FALSE_SOL()
{
	CDrGrafFrame*	pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	CString*		pstrNode;
	char*			buf;		
	///////////////////////////////////////////////////////////////////////
	int i,j;
	////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->m_indexNode_I	= m_indexNode_I;
	///////////////////////////////
	switch(m_SolProc)
	{
		case SP_LOFT:
		case SP_TENSOR:
		case SP_GORDON:

			///////////////////
			switch(m_nTwistDone)
			{
				case 0:	// fall thro'
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bCornerMode	= m_bCornerMode;
					((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pCornerTwist	= m_pCornerTwist;
					///
					for(i=0;i<2;i++)
						for(j=0;j<2;j++)
							((CSasePage*)(GetSolSheet()->GetActivePage()))->
									m_TwistMethod[i][j]	= m_TwistMethod;
				default:

					if(m_nTwistDone<4)
					{	
						((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nCornerI		= m_nCornerI;
						((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nCornerJ		= m_nCornerJ;
						/////
						((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlgForTwist();
						/////
						pstrNode	= new CString;
						buf			= pstrNode->GetBuffer(BUFF_SIZE);
						sprintf(buf,"Corner# %d of 4",m_nTwistDone+1);
						//////////////////
						if(m_SolProc == SP_LOFT)
							strCurr = "Loft Solid: Provide Twists at the ";
						else
						if(m_SolProc == SP_TENSOR)
							strCurr = "Tensor Product: Provide Twists at the ";
						else
						if(m_SolProc == SP_GORDON)
							strCurr = "Gordon Solid: Provide Twists at the ";
						strCurr += buf;
						strCurr +="@Done with it? Please Click On Update Button";
						delete pstrNode;
					}
					else
					{
						// Later we will Activate EditMode here by opening both Tensor
						// and EndCondPage
						m_bCornerMode	= FALSE;
						((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bCornerMode = m_bCornerMode;
						/////
						m_bEditMode		= TRUE;
						///////////////////////////////////////
						if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
							GetSolSheet()->DestroyWindow();
						///////////////////////////////////////// Set Tensor Primary Page back
						GetSolSheet()->SetEndCondMode(FALSE);
						///////////////////////////////////////// Create
						if(GetSolSheet()->SetProcPage() != MA_OK) 
						{
							AfxMessageBox(
								"Internal ERROR:\nCSolMouse::UpdateTwistDlg_FALSE()\n!GetSolSheet()->Create()");
							return MA_ERROR;
						}
						///////////////////////////////
						if(m_SolProc == SP_LOFT)
							strCurr = "Loft Solid: ";
						else
						if(m_SolProc == SP_TENSOR)
							strCurr = "Tensor Product Solid: ";
						else
						if(m_SolProc == SP_GORDON)
							strCurr = "Gordon Solid: ";
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
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	/////////////
	return MA_OK;
}
	
int CSolMouse::LeftUp_Sol_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
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

int CSolMouse::OldNode_N_Update_SOLContext(BOOL bCNode,BOOL bDistinct)
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
				if(m_nActiveTool == S_EXTRUDE)
					AfxMessageBox("ERROR:\nDegenerate Extrusion Direction:\nSame Node More than Once!");
				if(m_nActiveTool == S_ROTATE)
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

int CSolMouse::LeftUp_EXTRUDE_SOL(POINT point)
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
		case 1:	m_nPatchDone++;
				nResult = LeftUp_Sol_Patch(point);
				//
				if(nResult <0)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				///////
				return 0;
		case 2:	// fall thro'
		case 3:	m_nNodeDone++;
				nResult = LeftUp_Sol_Node(point,TRUE,TRUE,FALSE);
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

int CSolMouse::LeftUp_ROTATE_SOL(POINT point)
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
		case 1:	m_nPatchDone++;
				nResult = LeftUp_Sol_Patch(point);
				//
				if(nResult <0)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				////////////////////// prepare for Control Nodes
				pObjectMgr->SetNodeInfoID(m_CurrentNodeID,TRUE,pWnd->IsMeshMode());		
				///////
				return 0;
		case 2:	// fall thro'
		case 3:	m_nNodeDone++;
				nResult = LeftUp_Sol_Node(point,TRUE,TRUE,FALSE);
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

int CSolMouse::LeftUp_LOFT_SOL(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nPatchDone++;
				nResult = LeftUp_Sol_Patch(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nPatchDone--;
					return nResult;
				}
				else
				{
					CLoftSol_Compat LC;
					////////////////////////////////////////////////////////// Check Compatibility
					BOOL bResult;
					if(m_PatchList.GetCount()<=1)
						bResult = TRUE;
					else
						bResult = LC.ArePatchesCompatible(&m_PatchList,&m_PLatchList);
					////////////
					if(!bResult)
					{
						////////////////////////////////
						int j;
						CString* pstrNode;
						pstrNode	= new CString;
						LPTSTR buf	= pstrNode->GetBuffer(BUFF_SIZE);
						j = sprintf(buf,   "			*** DATA ERROR ***          \n");
						j += sprintf(buf+j,"Last Patch is Not Compatible with Others\n");
						j += sprintf(buf+j,"Incompatibility could be due to:\n");
						j += sprintf(buf+j,"\tNot All Closed or Open\n");
						j += sprintf(buf+j,"\tNot All having same Number of Bezier Segments\n");
						j += sprintf(buf+j,"\tLatch Option for the Patch may be wrong\n");
						j += sprintf(buf+j,"\tNot All having same Number of Elements per Segment\n");
						//////
						AfxMessageBox(*pstrNode);
						//////////////////
						delete pstrNode;
						///////////////////////// do not accept
						m_nPatchDone--;
						m_PatchList.RemoveTail();
						m_LatchList.RemoveTail();
						////////////////
						return MA_NOHIT;
					}
					//////////////////////////////////////// Update ElSeglist for Tensor Product
					if(m_nPatchDone>1)	// start saving from 2nd Patch of each row
						m_ElSegList_W.AddTail(m_ElPerSeg);
					/////////
					return 0;
				}
	}
	return MA_NOHIT;
}

int CSolMouse::LeftUp_TENSOR_SOL(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nNodeDone++;
				nResult = LeftUp_Sol_Node(point,FALSE,TRUE,TRUE);
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

int CSolMouse::LeftUp_GORDON_SOL(POINT point)
{
	int nResult =0;
	///////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		default:
				m_nPatchDone++;
//				nResult = LeftUp_Pat_Curve(point);	//
				nResult = LeftUp_Sol_Patch(point);	//
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel/Error or NoHit
				{
					m_nPatchDone--;
					return nResult;
				}
				else
				{
					CLoftSol_Compat LC;
					////////////////////////////////////////////////////////// Check Compatibility
					BOOL bResult;
					if(m_PatchList.GetCount()<=1)
						bResult = TRUE;
					else
						bResult = LC.ArePatchesCompatible(&m_PatchList,&m_PLatchList);
					////////////
					if(!bResult)
					{
						////////////////////////////////
						int j;
						CString* pstrNode;
						pstrNode	= new CString;
						LPTSTR buf	= pstrNode->GetBuffer(BUFF_SIZE);
						j = sprintf(buf,   "			*** DATA ERROR ***          \n");
						j += sprintf(buf+j,"Last Patch is Not Compatible with Others\n");
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
						m_nPatchDone--;
						m_PatchList.RemoveTail();
						m_LatchList.RemoveTail();
						////////////////
						return MA_NOHIT;
					}
					//////////////////////////////////////// Copy ElSeglist
					if(m_nInfoDone == 1)	//
					{
						CDrPatch* pPatch = (CDrPatch*)(m_PatchList.GetHead());
						m_ElSegList_U.AddTail(pPatch->GetElperSegList_S());
						m_ElSegList_V.AddTail(pPatch->GetElperSegList_T());
					}
					else
					if(m_nInfoDone == (m_nPatches_U + 1))	//
					{
						CDrPatch* pPatch = (CDrPatch*)m_PatchList.GetHead();
						m_ElSegList_V.AddTail(pPatch->GetElperSegList_S());
						m_ElSegList_W.AddTail(pPatch->GetElperSegList_T());
					}
					/////////
					return 0;
				}
	}
	return -1;
}

int CSolMouse::LeftUp_DUCT_SOL(POINT point)
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
		case 1:	m_nPatchDone++;	// XSec Patch
				nResult = LeftUp_Sol_Patch(point);
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				////////
				return 0;
		case 2:	m_nCurveDone++;	// Spine Curve
				nResult = LeftUp_Sol_Curve(point);	//
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
				nResult = LeftUp_Sol_Node(point,TRUE,TRUE,FALSE);
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

int CSolMouse::LeftUp_SWEEP_SOL(POINT point)
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
		case 1:	m_nPatchDone++;	// XSection Curve
				nResult = LeftUp_Sol_Patch(point);
				//
				if(nResult <0)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				return 0;
		case 2:	m_nCurveDone++;	// Spine Curve
				nResult = LeftUp_Sol_Curve(point);	//
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
				nResult = LeftUp_Sol_Node(point,TRUE,TRUE,FALSE);
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

int CSolMouse::LeftUp_COONS_SOL(POINT point)
{
	int nResult = 0;
	////////////////
	switch(m_nInfoDone)
	{
		case 1:	// fall thro'
		case 2:	// fall thro'
		case 3:	// fall thro'
		case 4:	// fall thro'
		case 5:	// fall thro'
		case 6:	m_nPatchDone++;
				nResult = LeftUp_Sol_Patch(point);
				//
				if(nResult <0 ||nResult == MA_NOHIT)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				return 0;
		default:break;
	}
	return -1;
}

int CSolMouse::LeftUp_Patch_Accept_OtherContext(CPoint point)
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
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrPatch*	pDrPatch;
	int			index;
	///////////////////////////////////////////// See if any Existing Patch Hit
	index = IsObjectHit(PATCH,point,0);
	/////////////////////////////////////////////////////////////// 
	if(index<0)						
		//////////////// Not Hit
		return MA_NOHIT;
	////////////////////////////////
	pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
	ID			= pDrPatch->GetObjectID();
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
		j = sprintf(buf,"***** A Patch Hit ****\n");
		j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
		j = ShowPatchInfo(pDrPatch, buf, j);
		////////////////////////////
		j += sprintf(buf+j,
			"\n\nYES:\t\tAccept This Existing Patch");
		j += sprintf(buf+j,
			"\nNO:\t\tFind Next Matching Patch");
		j += sprintf(buf+j,
			"\nCANCEL:\t\tCancel Selection Process");
		////////////////////////////
		if(!m_bAutoAcceptOn)
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
		else
			nResult = IDYES;
		/////////////
		delete str;
		if(nResult == IDYES)
		{
			///////////////// Accept Old
			m_pCurrentPatch = pDrPatch;
			return MA_ACCEPTOLD;
		}
		else
		if(nResult == IDNO)
		{
			//////////////////////////////////////////////////////// Retry
			index = IsObjectHit(PATCH,point,startIndex);
			/////////////////////////////////////////////////////////////// Right Type
			if(index>=0)
			{
				pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
				ID			= pDrPatch->GetObjectID();
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
				j = sprintf(buf,"***** No More Patch Found ****\n");
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

int CSolMouse::ShowPatchInfo(CDrPatch* pDrPatch, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	//////////////////////////////
	int j = jStart;
	/////////////////////////////// total elems
	ID						= pDrPatch->GetObjectID();
	int nIn					= pDrPatch->GetMaxINodes_S();
	int nElems				= pDrPatch->GetMaxOutPts_S();
	CDListMgr* pList		= pDrPatch->GetINodeList();
	//////////////////////////////
	j += sprintf(buf+j,
			"Solid %s contains:\n\t%d Interpolation Nodes\n\t%d Elements",
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

int CSolMouse::LeftUp_Sol_Patch(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	///////////////////////////////////////////// See if any Existing Curve Hit
	nResult = LeftUp_Patch_Accept_OtherContext(point);
	/////////////////////////////////////////////   
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentPatch->GetObjectID();
			///////////////////////////////////////// matches previous Curve in m_CurveList,INADMISSIBLE
			if(m_nPatchDone>1)
			{
				/////////////////////////////////////////// already exists
   				if((m_PatchList.GetObjectIndex(PATCH,ID) ) >=0)
				{
					BOOL bError = FALSE;
					////////////////////
/*011899
					if(m_nCurveDone>2)
					{	
						if((m_SolProc == SP_COONS) ||(m_SolProc == SP_LOFT) )
							bError = TRUE;
					}
					else
					if(m_nCurveDone>1)
					{
*/					
						if(
							(m_SolProc == SP_COONS) ||(m_SolProc == SP_LOFT) ||
							(m_SolProc == SP_DUCT) ||(m_SolProc == SP_SWEEP) ||
							(m_SolProc == SP_GORDON)
							)
							bError = TRUE;
//					}
					//////////////////
					if(bError)
					{
						AfxMessageBox("Degenerate Solid:\nSame Patch More than Once!");
						return MA_NOHIT;
					}
				}
				/////////////////////////////////////////// Update ElpersegList
				if(m_SolProc == SP_LOFT || m_SolProc == SP_GORDON) // for lofting & Gordon 
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
	PATCHLATCH	NewLat = PL_FIRST_FORWARD;
	if(m_Orient_P == "BACKWARD")
		NewLat = PL_FIRST_BACKWARD;
/*todo later
	//////////////////////////
	if(	m_nCurveDone > 1 && m_SolProc == SP_COONS)	// NOT IST curve
	{
		nResult = CheckCompatibility_COONS_Patch(m_pCurrentCurve,NewLat);
		///
		if(nResult<0)
			return nResult;
	}
*/
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentPatch,PATCH,TRUE);
	//////////////////////////////////////////////////////////////// PatSubType
	m_PatSubType = m_pCurrentPatch->GetPatSubType();
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurSolPatch					= m_pCurrentPatch;
	m_pOldSolPatch					= m_pCurSolPatch;
	m_PatchList.InsertObject(m_pCurSolPatch);
	///
	m_Orient_P	= "FORWARD_1";
	if(NewLat == PL_FIRST_BACKWARD)
		m_Orient = "BACKWARD_1";
	m_PLatchList.AddTail(NewLat);
	/////////
	return MA_OK;
}
/*
int CSolMouse::CheckCompatibility_COONS_Curve(CDrCurve* pDrCurve,CURVELATCH& NewLat)
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
	/////////////
//	OldLat		= m_PatCurveLatch[m_nCurveDone-2];
	////////////////////////////
	LocalPosOld = *(pNode_Old->GetLocalPos());
	//////////////////////////////////////////////////////// Curve New
	pCNList		= pDrCurve->GetCNodeList();
	pNode_Beg	= (CDrNode*)pCNList->GetHead();
	LocalPosB	= *(pNode_Beg->GetLocalPos());
	///////////////////////////////////////////
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
*/

int CSolMouse::LeftUp_Sol_Curve(POINT point)
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
			break;
		case MA_NOHIT:			// Hit Not 
			return MA_NOHIT;
		case MA_CANCEL:		// Cancel
			return MA_CANCEL;
		default:		// Error
			return MA_ERROR;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurSolCurve					= m_pCurrentCurve;
	m_pOldSolCurve					= m_pCurSolCurve;
	m_CurveList.InsertObject(m_pCurSolCurve);
	CURVELATCH cLat = CL_FORWARD;
	if(m_Orient == "BACKWARD")
		cLat = CL_BACKWARD;
	m_LatchList.AddTail(cLat);
	/////////////////////////////////////////////////
	return MA_OK;
}

int CSolMouse::ElementLeftUp_SOL(CPoint point)
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
		case S_EXTRUDE:

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_EXTRUDE)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_EXTRUDE_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;

		case S_ROTATE: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_ROTATE)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdateSDlg_TRUE();
			////////
			if((m_nInfoDone == 3) && m_bAxis)
			{
				m_nInfoDone++;
				m_nNodeDone++;
			}
			else
			{
				//////////////////
				nResult = LeftUp_ROTATE_SOL(point);
				//
				if(nResult<0 || nResult == MA_NOHIT )
				{
					m_nInfoDone--;
					return MA_OK;
				}
			}	
			nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;

		case S_LOFT: 

			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > m_nPatches_U)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_LOFT_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdateSDlg_FALSE();
			///////////////////////////////////////
			if(m_nInfoDone == m_nPatches_U )	// CurveInfoDone,
														// Get ready for EndCond
														// If m_nOrder_U or m_nOrder_V
														// appropriate
			{
				m_bAdvanced = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
				//////////////////////////////////////////////////////////////////// Tensor Product Compatible
				m_LatchList_U.AddTail(&m_LatchList);
				m_LatchList.RemoveAll();
				m_CurveList_U.AddTail(&m_CurveList);
				m_CurveList.RemoveAll();
				////////////////////
				nResult =
				CreateDataNodeList_Solid(&m_NodeList,&m_PatchList_U,&m_PLatchList_U,m_nNodes_U,m_nNodes_V);
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
					GetSolSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					nResult = UpdateEndDlg_FALSE();

				}
				else
					///
					nResult = UpdateSDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;


		case S_TENSOR: 

			/////////////////
			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > (m_nNodes_U*m_nNodes_V))
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdateSDlg_TRUE();
			if(LeftUp_TENSOR_SOL(point)<0)
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
				m_bAdvanced = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CSasePage*)(GetSolSheet()->GetActivePage()))->
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
					GetSolSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					nResult = UpdateEndDlg_FALSE();

				}
				else
					///
					nResult = UpdateSDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;


		case S_GORDON: 

			m_nInfoDone++;
			////////////////
			if(m_nInfoDone > (m_nCurves_U+m_nCurves_V))
			{
				m_nInfoDone--;
				return MA_OK;
			}
			/////////////////////////////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_GORDON_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}
			nResult = UpdateSDlg_FALSE();
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
				m_bAdvanced = ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAdvanced;
				//////////////////
				((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(FALSE);
				//////////////////////////////////////////////////////////////////// Tensor Product Compatible
				m_LatchList_V.AddTail(&m_LatchList);
				m_LatchList.RemoveAll();
				m_CurveList_V.AddTail(&m_CurveList);
				m_CurveList.RemoveAll();
				/////////////////////////////////////////////////////////////////
				nResult = CheckCompatibility_GORDON_Solid(
								&m_PatchList_U,&m_PLatchList_U,&m_PatchList_V,&m_PLatchList_V);
				///
				if(nResult == MA_ERROR)
					return MA_ERROR;
				////////////////////
				m_nNodes_U = m_nCurves_V; 
				m_nNodes_V = m_nCurves_U; 
				//////
				nResult =
				CreateDataNodeList_Solid(&m_NodeList,&m_PatchList_U,&m_PLatchList_U,m_nNodes_U,m_nNodes_V);
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
					GetSolSheet()->ShowWindow(FALSE);
					/////////////////////////////////
					UpdateEndDlg_FALSE();
*/

				}
				else
					///
					nResult = UpdateSDlg_FALSE();
					////////////////
			}
			else
				///
				nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;



		case S_DUCT: 

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_DUCT)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_DUCT_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;

		case S_SWEEP:

			m_nInfoDone++;
			if(m_nInfoDone > MAX_INFO_SWEEP)
			{
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_SWEEP_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			//////
			if(m_nInfoDone == MAX_INFO_SWEEP-1)	// Get Ready for Radial Curve
				m_bTwist = FALSE;
			//////
			nResult = UpdateSDlg_FALSE();
			////////////////
			return MA_OK;

		case S_COONS:		// 
			

			m_nInfoDone++;
			////////////////
			if(m_nCurveDone > MAX_INFO_COONS)
			{
				m_nCurveDone--;
				m_nInfoDone--;
				return MA_OK;
			}
			////////////////
			nResult = UpdateSDlg_TRUE();
			//////////////////
			nResult = LeftUp_COONS_SOL(point); 
			if(nResult<0 || nResult == MA_NOHIT )
			{
				m_nInfoDone--;
				return MA_OK;
			}		
			nResult = UpdateSDlg_FALSE();
			///////
			return MA_OK;
	
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	/////////////
	return MA_OK;
}

int CSolMouse::CheckCompatibility_GORDON_Solid(	
					CDListMgr* pPatchList_U,CList<PATCHLATCH,PATCHLATCH>* pPLatchList_U,
					CDListMgr* pPatchList_V,CList<PATCHLATCH,PATCHLATCH>* pPLatchList_V)
{
	return MA_OK;
}

int CSolMouse::CreateDataNodeList_Solid(CDListMgr* pNodeList,CDListMgr* pPatchList,
								  CList<PATCHLATCH,PATCHLATCH>*	pPLatchList_U,
									int& nNodes_U,int& nNodes_V)
{
/*
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
	for (pos = pCurveList->GetFirstObjectPos(),posL = pPLatchList_U->GetHeadPosition();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pCurve)
			return MA_ERROR;
		CURVELATCH Latch	= pPLatchList_U->GetNext(posL);  
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
			AfxMessageBox("Internal ERROR:\nCSolMouse::CreateDataNodeList_Solid\nnNodes_U != nNodes_UOld");
			Terminate_PAT(TRUE);
			return MA_ERROR;
		}

	}
*/
	////////////
	return MA_OK;
}

int CSolMouse::TENSORTwistDlgUpdate_SOL()
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
	
int CSolMouse::TENSOREndDlgUpdate_SOL()
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

int CSolMouse::IsEndCondNeeded_LOFT_SOL(BOOL& bEndCondMode,
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

int CSolMouse::GetBlendInfo_LOFT_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMSolMgr MSolMgr;
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
		if(MSolMgr.DoModal_Solid_TensorBlend(m_pBlendCurve_V,m_nNodes_U/*# V-Curves*/,2/*dir*/) == IDCANCEL)
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

int CSolMouse::IsEndCondNeeded_TENSOR_SOL(BOOL& bEndCondMode,
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

int CSolMouse::GetBlendInfo_TENSOR_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMSolMgr MSolMgr;
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
		if(MSolMgr.DoModal_Solid_TensorBlend(m_pBlendCurve_U,nCurves,1/*dir*/) == IDCANCEL)
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
		if(MSolMgr.DoModal_Solid_TensorBlend(m_pBlendCurve_V,m_nNodes_U/*# V-Curves*/,2/*dir*/) == IDCANCEL)
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
	
int CSolMouse::GORDONEndDlgUpdate_SOL()
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
		((CSasePage*)(GetSolSheet()->GetActivePage()))->ResetDlgForTwist();
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
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
	return MA_OK;
}

int CSolMouse::IsEndCondNeeded_GORDON_SOL(BOOL& bEndCondMode,
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

int CSolMouse::GetBlendInfo_GORDON_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CMSolMgr MSolMgr;
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
		if(MSolMgr.DoModal_Solid_TensorBlend(m_pBlendCurve_U,m_nCurves_U,1/*dir*/) == IDCANCEL)
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
		if(MSolMgr.DoModal_Solid_TensorBlend(m_pBlendCurve_V,m_nCurves_V,2/*dir*/) == IDCANCEL)
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

int CSolMouse::SwitchToEndCondDlg_SOL()
{
	///////////////////////////////////////
	if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
		GetSolSheet()->DestroyWindow();
	///////////////////////////////////////// Set right page
	GetSolSheet()->m_SolProc = m_SolProc;
	GetSolSheet()->SetEndCondMode(m_bEndCondMode);
	///////////////////////////////////////// Create
	if(GetSolSheet()->SetProcPage() != MA_OK) 
	{
		AfxMessageBox(
			"Internal ERROR:\nCSolMouse::SwitchToEndCondDlg\n!GetSolSheet()->Create()");
		return MA_ERROR;
	}
	////////////
	return MA_OK;
}

int CSolMouse::ShowSolidInfo(CDrSolid* pDrSolid)
{
	int nResult;
	CString ID;
	CString* pID = &ID;
	ID = pDrSolid->GetObjectID();
	//////////////////////////////////////////////////////////////////////
	SOLIDPROC 		SolProc		= pDrSolid->GetSolidProc();
	SOLSUBTYPE 		SolSubType	= pDrSolid->GetSolSubType();
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////
	j = sprintf(buf,"***** A Solid Hit To Spawn ****\n");
	//////////////////////////////////////
	switch(SolProc)
	{
		case SP_EXTRUDE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s was Generated by Extrusion\n",*pID);
			break;

		case SP_ROTATE:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s was Generated by Rotation\n",*pID);
			break;

		case SP_LOFT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\n",*pID);
			break;

		case SP_TENSOR:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s\nGenerated by Tensor Product\n",*pID);
			break;

		case SP_GORDON:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s\nGenerated by Gordon Method\n",*pID);
			break;

		case SP_DUCT:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s\nGenerated by Ducting\n",*pID);
			break;

		case SP_SWEEP:
			//////////////////////////////////////////////////// Show Patch
			j += sprintf(buf+j,"Solid %s\nGenerated by\nSweeping\n",*pID);
			break;

		case SP_COONS:
			//////////////////////////////////////////////////// Show Patch
			if(SolSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Solid %s\nTriangular Coons Type\n",*pID);
			else
			if(SolSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Patch
				j += sprintf(buf+j,"Solid %s\nQuadrilateral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	////////////////////////////
	j += sprintf(buf+j,
		"\nYES:\t\tSpawn This Solid");
	j += sprintf(buf+j,
		"\nNO:\t\tFind Next Solid with Intersecting Trace");
	j += sprintf(buf+j,
		"\nCANCEL:\t\tCancel Selection Process");
	if(!m_bAutoAcceptOn)
		nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	else
		nResult = IDYES;
//	nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
	///////////////
	delete str;
	return nResult;
}

void CSolMouse::OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSolMouse::OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SOL(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CSolMouse::OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case SOLID:
			break;
		////////////////////////////////////////////////// Patch
		default:
			break;
	}  
}

int CSolMouse::RightUp_Premature_SOL()
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
	pID			= &m_CurrentSolidID; 
	//////////////////////////////////////////////////// Check Adequate Curve,or cancel
	switch(m_SolProc)
	{
		case SP_EXTRUDE:

			if(m_nInfoDone<MAX_INFO_EXTRUDE)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Patch & 2 CNodes Needed";
				/////////////////////////
			}
			break;

		case SP_ROTATE:

			if(m_nInfoDone<MAX_INFO_ROTATE)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Patch & 2 CNodes Needed";
				/////////////////////////
			}
			break;

		case SP_LOFT:

			if(m_nInfoDone<MIN_INFO_LOFT)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Patches Needed";
			}
			break;

		case SP_TENSOR:

			if(m_nInfoDone<MIN_INFO_TENSOR)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Nodes Needed in Each Direction";
			}
			break;

		case SP_GORDON:

			if(m_nInfoDone<MIN_INFO_GORDON)
			{
				bPremature = TRUE;
				str = "Minimum of 2 Patches Needed in Each Direction";
			}
			break;

		case SP_DUCT:

			if(m_nInfoDone<4)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Patch, 1 Curve & 1 CNode and\nTwist Info Needed";
			}
			break;

		case SP_SWEEP:

			if(m_nInfoDone<5)
			{
				bPremature = TRUE;
				str = "Minimum of 1 Patch, 1 Curve & 1 CNode,\nTwist and Scaling Info Needed";
			}
			break;

		case SP_COONS:

			if(m_nInfoDone<4)
			{
				bPremature = TRUE;
				str = "Minimum of 4 Patches Needed";
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

int CSolMouse::RightUp_NotAutoAccept_SOL()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDrPatch*	pDrPatch;
	CDrNode*	pDrNode;
	////////////////////////////////////////////////////// Add to DataBase
	CString* pID;
	int i;
	int nAnswer = IDOK;
	////////////////////////////////
	pID			= &m_CurrentSolidID; 
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j;
		//////////
		pDrPatch = (CDrPatch*)(m_PatchList.GetObject(0) );	//Head
		//////////////////////////////////////////////////// Check Adequate Curve,or cancel
		switch(m_SolProc)
		{
			case SP_COONS:


				j = sprintf(buf,"Solid %s contains\n\t%d Coons Curves:\n",
					*pID,m_nPatchDone);

				for(i=0;i<m_nPatchDone;i++)
				{
					pDrPatch = (CDrPatch*)(m_PatchList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s Curve_%d\n",pDrPatch->GetObjectID(),i+1);
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case SP_EXTRUDE:

				j = sprintf(buf,"Solid %s contains\n\tExtrusion Patch:\t%s",
					*pID,pDrPatch->GetObjectID());

				j += sprintf(buf + j,"\n\t%d Direction Nodes:\t",m_nNodeDone);
				for(i=0;i<m_nNodeDone;i++)
				{
					pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
					j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case SP_ROTATE:

				j = sprintf(buf,"Solid %s contains\n\tRotational Patch:\t%s",
					*pID,pDrPatch->GetObjectID());

				j += sprintf(buf + j,"\n\t%d Axis Nodes:\t",m_nNodeDone);
				for(i=0;i<m_nNodeDone;i++)
				{
					pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
					j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case SP_LOFT:

				j = sprintf(buf,"Solid %s contains\n\t%d Lofting Patches:\n",
					*pID,m_nPatchDone);

				for(i=0;i<m_nPatchDone;i++)
				{
					pDrPatch = (CDrPatch*)(m_PatchList.GetObject(i) );
					//////////////////
					switch(i)
					{
						case 0:
							j += sprintf( buf + j, "\t%s To Loft From",pDrPatch->GetObjectID());
							break;
						case 1:
							j += sprintf( buf + j, "\t%s To Loft To",pDrPatch->GetObjectID());
							break;
						default:
							break;
					}
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case SP_TENSOR:

				j = sprintf(buf,"Solid %s consists of\n\t%d Nodes by %d Nodes:\n",
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


			case SP_GORDON:

				j = sprintf(buf,"Solid %s consists of\n\t%d Curves by %d Curves:\n",
					*pID,m_nCurves_U,m_nCurves_V);

				for(i=0;i<m_nCurveDone;i++)
				{
					pDrPatch = (CDrPatch*)(m_PatchList.GetObject(i) );
					//////////////////
					j += sprintf( buf + j, "\t%s ,",pDrPatch->GetObjectID());
				}
				sprintf( buf + j-2, "; ");
				/////////////////////////
				break;


			case SP_DUCT:

				j = sprintf(buf,"Solid %s contains\n\t%d Ducting Patch %d Spine Curve && %d Anchor Node:\n",
					*pID,m_nPatchDone,m_nCurveDone,m_nNodeDone);

				pDrPatch = (CDrPatch*)(m_PatchList.GetObject(0) );
				//////////////////
				j += sprintf( buf + j, "\t%s CrossSectional Patch",pDrPatch->GetObjectID());
				/////////////////////////////////////////////////////
				for(i=0;i<m_nCurveDone;i++)
				{
					CDrCurve* pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					switch(i)
					{
						case 0:
							j += sprintf( buf + j, "\t%s Spine Curve",pDrCurve->GetObjectID());
							break;
						case 1:
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


			case SP_SWEEP:

				j = sprintf(buf,"Solid %s contains\n\t%d Sweeping Patch %d Curves && %d Anchor Node:\n",
					*pID,m_nPatchDone,m_nCurveDone,m_nNodeDone);

				pDrPatch = (CDrPatch*)(m_PatchList.GetObject(0) );
				//////////////////
				j += sprintf( buf + j, "\t%s CrossSectional Patch",pDrPatch->GetObjectID());
				/////////////////////////////////////////////////////
				for(i=0;i<m_nCurveDone;i++)
				{
					CDrCurve* pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
					//////////////////
					switch(i)
					{
						case 0:
							j += sprintf( buf + j, "\t%s Spine Curve",pDrCurve->GetObjectID());
							break;
						case 1:
							j += sprintf( buf + j, "\t%s Twist Curve",pDrCurve->GetObjectID());
							break;
						case 2:
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

void CSolMouse::OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
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
	nResult = UpdateSDlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	nResult = RightUp_Premature_SOL();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_SOL(TRUE);return;
		case MA_CANCEL:Terminate_SOL(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	///////////////////////////////////////////////////////// Not Auto Accept
	nResult = RightUp_NotAutoAccept_SOL();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_SOL(TRUE);return;
		case MA_CANCEL:Terminate_SOL(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	////////////////////////////////////////////////////// Create & Show Patch
	nResult = ShowSolid(&m_CurrentSolidID);
	///////////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_SOL(TRUE);return;
		case MA_CANCEL:Terminate_SOL(TRUE);return;
	}
	/////////////////////////////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	m_bSolidDone	= TRUE;	  //
	m_nInfoDone		= 0;
	////////////////////////////////
	strCurr = "At Your Service!";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	/////////////////////////////////////// Reset: watch out! m_CurrentSolidID is also reset
	nResult = 
		AfxMessageBox("Do You Want to Continue\nwith the Same Procedure",MB_YESNO|MB_ICONQUESTION);
	if(nResult == IDYES)
	{
		/////////////////////
//		ResetVariables_SOL();
		/////////
		nResult = UpdateSDlg_FALSE();
		/////////
	}
	else
		Terminate_SOL(FALSE);
}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CSolMouse::ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID)
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
						case SOLID:			str = "SOLID";					ID = SOLID;
								strCur += "Select a Solid Type";	break;
						case S_TENSOR:		str = "Tensor Product@SOLID";	ID = S_TENSOR; 
								strCur += "A Tensor Product Solid";	break;
						case S_GORDON:		str = "Gordons@SOLID";			ID = S_GORDON;
								strCur += "A Gordons Solid";	break;
						case S_COONS:		str = "Coons@SOLID";			ID = S_COONS;
								strCur += "A Coons Solid";	break;
						case S_ROTATE:		str = "Rotational@SOLID";		ID = S_ROTATE; 
								strCur += "A Solid by Rotation";	break;
						case S_LOFT:		str = "Lofted@SOLID";			ID = S_LOFT; 
								strCur += "A Solid by Lofting";	break;
						case S_EXTRUDE:		str = "Extruded@SOLID";			ID = S_EXTRUDE; 
								strCur += "A Solid by Extrusion";	break;
						case S_DUCT:		str = "Ducted@SOLID";			ID = S_DUCT; 
								strCur += "A Solid by Ducting";	break;
						case S_SWEEP:		str = "Swept@SOLID";			ID = S_SWEEP; 
								strCur += "A Solid by Sweeping";	break;
						case S_FLATPLATE:	str = "Flat@SOLID";				ID = S_FLATPLATE;
								strCur += "A Solid by Tessalation";	break;
						default:			str = "UNKNOWN@SOLID";			ID = UNONE; 		break;
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
	
void CSolMouse::ModeLessOff_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetSolSheet()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_SOLIN,IDOK);
}

void CSolMouse::ModeLessOn_SOL()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	int aTool	= pWnd->GetActiveToolType();
	int aObj	= pWnd->GetActiveObjectType();
	/////////////////////////////////////////////////////////////////////////
		switch(aTool)
		{
			case S_EXTRUDE:
				m_SolProc = SP_EXTRUDE;
				break;

			case S_ROTATE:
				m_SolProc = SP_ROTATE;
				break;

			case S_LOFT:
				m_SolProc = SP_LOFT;
				break;

			case S_TENSOR:
				m_SolProc = SP_TENSOR;
				break;

			case S_GORDON:
				m_SolProc = SP_GORDON;
				break;

			case S_COONS:
				m_SolProc = SP_COONS;
				break;

			case S_DUCT:
				m_SolProc = SP_DUCT;
				break;
			case S_SWEEP:
				m_SolProc = SP_SWEEP;
				break;
			default:
				break;
		}
		/////////////////////////////////////// Reset
//		ResetVariables_SOL();
		////////////////////////////
//		if(!(((CSasePage*)(GetSolSheet()->GetActivePage()))->m_hWnd))

			pWnd->SendMessage(ID_ACTIVE_SOLIN,IDOK);
/*
	}
*/
}

long CSolMouse::CreateorActivateSolIn(UINT wParam, long lParam)
{
	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	SOLIDPROC solProc = GetSolSheet()->m_SolProc; 
	if(GetSolSheet()->m_SolProc != m_SolProc)
	{
		GetSolSheet()->m_SolProc = m_SolProc;
		///////////////////////////////////////
		if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
			GetSolSheet()->DestroyWindow();
		///////////////////////////////////////// Set right page
		GetSolSheet()->m_SolProc = m_SolProc;
		GetSolSheet()->SetEndCondMode(m_bEndCondMode);
		///////////////////////////////////////// Create
		if(GetSolSheet()->SetProcPage() != MA_OK) 
		{
			AfxMessageBox(
				"Internal ERROR:\nCSolMouse::CreateorActivateSolIn\n!GetSolSheet()->Create()");
			return MA_ERROR;
		}
	}
	///////////////////////// Show Dlg and prepare
	nResult = UpdateSDlg_FALSE();
	if(nResult == MA_ERROR || nResult == MA_CANCEL)
		return 0L;
	///////////////////////////////////////////////////////////////// if PatDlg Open
	if(((CSasePage*)(GetSolSheet()->GetActivePage()))->m_hWnd)
	{
		ResetVuBasedVars_SolDlg();
	}
	////////////////////////////////
	return 0L;
}
 
void CSolMouse::ResetVuBasedVars_SolDlg()
{
	if(	m_SolProc == SP_LOFT ||m_SolProc == SP_GORDON ||m_SolProc == SP_COONS ||
		m_bEndCondMode || m_bCornerMode || m_bEditMode)	// for Loft/Tensor/Gordon End Condition
														// doNothing
		return;
	////////////////////////////////////////////////////////////////// Set Info
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////// if NodeDlg Open
	if(((CSasePage*)(GetSolSheet()->GetActivePage()))->m_hWnd)
	{
		CStatic* pCtl;
		pCtl = (CStatic*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER));
		////////////////////////////////////////////////////////
		SwitchThirdCoordHeading(pCtl,
			(UINT)(pWnd->GetActiveViewNumber()) );
	}
}
	 
long CSolMouse::GoodByeSolIn(UINT wParam, long lParam)
{
	
	GetSolSheet()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSolMouse::CancelSolIn(UINT wParam, long lParam)
{
	
	GetSolSheet()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSolMouse::UpdateSolIn(UINT wParam, long lParam)
{
	int nResult;
	////////////
	((CSasePage*)(GetSolSheet()->GetActivePage()))->UpdateData(TRUE);
	//////////////////////////////////////
	if(m_bEndCondMode)	// End Tangents
	{
		m_nEndCondDone++;
		///
		nResult = UpdateEndDlg_TRUE_SOL();
		TENSOREndDlgUpdate_SOL();
		/////////////////////////////////
		nResult = UpdateEndDlg_FALSE_SOL();
		///
		return 0L;
	}
	else
	if(m_bCornerMode)	// Twist
	{
		m_nTwistDone++;
		///
		nResult = UpdateTwistDlg_TRUE_SOL();
		TENSORTwistDlgUpdate_SOL();
		/////////////////////////////////
		nResult = UpdateTwistDlg_FALSE_SOL();
		///
		return 0L;
	}
	//////////////////
	nResult = UpdateSDlg_TRUE();
	//////////////////////////// Special for Pat by Revolution
	if((m_SolProc == SP_ROTATE) && (m_nInfoDone == 2) & m_bAxis)
	{
		nResult = ProcessSolRotAxis();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_SOL(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdateSDlg_FALSE();
		}
	}
	else
	if(((m_SolProc == SP_DUCT)||(m_SolProc == SP_SWEEP)) && (m_nInfoDone == 3))
	{
		nResult = ProcessSolTwist_DUCT_SWEEP();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_SOL(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdateSDlg_FALSE();
		}
	}
	else
	if((m_SolProc == SP_SWEEP) && (m_nInfoDone == 4))
	{
		nResult = ProcessSolScale_SWEEP();
		//
		if(nResult == MA_ERROR)
		{
			Terminate_SOL(TRUE);
			return 0L;
		}
		else
		{
			m_nInfoDone++;
			////////////////////
			UpdateSDlg_FALSE();
		}
	}
	//////////
	return 0L;
}
	 
int CSolMouse::ProcessSolTwist_DUCT_SWEEP()
{
	// Twist Distribution
	//////////////////////
	int i;
	//////////////////////////////////
	m_bTwist			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist;
	if(!m_bTwist)
		return MA_ERROR;
	////////////////////
	m_nMaxTwist			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMaxTwist;
	m_pTwist			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pTwist;
	m_bIncrement		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement;
	m_TwistStart		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart;
	m_TwistMult			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult;
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

int CSolMouse::ProcessSolScale_SWEEP()
{
	// Radius Distribution
	//////////////////////
	int i;
	//////////////////////////////////
	m_bTwist			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist;
	if(m_bTwist)
		return MA_ERROR;
	////////////////////
	m_nMaxScale			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMaxTwist;
	m_pScale			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pTwist;
	m_bIncScale			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement;
	m_ScaleStart		= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart;
	m_ScaleMult			= ((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult;
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

int CSolMouse::ProcessSolRotAxis()
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
			AfxMessageBox("Internal ERROR:\nCSolMouse::ProcessPatRotAxis()\nm_nAxis !=1,2or3");
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

int CSolMouse::UpdateSDlg_FALSE_EXTRUDE()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Solid by Extrusion: Click in@A Patch To Extrude";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nExtruType= m_nExtruType;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dLen		= m_dLen;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_wLen		= m_wLen;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			////////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch = m_bGenPat;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->
																SetWindowText("PATCH");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
			/////
			break;
		case 1:
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Solid by Extrusion: Click in@Ist (C)Node defining Extrusion Direction";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Click in 2nd (C)Node defining Extrusion Dirn.@or Select Extrusion Type 2 from DialogBox";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node To");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
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

int CSolMouse::UpdateSDlg_FALSE_ROTATE()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Solid by Rotation: Click in@A Patch To Rotate";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nTotElems	= m_nTotElems;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAxis		= m_bAxis;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nAxis		= m_nAxis;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bNegative	= m_bNegative;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			////////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch = m_bGenPat;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->
																SetWindowText("Rotng.Patch");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("PATCH");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
 			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
			///
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_X)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Y)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Z)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NEGATIVE)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Solid by Rotation: Click in@Ist (C)Node defining Rotation Axis";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Click in 2nd (C)Node defining Rotation Axis@or Select An Axis of Rotation from DialogBox";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node To");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			///
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_X)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Y)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_AXIS_Z)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NEGATIVE)->
																		EnableWindow(TRUE);
			///////
			break;
		case 3:
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bClosed	= m_bClosed;
			if(m_bClosed)
				m_dAngSpec = 360.;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_dAngSpec	= m_dAngSpec;
			/////
			strCurr = "Ready with other Info.?@Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
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

int CSolMouse::UpdateSDlg_FALSE_LOFT()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMSolMgr MSolMgr;
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
			strCurr = "Loft Solid:@Provide Number of Patches";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MSolMgr.DoModal_Solid_LoftPatchCount(m_nPatches_W) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_SOL(TRUE);
				return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch = m_bGenPat;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("PATCH");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Patch# %d of %d Total Patches",
				m_nInfoDone+1,m_nPatches_W);
			//////////////////
			strCurr = "Loft Solid: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:			
			///
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->EnableWindow(TRUE);
			if(m_Orient_P == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<m_nPatches_W)
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Patch# %d of %d Total Patches",
					m_nInfoDone+1,m_nPatches_W);
				//////////////////
				strCurr = "Loft Solid: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Loft Solid: Provide B.C. for the Iso-Patch.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
					GetSolSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetSolSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetSolSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Loft Solid: ";
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

int CSolMouse::UpdateSDlg_FALSE_TENSOR()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMSolMgr MSolMgr;
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
			strCurr = "Tensor Product Solid:@Provide Number of Nodes";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MSolMgr.DoModal_Solid_TensorNodeCount(m_nNodes_U,m_nNodes_V,m_nNodes_W) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_SOL(TRUE);
					return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_NID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_V	= m_ElPerSeg_V;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_V	= m_Ratio_V;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMesh_W	= m_ElPerSeg_W;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_Ratio_W	= m_Ratio_W;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch = m_bGenPat;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("NODE");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			///
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Node# %d of %d Total Nodes(%dX%dX%d)",
				m_nInfoDone+1,(m_nNodes_U*m_nNodes_V*m_nNodes_W),m_nNodes_U,m_nNodes_V,m_nNodes_W);
			//////////////////
			strCurr = "Tensor Product: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		default:
			if(m_nInfoDone<(m_nNodes_U*m_nNodes_V*m_nNodes_W))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Node# %d of %d Total Nodes(%dX%dX%d)",
					m_nInfoDone+1,(m_nNodes_U*m_nNodes_V*m_nNodes_W),m_nNodes_U,m_nNodes_V,m_nNodes_W);
				//////////////////
				strCurr = "Tensor Product: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Tensor Product: Provide B.C. for the Iso-Patch.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
					GetSolSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetSolSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetSolSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Tensor Product Solid: ";
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

int CSolMouse::UpdateSDlg_FALSE_GORDON()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMSolMgr MSolMgr;
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
			strCurr = "Gordon Solid:@Provide Number of Patches";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MSolMgr.DoModal_Solid_GordonPatchCount(m_nPatches_U,m_nPatches_V,m_nPatches_W) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_SOL(TRUE);
				return MA_CANCEL;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("PATCH");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Patch# %d of %d Total Patches(%dX%dX%d)",
				m_nInfoDone+1,(m_nPatches_U+m_nPatches_V+m_nPatches_W),m_nPatches_U,m_nPatches_V,m_nPatches_W);
			//////////////////
			strCurr = "Gordon: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:			
			///
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<(m_nPatches_U+m_nPatches_V+m_nPatches_W))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Patch# %d of %d Total Patches(%dX%dX%d)",
				m_nInfoDone+1,(m_nPatches_U+m_nPatches_V+m_nPatches_W),m_nPatches_U,m_nPatches_V,m_nPatches_W);
				//////////////////
				strCurr = "Gordon: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Gordon Solid: Provide Twist Info. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetSolSheet()->GetSafeHwnd() != 0)	//  already created
					GetSolSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetSolSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetSolSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCSolMouse::UpdateSDlg_FALSE()\n!GetSolSheet()->Create()");
					return MA_ERROR;
				}
				///////////////////////////////
				strCurr = "Gordon Solid: ";
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

int CSolMouse::UpdateSDlg_FALSE_COONS()
{
//	int nResult;
	////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////
	if(m_Orient_P == "FORWARD")
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient_P == "BACKWARD")
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Solid by Coons Method:@Click in The First Patch";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			////////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve = m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch = m_bGenPat;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("Ist Patch");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
 			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
				////////////////////////////////
			break;
		case 1:
			strCurr = "Patch by Coons Method:@Click in The 2nd Patch";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("2nd Patch");
			break;
		case 2:
			strCurr += "Patch by Coons Method:@Click in The 3rd Patch";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("3rd Patch");
			break;
		case 3:
			strCurr = "Quadrilateral: Select Last Patch@ Triangle: Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Last Patch");
			break;
		case 4:
			strCurr = "Quadrilateral Patch:@Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
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

int CSolMouse::UpdateSDlg_FALSE_DUCT()
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
	if(m_Orient_P == "FORWARD")
		((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:	// XSectional Patch
			strCurr = "Solid by Ducting:@Click in Cross Sectional Patch";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_CID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_NID		= "";
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
			if(m_bTwist)
			{
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
			}
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve		= m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch		= m_bGenPat;
			////////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
 			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(TRUE);
			if(m_Orient_P == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient_P == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:	// Spine Curve
			strCurr = "Solid by Ducting:@Click in Spine Curve";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine CurveID");
 			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_C)))->EnableWindow(TRUE);
			if(m_Orient_C == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient_P == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->SetCurSel(1);//BACKWARD=1
			/////
			break;
		case 2:	// Anchor Node
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Solid by Ducting:@Click in Anchor Node";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:	// Twist Distrib
			strCurr = "Solid by Ducting: Provide in Dialog Box@Twist Distribution Factor Info.";
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxTwist	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxTwist>0 && !m_pTwist)
				m_pTwist = new double[m_nMaxTwist]; // deleted at UpdateSDlg_TRUE 
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxTwist;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pTwist	= m_pTwist;
			/////
			break;
		case 4:
			strCurr = "Solid by Ducting: Ready with other Info.?@Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
 																	EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
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

int CSolMouse::UpdateSDlg_FALSE_SWEEP()
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
	if(m_Orient_P == "FORWARD")
		((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient_P == "BACKWARD")
		((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:	// XSectional Patch
			strCurr += "Solid by Sweeping:@Click in Cross Sectional Patch";
			//////////////////////////////////////////////////////
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_SOL();
				m_bSolidDone = FALSE;	  // 
			}
			//////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SolProc	= m_SolProc;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_SID		= m_CurrentSolidID;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_PID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_CID		= "";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_NID		= "";
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
			if(m_bTwist)
			{
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bIncrement	= m_bIncrement;
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistStart	= m_TwistStart;
				((CSasePage*)(GetSolSheet()->GetActivePage()))->m_TwistMult		= m_TwistMult;
			}
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBCurve		= m_bGenCur;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bGenBPatch		= m_bGenPat;
			////////////////////////////////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_SID)->EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
 			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(TRUE);
			if(m_Orient_P == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient_P == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_P)))->SetCurSel(1);//BACKWARD=1
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(FALSE);
			/////
			break;
		case 1:	// Spine Curve
			strCurr = "Solid by Ducting:@Click in Spine Curve";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_P)))->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine CurveID");
 			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT_C)))->EnableWindow(TRUE);
			if(m_Orient_C == "FORWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient_P == "BACKWARD")
				((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->SetCurSel(1);//BACKWARD=1
			/////
			break;
		case 2:	// Anchor Node
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CComboBox*)(((CSasePage*)(GetSolSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT_C)))->EnableWindow(FALSE);
			//////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Solid by Ducting:@Click in Anchor Node";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:	// Twist Distrib
			strCurr = "Solid by Ducting: Provide in Dialog Box@Twist Distribution Factor Info.";
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxTwist	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxTwist>0 && !m_pTwist)
				m_pTwist = new double[m_nMaxTwist]; // deleted at UpdateSDlg_TRUE 
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxTwist;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pTwist	= m_pTwist;
			/////
			break;
		case 4:	// Scale Distrib
			strCurr = "Solid by Sweeping: Provide in Dialog Box@Radial Scale Distribution Factor Info.";
			/////
			m_bTwist	= FALSE;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_bTwist		= m_bTwist;
//			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_TWISTGROUP)->
//																SetWindowText("Radial Scale");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
																		EnableWindow(TRUE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
																		EnableWindow(TRUE);
			////////
			pSpineCurve = (CDrCurve*)m_CurveList.GetTail();
			pCNList		= pSpineCurve->GetCNodeList();
			bClosed		= pSpineCurve->IsClosed_S();
			nBZSegs		= pSpineCurve->GetMaxBezSegments_S();
			m_nMaxScale	= (bClosed)?nBZSegs:nBZSegs+1; 
			//
			if(m_nMaxScale>0 && !m_pScale)
				m_pScale = new double[m_nMaxScale]; // deleted at UpdateSDlg_TRUE 
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_nMaxTwist = m_nMaxScale;
			((CSasePage*)(GetSolSheet()->GetActivePage()))->m_pTwist	= m_pScale;
			/////
			break;
		case 5:
			strCurr = "Solid by Sweeping: Ready with other Info.?@Click Right Button";
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			/////
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_INCREMENT)->
 																	EnableWindow(FALSE);
			((CSasePage*)(GetSolSheet()->GetActivePage()))->GetDlgItem(IDC_DISTRIB)->
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
void CSolMouse::Serialize(CArchive& ar)
{

	CSolMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SolMouse:    Storing\n");	
		

	}
	else
	{
		TRACE(" SolMouse:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		
