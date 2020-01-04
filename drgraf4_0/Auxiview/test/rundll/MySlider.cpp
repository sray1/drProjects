// MySlider.cpp : implementation file
//

#include "stdafx.h"
#include "rundll.h"
#include "MySlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySlider

CMySlider::CMySlider()
{
}

CMySlider::~CMySlider()
{
}


BEGIN_MESSAGE_MAP(CMySlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CMySlider)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySlider message handlers

BOOL CMySlider::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	// TODO: Add your specialized code here and/or call the base class
	WNDCLASS wc;
	::GetClassInfo(AfxGetApp()->m_hInstance, TRACKBAR_CLASS, &wc);

	HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	wc.hCursor = hCursor;
	wc.lpszClassName = "New Slider";
	
	AfxRegisterClass(&wc);

/***
	CString ClassName = ::AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		hcursor);

	::GetClassInfo(AfxGetApp()->m_hInstance,ClassName,&wc);
	
	
	lpCreateStruct->lpszClass = ClassName;
***/

	// initialize common controls
//	VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTLS_REG));

	CWnd* pWnd = this;
	return pWnd->Create("New Slider", NULL, dwStyle, rect, pParentWnd, nID);
	

//	return CSliderCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

int CMySlider::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{


	if (CSliderCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	
	return 0;
}
