// viewinfo.cpp : implementation file
//

#include "stdafx.h"

#include "viewdll.h"
#include "DrAxis.h"
#include "AxisDraw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxisDraw ChildWindow

CAxisDraw::CAxisDraw()
{
}

BEGIN_MESSAGE_MAP(CAxisDraw, CWnd)
	//{{AFX_MSG_MAP(CAxisDraw)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionView_DLL;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAxisDraw message handlers

///////////////////////////////////////////////////////////
void CAxisDraw::OnPaint()
{
	CPaintDC dc(this); // device context for painting 
	///////////////////////////////////
	int nOldMapMode = dc.SetMapMode(MM_LOENGLISH);
	///////////////////////////////	
	DrawSampleAxes(&dc);
	////////////////////////   
	nOldMapMode = dc.SetMapMode(nOldMapMode);
	/////////////////////////////////////////////////
	// Do not call CDialog::OnPaint() for painting messages
}

void CAxisDraw::DrawSampleAxes(CDC* PtrDC)
{
	
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	CBrush  Brush;
   	CBrush* PtrOldBrush;
	
    /////////////////////////////////////////////////// 
    CRect	RectSample;
	GetClientRect(&RectSample);
	//////////////////////////////
	PtrDC->SetBkMode(TRANSPARENT);
//  Create inner border rectangle
/*
    RectSample.left   += 3;
    RectSample.top    += 3;
    RectSample.right  -= 3;
    RectSample.bottom -= 3;
*/    		
	
    Brush.CreateSolidBrush(RGB(0,0,0));
    PtrOldBrush= PtrDC->SelectObject(&Brush); 
    ////////////////////////////
    PtrDC->DPtoLP(&RectSample);
    PtrDC->Rectangle(&RectSample);
	///////////////////////////////////////////////////// Origin=LogCoord
	POINT Origin     = GetCenter(&RectSample);
//  PtrDC->LPtoDP(&RectSample); 
//	PtrDC->DPtoLP(&Origin);
    ///////////////////////////////////// Pen Width
    int nPenWidth = ::GetSystemMetrics(SM_CXBORDER);
	// Create Black Pen 3 Pixel wide;   
   	Pen.CreatePen (PS_SOLID,1,RGB(255,255,0));
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////// AxisLength	
	int nAxisLength  = (RectSample.right - RectSample.left)/3;  
   	//////////////////////////////////////
	CAxis Axis(nAxisLength);
	CAxis* pAxis = &Axis;
	pAxis->DrawAxes(PtrDC,Origin,(CView*)GetParent());
    ////////////////////////////
    PtrDC->SelectObject(PtrOldBrush);             
    Brush.DeleteObject(); 
	//////////////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject();
    ///////////////////
}

POINT CAxisDraw::GetCenter(CRect* Rect)
{
	POINT ptBeg;
	
	ptBeg.x = Rect->left + (Rect->right  - Rect->left)/2;
	ptBeg.y = Rect->top  + (Rect->bottom - Rect->top) /2;
	
	return ptBeg;
}	 
//////////////////////////// end of module ////////////
