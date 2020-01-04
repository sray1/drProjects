// samplvw.cpp : implementation of the CDeckView class
//

#include "stdafx.h"
#include <limits.h> // for INT_MAX
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
//////////////////////
#include "Def_View.h"

#include "DeckView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	MARGIN			10
#define	MARGIN_PRINT	720	// TWIPS
#define CARD_LEN		80
#define	CARD_NO_COL		CARD_LEN + 5
#define	CARD_NO_LEN		7
#define CARD_WIDTH		(CARD_NO_COL + CARD_NO_LEN)
/////////////////////////////////////////////////////////////////////////////
// CDeckView

IMPLEMENT_DYNCREATE(CDeckView, CScrollView)

BEGIN_MESSAGE_MAP(CDeckView, CScrollView)
	//{{AFX_MSG_MAP(CDeckView)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_COMMAND(IDM_DECK_FORMAT_FIX, OnDeckFormatFix)
	ON_UPDATE_COMMAND_UI(IDM_DECK_FORMAT_FIX, OnUpdateDeckFormatFix)
	ON_COMMAND(IDM_DECK_FORMAT_FREE, OnDeckFormatFree)
	ON_UPDATE_COMMAND_UI(IDM_DECK_FORMAT_FREE, OnUpdateDeckFormatFree)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeckView construction/destruction

CDeckView::CDeckView()
{
	m_nView					= VIEWDECK;  // View12 = 1 etc.
	m_pOldFont				= NULL;
	m_nCardIndexBeg			= 0;			// Begin  CardIndex for CurrentPage Printing
//	m_nCardIndexEnd			= 0;			// Ending CardIndex for CurrentPage Printing
	m_nCardCount			= 0;				// Deck Card Count	
//	m_nCardWidth;				// width of Card in current device units
//	m_nCardHeight;				// height of Card in current device untis
//	m_nCardsPerPrintedPage;		// how many Cards fit on a printed page
//	m_nLinesPerPrintedPage;		// how many Lines fit on a printed page
	m_nCurrentPage			= 1;
//	m_nPageHeight;
//	m_nPageWidth;
	////////////////////////
//	m_nHeaderHeight;
	m_nHeaderBot			= 0;
	////////////////////////
//	m_nFooterHeight;
//	m_nFooterTop;
}

CDeckView::~CDeckView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDeckView drawing

void CDeckView::OnDeckFormatFix() 
{
	GetDeckMgr()->SetFormatted(TRUE);	
}

void CDeckView::OnUpdateDeckFormatFix(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetDeckMgr()->IsFormatted());
}

void CDeckView::OnDeckFormatFree() 
{
	GetDeckMgr()->SetFormatted(FALSE);	
}

void CDeckView::OnUpdateDeckFormatFree(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!(GetDeckMgr()->IsFormatted()));
}

void CDeckView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// The size of text that is displayed, printed or previewed changes
	// depending on the DC.  We explicitly call OnPrepareDC() to prepare
	// CClientDC objects used for calculating text positions and to
	// prepare the text metric member variables of the CRowView object.
	// The framework also calls OnPrepareDC() before passing the DC to
	// OnDraw().
	///////////////////////////////////////////////////////
//	if(!pDC->IsPrinting())	// For Printing, GDI allocated in BeginPrint 
	{
		///////////////////////////////////////////////////////////////////////////
		CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
		CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
		CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
		///////////////////////////////////////////////////////// Color / lOGfONT
		COLORREF Color 	= pDrFont->GetTextColor();
		LOGFONT lf 		= pDrFont->GetCurrentLogFont();
 		///////////////////////////////////////////////////////// set font.
		m_Font.DeleteObject();
		////////////////
		m_Font.CreateFontIndirect(&lf);
		m_pOldFont = (CFont*)(pDC->SelectObject(&m_Font));
		m_pOldFont->GetLogFont(&m_LF);
		///////////////////////////////////////////////////////// TextAttribs
		pDC->SetTextColor(Color);
		pDC->SetBkMode(TRANSPARENT);
		//////////////////////////////////////////////
	}
	//////////////////////////////////////////////
	CalculateCardMetrics(pDC);
	UpdateScrollSizes();
	/////////////////////////////////////
	CScrollView::OnPrepareDC(pDC, pInfo);
}

void CDeckView::OnDraw(CDC* pDC)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
	///////////////////////////////////////////////////////// Coords of UpdateRgn
	RECT		ClipRect;
	pDC->GetClipBox(&ClipRect);
	/////////////////////////////////////////////////////////////////// Is Deck Empty
	CList<CString,CString>*	pDeckList	= GetDeckMgr()->GetDeckList();
	if(pDeckList->IsEmpty())
		return;
	/////////////////////////////////////////////////////////////////// Deck Not Empty
	///////////////////////////////////////////////////////// Display Cards
	int	Y = m_nHeaderBot; 
	POSITION pos = pDeckList->GetHeadPosition( );
	CString strCard;

	for (int nCount=0;pos !=NULL;nCount++)
	{
		strCard = pDeckList->GetNext( pos);
		////////
		Y += m_nCardHeight;
		////////////////
		if (!pDC->IsPrinting())
		{
			if(Y + m_nCardHeight >= ClipRect.top && Y <= ClipRect.bottom) 
				pDC->TextOut(MARGIN,Y,strCard);
		}
		else
			pDC->TextOut(MARGIN,Y,strCard);
	}
	//////////////////////////////// Get Original Font back
	if (!pDC->IsPrinting())	// for printing, after footer
	{
		CFont Font;
		////////////////
		Font.CreateFontIndirect(&m_LF);
		pDC->SelectObject(&Font);
		m_Font.DeleteObject();
		///////////////////////////////////////
	}
	///////
	return;

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDeckView diagnostics

#ifdef _DEBUG
void CDeckView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDeckView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

#endif //_DEBUG
CDrGrafDoc* CDeckView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrGrafDoc)));
	return (CDrGrafDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CDeckView message handlers

int CDeckView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	// Give the document a pointer to this view
//	GetDocument()->m_pListView = this;

	return 0;
}

void CDeckView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CDrGrafDoc* pDoc		= GetDocument();
	/////////////////////////////////////////////////////////////////// Update
	
}

void CDeckView::UpdateScrollSizes()
{
	// UpdateScrollSizes() is called when it is necessary to adjust the
	// scrolling range or page/line sizes.  There are two occassions
	// where this is necessary:  (1) when a new Card is added-- see
	// UpdateCard()-- and (2) when the window size changes-- see OnSize().

	CRect rectClient;
	GetClientRect(&rectClient);

	// The vert scrolling range is the total display height of all
	// of the Cards.
	CSize sizeTotal(m_nCardWidth,
		m_nCardHeight * (min(m_nCardCount, LastViewableCard()) ) + MARGIN  );

	// The vertical per-page scrolling distance is equal to the
	// how many Cards can be displayed in the current window, less
	// one Card for paging overlap.
	CSize sizePage(m_nCardWidth/5,
			max(m_nCardHeight,
				((rectClient.bottom/m_nCardHeight)-1)*m_nCardHeight));

	// The vertical per-line scrolling distance is equal to the
		// height of the Card.
	CSize sizeLine(m_nCardWidth/20, m_nCardHeight);

	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

void CDeckView::GetCardWidthHeightCount(CDC* pDC, int& nCardWidth, int& nCardHeight,
													int& nCardCount)
{
	CDrGrafDoc* pDoc		= GetDocument();
	/////////////////////////////////////////////////////////////////// Update
//	pDoc->GetDeckMgr()->UpdateDeckList();
	/////////////////////////////////////////////////////////////////// Is Deck Empty
	CList<CString,CString>*	pDeckList	= GetDeckMgr()->GetDeckList();
	if(pDeckList->IsEmpty())
	{
		nCardWidth	= 1;
		nCardHeight	= 1;
		nCardCount	= 0;
		////////////////
		return;
	}
	/////////////////////////////////////////////////////////////////// Deck Not Empty
	int			LineWidth = 0;
	SIZE		Size;
	TEXTMETRIC	TM;
	pDC->GetTextMetrics(&TM);
	///////////////////////////////////////////////////////// find Extents
	int	nCount; 
	POSITION pos = pDeckList->GetHeadPosition();
	CString strCard;
	for (nCount=0;pos !=NULL;nCount++)
	{
		strCard = pDeckList->GetNext( pos);
		int nLen = strCard.GetLength(); 
//		Size = pDC->GetTextExtent(strCard,strCard.GetLength());
		Size = pDC->GetTextExtent(strCard,nLen);
		if(Size.cx>LineWidth)
			LineWidth = Size.cx;
	}
	////////////
	Size.cx = LineWidth + MARGIN;
	Size.cy = TM.tmHeight + TM.tmExternalLeading;
	////////////
	nCardCount	= nCount;
	nCardWidth	= Size.cx;
	nCardHeight	= Size.cy;
	///////
	return;
}

int CDeckView::LastViewableCard()
{
	return ( (m_nCardHeight > 0)?INT_MAX / m_nCardHeight - 1 : INT_MAX);
}

void CDeckView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDrGrafDoc* pDoc		= GetDocument();
	/////////////////////////////////////////////////////////////////// Update
	GetDeckMgr()->UpdateDeckList();
	///////////////////
	Invalidate();
	UpdateWindow();
}

void CDeckView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// OnBeginPrinting() is called after the user has committed to
	// printing by OK'ing the Print dialog, and after the framework
	// has created a CDC object for the printer or the preview view.

	// This is the right opportunity to set up the page range.
	// Given the CDC object, we can determine how many Cards will
	// fit on a page, so we can in turn determine how many printed
	// pages represent the entire document.
	//////////////////////////////////////////////
//	pDC->SetMapMode(MM_TWIPS);
	//////////////////////////////////////////////////////////////
	m_nPageHeight	= pDC->GetDeviceCaps(VERTRES);
	m_nPageWidth	= pDC->GetDeviceCaps(HORZRES);
	//////////////////////////////////////////////
	m_nHeaderHeight	= 4 * m_nCardHeight;
	m_nFooterHeight	= 3 * m_nCardHeight;
	//////////////////////////
	m_nLinesPerPrintedPage = m_nPageHeight	/ m_nCardHeight;
	m_nCardsPerPrintedPage = (m_nPageHeight- m_nHeaderHeight - m_nFooterHeight
								 - 8 * MARGIN)	/ m_nCardHeight;
	int nPrintableCardCount = LastViewableCard() + 1;
	if (GetCardCount() < nPrintableCardCount)
		nPrintableCardCount = GetCardCount();
	pInfo->SetMaxPage((nPrintableCardCount + m_nCardsPerPrintedPage - 1)
		/ m_nCardsPerPrintedPage);
	pInfo->m_nCurPage = 1;  // start previewing at page# 1
	//////////////////////////////////////////////////////
}

void CDeckView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	///////////////////////////////////////
	CScrollView::OnEndPrinting(pDC, pInfo);
}

void CDeckView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

BOOL CDeckView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CDeckView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	int nMaxPages			= pInfo->GetMaxPage();
	m_nCurrentPage			= pInfo->m_nCurPage;
	///
/*
	int yTopOfPage = (pInfo->m_nCurPage -1) * m_nLinesPerPrintedPage
		* m_nCardHeight;

	// Orient the viewport so that the Header to be printed
	// has a viewport coordinate of (0,0).
	pDC->SetViewportOrg(0, -yTopOfPage);
	/////////////////////////////////////////////////////////////////////
	CRect rectClip = CRect(0, yTopOfPage, m_nPageWidth,
		 yTopOfPage + m_nLinesPerPrintedPage * m_nCardHeight);
	pDC->IntersectClipRect(&rectClip);
*/
	///////////////////////////////////////////////////////// Display Header
	PrintPageHeader(pDC);
	///////////////////////////////////////////////////////// Display Cards
	/////////////////////////////////////////// Is Deck Empty
	CList<CString,CString>*	pDeckList	= GetDeckMgr()->GetDeckList();
	if(pDeckList->IsEmpty())
		return;
	/////////////////////////////////////////// Deck Not Empty
	int	Y = m_nHeaderBot; 
	POSITION pos;
	CString strCard;
	////////////////////////////////// Print Current Cards
	m_nCardCount	= pDeckList->GetCount();
	m_nCardIndexBeg = (m_nCurrentPage -1)* m_nCardsPerPrintedPage; 
	m_nCardIndexEnd = m_nCardIndexBeg + m_nCardsPerPrintedPage -1;
	if(m_nCardIndexEnd>=m_nCardCount)
		m_nCardIndexEnd = m_nCardCount - 1;
	///////////////////////////////////////////// Display
	for (int nIndex=m_nCardIndexBeg;nIndex<=m_nCardIndexEnd;nIndex++)
	{
		if(nIndex>=pDeckList->GetCount())
			break;
		///////////
		pos		= pDeckList->FindIndex(nIndex);
		strCard = pDeckList->GetNext( pos);
		////////
		Y += m_nCardHeight;
		////////////////
		pDC->TextOut(MARGIN,Y,strCard);
	}
	///////////////////////////////////////////////////////// Display Footer
	PrintPageFooter(pDC);
	/////////////////////////////// Get Old Back
	CFont Font;
	////////////////
	Font.CreateFontIndirect(&m_LF);
	pDC->SelectObject(&Font);
	m_Font.DeleteObject();
}

void CDeckView::OnSetFocus(CWnd* pOldWnd)
{ 
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////// 
	if(pWnd->GetActiveViewNumber() != VIEWDECK)
	{
		pWnd->SetActiveViewNumber(VIEWDECK);
		//////////////////////////
	}
	//////////////////////////// close IGenBox, CntlBox
	pWnd->GetDrawBox()->ShowWindow(SW_HIDE);
	pWnd->GetIGenBox()->ShowWindow(SW_HIDE);
	pWnd->GetIGenBox()->ShowWindow(SW_HIDE);
	pWnd->GetEDimBox()->ShowWindow(SW_HIDE);
	pWnd->GetCntlBox()->ShowWindow(SW_HIDE);
	pWnd->GetOperBox()->ShowWindow(SW_HIDE);
	pWnd->GetCntlStat()->ShowWindow(SW_HIDE);
	pWnd->GetIGenStat()->ShowWindow(SW_HIDE);
	pWnd->GetOperStat()->ShowWindow(SW_HIDE);
	pWnd->GetCurrStat()->ShowWindow(SW_HIDE);
	/////////////////////////////////
	CScrollView::OnSetFocus(pOldWnd);
}

void CDeckView::PrintPageHeader(CDC* pDC)
{
	char buf[133];
	//////////////
	int	Y = 0; 
	///////////////////////////////////////////////////////// Display
	CString Hdr;
//	0         1         2         3         4         5         6         7         8         9         0
//	012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
	////////
	Hdr =
   "-------------------------------------------------------------";
	Hdr +=
   "-------------------------------------------------------------";
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	Y += m_nCardHeight; // twips
	////////////////
	Hdr =
   "UnSTRESS: An IDRI Universal STructural Response Expert System   ";
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	Y += m_nCardHeight;
	////////////////
	Hdr =
   "Call: Dr. Debu Ray @ (510)654-1630 DATE:mm/dd/year.TIME:hr:mi:se"; 
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	Y += m_nCardHeight;
	////////////////
	Hdr =
   "----------------------------------------------------------------";
	Hdr +=
   "----------------------------------------------------------------";
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	Y += MARGIN;
	////////////////
	m_nHeaderBot = Y;
}

void CDeckView::PrintPageFooter(CDC* pDC)
{
	char buf[133];
	//////////////
	m_nFooterTop = m_nPageHeight - 3 * m_nCardHeight - 6 * MARGIN;
	/////////////////////////////////
	int	Y = m_nFooterTop; 
	///////////////////////////////////////////////////////// Display
	CString Hdr;
//	0         1         2         3         4         5         6         7         8         9         0
//	012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
	////////
	Hdr =
   "-------------------------------------------------------------";
	Hdr +=
   "-------------------------------------------------------------";
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	Y += m_nCardHeight;
	////////////////
	Hdr =
   "Page"; 
	wsprintf(buf,"%s\t%3.3d",(LPCSTR)Hdr,m_nCurrentPage);
	pDC->TextOut(0,Y,buf);
	Y += m_nCardHeight;
	////////////////
	Hdr =
   "-------------------------------------------------------------";
	Hdr +=
   "-------------------------------------------------------------";
	wsprintf(buf,"%s",(LPCSTR)Hdr);
	pDC->TextOut(0,Y,buf);
	////////////////
/*
    char temp[133];

    CPoint point(0, -14400); // 10" down
    CDrGrafDoc* pDoc = GetDocument();
    wsprintf(temp, "Mesh Report: %s",(LPCSTR) pDoc->GetTitle());
    pDC->TextOut(point.x, point.y, temp);
    wsprintf(temp, "Page %d", m_nCurrentPage);
    CSize size = pDC->GetTextExtent(temp, strlen(temp));
    point.x += 11520 - size.cx;
    pDC->TextOut(point.x, point.y, temp); // right-justified
*/
}
//////////////////////////// end of Module //////////////
