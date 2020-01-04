// DVM_Edit.cpp : implementation of the CDVM_Del class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "drawview.h"
#include "Def_MoBox.h" 
//////////////////////
#include "DVM_Del.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDVM_Del, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDVM_Del


void CDVM_Del::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	pWnd->GetDelMgr()->SetViewCursor(pView->GetViewNum());
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
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
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

void CDVM_Del::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
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

void CDVM_Del::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
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

void CDVM_Del::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
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
		
void CDVM_Del::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
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
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetDelMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetDelMgr()->GetDLDMouse()->
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
