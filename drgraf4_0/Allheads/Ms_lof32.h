 // ms_Lof32.h : header file
//
#ifndef _MS_LOF32_H 
#define _MS_LOF32_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangS.h"
#include "DrSolid.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMS_Lof32 : public CMI_GangS
{
public:

	CMS_Lof32();
//////////////////////////////////////
	DECLARE_SERIAL(CMS_Lof32)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	int			SetInfoBase							// dLen and FromID, ToID given;		(Type 1)default
													// Axis Computed from FromID, ToID
				(
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					CDListMgr*						pCurveList,
					CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
					CList<int,int>*					pElperSegList,
					double							Ratio,
					CView*							pView
				); 
	CDrSolid*	GoDoIt(); 
	int			GoDoIt(CDrSolid* pDrSolid);
 
    				
		
protected:

	////////////////////////////////////////////////////////////
	int 		Loft(); 
	CDrSolid* 	GetInfo();
	int			GetInfo(CDrSolid* pDrSolid);
	int 		GenerateCNodes();
	/////////////////////////
		          

protected:  
// Attributes

//Operations
public:

	~CMS_Lof32();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMS_Lof32)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
