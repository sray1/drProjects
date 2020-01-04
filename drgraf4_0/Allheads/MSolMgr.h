// EDl2Mgr.h : header file
//
#ifndef _MSOLMGR_H
#define _MSOLMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CMSolMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMSolMgr : public CObject
{
// Construction
public:  
	CMSolMgr();
	DECLARE_SERIAL(CMSolMgr)
protected: 
public:
// Implementation 

public:

/*
//	Moved to EditMgr Dll   01/14/98 
	int		ShowSolidToEdit(CDrSolid* pDrSolid);
//	Moved to EditMgr Dll   01/14/98 end 
*/
	////////////////////////////////////////////////////////////// Patch
	UINT	DoModal_SolidCon(CString* pID,int nHowMany);
	UINT 	DoModal_Solid_Extrude(CString* pID,PATSUBTYPE TriORQuad);
	UINT 	DoModal_Solid_Rotate(CString* pID,PATSUBTYPE TriORQuad);
	UINT 	DoModal_Solid_Loft(CString* pID,PATSUBTYPE TriORQuad);
	UINT 	DoModal_Solid_Swip(CString* pID,PATSUBTYPE TriORQuad);
	UINT 	DoModal_Solid_Duct(CString* pID,PATSUBTYPE TriORQuad);
	//////////////////////////////////////////////////////////////
	UINT	DoModal_Solid_LoftX(CDrCurve* pDrCurve,int nLoftCurves);

	UINT	DoModal_Solid_LoftPatchCount(int& nPatches_U);
	UINT	DoModal_Solid_TensorBlend(CDrCurve* pDrCurve,int nLoftCurves,int nDir);
	UINT	DoModal_Solid_TensorNodeCount(int& nNodes_U,int& nNodes_V,int& nNodes_W);
	UINT	DoModal_Solid_GordonPatchCount(int& nPatches_U,int& nPatches_V,int& nPatches_W);
	UINT	DoModal_Solid_TwistFactors(pDOUBLE pTwist,int nMaxTwist,double& dScale);
	UINT	DoModal_Solid_RadiusFactors(pDOUBLE pRadius,int nMaxRadius,double& dScale);
/*
//	Moved to CreOMgr Dll   01/14/98 
	UINT	DoModal_Spawn_S(CDrSolid* pNewSolid,CString* pID,CString& ParentCid);
//	UINT 	DoModal_Solid_Post(CString* pID);
	CDrSolid*	SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp);
//	Moved to CreOMgr Dll   01/14/98 end 
*/

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMSolMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMSolMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
