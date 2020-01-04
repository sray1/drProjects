// CXVM_Genr.h : header file
//
#ifndef _XVM_GENR_H
#define _XVM_GENR_H


/////////////////////////////////////////////////////////////////////////////
// CXVM_Genr
/////////////////////////////////////////////////////////////////////////////
class  CXVM_Genr : public CObject
{
// Construction
public:  
	CXVM_Genr(){};


protected: 
public:
// Implementation
public:

		////////////////////////////////////////////	Mouse:CREATE
		void	MouseMove(CView* pView, UINT nFlags, CPoint point);
		void	LButtonDown(CView* pView, UINT nFlags, CPoint point);
		void	LButtonUp(CView* pView, UINT nFlags, CPoint point);
		void	RButtonDown(CView* pView, UINT nFlags, CPoint point);
		void	RButtonUp(CView* pView, UINT nFlags, CPoint point);


protected: 

public:
	virtual ~CXVM_Genr(){};
};
//////////////////////////////////////
#endif
