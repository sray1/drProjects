// Draw.cpp : implementation of the Floating tool Draw class
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "afxext.h"      // for TBBS_PRESSED

#include "DBoxrsrc.h"

#include "DBoxButt.h"
#include "drawbox.h"
#include "drawbar.h"	

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDrawBar

BEGIN_MESSAGE_MAP(CDrawBar, CPaletteBar)
	//{{AFX_MSG_MAP(CDrawBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNCREATE(CDrawBar, CPaletteBar)
///////////////////////////////////////////////////
// CDrawBar construction/destruction

#define CYCAPTION 9     /* height of the caption */
/////////////////////////////////////////////////////////////////////////////
// CDrawBar construction/destruction

CDrawBar::CDrawBar()
{ 

	///////////////////////////////////////////// 
	m_nActiveTool			= -1;    // -1 = None Selected(edit or move) 
	m_nActiveToolOld 		= m_nActiveTool;
	m_nActiveDrawObject		= -1;    // -1 = None Selected(other objects) 
	m_nActiveDrawObjectOld 	= m_nActiveDrawObject;
	/////////////////////////////////
	m_nButtCount     = DB_BUTT_COUNT; 
	for (int i = 0; i<m_nButtCount;i++)
	{
		m_nCheck[i] = 0;  //  unchecked 
	}			
	m_bButtonDown	= FALSE;
	m_bToolHit		= FALSE;	  	
											
}

CDrawBar::~CDrawBar()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}
/////////////////////////////////////////////////////////////////////////////
// CDrawBar diagnostics

#ifdef _DEBUG
void CDrawBar::AssertValid() const
{
	CToolBar::AssertValid();
}

void CDrawBar::Dump(CDumpContext& dc) const
{
	CToolBar::Dump(dc);
}

#endif //_DEBUG


void CDrawBar::OnLButtonDown(UINT nFlags, CPoint point)
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
		CDrawBox* pDrawBox = (CDrawBox*) GetParent();
		CToolBar* pTool = (CToolBar*)GetParent()->
			GetDescendantWindow(IDW_DRAWBAR);
		////////////////////////////////////////////////////// check if Edit/Move
		nID = pTool->GetItemID(Num);								
		if((nID == IDB_EDIT || nID == IDB_MOVE)  )
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
			if(m_nActiveDrawObject<0) return;	
			////////////////////////////////////////////////////////////////	
			nID = pTool->GetItemID(m_nActiveDrawObject);								
			if(!pDrawBox->IsDrawObject(nID)) // Not right kind
				return;
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
		m_nActiveDrawObjectOld = m_nActiveDrawObject;
		m_nActiveDrawObject    = Num;
		if(m_nActiveDrawObject != m_nActiveDrawObjectOld)
		{
										
			m_bToolHit = FALSE;
			m_nCheck[m_nActiveDrawObject] 	= 1;      	//depressed 
			pTool->GetButtonInfo(m_nActiveDrawObject,nID,nStyle,iImage);								
			pTool->SetButtonInfo(m_nActiveDrawObject,nID,
					nStyle|TBBS_PRESSED,iImage);
			InvalidateButton(m_nActiveDrawObject);
			UpdateWindow(); // immediate feedback

//			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)nID);
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
			//////////////////////////////////////////////
			if(m_nActiveDrawObjectOld>=0 )
			{
				m_nCheck[m_nActiveDrawObjectOld] 	= 0;   		//uncheck 
				pTool->GetButtonInfo(m_nActiveDrawObjectOld,nID,nStyle,iImage);								
				pTool->SetButtonInfo(m_nActiveDrawObjectOld,nID,
						m_nCheck[m_nActiveDrawObjectOld],iImage);
				InvalidateButton(m_nActiveDrawObjectOld);
				UpdateWindow(); // immediate feedback
			}
		}
		//////////////////////////////////////////            
	} 
}

void CDrawBar::OnLButtonUp(UINT nFlags, CPoint point)
{ 
	UINT nID;
	/////////////////
	if (m_bButtonDown)
	{
		m_bButtonDown = !m_bButtonDown;
		ReleaseCapture();
        //////////////////////////////////////////// get Button ID
		CDrawBox* pDrawBox  = (CDrawBox*) GetParent();
		CToolBar* pTool 	= (CToolBar*)GetParent()->
									GetDescendantWindow(IDW_DRAWBAR);
		if(m_nActiveDrawObject<0) return;
		///////////////////////////////////////////////////////////////							
		nID = pTool->GetItemID(m_nActiveDrawObject);								
		if (m_bToolHit && (!pDrawBox->IsDrawObject(nID)) ) return;      // not acceptable
		///////////////////////////////////////////// set for ToolBox                      
		//////////////////////////////////////////////////////////////
		// Note: drawBar.m_nActiveDrawObject is 
		//					sequencial index starting at 0
		//       drawBox.m_nActiveDrawObject is
		//					drawID(used in dboxrsrc.h & dbglobal.h
		/////////////////////////////////////////////////////////////	                     
		//////////////////////////////////////////// set ID
		nID = pTool->GetItemID(m_nActiveDrawObject);								
		pDrawBox->SetActiveDrawObject((int)nID);//
		///////////////////////////////////////// 
		if(!m_bToolHit)
			pDrawBox->SetActiveTool(-1);//
		else
		{	
			nID = pTool->GetItemID(m_nActiveTool);								
			pDrawBox->SetActiveTool((int)nID);//
		}	 
		///////////////////////////////////////////// 
		pDrawBox->GoRespondtoMouse(); 
		/////////////////////////////
	}
	else	
		CPaletteBar::OnLButtonUp(nFlags, point);
	
}

///////////////////////////////// end of module ///////////////////// 

