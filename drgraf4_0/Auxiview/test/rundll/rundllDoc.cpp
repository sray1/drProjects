// rundllDoc.cpp : implementation of the CRundllDoc class
//

#include "stdafx.h"
#include "rundll.h"

#include "rundllDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRundllDoc

IMPLEMENT_DYNCREATE(CRundllDoc, CDocument)

BEGIN_MESSAGE_MAP(CRundllDoc, CDocument)
	//{{AFX_MSG_MAP(CRundllDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRundllDoc construction/destruction

CRundllDoc::CRundllDoc()
{
	// TODO: add one-time construction code here

}

CRundllDoc::~CRundllDoc()
{
}

BOOL CRundllDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRundllDoc serialization

void CRundllDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRundllDoc diagnostics

#ifdef _DEBUG
void CRundllDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRundllDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRundllDoc commands
