// CClip.h : header file
//
#ifndef _CLIP_H_
#define _CLIP_H_


#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CClip
/////////////////////////////////////////////////////////////////////////////
class CClip : public CObject
{
// Construction
public:  
	CClip();
	DECLARE_SERIAL(CClip)
protected: 
public:
// Implementation
public:
 
    ///////////////////////////////////////////////////////////// 
	void 	SetDrHither(double z);
	double 	GetDrHither();
	void 	SetDrYon(double z);
	double 	GetDrYon();
	enum 	visibility	DrClipPt(LPOINT3* pPt, int nPrecision);
	enum 	visibility	DrClipLine(LPOINT3* pStart, LPOINT3* pEnd, int nPrecision);
	void 	DrSetCanonicalClipOn(BOOL bState);
	//////////////////////////////////			
	
protected:


protected: 

public:
	virtual ~CClip(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CClip)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif
