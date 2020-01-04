// drstatus.h : header file
//
#ifndef _STATUSBAR_H 
#define _STATUSBAR_H  

#include "afxext.h"
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// CTopStatusBar window
class CTopStatusBar: public CStatusBar
{
// Construction
public:
	CTopStatusBar();
	void UpdateStatusBar(CClientDC*  pDC);
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

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

class CBotStatusBar: public CStatusBar
{
// Construction
public:
	CBotStatusBar();
	void UpdateStatusBar(CClientDC*  pDC);
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

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
