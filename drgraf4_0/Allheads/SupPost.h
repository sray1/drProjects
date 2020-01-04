 // ELMouse.h : header file
//
#ifndef _SUP_DEL_H 
#define _SUP_DEL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "SolDel.h"
/////////////////////
#include "DrLinSup.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSupDel : public CSolDel
{
public:

	CSupDel();
//////////////////////////////////////
	DECLARE_SERIAL(CSupDel)
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

	////////////////////////////////////////////////////////////////////////////////
	int			ShowLinSuppToBeDeleted(CDrLinSup* pDrLinSup, BOOL bToBeDeleted);
	int			MarkLinSupp_Delete(CDrLinSup* pDrLinSup);
	///////////////////////////////////////////////////////// NodeLinSup
	int			ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart);
	int			MarkNodeLinSupp_Delete(CDrNode* pDrNode, int nType, BOOL bToBeDeleted);
	int 		LeftUp_NodeLinSupp(CPoint point);
	///////////////////////////////////////////////////////// CurveLinSup
	int			ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart);
	int			MarkCurveLinSupp_Delete(CDrCurve* pDrCurve, int nType, BOOL bToBeDeleted);
	int			LeftUp_CurveLinSupp(CPoint point);
	///////////////////////////////////////////////////////// PatchLinSup
	int			ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart);
	int			MarkPatchLinSupp_Delete(CDrPatch* pDrPatch, int nType, BOOL bToBeDeleted);
	int			LeftUp_PatchLinSupp(CPoint point);
	///////////////////////////////////////////////////////// SolidLinSup
	int			ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart);
	int			MarkSolidLinSupp_Delete(CDrSolid* pDrSolid, int nType, BOOL bToBeDeleted);
	int			LeftUp_SolidLinSupp(CPoint point);


protected:  
// Attributes


	UINT		m_nMainType;		// NSUP_RIGID etc
	/////////////////////////////////////////// Support
	CDrLinSup*	m_pCurrentSupp;



//Operations
public:

	~CSupDel();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSupDel)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
