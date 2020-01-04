// CDrPen.h : header file
//
#ifndef _DRPEN_H
#define _DRPEN_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrPen
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrPen : public CDrObject
{
// Construction
public:  
	CDrPen();

	DECLARE_SERIAL(CDrPen)


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
	///////////////////////////////////////////////////// Pen
	virtual CPen*       GetCurrentPen() { return &m_PenCur; };  
	virtual void 		ReplacePen();
    ////////////////////////////////////////////////
	virtual int			GetStyle() { return m_nPenStyle; };
	virtual void		SetStyle(int nStyle) { m_nPenStyle = nStyle; };
	virtual int			GetStyleOld() { return m_nPenStyleOld; };
	virtual void		SetStyleOld(int nStyle) { m_nPenStyleOld = nStyle; };
	virtual int			GetStyleDefault() { return m_nPenStyleDefault; };
	virtual void		SetStyleDefault(int nStyle) { m_nPenStyleDefault = nStyle; };

	virtual int			GetWidth() { return m_nPenWidth; };
	virtual void		SetWidth(int nWidth) { m_nPenWidth = nWidth; };
	virtual int			GetWidthOld() { return m_nPenWidthOld; };
	virtual void		SetWidthOld(int nWidth) { m_nPenWidthOld = nWidth; };
	virtual int			GetWidthDefault() { return m_nPenWidthDefault; };
	virtual void		SetWidthDefault(int nWidth) { m_nPenWidthDefault = nWidth; };

	virtual COLORREF	GetColor() { return m_nPenColor; };
 	virtual void		SetColor(COLORREF nColor) { m_nPenColor = nColor; };
	virtual COLORREF	GetColorOld() { return m_nPenColorOld; };
 	virtual void		SetColorOld(COLORREF nColor) { m_nPenColorOld = nColor; };
	virtual COLORREF	GetColorDefault() { return m_nPenColorDefault; };
 	virtual void		SetColorDefault(COLORREF nColor) { m_nPenColorDefault = nColor; };

    virtual UINT 		GetIndex(){return m_nPenStyleIndex;};
    virtual void 		SetIndex(UINT Index){m_nPenStyleIndex = Index;};
    virtual UINT 		GetIndexOld(){return m_nPenStyleIndexOld;};
    virtual void 		SetIndexOld(UINT Index){m_nPenStyleIndexOld = Index;};
    virtual UINT 		GetIndexDefault(){return m_nPenStyleIndexDefault;};
    virtual void 		SetIndexDefault(UINT Index){m_nPenStyleIndexDefault = Index;};
    ////////////////////////////////////////////////////////////////
    virtual UINT 		GetStyleNameCount(){return m_nPenStyleNameCount;};
    virtual void 		SetStyleNameCount(UINT nPenStyleNameCount)
    				{m_nPenStyleNameCount=nPenStyleNameCount;}; 
	virtual CString 	GetStyleName(UINT nNameIndex)
					{return m_PenStyleNames[nNameIndex];};				  
    virtual UINT		GetStyleConstant(UINT nIndex)
    				{return m_nPenStyleConstants[nIndex];};				
	////////////////////////
	virtual	void 		ReadDefaultDrPen();
	virtual	void 		InitDrPen();

protected: 


	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	///////////////////////////////////////////////////// Pen 
	CPen    	m_PenCur;           // pen created according to
	
	int			m_nPenStyleConstants[15];
	CString 	m_PenStyleNames[15]; 
	UINT		m_nPenStyleNameCount;   

    UINT		m_nPenStyleIndex;
	int			m_nPenWidth;         // user-selected pen style (width) 
	int     	m_nPenStyle;
	COLORREF 	m_nPenColor;   

    UINT		m_nPenStyleIndexOld;
	int			m_nPenWidthOld;         // user-selected pen style (width) 
	int     	m_nPenStyleOld;
	COLORREF 	m_nPenColorOld;

    UINT		m_nPenStyleIndexDefault;
	int			m_nPenWidthDefault;         // user-selected pen style (width) 
	int     	m_nPenStyleDefault;
	COLORREF 	m_nPenColorDefault;

protected: 

public:
	virtual ~CDrPen(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDrPen)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
