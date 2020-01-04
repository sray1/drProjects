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
#include "drgraf.h"
///////////////////
#include "SpDrawVu.h"	// Spectra
#include "SpDataVu.h"
#include "HsDrawVu.h"	// History
#include "HsDataVu.h"

#include "DrSplit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrSplitFrm

// Create a splitter window which splits an output text view and an input view
//                           |
//    TEXT VIEW (CTextView)  | INPUT VIEW (CInputView)
//                           |

IMPLEMENT_DYNCREATE(CDrSplitFrm, CMDIChildWnd)

CDrSplitFrm::CDrSplitFrm()
{
}

CDrSplitFrm::~CDrSplitFrm()
{
}


BOOL CDrSplitFrm::OnCreateClient(LPCREATESTRUCT,
	 CCreateContext* pContext)
{
	// create a splitter with 2 rows, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 2, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - Spectral Graphical Input/Output View
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CSpDrawVu), CSize(130, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - Spectral Data Input/Output View 
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CSpDataVu), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	// add the third splitter pane - History Graphical Input/Output View
	if (!m_wndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CHsDrawVu), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}

	// add the fourth splitter pane - History Data Input/Output View 
	if (!m_wndSplitter.CreateView(1, 1,
		RUNTIME_CLASS(CHsDataVu), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create fourth pane\n");
		return FALSE;
	}


	// activate the Spectral Graphical Input/Output View
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDrSplitFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDrSplitFrm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// 

IMPLEMENT_DYNAMIC(CDrSplitWnd, CSplitterWnd)

CDrSplitWnd::CDrSplitWnd()
{
}

CDrSplitWnd::~CDrSplitWnd()
{
}

CWnd* CDrSplitWnd::GetActivePane(int* pRow, int* pCol)
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


