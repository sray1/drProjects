// CDVM_CreO.cpp : implementation of the CDVM_CreO class         BASE Class
//


#include "stdafx.h"

 
#include "drgrafrm.h"
#include "drawview.h"
#include "Def_MoBox.h" 
//////////////////////
#include "DVM_CreO.h" 

//////////////////////////////////////
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDVM_CreO, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDVM_CreO


void CDVM_CreO::MouseMove(CView* pDrawView, UINT nFlags, CPoint point)
{

	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CDrawView* pView	= (CDrawView*)pDrawView;
	CClientDC	dc(pView);
	pView->OnPrepareDC(&dc);
	//////////////////////////////////////////
	pWnd->GetCreOpMgr()->SetViewCursor(pView->GetViewNum());
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
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
				OnEBoxMouseMove_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
				OnEBoxMouseMove_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
				OnEBoxMouseMove_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
				OnEBoxMouseMove_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
				OnEBoxMouseMove_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxMouseMove_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
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

void CDVM_CreO::LButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
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

void CDVM_CreO::LButtonUp(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxLButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
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

void CDVM_CreO::RButtonDown(CView* pDrawView, UINT nFlags, CPoint point)
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
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonDown_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
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
		
void CDVM_CreO::RButtonUp(CView* pDrawView, UINT nFlags,CPoint point)
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
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_NOD(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case CURVEBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_CUR(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case PATCHBOX:
				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_PAT(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case SOLIDBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_SOL(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case OBJ3DBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_O3D(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;
/*
			case SUPPORTBOX:

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
					OnEBoxRButtonUp_SUP(&dc,pView,pView->GetGenMode(),nFlags,point);
				//////
				break;

			case STATICLOADBOX:	

				pWnd->GetCreOpMgr()->GetSolCreOp()->SetViewNumber(pView->GetViewNum());    // View12 = 1 etc.
				pWnd->GetCreOpMgr()->GetSolCreOp()->
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
