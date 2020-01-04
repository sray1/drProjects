// drawbox.cpp : implementation file
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "Unit.h"
#include "MapFacto.h"
////////////////////
#include "Dlg_Unit.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawUnit dialog

CDrawUnit::CDrawUnit(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawUnit::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDrawUnit)
	m_szDrawUnit = "";
	//}}AFX_DATA_INIT
}

void CDrawUnit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawUnit)
	DDX_CBString(pDX, IDC_COMBO_UNITS, m_szDrawUnit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawUnit, CDialog)
	//{{AFX_MSG_MAP(CDrawUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawUnit message handlers
void CDrawUnit::OnUnit()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 		= pDoc->GetObjectMgr();
	CUnit* pUnit     	   		= (CUnit*)pObjectMgr->GetSpecObject(UNIT);
	CMapFactor* pMapFactor		= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
	///////////////////////////////////////////////
	CDrawUnit	dlg;
	UINT nUnitCount = pUnit->GetUnitNameCount();
	
	UINT nUnitIndex = pUnit->GetUnitIndex();
	pUnit->SetUnitIndexOld(nUnitIndex);
	//set dialog combo index
	dlg.m_szDrawUnit = pUnit->GetUnitName(nUnitIndex);
	
	if(dlg.DoModal() == IDOK)
	{
		// retrieve data 
		for(UINT i=0; i<nUnitCount; i++)
			if(dlg.m_szDrawUnit == pUnit->GetUnitName(i))
			{
				pUnit->SetUnitIndex(i);
				break;
			}
		///////////////// Reset MapFactor Info
		pObjectMgr->SetMapFactorInfo();	          
		/////////////////					
	}	
}

BOOL CDrawUnit::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CUnit* pUnit	 		= (CUnit*)pObjectMgr->GetSpecObject(UNIT);
   ////////////////////////////////////
	CWnd* pWndCtrl   = GetDlgItem(IDC_COMBO_UNITS);
	((CComboBox*)(pWndCtrl))->SetCurSel(pUnit->GetUnitIndex());
/*	
		CString str;
		char buf[80];
		sprintf(buf,"DrawMenu::OnInitDlg:m_nUnit = %u",pDoc->GetUnitIndex());
		str = buf;		  
		AfxMessageBox(str);
		str = "DrawMenu::OnInitDlg:dlg.m_szDrawUnit";
		str = str + m_szDrawUnit;		  
		AfxMessageBox(str);
*/	 
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}
