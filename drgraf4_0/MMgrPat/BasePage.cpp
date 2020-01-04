// BasePage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
/////////////////////
#include "BasePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasePage property page

IMPLEMENT_DYNCREATE(CBasePage, CPropertyPage)

CBasePage::CBasePage(CWnd* pMainWnd, PATCHPROC PatProc, UINT nIDTemplate, UINT nIDCaption)
					:CPropertyPage(nIDTemplate, nIDCaption)
{
	m_pWnd		= pMainWnd;
	m_PatProc	= PatProc;
	///////////////////////
	m_nMesh		= 1;
	m_nMesh_V	= 1;
}

CBasePage::CBasePage(CWnd* pMainWnd, PATCHPROC PatProc, LPCTSTR lpszTemplateName, UINT nIDCaption):
					CPropertyPage(lpszTemplateName, nIDCaption)
{
	m_pWnd			= pMainWnd;
	m_PatProc		= PatProc;
	///////////////////////
	m_nMesh			= 1;
	m_nMesh_V		= 1;
	m_bGenBCurve	= FALSE;
}

CBasePage::CBasePage():CPropertyPage()
{
}

CBasePage::~CBasePage()
{
}

void CBasePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBasePage, CPropertyPage)
	//{{AFX_MSG_MAP(CBasePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasePage message handlers
///////////////////////////// end of Module //////////////////////////////
