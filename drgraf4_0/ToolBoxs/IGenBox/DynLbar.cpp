// DynLortBar.cpp : implementation of the Floating tool Curve class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
//#include "globals.h"
//#include "toolbar.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "IGenRsrc.h"
#include "BoxWndID.h"
#include "DynLRsrc.h"	// DynLort ResourceID

#include "DynLButt.h"
#include "DynLbox.h"
#include "DynLbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDynLBar,CPaletteBar)

BEGIN_MESSAGE_MAP(CDynLBar, CPaletteBar)
	//{{AFX_MSG_MAP(CDynLBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CDynLBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CDynLBar construction/destruction
CDynLBar::CDynLBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveDynLObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveDynLObjectOld 	= m_nActiveDynLObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CDynLBar::~CDynLBar()
{    
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CDynLBar diagnostics

#ifdef _DEBUG
void CDynLBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CDynLBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CDynLBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_DYNAMICLOADBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveDynLObjectOld = m_nActiveDynLObject;
		m_nActiveDynLObject    = Num;
		if(m_nActiveDynLObject != m_nActiveDynLObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveDynLObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveDynLObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveDynLObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveDynLObject);
			GetItemRect(m_nActiveDynLObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveDynLObjectOld>=0 )
			{
				m_nCheck[m_nActiveDynLObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveDynLObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveDynLObjectOld,nID,
						m_nCheck[m_nActiveDynLObjectOld],iImage);
//				InvalidateButton(m_nActiveDynLObjectOld);
			GetItemRect(m_nActiveDynLObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CDynLBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: CurveBar.m_nActiveDynLObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_DYNAMICLOADBOX);
		pTool->GetButtonInfo(m_nActiveDynLObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CDynLBox* pElemBox = (CDynLBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CDynLBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
