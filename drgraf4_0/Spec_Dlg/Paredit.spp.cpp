// paredit.cpp: C++ derived edit control for numbers/letters etc
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "paredit.h"
#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// ParsedEdit

CParsedEdit::CParsedEdit()
{
	m_wParseStyle = 0;
	m_nIncrement  = 1;
}

BEGIN_MESSAGE_MAP(CParsedEdit, CEdit)
	//{{AFX_MSG_MAP(CParsedEdit)
	ON_WM_CHAR()
	ON_WM_VSCROLL()     // for associated spin controls
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Creating from C++ code

BOOL CParsedEdit::Create(DWORD dwStyle, const RECT& rect,
		CWnd* pParentWnd, UINT nID)
{
	m_wParseStyle = LOWORD(dwStyle);
	// figure out edit control style
	DWORD dwEditStyle = MAKELONG(ES_LEFT, HIWORD(dwStyle));
	return CWnd::Create("EDIT", NULL, dwEditStyle, rect, pParentWnd, nID);
}

/////////////////////////////////////////////////////////////////////////////
// Aliasing on top of an existing Edit control

BOOL CParsedEdit::SubclassEdit(UINT nID, CWnd* pParent, WORD wParseStyle)
{
	m_wParseStyle = wParseStyle;
	
	// SubclassWindow requires an HWND so we call the Windows GetDlgItem
	// and avoid creating a tempory CWnd and then calling GetSafeHwnd
	HWND hWndEdit = ::GetDlgItem(pParent->m_hWnd, nID);
	if (hWndEdit == NULL)
		return FALSE;
	return SubclassWindow(hWndEdit);
}

/////////////////////////////////////////////////////////////////////////////
// Input character filter

void CParsedEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	WORD type;

	if (nChar < 0x20)
		type = PES_ALL;                         // always allow control chars
	else if (nChar >= '0' && nChar <= '9')
		type = PES_NUMBERS;
	else if (nChar >= 'A' && nChar <= 'Z')      // hard coded to english
		type = PES_LETTERS;
	else if (nChar >= 'a' && nChar <= 'z')
		type = PES_LETTERS;
	else
		type = PES_OTHERCHARS;

	if (m_wParseStyle & type)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);  // permitted
	}
	else
	{
		// illegal character - inform parent
		OnBadInput();
	}
}

/////////////////////////////////////////////////////////////////////////////
// Spin controls will send scroll messages
void CParsedEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	BOOL bOk; 
	int nDelta = 1;
	
    UINT nEditID;
    nEditID = GetDlgCtrlID();     // whose ID I'm getting??????    This is not right!!!
    
	if(( nEditID == IDC_TILT) ||( nEditID == IDC_ROTATION))
	{	
		m_nIncrement = GetParent()->GetDlgItemInt(IDC_SPIN_INCREMENT, &bOk); 
	}
	else
		m_nIncrement = nDelta;
	if (nSBCode == SB_LINEDOWN)
		nDelta = -m_nIncrement;
	else if (nSBCode == SB_LINEUP)
		nDelta =  m_nIncrement;
	else
		return; // nothing special
		CSpinControl* pSpin = (CSpinControl*)(pScrollBar);
		ASSERT(pSpin != NULL);
	    UINT nMin,nMax;
	    pSpin->GetRange(nMin,nMax);
/*
	CString str;
	char buf[80];
	sprintf(buf,"ParEdit:nMin = %u  nMax = %u",nMin, nMax);
	AfxMessageBox(str=buf);
*/		 
	       

	// set the focus to this edit item and select it all
	SetFocus(); 

	//Get the number in the control.
	int nOld = GetParent()->GetDlgItemInt(GetDlgCtrlID(), &bOk);
	if (bOk)
	{
		// The MuScroll control also supports range checking
		// for this example, we just prevent overflow 
		int nNew = nOld + nDelta;
		if (nNew >= (int)nMin && nNew <= (int)nMax) 
		{
			GetParent()->SetDlgItemInt(GetDlgCtrlID(), nNew);
		}
		else
			bOk = FALSE;
	}

	if (!bOk)
		OnBadInput();
	SetSel(0, -1);
	
	if(bOk)           // RePaint
	{
		if((nEditID == IDC_TILT) ||(nEditID == IDC_ROTATION))
		{	
			RECT RectSample; 
			CWnd* pWnd = GetParent()->GetDlgItem(IDC_SAMPLE);
			pWnd->GetWindowRect(&RectSample);
			GetParent()->ScreenToClient(&RectSample);           
			/////////////////////////////////////// Redraw  Axes etc.	
			GetParent()->InvalidateRect(&RectSample,TRUE);
			GetParent()->UpdateWindow();
			//////////////////////////// 
		}				
	}
}

/////////////////////////////////////////////////////////////////////////////
// default bad input handler, beep (unless parent notification
//    returns -1.  Most parent dialogs will return 0 or 1 for command
//    handlers (i.e. Beep is the default)

void CParsedEdit::OnBadInput()
{
	if (GetParent()->SendMessage(WM_COMMAND,
		GetDlgCtrlID(), MAKELONG(m_hWnd, PEN_ILLEGALCHAR)) != -1)
	{
		MessageBeep(MB_ICONEXCLAMATION);
	}
}

/////////////////////////////////////////////////////////////////////////////
