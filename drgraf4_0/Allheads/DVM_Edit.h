// CDVM_Edit.h : header file
//
#ifndef _DVM_EDIT_H
#define _DVM_EDIT_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_Edit
/////////////////////////////////////////////////////////////////////////////
class  CDVM_Edit : public CObject
{
// Construction
public:  
	CDVM_Edit(){};
	DECLARE_DYNCREATE(CDVM_Edit)

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
	virtual ~CDVM_Edit(){};
};
//////////////////////////////////////
#endif
