// Force & Moment.h : header file
//
#ifndef _DRF_M_H
#define _DRF_M_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h" 
#include "Str_StaL.h" 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h" 
#include "DrLabel.h" 
//////////////////// 
// CDrF_M    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrF_M: public CDrObject
{
///////////////////////////////////////////////////
public:
// Construction                 
	CDrF_M();
//////////////////////////////////////
	DECLARE_SERIAL(CDrF_M);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual STALCARD*	Parse_drPipe(CString* pstrCard)
						{return (STALCARD*)NULL;};                    //  TOBE DONE
	virtual STALCARD*	GetStaLCard(){return &m_StaLCard;};
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
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
	virtual CDListMgr*  GetNodeList(){return &m_NodeList;};
	virtual CDListMgr*  GetCurveList(){return &m_CurveList;};
	virtual CDListMgr*  GetPatchList(){return &m_PatchList;};
	virtual CDListMgr*  GetSolidList(){return &m_SolidList;}; 
	
	virtual	CDrNode*	GetLabelNode(){return m_pLabelNode;};	// use when new Transformation
	virtual void		SetLabelNode(CDrNode* ptr){m_pLabelNode = ptr;};
	virtual	CDrLabel*	GetLabelPtr(){return m_pLabel;};	// use when new Transformation
	virtual void		SetLabelPtr(CDrLabel* ptr){m_pLabel = ptr;};
	virtual long 		GetLabelNo(){return m_nLabelNo;}; 
	virtual void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	/////////////////////////////////////////////////////////////
	virtual pMATRIX		GetLocalM(){return &m_LocalM;}; 
	virtual void		SetLocalM(pMATRIX pM){m_LocalM = *pM;};

	/////////////////////////////////////////////////////////////
	virtual COLORREF	GetColor(){return m_Color;}; 
	virtual void		SetColor(COLORREF f){ m_Color = f;};

	virtual int			GetnPts(int i){return m_nPts[i];};
	virtual pWORLD		GetpLoc(int i){return m_pLoc[i];};

	virtual BOOL		IsIsoPar(){return m_bIsoPar;};							
	virtual void		SetIsoPar(BOOL bSkewed){m_bIsoPar = bSkewed;};

	virtual BOOL		IsSkewed(){return m_bSkewed;};							
	virtual void		SetSkewed(BOOL bSkewed){m_bSkewed = bSkewed;};

	virtual pMATRIX		GetSkewMat(){return &m_SkewMat;};
	virtual void		SetSkewMat(pMATRIX s){m_SkewMat = *s;};
	//////////////////////////////////////////////////////
			void		InitRawData();

	 
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
			void		GoConnect_Force(CDC* PtrDC);
			void		GoConnect_Moment(CDC* PtrDC);
			/////////////////////////////////////////////////////////////////////// Prepare
			void		GetApproPts(WORLD pOut[],
									int nPts,int direction);
			int			GetApproDataLen(int direction);

		
// Helper functions
protected:
// Attributes
 

	////////////////////////////////////////////// IsoParametric Situation
	BOOL		m_bIsoPar;
	//////////////////////////////////////////////
	CDrNode*	m_pLabelNode;	// LabelNode
	CDrLabel*	m_pLabel;
	//////////////////////////
	MATRIX		m_LocalM;	// Local Transformation
	////////////////////////////////////////////// Skew: for Follower force etc
	BOOL		m_bSkewed;
	MATRIX		m_SkewMat;
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
	virtual ~CDrF_M();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrF_M)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



