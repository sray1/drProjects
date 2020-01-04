// XtruLens.cpp : implementation file
//

#include "stdafx.h"

#include "math.h"
#include <float.h>		// DBL_EPSILON

#include "Def_Type.h"
#include "Def_MouseAct.h"
/////////////////////
#include "XtruLens.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXtruLens dialog


CXtruLens::CXtruLens(CWnd* pParent /*=NULL*/)
	: CDialog(CXtruLens::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXtruLens)
	m_Xtru_X	= 0.0;
	m_Xtru_Y	= 0.0;
	m_Xtru_Z	= 0.0;
	m_DirX		= 0.0;
	m_DirY		= 0.0;
	m_DirZ		= 0.0;
	m_dLen		= 0.0;
	//}}AFX_DATA_INIT
}


void CXtruLens::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXtruLens)
	DDX_Text(pDX, IDC_EXTRU_X, m_Xtru_X);
	DDX_Text(pDX, IDC_EXTRU_Y, m_Xtru_Y);
	DDX_Text(pDX, IDC_EXTRU_Z, m_Xtru_Z);
	DDX_Text(pDX, IDC_DIRX, m_DirX);
	DDX_Text(pDX, IDC_DIRY, m_DirY);
	DDX_Text(pDX, IDC_DIRZ, m_DirZ);
	DDX_Text(pDX, IDC_EXTRU_LEN, m_dLen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXtruLens, CDialog)
	//{{AFX_MSG_MAP(CXtruLens)
	ON_EN_CHANGE(IDC_EXTRU_Z, OnChangeExtruZ)
	ON_EN_CHANGE(IDC_EXTRU_X, OnChangeExtruX)
	ON_EN_CHANGE(IDC_EXTRU_Y, OnChangeExtruY)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXtruLens message handlers

void CXtruLens::OnChangeExtruZ() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	ShowResultants();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	
}

void CXtruLens::OnChangeExtruX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	ShowResultants();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	
}

void CXtruLens::OnChangeExtruY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	ShowResultants();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	
}

void CXtruLens::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CXtruLens::OnOK() 
{
	if(m_Xtru_X == 0.0 && m_Xtru_Y == 0.0 && m_Xtru_Z == 0.0)
	{
		AfxMessageBox("INADMISSIBLE DATA:\nAll Components can NOT be\n Simultaneously 0.0");
		return;
	}
	CDialog::OnOK();
}

int CXtruLens::ShowResultants()
{
	WORLD wLen,wAxis;
	/////////////////
	wLen.x = m_Xtru_X;
	wLen.y = m_Xtru_Y;
	wLen.z = m_Xtru_Z;
	///////////////////////////////////////// AxisVector from wLen
	m_dLen	= UnitAxis_N_LenFromWorldLength(wLen,wAxis);
	m_DirX	= wAxis.x;
	m_DirY	= wAxis.y;
	m_DirZ	= wAxis.z;
	//////
	return MA_OK;
}

double CXtruLens::UnitAxis_N_LenFromWorldLength(WORLD wLen,WORLD& wAxis)
{
	///////////////////////////////////////////// Vector
	wAxis.x = wLen.x;  
	wAxis.y = wLen.y;  
	wAxis.z = wLen.z; 
	///////////////////////////////////////////// Unit
	double NewD =	sqrt(
							wAxis.x*wAxis.x +  
    						wAxis.y*wAxis.y +
    						wAxis.z*wAxis.z
						);
	/////////////////////
	if(NewD <DBL_EPSILON)
		return 0.0;
	////////////////////
	double r = 1.0/NewD;
	///////////////////////////// Unit vector
	wAxis.x *= r;  
	wAxis.y *= r;  
	wAxis.z *= r;
	///////////////
	return NewD; 
}

///////////////////////// end of Module //////////////////////////////
