 // ELMouse.h : header file
//
#ifndef _O3DMOUSE_H 
#define _O3DMOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "SolMouse.h"
///////////////////// Modeless
#include "Dlg_O3DI.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CO3DMouse : public CSolMouse
{
public:

	CO3DMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CO3DMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	int				O3DTopo_Update(CDrObj3D* pCurrentObj3D,CDListMgr* pCurrentO3DList,
								CDListMgr* pCurrentSolList,CDListMgr* pCurrentPatList,
								CDListMgr* pCurrentCurList,CDListMgr* pCurrentNodList);
	int				O3DTopo_ConnectObjects(CDrObj3D* pCurrentObject,CDListMgr* pList);
	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_O3D(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_O3D();
	void			ModeLessOff_O3D();
	void			ModeLessOn_O3D();
	////////////////////////////////////////////////////////
	CDlg_O3DI*		GetO3DInDlg(){return m_pO3DInDlg;};                                                                                
	////////////////////////////////////////////////////////////////
	long			CreateorActivateO3DIn(UINT wParam, long lParam);
	long			CancelO3DIn(UINT wParam, long lParam);
	long			GoodByeO3DIn(UINT wParam, long lParam);
	long			UpdateO3DIn(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	/////////////////////////////////////////////////////////////////////////// SOLID
	virtual CString&	GetCurrentObj3DID(){return m_CurrentObj3DID;};
	virtual void		SetCurrentObj3DID(CString Pid){m_CurrentObj3DID = Pid;};
	

		
protected:


	int			Terminate_O3D(BOOL bError);
	int			RightUp_Premature_O3D();
	int			RightUp_NotAutoAccept_O3D();
	int			ShowObj3D(CString* pID);
	//////////////////////////////////////////////
	void		ElementLeftDown_O3D();				// described in derived also
	void		ElementLeftUp_O3D(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_O3D_Obj3D(POINT point);
	int			LeftUp_Obj3D_Accept_OtherContext(CPoint point);
	int			ShowObj3DInfo(CDrObj3D* pDrObj3D, char* buf, int jStart);
	int			LeftUp_O3D_Solid(POINT point);
	int			LeftUp_Solid_Accept_OtherContext(CPoint point);
	int			ShowSolidInfo(CDrSolid* pDrSolid, char* buf, int jStart);
	int			LeftUp_O3D_Patch(POINT point);
	int			LeftUp_O3D_Curve(POINT point);
	int			LeftUp_O3D_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	//////////////////
	int			LeftDown_OBJ3D();
	void		UpdateODlg_TRUE();
	void		UpdateODlg_FALSE();
	//////////////////////////////////////////////////////// Spawn
	int			ShowObj3DInfo(CDrObj3D* pDrObj3D);


protected:  
// Attributes


	CDlg_O3DI*				m_pO3DInDlg; 
	/////////////////////////////////////////// MouseInsert:Interpolate
	CDrObj3D*				m_pCurrentObj3D;
	CDrObj3D*				m_pCurO3DObj3D;
	CDrObj3D*				m_pOldO3DObj3D;
	CDrSolid*				m_pCurO3DSolid;
	CDrSolid*				m_pOldO3DSolid;
	CDrPatch*				m_pCurO3DPatch;
	CDrPatch*				m_pOldO3DPatch;
	CDrCurve*				m_pCurO3DCurve;
	CDrCurve*				m_pOldO3DCurve;
	CDrNode*				m_pCurO3DNode;
	CDrNode*				m_pOldO3DNode;
	//////////
	CDListMgr				m_Obj3DList;		
	CDListMgr				m_SolidList;		
//	CDListMgr				m_PatchList;		// already in SolMouse
//	CDListMgr				m_CurveList;		// already in PatMouse
//	CDListMgr				m_NodeList;			// already in CurMouse
	//////////
    int						m_LastObj3DNum;		// internal
	CString					m_CurrentObj3DID;
	CString					m_CurrentObj3DIDOld;
	BOOL					m_bObj3DDone;		// for dragging
	int						m_nInfoDone;
	//////////////////////////////// Dlg_O3DI


//Operations
public:

	~CO3DMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CO3DMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
