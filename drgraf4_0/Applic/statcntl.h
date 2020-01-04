// StatCntl.h : header file
//
#ifndef _STATCNTL_H
#define _STATCNTL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////////////////////////////
// CStatCntl window 
class CStatCntl : public CWnd
{
public:
CStatCntl();
~CStatCntl();
	DECLARE_DYNCREATE(CStatCntl);


public:

	UINT		GetControlID(){return m_ControlID;};
	void		SetControlID(UINT i){m_ControlID = i;};
    /////////////////////////////////////////////////////////// Children,Popup etc
	BOOL		Create(CWnd* pParentWnd,CRect rect,UINT uControlID,UINT uParentID);
	BOOL		Create(CWnd* pParentWnd,CRect rect,UINT uControlID);
	///////////////////////////////////////////////////////////
	void		ReCalcLayOut();
	///////////////////////////
	CPoint&		GetLeftTop(){return m_ptLeftTop;};
    void		SetLeftTop(CPoint& p){m_ptLeftTop = p;};
	UINT		GetWidth(){return m_nWidth;};
    void		SetWidth(UINT nWidth){m_nWidth = nWidth;};
	UINT		GetHeight(){return m_nHeight;};
    void		SetHeight(UINT nHeight){m_nHeight = nHeight;};
	COLORREF	GetPenColor(){return m_crPenColor;};
	void		SetPenColor(COLORREF c){m_crPenColor = c;};
	COLORREF	GetBrColor(){return m_crBrColor;};
	void		SetBrColor(COLORREF c){m_crBrColor = c;};
	COLORREF	GetBrColorDfalt(){return m_crBrColorDfalt;};
	void		SetBrColorDfalt(COLORREF c){m_crBrColorDfalt = c;};
	////////////////////////////////////////////////////////////////////////// Normal
	void		GetPenInfo(UINT& nWidth,COLORREF& crColor,UINT& nStyle)
					{	nWidth  =	m_nPenWidth;
					 	crColor =	m_crPenColor;
						nStyle  =	m_nPenStyle;
				  	};	
	void		SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidth  = nWidth;
						m_crPenColor = crColor;
					 	m_nPenStyle  = nStyle;
					};
	CString&	GetText(){return m_strText;};
	void		SetText(CString& str){m_strText = str;};
	void		SetLogFont(LOGFONT lf){ m_lf = lf;};
	COLORREF	GetTextColor(){return m_crTextColor;};
	void		SetTextColor(COLORREF c){m_crTextColor = c;};
	LOGFONT		GetLogFont(){ return m_lf;};
	////////////////////////////////////////
	void		SetInfo(CPoint ptLeftTop,CString strText,UINT nPenStyle,
						UINT nPenWidth,COLORREF	crPenColor,COLORREF crBrColor,
						UINT nWidth,UINT nHeight,LOGFONT lf,COLORREF crTextColor)
				{
					/////////////////////////
					m_ptLeftTop		= ptLeftTop;
					m_strText		= strText;
					m_nPenStyle		= nPenStyle;
					m_nPenWidth		= nPenWidth;
					m_crPenColor	= crPenColor;
					m_crBrColor		= crBrColor;
					m_crBrColorDfalt= m_crBrColor;
					m_nWidth		= nWidth;
					m_nHeight		= nHeight;
					m_lf			= lf;
					m_crTextColor	= crTextColor;
					/////////////////////////
				};

protected:
			void	InvertTracker(CPoint point);

protected:
	BOOL		m_bTrackMove;
	CPoint		m_ptMouse, m_ptLast;
	/////////////////////////
	UINT		m_ParentID;
	CWnd*		m_pParentWnd;
	UINT		m_ControlID;
	/////////////////////////
	CPoint		m_ptLeftTop;
	CString		m_strText;
	UINT		m_nPenStyle;
	UINT		m_nPenWidth;
	COLORREF	m_crPenColor;
	COLORREF	m_crBrColor;
	COLORREF	m_crBrColorDfalt;
    UINT		m_nWidth;
    UINT		m_nHeight;
	//////////////////////
	LOGFONT		m_lf;
	COLORREF	m_crTextColor;


	// Generated message map functions
protected:

	//{{AFX_MSG(CStatCntl)
	afx_msg void OnPaint(); 
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA

#endif
/////////////////////////////////////////////////////////////////////////////
