// CNtLBar.cpp : implementation of the Floating tool Elem class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"

#include "MainButt.h"
#include "MainBox.h"

#include "MainBar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMainBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CMainBar, CPaletteBar)
	//{{AFX_MSG_MAP(CMainBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CMainBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CMainBar construction/destruction

CMainBar::CMainBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveElemObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveElemObjectOld 	= m_nActiveElemObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CMainBar::~CMainBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CMainBar diagnostics

#ifdef _DEBUG
void CMainBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CMainBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG

void CMainBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_MAINBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveElemObjectOld = m_nActiveElemObject;
		m_nActiveElemObject    = Num;
		if(m_nActiveElemObject != m_nActiveElemObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveElemObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveElemObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveElemObject);
			GetItemRect(m_nActiveElemObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveElemObjectOld>=0 )
			{
				m_nCheck[m_nActiveElemObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveElemObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveElemObjectOld,nID,
						m_nCheck[m_nActiveElemObjectOld],iImage);
//				InvalidateButton(m_nActiveElemObjectOld);
			GetItemRect(m_nActiveElemObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CMainBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: CurveBar.m_nActiveElemObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_MAINBOX);
		pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CMainBox* pElemBox = (CMainBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}
///////////////////////////////// end of module ///////////////////// 

void CMainBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
