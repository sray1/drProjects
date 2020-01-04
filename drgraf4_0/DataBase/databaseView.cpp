// databaseView.cpp : implementation of the CDatabaseView class
//

#include "stdafx.h"
#include "database.h"

#include "databaseDoc.h"
#include "databaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView

IMPLEMENT_DYNCREATE(CDatabaseView, CView)

BEGIN_MESSAGE_MAP(CDatabaseView, CView)
	//{{AFX_MSG_MAP(CDatabaseView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView construction/destruction

CDatabaseView::CDatabaseView()
{
	// TODO: add construction code here

}

CDatabaseView::~CDatabaseView()
{
}

BOOL CDatabaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView drawing

void CDatabaseView::OnDraw(CDC* pDC)
{
	CDatabaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView printing

BOOL CDatabaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDatabaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDatabaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView diagnostics

#ifdef _DEBUG
void CDatabaseView::AssertValid() const
{
	CView::AssertValid();
}

void CDatabaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDatabaseDoc* CDatabaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatabaseDoc)));
	return (CDatabaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView message handlers
