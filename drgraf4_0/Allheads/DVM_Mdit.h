// CDVM_Mdit.h : header file
//
#ifndef _DVM_MDIT_H
#define _DVM_MDIT_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_Mdit
/////////////////////////////////////////////////////////////////////////////
class  CDVM_Mdit : public CObject
{
// Construction
public:  
	CDVM_Mdit(){};
	DECLARE_DYNCREATE(CDVM_Mdit)

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
	virtual ~CDVM_Mdit(){};
};
//////////////////////////////////////
#endif
