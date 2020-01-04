// MyAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "viewex.h"
#include "MyAboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg dialog


CMyAboutDlg::CMyAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyAboutDlg)
	m_bCheck = FALSE;
	//}}AFX_DATA_INIT
}


void CMyAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyAboutDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CMyAboutDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg message handlers

void CMyAboutDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	CStatic *pStat = (CStatic *)GetDlgItem(IDC_MYSTATIC);
	CClientDC dc(pStat);
	CRect rect;
	CPen pen, *oldpen;
	CBrush br,*oldbr;
	pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	br.CreateSolidBrush(RGB(0,0,255));
	oldpen = dc.SelectObject(&pen);
	oldbr = dc.SelectObject(&br);
	pStat->GetClientRect(&rect);
	rect.InflateRect(-1,-1);
	pStat->InvalidateRect(NULL);
	pStat->UpdateWindow();
	dc.Rectangle(&rect);
	dc.SelectObject(oldpen);
	pen.DeleteObject();
	dc.SelectObject(oldbr);
	br.DeleteObject();
	pen.CreatePen(PS_SOLID,2,RGB(255,255,0));
	oldpen = dc.SelectObject(&pen);
	////////////////////////////////////////
//	dc.SetTextAlign(TA_UPDATECP
	////////////////
	UpdateData(TRUE);
	if (m_bCheck)
		;
//		dc.TextOut(

	UpdateData(FALSE);
}
