// CDVM_Genr.h : header file
//
#ifndef _DVM_GENR_H
#define _DVM_GENR_H


/////////////////////////////////////////////////////////////////////////////
// CDVM_Genr
/////////////////////////////////////////////////////////////////////////////
class  CDVM_Genr : public CObject
{
// Construction
public:  
	CDVM_Genr(){};
	DECLARE_DYNCREATE(CDVM_Genr)

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
		int		ResetDlg_NOD(UINT uVuNum);
		int		ResetDlg_CUR(UINT uVuNum);
		int		ResetDlg_PAT(UINT uVuNum);
		int		ResetDlg_SOL(UINT uVuNum);

public:
	virtual ~CDVM_Genr(){};
};
//////////////////////////////////////
#endif
