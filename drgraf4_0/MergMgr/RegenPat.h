 // ELMouse.h : header file
//
#ifndef _REGENPAT_H 
#define _REGENPAT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegenPat : public CMouse
{
public:

	CRegenPat();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenPat)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdatePatches(CDrNode* pDrNode);

protected:
	////////////////////////////////////////////////////////////////// Patch
	int				ReGen_EditedPatchControls(CDrPatch* pEditedPatch);
	int				SetUp_EditedPatchControls(CDrPatch* pEditedPatch);
	int				ReGen_Controls_EXTRUDE(CDrPatch* pEditedPatch,CString* pID);
	int				ReGen_Controls_ROTATE(CDrPatch* pEditedPatch,CString* pID);
	int				ReGen_Controls_LOFT2(CDrPatch* pEditedPatch,CString* pID);
	int				ReGen_Controls_DUCT(CDrPatch* pEditedPatch,CString* pID);
	int				ReGen_Controls_SWEEP(CDrPatch* pEditedPatch,CString* pID);
	int				ReGen_Controls_COONS(CDrPatch* pEditedPatch,CString* pID);

protected:  
// Attributes





//Operations
public:

	~CRegenPat();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenPat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
