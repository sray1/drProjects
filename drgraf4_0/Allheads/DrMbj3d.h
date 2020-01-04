// Obj3D.h : header file
//
#ifndef _DRMBJ3D_H_
#define _DRMBJ3D_H_       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h"
//#pragma warning( disable : 4200 )
#include "Def_Rend.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_OBJ3D	2
// CDrMbj3D    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrMbj3D: public CDrObject
{
public:
// Construction                 
	CDrMbj3D();
//////////////////////////////////////
	DECLARE_SERIAL(CDrMbj3D);
//////////////////////////////////////
	
	
// Operations
public:

	virtual void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
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
	virtual BOOL		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////////						
	virtual	int 		AppendToObject
						(
							CDListMgr* pObj3DList,
							CDListMgr* pSolidList,
							CDListMgr* pPatchList,
							CDListMgr* pCurveList
						);
//	virtual	int 		Calc_3DBounds();		//ConvexHull of CNodes
    ////////////////////////////////////////////////

	 

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
	////////////////////////////////////////////////////////////////////////////////////////
//	void 	FinishObject();
			
// Helper functions
protected:
// Attributes
 
    

public:
	virtual ~CDrMbj3D();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrMbj3D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



