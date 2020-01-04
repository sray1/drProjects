// elemobj.h : header file
//
#ifndef _DECKMGR_H
#define _DECKMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CDeckMgr
/////////////////////////////////////////////////////////////////////////////
class CDeckMgr : public CObject
{
// Construction
public:  
	CDeckMgr();
	DECLARE_SERIAL(CDeckMgr)
protected: 
public:
// Implementation 

public:

				// ItemID = Node etc. SubItemID = Coords, Connectivity etc	
//	UINT		Options(CView* pView,UINT ItemID,UINT SubItemID);
	void		UpdateDeckList();
	/////////////////////////////////////////////////////////////////
	BOOL		IsFormatted(){return m_bFormatted;}; 
	void		SetFormatted(BOOL b){m_bFormatted = b;};
	////////////////////////////////////////////////////
	CList<CString,CString>*	GetDeckList(){return &m_DeckList;};



protected:

	////////////////////////////////
	BOOL					m_bFormatted;	//cards
	CList<CString,CString>	m_DeckList;
	/////////////////////////////////

public:
	virtual ~CDeckMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDeckMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
