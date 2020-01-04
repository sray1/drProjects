// EDlgMgr.h : header file
//
#ifndef _EDLGMGR_H
#define _EDLGMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
//#include "DrPipe.h"
//#include "Dr_Qu_4.h"
/////////////////////////////////////////////////////////////////////////////
// CEDlgMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CEDlgMgr : public CObject
{
// Construction
public:  
	CEDlgMgr();
	DECLARE_SERIAL(CEDlgMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////////////// 
//	UINT	DoModal_Pipe(CDrPipe* pPipe);
//	UINT	DoModal_Qu_4(CDr_Qu_4* pQu_4);
	///////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CEDlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CEDlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
