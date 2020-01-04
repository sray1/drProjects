 // ELMouse.h : header file
//
#ifndef _CURMOUSE_H 
#define _CURMOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "NodMouse.h"
///////////////////// Modeless
#include "Dlg_LQCI.h"
#include "Dlg_CrcI.h"	//CIRCLE
/////////////////////
#include "DrCurve.h" 	
#include "MI_Cur_I.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurMouse : public CNodMouse
{
public:

	CCurMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CCurMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	int				CurTopo_Update(CDrCurve* pCurrentCurve,UINT CurrentCurveType,
											CDListMgr* pINodList/*m_NodeList*/);
	int				CurTopo_GetEndNodes(CDrCurve* pCurrentCurve,UINT CurrentCurveType,
								CDListMgr* pNodeList,CDListMgr* pHeadTail);
	int				CurTopo_EndNodeInOtherCurves(CDrCurve* pCurrentCurve,CDrCurve* pOtherCurve,
											CDrNode* pEndNode);
	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_CUR();
	void			ModeLessOff_CUR();
	void			ModeLessOn_CUR();
	////////////////////////////////////////////////////////
	void			ResetVuBasedVars_CurDlg();
	CDlg_LQCI*		GetLQCInDlg(){return m_pLQCInDlg;};                                                                                
	CDlg_CrcI*		GetCrcInDlg(){return m_pCrcInDlg;};                                                                                
	////////////////////////////////////////////////////////////////
	long			CreateorActivateLQCIn(UINT wParam, long lParam);
	long			CancelLQCIn(UINT wParam, long lParam);
	long			GoodByeLQCIn(UINT wParam, long lParam);
	long			UpdateLQCIn(UINT wParam, long lParam);
	///
	long			CreateorActivateCrcIn(UINT wParam, long lParam);
	long			CancelCrcIn(UINT wParam, long lParam);
	long			GoodByeCrcIn(UINT wParam, long lParam);
	long			UpdateCrcIn(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
 	///////////////////////////////////////////////////// PIPE
	virtual CString		GetCurrentPipeID(){return m_CurrentPipeID;}; 
    virtual void		SetCurrentPipeID(CString CurrentID)
    					{
    						m_CurrentPipeID = CurrentID;
    					};
   ///////////////////////////////////////////////////// Curve
	virtual CString		GetCurrentCurveID(){return m_CurrentCurveID;};
    virtual void		SetCurrentCurveID(CString CurrentCurveID)
    					{
    						m_CurrentCurveID = CurrentCurveID;
    					};
	virtual CDrCurve*	GetCurrentCurvePtr(){return m_pCurrentCurve;};
    virtual void		SetCurrentCurvePtr(CDrCurve* CurrentCurve)
    					{
    						m_pCurrentCurve = CurrentCurve;
    					};
	virtual int			GetCurrentElPerSeg(){return m_ElPerSeg;};
	virtual double		GetCurrentRatio(){return m_Ratio;};
	virtual void		SetCurrentElPerSeg(int nEl){m_ElPerSeg = nEl;};
	virtual void		SetCurrentRatio(double rat){m_Ratio = rat;};
	virtual BOOL		IsClosed(){return m_bClosed;};
	virtual void		SetClosed(BOOL b){ m_bClosed = b;};
	virtual BOOL		IsAdvanceOn(){return m_bAdvanceOn;};
	virtual void		SetAdvanceOn(BOOL b){ m_bAdvanceOn = b;};
	virtual BOOL		IsBLineOn(){return m_bBLineOn;};
	virtual void		SetBLineOn(BOOL b){ m_bBLineOn = b;};
	virtual BOOL		IsSingleSegOn(){return m_bSingleSegOn;};
	virtual void		SetSingleSegOn(BOOL b){ m_bSingleSegOn = b;};
  				
		
protected:


	void			ResetVariables_CUR();
	int				Terminate_CUR(BOOL bError);
	/////////////////////////////////////////////////////////
	int 			PutEndIdsInPipeList(CString nid[],int nEnds);
	void			SerializePipe(CArchive& ar);
	//////////////////////////////////////////////
	void			ElementLeftDown_CUR();				// described in derived also
	void			ElementLeftUp_CUR(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Curve
	int				LeftDown_CURVE();
	int				LeftUp_Cur_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	int				NewNode_N_Update_OtherContext(CPoint point,BOOL bCNode);
	int				OldNode_N_Update_CURContext(BOOL bCNode,BOOL bDistinct);
	int				LeftUp_Node_Accept_OtherContext(CPoint point,BOOL bCNode,BOOL bMeshMode,
						BOOL bCorINodeOpDone,BOOL bAutoAcceptOn,CDrNode** pCurrentNode);
	int				NewNode_OtherContext(CPoint point,BOOL bCNode);
	int				UpdateforOldNode(BOOL bCNode);
	int				UpdateforNewNode(BOOL bCNode);
	int				ShowNodeInfo_SameCoords_OtherContext(CDrNode* pDrNode);
	int				ShowCurve(CString* pID,BOOL bFinal);
	void			UpdateCDlg_TRUE();
	void			UpdateCDlg_FALSE();
	int				LeftUp_CURVE(CPoint point);
	int 			RightUp_CURVE();
	int				RightUp_CURVE_Error();
	int				RightUp_CURVE_Premature();
	int				RightUp_CURVE_NotAutoAccept();
	int				RightUp_NOTCIRCLE_NotAutoAccept();
	int				RightUp_CIRCLE_NotAutoAccept();
	//////////////////////////////////////////////////
	int				ShowCurveInfo(CDrCurve* pDrCurve);
/*
//	Moved to CreOMgr Dll   01/14/98 
	//////////////////////////////////////////////////////// Spawn
	int				LeftUp_CSPAWN(CPoint point);
	int				ShowCurveToSpawn(CDrCurve* pDrCurve);
//	Moved to CreOMgr Dll   01/14/98 end
*/


protected:  
// Attributes


	UINT		m_uContext;
	BOOL		m_bCorINodeOpDone;
	///
	CDlg_LQCI*	m_pLQCInDlg;                                                                                
	CDlg_CrcI*	m_pCrcInDlg;                                                                                
	/////////////////////////////////////////// MouseInsert:Interpolate
//	CMI_Cur_I	m_MI_Cur_I;
	/////////////////////////////////////////// Pipe     
	CString 	m_CurrentPipeID;
 	/////////////////////////////////////////// Curve
	CDrCurve*	m_pCurrentCurve;
	CDListMgr	m_NodeList;
	CList<int,int>	m_ElSegList;
    int			m_LastCurveNum;		// internal
	CURVEPROC	m_CurrentCurveType;
	CString 	m_CurrentCurveID;
	CString 	m_CurrentCurveIDOld;
	BOOL		m_bCurveDone;		// for dragging
	int			m_nCirMaxNode;		// = 3
	int			m_ElPerSeg;
	double		m_Ratio;
	BOOL		m_bClosed;
	BOOL		m_bAdvanceOn;
	BOOL		m_bSingleSegOn;
	BOOL		m_bBLineOn;
	/////////////////////////////////////////// Circle
	CIRCLETYPE	m_CircType;
	///////////////////////////////////////////////////////////
	int			m_nTotElems;	// UserGiven
	int			m_nTotElPerSeg;	// Sum of Individual Seg Elems
	// additional SegElem = m_nTotElems - m_nTotElPerSeg;
	///////////////////////////////////////////////////////////
	double		m_SegAngle;
	BOOL		m_bAutoSeg;
	double		m_dAngSpec;
	BOOL		m_bArc;
	double		m_dAng;	
	CString		m_FromID;
	CString		m_ToID;	
	CDrNode*		m_pFromNode;
	CDrNode*		m_pToNode;	
	CString		m_TIID;
	CString		m_CCID;	
	CString		m_CAID;
	CString		m_CBID;	
	UINT		m_NodeType;	// NODE or CNODE
	double		m_dRadius;
	///////
	BOOL		m_bAxis;	// if Axis Input
	int			m_nAxis;		// 1=X/2=Y/3=Z
	BOOL		m_bNegative;
	///////


//Operations
public:

	~CCurMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
