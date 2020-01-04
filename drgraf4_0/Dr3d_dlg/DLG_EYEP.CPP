// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"

#include "dlg_EyeP.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
//////////////////////////////////
#define	ViewISO	4
///////////////////////////
	RECT    RectSample;
/////////////////////////////////////////////////////////////////////////////
// CEyePosition dialog

CEyePosition::CEyePosition(CWnd* pParent /*=NULL*/)
	: CDialog(CEyePosition::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CEyePosition)
	m_nRotation = 30;
	m_nTilt     = 30;
	m_nIncrement = 1;
	//}}AFX_DATA_INIT
}

void CEyePosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEyePosition)
	DDX_Text(pDX, IDC_ROTATION, m_nRotation);
	DDV_MinMaxUInt(pDX, m_nRotation, 0, 360);
	DDX_Text(pDX, IDC_TILT, m_nTilt);
	DDV_MinMaxUInt(pDX, m_nTilt, 0, 360);
	DDX_Text(pDX, IDC_SPIN_INCREMENT, m_nIncrement);
	DDV_MinMaxUInt(pDX, m_nIncrement, 1, 50);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEyePosition, CDialog)
	//{{AFX_MSG_MAP(CEyePosition)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEyePosition message handlers

BOOL CEyePosition::OnInitDialog()
{
	CDialog::OnInitDialog();
//	AfxMessageBox("CEyePosition::OnInitDialog");
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
////////????????????????
//////////////////////////////// TILT    
	UINT nID = IDC_TILT;
	CPEditTilt.SubclassEdit(nID, this, PES_NUMBERS);
	CWnd* pWndCtrl = GetDlgItem(nID);
	((CEdit*)(pWndCtrl))->LimitText(3); 
//	SetDlgItemInt(nID, value);
	// associate button with edit item
	CSpinControl* pSpin = (CSpinControl*)GetDlgItem(IDC_BUTTON_TILT);
	ASSERT(pSpin != NULL);
		pSpin->SetAssociate(&CPEditTilt);
		pSpin->SetRange(0,360);
//////////////////////////////// ROTATION    
	     nID = IDC_ROTATION;
	CPEditRotation.SubclassEdit(nID, this, PES_NUMBERS);
	      pWndCtrl = GetDlgItem(nID);
	((CEdit*)(pWndCtrl))->LimitText(3); 
///	SetDlgItemInt(nID, value);
	// associate button with edit item
	              pSpin = (CSpinControl*)GetDlgItem(IDC_BUTTON_ROTATION);
	ASSERT(pSpin != NULL);
		pSpin->SetAssociate(&CPEditRotation);
		pSpin->SetRange(0,360);
//////////////////////////////// INCREMENT    
	     nID = IDC_SPIN_INCREMENT;
	CPEditIncrement.SubclassEdit(nID, this, PES_ALL);
	     pWndCtrl = GetDlgItem(nID);
	((CEdit*)(pWndCtrl))->LimitText(3); 
///	SetDlgItemInt(nID, value);
	// associate button with edit item
	              pSpin = (CSpinControl*)GetDlgItem(IDC_BUTTON_INCREMENT);
	ASSERT(pSpin != NULL);
		pSpin->SetAssociate(&CPEditIncrement);
		pSpin->SetRange(1,50);
/////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*
void CEyePosition::OnOK()
{
	UINT valueTilt,valueRotation;
	UINT increment;
	
	UINT nID = 0;
	BOOL bOk = TRUE;

	if(bOk)
	{
		nID = IDC_TILT;
		valueTilt = GetDlgItemInt(nID, &bOk);
	}		

	if (!bOk)
	{
		// report illegal value
		MessageBox("illegal value\n");
		CEdit& badEdit = *(CEdit*)GetDlgItem(nID);
		badEdit.SetSel(0, -1);
		badEdit.SetFocus();
		return;     // don't end dialog
	}

}
*/
void CEyePosition::OnPaint()
{
	CPaintDC dc(this); // device context for painting 
	///////////////////////////////////
	int nOldMapMode = dc.SetMapMode(MM_LOENGLISH);
	///////////////////////////////	
	DrawSampleAxes(&dc);
	////////////////////////   
	nOldMapMode = dc.SetMapMode(nOldMapMode);
	/////////////////////////////////////////////////
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CEyePosition::DrawSampleAxes(CDC* PtrDC)
{
	
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	CBrush  Brush;
   	CBrush* PtrOldBrush;
	
    /////////////////////////////////////////////////// 
    RECT	RectSample;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&RectSample);
	ScreenToClient(&RectSample);        
	//////////////////////////////
	PtrDC->SetBkMode(TRANSPARENT);
//  Create inner border rectangle

    RectSample.left   += 3;
    RectSample.top    +=12 ;
    RectSample.right  -= 3;
    RectSample.bottom -= 3;		
	///////////////////////////////////////////////////// AxisLength=DevCoord	
	int nAxisLength  = (RectSample.right - RectSample.left)/3;  
	
    Brush.CreateSolidBrush(RGB(255,0,0));
//   PtrOldBrush= (CBrush*)PtrDC->SelectStockObject(NULL_BRUSH); 
    PtrOldBrush= PtrDC->SelectObject(&Brush); 
    ////////////////////////////
    PtrDC->DPtoLP(&RectSample);
    PtrDC->Rectangle(&RectSample);
    ////////////////////////////
    PtrDC->SelectObject(PtrOldBrush);             
    Brush.DeleteObject(); 
	///////////////////////////////////////////////////// Origin=LogCoord
	POINT Origin     = GetCenter(&RectSample);
//  PtrDC->LPtoDP(&RectSample); 
//	PtrDC->DPtoLP(&Origin);
    ///////////////////////////////////// Pen Width
    int nPenWidth = ::GetSystemMetrics(SM_CXBORDER);
	// Create Black Pen 3 Pixel wide;   
   	Pen.CreatePen (PS_SOLID,1,0x000000);
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////////  Get Doc Info
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc); 
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CAxis* pAxis	 = pObjectMgr->GetAxis();
	CXForm* pXForm	 = pObjectMgr->GetXForm();
	/////////////////////////// Set Current Angles
	BOOL bOk;
	UINT nTilt,nRotation;
    nTilt     = (UINT)GetDlgItemInt(IDC_TILT    , &bOk); 
    nRotation = (UINT)GetDlgItemInt(IDC_ROTATION, &bOk);
	pXForm->SetTilt(nTilt);
	pXForm->SetRotation(nRotation);
    /////////////////////////// Get Transformation Array
    double Tran[2][3];
	pXForm->GetTranArray(Tran); 
	/////////////////////////// Get Axes
	UINT nAxes[3];
	pAxis ->GetAxes(nAxes);
    ////////////////////////////////////// Draw Axes: LogCoord
    pAxis->SetLength(nAxisLength);
	pAxis->DrawAxes(PtrDC,Origin,Tran,nAxes,ViewISO);
	////////////////////////////////////// Draw Prism: LogCoord 
	CPrism Prism(nAxisLength-15,nAxisLength-10,nAxisLength-15);
	Prism.DrawPrism(PtrDC,Origin,Tran);
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject();
    ///////////////////
}

POINT CEyePosition::GetCenter(RECT* Rect)
{
	POINT ptBeg;
	
	ptBeg.x = Rect->left + (Rect->right  - Rect->left)/2;
	ptBeg.y = Rect->top  + (Rect->bottom - Rect->top) /2;
	
	return ptBeg;
}	 
////////////////////////////////// end of module \\\\\\\\\\\\\\\\\\\\\
