// DrGrid.h : header file
//
#ifndef _DRGRID_H
#define _DRGRID_H       

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Str_Draw.h"
#include "Def_Draw.h"
#include "DrObject.h" 
#include "DListMgr.h"
//////////////////////////////
#define	MAX_NODES_GRID		2
/////////////////////////////////////////////////////////////////////////////
// CDrGrid    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrGrid: public CDrObject
{
public:
// Construction                 
	CDrGrid();
	CDrGrid(GR_INFO grInfo);       
//////////////////////////////////////
	DECLARE_SERIAL(CDrGrid);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	//////////////////////////////////////////////////////////////
	virtual BOOL		IsMoved(){return m_bMoved;};
	virtual void		SetMoved(BOOL  bMoved){m_bMoved = bMoved;};	
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODES_GRID;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 		FinishObject();
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	///////////////////////////////////////////////////////////////
	virtual void    GetPenInfo_G(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	nWidth  =	m_nPenWidth_G;
						crColor =	m_crPenColor_G;
						nStyle  =	m_nPenStyle_G;
				  	};	
	virtual void    SetPenInfo_G(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidth_G  = nWidth;
						m_crPenColor_G = crColor;
					 	m_nPenStyle_G  = nStyle;
					};
	virtual void    GetPenInfo_C(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	nWidth  =	m_nPenWidth_C;
					 	crColor =	m_crPenColor_C;
						nStyle  =	m_nPenStyle_C;
				  	};	
	virtual void    SetPenInfo_C(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidth_C  = nWidth;
						m_crPenColor_C = crColor;
					 	m_nPenStyle_C  = nStyle;
					};
	////////////////////////////////////////////////
	virtual CDListMgr*	GetNodeList(){return &m_NodeList;};
    ////////////////////////////////////////////////////////////////////// helper
	virtual pGR_INFO	GetGrInfo(){return &m_GrInfo;};
	virtual void		SetGrInfo(GR_INFO gi){m_GrInfo = gi;};    
	virtual WORLD		GetStep(){return m_wStep; };
	virtual void		SetStep(WORLD S){m_wStep = S;};
	virtual double		GetAngle(){return m_dAngle;};    
	virtual void		SetAngle(double A){m_dAngle = A;};
	virtual WORLD		GetAnchor(){return m_wAnchor; };
	virtual void		SetAnchor(WORLD A){m_wAnchor = A;};


	 
protected:
	
		void 	TransformToWorldPos(pMATRIX pLM,BOOL bYes);
		void 	TransformToEyePos(pMATRIX pViewM);
		void 	ProjectToScreenPos
					(pMATRIX pvv3DM,double dScale_U,double dScale_V);
		void 	Calc_ScreenRectFromCNodes();
		void 	GoDoIt(CDC* PtrDC,BOOL bPenChange);
		void 	DrawGrid(CDC* pDC,pWORLD max,pWORLD min,pWORLD steps,pGR_INFO pGrInfo);
			
			

			
// Helper functions
protected:
// Attributes
 
	GR_INFO		m_GrInfo;
	WORLD		m_wStep; 
	CDListMgr	m_NodeList;
	double		m_dAngle;    	// screen rotation for snap
	WORLD		m_wAnchor;		// alignment Control
    ////////////////////////////// Grid
	UINT        m_nPenWidth_G;    
	COLORREF	m_crPenColor_G;
	UINT		m_nPenStyle_G;
    ////////////////////////////// Connection
	UINT        m_nPenWidth_C;    
	COLORREF	m_crPenColor_C;
	UINT		m_nPenStyle_C;
	//////////////////////////////
	BOOL		m_bMoved;


public:
	virtual ~CDrGrid();
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       
