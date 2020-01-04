// CMsMath.h : header file
//
#ifndef _MSMATH_H_
#define _MSMATH_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "Def_Type.h"
#include "3dMath.h"
////////////////////////////
typedef	double	(*PDMA3)[4];
/////////////////////////////////////////////////////////////////////////////
// CMsMath
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMsMath : public C3DMath
{
// Construction
public:  
	CMsMath();
//////////////////////////////////////
	DECLARE_SERIAL(CMsMath)
//////////////////////////////////////
protected: 
public:
// Implementation
public:
 
//	int			IsCoLinear(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2);
//	int			IsCoPlanar(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2,pWORLD pwx3,
//						  pWORLD pNormal_ABC,pDOUBLE pD );
	int			IsCoLinear(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2,double dCoLin);
	int			IsCoPlanar(pWORLD pwx0,pWORLD pwx1,pWORLD pwx2,pWORLD pwx3,
						  pWORLD pNormal_ABC,pDOUBLE pD,double dCoLin);
	BOOL		IsIntersect_LINE_LINE(pWORLD LocalPos,WORLD& LocalPos_In);

	


public:
	virtual ~CMsMath(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMsMath)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
