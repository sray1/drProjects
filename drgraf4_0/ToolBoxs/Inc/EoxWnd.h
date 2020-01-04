// boxWnd.h : header file
// 
#ifndef _EOXWND_H
#define _EOXWND_H 


/////////////////////////////////////////////////////////////////////////////
// CEoxWnd window

class CEoxWnd : public CWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CEoxWnd();
	virtual ~CEoxWnd(); 


	DECLARE_DYNAMIC(CEoxWnd);



    UINT			GetWidth();
    UINT			GetHeight();
	int  			GetActiveTool();         // move,edit etc
	int  			GetActiveElemObject();   // object type
    /////////////////////////////////////////////////////////// Children,Popup etc
	BOOL			Create(CWnd* pParentWnd,CRect rect,UINT uParentID);
	BOOL 			Create(CWnd* pParentWnd,CRect rect);
	///////////////////////////////////////////////////////////
	int 			GetToolNum(int index);
	void 			FillToolNumArray();
    ///////////////////////////////////////////////////////////////////
	void 			SetActiveTool(int nTool){m_nActiveTool = nTool;};
	void 			SetActiveElemObject(int nObject){m_nActiveElemObject = nObject;};
    void			SetWidth(UINT nWidth){m_nWidth = nWidth;};
    void			SetHeight(UINT nHeight){m_nHeight = nHeight;};
	int				GetElemBarButtCount(){return m_nElemBarButtCount;};

// Suppations
public:
	BOOL 			IsEditMoveTool(UINT nID);
	void			CalcBoxRect(CRect& BoxRect, CRect& ItemRect,int BoxWidth,int BoxHeight,
						 int ScreenHeight, int ScreenWidth, BOOL bColumn);
	void			ReSetDataDialogs();

// Implementation

protected:
  
	UINT		m_WPARAM;
	UINT		m_LPARAM;
	/////////////////////////
	UINT		m_ParentID;
	CWnd*		m_pParentWnd;
	///////////////////////////////////
    UINT    	m_nElemBarColMax;
    UINT		m_nElemBarRowMax;
	int 		m_nActiveTool;         // tool(edit or move)
	int			m_nActiveElemObject;   // other objects
	int			m_nElemBarButtCount;
	int			m_nToolNumArray[100];
	UINT		m_elembox[100];
    /////////////////////////////////
    UINT		m_nWidth;
    UINT		m_nHeight;


	// Generated message map functions
protected:

	//{{AFX_MSG(CEoxWnd)
	afx_msg void OnPaint(); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

