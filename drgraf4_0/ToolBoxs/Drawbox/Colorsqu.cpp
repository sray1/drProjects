// colorsqu.cpp : implementation file
//
#include "stdafx.h"
#include "afxext.h"      // for CBitMapButton
#include "DBoxrsrc.h"
#include "drawbox.h"
#include "colorsqu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSuperButton
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CSuperButton, CButton)

BOOL CSuperButton::Create(CWnd* pOwnerWnd, CString strWndName,CRect rect,UINT nChildID)
{
	ASSERT(pOwnerWnd != NULL);
    ////////////////////////////////////////////////////////////////
	return CreateEx(	0,
					 	"SuperButton",
					 	strWndName, 
					 	WS_CHILD |WS_VISIBLE|BS_PUSHBUTTON,// CHILD
						rect.left, 
						rect.top, 
						rect.Width(), 
						rect.Height(), 
						pOwnerWnd->GetSafeHwnd(),
						(HMENU)nChildID, 
						NULL
					);
}
/////////////////////////////////////////////////////////////////////////////
// CCustomColor

BEGIN_MESSAGE_MAP(CCustomColor, CWnd)
	//{{AFX_MSG_MAP(CCustomColor)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED (IDB_CUSTOMFORE, OnButtonClickForeColor)
	ON_BN_CLICKED (IDB_CUSTOMBACK, OnButtonClickBackColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CCustomColor, CWnd)
/////////////////////////////////////////////////////////////////////////////
CCustomColor::CCustomColor()
{
}

CCustomColor::~CCustomColor()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}

int CCustomColor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//////////////////////////////////////////////////////////// SuperButton
	// Button/modify for cursor  
	WNDCLASS wc;

	if (!::GetClassInfo(NULL, "button" , &wc) )
	{
		AfxMessageBox("Couldnot get classInfo: Button");
		return -1;
	} 

	wc.lpszClassName 	= "SuperButton";
	wc.hCursor 			= AfxGetApp()->LoadStandardCursor(IDC_UPARROW);
	wc.hInstance		= AfxGetApp()->m_hInstance;
	
	if (!::RegisterClass(&wc))
	{
		AfxMessageBox("Couldnot Register: SuperButton");
		return -1; 
	} 
	/////////////////////////		
	CRect rect;
	GetClientRect(&rect);
	int nbot = rect.bottom;
	//////////////////////////////////////////////////////////// fore
	rect.left 	+= 3;
	rect.right	-= 3;
	rect.top  	+= 2;
	rect.bottom  =  rect.top + 19;
	CString Name = "CustomFore";
		
	if(!m_btnCustomFore.Create(this, Name, rect, IDB_CUSTOMFORE)  )
		////////////////////////////
		return -1;
	//////////////////////////////////////////////////////////// Back
	rect.bottom = nbot - 2;
	rect.top    = rect.bottom - 19;
	Name 		= "CustomBack";

	if(!m_btnCustomBack.Create(this, Name, rect, IDB_CUSTOMBACK)  )
		////////////////////////////
		return -1;
	//////////////////////////////////////////////////////////////////		
	return 0;
}
afx_msg void CCustomColor::OnButtonClickForeColor()
{
	CColorDialog	ColorDlg;
	CDrawBox *pParentWnd=(CDrawBox*)GetParent(); 
	
	ColorDlg.m_cc.Flags |= CC_RGBINIT;
	ColorDlg.m_cc.rgbResult = pParentWnd->GetForeColor();

	if(ColorDlg.DoModal() ==IDOK)
	{
	
		pParentWnd->SetForeColor(ColorDlg.GetColor());
		
		pParentWnd->Invalidate();
		pParentWnd->UpdateWindow();
	
	}
		
}	

afx_msg void CCustomColor::OnButtonClickBackColor()
{

	CColorDialog	ColorDlg;
	CDrawBox *pParentWnd=(CDrawBox*)GetParent();
	
	ColorDlg.m_cc.Flags |= CC_RGBINIT;
	ColorDlg.m_cc.rgbResult = pParentWnd->GetBackColor();
	
	if(ColorDlg.DoModal() ==IDOK)
	{
	
		pParentWnd->SetBackColor(ColorDlg.GetColor());
		
		pParentWnd->Invalidate();
		pParentWnd->UpdateWindow();
	
	}
		
}	

void CCustomColor::OnPaint()
{
	CPaintDC dc(this); // device context for painting
    CRect	 Rect;
    	
	// TODO: Add your message handler code here
    GetClientRect(&Rect);    		
	dc.SelectStockObject(LTGRAY_BRUSH); // gray back/blac rectangle
	dc.Rectangle(&Rect);
	// Do not call CWnd::OnPaint() for painting messages
}

/////////////////////////////////////////////////////////////////////////////
// CColorSquare

BEGIN_MESSAGE_MAP(CColorSquare, CWnd)
	//{{AFX_MSG_MAP(CColorSquare)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CColorSquare, CWnd)
////////////////////////////////////////////////////////////////
#define MAX_COLOR 24
	static COLORREF ColorTable[MAX_COLOR]=
		{
			RGB(255,0,0),RGB(255,64,0),RGB(255,64,64),RGB(255,128,0),
			RGB(255,128,64),RGB(255,128,128),RGB(255,192,0),RGB(255,192,64),
			RGB(0,255,0),RGB(0,255,64),RGB(64,255,0),RGB(128,255,0),
			RGB(0,255,128),RGB(192,255,0),RGB(0,255,192),RGB(64,255,0),
			RGB(0,0,255),RGB(64,0,255),RGB(0,64,255),RGB(128,0,255),
			RGB(0,128,255),RGB(192,0,255),RGB(255,255,255),RGB(192,192,255)
		};
////////////////////////////////////////////////////////////////
CColorSquare::CColorSquare()
{
}

CColorSquare::~CColorSquare()
{
	if(m_hWnd != NULL)	
		DestroyWindow();	
}

void CColorSquare::SetColor(int index)
{

	m_crColor = ColorTable[index];
	
}
	 
void CColorSquare::OnPaint()
{
	CPaintDC dc(this); // device context for painting
    CBrush	 Brush;
    CBrush*	 PtrOldBrush;
    RECT	 Rect;
    	
	// TODO: Add your message handler code here
    GetClientRect(&Rect);    		
	Brush.CreateSolidBrush(m_crColor);
	PtrOldBrush= dc.SelectObject(&Brush);
	dc.Rectangle(&Rect);
	dc.SelectObject(PtrOldBrush);
    Brush.DeleteObject();
	
	// Do not call CWnd::OnPaint() for painting messages
}
/////////////////////////////////////////////////////////////////////////////
// CColorSquare message handlers


void CColorSquare::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();    
}

void CColorSquare::OnLButtonUp(UINT nFlags, CPoint point)
{

	CDrawBox *pParentWnd=(CDrawBox*)GetParent();
	
	pParentWnd->SetForeColor(m_crColor);
	ReleaseCapture();	
	
	pParentWnd->Invalidate();
	pParentWnd->UpdateWindow();
	
}

void CColorSquare::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();    
}

void CColorSquare::OnRButtonUp(UINT nFlags, CPoint point)
{

	CDrawBox *pParentWnd=(CDrawBox*)GetParent();
	
	pParentWnd->SetBackColor(m_crColor);
	ReleaseCapture();	
	
	pParentWnd->Invalidate();
	pParentWnd->UpdateWindow();
	
}
//////////////////////////// end of module //////////////////

