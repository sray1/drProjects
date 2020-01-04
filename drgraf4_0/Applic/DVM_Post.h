// CDVM_Post.h : header file
//
#ifndef _DVM_POST_H
#define _DVM_POST_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_Post
/////////////////////////////////////////////////////////////////////////////
class  CDVM_Post : public CObject
{
// Construction
public:  
	CDVM_Post(){};
	DECLARE_DYNCREATE(CDVM_Post)


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
	virtual ~CDVM_Post(){};
};
//////////////////////////////////////
#endif
