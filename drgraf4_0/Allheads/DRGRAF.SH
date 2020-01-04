// drgraf.h : main header file for the DRGRAF application
//
#ifndef _DRGRAF
#define _DRGRAF 

#include "stdafx.h"
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "resource.h"		// main symbols 
#include "otherids.h"

#include "aboutbox.h"  
                       

#include "waitcur.h"
//#include "globals.h"    


/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp:
// See drgraf.cpp for the implementation of this class
//
///////////////////////////////// Forward References
class CDrGrafFrame;
class CSplashWnd;
//////////////////////////////////
class CDrGrafApp : public CWinApp
{
public:
	CDrGrafApp();
	void 	UpdateIniFileWithDocPath(const char* pszPathName);
	CString GetDocPathFromIniFile(); 

// Overrides                    
private:
	virtual BOOL InitInstance(); 
	virtual int	 ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCSTR lpszFileName);
    virtual	BOOL OnIdle(LONG lCount);  
   
    DWORD		m_dwSplashTime;
    CSplashWnd  m_splash;
    
// Implementation  
public:   

	CMultiDocTemplate* m_p12ViewTemplate;
	CMultiDocTemplate* m_p23ViewTemplate;
	CMultiDocTemplate* m_p31ViewTemplate;  
	CMultiDocTemplate* m_pIsoViewTemplate;  
	CMultiDocTemplate* m_pDataViewTemplate;  

    CDocument*	m_pDoc;    
    CDocument*	m_Current_pDoc;

private:
	
	void CreateMainFrame(CDrGrafFrame* pMainFrame); 
	void RegisterDocTemplates();
 	
	//{{AFX_MSG(CDrGrafApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
//}}AFX_VBX_REGISTER

/////////////////////////////////////////////////////////////////////////////
extern CDrGrafApp	theApp; 
#endif
