// CNtLBar.cpp : implementation of the Floating tool Elem class
//
#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"

#include "IGenButt.h"
#include "IGenBox.h"
#include "MGenBox.h"

#include "IGenBar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CIGenBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CIGenBar, CPaletteBar)
	//{{AFX_MSG_MAP(CIGenBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CIGenBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CIGenBar construction/destruction

CIGenBar::CIGenBar()
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

CIGenBar::~CIGenBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CIGenBar diagnostics

#ifdef _DEBUG
void CIGenBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CIGenBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CIGenBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL m_bMeshMode	= pWnd->IsMeshMode();
	CToolBar* pTool;
	/////////////////////////////////////////////////////
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
		if(m_bMeshMode)
			pTool = (CToolBar*)GetParent()->GetDescendantWindow(IDW_MGENBOX);
		else
			pTool = (CToolBar*)GetParent()->GetDescendantWindow(IDW_IGENBOX);
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


void CIGenBar::OnLButtonUp(UINT nFlags, CPoint point)
{ 
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL m_bMeshMode	= pWnd->IsMeshMode();
	CToolBar* pTool;
	/////////////////////////////////////////////////////
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
		if(m_bMeshMode)
			pTool = (CToolBar*)GetParent()->GetDescendantWindow(IDW_MGENBOX);
		else
			pTool = (CToolBar*)GetParent()->GetDescendantWindow(IDW_IGENBOX);
		pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		if(m_bMeshMode)
		{
			((CMGenBox*) GetParent())->SetActiveElemObject((int)nID);// 
			((CMGenBox*) GetParent())->GoRespondtoMouse();
		}
		else
		{
			((CIGenBox*) GetParent())->SetActiveElemObject((int)nID);// 
			((CIGenBox*) GetParent())->GoRespondtoMouse();
		}
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}
///////////////////////////////// end of module ///////////////////// 

void CIGenBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
