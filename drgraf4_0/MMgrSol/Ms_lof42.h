 // ms_Lof42.h : header file
//
#ifndef _MS_LOF42_H 
#define _MS_LOF42_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangS.h"
#include "DrSolid.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMS_Lof42 : public CMI_GangS
{
public:

	CMS_Lof42();
//////////////////////////////////////
	DECLARE_SERIAL(CMS_Lof42)
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
					CDListMgr*						pPatchList,
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
	Pre_ST_Direction(CDrPatch* pDrPatch,int i, int nOut_ST);
	Patch_ST_Process();
		          

protected:  
// Attributes

//Operations
public:

	~CMS_Lof42();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMS_Lof42)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
