// Elembox.cpp : implementation file
//
#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++1.5)
#include "OldGlob.h"
#include "OldTool.h"
/////////////////////
#include "drgraf.h"
#include "UserMsg.h"
#include "drgrafrm.h"
/////////////////////
#include "palette.h"
#include "CntlButt.h"
#include "BoxWndID.h"
#include "BoxBMPID.h"
#include "IGenRsrc.h"	// DLL specific
#include "SuppRsrc.h"	// DLL specific
#include "StaLRsrc.h"	// DLL specific
#include "SpeLRsrc.h"	// DLL specific
#include "DynLRsrc.h"	// DLL specific
/////////////////////
#include "Def_IGen.h"   // Operations
#include "Def_Elem.h"   // Operations
#include "Def_Supp.h"   // Operations
#include "Def_StaL.h"   // Operations
#include "Def_SpeL.h"   // Operations
#include "Def_DynL.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"

#include "CntlBox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCntlBox, CBoxWnd)
	//{{AFX_MSG_MAP(CCntlBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CCntlBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_ELEMENT,
	IDB_SUPPORT,
	IDB_STATICLOAD,
	IDB_DYNAMICLOAD,
	IDB_SPECTRALOAD
}; 

/////////////////////////////////////////////////////////////////////////////
// CCntlBox
CCntlBox::CCntlBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CCntlBox::~CCntlBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CCntlBox message handlers
int CCntlBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CCntlBox::OnCreate\nCannot Create ElemBar");
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
	////////////////////////////////////////////////// Secondary Boxes
	CRect BoxRect;
	BoxRect.left = BoxRect.top = BoxRect.right = BoxRect.bottom = 0;
	/////////////////////////////////////////// SuppBox
//	GetEDimBox()->Create((CWnd*)this,BoxRect,IDW_CNTLBOX);
	/////////////////////////////////////////// SuppBox
	GetSuppBox()->Create((CWnd*)this,BoxRect,IDW_CNTLBOX);
	/////////////////////////////////////////// StaLBox
	GetStaLBox()->Create((CWnd*)this,BoxRect,IDW_CNTLBOX);
	/////////////////////////////////////////// StaLBox
	GetDynLBox()->Create((CWnd*)this,BoxRect,IDW_CNTLBOX);
	/////////////////////////////////////////// StaLBox
	GetSpeLBox()->Create((CWnd*)this,BoxRect,IDW_CNTLBOX);
	/////////////////    
	return 0;
}

void CCntlBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// EDimBox
//	if(GetEDimBox()->m_hWnd != NULL)
//		GetEDimBox()->DestroyWindow();
	/////////////////////////////////////////// SuppBox
	if(GetSuppBox()->m_hWnd != NULL)
		GetSuppBox()->DestroyWindow();
	/////////////////////////////////////////// SpeLBox
	if(GetSpeLBox()->m_hWnd != NULL)
		GetSpeLBox()->DestroyWindow();
	/////////////////////////////////////////// DynLBox
	if(GetDynLBox()->m_hWnd != NULL)
		GetDynLBox()->DestroyWindow();
	/////////////////////////////////////////// StaLBox
	if(GetStaLBox()->m_hWnd != NULL)
		GetStaLBox()->DestroyWindow();
	/////////////////////////////////////////// Bar
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CCntlBox::CreateElemBar()
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
		AfxMessageBox("ERROR:CCntlBox::CreateElemBar()\nButton Count Discrepancy");
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
	TRACE("CntlBox string = %s\n", (const char*) strRes); 
#endif
/////////////////////////////////////////////////////////////////
	////////////////////////////////////////////			
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_CNTLBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_CNTLBOX) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CCntlBox::CreateElemBar()\nFailed to create toolbar\n");
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

void CCntlBox::OnPaint()
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

int CCntlBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CCntlBox::GoRespondtoMouse()
{
	
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////
	CString strCur;
	CString str;
	//////////////////////////////////////////////////////////////
	if(pWnd->GetCurrentOperID() != GOP_POST)
	{
		str = "UNKNOWN";
		pWnd->SetstrIGenID(str);
		pWnd->SetCurrentIGenID(UNONE);
		pWnd->SetActiveToolType((int)UNONE);
		strCur = "Ready for ";
		pWnd->SetstrCurrID(strCur);
	}
	///////////////////////////////////////
	pWnd->SetCntlBoxStatus(TRUE);
	pWnd->SetIGenBoxStatus(FALSE);
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
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	////////////////////////////
	pWnd->SetCurrentCntlID(mID);
	////////////////////////////////////////// Hide CntlBox by toggle
//	ShowWindow((GetStyle() & WS_VISIBLE) == 0);
	////////////////////
	///////////
	switch(mID)
	{
		case ELEMENT:

			pWnd->SetMouseBoxType(ELEMDIMBOX);
			////////////////////////////////////////// Hide CntlBox by toggle
			ShowWindow((GetStyle() & WS_VISIBLE) == 0);
			//////////////////////////////////////////////////////////////
			if((GetSuppBox()->GetStyle()) & WS_VISIBLE)
				GetSuppBox()->ShowWindow(SW_HIDE);
			if((GetStaLBox()->GetStyle()) & WS_VISIBLE)
				GetStaLBox()->ShowWindow(SW_HIDE);
			if((GetDynLBox()->GetStyle()) & WS_VISIBLE)
				GetDynLBox()->ShowWindow(SW_HIDE);
			if((GetSpeLBox()->GetStyle()) & WS_VISIBLE)
				GetSpeLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
/*
			BoxWidth  	= (int)GetEDimBox()->GetWidth();
			BoxHeight 	= (int)GetEDimBox()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(ELEMENT);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsCntlOpen(0))
			{
				GetEDimBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				///////
				return;
			}
			else
			{
*/
				if(bMeshMode)
					str = "Mesh@ELEMENT";
				else
					str = "Generator@ELEMENT";
				pWnd->SetstrCntlID(str);
				/////////
				if(pWnd->GetCurrentOperID() != GOP_POST)
					strCur += "ELEMENT"; 
				//////
				break;
/*
			}			
*/

		case	SUPPORT:

			pWnd->SetMouseBoxType(SUPPORTBOX);
			///////////////////////////////////////////
//			if((GetEDimBox()->GetStyle()) & WS_VISIBLE)
//				GetEDimBox()->ShowWindow(SW_HIDE);
			if((GetStaLBox()->GetStyle()) & WS_VISIBLE)
				GetStaLBox()->ShowWindow(SW_HIDE);
			if((GetDynLBox()->GetStyle()) & WS_VISIBLE)
				GetDynLBox()->ShowWindow(SW_HIDE);
			if((GetSpeLBox()->GetStyle()) & WS_VISIBLE)
				GetSpeLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetSuppBox()->GetWidth();
			BoxHeight 	= (int)GetSuppBox()->GetHeight();
			/////////
			index		= GetElemBar()->CommandToIndex(SUPPORT);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsCntlOpen(1))
			{
				GetSuppBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				///////
				return;
			}
			else
			{
				str = "SUPPORT";
				pWnd->SetstrCntlID(str);
				/////////
				if(pWnd->GetCurrentOperID() != GOP_POST)
					strCur += str; 
				//////
				break;
			}			


		case	STATICLOAD:

			pWnd->SetMouseBoxType(STATICLOADBOX);
			///////////////////////////////////////////
//			if((GetEDimBox()->GetStyle()) & WS_VISIBLE)
//				GetEDimBox()->ShowWindow(SW_HIDE);
			if((GetSuppBox()->GetStyle()) & WS_VISIBLE)
				GetSuppBox()->ShowWindow(SW_HIDE);
			if((GetDynLBox()->GetStyle()) & WS_VISIBLE)
				GetDynLBox()->ShowWindow(SW_HIDE);
			if((GetSpeLBox()->GetStyle()) & WS_VISIBLE)
				GetSpeLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetStaLBox()->GetWidth();
			BoxHeight 	= (int)GetStaLBox()->GetHeight();		
			/////////
			index		= GetElemBar()->CommandToIndex(STATICLOAD);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsCntlOpen(2))
			{
				GetStaLBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				///////
				return;
			}
			else
			{
				str = "STATIC@LOAD";
				pWnd->SetstrCntlID(str);
				/////////
				if(pWnd->GetCurrentOperID() != GOP_POST)
					strCur += "STATIC LOAD"; 
				//////
				break;
			}			


		case	DYNAMICLOAD:

			pWnd->SetMouseBoxType(DYNAMICLOADBOX);
			///////////////////////////////////////////
//			if((GetEDimBox()->GetStyle()) & WS_VISIBLE)
//				GetEDimBox()->ShowWindow(SW_HIDE);
			if((GetSuppBox()->GetStyle()) & WS_VISIBLE)
				GetSuppBox()->ShowWindow(SW_HIDE);
			if((GetStaLBox()->GetStyle()) & WS_VISIBLE)
				GetStaLBox()->ShowWindow(SW_HIDE);
			if((GetSpeLBox()->GetStyle()) & WS_VISIBLE)
				GetSpeLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetDynLBox()->GetWidth();
			BoxHeight 	= (int)GetDynLBox()->GetHeight();		
			/////////
			index		= GetElemBar()->CommandToIndex(DYNAMICLOAD);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsCntlOpen(3))
			{
				///////////
				GetDynLBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				///////
				return;
			}
			else
			{
				str = "DYNAMIC@LOAD";
				pWnd->SetstrCntlID(str);
				/////////
				if(pWnd->GetCurrentOperID() != GOP_POST)
					strCur += "DYNAMIC LOAD"; 
				//////
				break;
			}			


		case	SPECTRALOAD:

			pWnd->SetMouseBoxType(SPECTRALOADBOX);
			///////////////////////////////////////////
//			if((GetEDimBox()->GetStyle()) & WS_VISIBLE)
//				GetEDimBox()->ShowWindow(SW_HIDE);
			if((GetSuppBox()->GetStyle()) & WS_VISIBLE)
				GetSuppBox()->ShowWindow(SW_HIDE);
			if((GetStaLBox()->GetStyle()) & WS_VISIBLE)
				GetStaLBox()->ShowWindow(SW_HIDE);
			if((GetDynLBox()->GetStyle()) & WS_VISIBLE)
				GetDynLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			BoxWidth  	= (int)GetSpeLBox()->GetWidth();
			BoxHeight 	= (int)GetSpeLBox()->GetHeight();		
			/////////
			index		= GetElemBar()->CommandToIndex(SPECTRALOAD);
			GetElemBar()->GetItemRect(index,&ItemRect);
			ClientToScreen(&ItemRect);
			//////////////////////////
			CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
			//////////////////////////////////////////////////////////////
			if(pWnd->IsCntlOpen(4))
			{
				///////////
				GetSpeLBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
				///////
				return;
			}
			else
			{
				str = "SPECTRAL@LOAD";
				pWnd->SetstrCntlID(str);
				/////////
				if(pWnd->GetCurrentOperID() != GOP_POST)
					strCur += "SPECTRAL LOAD"; 
				//////
				break;
			}			
			

	
			
		default:

			pWnd->SetMouseBoxType(CNTLBOX);
			//////////////////////////////////
//			if((GetEDimBox()->GetStyle()) & WS_VISIBLE)
//				GetEDimBox()->ShowWindow(SW_HIDE);
			if((GetSuppBox()->GetStyle()) & WS_VISIBLE)
				GetSuppBox()->ShowWindow(SW_HIDE);
			if((GetStaLBox()->GetStyle()) & WS_VISIBLE)
				GetStaLBox()->ShowWindow(SW_HIDE);
			if((GetDynLBox()->GetStyle()) & WS_VISIBLE)
				GetDynLBox()->ShowWindow(SW_HIDE);
			if((GetSpeLBox()->GetStyle()) & WS_VISIBLE)
				GetSpeLBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			str = "UNKNOWN";
			pWnd->SetstrCntlID(str);
			/////////
			if(pWnd->GetCurrentOperID() != GOP_POST)
			{
				strCur = "UNKNOWN Control Option";
				pWnd->SetstrCurrID(strCur);
			}
			return;
			///////		
	}
	///////////////////////////////////// Reset TaskID
	if(pWnd->GetCurrentOperID() == GOP_POST)
		pWnd->SetCurrentCntlID_Alternate(GetActiveElemObject());
	else
	if(bMeshMode)
		pWnd->SetCurrentCntlID_Mesh(GetActiveElemObject());
	else
		pWnd->SetCurrentCntlID(GetActiveElemObject());
	///
	m_WPARAM = IDW_CNTLBOX;
//	ReSetDataDialogs();
	////////////////
	if(pWnd->GetCurrentOperID() != GOP_POST)
	{
		if(bMeshMode)
		{
			strCur += "@Left CLICK: Select from MESH Box";
			pWnd->GetMGenBox()->ShowWindow(TRUE);	// Open MGenBox
			pWnd->GetMGenBox()->SetFocus();
		}
		else
		{
			strCur += "@Left CLICK: Select from GENERATOR Box";
			pWnd->GetIGenBox()->ShowWindow(TRUE);	// Open IGenBox
			pWnd->GetIGenBox()->SetFocus();
		}
		///
	}
	pWnd->SetstrCurrID(strCur);
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
	///////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
