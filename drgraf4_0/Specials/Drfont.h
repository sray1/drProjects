// CDrFont.h : header file
//
#ifndef _DRFONT_H
#define _DRFONT_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrFont
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFont : public CDrObject
{
// Construction
public:  
	CDrFont();

	DECLARE_SERIAL(CDrFont)


protected: 
public:
// Implementation
public:

	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void 	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	//////////////////////////////////////////////// Font
	virtual BOOL		IsFontSelected(){return m_bFontSelected;};
	virtual COLORREF	GetTextColor(){return m_FontColor;};
	virtual void		SetTextColor(COLORREF crColor){m_FontColor = crColor;};
	virtual LOGFONT		GetCurrentLogFont(){return m_lf;};
	virtual void		SetCurrentLogFont(LOGFONT lf){m_lf = lf;};
//	HFONT		GetCurrentFontHandle(){return m_hFont;};
	virtual void 		DoTextFont();
	////////////////////////
	virtual	void 		ReadDefaultDrFont();
	virtual	void 		InitDrFont();


protected: 

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	///////////////////////////////////////// Font
	BOOL		m_bFontSelected;
	COLORREF	m_FontColor;
	LOGFONT		m_lf;

protected: 

public:
	virtual ~CDrFont(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFont)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
