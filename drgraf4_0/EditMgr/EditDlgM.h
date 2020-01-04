// EDl2Mgr.h : header file
//
#ifndef _EDITDLGM_H
#define _EDITDLGM_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CEditDlgM
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CEditDlgM : public CObject
{
// Construction
public:  
	CEditDlgM();
	DECLARE_SERIAL(CEditDlgM)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber);
	UINT		DoModal_ShowCurveToEdit(CDrCurve* pDrCurve, int nViewNumber);
	UINT		DoModal_ShowPatchToEdit(CDrPatch* pDrPatch, int nViewNumber);
	UINT		DoModal_ShowSolidToEdit(CDrSolid* pDrSolid, int nViewNumber);
	//////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CEditDlgM();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CEditDlgM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
