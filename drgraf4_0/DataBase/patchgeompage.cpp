// PatchGeomPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Mouse.h"
#include "PatchSheet.h"
/////////////////////
#include "PatchGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
// CPatchGeomPage property page

IMPLEMENT_DYNCREATE(CPatchGeomPage, CPropertyPage)

CPatchGeomPage::CPatchGeomPage() : CPropertyPage(CPatchGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchGeomPage)
	m_AxisX			= 0.0;
	m_AxisY			= 0.0;
	m_AxisZ			= 0.0;
	m_CenterX		= 0.0;
	m_CenterY		= 0.0;
	m_CenterZ		= 0.0;
	m_Class			= _T("");
	m_bIso			= FALSE;
	m_IsoTo			= _T("");
	m_Radius		= 0.0;
	m_TotAngle		= 0.0;
	m_TotElems		= 0.0;
	m_bClosed_S = FALSE;
	m_bClosed_T = FALSE;
	m_dLenX = 0.0;
	m_dLenY = 0.0;
	m_dLenZ = 0.0;
	m_TotNodeU = 0;
	m_TotNodeV = 0;
	m_TotNodeW = 0;
	m_PatchID = _T("");
	m_PatchProc = _T("");
	m_PatchSubType = _T("");
	//}}AFX_DATA_INIT
}

CPatchGeomPage::~CPatchGeomPage()
{
}

void CPatchGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchGeomPage)
	DDX_Text(pDX, IDC_AXISX, m_AxisX);
	DDX_Text(pDX, IDC_AXISY, m_AxisY);
	DDX_Text(pDX, IDC_AXISZ, m_AxisZ);
	DDX_Text(pDX, IDC_CENTERX, m_CenterX);
	DDX_Text(pDX, IDC_CENTERY, m_CenterY);
	DDX_Text(pDX, IDC_CENTERZ, m_CenterZ);
	DDX_Text(pDX, IDC_CLASS, m_Class);
	DDX_Check(pDX, IDC_ISO, m_bIso);
	DDX_Text(pDX, IDC_ISOTO, m_IsoTo);
	DDX_Text(pDX, IDC_RADIUS, m_Radius);
	DDX_Text(pDX, IDC_TOTANGLE, m_TotAngle);
	DDX_Text(pDX, IDC_TOTELEMS, m_TotElems);
	DDX_Check(pDX, IDC_CLOSED_S, m_bClosed_S);
	DDX_Check(pDX, IDC_CLOSED_T, m_bClosed_T);
	DDX_Text(pDX, IDC_LENX, m_dLenX);
	DDX_Text(pDX, IDC_LENY, m_dLenY);
	DDX_Text(pDX, IDC_LENZ, m_dLenZ);
	DDX_Text(pDX, IDC_TOTNODE_U, m_TotNodeU);
	DDX_Text(pDX, IDC_TOTNODE_V, m_TotNodeV);
	DDX_Text(pDX, IDC_TOTNODE_W, m_TotNodeW);
	DDX_Text(pDX, IDD_PATCH_ID, m_PatchID);
	DDX_Text(pDX, IDD_PATCH_PROC, m_PatchProc);
	DDX_Text(pDX, IDD_PATCH_SUBTYPE, m_PatchSubType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchGeomPage message handlers

int CPatchGeomPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(PATCH);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(PATCH,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrPatch* pObject = (CDrPatch*)(pList->GetObject(index));
	if(pObject)
	{
		UpdateInfo(pObject);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CPatchGeomPage::UpdateInfo(CDrPatch* pObject)
{
	CMouse Mouse;
	/////////////
	m_PatchID = pObject->GetObjectID();
	///
	PATSUBTYPE PatchSubType = pObject->GetPatSubType();
	PatchSubTypetoString(m_PatchSubType,PatchSubType);
	//////////////////////////////////////////// Common Info
//	m_BZSegs	= pObject->GetSegmentCount_T();
	m_bClosed_S	= pObject->IsClosed_S();
	m_bClosed_T	= pObject->IsClosed_T();
	/////////////////////////////////////
	int nClass	= pObject->GetClass_T();
	ClassTypetoString(m_Class,nClass);
	/////////////////////////////////////
	m_bClosed_S = pObject->IsClosed_S();
	m_bClosed_T = pObject->IsClosed_T();
	m_bIso		= pObject->IsIso();
	m_IsoTo		= pObject->GetIsoToID();
	m_TotElems	= (pObject->GetOut_S()-1)*(pObject->GetOut_T()-1);
	m_TotNodeU	= pObject->GetOut_S();
	m_TotNodeV	= pObject->GetOut_T();
//	m_TotNodeW	= 0;	// set in Triangular
	//////////////////////////////////////////////////////// Combos
	////////////////////////////////////////////////////////
	if(PatchSubType == PS_QUADRILAT)
		UpdateInfoQuadrilateral(pObject);
	else
	if(PatchSubType == PS_TRIANGLE)
		UpdateInfoTriangular(pObject);
	/////////
	return 0;
}

int CPatchGeomPage::UpdateInfoQuadrilateral(CDrPatch* pObject)
{
	///
	PATCHPROC PatchProc = pObject->GetPatchProc();
	PatchProctoString(m_PatchProc,PatchProc,pObject);
	/////////
	return 0;
}

int CPatchGeomPage::UpdateInfoTriangular(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	/////////////////
	m_TotNodeW	= pObject->GetOut_S();
	//////////////////////////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	///////////////////////////////////////////////////////////
	CDListMgr* pList = pObject->GetCurveList();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Curves");
	UpdateCombo(pList,IDC_CURVECOMBO);
	/// general latch combo disable
	GetDlgItem(IDC_LATCHCOMBO)->EnableWindow(FALSE);
	////////////////////////////////// 
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("Curve u");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	//////////////
	GetDlgItem(IDC_CURVEVORTWIST)->SetWindowText("Curve v");
	strCurve = pObject->GetCurveID(1);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->ResetContent();
	CLatch = pObject->GetCurveLatch(1);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	//////////////
	GetDlgItem(IDC_CURVEWORRAD)->SetWindowText("Curve w");
	strCurve = pObject->GetCurveID(2);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_W))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_W))->ResetContent();
	CLatch = pObject->GetCurveLatch(2);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_W))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoExtrusion(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	//////////////////////////////////////////////////////for Type 2 Input:wLen
	int nType = pObject->GetExtruType_T();
	if(nType == 1)
	{
		double dDouble = pObject->GetLength_T();
		Mouse.WORtoWOP(&dDouble,&dDouble);
		///
		m_dLenX = dDouble;
	}
	else
	if(nType == 2)
	{
		WORLD dWorld = pObject->GetWorldLength_T();
		Mouse.WORtoWOP(&dWorld,&dWorld);
		///
		m_dLenX = dWorld.x;
		m_dLenY = dWorld.y;
		m_dLenZ = dWorld.z;
	}
	/////////////////////////////////////////////////////////// Combo
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	CDListMgr* pList = pObject->GetCurveList();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Curves");
	UpdateCombo(pList,IDC_CURVECOMBO);
	/// general latch combo disable
	GetDlgItem(IDC_LATCHCOMBO)->EnableWindow(FALSE);
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("CurveToExtru.");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoRevolution(CDrPatch* pObject)
{
	CMouse Mouse;
	WORLD	wWorld;
	CString strCurve;
	CURVELATCH CLatch;
	////////////////////////////////////////////
	wWorld = pObject->GetNormal_T();
	Mouse.WORtoWOP(&wWorld,&wWorld);
	m_AxisX			= wWorld.x;
	m_AxisY			= wWorld.y;
	m_AxisZ			= wWorld.z;
	//////////////////////////
	wWorld = pObject->GetCenter_T();
	Mouse.WORtoWOP(&wWorld,&wWorld);
	m_CenterX		= wWorld.x;
	m_CenterY		= wWorld.y;
	m_CenterZ		= wWorld.z;
	//////////////////////////
	double dDouble = pObject->GetRadius_T();
	Mouse.WORtoWOP(&dDouble,&dDouble);
	m_Radius		= dDouble;
	//////////////////////////
	m_TotAngle		= pObject->GetAng_2_T();
	//////////////////////////////////////////////////////// Combos
	///////////////////////////////// Angle/Seg Distribution
	int BZSegs		= pObject->GetMaxBezSegments_T();
	pDOUBLE pDisAng	= pObject->GetDis_AngPointer_T(); 
	UpdateCombo_Double(pDisAng,BZSegs,IDC_ANGPERSEGCOMBO);
	//////////////////////////////////////////////////////// Combos
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	CDListMgr* pList = pObject->GetCurveList();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Curves");
	UpdateCombo(pList,IDC_CURVECOMBO);
	/// general latch combo disable
	GetDlgItem(IDC_LATCHCOMBO)->EnableWindow(FALSE);
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("CurveToRev.");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoLoft2(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	//////////////////////////////////////////////////////// Combos
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	CDListMgr* pList = pObject->GetCurveList();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Curves");
	UpdateCombo(pList,IDC_CURVECOMBO);
	/// general latch combo disable
	GetDlgItem(IDC_LATCHCOMBO)->EnableWindow(FALSE);
	///////////////////////////////////////////////////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("Cur:LoftFrom");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	GetDlgItem(IDC_CURVEVORTWIST)->SetWindowText("Cur:LoftTo.");
	strCurve = pObject->GetCurveID(1);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->ResetContent();
	CLatch = pObject->GetCurveLatch(1);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	//////////////////////////////////
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoCoons(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	///////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	CDListMgr* pList = pObject->GetCurveList();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Curves");
	UpdateCombo(pList,IDC_CURVECOMBO);
	/// general latch combo disable
	GetDlgItem(IDC_LATCHCOMBO)->EnableWindow(FALSE);
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("Curve u");
	strCurve = pObject->GetCurveID(0);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	strCurve = pObject->GetCurveID(2);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	CLatch = pObject->GetCurveLatch(2);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	GetDlgItem(IDC_CURVEVORTWIST)->SetWindowText("Curve v");
	strCurve = pObject->GetCurveID(1);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->ResetContent();
	CLatch = pObject->GetCurveLatch(1);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	strCurve = pObject->GetCurveID(3);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	/// latch
	CLatch = pObject->GetCurveLatch(3);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	//////////////////////////////////
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoDuct(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	///////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Spine Curve");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("XSec. Curve");
	strCurve = pObject->GetCurveID(1);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(1);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	GetDlgItem(IDC_CURVEVORTWIST)->SetWindowText("Twist Curve");
	strCurve = pObject->GetCurveID(2);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->ResetContent();
	CLatch = pObject->GetCurveLatch(2);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoSweep(CDrPatch* pObject)
{
	CMouse Mouse;
	CString strCurve;
	CURVELATCH CLatch;
	///////////////
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->ResetContent();
	GetDlgItem(IDC_CURVEORSPINE)->SetWindowText("Spine Curve");
	strCurve = pObject->GetCurveID(0);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO))->ResetContent();
	CLatch = pObject->GetCurveLatch(0);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->ResetContent();
	GetDlgItem(IDC_CURVEUORXSEC)->SetWindowText("XSec. Curve");
	strCurve = pObject->GetCurveID(1);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_U))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->ResetContent();
	CLatch = pObject->GetCurveLatch(1);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_U))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->ResetContent();
	GetDlgItem(IDC_CURVEVORTWIST)->SetWindowText("Twist Curve");
	strCurve = pObject->GetCurveID(2);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_V))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->ResetContent();
	CLatch = pObject->GetCurveLatch(2);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_V))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	////////////////////////////////// 
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_W))->ResetContent();
	GetDlgItem(IDC_CURVEWORRAD)->SetWindowText("Radius Curve");
	strCurve = pObject->GetCurveID(3);
	((CComboBox*)GetDlgItem(IDC_CURVECOMBO_W))->AddString(strCurve);
	/// latch
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_W))->ResetContent();
	CLatch = pObject->GetCurveLatch(3);
	((CComboBox*)GetDlgItem(IDC_LATCHCOMBO_W))->AddString
		((CLatch == CL_FORWARD)?"FORWARD":"BACKWARD");
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateInfoGordon(CDrPatch* pObject)
{
	CMouse Mouse;
	/////////////
	return 0;
}

int CPatchGeomPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
{
	if(pList->IsEmpty())
		return 0;
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	CDrObject* pObject;			       
	POSITION pos;
	///	
	pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pList->GetNextObject( pos);
    	((CComboBox*)pWndCtrl)->AddString(pObject->GetObjectID());	// Show ALL  
   	}
	///
   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

int CPatchGeomPage::UpdateCombo_Double(pDOUBLE pData, int nData, UINT DlgComboID)
{
	if(nData<=0)
		return 0;
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	///
	for(int i=0;i<nData;i++)
	{
		double dData = pData[i];
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"%f",dData);
		///
    	((CComboBox*)pWndCtrl)->AddString(*str);
		///
		delete str;
   	}
	///
//   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

int CPatchGeomPage::UpdateCombo_Int(pINT pData, int nData, UINT DlgComboID)
{
	if(nData<=0)
		return 0;
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	///
	for(int i=0;i<nData;i++)
	{
		int nElem = pData[i];
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"%d",nElem);
		///
    	((CComboBox*)pWndCtrl)->AddString(*str);
		///
		delete str;
   	}
	///
//   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

int CPatchGeomPage::PatchProctoString(CString& str,PATCHPROC nType,
												CDrPatch* pObject)
{
	static CString CTyp[] 	= {
		"EXTRUSION","REVOLUTION","LOFTING","LOFTING","LOFTING","LOFTING MANY",
		"SWEEPING","DUCTING","TENSOR PRODUCT","COONS","GORDON",
		"TESSALATION","SPAWNING","STITCHING"
		};
	//////////
	switch(nType)
	{
		case 	PP_EXTRUDE: 		
   			str = CTyp[0];
			UpdateInfoExtrusion(pObject);
			break;
		case 	PP_ROTATE:		
   			str = CTyp[1];
			UpdateInfoRevolution(pObject);
			break;
		case 	PP_LOFT2: 		
			UpdateInfoLoft2(pObject);
   			str = CTyp[2];
			break;
		case 	PP_COONSTRI:	// Triangular Coons	
   			str = CTyp[9];
			UpdateInfoCoons(pObject);
			break;
		case 	PP_COONSQUAD:	// Quadrilat Coons	
   			str = CTyp[9];
			UpdateInfoCoons(pObject);
			break;
		case 	PP_LOFTX:       
   			str = CTyp[5];
			break;
		case 	PP_SWEEP:		
			UpdateInfoSweep(pObject);
			break;
		case 	PP_DUCT:	
   			str = CTyp[7];
			UpdateInfoDuct(pObject);
			break;
		case 	PP_TENSOR:	
   			str = CTyp[8];
			break;
		case 	PP_COONS:	
   			str = CTyp[9];
			UpdateInfoCoons(pObject);
			break;
		case 	PP_GORDON:	
   			str = CTyp[10];
			UpdateInfoGordon(pObject);
			break;
		case 	PP_FLAT:	
   			str = CTyp[11];
			break;
		case 	PP_SPAWN:	
   			str = CTyp[12];
			break;
		case 	PP_STITCH:	
   			str = CTyp[13];
			break;
		default:
			break;
	}
	//////////
	return 0;
}

int CPatchGeomPage::DegreeTypetoString(CString& str,int nType)
{
	static CString Deg[] 	= {	"0","1","2","3"};
	str = Deg[nType];
	//////////
	return 0;
}

int CPatchGeomPage::ClassTypetoString(CString& str,int nType)
{
	static CString Cls[] 	= {	"C0","C1","C2"};
	str = Cls[nType];
	//////////
	return 0;
}

int CPatchGeomPage::PatchSubTypetoString(CString& str,PATSUBTYPE nType)
{
	switch(nType)
	{
		case 	PS_TRIANGLE:
			str = "TRIANGLE";
			break;
		case 	PS_QUADRILAT:
			str = "QUADRILATERAL";
			break;
		case 	PS_RANDOM:
			str = "Random";
			break;
		default:
			break;
	}
	/////////
	return 0;
}

BOOL CPatchGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CPatchSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
