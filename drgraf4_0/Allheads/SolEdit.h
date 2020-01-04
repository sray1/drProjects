 // ELMouse.h : header file
//
#ifndef _SOLEDIT_H 
#define _SOLEDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "PatEdit.h"
/////////////////////
#include "DrSolid.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSolEdit : public CPatEdit
{
public:

	CSolEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CSolEdit)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID);
	/////////////////////
	void 			OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
 	///////////////////////////////////////////////////// NODE
	int				ShowSolidToEdit(CDrSolid* pDrSolid);
	int				ShowSolidInfo(CDrSolid* pDrSolid);
	

		
protected:


	//////////////////////////////////////////////
	void		ElementLeftDown_SOL();				// described in derived also
	void		ElementLeftUp_SOL(CPoint point);	// described in derived also
	int			LeftUp_Solid(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Solid
	CDrPatch*	m_pCurrentSolid;


//Operations
public:

	~CSolEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSolEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
