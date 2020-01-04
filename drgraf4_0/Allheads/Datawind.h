// CDataWindow.h : header file
//
#ifndef _DATAWINDOW
#define _DATAWINDOW

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDataWindow
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDataWindow : public CDrObject
{
// Construction
public:  
	CDataWindow();

	DECLARE_SERIAL(CDataWindow)


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
	////////////////////////////////////////////////////////
	virtual LPOINT3		GetWinOrgWIC(){return m_WinOrgWIC;};
	virtual LPOINT3		GetWinMinWIC(){return m_WinMinWIC;};
	virtual LPOINT3		GetWinMaxWIC(){return m_WinMaxWIC;};
    virtual void		SetWinMinMaxWIC(LPOINT3 NewWIC);
    virtual LPOINT3		GetWinExtWIC(){return m_WinExtWIC;};
    virtual void		SetWinExtWIC();
	////////////////////////////////////////////
	virtual	void 		ReadDefaultDataWindow();
	virtual	void 		InitDataWindow();


protected: 

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	///////////////////////////////////////////////////// DataWindow
	LPOINT3		m_WinOrgWIC;
	LPOINT3		m_WinOrgWICOld;
	LPOINT3		m_WinOrgWICDefault;
	LPOINT3		m_WinMinWIC;
	LPOINT3		m_WinMaxWIC;
	LPOINT3		m_WinExtWIC;
	LPOINT3		m_WinMinWICOld;
	LPOINT3		m_WinMaxWICOld;
	LPOINT3		m_WinExtWICOld;
	LPOINT3		m_WinMinWICDefault;
	LPOINT3		m_WinMaxWICDefault;
	LPOINT3		m_WinExtWICDefault; 

protected: 

public:
	virtual ~CDataWindow(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDataWindow)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
