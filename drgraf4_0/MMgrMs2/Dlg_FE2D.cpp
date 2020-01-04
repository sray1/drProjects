// PlatProp.cpp : implementation file
//
#include "stdafx.h"


#include "glb_Objs.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// cards
#include "crdefine.h"
///////////////////// ElemObjs
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrPlate.h"
///////////////////// SpecObjs
#include "spdefine.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "Dlg_Plat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////
// CPlatProp dialog

CDlg_Plat::CDlg_Plat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Plat::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Plat)
	m_matID = "";
	m_nid_I = "";
	m_nid_J = "";
	m_nid_K = "";
	m_nid_L = "";
	m_propID = "";
	m_rid_I = "";
	m_rid_J = "";
	m_rid_K = "";
	m_rid_L = "";
	m_PlateType = "AxiSym";
	m_RefTemp = 0.0;
	m_Thk = 1.0;
	m_bDispMode = TRUE;
	m_SPRid = "";
	m_lid = "";
	//}}AFX_DATA_INIT
}

void CDlg_Plat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Plat)
	DDX_CBString(pDX, IDD_MID, m_matID);
	DDV_MaxChars(pDX, m_matID, 5);
	DDX_CBString(pDX, IDD_NID_I, m_nid_I);
	DDV_MaxChars(pDX, m_nid_I, 5);
	DDX_CBString(pDX, IDD_NID_J, m_nid_J);
	DDV_MaxChars(pDX, m_nid_J, 5);
	DDX_CBString(pDX, IDD_NID_K, m_nid_K);
	DDV_MaxChars(pDX, m_nid_K, 5);
	DDX_CBString(pDX, IDD_NID_L, m_nid_L);
	DDV_MaxChars(pDX, m_nid_L, 5);
	DDX_CBString(pDX, IDD_PID, m_propID);
	DDV_MaxChars(pDX, m_propID, 5);
	DDX_CBString(pDX, IDD_RID_I, m_rid_I);
	DDV_MaxChars(pDX, m_rid_I, 5);
	DDX_CBString(pDX, IDD_RID_J, m_rid_J);
	DDV_MaxChars(pDX, m_rid_J, 5);
	DDX_CBString(pDX, IDD_RID_K, m_rid_K);
	DDV_MaxChars(pDX, m_rid_K, 5);
	DDX_CBString(pDX, IDD_RID_L, m_rid_L);
	DDV_MaxChars(pDX, m_rid_L, 5);
	DDX_Text(pDX, IDC_REFTEMP, m_RefTemp);
	DDX_Text(pDX, IDC_THKNESS, m_Thk);
	DDV_MinMaxFloat(pDX, m_Thk, 1.e-006, 9999.);
	DDX_Check(pDX, IDC_DISP, m_bDispMode);
	DDX_CBString(pDX, IDD_SPRID, m_SPRid);
	DDV_MaxChars(pDX, m_SPRid, 5);
	DDX_CBString(pDX, IDD_LID, m_lid);
	DDV_MaxChars(pDX, m_lid, 5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Plat, CDialog)
	//{{AFX_MSG_MAP(CDlg_Plat)
	ON_BN_CLICKED(IDD_ADD, OnClickedAdd)
	ON_BN_CLICKED(IDD_DEL, OnClickedDel)
	ON_BN_CLICKED(IDD_EDIT, OnClickedEdit)
	ON_LBN_SELCHANGE(IDD_LIST, OnSelchangeList)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnClickedAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnClickedDel)
	ON_BN_DOUBLECLICKED(IDD_EDIT, OnClickedEdit)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_DISP, OnDispMode)
	ON_BN_DOUBLECLICKED(IDC_DISP, OnDispMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Plat message handlers

BOOL CDlg_Plat::OnInitDialog()
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
	CWnd* pWndCtrl;
//	pWndCtrl = GetDlgItem(IDD_PLATE_NSEG);
//	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	/////////////////////////////////////////////
	pDListMgr		= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes	= pDListMgr->GetSpecificObjectCount(NODE);//
	if (nMaxNodes<=0)
		return TRUE;
	/////////////////////////////////////////////////////
	FillListAllNodeIDs(1);  // nid_I
	FillListAllNodeIDs(2);  // nid_J
	FillListAllNodeIDs(3);  // nid_K
	FillListAllNodeIDs(4);  // nid_L
	////////////////////////////////
	pDListMgr		= pObjectMgr->GetObjectList(PLATE);
	int nMaxPlats 	= pDListMgr->GetSpecificObjectCount(PLATE);//
	if(nMaxPlats>0)
	{
		///////////////////////////////////////////////	
 		FillListAllString();          // filling Plat List
 		////////////////////
		int nActiveObjIndex = pObjectMgr->GetActiveObjectIndex();//notactive = -1
		CDrObject* pObject = (CDrObject*)(pDListMgr->GetObject(nActiveObjIndex));       // 
		if (pObject->GetObjectType() == (int)PLATE) 
			FillOthers(nActiveObjIndex);		// Active Plat
		else
			FillOthers(-1);           			// First Plat
		//////////////////////////////////////////////////////////////////////
		CString nid[MAX_NODES_PLAT];
		int nEnds = MAX_NODES_PLAT;
		///////////////
		nid[0] = m_nid_I; 
		nid[1] = m_nid_J; 
		nid[2] = m_nid_K; 
		nid[3] = m_nid_L;
		////////////////// 
		
		///////////////////////////////////////////// EndNids
		CString blank(' '),EndNids;
		EndNids	= nid[0]; 	
		for (int i=1; i < nEnds; i++)
			EndNids += blank + nid[i]; 
		///////////////////////////////////////////////////////////////////////
		pWndCtrl = GetDlgItem(IDD_LIST);
		int index = ((CListBox*)pWndCtrl)->FindStringExact(-1,EndNids);
		((CListBox*)pWndCtrl)->SetCurSel(index);
		//////////////////////////////////////// 
		pWndCtrl = GetDlgItem(IDD_NID_I);
		index = ((CComboBox*)pWndCtrl)->FindStringExact(-1,m_nid_I);
		((CComboBox*)pWndCtrl)->SetCurSel(index); 
		((CComboBox*)pWndCtrl)->SetFocus; 
	    ////////////////////////////////////////
		pWndCtrl = GetDlgItem(IDD_NID_J);
		index = ((CComboBox*)pWndCtrl)->FindStringExact(-1,m_nid_J);
		((CComboBox*)pWndCtrl)->SetCurSel(index);
	    ////////////////////////////////////////
		pWndCtrl = GetDlgItem(IDD_NID_K);
		index = ((CComboBox*)pWndCtrl)->FindStringExact(-1,m_nid_K);
		((CComboBox*)pWndCtrl)->SetCurSel(index);
	    ////////////////////////////////////////
		pWndCtrl = GetDlgItem(IDD_NID_L);
		index = ((CComboBox*)pWndCtrl)->FindStringExact(-1,m_nid_L);
		((CComboBox*)pWndCtrl)->SetCurSel(index);
	}
	//////////////////
	UpdateData(FALSE);
	//////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Plat::OnClickedAdd()
{
//       case IDD_ADD:
    ////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
    ///////////////////	
	if((!m_nid_I.GetLength())||(!m_nid_J.GetLength())||
	   (!m_nid_K.GetLength())||(!m_nid_L.GetLength())   )   // blank nIDs
	{
		AfxMessageBox("No Node Exists!!\nUse Cancel Button\nCreate Nodes First");
   		return;
   	} 
	//////////////////////////////////////////////////////////////////////
	int i,j,index;
	CString nid[MAX_NODES_PLAT];
	int nEnds = MAX_NODES_PLAT;
	///////////////
	nid[0] = m_nid_I; 
	nid[1] = m_nid_J; 
	nid[2] = m_nid_K; 
	nid[3] = m_nid_L;
	////////////////// 
	static char NodeEnds[] = {'I','J','K','L'};
	CString str;
	char buf[100];
	for (i = 0;i<nEnds-1;i++)
	{
		for(j = i+1;j<nEnds;j++)
		{	 
			if(nid[i] == nid[j])
			{
				sprintf(buf,"Node IDs for End: %c & End: %c must be different!!",
								NodeEnds[i],NodeEnds[j]);
				str = buf;
				AfxMessageBox(str);
   				return;
   			}
   		}
   	}
   	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	///////////////////////////////////////////////////////////////////////
	CString EndNids;  
	///////////////////////////////////////////// EndNids
	CString blank(' ');
	EndNids	= nid[0]; 	
	for ( i=1; i < nEnds; i++)
		EndNids += blank + nid[i]; 
	/////////////////////////////////////////// already exists
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
   	if(( i= pObjectMgr->GetObjectIndexfromKey(PLATE,EndNids,1)) >=0)
   	{
   		index = ((CListBox*)pWndCtrl)->GetCurSel();
		AfxMessageBox("Plate with these NodeIDs Already Exists !!\nUse Edit Button");
   		return;
	}
    ////////////////////////////////////////////////// Add Plate to DrObjectList 
	/////////////////////////////////////////////
	int nActiveIndex;
    CDrPlat* pAdd 	= (CDrPlat*)(pObjectMgr->AddToDataBase(nActiveIndex,PLATE));
    SetInfoForDataBase(pAdd);
    //////////////////////////////////////////////////////////////////////////////// Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,PLATE);
	///////////////////////////////////////////////
	index = ((CListBox*)pWndCtrl)->FindStringExact(-1,EndNids);
	((CListBox*)(pWndCtrl))->AddString(EndNids);
	((CListBox*)pWndCtrl)->SetCurSel(index); 
	////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
	///////////////////
	return;
}

void CDlg_Plat::OnClickedDel()
{
//       case IDD_DEL:
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PLATE);
	///////////////////////////////////////////////
	UpdateData(TRUE);
	///////////////////////////////////////////////////////////////////////
	CString EndNids;  
			
	CString blank(' ');
	EndNids = m_nid_I + blank + m_nid_J + blank + m_nid_K + blank + m_nid_L;
	////////////////////////////////////////////////////////////////////////
	int nMaxPlats;
	nMaxPlats = pDListMgr->GetSpecificObjectCount(PLATE);  
	if(nMaxPlats <= 0 )   // no Plat
	{
		AfxMessageBox("No Plate to Delete!!");
   		return;
   	} 
	//////////////////////////////////////////////////////	
//   	CDrPlat Plat;
	int i;
   	///////////////////////////
   	i = pObjectMgr->GetObjectIndexfromKey(PLATE,EndNids,1);
   	if(i<0)
   	{
   		AfxMessageBox("No Need to Delete !!\nPlate was Not saved");
   		return;
   	}		
	/////////////////////////////////////////////////////////////
	CString strDel = "Deleting Plate with ends\n" + m_nid_I + " & "+ m_nid_J +
										     " & "+ m_nid_K + " & "+ m_nid_L +
												"\nAre You Sure !!"; 
		if(AfxMessageBox(strDel,MB_YESNO) == IDNO)
		return;
	/////////////////////////////////////////////////////////////// DELETE
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	int index;
 	index = ((CListBox*)pWndCtrl)->FindStringExact(-1,EndNids);
	((CListBox*)(pWndCtrl))->DeleteString(index); 
	//////////////////////////////////////////////////////////////// DELETE
	pObjectMgr->DeleteFromDataBase(i, PLATE);
	/////////////////////////////
	nMaxPlats = pDListMgr->GetSpecificObjectCount(PLATE);
	if(nMaxPlats>0)
	{
    	((CListBox*)pWndCtrl)->SetCurSel(0);
    	OnSelchangeList();
    	((CListBox*)pWndCtrl)->GetText(0,EndNids); 
    	//////////////////////////////////////////////// change ActiveObjIndex
   		if((i = pObjectMgr->GetObjectIndexfromKey(PLATE,EndNids,1)) >=0)
			pObjectMgr->SetActiveObjectIndex(i);
   	    ////////////////////////////////////////////////
    	
    }
    else
    {
    	//////////////////////////////////////////////// change ActiveObjIndex
 		pObjectMgr->SetActiveObjectIndex(-1);
   	    ////////////////////////////////////////////////
	} 
	////////////////////
	UpdateData(FALSE);          //To Screen
	//////////////////// 
	return;
}

void CDlg_Plat::OnClickedEdit()
{
//      case IDD_EDIT:   
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PLATE);
	///////////////////////////////////////////// 
	UpdateData(TRUE);
	//////////////////
	int i,nMaxPlats;                   
	
	nMaxPlats = pDListMgr->GetSpecificObjectCount(PLATE);  
	if(nMaxPlats <= 0 )   // no Plate
	{
		AfxMessageBox("No Plate to Edit!!\nUse Add Button");
   		return;
   	}
   	/////////////////////////////////////////////////////////////////// 
	if((!m_nid_I.GetLength())||(!m_nid_J.GetLength())||
	   (!m_nid_K.GetLength())||(!m_nid_L.GetLength())   )   // blank nIDs
	{
		AfxMessageBox("No Node Exists!!\nUse Cancel Button\nCreate Nodes First");
   		return;
   	} 
	////////////////////////////////
	// for Triangular Element: K=L 
	// for too many noded elements with last 2 nodes that can be equal
	// do following for acceptability:
	// 1. store in an array all nodes from dialog
	// 2. for(i=0;i<max-2;i++)
	// 3  for(j=i+1;j<max;j++)
	// 4  compare (i==j) for validity		
	//////////////////////////////////
	// HERE we are checking individually!!	 
	if(m_nid_I == m_nid_J)
	{
		AfxMessageBox("Node IDs for End: I & End: J must be different!!");
   		return;
   	} 
	if(m_nid_I == m_nid_K)
	{
		AfxMessageBox("Node IDs for End: I & End: K must be different!!");
   		return;
   	} 
	if(m_nid_I == m_nid_L)
	{
		AfxMessageBox("Node IDs for End: I & End: L must be different!!");
   		return;
   	} 
	if(m_nid_J == m_nid_K)
	{
		AfxMessageBox("Node IDs for End: J & End: K must be different!!");
   		return;
   	} 
	if(m_nid_J == m_nid_L)
	{
		AfxMessageBox("Node IDs for End: J & End: L must be different!!");
   		return;
   	} 
	///////////////////////////////////////////////////////////////////////
	CString EndNids;  

	CString blank(' ');
	EndNids = m_nid_I + blank + m_nid_J + blank + m_nid_K + blank + m_nid_L;
	////////////////////////////////////////////////////////////////////////
//	CDrPlat Plat;
	///////////////////////////////////////////////
    if((i= pObjectMgr->GetObjectIndexfromKey(PLATE,EndNids,1)) <0)
    {
		AfxMessageBox("Plate does not Exist!!\nUse Add Button");
   		return;
   	}
	else
	{	
       ///////////////////////////////////////////////////// EDIT
		CDrPlat* pPlat = (CDrPlat*)pDListMgr->GetObject(i);    
    	SetInfoForDataBase(pPlat);
   		pDListMgr->EditObject(i,pPlat);
		////////////////////
		UpdateData(FALSE);			//TO  Screen(FALSE)    
   		///////////////////	
	}		
	////////    
	return;
}

void CDlg_Plat::OnOK()
{ 

	CDialog::OnOK();

} 

void CDlg_Plat::OnSelchangeList()
{
//      case IDD_LIST:
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PLATE);
	/////////////////////////////////////////////
	CString EndNids;  
	////////////////////////////
	int nMaxPlats = pDListMgr->GetSpecificObjectCount(PLATE);
	if(nMaxPlats <= 0) return;
	//////////////////////////
   	////////////////////
	UpdateData(TRUE);			//Get From Screen(TRUE)    
   	///////////////////	

	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
	    
    ((CListBox*)pWndCtrl)->GetText(index,EndNids); 
    
	int i;
	///////////////////////////////////////////////
   	if((i= pObjectMgr->GetObjectIndexfromKey(PLATE,EndNids,1)) <0)
   	{
    	MessageBeep(0); 
    	return;
	}
	else
	{    	
   		//////////////
   		FillOthers(i);     
   		//////////////
	}    	    
   	////////////////////
	UpdateData(FALSE);			//TO Screen(FALSE)    
   	///////////////////	
	
}
/*
void CDlg_Plat::OnEditupdatePipeLineId()
{ 

	/////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_PLATE_LINE_ID);
	
	int index;
   	CString EditString = 
   	index = ((CComboBox*)pComCtrlI)->GetCurSel();
   	
    ((CComboBox*)pComCtrlI)->GetLBText(index,m_nid_I);
   	index = ((CComboBox*)pComCtrlJ)->GetCurSel();
    ((CComboBox*)pComCtrlI)->GetLBText(index,m_nid_J);
	//////////////////
	/////////////////////////////////////////////
	m_LineID = (pPipe->GetPipeCard())->line_id;
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_LineID);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////

	// TODO: Add your control notification handler code here
	
}

void CDlg_Plat::OnSelchangePipeLineId()
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_Plat::OnKillfocusPipeLineId()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	m_LineID.MakeUpper();
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
	// TODO: Add your control notification handler code here
		
}
*/

void CDlg_Plat::OnDispMode()
{
	// TODO: Add your control notification handler code here
	m_bDispMode = !m_bDispMode;
	
}
////////////////////////////////////////////////////////////// HELPERS
void CDlg_Plat::FillOthers(int i)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PLATE);
	/////////////////////////////////////////////////////////
	// if   i<0, get First Plate
	//		>=0  get according to index
	///////////////////////////////////
	int index;
	if (i<0)
	{
		index = pDListMgr->GetObjectFirstIndex(PLATE);
	}
	else
		index = i;	
	CDrPlat* pPlat 	  = (CDrPlat*)(pDListMgr->GetObject(index));       // Plat 
	CWnd* pComCtrl;
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_NID_I);
	m_nid_I  = (pPlat->GetPlatCard())->nid[0];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_nid_I);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_NID_J);
	m_nid_J  = (pPlat->GetPlatCard())->nid[1];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_nid_J);
   	if(index>= 0)
	    ((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_NID_K);
	m_nid_K  = (pPlat->GetPlatCard())->nid[2];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_nid_K);
   	if(index>= 0)
	    ((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_NID_L);
	m_nid_L  = (pPlat->GetPlatCard())->nid[3];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_nid_L);
   	if(index>= 0)
	    ((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
//	pComCtrl = GetDlgItem(IDD_LINE_ID);
//	m_LineID = (pPlat->GetPlatCard())->line_id;
//   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_LineID);
//   	if(index>= 0)
//    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_MID);
	m_matID  = (pPlat->GetPlatCard())->mid;
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_matID);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_PID);
	m_propID = (pPlat->GetPlatCard())->pid;
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_propID);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_RID_I);
	m_rid_I  = (pPlat->GetPlatCard())->rid[0];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_rid_I);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_RID_J);
	m_rid_J  = (pPlat->GetPlatCard())->rid[1];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_rid_J);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_RID_K);
	m_rid_K  = (pPlat->GetPlatCard())->rid[2];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_rid_K);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
	pComCtrl = GetDlgItem(IDD_RID_L);
	m_rid_L  = (pPlat->GetPlatCard())->rid[3];
   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_rid_L);
   	if(index>= 0)
    	((CComboBox*)pComCtrl)->SetCurSel(index);
	/////////////////////////////////////////////
//	pComCtrl = GetDlgItem(IDD_STRESS_ID_I);
//	m_stressID_I = (pPlat->GetPlatCard())->sid_i;
//   	index    = ((CComboBox*)pComCtrl)->FindStringExact(-1,m_stressID_I);
//   	if(index>= 0)
//    	((CComboBox*)pComCtrl)->SetCurSel(index);
	////////////////////////////////////////////// Thro' data exchange
	m_Thk        = (pPlat->GetPlatCard())->Thkness;
	m_RefTemp    = (pPlat->GetPlatCard())->refTemp;

}

void CDlg_Plat::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PLATE);
	/////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString EndNids,NidI,NidJ,NidK,NidL;
	
	int nMaxPlats = pDListMgr->GetSpecificObjectCount(PLATE);
    if(nMaxPlats>0)
    {
		CDrObject* pObject;			       // Plate
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos); 
			if(pObject->GetObjectType() == (int)PLATE)
			{ 
				CDrPlat* pPlat = (CDrPlat*)pObject;
				//////////////////////////////////////////////////////////////////////
				CString nid[MAX_NODES_PLAT];
				int nEnds = MAX_NODES_PLAT;
				///////////////
				nid[0] = (pPlat->GetPlatCard())->nid[0]; 
				nid[1] = (pPlat->GetPlatCard())->nid[1]; 
				nid[2] = (pPlat->GetPlatCard())->nid[2]; 
				nid[3] = (pPlat->GetPlatCard())->nid[3];
				///////////////////////////////////////////// EndNids 
				int i;
				CString blank(' ');
				EndNids	= nid[0]; 	
				for ( i=1; i < nEnds; i++)
					EndNids += blank + nid[i]; 
				///////////////////////////////////////////////////////////////////////
				((CListBox*)(pWndCtrl))->AddString(EndNids); 
 		   	}
		} 		   	
	} 
    
}    
void CDlg_Plat::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_Plat::SetInfoForDataBase(CDrPlat* pPlat)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Plat
	/////////////////////////////////////////////////
	pPlat->SetObjectType((int)PLATE);
	pPlat->SetElemType((int)EL3D_OBJECT);              // globals.h
    pPlat->SetLevelType((int)LEVEL_GRAPA);          // globals
	/////////////////////////////////////////////////
	(pPlat->GetPlatCard())->nid[0]		= m_nid_I;
	(pPlat->GetPlatCard())->nid[1]		= m_nid_J;
	(pPlat->GetPlatCard())->nid[2]		= m_nid_K;
	(pPlat->GetPlatCard())->nid[3]		= m_nid_L;
	(pPlat->GetPlatCard())->Thkness		= m_Thk;
	(pPlat->GetPlatCard())->pid			= m_propID;
	(pPlat->GetPlatCard())->mid			= m_matID;
	(pPlat->GetPlatCard())->rid[0]		= m_rid_I;
	(pPlat->GetPlatCard())->rid[1]		= m_rid_J;
	(pPlat->GetPlatCard())->rid[2]		= m_rid_K;
	(pPlat->GetPlatCard())->rid[3]		= m_rid_L;
	(pPlat->GetPlatCard())->refTemp		= m_RefTemp; 
    ////////////////////////////////////////////////////////////////// TEMPORARY
//	m_PlateType = "AxiSym";
	(pPlat->GetPlatCard())->IDNum		= 4;   // temporarily//3=Membrane; 4=2D FEM
    (pPlat->GetPlatCard())->nCorners	= 4;   //3=triangular; 4=quadrilateral
    (pPlat->GetPlatCard())->nPlateType	= 1;   //1=AxiSym;2=Pl.Strain;3=Pl.Stress(2D FEM)
    for(int i=0;i<MAX_LOADS;i++)
    	(pPlat->GetPlatCard())->lid[i]	= m_lid;   //Loadcase A,B,C,D
    (pPlat->GetPlatCard())->sprid		= m_SPRid;   //stress print CodeID */
    //////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////
	pPlat->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pPlat->SetLayer(pLayer->GetCurrentLayer());
	///////////////////////////////////////////////////////// store node pointers 
	int index;
	//////////////////////////////////////////////////////////////////////
	CString nid[MAX_NODES_PLAT];
	int nEnds = MAX_NODES_PLAT;
	///////////////
	nid[0] = (pPlat->GetPlatCard())->nid[0]; 
	nid[1] = (pPlat->GetPlatCard())->nid[1]; 
	nid[2] = (pPlat->GetPlatCard())->nid[2]; 
	nid[3] = (pPlat->GetPlatCard())->nid[3];
	/////////////////////////////////////////////////////  
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
    for(i=0;i<nEnds;i++)
    {
		if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
		{
			CDrNode* pDrNode = (CDrNode*)pDListMgr->GetObject(index);
  			pPlat->GetNodeList()->InsertObject(pDrNode);
			//////////////////////////////// save Current Plate Pointer in Nodes
			pDrNode->GetElemList()->InsertObject(pPlat);
		}			
	
  	}	
	//////////////////////////
} 

void CDlg_Plat::FillListAllNodeIDs(int IorJ)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////////
	CWnd* pWndCtrl;
	if(IorJ == 1)
		pWndCtrl = GetDlgItem(IDD_NID_I);
	else if(IorJ == 2)
		pWndCtrl = GetDlgItem(IDD_NID_J); 
	else if(IorJ == 3)
		pWndCtrl = GetDlgItem(IDD_NID_K); 
	else if(IorJ == 4)
		pWndCtrl = GetDlgItem(IDD_NID_L); 
	//////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);//
	if (nMaxNodes<=0)
		return;
    if(nMaxNodes)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == NODE)
			{ 
				CDrNode* pNode = (CDrNode*)pObject;
	   			CString Nid     = (pNode->GetNodeCard())->id;
	   		    ((CComboBox*)(pWndCtrl))->AddString(Nid);
			}	   		     
    	}
	} 
    
}    
///////////////////////////////// End of Module ///////////////*
