// EDl2Mgr.h : header file
//
#ifndef _EDITDLGM_H
#define _EDITDLGM_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "DrFE0D.h"
#include "DrMesh1D.h"
#include "DrMesh2D.h"
#include "DrMesh3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMditDlgM
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMditDlgM : public CObject
{
// Construction
public:  
	CMditDlgM();
	DECLARE_SERIAL(CMditDlgM)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber);
	UINT		DoModal_ShowCurveToEdit(CDrMesh1D* pDrCurve, int nViewNumber);
	UINT		DoModal_ShowPatchToEdit(CDrMesh2D* pDrPatch, int nViewNumber);
	UINT		DoModal_ShowSolidToEdit(CDrMesh3D* pDrSolid, int nViewNumber);
	//////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMditDlgM();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMditDlgM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
