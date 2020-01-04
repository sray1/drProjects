 // ELMouse.h : header file
//
#ifndef _REGENMS2_H 
#define _REGENMS2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
//#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegenMs2 : public CObject
{
public:

	CRegenMs2();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenMs2)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

//	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateMeshElemCentroids(CDrFE0D* pDrFe0D);
	int				UpdateFE2DCentroid(CDrFE2D* pDrFe2D);

protected:
	////////////////////////////////////////////////////////////////// Curve

protected:  
// Attributes





//Operations
public:

	~CRegenMs2();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenMs2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
