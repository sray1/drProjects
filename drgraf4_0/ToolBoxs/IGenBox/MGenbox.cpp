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
#include "Def_Elem.h"   // Operations
#include "Def_IGen.h"   // Operations
#include "Def_Supp.h"   // Operations
#include "Def_StaL.h"   // Operations
#include "Def_SpeL.h"   // Operations
#include "Def_DynL.h"   // Operations
#include "Def_Mo.h"   // Operations
#include "Ext_Mo.h"
#include "Def_MoBox.h"
#include "MGenbox.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionIGen_DLL;
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMGenBox, CBoxWnd)
	//{{AFX_MSG_MAP(CMGenBox)
	ON_WM_CREATE()
	ON_WM_PAINT()  
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 

IMPLEMENT_DYNAMIC(CMGenBox,CBoxWnd)
/////////////////////////////////////////////////////////////////////////////
//array ofIDs Used to Initialize Elembar

static UINT BASED_CODE elembox[] =
{
	// same order as in the bitmap 'Elembox.bmp'
	IDB_MESH0D,
	IDB_MESH1D,
	IDB_MESH2D,
	IDB_MESH3D,
	IDB_MBJ3D
}; 

/////////////////////////////////////////////////////////////////////////////
// CMGenBox
CMGenBox::CMGenBox()
{ 
	m_nElemBarColMax 	= EB_MAX_BUTT_COL;	  // ElemBar Column 
	m_nElemBarRowMax	= 1;
	m_nActiveTool		= -1;             // None Selected                               //temorary
	m_nActiveElemObject	= -1;             // None Selected                               //temorary
    //////////////////////////////////    // map ToolIndex to ToolNumber
	FillToolNumArray();
	///////////////////
}                    

CMGenBox::~CMGenBox()
{
}
/////////////////////////////////////////////////////////////////////////////
// CMGenBox message handlers
int CMGenBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1; 
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////// ElemBar creation
	if (!CreateElemBar())
	{	
		AfxMessageBox("CMGenBox::OnCreate\nCannot Create ElemBar");
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
	/////////////////////////////////////////// MeshCNodeBox
	GetCNodeBox()->Create((CWnd*)this,BoxRect);
	/////////////////    
	return 0;
}

void CMGenBox::OnDestroy()
{
	CWnd::OnDestroy();
	/////////////////////////////////////////// NodeBox
	if(GetNodeBox()->m_hWnd != NULL)
		GetNodeBox()->DestroyWindow();
	/////////////////////////////////////////// Bar
	if(m_wndElemBar.m_hWnd != NULL)	
		m_wndElemBar.DestroyWindow();	
	
	// TODO: Add your message handler code here
	
}
//////////////////////////////////////////////////////////////////////
BOOL CMGenBox::CreateElemBar()
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
		AfxMessageBox("ERROR:CMGenBox::CreateElemBar()\nButton Count Discrepancy");
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
	if (!m_wndElemBar.Create(this, nLeft, nTop,IDW_MGENBOX,IDC_BUTTON) ||
		!m_wndElemBar.LoadBitmap(IDB_MGENBOX) ||
		!m_wndElemBar.SetButtons(elembox,sizeof(elembox)/sizeof(UINT),m_nElemBarColMax) )
	{
		TRACE("CMGenBox::CreateElemBar()\nFailed to create toolbar\n");
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

void CMGenBox::OnPaint()
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

int CMGenBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	
	return MA_ACTIVATE;
}

void CMGenBox::GoRespondtoMouse()
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
	////////////////////////////////////////// get index 
	index = GetElemBar()->CommandToIndex(mID);
    ////////////////////////// Show PatchBox 
	GetElemBar()->GetItemRect(index,&ItemRect);
	ClientToScreen(&ItemRect);
	//////////////////////////
//052997	pWnd->SetCurrentIGenID(mID);
	/////////////
	switch(mID)
	{
		case MESH0D:

			pWnd->SetMouseBoxType(NODEBOX);
			///////////
			if(pWnd->IsIGenOpen(0))
			{
				if(pWnd->GetCurrentOperID() == COP_CREATE)
				{
					///////////////////////////////////////////// Box 
					BoxWidth  	= (int)GetCNodeBox()->GetWidth();
					BoxHeight 	= (int)GetCNodeBox()->GetHeight();
					//////////////////////////
					CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
					GetCNodeBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
					      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
					////////////////////////////////////////////////////////////// 
				}		
				else
				{
					///////////////////////////////////////////// Box 
					BoxWidth  	= (int)GetNodeBox()->GetWidth();
					BoxHeight 	= (int)GetNodeBox()->GetHeight();
					//////////////////////////
					CalcBoxRect(BoxRect,ItemRect,BoxWidth,BoxHeight,ScreenHeight,ScreenWidth,FALSE);
					GetNodeBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
					      BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
					////////////////////////////////////////////////////////////// 
				}		
				return;
			}
			else
			{
				str = "0D@MESH";
				pWnd->SetstrIGenID(str);
				//////
				break;
			}			

		case MESH1D:

			pWnd->SetMouseBoxType(CURVEBOX);
			///////////
			str = "1D@MESH";
			pWnd->SetstrIGenID(str);
			//////
			break;
			
			
		case MESH2D:

			pWnd->SetMouseBoxType(PATCHBOX);
			///////////
			str = "2D@MESH";
			pWnd->SetstrIGenID(str);
			//////
			break;
			
		case MESH3D:

			pWnd->SetMouseBoxType(SOLIDBOX);
			///////////
			str = "3D@MESH";
			pWnd->SetstrIGenID(str);
			//////
			break;
			
		case MBJ3D:

			pWnd->SetMouseBoxType(OBJ3DBOX);
			///////////
			str = "Super@MESH";
			pWnd->SetstrIGenID(str);
			//////
			break;
			
		default:

			pWnd->SetMouseBoxType(MGENBOX);
			//////////////////////////////////
			if((GetNodeBox()->GetStyle()) & WS_VISIBLE)
				GetNodeBox()->ShowWindow(SW_HIDE);
			//////////////////////////////////////////////////////////////
			str = "DON'T KNOW";
			pWnd->SetstrIGenID(str);
			strCur = "UNKNOWN Control Option";
			pWnd->SetstrCurrID(strCur);
			return;
			///////		
			
	}
	///////////////////////////////////// Reset TaskID
	pWnd->SetCurrentIGenID_Mesh(GetActiveElemObject());
	///
	m_WPARAM = IDW_MGENBOX;
	ReSetDataDialogs();
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SendMessage(ID_UPDATE_STATCNTLS);
	///////
	return; 
		
}
///////////////////////////////// end of module ///////////////////////
