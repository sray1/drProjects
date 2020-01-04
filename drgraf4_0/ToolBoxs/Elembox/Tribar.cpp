// TriBar.cpp : implementation of the Floating tool Trita class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "EoxWndID.h"
#include "EoxBMPID.h"
#include "EBoxrsrc.h"

#include "TriButt.h"
#include "Tribox.h"
#include "Tribar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CTriBar,CPaletteBar)

BEGIN_MESSAGE_MAP(CTriBar, CPaletteBar)
	//{{AFX_MSG_MAP(CTriBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CTriBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CTriBar construction/destruction
CTriBar::CTriBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveCurveObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveCurveObjectOld 	= m_nActiveCurveObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CTriBar::~CTriBar()
{    
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CTriBar diagnostics

#ifdef _DEBUG
void CTriBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CTriBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CTriBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_TRIBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveCurveObjectOld = m_nActiveCurveObject;
		m_nActiveCurveObject    = Num;
		if(m_nActiveCurveObject != m_nActiveCurveObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveCurveObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveCurveObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveCurveObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveCurveObject);
			GetItemRect(m_nActiveCurveObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveCurveObjectOld>=0 )
			{
				m_nCheck[m_nActiveCurveObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveCurveObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveCurveObjectOld,nID,
						m_nCheck[m_nActiveCurveObjectOld],iImage);
//				InvalidateButton(m_nActiveCurveObjectOld);
			GetItemRect(m_nActiveCurveObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CTriBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: TriBar.m_nActiveCurveObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_TRIBOX);
		pTool->GetButtonInfo(m_nActiveCurveObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CTriBox* pElemBox = (CTriBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CTriBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}