 // mp_Rotat.h : header file
//
#ifndef _MC_PARAB_H 
#define _MC_PARAB_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "In_Parab.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Parab : public CMI_GangC
class AFX_EXT_CLASS CMC_Parab : public CMI_GangC
{
public:

	CMC_Parab();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Parab)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	CreateParabola(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
					 CURVEPROC kind,CList<int,int>* pElperSegList,
					 BOOL bAdvanceOn,BOOL bFinal);
	CDrCurve*	GoDoIt(); 
 	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
	int 		InterPolate(BOOL bFinal);

    				
		
protected:

	CDrCurve*	GetInfo(int nButton);
	/////////////////////////////////////////////////////////////////// Linear
	int 		SetMemory();
	int 		PrepInterpolation();
	int 		PostInterpolation(BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes
	CIn_Parab	m_In_Conics;
	UINT		m_nInputType;	// PARABOLA_BY_NO3 etc

//Operations
public:

	~CMC_Parab();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Parab)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
