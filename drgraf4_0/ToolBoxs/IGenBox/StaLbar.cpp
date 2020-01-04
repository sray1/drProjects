// StaticLoadBar.cpp : implementation of the Floating tool Curve class
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
#include "StaLRsrc.h"	// StaticLoad ResourceIDs

#include "StaLButt.h"
#include "StaLbox.h"
#include "StaLbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CStaLBar,CPaletteBar)

BEGIN_MESSAGE_MAP(CStaLBar, CPaletteBar)
	//{{AFX_MSG_MAP(CStaLBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CStaLBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CStaLBar construction/destruction
CStaLBar::CStaLBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveStaLObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveStaLObjectOld 	= m_nActiveStaLObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CStaLBar::~CStaLBar()
{    
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CStaLBar diagnostics

#ifdef _DEBUG
void CStaLBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CStaLBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CStaLBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_STATICLOADBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveStaLObjectOld = m_nActiveStaLObject;
		m_nActiveStaLObject    = Num;
		if(m_nActiveStaLObject != m_nActiveStaLObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveStaLObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveStaLObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveStaLObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveStaLObject);
			GetItemRect(m_nActiveStaLObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveStaLObjectOld>=0 )
			{
				m_nCheck[m_nActiveStaLObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveStaLObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveStaLObjectOld,nID,
						m_nCheck[m_nActiveStaLObjectOld],iImage);
//				InvalidateButton(m_nActiveStaLObjectOld);
			GetItemRect(m_nActiveStaLObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CStaLBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: CurveBar.m_nActiveStaLObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_STATICLOADBOX);
		pTool->GetButtonInfo(m_nActiveStaLObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CStaLBox* pElemBox = (CStaLBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CStaLBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
