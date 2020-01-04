// databaseDoc.cpp : implementation of the CDatabaseDoc class
//

#include "stdafx.h"
#include "database.h"
#include "databaseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc

IMPLEMENT_DYNCREATE(CDatabaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CDatabaseDoc, CDocument)
	//{{AFX_MSG_MAP(CDatabaseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc construction/destruction

CDatabaseDoc::CDatabaseDoc()
{
	// TODO: add one-time construction code here
	m_CurrentItem = "Node 1";
	PopulateMap();
}

CDatabaseDoc::~CDatabaseDoc()
{
}

BOOL CDatabaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

UINT CDatabaseDoc::GetObjectType_N_Item(CString& strItem)
{
	UINT uValue;
	////////////
	strItem = GetCurrentItem();
	///
	CString strPar = GetCurrentParent();
	if(strPar == "")	// Top Level
	{
		m_strUintMap.Lookup(strItem,uValue);
		strItem = "";
	}
	else				// child
		m_strUintMap.Lookup(strPar,uValue);
	/////////
	return uValue;
}

int CDatabaseDoc::PopulateMap()
{
	m_strUintMap["INPUT NODE"]			= NODE;
	m_strUintMap["CONTROL NODE"]		= CNODE;
	m_strUintMap["CURVE"]				= CURVE;
	m_strUintMap["PROFILE CURVE"]		= PROFILE_C;
	m_strUintMap["PATCH"]				= PATCH;
	m_strUintMap["PROFILE PATCH"]		= PROFILE_P;
	m_strUintMap["SOLID"]				= SOLID;
	m_strUintMap["SUBASSEMBLY"]			= OBJ3D;
	/////////////////////////////////////
	m_strUintMap["MESH NODE"]			= MNODE;
	m_strUintMap["MESH CONTROL NODE"]	= MCNODE;
	m_strUintMap["1D MESH"]				= MESH1D;
	m_strUintMap["2D MESH"]				= MESH2D;
	m_strUintMap["3D MESH"]				= MESH3D;
	m_strUintMap["MESH SUBASSEMBLY"]	= MBJ3D;
	//////////
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc serialization

void CDatabaseDoc::Serialize(CArchive& ar)
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
// CDatabaseDoc diagnostics

#ifdef _DEBUG
void CDatabaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDatabaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc commands
/*debu
int CDatabaseDoc::FillTreeCtrl(CTreeCtrl & TCtrl)
{
	CTreeHandler TH;
	TH.PopulateTreeCtrl(TCtrl);
	UpdateAllViews(NULL);

	return 0;
}
*/
