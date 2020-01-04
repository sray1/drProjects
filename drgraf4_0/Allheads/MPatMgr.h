// EDl2Mgr.h : header file
//
#ifndef _MPATMGR_H
#define _MPATMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CMPatMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMPatMgr : public CObject
{
// Construction
public:  
	CMPatMgr();
	DECLARE_SERIAL(CMPatMgr)
protected: 
public:
// Implementation 

public:

	int		ShowPatchToEdit(CDrPatch* pDrPatch);
	////////////////////////////////////////////////////////////// Patch
/*
	UINT	DoModal_PatchCon(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_Extrude(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_Rotate(CString* pID,int nHowMany);
*/
	UINT 	DoModal_Patch_Loft(CString* pID,int nHowMany);

	UINT	DoModal_Patch_LoftX(CDrCurve* pDrCurve,int nLoftCurves);

	UINT	DoModal_Patch_LoftCurveCount(int& nCurves_U);
	UINT	DoModal_Patch_TensorBlend(CDrCurve* pDrCurve,int nLoftCurves,int nDir);
	UINT	DoModal_Patch_TensorNodeCount(int& nNodes_U,int& nNodes_V);
	UINT	DoModal_Patch_GordonCurveCount(int& nCurves_U,int& nCurves_V);
	UINT	DoModal_Patch_TwistFactors(pDOUBLE pTwist,int nMaxTwist,double& dScale);
	UINT	DoModal_Patch_RadiusFactors(pDOUBLE pRadius,int nMaxRadius,double& dScale);
/*
	UINT 	DoModal_Patch_Swip(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_Duct(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_Coon(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_CoP3(CString* pID,int nHowMany);
	UINT 	DoModal_Patch_Co34(UINT* pIn,int nHowMany);
*/
//	UINT 	DoModal_Patch_Post(CString* pID);
	//////////////////////////////////////////////////////////////
/*
//	Moved to CreOMgr Dll   01/14/98 
	UINT	DoModal_Spawn_P(CDrPatch* pNewPatch,CString* pID,CString& ParentCid);
	CDrPatch*	SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp);
//	Moved to EditMgr Dll   01/14/98 end
*/ 



protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMPatMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMPatMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
