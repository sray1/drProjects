 // mp_Rotat.h : header file
//
#ifndef _MC_BEZIER_H 
#define _MC_BEZIER_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "Inter_C1.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Bezier : public CMI_GangC
class AFX_EXT_CLASS CMC_Bezier : public CMI_GangC
{
public:

	CMC_Bezier();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Bezier)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

 	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
	int 		InterPolate_BZ(BOOL bFinal);

    				
		
protected:

	/////////////////////////////////////////////////////////////////// Linear
	int 		C1_SetMemory();
	int 		BZ_Interpolation_C1(pWORLD pCon_BZ_S,pWORLD pData,int nData);
	int 		BZ_Interpolation_C2(pWORLD pCon_BZ_S,pWORLD pData,int nData);
	int 		BZ_Interpolation_C3(CDrCurve* pCurve,pWORLD pCon_BZ_S,pWORLD pData,int nData);
	int 		BZ_PostInterpolation(pWORLD pCon_BZ_S,pWORLD pData,int nData,
																BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes


//Operations
public:

	~CMC_Bezier();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Bezier)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
