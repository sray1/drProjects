 // ELMouse.h : header file
//
#ifndef _SLD_EDIT_H 
#define _SLD_EDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SupEdit.h"
#include "SLDPat.h"
/////////////////////
#include "DrStatic.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSLDEdit : public CSupEdit
{
public:

	CSLDEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDEdit)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SLD(UINT CntlID,UINT IGenID, UINT OperID);
	/////////////////////
	void 			OnEBoxMouseMove_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_SLD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);

  				
		
protected:


	virtual void	ElementLeftDown_SLD();				// described in derived also
	virtual void	ElementLeftUp_SLD(CPoint point);	// described in derived also
	////////////////////////////////////////////////////////////////////////////////
	void			SetMainType_SLD();
	////////////////////////////////////////////////////////////////////////////////
	void			FillStaticInfo(CDrStatic* pStatic);
	void			UpdateSLEObjInfo();

	int 			LeftUp_NodeStatic(CPoint point);
	int				LeftUp_CurveStatic(CPoint point);
	int				LeftUp_PatchStatic(CPoint point);


protected:  
// Attributes


	BOOL		m_bStaLDone;
	////////////////////
	CSLDPat		m_SLEPat;		// Needs TOBE changed to CSLDSol
	/////////////////////////////////////////// Static
	CString		m_CurrentStLID;
	CString		m_CurrentStLIDOld;
	CString		m_CurrentStCID;
	CString		m_CurrentStCIDOld;
	CDrCurve	*m_pCurrentSCurveT[4];	// Iso or NonIso curve
	CDrCurve	*m_pCurrentSCurveR[4];	// Iso or NonIso curve
	CDrStatic*	m_pCurrentStaL;
	STALPROC	m_StaLProcOld;
	STALPROC	m_StaLProc;
	BOOL    	m_bTx;
	BOOL    	m_bTy;
	BOOL    	m_bTz;
	BOOL    	m_bRx;
	BOOL    	m_bRy;
	BOOL    	m_bRz;
	///
	double		m_dTx;
	double		m_dTy;
	double		m_dTz;
	double		m_dRx;
	double		m_dRy;
	double		m_dRz;
	///
	CString		m_cid_Iso;		// Iso  or NonIso to this Curve				
	CString		m_cid_ParentT;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve) Tran				
	CString		m_cid_ParentR;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)	Rot			
	CString		m_cid_Parent;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	CString		m_aNid;			// Should be in supEdit
	CString		m_bNid;			// NodeToID for StaticCurveInput (Skewed)
	BOOL    	m_bCN_a;
	BOOL    	m_bCN_b;
	BOOL		m_bTanCur;			// already in supMpouse
	BOOL		m_bTanPat;			// already in supMpouse
	BOOL		m_bNorPat;			// already in supMpouse
	UINT		m_GenKind;
	///
	CString		m_ID_CP;
	JOINTCOORD	m_jcType;
	BOOL    	m_bUniform;
	BOOL    	m_bConOrDis;
	//////////////////////////////
	WORLD		m_SkewDir;
	pDOUBLE		m_dUnif;
	/////////////////////// NonIso
	BOOL		m_bIso;
	BOOL		m_bNonIso;
	CString		m_CID;
	BOOL		m_bIncrement;
	CString		m_Orient;
	double		m_dScale;
	double		m_dStep;
	double		m_dStart;
	/////////////////////////////////////////////////////////////////// Patch
	CString		m_CurrentStPID;
	CString		m_CurrentStPIDOld;
	//////////////////////////
	BOOL		m_bGravMul;



//Operations
public:

	~CSLDEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif