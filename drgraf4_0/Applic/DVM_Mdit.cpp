// DVM_Edit.cpp : implementation of the CDVM_Mdit class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "drawview.h"
#include "Def_MoBox.h" 
//////////////////////
#include "DVM_Mdit.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDVM_Mdit, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDVM_Mdit


void CDVM_Mdit::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	pWnd->GetMditMgr()->SetViewCursor(pView->GetViewNum());
	////////////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		//////////////////////////////////////////////
		if(pWnd->GetOpMode() == OP_OUTPUT)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
 
			case CURVEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
*/

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

void CDVM_Mdit::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	BOOL bActive = pWnd->IsIGenBoxActive();
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////////
		if(pWnd->GetOpMode() == OP_OUTPUT)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
*/

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

void CDVM_Mdit::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////////
		if(pWnd->GetOpMode() == OP_OUTPUT)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
*/

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

void CDVM_Mdit::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{ 
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////////
		if(pWnd->GetOpMode() == OP_OUTPUT)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
*/


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
		
void CDVM_Mdit::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	if(pWnd->IsIGenBoxActive())
	{
		/////////////////////////
		if(pWnd->GetOpMode() == OP_OUTPUT)
			return;
		/////////////////////////
		switch(pWnd->GetMouseBoxType())
		{
			case ELEMDIMBOX:
			case NODEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMditMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMditMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SLD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
*/


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
