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
//#include "Def_Lims.h"                    
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_MouseAct.h" // Mouse Action                   
#include "Def_CuPS.h"                    
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
//#include "EDlgMgr.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
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
///////////////////// Static Loads
#include "MSTLMgr.h" 
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
#include "SLDNod.h" 
#include "SLDCur.h" 
#include "SLDPat.h" 
//////////////////////
#include "CommRsrc.h" 
#include "Dlg_StLI.h"
//////////////////////
#include "SLDMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
//////////////////////////////////////////////////// Joint Coord Info
#define MAX_INFO_UNIFORM			1	// 1 Object = Node or Curve or Patch etc			
#define MAX_INFO_JC_DEFAULT			1	// 1 Object = Node or Curve or Patch etc			
#define MAX_INFO_JC_X_FIXEDDIR		3	// 1 Object & 2 Nodes
#define MAX_INFO_JC_X_TAN_CURVE		2	// 1 Object & 1 Curve
#define MAX_INFO_JC_I_TAN_PATCH		2	// 1 Object & 1 Patch
#define MAX_INFO_JC_Z_NOR_PATCH		2	// 1 Object & 1 Patch
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDMouse,CSupMouse,1)
/////////////////////////////////////////////////////////////////////////////
CSLDMouse::CSLDMouse()
{

	///////////////////////
	m_pStLInDlg	= NULL;                                                                                
	/////////////////////////////////////////// Static
	m_Category		= CA_FORCE;
	m_StaLProc		= STL_FORCE;
	m_StaLProcOld	= m_StaLProc;
	m_bTx			= FALSE;
	m_bTy			= FALSE;
	m_bTz			= FALSE;
	m_bRx			= FALSE;
	m_bRy			= FALSE;
	m_bRz			= FALSE;
	///////////////
	m_dUnif = new double[6];
	/////
	for(int i=0;i<6;i++)
		m_dUnif[i]	= 0.0;
	/////////////////////// NonIso
	m_bNonIso		= TRUE;
	m_cid_Parent	= "";
	m_bIncrement	= FALSE;
	m_Orient		= "FORWARD";
	m_dScale		= 0.0;
	m_dStep			= 0.0;
	m_dStart		= 0.0;
	////////////////////////////////
	m_CurrentStLID		= "";
	m_CurrentStLIDOld	= "";
	////////////////////////////////
	m_CurrentStCID		= "StC0";
	m_CurrentStCIDOld	= "StC0";
	////////////////////////////////
	m_CurrentStPID		= "StP0";
	m_CurrentStPIDOld	= "StP0";

}

CSLDMouse::~CSLDMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pStLInDlg)
	{
		if(m_pStLInDlg->m_hWnd)
			m_pStLInDlg->DestroyWindow();
		///////////////////
		delete m_pStLInDlg;                                                                                
		///////////////////
	}
	if(m_dUnif)
		delete [] m_dUnif;                                                                                
}

void CSLDMouse::InitDlgIn_SLD()
{
	///////////////////////////
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pStLInDlg			= new CDlg_StLI(pWnd);                                                                                
}

void CSLDMouse::Init_SLD()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_GenKind			= pWnd->GetCurrentIGenID(); 
	m_pFixDirNode		= NULL;
	m_pTanCurve			= NULL;
	m_pNorPatch			= NULL;
	m_pCurrentStaL		= NULL;
	///////////////////////////
	m_NodeList.RemoveAll();
	////////////////////////
	m_bUniform			= TRUE;
	//
	m_bIso				= FALSE;
	m_bConOrDis			= TRUE;
	//
	m_bNonIso			= FALSE;
	////////////////////////////
	m_bCN_a				= FALSE;
	m_bCN_b				= FALSE;
	////////////////////////
	m_nInfoDone			= 0;
	m_nNodeDone			= 0;
	m_nCurveDone		= 0;
	m_nPatchDone		= 0;
	m_bSuppDone			= TRUE;		// for dragging
	/////////////////////////////////////// Set next SupportID
	if(m_CurrentStLIDOld == m_CurrentStLID) // user didnot change
	{
		pObjectMgr->SetObjInfoID(m_CurrentStLID,STATICLOAD);
		m_CurrentStLIDOld	= m_CurrentStLID;
	}
	/////////////////////////////
	m_ID_CP			= "";
	/////////////////////////////
	m_bTx			= FALSE;
	m_bTy			= FALSE;
	m_bTz			= FALSE;
	m_bRx			= FALSE;
	m_bRy			= FALSE;
	m_bRz			= FALSE;
	/////
	for(int i=0;i<6;i++)
		m_dUnif[i]	= 0.0;
	///////////////////////////////////////////////////////// Jc_Type
	GetStLInDlg()->GetDlgItem(IDC_COMBO_JCTYPE)->EnableWindow(TRUE);	
	/////////////////////////////////////////////////////////
}

void CSLDMouse::Terminate_SLD(BOOL bError)
{
	////////////
	if(!bError)
		return;
	///////////////////////////
	if(m_pCurrentStaL)
	{ 
		delete m_pCurrentStaL;
		m_pCurrentStaL = NULL;
	}
	/////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	///////////////////
	pObjectMgr->SetActiveObjectType(STATICLOAD);
	///////////////////////////////////////// delete
	pList = pObjectMgr->GetObjectList(STATICLOAD);
	nActiveIndex = pList->GetObjectIndex(STATICLOAD, m_CurrentStLID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, STATICLOAD);
		m_pCurrentStaL = (CDrStatic*)NULL;
	}
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return;
}

void CSLDMouse:: ElementLeftDown_SLD()
{	
	GetStLInDlg()->GetDlgItem(IDC_COMBO_JCTYPE)->EnableWindow(FALSE);	
	////////////////////////
	m_bStaLDone	= FALSE;
}

int CSLDMouse::UpdateSLDObjInfo()
{
	m_SLDPat.m_dTx			= m_dUnif[0];			// also for Prs,Thr and LWt
	m_SLDPat.m_dTy			= m_dUnif[1];			// also for Prs,Thr and LWt
	m_SLDPat.m_dTz			= m_dUnif[2];			// also for             LWt
	m_SLDPat.m_dRx			= m_dUnif[3];
	m_SLDPat.m_dRy			= m_dUnif[4];
	m_SLDPat.m_dRz			= m_dUnif[5];
	/////
	m_SLDPat.m_ID_CP		= m_ID_CP;		// Used for NodeBased
	m_SLDPat.m_jcType		= m_jcType;		//	JC_DEFAULT,
	m_SLDPat.m_bUniform		= m_bUniform;	// Uniform distribution
	m_SLDPat.m_bConOrDis	= m_bConOrDis;	// IsoParametric Concentrated or Distributed Input
	//////////////////////////
	m_SLDPat.m_bGravMul		= m_bGravMul;

	m_SLDPat.m_StaLProc		= m_StaLProc;
	/////////////////////////////////////////////////////////
	m_SLDPat.m_bRx			= m_bRx;
	m_SLDPat.m_bRy			= m_bRy;
	m_SLDPat.m_bRz			= m_bRz;
	m_SLDPat.m_bTx			= m_bTx;
	m_SLDPat.m_bTy			= m_bTy;
	m_SLDPat.m_bTz			= m_bTz;
	/////////////////////////////////////////////////////
	if( m_jcType == JC_X_FIXEDDIR)	
	{
		if(m_NodeList.GetCount() != 2)
		{
			AfxMessageBox("Internal Error\nCSLDMouse::UpdateSLDObjInfo\nm_NodeList.GetCount() != 2");
			return MA_ERROR;
		}
		/////////////////////////////
		CDrNode* pNodeA = (CDrNode*)m_NodeList.GetHead();
		CDrNode* pNodeB = (CDrNode*)m_NodeList.GetTail();
		///////
		m_SLDPat.m_aNid			= pNodeA->GetObjectID();				
		m_SLDPat.m_bNid			= pNodeB->GetObjectID();				
		m_SLDPat.m_bCN_a		= pNodeA->IsControlNode();
		m_SLDPat.m_bCN_b		= pNodeB->IsControlNode();
		//////////////////////////////////////////////
		WORLD		NewX;
		pWORLD		pNewX = &NewX;	// 
	
		WORLD		CNodPosA,CNodPosB;		
		////////////////
		CNodPosA			= *(pNodeA->GetLocalPos());
		CNodPosB			= *(pNodeB->GetLocalPos());
		////////////////////////////////////////////////////// Get NewX Direction
		C3DMath Math3D;
		Math3D.Sub3DPts(&CNodPosB,&CNodPosA,pNewX);
		Math3D.Normalize(pNewX,pNewX);
		////////////////////////////////////////////////////// Save
		m_SLDPat.m_SkewDir.x = pNewX->x;
		m_SLDPat.m_SkewDir.y = pNewX->y;
		m_SLDPat.m_SkewDir.z = pNewX->z;
		/////////////////////////////
	}
	/////////////////////////////////////////////////////////// Tan or Nor?
	m_SLDPat.m_bTanCur		= FALSE;				
	m_SLDPat.m_ID_CP		= "";
	///
	if( m_jcType == JC_X_TAN_CURVE)
	{		
		m_SLDPat.m_bTanCur	= TRUE;				
		m_SLDPat.m_ID_CP	= m_pTanCurve->GetObjectID();
	}
	else
	if( m_jcType == JC_I_TAN_PATCH)	
	{
		m_SLDPat.m_bTanPat	= TRUE;				
		m_SLDPat.m_ID_CP		= m_pNorPatch->GetObjectID();
	}
	else
	if( m_jcType == JC_Z_NOR_PATCH)	
	{
		m_SLDPat.m_bNorPat	= TRUE;				
		m_SLDPat.m_ID_CP	= m_pNorPatch->GetObjectID();
	}
	m_SLDPat.m_GenKind		= m_GenKind;
	m_SLDPat.m_jcType		= m_jcType;
	//////////////////////////////////////////////
	m_SLDPat.m_bIso			= m_bIso;
	m_SLDPat.m_bConOrDis	= m_bConOrDis;
	////////////////////////////////////////////// NonIso
	m_SLDPat.m_bNonIso		= m_bNonIso;
	m_SLDPat.m_CID			= m_cid_Parent;
	m_SLDPat.m_bIncrement	= m_bIncrement;
	m_SLDPat.m_Orient		= m_Orient;
	m_SLDPat.m_dScale		= m_dScale;
	m_SLDPat.m_dStep		= m_dStep;
	m_SLDPat.m_dStart		= m_dStart;
	///////////////////////////////////
	return MA_OK;
}

int CSLDMouse::ShowStatic(CString* pID)
{ 
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCur;
	//////////////////////////////////////////////////////////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Node Based										
		case NSL_FORCE:
		case NSL_DISPLACE:
		case NSL_PRESSURE:
		case NSL_THERMAL:
		case NSL_LUMPWT:
			////////////////
			return ShowStatic_Node(pID);
			///

		////////////////////////////////////////////////////// Static: Curve Based										
		case CSL_FORCE:
		case CSL_DISPLACE:
		case CSL_PRESSURE:
		case CSL_THERMAL:
		case CSL_LUMPWT:


			////////////////
			return ShowStatic_Curve(pID);
			///

			break;
		////////////////////////////////////////////////////// Static: Patch Based										
		case PSL_FORCE:
		case PSL_DISPLACE:
		case PSL_PRESSURE:
		case PSL_THERMAL:
		case PSL_LUMPWT:
			
			////////////////
			return ShowStatic_Patch(pID);
			///

		////////////////////////////////////////////////////// Static: Patch Based										
		case SSL_FORCE:
		case SSL_DISPLACE:
		case SSL_PRESSURE:
		case SSL_THERMAL:
		case SSL_LUMPWT:

			////////////////
			return ShowStatic_Solid(pID);
			///

		//////////////////////////////////////////////////
		default:  
			break;
	}
	return MA_ERROR;
}	

int CSLDMouse::ShowStatic_Node(CString* pID)
{
	int nResult = 0;
	///////////////
	nResult = m_SLDPat.ShowNodeStaticLoad(m_pCurrentNode,pID);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("ERROR:\nCSLDMouse::ShowStatic_Node Problem");
		return -1;
	}
	///////////////////////////////
	return MA_OK;
}	 

int CSLDMouse::ShowStatic_Curve(CString* pID)
{
	int nResult = 0;
	///////////////
	nResult = m_SLDPat.ShowCurveStaticLoad(m_pCurrentCurve,pID);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("ERROR:\nCSLDMouse::ShowStatic_Curve Problem");
		return -1;
	}
	///////////////////////////////
	return MA_OK;
}	 

int CSLDMouse::ShowStatic_Patch(CString* pID)
{
	int nResult = 0;
	///////////////
	nResult = m_SLDPat.ShowPatchStaticLoad(m_pCurrentPatch,pID);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("ERROR:\nCSLDMouse::ShowStatic_Patch Problem");
		return -1;
	}
	///////////////////////////////
	return MA_OK;
}

int CSLDMouse::ShowStatic_Solid(CString* pID)
{
	int nResult = MA_ERROR;	// for now
	///////////////
//todo	nResult = m_SLDPat.ShowSolidStaticLoad(m_pCurrentSolid,pID);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("ERROR:\nCSLDMouse::ShowStatic_Solid Problem");
		return -1;
	}
	///////////////////////////////
	return MA_OK;
}


void CSLDMouse::OnEBoxLButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
	////////////////////////////////
	if(m_bStaLDone)			// Reset
	{
		m_bStaLDone		= FALSE;
		////////////////////////
		m_nInfoDone		= 0;
		m_nNodeDone		= 0;
		m_nCurveDone	= 0;
		m_nPatchDone	= 0;
		////////////////////
		m_NodeList.RemoveAll();
	}
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	///////////////////////////////////////// make sure Dlg is Open
	if( !(GetStLInDlg()->m_hWnd) )
	{
		switch(m_StaLProc)
		{
			case STL_FORCE:
				pWnd->SendMessage(ID_ACTIVE_FANDMIN,IDOK);
				break;
			case STL_DISPLACE:
				pWnd->SendMessage(ID_ACTIVE_DANDRIN,IDOK);
				break;
			case STL_THERMAL:
				pWnd->SendMessage(ID_ACTIVE_THERMIN,IDOK);
				break;
			case STL_PRESSURE:
				pWnd->SendMessage(ID_ACTIVE_PRESSIN,IDOK);
				break;
			case STL_LUMPWT:
				pWnd->SendMessage(ID_ACTIVE_LUMPWTIN,IDOK);
				break;
			default:
				break;
		}
	}
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
		ElementLeftDown_SLD();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}
	 
void CSLDMouse::UpdateDlgIn_TRUE()
{
	GetStLInDlg()->UpdateData(TRUE);
	////////////////////////////////////////////////////////////////// Get Info
	////////////////////////////////////////////// NonIso
	m_pCurrentPatch = GetStLInDlg()->m_pDrPatch;
	m_pCurrentCurve = GetStLInDlg()->m_pDrCurve;
	m_Category		= GetStLInDlg()->m_Category;
	//////////////////////////////////////////////
	for(int i=0;i<6;i++)
		m_dUnif[i]	= GetStLInDlg()->m_dUnif[i];
	/////////////////////////////////////////////////
	m_jcType		= GetStLInDlg()->m_jcType;		//	JC_DEFAULT,
	m_CurrentStLID	= GetStLInDlg()->m_LoadID;
	m_bRx			= GetStLInDlg()->m_bRx;
	m_bRy			= GetStLInDlg()->m_bRy;
	m_bRz			= GetStLInDlg()->m_bRz;
	m_bTx			= GetStLInDlg()->m_bTx;
	m_bTy			= GetStLInDlg()->m_bTy;
	m_bTz			= GetStLInDlg()->m_bTz;
	//////
	m_StaLProc		= GetStLInDlg()->m_StaLProc;
	///////////////////////////////////////////
	m_bUniform		= GetStLInDlg()->m_bUniform;
	m_bIso			= GetStLInDlg()->m_bIso;
	m_bConOrDis		= GetStLInDlg()->m_bConOrDis;
	////////////////////////////////////////////// NonIso
	m_bNonIso		= GetStLInDlg()->m_bNonIso;
	m_cid_Parent	= GetStLInDlg()->m_CID;
	m_bIncrement	= GetStLInDlg()->m_bIncrement;
	m_Orient		= GetStLInDlg()->m_Orient;
	m_dScale		= GetStLInDlg()->m_dScale;
	m_dStep			= GetStLInDlg()->m_dStep;
	m_dStart		= GetStLInDlg()->m_dStart;
	/////////////////////////////////////
	return;
}
			
void CSLDMouse::UpdateDlgIn_FALSE()
{
	////////////////////////////////////////////// NonIso
	GetStLInDlg()->m_pDrNode	= m_pCurrentNode;
	GetStLInDlg()->m_pDrCurve	= m_pCurrentCurve;
	GetStLInDlg()->m_pDrPatch	= m_pCurrentPatch;
	GetStLInDlg()->m_Category	= m_Category;
	/////////////////////////////////////////////////
	GetStLInDlg()->m_dUnif		= m_dUnif;
	/////////////////////////////////////////////////////////
	GetStLInDlg()->m_jcType		= m_jcType;		//	JC_DEFAULT,
	///////////////////////////////////////////
	GetStLInDlg()->m_bUniform	= m_bUniform;
	GetStLInDlg()->m_bIso		= m_bIso;
	GetStLInDlg()->m_bConOrDis	= m_bConOrDis;
	GetStLInDlg()->m_GenKind	= m_GenKind;
	///
	GetStLInDlg()->m_bRx		= m_bRx;
	GetStLInDlg()->m_bRy		= m_bRy;
	GetStLInDlg()->m_bRz		= m_bRz;
	GetStLInDlg()->m_bTx		= m_bTx;
	GetStLInDlg()->m_bTy		= m_bTy;
	GetStLInDlg()->m_bTz		= m_bTz;
	///
	GetStLInDlg()->m_LoadID		= m_CurrentStLID;
	GetStLInDlg()->m_StaLProc	= m_StaLProc;
	////////////////////////////////////////////// NonIso
	GetStLInDlg()->m_bNonIso	= m_bNonIso;
	GetStLInDlg()->m_CID		= m_cid_Parent;
	GetStLInDlg()->m_bIncrement	= m_bIncrement;
	GetStLInDlg()->m_Orient		= m_Orient;
	GetStLInDlg()->m_dScale		= m_dScale;
	GetStLInDlg()->m_dStep		= m_dStep;
	GetStLInDlg()->m_dStart		= m_dStart;
	///////////////////////////////////////
}

void CSLDMouse::UpdateStaticDlg_TRUE()
{
	UpdateDlgIn_TRUE();
	///////////////////
	return;
}

void CSLDMouse::CurrentOperationString(UINT CntlID,UINT IGenID,CString& strCur)
{
	//////
	strCur = "Ready for Creation:  ";
	///////////////////////////////////////////////////
	switch(CntlID)
	{
		//////////////////////////////////////// Static
		case STATICLOAD:

			strCur += "Loading/Kinematic BC@";
			strCur += "Select A Load/Kinematic BC Type";	
			return;
		///////////////////////////////////////// RIGID Support
		case FORCE:

			strCur += "Force & Moment@";
			break;
		///////////////////////////////////////// LINSPRING
		case DISPLACE:

			strCur += "Displacement & Rotation@";
			break;
		///////////////////////////////////////// LINSNUBBER
		case PRESSURE:

			strCur += "Pressure Loading@";
			break;
		///////////////////////////////////////// NONSPRING
		case THERMAL:

			strCur += "Thermal Loading@";
			break;
		///////////////////////////////////////// NONSNUBBER
		case LUMPWT:

			strCur += "Lump Weights@";
			break;
		////////
		default:
			return;
	}
	/////////////////////////////////
	strCur += "Click On ";
	switch(IGenID)
	{
		/////////
		case NODE:	strCur += "An Input Node";	break;
		case CURVE:	strCur += "A Curve";		break;
		case PATCH:	strCur += "A Patch";		break;
		case SOLID:	strCur += "A Solid";		break;
		default:	return;
	}
}
			
void CSLDMouse::UpdateStaticDlg_FALSE()
{
	////////////////////////////////////////////// NonIso
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	UINT IGenID				= pWnd->GetCurrentIGenID(); 
	UINT CntlID				= pWnd->GetCurrentCntlID(); 
	CString strCurr; 
	/////////////////////////////////////////////////
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////// CurrStat: Show
	if(m_nInfoDone>=1)
		GetStLInDlg()->GetDlgItem(IDC_LOADID)->EnableWindow(FALSE);
	///////////////////////////////
	switch(m_jcType)
	{
		case JC_DEFAULT:

			switch(m_nInfoDone)
			{
				case 0:

					CurrentOperationString(CntlID,IGenID,strCurr);
					////
					break;

				case 1:
					strCurr = "Ready with other Info.?@Click Right Button";
					///////
					if(m_pStLInDlg->GetSafeHwnd())
						m_pStLInDlg->GetDlgItem(IDC_LOADID)->EnableWindow(TRUE);
					break;
				default:
					break;
			}
			break;


		case JC_X_FIXEDDIR:

			/////
			switch(m_nInfoDone)
			{
				case 0:
					CurrentOperationString(CntlID,IGenID,strCurr);
					break;

				case 1:
					strCurr = "Fixed Direction Skewed Load/Disp Creation@Click in From-Node defining Direction";
					break;

				case 2:
					strCurr = "Fixed Direction Skewed Load/Disp Creation@Click in To-Node defining Direction";
					break;

				case 3:
					strCurr = "Ready with other Info.?@Click Right Button";
					///////
					if(m_pStLInDlg->GetSafeHwnd())
						m_pStLInDlg->GetDlgItem(IDC_LOADID)->EnableWindow(TRUE);
					break;
				default:
					break;
			}
			break;


		case JC_X_TAN_CURVE:

			/////
			switch(m_nInfoDone)
			{
				case 0:
					CurrentOperationString(CntlID,IGenID,strCurr);
					break;

				case 1:
					strCurr = "More than One Curve thro' the Node@Click ON the Curve for X-dir Tangent";
					break;

				case 2:
					strCurr = "Ready with other Info.?@Click Right Button";
					///////
					if(m_pStLInDlg->GetSafeHwnd())
						m_pStLInDlg->GetDlgItem(IDC_LOADID)->EnableWindow(TRUE);
					break;
				default:
					break;
			}
			break;


		case JC_I_TAN_PATCH:
		case JC_Z_NOR_PATCH:

			/////
			switch(m_nInfoDone)
			{
				case 0:
					CurrentOperationString(CntlID,IGenID,strCurr);
					break;

				case 1:
					strCurr = "More than One Patch thro' the Node@Click ON the Patch for Z-dir Normal";
					break;

				case 2:
					strCurr = "Ready with other Info.?@Click Right Button";
					///////
					if(m_pStLInDlg->GetSafeHwnd())
						m_pStLInDlg->GetDlgItem(IDC_LOADID)->EnableWindow(TRUE);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////
	m_pStLInDlg->UpdateData(FALSE); // to screen
	////////////////////////////
}
	
int CSLDMouse::LeftUp_Node_SLDContext(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
{
	// to get tangent defining auxilliary nodes: 
	///////////////////////////////////////////////////////////////////////
	//	bDistinct		=		TRUE	-> Should Not be in m_NODELIST
	//							FALSE	-> DONT CARE
	//	bNoOtherType	=		TRUE	-> Should Not be other than Type dictated by bCNode
	//							FALSE	-> DONT CARE
	///////////////////////////////////////////////////////////////////////
	int nResult = 0;
	CDrNode*	pTempNode;
	CString		strNodeID;
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
						m_bCorINodeOpDone,m_bAutoAcceptOn,&m_pFixDirNode);
	/////////////////////////////////////////////   
	//	MA_CREATE		// Create Anyway
	//	MA_ACCEPTOLD	// Accept Old	
	//	MA_ACCEPTNEW	// Accept New	
	//	MA_NOHIT		// No Hit	
	//	MA_CANCEL		// Cancel Process
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
			nResult = OldNode_N_Update_SLDContext(m_pFixDirNode->IsControlNode(),bDistinct); // right type
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

		case MA_CREATE:			// Hit or Not , Create NEW anyway (m_wLoc Set)
			// next subroutine updates m_pCurrentNode, so store temporarily
			pTempNode = m_pCurrentNode;
			///
			strNodeID = ""; // force naming 
			nResult = NewNode_N_Update_SLDContext(strNodeID,point,TRUE); // desired Type is Control Node
			///
			m_pFixDirNode	= m_pCurrentNode;
			m_pCurrentNode	= pTempNode;
			///////////////
			return nResult;
			/////////
		case MA_CANCEL:		// Cancel
			return MA_CANCEL;
		default:		// Error
			return MA_ERROR;
	}					
}

int CSLDMouse::NewNode_N_Update_SLDContext(CString& NodeID,CPoint point,BOOL bCNode)
{
	/////////////////////////////////////////////////////////// NEW Node
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= -12345;	// Used as an afterthought for creating Node anyway
							// in GangN.CreateNode
							// even if same coords node exists already !!!
							// when nAnyway == -12345
							// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	///
	CDListMgr* pList;
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CDrNode*	pDrNode;
	int			index;
	//////////////////////////////////////////////////////////////////////////// NEW Node
	///////////////////////////////////////////////////// Blank NodeID? provide
	if(NodeID == "")
	{
		/////////////
		UINT uType;
		if(bCNode)
			uType = pWnd->IsMeshMode()?MCNODE:CNODE;
		else
			uType = pWnd->IsMeshMode()?MNODE:NODE;
		///
		pObjectMgr->SetNodeInfoID(NodeID,bCNode,uType);
		/////////
	}
	///////////////////////////////////////////////////// ERROR:Conflicting ID
	pList = pObjectMgr->GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());
	///
	if(pWnd->IsMeshMode())
		index	= pList->GetObjectIndex(FE0D, NodeID);
	else
		index	= pList->GetObjectIndex(NODE, NodeID);
	///
	if(index>=0)						// User selected CONFLICTING pID
	{
		pDrNode = (CDrNode*)(pList->GetObject(index));
		ShowNodeInfo_SameID(pDrNode);
		/////////
		return MA_ERROR;
	}
	////////////////////////////////////////////////////// finally New Node
	if(!m_bAutoAcceptOn)
	{
		/////////////////////////////////////////////////
		CString*	str		= new CString;
		char*		buf		= str->GetBuffer(BUFF_SIZE);
		int j;
		///////////////////////////////// Using GangN
		LPOINT3 MouseWIC = GetMouseWIC();
		WICtoWOR(&MouseWIC,&m_wLoc);	
		//////////////////////////
		WORLD wPt;
		WORtoWOP(&m_wLoc,&wPt);	// to Physical
		//////////////////////////////
		j = sprintf(buf,
			"***** A New Node Creation: *****\nNodeID = %s\nCoordinates:\n\tX = %f\n\tY = %f\n\tZ = %f ",
			NodeID,wPt.x,wPt.y,wPt.z);
		j += sprintf(buf+j,"\n\nAccept This New Node?");
		////////////////////////////
		int nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////
		if(nResult == IDNO)
			return MA_CANCEL;
		//////////////
		delete str;
	}
	//////////////////////////////////
	if(ShowNode(&NodeID,bCNode,nAnyway)<0)
	{
		AfxMessageBox("ERROR:\nCSLDMouse::NewNode_OtherContext\nShowNode Problem");
		return MA_ERROR;
	}
	/////////////////////////////////////////////////////////// Update
	m_NodeList.InsertObject(m_pCurrentNode);
	/////////////
	return MA_OK;
}

int CSLDMouse::OldNode_N_Update_SLDContext(BOOL bCNode,BOOL bDistinct)
{
	///
	if(bDistinct)
	{
		/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
		if(m_nNodeDone>1)
		{
			////////////////////////////////////////////////// already exists
			if(m_NodeList.GetObjectIndex(m_pFixDirNode) >=0)
			{
				m_pFixDirNode = NULL;
				AfxMessageBox("ERROR:\nDegenerate Loading Direction:\nSame Node More than Once!");
				return MA_CANCEL;
			}
		}
	}
	/////////////////////
	m_NodeList.InsertObject(m_pFixDirNode);
	/////////////
	return MA_OK;
}

int CSLDMouse::LeftUp_JC_X_FIXEDDIR_SLD(POINT point)
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
		case 1:	m_nNodeDone++;
				nResult = LeftUp_Node_SLDContext(point,FALSE,TRUE,FALSE/*NoOtherType*/);
				if(nResult <0)		// Cancel
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;

		case 2:	m_nNodeDone++;
				nResult = LeftUp_Node_SLDContext(point,FALSE,TRUE,FALSE);
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

int CSLDMouse::LeftUp_JC_X_TAN_CURVE_SLD(POINT point)
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
				nResult = LeftUp_Curve_Accept_OtherContext(point);
				if(nResult <0)		// Cancel
				{
					m_nCurveDone--;
					return nResult;
				}
				else
				{
					m_pTanCurve = m_pCurrentCurve;
					m_pCurrentCurve = NULL;
					/////////
					return 0;
				}
		default:break;
	}
	return -1;
}

int CSLDMouse::LeftUp_JC_Z_NOR_PATCH_SLD(POINT point)
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
				nResult = LeftUp_Patch_Accept_OtherContext(point);
				if(nResult <0)		// Cancel
				{
					m_nPatchDone--;
					return nResult;
				}
				else
				{
					m_pNorPatch = m_pCurrentPatch;
					m_pCurrentPatch = NULL;
					/////////
					return 0;
				}

		default:break;
	}
	return -1;
}

int CSLDMouse::LeftUp_GetNodeStatic(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////////////////
	int nResult = LeftUp_Node_Accept_NodeBased(point,FALSE);
	///
	switch (nResult)
	{
		case MA_CREATE:
			break;
		case MA_NOHIT:
		case MA_CANCEL:
		case MA_ERROR:
		default:
			return nResult;
	}
	////////////////////////////
	return MA_OK;
}

int CSLDMouse::LeftUp_Node_Accept_NodeBased(CPoint point,BOOL bCNode)
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
		////////////////
		if(bCNode)
			index = IsObjectHit(CNODE,point,0);
		else
			index = IsObjectHit(NODE,point,0);
	}
	/////////////////////////////////////////////////////////////// No Hit
	if(index<0)
		return MA_NOHIT;
	/////////////////////////////////////////////////////////////// Right Type
	pDrNode	= (CDrNode*)pDListMgr->GetObject(index);
	ID		= pDrNode->GetObjectID();
	///////////////////////////////// Node must be connected to a Curve or Patch via curve
	if(m_nInfoDone == 0) // first time
	{
		if(m_jcType == JC_X_TAN_CURVE)
		{
			if(pDrNode->GetCurveList()->IsEmpty())
			return MA_NOHIT;
		}
		else
		if(m_jcType == JC_Z_NOR_PATCH || m_jcType == JC_I_TAN_PATCH) 
		{
			BOOL bConnectedToPatch = FALSE;
			if(	!pDrNode->GetPatchList()->IsEmpty() )
				bConnectedToPatch = TRUE;
			else
			{
				CDListMgr* pList = pDrNode->GetCurveList();
				if(!pList->IsEmpty() )
				{
					for(int k=0;k<pList->GetCount();k++)
					{
						CDrCurve* pCurve = (CDrCurve*)pList->GetObject(k);
						if(!(pCurve->GetPatchList()->IsEmpty()) )
						{
							bConnectedToPatch = TRUE;
							break;
						}	
					}
				}
			}
			//////////////////////////////
			if(bConnectedToPatch == FALSE)
				return MA_NOHIT;
		}
	}
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
			nResult = Show_NodeBased_NodeInfo(pDrNode);
			////////////////////////////////
			if(nResult == MA_CREATE)
				//////////////////////////////////////////////////////// Create
				break;
			if( (nResult == MA_CANCEL) || (nResult == MA_ERROR))
				return nResult;
			else
			if(nResult == MA_SEARCH)
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
					return MA_CANCEL;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
				return MA_CANCEL;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentNode = pDrNode;
	/////////////////
	return MA_CREATE;
	/////////
}
	
int CSLDMouse::Show_NodeBased_NodeInfo(CDrNode* pDrNode)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrNode->GetObjectID();
	WORLD wLoc = *(pDrNode->GetLocalPos());
	WORtoWOP(&wLoc,&wLoc);	// to Physical
	//////////////////////////////
	CDListMgr* pList = pDrNode->GetStaLList();
	///////////////////////////////
	if(!pList->IsEmpty())
	{
		//////////////
		j = sprintf(buf,"***** Selected Node is Already Loaded  *****\n");
		j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
						ID,wLoc.x,wLoc.y,wLoc.z);
		//////////////////////////
		UpdateSLDObjInfo();
		///////////////////
		j = m_SLDPat.ShowInfo_NodeStaticLoad(pDrNode, buf, j,m_CurrentStLID);
		///////
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Nodal Loading");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Node with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_CREATE;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Nodal Loading");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Node");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Node with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			else
			if(nResult == IDCANCEL)
				nResult = MA_CREATE;
			/////////////
		}
	}
	else
	{
		//////////////////////////////
		j = sprintf(buf,"***** Existing Node Selected *****\n");
		j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f ",
						ID,wLoc.x,wLoc.y,wLoc.z);
		////////////////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
					"\n\nYES:\tAccept This Existing Node");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_CANCEL;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Node");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Node");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			/////////////
		}
	}
	//////////////
	return nResult;
}
	
int CSLDMouse::Show_CurveBased_CurveInfo(CDrCurve* pDrCurve)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrCurve->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrCurve->GetStaLList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Curve is Already Loaded  *****\n");
		j += sprintf(buf+j,"\nCurveID = %s ",ID);
		//////////////////////////
		UpdateSLDObjInfo();
		///////////////////
		j = m_SLDPat.ShowInfo_CurveStaticLoad(pDrCurve, buf, j,m_CurrentStLID);
		///////
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing CurveBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Curve with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_CREATE;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing CurveBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Curve");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Curve with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			else
			if(nResult == IDCANCEL)
				nResult = MA_CREATE;
			/////////////
		}
	}
	else
	{
		//////////////////////////////
		j = sprintf(buf,"***** Existing Curve Selected *****\n");
		j += sprintf(buf+j,"\nCurveID = %s ",ID);
		////////////////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
					"\n\nYES:\tAccept This Existing Curve");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_CANCEL;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Curve");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Curve");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			/////////////
		}
	}
	//////////////
	return nResult;
}
int CSLDMouse::LeftUp_GetCurveStatic(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreateNodeLinSup
						// even if same coords node exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	int nResult = LeftUp_Curve_Accept(point);
	///
	switch (nResult)
	{
		case MA_CREATE:
			nAnyway	= -12345;	// Create Anyway
			break;
		case MA_NOHIT:
		case MA_CANCEL:
		case MA_ERROR:
		default:
			return nResult;
	}
	////////////////////////////
	return MA_OK;
}

int CSLDMouse::LeftUp_Curve_Accept(CPoint point)
{
	// Curve-Based Support Curve
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrCurve*	pDrCurve;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Curve Hit
	if(m_ProbLim == PDL_TWO)
		index = IsObjectHit(CURVE,point,0);
	else
	if(m_ProbLim == PDL_THREE)
		index = IsObjectHit(CURVE,point,0);
	/////////////////////////////////////////////////////////////// No Hit
	if(index<0)
		return MA_NOHIT;
	/////////////////////////////////////////////////////////////// Right Type
	pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
	ID			= pDrCurve->GetObjectID();
	///////////////////////////////// Node must be connected to a Curve or Patch
	if((pDrCurve->GetPatchList()->IsEmpty())  && (m_nInfoDone == 0)) // first time
	{
		if(m_jcType == JC_Z_NOR_PATCH || m_jcType == JC_I_TAN_PATCH)
			return MA_NOHIT;
	}
	/////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrCurve,CURVE,TRUE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	int nResult;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		/////////////
		for(;;)
		{
			nResult = Show_CurveBased_CurveInfo(pDrCurve);
			////////////////////////////////
			if(nResult == MA_CREATE)
				//////////////////////////////////////////////////////// Create
				break;
			if( (nResult == MA_CANCEL) || (nResult == MA_ERROR))
				return nResult;
			else
			if(nResult == MA_SEARCH)
			{
				//////////////////////////////////////////////////////// Retry
				if(m_ProbLim == PDL_TWO)
					index = IsObjectHit(CURVE,point,startIndex);
				if(m_ProbLim == PDL_THREE)
					index = IsObjectHit(CURVE,point,startIndex);
				/////////////////////////////////////////////////////////////// Right Type
				if(index>=0)
				{
					pDrCurve	= (CDrCurve*)pDListMgr->GetObject(index);
					ID		= pDrCurve->GetObjectID();
					/////////////////////////////////////////////
					pObjectMgr->ShowObject_On_Off(pDrCurve,CURVE,TRUE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
					////////////////
					return MA_CANCEL;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
				return MA_CANCEL;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentCurve = pDrCurve;
	/////////////////
	return MA_CREATE;
	/////////
}
	
int CSLDMouse::Show_PatchBased_PatchInfo(CDrPatch* pDrPatch)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrPatch->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrPatch->GetStaLList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Patch is Already Loaded  *****\n");
		j += sprintf(buf+j,"\nPatchID = %s ",ID);
		//////////////////////////
		UpdateSLDObjInfo();
		///////////////////
		j = m_SLDPat.ShowInfo_PatchStaticLoad(pDrPatch, buf, j,m_CurrentStLID);
		///////
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing PatchBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Patch with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_CREATE;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing PatchBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Patch");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Patch with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			else
			if(nResult == IDCANCEL)
				nResult = MA_CREATE;
			/////////////
		}
	}
	else
	{
		//////////////////////////////
		j = sprintf(buf,"***** Existing Patch Selected *****\n");
		j += sprintf(buf+j,"\nPatchID = %s ",ID);
		////////////////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
					"\n\nYES:\tAccept This Existing Patch");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_CANCEL;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Patch");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Patch");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			/////////////
		}
	}
	//////////////
	return nResult;
}

int CSLDMouse::LeftUp_GetPatchStatic(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	int nAnyway	= 0;	// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreateNodeLinSup
						// even if same coords node exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowNode to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	int nResult = LeftUp_Patch_Accept(point);
	///
	switch (nResult)
	{
		case MA_CREATE:
			nAnyway	= -12345;	// Create Anyway
			break;
		case MA_NOHIT:
		case MA_CANCEL:
		case MA_ERROR:
		default:
			return nResult;
	}
	////////////////////////////
	return MA_OK;
}

int CSLDMouse::LeftUp_Patch_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrPatch*	pDrPatch;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_ProbLim == PDL_TWO)
		index = IsObjectHit(PATCH,point,0);
	else
	if(m_ProbLim == PDL_THREE)
		index = IsObjectHit(PATCH,point,0);
	/////////////////////////////////////////////////////////////// No Hit
	if(index<0)
		return MA_NOHIT;
	/////////////////////////////////////////////////////////////// Right Type
	pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
	ID			= pDrPatch->GetObjectID();
	/////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrPatch,PATCH,TRUE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	int nResult;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		/////////////
		for(;;)
		{
			nResult = Show_PatchBased_PatchInfo(pDrPatch);
			////////////////////////////////
			if(nResult == MA_CREATE)
				//////////////////////////////////////////////////////// Create
				break;
			if( (nResult == MA_CANCEL) || (nResult == MA_ERROR))
				return nResult;
			else
			if(nResult == MA_SEARCH)
			{
				//////////////////////////////////////////////////////// Retry
				if(m_ProbLim == PDL_TWO)
					index = IsObjectHit(PATCH,point,startIndex);
				if(m_ProbLim == PDL_THREE)
					index = IsObjectHit(PATCH,point,startIndex);
				/////////////////////////////////////////////////////////////// Right Type
				if(index>=0)
				{
					pDrPatch	= (CDrPatch*)pDListMgr->GetObject(index);
					ID		= pDrPatch->GetObjectID();
					/////////////////////////////////////////////
					pObjectMgr->ShowObject_On_Off(pDrPatch,PATCH,TRUE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
					////////////////
					return MA_CANCEL;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
				return MA_CANCEL;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentPatch = pDrPatch;
	/////////////////
	return MA_CREATE;
	/////////
}
	
int CSLDMouse::ShowSolidInfo(CDrSolid* pDrSolid)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrSolid->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrSolid->GetStaLList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Solid is Already Loaded  *****\n");
		j += sprintf(buf+j,"\nSolidID = %s ",ID);
		//////////////////////////
		UpdateSLDObjInfo();
		///////////////////
//todo		j = m_SLDPat.ShowInfo_SolidStaticLoad(pDrNode, buf, j,m_CurrentStLID);
		///////
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing SolidBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Solid with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_CREATE;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing SolidBased Loading");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Solid");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Solid with New Loading Anyway");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNOCANCEL|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CANCEL;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			else
			if(nResult == IDCANCEL)
				nResult = MA_CREATE;
			/////////////
		}
	}
	else
	{
		//////////////////////////////
		j = sprintf(buf,"***** Existing Solid Selected *****\n");
		j += sprintf(buf+j,"\nSolidID = %s ",ID);
		////////////////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
					"\n\nYES:\tAccept This Existing Solid");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_CANCEL;
			/////////////
		}
		else
		if(m_ProbLim == PDL_THREE)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Solid");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Solid");
			////////////////////////////
			nResult = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			delete str;
			/////////////
			if(nResult == IDYES)
				nResult = MA_CREATE;
			else
			if(nResult == IDNO)
				nResult = MA_SEARCH;
			/////////////
		}
	}
	//////////////
	return nResult;
}

int CSLDMouse::ShowInfo_SolidStatic(CDrSolid* pDrSolid, char* buf, int jStart)
{
	int nResult = 0;
	////////////////
	nResult = AfxMessageBox("SOLIDBASED LOADING\nNOT SUPPORTED YET",MB_YESNO|MB_ICONQUESTION);
	return MA_CANCEL;
}

int CSLDMouse::LeftUp_Static_Solid(CPoint point)
{
	int nResult = 0;
	////////////////
	nResult = AfxMessageBox("SOLIDBASED LOADING\nNOT SUPPORTED YET",MB_YESNO|MB_ICONQUESTION);
	return MA_CANCEL;
}

int CSLDMouse::LeftUp_Solid_Accept(CPoint point)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrSolid*	pDrSolid;
	int			index;
	////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	WORtoWOP(&dTol,&dTol);	// physical
	///////////////////////////////////////////// See if any Existing Node Hit
	if(m_ProbLim == PDL_TWO)
		index = IsObjectHit(SOLID,point,0);
	else
	if(m_ProbLim == PDL_THREE)
		index = IsObjectHit(SOLID,point,0);
	/////////////////////////////////////////////////////////////// No Hit
	if(index<0)
		return MA_NOHIT;
	/////////////////////////////////////////////////////////////// Right Type
	pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
	ID			= pDrSolid->GetObjectID();
	/////////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(pDrSolid,SOLID,TRUE);
	//////////////////////////////////////////////////////////////// MultipleSearch
	int startIndex = index+1;
	int nResult;
	/////////////////////////
	if(!m_bAutoAcceptOn)
	{
		/////////////
		for(;;)
		{
			nResult = ShowSolidInfo(pDrSolid);
			////////////////////////////////
			if(nResult == MA_CREATE)
				//////////////////////////////////////////////////////// Create
				break;
			if( (nResult == MA_CANCEL) || (nResult == MA_ERROR))
				return nResult;
			else
			if(nResult == MA_SEARCH)
			{
				//////////////////////////////////////////////////////// Retry
				if(m_ProbLim == PDL_TWO)
					index = IsObjectHit(SOLID,point,startIndex);
				if(m_ProbLim == PDL_THREE)
					index = IsObjectHit(SOLID,point,startIndex);
				/////////////////////////////////////////////////////////////// Right Type
				if(index>=0)
				{
					pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
					ID			= pDrSolid->GetObjectID();
					/////////////////////////////////////////////
					pObjectMgr->ShowObject_On_Off(pDrSolid,SOLID,TRUE);
					////////////////////////////////////////
					startIndex  = index+1;
					/////////////////////
				}
				else
					////////////////
					return MA_CANCEL;
				/////////
			}
			else				// Cancel
				//////////////////////////////////////////////////////// Do Nothing
				return MA_CANCEL;
		}						// end for loop
		///////////////////////////////////////
	}				// end !AutoAccept loop
	//////////////////////////////////////////////////////////////////// finally, accept
	m_pCurrentSolid = pDrSolid;
	/////////////////
	return MA_CREATE;
	/////////
}

int CSLDMouse::LeftUp_Static_NODE(POINT point,UINT uStaLProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetNodeStatic(point);// FALSE =bCNode
			///
			switch (nResult)
			{
				case MA_OK:
					m_nNodeDone++;
					/////////////////////////
					// more than one curve thro' node, if not
					// bump for JC_X_TAN_CURVE & JC_Z_NOR_PATCH
					if(m_pCurrentNode->GetCurveList()->GetCount()<2)
					{
						if(jcType == JC_X_TAN_CURVE)
						{
							m_pTanCurve = (CDrCurve*)(
								m_pCurrentNode->GetCurveList()->GetHead());
							m_nInfoDone++;	// bump
						}
					}
					////////////////////////////////////////////////
					if(jcType == JC_Z_NOR_PATCH || jcType == JC_I_TAN_PATCH)
					{
						if(	!m_pCurrentNode->GetPatchList()->IsEmpty() )
						{
							m_pNorPatch = (CDrPatch*)(
								m_pCurrentNode->GetPatchList()->GetHead());
							m_nInfoDone++;	// bump
						}
						else
						{
							m_pNorPatch = NULL;
							int nPatchCount = 0;
							CDListMgr PatchList;
							PatchList.RemoveAll();
							////////////////////
							CDListMgr* pList = m_pCurrentNode->GetCurveList();
							if(!pList->IsEmpty() )
							{
								for(int k=0;k<pList->GetCount();k++)
								{
									CDrCurve* pCurve = (CDrCurve*)pList->GetObject(k);
									if(!(pCurve->GetPatchList()->IsEmpty()) )
									{
										for(int m=0;m<pCurve->GetPatchList()->GetCount();m++)
										{
											POSITION pos = pCurve->GetPatchList()->FindIndex(m); 
											CDrPatch* pPatch = (CDrPatch*)(pCurve->GetPatchList()->GetAt(pos));
											if(PatchList.GetObjectIndex(pPatch)<0)	// not in yet
											{		
												nPatchCount++;
												PatchList.InsertObject(pPatch);
											}
										}
									}	
								}
								/////////////////////////// Only One Patch, so no need to ask User
								if(nPatchCount == 1)
								{
									m_pNorPatch = (CDrPatch*)(PatchList.GetHead());
									m_nInfoDone++;	// bump
								}
							}
						}

					}
					//////////////////////////////////// GetUniform Values
					GetStLInDlg()->Get_Values_Uniform();
					//////
					break;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					break;
				case MA_ERROR:	// fall thro'
				default:
					return MA_ERROR;
			}
			return nResult;


		case 1:

			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					break;
				case JC_X_TAN_CURVE:
					nResult = LeftUp_JC_X_TAN_CURVE_SLD(point);
					break;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					nResult = LeftUp_JC_Z_NOR_PATCH_SLD(point);
					break;
				default:
					return MA_ERROR;
			}
			return nResult;


		case 2:

			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					break;
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					break;
				case JC_X_TAN_CURVE:	// fall thro'
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					return nResult;	// No Hit
				default:
					return MA_ERROR;
			}
			return nResult;

		default:
			return MA_ERROR;
	}
	return nResult;	// No Hit
}

int CSLDMouse::GetValues_CURVE()
{
	int nResult = MA_OK;
	//////////////////////////////////////////////// Get Values
	UpdateSLDObjInfo();
	///////////////////
	if(m_bIso)
	{
		///////////////////////////// Iso
		m_SLDPat.Get_Values_Iso_Cur(m_pCurrentCurve,m_StaLProc,-1,FALSE); // -1= No skipping of node
		/////////
		CString strID;
		//////////////
		if(m_bTx ||m_bTy ||m_bTz)
		{
			strID = m_CurrentStLID + "_CC";
			strID += "_T";
			m_SLDPat.Generate_IsoCurveControls(m_pCurrentCurve,0,&strID,TRUE);	// TRUE = Translation
		}
		if(m_bRx ||m_bRy ||m_bRz)
		{
			strID = m_CurrentStLID + "_CC";
			strID += "_R";
			m_SLDPat.Generate_IsoCurveControls(m_pCurrentCurve,0,&strID,FALSE);	// FALSE = Rotation
		}
	}
	else
	if(m_bNonIso)
		///////////////////////////// NonIso
		m_SLDPat.Get_Values_NonIso_Cur(m_StaLProc);
		//////////////
	else	// this will be provided by Dlg_StLIn
		///////////////////////////// Uniform
		GetStLInDlg()->Get_Values_Uniform();
	////////////
	return nResult;
}

int CSLDMouse::LeftUp_Static_CURVE(POINT point,UINT uStaLProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetCurveStatic(point);
			///
			switch (nResult)
			{
				case MA_OK:
					m_nCurveDone++;
					// bump for JC_X_TAN_CURVE
					if(jcType == JC_X_TAN_CURVE)
					{
						m_pTanCurve = m_pCurrentCurve;
						m_nInfoDone++;	// bump
						//////////////////////// Get Values
						GetValues_CURVE();
						//////////////
						return nResult;
					}
					////////////////////////////////////////////////
					if(m_pCurrentCurve->GetPatchList()->GetCount()<2)
					{
						if(jcType == JC_Z_NOR_PATCH || jcType == JC_I_TAN_PATCH)
						{
							m_pNorPatch = (CDrPatch*)(
								m_pCurrentCurve->GetPatchList()->GetHead());
							m_nInfoDone++;	// bump
							//////////////////////// Get Values
							GetValues_CURVE();
							//////////////
							return nResult;
						}
					}
					//////////////////////// Get Values
					if(jcType == JC_DEFAULT)
						//////////////////
						GetValues_CURVE();
						//////////////////
					return nResult;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					break;
				case MA_ERROR:	// fall thro'
				default:
					return MA_ERROR;
			}
			return nResult;


		case 1:

			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					break;
				case JC_X_TAN_CURVE:
					if(m_nInfoDone>= MAX_INFO_JC_X_TAN_CURVE)
						return nResult;	// No Hit
					break;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					if(m_nInfoDone>= MAX_INFO_JC_Z_NOR_PATCH)
						return nResult;	// No Hit
					nResult = LeftUp_JC_Z_NOR_PATCH_SLD(point);
					//////////////////////// Get Values
					GetValues_CURVE();
					//////////////////
					break;
				default:
					return MA_ERROR;
			}
			return nResult;


		case 2:

			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					break;
				case JC_X_FIXEDDIR:
					if(m_nInfoDone>= MAX_INFO_JC_X_FIXEDDIR)
						return nResult;	// No Hit
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					//////////////////////// Get Values
					GetValues_CURVE();
					//////////////////
					break;
				case JC_X_TAN_CURVE:	// fall thro'
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					return nResult;	// No Hit
				default:
					return MA_ERROR;
			}
			return nResult;


		default:
			return MA_ERROR;
	}
	/////////////////////////
	return nResult;	// No Hit
}

int CSLDMouse::GetValues_PATCH()
{
	int nResult = MA_OK;
	//////////////////////////////////////////////// Get Values
	UpdateSLDObjInfo();
	///////////////////
	if(m_bIso)
	{
		///////////////////////////// Iso
		m_SLDPat.Get_Values_Iso_Pat(m_pCurrentPatch,m_StaLProc,m_CurrentStPID);
		/////////
		CString strID;
		strID = m_CurrentStLID + "_PP";
		//////////////
		if(m_bTx ||m_bTy ||m_bTz)
		{
			strID = m_CurrentStLID + "_PP";
			strID += "_T";
			m_SLDPat.Generate_IsoPatchControls(m_pCurrentPatch,&strID,TRUE);	// TRUE = Translation
		}
		if(m_bRx ||m_bRy ||m_bRz)
		{
			strID = m_CurrentStLID + "_PP";
			strID += "_R";
			m_SLDPat.Generate_IsoPatchControls(m_pCurrentPatch,&strID,FALSE);	// FALSE = Rotation
		}
	}
	else
	if(m_bNonIso)
		///////////////////////////// NonIso
		m_SLDPat.Get_Values_NonIso_Cur(m_StaLProc);
		//////////////
	else	// this will be provided by Dlg_SLDIn
		///////////////////////////// Uniform
		GetStLInDlg()->Get_Values_Uniform();
	///////////////////
	return nResult;
}

int CSLDMouse::LeftUp_Static_PATCH(POINT point,UINT uStaLProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetPatchStatic(point);
			///
			switch (nResult)
			{
				case MA_OK:
					m_nPatchDone++;
					// bump for JC_Z_NOR_PATCH
					if(jcType == JC_Z_NOR_PATCH || jcType == JC_I_TAN_PATCH)
					{
						m_pNorPatch = m_pCurrentPatch;
						m_nInfoDone++;	// bump
						//////////////////////// Get Values
						GetValues_PATCH();
						//////////////
						return nResult;
					}
					//////////////////////// Get Values
					if(jcType == JC_DEFAULT)
						//////////////////
						GetValues_PATCH();
						//////////////////
					return nResult;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					break;
				case MA_ERROR:	// fall thro'
				default:
					return MA_ERROR;
			}
			return nResult;


		case 1:

			////////////////////
			switch(jcType)
			{
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					break;
				case JC_DEFAULT:	// fall thro'
				case JC_X_TAN_CURVE:
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					return nResult;	// No Hit
				default:
					return MA_ERROR;
			}
			return nResult;


		case 2:

			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					if(m_nInfoDone>= MAX_INFO_JC_X_FIXEDDIR)
						return nResult;	// No Hit
					nResult = LeftUp_JC_X_FIXEDDIR_SLD(point);
					//////////////////////// Get Values
					GetValues_PATCH();
					//////////////////
					break;
				case JC_X_TAN_CURVE:
					m_pTanCurve = m_pCurrentCurve;
					m_nCurveDone++;
					return MA_OK;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					nResult = LeftUp_JC_Z_NOR_PATCH_SLD(point);
					break;
				default:
					return MA_ERROR;
			}
			return nResult;


		default:
			return MA_ERROR;
	}
	return nResult;	// No Hit
}

int CSLDMouse::GetValues_SOLID()
{
	int nResult = MA_OK;
	//////////////////////////////////////////////// Get Values
	UpdateSLDObjInfo();
	///////////////////
	return nResult;
}

int CSLDMouse::LeftUp_Static_SOLID(POINT point,UINT uStaLProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	return nResult;
}

void CSLDMouse::ElementLeftUp_SLD(CPoint point)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////////////
//	CString*	pID;
	/////////////
//	char buf[20];
	CString Nid;
	////////////////
	UpdateStaticDlg_TRUE();
	///////////////////////////////////////////////////////// Check If Any Composelected
	if(!m_bTx && !m_bTy &&!m_bTz && !m_bRx &&!m_bRy && !m_bRz)
	{
		AfxMessageBox(
			"Please Select Atleast\nOne Degree of Freedom\nFrom the DialogBox",
			MB_ICONEXCLAMATION);
		return;
	}
	///////////////////
	SetMainType_SLD();
	///////////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Static: Node Based										
		case NSL_FORCE:
		case NSL_DISPLACE:
		case NSL_PRESSURE:
		case NSL_THERMAL:
		case NSL_LUMPWT:


			////////////////
			UpdateStaticDlg_TRUE();
			////////////////
			nResult = LeftUp_Static_NODE(point,m_nMainType,m_jcType);
			///
			switch (nResult)
			{
				case MA_OK:
					m_nInfoDone++;
					break;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					m_nInfoDone--;
					return;
				case MA_ERROR:	// fall thro'
				default:
					Terminate_SLD(TRUE); // TRUE = bError
					Init_SLD();
					return;
			}
			////////////////
			UpdateStaticDlg_FALSE();
			////////////////
			break;

		///////////////////////////////////////////////////// Static: Curve Based										
		case CSL_FORCE:
		case CSL_DISPLACE:
		case CSL_PRESSURE:
		case CSL_THERMAL:
		case CSL_LUMPWT:

			////////////////////
			UpdateStaticDlg_TRUE();
			////////////////
			nResult = LeftUp_Static_CURVE(point,m_nMainType,m_jcType);
			///
			switch (nResult)
			{
				case MA_OK:
					m_nInfoDone++;
					break;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					m_nInfoDone--;
					return;
				case MA_ERROR:	// fall thro'
				default:
					Terminate_SLD(TRUE); // TRUE = bError
					Init_SLD();
					return;
			}
			////////////////
			UpdateStaticDlg_FALSE();
			////////////////////
			break;

		///////////////////////////////////////////////////// Static: Patch Based										
		case PSL_FORCE:
		case PSL_DISPLACE:
		case PSL_PRESSURE:
		case PSL_THERMAL:
		case PSL_LUMPWT:

			////////////////////
			UpdateStaticDlg_TRUE();
			////////////////
			nResult = LeftUp_Static_PATCH(point,m_nMainType,m_jcType);
			///
			switch (nResult)
			{
				case MA_OK:
					m_nInfoDone++;
					break;
				case MA_NOHIT:	// fall thro'
				case MA_CANCEL:
					m_nInfoDone--;
					return;
				case MA_ERROR:	// fall thro'
				default:
					Terminate_SLD(TRUE); // TRUE = bError
					Init_SLD();
					return;
			}
			////////////////
			UpdateStaticDlg_FALSE();
			////////////////////
			break;
		///////////////////////////////////////////////////// Static: Solid Based										
		case SSL_FORCE:
		case SSL_DISPLACE:
		case SSL_PRESSURE:
		case SSL_THERMAL:
		case SSL_LUMPWT:

			////////////////////
//			LeftUp_Static_Solid(point,m_nMainType,m_jcType);	
			////////////////////
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CSLDMouse::OnEBoxMouseMove_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSLDMouse::OnEBoxLButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SLD(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CSLDMouse::OnEBoxRButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
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
		
		case FORCE:
			break;
		////////////////////////////////////////////////// Patch
		case NONE:  
		default:
			break;
	}  
}

int CSLDMouse::RightUp_Static_Error()
{
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	////////////////////////////////////////////////////////////////// 
	//////////
	return MA_OK;
}

int CSLDMouse::RightUp_Static_Premature()
{
	int nAnswer = MA_OK;
	////////////////////
//	int nAnswer = IDOK		= MA_OK;				// no problem
//	int nAnswer = IDOK		= MA_GETMOREINFO;		// continue get more info
//	int nAnswer = IDCANCEL	= MA_CANCEL;			// Cancel Process
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	BOOL bPreMature = FALSE;
	////////////////////////////////////////////////////////////////// 
	CString* pID;
	CString strObj;
	//////////////////////////////////////////////////// Acceptance Not Automatic
	pID			= &m_CurrentStLID; 
	//////////////////////////////////////////////////// Check Adequate Info,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////////////////////////////////////
	switch(m_nMainType) 
	{

		///////////////////////////////////////////////////// Static: Node Based										
		case NSL_FORCE:
		case NSL_DISPLACE:
		case NSL_PRESSURE:
		case NSL_THERMAL:
		case NSL_LUMPWT:
			////////////////
			switch(m_jcType)
			{
				case JC_DEFAULT:		// fall thro'
					if(m_nInfoDone < MAX_INFO_JC_DEFAULT)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\nNeed to Select A Node");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_X_FIXEDDIR:
					if(m_nInfoDone < MAX_INFO_JC_X_FIXEDDIR)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Node, and direction\ndefining Nodes");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_X_TAN_CURVE:
					if(m_nInfoDone < MAX_INFO_JC_X_TAN_CURVE)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Node, and a Curve for Tangent direction ");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_I_TAN_PATCH:
					if(m_nInfoDone < MAX_INFO_JC_I_TAN_PATCH)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Node, and a Patch for Tangent direction ");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_Z_NOR_PATCH:
					if(m_nInfoDone < MAX_INFO_JC_Z_NOR_PATCH)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Node, and a Patch for Normal direction ");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				default:
					return MA_ERROR;
			}
			break;
		///////////////////////////////////////////////////// Static: Curve Based										
		case CSL_FORCE:
		case CSL_DISPLACE:
		case CSL_PRESSURE:
		case CSL_THERMAL:
		case CSL_LUMPWT:
			////////////////
			switch(m_jcType)
			{
				case JC_DEFAULT:		// fall thro'
				case JC_X_TAN_CURVE:
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					if(m_nInfoDone < MAX_INFO_JC_DEFAULT)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\nNeed to Select A Curve");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_X_FIXEDDIR:
					if(m_nInfoDone < MAX_INFO_JC_X_FIXEDDIR)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Curve, and direction\ndefining Nodes");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				default:
					return MA_ERROR;
			}
			break;
		///////////////////////////////////////////////////// Static: Patch Based										
		case PSL_FORCE:
		case PSL_DISPLACE:
		case PSL_PRESSURE:
		case PSL_THERMAL:
		case PSL_LUMPWT:

			////////////////
			switch(m_jcType)
			{
				case JC_DEFAULT:		// fall thro'
				case JC_X_TAN_CURVE:
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					if(m_nInfoDone < MAX_INFO_JC_DEFAULT)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\nNeed to Select A Patch");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_X_FIXEDDIR:
					if(m_nInfoDone < MAX_INFO_JC_X_FIXEDDIR)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Patch, and direction\ndefining Nodes");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				default:
					return MA_ERROR;
			}
			break;
		///////////////////////////////////////////////////// Static: Solid Based										
		case SSL_FORCE:
		case SSL_DISPLACE:
		case SSL_PRESSURE:
		case SSL_THERMAL:
		case SSL_LUMPWT:

			////////////////
			switch(m_jcType)
			{
				case JC_DEFAULT:		// fall thro'
				case JC_X_TAN_CURVE:
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					if(m_nInfoDone < MAX_INFO_JC_DEFAULT)
					{
						////////////////////
						j = sprintf(buf,"ERROR:\nNeed to Select A Solid");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				case JC_X_FIXEDDIR:
					if(m_nInfoDone < MAX_INFO_JC_X_FIXEDDIR)
					{
						////////////////////
						j = sprintf(buf,
							"ERROR:\nNeed to Select A Solid, and direction\ndefining Nodes");
						/////////////////////////	
						bPreMature = TRUE;
					}
					break;
				default:
					return MA_ERROR;
			}
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	/////////////////////////////////
	if(bPreMature)
	{
		j += sprintf(buf+j,"Do You want to Continue to Get More Info(s) ?");
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		delete str;
	}
	else
		return MA_OK;
	//////////////////////////////////////////////////////////////////// Dialog result
	if(nAnswer == IDNO)		// Cancel
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Are You Sure You Want to\nDelete Current Loading?");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			/////////////////////////////////////// Reset
			Init_SLD();
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
		}
		delete str;
		///////////////////////////
		return MA_CANCEL;	// cancel

	}
	// (nAnswer == IDYES)		//continue to get more info
	////////
	return MA_GETMOREINFO;
}

int CSLDMouse::RightUp_Static_NotAutoAccept()
{
//	int nAnswer = IDOK;		// Continue Process
//	int nAnswer = IDCANCEL;	// Cancel Process
	///////////////////
	int nAnswer = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	////////////////////////////////////////////////////////////////// 
	CString* pID;
	pID			= &m_CurrentStLID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j = 0;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	int nResult = ShowAcceptInfo_Static(buf, j);
	////////////////////////////////////
	if(nResult == MA_ERROR)
		return nResult;
	/////////////////////////
	nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	/////////////////////////
	if(nAnswer == IDCANCEL)
	{
		sprintf(buf,"Are You Sure You Want to\nDelete Current Loading?");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			///////////
			delete str;
			///////////////////////
			return MA_CANCEL;
		}
	}
	/////////////////////
	str->ReleaseBuffer();
	delete str;
	///////////////
	return MA_OK;
}

int CSLDMouse::ShowAcceptInfo_Static(char* buf, int& j)
{
	////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Node Based										
		case NSL_FORCE:
		case NSL_DISPLACE:
		case NSL_PRESSURE:
		case NSL_THERMAL:
		case NSL_LUMPWT:

			////////////////
			j += sprintf(buf+j,"***** Selected Node-Based Loading Info  *****\n");
			return ShowAcceptInfo_NodeBased(m_pCurrentNode,buf,j);
			////////////////

		///////////////////////////////////////////////////// Curve Based										
		case CSL_FORCE:
		case CSL_DISPLACE:
		case CSL_PRESSURE:
		case CSL_THERMAL:
		case CSL_LUMPWT:

			////////////////
			return ShowAcceptInfo_CurveBased(m_pCurrentCurve,buf,j);
			////////////////

		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSL_FORCE:
		case PSL_DISPLACE:
		case PSL_PRESSURE:
		case PSL_THERMAL:
		case PSL_LUMPWT:

			////////////////
			return ShowAcceptInfo_PatchBased(m_pCurrentPatch,buf,j);
			////////////////

		///////////////////////////////////////////////////// Solid Based										
		case SSL_FORCE:
		case SSL_DISPLACE:
		case SSL_PRESSURE:
		case SSL_THERMAL:
		case SSL_LUMPWT:

			////////////////
			return ShowAcceptInfo_SolidBased(m_pCurrentSolid,buf,j);
			//////////////////// 

		//////////////////////////////////////////////////
		default:  
			return MA_ERROR;
	} 
	////////////
}
	
int CSLDMouse::ShowAcceptInfo_NodeBased(CDrNode* pDrNode, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrNode->GetObjectID();
	//////////////
	UpdateSLDObjInfo();
	///////////////////
	j = m_SLDPat.ShowInfo_NodeStaticLoad(pDrNode, buf, j,m_CurrentStLID);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSLDMouse::ShowAcceptInfo_CurveBased(CDrCurve* pDrCurve, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrCurve->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nLoading at CurveID = %s\n",ID);
	//////////////
	UpdateSLDObjInfo();
	///////////////////
	j = m_SLDPat.ShowInfo_CurveStaticLoad(pDrCurve, buf, j,m_CurrentStLID);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSLDMouse::ShowAcceptInfo_PatchBased(CDrPatch* pDrPatch, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrPatch->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nLoading at PatchID = %s\n",ID);
	//////////////
	UpdateSLDObjInfo();
	///////////////////
	j = m_SLDPat.ShowInfo_PatchStaticLoad(pDrPatch, buf, j,m_CurrentStLID);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSLDMouse::ShowAcceptInfo_SolidBased(CDrSolid* pDrSolid, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrSolid->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nLoading at SolidID = %s\n",ID);
	//////////////
	UpdateSLDObjInfo();
	///////////////////
//todo	j = m_SLDPat.ShowInfo_SolidStaticLoad(pDrSolid, buf, j,m_CurrentStLID);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}

void CSLDMouse::OnEBoxRButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	int nResult = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////// Premature?
	nResult = RightUp_Static_Premature();
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SLD(TRUE);
			Init_SLD();
			return;
		case MA_GETMOREINFO:
			return;
	}
	//////////////////////////////////////////////////// Error 
	nResult = MA_OK;
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SLD(TRUE);
			Init_SLD();
			return;
		case MA_GETMOREINFO:
			return;
	}
	//////////////////////////////////////////////////// Fill StaLCard
	UpdateSLDObjInfo();
	/////////////////////////////////////////////////////////////// Not AutoAccept
	if(!m_bAutoAcceptOn)
	{
		nResult = RightUp_Static_NotAutoAccept();
		switch(nResult)
		{
		case MA_OK:
			break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SLD(TRUE);
			Init_SLD();
			return;
		case MA_GETMOREINFO:
			return;
		}
	}
	/////////////////////////////////////////////////////////////////////// Show NewSupport
	nResult = ShowStatic(&m_CurrentStLID);		// TRUE = Final
	//////////////////////////////
	switch(nResult)
	{
		case MA_OK:
			/////////////
			pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
			Init_SLD();
			////////////////////
			UpdateStaticDlg_FALSE();
			//////////////////// 
			return;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SLD(TRUE);
			Init_SLD();
			return;
	}
	///////////////
	return;
}
////////////////////////////////////////////////////////////////////	
UINT CSLDMouse::ReSetToolID_SLD(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
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
				//////////////////////////////////////// StaticLoad
				case STATICLOAD:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "Static@Load";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// Force
					switch(IGenID)
					{
						/////////
						case NODE:			str = "Input@NODE";	ID = STATICLOAD;	break;
						case CURVE:			str = "CURVE";		ID = STATICLOAD;	break;
						case PATCH:			str = "PATCH";		ID = STATICLOAD;	break;
						case SOLID:			str = "SOLID";		ID = STATICLOAD;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				//////////////////
				case FORCE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "FORCE";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// Force
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_FOR_NODE;	break;
						case CURVE:			str = "CURVE";		ID = CSL_FORCE;		break;
						case PATCH:			str = "PATCH";		ID = PSL_FORCE;		break;
						case SOLID:			str = "SOLID";		ID = SSL_FORCE;		break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				//////////////////
				case DISPLACE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "DISPLACE";
					pWnd->SetstrCntlID(str);
					////////////////// Displacement
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_DIS_NODE;	break;
						case CURVE:			str = "CURVE";		ID = CSL_DISPLACE;	break;
						case PATCH:			str = "PATCH";		ID = PSL_DISPLACE;	break;
						case SOLID:			str = "SOLID";		ID = SSL_DISPLACE;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				//////////////////
				case PRESSURE:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "PRESSURE";
					pWnd->SetstrCntlID(str);
					////////////////// Pressure
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_PRS_NODE;	break;
						case CURVE:			str = "CURVE";		ID = CSL_PRESSURE;	break;
						case PATCH:			str = "PATCH";		ID = PSL_PRESSURE;	break;
						case SOLID:			str = "SOLID";		ID = SSL_PRESSURE;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////// 
				case THERMAL:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "THERMAL";
					pWnd->SetstrCntlID(str);
					////////////////// Thermal
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_THR_NODE;	break;
						case CURVE:			str = "CURVE";		ID = CSL_THERMAL;	break;
						case PATCH:			str = "PATCH";		ID = PSL_THERMAL;	break;
						case SOLID:			str = "SOLID";		ID = SSL_THERMAL;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////// 
				case LUMPWT:

					pWnd->SetMouseBoxType(STATICLOADBOX);
					str = "LUMPWT";
					pWnd->SetstrCntlID(str);
					////////////////// LumpWt
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSL_LWT_NODE;	break;
						case CURVE:			str = "CURVE";		ID = CSL_LUMPWT;	break;
						case PATCH:			str = "PATCH";		ID = PSL_LUMPWT;	break;
						case SOLID:			str = "SOLID";		ID = SSL_LUMPWT;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				/////////
				default:					str = "UNKNOWN";	ID = UNONE;
					pWnd->SetstrIGenID(str);
					return ID;
			}
			break;
		////////
		default:							str = "UNKNOWN";	ID = UNONE;
			pWnd->SetstrOperID(str);
			return ID;
		}
	}
	pWnd->SetstrIGenID(str);
	////////////////////////
	CurrentOperationString(CntlID,IGenID,strCur);
	pWnd->SetstrCurrID(strCur);
	//////////
	return ID;
}

void CSLDMouse::ModeLessOff_SLD()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetStLInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_FANDMIN,IDOK);
	if(GetStLInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_DANDRIN,IDOK);
	if(GetStLInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_PRESSIN,IDOK);
	if(GetStLInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_THERMIN,IDOK);
	if(GetStLInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_LUMPWTIN,IDOK);
}

void CSLDMouse::SetMainType_SLD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nActiveTool	= pWnd->GetActiveToolType();
	///////////////////
	switch(m_nActiveTool) 
	{
	
		case STATICLOAD:
			
			m_nMainType	= STATICLOAD;
			break;

		///////////////////////////////////////////////////// Static: Node Based										
		case NSL_FORCE:
		case NSL_FOR_NODE:
		case NSL_FOR_CNODE:

			m_nMainType	= NSL_FORCE;
			break;

		case NSL_DISPLACE:
		case NSL_DIS_NODE:
		case NSL_DIS_CNODE:

			m_nMainType	= NSL_DISPLACE;
			break;

		case NSL_PRESSURE:
		case NSL_PRS_NODE:
		case NSL_PRS_CNODE:

			m_nMainType	= NSL_PRESSURE;
			break;

		case NSL_THERMAL:
		case NSL_THR_NODE:
		case NSL_THR_CNODE:

			m_nMainType	= NSL_THERMAL;
			break;

		case NSL_LUMPWT:
		case NSL_LWT_NODE:
		case NSL_LWT_CNODE:

			m_nMainType	= NSL_LUMPWT;
			break;
		////////////////////////////////////////////////////// Static: Curve Based										
		case CSL_FORCE:
		case CSL_FOR_CIRCLE:
		case CSL_FOR_ELLIPSE:
		case CSL_FOR_PARABOLA:
		case CSL_FOR_LINEAR:
		case CSL_FOR_QUADRATIC:
		case CSL_FOR_CUBIC:
		case CSL_FOR_HERMITE:
		case CSL_FOR_BEZIER:
		case CSL_FOR_BSPLINE:
		case CSL_FOR_NURB:
		case CSL_FOR_STITCH:
		case CSL_FOR_SPAWN:

			m_nMainType	= CSL_FORCE;
			break;


		case CSL_DISPLACE:
		case CSL_DIS_CIRCLE:
		case CSL_DIS_ELLIPSE:
		case CSL_DIS_PARABOLA:
		case CSL_DIS_LINEAR:
		case CSL_DIS_QUADRATIC:
		case CSL_DIS_CUBIC:
		case CSL_DIS_HERMITE:
		case CSL_DIS_BEZIER:
		case CSL_DIS_BSPLINE:
		case CSL_DIS_NURB:
		case CSL_DIS_STITCH:
		case CSL_DIS_SPAWN:

			m_nMainType	= CSL_DISPLACE;
			break;


		case CSL_PRESSURE:
		case CSL_PRS_CIRCLE:
		case CSL_PRS_ELLIPSE:
		case CSL_PRS_PARABOLA:
		case CSL_PRS_LINEAR:
		case CSL_PRS_QUADRATIC:
		case CSL_PRS_CUBIC:
		case CSL_PRS_HERMITE:
		case CSL_PRS_BEZIER:
		case CSL_PRS_BSPLINE:
		case CSL_PRS_NURB:
		case CSL_PRS_STITCH:
		case CSL_PRS_SPAWN:

			m_nMainType	= CSL_PRESSURE;
			break;

		case CSL_THERMAL:
		case CSL_THR_CIRCLE:
		case CSL_THR_ELLIPSE:
		case CSL_THR_PARABOLA:
		case CSL_THR_LINEAR:
		case CSL_THR_QUADRATIC:
		case CSL_THR_CUBIC:
		case CSL_THR_HERMITE:
		case CSL_THR_BEZIER:
		case CSL_THR_BSPLINE:
		case CSL_THR_NURB:
		case CSL_THR_STITCH:
		case CSL_THR_SPAWN:

			m_nMainType	= CSL_THERMAL;
			break;

		case CSL_LUMPWT:
		case CSL_LWT_CIRCLE:
		case CSL_LWT_ELLIPSE:
		case CSL_LWT_PARABOLA:
		case CSL_LWT_LINEAR:
		case CSL_LWT_QUADRATIC:
		case CSL_LWT_CUBIC:
		case CSL_LWT_HERMITE:
		case CSL_LWT_BEZIER:
		case CSL_LWT_BSPLINE:
		case CSL_LWT_NURB:
		case CSL_LWT_STITCH:
		case CSL_LWT_SPAWN:

			m_nMainType	= CSL_LUMPWT;
			break;
		////////////////////////////////////////////////////// Static: Patch Based										
		case PSL_FORCE:
		case PSL_FOR_TENSOR: 	
		case PSL_FOR_GORDONS:	  
		case PSL_FOR_COONS: 	 
		case PSL_FOR_LOFT: 		
		case PSL_FOR_EXTRUDE:	
		case PSL_FOR_DUCT: 		 
		case PSL_FOR_SWEEP: 	 
		case PSL_FOR_FLATPLATE:	  
		case PSL_FOR_STITCH: 	
		case PSL_FOR_SPAWN: 	

			m_nMainType	= PSL_FORCE;
			break;


		case PSL_DISPLACE:
		case PSL_DIS_TENSOR: 	
		case PSL_DIS_GORDONS:	  
		case PSL_DIS_COONS: 	 
		case PSL_DIS_LOFT: 		
		case PSL_DIS_EXTRUDE:	
		case PSL_DIS_DUCT: 		 
		case PSL_DIS_SWEEP: 	 
		case PSL_DIS_FLATPLATE:	  
		case PSL_DIS_STITCH: 	
		case PSL_DIS_SPAWN: 	

			m_nMainType	= PSL_DISPLACE;
			break;


		case PSL_PRESSURE:
		case PSL_PRS_TENSOR: 	
		case PSL_PRS_GORDONS:	  
		case PSL_PRS_COONS: 	 
		case PSL_PRS_LOFT: 		
		case PSL_PRS_EXTRUDE:	
		case PSL_PRS_DUCT: 		 
		case PSL_PRS_SWEEP: 	 
		case PSL_PRS_FLATPLATE:	  
		case PSL_PRS_STITCH: 	
		case PSL_PRS_SPAWN: 	

			m_nMainType	= PSL_PRESSURE;
			break;

		case PSL_THERMAL:
		case PSL_THR_TENSOR: 	
		case PSL_THR_GORDONS:	  
		case PSL_THR_COONS: 	 
		case PSL_THR_LOFT: 		
		case PSL_THR_EXTRUDE:	
		case PSL_THR_DUCT: 		 
		case PSL_THR_SWEEP: 	 
		case PSL_THR_FLATPLATE:	  
		case PSL_THR_STITCH: 	
		case PSL_THR_SPAWN: 	

			m_nMainType	= PSL_THERMAL;
			break;

		case PSL_LUMPWT: 		
		case PSL_LWT_TENSOR: 	
		case PSL_LWT_GORDONS:	  
		case PSL_LWT_COONS: 	 
		case PSL_LWT_LOFT: 		
		case PSL_LWT_EXTRUDE:	
		case PSL_LWT_DUCT: 		 
		case PSL_LWT_SWEEP: 	 
		case PSL_LWT_FLATPLATE:	  
		case PSL_LWT_STITCH: 	
		case PSL_LWT_SPAWN: 	

			m_nMainType	= PSL_LUMPWT;
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	}
	////////
	return;
}

void CSLDMouse::ModeLessOn_SLD()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////
	SetMainType_SLD();
	/////////////////////////////////////////////////////////////////// Open
	switch(m_nMainType)
	{
		case NSL_FORCE:
		case CSL_FORCE:
		case PSL_FORCE:
		case SSL_FORCE:

//			if(!(GetStLInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_FANDMIN,IDOK);
			break;

		case NSL_DISPLACE:
		case CSL_DISPLACE:
		case PSL_DISPLACE:
		case SSL_DISPLACE:

//			if(!(GetStLInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_DANDRIN,IDOK);
			break;

		case NSL_PRESSURE:
		case CSL_PRESSURE:
		case PSL_PRESSURE:
		case SSL_PRESSURE:

//			if(!(GetStLInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_PRESSIN,IDOK);
			break;

		case NSL_THERMAL:
		case CSL_THERMAL:
		case PSL_THERMAL:
		case SSL_THERMAL:

//			if(!(GetStLInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_THERMIN,IDOK);
			break;

		case NSL_LUMPWT:
		case CSL_LUMPWT:
		case PSL_LUMPWT:
		case SSL_LUMPWT:

//			if(!(GetStLInDlg()->m_hWnd))
				pWnd->SendMessage(ID_ACTIVE_LUMPWTIN,IDOK);
			break;

		default:
			break;
	}
	////////
	return;
}

long CSLDMouse::CreateorActivateF_MIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetStLInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetStLInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetStLInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetStLInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		Init_SLD();
		///////////
	}
	else
		GetStLInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if F_MDlg Open
	if(GetStLInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_FANDMIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_StaLProc = STL_FORCE;
	//////////////////// Core
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////////////////////////// Overrides
	GetStLInDlg()->SetWindowText("Forces & Moments");	
	///////////////////////////////////////////////// Nodal Exceptions
	if(m_nMainType == NSL_FORCE)
	{
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Values...");
		////////////////////////////////////////////////////
	}
	else
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Uniform");
	////////////////////////////////
	GetStLInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	if(m_nMainType == NSL_FORCE)
	{
			strCurr = "Imposing Node-based Force Conditions@";
			strCurr += "Click on An Existing Input Node";
	}
	else
	if(m_nMainType == CSL_FORCE)
	{
			strCurr = "Imposing Curve-based Force Conditions@";
			strCurr += "Click on An Existing Curve";
	}
	else
	if(m_nMainType == PSL_FORCE)
	{
			strCurr = "Imposing Patch-based Force Conditions@";
			strCurr += "Click on An Existing Patch";
	}
	else
	if(m_nMainType == SSL_FORCE)
	{
			strCurr = "Imposing Solid-based Force Conditions@";
			strCurr += "Click on An Existing Solid";
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSLDMouse::CancelF_MIn(UINT wParam, long lParam)
{
	
	GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::GoodByeF_MIn(UINT wParam, long lParam)
{
	
	if(GetStLInDlg()->m_hWnd)
		GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::UpdateF_MIn(UINT wParam, long lParam)
{
	UpdateDlgIn_TRUE();
	///////////////////
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////// D_R
long CSLDMouse::CreateorActivateD_RIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetStLInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetStLInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetStLInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetStLInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		Init_SLD();
		///////////
	}
	else
		GetStLInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if D_RDlg Open
	if(GetStLInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_DANDRIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_StaLProc = STL_DISPLACE;
	//////////////////// Core
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////////////////////////// Overrides
	GetStLInDlg()->SetWindowText("Displacements & Rotations");	
	//////////////////////////////// Nodal Exceptions
	if(m_nMainType == NSL_DISPLACE)
	{
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Values...");
		////////////////////////////////////////////////////
	}
	else
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Uniform");
	////////////////////////////////
	GetStLInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	if(m_nMainType == NSL_DISPLACE)
	{
			strCurr = "Imposing Node-based Kinematic Conditions@";
			strCurr += "Click on An Existing Input Node";
	}
	else
	if(m_nMainType == CSL_DISPLACE)
	{
			strCurr = "Imposing Curve-based Kinematic Conditions@";
			strCurr += "Click on An Existing Curve";
	}
	else
	if(m_nMainType == PSL_DISPLACE)
	{
			strCurr = "Imposing Patch-based Kinematic Conditions@";
			strCurr += "Click on An Existing Patch";
	}
	else
	if(m_nMainType == SSL_DISPLACE)
	{
			strCurr = "Imposing Solid-based Kinematic Conditions@";
			strCurr += "Click on An Existing Solid";
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSLDMouse::CancelD_RIn(UINT wParam, long lParam)
{
	
	GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::GoodByeD_RIn(UINT wParam, long lParam)
{
	
	if(GetStLInDlg()->m_hWnd)
		GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::UpdateD_RIn(UINT wParam, long lParam)
{
	UpdateDlgIn_TRUE();
	///////////////////
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////// Prs
long CSLDMouse::CreateorActivatePrsIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetStLInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetStLInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetStLInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetStLInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		Init_SLD();
		///////////
	}
	else
		GetStLInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if PrsDlg Open
	if(GetStLInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_PRESSIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_StaLProc = STL_PRESSURE;
	//////////////////// Core
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////////////////////////// Overrides
	GetStLInDlg()->SetWindowText("Pressures & Tractions");	
	/////////////////////////
	GetStLInDlg()->GetDlgItem(IDC_TX)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_TY)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_TZ)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(FALSE);

	GetStLInDlg()->GetDlgItem(IDC_RX)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RY)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->SetWindowText("");
	//////////////////////////////// Nodal Exceptions
	if(m_nMainType == NSL_PRESSURE)
	{
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Values...");
		////////////////////////////////////////////////////
	}
	else
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Uniform");
	////////////////////////////////
	GetStLInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	if(m_nMainType == NSL_PRESSURE)
	{
			strCurr = "Imposing Node-based Pressure Conditions@";
			strCurr += "Click on An Existing Input Node";
	}
	else
	if(m_nMainType == CSL_PRESSURE)
	{
			strCurr = "Imposing Curve-based Pressure Conditions@";
			strCurr += "Click on An Existing Curve";
	}
	else
	if(m_nMainType == PSL_PRESSURE)
	{
			strCurr = "Imposing Patch-based Pressure Conditions@";
			strCurr += "Click on An Existing Patch";
	}
	else
	if(m_nMainType == SSL_PRESSURE)
	{
			strCurr = "Imposing Solid-based Pressure Conditions@";
			strCurr += "Click on An Existing Solid";
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSLDMouse::CancelPrsIn(UINT wParam, long lParam)
{
	
	GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::GoodByePrsIn(UINT wParam, long lParam)
{
	
	if(GetStLInDlg()->m_hWnd)
		GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::UpdatePrsIn(UINT wParam, long lParam)
{
	UpdateDlgIn_TRUE();
	///////////////////
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////// Thr
long CSLDMouse::CreateorActivateThrIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetStLInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetStLInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetStLInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetStLInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		Init_SLD();
		///////////
	}
	else
		GetStLInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if ThrDlg Open
	if(GetStLInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_THERMIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_StaLProc = STL_THERMAL;
	//////////////////// Core
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////////////////////////// Overrides
	GetStLInDlg()->SetWindowText("Thermal Loadings");	
	/////////////////////////
	GetStLInDlg()->GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(FALSE);

	GetStLInDlg()->GetDlgItem(IDC_RX)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RY)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->SetWindowText("");
	/////////////////////////////// Nodal Exceptions
	if(m_nMainType == NSL_THERMAL)
	{
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Values...");
		////////////////////////////////////////////////////
	}
	else
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Uniform");
	////////////////////////////////
	GetStLInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	if(m_nMainType == NSL_THERMAL)
	{
			strCurr = "Imposing Node-based Thermal Conditions@";
			strCurr += "Click on An Existing Input Node";
	}
	else
	if(m_nMainType == CSL_THERMAL)
	{
			strCurr = "Imposing Curve-based Thermal Conditions@";
			strCurr += "Click on An Existing Curve";
	}
	else
	if(m_nMainType == PSL_THERMAL)
	{
			strCurr = "Imposing Patch-based Thermal Conditions@";
			strCurr += "Click on An Existing Patch";
	}
	else
	if(m_nMainType == SSL_THERMAL)
	{
			strCurr = "Imposing Solid-based Thermal Conditions@";
			strCurr += "Click on An Existing Solid";
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSLDMouse::CancelThrIn(UINT wParam, long lParam)
{
	UpdateDlgIn_TRUE();
	///////////////////
	return 0L;
}
	 
long CSLDMouse::GoodByeThrIn(UINT wParam, long lParam)
{
	
	if(GetStLInDlg()->m_hWnd)
		GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::UpdateThrIn(UINT wParam, long lParam)
{
	UpdateF_MIn(wParam, lParam);
	////////////////////////////
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////// LWt
long CSLDMouse::CreateorActivateLWtIn(UINT wParam, long lParam)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetStLInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetStLInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetStLInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetStLInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
		Init_SLD();
		///////////
	}
	else
		GetStLInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if LWtDlg Open
	if(GetStLInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_LUMPWTIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// Set Info
	m_StaLProc = STL_LUMPWT;
	//////////////////// Core
	UpdateDlgIn_FALSE();
	////////////////////////////////////////////////////////////////// Overrides
	GetStLInDlg()->SetWindowText("Lump Weights");	
	/////////////////////////
	GetStLInDlg()->GetDlgItem(IDC_TX)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_TY)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_TZ)->EnableWindow(TRUE);	
	GetStLInDlg()->GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(FALSE);

	GetStLInDlg()->GetDlgItem(IDC_RX)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RY)->SetWindowText("");	
	GetStLInDlg()->GetDlgItem(IDC_RZ)->SetWindowText("");
	////////////////////////////// Nodal Exceptions
	if(m_nMainType == NSL_LUMPWT)
	{
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_CONC)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_NONISO)->EnableWindow(FALSE);
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->SetWindowText("");
		GetStLInDlg()->GetDlgItem(IDC_ISOPAR_DISTRIB)->EnableWindow(FALSE);
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Values...");
		////////////////////////////////////////////////////
	}
	else
		//////////////////
		GetStLInDlg()->GetDlgItem(IDC_UNIFORM)->SetWindowText("Uniform");
	////////////////////////////////
	GetStLInDlg()->UpdateData(FALSE);
	////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	if(m_nMainType == NSL_LUMPWT)
	{
			strCurr = "Imposing Node-based Lump Weights@";
			strCurr += "Click on An Existing Input Node";
	}
	else
	if(m_nMainType == CSL_LUMPWT)
	{
			strCurr = "Imposing Curve-based Lump Weights@";
			strCurr += "Click on An Existing Curve";
	}
	else
	if(m_nMainType == PSL_LUMPWT)
	{
			strCurr = "Imposing Patch-based Lump Weights@";
			strCurr += "Click on An Existing Patch";
	}
	else
	if(m_nMainType == SSL_LUMPWT)
	{
			strCurr = "Imposing Solid-based Lump Weights@";
			strCurr += "Click on An Existing Solid";
	}
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSLDMouse::CancelLWtIn(UINT wParam, long lParam)
{
	
	GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::GoodByeLWtIn(UINT wParam, long lParam)
{
	
	if(GetStLInDlg()->m_hWnd)
		GetStLInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSLDMouse::UpdateLWtIn(UINT wParam, long lParam)
{
	UpdateDlgIn_TRUE();
	///////////////////
	return 0L;
}
	
void CSLDMouse::Serialize(CArchive& ar)
{

	CSLDMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDMouse:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////	
/* SAVE for now	
						case CNODE:			str = "Control@CNODE";	ID = NSL_FOR_CNODE;		break;
						case C_CIRCLE:		str = "CIRCULAR@CURVE";	ID = CSL_FOR_CIRCLE;	break;
						case C_ELLIPSE:		str = "ELLIPTIC@CURVE";	ID = CSL_FOR_ELLIPSE;	break;
						case C_PARABOLA:	str = "PARABOLIC@CURVE";ID = CSL_FOR_PARABOLA;	break;
						case C_LINEAR:		str = "LINEAR@CURVE";	ID = CSL_FOR_LINEAR;	break;
						case C_QUADRATIC:	str = "QUADRATIC@CURVE";ID = CSL_FOR_QUADRATIC;	break;
						case C_CUBIC:		str = "CUBIC@CURVE";	ID = CSL_FOR_CUBIC;		break;
						case C_HERMITE:		str = "HERMITE@CURVE";	ID = CSL_FOR_HERMITE;	break;
						case C_BEZIER:		str = "BEZIER@CURVE";	ID = CSL_FOR_BEZIER;	break;
						case C_BSPLINE:		str = "BSPLINE@CURVE";	ID = CSL_FOR_BSPLINE;	break;
						case C_NURB:		str = "NURB@CURVE";		ID = CSL_FOR_NURB;		break;
						case C_STITCH:		str = "STITCH@CURVE";	ID = CSL_FOR_STITCH;	break;
						case C_SPAWN:		str = "SPAWN@CURVE";	ID = CSL_FOR_SPAWN;		break;
						case P_TENSOR:		str = "TENSOR PRODUCT@PATCH";	ID = PSL_FOR_TENSOR; 	break;
						case P_GORDONS:		str = "GORDONS@PATCH";			ID = PSL_FOR_GORDONS;	break;  
						case P_COONS:		str = "COONS@PATCH";			ID = PSL_FOR_COONS; 	break; 
						case P_LOFT:		str = "LOFT@PATCH";				ID = PSL_FOR_LOFT; 		break;
						case P_EXTRUDE:		str = "EXTRUDE@PATCH";			ID = PSL_FOR_EXTRUDE;	break;
						case P_DUCT:		str = "DUCT@PATCH";				ID = PSL_FOR_DUCT; 		break; 
						case P_SWEEP:		str = "SWEEP@PATCH";			ID = PSL_FOR_SWEEP; 	break; 
						case P_FLATPLATE:	str = "TRIANGULATE@PATCH";		ID = PSL_FOR_FLATPLATE;	break;  
						case P_STITCH:		str = "STITCH@PATCH";			ID = PSL_FOR_STITCH; 	break;
						case P_SPAWN:		str = "SPAWN@PATCH";			ID = PSL_FOR_SPAWN; 	break;
*/

