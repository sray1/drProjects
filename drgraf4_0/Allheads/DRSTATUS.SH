// drstatus.h : header file
//
#ifndef _STATUSBAR_H 
#define _STATUSBAR_H  

#include "stdafx.h"
#include "afxext.h"
#include "D:\msvc\mfc\src\auxdata.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDrStatusBar window

class CDrStatusBar : public CStatusBar
{
// Construction
public:
	CDrStatusBar();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CDrStatusBar();

protected:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	
////////////////////////////////////////////////////////////FROM: afxext.h   
	static void PASCAL DrawStatusText(HDC hDC, CRect const& rect,
			LPCSTR lpszText, UINT nStyle);
	virtual void DoPaint(CDC* pDC);
///////////////////////////////////// 
};

//////////////////////////////////////////////// CTopStatusBar window
class CTopStatusBar: public CDrStatusBar
{
// Construction
public:
	CTopStatusBar();

// Attributes
public:

// Operations
public:
	int	 Init();

// Implementation
public:
	virtual ~CTopStatusBar(){};

};

 //////////////////////////////////////////////// CBottomStatusBar window

class CBotStatusBar: public CDrStatusBar
{
// Construction
public:
	CBotStatusBar();

// Attributes
public:

// Operations
public:
	int	 Init();

// Implementation
public:
	virtual ~CBotStatusBar(){};

};
///////////////////////////////
#endif
