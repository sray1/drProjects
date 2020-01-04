// FE3D.h : header file
//
#ifndef _DRFE3D_H
#define _DRFE3D_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
#include "DrNode.h" 
#include "crextern.h"           // card structures
//////////////////////////////
#define	MAX_NODES_FE3D		21
#define MAX_FE3D_DRAW_PT	8
#define MAX_FE3D_DRAW_PT2	8
/////////////////////////////////////////////////////////////////////////////
// CDrFE3D    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFE3D: public CDrObject
{
public:
// Construction                 
	CDrFE3D();
//////////////////////////////////////
	DECLARE_SERIAL(CDrFE3D);
//////////////////////////////////////
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual FE3DCARD*	Parse_drPipe(CString* pstrCard)
						{return (FE3DCARD*)NULL;};                    //  TOBE DONE
	virtual FE3DCARD*	GetSolCard(){return &m_Fe3DCard;};
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return m_SolCard.nCorners;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual	void 		FinishObject();
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual	BOOL 		CullScreen(pMATRIX pViewM);
	virtual	BOOL 		CullWorld(WORLD ViewDir);

	virtual BOOL 		IsCulled(){return m_bCulled;};
	virtual void 		SetCulled(BOOL bCulled){m_bCulled = bCulled;};
	virtual CDListMgr*	GetPolyList(){return &m_PolyList;};
	//////////////////////////////////////////////
	virtual	int		 	GetSolidType(){return m_SolCard.nSolidType;};
	virtual	void		SetSolidType(int nSolidType)
						{
							m_SolCard.nSolidType = nSolidType;};
    //////////////////////////////////////////////////////
	virtual void 		Calc_CentroidWorld();
	virtual void 		Calc_CentroidEye();
	virtual void 		Calc_CentroidScreen3D(double dScale_U,double dScale_V);
	virtual void 		Calc_NormalWorld();
	virtual void 		TransformNormalToEye(pMATRIX pView);
	virtual void 		ProjectNormalToScreen3D
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);

	 
protected:
	
			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
			void 		TransformToEyePos(pMATRIX pViewM);
			void 		ProjectToScreenPos
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
			void 		Calc_ScreenRectFromCNodes();
			void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes

	///////////////////////////////// Render 
    BOOL		m_bCulled;
	//////////////////////////////
	CDListMgr	m_PolyList;
	/////////////////////////////////
	FE3DCARD	m_Fe3DCard;
	int			m_nCardNo;


public:
	virtual ~CDrFE3D(){};
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



