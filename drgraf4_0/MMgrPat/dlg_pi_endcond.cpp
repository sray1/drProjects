// Dlg_EndTan.cpp : implementation file
//

#include "stdafx.h"

#include "3DMath.h"

#include "UserMsg.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_Mous.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrPatch.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
//////////////////////////
#include "Dlg_Tang.h"
#include "BasePage.h"
#include "Dlg_PI_EndCond.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////
	static CString IsoDir[]	= {"Iso_U","Iso_V"};
	static CString BCs[] 	= {	"AUTO","CLAMPED","FREE","BESSEL","QUADRATIC",
								"NOT_A_KNOT","TANGENT"};
	static int nBC 			= sizeof(BCs)/sizeof(BCs[0]);
	static CString TWs[] 	= {	"AUTO","ZERO","BESSEL","ADINI","SPLINE",
								"ENERGY","USER"};
	static int nTW 			= sizeof(TWs)/sizeof(TWs[0]);
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_EndCond dialog

IMPLEMENT_DYNCREATE(CDlg_PI_EndCond, CBasePage)

CDlg_PI_EndCond::CDlg_PI_EndCond(): CBasePage()
{
	m_bCornerMode	= 0;
	m_bEditMode = 0;
}

CDlg_PI_EndCond::CDlg_PI_EndCond(CWnd* pMainWnd,PATCHPROC PatProc)
					: CBasePage(pMainWnd,PatProc,CDlg_PI_EndCond::IDD)
{
	//{{AFX_DATA_INIT(CDlg_PI_EndCond)
	m_strBCL 	= "AUTO";
	m_strBCR 	= "AUTO";
	m_bRightOn 	= TRUE;
	m_bLeftOn 	= TRUE;
	m_strDir	= _T("");
	m_NodeID	= _T("");
	m_strTwist	= _T("");
	m_bAllSame	= FALSE;
	m_bDefault	= FALSE;
	//}}AFX_DATA_INIT
	m_NodeID_I	= m_NodeID;
	m_NodeID_J	= "";
	m_bCornerMode	= 0;
	m_bEditMode = 0;
}


void CDlg_PI_EndCond::DoDataExchange(CDataExchange* pDX)
{
	CBasePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PI_EndCond)
	DDX_CBString(pDX, IDC_BC_LEFT, m_strBCL);
	DDX_CBString(pDX, IDC_BC_RIGHT, m_strBCR);
	DDX_Check(pDX, IDC_BC_RIGHT_ON, m_bRightOn);
	DDX_Check(pDX, IDC_BC_LEFT_ON, m_bLeftOn);
	DDX_CBString(pDX, IDC_COMBODIR, m_strDir);
	DDX_CBString(pDX, IDC_COMBONODE, m_NodeID);
	DDX_CBString(pDX, IDC_COMBOTWIST, m_strTwist);
	DDX_Check(pDX, IDC_ALLSAME, m_bAllSame);
	DDX_Check(pDX, IDC_DEFAULT, m_bDefault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_PI_EndCond, CBasePage)
	//{{AFX_MSG_MAP(CDlg_PI_EndCond)
	ON_CBN_SELCHANGE(IDC_BC_LEFT, OnSelchangeBcLeft)
	ON_CBN_SELCHANGE(IDC_BC_RIGHT, OnSelchangeBcRight)
	ON_BN_CLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_CLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_CBN_SELCHANGE(IDC_COMBONODE, OnSelchangeComboNode)
	ON_CBN_SELCHANGE(IDC_COMBODIR, OnSelchangeComboDir)
	ON_CBN_SELCHANGE(IDC_COMBOTWIST, OnSelchangeComboTwist)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_ALLSAME, OnAllSame)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_BC_LEFT_ON, OnBcLeftOn)
	ON_BN_DOUBLECLICKED(IDC_BC_RIGHT_ON, OnBcRightOn)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_DOUBLECLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_EndCond message handlers
BOOL CDlg_PI_EndCond::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	//////////////////////////////////////////////
//	GetDlgItem(IDC_STATICNODE)->SetWindowText("");	
	GetDlgItem(IDC_COMBOTWIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBONODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBODIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT)->EnableWindow(FALSE);
	///
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_PI_EndCond::OnDefault() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
	if(!m_bDefault)
		return;
	//////////////////////////////
	SetIendJendCombos();	// sets to AUTO
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CDlg_PI_EndCond::OnAllSame() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
}

void CDlg_PI_EndCond::OnSelchangeComboNode() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
}

void CDlg_PI_EndCond::OnSelchangeComboDir() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
	if(!m_bEditMode)
		return;
	///////////////////
	m_bU = (m_strDir == IsoDir[0]);
	///////////////////////////////
	m_indexEnd = 0;
	///////////////
	if(m_bU)
	{
		FillBndryNodeIDCombo(m_BndryList_U);
		FillOthers(m_indexEnd,m_pEndList_U);
	}
	else
	{
		FillBndryNodeIDCombo(m_BndryList_V);
		FillOthers(m_indexEnd,m_pEndList_V);
	}
	///
	((CComboBox*)GetDlgItem(IDC_COMBONODE))->SetCurSel(0);
	///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
	/////////////////// 
	
}

void CDlg_PI_EndCond::OnSelchangeComboTwist() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
}

void CDlg_PI_EndCond::ResetDlgForTwist()
{
	CDrNode* pNode;
	POSITION pos;
	int index;
	//////////////////////////////////////////////// 
	GetDlgItem(IDC_COMBODIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BC_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BC_RIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BC_LEFT_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
	/////////////////////////////////////////////////
	GetDlgItem(IDC_COMBONODE)->EnableWindow(FALSE);
	///
	index		= m_indexNode_I; 
	pos			= m_pNodeList->FindIndex(index);
	pNode		= (CDrNode*)m_pNodeList->GetAt(pos);
	m_NodeID	= pNode->GetObjectID();
	///////////////////////////////////////////////// Twist
	GetDlgItem(IDC_COMBOTWIST)->EnableWindow(TRUE);
	((CComboBox*)GetDlgItem(IDC_COMBOTWIST))->SetCurSel(0);
	GetDlgItem(IDC_COMBOTWIST)->SetFocus();
}

void CDlg_PI_EndCond::ResetDlg()
{
	SetIsoDir();
	SetNodeIDs();
	SetIendJendBoolText();
	SetIendJendCombos();
	SetEndListIndex();
	/////////////////////
	BuildBndryNodeList();
	///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
	/////////////////// 
}

void CDlg_PI_EndCond::ResetDlgForEdit()
{
	SetIsoDir();
	SetNodeIDs();
	SetIendJendBoolText();
	SetIendJendCombos();
	SetEndListIndex();
	/////////////////////
	GetDlgItem(IDC_COMBODIR)->EnableWindow(TRUE);
	((CComboBox*)GetDlgItem(IDC_COMBODIR))->SetCurSel(0);
	////////////
	m_bU = TRUE;
	///////////////////////////////////////////////
	GetDlgItem(IDC_COMBONODE)->EnableWindow(TRUE);
	FillBndryNodeIDCombo(m_BndryList_U);
	((CComboBox*)GetDlgItem(IDC_COMBONODE))->SetCurSel(0);
	///////////////
	m_indexEnd = 0;
	FillOthers(m_indexEnd,m_pEndList_U);
	//////////////////////////////////////////
	GetDlgItem(IDC_EDIT)->EnableWindow(TRUE);
	///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
	/////////////////// 
}

void CDlg_PI_EndCond::FillBndryNodeIDCombo(CList<CString,CString>& BndryList)
{
	int nCount = BndryList.GetCount();
	if(nCount<=0)
		return;
    ////////////////////////////////// 
	POSITION pos;
	int i;
 	CComboBox* pCombo;
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_COMBONODE); 
	//////////////////////////////////////////////// always left to start with
	for(i=0;i<nCount;i++)	// 
	{
		pos = BndryList.FindIndex(i);
 		pCombo->AddString(BndryList.GetAt(pos));
	}
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CDlg_PI_EndCond::FillOthers(int index,CList<BLENDEND,BLENDEND>* pEndList)
{
	int nCount = pEndList->GetCount();
	if(nCount<=0)
		return;
    ////////////////////////////////// 
	POSITION pos		= pEndList->FindIndex(index);
	BLENDEND blendEnd	= pEndList->GetAt(pos);
	/////////////
   	m_BCL	= blendEnd.m_BCL;
   	m_BCR	= blendEnd.m_BCR;
	/////////////////////////
	VECTOR tan;
	///
	tan = blendEnd.m_TanL;
	////////
	m_TanL.x = tan.v[0];
	m_TanL.y = tan.v[1];
	m_TanL.z = tan.v[2];
	///
	tan = blendEnd.m_TanR;
	////////
	m_TanR.x = tan.v[0];
	m_TanR.y = tan.v[1];
	m_TanR.z = tan.v[2];
	////////////////////
}

void CDlg_PI_EndCond::SetIsoDir()
{
    /////////////////// 
 	CComboBox* pCombo;
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_COMBODIR);
	////////
	pCombo->ResetContent();// ALL REMOVED 
	pCombo->AddString(IsoDir[0]);
	pCombo->AddString(IsoDir[1]);
	pCombo->SetCurSel(m_bU?0:1);
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CDlg_PI_EndCond::SetNodeIDs()
{
	CDrNode* pNode;
	POSITION pos;
	int index;
	//////////////////////////////////////////////// Iend
	index		= m_indexNode_I; 
	pos			= m_pNodeList->FindIndex(index);
	pNode		= (CDrNode*)m_pNodeList->GetAt(pos);
	m_NodeID_I	= pNode->GetObjectID();
	//////////////////////////////////////////////// Jend
	index		= GetIndexJ(m_indexNode_I,m_bU); 
	pos			= m_pNodeList->FindIndex(index);
	pNode		= (CDrNode*)m_pNodeList->GetAt(pos);
	m_NodeID_J	= pNode->GetObjectID();
	/////////////////////////
	m_NodeID	= m_NodeID_I;
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

int CDlg_PI_EndCond::GetIndexJ(int indexI, BOOL bU)
{
	if(bU) // U-dir Curve
		return (indexI + m_nNode_U - 1);
	else
		return (indexI + m_nNode_U*(m_nNode_V-1) );
}

void CDlg_PI_EndCond::SetIendJendBoolText()
{
	if(m_NodeID_I != "")
 		GetDlgItem(IDC_BC_LEFT_ON)->SetWindowText(m_NodeID_I);
	if(m_NodeID_J != "")
 		GetDlgItem(IDC_BC_RIGHT_ON)->SetWindowText(m_NodeID_J);
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 
}

void CDlg_PI_EndCond::SetEndListIndex()
{
	//////////////////
	if(m_bU)
		m_indexEnd = m_indexNode_I/m_nNode_U;
	else
		m_indexEnd = m_indexNode_I;
}

void CDlg_PI_EndCond::BuildBndryNodeList()
{
	if(m_NodeID == "")
		return;
	//////////////////
	if(m_bU)
		m_BndryList_U.AddTail(m_NodeID);
	else
		m_BndryList_V.AddTail(m_NodeID);
}

void CDlg_PI_EndCond::SetIendJendCombos()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    /////////////////// 
	int i,index;
 	CComboBox* pCombo;
	////////////////////////////////////////////////// Change LEFTBoundaryCombo
 	pCombo = (CComboBox*)GetDlgItem(IDC_BC_LEFT); 
 	/////////////////////////////////////////////
    if(m_nOrder == 3)		// QUADRATIC
    {
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
       	pCombo->SetCurSel(0);	//	AUTO
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
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
    if(m_nOrder == 3)		// QUADRATIC
    {
		//////////////////////////////////////////////// always False to start with
   		pCombo->ResetContent();// ALL REMOVED 
  		pCombo->EnableWindow(FALSE);	
		m_bRightOn = FALSE;
		GetDlgItem(IDC_BC_RIGHT_ON)->EnableWindow(FALSE);
	}
	else        
    if(m_nOrder == 4)		// CUBIC
    {
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
    ///////////////////
	UpdateData(FALSE);		    //To Screen(FALSE)    
    /////////////////// 

} 

void CDlg_PI_EndCond::OnBcLeftOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
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

void CDlg_PI_EndCond::OnBcRightOn()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////
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

void CDlg_PI_EndCond::OnSelchangeBcLeft()
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

void CDlg_PI_EndCond::OnSelchangeBcRight()
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

void CDlg_PI_EndCond::OnUpdate()
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
	if(m_bCornerMode)
		UpdateDataBase_Twist();
	else
	{
		if(m_bU)
			UpdateDataBase_BC(m_indexEnd,m_pEndList_U);
		else
			UpdateDataBase_BC(m_indexEnd,m_pEndList_V);
	}
	//////////////////////////////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PATIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_PI_EndCond::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_PATIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
 
void CDlg_PI_EndCond::UpdateDataBase_BC(int nNodeIndex,CList<BLENDEND,BLENDEND>* pEndList)
{
	CList<BLENDEND,BLENDEND> TempList;
	BLENDEND blendEnd;
	POSITION pos;
	int i,nMax,nCount;
	///////////////////////////////////
	nCount	= pEndList->GetCount(); 
	nMax	= (m_bU)?m_nNode_V:m_nNode_U;
	////////////////////////////////////////////////// copy upto nEndIndex-1
	TempList.RemoveAll();
	for(i=0;i<nNodeIndex;i++)
	{
		pos			= pEndList->FindIndex(i);
		blendEnd	= pEndList->GetAt(pos);
		TempList.AddTail(blendEnd);
	}
	////////////////////////////////////////////////// Boundary at nNodeIndex
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
	blendEnd.m_BCL = m_BCL;
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
	blendEnd.m_BCR = m_BCR;
	/////////////////////////
	if(m_BCL == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanL.x;
		tan.v[1] = m_TanL.y;
		tan.v[2] = m_TanL.x;
		tan.v[3] = 0;
		////////
		blendEnd.m_TanL = tan;
	}	
	if(m_BCR == BC_TANGENT)
	{
		VECTOR tan;
		tan.v[0] = m_TanR.x;
		tan.v[1] = m_TanR.y;
		tan.v[2] = m_TanR.x;
		tan.v[3] = 0;
		////////
		blendEnd.m_TanR = tan;
	}
	/////////////////////////////////////////////////////// Quadratic
	// Only One BC end is allowable:
	//	 ifLeft	- set tan.v for right 	 -99999.	
	//	 ifRight- set tan.v for left 	= -99999.
	/////////////////////////////////////////////
	if(3 == m_nOrder)
	{
		if(!m_bLeftOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			blendEnd.m_TanL = tan;
		}	
		if(!m_bRightOn)
		{
			VECTOR tan;
			tan.v[0] = -99999.;	
			////////
			blendEnd.m_TanR = tan;
		}
	}
	////////////////////////////////////////////////// save Rest with Current
	if(m_bAllSame)
	{
		for(i=nNodeIndex;i<nMax;i++)
			TempList.AddTail(blendEnd);
	}
	else
	{
		TempList.AddTail(blendEnd);
		///////////////////////////////////////////// copy from nNodeIndex+1 to end
		for(i=nNodeIndex+1;i<nCount;i++)
		{
			pos			= pEndList->FindIndex(i);
			blendEnd	= pEndList->GetAt(pos);
			TempList.AddTail(blendEnd);
		}
	}
	////////////////////////////////////////////////// Now save it back
	pEndList->RemoveAll();
	pEndList->AddTail(&TempList);
	TempList.RemoveAll();
	///////////
	return;
}

void CDlg_PI_EndCond::UpdateDataBase_Twist()
{
	int i,j;
	////////////////////////////////////////////////// Corner Twist
	if(!m_bCornerMode)
		return;
	//////////////////////////////////////////////////////
	if(m_strTwist == TWs[0])			// TWist Condition
   		m_Twist = TW_AUTO;
	else
	if(m_strTwist == TWs[1])			// TWist Condition
   		m_Twist = TW_ZERO;
	else
	if(m_strTwist == TWs[2])			// TWist Condition
   		m_Twist = TW_BESSEL;
	else
	if(m_strTwist == TWs[3])			// TWist Condition
   		m_Twist = TW_ADINI;
	else
	if(m_strTwist == TWs[4])			// TWist Condition
   		m_Twist = TW_SPLINE;
	else
	if(m_strTwist == TWs[5])			// TWist Condition
   		m_Twist = TW_ENERGY;
	else
	if(m_strTwist == TWs[6])			// TWist Condition
   		m_Twist = TW_USER;
	//////////////////////////////////////
	if(m_bAllSame)
	{
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
				m_TwistMethod[i][j] = m_Twist;
	}
	else
		m_TwistMethod[m_nCornerI][m_nCornerJ] = m_Twist;
	///////
	return;
	
} 

void CDlg_PI_EndCond::OnEdit() 
{
    ///////////////////
	UpdateData(TRUE);		    //From Screen(TRUE)    
    ///////////////////
	if(m_bCornerMode)
		UpdateDataBase_Twist();
	else
	{
		if(m_bU)
			UpdateDataBase_BC(m_indexEnd,m_pEndList_U);
		else
			UpdateDataBase_BC(m_indexEnd,m_pEndList_V);
	}
}
////////////////////////////////////// end of Module ///////////////////////////
