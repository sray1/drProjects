// elemdoc.cpp : implementation file
//

#include "stdafx.h"
#include "drgraf.h"
#include "elemdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElemDoc

IMPLEMENT_SERIAL(CElemDoc, CDocument, 0 /* schema number*/ )

CElemDoc::CElemDoc()
{
	/////////////////////////////////////////// Node     
	m_CurrentNodeID = "";
	m_AnchorNodeID  = "";
	m_MaxNodes 		= m_NodeList.GetCount();
}

BOOL CElemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CElemDoc::~CElemDoc()
{
}


BEGIN_MESSAGE_MAP(CElemDoc, CDocument)
	//{{AFX_MSG_MAP(CElemDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElemDoc serialization

void CElemDoc::Serialize(CArchive& ar)
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
// CElemDoc commands
