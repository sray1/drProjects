 // ELMouse.h : header file
//
#ifndef _REGENSOL_H 
#define _REGENSOL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CRegenSol : public CMouse
{
public:

	CRegenSol();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenSol)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateSolids(CDrNode* pDrNode);

protected:
	////////////////////////////////////////////////////////////////// Solid
	int				ReGen_EditedSolidControls(CDrSolid* pEditedSolid);
	int				SetUp_EditedSolidControls(CDrSolid* pEditedSolid);
	int				ReGen_Controls_EXTRUDE(CDrSolid* pEditedSolid,CString* pID);
	int				ReGen_Controls_ROTATE(CDrSolid* pEditedSolid,CString* pID);
	int				ReGen_Controls_LOFT2(CDrSolid* pEditedSolid,CString* pID);
	int				ReGen_Controls_DUCT(CDrSolid* pEditedSolid,CString* pID);
	int				ReGen_Controls_SWEEP(CDrSolid* pEditedSolid,CString* pID);
	int				ReGen_Controls_COONS(CDrSolid* pEditedSolid,CString* pID);

protected:  
// Attributes





//Operations
public:

	~CRegenSol();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenSol)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
