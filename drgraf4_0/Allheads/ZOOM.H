// CZoom.h : header file
//
#ifndef _ZOOMOBJECT
#define _ZOOMOBJECT

#include "stdafx.h"  

#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CZoom
/////////////////////////////////////////////////////////////////////////////
class CZoom : public CObject
{
// Construction
public:  
	CZoom();
	DECLARE_SERIAL(CZoom)
protected: 
public:
// Implementation
public:     

	/////////////////////////////////////////////////////////// Zoom/Frame
	void	SetZoomFactor(WORLD NewZoomFactor,int n_ViewNumber);
	WORLD	GetZoomFactor(int nViewNumber);   

protected: 

	///////////////////////////////////////////////////// Zoom 
	void 	ReadDefaultZoom();
	void	InitializeZoom();
	
protected:

	///////////////////////////////////////// Zoom/Frame
	WORLD		m_ZoomFactor12;             
	WORLD		m_ZoomFactor23;             
	WORLD		m_ZoomFactor31;             
	WORLD		m_ZoomFactorISO;            
	////////////////////////////
	
protected: 

public:
	virtual ~CZoom(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CZoom)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif
