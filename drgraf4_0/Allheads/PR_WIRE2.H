// PreRender....h : interface of the CPR_Wire2 class
//
#ifndef _PR_Wire2_H_ 
#define _PR_Wire2_H_ 

#include "DrObject.h"
////////////////////////////////////////////////////
class CPR_Wire2 : public CObject
{
public: // create from serialization only
	CPR_Wire2();
	CPR_Wire2(BOOL bParallel,int nView,BOOL bCulling3D,WORLD VDir,
				pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
				double dScale_U,double dScale_V);
	DECLARE_DYNAMIC(CPR_Wire2)

// Operations
public:

	virtual void 	Init(CDListMgr* pSortList,double dzMin,BOOL bCanonClip);
	virtual void 	RenderReadySCENE(CDC* pDC);
	virtual	void 	RenderReadyOBJECT
						(CDC* pDC,CDrObject* pObject,int nObjType);
/*
	virtual	void 	RenderReadySOLID
						(CDrObject* pObject,int nObjType);
	virtual	void 	RenderReadyPATCH
						(CDrObject* pObject,int nObjType);
*/

protected:
						
			void 	Corner_3Dto2D(CDrObject* pObject,int nObjectType);
			int		SortReadyOBJECT(CDrObject* pObj3D);
			int		SortReadySOLID(CDrObject* pSolid);
			int		SortReadyPATCH(CDrObject* pPatch);
			////////////////////////////////////////

public:
	
	virtual ~CPR_Wire2(){}; 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	CDListMgr*	m_pSortList; 
	double		m_dzMin; 	// for Clipping
	BOOL		m_bCanon;   // for Clipping
	/////////////////////////////////////////// ViewNumber
    int 		m_nView;
	/////////////////////////////////////////// Document Size
	double 		m_dScale_U;		// vv3DToLP:U-direction  
	double 		m_dScale_V;     // vv3DToLP:V-direction
	/////////////////////////////////////////// 3D drawing
	MATRIX		m_ViewM;		// viewers transform MATRIX
	MATRIX		m_ComposedM;
	MATRIX		m_vv3DM;		// Window to 3D Viewport MATRIX
    //////////////////////////////
	BOOL		m_bParallel;	// if true disables perspective projection
	BOOL		m_bCulling3D;	// if true BackFaceCulling in WorldSpace
	/////////////////// View Orientation Parameters /////////////
	WORLD		m_VDir;			// View Direction
	///////////////////////////////////////////

// Generated message map functions
protected:
	//{{AFX_MSG(CPR_Wire2)
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////
#endif
