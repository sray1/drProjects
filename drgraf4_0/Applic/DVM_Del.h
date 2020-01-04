// CDVM_Del.h : header file
//
#ifndef _DVM_DEL_H
#define _DVM_DEL_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_Del
/////////////////////////////////////////////////////////////////////////////
class  CDVM_Del : public CObject
{
// Construction
public:  
	CDVM_Del(){};
	DECLARE_DYNCREATE(CDVM_Del)

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
	virtual ~CDVM_Del(){};
};
//////////////////////////////////////
#endif
