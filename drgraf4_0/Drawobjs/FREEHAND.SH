// FreeHand.h : header file
//
#ifndef _FREEHAND_H
#define _FREEHAND_H       

#include "globals.h"

//////////////////// 
#define MAX_FREEHAND_DRAW_PT	1
// CElemObject///////////////////////////////////////////////////////////////
class CDrFreeHand: public CObject
{
public:
// Construction                 
	CDrFreeHand();
	DECLARE_SERIAL(CDrFreeHand)
	
// Operations
public:
	CRect&	 	GetBoundingRect() { return m_rectBounding; };
	void 		FinishFreeHand();
	void 		DoFreeHands(CDC* PtrDC,UINT nViewNumber);
	void 		ViewCurrentFreeHand(CDC* PtrDC,int nViewNumber);
	///////////////////////////////////////// DataBase	
    ///////////////////////////////////////////////////////////// Pen
    void		ReplacePen();  
	void		SetPen(int nStyle,int nWidth,COLORREF Color)
				{
					m_nPenStyle = nStyle;
					m_nPenWidth = nWidth;
					m_nPenColor = Color;
				};												    
	COLORREF	GetColor(){return m_nPenColor;};
	void		SetColor(COLORREF Color)
				{
					m_nPenColor = Color;
				};	
	int			GetWidth(){return m_nPenWidth;};
	void		SetWidth(int nPenWidth)
				{
					m_nPenWidth = nPenWidth;
				};	
	int			GetStyle(){return m_nPenStyle;};
	void		SetStyle(int nPenStyle)
				{
					m_nPenStyle = nPenStyle;
				};	
	int			GetType(){return m_nType;};
	void		SetType(int nType)
				{
					m_nType = nType;
				};	
	UINT		GetKeyNo(){return m_nFHNumber;};
	void		SetType(UINT nFHNumber)
				{
					m_nFHNumber = nFHNumber;
				};	
	UINT		GetLayer(){return m_nLayer;};
	void		SetLayer(UINT nLayer){ m_nLayer = nLayer;};
	LPOINT3		GetCorner(){return m_lCorner;};
	void		SetCorner(LPOINT3 lCorner);
	LPOINT3		GetOtherCorner(){return m_lRBCorner;};
	void 		SetOtherCorner(LPOINT3 lCorner);
	void 		AddPoint(CPoint pt);
	void 		SetInfo(CDrFreeHand* pFreeHand);
	int			IsFreeHandHit(CClientDC* ptrDC,POINT point,RECT* pRect,int nViewNumber);

// Helper functions
protected:
	void 		DrawFreeHand(CDC* PtrDC,BOOL bLayerOn,UINT nViewNumber);
	void 		GoDoIt(CDC* PtrDC,POINT pt,UINT nViewNumber,int nSequence);
	CPoint		GetPoint(int i) const { return CPoint(m_pointArray[i]); }

// Attributes 
protected:

// Attributes
	UINT			m_nFHNumber;		// FreeHand Number
	CDWordArray 	m_pointArray;   	// series of connected points
	CRect           m_rectBounding; 	// smallest rect that surrounds all
										// of the points in the stroke
										// measured in MM_LOENGLISH units
										// (0.01 inches, with Y-axis inverted)
	UINT			m_nLayer;
    int				m_nType;
    LPOINT3			m_lCorner;
    LPOINT3			m_lRBCorner;
	//////////////////////////
    CPen		m_PenCur;
	int	        m_nPenWidth;    	// pen width for FreeHand
	COLORREF	m_nPenColor;
	int			m_nPenStyle; 
	//////////////////////// 
	

public:
	virtual ~CDrFreeHand(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFreeHand)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#endif


