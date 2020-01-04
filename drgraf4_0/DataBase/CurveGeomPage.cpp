// CurveGeomPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Mouse.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
// CCurveGeomPage property page

IMPLEMENT_DYNCREATE(CCurveGeomPage, CPropertyPage)

CCurveGeomPage::CCurveGeomPage() : CPropertyPage(CCurveGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveGeomPage)
	m_AxisX			= 0.0;
	m_AxisY			= 0.0;
	m_AxisZ			= 0.0;
	m_BCLeft		= _T("");
	m_BCRight		= _T("");
	m_BZSegs		= 0;
	m_CenterX		= 0.0;
	m_CenterY		= 0.0;
	m_CenterZ		= 0.0;
	m_CircleType	= _T("");
	m_Class			= _T("");
	m_bClosed		= FALSE;
	m_bIso			= FALSE;
	m_IsoTo			= _T("");
	m_KnotType		= _T("");
	m_Radius		= 0.0;
	m_Ratio			= 0.0;
	m_TanX			= 0.0;
	m_TanY			= 0.0;
	m_TanZ			= 0.0;
	m_TotAngle		= 0.0;
	m_TotElems		= 0.0;
	m_bUniform		= FALSE;
	m_WeightType	= _T("");
	m_CurveID		= _T("");
	m_CurveType		= _T("");
	m_Degree		= _T("");
	//}}AFX_DATA_INIT
}

CCurveGeomPage::~CCurveGeomPage()
{
}

void CCurveGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveGeomPage)
	DDX_Text(pDX, IDC_AXISX, m_AxisX);
	DDX_Text(pDX, IDC_AXISY, m_AxisY);
	DDX_Text(pDX, IDC_AXISZ, m_AxisZ);
	DDX_Text(pDX, IDC_BCLEFT, m_BCLeft);
	DDX_Text(pDX, IDC_BCRIGHT, m_BCRight);
	DDX_Text(pDX, IDC_BZSEGS, m_BZSegs);
	DDX_Text(pDX, IDC_CENTERX, m_CenterX);
	DDX_Text(pDX, IDC_CENTERY, m_CenterY);
	DDX_Text(pDX, IDC_CENTERZ, m_CenterZ);
	DDX_Text(pDX, IDC_CIRCLETYPE, m_CircleType);
	DDX_Text(pDX, IDC_CLASS, m_Class);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Check(pDX, IDC_ISO, m_bIso);
	DDX_Text(pDX, IDC_ISOTO, m_IsoTo);
	DDX_Text(pDX, IDC_KNOTTYPE, m_KnotType);
	DDX_Text(pDX, IDC_RADIUS, m_Radius);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_Text(pDX, IDC_TANX, m_TanX);
	DDX_Text(pDX, IDC_TANY, m_TanY);
	DDX_Text(pDX, IDC_TANZ, m_TanZ);
	DDX_Text(pDX, IDC_TOTANGLE, m_TotAngle);
	DDX_Text(pDX, IDC_TOTELEMS, m_TotElems);
	DDX_Check(pDX, IDC_UNIFORM, m_bUniform);
	DDX_Text(pDX, IDC_WEIGHTTYPE, m_WeightType);
	DDX_Text(pDX, IDD_CURVE_ID, m_CurveID);
	DDX_Text(pDX, IDD_CURVE_TYPE, m_CurveType);
	DDX_Text(pDX, IDC_DEGREE, m_Degree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveGeomPage message handlers

int CCurveGeomPage::UpdateObjData(CString& strItemID)
{
//	CWnd* pParent = GetParent();			// CCurveSheet
//	CWnd* pParentOwner = GetParentOwner();	// CDrGrafFrame
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(CURVE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(CURVE,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrCurve* pObject = (CDrCurve*)(pList->GetObject(index));
	if(pObject)
	{
		UpdateInfo(pObject);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CCurveGeomPage::UpdateInfo(CDrCurve* pObject)
{
	CMouse Mouse;
	/////////////
	m_CurveID = pObject->GetObjectID();
	///
	CURVEPROC CurveProc = pObject->GetCurveType_S();
	CurveProctoString(m_CurveType,CurveProc);
	//////////////////////////////////////////// Common Info
	m_BZSegs	= pObject->GetMaxBezSegments_S();
	m_bClosed	= pObject->IsClosed_S();
	/////////////////////////////////////
	int nClass	= pObject->GetClass_S();
	ClassTypetoString(m_Class,nClass);
	/////////////////////////////////////
	int nDegree	= pObject->GetOrder_S() - 1;
	DegreeTypetoString(m_Degree,nDegree);
	/////////////////////////////////////
	m_bIso		= pObject->IsIso();
	m_IsoTo		= pObject->GetIsoToID();
	m_Ratio		= pObject->GetRatio_S();
	m_TotElems	= pObject->GetMaxOutPts_S() - 1;
	m_bUniform	= pObject->IsUniform_S();
	//////////////////////////////////////////////////////// Combos
	CDListMgr* pList = pObject->GetINodeList();
	UpdateCombo(pList,IDC_INODECOMBO);
	///////////////////////////////////// Elem/Seg Distribution
	pINT pNumElem = pObject->GetNum_tPointer_S(); 
	UpdateCombo_Int(pNumElem,m_BZSegs,IDC_ELPERSEGCOMBO);
	////////////////////////////////////////////////////////
	if(CurveProc == CP_CIRCLE)
		UpdateInfoCircle(pObject);
	else
		UpdateInfoCurve(pObject);
	/////////
	return 0;
}

int CCurveGeomPage::UpdateInfoCurve(CDrCurve* pObject)
{
	CMouse Mouse;
	/////////////
	KNOT KnTyp  = pObject->GetKnotType_S();
	KnotTypetoString(m_KnotType,KnTyp);
	WEIGHT WtTyp= pObject->GetWtType_S();
	WeightTypetoString(m_WeightType,WtTyp);
	///////////////////////////////////	
	BOUNDARY BCL = pObject->GetBCL_S();
	BCTypetoString(m_BCLeft,BCL);
	BOUNDARY BCR = pObject->GetBCR_S();
	BCTypetoString(m_BCRight,BCR);
	//
	VECTOR Tan;
	if(BCL == BC_TANGENT)
	{
		Tan 	= pObject->GetTanL_S();
		m_TanX	= Tan.v[0];
		m_TanY	= Tan.v[1];
		m_TanZ	= Tan.v[2];
	}
	if(BCR == BC_TANGENT)
	{
		Tan 	= pObject->GetTanR_S();
		m_TanX	= Tan.v[0];
		m_TanY	= Tan.v[1];
		m_TanZ	= Tan.v[2];
	}
	/////////////////
	return 0;
}

int CCurveGeomPage::UpdateInfoCircle(CDrCurve* pObject)
{
	CMouse Mouse;
	WORLD	wWorld;
	/////////////
	CIRCLETYPE nType = pObject->GetCircleType();
	CircleTypetoString(m_CircleType,nType);
	////////////////////////////////////////////
	wWorld = pObject->GetNormal_S();
	m_AxisX			= wWorld.x;
	m_AxisY			= wWorld.y;
	m_AxisZ			= wWorld.z;
	//////////////////////////
	wWorld = pObject->GetCenter_S();
	Mouse.WORtoWOP(&wWorld,&wWorld);
	m_CenterX		= wWorld.x;
	m_CenterY		= wWorld.y;
	m_CenterZ		= wWorld.z;
	//////////////////////////
	double dDouble = pObject->GetRadius_S();
	Mouse.WORtoWOP(&dDouble,&dDouble);
	m_Radius		= dDouble;
	//////////////////////////
	m_TotAngle		= pObject->GetTheta_S();
	//////////////////////////////////////////////////////// Combos
	///////////////////////////////// Angle/Seg Distribution
	int BZSegs		= pObject->GetMaxBezSegments_S();
	pDOUBLE pDisAng	= pObject->GetDis_AngPointer_S(); 
	UpdateCombo_Double(pDisAng,BZSegs,IDC_ANGPERSEGCOMBO);
	/////////////////
	return 0;
}

int CCurveGeomPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

int CCurveGeomPage::UpdateCombo_Double(pDOUBLE pData, int nData, UINT DlgComboID)
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

int CCurveGeomPage::UpdateCombo_Int(pINT pData, int nData, UINT DlgComboID)
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

int CCurveGeomPage::CurveProctoString(CString& str,CURVEPROC nType)
{
	static CString CTyp[] 	= {	
		"BEZIER","Cubic BSPLINE","NURB","CATMULLROM",
		"Cardinal SPLINE","HERMITE","Beta SPLINE","Quad. BSPLINE",
		"CIRCLE","ELLIPSE","PARABOLA","HYPERBOLA","LINEAR"
		};
	//////////
	switch(nType)
	{
		case 	CP_BEZIER: 		// Bezier:
   			str = CTyp[0];
			break;
		case 	CP_BSPLINE:		// B-Spline UNIFORM
   			str = CTyp[1];
			break;
		case 	CP_NURB: 		// B-Spline NON-UNIFORM RATIONAL
   			str = CTyp[2];
			break;
		case 	CP_CATMULLROM:	// Catmull-Rom
   			str = CTyp[3];
			break;
		case 	CP_CARDISPLINE:	// Cardinal Spline (ALFA Catmull-Rom)
   			str = CTyp[4];
			break;
		case 	CP_HERMITE:       // Hermite
   			str = CTyp[5];
			break;
		case 	CP_BETA:		// Beta-Spline
   			str = CTyp[6];
			break;
		case 	CP_QUADRATIC:	// Quadratics
   			str = CTyp[7];
			break;
		case 	CP_CIRCLE:	
   			str = CTyp[8];
			break;
		case 	CP_ELLIPSE:	
   			str = CTyp[9];
			break;
		case 	CP_PARABOLA:	
   			str = CTyp[10];
			break;
		case 	CP_HYPERBOLA:	
   			str = CTyp[11];
			break;
		case 	CP_LINEAR:	
   			str = CTyp[12];
			break;
		default:
			break;
	}
	//////////
	return 0;
}

int CCurveGeomPage::DegreeTypetoString(CString& str,int nType)
{
	static CString Deg[] 	= {	"0","1","2","3"};
	str = Deg[nType];
	//////////
	return 0;
}

int CCurveGeomPage::ClassTypetoString(CString& str,int nType)
{
	static CString Cls[] 	= {	"C0","C1","C2"};
	str = Cls[nType];
	//////////
	return 0;
}

int CCurveGeomPage::KnotTypetoString(CString& str,int nType)
{
	static CString KNs[] 	= {"UNIFORM","CHORDLENGTH","CENTRIPETAL","FOLEY","USER"};
	////////////////////////////////////////////////////////////////////////
	switch(nType)
	{
		case 	KN_UNIFORM:		
   			str = KNs[0];
			break;
		case 	KN_AUTO:		// fall thro'		
		case 	KN_CHORDLENGTH:			
   			str = KNs[1];
			break;
		case 	KN_CENTRIPETAL:		
   			str = KNs[2];
			break;
		case 	KN_FOLEY:		
   			str = KNs[3];
			break;
		case 	KN_USER:		
   			str = KNs[4];
			break;
		default:
			break;
	}
	//////////
	return 0;
}

int CCurveGeomPage::WeightTypetoString(CString& str,int nType)
{
	static CString WTs[] 	= {"AUTO","UNIFORM","USER"};
	////////////////////////////////////////////////////////////////////////
	switch(nType)
	{
		case 	WT_AUTO:		// depend on Conics				
   			str = WTs[0];
			break;
		case 	KN_UNIFORM:		
   			str = WTs[1];
			break;
		case 	KN_USER:		
   			str = WTs[2];
			break;
		default:
			break;
	}
	//////////
	return 0;
}
	
int CCurveGeomPage::BCTypetoString(CString& str,BOUNDARY nType)
{
	static CString BCs[] 	= {	"AUTO","CLAMPED","FREE","BESSEL","QUADRATIC",
								"NOT_A_KNOT","TANGENT"};
	////////////////////////////////////////////////////////////////////////
	switch(nType)
	{
		case 	BC_AUTO:		// should be set to BESSEL
   			str = BCs[3];
			break;
		case 	BC_CLAMPED:
   			str = BCs[1];
			break;
		case 	BC_FREE:
   			str = BCs[2];
			break;
		case 	BC_BESSEL:
   			str = BCs[3];
			break;
		case 	BC_QUADRATIC:
   			str = BCs[4];
			break;
		case 	BC_NOT_A_KNOT:
   			str = BCs[5];
			break;
		case 	BC_TANGENT:
   			str = BCs[6];
			break;
		default:
			break;
	}
	//////////
	return 0;
}

int CCurveGeomPage::CircleTypetoString(CString& str,CIRCLETYPE nType)
{
	switch(nType)
	{
		case 	CIRCLE_BY_ROT:
			str = "1 NODE_ANGLE";
			break;
		case 	CIRCLE_BY_NO3:
			str = "3 NODES";
			break;
		case 	CIRCLE_BY_2N_TI:
			str = "2 NODES_T.INT.";
			break;
		case 	CIRCLE_BY_2N_CC:
			str = "2 NODES_CENTER";
			break;
		case 	CIRCLE_BY_2CN_TI_R:
			str = "2 CN_T.INT_RAD";
			break;
		default:
			break;
	}
	/////////
	return 0;
}

BOOL CCurveGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
