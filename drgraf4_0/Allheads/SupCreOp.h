 // ELMouse.h : header file
//
#ifndef _SUP_CREOP_H 
#define _SUP_CREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "SolCreOp.h"
/////////////////////
#include "DrLinSup.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSupCreOp : public CSolCreOp
{
public:

	CSupCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CSupCreOp)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SUP(UINT CntlID,UINT IGenID, UINT OperID);
	/////////////////////
	void 			OnEBoxMouseMove_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_SUP(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
  				
		
protected:


	virtual void	ElementLeftDown_SUP();				// described in derived also
	virtual void	ElementLeftUp_SUP(CPoint point);	// described in derived also
	////////////////////////////////////////////////////////////////////////////////
	void		SetMainType_SUP();
	////////////////////////////////////////////////////////////////////////////////
	int			FillInfo_Rigid(SUPPCARD supCard,char* buf, int jStart);
	int			FillInfo_SprOrSnu(CString& Nid,SUPPCARD supCard,char* buf, int jStart,BOOL bPat);
	///////////////////////////////////////////////////////// NodeLinSup
	int			ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart);
	int 		ShowNodeLinSuppToEdit();
	int 		LeftUp_NodeLinSupp(CPoint point);
	///////////////////////////////////////////////////////// CurveLinSup
	int			ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart);
	int			ShowCurveLinSuppToEdit();
	int			LeftUp_CurveLinSupp(CPoint point);
	///////////////////////////////////////////////////////// PatchLinSup
	int			ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart);
	int			ShowPatchLinSuppToEdit();
	int			LeftUp_PatchLinSupp(CPoint point);
	///////////////////////////////////////////////////////// SolidLinSup
	int			ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart);
	int			ShowSolidLinSuppToEdit();
	int			LeftUp_SolidLinSupp(CPoint point);
	///////////////////////////////////////////////////////// MsgBox
	void		NoRigidEdit_Msg();

protected:  
// Attributes


	UINT		m_nMainType;		// NSUP_RIGID etc
	/////////////////////////////////////////// Support
	CDrLinSup*	m_pCurrentSupp;



//Operations
public:

	~CSupCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSupCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
