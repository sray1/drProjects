// Patch.cpp : implementation of the Floating tool Patch class
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

#include "PBoxButt.h"
#include "PatchBox.h"
#include "PatchBar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CPatchBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CPatchBar, CPaletteBar)
	//{{AFX_MSG_MAP(CPatchBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CPatchBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CPatchBar construction/destruction

CPatchBar::CPatchBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActivePatchObject		= -1;    // -1 = None Selected(other objects) 
	m_nActivePatchObjectOld 	= m_nActivePatchObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CPatchBar::~CPatchBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CPatchBar diagnostics

#ifdef _DEBUG
void CPatchBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CPatchBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CPatchBar::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_PATCHBOX);
		///////////////////////////////////////////////////////// Objects	
		m_nActivePatchObjectOld = m_nActivePatchObject;
		m_nActivePatchObject    = Num;
		if(m_nActivePatchObject != m_nActivePatchObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActivePatchObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActivePatchObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActivePatchObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActivePatchObject);
			GetItemRect(m_nActivePatchObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActivePatchObjectOld>=0 )
			{
				m_nCheck[m_nActivePatchObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActivePatchObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActivePatchObjectOld,nID,
						m_nCheck[m_nActivePatchObjectOld],iImage);
//				InvalidateButton(m_nActivePatchObjectOld);
				GetItemRect(m_nActivePatchObjectOld,&rectButton);
				InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CPatchBar::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: PatchBar.m_nActivePatchObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					PatchID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_PATCHBOX);
		pTool->GetButtonInfo(m_nActivePatchObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CPatchBox* pElemBox = (CPatchBox*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CPatchBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
