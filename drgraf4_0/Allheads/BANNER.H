// drgrafrm.h : interface of the CBanner class
//
#ifndef _CBANNER_H_ 
#define _CBANNER_H_ 

#include "mdib.h"
/////////////////////////////////////////////////////////////////////////////
class CBanner : public CWnd
{
	DECLARE_SERIAL(CBanner)
public:
	CBanner();

// Attributes
public:

// Operations
public: 

	void 	Init(int nPic);
	void	SetDestroy(BOOL bD){m_bDestroy = bD;}; 
	BOOL 	Create();
	void 	DissolveDot(CDC*pDC,CRect &clRect);
	void 	DissolveRect(CDC*pDC,CRect &clRect);
	void 	Dog_N_PonyShow(CDC*pDC,CRect &clRect);


public:
	HDIB 	GetHDIB() const
				{ return m_hDIB; }
			CPalette* GetDocPalette() const
				{ return m_palDIB; }

// Operations
private: 

	void 	InitDIBData();
	void 	ReplaceHDIB(HDIB hDIB);
	void 	LoadImageDIB(CDC *pDC,int nPicture);
	BOOL 	LoadImageDIBfromFile(CMDIB *pDIB, char* pszPathName);

    
// Implementation
public:
	virtual ~CBanner();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HDIB 		m_hDIB;
	CPalette* 	m_palDIB;
protected:  // 

	BOOL		m_bDestroy;
	CPalette* 	m_pColorPal;
	
private:


	CMDIB*		m_pDIBImage;	

	int 		m_bmWidth;     // Bitmap width
	int 		m_bmHeight;    // Bitmap height


	UINT 		m_imageScanLines;
	void*		m_lpImageBits; 
	BITMAPINFO*	m_lpImageBitsInfo;
	DWORD 		m_imageDIBWidth;
	DWORD 		m_imageDIBHeight;

	int 		m_screenWidth;
	int 		m_screenHeight;
		
	
    
// Generated message map functions
protected:
	// User message
	//{{AFX_MSG(CBanner)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
