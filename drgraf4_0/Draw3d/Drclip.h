// CDrClip.h : header file
//
#ifndef _CDRCLIP_H_
#define _CDRCLIP_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "Def_View.h"
/////////////////////////////////////////////////////////////////////////////
// CClip  class AFX_EXT_CLASS CMyClass : public CDocument

/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrClip : public CObject
{
	DECLARE_SERIAL(CDrClip)
// Construction
public:  
	CDrClip();
	CDrClip(double dzMin, BOOL bPer, BOOL bCanon);  //overload

protected: 
public:
// Implementation
public:
 
    ///////////////////////////////////////////////////// 
	virtual VISIBILITY	ClipLine_SC(pWORLD startPt,pWORLD endPt);
	virtual VISIBILITY	ClipPt(pWORLD Pt);
	virtual VISIBILITY 	ClipLine_LB(pWORLD pS,pWORLD pE);
	//////////////////////////////////			
	virtual void 		SetzMin(double dzMin){m_dzMin = dzMin;};
	virtual double		GetzMin(){return m_dzMin;};	
	virtual void 		SetPerspective(BOOL bPer){m_bPer = bPer;};
	virtual BOOL		GetPerspective(){return m_bPer;};	
	virtual void 		SetCanonical(BOOL bCan){m_bCanon = bCan;};
	virtual BOOL		GetCanonical(){return m_bCanon;};	

protected:

	void 	PushDown(pWORLD S,pWORLD E);
	void 	PushUp(pWORLD S,pWORLD E);
	void 	PushLeft(pWORLD S,pWORLD E);
	void 	PushRight(pWORLD S,pWORLD E);
	void 	PushFront(pWORLD S,pWORLD E);
	void 	PushBack(pWORLD S,pWORLD E);
	void 	Push(WORD cb,pWORLD p1,pWORLD p2);
	WORD 	ClipEncode(pWORLD p);
	BOOL 	ClipPt_LB(double denom,double num,double* pdtE,double* pdtL);


protected:

	double	m_dzMin;
	BOOL	m_bPer;
	BOOL	m_bCanon;
	 

public:
	virtual ~CDrClip();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDrClip)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
