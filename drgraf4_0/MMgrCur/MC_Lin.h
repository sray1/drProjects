 // mp_Rotat.h : header file
//
#ifndef _MC_LIN_H 
#define _MC_LIN_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "Inter_C1.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Lin : public CMI_GangC
class AFX_EXT_CLASS CMC_Lin : public CMI_GangC
{
public:

	CMC_Lin();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Lin)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	GoDoIt(); 
 	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
	int 		InterPolate_C1(BOOL bFinal);

    				
		
protected:

	CDrCurve*	GetInfo(int nButton);
	/////////////////////////////////////////////////////////////////// Linear
	int 		C1_SetMemory();
	int 		C1_PrepInterpolation(CInter_C1* pInter_C1);
	int 		C1_PostInterpolation(CInter_C1* pInter_C1,BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes


//Operations
public:

	~CMC_Lin();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Lin)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
