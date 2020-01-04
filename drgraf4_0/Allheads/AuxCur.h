// DrCurve.h : header file
//
#ifndef _AUXCUR_H_
#define _AUXCUR_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrCurve.h"
//#pragma warning( disable : 4200 )
/////////////////////////////////////////////////////////////////////////////
// CAuxCur    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CAuxCur: public CDrCurve
{
public:
// Construction                 
	CAuxCur();
//////////////////////////////////////
	DECLARE_SERIAL(CAuxCur);
//////////////////////////////////////
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	//////////////////////////						
	virtual void		Serialize(CArchive& ar);	




protected:
	
		          

			
// Helper functions
protected:
// Attributes
 
    

public:
	virtual ~CAuxCur();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CAuxCur)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



