// DrF_MCur.h : header file
//
#ifndef _DRF_MCUR_H_
#define _DRF_MCUR_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrCurve.h"

//#pragma warning( disable : 4200 )
/////////////////////////////////////////////////////////////////////////////
// CDrF_MCur    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrF_MCur: public CDrCurve
{
public:
// Construction                 
	CDrF_MCur();
//////////////////////////////////////
	DECLARE_SERIAL(CDrF_MCur);
//////////////////////////////////////
	virtual void		Serialize(CArchive& ar);	
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrCurve;
	virtual void		DoDataView(CDC* PtrDC, int y);

			
// Helper functions
protected:
// Attributes
 

    

public:
	virtual ~CDrF_MCur();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrF_MCur)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



