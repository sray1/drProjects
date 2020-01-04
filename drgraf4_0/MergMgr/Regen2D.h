 // ELMouse.h : header file
//
#ifndef _REGEN2D_H 
#define _REGEN2D_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegen2D : public CMouse
{
public:

	CRegen2D();
//////////////////////////////////////
	DECLARE_SERIAL(CRegen2D)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void		SetCurrentView(CView* v){m_pView = v;};
	int			Update2Ds(CDrFE0D* pDrNode);

protected:
	////////////////////////////////////////////////////////////////// Curve
	int			ReGen_EditedElemNodes(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	/////////////////////////////////////////////////////////////////////////////////// Triangles
	int			ReComputeAddlNodeCoords_TR_3(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_TR_6(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_TR_9(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_TR_10(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	/////////////////////////////////////////////////////////////////////////////////// Quadrilats
	int			ReComputeAddlNodeCoords_QU_4(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_QU_8(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_QU_9(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_QU_12(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);
	int			ReComputeAddlNodeCoords_QU_16(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode);



protected:  
// Attributes





//Operations
public:

	~CRegen2D();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegen2D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
