// Drawbox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "drgraf.h"
#include "UserMsg.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h" 
#include "ObjMgr.h"
///////////////////// Spec
#include "Def_Spec.h"
#include "drfont.h"
/////////////////////
#include "DBoxButt.h" 
#include "DBoxrsrc.h" 

#include "Ext_DBox.h"
#include "drawbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDrawBox, CWnd)
	//{{AFX_MSG_MAP(CDrawBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CDrawBox,CWnd)
///////////////////////////////////////////////////
//array ofIDs Used to Initialize Drawbar

static UINT BASED_CODE drawbox[] =
{
	// same order as in the bitmap 'drawbox.bmp'
	IDB_LABEL,
	IDB_FREEHAND,
	IDB_RECT_FILL,
	IDB_RECT,
	IDB_RRECT_FILL,
	IDB_RRECT,
	IDB_CIRCLE_FILL,
	IDB_CIRCLE,
	IDB_LINE,
	//////////////
	IDB_GRID,
	IDB_ZOOM,
	IDB_DIMENSION,
	IDB_FONT,
	IDB_BRUSH,
	/////////////
	IDB_EDIT,
	IDB_MOVE
	
};
/////////////////////////////////////////////////////////////////////////////
// CDrawBox
CDrawBox::CDrawBox()
{ 
	m_nDrawBarColMax 	= DB_MAX_BUTT_COL;	  // DrawBar Column 
	m_nDrawBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveDrawObject	= -1;             // None Selected                               //temorary
    ////////////////////////////////
	m_nColorSquareColMax= DB_MAX_SQ_COL;
    m_nColorSquareRowMax= DB_MAX_SQ_ROW;
    m_nSquareTop		= 0;
    m_crForeColor		= RGB(255,0,0);   // red
    m_crBackColor       = RGB(0,255,0);   // green
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    


CDrawBox::~CDrawBox()
{
	if(m_hWnd != NULL)	
		DestroyWindow();
}

//BOOL CDrawBox::Create(CMDIFrameWnd* pParentWnd,CRect rect)
BOOL CDrawBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWnd,
						NULL,
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_DRAWBOX*/,
						NULL
					);
	return bOk;				
}

UINT CDrawBox::GetHeight()
{
	return m_nHeight;
}

UINT CDrawBox::GetWidth()
{
	return m_nWidth;
}

int CDrawBox::GetActiveTool()
{
	return m_nActiveTool;
}

int CDrawBox::GetActiveDrawObject()
{
	return m_nActiveDrawObject;
} 

COLORREF CDrawBox::GetForeColor()
{
	return m_crForeColor;
}
COLORREF CDrawBox::GetBackColor()
{
	return m_crBackColor;
}

void CDrawBox::FillToolNumArray()
{

	for (int i = 0; i<nMax_DBoxTypes; i++)
		m_nToolNumArray[i] =  DbTypes[i].num;

}

int CDrawBox::GetToolNum(int index)
{

	if (index>(int)m_nDrawBarButtCount)
	{
		AfxMessageBox("CDrawBox::GetToolNum index Overflow");
    	return -2;
    }
    else	
		return m_nToolNumArray[index];
		
}		 	
	
BOOL CDrawBox::IsDrawTool(UINT nID)
{
  
//	type;  		// 0 	= edit & move tool(for button management)
				// 1	= object that can be edited & moved
				// 2	= independent tool other than move/edit
				// 3	= 3dObject
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if((int)nID == DbTypes[i].num)
		{
			if(DbTypes[i].type == 2) 
				return TRUE;
		}
	}	
	return FALSE;
}	  

BOOL CDrawBox::IsEditMoveTool(UINT nID)
{
  
//	type;  		// 0 	= edit & move tool(for button management)
				// 1	= object that can be edited & moved
				// 2	= independent tool other than move/edit
				// 3	= 3dObject
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if((int)nID == DbTypes[i].num)
		{
			if(DbTypes[i].type == 0) 
				return TRUE;
		}
	}	
	return FALSE;
}	  

BOOL CDrawBox::IsDrawObject(UINT nID)
{
  
//	type;  		// 0 	= edit & move tool(for button management)
				// 1	= object that can be edited & moved
				// 2	= independent tool other than move/edit
				// 3	= 3dObject
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if((int)nID == DbTypes[i].num)
		{
			if(DbTypes[i].type == 1||DbTypes[i].type == 3) 
				return TRUE;
		}
	}	
	return FALSE;
}	  
/////////////////////////////////////////////////////////////////////////////
// CDrawBox message handlers
int CDrawBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// DrawBar creation
	if (!CreateDrawBar())
	{	
		AfxMessageBox("Cannot Create DrawBar");
		return -1;
    }
	
	m_wndDrawBar.ShowWindow((m_wndDrawBar.GetStyle() & WS_VISIBLE) == 0);
    ////////////////////////////////////////////////// Color/CustomSquares Creation
	if (!CreateColorSquares())
	{	
		AfxMessageBox("Cannot Create ColorSquare");
		return -1;
    }
    ////////////////////////////////////////////////// PopUp Zoom Window/No Show
/*
	if (!CreateZoomScreen())
	{	
		AfxMessageBox("Cannot Create ZoomScreen");
		return -1;
    }
*/ 
    /////////////////////////////////////////////////// set Height/Width
   	UINT width  = 6 + m_nDrawBarColMax*DB_BNSIZE_CX + 6;
   	SetWidth(width);
   	/////////////////
   	UINT height = DB_COLOR_BNSIZE;                  // caption etc.
   	height +=    m_nDrawBarRowMax*DB_BNSIZE_CY + 8 +
   					 DB_MAX_SQ_ROW*DB_COLOR_BNSIZE;//colrSqrs
   	height += 2 * DB_COLOR_BNSIZE;             // fore/back button
   	height += 5 * DB_COLOR_BNSIZE;             // display plank                     
	SetHeight(height);
	/////////////////    
	return 0;
}
//////////////////////////////////////////////////////////////////////

BOOL CDrawBox::CreateDrawBar()
{
	// Create the Palette.  We are using hardcoded numbers for ease here
	// normally the location would be read in from an ini file.
	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left + 6;
	nTop  = Rect.top  + 4;
	/////////////////////////////////////////////////////////
	m_nDrawBarButtCount = sizeof(drawbox)/sizeof(UINT); 
	if(m_nDrawBarButtCount != DB_BUTT_COUNT)
	{
		AfxMessageBox("Button Count Discrepancy");
		return FALSE;
	}
///////////////////////////////////////////////////////////////////////////////////			
	//////////////////////////////////////////////////////////////////////
	CString strRes;
//////////////////////////////////////////////////////////////////////////
/*#ifdef _AFXDLL

	TRACE("In Drawbox.Create\n");

	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	//////////////////////
	HINSTANCE hInstApp = AfxGetInstanceHandle(); // uses client's instance handle
	HINSTANCE hOldInst = AfxGetResourceHandle(); 
	///////////////
	AfxSetResourceHandle(hInstApp); // uses client's instance handle 
	strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	//////////////
	AfxSetResourceHandle(hOldInst); // resource handle back 
    ////////////// 
#endif*/	

#ifdef _AFXDLL
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionDBox_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////	
	if (!m_wndDrawBar.Create(this, nLeft, nTop,IDW_DRAWBAR,IDC_BUTTON) ||
		!m_wndDrawBar.LoadBitmap(IDB_DBOX) ||
		!m_wndDrawBar.SetButtons(drawbox,sizeof(drawbox)/sizeof(UINT),m_nDrawBarColMax) )
	{
		TRACE("Failed to create toolbar\n");
		return FALSE;       // fail to create
	}
	
#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#endif

	//////////////////////////////////////////////// set Row Count
	m_nDrawBarRowMax = m_nDrawBarButtCount/m_nDrawBarColMax;
	if(m_nDrawBarButtCount%m_nDrawBarColMax) m_nDrawBarRowMax++;
	///////////////////////////////////////// set sizes / NO CAPTION
	CSize szButton,szImage;
	///////////////////////
	szButton.cx  = DB_BNSIZE_CX;
	szButton.cy  = DB_BNSIZE_CY; 
		
	szImage.cx   = DB_IMAGE_CX;
	szImage.cy   = DB_IMAGE_CY;
	///////////////////////
	m_wndDrawBar.SetSizes(szButton,szImage,FALSE);
	///////////////////////////////////////////
	return TRUE;
}

BOOL CDrawBox::CreateColorSquares()
{                   

	CRect Rect;
	UINT	i,j,k;
	/////////////////////////////////////////////////
	m_nSquareTop  = m_nDrawBarRowMax*DB_BNSIZE_CY + 8;
	/////////////////////////////////////////////////
	SetSqTop(m_nSquareTop);
	////////////////////////                                   
    Rect.top = GetSqTop();
    //////////////////////////////////////////////// 
	// Register a custom WndClass and create  windows.
	// This must be done because ColorSquares have  custom cursor, and
	//  no icon.
	CString strDrawBoxClassName =
		AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
			LoadCursor(NULL, IDC_UPARROW),
			(HBRUSH)(COLOR_WINDOW+1),NULL);
    ///////////////////////////
    for (i=0;i<DB_MAX_SQ_ROW;i++)    // Child Squares Positioning
   	{
   		for (j=0;j<DB_MAX_SQ_COL;j++)
   		{
   			k=((DB_MAX_SQ_COL)*i)+j;
   			Rect.left    = j*DB_COLOR_BNSIZE + 6;
   			Rect.right   = Rect.left + DB_COLOR_BNSIZE -1;
   			Rect.bottom  = Rect.top  + DB_COLOR_BNSIZE -1;  
			/////////////////////////////////////////////					
   			if(!m_wndColorSquare[i][j].Create (strDrawBoxClassName,
   												NULL,
      											WS_CHILD | WS_VISIBLE,
      											Rect,
      											this,
      											(k+1)) )
      			return FALSE;
			///////////////////////
			int index = j + i*GetColorSquareRowMax();      					
      		m_wndColorSquare[i][j].SetColor(index);			
        }                                                     
    	Rect.top    += DB_COLOR_BNSIZE;
	}                                               
	//////////////////////////////////////////////// Custom Color Window(2*BNSIZE=height)
	int nHeight = 2*DB_COLOR_BNSIZE;
	int nWidth  = DB_MAX_SQ_COL*DB_COLOR_BNSIZE;
	////////////////////////////////					
	Rect.left    = 6;
   	Rect.right   = Rect.left + nWidth -1;
	Rect.bottom  = Rect.top  + nHeight -1;  
	if(!m_wndCustomColor.Create (
									strDrawBoxClassName,
   									NULL,
      								WS_CHILD |WS_VISIBLE,
      								Rect,
      								this,
      								IDW_CUSTOMCOLOR
      							)   							 )
      	return FALSE;
    /////////////////  	
	return TRUE;
	
}
	     					
BOOL CDrawBox::CreateZoomScreen()
{
 
 	CRect rect = (0,0,0,0);
	BOOL bOk = CreateEx(	0,
						"AfxWnd",
						"Zoom",
						WS_POPUP |WS_CAPTION |WS_VSCROLL,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						this->GetSafeHwnd(),
						(HMENU)NULL,
						NULL
					);
	return bOk;				
}
void CDrawBox::OnPaint()
{

   CPaintDC dc(this); // device context for painting
	
   RECT    Rect;
   CPen    Pen;
   CBrush  Brush;
   CBrush* PtrOldBrush;
	
// color background LightGray

   GetClientRect(&Rect);
   dc.FillRect(&Rect,Brush.FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)) );


// Create inner border rectangle

   	Rect.left   += 3;
   	Rect.top    += 3;
   	Rect.right  -= 3;
   	Rect.bottom -= 3;		

   	PtrOldBrush= (CBrush*)dc.SelectStockObject(NULL_BRUSH); 
  	dc.Rectangle(&Rect);
   	dc.SelectObject(PtrOldBrush);
   	Brush.DeleteObject();
	/////////////////////////////		
   	int nSquareTop = m_nSquareTop;  
   	SetSqTop(nSquareTop);                                       
   
// 	BottomMost Rectangle + 2 for Custom Rectangle
   	SetSqTop(nSquareTop + (DB_MAX_SQ_ROW+2)*DB_COLOR_BNSIZE);

   	Draw_Bottom_Box();		
// 	CREATE 2 RECT FOR FORE/BACK

   	Draw_Fore_Back_Rect();

	// Do not call C???::OnPaint() for painting messages 
}


void CDrawBox::Draw_Bottom_Box()
{
   CClientDC dc(this); // device context for painting
	
   RECT    Rect;
   CPen    Pen;
   CPen*   PtrOldPen;


// BottomMost Rectangle
   GetClientRect(&Rect); 
   
   Rect.top    = GetSqTop() + 4;
   Rect.left   += 9;
   Rect.right  -= 9;
   Rect.bottom -= 9;
    	
    
   dc.MoveTo(Rect.left,Rect.top);

// Create Gray Pen   
   Pen.CreatePen (PS_SOLID,1,0x808080);
   PtrOldPen=dc.SelectObject(&Pen); 
   dc.LineTo(Rect.right,Rect.top);
   dc.SelectObject(PtrOldPen);   
   Pen.DeleteObject();

// Create White Pen
   Pen.CreatePen (PS_SOLID,1,0xffffff);
   PtrOldPen=dc.SelectObject(&Pen); 
   dc.LineTo(Rect.right,Rect.bottom);
   dc.LineTo(Rect.left,Rect.bottom);
   dc.SelectObject(PtrOldPen);   
   Pen.DeleteObject();

// Create Gray Pen
   Pen.CreatePen (PS_SOLID,1,0x808080);
   PtrOldPen=dc.SelectObject(&Pen); 
   dc.LineTo(Rect.left,Rect.top);
   dc.SelectObject(PtrOldPen);
   Pen.DeleteObject();
   
   return;
} 

void CDrawBox::Draw_Fore_Back_Rect()
{

   CClientDC dc(this); // device context for painting
	
   RECT    Rect;
   CBrush  Brush;
   CBrush* PtrOldBrush;
// CREATE 2 RECT FOR FORE/BACK
       
   GetClientRect(&Rect);		
   Rect.top = GetSqTop() + DB_COLOR_BNSIZE;
   //////////////////////////////////////////////////////////////////////////
   Rect.left   = (Rect.right-Rect.left)/2 - DB_COLOR_BNSIZE/2 -5;    // BACKGROUND
   Rect.top    += DB_COLOR_BNSIZE/2 -5;
   Rect.right  =  Rect.left + DB_COLOR_BNSIZE ;
   Rect.bottom =  Rect.top  + DB_COLOR_BNSIZE ;
   		
     
   Brush.CreateSolidBrush(GetBackColor());
   PtrOldBrush= dc.SelectObject(&Brush);
   dc.Rectangle(&Rect);
   dc.SelectObject(PtrOldBrush);             
   Brush.DeleteObject();
   /////////////////////////////////////////////////////////////////////////
   Rect.left   += 5;                                            //FOREGROUND
   Rect.top    += 5;
   Rect.right  = Rect.left + DB_COLOR_BNSIZE ;
   Rect.bottom = Rect.top  + DB_COLOR_BNSIZE ;
   		
   
   Brush.CreateSolidBrush(GetForeColor());
   PtrOldBrush= dc.SelectObject(&Brush);
   dc.Rectangle(&Rect);
   dc.SelectObject(PtrOldBrush); 
   Brush.DeleteObject();
   /////////////////////////
   return;   
}
/////////////////////////////////////////////////////////////////////////////
// CDrawBar message handlers

int CDrawBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CDrawBox::GoRespondtoMouse()
{

	///////////////////////////////////////
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetIGenBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(TRUE);
	///////////////////////////////////////////////////// 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrFont* pDrFont		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
	/////////////////////////////////////////////////////////
	int nID = GetActiveDrawObject(); 
	if(nID<0) return;
	////////////////////////////////////////// get index
/*
	CString str;
	for (int i = 0; i<nMax_DBoxTypes; i++)
	{
		if(nID == DbTypes[i].num)
		{
			str = DbTypes[i].ObjName;
			/////////////////////////
			if((nID = GetActiveTool())>=0)
			{
				for (int j = 0; j<nMax_DBoxTypes; j++)
				{
					if(nID == DbTypes[j].num)
					str += DbTypes[j].ObjName;
				}	 
            }
			AfxMessageBox(str);
		}
	}	
*/
	////////////////////////////////////////////
	if(nID == DRFONT)
	{
		pDrFont->DoTextFont();
		//////////////////////
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		pWnd->SetActiveObjectType(GetActiveDrawObject());
		pWnd->SetActiveToolType(GetActiveTool());
		pWnd->SetActiveForeColor(GetForeColor());
		pWnd->SetActiveBackColor(GetBackColor());
	}	
				
}


