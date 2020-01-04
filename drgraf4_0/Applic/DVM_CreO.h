// CDVM_CreO.h : header file
//
#ifndef _DVM_CREO_H
#define _DVM_CREO_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_CreO
/////////////////////////////////////////////////////////////////////////////
class  CDVM_CreO : public CObject
{
// Construction
public:  
	CDVM_CreO(){};
	DECLARE_DYNCREATE(CDVM_CreO)


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
	virtual ~CDVM_CreO(){};
};
//////////////////////////////////////
#endif
