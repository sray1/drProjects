// Elembox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
/////////////////////
#include "palette.h"
#include "IGenButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"	// DLL specific
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Supp.h"   // Operations
#include "Def_StaL.h"   // Operations
#include "Def_SpeL.h"   // Operations
#include "Def_DynL.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "IGenbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CIGenBox, CBoxWnd)
	//{{AFX_MSG_MAP(CIGenBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CIGenBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_NODE,
	IDB_CURVE,
	IDB_PATCH,
	IDB_SOLID,
	IDB_OBJ3D

	
}; 

/////////////////////////////////////////////////////////////////////////////
// CIGenBox
CIGenBox::CIGenBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CIGenBox::~CIGenBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CIGenBox message handlers
int CIGenBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CIGenBox::OnCreate\nCannot Create ElemBar");
		return -1;
    }
	
	m_wndElemBar.ShowWindow((m_wndElemBar.GetStyle() & WS_VISIBLE) == 0);
    /////////////////////////////////////////////////// set Height/Width
//   	UINT width  = 5 + 1 + m_nElemBarColMax*EB_BNSIZE_CX + 3 + 1;
   	UINT width  = m_nElemBarColMax*EB_BNSIZE_CX;
   	////////////////
   	SetWidth(width);
   	/////////////////
//+   	UINT height = 2*EB_CAP_ETC_SIZE + 10;                  // caption etc.
//   	UINT height = 10;                  // border etc.
//   	height +=    m_nElemBarRowMax*EB_BNSIZE_CY;//
   	UINT height = m_nElemBarRowMax*EB_BNSIZE_CY;//
	///////////////////
	SetHeight(height);
	//////////////////////////////////////////////////////////////////    
	////////////////////////////////////////////////// Secondary Boxes
	CRect BoxRect;
	BoxRect.left = BoxRect.top = BoxRect.right = BoxRect.bottom = 0;
	/////////////////////////////////////////// NodeBox
	GetNodeBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// CurveBox
	GetCurveBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// PatchBox
	GetPatchBox()->Create((CWnd*)this,BoxRect);
	/////////////////////////////////////////// SolidBox
	GetSolidBox()->Create((CWnd*)this,BoxRect);
	/////////////////    
	return 0;
}

void CIGenBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// NodeBox
	if(GetNodeBox()->m_hWnd != NULL)
		GetNodeBox()->DestroyWindow();
	/////////////////////////////////////////// CurveBox
	if(GetCurveBox()->m_hWnd != NULL)
		GetCurveBox()->DestroyWindow();
	/////////////////////////////////////////// PatchBox
	if(GetPatchBox()->m_hWnd != NULL)
		GetPatchBox()->DestroyWindow();
	/////////////////////////////////////////// SolidBox
	if(GetSolidBox()->m_hWnd != NULL)
		GetSolidBox()->DestroyWindow();
	/////////////////////////////////////////// Bar
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CIGenBox::CreateElemBar()
{

	
	int     nLeft, nTop;     
	RECT	Rect;
	
	GetClientRect(&Rect);
	
	nLeft = Rect.left;       // ElemBar Left,Top
	nTop  = Rect.top;
	////////////////////////////////////////////////////////////////////
	m_nElemBarButtCount = sizeof(elembox)/sizeof(UINT); //EB_BUTT_COUNT 
	if(m_nElemBarButtCount != EB_BUTT_COUNT)
	{
		AfxMessageBox("ERROR:CIGenBox::CreateElemBar()\nButton Count Discrepancy");
		return FALSE;
	}
	////////////////////////////////////////////////////////////////////// 
	CString strRes;
//////////////////////////////////////////////////////////////////////////
/*
#ifdef _AFXDLL

	TRACE("In Elembox.Create\n");

	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
	//////////////////////
	HINSTANCE hInstApp = AfxGetInstanceHandle(); // uses client's instance handle
	HINSTANCE hOldInst = AfxGetResourceHandle(); 
	///////////////
	AfxSetResourceHandle(hInstApp); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	//////////////
	AfxSetResourceHandle(hOldInst); // resource handle back 
    //////////////
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEBox_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#endif	
*/
#ifdef _AFXDLL
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionIGen_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_IGENBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_IGENBOX) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CIGenBox::CreateElemBar()\nFailed to create toolbar\n");
		return FALSE;       // fail to create
	} 

#ifdef _AFXDLL
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
#endif

	//////////////////////////////////////////////// set Row Count
	m_nElemBarRowMax = m_nElemBarButtCount/m_nElemBarColMax;
	if(m_nElemBarButtCount%m_nElemBarColMax) m_nElemBarRowMax++;
	///////////////////////////////////////// set sizes / NO CAPTION
	CSize szButton,szImage;
	///////////////////////
	szButton.cx  = EB_BNSIZE_CX;
	szButton.cy  = EB_BNSIZE_CY; 
		
	szImage.cx   = EB_IMAGE_CX;
	szImage.cy   = EB_IMAGE_CY;
	///////////////////////
	m_wndElemBar.SetSizes(szButton,szImage,FALSE);
	///////////////////////////////////////////
	return TRUE;
}

void CIGenBox::OnPaint()
{

	///////////////
//?	return;      // do nothing
	///////////////

   CPaintDC dc(this); // device context for painting
	
   RECT    Rect;
   CPen    Pen;
   CBrush  Brush;
//   CBrush* PtrOldBrush;
	
// color background LightGray

   GetClientRect(&Rect);
   dc.FillRect(&Rect,Brush.FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)) );

/*
// Create inner border rectangle

   	Rect.left   += 2;
   	Rect.top    += 2;
   	Rect.right  -= 2;
   	Rect.bottom -= 2;		

   	PtrOldBrush= (CBrush*)dc.SelectStockObject(NULL_BRUSH); 
  	dc.Rectangle(&Rect);
   	dc.SelectObject(PtrOldBrush); 
*/   	
   	Brush.DeleteObject();
	/////////////////////////////
			
}

/////////////////////////////////////////////////////////////////////////////
// CElemBar message handlers

int CIGenBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CIGenBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	CString str;
	/////
	if(pWnd->GetCurrentOperID() == GOP_POST)
	{
		str = "UNKNOWN";
		pWnd->SetstrCntlID(str);
		pWnd->SetCurrentCntlID(UNONE);
		pWnd->SetActiveToolType((int)UNONE);
		strCur = "Ready for ";
		pWnd->SetstrCurrID(strCur);
	}
	///////////////////////////////////////
	pWnd->SetIGenBoxStatus(TRUE);
	pWnd->SetCntlBoxStatus(FALSE);
	pWnd->SetDrawBoxStatus(FALSE);
	////////////////////////////////////////////////// Check If SecondaryBoxes
	CClientDC dc(this);
	int ScreenWidth = dc.GetDeviceCaps(HORZRES);
	int ScreenHeight = dc.GetDeviceCaps(VERTRES);
	CRect BoxRect,ItemRect;;
	int BoxWidth,BoxHeight,index;
	////////////////////////////////////////////
	int nID 	= GetActiveElemObject(); 
	if(nID<0) return;
	//////////////////////////////
	UINT mID	= (UINT)nID;
	////////////////////////////////////////// Hide CntlBox by toggle
//	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	////////////////////
//052997	pWnd->SetCurrentIGenID(mID);
	/////////////
	switch(mID)
	{
		case NODE:

			pWnd->SetMouseBoxType(NODEBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetNodeBox()->GetWidth();
			BoxHeight 	= (int)GetNodeBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			if(pWnd->GetCurrentOperID() == GOP_POST)
			{
				pWnd->ReSetEDimOpen(TRUE,0);	// 0D->Open	
				pWnd->ReSetEDimOpen(FALSE,1);	// 1D->Close	
				pWnd->ReSetEDimOpen(FALSE,2);	// 2D->Close	
				pWnd->ReSetEDimOpen(FALSE,3);	// 3D->Close	
			}
			///////////
			if(pWnd->IsIGenOpen(0))
			{
				///////////////////////////////
				GetNodeBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
			{
				str = "NODE";
				pWnd->SetstrIGenID(str);
				////
				if(pWnd->GetCurrentOperID() == GOP_POST)
					strCur += str; 
				//////
				break;
			}			

		case CURVE:

			pWnd->SetMouseBoxType(CURVEBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetCurveBox()->GetWidth();
			BoxHeight 	= (int)GetCurveBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			if(pWnd->GetCurrentOperID() == GOP_POST)
			{
				pWnd->ReSetEDimOpen(TRUE,0);	// 0D->Open	
				pWnd->ReSetEDimOpen(TRUE,1);	// 1D->Open	
				pWnd->ReSetEDimOpen(FALSE,2);	// 2D->Close	
				pWnd->ReSetEDimOpen(FALSE,3);	// 3D->Close	
			}
			///////////
			if(pWnd->IsIGenOpen(1))	// CURVE
			{
				///////////////////////////////
				GetCurveBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
			{
				str = "CURVE";
				pWnd->SetstrIGenID(str);
				////
				if(pWnd->GetCurrentOperID() == GOP_POST)
					strCur += str; 
				//////
				break;
			}			
			
		case PATCH:

			pWnd->SetMouseBoxType(PATCHBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetPatchBox()->GetWidth();
			BoxHeight 	= (int)GetPatchBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			////////////
			if(pWnd->GetCurrentOperID() == GOP_POST)
			{
				pWnd->ReSetEDimOpen(TRUE,0);	// 0D->Open	
				pWnd->ReSetEDimOpen(TRUE,1);	// 1D->Open	
				pWnd->ReSetEDimOpen(TRUE,2);	// 2D->Open	
				pWnd->ReSetEDimOpen(FALSE,3);	// 3D->Close	
			}
			///////////
			if(pWnd->IsIGenOpen(2))	// PATCH
			{
				///////////////////////////////
				GetPatchBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
			{
				str = "PATCH";
				pWnd->SetstrIGenID(str);
				////
				if(pWnd->GetCurrentOperID() == GOP_POST)
					strCur += str; 
				//////
				break;
			}			
			
		case SOLID:

			pWnd->SetMouseBoxType(SOLIDBOX);
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetSolidBox()->GetWidth();
			BoxHeight 	= (int)GetSolidBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			////////////
			if(pWnd->GetCurrentOperID() == GOP_POST)
			{
				pWnd->ReSetEDimOpen(TRUE,0);	// 0D->Open	
				pWnd->ReSetEDimOpen(TRUE,1);	// 1D->Open	
				pWnd->ReSetEDimOpen(TRUE,2);	// 2D->Open	
				pWnd->ReSetEDimOpen(TRUE,3);	// 3D->Open	
			}
			///////////
			if(pWnd->IsIGenOpen(3))	// SOLID
			{
				///////////////////////////////
				GetSolidBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
			{
				str = "SOLID";
				pWnd->SetstrIGenID(str);
				////
				if(pWnd->GetCurrentOperID() == GOP_POST)
					strCur += str; 
				//////
				break;
			}			
			
		case OBJ3D:

			pWnd->SetMouseBoxType(OBJ3DBOX);
/*
			///////////////////////////////////////////// Box 
			BoxWidth  	= (int)GetSolidBox()->GetWidth();
			BoxHeight 	= (int)GetSolidBox()->GetHeight();
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			////////////
			if(pWnd->GetCurrentOperID() == GOP_POST)
			{
				pWnd->ReSetEDimOpen(TRUE,0);	// 0D->Open	
				pWnd->ReSetEDimOpen(TRUE,1);	// 1D->Open	
				pWnd->ReSetEDimOpen(TRUE,2);	// 2D->Open	
				pWnd->ReSetEDimOpen(TRUE,3);	// 3D->Open	
			}
			///////////
			if(pWnd->IsIGenOpen(3))	// SOLID
			{
				///////////////////////////////
				GetSolidBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				//////////////////////////////////////////////////////////////            
				return;
			}
			else
			{
*/
				str = "OBJ3D";
				pWnd->SetstrIGenID(str);
				////
/*
				if(pWnd->GetCurrentOperID() == GOP_POST)
					strCur += str; 
*/
				//////
				break;
/*
			}			
*/			
			
		default:

			////////////////////////////////////////// Hide by toggle
			ShowWindow((GetStyle() & WS_VISIBLE) == 0);
			/////////////
			pWnd->SetMouseBoxType(IGENBOX);
			//////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			if((GetCurveBox()->GetStyle()) & WS_VISIBLE)
				GetCurveBox()->ShowWindow(SW_HIDE);
			if((GetPatchBox()->GetStyle()) & WS_VISIBLE)
				GetPatchBox()->ShowWindow(SW_HIDE);
			if((GetSolidBox()->GetStyle()) & WS_VISIBLE)
				GetSolidBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			str = "DON'T KNOW";
			pWnd->SetstrIGenID(str);
			strCur = "UNKNOWN Control Option";
			pWnd->SetstrCurrID(strCur);
			return;
			///////		
			
	}
	///////////////////////////////////// Reset TaskID
	if(pWnd->GetCurrentOperID() == GOP_POST)
		pWnd->SetCurrentIGenID_Alternate(GetActiveElemObject());
	else
		pWnd->SetCurrentIGenID(GetActiveElemObject());
	///
	m_WPARAM = IDW_IGENBOX;
//	ReSetDataDialogs();
	////////////////
	if(pWnd->GetCurrentOperID() == GOP_POST)
	{
		strCur += "@Left CLICK on Object in CONTROL Box";
		pWnd->GetCntlBox()->ShowWindow(TRUE);	// Open MGenBox
		pWnd->GetCntlBox()->SetFocus();
		pWnd->SetstrCurrID(strCur);
	}
	////////////////////////////////////////// Hide IGenBox by toggle
	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
	///////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////