// viewinfo.cpp : implementation file
//

#include "stdafx.h"

#include "viewdll.h"
#include "viewinfo.h"
#include "CommRsrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewInfo dialog


CViewInfo::CViewInfo(CView* pView)
	: CDialog()                    // Modeless constructor
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CViewInfo)
	m_dBack 	= 0;
	m_dFront 	= 1;
	m_PRP_X 	= 0;
	m_PRP_Y 	= 0;
	m_PRP_Z 	= 0;
	m_Umax 		= 0;
	m_Umin 		= 0;
	m_Vmax 		= 0;
	m_Vmin 		= 0;
	m_VPN_X 	= 0;
	m_VPN_Y 	= 0;
	m_VPN_Z 	= 0;
	m_VRP_X 	= 0;
	m_VRP_Y 	= 0;
	m_VRP_Z 	= 0;
	m_VUP_X 	= 0;
	m_VUP_Y 	= 0;
	m_VUP_Z 	= 0;
	//}}AFX_DATA_INIT
	m_pView 	= pView;
}

void CViewInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewInfo)
	DDX_Text(pDX, IDC_FRONT, m_dFront);
	DDX_Text(pDX, IDC_BACK, m_dBack);
	DDX_Text(pDX, IDC_PRP_X, m_PRP_X);
	DDX_Text(pDX, IDC_PRP_Y, m_PRP_Y);
	DDX_Text(pDX, IDC_PRP_Z, m_PRP_Z);
	DDX_Text(pDX, IDC_UMAX, m_Umax);
	DDX_Text(pDX, IDC_UMIN, m_Umin);
	DDX_Text(pDX, IDC_VMAX, m_Vmax);
	DDX_Text(pDX, IDC_VMIN, m_Vmin);
	DDX_Text(pDX, IDC_VPN_X, m_VPN_X);
	DDX_Text(pDX, IDC_VPN_Y, m_VPN_Y);
	DDX_Text(pDX, IDC_VPN_Z, m_VPN_Z);
	DDX_Text(pDX, IDC_VRP_X, m_VRP_X);
	DDX_Text(pDX, IDC_VRP_Y, m_VRP_Y);
	DDX_Text(pDX, IDC_VRP_Z, m_VRP_Z);
	DDX_Text(pDX, IDC_VUP_X, m_VUP_X);
	DDX_Text(pDX, IDC_VUP_Y, m_VUP_Y);
	DDX_Text(pDX, IDC_VUP_Z, m_VUP_Z);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewInfo, CDialog)
	//{{AFX_MSG_MAP(CViewInfo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionView_DLL;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CViewInfo message handlers

BOOL CViewInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CViewInfo::Create ()
{
	
#ifdef _AFXDLL
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionView_DLL.hModule); // uses server's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
	/////////////////////////////////////////////////////////////
	return CDialog::Create(CViewInfo::IDD);
	///////////////////////////////////////
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	
}

void CViewInfo::OnCancel()
{
	CDialog::OnCancel();
	////////////////////
	if(m_pView !=NULL)
		m_pView->SendMessage(ID_GOODBYE_EYEPOS,IDCANCEL);
}

void CViewInfo::OnOK()
{
	CDialog::OnOK();
	////////////////////
	if(m_pView !=NULL)
		m_pView->SendMessage(ID_GOODBYE_EYEPOS,IDOK);
}

void CViewInfo::OnUpdate()
{
	if(m_pView !=NULL)
		m_pView->SendMessage(ID_UPDATE_EYEPOS,IDC_UPDATE);
}
//////////////////////////// end of module ////////////
