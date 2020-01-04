 // mp_Loft2.h : header file
//
#ifndef _MP_LOFT2_H 
#define _MP_LOFT2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_Loft2 : public CMI_GangP
class AFX_EXT_CLASS CMP_Loft2 : public CMI_GangP
{
public:

	CMP_Loft2();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Loft2)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	int			SetInfoBase
				(
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pCurveList,
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					CList<int,int>*					pElperSegList,
					double							Ratio,
					CView*							pView
				); 
	CDrPatch*	GoDoIt(); 
  	int			GoDoIt(CDrPatch* pDrPatch);

    				
		
protected:

	////////////////////////////////////////////////////////////
	int 		Loft(); 
	CDrPatch* 	GetInfo();
	int			GetInfo(CDrPatch* pDrPatch);
	int 		GenerateCNodes();
	/////////////////////////
	int			Pre_S_Direction(CDrCurve* pDrCurve,int i, int nOut_S);
	int			Curve_S_Process();
		          

protected:  
// Attributes

//Operations
public:

	~CMP_Loft2();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Loft2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
