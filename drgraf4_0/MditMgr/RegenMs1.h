 // ELMouse.h : header file
//
#ifndef _REGENMS1_H 
#define _REGENMS1_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
//#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegenMs1 : public CObject
{
public:

	CRegenMs1();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenMs1)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

//	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateMeshElemCentroids(CDrFE0D* pDrFe0D);
	int				UpdateFE1DCentroid(CDrFE1D* pDrFe1D);

protected:
	////////////////////////////////////////////////////////////////// Curve

protected:  
// Attributes





//Operations
public:

	~CRegenMs1();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenMs1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
