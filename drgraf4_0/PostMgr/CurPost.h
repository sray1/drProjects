 // ELMouse.h : header file
//
#ifndef _CURPOST_H 
#define _CURPOST_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "NodPost.h"
#include "DrMesh1D.h"
#include "Po_FE1D.h"
#include "Po_Pipe.h"
#include "Po_Beam.h"
#include "Po_Truss.h"
#include "Po_Elbow.h"
///////////////////// Modeless
#include "Dlg_FE1i.h"
/////////////////////
#include "DrCurve.h" 	
#include "DrPipe.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurPost : public CNodPost
{
public:

	CCurPost();
//////////////////////////////////////
	DECLARE_SERIAL(CCurPost)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			InitDlgIn_CUR();
	////////////////////////////////
	UINT			ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID);
	void			ModeLessOff_CUR();
	void			ModeLessOn_CUR();
	////////////////////////////////////////////////////////
	CDlg_FE1I*		GetPost1DDlg(){return m_pPost1DDlg;};                                                                                
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivatePost_CUR(UINT wParam, long lParam);
	long			CancelPost_CUR(UINT wParam, long lParam);
	long			UpdatePost_CUR(UINT wParam, long lParam);
	long			GoodByePost_CUR(UINT wParam, long lParam);
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
    ////////////////////////////////////////////////////////////////////// PATCH
		

protected:


	void			Init_CUR();
	void			Terminate_CUR(BOOL bError);
	//////////////////////////////////////////////
	void			ElementLeftDown_CUR();				// described in derived also
	void			ElementLeftUp_CUR(CPoint point);	// described in derived also
	int				LeftUp_CURVE(CPoint point);
	//////////////////////////////////////////////////
	void			UpdateDlg_TRUE_CUR();

	void			UpdateDlg_FALSE_CUR();
	void			UpdateDlg_FALSE_CUR_0();
	void			UpdateDlg_FALSE_INODE();
	void			UpdateDlg_FALSE_CNODE();
	////////////////////////////////////////
	void			UpdateDlg_FALSE_1D();
	void			UpdateDlg_FALSE_TRUSS();
	void			UpdateDlg_FALSE_BEAM();
	void			UpdateDlg_FALSE_PIPE();
	void			UpdateDlg_FALSE_ELBOW();
	//////////////////////////////////////////////
	int				RightUp_Premature_CUR();
	int				RightUp_NotAutoAccept_CUR();
	//////////////////////////////////////////////
	int				ShowCurveToPost(CDrCurve* pDrCurve, BOOL bToBePosted);
	int				MarkCurve_Post(CDrCurve* pDrCurve);
	///////////////////////////////////////////////////////////////////////
	int				ShowInputInfo_INODE();
	int				ShowInputInfo_CNODE();
	int				Post_IorCNODE(CDrCurve* pCurve, BOOL bCNode);		
	/////////////////////////////////////////////////////////////////////// TRUSS
	int				ShowInputInfo_TRUSS();
//	int				Post_TRUSS(CDrCurve* pDrCurve);		
//	int				FillData_TRUSS(CPo_Truss* pFE1D);		
	/////////////////////////////////////////////////////////////////////// BEAM
	int				ShowInputInfo_BEAM();
//	int				Post_BEAM(CDrCurve* pDrCurve);
//	int				FillData_BEAM(CPo_Beam* pFE1D);		
	/////////////////////////////////////////////////////////////////////// PIPE
	int				ShowInputInfo_PIPE();
//	int				Post_PIPE(CDrCurve* pDrCurve);		
//	int				FillData_PIPE(CPo_Pipe* pFE1D);		
	/////////////////////////////////////////////////////////////////////// ELBOW
	int				ShowInputInfo_ELBOW();
//	int				Post_ELBOW(CDrCurve* pDrCurve);		
//	int				FillData_ELBOW(CPo_Elbow* pFE1D);		
	/////////////////////////////////////////////////////////////////////// FE1D
	int				PrePost_Curve(CDrCurve* pDrCurve,CObject* pGang1,BOOL b0D);		
	int				GenPost_Mesh_Vertices(CDrCurve* pDrCurve,BOOL bMNode,BOOL bAnyWay);		
	int				FillData_Curve_0D(CObject* pGang1);		
	int				FillData_Curve_1D(CObject* pGang1);		
	int				Pre_Common_1D(CDrCurve* pDrCurve,int& nActiveIndex);		
	int				Post_Common_1D(CDrCurve* pDrCurve,int nActiveIndex,
															int nResult);
	int				FillData_1D(CPo_FE1D* pFE1D);		
//	int				SetElemInfoID(CString& ElemID,UINT nElemType);		

protected:  
// Attributes


	//////////////////////////////
	CDlg_FE1I*	m_pPost1DDlg;                                                                                
 	/////////////////////////////////////////// Curve
	CDrMesh1D*	m_pMesh1D;
	CDrCurve*	m_pCurrentCurve;
	/////////////////////////////////////////// Fe1DIn_Dlg
	BOOL		m_bValve;
	CString		m_matID;
	CString		m_propID;
	CString		m_rid_I;
	CString		m_rid_J;
	CString		m_stressID_I;
	CString		m_stressID_J;
	CString		m_KNodeID;		// for Beam
	double		m_RefTemp;
	UINT		m_ObjType;
	/////////////////////////////////////////// Elbow Data
	CString		m_CCID;
	CString		m_TIID;
	CString		m_CAID;
	CString		m_CBID;
	/////////////////////////////////////////// FE1D Common Data Not Included Above
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	short		m_nNodes;			// intermediate + corner Nodes = ALL
	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc
	//////////////////////////////////
	CString		m_line_id;
	UINT		m_rel_I; 
	UINT		m_rel_J; 
	//////////////////////////////////
	UINT		m_line_no;
	UINT		m_numseg;				//
	////////////////////////////// 
	POINT 		m_nCenter; 
	///////////////////////
	BOOL		m_bOnBndry;


//Operations
public:

	~CCurPost();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurPost)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
