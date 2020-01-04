// dboxedoc.cpp : implementation of the CDBoxEBoxDoc class
//

#include "stdafx.h"
#include "dboxebox.h"

#include "dboxedoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxDoc

IMPLEMENT_DYNCREATE(CDBoxEBoxDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBoxEBoxDoc, CDocument)
	//{{AFX_MSG_MAP(CDBoxEBoxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxDoc construction/destruction

CDBoxEBoxDoc::CDBoxEBoxDoc()
{
	// TODO: add one-time construction code here
}

CDBoxEBoxDoc::~CDBoxEBoxDoc()
{
}

BOOL CDBoxEBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxDoc serialization

void CDBoxEBoxDoc::Serialize(CArchive& ar)
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
// CDBoxEBoxDoc diagnostics

#ifdef _DEBUG
void CDBoxEBoxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBoxEBoxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxDoc commands
