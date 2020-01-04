// inputvw.cpp : implementation file
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

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecView

IMPLEMENT_DYNCREATE(CSpecView, CView)

CSpecView::CSpecView()
{
}

CSpecView::~CSpecView()
{
}

void CSpecView::OnUpdate(CView*, LPARAM, CObject*)
{
	CMainDoc* pDoc = GetDocument();
	m_strData = pDoc->m_strData;

	if (pDoc->m_colorData == RGB(255, 0, 0))
		m_iColor = 0;
	else if (pDoc->m_colorData == RGB(0, 255, 0))
		m_iColor = 1;
	else if (pDoc->m_colorData == RGB(0, 0, 255))
		m_iColor = 2;
	else
		m_iColor = -1;

TRACE2("OnUpdate: m_iColor = %d ($%lx)\n", m_iColor, pDoc->m_colorData);

	UpdateData(FALSE);  // set the data into the controls
}

BEGIN_MESSAGE_MAP(CSpecView, CFormView)
	//{{AFX_MSG_MAP(CSpecView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecView message handlers
/////////////////////////////////////////////////////////////////////////////
