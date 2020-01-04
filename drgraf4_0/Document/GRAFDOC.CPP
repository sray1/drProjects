// grafdoc.cpp : implementation file
//

#include "stdafx.h"
#include "drgraf.h"

#include "grafdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif    

/////////////////////////////////////////////////////////////////////////////
// CGrafDoc

IMPLEMENT_SERIAL(CGrafDoc, CDocument, 0 /* schema number*/ )

BEGIN_MESSAGE_MAP(CGrafDoc, CDocument)
	//{{AFX_MSG_MAP(CGrafDoc)
	ON_COMMAND(IDM_DRAW_AXIS, OnDrawAxis)
	ON_COMMAND(IDM_DRAW_EYEPOSITION, OnDrawEyeposition)
	ON_COMMAND(IDM_DRAW_LAYER, OnDrawLayer)
	ON_COMMAND(ID_OPTIONS_PENCHANGE, OnOptionsPenchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGrafDoc::CGrafDoc()
{
//	ReadDefaults();
//	Initialize();
}

BOOL CGrafDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CGrafDoc::~CGrafDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CGrafDoc serialization

void CGrafDoc::Serialize(CArchive& ar)
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
// CGrafDoc commands

void CGrafDoc::ReplacePen()
{
	// Change the current pen to reflect the new user-specified width.
	m_PenCur.DeleteObject();
	m_PenCur.CreatePen(m_nPenStyle, m_nPenWidth, m_nPenColor); 
}
//////////////////// end of module //////////////
