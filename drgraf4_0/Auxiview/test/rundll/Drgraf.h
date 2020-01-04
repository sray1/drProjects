// drgraf.h : main header file for the DRGRAF application
//
#ifndef _DRGRAF
#define _DRGRAF 

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols 
#include "aboutbox.h"  
#include "Banner.h"  
/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp:
// See drgraf.cpp for the implementation of this class
//
///////////////////////////////// Forward References 
class CDrGrafDoc;
class CDrGrafFrame;
class CSplashWnd;
//////////////////////////////////
class CDrGrafApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDrGrafApp();
	~CDrGrafApp();
// Overrides
	virtual BOOL InitInstance();
    virtual	BOOL OnIdle(long lCount);  

// Implementation

	BOOL 		CreateBannerWnd(CBanner* pBanWnd);
	CBanner*	GetBannerWnd(){return &m_BannerWnd;};
	CDrGrafDoc* GetDocument(){return m_pDocument;};
	void 		SetDocument();
	void 		SetDocument(CDrGrafDoc* pDoc);
    //////////////////////////////////////////////////////////////
	CMultiDocTemplate* 	Get12ViewTemplate(){return m_p12ViewTemplate;};
	CMultiDocTemplate* 	Get23ViewTemplate(){return m_p23ViewTemplate;};
	CMultiDocTemplate* 	Get31ViewTemplate(){return m_p31ViewTemplate;};
	CMultiDocTemplate* 	Get3DViewTemplate(){return m_p3DViewTemplate;};
	CMultiDocTemplate* 	GetDataViewTemplate(){return m_pDataViewTemplate;};
	CMultiDocTemplate* 	GetMeshDataViewTemplate(){return m_pMeshDataViewTemplate;};
	CMultiDocTemplate* 	GetDeckViewTemplate(){return m_pDeckViewTemplate;};
	CMultiDocTemplate* 	GetStatViewTemplate(){return m_pSpecViewTemplate;};
	CMultiDocTemplate* 	GetSpecViewTemplate(){return m_pSpecViewTemplate;};
	CMultiDocTemplate* 	GetHistViewTemplate(){return m_pSpecViewTemplate;};
    //////////////////////////////////////////////////////////////
	virtual 	CDocument* OpenDocumentFile(LPCSTR lpszFileName);
	void 		UpdateIniFileWithDocPath(const char* pszPathName);
	CString 	GetDocPathFromIniFile();
	

public:

	COleTemplateServer m_server;
		// Server object for document creation



protected:
	
	BOOL 	CreateMainFrame(CDrGrafFrame* pMainFrame); 
	void 	RegisterDocTemplates();
	//////////////////////////////// DrCafeBitMap
	void	Dog_N_PonyShow();
	void 	Dissolve();
	/////////////////////////////
	BOOL	RegisterNewClasses();
	void	InitDLLs();
	BOOL	ShowBanner();
	
		
protected:


	/////////////////////////////////////////////// Banner
	CBanner				m_BannerWnd;
	/////////////////////////////////////////////// Templates
	CMultiDocTemplate* 	m_p12ViewTemplate;
	CMultiDocTemplate* 	m_p23ViewTemplate;
	CMultiDocTemplate* 	m_p31ViewTemplate;  
	CMultiDocTemplate* 	m_p3DViewTemplate;  
	CMultiDocTemplate* 	m_pDataViewTemplate; 
	CMultiDocTemplate* 	m_pMeshDataViewTemplate; 
	CMultiDocTemplate* 	m_pDeckViewTemplate; 
	CMultiDocTemplate* 	m_pStatViewTemplate; 
	CMultiDocTemplate* 	m_pSpecViewTemplate; 
	CMultiDocTemplate* 	m_pHistViewTemplate; 
	/////////////////////////////////////////////// DrCafe BitMap
    DWORD				m_dwDrCafeTime;
	CBitmap				m_DrCafeBM;
	CDC					m_DrCafeDC;
	CBitmap*			m_pOldBM;
	int					m_nsW;	
	int					m_nsH;	
	int					m_nX;	
	int					m_nY;	
    /////////////////////////////////////////////// Splash Window
    DWORD				m_dwSplashTime;
    CSplashWnd  		m_splash; 
    ///////////////////////////////////////////////
	CDrGrafDoc*			m_pDocument;		


	//{{AFX_MSG(CDrGrafApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnContextHelp();
	afx_msg void OnUpdateContextHelp(CCmdUI* pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
//}}AFX_VBX_REGISTER

/////////////////////////////////////////////////////////////////////////////
#endif
