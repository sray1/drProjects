// ODDialog.cpp : implementation file
//

#include "stdafx.h"
#include "rundll.h"
#include "ODDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODDialog dialog


CODDialog::CODDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CODDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CODDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CODDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CODDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CODDialog, CDialog)
	//{{AFX_MSG_MAP(CODDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODDialog message handlers
