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
#include "Def_Ms.h" // Mesh Types for Solch
///////////////////// dialogMgr
#include "MSolMgr.h"  
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
#include "DrPen.h"
#include "Layer.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "mouse.h"
#include "DListMgr.h"
/////////////////////
#include "MI_GangS.h" 
#include "MI_OSPN.h" 
////////////////////// 
#include "Dlg_O3DI.h"
//////////////////////
#include "O3DMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
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
IMPLEMENT_SERIAL(CO3DMouse,CSolMouse,1)
/////////////////////////////////////////////////////////////////////////////
CO3DMouse::CO3DMouse()
{

	m_nInfoDone		= 0;
	m_bObj3DDone	= FALSE;
	////////////////////////////
	m_bObj3DDone		= TRUE;		// for dragging
	m_CurrentObj3DID	= "Ss0";
	m_LastObj3DNum		= 0;		// internal
	///////////////////////////////////////////// 
	m_NodeList.RemoveAll();
	m_CurveList.RemoveAll();
	m_PatchList.RemoveAll();
	m_SolidList.RemoveAll();
	m_Obj3DList.RemoveAll();
	////////////////////////
}

CO3DMouse::~CO3DMouse()
{
/*
	if(!m_NodeList.IsEmpty())
		m_NodeList.RemoveAll();
	if(!m_CurveList.IsEmpty())
		m_CurveList.RemoveAll();
	if(!m_PatchList.IsEmpty())
		m_PatchList.RemoveAll();
	if(!m_SolidList.IsEmpty())
		m_SolidList.RemoveAll();
	if(!m_Obj3DList.IsEmpty())
		m_Obj3DList.RemoveAll();
*/
	/////////////////////////////////// Modeless Dialogs
	if(m_pO3DInDlg)
	{
		if(m_pO3DInDlg->m_hWnd)
			m_pO3DInDlg->DestroyWindow();
		///////////////////
		delete m_pO3DInDlg; 
		///////////////////
	}
}

void CO3DMouse::InitDlgIn_O3D()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////// System Sizes
	m_pO3DInDlg		= new CDlg_O3DI(pWnd); 
}

int CO3DMouse::Terminate_O3D(BOOL bError)
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
	pObjectMgr->SetActiveObjectType(OBJ3D);
	///////////////////////////////////////// delete
	pList = pObjectMgr->GetObjectList(OBJ3D);
	nActiveIndex = pList->GetObjectIndex(OBJ3D, m_CurrentObj3DID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, OBJ3D);
		m_pCurrentObj3D = (CDrObj3D*)NULL;
	}
	/////////////////////////////////////////////////////////
	m_nInfoDone		= 0;	// 
	m_bObj3DDone	= TRUE;	//   
	m_pCurrentObj3D	= NULL;
	//////////////////////////
	m_NodeList.RemoveAll();
	m_CurveList.RemoveAll();
	m_PatchList.RemoveAll();
	m_SolidList.RemoveAll();
	m_Obj3DList.RemoveAll();
	/////////////////// reset
	if(m_pO3DInDlg->GetSafeHwnd())
		m_pO3DInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	/////////////////////////////////////
	pDoc->UpdateAllViews(NULL);
	/////////
	return 0;
}

	
int CO3DMouse::LeftDown_OBJ3D()
{
	return 0;
}
	
void CO3DMouse:: ElementLeftDown_O3D()
{	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CBooleans* pBool		= (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	/////////////////////////////////////////////////////////
//	int nMeshType;
	////////////////////////
	m_bObj3DDone	= FALSE;
	/////////////////////
	switch(m_nActiveTool) 
	{
		
		////////////////////////////////////////////////// OBJ3D
		case OBJ3D:

			LeftDown_OBJ3D();
			return;
		//////////////////////////////////////////////////
		default:
			break;
	}  

}

void CO3DMouse::OnEBoxLButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
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
	if(m_bObj3DDone)			// Reset
	{
		m_nInfoDone		= 0;
		////////////////////
		if(!m_NodeList.IsEmpty())
			m_NodeList.RemoveAll();
		if(!m_CurveList.IsEmpty())
			m_CurveList.RemoveAll();
		if(!m_PatchList.IsEmpty())
			m_PatchList.RemoveAll();
		if(!m_SolidList.IsEmpty())
			m_SolidList.RemoveAll();
		if(!m_Obj3DList.IsEmpty())
			m_Obj3DList.RemoveAll();
	}
	//////////////////////////////////////////////////////// LOG
	m_pdc->DPtoLP(&point);
	///////////////////////////////////////// make sure Dlg is Open
	if( !(GetO3DInDlg()->m_hWnd) )
		pWnd->SendMessage(ID_ACTIVE_O3DIN,IDOK);
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
		ElementLeftDown_O3D();
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftDown_I();
	//////////////////////////////////
}

void CO3DMouse::UpdateODlg_TRUE()
{
	//////////////////////////////////
	m_pO3DInDlg->UpdateData(TRUE); // from screen
	//////////////////////////////
	m_CurrentObj3DID	= GetO3DInDlg()->m_PID;
	////////////
}			

void CO3DMouse::UpdateODlg_FALSE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	GetO3DInDlg()->m_PID		= m_CurrentObj3DID;
	///////////////
	strCurr = "Click in Objects to Include@Hit RightButton to Conclude";
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	m_pO3DInDlg->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

int CO3DMouse::LeftUp_Obj3D_Accept_OtherContext(CPoint point)
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
	pDListMgr	= pObjectMgr->GetObjectList(OBJ3D);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrObj3D*	pDrObj3D;
	int			index;
	///////////////////////////////////////////// See if any Existing Obj3D Hit
	index = IsObjectHit(OBJ3D,point,0);
	/////////////////////////////////////////////////////////////// 
	if(index<0)						
		//////////////// Not Hit
		return -2;
	////////////////////////////////
	pDrObj3D	= (CDrObj3D*)pDListMgr->GetObject(index);
	ID			= pDrObj3D->GetObjectID();
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
		j = sprintf(buf,"***** A SubAssembly Hit ****\n");
		j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
		j = ShowObj3DInfo(pDrObj3D, buf, j);
		////////////////////////////
		j += sprintf(buf+j,
			"\n\nYES:\t\tAccept This Existing SubAssembly");
		j += sprintf(buf+j,
			"\nNO:\t\tFind Next Matching SubAssembly");
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
			m_pCurrentObj3D = pDrObj3D;
			return 1;
		}
		else
		if(nResult == IDNO)
		{
			//////////////////////////////////////////////////////// Retry
			index = IsObjectHit(OBJ3D,point,startIndex);
			/////////////////////////////////////////////////////////////// Right Type
			if(index>=0)
			{
				pDrObj3D	= (CDrObj3D*)pDListMgr->GetObject(index);
				ID			= pDrObj3D->GetObjectID();
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
				j = sprintf(buf,"***** No More Obj3D Found ****\n");
				j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
				/////////////
				delete str;
				nResult = IDNO;
				//////////////// Cancel
				return -2;
			}
		}
	}	// end for Loop			
	//////////////// Cancel
	return -2;
}

int CO3DMouse::LeftUp_Solid_Accept_OtherContext(CPoint point)
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
	pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	CDrSolid*	pDrSolid;
	int			index;
	///////////////////////////////////////////// See if any Existing Solid Hit
	index = IsObjectHit(SOLID,point,0);
	/////////////////////////////////////////////////////////////// 
	if(index<0)						
		//////////////// Not Hit
		return -2;
	////////////////////////////////
	pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
	ID			= pDrSolid->GetObjectID();
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
		j = sprintf(buf,"***** A Solid Hit ****\n");
		j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
		j = ShowSolidInfo(pDrSolid, buf, j);
		////////////////////////////
		j += sprintf(buf+j,
			"\n\nYES:\t\tAccept This Existing Solid");
		j += sprintf(buf+j,
			"\nNO:\t\tFind Next Matching Solid");
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
			m_pCurrentSolid = pDrSolid;
			return 1;
		}
		else
		if(nResult == IDNO)
		{
			//////////////////////////////////////////////////////// Retry
			index = IsObjectHit(SOLID,point,startIndex);
			/////////////////////////////////////////////////////////////// Right Type
			if(index>=0)
			{
				pDrSolid	= (CDrSolid*)pDListMgr->GetObject(index);
				ID			= pDrSolid->GetObjectID();
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
				j = sprintf(buf,"***** No More Solid Found ****\n");
				j += sprintf(buf+j,"(with a Net Sieve of %f)\n",dTol);
				////////////////////////////
				int nResult = AfxMessageBox(*str,MB_OK|MB_ICONEXCLAMATION);
				/////////////
				delete str;
				nResult = IDNO;
				//////////////// Cancel
				return -2;
			}
		}
	}	// end for Loop			
	//////////////// Cancel
	return -2;
}

int CO3DMouse::ShowSolidInfo(CDrSolid* pDrSolid, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	//////////////////////////////////////////////////////////////////////
	SOLIDPROC 		SolProc		= pDrSolid->GetSolidProc();
	SOLSUBTYPE 		SolSubType	= pDrSolid->GetSolSubType();
	//////////////////////////////
	int j = jStart;
	/////////////////////////////// total elems
	switch(SolProc)
	{
		case SP_EXTRUDE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Extrusion\n",*pID);
			break;

		case SP_ROTATE:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s was Generated by Rotation\n",*pID);
			break;

		case SP_LOFT2:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Lofting\n",*pID);
			break;

		case SP_DUCT:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by Ducting\n",*pID);
			break;

		case SP_SWEEP:
			//////////////////////////////////////////////////// Show Solid
			j += sprintf(buf+j,"Solid %s\nGenerated by\nSweeping\n",*pID);
			break;

		case SP_COONS:
			//////////////////////////////////////////////////// Show Solid
//			if(PatSubType == PS_TRIANGLE)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nTriangular Coons Type\n",*pID);
//			else
//			if(PatSubType == PS_QUADRILAT)
				//////////////////////////////////////////////////// Show Solid
				j += sprintf(buf+j,"Solid %s\nQuadrilateral Coons Type\n",*pID);

			////
			break;

		default:
			break;
	}
	/////////
	return j;
}

int CO3DMouse::LeftUp_O3D_Obj3D(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(OBJ3D);
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	///////////////////////////////////////////// See if any Existing Obj3D Hit
	nResult = LeftUp_Obj3D_Accept_OtherContext(point);
	/////////////////////////////////////////////   
	BOOL bError = FALSE;
	switch(nResult)
	{
		case 1:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentObj3D->GetObjectID();
			///////////////////////////////////////// Check if matches previous Obj3Ds,INADMISSIBLE
			if((m_Obj3DList.GetObjectIndex(OBJ3D,ID) ) >=0)
				bError = TRUE;
			//////////////////
			if(bError)
			{
				AfxMessageBox("ILLEGAL Selection :\nSame SubAssembly More than Once!");
				return -2;
			}
			/////////////////////////////////////////////
			break;
		case 0:			// Hit Not , cancel	fall thro
		case -2:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentObj3D,OBJ3D,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurO3DObj3D					= m_pCurrentObj3D;
	m_pOldO3DObj3D					= m_pCurO3DObj3D;
	m_Obj3DList.InsertObject(m_pCurrentObj3D);
	/////////
	return 0;
}

int CO3DMouse::LeftUp_O3D_Solid(POINT point)
{
	int nResult = 0;
	////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	pDListMgr	= pObjectMgr->GetObjectList(SOLID);
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	///////////////////////////////////////////// See if any Existing Solid Hit
	nResult = LeftUp_Solid_Accept_OtherContext(point);
	/////////////////////////////////////////////   
	BOOL bError = FALSE;
	switch(nResult)
	{
		case 1:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentSolid->GetObjectID();
			///////////////////////////////////////// Check if matches previous Solids,INADMISSIBLE
			if((m_SolidList.GetObjectIndex(SOLID,ID) ) >=0)
				bError = TRUE;
			//////////////////
			if(bError)
			{
				AfxMessageBox("ILLEGAL Selection :\nSame Solid More than Once!");
				return -2;
			}
			/////////////////////////////////////////////
			break;
		case 0:			// Hit Not , cancel	fall thro
		case -2:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentSolid,SOLID,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurO3DSolid					= m_pCurrentSolid;
	m_pOldO3DSolid					= m_pCurO3DSolid;
	m_SolidList.InsertObject(m_pCurrentSolid);
	/////////
	return 0;
}

int CO3DMouse::LeftUp_O3D_Patch(POINT point)
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
	///////////////////////////////////////////// See if any Existing Patch Hit
	nResult = LeftUp_Patch_Accept_OtherContext(point);
	/////////////////////////////////////////////   
	BOOL bError = FALSE;
	switch(nResult)
	{
		case 1:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentPatch->GetObjectID();
			///////////////////////////////////////// Check if matches previous Patchs,INADMISSIBLE
			if((m_PatchList.GetObjectIndex(PATCH,ID) ) >=0)
				bError = TRUE;
			//////////////////
			if(bError)
			{
				AfxMessageBox("ILLEGAL Selection :\nSame Patch More than Once!");
				return -2;
			}
			/////////////////////////////////////////////
			break;
		case 0:			// Hit Not , cancel	fall thro
		case -2:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentPatch,PATCH,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurO3DPatch					= m_pCurrentPatch;
	m_pOldO3DPatch					= m_pCurO3DPatch;
	m_PatchList.InsertObject(m_pCurrentPatch);
	/////////
	return 0;
}

int CO3DMouse::LeftUp_O3D_Curve(POINT point)
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
	BOOL bError = FALSE;
	switch(nResult)
	{
		case 1:		// Accept Old One
			/////////////////////////////////////
			ID	= m_pCurrentCurve->GetObjectID();
			///////////////////////////////////////// Check if matches previous Curves,INADMISSIBLE
			if((m_CurveList.GetObjectIndex(CURVE,ID) ) >=0)
				bError = TRUE;
			//////////////////
			if(bError)
			{
				AfxMessageBox("ILLEGAL Selection :\nSame Curve More than Once!");
				return -2;
			}
			/////////////////////////////////////////////
			break;
		case 0:			// Hit Not , cancel	fall thro
		case -2:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentCurve,CURVE,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurO3DCurve					= m_pCurrentCurve;
	m_pOldO3DCurve					= m_pCurO3DCurve;
	m_CurveList.InsertObject(m_pCurrentCurve);
	/////////////////////////////////////////////////
	return 0;
}

int CO3DMouse::LeftUp_O3D_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType)
{
	///////////////////////////////////////////////////////////////////////
	//	bDistinct		=		TRUE	-> Should Not be in m_NODELIST
	//							FALSE	-> DONT CARE
	//	bNoOtherType	=		TRUE	-> Should Not be other than Type dictated by bCNode
	//							FALSE	-> DONT CARE
	///////////////////////////////////////////////////////////////////////
	int nResult = 0;
	////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetNodeList_OtherContext(bCNode,pWnd->IsMeshMode());		
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	//////////////////////////////////////////////////////////////////
	CString ID;
	///////////////////////////////////////////// See if any Existing Node Hit
	m_bCorINodeOpDone = FALSE;	// will not ask to create new node
	nResult = LeftUp_Node_Accept_OtherContext(point,bCNode,pWnd->IsMeshMode(),
						m_bCorINodeOpDone,m_bAutoAcceptOn,&m_pCurrentNode);
	/////////////////////////////////////////////   
	BOOL bError = FALSE;
	switch(nResult)
	{
		case MA_ACCEPTOLD:		// Accept Old One
			/////////////////// matches previous Node in m_NodeList,INADMISSIBLE
			nResult = OldNode_N_Update_CURContext(m_pCurrentNode->IsControlNode(),bDistinct); // right type
				return nResult;
		case MA_NOHIT:			// Hit Not , cancel	fall thro
		case MA_CANCEL:		// Cancel
			return -2;
		default:		// Error
			return -1;
	}
	/////////////////////////////////////////
	if(bCNode)
		pObjectMgr->ShowObject_On_Off(m_pCurrentNode,CNODE,TRUE);
	else
		pObjectMgr->ShowObject_On_Off(m_pCurrentNode,NODE,TRUE);
	/////////////////////////////////////////////////  VALID:Progess
	m_pCurO3DNode					= m_pCurrentNode;
	m_pOldO3DNode					= m_pCurO3DNode;
	m_NodeList.InsertObject(m_pCurrentNode);
	/////////////////////////////////////////////////
	return 0;
}

void CO3DMouse::ElementLeftUp_O3D(CPoint point)
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
	UpdateODlg_TRUE();
	///
	if(LeftUp_O3D_Obj3D(point)<0)
	{
		if(LeftUp_O3D_Solid(point)<0)
		{
			if(LeftUp_O3D_Patch(point)<0)
			{
				if(LeftUp_O3D_Curve(point)<0)
				{
					if(LeftUp_O3D_Node(point,FALSE,TRUE,TRUE)<0)
						return;
				}
			}
		}
	}
	else
	{
		UpdateODlg_FALSE();
		////////////////
		return;
	}
	//////////////////////////////////////////////////
	return;
}	

void CO3DMouse::OnEBoxMouseMove_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
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

void CO3DMouse::OnEBoxLButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
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
		ElementLeftUp_O3D(Logpoint);
	else	
    if(m_Gener == REVERSE)
		;
//		ElementLeftUp_I();
	/////////////////
	PostLeft();
	/////////////////////////
	
}

void CO3DMouse::OnEBoxRButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
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
		case OBJ3D:
			break;
		////////////////////////////////////////////////// Solid
		default:
			break;
	}  
}

int CO3DMouse::RightUp_Premature_O3D()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
	////////////////////////////////////////////////////// Add to DataBase
	CString* pID;
	int		nAnswer = IDOK;
	BOOL	bPremature = FALSE;
	////////////////////////////////
	pID			= &m_CurrentObj3DID; 
	//////////////////////////////////////////////////// Check Adequate Curve,or cancel
	if(m_NodeList.IsEmpty()  && m_CurveList.IsEmpty() &&
	   m_PatchList.IsEmpty() && m_SolidList.IsEmpty() &&
	   m_Obj3DList.IsEmpty() )
	{	 
		bPremature = TRUE;
		nAnswer = AfxMessageBox(
				"Minimum of 1 Node,Curve,Patch,Solid or SubAsembly Needed\n Do You want to Continue to Get More Info. ?",
				MB_YESNO|MB_ICONQUESTION );
		/////////////////////////
		return -1;
	}
	//////////////////////////////////////////////////////// OK
	if(!bPremature)
		return 0;
	//////////////////////////////////////////////////////// ReConfirm: Don't Continue			
	if(nAnswer == IDNO)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"Do You Want to Delete\nCurrent SubStructure to Start Allover");
		/////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
		///////////
		delete str;
		/////////////////////////
		if(nAnswer == IDYES)		//delete
		{
			///////////////////////////////////////// delete
			pList = pObjectMgr->GetObjectList(OBJ3D);
			int nActiveIndex = pList->GetObjectIndex(OBJ3D, *pID);
			//////////////////////////////////////////////////// Reset
			pObjectMgr->DeleteFromDataBase(nActiveIndex, OBJ3D);
			/////////////////////////////////////// Reset
			m_nInfoDone		= 0;
			m_bObj3DDone	= TRUE;	// 
			//////////////////////////
			m_pCurrentObj3D = NULL;
			m_NodeList.RemoveAll();
			m_CurveList.RemoveAll();
			m_PatchList.RemoveAll();
			m_SolidList.RemoveAll();
			m_Obj3DList.RemoveAll();
			/////////////////// reset
			if(m_pO3DInDlg->GetSafeHwnd())
				m_pO3DInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			/////////////////////////////////////
			pDoc->UpdateAllViews(NULL);
			///////////////////////////
		}
		///////////
	}
	////////
	return -1;
}	

int CO3DMouse::RightUp_NotAutoAccept_O3D()
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	CDListMgr*	pList;
	CDrObj3D*	pDrObj3D;
	CDrSolid*	pDrSolid;
	CDrPatch*	pDrPatch;
	CDrCurve*	pDrCurve;
	CDrNode*	pDrNode;
	////
	int			nItems;
	////////////////////////////////////////////////////// Add to DataBase
	CString* pID;
	int i;
	int nAnswer = IDOK;
	////////////////////////////////
	pID			= &m_CurrentObj3DID; 
	////////////////////////////////
	if(!m_bAutoAcceptOn)
	{
		///////////////////////////////////////////////////////////// show Info
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j;
		//////////////////////////////////////////////////// Check Adequate or cancel
		j = sprintf(buf,"SubAssembly %s contains:\n",*pID);
		///
		nItems = m_Obj3DList.GetCount();
		j += sprintf(buf + j,"\t%d SubAssembliess",nItems);
		for(i=0;i<nItems;i++)
		{
			if(i==0)
				j += sprintf(buf + j,":\n\t");
			pDrObj3D = (CDrObj3D*)(m_Obj3DList.GetObject(i) );
			j += sprintf( buf + j, "%s, ",pDrObj3D->GetObjectID());
		}
		sprintf( buf + j-2, "; ");
		///
		nItems = m_SolidList.GetCount();
		j += sprintf(buf + j,"\n\t%d Solids",nItems);
		for(i=0;i<nItems;i++)
		{
			if(i==0)
				j += sprintf(buf + j,":\n\t");
			pDrSolid = (CDrSolid*)(m_SolidList.GetObject(i) );
			j += sprintf( buf + j, "%s, ",pDrSolid->GetObjectID());
		}
		sprintf( buf + j-2, "; ");
		///
		nItems = m_PatchList.GetCount();
		j += sprintf(buf + j,"\n\t%d Patches",nItems);
		for(i=0;i<nItems;i++)
		{
			if(i==0)
				j += sprintf(buf + j,":\n\t");
			pDrPatch = (CDrPatch*)(m_PatchList.GetObject(i) );
			j += sprintf( buf + j, "%s, ",pDrPatch->GetObjectID());
		}
		sprintf( buf + j-2, "; ");
		///
		nItems = m_CurveList.GetCount();
		j += sprintf(buf + j,"\n\t%d Curves",nItems);
		for(i=0;i<nItems;i++)
		{
			if(i==0)
				j += sprintf(buf + j,":\n\t");
			pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
			j += sprintf( buf + j, "%s, ",pDrCurve->GetObjectID());
		}
		sprintf( buf + j-2, "; ");
		///
		nItems = m_NodeList.GetCount();
		j += sprintf(buf + j,"\n\t%d Nodes",nItems);
		for(i=0;i<nItems;i++)
		{
			if(i==0)
				j += sprintf(buf + j,":\n\t");
			pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
			j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
		}
		sprintf( buf + j-2, "; ");
		/////////////////////////
		if(j>BUFF_SIZE)
		{
			sprintf( buf, "Internal Error:\nIncrease buffer to %d",j);
			AfxMessageBox(*str);
			delete str;
			return -1;
		}	 
		///////////////////////////////////////////////////////////////	
		nAnswer = AfxMessageBox(*str,MB_OKCANCEL|MB_ICONQUESTION );
		/////////////////////////
		if(nAnswer == IDCANCEL)
		{
			sprintf(buf,"Do You Want to Delete\nCurrent SubStructure to Start Allover");
			/////////////////////////	
			nAnswer = AfxMessageBox(*str,MB_YESNO|MB_ICONQUESTION);
			/////////////////////////
			if(nAnswer == IDYES)		//delete
			{
				///////////////////////////////////////// delete
				pList = pObjectMgr->GetObjectList(OBJ3D);
				int nActiveIndex = pList->GetObjectIndex(OBJ3D, *pID);
				//////////////////////////////////////////////////// Reset
				pObjectMgr->DeleteFromDataBase(nActiveIndex, OBJ3D);
				/////////////////////////////////////// Reset
				m_nInfoDone		= 0;	// 
				m_bObj3DDone	= TRUE;	// 
				m_pCurrentObj3D	= NULL;	// 
				//////////////////////////
				m_NodeList.RemoveAll();
				m_CurveList.RemoveAll();
				m_PatchList.RemoveAll();
				m_SolidList.RemoveAll();
				m_Obj3DList.RemoveAll();
				/////////////////////////////////////
				pDoc->UpdateAllViews(NULL);
				///////////////////////////
				delete str;
				///////////
				return -1;
			}
		}
		/////////////////////
		delete str;
		return 0; 
	}
	/////////
	return 0;
}

int CO3DMouse::ShowObj3DInfo(CDrObj3D* pDrObj3D, char* buf, int jStart)
{
	CString ID;
	CString* pID = &ID;
	//////////////////////////////
	int j = jStart;
	int i,nItems;
	//////////////////////////////////////////////////// Check Adequate or cancel
	j += sprintf(buf+j,"SubAssembly %s contains:\n",pDrObj3D->GetObjectID());
	///
	nItems = m_Obj3DList.GetCount();
	j += sprintf(buf + j,"\t%d SubAssembliess",nItems);
	for(i=0;i<nItems;i++)
	{
		if(i==0)
			j += sprintf(buf + j,":\n\t");
		pDrObj3D = (CDrObj3D*)(m_Obj3DList.GetObject(i) );
		j += sprintf( buf + j, "%s, ",pDrObj3D->GetObjectID());
	}
	sprintf( buf + j-2, "; ");
	///
	nItems = m_SolidList.GetCount();
	j += sprintf(buf + j,"\n\t%d Solids",nItems);
	for(i=0;i<nItems;i++)
	{
		if(i==0)
			j += sprintf(buf + j,":\n\t");
		CDrSolid* pDrSolid = (CDrSolid*)(m_SolidList.GetObject(i) );
		j += sprintf( buf + j, "%s, ",pDrSolid->GetObjectID());
	}
	sprintf( buf + j-2, "; ");
	///
	nItems = m_PatchList.GetCount();
	j += sprintf(buf + j,"\n\t%d Patches",nItems);
	for(i=0;i<nItems;i++)
	{
		if(i==0)
			j += sprintf(buf + j,":\n\t");
		CDrPatch* pDrPatch = (CDrPatch*)(m_PatchList.GetObject(i) );
		j += sprintf( buf + j, "%s, ",pDrPatch->GetObjectID());
	}
	sprintf( buf + j-2, "; ");
	///
	nItems = m_CurveList.GetCount();
	j += sprintf(buf + j,"\n\t%d Curves",nItems);
	for(i=0;i<nItems;i++)
	{
		if(i==0)
			j += sprintf(buf + j,":\n\t");
		CDrCurve* pDrCurve = (CDrCurve*)(m_CurveList.GetObject(i) );
		j += sprintf( buf + j, "%s, ",pDrCurve->GetObjectID());
	}
	sprintf( buf + j-2, "; ");
	///
	nItems = m_NodeList.GetCount();
	j += sprintf(buf + j,"\n\t%d Nodes",nItems);
	for(i=0;i<nItems;i++)
	{
		if(i==0)
			j += sprintf(buf + j,":\n\t");
		CDrNode* pDrNode = (CDrNode*)(m_NodeList.GetObject(i) );
		j += sprintf( buf + j, "%s, ",pDrNode->GetObjectID());
	}
	/////////
	return j;
}



int CO3DMouse::ShowObj3D(CString* pID)
{
	int nResult =0;
	///////////////
	CDrGrafFrame*	pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString			strCurr;
	////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////////////////// Show NewSolid
	int nActiveIndex;
	///////////////////////////
	m_pCurrentObj3D	= (CDrObj3D*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,OBJ3D));
	m_pCurrentObj3D->SetShow(FALSE);	// not quite ready
	////////////////////////////////
	strCurr = "Please Wait";
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////////////////////////// Copy Lists
	if(!m_Obj3DList.IsEmpty())
		m_pCurrentObj3D->GetObj3DList()->InsertObject(&m_Obj3DList);
	if(!m_SolidList.IsEmpty())
		m_pCurrentObj3D->GetSolidList()->InsertObject(&m_SolidList);
	if(!m_PatchList.IsEmpty())
		m_pCurrentObj3D->GetPatchList()->InsertObject(&m_PatchList);
	if(!m_CurveList.IsEmpty())
		m_pCurrentObj3D->GetCurveList()->InsertObject(&m_CurveList);
	if(!m_NodeList.IsEmpty())
		m_pCurrentObj3D->GetNodeList()->InsertObject(&m_NodeList);
	////////////////////////////////////////////////////////////////////// Show
	m_pCurrentObj3D->SetShow(TRUE);
	m_pCurrentObj3D->SetDirty(TRUE);
	/////////////////////////////////////////
	pObjectMgr->ShowObject_On_Off(m_pCurrentObj3D,OBJ3D,TRUE);
	/////////////////////////////////////////////////////////// Update Obj3D Topology
	nResult = O3DTopo_Update(m_pCurrentObj3D,&m_Obj3DList,&m_SolidList,
									&m_PatchList,&m_CurveList,&m_NodeList);
	if(nResult<0)
		return MA_ERROR;
	/////////////
	return MA_OK;
}

int CO3DMouse::O3DTopo_Update(CDrObj3D* pCurrentObj3D,CDListMgr* pCurrentO3DList,
							CDListMgr* pCurrentSolList,CDListMgr* pCurrentPatList,
							CDListMgr* pCurrentCurList,CDListMgr* pCurrentNodList)
{
	////////////////
	int nResult = 0;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////////////////////// Obj3D_dependent Connection 
	int i,nCount;
	///////////////////
	nCount = pCurrentO3DList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrObj3D* pObj3D	= (CDrObj3D*)(pCurrentO3DList->GetObject(i));
		////////////////
		if(!pObj3D)
		{
			AfxMessageBox(
				"Internal ERROR:\nCO3DMouse::O3DTopo_Update\n!pObj3D");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pO3DList = pObj3D->GetObj3DList();
		///
		nResult = O3DTopo_ConnectObjects(pCurrentObj3D,pO3DList);
		if(nResult<0)
			return nResult;
		///
	}
	/////////////////////////////////////////////////////////// Solid_dependent Connection 
	nCount = pCurrentSolList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrSolid* pSolid	= (CDrSolid*)(pCurrentSolList->GetObject(i));
		////////////////
		if(!pSolid)
		{
			AfxMessageBox(
				"Internal ERROR:\nCO3DMouse::O3DTopo_Update\n!pSolid");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pO3DList = pSolid->GetObj3DList();
		///
		nResult = O3DTopo_ConnectObjects(pCurrentObj3D,pO3DList);
		if(nResult<0)
			return nResult;
		///
	}
	/////////////////////////////////////////////////////////// Patch_dependent Connection 
	nCount = pCurrentPatList->GetCount();
	///
	for(i=0;i<nCount;i++)	
	{
		CDrPatch* pPatch	= (CDrPatch*)(pCurrentPatList->GetObject(i));
		////////////////
		if(!pPatch)
		{
			AfxMessageBox(
				"Internal ERROR:\nCO3DMouse::O3DTopo_Update\n!pPatch");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pO3DList = pPatch->GetObj3DList();
		///
		nResult = O3DTopo_ConnectObjects(pCurrentObj3D,pO3DList);
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
				"Internal ERROR:\nCO3DMouse::O3DTopo_Update\n!pCurve");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pO3DList = pCurve->GetObj3DList();
		///
		nResult = O3DTopo_ConnectObjects(pCurrentObj3D,pO3DList);
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
				"Internal ERROR:\nCO3DMouse::O3DTopo_Update\n!pNode");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		CDListMgr* pO3DList = pNode->GetObj3DList();
		///
		nResult = O3DTopo_ConnectObjects(pCurrentObj3D,pO3DList);
		if(nResult<0)
			return nResult;
		///
	}
	//////////////
	return nResult;
}

int CO3DMouse::O3DTopo_ConnectObjects(CDrObj3D* pCurrentObject,CDListMgr* pList)
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
		CDrObj3D* pObject	= (CDrObj3D*)(pList->GetObject(j));
		////////////////
		if(!pObject)
		{
			AfxMessageBox(
				"Internal ERROR:\nCO3DMouse::O3DTopo_ConnectObjects\n!pObject");
			nResult = -1;
			return nResult;
		}
		///////////////////////////////////////////////////////// 
		if(pObject != pCurrentObject)	// EXIST in other Obj3D
		{
			pObjObjList = pCurrentObject->GetObj3DList();
			///
			index = pObjObjList->GetObjectIndex(pObject);
			if(index<0)		// not in the list yet
			pObjObjList->InsertObject(pObject);
			////////////////////////////////////// Reciprocate Solid, if necessary
			pObjObjList = pObject->GetObj3DList();
			index = pObjObjList->GetObjectIndex(pCurrentObject);
			if(index<0)		// not in the list yet
				pObjObjList->InsertObject(pCurrentObject);
		}
	}
	///////////////
	return nResult;
}			

void CO3DMouse::OnEBoxRButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
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
	UpdateODlg_TRUE();
	///////////////////////////////////////////////////////// Is Enough Info?
	nResult = RightUp_Premature_O3D();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_O3D(TRUE);return;
		case MA_CANCEL:Terminate_O3D(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	///////////////////////////////////////////////////////// Not Auto Accept
	nResult = RightUp_NotAutoAccept_O3D();
	//////////////////////////////////
	switch(nResult)
	{
		case MA_OK:break;
		case MA_ERROR:Terminate_O3D(TRUE);return;
		case MA_CANCEL:Terminate_O3D(TRUE);return;
		case MA_GETMOREINFO:return;
	}
	///////////////////////////////////////////////////// Show Obj3D 
	switch(m_nActiveTool) 
	{

			
		case OBJ3D:
						
			/////////////////////////////
			nResult = ShowObj3D(&m_CurrentObj3DID);
			switch(nResult)
			{
				case MA_OK:break;
				case MA_ERROR:Terminate_O3D(TRUE);return;
				case MA_CANCEL:Terminate_O3D(TRUE);return;
			}
			/////////
			UpdateODlg_FALSE();
			///////////////////	
			return;
		
		
		default:  
			break;
	} 
	/////////////////////////////////////////
	pWnd->GetMouseMgr()->SetCurrentProcessDone(TRUE);
	/////////////////////////////////////// Set Obj3DID
	*pID = m_pCurrentObj3D->GetObjectID(); 
	if(*pID == m_CurrentObj3DID)
		pObjectMgr->SetObjInfoID(m_CurrentObj3DID,OBJ3D);
	////////////////////////// reset
	m_nInfoDone		= 0;	// 
	m_bObj3DDone	= TRUE;	//   
	m_pCurrentObj3D	= NULL;
	//////////////////////////
	m_NodeList.RemoveAll();
	m_CurveList.RemoveAll();
	m_PatchList.RemoveAll();
	m_SolidList.RemoveAll();
	m_Obj3DList.RemoveAll();
	/////////////////////////////////////// Reset
	if(m_pO3DInDlg->GetSafeHwnd())
		m_pO3DInDlg->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	/////////////////////////////////////
	return;
	////

}
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CO3DMouse::ReSetToolID_O3D(UINT CntlID,UINT IGenID, UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	//////////////////////////////////////////// TaskID
	strCur = "Ready for Defining SubStructure. Select Node@";
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
						case OBJ3D:			str = "Sub@Structure";				ID = OBJ3D;
								strCur += "Curve,Patch,Solid or SubStructure";	break;
						default:			str = "UNKNOWN@OBJ3D";			ID = UNONE; 		break;
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
	
void CO3DMouse::ModeLessOff_O3D()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	if(GetO3DInDlg()->m_hWnd)
		pWnd->SendMessage(ID_GOODBYE_O3DIN,IDOK);
}

void CO3DMouse::ModeLessOn_O3D()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////////////////////
//		if(!(GetSolInDlg()->m_hWnd))
			pWnd->SendMessage(ID_ACTIVE_O3DIN,IDOK);

}

long CO3DMouse::CreateorActivateO3DIn(UINT wParam, long lParam)
{
	
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	/////////////////////////////////////////////////////////
	if(GetO3DInDlg()->GetSafeHwnd() ==0)	// not created already
	{
		GetO3DInDlg()->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		GetO3DInDlg()->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		GetO3DInDlg()->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
		//////////////////////////////////////////////////////////////  
	}
	else
	{
		GetO3DInDlg()->SetActiveWindow();
		GetO3DInDlg()->ResetDlg();
	}
	///////////////////////// CurrStat: Show
	strCur = "Defining SubStructure. Click In Node@";
	strCur += "Curve,Patch,Solid or SubStructure";
	////////////////////////////////////////////////////////////////// Set Info
	GetO3DInDlg()->m_PID		= m_CurrentObj3DID;
	////////////////////////////////
	GetO3DInDlg()->UpdateData(FALSE);
	///////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCur);
	pWnd->UpdateCurrStat(strCur);
	////////////////////////////////
	return 0L;
}
	 
long CO3DMouse::GoodByeO3DIn(UINT wParam, long lParam)
{
	
	GetO3DInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CO3DMouse::CancelO3DIn(UINT wParam, long lParam)
{
	
	GetO3DInDlg()->DestroyWindow();
	//////////
	return 0L;
}
	 
long CO3DMouse::UpdateO3DIn(UINT wParam, long lParam)
{

	GetO3DInDlg()->UpdateData(TRUE);
	//////////////////////////////////////
	UpdateODlg_TRUE();
	//////////
	return 0L;
}

void CO3DMouse::Serialize(CArchive& ar)
{

	CSolMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" O3DMouse:    Storing\n");	
		

	}
	else
	{
		TRACE(" O3DMouse:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		

