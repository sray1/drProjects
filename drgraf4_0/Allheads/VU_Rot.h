 // ELMouse.h : header file
//
#ifndef _VUROT_H 
#define _VUROT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CVu_Rot : public CMouse
{
public:

	CVu_Rot();
//////////////////////////////////////
	DECLARE_SERIAL(CVu_Rot)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT				ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////// 
	int					Do_VU_Rotate();

	
		
protected:


//	void			SizeRectDlgEd(CRect& BoxRect);

protected:  
// Attributes


	///////////////////////////////////////////////////
	int			m_nActiveObject;
	int			m_nActiveTool;



//Operations
public:

	~CVu_Rot();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CVu_Rot)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
