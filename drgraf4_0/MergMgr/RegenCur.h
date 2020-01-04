 // ELMouse.h : header file
//
#ifndef _REGENCUR_H 
#define _REGENCUR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegenCur : public CMouse
{
public:

	CRegenCur();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenCur)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateCurves(CDrNode* pDrNode);

protected:
	////////////////////////////////////////////////////////////////// Curve
	int				ReGen_EditedCurveControls(CDrCurve* pEditedCurve);

protected:  
// Attributes





//Operations
public:

	~CRegenCur();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenCur)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
