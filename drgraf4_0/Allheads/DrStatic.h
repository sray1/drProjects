// Linear Support.h : header file
//
#ifndef _DRSTATIC_H
#define _DRSTATIC_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h" 
#include "Str_StaL.h"           // card structures 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h" 
#include "DrLabel.h" 
//////////////////// 
// CDrStatic    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrStatic: public CDrObject
{
///////////////////////////////////////////////////
public:
// Construction                 
	CDrStatic();
//////////////////////////////////////
	DECLARE_SERIAL(CDrStatic);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual STALCARD*	Parse_drPipe(CString* pstrCard)
						{return (STALCARD*)NULL;};                    //  TOBE DONE
	int			GetCardNo(){return m_nCardNo;};
	void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
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
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual void		TransformObjectToViewDirect
							(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
    ////////////////////////////////////////////////////////////////////// 
	STALCARD*	GetStaLCard(){return &m_StaLCard;};
	void		SetStaLCard(STALCARD sC);
	CDListMgr*  GetNodeList(){return &m_NodeList;};
	CDListMgr*  GetCurveList(){return &m_CurveList;};
	CDListMgr*  GetPatchList(){return &m_PatchList;};
	CDListMgr*  GetSolidList(){return &m_SolidList;}; 
	
	CDrNode*	GetLabelNode(){return m_pLabelNode;};	// use when new Transformation
	void		SetLabelNode(CDrNode* ptr){m_pLabelNode = ptr;};
	CDrLabel*	GetLabelPtr(){return m_pLabel;};	// use when new Transformation
	void		SetLabelPtr(CDrLabel* ptr){m_pLabel = ptr;};
	long 		GetLabelNo(){return m_nLabelNo;}; 
	void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	/////////////////////////////////////////////////////////////
	pMATRIX		GetLocalM(){return &m_LocalM;}; 
	void		SetLocalM(pMATRIX pM){m_LocalM = *pM;};
	/////////////////////////////////////////////////////////////

	int			GetnPts(int i){return m_nPts[i];};
	pWORLD		GetpLoc(int i){return m_pLoc[i];};

	BOOL		IsSkewed(){return m_bSkewed;};							
	void		SetSkewed(BOOL bSkewed){m_bSkewed = bSkewed;};

	pMATRIX		GetSkewMat(){return &m_SkewMat;};
	void		SetSkewMat(pMATRIX s){m_SkewMat = *s;};
	////////////////////////////////////////////////////////////////// Quick Search
	UINT		GetCreateBase(){return m_CreateBase;};
	void		SetCreateBase(UINT n){m_CreateBase = n;};
	BOOL		IsTriangle(){return m_bTriangle;};							
	void		SetTriangle(BOOL bTriangle){m_bTriangle = bTriangle;};
	BOOL		IsPentaHed(){return m_bPentaHed;};							
	void		SetPentaHed(BOOL bTriangle){m_bPentaHed = bTriangle;};
	int			GetCreate_i(){return m_Create_i;};
	void		SetCreate_i(int n){m_Create_i = n;};
	int			GetCreate_j(){return m_Create_j;};
	void		SetCreate_j(int n){m_Create_j = n;};
	int			GetCreate_k(){return m_Create_k;};
	void		SetCreate_k(int n){m_Create_k = n;};
	pWORLD		GetNodPos(){return &m_NodPos;};
	void		SetNodPos(WORLD& n){m_NodPos = n;};
	//////////////////////////////////////////////////////
			void		InitRawData(STALPROC StalProc);

	 
protected:
	
	
			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
			void		TransformToEyePosDirect
							(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes);
			void 		TransformToEyePos(pMATRIX pViewM);
			void 		ProjectToScreenPos
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
			int			Calc_3DBoundsLocal(pWORLD pOut, int nPts);
			void 		Calc_ScreenRectFromCNodes();
			void		Rearrange2DCorners();
			void 		GoDoIt(CDC* PtrDC,int direction);
			void		GoConnect_TRANSLATION(CDC* PtrDC,int direction);// for,disp,pres
			void		GoConnect_ROTATION(CDC* PtrDC, int direction);	// mom,rotn
			void		GoConnect_THERMAL(CDC* PtrDC, int direction);
			void		GoConnect_LUMPWT(CDC* PtrDC, int direction);
			/////////////////////////////////////////////////////////////////////// Prepare
			void		GetApproPts(STALPROC StaLProc,WORLD pOut[],
												int nPts,int direction);
			int			GetApproDataLen(STALPROC StaLProc,int direction);

		
// Helper functions
protected:
// Attributes
 
	///////////////////////////////////////////////////////////////////// Quick Search
	UINT		m_CreateBase;		// NODE,CURVE,PATCH or SOLID
	BOOL		m_bTriangle;		// if CreateBase = PATCH, Is It Triangle;
									// if CreateBase = Solid, Is It TetraHed
	BOOL		m_bPentaHed;		// if CreateBase = Solid, Is It PentaHed;
	int			m_Create_i;		// index in the CreateBaseList or TriangleList, if bTriangle = TRUE
	int			m_Create_j;
	int			m_Create_k;
	WORLD		m_NodPos;		// Needed to avoid Duplicate in Triangle Situation
	////////////////////////////// Joint Coordinates (Skewed)
	BOOL		m_bSkewed;
	MATRIX		m_SkewMat;
	//////////////////////////////////////////////
	CDrNode*	m_pLabelNode;	// LabelNode
	CDrLabel*	m_pLabel;
	//////////////////////////
	MATRIX		m_LocalM;	// Local Transformation
	/////////////////////////// Bounding Corners
	BOOL		m_bDoneXform;
	BOOL		m_bDoneProject;
	///////////////////////////
	STALCARD	m_StaLCard;
	int			m_nCardNo;
	/////////////////////////// Current
	int			m_CurDir;
	int			m_nPts[6];
	pWORLD		m_pLoc[6];// stores Local  and then Translated to NodePos	
	pWORLD		m_pEye[6];// EyePos also stores WorPos
	/////////////////////////// Smart Paint
	WORLD		m_dMin;
	WORLD		m_dMax;

public:
	virtual ~CDrStatic();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrStatic)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



