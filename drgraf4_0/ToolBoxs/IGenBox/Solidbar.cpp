// Solid.cpp : implementation of the Floating tool Solid class
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

#include "SBoxButt.h"
#include "SolidBox.h"
#include "SolidBar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSolidBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CSolidBar, CPaletteBar)
	//{{AFX_MSG_MAP(CSolidBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CSolidBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CSolidBar construction/destruction

CSolidBar::CSolidBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveSolidObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveSolidObjectOld 	= m_nActiveSolidObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CSolidBar::~CSolidBar()
{
}

void CSolidBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
/////////////////////////////////////////////////////////////////////////////
// CSolidBar diagnostics

#ifdef _DEBUG
void CSolidBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CSolidBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CSolidBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_SOLIDBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveSolidObjectOld = m_nActiveSolidObject;
		m_nActiveSolidObject    = Num;
		if(m_nActiveSolidObject != m_nActiveSolidObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveSolidObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveSolidObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveSolidObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveSolidObject);
			GetItemRect(m_nActiveSolidObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveSolidObjectOld>=0 )
			{
				m_nCheck[m_nActiveSolidObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveSolidObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveSolidObjectOld,nID,
						m_nCheck[m_nActiveSolidObjectOld],iImage);
//				InvalidateButton(m_nActiveSolidObjectOld);
			GetItemRect(m_nActiveSolidObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CSolidBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: SolidBar.m_nActiveSolidObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					SolidID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_SOLIDBOX);
		pTool->GetButtonInfo(m_nActiveSolidObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CSolidBox* pElemBox = (CSolidBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 
