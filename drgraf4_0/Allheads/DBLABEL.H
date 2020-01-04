// LabelBase.h : interface of the CLabelBase class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef LABELBASE_H
#define LABELBASE_H 
 
#include "stdafx.h"

#include "dboxmgr.h"
#include "label.h"
#include "globals.h"  

class CLabelBase : public CObject 
{

protected: // create from serialization only
	CLabelBase();
	DECLARE_DYNCREATE(CLabelBase)

// Attributes
public: 
	///////////////////////////////////////////////////// Label
	POSITION	GetFirstLabelPos();  				
	CDrLabel*	GetNextLabel( POSITION& pos);
	CDrLabel* 	GetLabel(int index);
	CDrLabel*	NewLabel();
	int 		AddLabel(CDrLabel* pAddLabel);
	int			EditLabel(int index,CDrLabel* pEditLabel);
	int			DeleteLabel(int index);
	int			GetLabelIndex(CString KeyID,UINT KeyNo); 
	/////////////////////////////////////////////////////////////
protected:                  

    UINT		m_MaxLabels;
    
// Operations
public:
// Implementation
public:
	virtual ~CLabelBase();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CLabelBase)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
