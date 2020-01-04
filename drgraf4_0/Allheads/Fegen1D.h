 // ELMouse.h : header file
//
#ifndef _REGEN1D_H 
#define _REGEN1D_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegen1D : public CMouse
{
public:

	CRegen1D();
//////////////////////////////////////
	DECLARE_SERIAL(CRegen1D)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			SetCurrentView(CView* v){m_pView = v;};
	int				Update1Ds(CDrFE0D* pDrNode);

protected:
	////////////////////////////////////////////////////////////////// Curve
	int				ReGen_EditedElemNodes(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int				ReComputeAddlNodeCoords_TRUSS(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int				ReComputeAddlNodeCoords_BEAM(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int				ReComputeAddlNodeCoords_PIPE(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int				ReComputeAddlNodeCoords_ELBOW(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);



protected:  
// Attributes





//Operations
public:

	~CRegen1D();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegen1D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
