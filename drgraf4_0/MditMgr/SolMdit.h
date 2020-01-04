 // ELMouse.h : header file
//
#ifndef _SOLMDIT_H 
#define _SOLMDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "PatMdit.h"
/////////////////////
#include "DrMesh3D.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSolMdit : public CPatMdit
{
public:

	CSolMdit();
//////////////////////////////////////
	DECLARE_SERIAL(CSolMdit)
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
	int				ShowSolidToEdit(CDrMesh3D* pDrSolid);
	int				ShowSolidInfo(CDrMesh3D* pDrSolid);
	

		
protected:


	//////////////////////////////////////////////
	void		ElementLeftDown_SOL();				// described in derived also
	void		ElementLeftUp_SOL(CPoint point);	// described in derived also
	int			LeftUp_Solid(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Solid
	CDrMesh3D*	m_pCurrentSolid;


//Operations
public:

	~CSolMdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSolMdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
