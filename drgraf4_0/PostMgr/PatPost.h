 // ELMouse.h : header file
//
#ifndef _PATPOST_H 
#define _PATPOST_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CurPost.h"
#include "DrMesh2D.h"
#include "Po_FE2D.h"
#include "Def_Mesh.h"
///////////////////// Modeless
#include "Dlg_FE2i.h"
/////////////////////
#include "DrPatch.h" 	
#include "DrPipe.h" 
/////////////////////
//#include "MI_Gang2.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatPost : public CCurPost
{
public:

	CPatPost();
//////////////////////////////////////
	DECLARE_SERIAL(CPatPost)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			InitDlgIn_PAT();
	////////////////////////////////
	UINT			ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID);
	void			ModeLessOff_PAT();
	void			ModeLessOn_PAT();
	////////////////////////////////////////////////////////
	CDlg_FE2I*		GetPost2DDlg(){return m_pPost2DDlg;};                                                                                
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivatePost_PAT(UINT wParam, long lParam);
	long			CancelPost_PAT(UINT wParam, long lParam);
	long			UpdatePost_PAT(UINT wParam, long lParam);
	long			GoodByePost_PAT(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
    ////////////////////////////////////////////////////////////////////// PATCH
		

protected:


	void			Init_PAT();
	void			Terminate_PAT(BOOL bError);
	//////////////////////////////////////////////
	void			ElementLeftDown_PAT();				// described in derived also
	void			ElementLeftUp_PAT(CPoint point);	// described in derived also
	int				LeftUp_PATCH(CPoint point);
	int				ShowPatchInfo(CDrPatch* pDrPatch);
	//////////////////////////////////////////////////
	void			FillDlgRefinementRules();
	void			UpdateDlg_TRUE_PAT();

	void			UpdateDlg_FALSE_PAT();
	void			UpdateDlg_FALSE_PAT_0();
	void			UpdateDlg_FALSE_QUAD();
	void			UpdateDlg_FALSE_TRI();
	//////////////////////////////////////////////
	int				RightUp_Premature_PAT();
	int				RightUp_NotAutoAccept_PAT();
	//////////////////////////////////////////////
	int				ShowPatchToPost(CDrPatch* pDrPatch, BOOL bToBePosted);
	int				MarkPatch_Post(CDrPatch* pDrPatch);
	/////////////////////////////////////////////////////////////////////// 0D
	int				Post_IorCNODE(CDrPatch* pPatch, BOOL bCNode);		
	/////////////////////////////////////////////////////////////////////// 1D
	int				FillData_1D(CObject* pGang2);		
	/////////////////////////////////////////////////////// CURVE
	int				Post_CURVE(CDrPatch* pDrPatch);	
	/////////////////////////////////////////////////////////////////////// 2D
	int				ShowInputInfo_QUADorTRI(BOOL bQuad);
	/////////////////////////////////////////////////////////////////////// FE2D
	int				PrePost_Patch(CDrPatch* pDrPatch,CObject* pGang2,BOOL b1D);		
	int				Pre_Common_2D(CDrPatch* pDrPatch,int& nActiveIndex);		
	int				Post_Common_2D(CDrPatch* pDrPatch,int nActiveIndex,
															int nResult);
	int				GenPost_Mesh_Vertices(CDrPatch* pDrPatch,BOOL bMNode,BOOL bAnyWay);		
	int				GenPost_PatchNodes(CDrPatch* pDrPatch,BOOL bMNode
														,BOOL bAnyWay);		
	int				GenPost_PatchEdges();		
	int				FillData_Patch_1D(CObject* pGang2);		
	int				FillData_Patch_2D(CObject* pGang2);		



protected:  
// Attributes


	BOOL		m_bQuadSelect;	// Accept Quad or Tri-patch in LeftUpPatch
	//////////////////////////////
	CDlg_FE2I*	m_pPost2DDlg;                                                                                
 	/////////////////////////////////////////// Patch
	CDrMesh2D*	m_pMesh2D;
	CDrPatch*	m_pCurrentPatch;
	/////////////////////////////////////////// Fe1DIn_Dlg
//	CString		m_rid_I;	// already in CurPost
//	CString		m_rid_J;	// already in CurPost
	CString		m_rid_K;
	CString		m_rid_L;
	CString		m_RefRule;
//	double		m_RefTemp;	// already in CurPost
	double		m_Thick;
//	UINT		m_ObjType;	// already in CurPost
	CString		m_Orient;
	///
	ELEM_DEGREE	m_ElDegree;
	ORIENT		m_OrientType;
	REF_TRI		m_Ref_Tri;
	REF_QUAD	m_Ref_Quad;
	/////////////////////////////////////////// FE2D Common Data Not Included Above
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
//	short		m_nNodes;			// intermediate + corner Nodes = ALL	// already in CurPost
//	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc		// already in CurPost
	//////////////////////////////////
//	CString		m_line_id;	// already in CurPost
//	UINT		m_rel_I;	// already in CurPost 
//	UINT		m_rel_J;	// already in CurPost 
	UINT		m_rel_K; 
	UINT		m_rel_L; 
	//////////////////////////////////
//	UINT		m_line_no;	// already in CurPost
//	UINT		m_numseg;	// already in CurPost				//
	////////////////////////////// 
//	POINT 		m_nCenter;	// already in CurPost 
	///////////////////////
//	BOOL		m_bOnBndry;	// already in CurPost


//Operations
public:

	~CPatPost();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatPost)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
