// Elem.cpp : implementation of the Floating tool Elem class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "EBoxrsrc.h"

#include "MeshButt.h"
#include "Meshbox.h"
#include "Meshbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMeshBar, CPaletteBar)

BEGIN_MESSAGE_MAP(CMeshBar, CPaletteBar)
	//{{AFX_MSG_MAP(CMeshBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
// CMeshBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CMeshBar construction/destruction

CMeshBar::CMeshBar()
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

CMeshBar::~CMeshBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CMeshBar diagnostics

#ifdef _DEBUG
void CMeshBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CMeshBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CMeshBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	int Num;
	int iImage;
	UINT nID,nStyle;
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
		CMeshBox* pElemBox = (CMeshBox*) GetParent();
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_MESHBAR);
		////////////////////////////////////////////////////// check if CURVE/PATCH
		nID = pTool->GetItemID(Num);								
		if(nID == IDB_PATCH ||nID == IDB_CURVE)
		{
			m_nActiveTool    = Num;
			return;
		}	
		//////////////////////////////////////// check if Edit/Move/Post
		if((nID == IDB_EDIT || nID == IDB_MOVE || nID == IDB_POST)  )
		{
			/////////////////////////////////////////////////////////////// release edit/move
			if(Num == m_nActiveTool)       // same button over      
			{
				m_bToolHit = FALSE;  		// lift up 
				m_nActiveTool 	 = -1;      // reset
				m_nActiveToolOld = m_nActiveTool;
				m_nCheck[Num]    = 0;
				pTool->GetButtonInfo(Num,nID,nStyle,iImage);								
				pTool->SetButtonInfo(Num,nID,m_nCheck[Num],iImage);    //release button
				
				return;
			}
			else
				m_bToolHit = TRUE; 
			////////////////////////////////////////////////////////////////
			if(m_nActiveElemObject<0) return;	
			////////////////////////////////////////////////////////////////	
			nID = pTool->GetItemID(m_nActiveElemObject);								
//			if(!pElemBox->IsDrawObject(nID)) // Not right kind
//				return;
			m_nActiveToolOld = m_nActiveTool;
			m_nActiveTool    = Num;
			if(m_nActiveTool != m_nActiveToolOld)
			{
										
				m_nCheck[m_nActiveTool] 	= 1;      	//depressed 
				pTool->GetButtonInfo(m_nActiveTool,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveTool,nID,
						nStyle|TBBS_PRESSED,iImage);
				InvalidateButton(m_nActiveTool);
				UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
				//////////////////////////////////////////////
				if(m_nActiveToolOld>=0 )
				{
					m_nCheck[m_nActiveToolOld] 	= 0;   		//uncheck 
					pTool->GetButtonInfo(m_nActiveToolOld,nID,nStyle,iImage);								
					pTool->SetButtonInfo(m_nActiveToolOld,nID,
							m_nCheck[m_nActiveToolOld],iImage);
					InvalidateButton(m_nActiveToolOld);
					UpdateWindow(); // immediate feedback
				}            
			}
		return;		
		}
		///////////////////////////////////////////////////////// other Objects	
		m_nActiveElemObjectOld = m_nActiveElemObject;
		m_nActiveElemObject    = Num;
		if(m_nActiveElemObject != m_nActiveElemObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveElemObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveElemObject,nID,
					nStyle|TBBS_PRESSED,iImage);
			InvalidateButton(m_nActiveElemObject);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
/*
			/////////////////////////////////////////////////////////////////
			// Check if DrawObject is not of kind that can be Moved or Edited
			nID = pTool->GetItemID(m_nActiveDrawObject);								
			if(!pDrawBox->IsDrawObject(nID)) // Not right kind
			{
				int index = pTool->CommandToIndex(IDB_EDIT);    // Get Edit
				pTool->GetButtonInfo(index,nID,nStyle,iImage);	// and							
				pTool->SetButtonInfo(index,nID,0,iImage);       // uncheck
					index = pTool->CommandToIndex(IDB_MOVE);    // Get Move
				pTool->GetButtonInfo(index,nID,nStyle,iImage);	// and							
				pTool->SetButtonInfo(index,nID,0,iImage);       // uncheck
				///////////////////////////////// reset
				m_nActiveTool 		= -1;
				m_nActiveToolOld 	= m_nActiveTool;
			}
*/				
			//////////////////////////////////////////////
			if(m_nActiveElemObjectOld>=0 )
			{
				m_nCheck[m_nActiveElemObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveElemObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveElemObjectOld,nID,
						m_nCheck[m_nActiveElemObjectOld],iImage);
				InvalidateButton(m_nActiveElemObjectOld);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}


void CMeshBar::OnLButtonUp(UINT nFlags, CPoint point)
{ 
	int iImage;
	UINT nID,nStyle;
	/////////////////
	if (m_bButtonDown)
	{
		m_bButtonDown = !m_bButtonDown;
		ReleaseCapture();      
		/////////////////////////////////
		CMeshBox* pElemBox = (CMeshBox*) GetParent();
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_MESHBAR);
		///////////////////////////////////////////// set for ToolBox 
		if(m_nActiveElemObject<0)
		{
			AfxMessageBox("Select an Element");
			return;
		}	
		///////////////////////////////////////////// check if CURVE/PATCH
		if(m_nActiveTool>=0)
		{
			nID = pTool->GetItemID(m_nActiveTool);								
			if(nID == IDB_CURVE || nID == IDB_PATCH)
			{
				pElemBox->SetActiveTool((int)nID);//
				pElemBox->GoRespondtoMouse(); // ask elembox to respond
				m_nActiveTool = -1;   //reset
				return;
			}
		}		
        //////////////////////////////////////////// get Button ID
		pTool->GetButtonInfo(m_nActiveElemObject,nID,nStyle,iImage);								
		//////////////////////////////////////////////////////////////
		// Note: elemBar.m_nActiveElemObject is 
		//					sequencial index starting at 0
		//       elemBox.m_nActiveElemObject is
		//					elementID(used in eboxrsrc.h & elglobal.h
		/////////////////////////////////////////////////////////////	                     
		//////////////////////////////////////////// set ID
		nID = pTool->GetItemID(m_nActiveElemObject);								
		pElemBox->SetActiveElemObject((int)nID);//
		///////////////////////////////////////// 
		if(!m_bToolHit)
			pElemBox->SetActiveTool(-1);//
		else
		{	
			nID = pTool->GetItemID(m_nActiveTool);								
			pElemBox->SetActiveTool((int)nID);//
		}	 
		///////////////////////////////////////////// 
		pElemBox->GoRespondtoMouse();
		/////////////////////////////
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

void CMeshBar::OnDestroy()
{
	CPaletteBar::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
