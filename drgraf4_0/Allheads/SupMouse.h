 // ELMouse.h : header file
//
#ifndef _SUP_MOUSE_H 
#define _SUP_MOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "O3DMouse.h"
///////////////////// Modeless
#include "Dlg_SupI.h"
/////////////////////
#include "DrLinSup.h" 	
#include "DrNode.h" 	
#include "DrLabel.h" 	
#include "DrCurve.h" 	
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "str_Supp.h"	// support                    
#include "Def_Supp.h"	// support                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSupMouse : public CO3DMouse
{
public:

	CSupMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CSupMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SUP(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_SUP();
	void			ModeLessOff_SUP();
	void			ModeLessOn_SUP();
	CDlg_SupI*		GetSupInDlg(){return m_pSupInDlg;};	// NodeLinSup(NLS)                                                                                
	//////////////////////////////
	long			CreateorActivateSupIn(UINT wParam, long lParam);
	long			CancelSupIn(UINT wParam, long lParam);
	long			GoodByeSupIn(UINT wParam, long lParam);
	long			UpdateSupIn(UINT wParam, long lParam);
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
	/////////////////////////////////////////////////////////////////////////// SUPPORT
	double		GetDfaltStif(){return m_DfaltStif;};
    void		SetDfaltStif(double St)
    					{
    						m_DfaltStif = St;
    					}; 
	double		GetCurrentStif(int index){return m_CurrentStif[index];};
    void		SetCurrentStif(double St,int index)
    					{
    						m_CurrentStif[index] = St;
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

	BOOL		GetTxG(){return m_bTxG;};
	void		SetTxG(BOOL b){ m_bTxG = b;};
	BOOL		GetTyG(){return m_bTyG;};
	void		SetTyG(BOOL b){ m_bTyG = b;};
	BOOL		GetTzG(){return m_bTzG;};
	void		SetTzG(BOOL b){ m_bTzG = b;};
	BOOL		GetRxG(){return m_bRxG;};
	void		SetRxG(BOOL b){ m_bRxG = b;};
	BOOL		GetRyG(){return m_bRyG;};
	void		SetRyG(BOOL b){ m_bRyG = b;};
	BOOL		GetRzG(){return m_bRzG;};
	void		SetRzG(BOOL b){ m_bRzG = b;};

	SUPPPROC	GetSuppProc(){return m_SuppProc;};
	void		SetSuppProc(SUPPPROC b)
						{
							m_SuppProcOld	= m_SuppProc;
							m_SuppProc		= b;
						};
  				
		
protected:


	void		Init_SUP();
	void		Terminate_SUP(BOOL bError);
	void		ElementLeftDown_SUP();				// described in derived also
	void		ElementLeftUp_SUP(CPoint point);	// described in derived also
	////////////////////////////////////////////////////////////////////////////////
	void		SetMainType_SUP();
	void		CurrentOperationString(UINT CntlID,UINT IGenID,CString& strCur);
	////////////////////////////////////////////////////////////////////////////////
	void		UpdateLinSupDlg_TRUE();
	void		UpdateLinSupDlg_FALSE();
	int			FillSupCard(SUPPCARD& supCard,CString* pID);
	////////////////////////
	int			ShowLinSupp(CString* pID);
	int			ShowInfo_SupCard(SUPPCARD& supCard, char* buf, int jStart);
	int			ShowInfo_Rigid(SUPPCARD supCard,char* buf, int jStart);
	int			ShowInfo_SprOrSnu(SUPPCARD supCard,char* buf, int jStart);
	int			LeftUp_JC_X_FIXEDDIR_SUP(POINT point);
	int			LeftUp_JC_X_TAN_CURVE_SUP(POINT point);
	int			LeftUp_JC_Z_NOR_PATCH_SUP(POINT point);
	int			ShowAcceptInfo_Support(char* buf, int& j);
	///////////////////////////////////////////////////////// NodeLinSup
	int			LeftUp_LinSupp_NODE(POINT point,UINT uSuppProc,JOINTCOORD jcType);
	int			ShowLinSupp_Node(CString* pID);
	int			LeftUp_Node_SupContext(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	int			NewNode_N_Update_SUPContext(CString& NodeID,CPoint point,BOOL bCNode);
	int			OldNode_N_Update_SUPContext(BOOL bCNode,BOOL bDistinct);
	int			ShowInfo_NodeLinSupport(CDrNode* pDrNode, char* buf, int jStart);
	int			LeftUp_GetNodeLinSupp(CPoint point);
	int			LeftUp_Node_Accept_NodeBased(CPoint point,BOOL bCNode);
	int			Show_NodeBased_NodeInfo(CDrNode* pDrNode);
	int			ShowAcceptInfo_NodeBased(CDrNode* pDrNode, char* buf, int& j);
	///////////////////////////////////////////////////////// CurveLinSup
	int			LeftUp_LinSupp_CURVE(POINT point,UINT uSuppProc,JOINTCOORD jcType);
	int			ShowLinSupp_Curve(CString* pID);
	int			Show_CurveBased_CurveInfo(CDrCurve* pDrCurve);
	int			ShowInfo_CurveLinSupport(CDrCurve* pDrCurve, char* buf, int jStart);
	int			LeftUp_GetCurveLinSupp(CPoint point);
	int			LeftUp_Curve_Accept(CPoint point);
	int			ShowAcceptInfo_CurveBased(CDrCurve* pDrCurve, char* buf, int& j);
	///////////////////////////////////////////////////////// PatchLinSup
	int			LeftUp_LinSupp_PATCH(POINT point,UINT uSuppProc,JOINTCOORD jcType);
	int			ShowLinSupp_Patch(CString* pID);
	int			ShowInfo_PatchLinSupport(CDrPatch* pDrPatch, char* buf, int jStart);
	int			Show_PatchBased_PatchInfo(CDrPatch* pDrPatch);
	int			LeftUp_GetPatchLinSupp(CPoint point);
	int			LeftUp_Patch_Accept(CPoint point);
	int			ShowAcceptInfo_PatchBased(CDrPatch* pDrPatch, char* buf, int& j);
	///////////////////////////////////////////////////////// SolidLinSup
	int			ShowLinSupp_Solid(CString* pID);
	int			ShowSolidInfo(CDrSolid* pDrSolid);
	int			ShowInfo_SolidLinSupport(CDrSolid* pDrSolid, char* buf, int jStart);
	int			LeftUp_SolidLinSupp(CPoint point);
	int			LeftUp_Solid_Accept(CPoint point);
	int			ShowAcceptInfo_SolidBased(CDrSolid* pDrSolid, char* buf, int& j);
	//////////////////////////////////////////////////////////////
	int			RightUp_SUPPORT_Error();
	int			RightUp_LinSup_Premature();
	int			RightUp_LinSup_NotAutoAccept();



protected:  
// Attributes


	int			m_nNodPos_S_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_S_End;		// index of Bezier Segment in s direction:End
									// now,useful for CProf internally
//todo									// later for UserInterface of BezSeg dependent input
	int			m_nNodPos_T_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_T_End;		// index of Bezier Segment in s direction:End
									// later,useful for PProf internally
	int			m_nNodPos_R_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_R_End;		// index of Bezier Segment in s direction:End
									// later,useful for SProf internally
	int			m_nStartIndex;	// index in StaLList         
	int			m_nTotal;			// total generated in StaLList having
									// this StaLCard Properties         
	/////////////////////////////////////////// Static
	BOOL		m_bSuppDone;		
	UINT		m_nMainType;		// NSUP_RIGID etc
	//////////////////////////
	CDlg_SupI*	m_pSupInDlg;                                                                                
	/////////////////////////////////////////// Support
	CString		m_CurrentSupID;
	CString		m_CurrentSupIDOld;
	CDrLinSup*	m_pCurrentSupp;
	SUPPCARD	m_supCard;
	SUPPPROC	m_SuppProcOld;
	SUPPPROC	m_SuppProc;
 	double		m_DfaltStif;
	pDOUBLE		m_CurrentStif;
	BOOL    	m_bTx;
	BOOL    	m_bTy;
	BOOL    	m_bTz;
	BOOL    	m_bRx;
	BOOL    	m_bRy;
	BOOL    	m_bRz;
	BOOL    	m_bTxG;
	BOOL    	m_bTyG;
	BOOL    	m_bTzG;
	BOOL    	m_bRxG;
	BOOL    	m_bRyG;
	BOOL    	m_bRzG;
	/////////////////////
	CDrNode*	m_pFixDirNode;
	///////////////////////
	UINT		m_GenKind;	// NODE, CURVE, PATCH, SOLID
	/////////////////////// Curve
	CATEGORY	m_Category;
	/////////////////////// Patch
//	BOOL		m_bPat;		//Is it Patch Currently
	/////////////////////////////////////////////////
	CDrCurve*	m_pTanCurve;
	CDrCurve*	m_pNorPatch;
	CString		m_ID_CP;		// for NodeBased: 
									// CurveID if JC_X_TAN_CURVE
									// PatchID if JC_Z_NOR_PATCH
	JOINTCOORD  m_jcType;		// Joint Coordinate Type 		
									//	JC_DEFAULT,
									//	JC_X_FIXEDDIR,
									//	JC_X_TAN_CURVE,
									//	JC_Z_NOR_PATCH



//Operations
public:

	~CSupMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSupMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
