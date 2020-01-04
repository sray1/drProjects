// SpeLortBar.cpp : implementation of the Floating tool Curve class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "IGenRsrc.h"
#include "BoxWndID.h"
#include "SpeLRsrc.h"	// SpeLort ResourceID

#include "SpeLButt.h"
#include "SpeLbox.h"
#include "SpeLbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSpeLBar,CPaletteBar)

BEGIN_MESSAGE_MAP(CSpeLBar, CPaletteBar)
	//{{AFX_MSG_MAP(CSpeLBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CSpeLBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CSpeLBar construction/destruction
CSpeLBar::CSpeLBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveSpeLObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveSpeLObjectOld 	= m_nActiveSpeLObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CSpeLBar::~CSpeLBar()
{    
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CSpeLBar diagnostics

#ifdef _DEBUG
void CSpeLBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CSpeLBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CSpeLBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_SPECTRALOADBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveSpeLObjectOld = m_nActiveSpeLObject;
		m_nActiveSpeLObject    = Num;
		if(m_nActiveSpeLObject != m_nActiveSpeLObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveSpeLObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveSpeLObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveSpeLObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveSpeLObject);
			GetItemRect(m_nActiveSpeLObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveSpeLObjectOld>=0 )
			{
				m_nCheck[m_nActiveSpeLObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveSpeLObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveSpeLObjectOld,nID,
						m_nCheck[m_nActiveSpeLObjectOld],iImage);
//				InvalidateButton(m_nActiveSpeLObjectOld);
			GetItemRect(m_nActiveSpeLObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CSpeLBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: CurveBar.m_nActiveSpeLObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_SPECTRALOADBOX);
		pTool->GetButtonInfo(m_nActiveSpeLObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CSpeLBox* pElemBox = (CSpeLBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CSpeLBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
