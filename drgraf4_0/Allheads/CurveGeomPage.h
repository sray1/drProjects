#if !defined(AFX_CURVEGEOMPAGE_H__AA812A6E_7244_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CURVEGEOMPAGE_H__AA812A6E_7244_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurveGeomPage.h : header file
//

#include "DbRsrc.h"
#include "DrCurve.h"
#include "Def_CuPs.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveGeomPage dialog

class CCurveGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveGeomPage)

// Construction
public:
	CCurveGeomPage();
	~CCurveGeomPage();

// Dialog Data
	//{{AFX_DATA(CCurveGeomPage)
	enum { IDD = IDD_CURVE_GEOM };
	double	m_AxisX;
	double	m_AxisY;
	double	m_AxisZ;
	CString	m_BCLeft;
	CString	m_BCRight;
	int		m_BZSegs;
	double	m_CenterX;
	double	m_CenterY;
	double	m_CenterZ;
	CString	m_CircleType;
	CString	m_Class;
	BOOL	m_bClosed;
	BOOL	m_bIso;
	CString	m_IsoTo;
	CString	m_KnotType;
	double	m_Radius;
	double	m_Ratio;
	double	m_TanX;
	double	m_TanY;
	double	m_TanZ;
	double	m_TotAngle;
	double	m_TotElems;
	BOOL	m_bUniform;
	CString	m_WeightType;
	CString	m_CurveID;
	CString	m_CurveType;
	CString	m_Degree;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);
	int		UpdateInfo(CDrCurve* pObject);


protected:

	int		UpdateInfoCurve(CDrCurve* pObject);
	int		UpdateInfoCircle(CDrCurve* pObject);
	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	int		UpdateCombo_Double(pDOUBLE pData, int nData, UINT DlgComboID);
	int		UpdateCombo_Int(pINT pData, int nData, UINT DlgComboID);
	int		CurveProctoString(CString& str,CURVEPROC nType);
	int		DegreeTypetoString(CString& str,int nType);
	int		ClassTypetoString(CString& str,int nType);
	int		KnotTypetoString(CString& str,int nType);
	int		WeightTypetoString(CString& str,int nType);
	int		BCTypetoString(CString& str,BOUNDARY nType);
	int		CircleTypetoString(CString& str,CIRCLETYPE nType);



protected:

	CDrCurve*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEGEOMPAGE_H__AA812A6E_7244_11D2_8B46_444553540000__INCLUDED_)
