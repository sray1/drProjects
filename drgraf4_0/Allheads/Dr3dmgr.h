// Dr3DMgr.h : header file
//
#ifndef _DR3DMGR_H
#define _DR3DMGR_H
 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

//#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CDr3DMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDr3DMgr : public CObject
{
// Construction
public:  
	CDr3DMgr();
//////////////////////////////////////
	DECLARE_SERIAL(CDr3DMgr)
//////////////////////////////////////
protected: 
public:
// Implementation 
	void CDr3DMgr::Init();

public:

	virtual void SetTimeStatusCursor(float fPercent);
	////////////////////////////////////////// 
//	UINT 	DoModal_EyePosition();
	///////////////////////							


protected:

	HCURSOR m_h000;
	HCURSOR m_h012;
	HCURSOR m_h250;
	HCURSOR m_h037;
	HCURSOR m_h050;
	HCURSOR m_h062;
	HCURSOR m_h075;
	HCURSOR m_h087;
	HCURSOR m_h100;


public:
	virtual ~CDr3DMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDr3DMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif
