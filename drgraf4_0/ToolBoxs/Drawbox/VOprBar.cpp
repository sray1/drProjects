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

#include "VOprButt.h"
#include "VOprBox.h"

#include "VOprBar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CVOprBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CVOprBar, CPaletteBar)
	//{{AFX_MSG_MAP(CVOprBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CVOprBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CVOprBar construction/destruction

CVOprBar::CVOprBar()
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

CVOprBar::~CVOprBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CVOprBar diagnostics

#ifdef _DEBUG
void CVOprBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CVOprBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG

void CVOprBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_VOPRBOX);
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


void CVOprBar::OnLButtonUp(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_VOPRBOX);
		pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CVOprBox* pElemBox = (CVOprBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}
///////////////////////////////// end of module ///////////////////// 

void CVOprBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
