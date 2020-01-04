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
///////////////////// Supports
#include "MSupMgr.h"
#include "Str_Supp.h"
#include "Def_Supp.h"
#include "MI_LSupp.h" 
////////////////////// 
#include "CommRsrc.h"
#include "Dlg_SupI.h"
//////////////////////
#include "SupMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
//////////////////////////////////////////////
#define	DEFAULT_STIF		10.e+10
//////////////////////////////////////////////////// Joint Coord Info
#define MAX_INFO_RIGID				1	// 1 Object = Node or Curve or Patch etc			
#define MAX_INFO_JC_DEFAULT			1	// 1 Object = Node or Curve or Patch etc			
#define MAX_INFO_JC_X_FIXEDDIR		3	// 1 Object & 2 Nodes
#define MAX_INFO_JC_X_TAN_CURVE		2	// 1 Object & 1 Curve
#define MAX_INFO_JC_I_TAN_PATCH		2	// 1 Object & 1 Patch
#define MAX_INFO_JC_Z_NOR_PATCH		2	// 1 Object & 1 Patch
////////////////////////////////////
IMPLEMENT_SERIAL(CSupMouse,CO3DMouse,1)
/////////////////////////////////////////////////////////////////////////////
CSupMouse::CSupMouse()
{
	m_GenKind			= (UINT)NONE;
	m_pFixDirNode		= NULL;
	m_pTanCurve			= NULL;
	m_pNorPatch			= NULL;
	///////////////////////////
	m_nInfoDone			= 0;
	m_nNodeDone			= 0;
	m_nCurveDone		= 0;
	m_nPatchDone		= 0;
	m_bSuppDone			= TRUE;		// for dragging
	///////////////////////////
	m_ID_CP			= "";
	m_jcType		= JC_DEFAULT;
	/////////////////////////////
	m_pSupInDlg	= NULL;                                                                                
	///////////////
	m_CurrentStif = new double[6];
	/////////////////////////////////////////// Support
	m_SuppProc		= SUP_RIGID;
	m_SuppProcOld	= m_SuppProc;
	m_bTx			= TRUE;
	m_bTy			= TRUE;
	m_bTz			= TRUE;
	m_bRx			= TRUE;
	m_bRy			= TRUE;
	m_bRz			= TRUE;
	/////
	m_bTxG			= FALSE;
	m_bTyG			= FALSE;
	m_bTzG			= FALSE;
	m_bRxG			= FALSE;
	m_bRyG			= FALSE;
	m_bRzG			= FALSE;
	/////
	for(int i=0;i<6;i++)
		m_CurrentStif[i]	= DEFAULT_STIF;
	////////////////////////////////
	m_CurrentSupID		= "";
	m_CurrentSupIDOld	= "";

}

CSupMouse::~CSupMouse()
{
	/////////////////////////////////// Modeless Dialogs
	if(m_pSupInDlg)
	{
		if(m_pSupInDlg->m_hWnd)
			m_pSupInDlg->DestroyWindow();
		///////////////////
		delete m_pSupInDlg;                                                                                
		///////////////////
	}
	if(m_CurrentStif)
		delete [] m_CurrentStif;                                                                                
}

void CSupMouse::InitDlgIn_SUP()
{
	///////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pSupInDlg		= new CDlg_SupI(pWnd);                                                                                
}

void CSupMouse::Init_SUP()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_GenKind			= pWnd->GetCurrentIGenID(); 
	m_pFixDirNode		= NULL;
	m_pTanCurve			= NULL;
	m_pNorPatch			= NULL;
	m_pCurrentSupp		= NULL;
	///////////////////////////
	m_NodeList.RemoveAll();
	////////////////////////
	m_nInfoDone			= 0;
	m_nNodeDone			= 0;
	m_nCurveDone		= 0;
	m_nPatchDone		= 0;
	m_bSuppDone			= TRUE;		// for dragging
	/////////////////////////////////////// Set next SupportID
	if(m_CurrentSupIDOld == m_CurrentSupID) // user didnot change
	{
		pObjectMgr->SetObjInfoID(m_CurrentSupID,LIN_SUPPORT);
		m_CurrentSupIDOld	= m_CurrentSupID;
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
	m_bTxG			= FALSE;
	m_bTyG			= FALSE;
	m_bTzG			= FALSE;
	m_bRxG			= FALSE;
	m_bRyG			= FALSE;
	m_bRzG			= FALSE;
	/////
	for(int i=0;i<6;i++)
		m_CurrentStif[i]	= DEFAULT_STIF;
	///////////////////////////////////////////////////////// Jc_Type
	GetSupInDlg()->GetDlgItem(IDC_COMBO_JCTYPE)->EnableWindow(TRUE);	
	/////////////////////////////////////////////////////////
	SetMainType_SUP();
	///////////////////
	switch(m_nMainType) 
	{
		
		////////////////////////////////////////////////// Rigid	
		case NSUP_RIGID:
		case CSUP_RIGID:
		case PSUP_RIGID:
		case SSUP_RIGID:

			m_Category		= CA_RIGID;
			m_SuppProcOld	= m_SuppProc;
			m_SuppProc		= SUP_RIGID;
			////////////////////////
			m_bTx			= TRUE;
			m_bTy			= TRUE;
			m_bTz			= TRUE;
			m_bRx			= TRUE;
			m_bRy			= TRUE;
			m_bRz			= TRUE;
			////////////////////////////////////////
			GetSupInDlg()->GetDlgItem(IDC_TX)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_TY)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_TZ)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(FALSE);
			///
			GetSupInDlg()->GetDlgItem(IDC_GX)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_GY)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_GZ)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_GRX)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_GRY)->EnableWindow(FALSE);	
			GetSupInDlg()->GetDlgItem(IDC_GRZ)->EnableWindow(FALSE);
			///////
			break;
		////////////////////////////////////////////////// LinSpring	
		case NSUP_LINSPRING:
		case CSUP_LINSPRING:
		case PSUP_LINSPRING:
		case SSUP_LINSPRING:

			m_Category		= CA_LINSPR;
			m_SuppProcOld	= m_SuppProc;
			m_SuppProc		= SUP_LINSPR;
			///////
			break;
		////////////////////////////////////////////////// LinSnubber	
		case NSUP_LINSNUBBER:
		case CSUP_LINSNUBBER:
		case PSUP_LINSNUBBER:
		case SSUP_LINSNUBBER:

			m_Category		= CA_LINSNU;
			m_SuppProcOld	= m_SuppProc;
			m_SuppProc		= SUP_LINSNU;
			////////////////////////
			GetSupInDlg()->GetDlgItem(IDC_STIFFNESS)->EnableWindow(FALSE);	
			///////
			break;
		//////////////////////////////////////////////////
		default:
			break;
	} 
}

void CSupMouse::Terminate_SUP(BOOL bError)
{
	////////////
	if(!bError)
		return;
	///////////////////////////
	if(m_pCurrentSupp)
	{ 
		delete m_pCurrentSupp;
		m_pCurrentSupp = NULL;
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
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);
	///////////////////////////////////////// delete
	pList = pObjectMgr->GetObjectList(LIN_SUPPORT);
	nActiveIndex = pList->GetObjectIndex(LIN_SUPPORT, m_CurrentSupID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, LIN_SUPPORT);
		m_pCurrentSupp = (CDrLinSup*)NULL;
	}
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return;
}

void CSupMouse:: ElementLeftDown_SUP()
{	
	GetSupInDlg()->GetDlgItem(IDC_COMBO_JCTYPE)->EnableWindow(FALSE);	
	////////////////////////
	m_bSuppDone	= FALSE;
}

int CSupMouse::FillSupCard(SUPPCARD& supCard,CString* pID)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////// Support
	supCard.nNodPos_S_Beg		= m_nNodPos_S_Beg;
	supCard.nNodPos_S_End		= m_nNodPos_S_End;
	supCard.nNodPos_T_Beg		= m_nNodPos_T_Beg;
	supCard.nNodPos_T_End		= m_nNodPos_T_End;
	supCard.nNodPos_R_Beg		= m_nNodPos_R_Beg;
	supCard.nNodPos_R_End		= m_nNodPos_R_End;
	supCard.nStartIndex			= m_nStartIndex;
	supCard.nTotal				= m_nTotal;
	///////////////////
	supCard.sup_id		= *pID;
	supCard.SuppProc	= m_SuppProc;
	///////////////////////////////////
	supCard.kode[0]		= (BYTE)m_bTx;
	supCard.kode[1]		= (BYTE)m_bTy;
	supCard.kode[2]		= (BYTE)m_bTz;
	supCard.kode[3]		= (BYTE)m_bRx;
	supCard.kode[4]		= (BYTE)m_bRy;
	supCard.kode[5]		= (BYTE)m_bRz;
	///////////////////////////////////
	supCard.pgap[0]		= (BYTE)m_bTxG;
	supCard.pgap[1]		= (BYTE)m_bTyG;
	supCard.pgap[2]		= (BYTE)m_bTzG;
	supCard.pgap[3]		= (BYTE)m_bRxG;
	supCard.pgap[4]		= (BYTE)m_bRyG;
	supCard.pgap[5]		= (BYTE)m_bRzG;
	///////////////////////////////////
	for(int i=0;i<6;i++)
		supCard.stiffness[i]	= m_CurrentStif[i];
	/////////////////////////////////////////////////// Create, if Fixed Skewed Direction
	supCard.nid_a		= "";				
	supCard.nid_b		= "";				
	supCard.bCN_a		= FALSE;
	supCard.bCN_b		= FALSE;
	////////////////////
	if( m_jcType == JC_X_FIXEDDIR)	
	{
		if(m_NodeList.GetCount() != 2)
		{
			AfxMessageBox("Internal Error\nCSupMouse::FillSupCard\nm_NodeList.GetCount() != 2");
			return MA_ERROR;
		}
		/////////////////////////////
		CDrNode* pNodeA = (CDrNode*)m_NodeList.GetHead();
		CDrNode* pNodeB = (CDrNode*)m_NodeList.GetTail();
		///////
		supCard.nid_a		= pNodeA->GetObjectID();				
		supCard.nid_b		= pNodeB->GetObjectID();				
		supCard.bCN_a		= pNodeA->IsControlNode();
		supCard.bCN_b		= pNodeA->IsControlNode();
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
		supCard.SkewDir.x = pNewX->x;
		supCard.SkewDir.y = pNewX->y;
		supCard.SkewDir.z = pNewX->z;
		/////////////////////////////
	}
	/////////////////////////////////////////////////////////// Tan or Nor?
	supCard.bTanCur		= FALSE;				
	supCard.ID_CP		= "";
	///
	if( m_jcType == JC_X_TAN_CURVE)
	{		
		supCard.bTanCur	= TRUE;				
		supCard.ID_CP	= m_pTanCurve->GetObjectID();
	}
	else
	if( m_jcType == JC_I_TAN_PATCH)	
	{
		supCard.bTanPat	= TRUE;				
		supCard.ID_CP	= m_pNorPatch->GetObjectID();
	}
	else
	if( m_jcType == JC_Z_NOR_PATCH)	
	{
		supCard.bNorPat	= TRUE;				
		supCard.ID_CP	= m_pNorPatch->GetObjectID();
	}
	supCard.GenKind	= m_GenKind;
	supCard.jcType	= m_jcType;
	///////////////////////////////////
	return 0;
}

int CSupMouse::ShowLinSupp(CString* pID)
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
		///////////////////////////////////// LinSup										
		case NSUP_RIGID:
		case NSUP_LINSPRING:
		case NSUP_LINSNUBBER:

			////////////////
			return ShowLinSupp_Node(pID);
			///

		///////////////////////////////////// NonSup										
		case NSUP_NLSPRING:
		case NSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Curve Based										
		///////////////////////////////////// LinSup										
		case CSUP_RIGID:
		case CSUP_LINSPRING:
		case CSUP_LINSNUBBER:

			////////////////
			return ShowLinSupp_Curve(pID);
			///

		///////////////////////////////////// NonSup										
		case CSUP_NLSPRING:
		case CSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSUP_RIGID:
		case PSUP_LINSPRING:
		case PSUP_LINSNUBBER:

			////////////////
			return ShowLinSupp_Patch(pID);
			///

		///////////////////////////////////// NonSup										
		case PSUP_NLSPRING:
		case PSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Solid Based										
		///////////////////////////////////// LinSup										
		case SSUP_RIGID:
		case SSUP_LINSPRING:
		case SSUP_LINSNUBBER:

			////////////////
			return ShowLinSupp_Solid(pID);
			///

		///////////////////////////////////// NonSup										
		case SSUP_NLSPRING:
		case SSUP_NLSNUBBER:
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	}
	return MA_ERROR;
}	

int CSupMouse::ShowLinSupp_Node(CString* pID)
{
	int nResult = MA_OK;
	////////////////////
	m_nNodPos_S_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_S_End = 1;
								// index of Output NodPos in s direction:End
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp MI_LSupp;
	/////////////////////
	SUPPCARD SupCard;
	FillSupCard(SupCard,pID);
	//////////////
	CList<SUPPCARD,SUPPCARD> TempList;
	TempList.RemoveAll();
	TempList.AddTail(SupCard);
	///
	nResult = MI_LSupp.CreateNodeBased(m_pCurrentNode,&TempList);
	///
	SupCard = TempList.GetTail(); 
	m_pCurrentNode->GetSuppCardList()->AddTail(SupCard);
	////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->ShowObject_On_Off(m_pCurrentNode,NODE,TRUE);
/*
	CDListMgr* pSuppList = m_pCurrentNode->GetSuppList(); 
	for (POSITION posI = pSuppList->GetFirstObjectPos( );posI !=NULL;)
	{
		CDrLinSup* pSupp = (CDrLinSup*)pSuppList->GetNext(posI);
		pObjectMgr->ShowObject_On_Off(pSupp,LIN_SUPPORT,TRUE);
	}
*/
	///////////////////////////////
	return MA_OK;
}	 

int CSupMouse::ShowLinSupp_Curve(CString* pID)
{
	int nResult = MA_OK;
	////////////////////
	m_nNodPos_S_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_S_End = m_pCurrentCurve->GetLongOutPts(); // does not recognize "Curve may be Closed!"
								// index of Output NodPos in s direction:End
	if(m_pCurrentCurve->IsClosed_S())
		m_nNodPos_S_End--;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp	MI_LSupp;
	SUPPCARD	SupCard;
	/////////////////////////
	FillSupCard(SupCard,pID);
	//////////////
	CList<SUPPCARD,SUPPCARD> TempList;
	TempList.RemoveAll();
	TempList.AddTail(SupCard);
	///
	nResult = MI_LSupp.CreateCurveBased(m_pCurrentCurve,&TempList);
	///
	SupCard = TempList.GetTail(); 
	m_pCurrentCurve->GetSuppCardList()->AddTail(SupCard);
	////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,TRUE);
/*
	CDListMgr* pSuppList = m_pCurrentCurve->GetSuppList(); 
	for (POSITION posI = pSuppList->GetFirstObjectPos( );posI !=NULL;)
	{
		CDrLinSup* pStatic = (CDrLinSup*)pSuppList->GetNext(posI);
		pObjectMgr->ShowObject_On_Off(pStatic,SUPPORT,TRUE);
	}
*/
	///////////////////////////////
	return MA_OK;

}	 

int CSupMouse::ShowLinSupp_Patch(CString* pID)
{
	int nResult = MA_OK;
	////////////////////
	m_nNodPos_S_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_S_End = m_pCurrentPatch->GetOut_S();
								// index of Output NodPos in s direction:End
	m_nNodPos_T_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_T_End = m_pCurrentPatch->GetOut_T();
								// index of Output NodPos in s direction:End
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(LIN_SUPPORT);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_LSupp MI_LSupp;
	///
	SUPPCARD	SupCard;
	FillSupCard(SupCard,pID);
	//////////////
	CList<SUPPCARD,SUPPCARD> TempList;
	TempList.RemoveAll();
	TempList.AddTail(SupCard);
	///
	if(m_pCurrentPatch->GetPatSubType() == PS_QUADRILAT)
		nResult = MI_LSupp.CreatePatchBased_4(m_pCurrentPatch,&TempList);	// TRUE = NonUniform
	if(m_pCurrentPatch->GetPatSubType() == PS_TRIANGLE)
		nResult = MI_LSupp.CreatePatchBased_3(m_pCurrentPatch,&TempList);	// TRUE = NonUniform
	///
	SupCard = TempList.GetTail(); 
	m_pCurrentPatch->GetSuppCardList()->AddTail(SupCard);
	////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->ShowObject_On_Off(m_pCurrentPatch,PATCH,TRUE);
/*
	CDListMgr* pSuppList = m_pCurrentPatch->GetSuppList(); 
	for (POSITION posI = pSuppList->GetFirstObjectPos( );posI !=NULL;)
	{
		CDrLinSup* pStatic = (CDrLinSup*)pSuppList->GetNext(posI);
		pObjectMgr->ShowObject_On_Off(pStatic,SUPPORT,TRUE);
	}
*/
	///////////////////////////////
	return MA_OK;
}

int CSupMouse::ShowLinSupp_Solid(CString* pID)
{
	return MA_ERROR;
}

void CSupMouse::OnEBoxLButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(m_bSuppDone)			// Reset
	{
		m_bSuppDone		= FALSE;
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
	if( !(GetSupInDlg()->m_hWnd) )
		pWnd->SendMessage(ID_ACTIVE_SUPIN,IDOK);
	//////////////////////////////////////////////////
	m_nActiveObject = pWnd->GetActiveObjectType(); 
	m_nActiveTool	= pWnd->GetActiveToolType();    // -1= INSERT
	/////////////////////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(m_nActiveObject);       // Set ObjectType 
	////////////////////////////////////////////////// take care of Edit AllClear
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	if(!(pDListMgr->GetSpecificObjectCount(NODE)) ) m_nNodeDone = 0;
    /////////////////////////////  ELement Dialog On/Off Check
    if(m_Gener == FORWARD)
		ElementLeftDown_SUP();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CSupMouse::UpdateLinSupDlg_TRUE()
{
	//////////////////////////////////
	m_pSupInDlg->UpdateData(TRUE); // from screen
	////////////
	m_bRx			= GetSupInDlg()->m_bRx;
	m_bRy			= GetSupInDlg()->m_bRy;
	m_bRz			= GetSupInDlg()->m_bRz;
	m_bTx			= GetSupInDlg()->m_bTx;
	m_bTy			= GetSupInDlg()->m_bTy;
	m_bTz			= GetSupInDlg()->m_bTz;
	/////
	m_bRxG			= GetSupInDlg()->m_bRxG;
	m_bRyG			= GetSupInDlg()->m_bRyG;
	m_bRzG			= GetSupInDlg()->m_bRzG;
	m_bTxG			= GetSupInDlg()->m_bTxG;
	m_bTyG			= GetSupInDlg()->m_bTyG;
	m_bTzG			= GetSupInDlg()->m_bTzG;
	//////
	for(int i=0;i<6;i++)
		m_CurrentStif[i]	= GetSupInDlg()->m_dStif[i];
	m_CurrentSupID	= GetSupInDlg()->m_SupID;
	m_SuppProc		= GetSupInDlg()->m_SuppProc;
	/////////////////////////////////////
	m_jcType		= GetSupInDlg()->m_jcType;
}
			
void CSupMouse::UpdateLinSupDlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	UINT IGenID				= pWnd->GetCurrentIGenID(); 
	UINT CntlID				= pWnd->GetCurrentCntlID(); 
	CString strCurr; 
	/////////////////////////////////////////////////////////
	GetSupInDlg()->m_bRx		= m_bRx;
	GetSupInDlg()->m_bRy		= m_bRy;
	GetSupInDlg()->m_bRz		= m_bRz;
	GetSupInDlg()->m_bTx		= m_bTx;
	GetSupInDlg()->m_bTy		= m_bTy;
	GetSupInDlg()->m_bTz		= m_bTz;
	///
	GetSupInDlg()->m_bRxG		= m_bRxG;
	GetSupInDlg()->m_bRyG		= m_bRyG;
	GetSupInDlg()->m_bRzG		= m_bRzG;
	GetSupInDlg()->m_bTxG		= m_bTxG;
	GetSupInDlg()->m_bTyG		= m_bTyG;
	GetSupInDlg()->m_bTzG		= m_bTzG;
	///
	GetSupInDlg()->m_dStif		= m_CurrentStif;
	GetSupInDlg()->m_SupID		= m_CurrentSupID;
	GetSupInDlg()->m_SuppProc	= m_SuppProc;
	/////////////////////////////////////
	GetSupInDlg()->m_jcType		= m_jcType;
	if(m_nInfoDone>=1)
		GetSupInDlg()->GetDlgItem(IDC_SUPID)->EnableWindow(FALSE);
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
					if(m_pSupInDlg->GetSafeHwnd())
						m_pSupInDlg->GetDlgItem(IDC_SUPID)->EnableWindow(TRUE);
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
					strCurr = "Fixed Direction Skewed Support Creation@Click in From-Node defining Direction";
					break;

				case 2:
					strCurr = "Fixed Direction Skewed Support Creation@Click in To-Node defining Direction";
					break;

				case 3:
					strCurr = "Ready with other Info.?@Click Right Button";
					if(m_pSupInDlg->GetSafeHwnd())
						m_pSupInDlg->GetDlgItem(IDC_SUPID)->EnableWindow(TRUE);
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
					if(m_pSupInDlg->GetSafeHwnd())
						m_pSupInDlg->GetDlgItem(IDC_SUPID)->EnableWindow(TRUE);
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
					if(m_pSupInDlg->GetSafeHwnd())
						m_pSupInDlg->GetDlgItem(IDC_SUPID)->EnableWindow(TRUE);
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
	m_pSupInDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}
	
int CSupMouse::LeftUp_Node_SupContext(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
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
			nResult = OldNode_N_Update_SUPContext(m_pFixDirNode->IsControlNode(),bDistinct); // right type
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
			nResult = NewNode_N_Update_SUPContext(strNodeID,point,TRUE); // desired Type is Control Node
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

int CSupMouse::NewNode_N_Update_SUPContext(CString& NodeID,CPoint point,BOOL bCNode)
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
		AfxMessageBox("ERROR:\nCSupMouse::NewNode_OtherContext\nShowNode Problem");
		return MA_ERROR;
	}
	/////////////////////////////////////////////////////////// Update
	m_NodeList.InsertObject(m_pCurrentNode);
	/////////////
	return MA_OK;
}

int CSupMouse::OldNode_N_Update_SUPContext(BOOL bCNode,BOOL bDistinct)
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
				AfxMessageBox("ERROR:\nDegenerate Support Direction:\nSame Node More than Once!");
				return MA_CANCEL;
			}
		}
	}
	/////////////////////
	m_NodeList.InsertObject(m_pFixDirNode);
	/////////////
	return MA_OK;
}

//int CSupMouse::LeftUp_EXTRUDE_PAT(POINT point)
int CSupMouse::LeftUp_JC_X_FIXEDDIR_SUP(POINT point)
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
				nResult = LeftUp_Node_SupContext(point,FALSE,TRUE,FALSE/*NoOtherType*/);
				if(nResult <0)		// Cancel
				{
					m_nNodeDone--;
					return nResult;
				}
				else
					return 0;

		case 2:	m_nNodeDone++;
				nResult = LeftUp_Node_SupContext(point,FALSE,TRUE,FALSE);
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

int CSupMouse::LeftUp_JC_X_TAN_CURVE_SUP(POINT point)
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

int CSupMouse::LeftUp_JC_Z_NOR_PATCH_SUP(POINT point)
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

int CSupMouse::ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart)
{
	int j = jStart;
	////////////////////////////////////////
	// The List Should Have ATMOST 2 items:
	//			1	Lin_Spring 
	//			1	Lin_Snubber
	////////////////////////////////////////
	CDListMgr* pList = pDrNode->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupMouse::FillInfo_NodeLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupMouse::FillInfo_NodeLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		j = ShowInfo_SupCard(supCard, buf, j);
		/////////////////////////////////////////
	}
	//////////
	return j;
}

int CSupMouse::ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrCurve->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupMouse::ShowInfo_CurveLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupMouse::ShowInfo_CurveLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		j = ShowInfo_SupCard(supCard, buf, j);
		/////////////////////////////////////////
	}
	//////////
	return j;
}

int CSupMouse::ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrPatch->GetSuppList();
	///////////////////////////////
	if(pList->GetCount() > 2)
	{
		AfxMessageBox("Internal ERROR:\nCSupMouse::ShowInfo_PatchLinSupport\npList->GetCount() > 2"); 
		return -2;
	}
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrLinSup*	pDrLinSup;
	SUPPCARD	supCard;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		if(i==0)
			pDrLinSup = (CDrLinSup*)pList->GetHead();
		else
			pDrLinSup = (CDrLinSup*)pList->GetTail();
		////
		if(pDrLinSup)
			supCard = *(pDrLinSup->GetSuppCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSupMouse::ShowInfo_PatchLinSupport\npDrLinSup=NULL"); 
			return -2;
		}
		//////
		j = ShowInfo_SupCard(supCard, buf, j);
		/////////////////////////////////////////
	}
	//////////
	return j;
}

int CSupMouse::ShowInfo_SupCard(SUPPCARD& supCard, char* buf, int jStart)
{
	int j = jStart;
	/////////////////////////////////////////
	switch (supCard.SuppProc)
	{
		case SUP_RIGID:
			j = ShowInfo_Rigid(supCard, buf, j);
			break;
		case SUP_LINSPR:	// fall thro'
		case SUP_LINSNU:
			j	= ShowInfo_SprOrSnu(supCard, buf, j);	
			break;
/*	These will be in separate List: NSupList
					case SUP_NONSPR:
						j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SPRING\n");
						FillInfo_NonSpring(supCard,buf,j);
						break;
					case SUP_NONSNU:
						j += sprintf(buf+j,"\n\nSupportType = NONLINEAR SNUBBER\n");
						FillInfo_NonSnubber(supCard,buf,j);
						break;
*/ 
		default:
			break;
	}
	//////////
	return j;
}

int CSupMouse::ShowInfo_Rigid(SUPPCARD supCard,char* buf, int jStart)
{

	int j = jStart;
	///////////////
	j += sprintf(buf+j,"\nSupportID = %s\n",supCard.sup_id);
	j += sprintf(buf+j,"\n\tStiffness = %f\n",supCard.stiffness);
	/////////
	return j;
}

int CSupMouse::ShowInfo_SprOrSnu(SUPPCARD supCard,char* buf, int jStart)
{
	CString dir[] = {"X","Y","Z"};

	int i, j = jStart;
	///////////////
	if(supCard.SuppProc == SUP_LINSPR) 
		j += sprintf(buf+j,"\n\nSupportType = LINEAR SPRING\n");
	else
	if(supCard.SuppProc == SUP_LINSNU) 
		j += sprintf(buf+j,"\n\nSupportType = LINEAR SNUBBER\n");
	else
		return -2;
	//////////////
	j += sprintf(buf+j,"\nSupportID = %s\n",supCard.sup_id);
	/////////////////////////////////////////////////////////////////////// Translational
	j += sprintf(buf+j,"\n\tTranslational:\n");
	for(i=0;i<3;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\t\tDirection %s = SUPPORTED with Stiffness = %f\n",
							dir[i],supCard.stiffness[i]);
		else
			j += sprintf(buf+j,"\t\tDirection %s = UNSUPPORTED\n", dir[i]);
	}
	/////////////////////////////////////////////////////////////////////// Rotational
	j += sprintf(buf+j,"\n\tRotational:\n");
	for(i=3;i<6;i++)
	{
		if((BOOL)supCard.kode[i])
			j += sprintf(buf+j,"\t\tDirection %s = SUPPORTED with Stiffness = %f\n",
							dir[i-3],supCard.stiffness[i-3]);
		else
			j += sprintf(buf+j,"\t\tDirection %s = UNSUPPORTED\n", dir[i-3]);
	}
	/////////////////////////////////////////////////////////////////////// Skewed
	if(supCard.jcType == JC_X_FIXEDDIR)	
	{	
			j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis defined by Nodes:\n");
			j += sprintf(buf+j,"\t%s and %s\n",supCard.nid_a,supCard.nid_b);
	}
	else
	if(supCard.jcType == JC_X_TAN_CURVE)	
	{	
		j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
		j += sprintf(buf+j,"X-axis along Tangent to Curve %s\n",supCard.ID_CP);
	}
	else
	if(supCard.jcType == JC_I_TAN_PATCH)
	{	
		j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
		j += sprintf(buf+j,"X & Y-axis along Iso_Curves to Patch %s\n",supCard.ID_CP);
	}
	else
	if(supCard.jcType == JC_Z_NOR_PATCH)
	{	
		j += sprintf(buf+j,"\nJoint Coordinate is Skewed with\n");
		j += sprintf(buf+j,"Z-axis along Normal to Patch %s\n",supCard.ID_CP);
	}
	else
		; // not skewed
	/////////////////////////////////////////////////////////////////////// PseudoGap
	BOOL bGap = FALSE;
	for(i=0;i<6;i++)
	{
		if((BOOL)supCard.pgap[i])
		{
			bGap = TRUE;
			break;
		}
	}
	////////
	if(bGap)
	{
		j += sprintf(buf+j,"\nSupport Modeled as PseudoGap(s)\n");
		////
		j += sprintf(buf+j,"\n\tTranslational:\n");
		for(i=0;i<3;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\t\tDirection %s = GAP\n", dir[i]);
			else
				j += sprintf(buf+j,"\t\tDirection %s = NONE\n", dir[i]);
		}
		////
		j += sprintf(buf+j,"\n\tRotational:\n");
		for(i=3;i<6;i++)
		{
			if((BOOL)supCard.pgap[i])
				j += sprintf(buf+j,"\t\tDirection %s = GAP\n", dir[i-3]);
			else
				j += sprintf(buf+j,"\t\tDirection %s = NONE\n", dir[i-3]);
		}
		////
	}
	/////////
	return j;
}

int CSupMouse::LeftUp_GetNodeLinSupp(CPoint point)
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

int CSupMouse::LeftUp_Node_Accept_NodeBased(CPoint point,BOOL bCNode)
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
	
int CSupMouse::Show_NodeBased_NodeInfo(CDrNode* pDrNode)
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
	CDListMgr* pList = pDrNode->GetSuppList();
	///////////////////////////////
	if(!pList->IsEmpty())
	{
		//////////////
		j = sprintf(buf,"***** Selected Node is Already Supported  *****\n");
		j += sprintf(buf+j,"\nNodeID = %s\nCoordinates:\n\t X = %f\n\t Y = %f\n\t Z = %f\n",
						ID,wLoc.x,wLoc.y,wLoc.z);
		//////////////////////////
		j = ShowInfo_NodeLinSupport(pDrNode, buf, j);
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing Nodal Support");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Node with New Support Anyway");
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
				"\n\nYES:\tAccept The Existing Nodal Support");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Node");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Node with New Support Anyway");
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
	
int CSupMouse::Show_CurveBased_CurveInfo(CDrCurve* pDrCurve)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrCurve->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrCurve->GetSuppList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Curve is Already Supported  *****\n");
		j += sprintf(buf+j,"\nCurveID = %s ",ID);
		//////////////////////////
		j = ShowInfo_CurveLinSupport(pDrCurve, buf, j);
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing CurveBased Support");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Curve with New Support Anyway");
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
				"\n\nYES:\tAccept The Existing CurveBased Support");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Curve");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Curve with New Support Anyway");
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

//int CSupMouse::LeftUp_CurveLinSupp(CPoint point)
int CSupMouse::LeftUp_GetCurveLinSupp(CPoint point)
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

int CSupMouse::LeftUp_Curve_Accept(CPoint point)
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
	
int CSupMouse::Show_PatchBased_PatchInfo(CDrPatch* pDrPatch)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrPatch->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrPatch->GetSuppList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Patch is Already Supported  *****\n");
		j += sprintf(buf+j,"\nPatchID = %s ",ID);
		//////////////////////////
		j = ShowInfo_PatchLinSupport(pDrPatch, buf, j);
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing PatchBased Support");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Patch with New Support Anyway");
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
				"\n\nYES:\tAccept The Existing PatchBased Support");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Patch");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Patch with New Support Anyway");
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

//int CSupMouse::LeftUp_PatchLinSupp(CPoint point)
int CSupMouse::LeftUp_GetPatchLinSupp(CPoint point)
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

int CSupMouse::LeftUp_Patch_Accept(CPoint point)
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
	
int CSupMouse::ShowSolidInfo(CDrSolid* pDrSolid)
{
	int nResult;
	//////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	/////////////////////////////// Coords
	CString ID = pDrSolid->GetObjectID();
	//////////////////////////////
	CDListMgr* pList = pDrSolid->GetSuppList();
	///////////////////////////////
	if(pList->GetCount())
	{
		//////////////
		j = sprintf(buf,"***** Selected Solid is Already Supported  *****\n");
		j += sprintf(buf+j,"\nSolidID = %s ",ID);
		//////////////////////////
		j = ShowInfo_SolidLinSupport(pDrSolid, buf, j);
		if(j<0)
			return MA_ERROR;
		//////////////
		if(m_ProbLim == PDL_TWO)
		{
			////////////////////////////
			j += sprintf(buf+j,
				"\n\nYES:\tAccept The Existing SolidBased Support");
			j += sprintf(buf+j,
				"\nNO:\tUpdate Solid with New Support Anyway");
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
				"\n\nYES:\tAccept The Existing SolidBased Support");
			j += sprintf(buf+j,
				"\nNO:\tFind Next Matching Solid");
			j += sprintf(buf+j,
				"\nCANCEL:\tUpdate Solid with New Support Anyway");
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

int CSupMouse::ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart)
{
	int nResult = 0;
	////////////////
	nResult = AfxMessageBox("SOLIDBASED SUPPORT\nNOT SUPPORTED YET",MB_YESNO|MB_ICONQUESTION);
	return MA_CANCEL;
}

int CSupMouse::LeftUp_SolidLinSupp(CPoint point)
{
	int nResult = 0;
	////////////////
	nResult = AfxMessageBox("SOLIDBASED SUPPORT\nNOT SUPPORTED YET",MB_YESNO|MB_ICONQUESTION);
	return MA_CANCEL;
}

int CSupMouse::LeftUp_Solid_Accept(CPoint point)
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

int CSupMouse::LeftUp_LinSupp_NODE(POINT point,UINT uSuppProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetNodeLinSupp(point);// FALSE =bCNode
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

			if(uSuppProc == NSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
					break;
				case JC_X_TAN_CURVE:
					nResult = LeftUp_JC_X_TAN_CURVE_SUP(point);
					break;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					nResult = LeftUp_JC_Z_NOR_PATCH_SUP(point);
					break;
				default:
					return MA_ERROR;
			}
			return nResult;


		case 2:

			if(uSuppProc == NSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					break;
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
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

int CSupMouse::LeftUp_LinSupp_CURVE(POINT point,UINT uSuppProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetCurveLinSupp(point);
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
					}
					////////////////////////////////////////////////
					if(m_pCurrentCurve->GetPatchList()->GetCount()<2)
					{
						if(jcType == JC_Z_NOR_PATCH || jcType == JC_I_TAN_PATCH)
						{
							m_pNorPatch = (CDrPatch*)(
								m_pCurrentCurve->GetPatchList()->GetHead());
							m_nInfoDone++;	// bump
						}
					}
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

			if(uSuppProc == CSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
					break;
				case JC_X_TAN_CURVE:
					if(m_nInfoDone>= MAX_INFO_JC_X_TAN_CURVE)
						return nResult;	// No Hit
					break;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					nResult = LeftUp_JC_Z_NOR_PATCH_SUP(point);
					break;
				default:
					return MA_ERROR;
			}
			return nResult;


		case 2:

			if(uSuppProc == CSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					break;
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
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

int CSupMouse::LeftUp_LinSupp_PATCH(POINT point,UINT uSuppProc,JOINTCOORD jcType)
{
	int nResult = MA_NOHIT;
	///////////
	switch(m_nInfoDone)
	{
		case 0:	
			////////////////////
			nResult = LeftUp_GetPatchLinSupp(point);
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
					}
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

			if(uSuppProc == PSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
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

			if(uSuppProc == PSUP_RIGID)
					return nResult;	// No Hit
			////////////////////
			switch(jcType)
			{
				case JC_DEFAULT:
					return nResult;	// No Hit
				case JC_X_FIXEDDIR:
					nResult = LeftUp_JC_X_FIXEDDIR_SUP(point);
					break;
				case JC_X_TAN_CURVE:
					m_pTanCurve = m_pCurrentCurve;
					m_nCurveDone++;
					return MA_OK;
				case JC_I_TAN_PATCH:
				case JC_Z_NOR_PATCH:
					nResult = LeftUp_JC_Z_NOR_PATCH_SUP(point);
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

void CSupMouse::ElementLeftUp_SUP(CPoint point)
{ 
	int nResult;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCur;
	//////////////////////////////////////////////////////////////////
	CString Nid;
	////////////////
	UpdateLinSupDlg_TRUE();
	///////////////////////////////////////////////////////// Check If Any Composelected
	if(!m_bTx && !m_bTy &&!m_bTz && !m_bRx &&!m_bRy && !m_bRz)
	{
		AfxMessageBox(
			"Please Select Atleast\nOne Degree of Freedom\nFrom the DialogBox",
			MB_ICONEXCLAMATION);
		return;
	}
	///////////////////
	SetMainType_SUP();
	///////////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Node Based										
		///////////////////////////////////// LinSup										
		case NSUP_RIGID:
			if(m_nInfoDone >= MAX_INFO_RIGID)
				return;

		case NSUP_LINSPRING:
		case NSUP_LINSNUBBER:

			////////////////
			UpdateLinSupDlg_TRUE();
			nResult = LeftUp_LinSupp_NODE(point,m_nMainType,m_jcType);
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
					Terminate_SUP(TRUE); // TRUE = bError
					Init_SUP();
					return;
			}
			UpdateLinSupDlg_FALSE();
			////////////////
			break;

		///////////////////////////////////// NonSup										
		case NSUP_NLSPRING:
		case NSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Curve Based										
		///////////////////////////////////// LinSup										
		case CSUP_RIGID:
			if(m_nInfoDone >= MAX_INFO_RIGID)
				return;

		case CSUP_LINSPRING:
		case CSUP_LINSNUBBER:

			////////////////
			UpdateLinSupDlg_TRUE();
			nResult = LeftUp_LinSupp_CURVE(point,m_nMainType,m_jcType);
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
					Terminate_SUP(TRUE); // TRUE = bError
					Init_SUP();
					return;
			}
			UpdateLinSupDlg_FALSE();
			////////////////
			break;

		///////////////////////////////////// NonSup										
		case CSUP_NLSPRING:
		case CSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSUP_RIGID:
			if(m_nInfoDone >= MAX_INFO_RIGID)
				return;

		case PSUP_LINSPRING:
		case PSUP_LINSNUBBER:

			////////////////
			UpdateLinSupDlg_TRUE();
			nResult = LeftUp_LinSupp_PATCH(point,m_nMainType,m_jcType);
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
					Terminate_SUP(TRUE); // TRUE = bError
					Init_SUP();
					return;
			}
			UpdateLinSupDlg_FALSE();
			////////////////
			break;

		///////////////////////////////////// NonSup										
		case PSUP_NLSPRING:
		case PSUP_NLSNUBBER:
			break;
		///////////////////////////////////////////////////// Solid Based										
		///////////////////////////////////// LinSup										
		case SSUP_RIGID:
		case SSUP_LINSPRING:
		case SSUP_LINSNUBBER:

			////////////////
			UpdateLinSupDlg_TRUE();
			////////////////////
			nResult = LeftUp_SolidLinSupp(point);	
			///
			switch (nResult)
			{
				case MA_OK:
					break;
				case MA_NOHIT:
				case MA_CANCEL:
					return;
				case MA_ERROR:
				default:
					Terminate_SUP(TRUE); // TRUE = bError
			}
			////////////////////
			UpdateLinSupDlg_FALSE();
			//////////////////// 
			break;

		///////////////////////////////////// NonSup										
		case SSUP_NLSPRING:
		case SSUP_NLSNUBBER:
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
}	

void CSupMouse::OnEBoxMouseMove_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CSupMouse::OnEBoxLButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_SUP(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CSupMouse::OnEBoxRButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
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
		
		////////////////////////////////////////////////// Patch
		case NONE:  
		default:
			break;
	}  
}

int CSupMouse::RightUp_SUPPORT_Error()
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

int CSupMouse::RightUp_LinSup_Premature()
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
	pID			= &m_CurrentSupID; 
	//////////////////////////////////////////////////// Check Adequate Info,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j;
	//////////////////////////////////////
	switch(m_nMainType) 
	{

		case NSUP_RIGID:
		case CSUP_RIGID:
		case PSUP_RIGID:
		case SSUP_RIGID:
			///////////////////////////////////// LinSup										
			if(m_nInfoDone < MAX_INFO_RIGID)
			{
				switch(m_nMainType)
				{
					case NSUP_RIGID: strObj = "Node";	break;
					case CSUP_RIGID: strObj = "Curve";	break;
					case PSUP_RIGID: strObj = "Patch";	break;
					case SSUP_RIGID: strObj = "Solid";	break;
					default: return MA_ERROR; 
				}
				////////////////////
				j = sprintf(buf,"ERROR:\nNeed to Select A %s",strObj);
				/////////////////////////	
				bPreMature = TRUE;
			}
			break;
		///////////////////////////////////////////////////////////// NodeBased
		case NSUP_LINSPRING:
		case NSUP_LINSNUBBER:
			////////////////
			switch(m_jcType)
			{
				case JC_DEFAULT:
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
		///////////////////////////////////////////////////// Curve Based										
		///////////////////////////////////// LinSup										
		case CSUP_LINSPRING:
		case CSUP_LINSNUBBER:
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
		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSUP_LINSPRING:
		case PSUP_LINSNUBBER:
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
		///////////////////////////////////////////////////// Solid Based										
		///////////////////////////////////// LinSup										
		case SSUP_LINSPRING:
		case SSUP_LINSNUBBER:
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
		///////////////////////////////////// NonSup										
		case NSUP_NLSPRING:
		case NSUP_NLSNUBBER:
		case CSUP_NLSPRING:
		case CSUP_NLSNUBBER:
		case PSUP_NLSPRING:
		case PSUP_NLSNUBBER:
		case SSUP_NLSPRING:
		case SSUP_NLSNUBBER:
			////////////////////
			j = sprintf(buf,
				"ERROR:\nNonLinear Support\nNOT SUPPORTED YET!!");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_OK|MB_ICONINFORMATION);
			delete str;
			return MA_ERROR;
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
		sprintf(buf,"Are You Sure You Want to\nDelete Current Support?");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			/////////////////////////////////////// Reset
			Init_SUP();
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

int CSupMouse::RightUp_LinSup_NotAutoAccept()
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
	pID			= &m_CurrentSupID; 
	//////////////////////////////////////////////////// Check Adequate Node,or cancel
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	int j = 0;
	/////////////////////////////////////////////////////////////// Not AutoAccept
	int nResult = ShowAcceptInfo_Support(buf, j);
	////////////////////////////////////
	if(nResult == MA_ERROR)
		return nResult;
	/////////////////////////
	nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
	/////////////////////////
	if(nAnswer == IDCANCEL)
	{
		sprintf(buf,"Are You Sure You Want to\nDelete Current Support?");
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

int CSupMouse::ShowAcceptInfo_Support(char* buf, int& j)
{
	////////////
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// Node Based										
		///////////////////////////////////// LinSup										
		case NSUP_RIGID:
		case NSUP_LINSPRING:
		case NSUP_LINSNUBBER:

			////////////////
			j += sprintf(buf+j,"***** Selected Node-Based Support Info  *****\n");
			return ShowAcceptInfo_NodeBased(m_pCurrentNode,buf,j);
			////////////////

		///////////////////////////////////// NonSup										
		case NSUP_NLSPRING:
		case NSUP_NLSNUBBER:
			return MA_ERROR;
		///////////////////////////////////////////////////// Curve Based										
		///////////////////////////////////// LinSup										
		case CSUP_RIGID:
		case CSUP_LINSPRING:
		case CSUP_LINSNUBBER:

			////////////////
			return ShowAcceptInfo_CurveBased(m_pCurrentCurve,buf,j);
			////////////////

		///////////////////////////////////// NonSup										
		case CSUP_NLSPRING:
		case CSUP_NLSNUBBER:
			return MA_ERROR;
		///////////////////////////////////////////////////// Patch Based										
		///////////////////////////////////// LinSup										
		case PSUP_RIGID:
		case PSUP_LINSPRING:
		case PSUP_LINSNUBBER:

			////////////////
			return ShowAcceptInfo_PatchBased(m_pCurrentPatch,buf,j);
			////////////////
			break;

		///////////////////////////////////// NonSup										
		case PSUP_NLSPRING:
		case PSUP_NLSNUBBER:
			return MA_ERROR;
		///////////////////////////////////////////////////// Solid Based										
		///////////////////////////////////// LinSup										
		case SSUP_RIGID:
		case SSUP_LINSPRING:
		case SSUP_LINSNUBBER:

			////////////////
			return ShowAcceptInfo_SolidBased(m_pCurrentSolid,buf,j);
			//////////////////// 
			break;

		///////////////////////////////////// NonSup										
		case SSUP_NLSPRING:
		case SSUP_NLSNUBBER:
			return MA_ERROR;
		//////////////////////////////////////////////////
		default:  
			return MA_ERROR;
	} 
	////////////
}
	
int CSupMouse::ShowAcceptInfo_NodeBased(CDrNode* pDrNode, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrNode->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nSupport at NodeID = %s\n",ID);
	//////////////////////////
	j = ShowInfo_SupCard(m_supCard, buf, j);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSupMouse::ShowAcceptInfo_CurveBased(CDrCurve* pDrCurve, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrCurve->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nSupport at CurveID = %s\n",ID);
	//////////////////////////
	j = ShowInfo_SupCard(m_supCard, buf, j);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSupMouse::ShowAcceptInfo_PatchBased(CDrPatch* pDrPatch, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrPatch->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nSupport at PatchID = %s\n",ID);
	//////////////////////////
	j = ShowInfo_SupCard(m_supCard, buf, j);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}
	
int CSupMouse::ShowAcceptInfo_SolidBased(CDrSolid* pDrSolid, char* buf, int& j)
{
	/////////////////////////////// ID
	CString ID = pDrSolid->GetObjectID();
	//////////////
	j += sprintf(buf+j,"\nSupport at SolidID = %s\n",ID);
	//////////////////////////
	j = ShowInfo_SupCard(m_supCard, buf, j);
	///////
	if(j<0)
		return MA_ERROR;
	///////////////
	return MA_OK;
}

void CSupMouse::OnEBoxRButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
								UINT nFlags, CPoint point)
{
	int nResult = MA_OK;
	///////////////////////////////////////////////////////// Enable BLine,if needed
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////// Recompute Suppproc,for Drawing Support
	if((m_bTx == TRUE) && (m_bTy == TRUE) && (m_bTz == TRUE)
		 && (m_bRx == TRUE) && (m_bRy == TRUE) && (m_bRz == TRUE) )
		m_SuppProc == SUP_RIGID;
	//////////////////////////////////////////////////// Error 
//	nResult = RightUp_LinSup_Error();
	nResult = MA_OK;
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SUP(TRUE);
			Init_SUP();
			return;
		case MA_GETMOREINFO:
			return;
	}
	//////////////////////////////////////////////////// Premature?
	nResult = RightUp_LinSup_Premature();
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SUP(TRUE);
			Init_SUP();
			return;
		case MA_GETMOREINFO:
			return;
	}
	//////////////////////////////////////////////////// Fill SupCard
	FillSupCard(m_supCard,&m_CurrentSupID);
	/////////////////////////////////////////////////////////////// Not AutoAccept
	if(!m_bAutoAcceptOn)
	{
		nResult = RightUp_LinSup_NotAutoAccept();
		switch(nResult)
		{
		case MA_OK:
			break;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SUP(TRUE);
			Init_SUP();
			return;
		case MA_GETMOREINFO:
			return;
		}
	}
	/////////////////////////////////////////////////////////////////////// Show NewSupport
	nResult = ShowLinSupp(&m_CurrentSupID);		// TRUE = Final
	//////////////////////////////
	switch(nResult)
	{
		case MA_OK:
			/////////////
			pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
			Init_SUP();
			////////////////////
			UpdateLinSupDlg_FALSE();
			//////////////////// 
			return;
		case MA_ERROR:
		case MA_CANCEL:
			Terminate_SUP(TRUE);
			Init_SUP();
			return;
	}
	///////////////
	return;
}
////////////////////////////////////////////////////////////////////	
UINT CSupMouse::ReSetToolID_SUP(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// for jcType
	m_bDoModalDone = FALSE;
	//////////////////////////////////////////// TaskID
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
				//////////////////////////////////////// Support
				case SUPPORT:

//					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "SUPPORT";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "Input@NODE";		ID = SUPPORT;	break;
						case CURVE:			str = "CURVE";			ID = SUPPORT;	break;
						case PATCH:			str = "PATCH";			ID = SUPPORT;	break;
						case SOLID:			str = "SOLID";			ID = SUPPORT;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				//////////////////////////////////////// RIGID Support
				case SUPPORT_RIGID:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Rigid@Support";
					pWnd->SetstrCntlID(str);
					///////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "Input@NODE";		ID = NSUP_RIG_NODE;	break;			;
						case CURVE:			str = "CURVE";			ID = CSUP_RIGID;	break;
						case PATCH:			str = "PATCH";			ID = PSUP_RIGID;	break;
						case SOLID:			str = "SOLID";			ID = SSUP_RIGID;	break;
						default:			str = "UNKNOWN";	ID = UNONE;
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////////////////////// LINSPRING
				case SUPPORT_LINSPRING:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Linear@Spring";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_LSP_NODE;		break;
						case CURVE:			str = "CURVE";		ID = CSUP_LINSPRING;	break;
						case PATCH:			str = "PATCH";		ID = PSUP_LINSPRING;	break;
						case SOLID:			str = "SOLID";		ID = SSUP_LINSPRING;	break;
						default:			str = "UNKNOWN";	ID = UNONE;		
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////////////////////// LINSNUBBER
				case SUPPORT_LINSNUBBER:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "Linear@Snubber";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_LSN_NODE;		break;	
						case CURVE:			str = "CURVE";		ID = CSUP_LINSNUBBER;	break;
						case PATCH:			str = "PATCH";		ID = PSUP_LINSNUBBER;	break;
						case SOLID:			str = "SOLID";		ID = SSUP_LINSNUBBER;	break;
						default:			str = "UNKNOWN";	ID = UNONE;			
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////////////////////// NONSPRING
				case SUPPORT_NLSPRING:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "NonLinear@Spring";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_NSP_NODE;		break;
						case CURVE:			str = "CURVE";		ID = CSUP_NLSPRING;		break;
						case PATCH:			str = "PATCH";		ID = PSUP_NLSPRING;		break;
						case SOLID:			str = "SOLID";		ID = SSUP_NLSPRING;		break;

						default:			str = "UNKNOWN";	ID = UNONE; 				
							pWnd->SetstrIGenID(str);
							return ID;
					}
					break;
				////////////////////////////////// NONSNUBBER
				case SUPPORT_NLSNUBBER:

					pWnd->SetMouseBoxType(SUPPORTBOX);
					str = "NonLinear@RESEVED";
					pWnd->SetstrCntlID(str);
					////////////////////////////////// 
					switch(IGenID)
					{
						/////////
						case NODE:			str = "NODE";		ID = NSUP_NSN_NODE;		break;
						case CURVE:			str = "CURVE";		ID = CSUP_NLSNUBBER;	break;
						case PATCH:			str = "PATCH";		ID = PSUP_NLSNUBBER;	break; 
						case SOLID:			str = "SOLID";		ID = SSUP_NLSNUBBER;	break;
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
			pWnd->SetstrIGenID(str);
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

void CSupMouse::CurrentOperationString(UINT CntlID,UINT IGenID,CString& strCur)
{
	strCur = "Ready for Assignment: ";
	///////////////////////////////////////////////////
	switch(CntlID)
	{
		//////////////////////////////////////// Support
		case SUPPORT:

			strCur += "Supports@";
			strCur += "Select A Support Type";	
			return;
		///////////////////////////////////////// RIGID Support
		case SUPPORT_RIGID:

			strCur += "Rigid Supports@";
			break;
		///////////////////////////////////////// LINSPRING
		case SUPPORT_LINSPRING:

			strCur += "Linear Springs@";
			break;
		///////////////////////////////////////// LINSNUBBER
		case SUPPORT_LINSNUBBER:

			strCur += "Linear Snubbers@";
			break;
		///////////////////////////////////////// NONSPRING
		case SUPPORT_NLSPRING:

			strCur += "NonLinear Springs@";
			break;
		///////////////////////////////////////// NONSNUBBER
		case SUPPORT_NLSNUBBER:

			strCur += "NonLinear Snubbers@";
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

void CSupMouse::ModeLessOff_SUP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetSupInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_SUPIN,IDOK);
}

void CSupMouse::SetMainType_SUP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_nActiveTool	= pWnd->GetActiveToolType();
	///////////////////
	switch(m_nActiveTool) 
	{
	
		case SUPPORT:
			
			m_nMainType	= SUPPORT;
			break;

		///////////////////////////////////////////////////// Static: Node Based										
		case NSUP_RIGID:	
		case NSUP_RIG_NODE:
		case NSUP_RIG_CNODE:
			
			m_nMainType	= NSUP_RIGID;
			break;

		case NSUP_LINSPRING:
		case NSUP_LSP_NODE:
		case NSUP_LSP_CNODE:
			
			m_nMainType	= NSUP_LINSPRING;
			break;

		case NSUP_LINSNUBBER:
		case NSUP_LSN_NODE:
		case NSUP_LSN_CNODE:
			
			m_nMainType	= NSUP_LINSNUBBER;
			break;
		///////////////////////////////////////////////////// Support: Curve Based										
		case CSUP_RIGID:
		case CSUP_RIG_ELLIPSE:
		case CSUP_RIG_PARABOLA:
		case CSUP_RIG_LINEAR:
		case CSUP_RIG_QUADRATIC:
		case CSUP_RIG_CUBIC:
		case CSUP_RIG_HERMITE:
		case CSUP_RIG_BEZIER:
		case CSUP_RIG_BSPLINE:
		case CSUP_RIG_NURB:
		case CSUP_RIG_STITCH:
		case CSUP_RIG_SPAWN:

			m_nMainType	= CSUP_RIGID;
			break;


		case CSUP_LINSPRING:
		case CSUP_LSP_ELLIPSE:
		case CSUP_LSP_PARABOLA:
		case CSUP_LSP_LINEAR:
		case CSUP_LSP_QUADRATIC:
		case CSUP_LSP_CUBIC:
		case CSUP_LSP_HERMITE:
		case CSUP_LSP_BEZIER:
		case CSUP_LSP_BSPLINE:
		case CSUP_LSP_NURB:
		case CSUP_LSP_STITCH:
		case CSUP_LSP_SPAWN:

			m_nMainType	= CSUP_LINSPRING;
			break;


		case CSUP_LINSNUBBER:
		case CSUP_LSN_ELLIPSE:
		case CSUP_LSN_PARABOLA:
		case CSUP_LSN_LINEAR:
		case CSUP_LSN_QUADRATIC:
		case CSUP_LSN_CUBIC:
		case CSUP_LSN_HERMITE:
		case CSUP_LSN_BEZIER:
		case CSUP_LSN_BSPLINE:
		case CSUP_LSN_NURB:
		case CSUP_LSN_STITCH:
		case CSUP_LSN_SPAWN:

			m_nMainType	= CSUP_LINSNUBBER;
			break;
		///////////////////////////////////////////////////// Support: Patch Based										
		case PSUP_RIGID:
		case PSUP_RIG_EXTRUDE:
		case PSUP_RIG_ROTATE:
		case PSUP_RIG_LOFT2:
		case PSUP_RIG_LOFT3:
		case PSUP_RIG_LOFT4:
		case PSUP_RIG_LOFTMANY:
		case PSUP_RIG_SWEEP:
		case PSUP_RIG_DUCT:
		case PSUP_RIG_TENSOR:
		case PSUP_RIG_COONS:
		case PSUP_RIG_GORDON:
		case PSUP_RIG_FLAT:
		case PSUP_RIG_STITCH:
		case PSUP_RIG_SPAWN:

			m_nMainType	= PSUP_RIGID;
			break;


		case PSUP_LINSPRING:
		case PSUP_LSP_EXTRUDE:
		case PSUP_LSP_ROTATE:
		case PSUP_LSP_LOFT2:
		case PSUP_LSP_LOFT3:
		case PSUP_LSP_LOFT4:
		case PSUP_LSP_LOFTMANY:
		case PSUP_LSP_SWEEP:
		case PSUP_LSP_DUCT:
		case PSUP_LSP_TENSOR:
		case PSUP_LSP_COONS:
		case PSUP_LSP_GORDON:
		case PSUP_LSP_FLAT:
		case PSUP_LSP_STITCH:
		case PSUP_LSP_SPAWN:

			m_nMainType	= PSUP_LINSPRING;
			break;



		case PSUP_LINSNUBBER:
		case PSUP_LSN_EXTRUDE:
		case PSUP_LSN_ROTATE:
		case PSUP_LSN_LOFT2:
		case PSUP_LSN_LOFT3:
		case PSUP_LSN_LOFT4:
		case PSUP_LSN_LOFTMANY:
		case PSUP_LSN_SWEEP:
		case PSUP_LSN_DUCT:
		case PSUP_LSN_TENSOR:
		case PSUP_LSN_COONS:
		case PSUP_LSN_GORDON:
		case PSUP_LSN_FLAT:
		case PSUP_LSN_STITCH:
		case PSUP_LSN_SPAWN:

			m_nMainType	= PSUP_LINSNUBBER;
			break;


		case PSUP_NLSPRING:
		case PSUP_NSP_EXTRUDE:
		case PSUP_NSP_ROTATE:
		case PSUP_NSP_LOFT2:
		case PSUP_NSP_LOFT3:
		case PSUP_NSP_LOFT4:
		case PSUP_NSP_LOFTMANY:
		case PSUP_NSP_SWEEP:
		case PSUP_NSP_DUCT:
		case PSUP_NSP_TENSOR:
		case PSUP_NSP_COONS:
		case PSUP_NSP_GORDON:
		case PSUP_NSP_FLAT:
		case PSUP_NSP_STITCH:
		case PSUP_NSP_SPAWN:

			m_nMainType	= PSUP_NLSPRING;
			break;



		case PSUP_NLSNUBBER:
		case PSUP_NSN_EXTRUDE:
		case PSUP_NSN_ROTATE:
		case PSUP_NSN_LOFT2:
		case PSUP_NSN_LOFT3:
		case PSUP_NSN_LOFT4:
		case PSUP_NSN_LOFTMANY:
		case PSUP_NSN_SWEEP:
		case PSUP_NSN_DUCT:
		case PSUP_NSN_TENSOR:
		case PSUP_NSN_COONS:
		case PSUP_NSN_GORDON:
		case PSUP_NSN_FLAT:
		case PSUP_NSN_STITCH:
		case PSUP_NSN_SPAWN:

			m_nMainType	= PSUP_NLSNUBBER;
			break;
		///////////////////////////////////////////////////// Support: Solid Based										
		case SSUP_RIGID:
		case SSUP_RIG_EXTRUDE:
		case SSUP_RIG_ROTATE:
		case SSUP_RIG_LOFT2:
		case SSUP_RIG_LOFT3:
		case SSUP_RIG_LOFT4:
		case SSUP_RIG_LOFTMANY:
		case SSUP_RIG_SWEEP:
		case SSUP_RIG_DUCT:
		case SSUP_RIG_TENSOR:
		case SSUP_RIG_COONS:
		case SSUP_RIG_GORDON:
		case SSUP_RIG_STITCH:
		case SSUP_RIG_SPAWN:

			m_nMainType	= SSUP_RIGID;
			break;


		case SSUP_LINSPRING:
		case SSUP_LSP_EXTRUDE:
		case SSUP_LSP_ROTATE:
		case SSUP_LSP_LOFT2:
		case SSUP_LSP_LOFT3:
		case SSUP_LSP_LOFT4:
		case SSUP_LSP_LOFTMANY:
		case SSUP_LSP_SWEEP:
		case SSUP_LSP_DUCT:
		case SSUP_LSP_TENSOR:
		case SSUP_LSP_COONS:
		case SSUP_LSP_GORDON:
		case SSUP_LSP_STITCH:
		case SSUP_LSP_SPAWN:

			m_nMainType	= SSUP_LINSPRING;
			break;



		case SSUP_LINSNUBBER:
		case SSUP_LSN_EXTRUDE:
		case SSUP_LSN_ROTATE:
		case SSUP_LSN_LOFT2:
		case SSUP_LSN_LOFT3:
		case SSUP_LSN_LOFT4:
		case SSUP_LSN_LOFTMANY:
		case SSUP_LSN_SWEEP:
		case SSUP_LSN_DUCT:
		case SSUP_LSN_TENSOR:
		case SSUP_LSN_COONS:
		case SSUP_LSN_GORDON:
		case SSUP_LSN_STITCH:
		case SSUP_LSN_SPAWN:

			m_nMainType	= SSUP_LINSNUBBER;
			break;


		case SSUP_NLSPRING:
		case SSUP_NSP_EXTRUDE:
		case SSUP_NSP_ROTATE:
		case SSUP_NSP_LOFT2:
		case SSUP_NSP_LOFT3:
		case SSUP_NSP_LOFT4:
		case SSUP_NSP_LOFTMANY:
		case SSUP_NSP_SWEEP:
		case SSUP_NSP_DUCT:
		case SSUP_NSP_TENSOR:
		case SSUP_NSP_COONS:
		case SSUP_NSP_GORDON:
		case SSUP_NSP_STITCH:
		case SSUP_NSP_SPAWN:

			m_nMainType	= SSUP_NLSPRING;
			break;



		case SSUP_NLSNUBBER:
		case SSUP_NSN_EXTRUDE:
		case SSUP_NSN_ROTATE:
		case SSUP_NSN_LOFT2:
		case SSUP_NSN_LOFT3:
		case SSUP_NSN_LOFT4:
		case SSUP_NSN_LOFTMANY:
		case SSUP_NSN_SWEEP:
		case SSUP_NSN_DUCT:
		case SSUP_NSN_TENSOR:
		case SSUP_NSN_COONS:
		case SSUP_NSN_GORDON:
		case SSUP_NSN_STITCH:
		case SSUP_NSN_SPAWN:

			m_nMainType	= SSUP_NLSNUBBER;
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	}
	////////
	return;
}

void CSupMouse::ModeLessOn_SUP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	///////////////////
	SetMainType_SUP();
/*
	//////////////////////
	CMSupMgr* pMSupMgr;
	/////////////////////////////////////////////////////////////// Using MCurMgr
	if(!m_bDoModalDone)
	{		
		if(pMSupMgr->DoModal_Sup_JCType(m_jcType) == IDCANCEL)
		{
			///////////////////////////////////// Reset TaskID
			pWnd->SetCurrentIGenID(SUPPORT);
			pWnd->SendMessage(ID_RESET_MODELESS,0);
			return;
		}
		m_bDoModalDone = TRUE;
	}
*/
	/////////////////////////////////////////////////////////////////// Open
//	if(!(GetSupInDlg()->m_hWnd))
		pWnd->SendMessage(ID_ACTIVE_SUPIN,IDOK); // always, because of different types

}

long CSupMouse::CreateorActivateSupIn(UINT wParam, long lParam)
{
	//////////////////////////// no Op
	if (m_nMainType == SUPPORT)
		return 0L;
	/////////////////////////////////////////////////////////		
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	/////////////////////////////////////////////////////////
	CWnd  wndTopMost;
	///////////////////////////////////////////////////////// 
	if(GetSupInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetSupInDlg()->Create();
		//////////////////////
		CRect BoxRect;
		CWnd  wndTopMost;
		GetSupInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////
		GetSupInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		/////////////////////////////////////
		Init_SUP();
		//////////////////////////////////////////////////////////////  
	}
	else
		GetSupInDlg()->SetActiveWindow();
	///////////////////////////////////////////////////////////////// if SupeDlg Open
	if(GetSupInDlg()->m_hWnd)
	{
		if((UINT)(pWnd->GetActiveViewNumber()) == VIEWISO)
		{
			pWnd->SendMessage(ID_GOODBYE_SUPIN,IDOK);
			return 0L;
		}
	}
	////////////////////////////////////////////////////////////////// CurrStat: Show
	pWnd->GetCurrStat()->ShowWindow(TRUE);
	////////////////////////////////////////////////////////////////// Set Info
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// RigSup:										
		////////////////////////////////// Node Based										
		case NSUP_RIGID:

			m_SuppProc	= SUP_RIGID;
			strCurr = "Creating Node-based Rigid Support:@";
			strCurr		+= "Click on An Existing Input Node";
			//////////////////// 
			break;
		////////////////////////////////// Curve Based										
		case CSUP_RIGID:

			m_SuppProc	= SUP_RIGID;
			strCurr = "Creating Curve-based Rigid Support:@";
			strCurr		+= "Click on An Existing Curve";
			//////////////////// 
			break;
		////////////////////////////////// Patch Based										
		case PSUP_RIGID:

			m_SuppProc	= SUP_RIGID;
			strCurr = "Creating Patch-based Rigid Support:@";
			strCurr		+= "Click on An Existing Patch";
			//////////////////// 
			break;
		////////////////////////////////// Solid Based										
		case SSUP_RIGID:

			m_SuppProc	= SUP_RIGID;
			strCurr = "Creating Solid-based Rigid Support:@";
			strCurr		+= "Click on An Existing Solid";
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSpr:										
		////////////////////////////////// Node Based										
		case NSUP_LINSPRING:

			m_SuppProc	= SUP_LINSPR;
			strCurr = "Creating Node-based Linear Spring@Support: ";
			strCurr		+= "Click on An Existing Input Node";
			//////////////////// 
			break;
		////////////////////////////////// Curve Based										
		case CSUP_LINSPRING:

			m_SuppProc	= SUP_LINSPR;
			strCurr = "Creating Curve-based Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Curve";
			//////////////////// 
			break;
		////////////////////////////////// Patch Based										
		case PSUP_LINSPRING:

			m_SuppProc	= SUP_LINSPR;
			strCurr = "Creating Patch-based Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Patch";
			//////////////////// 
			break;
		////////////////////////////////// Solid Based										
		case SSUP_LINSPRING:

			m_SuppProc	= SUP_LINSPR;
			strCurr = "Creating Solid-based Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Solid";
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSnu:										
		////////////////////////////////// Node Based										
		case NSUP_LINSNUBBER:

			m_SuppProc	= SUP_LINSNU;
			strCurr = "Creating Node-based Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Input Node";
			//////////////////// 
			break;
		////////////////////////////////// Curve Based										
		case CSUP_LINSNUBBER:

			m_SuppProc	= SUP_LINSNU;
			strCurr = "Creating Curve-based Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Curve";
			//////////////////// 
			break;
		////////////////////////////////// Patch Based										
		case PSUP_LINSNUBBER:

			m_SuppProc	= SUP_LINSNU;
			strCurr = "Creating Patch-based Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Patch";
			//////////////////// 
			break;
		////////////////////////////////// Solid Based										
		case SSUP_LINSNUBBER:

			m_SuppProc	= SUP_LINSNU;
			strCurr = "Creating Solid-based Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Solid";
			//////////////////// 
			break;
		///////////////////////////////////////////////////// NonSpr:										
		////////////////////////////////// Node Based										
		case NSUP_NLSPRING:

			m_SuppProc	= SUP_NONSPR;
			strCurr = "Creating Node-based Non-Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Input Node";
			//////////////////// 
			break;
		////////////////////////////////// Curve Based										
		case CSUP_NLSPRING:

			m_SuppProc	= SUP_NONSPR;
			strCurr = "Creating Curve-based Non-Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Curve";
			//////////////////// 
			break;
		////////////////////////////////// Patch Based										
		case PSUP_NLSPRING:

			m_SuppProc	= SUP_NONSPR;
			strCurr = "Creating Patch-based Non-Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Patch";
			//////////////////// 
			break;
		////////////////////////////////// Solid Based										
		case SSUP_NLSPRING:

			m_SuppProc	= SUP_NONSPR;
			strCurr = "Creating Solid-based Non-Linear Spring@ Support:";
			strCurr		+= "Click on An Existing Solid";
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSnu:										
		////////////////////////////////// Node Based										
		case NSUP_NLSNUBBER:

			m_SuppProc	= SUP_NONSNU;
			strCurr = "Creating Node-based Non-Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Input Node";
			//////////////////// 
			break;
		////////////////////////////////// Curve Based										
		case CSUP_NLSNUBBER:

			m_SuppProc	= SUP_NONSNU;
			strCurr = "Creating Curve-based Non-Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Curve";
			//////////////////// 
			break;
		////////////////////////////////// Patch Based										
		case PSUP_NLSNUBBER:

			m_SuppProc	= SUP_NONSNU;
			strCurr = "Creating Patch-based Non-Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Patch";
			//////////////////// 
			break;
		////////////////////////////////// Solid Based										
		case SSUP_NLSNUBBER:

			m_SuppProc	= SUP_NONSNU;
			strCurr = "Creating Solid-based Non-Linear Snubber@ Support:";
			strCurr		+= "Click on An Existing Solid";
			//////////////////// 
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	/////////////////////////////////////////////////// Reset in SupMouse & Sup_Dlg
	GetSupInDlg()->m_SuppProc = m_SuppProc;
	GetSupInDlg()->UpdateData(FALSE);
	///////////////////////////////////////////////////
	GetSupInDlg()->m_bRx		= GetRx();
	GetSupInDlg()->m_bRy		= GetRy();
	GetSupInDlg()->m_bRz		= GetRz();
	GetSupInDlg()->m_bTx		= GetTx();
	GetSupInDlg()->m_bTy		= GetTy();
	GetSupInDlg()->m_bTz		= GetTz();
	///
	GetSupInDlg()->m_bRxG		= GetRxG();
	GetSupInDlg()->m_bRyG		= GetRyG();
	GetSupInDlg()->m_bRzG		= GetRzG();
	GetSupInDlg()->m_bTxG		= GetTxG();
	GetSupInDlg()->m_bTyG		= GetTyG();
	GetSupInDlg()->m_bTzG		= GetTzG();
	///
	GetSupInDlg()->m_dStif		= m_CurrentStif;
	GetSupInDlg()->m_SupID		= m_CurrentSupID;
	GetSupInDlg()->m_SuppProc	= m_SuppProc;
	GetSupInDlg()->m_jcType		= m_jcType;
	///////////////////////////////////////
	if(m_SuppProc == SUP_RIGID)
	{
		////////////////////////////////////////
		GetSupInDlg()->GetDlgItem(IDC_TX)->EnableWindow(FALSE);	
		GetSupInDlg()->GetDlgItem(IDC_TY)->EnableWindow(FALSE);	
		GetSupInDlg()->GetDlgItem(IDC_TZ)->EnableWindow(FALSE);	
		GetSupInDlg()->GetDlgItem(IDC_RX)->EnableWindow(FALSE);	
		GetSupInDlg()->GetDlgItem(IDC_RY)->EnableWindow(FALSE);	
		GetSupInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(FALSE);
	}
	else
	{
		////////////////////////////////////////
		GetSupInDlg()->GetDlgItem(IDC_TX)->EnableWindow(TRUE);	
		GetSupInDlg()->GetDlgItem(IDC_TY)->EnableWindow(TRUE);	
		GetSupInDlg()->GetDlgItem(IDC_TZ)->EnableWindow(TRUE);	
		GetSupInDlg()->GetDlgItem(IDC_RX)->EnableWindow(TRUE);	
		GetSupInDlg()->GetDlgItem(IDC_RY)->EnableWindow(TRUE);	
		GetSupInDlg()->GetDlgItem(IDC_RZ)->EnableWindow(TRUE);
	}
	////////////////////////////////
	GetSupInDlg()->UpdateData(FALSE);
	//////
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////
	return 0L;
}
	 
long CSupMouse::CancelSupIn(UINT wParam, long lParam)
{
	
	GetSupInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSupMouse::GoodByeSupIn(UINT wParam, long lParam)
{
	
	if(GetSupInDlg()->m_hWnd)
		GetSupInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CSupMouse::UpdateSupIn(UINT wParam, long lParam)
{

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	GetSupInDlg()->UpdateData(TRUE);
	///////////////////
	SetMainType_SUP();
	/////////////////////////////////////////////////////////////////// Update
	switch(m_nMainType) 
	{
		
		///////////////////////////////////////////////////// RigSup:										
		case NSUP_RIGID:
		case CSUP_RIGID:
		case PSUP_RIGID:
		case SSUP_RIGID:

			m_SuppProc	= SUP_RIGID;
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSpr:										
		case NSUP_LINSPRING:
		case CSUP_LINSPRING:
		case PSUP_LINSPRING:
		case SSUP_LINSPRING:

			m_SuppProc	= SUP_LINSPR;
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSnu:										
		case NSUP_LINSNUBBER:
		case CSUP_LINSNUBBER:
		case PSUP_LINSNUBBER:
		case SSUP_LINSNUBBER:

			m_SuppProc	= SUP_LINSNU;
			//////////////////// 
			break;
		///////////////////////////////////////////////////// NonSpr:										
		case NSUP_NLSPRING:
		case CSUP_NLSPRING:
		case PSUP_NLSPRING:
		case SSUP_NLSPRING:

			m_SuppProc	= SUP_NONSPR;
			//////////////////// 
			break;
		///////////////////////////////////////////////////// LinSnu:										
		case NSUP_NLSNUBBER:
		case CSUP_NLSNUBBER:
		case PSUP_NLSNUBBER:
		case SSUP_NLSNUBBER:

			m_SuppProc	= SUP_NONSNU;
			//////////////////// 
			break;
		//////////////////////////////////////////////////
		default:  
			break;
	} 
	/////////////////////////////////////////////////// Reset in SupMouse & Sup_Dlg
	GetSupInDlg()->m_SuppProc = m_SuppProc;
	////////////////////////////////
	GetSupInDlg()->UpdateData(FALSE);
	///////////////////////////////// Reset data in ElMouse
	m_CurrentSupID	= GetSupInDlg()->m_SupID;
	///
	SetTx(GetSupInDlg()->m_bTx);
	SetTy(GetSupInDlg()->m_bTy);
	SetTz(GetSupInDlg()->m_bTz);
	SetRx(GetSupInDlg()->m_bRx);
	SetRy(GetSupInDlg()->m_bRy);
	SetRz(GetSupInDlg()->m_bRz);
	///
	SetTxG(GetSupInDlg()->m_bTxG);
	SetTyG(GetSupInDlg()->m_bTyG);
	SetTzG(GetSupInDlg()->m_bTzG);
	SetRxG(GetSupInDlg()->m_bRxG);
	SetRyG(GetSupInDlg()->m_bRyG);
	SetRzG(GetSupInDlg()->m_bRzG);
	///
	SetSuppProc(m_SuppProc);
	//////////
	return 0L;
}

void CSupMouse::Serialize(CArchive& ar)
{

	CSolMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SupMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SupMouse:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////

