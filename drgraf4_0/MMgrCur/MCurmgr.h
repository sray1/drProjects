// EDl2Mgr.h : header file
//
#ifndef _MCURMGR_H
#define _MCURMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h"
#include "DrCurve.h"
/////////////////////////////////////////////////////////////////////////////
// CMCurMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMCurMgr : public CObject
{
// Construction
public:  
	CMCurMgr();
	DECLARE_SERIAL(CMCurMgr)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowCurveToEdit(CDrCurve* pDrCurve);
	////////////////////////////////////////////////////////////// Curve 
	UINT		DoModal_Cur_Advance_In(CDrCurve* pDrCurve,int nOrder);
	UINT		DoModal_CIRCLE_Type(CIRCLETYPE& nType);						// Circle Type
	//////////////////////////////////////////////////////////////
	UINT		DoModal_Cur_I_LB(CString* pID,int nHowMany);  //Interpolate:Left Button
	UINT		DoModal_Cur_I_RB(CString* pID,int nHowMany);  //Interpolate:Right Button
	UINT		DoModal_Cur_I_CIRCLE(CString* pID,int nHowMany);  //Interpolate:Right Button
	UINT		DoModal_Profile_C(CString* pID,int nHowMany);
	UINT		DoModal_Profile_C_ShowInfo(CString* pID,CDListMgr* pCurveList);  	//Profile
/*
	UINT		DoModal_Spawn_C(CDrCurve* pNewCurve,CString* pID,CString* pParentID);
	///////////////////////////////////////////////////////////////
	CDrCurve*	SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp);
*/

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMCurMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMCurMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
