// Mouse.h : header file
//
#ifndef _MOUSE_H 
#define _MOUSE_H  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Objs.h"
#include "Def_Type.h"
#include "Def_Mous.h"                    
#include "DListMgr.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMouse : public CObject
{
public:

	CMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public: 


	void		SwitchThirdCoordHeading(CStatic* pCtl,UINT VuNum);
	///////////////////////////////////////////////////////
	PROBDIMLIM	GetProbLim(){return m_ProbLim;};
	void		SetProbLim(PROBDIMLIM p){m_ProbLim = p;};
	ELEMDIMLIM	GetElemLim(){return m_ElemLim;};
	void		SetElemLim(ELEMDIMLIM e){m_ElemLim = e;};
	///////////////////////////////////////////////////// 
	double	GetCurrentThirdCoord(){return m_ThirdCoord;};
	void	SetCurrentThirdCoord(double d){m_ThirdCoord = d;};
	void	WICtoWOR(long LC,pDOUBLE pDblC);
	void	WORtoWIC(long* pLongC,double DblC);
	void	WICtoWOP(long LC,pDOUBLE pDblC);
	void	WOPtoWIC(long* pLongC,double DblC);
	void	WOPtoWOR(pDOUBLE pPhysi,pDOUBLE pWorld);
	void	WORtoWOP(pDOUBLE pWorld,pDOUBLE pPhysi);
	////////////////////////////////////////////////
	void	WOPtoWOR(pWORLD pPhysi,pWORLD pWorld);
	void	WORtoWOP(pWORLD pWorld,pWORLD pPhysi);
	void	WICtoWOR(LPOINT3* pWIC,pWORLD pWorld);
	void	WORtoWIC(LPOINT3* pWIC,pWORLD pWorld);
	void	WICtoWOP(LPOINT3* pWIC,pWORLD pWorld);
	void	WOPtoWIC(LPOINT3* pWIC,pWORLD pWorld);
	////////////////////////////////////// Mouse Helpers
	void	SetViewNumber(UINT nView); 
	//////////////////////////////////////////////// Mouse Location   
	LPOINT3	GetMouseWIC(){return m_MouseWIC;};	
	void 	SetMouseWIC(LPOINT3 NewMouseWIC);	
	LPOINT3	GetMouseOldWIC(){return m_MouseOldWIC;};	
	void 	SetMouseOldWIC(LPOINT3 NewMouseOldWIC);
	//////////////////////////////////////////////			    

protected:

	////////////
	int		IsObjectHit(int nObjectType,pWORLD point, int startIndex);// 3D Problem
	int		IsObjectHit(int nObjectType,POINT point, int startIndex);// 2D Problem
	int		IsObjectHit(int nObjectType,POINT point,CRect* pRect); //Label
	////////////
	int		LabelHit_SetBMSize(CString& NodeID);
	void	LabelHit_InitBM(CPoint Point,CString& NodeID);
	void	LabelHit_ShowBM(CPoint point, CString& NodeID, BOOL bFirstTime);
	/////////////////////////////////////////////////////
	void 	DevtoScrolledWIC2D(CPoint point,LPOINT* pLptScrolled);
	void	WICtoLOG(LPOINT3* pWIC,LPOINT* LpLOG);
	void 	LOGtoWIC(LPOINT3* pWIC,LPOINT* LpLOG);
	void 	LOGtoWIC2(LPOINT3* pWIC,LPOINT* LpLOG,LPOINT3* pOldWIC);
	LPOINT	GetScrolledMouseWIC2D(){return m_LptScrolled;};
	void	SetScrolledMouseWIC2D(LPOINT LptScrolled)
			{
				m_LptScrolled.x = LptScrolled.x;
				m_LptScrolled.y = LptScrolled.y;
			};
	///////////////////////////////////////// Mouse Location 
	void 	ReadDefaults();
	void 	Initialize();   
	///////////////////////////////////////// View
//	CView* 		GetCurrentViewPointer(CRuntimeClass* pViewClass);
	
// Attributes
protected:


	///////////////////////////////////////// interface
	PROBDIMLIM	m_ProbLim;
	ELEMDIMLIM	m_ElemLim;
	UINT		m_nFlags;
	CView*		m_pView;
	CClientDC*	m_pdc;
    ///////////////////////////////////////// MouseLocation
    LPOINT		m_LptScrolled;
	POINT		m_MouseVUC;
	POINT		m_MouseOldVUC;
	POINT		m_AnchorVUC;
	LPOINT3		m_MouseWIC;
	LPOINT3		m_MouseOldWIC;
	LPOINT3		m_MouseDefaultWIC;
  	LPOINT3		m_AnchorWIC;  
	///////////////////////////////////////// View
	UINT		m_nView;
    ///////////////////////////////////////// Mouse
	double		m_ThirdCoord;
	POINT		m_MouseLOG;
	POINT		m_MouseOldLOG;
	POINT		m_AnchorNodeLOG; 
	POINT		m_PointOld;
	///////////////////////////////////////////
	BOOL		m_bAutoAcceptOn;
	BOOL		m_bDialogOn;
	BOOL		m_bRefreshOn;
	BOOL		m_bDragOn;
	BOOL		m_bDragging;
	/////////////////////////////////////////// 
	CDC			m_MemDC;
	int			m_BMWidth;
	int			m_BMHeight;
	CBitmap		m_BitmapSave;
	CBitmap		m_BitmapSource;
	CFont		m_Font;
	LOGFONT		m_lf;
 	///////////////////////////////////////// ObjectMove		
	int			m_CurrentMoveObjectIndex;
	CRect		m_InvalidMoveRect;
	///////////////////////////////////////// FreeHand
	POINT		m_ptPrev;         // the last mouse pt 
							  // in progress
	/////////////////////////////////////////// Text Move Select
	BOOL		m_bMoving;
	CRect		m_ObjectRect;
	CRect		m_ObjectRectOld;
	
   
//Operations
public:

	~CMouse();
	virtual void Serialize(CArchive& ar);
/////////////////////////////////////////////////////////////////////////////
/*
	// Generated message map functions

	//{{AFX_MSG(CMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
