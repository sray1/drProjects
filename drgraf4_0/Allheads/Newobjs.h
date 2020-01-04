// NewObjs.h : interface of the CNewObjs class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _NEWOBJS_H_
#define _NEWOBJS_H_ 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "stdafx.h" 

#include "DrObject.h"

class AFX_EXT_CLASS CNewObjs : public CObject 
{

public: // create from serialization only
	CNewObjs();

	DECLARE_DYNCREATE(CNewObjs)



// Attributes
public: 
	///////////////////////////////////////////////////// Object
	CDrObject*	NewObject(int nObjectType);
	/////////////////////////////////////////////////////
	
protected:                  

    
// Operations
public:
// Implementation
public:
	virtual ~CNewObjs();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:


};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif
