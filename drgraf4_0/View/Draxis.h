// Axis.h : header file
//
#ifndef _AXISOBJECT
#define _AXISOBJECT  


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
//////////////////
#define	MAX_PT_AXIS	14
//////////////////////////////////////////////////////////////
// CAxisObject////////////////////////////////////////////////
class AFX_EXT_CLASS CAxis: public CObject
{
public:  
	CAxis();                      // call from serialization only
	DECLARE_DYNAMIC(CAxis)
public:
// Construction                 
	CAxis(UINT nLength);
public: 

	virtual void 	DrawAxes(CDC* PtrDC,POINT Origin,CView* pView);
	
protected:	

	//////////////////////////
	virtual void 	GoDoIt(CDC* PtrDC,POINT* pt);


protected:

    ///////////////////////////// drawing
	UINT 	m_nLength;
	POINT 	m_pt[MAX_PT_AXIS];
	WORLD 	m_Coord[MAX_PT_AXIS];

public:
	virtual ~CAxis(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CAxis)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
