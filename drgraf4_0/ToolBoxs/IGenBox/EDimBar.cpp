// Oper.cpp : implementation of the Floating tool Oper class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"

#include "EDimButt.h"
#include "EDimbox.h"
#include "EDimbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CEDimBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CEDimBar, CPaletteBar)
	//{{AFX_MSG_MAP(CEDimBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CEDimBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CEDimBar construction/destruction

CEDimBar::CEDimBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveOperObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveOperObjectOld 	= m_nActiveOperObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CEDimBar::~CEDimBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CEDimBar diagnostics

#ifdef _DEBUG
void CEDimBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CEDimBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CEDimBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_ELEMDIMBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveOperObjectOld = m_nActiveOperObject;
		m_nActiveOperObject    = Num;
		if(m_nActiveOperObject != m_nActiveOperObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveOperObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveOperObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveOperObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveOperObject);
			GetItemRect(m_nActiveOperObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveOperObjectOld>=0 )
			{
				m_nCheck[m_nActiveOperObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveOperObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveOperObjectOld,nID,
						m_nCheck[m_nActiveOperObjectOld],iImage);
//				InvalidateButton(m_nActiveOperObjectOld);
				GetItemRect(m_nActiveOperObjectOld,&rectButton);
				InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CEDimBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: OperBar.m_nActiveOperObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					OperID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_ELEMDIMBOX);
		pTool->GetButtonInfo(m_nActiveOperObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CEDimBox* pElemBox = (CEDimBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CEDimBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
