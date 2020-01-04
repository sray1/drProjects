// DrProf_C.h : header file
//
#ifndef _DRPROF_C_H_
#define _DRPROF_C_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "DrObject.h"
#include "DrCurve.h"
#include "MatObj.h"
#include "glb_Type.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_PROF_C	2
// CDrProf_C    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrProf_C: public CDrObject
{
public:
// Construction                 
	CDrProf_C();
//////////////////////////////////////
	DECLARE_SERIAL(CDrProf_C);
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
							CDListMgr* pCurveList
						);
//	virtual	int 		Calc_3DBounds();		//ConvexHull of CNodes
    ////////////////////////////////////////////////
    virtual	CDListMgr*	GetCurveList(){return &m_CurveList;};	// curves
	virtual	CMatObj*	GetMatObj(){return m_pMatObj;};			// LocalM Input Info for later Editing
	virtual	void		SetMatObj(CMatObj* cM){m_pMatObj = cM;};
    ////////////////////////////////////////////////
    virtual	CDrCurve*	GetCurve(){return m_pCurve;};	// curves
    virtual	void		SetCurve(CDrCurve* pC){m_pCurve = pC;};

	 

protected:
	
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
	//////////////////////////////////////////////
	WORLD 	Calc_NewMin(WORLD dMinO, WORLD dMinN);
	WORLD 	Calc_NewMax(WORLD dMaxO, WORLD dMaxN);
	void 	Calc_ScreenRectFromGenerators();
	/////////////////////////////
//	void 	FinishObject();
			

protected:
// Attributes
	
	CDrCurve*	m_pCurve;		// Profile Assembled Curve
	CDListMgr	m_CurveList;	// CurveList
	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
    
    

public:
	virtual ~CDrProf_C();
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



