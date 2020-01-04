// Pipe.h : header file
//
#ifndef _DRFACE_H
#define _DRFACE_H       

#include "DListMgr.h"
/////////////////////////////////////////////////////////////////////////////
// CDrFace    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFace: public CObject
{
public:
// Construction                 
	CDrFace();
	DECLARE_SERIAL(CDrFace);
	
	
// Operations
public:


	virtual void		Serialize(CArchive& ar);
	////////////////////////////////////////////////////////////////////// Members




protected:
	
			
			
// Helper functions
protected:
// Attributes

	CDListMgr			m_EdgeInfoList;		// oriented list of Edges
	////////////////////////////////////////// Mesh Manipulation
	int					m_nHist_RCH;	// RC/CH/HR-index of the generating
											// Curve/Patch/Solid(-1 = Not On Generatrix)
	int					m_nHistType;	// 1=RowCol(ST)/2=ColHgt(TR)/3=HgtRow(RS)


public:
	virtual ~CDrFace();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFace)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



