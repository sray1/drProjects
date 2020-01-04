// FreeHandBase.h : interface of the CFreeHandBase class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _FREEHANDBASE_H
#define _FREEHANDBASE_H 
 
#include "stdafx.h"
#include "dboxmgr.h"
#include "FreeHand.h"
#include "globals.h"  

class CFreeHandBase : public CObject 
{

protected: // create from serialization only
	CFreeHandBase();
	DECLARE_DYNCREATE(CFreeHandBase)

// Attributes
public: 
	///////////////////////////////////////////////////// FreeHand
	POSITION		GetFirstFreeHandPos();  				
	CDrFreeHand*	GetNextFreeHand( POSITION& pos);
	CDrFreeHand* 	GetFreeHand(int index);
	CDrFreeHand*	NewFreeHand();
	int 			AddFreeHand(CDrFreeHand* pAddFreeHand);
	int				EditFreeHand(int index,CDrFreeHand* pEditFreeHand);
	int				DeleteFreeHand(int index);
	int				GetFreeHandIndex(UINT KeyNo); 
//	int				GetFreeHandIndex(CString KeyID,UINT KeyNo); 
	/////////////////////////////////////////////////////////////
protected:                  

    UINT			m_MaxFreeHands;
    
// Operations
public:
// Implementation
public:
	virtual ~CFreeHandBase();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CFreeHandBase)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
