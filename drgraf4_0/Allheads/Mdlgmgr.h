// EDl2Mgr.h : header file
//
#ifndef _MDLGMGR_H
#define _MDLGMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "glb_Type.h"
#include "glb_CuPS.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
/////////////////////////////////////////////////////////////////////////////
// CMDlgMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMDlgMgr : public CObject
{
// Construction
public:  
	CMDlgMgr();
	DECLARE_SERIAL(CMDlgMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// Curve 
	UINT	DoModal_Cur_Advance_In(CDrCurve* pDrCurve,int nOrder);
	UINT	DoModal_CIRCLE_Type(CIRCLETYPE& nType);						// Circle Type
	////////////////////////////////////////////////////////////// Patch
	////////////////////////////////////////////////////////////// Solid
	//////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMDlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMDlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
