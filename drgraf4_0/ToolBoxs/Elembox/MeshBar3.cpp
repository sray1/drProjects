// Elem.cpp : implementation of the Floating tool Elem class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "EoxWndID.h"
#include "EoxBMPID.h"
#include "EBoxrsrc.h"

#include "MeshBut3.h"
#include "Meshbox3.h"
#include "Meshbar3.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMeshBar3, CPaletteBar)

BEGIN_MESSAGE_MAP(CMeshBar3, CPaletteBar)
	//{{AFX_MSG_MAP(CMeshBar3)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CMeshBar3 construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CMeshBar3 construction/destruction

CMeshBar3::CMeshBar3()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit/move/post) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveNodeObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveNodeObjectOld 	= m_nActiveNodeObject;
	/////////////////////////////////
	m_nButtCount     = EB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CMeshBar3::~CMeshBar3()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CMeshBar3 diagnostics

#ifdef _DEBUG
void CMeshBar3::AssertValid() const
{
	CToolBar::AssertValid();
}

void CMeshBar3::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CMeshBar3::OnLButtonDown(UINT nFlags, CPoint point)
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
			GetDescendantWindow(IDW_MESHBOX3);
		///////////////////////////////////////////////////////// Objects	
		m_nActiveNodeObjectOld = m_nActiveNodeObject;
		m_nActiveNodeObject    = Num;
		if(m_nActiveNodeObject != m_nActiveNodeObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveNodeObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveNodeObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveNodeObject,nID,
					nStyle|TBBS_PRESSED,iImage);
//			InvalidateButton(m_nActiveNodeObject);
			GetItemRect(m_nActiveNodeObject,&rectButton);
			InvalidateRect(&rectButton);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESHEXNG, (WPARAM)nID);
			//////////////////////////////////////////////
			if(m_nActiveNodeObjectOld>=0 )
			{
				m_nCheck[m_nActiveNodeObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveNodeObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveNodeObjectOld,nID,
						m_nCheck[m_nActiveNodeObjectOld],iImage);
//				InvalidateButton(m_nActiveNodeObjectOld);
			GetItemRect(m_nActiveNodeObjectOld,&rectButton);
			InvalidateRect(&rectButton);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CMeshBar3::OnLButtonUp(UINT nFlags, CPoint point)
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
		// Note: HexBar.m_nActiveNodeObject is 
		//					sequencial index starting at 0
		//       ElemBox.m_nActiveElemObject is
		//					CurveID(used in eboxrsrc.h & PaGlobal.h
		/////////////////////////////////////////////////////////////	                     
        //////////////////////////////////////////// get Button ID
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_MESHBOX3);
		pTool->GetButtonInfo(m_nActiveNodeObject,nID,nStyle,iImage);								
		//////////////////////////////////////////// set ID	
		CMeshBox3* pElemBox = (CMeshBox3*) GetParent();
		pElemBox->SetActiveElemObject((int)nID);// 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
	
}

///////////////////////////////// end of module ///////////////////// 

void CMeshBar3::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
