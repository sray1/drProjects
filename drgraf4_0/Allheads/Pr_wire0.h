// PreRender....h : interface of the CPR_Wire0 class
//
#ifndef _PR_Wire0_H_ 
#define _PR_Wire0_H_ 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
////////////////////////////////////////////////////
class AFX_EXT_CLASS CPR_Wire0 : public CObject
{
public: // create from serialization only
	CPR_Wire0();
	CPR_Wire0(BOOL bParallel,int nView,BOOL bCulling3D,WORLD VDir,
				pMATRIX pViewM,pMATRIX pComposedM,pMATRIX pvv3DM,
				double dzMin,double dScale_U,double dScale_V);
	DECLARE_DYNAMIC(CPR_Wire0)

// Operations
public:

	virtual void 	RenderReadySCENE(CDC* pDC);
	virtual	void 	RenderReadyOBJECT
						(CDC* pDC,CDrObject* pObject,int nObjectType);


protected:
						
			void 	Corner_3Dto2D(CDrObject* pObject,int nObjectType);
	////////////////////////////////////////

public:
	
	virtual ~CPR_Wire0(){}; 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	/////////////////////////////////////////// ViewNumber
    int 		m_nView;
	/////////////////////////////////////////// Document Size
	double 		m_dzMin;
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
	//{{AFX_MSG(CPR_Wire0)
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
