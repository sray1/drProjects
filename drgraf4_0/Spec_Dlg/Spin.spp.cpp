// spin.cpp: Spin control - C++ class wrapping "MicroScroll" control in a DLL
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

#include "stdafx.h"

#include "spin.h"

IMPLEMENT_DYNAMIC(CSpinControl, CWnd)

BOOL CSpinControl::Create(DWORD dwStyle, const RECT& rect,
		CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create("MicroScroll", NULL, dwStyle, rect, pParentWnd, nID);
}

WNDPROC* CSpinControl::GetSuperWndProcAddr()
{
	static WNDPROC pfnSuper;
	return &pfnSuper;
}
BEGIN_MESSAGE_MAP(CSpinControl, CWnd)
	//{{AFX_MSG_MAP(CSpinControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// inlines
//inline CSpinControl::CSpinControl()
CSpinControl::CSpinControl()
	{ }

CWnd* CSpinControl::GetAssociate()
	{ return CWnd::FromHandle((HWND)SendMessage(MSM_HWNDASSOCIATEGET)); }
void CSpinControl::SetAssociate(CWnd* pNew)
	{ SendMessage(MSM_HWNDASSOCIATESET, (UINT)pNew->GetSafeHwnd()); }
void CSpinControl::GetRange(UINT& iMin, UINT& iMax)
	{ DWORD dw = SendMessage(MSM_DWRANGEGET);
		iMin = LOWORD(dw); iMax = HIWORD(dw);
	}
void CSpinControl::SetRange(UINT iMin, UINT iMax)
	{ SendMessage(MSM_DWRANGESET, 0, MAKELONG(iMin, iMax)); }
UINT CSpinControl::GetCurrentPos()
	{ return (UINT)SendMessage(MSM_WCURRENTPOSGET); }
void CSpinControl::SetCurrentPos(UINT iPos)
	{ SendMessage(MSM_WCURRENTPOSSET, iPos); }

