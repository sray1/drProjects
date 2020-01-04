// grafobj.h : header file
//
#ifndef _DBOBJMGR_H
#define _DBOBJMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

//////////////////////////////////////////////// DeckRowHint Class
class AFX_EXT_CLASS CBaseRowHint : public CObject
{
public:
	CBaseRowHint();
	DECLARE_DYNAMIC(CBaseRowHint)
};
/////////////////////////////////////////////////////////////////////////////
// CDbObjMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDbObjMgr : public CObject
{
// Construction
public:
	CDbObjMgr();

	DECLARE_SERIAL(CDbObjMgr)


public:
 

	void			Init();
	CString&		GetCurrentItem() { return m_CurrentItem; };
	void			SetCurrentItem(CString& item) {m_CurrentItem = item;} ;
	CString&		GetCurrentParent() { return m_CurrentParent; };
	void			SetCurrentParent(CString& item) {m_CurrentParent = item;} ;
	UINT			GetObjectName_N_ID(CString& strItem);
	UINT			LookUpID(CString& strItem);
	LPCTSTR			LookUpName(UINT ID);
	int				ShowActiveObject_On_Off(CString& strItem,CString& strPar,BOOL bOn);
	
// Helper functions




protected:

										
		   
protected:

	CString		m_CurrentItem;
	CString		m_CurrentParent;
	////////////////////////
	
public:
// Implementation
public:
	virtual ~CDbObjMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o



};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////
#endif

