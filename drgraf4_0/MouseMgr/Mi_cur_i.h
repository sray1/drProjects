 // ELMouse.h : header file
//
#ifndef _MI_CUR_I_H 
#define _MI_CUR_I_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
#include "drpatch.h"
#include "drNode.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Cur_I : public CObject
{
public:

	CMI_Cur_I();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Cur_I)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual int 	Post_Curve(CDrObject* pObject);
    /////////////////////////////////////////////
    virtual int 	LBDownInit_CPost(){return 0;}; 
    virtual int 	LBUpCurvePost(){return 0;};
    
    virtual int 	LBDownInit_CEdit(){return 0;}; 
    virtual int 	LBUpCurveEdit(){return 0;}; 
    virtual int 	LBDownInit_CMove(){return 0;}; 
    virtual int 	LBUpCurveMove(){return 0;}; 
	///////////////////////////////////////////// 
    virtual int 	RBDown_CInsert(enum CURVEPROC kind,CView* pView,UINT nView); 
    virtual int 	RBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView); 
    				
		
protected:


protected:  
// Attributes
protected:

	CDrCurve* 	m_pDrCurve;
/*
 	/////////////////////////////////////////// INode     
	int		    m_nINodeDone;		// for Curve & Patch
	CString 	m_CurrentINodeID;
	/////////////////////////////////////////// Curve
	int			m_nMaxCurveCNodes;
	int			m_nMaxCurveINodes;
	//////////////////////////////
*/


//Operations
public:

	~CMI_Cur_I();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Cur_I)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
