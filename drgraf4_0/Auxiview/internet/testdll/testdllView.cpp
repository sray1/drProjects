// testdllView.cpp : implementation of the CTestdllView class
//

#include "stdafx.h"
#include "testdll.h"

#include "testdllDoc.h"
#include "testdllView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestdllView

IMPLEMENT_DYNCREATE(CTestdllView, CView)

BEGIN_MESSAGE_MAP(CTestdllView, CView)
	//{{AFX_MSG_MAP(CTestdllView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestdllView construction/destruction

CTestdllView::CTestdllView()
{
	// TODO: add construction code here

}

CTestdllView::~CTestdllView()
{
}

BOOL CTestdllView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestdllView drawing

void CTestdllView::OnDraw(CDC* pDC)
{
	CTestdllDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestdllView printing

BOOL CTestdllView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestdllView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestdllView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestdllView diagnostics

#ifdef _DEBUG
void CTestdllView::AssertValid() const
{
	CView::AssertValid();
}

void CTestdllView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestdllDoc* CTestdllView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestdllDoc)));
	return (CTestdllDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestdllView message handlers
