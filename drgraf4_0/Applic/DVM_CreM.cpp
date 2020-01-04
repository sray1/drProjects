// CDVM_CreM.cpp : implementation of the CDVM_CreM class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "drawview.h"
#include "Def_MoBox.h" 
//////////////////////
#include "DVM_CreM.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDVM_CreM, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDVM_CreM


void CDVM_CreM::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	pWnd->GetCreOMMgr()->SetViewCursor(pView->GetViewNum());
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
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//				OnEBoxMouseMove_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
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

void CDVM_CreM::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxLButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
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

void CDVM_CreM::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxLButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
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

void CDVM_CreM::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxRButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
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
		
void CDVM_CreM::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
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
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
//				pWnd->GetCreOMMgr()->GetSolCreOp()->
//					OnEBoxRButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOMMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOMMgr()->GetSolCreOp()->
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
