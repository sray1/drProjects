 // mp_Rotat.h : header file
//
#ifndef _MC_CIRCL_H 
#define _MC_CIRCL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Circl : public CMI_GangC
class AFX_EXT_CLASS CMC_Circl : public CMI_GangC
{
public:

	CMC_Circl();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Circl)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	GoDoIt(); 
	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal); 
 	int 		Circle(); 

    				
		
protected:

	////////////////////////////////////////////////////////////
	CDrCurve* 	GetInfo();
	int			Circle_PrepInterpolation();
	void		FillINodesLOCAL(CDListMgr* pCurveCNodeList,
							pWORLD pIn,pDOUBLE pInWts,int nMaxCNodes);
	int			Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE Radius, WORLD Normal,WORLD AxPt);
	void		UnitAxisFromEndNodes(pWORLD pNormal);
	int 		GenerateCNodes();
	int			Circle_PostInterpolation(BOOL bFinal);
	/////////////////////////
		          

protected:  
// Attributes

	int			m_nInputType;

//Operations
public:

	~CMC_Circl();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Circl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
