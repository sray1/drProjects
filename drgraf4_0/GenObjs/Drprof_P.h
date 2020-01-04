// DrProf_P.h : header file
//
#ifndef _DRPROF_P_H_
#define _DRPROF_P_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrProf_C.h"

#include "DrObject.h"
#include "DrPatch.h"
#include "MatObj.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_CURVES_PROF_P	1
// CDrProf_P    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrProf_P: public CDrProf_C
{
public:
// Construction                 
	CDrProf_P();
//////////////////////////////////////
	DECLARE_SERIAL(CDrProf_P);
//////////////////////////////////////
	
	
// Operations
public:

	virtual void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	///////////////////////////////////////////////////////////////////////
	virtual void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual void 		TransformObjectToView(pMATRIX pViewM);
	virtual BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual void 		ProjectObject
							(	pMATRIX pvv3DM,
								double dScale_U,double dScale_V
							);
	virtual	int 		Calc_3DBoundsLocal();
	///////////////////////////////////////////////////////////////////
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////////						
	virtual	int 		AppendToObject
						(
							CDListMgr* pPatchList
						);
//	virtual	int 		Calc_3DBounds();		//ConvexHull of CNodes
    ////////////////////////////////////////////////
    virtual	CDListMgr*	GetPatchList(){return &m_PatchList;};	// Patches
    ////////////////////////////////////////////////
    virtual	CList<int,int>*	GetCurIndexList(){return &m_CurIndexList;};	// Indices
    ////////////////////////////////////////////////
    virtual	CDrPatch*	GetPatch(){return m_pPatch;};	// Patch
    virtual	void		SetPatch(CDrPatch* pC){m_pPatch = pC;};

	 

protected:
	
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
	//////////////////////////////////////////////
//	WORLD 	Calc_NewMin(WORLD dMinO, WORLD dMinN);
//	WORLD 	Calc_NewMax(WORLD dMaxO, WORLD dMaxN);
	void 	Calc_ScreenRectFromGenerators();
	/////////////////////////////
//	void 	FinishObject();
			

protected:
// Attributes
	
	CDrPatch*		m_pPatch;		// Profile Assembled Patch
	CDListMgr		m_PatchList;	// PatchList
	CList<int,int>	m_CurIndexList;	// Jouned_Curves Indices for Patches making up Profile
									// for quick search
//	CDListMgr	m_LMList;		// Local Transform List
    
    

public:
	virtual ~CDrProf_P();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



