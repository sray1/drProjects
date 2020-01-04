// pendlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxcmn.h>		// CSpinButtonCtrl ( Technical Note #60 )

#include "sdlgrsrc.h"
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "DrPen.h"
////////////////////
#include "Dlg_Pen.h" 

#ifdef _DEBUG
#undef THIS_FILE
#include "drgraf.h"
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
///////////////////////
#define NUMLEN		3
#define	WIDTHMAX	999
/////////////////////////////////////////////////////////////////////////////
// CPenDlg dialog

CPenDlg::CPenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenDlg::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CPenDlg)
	m_nWidth    = 0;
	m_StyleName = "";
	//}}AFX_DATA_INIT
}

void CPenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPenDlg)
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 0, 999);
	DDX_CBString(pDX, IDC_COMBO_STYLE, m_StyleName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPenDlg, CDialog)
	//{{AFX_MSG_MAP(CPenDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenDlg message handlers
void CPenDlg::OnPen()
{
	// TODO: Add your command handler code here
				  		
/////////////////////////////////////////////////////////////////////////////
/*
// Run the test		//16

	HINSTANCE hLibrary;
//16	if ( (hLibrary = LoadLibrary("MUSCROLL.DLL")) < HINSTANCE_ERROR)
	if( 	(hLibrary = LoadLibrary("MUSCROLL.DLL")) == NULL)
	{
		AfxMessageBox("Can not Spin without custom control library");

		// prevent it from happening again
//		GetMenu()->EnableMenuItem(IDM_TEST_SPIN_EDIT, MF_DISABLED|MF_GRAYED);
		return;
	}

	TRACE("running dialog with spin controls in it\n");
*/
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen* pDrPen	 		= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
    ////////////////////////////////////
	CPenDlg	dlg;
	UINT nStyleCount = pDrPen->GetStyleNameCount();
	
	pDrPen->SetStyleOld(pDrPen->GetStyle() );       // save old
	//set dialog combo index
	dlg.m_StyleName = pDrPen->GetStyleName(pDrPen->GetIndex());
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data 
		for(UINT i=0; i<nStyleCount; i++)
		{
			if(dlg.m_StyleName == pDrPen->GetStyleName(i))
			{
				pDrPen->SetIndex(i);
				break;
			}
		}
   		UINT index = pDrPen->GetIndex(); 
		UINT nStyle= pDrPen->GetStyleConstant(index);
		////////////////////////	
		pDrPen->SetStyle(nStyle);
		pDrPen->SetColor(dlg.m_PenColor);
		pDrPen->SetWidth(dlg.m_nWidth);
		if(nStyle != PS_SOLID)
			pDrPen->SetWidth(0);    // all other Penstyles valid for width = 1			
		///////////////// Reset Pen
		pDrPen->ReplacePen();	          
		///////////////					
	}		
	//////////////////////
//16	FreeLibrary(hLibrary);
	//////////////////////
	
}

BOOL CPenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here 
	////////////////////////////////////////////////////////////////// 
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
/*
//////////////////////////////// WIDTH    
	UINT nID = IDC_EDIT_WIDTH;
	CPEditWidth.SubclassEdit(nID, this, PES_NUMBERS);
	CWnd* pWndCtrl = GetDlgItem(nID);
	((CEdit*)(pWndCtrl))->LimitText(NUMLEN); 
	// associate button with edit item
	CSpinControl* pSpin = (CSpinControl*)GetDlgItem(IDC_BUTTON_WIDTH);
	ASSERT(pSpin != NULL);
		pSpin->SetAssociate(&CPEditWidth);
		pSpin->SetRange(0,WIDTHMAX);
*/
	CWnd* pEditWidth = GetDlgItem(IDC_EDIT_WIDTH);
	((CEdit*)(pEditWidth))->LimitText(NUMLEN); 
	// associate button with edit item
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_WIDTH);
	ASSERT(pSpin != NULL);
	pSpin->SetBuddy(pEditWidth);
	pSpin->SetBase(10);
	pSpin->SetRange(0,WIDTHMAX);
	pSpin->SetPos(0);
//////////////////////////////// COLOR LISTBOX    
	// subclass the control
	VERIFY(m_colors.SubclassDlgItem(IDC_LIST_COLOR, this));

	// add 8 colors to the listbox (primary + secondary color only)
	for (int red = 0; red <= 255; red += 255)
		for (int green = 0; green <= 255; green += 255)
			for (int blue = 0; blue <= 255; blue += 255)
				m_colors.AddColorItem(RGB(red, green, blue));
/*
	for (int red = 0; red <= 255; red<255 ? red+= 128:red = 255)
		for (int green = 0; green <= 255; green<255 ? green+= 128:green = 255)
			for (int blue = 0; blue <= 255; blue<255 ? blue+= 128:blue = 255)
				m_colors.AddColorItem(RGB(red, green, blue)); 
*/				
	//////////////////////////// STYLE
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen* pDrPen	 		= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
    ////////////////////////////////////
	CWnd* pWndCtrl   = GetDlgItem(IDC_COMBO_STYLE);
	((CComboBox*)(pWndCtrl))->SetCurSel(pDrPen->GetIndex());
    ////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPenDlg::OnOK()
{
	// get the final width
	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_WIDTH);
	ASSERT(pSpin != NULL);
	m_nWidth = pSpin->GetPos();
	///////////////////////////////////
	// get the final color
	int nIndex = m_colors.GetCurSel();
	if (nIndex == -1)
	{
		MessageBox("Please Select a Color");
		m_colors.SetFocus();
		return;
	}
	m_PenColor = m_colors.GetItemData(nIndex);

#ifdef _DEBUG
	// normally do something with it...
	TRACE("final color RGB = 0x%06lX\n", m_PenColor);
#endif

//	EndDialog(IDOK);
	CDialog::OnOK();
}

///////////////////////////////////////////////////////////////////
void CColorListBox::AddColorItem(COLORREF color)
{
	// add a listbox item
	AddString((LPCSTR) color);
		// Listbox does not have the LBS_HASSTRINGS style, so the
		//  normal listbox string is used to store an RGB color
}

///////////////////////////////////////////////////////////////////

#define COLOR_ITEM_HEIGHT   20

void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	// all items are of fixed size
	// must use LBS_OWNERDRAWVARIABLE for this to work
	lpMIS->itemHeight = COLOR_ITEM_HEIGHT;
}

void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	COLORREF cr = (COLORREF)lpDIS->itemData; // RGB in item data

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		// Paint the color item in the color requested
		CBrush br(cr);
		pDC->FillRect(&lpDIS->rcItem, &br);
	}

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// item has been selected - hilite frame
		COLORREF crHilite = RGB(255-GetRValue(cr),
						255-GetGValue(cr), 255-GetBValue(cr));
		CBrush br(crHilite);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		// Item has been de-selected -- remove frame
		CBrush br(cr);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}
}

int CColorListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCIS)
{
	COLORREF cr1 = (COLORREF)lpCIS->itemData1;
	COLORREF cr2 = (COLORREF)lpCIS->itemData2;
	if (cr1 == cr2)
		return 0;       // exact match

	// first do an intensity sort, lower intensities go first
	int intensity1 = GetRValue(cr1) + GetGValue(cr1) + GetBValue(cr1);
	int intensity2 = GetRValue(cr2) + GetGValue(cr2) + GetBValue(cr2);
	if (intensity1 < intensity2)
		return -1;      // lower intensity goes first
	else if (intensity1 > intensity2)
		return 1;       // higher intensity goes second

	// if same intensity, sort by color (blues first, reds last)
	if (GetBValue(cr1) > GetBValue(cr2))
		return -1;
	else if (GetGValue(cr1) > GetGValue(cr2))
		return -1;
	else if (GetRValue(cr1) > GetRValue(cr2))
		return -1;
	else
		return 1;
}

/////////////////////////////////////////////////////////////////////////////
