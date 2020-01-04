 // ELMouse.h : header file
//
#ifndef _PATMOUSE_H 
#define _PATMOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "CurMouse.h"
///////////////////// Modeless
#include "Dlg_Co4I.h"
/////////////////////
#include "DrNode.h" 	
#include "DrLabel.h" 	
#include "DrCurve.h" 	
#include "MI_Pat_P.h"
#include "MI_Pat_I.h"
#include "DListMgr.h"
#include "glb_CuPS.h"                    
#include "glb_Type.h"                    
#include "glb_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatMouse : public CCurMouse
{
public:

	CPatMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CPatMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_PAT();
	void			ModeLessOff_PAT();
	void			ModeLessOn_PAT();
	////////////////////////////////////////////////////////
	CDlg_Co4I*		GetCo4InDlg(){return m_pCo4InDlg;};                                                                                
	////////////////////////////////////////////////////////////////
	long			CreateorActivateCo4In(UINT wParam, long lParam);
	long			GoodByeCo4In(UINT wParam, long lParam);
	long			UpdateCo4In(UINT wParam, long lParam);
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
	virtual CString&	GetCurrentPatchID(){return m_CurrentPatchID;};
	virtual void		SetCurrentPatchID(CString Pid){m_CurrentPatchID = Pid;};
	virtual CString&	GetPatCurveID(int i){return m_PatCurveID[i];};
	virtual void		SetCurrentPatCurveID(CString Cid, int i){m_PatCurveID[i] = Cid;};
	virtual CURVELATCH  GetPatCurveLat(int i){return m_PatCurveLatch[i];};
	virtual void		SetPatCurveLat(CURVELATCH CLat, int i){m_PatCurveLatch[i] = CLat;};
	virtual int			GetPatCurveElem(int i){return m_PatCurveElem[i];};
	virtual void		SetPatCurveElem(int Elem, int i){m_PatCurveElem[i] = Elem;};
 	virtual PATSUBTYPE	GetCurrentPatSubType(){return m_CurrentPatSubType;};
	virtual void		SetCurrentPatSubType(PATSUBTYPE pst){m_CurrentPatSubType = pst;};
  				
		
protected:


	//////////////////////////////////////////////
	void		ElementLeftDown_PAT();				// described in derived also
	void		ElementLeftUp_PAT(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Patch
	int			LeftDown_PATCH();
	int			LeftUp_Coons(POINT point);
	int			RightUp_PATCH();
	void		UpdatePDlg_TRUE();
	void		UpdatePDlg_FALSE();
	/////////////////////////////////////////////////////////
	int 		PutEndIdsInPlateList(CString nid[],int nEnds);
	int 		PutObjectinPatch(CDrObject* pAddObject,CString nid[],int nEnds);


protected:  
// Attributes


	CDlg_Co4I*	m_pCo4InDlg;                                                                                
	/////////////////////////////////////////// MousePost:MeshGeneration
	CMI_Pat_P	m_MI_Pat_P;
	/////////////////////////////////////////// MouseInsert:Interpolate
	CMI_Pat_I	m_MI_Pat_I;
	/////////////////////////////////////////// Patch
	CDrPatch*	m_pCurrentPatch;
	CDrCurve*	m_pCurPatCurve;
	CDrCurve*	m_pOldPatCurve;
//	CDListMgr	m_CurveList;		// will need this for Gordon Type
//	CList<int,int>	m_ElemList;		// will need this for Gordon Type
    int			m_LastPatchNum;		// internal
	PATCHPROC	m_CurrentPatchType;
	PATSUBTYPE	m_CurrentPatSubType;
	CString		m_CurrentPatchID;
	CString		m_CurrentPatchIDOld;
	BOOL		m_bPatchDone;		// for dragging
	int			m_nCurveDone;
	CString		m_PatCurveID[4];
	CURVELATCH	m_PatCurveLatch[4];
	int			m_PatCurveElem[4];



//Operations
public:

	~CPatMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
