// SupportBar.cpp : implementation of the Floating tool Curve class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "IGenRsrc.h"
#include "BoxWndID.h"
#include "SuppRsrc.h"	// Support ResourceID

#include "SuppButt.h"
#include "Suppbox.h"
#include "Suppbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSuppBar,CPaletteBar)

BEGIN_MESSAGE_MAP(CSuppBar, CPaletteBar)
	//{{AFX_MSG_MAP(CSuppBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CSuppBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CSuppBar construction/destruction
CSuppBar::CSuppBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveSuppObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveSuppObjectOld 	= m_nActiveSuppObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CSuppBar::~CSuppBar()
{    
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CSuppBar diagnostics

#ifdef _DEBUG
void CSuppBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CSuppBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CSuppBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	int Num;
	int iImage;
	UINT nID,nStyle;
	CRect rectButton;
	///////////////////////////////////////////////// 
	if (point.y <= m_cyTopBorder)
	{
		CPaletteBar::OnLButtonDown(nFlags, point);
		return;
	}
	else if((Num = HitTest(point)) >= 0)
	{
	
		SetCapture();
		m_bButtonDown 	 = TRUE;
        ////////////////////////////////////////////
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_SUPPORTBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveSuppObjectOld = m_nActiveSuppObject;
		m_nActiveSuppObject    = Num;
		if(m_nActiveSuppObject != m_nActiveSuppObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveSuppObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveSuppObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveSuppObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveSuppObject);
			GetItemRect(m_nActiveSuppObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveSuppObjectOld>=0 )
			{
				m_nCheck[m_nActiveSuppObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveSuppObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveSuppObjectOld,nID,
						m_nCheck[m_nActiveSuppObjectOld],iImage);
//				InvalidateButton(m_nActiveSuppObjectOld);
			GetItemRect(m_nActiveSuppObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CSuppBar::OnLButtonUp(UINT nFlags, CPoint point)
{ 
	int iImage;
	UINT nID,nStyle;
	/////////////////
	if (m_bButtonDown)
	{
		m_bButtonDown = !m_bButtonDown;
		ReleaseCapture();      
		///////////////////////////////////////////// set for ToolBox 
		//////////////////////////////////////////////////////////////
		// Note: CurveBar.m_nActiveSuppObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_SUPPORTBOX);
		pTool->GetButtonInfo(m_nActiveSuppObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CSuppBox* pElemBox = (CSuppBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CSuppBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
