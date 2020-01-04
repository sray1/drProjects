// NodGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage property page

IMPLEMENT_DYNCREATE(CNodeGeomPage, CPropertyPage)

CNodeGeomPage::CNodeGeomPage() : CPropertyPage(CNodeGeomPage::IDD,CNodeGeomPage::IDS)
{
	//{{AFX_DATA_INIT(CNodeGeomPage)
	m_NGText = _T("");
	//}}AFX_DATA_INIT
}

CNodeGeomPage::~CNodeGeomPage()
{
}

void CNodeGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeGeomPage)
	DDX_Text(pDX, IDC_NODEGEOM_TEXT, m_NGText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage message handlers
