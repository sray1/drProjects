// DVM_Genr.cpp : implementation of the CXVM_Genr class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "AxDrawVu.h"
#include "Def_MoBox.h" 
//////////////////////
#include "XVM_Genr.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXVM_Genr


void CXVM_Genr::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{
	return;
	///////
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CAxDrawVu* pView	= (CAxDrawVu*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	pWnd->GetMouAXMgr()->SetViewCursor(pView->GetViewNum());
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
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
				OnEBoxMouseMove_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
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
		pWnd->GetMouAXMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouAXMgr()->GetDBMouse()->
			OnDBoxMouseMove(&dc,pView,nFlags,point);
	}	
	///////////////////////////////////////////////////// Update StatusBar
	pWnd->GetSBarBot()->UpdateStatusBar(&dc);
	pWnd->GetSBarTop()->UpdateStatusBar(&dc);
	///////////////////////////////	
*/			
}

void CXVM_Genr::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CAxDrawVu* pView	= (CAxDrawVu*)pDrawView;
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
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
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
		pWnd->GetMouAXMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouAXMgr()->GetDBMouse()->
			OnDBoxLButtonDown(&dc,pView,nFlags,point);
	}	
*/
}

void CXVM_Genr::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CAxDrawVu* pView	= (CAxDrawVu*)pDrawView;
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
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
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
		pWnd->GetMouAXMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouAXMgr()->GetDBMouse()->
			OnDBoxLButtonUp(&dc,pView,nFlags,point);
	}	
*/		
}

void CXVM_Genr::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CAxDrawVu* pView	= (CAxDrawVu*)pDrawView;
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
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
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
		pWnd->GetMouAXMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouAXMgr()->GetDBMouse()->
			OnDBoxRButtonDown(&dc,pView,nFlags,point);
	}	
*/
}
		
void CXVM_Genr::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
{
/*
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CAxDrawVu* pView	= (CAxDrawVu*)pDrawView;
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
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SUPPORTBOX:

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetMouAXMgr()->GetDLDMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetMouAXMgr()->GetDLDMouse()->
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
		pWnd->GetMouAXMgr()->GetDBMouse()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
		pWnd->GetMouAXMgr()->GetDBMouse()->
			OnDBoxRButtonUp(&dc,pView,nFlags,point);
	}	
*/
}
//////////////////////////////////////////// end of module //////////////////
