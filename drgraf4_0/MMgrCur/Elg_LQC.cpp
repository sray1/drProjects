// dlg_cirr.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
//#include "drgrafrm.h" 
/////////////////////
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "dlg_CMsR.h"	
#include "dlg_CMes.h"	
#include "dlg_Knot.h"	
#include "dlg_Wts.h"	
#include "dlg_Tang.h"
	
#include "CommRsrc.h"
#include "Elg_LQC.h"	// Curve Interpolate Rational: Rightbutton

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_UNIF	1
///////////////////////////////////////////////////////////////////////////////
//				DO NOT CHANGE FOLLOWING ORDER AND SPELLING
	static CString BCs[] 	= {	"AUTO","CLAMPED","FREE","BESSEL","QUADRATIC",
								"NOT_A_KNOT","TANGENT"};
	static int nBC 			= sizeof(BCs)/sizeof(BCs[0]);
	static CString Deg[] 	= {	"LINEAR","QUADRATIC","CUBIC"};
	static int Ord[] 		= {2,3,4};
	static int nDeg 		= sizeof(Deg)/sizeof(Deg[0]);
/////////////////////////////////////////////////////////////////////////////
// CElg_LQC dialog


CElg_LQC::CElg_LQC(CWnd* pParent /*=NULL*/)
	: CDialog(CElg_LQC::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CElg_LQC)
	m_bAutoKn 	= TRUE;
	m_bAutoWt 	= FALSE;
	m_strBCL 	= "AUTO";
	m_strBCR 	= "AUTO";
	m_nControls = 0;			// L + k - 1 = nData + k - 2 = n + 1
	m_nCurveSeg = 0;			// L = nData - 1  intervals
	m_strDegree = "CUBIC";		// k - 1
	m_bUnifKN 	= FALSE;
	m_bUnifWT 	= TRUE;
	m_strKN 	= "AUTO";
	m_bClosed 	= FALSE;
	m_bRightOn 	= TRUE;
	m_bLeftOn 	= TRUE;
	m_CurveID  	= "";
	//}}AFX_DATA_INIT
	//////////////////////////
	m_Ratio			= 1.0;
	m_Typ_KN 		= KN_AUTO;
	m_Typ_WT 		= WT_UNIFORM;
	///////////////////////////////////////////	
	m_bUnifOT 		= TRUE;
	m_nMaxOSeg 		= DEFAULT_UNIF; 
	m_nMaxDistinct 	= 0;		// n - k + 3 = nData				Knots, Weights
	m_nMaxTotal		= 0;		// n + k + 1 = nData + (2k - 2)		Knots, Weights
	/////////////////////// Memory
	m_pKVal 		= NULL;
	m_pWVal 		= NULL;
	m_pOSeg 		= NULL;
	m_pODis 		= NULL;
	///////////////////////
	
}

void CElg_LQC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElg_LQC)
	DDX_Check(pDX, IDC_AUTO_KN, m_bAutoKn);
	DDX_Check(pDX, IDC_AUTO_WT, m_bAutoWt);
	DDX_CBString(pDX, IDC_BC_LEFT, m_strBCL);
	DDX_CBString(pDX, IDC_BC_RIGHT, m_strBCR);
	DDX_Text(pDX, IDC_CPOUT, m_nControls);
	DDX_Text(pDX, IDC_CSOUT, m_nCurveSeg);
	DDX_CBString(pDX, IDC_DEGREE, m_strDegree);
	DDX_Check(pDX, IDC_UNIF_KN, m_bUnifKN);
	DDX_Check(pDX, IDC_UNIF_WT, m_bUnifWT);
	DDX_CBString(pDX, IDC_KN_OPTION, m_strKN);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Check(pDX, IDC_BC_RIGHT_ON, m_bRightOn);
	DDX_Check(pDX, IDC_BC_LEFT_ON, m_bLeftOn);
	DDX_Text(pDX, IDC_CID, m_CurveID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CElg_LQC, CDialog)
	//{{AFX_MSG_MAP(CElg_LQC)
	ON_BN_CLICKED(IDC_AUTO_KN, OnAutoKn)
	ON_BN_CLICKED(IDC_AUTO_WT, OnAutoWt)
	ON_BN_CLICKED(IDC_NONU_KN, OnNonuKn)
	ON_BN_CLICKED(IDC_NONU_WT, OnNonuWt)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_CLICKED(IDC_UNIF_KN, OnUnifKn)
	ON_BN_CLICKED(IDC_UNIF_WT, OnUnifWt)
	ON_CBN_SELCHANGE(IDC_BC_LEFT, OnSelchangeBcLeft)
	ON_CBN_SELCHANGE(IDC_BC_RIGHT, OnSelchangeBcRight)
	ON_CBN_SELCHANGE(IDC_DEGREE, OnSelchangeDegree)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_CLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	ON_BN_DOUBLECLICKED(IDC_AUTO_KN, OnAutoKn)
	ON_BN_DOUBLECLICKED(IDC_AUTO_WT, OnAutoWt)
	ON_BN_DOUBLECLICKED(IDC_NONU_KN, OnNonuKn)
	ON_BN_DOUBLECLICKED(IDC_NONU_WT, OnNonuWt)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_UNIF_KN, OnUnifKn)
	ON_BN_DOUBLECLICKED(IDC_UNIF_WT, OnUnifWt)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_DOUBLECLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CElg_LQC message handlers

BOOL CElg_LQC::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//structural
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString_Pool();   // only with Nodes
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllString_Curve();   // only with Curves
	GetDlgItem(IDD_LIST)->EnableWindow(FALSE);// for view only	
	/////////////////////////////////////////////////////////
	m_strDegree = "CUBIC";	// k - 1 	DEFAULT
	if(m_nOrder == 2)
		m_strDegree = "LINEAR";		// k - 1
	else	
	if(m_nOrder == 3)
		m_strDegree = "QUADRATIC";	// k - 1
	else	
	if(m_nOrder == 4)
		m_strDegree = "CUBIC";	// k - 1
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_DEGREE))->SetCurSel(4-m_nOrder);//Cubic=0/Quad=1/Lin=2
   	////////////
	OnSelchangeDegree(); // this will reset Combos according to ORDER
	//////////////////////////////////////////////////////////////////
/*			
	// Set: CUBIC:	NonRational(ALWAYS)
	CComboBox*	pCombo;
	/////////////////////////////////////////////// BoundaryCombosRight
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
	int i;
	for(i=0;i<nBC-1;i++)	// 								
 		pCombo->AddString(BCs[i]);
 	pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
	/////////////////////////////////////////////// BoundaryCombosLeft
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT);
	for(i=0;i<nBC-1;i++)	// 								
 		pCombo->AddString(BCs[i]);
 	pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
    /////////////////////////////////////////////// Disabled Windows(Weights)
	(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
	(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
	(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
    /////////////////////////////////////////////// Disabled Window(Unif/Non Knot)
    // only AUTO
	(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
	(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
*/	
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
	pWndCtrl->SetFocus();
    //////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CElg_LQC::OnDel()
{
	//delete current selection from SelectList	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
		((CListBox*)(pWndCtrl))->DeleteString(index); 
	//////////////////////////////////////////////// Update	 
    int nData 		= ((CListBox*)(pWndCtrl))->GetCount();
	m_nControls 	= nData + m_nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nMaxDistinct 	= nData;						// n - k + 3 = nData				
	m_nMaxTotal		= nData + (2 * m_nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	//////////////////////////////////////////////////
	if(nData<3)
		m_bClosed	= FALSE; 
	m_nCurveSeg 	= m_bClosed ? nData : nData - 1;
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnAdd()
{
	// Add Current selction of POOLLIST to SELECTLIST	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
   	{
		CString CNid;
		((CListBox*)(pWndCtrl))->GetText(index,CNid);
		////////////////////////////////////// 
		pWndCtrl = GetDlgItem(IDD_SELECTLIST);
		if( (((CListBox*)(pWndCtrl))->FindString(-1,CNid) ) >=0)     // already selected:
			return;                                                  // Distinct Data Only
		((CListBox*)(pWndCtrl))->AddString(CNid);
	}
	//////////////////////////////////////////////// Update	 
    int nData 		= ((CListBox*)(pWndCtrl))->GetCount();
	m_nControls 	= nData + m_nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nMaxDistinct 	= nData;						// n - k + 3 = nData				
	m_nMaxTotal		= nData + (2 * m_nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	//////////////////////////////////////////////////
	if(nData<3)
		m_bClosed	= FALSE; 
	m_nCurveSeg 	= m_bClosed ? nData : nData - 1;
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////// Curve ID
   	if("" == m_CurveID)
   	{
   		AfxMessageBox("Please Select a Curve ID");
   		return;
   	}
   ///////////////////	
	//	 Check first If Adequate Number of DataNodes: AtLeast 2
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int nCount = ((CListBox*)pWndCtrl)->GetCount();
   	/////////////////////////////////////////////// Minimum Required
   	int nMinCNode = 2; // m_nHowMany = 2
   	if(m_bClosed)
   		nMinCNode++;
   	////////////////////////	
   	if(nCount < nMinCNode)
   	{
   		CString str;
   		char buf[100];
   		sprintf(buf,"Minimum No. of Data Nodes Required = %d\n\
   		             No. of Data Nodes Selected         = %d",
   								nMinCNode,nCount	);
   		AfxMessageBox(str = buf);
   		return;
   	}
   	else
   	{
		/////////////////////////////////////////////////////////////////  ADD
		int nActiveIndex;
		CDrCurve* pAdd 	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
		SetInfoForDataBase(pAdd);
		/////////////////////////////////////////////////////////
		// Temporarily: Hide from drawing by View which will otherwise
		// 					access The list 
		//	and find pDrCurve which IS NOT  YET INTERPOLATED
		/////////////////////////////////////////////////////////
		pAdd->SetShow(FALSE);
		//////////////////////////
	} 
	///////////////
	CDialog::OnOK();
}

void CElg_LQC::OnCancel()
{
	if(m_pKVal)
	{
		delete [] m_pKVal;
		m_pKVal = NULL;
	}	
	if(m_pWVal)
	{
		delete [] m_pWVal;
		m_pWVal = NULL;
	}	
	if(m_pOSeg)
	{
		delete [] m_pOSeg;
		m_pOSeg = NULL;
	}	
	if(m_pODis)
	{
		delete [] m_pODis;
		m_pODis = NULL;
	}	
	////////////////////
	m_CurveID = "";
	////////////////////
	CDialog::OnCancel();
}

void CElg_LQC::FillListAllString_Pool()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMaxNodes>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == NODE)
			{ 
				CDrNode* pNode = (CDrNode*)pObject;
   				Nid   = (pNode->GetNodeCard())->id;
		    	((CListBox*)(pWndCtrl))->AddString(Nid);
			}			    
    	}
	} 
    
}
    
void CElg_LQC::FillListAllString_Curve()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Cid;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);
    if(nMaxCurves>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == CURVE)
			{ 
				CDrCurve* pCurve = (CDrCurve*)pObject;
   				Cid   = pCurve->GetObjectID();
		    	((CListBox*)(pWndCtrl))->AddString(Cid);
			}			    
    	}
	} 
    
}
    
void CElg_LQC::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}

void CElg_LQC::OnAutoKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoKn)
	{
		m_Typ_KN 	= KN_AUTO;
		m_bUnifKN	= FALSE;
		/////////////////////////////////////////////// Disable
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
	}
	else
	{
		/////////////////////////////////////////////// Enable
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
	}	
		
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnAutoWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoWt)
	{
		m_Typ_WT 	= WT_AUTO;
		m_bUnifWT	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnClosed()
{
    ////////////////////
//	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
	//////////////////////////////////////////////// Update	 
    int nData 		= ((CListBox*)(pWndCtrl))->GetCount();
    if(nData>=3)	// need to select atleast 3 points to close
    {
    	m_bClosed 	= !m_bClosed;
		m_nCurveSeg 	= m_bClosed? nData : nData - 1;
	}
	else
	{
		AfxMessageBox("You Need to Select\nAtleast 3 Nodes to Close !");
		m_bClosed		= FALSE; 
	}	
	if(m_bClosed)					
	{
		CComboBox* pCombo;	
		////////////////////////////////////////////// CLosed:Disable BoundaryCombos
	 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
   		pCombo->ResetContent();// ALL REMOVED
  		pCombo->EnableWindow(FALSE);	// disabled
		m_bLeftOn 	= FALSE;
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(FALSE);
        ///////////////////////////////////////////////
	 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT); 
   		pCombo->ResetContent();// ALL REMOVED
  		pCombo->EnableWindow(FALSE);	// disabled
		m_bRightOn 	= FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
        ///////////////////////////////////////////////
	}
	else
		OnSelchangeDegree(); // this will reset Combos according to ORDER		
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnUnifKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bUnifKN)
	{
		m_Typ_KN 	= KN_UNIFORM;
		m_bAutoKn	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnUnifWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bUnifWT)
	{
		m_Typ_WT 	= WT_UNIFORM;
		m_bAutoWt	= FALSE;
	}	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnNonuKn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_Knot	Dlg;
	///////////////////////// set Dialog data
	int nMax;
	BOOL bDistinct;
	///////////////
//											// This is for CIRR.cpp	
	nMax 		= m_nMaxDistinct;
	m_pKVal		= new double[nMax];
	bDistinct	= TRUE;
/*											// This is for CDRR.cpp	
	else	
	{
		nMax 		= m_nMaxTotal;
		m_pKVal		= new double[nMax];
		bDistinct	= FALSE;
	} 
*/					
	///////////////////////////////////
	Dlg.m_nMaxKnot	= nMax;
	Dlg.m_pKVal		= m_pKVal;
	Dlg.m_bDistinct = bDistinct;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_bUnifKN 	= FALSE;
		m_bAutoKn 	= FALSE;
		m_Typ_KN 	= KN_USER;
	}
	else		// Cancel
		delete [] m_pKVal;
	//////////////////////	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnNonuWt()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	CDlg_Wts	Dlg;
	///////////////////////// set Dialog data
	int nMax;
	///////////////
//											// This is for CIRR.cpp	
	nMax 		= m_nMaxDistinct;
	m_pWVal		= new double[nMax];
/*											// This is for CDRR.cpp	
	else	
	{
		nMax 		= m_nMaxTotal;
		m_pWVal		= new double[nMax];
	}
*/	
	///////////////////////////////////
	Dlg.m_nMaxWeight	= nMax;
	Dlg.m_pWVal			= m_pWVal;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_bUnifWT 	= FALSE;
		m_bAutoWt 	= FALSE;
		m_Typ_WT 	= WT_USER;
	}
	else		// Cancel
		delete [] m_pWVal;
	//////////////////////	
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnSelchangeDegree()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
 	CComboBox* pCombo;
 	pCombo = (CComboBox*)GetDlgItem(IDC_DEGREE);
   	int index = pCombo->GetCurSel();
   	if(index<0)
   		return;
   	////////////
	CString str;
	pCombo->GetLBText(index,str);
	/////////////////////////////////////////////
	for(int i=0;i<nDeg;i++)
	{
		if(Deg[i] == str)
		{
			m_nOrder = Ord[i];
			break;
		}	
	}
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
 	/////////////////////////////////////////////
    if(m_nOrder == 2)		// LINEAR
    {
   		pCombo->ResetContent();// ALL REMOVED
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		(GetDlgItem(IDC_BC_LEFT_ON))->EnableWindow(FALSE);
        ///////////////////////////////////////////////
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
     	/////////////////////////////////////////////// Enabled Windows ALL(RATIONAL)
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(TRUE);
		//////////////////////////////////////////////// always left to start with
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn = TRUE;
  		pCombo->EnableWindow(TRUE);	
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox
		////////////////////////////////////	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
       	pCombo->SetCurSel(0);	//
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
     	/////////////////////////////////////////////// Disabled Windows
		OnAutoKn();
		/////////////////////////////////////////////// 
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		////////////////////////////////////////////////
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn 	= TRUE;
		///////////////////
   		pCombo->EnableWindow(TRUE);	// enabled 
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
        pCombo->SetCurSel(0);	//
	}
	////////////////////////////////////////////////// Change RIGHTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
 	//////////////////////////////////////////////
    if(m_nOrder == 2)		// LINEAR
    {
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
		///////////////////////////////////////////////
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(FALSE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(FALSE);
		////////////////////////////////////////////////
   	}	 
   	else	
    if(m_nOrder == 3)		// QUADRATIC
    {
     	/////////////////////////////////////////////// Enabled Windows ALL(RATIONAL)
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(TRUE);
		(GetDlgItem(IDC_NONU_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_UNIF_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_AUTO_KN))->EnableWindow(TRUE);
		(GetDlgItem(IDC_KN_OPTION))->EnableWindow(TRUE);
		//////////////////////////////////////////////// always False to start with
   		pCombo->ResetContent();// ALL REMOVED 
  		pCombo->EnableWindow(FALSE);	
		m_bRightOn = FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
     	/////////////////////////////////////////////// Disabled Windows
		OnAutoKn();
		/////////////////////////////////////////////// 
		(GetDlgItem(IDC_NONU_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_UNIF_WT))->EnableWindow(FALSE);
		(GetDlgItem(IDC_AUTO_WT))->EnableWindow(FALSE);
		////////////////////////////////////////////////
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(TRUE);
		m_bRightOn 	= TRUE;
		///////////////////
   		pCombo->EnableWindow(TRUE);	// enabled 
   		pCombo->ResetContent();// ALL REMOVED 
		for(i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
        pCombo->SetCurSel(0);	//
	}
	////////////////////////////////////////////////// OverRide BCs
	if(m_bClosed)					
	{
		CComboBox* pCombo;	
		////////////////////////////////////////////// CLosed:Disable BoundaryCombos
	 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
   		pCombo->ResetContent();// ALL REMOVED
  		pCombo->EnableWindow(FALSE);	// disabled
		m_bLeftOn 	= FALSE;
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(FALSE);
        ///////////////////////////////////////////////
	 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT); 
   		pCombo->ResetContent();// ALL REMOVED
  		pCombo->EnableWindow(FALSE);	// disabled
		m_bRightOn 	= FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
        ///////////////////////////////////////////////
	}
	////////////////////////////////////////////////////// Update	
 	CListBox* pListCtrl	= (CListBox*)GetDlgItem(IDD_SELECTLIST);
   	int nData 			= pListCtrl->GetCount();
	m_nControls 		= nData + m_nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nMaxTotal			= nData + (2 * m_nOrder - 2);	// n + k + 1 = nData + (2k - 2)
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 

} 

void CElg_LQC::OnBcLeftOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
    // for LINEAR: everything is already Disabled
    /////////////////////////////////////////////
    if(m_nOrder == 4)		// CUBIC:keep BCs On
    {
    	m_bLeftOn = TRUE;
    	return;
    }
	/////////////////////	
 	CComboBox* pCombo;
	if(!m_bLeftOn)
	{
		////////////////////////////////////////////////// DISABLE LEFTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT);
 		//////////////////////////////////////////////
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(FALSE);
		////////////////////////////////////////////////// FILL RIGHTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
  		pCombo->EnableWindow(TRUE);	// Enabled
   		pCombo->ResetContent();// ALL REMOVED 
		for(int i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
		////////////////////////////////////
		int index;	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
        pCombo->SetCurSel(0);	//
        /////////////////////////////////////////////////
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(TRUE);
		m_bRightOn = TRUE;
		//////////////////
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnBcRightOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
    // for LINEAR: everything is already Disabled
    /////////////////////////////////////////////
    if(m_nOrder == 4)		// CUBIC:keep BCs On
    {
    	m_bRightOn = TRUE;
    	return;
    }
	/////////////////////	
 	CComboBox* pCombo;
	if(!m_bRightOn)
	{
		////////////////////////////////////////////////// DISABLE LEFTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_RIGHT);
 		//////////////////////////////////////////////
   		pCombo->ResetContent();// ALL REMOVED 
     	/////////////////////////////////////////////// Disabled Windows
  		pCombo->EnableWindow(FALSE);	// disabled
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
		////////////////////////////////////////////////// FILL RIGHTComboList
 		pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT);
  		pCombo->EnableWindow(TRUE);	// Enabled
   		pCombo->ResetContent();// ALL REMOVED 
		for(int i=0;i<nBC-1;i++)	// 								
 			pCombo->AddString(BCs[i]);
 		pCombo->AddString(BCs[nBC-1]+"...");	// TANGENT has DialogBox	
		////////////////////////////////////
		int index;	
		index = pCombo->FindStringExact(-1,"NOT_A_KNOT");	//"NOT_A_KNOT" 
       	pCombo->DeleteString(index);
		index = pCombo->FindStringExact(-1,"QUADRATIC");	//"QUADRATIC" 
       	pCombo->DeleteString(index);
        pCombo->SetCurSel(0);	//
        /////////////////////////////////////////////////
		GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(TRUE);
		m_bLeftOn = TRUE;
		//////////////////
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_LQC::OnSelchangeBcLeft()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
   	if(m_strBCL.Left(7) == "TANGENT")	// "TANGENT"
   	{
   		CDlg_Tang	Dlg;
   		if(Dlg.DoModal() == IDOK)
   		{
   			m_TanL.x = Dlg.m_dTanX;			
   			m_TanL.y = Dlg.m_dTanY;			
   			m_TanL.z = Dlg.m_dTanZ;			
   		}
   		else
   			m_strBCL = "AUTO";
   		
   	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CElg_LQC::OnSelchangeBcRight()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
   	if(m_strBCR.Left(7) == "TANGENT")	// "TANGENT"
   	{
   		CDlg_Tang	Dlg;
   		if(Dlg.DoModal() == IDOK)
   		{
   			m_TanR.x = Dlg.m_dTanX;			
   			m_TanR.y = Dlg.m_dTanY;			
   			m_TanR.z = Dlg.m_dTanZ;			
   		}
   		else
   			m_strBCR = "AUTO";
   		
   	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}
 
void CElg_LQC::SetInfoForDataBase(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pDListMgr;
	CDListMgr* pINodeList	= pDrObject->GetINodeList();
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nData,index;  
	CString Nid;
	CDrNode* pDrNode;
	////////////////////////////////////
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed);
    ////////////////////////////////////////////////////////////////////	
    nData = ((CListBox*)(pWndCtrl))->GetCount();
    /////////////////
	for (i=0;i<nData;i++)
	{
		((CListBox*)(pWndCtrl))->GetText(i,Nid);
		//////////////////////////////////
		pDListMgr	= pObjectMgr->GetObjectList(NODE);
		index = pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1);
		if(index>=0)
		{
			pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
			pINodeList->InsertObject(pDrNode);
			////////////////////////////////// save curve
			pDrNode->GetCurveList()->InsertObject(pDrObject);
		}
	}
	////////////////////////////////////////////////////////////// interpolation
	pDrObject->SetData_S(nData);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(nData);
	pDrObject->SetOrder_S(m_nOrder);				// k
	//////////////////////////////////////////////// Update	 
	m_nControls 	= nData + m_nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nCurveSeg 	= nData - 1;
	m_nMaxDistinct 	= nData;
	m_nMaxTotal		= nData + (2 * m_nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	if(m_bClosed)
	{
		m_nCurveSeg++;
		m_nMaxDistinct++;
		m_nMaxTotal++;
	}
    ////////////////////
//	m_Inter_C3.SetCurveType(CTyp);
//	pDrObject->SetCurveType(kind);
	pDrObject->SetKnotType_S(m_Typ_KN);
	pDrObject->SetWtType_S(m_Typ_WT);
	////////////////////////////////////////////////// Boundary
   	if(m_strBCL == BCs[0])	// 
   		m_BCL = BC_AUTO;
   	else	
   	if(m_strBCL == BCs[1])	// 
   		m_BCL = BC_CLAMPED;
   	else	
   	if(m_strBCL == BCs[2])	// 
   		m_BCL = BC_FREE;
   	else	
   	if(m_strBCL == BCs[3])	// 
   		m_BCL = BC_BESSEL;
   	else	
   	if(m_strBCL == BCs[4])	// 
   		m_BCL = BC_QUADRATIC;
   	else	
   	if(m_strBCL == BCs[5])	// 
   		m_BCL = BC_NOT_A_KNOT;
   	else	
   	if(m_strBCL.Left(7) == BCs[6])	// "TANGENT" On DialogListBox it is TANGENT...
   		m_BCL = BC_TANGENT;
	//////////////////////////
	pDrObject->SetBCL_S(m_BCL);
	/////////////////////////
   	if(m_strBCR == BCs[0])	// 
   		m_BCR = BC_AUTO;
   	else	
   	if(m_strBCR == BCs[1])	// 
   		m_BCR = BC_CLAMPED;
   	else	
   	if(m_strBCR == BCs[2])	// 
   		m_BCR = BC_FREE;
   	else	
   	if(m_strBCR == BCs[3])	// 
   		m_BCR = BC_BESSEL;
   	else	
   	if(m_strBCR == BCs[4])	// 
   		m_BCR = BC_QUADRATIC;
   	else	
   	if(m_strBCR == BCs[5])	// 
   		m_BCR = BC_NOT_A_KNOT;
   	else	
   	if(m_strBCR.Left(7) == BCs[6])	// "TANGENT" On DialogListBox it is TANGENT...
   		m_BCR = BC_TANGENT;
	/////////////////////////
	pDrObject->SetBCR_S(m_BCR);
	/////////////////////////
	if(m_BCL == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanL.x;
		tan.v[1] = m_TanL.y;
		tan.v[2] = m_TanL.x;
		tan.v[3] = 0;
		////////
		pDrObject->SetTanL_S(tan);
	}	
	if(m_BCR == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanR.x;
		tan.v[1] = m_TanR.y;
		tan.v[2] = m_TanR.x;
		tan.v[3] = 0;
		////////
		pDrObject->SetTanR_S(tan);
	}
	/////////////////////////////////////////////////////// Quadratic
	// Only One BC end is allowable:
	//	 ifLeft	- set tan.v for right 	 -99999.	
	//	 ifRight- set tan.v for left 	= -99999.
	/////////////////////////////////////////////
	if(3 == m_nOrder)
	{
		if(m_bLeftOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			pDrObject->SetTanR_S(tan);
		}	
		if(m_bRightOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			pDrObject->SetTanL_S(tan);
		}
	}		
	///////////////////////////////////////////////////////////////////
	if( m_Typ_WT == WT_USER)
		pDrObject->SetpWts_DT_S(m_pWVal);	// pointer
	else
		pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	/////////////	
	if( m_Typ_KN == KN_USER)
		pDrObject->SetpKnots_S(m_pKVal);	// pointer
	else
		pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	//////////////////////////////
	int nDim 		= 3;			// NonRational
	if(m_Typ_WT != WT_UNIFORM)
		nDim 		= 4;			// Homogeneous(Rational)
	pDrObject->SetnDim_S(nDim);
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(m_nMaxDistinct);
	pDrObject->SetnMKnots_S(m_nMaxTotal);
	////////////////////////////////////////
	int nCon_BZ	= (m_nOrder - 1) * m_nCurveSeg + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	/////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	////////////////////////////////////////////////////////////////////////// ReDistribute
	//////////////////////////////////////////////////////////////////////////
	//	NOTE:
	//
	//		If single Segment & Linear:
	//			Allow RATIO of First to Last, etc.
	///////////////////////////////////////////////////////////// Linear/Single Segment
	BOOL bCancel = TRUE;
	////////////////////
	if (m_nOrder == 2 && m_nCurveSeg == 1)
	{
		CDlg_CMsR	Dlg;
		////////////////
		Dlg.m_nElOut	= DEFAULT_UNIF;
		Dlg.m_Ratio		= m_Ratio;
		////////////////
		if(Dlg.DoModal() == IDOK)
		{
			bCancel		= FALSE;
			m_nMaxOSeg 	= Dlg.m_nElOut;	
			m_Ratio		= Dlg.m_Ratio;
			/////////////////////
			if(m_Ratio == 1.0)		
				m_bUnifOT = TRUE;
			else			
				m_bUnifOT = FALSE;
		}
		else
		{
			bCancel		= TRUE;
			m_Ratio		= 1.0;
			m_nMaxOSeg 	= DEFAULT_UNIF; 
			m_bUnifOT	= TRUE;
		}
		//////////////////////	
		pDrObject->SetRatio_S(m_Ratio);					
		pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
		///////////////////////////////////////// save
		//			 	in Inter_C1: make One Segment of Control Nodes
		//				with m_nMaxOSeg Output segment in it, i.e.,
		//				1 Segment in S-direction
		/////////////////////////////////////////////////////////////////////
		int i;
		//////
		if(!bCancel)
		{
			m_pOSeg = new int[1];
			/////////////////////
			m_pOSeg[0] = m_nMaxOSeg;
			/////////////////////
			if(m_bUnifOT)			// Uniform and OK
			{
				m_pODis = new double[m_nMaxOSeg+1];
				///////////////////////////////
				double delt;
				delt	= 1.0/m_nMaxOSeg;
				////////////////
				m_pODis[0] = 0.;
				////////////////
				for (i=1;i<=m_nMaxOSeg;i++)
				{
					m_pODis[i] = m_pODis[i-1] + delt;
				}
				/////////////////////
			}
			else								// NonUniform
			{
				m_pODis = new double[m_nMaxOSeg+1];
				/////////////////////////////////////////////////////////
				// NOTE:	allows Unequal Generation
				//		# of Segments = n + 1			= nSegs 
				//		SPACEs between pts. are:
				//			x, x+a, x+2a, x+3a, ..., x+na
				//		with
				//			x = 2/(segs*(ratio+1))
				//			a = (x*(ratio-1))/(segs-1)
				//
				//////////////////////////////////////////////////////////
				double x	= 2./(m_nMaxOSeg * (m_Ratio + 1));
				double a	= (m_nMaxOSeg == 1)?0.:(x * (m_Ratio-1))/(m_nMaxOSeg-1);
				//////////////////////////// save
				int i;
				//////
				m_pODis[0] = 0.;
				////////////////
				for (i=0;i<m_nMaxOSeg;i++)
				{
					///////////////////
					m_pODis[i+1] = m_pODis[i] + x + i * a;
					///////////////////
				}
			}
			//////////////////////////////////////////		 
			pDrObject->SetMaxOutSeg_S(m_nMaxOSeg);	// Number of Output Segments
			pDrObject->SetSegmentCount_S(1); 	// for Old Compatibility per patch
			pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
														// each Curve Segment
			pDrObject->SetDis_tPointer_S(m_pODis);	// Number of Outputs for
														// each Curve Segment
			////////////////////////////////////////////// Total Evaluation Pts
			int nOut = m_nMaxOSeg + 1;
			///////////////////////
			pDrObject->SetMaxOutPts_S(nOut);
			pDrObject->SetLongOutPts((long)nOut);
			////////////////////////////////////////////////
		}	
	}	
	///////////////////////////////////////////////////////////////// Other Cases
	if(bCancel)
	{
		CDlg_CMesh	Dlg;
		//////////////////////////// Fill Data
		Dlg.m_pDrCurve	= pDrObject; 
		Dlg.m_nSeg_DT	= m_nCurveSeg;	// L = nData - 1
		Dlg.m_nDefOSeg	= DEFAULT_UNIF;
		//////////////////////////// Memory 
		m_pOSeg = new int[m_nCurveSeg];		// L = nData - 1
		/////////////////////////////
		for(int i=0;i<m_nCurveSeg;i++) 
			m_pOSeg[i] = DEFAULT_UNIF;	// default = Uniform for All CurveSegs
		Dlg.m_pOSeg		= m_pOSeg;                             
		////////////////////////////
		if(Dlg.DoModal() == IDOK)
		{
			m_nMaxOSeg 	= Dlg.m_nMaxOSeg;	// for uniform OT only
			/////////////////////
			m_bUnifOT 	= Dlg.m_bUnifOT;
		}
		else
			m_nMaxOSeg 	= DEFAULT_UNIF;
		///////////////////////////////////////// save for Uniform
		if(m_bUnifOT)
		{
//			m_pOSeg = new int[m_nCurveSeg];
			///////////////////////////////
			for (i=0;i<m_nCurveSeg;i++)
			{
				m_pOSeg[i] = m_nMaxOSeg;
			}
		}
		//////////////////////////////////////////		 
		pDrObject->SetMaxOutSeg_S(m_nCurveSeg);	// Number of Output Segments
											// = nData - 1 = L = m_nCurveSeg
		pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
		//////////////////////////////////////////
		pDrObject->SetSegmentCount_S(m_nMaxOSeg); 	// for Old Compatibility
		////////////////////////////////////////////// Total Evaluation Pts
		int nOut = 0;
	
		for (i=0;i<m_nCurveSeg;i++)
			nOut += *(m_pOSeg+i);
		nOut++;
		////////////////////////////////
		pDrObject->SetMaxOutPts_S(nOut);
		pDrObject->SetLongOutPts((long)nOut);
	}
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////////// end of Module ///////////////////////////
