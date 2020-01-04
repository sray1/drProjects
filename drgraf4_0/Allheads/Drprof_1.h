// DrProf_C.h : header file
//
#ifndef _DRPROF_1_H_
#define _DRPROF_1_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "DrObject.h"
#include "DrMesh1D.h"
#include "MatObj.h"
#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_PROF_C	2
// CDrProf_1    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrProf_1: public CDrObject
{
public:
// Construction                 
	CDrProf_1();
//////////////////////////////////////
	DECLARE_SERIAL(CDrProf_1);
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
							CDListMgr* pMesh1DList
						);
//	virtual	int 		Calc_3DBounds();		//ConvexHull of CNodes
    ////////////////////////////////////////////////
    virtual	CDListMgr*	GetMesh1DList(){return &m_Mesh1DList;};	// curves
    virtual	CDListMgr*	GetLMList(){return &m_LMList;};	// Local Matrix
//	virtual	CMatObj*	GetMatObj(){return m_pMatObj;};			// LocalM Input Info for later Editing
//	virtual	void		SetMatObj(CMatObj* cM){m_pMatObj = cM;};
    ////////////////////////////////////////////////
    virtual	CDrMesh1D*	GetMesh1D(){return m_pMesh1D;};	// curves
    virtual	void		SetMesh1D(CDrMesh1D* pC){m_pMesh1D = pC;};

	 

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
	
	CDrMesh1D*	m_pMesh1D;		// Profile Assembled Mesh1D
	CDListMgr	m_Mesh1DList;	// Mesh1DList
//	CMatObj*	m_pMatObj;		// Local Transform Input Info for later Editing
	CDListMgr	m_LMList;		// Local Transform List
    
    

public:
	virtual ~CDrProf_1();
public:
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



