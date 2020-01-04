// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "rundll.h"
#include "MyButton.h"
#include "def_usr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

BOOL CMyButton::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{

	CWnd* pWnd = this;
	return CButton::Create("", dwStyle, rect, pParentWnd, nID);
	
}

int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{


	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	
	return 0;
}

void CMyButton::OnClicked() 
{
	GetParent()->SendMessage(UM_OPEN_FRAME);
}
////////////////
