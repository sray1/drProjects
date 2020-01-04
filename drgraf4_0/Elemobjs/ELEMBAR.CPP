// Element.cpp : implementation of the Floating tool Element class
//

#include "drgraf.h" 
#include "drgradoc.h"
#include "drgrafrm.h"
#include "grafobj.h"
 
#include "elglobal.h"
#include "elembar.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

BEGIN_MESSAGE_MAP(CElementBar, CPaletteBar)
	//{{AFX_MSG_MAP(CElementBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//////////////////////
#define	CYCAPTION	9
/////////////////////////////////////////////////////////////////////////////
// CElementBar construction/destruction

CElementBar::CElementBar()
{                          
	for (int i=0;i<MAX_ELEMENT_BUTTON;i++)
		m_bSubBar[i]     = TRUE;  
	m_bButtonDown = FALSE;
	m_nActiveElement = 0;
	     	
}

CElementBar::~CElementBar()
{
}

BOOL CElementBar::SetButtons(const UINT FAR* lpIDArray,
	int nIDCount, UINT nColumns,BOOL bCaption)
{
		m_sizeButton.cx  = EL_BNSIZE_CX;
		m_sizeButton.cy  = EL_BNSIZE_CY; 
		
        CSize sizeImage;
		sizeImage.cx   	 = EL_IMAGE_CX;
		sizeImage.cy   	 = EL_IMAGE_CY;
		
		m_cyCaption   	 = CYCAPTION;
		m_cyTopBorder    = CYCAPTION + 2;
		m_cxLeftBorder   = 0;
		m_cxRightBorder  = 0;
		m_cyBottomBorder = 0;  
		
	if(!bCaption)
	{ 
		m_cyCaption   	 = 0;
		m_cyTopBorder    = 0;
	}		
	///////////////////////////////////////////
	CToolBar::SetSizes(m_sizeButton,sizeImage);
	/////////////////////////////////////////// 
	m_nColumns = nColumns;
	RecalcLayout(nIDCount);
	return CToolBar::SetButtons(lpIDArray, nIDCount);
}
	
BOOL CElementBar::Create(CWnd* pOwnerWnd, int x, int y)
{
	ASSERT(pOwnerWnd != NULL);
	m_pOwnerWnd = pOwnerWnd;

	return CreateEx(0, "AfxControlBar", NULL, WS_POPUP,     // POPUP
		x, y, 0, 0, pOwnerWnd->GetSafeHwnd(), NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CElementBar diagnostics

#ifdef _DEBUG
void CElementBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CElementBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CElementBar message handlers

void CElementBar::OnLButtonDown(UINT nFlags, CPoint point)
{  
     
	int Num;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(theApp.m_pDoc ); 
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr(); 
	CBooleans* pBool		= pDoc->GetBooleans(); 
	CElemObject* pEBoxMgr 	= pObjectMgr->GetEBoxMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	CDrGrafFrame* pWnd 		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd );
	////////////////////////////////////////////////////////////////////
	if (point.y <= m_cyTopBorder)
	{
		m_bTrackMove = TRUE;
		m_ptMouse = point;
		SetCapture();
		ClientToScreen(&point);
		InvertTracker(point);
		m_ptLast = point;
	}
	else if((Num = HitTest(point) )>=0)
	{
		m_bButtonDown 	 = !m_bButtonDown;
		SetCapture(); 
		pDBoxMgr->SetDrawBoxStatus(FALSE);
		pEBoxMgr->SetElementBoxStatus(TRUE);
//		CDrGrafFrame* pWnd= (CDrGrafFrame*)GetWindow(GW_OWNER);
		///////////////////////////////////////////////////////
		int nElemNum = Num + 1   ; // Num starts at 0
		///////////////////////////////////////////////
		pObjectMgr->SetActiveObjectType(nElemNum);             // Set ObjectType 
		///////////////////////////////////////////////
		switch(nElemNum)
		{
			case  NODE : 		// NODE Library
//				SwitchButton(0);
				pObjectMgr->SetActiveObjectType(NODE);
				pEBoxMgr->SetElementType(NODE);
				break;
				
			case  PIPE : 		// PIPE Library
//				SwitchButton(1);
				pObjectMgr->SetActiveObjectType(PIPE);
				pEBoxMgr->SetElementType(PIPE);
				break;
				
			case  ELBOW : 		// ELBOW Library
				pObjectMgr->SetActiveObjectType(ELBOW);
				pEBoxMgr->SetElementType(ELBOW);
				break;
				
			case  BEAM : 		// BEAM Library
				pObjectMgr->SetActiveObjectType(BEAM);
				pEBoxMgr->SetElementType(BEAM);
				break;  
				
			case  SUPPORT : 		// SUPPORT Library
				pObjectMgr->SetActiveObjectType(SUPPORT);
				pEBoxMgr->SetElementType(SUPPORT);
			    ////////////////////////////////////////////////////////////////
				if (m_bSubBar[Num])
					pWnd->SendMessage(ELM_SUPPORT,(UINT)Num,1L); // 1=SHOW
				else
					pWnd->SendMessage(ELM_SUPPORT,(UINT)Num,0L); // 0=HIDE
				m_bSubBar[Num] = !m_bSubBar[Num];            // Toggle ViewState
				break;
				
			case  TRUSS : 		// TRUSS Library
				pObjectMgr->SetActiveObjectType(TRUSS);
				pEBoxMgr->SetElementType(TRUSS);
				break; 
				
			case  PLANE : 		// PLANE Library
				pObjectMgr->SetActiveObjectType(PLANE);
				pEBoxMgr->SetElementType(PLANE);
				break; 
				
			case  PLATE : 		// PLATE Library
				pObjectMgr->SetActiveObjectType(PLATE);
				pEBoxMgr->SetElementType(PLATE);
				break;  
				
			case  SHELL : 		// SHELL Library
				pObjectMgr->SetActiveObjectType(SHELL);
				pEBoxMgr->SetElementType(SHELL);
				break;
			
			default:
				break;					
     	}
	}	
	else
		CToolBar::OnLButtonDown(nFlags, point);
}
	
void CElementBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc );  
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd );
	/////////////////////////////////////////////////////////
	if (m_bTrackMove)
	{
		m_bTrackMove=FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
		ShowWindow(SW_SHOW);
		//////////////////////////////////////// set new location of Element Rect
											//// Needed for Support Bar Location  
		RECT Rect;
		GetWindowRect(&Rect);									
		pWnd->SetElementLeft((UINT)(Rect.left));
		pWnd->SetElementTop ((UINT)(Rect.top));
		////////////////////////////////////
	}
	/////////////////
	else if (m_bButtonDown)
	{
		m_bButtonDown = !m_bButtonDown;                      
		ReleaseCapture();

		CString StatusString;
		int Num = HitTest(point);
		int nElemNum = Num + 1;	    
//		CDrGrafFrame* pWnd= (CDrGrafFrame*)GetWindow(GW_OWNER);
		switch(nElemNum)
		{
			case  NODE : 		// NODE Library
			case  PIPE : 		// PIPE Library
			case  ELBOW: 		// ELBOW Library
			case  BEAM : 		// BEAM Library
			case  SUPPORT: 		// SUPPORT Library
			case  TRUSS : 		// TRUSS Library
			case  PLANE : 		// PLANE Library
			case  PLATE : 		// PLATE Library
			case  SHELL : 		// SHELL Library

				break;
			
			default:
				break;					
     	}
	}
	else
		CToolBar::OnLButtonUp(nFlags, point);
}

void CElementBar::SwitchButton(UINT nButton)
{

	if(m_nActiveElement == nButton)
		return;
	/////////////////////////
	switch(m_nActiveElement)
	{
		case 0:
			_SetButtonStyle(0,TBBS_DISABLED);
			InvalidateButton(0);
			UpdateWindow();
			break;
		case 1:   
			AfxMessageBox("switchButton:case 1");
			_SetButtonStyle(0,TBBS_DISABLED);
			InvalidateButton(0);
			UpdateWindow(); 
			break;
		default:
			break;
	}			             
	////////////////
	switch(nButton)
	{
		case 0:
			_SetButtonStyle(0,TBBS_BUTTON);
			InvalidateButton(0);
			UpdateWindow();
			break;
		case 1:   
			AfxMessageBox("switchButton:case 1");
			_SetButtonStyle(0,TBBS_BUTTON);
			InvalidateButton(0);
			UpdateWindow(); 
			break;
		default:
			break;
	}			    
	///////////////////////////
	m_nActiveElement = nButton;
}

void CElementBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bTrackMove)
	{
		ClientToScreen(&point);
		InvertTracker(m_ptLast);
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else
		CToolBar::OnMouseMove(nFlags, point);
	// TODO: Add your message handler code here and/or call default
	
}
/*
void CElementBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
}
*/