// BasePage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
/////////////////////
#include "SasePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSasePage property page

IMPLEMENT_DYNCREATE(CSasePage, CPropertyPage)

CSasePage::CSasePage(CWnd* pMainWnd, SOLIDPROC SolProc, UINT nIDTemplate, UINT nIDCaption)
					:CPropertyPage(nIDTemplate, nIDCaption)
{
	m_pWnd		= pMainWnd;
	m_SolProc	= SolProc;
	///////////////////////
	m_nMesh		= 1;
	m_nMesh_V	= 1;
}

CSasePage::CSasePage(CWnd* pMainWnd, SOLIDPROC SolProc, LPCTSTR lpszTemplateName, UINT nIDCaption):
					CPropertyPage(lpszTemplateName, nIDCaption)
{
	m_pWnd			= pMainWnd;
	m_SolProc		= SolProc;
	///////////////////////
	m_nMesh			= 1;
	m_nMesh_V		= 1;
	m_bGenBCurve	= FALSE;
	m_bGenBPatch	= FALSE;
}

CSasePage::CSasePage():CPropertyPage()
{
}

CSasePage::~CSasePage()
{
}

void CSasePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSasePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSasePage, CPropertyPage)
	//{{AFX_MSG_MAP(CSasePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSasePage message handlers
///////////////////////////// end of Module //////////////////////////////
