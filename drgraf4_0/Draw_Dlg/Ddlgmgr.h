// DDlgMgr.h : header file
//
#ifndef _DDLGMGR_H
#define _DDLGMGR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CDDlgMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDDlgMgr : public CObject
{
// Construction
public:  
	CDDlgMgr();
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
	DECLARE_SERIAL(CDDlgMgr)
//////////////////////////////////////
#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA
protected: 
public:
// Implementation 

public:

	//////////////////////////////////////////////////////////// 
	UINT DoModal_Label_Insert(int nView, POINT point);
	UINT DoModal_Label_Edit(int index);
	UINT DoModal_Grid_Insert();
	/////////////////////////////////////////////							

public:
	virtual ~CDDlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CDDlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
