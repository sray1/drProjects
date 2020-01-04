// CDVM_CreM.h : header file
//
#ifndef _DVM_CREM_H
#define _DVM_CREM_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_CreM
/////////////////////////////////////////////////////////////////////////////
class  CDVM_CreM : public CObject
{
// Construction
public:  
	CDVM_CreM(){};
	DECLARE_DYNCREATE(CDVM_CreM)

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
	virtual ~CDVM_CreM(){};
};
//////////////////////////////////////
#endif
