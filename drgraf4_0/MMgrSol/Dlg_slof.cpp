// dlg_loft.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// cards
#include "Def_Card.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
#include "dlg_Slof.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1

/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft_S dialog


CDlg_Loft_S::CDlg_Loft_S(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Loft_S::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Loft_S)
	m_CID_1 	= "";
	m_CID_2 	= "";
	m_TotEl_1	= 0;
	m_TotEl_2	= 0;
	m_PatchID 	= "";
	m_nMesh 	= DEFAULT_UNIF;
	m_Ratio 	= 1;	//default
	//}}AFX_DATA_INIT
	m_bUnifOT 		= TRUE;
	/////////////////////// Memory
	m_pOSeg 		= NULL;
	m_pODis 		= NULL;
	///////////////////////
}

void CDlg_Loft_S::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Loft_S)
	DDX_CBString(pDX, IDC_CID_1, m_CID_1);
	DDX_CBString(pDX, IDC_CID_2, m_CID_2);
	DDX_Text(pDX, IDC_TOTEL_1, m_TotEl_1);
	DDX_Text(pDX, IDC_TOTEL_2, m_TotEl_2);
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Loft_S, CDialog)
	//{{AFX_MSG_MAP(CDlg_Loft_S)
	ON_CBN_SELCHANGE(IDC_CID_1, OnSelchangeCid1)
	ON_CBN_SELCHANGE(IDC_CID_2, OnSelchangeCid2)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft_S message handlers
BOOL CDlg_Loft_S::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CID_1);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_2);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatches	 = pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMaxPatches)
		FillListAllPatchIDs();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMaxCurves)
		FillListAllSolidIDs();   //  with Solids
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Loft_S::OnSelchangeCid1() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrPatch*	pDrPatch;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_1);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{
		pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
		pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
		if(m_SubType == PS_TRIANGLE)
		{
			int nOut	= pDrPatch->GetOut_S();
			m_TotEl_1	= nOut*(nOut+1)/2;			// No. of Vertices in ST plane
		}
		else
			m_TotEl_1	= pDrPatch->GetLongOutPts();// No. of Vertices in ST plane
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Loft_S::OnSelchangeCid2() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrPatch*	pDrPatch;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID_2);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{
		pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
		pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
		if(m_SubType == PS_TRIANGLE)
		{
			int nOut	= pDrPatch->GetOut_S();
			m_TotEl_2	= nOut*(nOut+1)/2;			// No. of Vertices in ST plane
		}
		else
			m_TotEl_2	= pDrPatch->GetLongOutPts();// No. of Vertices in ST plane
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_Loft_S::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	//	 Check first If Solid ID Selected
	if(m_PatchID == "")
   	{
   		AfxMessageBox("No Solid ID Selected\nPlease Select or Use Cancel");
   		return;
   	}
    ///////////////////////////////////////////////////////////////////////// Check T-dir Compatibility
	int index;
	CDrPatch* pDrCurve;
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(PATCH,m_CID_1,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Beginning Patch!\nPlease Select One from the List");
		return;
	}
	pDListMgr		= pObjectMgr->GetObjectList(PATCH);
	pDrCurve		= (CDrPatch*)(pDListMgr->GetObject(index));
	int nOut1		= m_TotEl_1;
	BOOL bClosed1	= pDrCurve->IsClosed_S();
	////////////////////////////////////////////////////////////////////////// Curve2
	index 			= pObjectMgr->GetObjectIndexfromKey(PATCH,m_CID_2,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Ending Patch!\nPlease Select One from the List");
		return;
	}
	pDrCurve		= (CDrPatch*)(pDListMgr->GetObject(index));
	int nOut2		= m_TotEl_2;
	BOOL bClosed2	= pDrCurve->IsClosed_S();
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		wsprintf(buf,"Patch MisMatch!\nBOTH PATCHES MUST HAVE SAME NUMBER OF NODES\nBeginning:\n\tNumber of Nodes = %d\nEnding:\n\tNumber of Nodes = %d",
			nOut1,nOut2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
/*
	////////////////////////////////////// Both must be closed or open
	if(bClosed1 != bClosed2)
	{
		CString str,str1,str2;
		str1 = (bClosed1)?"CLOSED":"OPEN";
		str2 = (bClosed2)?"CLOSED":"OPEN";
		LPTSTR buf = str.GetBuffer( 200 );
		wsprintf(buf,"Patch MisMatch!\nBOTH PATCHES SHOULD BE EITHER OPEN OR CLOSED\nBeginning: %s\nEnding: %s",
			str1,str2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
*/
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrSolid* pAdd 	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
    SetInfoForDataBase(pAdd);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrCurve which IS NOT  YET INTERPOLATED
	/////////////////////////////////////////////////////////
	pAdd->SetShow(FALSE);
	///////////////
	CDialog::OnOK();
}

void CDlg_Loft_S::OnCancel()
{
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
	m_PatchID = "";
	////////////////////
	CDialog::OnCancel();
}

void CDlg_Loft_S::FillListAllSolidIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(SOLID);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == SOLID)
			{ 
				CDrSolid* pCurve = (CDrSolid*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDD_LIST);
	   		    ((CListBox*)(pWndCtrl))->AddString(CID);
			}	   		     
    	}
	} 
    
}    

void CDlg_Loft_S::FillListAllPatchIDs()
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
				CDrPatch* pCurve = (CDrPatch*)pObject;
				if(pCurve->GetPatSubType() == m_SubType)		// make sure Right Stuff!!
				{
   					CString CID		 = pCurve->GetObjectID();
	   				/////////////////////////////////
					pWndCtrl = GetDlgItem(IDC_CID_1);
	   				((CComboBox*)(pWndCtrl))->AddString(CID);
	   				/////////////////////////////////
					pWndCtrl = GetDlgItem(IDC_CID_2);
	   				((CComboBox*)(pWndCtrl))->AddString(CID);
	   				/////////////////////////////////
				}
			}	   		     
    	}
	} 
    
}    

void CDlg_Loft_S::SetInfoForDataBase(CDrSolid* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr;
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetSolidProc(SP_LOFT2);
	pDrObject->SetSolidType(SO_TENSOR);
	////////////////////////////////////////// SubType
	if(m_SubType == PS_TRIANGLE)
		pDrObject->SetSolSubType(SS_PENTA);	//
	else
	if(m_SubType == PS_QUADRILAT)
		pDrObject->SetSolSubType(SS_HEXA);	// 
	//////////////////////////////////////////
	pDrObject->SetOrder_R(2);					// k = LINEAR for extrusion
	pDrObject->SetCurveType_R(CP_LINEAR);					// k = LINEAR for extrusion
	pDrObject->SetnDim_R(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_R(FALSE);					// k = LINEAR for extrusion
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetPatchID(m_CID_1,0);
	pDrObject->SetPatchID(m_CID_2,1);
	////////////////////////////////////////// Reciprocate
	int index;
	CDrPatch* pDrCurve;
	index 		= pObjectMgr->GetObjectIndexfromKey(PATCH,m_CID_1,1);
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	pDrCurve	= (CDrPatch*)(pDListMgr->GetObject(index));
	pDrCurve->GetSolidList()->InsertObject(pDrObject);
	pDrObject->GetPatchList()->InsertObject(pDrCurve);
	///
	index 		= pObjectMgr->GetObjectIndexfromKey(PATCH,m_CID_2,1);
	pDrCurve	= (CDrPatch*)(pDListMgr->GetObject(index));
	pDrCurve->GetSolidList()->InsertObject(pDrObject);
	pDrObject->GetPatchList()->InsertObject(pDrCurve);
	/////////////////////////////////////////////////
//	pDrObject->SetSegs(m_nSegs);
//	pDrObject->SetPatchType(PA_DUCT);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_R(SO_HORNER);		// Output Method
	///////////////////////////////////////////////////////////// ReDistribute 
	if(m_Ratio == 1.0)
		m_bUnifOT = TRUE;
	else			
		m_bUnifOT = FALSE;
	//////////////////////	
	pDrObject->SetRatio_R(m_Ratio);					
	pDrObject->SetUniform_R(m_bUnifOT);		// Output Distribution:
	///////////////////////////////////////// save
	//			 	in Inter_C1: make One Segment of Control Nodes
	//				with m_nMesh Output segment in it, i.e.,
	//				1 Segment in T-direction
	/////////////////////////////////////////////////////////////////////
	int i;
	//////
	m_pOSeg = new int[1];
	m_pODis = new double[m_nMesh+1];
	/////////////////////
	m_pOSeg[0] = m_nMesh;
	/////////////////////
	if(m_bUnifOT)			// Uniform and OK
	{
		///////////////////////////////
		double delt;
		delt	= 1.0/m_nMesh;
		////////////////
		m_pODis[0] = 0.;
		////////////////
		for (i=1;i<=m_nMesh;i++)
		{
			m_pODis[i] = m_pODis[i-1] + delt;
		}
		/////////////////////
	}
	else								// NonUniform
	{
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
		double x	= 2./(m_nMesh * (m_Ratio + 1));
		double a	= (m_nMesh == 1)?0.:(x * (m_Ratio-1))/(m_nMesh-1);
		//////////////////////////// save
		int i;
		//////
		m_pODis[0] = 0.;
		////////////////
		for (i=0;i<m_nMesh;i++)
		{
			///////////////////
			m_pODis[i+1] = m_pODis[i] + x + i * a;
			///////////////////
		}
	}
	//////////////////////////////////////////		 
	pDrObject->SetMaxOutSeg_R(m_nMesh);	// Number of Output Segments
	pDrObject->SetOutSegUnif_R(1); 	// for Old Compatibility per patch
	pDrObject->SetNum_tPointer_R(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_tPointer_R(m_pODis);	// Number of Outputs for
												// each Curve Segment
	////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMesh + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_R(nOut);
	pDrObject->SetOut_R(nOut);
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
