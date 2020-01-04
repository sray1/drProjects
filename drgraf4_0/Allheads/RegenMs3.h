 // ELMouse.h : header file
//
#ifndef _REGENMS3_H 
#define _REGENMS3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
//#include "Mouse.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CRegenMs3 : public CObject
{
public:

	CRegenMs3();
//////////////////////////////////////
	DECLARE_SERIAL(CRegenMs3)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

//	void			SetCurrentView(CView* v){m_pView = v;};
	int				UpdateMeshElemCentroids(CDrFE0D* pDrFe0D);
	int				UpdateFE3DCentroid(CDrFE3D* pDrFe3D);

protected:
	////////////////////////////////////////////////////////////////// Curve

protected:  
// Attributes





//Operations
public:

	~CRegenMs3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CRegenMs3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
