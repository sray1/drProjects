 // ELMouse.h : header file
//
#ifndef _SLD_MOUSE_H 
#define _SLD_MOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SupMouse.h"
#include "SLDPat.h"
///////////////////// Modeless
#include "Dlg_StLI.h"
/////////////////////
#include "DrStatic.h" 	
#include "DrNode.h" 	
#include "DrLabel.h" 	
#include "DrCurve.h" 	
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "Def_StaL.h"	// support                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSLDMouse : public CSupMouse
{
public:

	CSLDMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SLD(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_SLD();
	void			ModeLessOff_SLD();
	void			ModeLessOn_SLD();
	CDlg_StLI*		GetStLInDlg(){return m_pStLInDlg;};	// NodeLinSup(NLS)                                                                                
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
	/////////////////////////////////////////////////////////////////////////// Force_Moment
	long			CreateorActivateF_MIn(UINT wParam, long lParam);
	long			CancelF_MIn(UINT wParam, long lParam);
	long			GoodByeF_MIn(UINT wParam, long lParam);
	long			UpdateF_MIn(UINT wParam, long lParam);
	/////////////////////////////////////////////////////////////////////////// Force_Moment
	long			CreateorActivateD_RIn(UINT wParam, long lParam);
	long			CancelD_RIn(UINT wParam, long lParam);
	long			GoodByeD_RIn(UINT wParam, long lParam);
	long			UpdateD_RIn(UINT wParam, long lParam);
	/////////////////////////////////////////////////////////////////////////// Force_Moment
	long			CreateorActivatePrsIn(UINT wParam, long lParam);
	long			CancelPrsIn(UINT wParam, long lParam);
	long			GoodByePrsIn(UINT wParam, long lParam);
	long			UpdatePrsIn(UINT wParam, long lParam);
	/////////////////////////////////////////////////////////////////////////// Force_Moment
	long			CreateorActivateThrIn(UINT wParam, long lParam);
	long			CancelThrIn(UINT wParam, long lParam);
	long			GoodByeThrIn(UINT wParam, long lParam);
	long			UpdateThrIn(UINT wParam, long lParam);
	/////////////////////////////////////////////////////////////////////////// Force_Moment
	long			CreateorActivateLWtIn(UINT wParam, long lParam);
	long			CancelLWtIn(UINT wParam, long lParam);
	long			GoodByeLWtIn(UINT wParam, long lParam);
	long			UpdateLWtIn(UINT wParam, long lParam);
	//////////////////////////////////////////////////////
	virtual STALPROC	GetStaLProc(){return m_StaLProc;};
	virtual void		SetStaLProc(STALPROC b)
						{
							m_StaLProcOld	= m_StaLProc;
							m_StaLProc		= b;
						};
	BOOL		GetTx(){return m_bTx;};
	void		SetTx(BOOL b){ m_bTx = b;};
	BOOL		GetTy(){return m_bTy;};
	void		SetTy(BOOL b){ m_bTy = b;};
	BOOL		GetTz(){return m_bTz;};
	void		SetTz(BOOL b){ m_bTz = b;};
	BOOL		GetRx(){return m_bRx;};
	void		SetRx(BOOL b){ m_bRx = b;};
	BOOL		GetRy(){return m_bRy;};
	void		SetRy(BOOL b){ m_bRy = b;};
	BOOL		GetRz(){return m_bRz;};
	void		SetRz(BOOL b){ m_bRz = b;};

  				
		
protected:


	void		ElementLeftDown_SLD();				// described in derived also
	void		ElementLeftUp_SLD(CPoint point);	// described in derived also
	////////////////////////////////////////////////////////////////////////////////
	void		SetMainType_SLD();
	////////////////////////////////////////////////////////////////////////////////
	void		Init_SLD();
	void		Terminate_SLD(BOOL bError);
	int			UpdateSLDObjInfo();
	int			ShowStatic(CString* pID);
	int			ShowStatic_Node(CString* pID);
	int			ShowStatic_Curve(CString* pID);
	int			ShowStatic_Patch(CString* pID);
	int			ShowStatic_Solid(CString* pID);
	void		UpdateDlgIn_TRUE();
	void		UpdateDlgIn_FALSE();
	void		UpdateStaticDlg_TRUE();
	void		CurrentOperationString(UINT CntlID,UINT IGenID,CString& strCur);
	void		UpdateStaticDlg_FALSE();
	int			LeftUp_Node_SLDContext(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	int			NewNode_N_Update_SLDContext(CString& NodeID,CPoint point,BOOL bCNode);
	int			OldNode_N_Update_SLDContext(BOOL bCNode,BOOL bDistinct);
	int			LeftUp_JC_X_FIXEDDIR_SLD(POINT point);
	int			LeftUp_JC_X_TAN_CURVE_SLD(POINT point);
	int			LeftUp_JC_Z_NOR_PATCH_SLD(POINT point);
	int			LeftUp_GetNodeStatic(CPoint point);
	int			LeftUp_Node_Accept_NodeBased(CPoint point,BOOL bCNode);
	int			Show_NodeBased_NodeInfo(CDrNode* pDrNode);
	int			Show_CurveBased_CurveInfo(CDrCurve* pDrCurve);
	int			LeftUp_GetCurveStatic(CPoint point);
	int			LeftUp_Curve_Accept(CPoint point);
	int			Show_PatchBased_PatchInfo(CDrPatch* pDrPatch);
	int			LeftUp_GetPatchStatic(CPoint point);
	int			LeftUp_Patch_Accept(CPoint point);
	int			ShowSolidInfo(CDrSolid* pDrSolid);
	int			ShowInfo_SolidStatic(CDrSolid* pDrSolid, char* buf, int jStart);
	int			LeftUp_Static_Solid(CPoint point);
	int			LeftUp_Solid_Accept(CPoint point);
	int			LeftUp_Static_NODE(POINT point,UINT uStaLProc,JOINTCOORD jcType);
	int			GetValues_CURVE();
	int			LeftUp_Static_CURVE(POINT point,UINT uStaLProc,JOINTCOORD jcType);
	int			GetValues_PATCH();
	int			LeftUp_Static_PATCH(POINT point,UINT uStaLProc,JOINTCOORD jcType);
	int			GetValues_SOLID();
	int			LeftUp_Static_SOLID(POINT point,UINT uStaLProc,JOINTCOORD jcType);
	int			RightUp_Static_Error();
	int			RightUp_Static_Premature();
	int			RightUp_Static_NotAutoAccept();
	int			ShowAcceptInfo_Static(char* buf, int& j);
	int			ShowAcceptInfo_NodeBased(CDrNode* pDrNode, char* buf, int& j);
	int			ShowAcceptInfo_CurveBased(CDrCurve* pDrCurve, char* buf, int& j);
	int			ShowAcceptInfo_PatchBased(CDrPatch* pDrPatch, char* buf, int& j);
	int			ShowAcceptInfo_SolidBased(CDrSolid* pDrSolid, char* buf, int& j);
	////////////////////////////////////////////////////////////////////	





protected:  
// Attributes


	BOOL		m_bStaLDone;
	BOOL    	m_bUniform;
	////////////////////////
	BOOL		m_bIso;
	BOOL    	m_bConOrDis;
	BOOL    	m_bCN_a;
	BOOL    	m_bCN_b;
	////////////////////
	CSLDPat		m_SLDPat;
	//////////////////////////
	CDlg_StLI*	m_pStLInDlg;                                                                                
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
	CString		m_cid_Iso;		// Iso  or NonIso to this Curve				
	CString		m_cid_Parent;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	CString		m_aNid;			// already in supMpouse
								// NodeToID for StaticNodeInput (Skewed), but
								// NodeFromID for StaticCurveInput (Skewed)
	CString		m_bNid;			// NodeToID for StaticCurveInput (Skewed)
	BOOL		m_bTan;			// already in supMpouse
	//////////////////////////////
	pDOUBLE		m_dUnif;
	/////////////////////// NonIso
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

	~CSLDMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
