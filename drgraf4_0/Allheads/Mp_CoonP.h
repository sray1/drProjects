 // mp_Loft2.h : header file
//
#ifndef _MP_COONP_H 
#define _MP_COONP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_CoonP : public CMI_GangP
class AFX_EXT_CLASS CMP_CoonP : public CMI_GangP
{
public:

	CMP_CoonP();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_CoonP)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrPatch*	GoDoIt(); 
	int			GoDoIt(
						CString&	PatchID,		
						CDrPatch*	pDrPatch,
//						CString		PatCurveID[],
						CDListMgr*	pCurveList,
//						CURVELATCH	PatCurveLatchID[]
						CList<CURVELATCH,CURVELATCH>*	pLatchList
				     );
	int 		Coon(); 
	int			Coon_ByControl();

    				
		
protected:

	int			FindIfPatByControl(BOOL* bSdir,BOOL* bTdir);
	BOOL		CheckElemCompatibility();
	void		SetInfoForCoonBase(CDrPatch* pDrObject);
	void		SetInfoForCoonBase_ByControl(CDrPatch* pDrObject);
	////////////////////////////////////////////////////////////
	CDrPatch* 	GetInfo();
	int 		GenerateCNodes();
	/////////////////////////
	int			Pre_Curve(CDrCurve* pDrCurve,int i, int nOut);
	int			Pre_Curve_ByControl(CDrCurve* pDrCurve,int i, int nOut);
	int			Curve_S_Process();
	int			Curve_T_Process();
	int			GetInfo_Curve_T(CDrCurve* pDrCurve);
	int			GetInfo_Curve_T_ByControl(CDrCurve* pDrCurve);

	

protected:  
// Attributes
	CString		m_PatchID;
	BOOL		m_bSdirByControl;
	BOOL		m_bTdirByControl;


//Operations
public:

	~CMP_CoonP();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_CoonP)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
