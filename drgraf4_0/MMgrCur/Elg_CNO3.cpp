// dlg_crc2.cpp : implementation file
//
////////////////////////////////////////////////////////////////////////////
//	THIS SUBROUTINE IS NOT READY FOR USE: SEE COMMENT ON SetInfoForDataBase
////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "3DMath.h"
#include "XForm.h"

//#include "EDlgMgr.h"

//#include "Def_Lims.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
////////////////////
#include "Elg_CNO3.h"	// Circle by 3 Nodes on the Circumference

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	5
/////////////////////////////////////////////////////////////////////////////
// CElg_CNO3 dialog


CElg_CNO3::CElg_CNO3(CDrCurve* pDrCurve, CWnd* pParent /*=NULL*/)
	: CDialog(CElg_CNO3::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CElg_CNO3)
	m_CurveID	= "";
	m_Ratio 	= 1;
	m_nMesh 	= DEFAULT_UNIF;
	m_bClosed 	= FALSE;
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	m_dAngSpec	= 90.0;
	//}}AFX_DATA_INIT
	//////////////////////////
	m_pDrCurve	= pDrCurve;
	//////////////////////////
	m_bArc		= TRUE;
	m_bUnifOT 	= TRUE;
	/////////////////////// Memory
	m_pOSeg 	= NULL;
	///////////////////////
	
}

void CElg_CNO3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElg_CNO3)
	DDX_CBString(pDX, IDC_CID, m_CurveID);
	DDX_Text(pDX, IDC_ELOUT_RATIO2, m_Ratio);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	DDX_Text(pDX, IDC_ANG_END, m_dAngSpec);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CElg_CNO3, CDialog)
	//{{AFX_MSG_MAP(CElg_CNO3)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_CLICKED(IDC_ANGSPEC, OnAngspec)
	ON_BN_DOUBLECLICKED(IDC_ANGSPEC, OnAngspec)
	ON_BN_CLICKED(IDC_ARC, OnArc)
	ON_BN_DOUBLECLICKED(IDC_ARC, OnArc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CElg_CNO3 message handlers
BOOL CElg_CNO3::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	Init();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString_Pool();   // only with Nodes
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllString_Curve();   // only with Curves
	////////////////////////////////////////// Focus
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
	pWndCtrl->SetFocus();
	///////////////////////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CElg_CNO3::Init()
{
	m_CurveID	= m_pDrCurve->GetObjectID();
	m_Ratio 	= m_pDrCurve->GetRatio_S();
	m_nMesh 	= m_pDrCurve->GetMaxOutSeg_S();
	m_bClosed 	= m_pDrCurve->IsClosed_S();
	m_SegAngle 	= m_pDrCurve->GetSegAngle_S();	
	m_bAutoSeg 	= TRUE;
	m_dAngSpec	= m_pDrCurve->GetTheta_S();
	//////////////////////////
	m_bArc		= m_pDrCurve->IsArcType();
	m_bUnifOT 	= m_pDrCurve->IsUniform_S();
	////////////////////////////// Memory
	m_pOSeg 	= m_pDrCurve->GetNum_tPointer_S();
	m_pODis		= m_pDrCurve->GetDis_AngPointer_S();
	////////////////////////////// Fill Select List
	FillListAllString_Select();
	//////////////////////////////////////////////////// Disable SegAngle
	GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);	
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_ARC))->SetCheck(m_bArc);
	((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);	
	////////////////////////////////////////// Select
	if(m_bClosed)
	{
		GetDlgItem(IDC_ARC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANGSPEC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
		////////////////////////////////////////// UnCheck
		((CButton*)GetDlgItem(IDC_ARC))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
	}
	else
	if(m_bArc) 
	{
		////////////////////////////////////////// Select
		((CButton*)GetDlgItem(IDC_ARC))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);	
	}
	else
	{
		GetDlgItem(IDC_ARC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANGSPEC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
		////////////////////////////////////////// Check AngleSpecified
		((CButton*)GetDlgItem(IDC_ARC))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(TRUE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);	
	}
}

void CElg_CNO3::OnDel()
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
	//////////////////////////////////////////////////
	if(nData<3)
		m_bClosed	= FALSE; 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnAdd()
{
	// Add Current selction of POOLLIST to SELECTLIST	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////////// Only 3 Nodes Required for Circle
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int nData 		= ((CListBox*)(pWndCtrl))->GetCount();
    if(nData>=3)	// 
	{
		AfxMessageBox("You may Select Exactly 3 Nodes\nTo Create Circle or Circcular Arc !");
		return; 
	}
	////////////////////////////////////////////////	
	pWndCtrl = GetDlgItem(IDD_POOLLIST);
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
	pWndCtrl 		= GetDlgItem(IDD_SELECTLIST);
    nData 			= ((CListBox*)(pWndCtrl))->GetCount();
	//////////////////////////////////////////////////
	if(nData<3)
		m_bClosed	= FALSE; 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    /////////////////////////////////////////////// Curve ID
   	if("" == m_CurveID)
   	{
   		AfxMessageBox("Please Select a Circle ID");
   		return;
   	}
	/////////////////////////////////
	//	 Check first If Adequate Number of DataNodes: AtLeast 2
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int nCount = ((CListBox*)pWndCtrl)->GetCount();
   	/////////////////////////////////////////////// Minimum Required
   	int nMinCNode = 3; // m_nHowMany = 3
   	////////////////////////	
   	if(nCount != nMinCNode)
   	{
   		CString str;
   		char buf[100];
   		sprintf(buf,"Exact No. of Nodes Required\t= %d\
   					\nNo. of Data Nodes Selected\t = %d",nMinCNode,nCount	);
   		AfxMessageBox(str = buf);
   		return;
   	}
	/////////////////////////////////////////////// Check
	if(m_bClosed)
	{
		if(m_nMesh<3)
		{
			AfxMessageBox("Need atleast 3 Elements!");
			/////////////////
			CWnd* pWndCtrl = GetDlgItem(IDC_ELOUT_SEG);
			pWndCtrl->SetFocus();
			/////////////////////
			return;
		}
	}
	/////////////////////////////////////////////////////////////////  Edit
    SetInfoForDataBase(m_pDrCurve);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrCurve which IS NOT  YET INTERPOLATED
	/////////////////////////////////////////////////////////
	m_pDrCurve->SetShow(FALSE);
	///////////////
	CDialog::OnOK();
}

void CElg_CNO3::OnCancel()
{
	if(m_pOSeg)
	{
		delete [] m_pOSeg;
		m_pOSeg = NULL;
	}	
	////////////////////
	m_CurveID = "";
	////////////////////
	CDialog::OnCancel();
}

void CElg_CNO3::FillListAllString_Select()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CDListMgr* pINodeList	= m_pDrCurve->GetINodeList();
	CWnd* pWndCtrl			= GetDlgItem(IDD_SELECTLIST);
	CString Nid;
	
	int nMaxNodes = pINodeList->GetCount();
    if(nMaxNodes<=0)
		return;
	////////////////////////////////////
	CDrObject* pObject;			       

	POSITION pos = pINodeList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pINodeList->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
			if(!((pNode->GetNodeCard())->bnid_c))             // Only with Data Nodes
			{
   				Nid   = (pNode->GetNodeCard())->id;
		    	((CListBox*)(pWndCtrl))->AddString(Nid);
		    }	 
		}			    
   	}
} 
    
void CElg_CNO3::FillListAllString_Pool()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMaxNodes<=0)
		return;
	////////////////////////////////////
	CDrObject* pObject;			       

	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
			if(!((pNode->GetNodeCard())->bnid_c))             // Only with Data Nodes
			{
   				Nid   = (pNode->GetNodeCard())->id;
		    	((CListBox*)(pWndCtrl))->AddString(Nid);
		    }	 
		}			    
   	}
} 
    
void CElg_CNO3::FillListAllString_Curve()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	//////////////////////////
	CString Cid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);
    if(nMaxCurves<=0)
    	return;
    //////////////////////////////////////////////////////////	
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
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}
    
void CElg_CNO3::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}

void CElg_CNO3::OnClosed()
{
    ////////////////////
//	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	//////////////////////////////////////////////// Update	 
   	m_bClosed 	= !m_bClosed;
	////////////////////////////////////////// Select
	if(m_bClosed)
	{
		GetDlgItem(IDC_ARC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANGSPEC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
		////////////////////////////////////////// UnCheck
		((CButton*)GetDlgItem(IDC_ARC))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
	}
	else
	{
		GetDlgItem(IDC_ARC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANGSPEC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
		////////////////////////////////////////// Check Arc
		((CButton*)GetDlgItem(IDC_ARC))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
		GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);	
	}
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnAngspec() 
{
	m_bClosed	= FALSE;
	m_bArc		= FALSE;
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_ARC))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(TRUE);
	GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);	
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnArc() 
{
	m_bClosed	= FALSE;
	m_bArc		= TRUE;
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_ARC))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);	
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnAutoSeg()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoSeg)
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
	else	
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(TRUE);
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CNO3::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

int CElg_CNO3::SetInfoForDataBase(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pINodeList	= pDrObject->GetINodeList();
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nData,index;  
	CString Nid;
	CDrNode* pDrNode;
	////////////////////////////////////
//    pDrObject->SetObjectType((int)CURVE);
//    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
//    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed);
    /////////////////////////////////////////////////////////////// Rmove & Disconnect Old Relation
    nData = pINodeList->GetCount();
	///////////////////////////////
	for (i=0;i<nData;i++)
	{
		POSITION pos	= pINodeList->FindIndex(i);
		pDrNode			= (CDrNode*)(pINodeList->GetAt(pos));
		///////////////////////////////////////////////////// Remove Node
		pINodeList->RemoveObject(nData - 1 - i);
		///////////////////////////////////////////////////// Disconnect curve
		index			= pDrNode->GetCurveList()->GetObjectIndex(pDrObject);
		pDrNode->GetCurveList()->RemoveObject(index);
	}
	/////////////////////////////////////////////////////////////// Now Save
    nData = ((CListBox*)(pWndCtrl))->GetCount();
    /////////////////
	for (i=0;i<nData;i++)
	{
		((CListBox*)(pWndCtrl))->GetText(i,Nid);
		//////////////////////////////////
		index = pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1);
		if(index>=0)
		{
			CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(NODE);
			pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
			pINodeList->InsertObject(pDrNode);
			////////////////////////////////// save curve
			pDrNode->GetCurveList()->InsertObject(pDrObject);
		}
	}
	////////////////////////////////////////////////////////////// interpolation
//	pDrObject->SetInputType(2);		// 3 Nodes on Circumference 
	//////////////////////////////////
	pDrObject->SetMaxINodes_S(nData);
	///////////////////////////////////
	int nOrder = 3;// k = 3 for Circle
	pDrObject->SetOrder_S(nOrder);				// k = 3 for Circle
//	pDrObject->SetCurveType_S(CP_CIRCLE);
	pDrObject->SetSegAngle_S(m_SegAngle);
	///////////////////////////////////////////////////////////////////
//	int nDim	= 4;			// Homogeneous(Rational)
//	pDrObject->SetnDim_S(nDim);
	///////////////////////////////////////////////////////////////////////////////
	// FROM HERE ON UNDER: EVERYTHING NEEDS TOBE OVERVIEWED FOR EDITING
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////// ReDistribute 
//	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	/////////////////////////////////////
	if(m_Ratio == 1.0)		
		m_bUnifOT = TRUE;
	else			
		m_bUnifOT = FALSE;
	//////////////////////	
	pDrObject->SetRatio_S(m_Ratio);					
	pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
	///////////////////////////////////////// save
	// if
	//		 Uniform:
	//			 	make As Many Segment of Control Nodes
	//				as Close to SegAng(Default=120) with total of m_nMesh Output segment
	//				in all of them i.e.,
	//				nSegs = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				variable Angles are stored in m_pODis;
	//				m_pONum containing Number of Mesh for each CurveSeg
	//		 NonUniform:
	//			 	make m_nMesh Segments of Control Nodes
	//				with 1 Output segment in each, i.e.,
	//				m_nMesh many CurveSeg in S-direction
	//				nSegs = m_nMesh = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				Total Angle is stored in m_pODis[0];
	//				m_pONum[0] containing Number of Mesh for the Patch
	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// find  and SetUp Angle, Radius & Normal
	//////////////////////////////////////
	SetAdditionalInfo(pDrObject, &m_dAng);
	////////////////////////////////////// if Closed, set angle to 360
	if(m_bClosed)
		m_dAng = 360.;
	////////////////////////////////////// if Angle Specified, Override angle
	if(!m_bArc)
		m_dAng = m_dAngSpec;
	/////////////////////////
	BOOL bClosed;
	if(m_dAng<0.)
		m_dAng = 0.;
	if(m_dAng>360.)
		m_dAng = 360.;
	double dAng = m_dAng;
	//////////////////////////////// Closed ?
	if(dAng == 360)
		bClosed = TRUE;
	else
		bClosed = FALSE;
	//////////
	pDrObject->SetArcType(m_bArc);	// for later editing		
	pDrObject->SetTheta_S(m_dAng);		
	pDrObject->SetClosed_S(bClosed);
	////////////////////////////////
	int nSegs;
	//////////////////////////////////////////////////////// Uniform
	if(m_bUnifOT)						// Uniform
	{
		// Max Angle for each Patch Segment = 120;
		// for stability
		////////////////////////////////////////// <=m_SegAngle:One Curve 
		if(dAng<= m_SegAngle)
		{
			nSegs = 1;
			//////////////////////////// Memory
			m_pOSeg = new int[nSegs];
			m_pODis = new double[nSegs];
			//////////////////////////// save
			m_pOSeg[0] = m_nMesh;
			m_pODis[0] = dAng;
			/////////////////////
		}
		////////////////////////////////////////// >m_SegAngle:Many Curves 
		else
		{
			int		nTimes,nMesh,nRem,i;
			double	dAngInc,dSegAng;
			////////////////
			dAngInc	= dAng/m_nMesh; // assume dAngInc ALWAYS <=120
			if(dAngInc>120)
			{
				AfxMessageBox("Error:\nToo Few Number of Elements!");
				/////////////////////
				return -1;
			}
			nTimes	= (int)(m_SegAngle/dAngInc);
			dSegAng	= nTimes * dAngInc;	// get biggest possible angle<=m_SegAngle
			nSegs	= (int)(dAng/dSegAng);
			nMesh	= nSegs*nTimes;
			nRem	= m_nMesh%nMesh;
			////
			if(nRem)
				nSegs++;
			//////////////////////////// Memory
			m_pOSeg = new int[nSegs];
			m_pODis = new double[nSegs];
			//////////////////////////// save
			for(i=0;i<nSegs;i++)
			{
				///////////////
				m_pOSeg[i] = nTimes;
				m_pODis[i] = dSegAng;
				/////////////////////
			}
			//////////////////////////// adjust  the Last one
			if(nRem)
			{
				int nSeg1 = nSegs -1;
				/////////////////////
				m_pOSeg[nSeg1] = m_nMesh	- nTimes * nSeg1;
				m_pODis[nSeg1] = dAng		- dSegAng* nSeg1;
				/////////////////////
			}
		}
	}
	//////////////////////////////////////////////////////// NonUniform
	else
	{
		nSegs = m_nMesh;
		//////////////////////////// Memory
		m_pOSeg = new int[nSegs];
		m_pODis = new double[nSegs];
		/////////////////////////////////////////////////////////
		// NOTE:	allows Unequal Generation
		//		# of Segments = n + 1			= nSegs 
		//		SPACEs between pts. are:
		//			x, x+a, x+2a, x+3a, ..., x+na
		//		with
		//			x = (2*theta)/(segs*(ratio+1))
		//			a = (x*(ratio-1))/(segs-1)
		//
		//////////////////////////////////////////////////////////
		double x	= (2 * dAng)/(nSegs * (m_Ratio + 1));
		double a	= (nSegs == 1)?0.:(x * (m_Ratio-1))/(nSegs-1);
		//////////////////////////// save
		int i;
		//////
		for (i=0;i<nSegs;i++)
		{
			m_pOSeg[i] = 1;	// one Element in each
			double angle = x + i * a;
			/////////////////////////
			if(angle>120)
			{
				AfxMessageBox("Error:\nToo Few Number of Elements!");
				/////////////////////
				return -1;
			}
			///////////////////
			m_pODis[i] = angle;
			///////////////////
		}
	}
	/////////////////////
	pDrObject->SetMaxOutSeg_S(m_nMesh);		// Total Number of Output Segments
			/////////////////////////////////////// Uniform needed for Triangular Patch
//	pDrObject->SetSegmentCount_S(nSegs); 	// # of Curves ( B-Spline Segs)
//	pDrObject->SetOutSegUnif_S(m_nMaxOSeg); 	// for Old Compatibility
	//////////////////////////////////////////		 
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	pDrObject->SetNum_tPointer_Ex_S(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_AngPointer_S(m_pODis);// Number of Angles for
											// Bezier Control Pts. Generation
    ////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMesh + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////
	int nCon_BZ	= (nOrder - 1) * nSegs + 1;	// (k-1) * L + 1 , Open
	if(bClosed)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	////////////////////////////////////////////////////////////////////// Mesh(Output)
	nData			= nSegs + 1;
	//////////////////////////////////////////////// Update	 
	pDrObject->SetData_S(nData);		// Generated: # of Data
	pDrObject->SetData_Ex_S(nData);		// Adjusted# of Data for Conics(Circle) 
	////////////////////////////
	int		nControls,nCurveSeg,nMaxDistinct,nMaxTotal;
	///////////////////////////////////////////////////
	nControls 	= nData + nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	nCurveSeg 	= nData - 1;					// L
	nMaxDistinct 	= nData;
	nMaxTotal		= nData + (2 * nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	if(bClosed)
	{
		nCurveSeg++;
		nMaxDistinct++;
		nMaxTotal++;
	}
    ////////////////////
	pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	/////////////	
	pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	//////////////////////////////
	pDrObject->SetnCon_BS_S(nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(nMaxDistinct);
	pDrObject->SetnMKnots_S(nMaxTotal);
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return 0;
	
}
 
int CElg_CNO3::SetAdditionalInfo(CDrCurve* pDrCurve, double* pTheta)
{

	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	pWORLD pData	 		= NULL;
	pWORLD pDat_Ex 			= NULL;
    ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCElg_CNO3::SetInfoForDataBase_Ex_1");
		return -1;
	}
	////////////////////////////////////////////// Set Data
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius;
	Calc_C_R_Normal(pData, &Center, &Radius, &Normal);
	//////////////////////////////////////////// save
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	////////////////////////////////////////////////////////// Central Angles
	*pTheta = Calc_CentralAngles(pData,Center,Radius);
	///////////////////////////////////////////////////////// # of Spline & Bezier Controls
	return 0;
}

int CElg_CNO3::SetUpINodes(CDListMgr* pList,pWORLD inData,int nData)
{

	int k;
	///////////
    if(nData<=0)
    	return -1;
    ///////////////////////
    k = -1;
    double x,y,z;
    //////////////	
	POSITION pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject( pos);
		k++;
		x = (pNode->GetNodeCard())->x;
		y = (pNode->GetNodeCard())->y;
		z = (pNode->GetNodeCard())->z;
		inData[k].x = x;
		inData[k].y = y;
		inData[k].z = z;
	}
	///////////
	if(k != (nData-1))
		return -1;
	else
		return 0;
	/////////////		 
}

int CElg_CNO3::Calc_C_R_Normal(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal)
{
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////// Translate Center & DOld to Origin
	XForm.Translate(pRot, -Data[0].x, -Data[0].y, -Data[0].z, XF_REPLACE);	
	////////////
	WORLD a,b,c;
	XForm.Transform(&Data[0], &a, pRot);
	XForm.Transform(&Data[1], &b, pRot);
	XForm.Transform(&Data[2], &c, pRot);
	//////////////////////////////////////// midPts
	WORLD mid1,mid2;
	Math3D.Avg3DPts(&a, &b, &mid1);
	Math3D.Avg3DPts(&b, &c, &mid2);
	//////////////////////////////////////// Normal to plane of Circle
	WORLD wN;
	WORLD rab,rac;
	Math3D.Sub3DPts(&b, &a, &rab);
	Math3D.Sub3DPts(&c, &a, &rac);
	Math3D.Cross3DPts(&rab,&rac,&wN);
	///////////////////////////////// Save
	Normal->x = wN.x;
	Normal->y = wN.y;
	Normal->z = wN.z;
	//////////////////////// Normalize
	Math3D.Normalize(Normal,Normal);
	//////////////////////////////////////// Rotation Mat: wN->Z-axis/rab->Y-Axis
	Math3D.GetIdentityMATRIX(pRot);
	XForm.VRCtoWORLDRotationMATRIX(pRot,&wN,&rab);	
	//////////////////////////////////////// Change Effectively to 2D
	WORLD aBar,bBar,cBar,mid1Bar,mid2Bar;
	XForm.Transform(&a, &aBar, pRot);
	XForm.Transform(&b, &bBar, pRot);
	XForm.Transform(&c, &cBar, pRot);
	XForm.Transform(&mid1, &mid1Bar, pRot);
	XForm.Transform(&mid2, &mid2Bar, pRot);
	///////////////////////////////////////
	WORLD Center2;
	double m2Bar,b1Bar,b2Bar;
//	m1Bar = 0;										// 2D slope of ab chord bisector 
	if((cBar.y-bBar.y) == 0.)						// ab perpendicular to ac
	{
		Center2.x 	= mid2Bar.x;	 
		Center2.y 	= mid1Bar.y;
	}
	else
	{	 
		b1Bar 		= mid1Bar.y;						// 2D intercept of ab chord bisector
		m2Bar 		= (bBar.x-cBar.x)/(cBar.y-bBar.y);	// 2D Slope of bc chord bisector
		b2Bar 		= mid2Bar.y - m2Bar*mid2Bar.x;		// 2D intercept of ab chord bisector
		//////////////////////////////////////
		Center2.y 	= b1Bar;
		Center2.x 	= (Center2.y-b2Bar)/m2Bar;	 
	}
	/////////////////		 
	Center2.z 	= 0.;
	//////////////////////////////////////// Transform Center to 3D & Translate Back 
	Math3D.TransposeMATRIX(pRot);
	XForm.Transform(&Center2, Center, pRot);
	///////////////////////////////
	Math3D.GetIdentityMATRIX(pRot);
	XForm.Translate(pRot, Data[0].x, Data[0].y, Data[0].z, XF_REPLACE);	
	XForm.Transform(Center, &Center2, pRot);
	Center->x = Center2.x;
	Center->y = Center2.y;
	Center->z = Center2.z;
	//////////////////////////////////////// Radius
	WORLD rVec;
	Math3D.Sub3DPts(&Data[0], Center, &rVec);
	*Radius = sqrt(rVec.x*rVec.x + rVec.y*rVec.y +rVec.z*rVec.z);
	/////////
	return 0;

}

double CElg_CNO3::Calc_CentralAngles(pWORLD Data, WORLD Center, double Radius)
{
	// Compute Phi and Si in degrees: Should be called from Pre_Interpolate
	///////////////
	C3DMath	Math3D;
	double pi180 = 180./acos(-1.0);
	///////////////////////////////////////
	WORLD rCenA,rCenB,rCenC;
	Math3D.Sub3DPts(&Data[0], &Center, &rCenA);
	Math3D.Sub3DPts(&Data[1], &Center, &rCenB);
	Math3D.Sub3DPts(&Data[2], &Center, &rCenC);
//	lCenC = Math3D.Len3DPts(&rCenC);
	///////////////////////////////////////////
	double Norm12	= Radius * Radius;
	double cosPhi	= (Math3D.Dot3DPts(&rCenA,&rCenB))/Norm12;
	double cosSi	= (Math3D.Dot3DPts(&rCenB,&rCenC))/Norm12;
	////////////
	cosPhi			= acos(cosPhi) * pi180;
	cosSi			= acos(cosSi)  * pi180;
	/////////////////
	double theta 	= cosPhi + cosSi;
	/////////
	return theta;
}
////////////////////////////////////// end of Module ///////////////////////////
