// dlg_Co4I.cpp : implementation file
//

#include "stdafx.h"

#include "3DMath.h"

#include "UserMsg.h"
#include "glb_Objs.h"
#include "glb_CuPS.h"
#include "Glb_Mous.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
////////////////////
#include "CommRsrc.h"
#include "MPatRsrc.h"

#include "dlg_Co4I.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1

/////////////////////////////////////////////////////////////////////////////
// CDlg_Co4I dialog


CDlg_Co4I::CDlg_Co4I(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_Co4I)
	//}}AFX_DATA_INIT
	///////////////////////
	m_pWnd 	= pWnd;
	m_Orient_1 = "FORWARD";
	m_Orient_2 = "FORWARD";
	m_Orient_3 = "FORWARD";
	m_Orient_4 = "FORWARD";
}

void CDlg_Co4I::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Co4I)
	DDX_CBString(pDX, IDC_PID, m_PatchID);
	DDX_CBString(pDX, IDC_CID_1, m_CID_1);
	DDX_CBString(pDX, IDC_CID_2, m_CID_2);
	DDX_CBString(pDX, IDC_CID_3, m_CID_3);
	DDX_CBString(pDX, IDC_CID_4, m_CID_4);
	DDX_Text(pDX, IDC_TOTEL_1, m_TotEl_1);
	DDX_Text(pDX, IDC_TOTEL_2, m_TotEl_2);
	DDX_Text(pDX, IDC_TOTEL_3, m_TotEl_3);
	DDX_Text(pDX, IDC_TOTEL_4, m_TotEl_4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Co4I, CDialog)
	//{{AFX_MSG_MAP(CDlg_Co4I)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_CID_1, OnSelchangeCid1)
	ON_CBN_SELCHANGE(IDC_CID_2, OnSelchangeCid1)
	ON_CBN_SELCHANGE(IDC_CID_3, OnSelchangeCid1)
	ON_CBN_SELCHANGE(IDC_CID_4, OnSelchangeCid1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;

BOOL CDlg_Co4I::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMPat_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_Co4I::IDD);
	///////////////////////////////////////
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
	//////////////////
	return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CDlg_Co4I message handlers
BOOL CDlg_Co4I::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
/*
	pWndCtrl = GetDlgItem(IDC_CID_1);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_2);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
*/
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatches	= pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMaxPatches)
		FillListAllPatchIDs();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves	= pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllCurveIDs();   //  with Curves
	///////////////////////////////////////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Co4I::OnSelchangeCid1() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrCurve*	pDrCurve;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_1);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{
		pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_TotEl_1	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Co4I::OnSelchangeCid2() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrCurve*	pDrCurve;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_2);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{
		pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_TotEl_2	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Co4I::OnSelchangeCid3() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrCurve*	pDrCurve;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_3);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{
		pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_TotEl_3	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Co4I::OnSelchangeCid4() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrCurve*	pDrCurve;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_4);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{
		pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_TotEl_4	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Co4I::OnUpdate()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	BOOL bClosed;
	int nOut1,nOut2;
	int index;
	CDrCurve* pDrCurve1;
	CDrCurve* pDrCurve2;
	CDrCurve* pDrCurve3;
	CDrCurve* pDrCurve4;
    ///////////////////////////////////////////////////////////////////////// Check S-dir Compatibility
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_1,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_1!\nPlease Select One from the List");
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	pDrCurve1	= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut1		= pDrCurve1->GetMaxOutPts_S();
	bClosed		= pDrCurve1->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	////////////////////////////////////////////////////////////////////////// Curve3
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_3,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_3!\nPlease Select One from the List");
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	pDrCurve3		= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut2			= pDrCurve3->GetMaxOutPts_S();
	bClosed			= pDrCurve3->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_3);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_1:\n\tNumber of Elements = %d\nCURVE_3:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
    ///////////////////////////////////////////////////////////////////////// Check T-dir Compatibility
	///////////////////////////////////////////////////////////////////////// Curve2
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_2,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_2!\nPlease Select One from the List");
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	pDrCurve2		= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut1			= pDrCurve2->GetMaxOutPts_S();
	bClosed			= pDrCurve2->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	////////////////////////////////////////////////////////////////////////// Curve4
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_4,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_4!\nPlease Select One from the List");
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	pDrCurve4		= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut2			= pDrCurve4->GetMaxOutPts_S();
	bClosed			= pDrCurve4->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_4);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_2:\n\tNumber of Elements = %d\nCURVE_4:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	///////////////////////////////////////////////////////////////// Check CONNECTIVITY
	C3DMath Math3D;
	///////////////
	CDListMgr*	pINList;
	WORLD		LocalPosB1,LocalPosE1,LocalPosB2,LocalPosE2,
				LocalPosB3,LocalPosE3,LocalPosB4,LocalPosE4,
				LocalPosB;
	CDrNode*	pNode_Beg;
	CDrNode*	pNode_End;
	//////////////////////////////////////////////////////// Curve 1
	pINList		= pDrCurve1->GetCNodeList();
	////////////////////////////////////////////
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_1 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB1 = *(pNode_Beg->GetLocalPos());
	LocalPosE1 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Curve 2
	pINList		= pDrCurve2->GetCNodeList();
	////////////////////////////////////////////
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_2 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB2 = *(pNode_Beg->GetLocalPos());
	LocalPosE2 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Curve 3
	pINList		= pDrCurve3->GetCNodeList();
	////////////////////////////////////////////
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_3 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB3 = *(pNode_Beg->GetLocalPos());
	LocalPosE3 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Curve 4
	pINList		= pDrCurve4->GetCNodeList();
	////////////////////////////////////////////
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_4 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB4 = *(pNode_Beg->GetLocalPos());
	LocalPosE4 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Do Check
	BOOL bDisJoint = TRUE;
	double dLen;
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB1,&LocalPosE4,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB1)) * fabs(Math3D.Len3DPts(&LocalPosE4)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_4(End) & Curve_1(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB2,&LocalPosE1,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB2)) * fabs(Math3D.Len3DPts(&LocalPosE1)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_1(End) & Curve_2(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB3,&LocalPosE2,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB3)) * fabs(Math3D.Len3DPts(&LocalPosE2)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_2(End) & Curve_3(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB4,&LocalPosE3,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB4)) * fabs(Math3D.Len3DPts(&LocalPosE3)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_3(End) & Curve_4(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		///////////////////////////////////////////////////
		if(m_pWnd !=NULL)
			m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_ERRDATA) );
		////////////////////////////////////////////////////
	}
/*
	/////////////////////////////////////////////////////////////////  VALID:ADD
	int nActiveIndex;
    CDrPatch* pAdd 	= (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
    SetInfoForDataBase(pAdd);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrCurve which IS NOT  YET INTERPOLATED
	/////////////////////////////////////////////////////////
	pAdd->SetShow(FALSE);
	///////////////
	CDialog::OnOK();
*/
	///////////////////////////////////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_CO4IN,
					MAKEWPARAM(IDC_UPDATE,ID_OKDATA) );
	////////////////////////////////////////////////////
}
/*
void CDlg_Co4I::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
*/
void CDlg_Co4I::FillListAllPatchIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(PATCH);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == PATCH)
			{ 
				CDrCurve* pCurve = (CDrCurve*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_PID);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
			}	   		     
    	}
	} 
    
}    

void CDlg_Co4I::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == CURVE)
			{ 
				CDrCurve* pCurve = (CDrCurve*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_1);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_2);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_3);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_4);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   		    /////////////////////////////////
			}	   		     
    	}
	} 
    
}    
////////////////////////////////// end of module //////////////////////
