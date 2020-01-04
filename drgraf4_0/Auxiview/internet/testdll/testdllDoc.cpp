// testdllDoc.cpp : implementation of the CTestdllDoc class
//

#include "stdafx.h"
#include "testdll.h"

#include "testdllDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestdllDoc

IMPLEMENT_DYNCREATE(CTestdllDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestdllDoc, CDocument)
	//{{AFX_MSG_MAP(CTestdllDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestdllDoc construction/destruction

CTestdllDoc::CTestdllDoc()
{
	// TODO: add one-time construction code here

}

CTestdllDoc::~CTestdllDoc()
{
}

BOOL CTestdllDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestdllDoc serialization

void CTestdllDoc::Serialize(CArchive& ar)
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
// CTestdllDoc diagnostics

#ifdef _DEBUG
void CTestdllDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestdllDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestdllDoc commands
