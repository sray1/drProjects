// rundllView.cpp : implementation of the CRundllView class
//

#include "stdafx.h"
#include "rundll.h"

#include "rundllDoc.h"
#include "rundllView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRundllView

IMPLEMENT_DYNCREATE(CRundllView, CView)

BEGIN_MESSAGE_MAP(CRundllView, CView)
	//{{AFX_MSG_MAP(CRundllView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRundllView construction/destruction

CRundllView::CRundllView()
{
	// TODO: add construction code here

}

CRundllView::~CRundllView()
{
}

BOOL CRundllView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRundllView drawing

void CRundllView::OnDraw(CDC* pDC)
{
	CRundllDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRundllView printing

BOOL CRundllView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRundllView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRundllView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRundllView diagnostics

#ifdef _DEBUG
void CRundllView::AssertValid() const
{
	CView::AssertValid();
}

void CRundllView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRundllDoc* CRundllView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRundllDoc)));
	return (CRundllDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRundllView message handlers
