// zoomdlg.h : header file
/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog
#ifndef _ZOOMFACTOR
#define _ZOOMFACTOR  

#include "stdafx.h"

#include "resource.h"

class CZoomDlg : public CDialog
{
// Construction
public:
	CZoomDlg(CWnd* pParent = NULL);	// standard constructor 
	void 	SetZoomX(float fZoomX){m_Zoom_X = fZoomX;};
	void 	SetZoomY(float fZoomY){m_Zoom_Y = fZoomY;};
	void 	SetZoomZ(float fZoomZ){m_Zoom_Z = fZoomZ;};
	float 	GetZoomX(){return m_Zoom_X;};
	float 	GetZoomY(){return m_Zoom_Y;};
	float 	GetZoomZ(){return m_Zoom_Z;};
protected: 
	CBitmapButton buttonOK,buttonCancel;

// Dialog Data
	//{{AFX_DATA(CZoomDlg)
	enum { IDD = IDD_ZOOMFACTOR };
	float	m_Zoom_X;
	float	m_Zoom_Y;
	float	m_Zoom_Z;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CZoomDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
///////////////////////
