// splitter.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "splitter.h"
#include "rundllDoc.h"
#include "inputvw.h"
#include "HistVw.h"
#include "SpecVw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterFrame

// Create a splitter window which splits an output text view and an input view
//                           |
//    TEXT VIEW (CTextView)  | INPUT VIEW (CInputView)
//                           |

IMPLEMENT_DYNCREATE(CSplitterFrame, CMDIChildWnd)

CSplitterFrame::CSplitterFrame()
{
}

CSplitterFrame::~CSplitterFrame()
{
}


BOOL CSplitterFrame::OnCreateClient(LPCREATESTRUCT,
	 CCreateContext* pContext)
{
	// create a splitter with 2 rows, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 2, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(130, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CSpecVw), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	// add the third splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CInputView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}

	// add the fourth splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(1, 1,
		RUNTIME_CLASS(CHistVw), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create fourth pane\n");
		return FALSE;
	}


	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(1,1));

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSplitterFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSplitterFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********
CWnd* CViewExSplitWnd::GetActivePane(int* pRow, int* pCol)
{
	ASSERT_VALID(this);

	// attempt to use active view of frame window
	CWnd* pView = NULL;
 	CFrameWnd* pFrameWnd = GetParentFrame();
	ASSERT_VALID(pFrameWnd);
	pView = pFrameWnd->GetActiveView();

	// failing that, use the current focus
	if (pView == NULL)
		pView = GetFocus();

	return pView;
}

*******/


