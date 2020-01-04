#if !defined(AFX_PATCH_GEOM_H__F1213066_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_PATCH_GEOM_H__F1213066_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Patch_Geom.h : header file
//

#include "DbRsrc.h"
#include "DrPatch.h"
#include "Def_CuPs.h"
/////////////////////////////////////////////////////////////////////////////
// CPatchGeomPage dialog

class CPatchGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPatchGeomPage)

// Construction
public:
	CPatchGeomPage();
	~CPatchGeomPage();

// Dialog Data
	//{{AFX_DATA(CPatchGeomPage)
	enum { IDD = IDD_PATCH_GEOM };
	double	m_AxisX;
	double	m_AxisY;
	double	m_AxisZ;
	double	m_CenterX;
	double	m_CenterY;
	double	m_CenterZ;
	CString	m_Class;
	BOOL	m_bIso;
	CString	m_IsoTo;
	double	m_Radius;
	double	m_TotAngle;
	double	m_TotElems;
	BOOL	m_bClosed_S;
	BOOL	m_bClosed_T;
	double	m_dLenX;
	double	m_dLenY;
	double	m_dLenZ;
	int		m_TotNodeU;
	int		m_TotNodeV;
	int		m_TotNodeW;
	CString	m_PatchID;
	CString	m_PatchProc;
	CString	m_PatchSubType;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);
	int		UpdateInfo(CDrPatch* pObject);


protected:

	int		UpdateInfoQuadrilateral(CDrPatch* pObject);
	int		UpdateInfoTriangular(CDrPatch* pObject);
	int		UpdateInfoCurve(CDrPatch* pObject);
	int		UpdateInfoExtrusion(CDrPatch* pObject);
	int		UpdateInfoLoft2(CDrPatch* pObject);
	int		UpdateInfoCoons(CDrPatch* pObject);
	int		UpdateInfoGordon(CDrPatch* pObject);
	int		UpdateInfoRevolution(CDrPatch* pObject);
	int		UpdateInfoDuct(CDrPatch* pObject);
	int		UpdateInfoSweep(CDrPatch* pObject);
	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	int		UpdateCombo_Double(pDOUBLE pData, int nData, UINT DlgComboID);
	int		UpdateCombo_Int(pINT pData, int nData, UINT DlgComboID);
	int		PatchProctoString(CString& str,PATCHPROC nType,CDrPatch* pObject);
	int		DegreeTypetoString(CString& str,int nType);
	int		ClassTypetoString(CString& str,int nType);
	int		PatchSubTypetoString(CString& str,PATSUBTYPE nType);



protected:

	CDrPatch*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPatchGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPatchGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATCH_GEOM_H__F1213066_72EF_11D2_8B46_444553540000__INCLUDED_)
