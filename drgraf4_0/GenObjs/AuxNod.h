// Node.h : header file
//
#ifndef _AUXNOD_H
#define _AUXNOD_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrNode.h"
/////////////////////////////////////////////////////////////////////////////
// CAuxNod    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CAuxNod: public CDrNode
{
///////////////////////////////////////////////////
public:
// Construction                 
	CAuxNod();
//////////////////////////////////////
	DECLARE_SERIAL(CAuxNod);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual NODECARD*	Parse_drPipe(CString* pstrCard)
						{return (NODECARD*)NULL;};                    //  TOBE DONE
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	// for DECKVIEW
	virtual	void		DoFormattedCardView(CString* pstrCard,CString& strFmt){};
	virtual	void		DoUnFormattedCardView(CString* pstrCard){};
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	//////////////////////////						
	virtual void		Serialize(CArchive& ar);	

	///////////////////////////////////////////////////////////////



	
protected:
	
// Helper functions
protected:
// Attributes
 
 
	
	//////////////////////////////    							

public:
	virtual ~CAuxNod();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CAuxNod)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



