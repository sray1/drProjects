// DVM_Genr.cpp : implementation of the CDVM_Genr class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "drawview.h"
#include "Def_MoBox.h" 
//////////////////////
#include "DVM_Genr.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDVM_Genr, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDVM_Genr

int CDVM_Genr::ResetDlg_NOD(UINT uVuNum)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->SetActiveViewNumber(uVuNum);
/*
	//////////////////////////////////////////
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	/////////////////////
	if(uVuNum == VIEWISO)
		return -1;
*/
	////////////////////////////////////////////////
	if((pWnd->GetMouseMgr()->GetDLDMouse()->GetNodInDlg()->GetSafeHwnd()) != 0) //Open 
	{
/*
		if(uVuNum == VIEWISO)
		{
			pWnd->OnModeOutput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetNodInDlg()->ShowWindow(FALSE); //Shut
			return -1;
		}
		else
		{
*/
			pWnd->OnModeInput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetNodInDlg()->ShowWindow(TRUE); //Open                                                                                
			pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_NodDlg();
			//////////////////////////////////////////
			pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(uVuNum);    // View12 = 1 etc.
			if((pWnd->GetMouseMgr()->GetDLDMouse()->GetNodInDlg()->GetSafeHwnd()) != 0) //Open                                                                                
				pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_NodDlg();
			/////////////////////////////////////////
			return 0;
/*
		}
*/
	}
	return 0;
}

int CDVM_Genr::ResetDlg_CUR(UINT uVuNum)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->SetActiveViewNumber(uVuNum);
	//////////////////////////////////////////
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	/////////////////////
	if(uVuNum == VIEWISO)
		return -1;
	////////////////////////////////////////////////
	switch(pWnd->GetCurrentIGenID())
	{
		case C_CIRCLE:
		//////////////////
			if((pWnd->GetMouseMgr()->GetDLDMouse()->GetCrcInDlg()->GetSafeHwnd()) != 0) //Open 
			{
				if(uVuNum == VIEWISO)
				{
					pWnd->OnModeOutput(); 
					pWnd->GetMouseMgr()->GetDLDMouse()->GetCrcInDlg()->ShowWindow(FALSE); //Shut
					return -1;
				}
				else
				{
					pWnd->OnModeInput(); 
					pWnd->GetMouseMgr()->GetDLDMouse()->GetCrcInDlg()->ShowWindow(TRUE); //Open                                                                                
					pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_CurDlg();
					//////////////////////////////////////////
					pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(uVuNum);    // View12 = 1 etc.
					if((pWnd->GetMouseMgr()->GetDLDMouse()->GetCrcInDlg()->GetSafeHwnd()) != 0) //Open                                                                                
						pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_CurDlg();
					/////////////////////////////////////////
					return 0;
				}
			}
			return 0;
		//////////////////
		case C_LINEAR:
		case C_QUADRATIC:
		case C_CUBIC:
		case C_PARABOLA:
		case C_BEZIER:
		case C_BSPLINE:
		case C_NURB:
		//////////////////
			if((pWnd->GetMouseMgr()->GetDLDMouse()->GetLQCInDlg()->GetSafeHwnd()) != 0) //Open 
			{
				if(uVuNum == VIEWISO)
				{
					pWnd->OnModeOutput(); 
					pWnd->GetMouseMgr()->GetDLDMouse()->GetLQCInDlg()->ShowWindow(FALSE); //Shut
					return -1;
				}
				else
				{
					pWnd->OnModeInput(); 
					pWnd->GetMouseMgr()->GetDLDMouse()->GetLQCInDlg()->ShowWindow(TRUE); //Open                                                                                
					pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_CurDlg();
					//////////////////////////////////////////
					pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(uVuNum);    // View12 = 1 etc.
					if((pWnd->GetMouseMgr()->GetDLDMouse()->GetLQCInDlg()->GetSafeHwnd()) != 0) //Open                                                                                
						pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_CurDlg();
					/////////////////////////////////////////
					return 0;
				}
			}
			return 0;
		//////////////////
		default:
			return -1;
	}
	return 0;
}

int CDVM_Genr::ResetDlg_PAT(UINT uVuNum)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->SetActiveViewNumber(uVuNum);
	//////////////////////////////////////////
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	/////////////////////
	if(uVuNum == VIEWISO)
		return -1;
	////////////////////////////////////////////////
	if((pWnd->GetMouseMgr()->GetDLDMouse()->GetPatSheet()->GetSafeHwnd()) != 0) //Open 
	{
		if(uVuNum == VIEWISO)
		{
			pWnd->OnModeOutput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetPatSheet()->ShowWindow(FALSE); //Shut
			return -1;
		}
		else
		{
			pWnd->OnModeInput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetPatSheet()->ShowWindow(TRUE); //Open                                                                                
			pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_PatDlg();
			//////////////////////////////////////////
			pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(uVuNum);    // View12 = 1 etc.
			if((pWnd->GetMouseMgr()->GetDLDMouse()->GetPatSheet()->GetSafeHwnd()) != 0) //Open                                                                                
				pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_PatDlg();
			/////////////////////////////////////////
			return 0;
		}
	}
	return 0;
}

int CDVM_Genr::ResetDlg_SOL(UINT uVuNum)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	pWnd->SetActiveViewNumber(uVuNum);
	//////////////////////////////////////////
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	/////////////////////
	if(uVuNum == VIEWISO)
		return -1;
	////////////////////////////////////////////////
	if((pWnd->GetMouseMgr()->GetDLDMouse()->GetSolSheet()->GetSafeHwnd()) != 0) //Open 
	{
		if(uVuNum == VIEWISO)
		{
			pWnd->OnModeOutput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetSolSheet()->ShowWindow(FALSE); //Shut
			return -1;
		}
		else
		{
			pWnd->OnModeInput(); 
			pWnd->GetMouseMgr()->GetDLDMouse()->GetSolSheet()->ShowWindow(TRUE); //Open                                                                                
			pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_SolDlg();
			//////////////////////////////////////////
			pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(uVuNum);    // View12 = 1 etc.
			if((pWnd->GetMouseMgr()->GetDLDMouse()->GetSolSheet()->GetSafeHwnd()) != 0) //Open                                                                                
				pWnd->GetMouseMgr()->GetDLDMouse()->ResetVuBasedVars_SolDlg();
			/////////////////////////////////////////
			return 0;
		}
	}
	return 0;
}

void CDVM_Genr::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	UINT uVuNum = pView->GetViewNum(); 
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	////////////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////
		if(uVuNum == VIEWISO)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				//***************************************************************
//				if(ResetDlg_NOD(pView->GetViewNum())<0)	// ISOVIEW
//					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				//***************************************************************
//				if(ResetDlg_CUR(pView->GetViewNum())<0)	// ISOVIEW
//					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				//***************************************************************
//				if(ResetDlg_PAT(pView->GetViewNum())<0)	// ISOVIEW
//					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:
				//***************************************************************
//				if(ResetDlg_SOL(pView->GetViewNum())<0)	// ISOVIEW
//					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
				OnEBoxMouseMove_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;


			case MESHBOX0:	
			case MESHBOX1:	
			case MESHBOX2:	
			case MESHBOX3:	
			case DYNAMICLOADBOX:
			default:
				break;
		}
	}	    
	else 
	if(pWnd->IsDrawBoxActive())
	{
		pWnd->GetMouseMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouseMgr()->GetDBMouse()->
			OnDBoxMouseMove(&dc,pView,nFlags,point);
	}	
	///////////////////////////////////////////////////// Update StatusBar
	pWnd->GetSBarBot()->UpdateStatusBar(&dc);
	pWnd->GetSBarTop()->UpdateStatusBar(&dc);
	///////////////////////////////	
			
}

void CDVM_Genr::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	UINT uVuNum = pView->GetViewNum(); 
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////
		if(uVuNum == VIEWISO)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				//***************************************************************
				if(ResetDlg_NOD(uVuNum)<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				//***************************************************************
				if(ResetDlg_CUR(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				//***************************************************************
				if(ResetDlg_PAT(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:
				//***************************************************************
				if(ResetDlg_SOL(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;


			case MESHBOX0:	
			case MESHBOX1:	
			case MESHBOX2:	
			case MESHBOX3:	
			case DYNAMICLOADBOX:
			default:
				break;
		}
	}	    
	else
	if(pWnd->IsDrawBoxActive())
	{
		pWnd->GetMouseMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouseMgr()->GetDBMouse()->
			OnDBoxLButtonDown(&dc,pView,nFlags,point);
	}	

}

void CDVM_Genr::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	UINT uVuNum = pView->GetViewNum(); 
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////
		if(uVuNum == VIEWISO)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				//***************************************************************
				if(ResetDlg_NOD(uVuNum)<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				//***************************************************************
				if(ResetDlg_CUR(uVuNum)<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				//***************************************************************
				if(ResetDlg_PAT(uVuNum)<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:
				//***************************************************************
				if(ResetDlg_SOL(uVuNum)<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;


			case MESHBOX0:	
			case MESHBOX1:	
			case MESHBOX2:	
			case MESHBOX3:	
			case DYNAMICLOADBOX:
			default:
				break;
		}
	}	    
	else
	if(pWnd->IsDrawBoxActive())
	{
		pWnd->GetMouseMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouseMgr()->GetDBMouse()->
			OnDBoxLButtonUp(&dc,pView,nFlags,point);
	}	
		
}

void CDVM_Genr::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{ 
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	UINT uVuNum = pView->GetViewNum(); 
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////
		if(uVuNum == VIEWISO)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				//***************************************************************
				if(ResetDlg_NOD(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				//***************************************************************
				if(ResetDlg_CUR(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				//***************************************************************
				if(ResetDlg_PAT(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:
				//***************************************************************
				if(ResetDlg_SOL(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;



			case MESHBOX0:	
			case MESHBOX1:	
			case MESHBOX2:	
			case MESHBOX3:	
			case DYNAMICLOADBOX:
			default:
				break;
		}
	}	    
	else
	if(pWnd->IsDrawBoxActive())
	{
		pWnd->GetMouseMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouseMgr()->GetDBMouse()->
			OnDBoxRButtonDown(&dc,pView,nFlags,point);
	}	

}
		
void CDVM_Genr::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	UINT uVuNum = pView->GetViewNum(); 
	pWnd->GetMouseMgr()->SetViewCursor(uVuNum);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////
		if(uVuNum == VIEWISO)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				//***************************************************************
				if(ResetDlg_NOD(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				//***************************************************************
				if(ResetDlg_CUR(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				//***************************************************************
				if(ResetDlg_PAT(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:
				//***************************************************************
				if(ResetDlg_SOL(pView->GetViewNum())<0)	// ISOVIEW
					return;
				//***************************************************************
				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouseMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouseMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;



			case MESHBOX0:	
			case MESHBOX1:	
			case MESHBOX2:	
			case MESHBOX3:	
			case DYNAMICLOADBOX:
			default:
				break;
		}
	}	    
	else
	if(pWnd->IsDrawBoxActive())
	{
		pWnd->GetMouseMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouseMgr()->GetDBMouse()->
			OnDBoxRButtonUp(&dc,pView,nFlags,point);
	}	

}
//////////////////////////////////////////// end of module //////////////////
