// Node.h : header file
//
#ifndef _DRNODE_H
#define _DRNODE_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h" 
#include "Str_Gen.h"           // card structures 
#include "Def_Type.h"
#include "Def_CuPS.h"			// enum CATEGORY			
#include "Str_Supp.h"	// Support data			
#include "Str_StaL.h"	// Static  data			
//////////////////// 
#define MAX_NODE_DRAW_PT	1
/////////////////////////////////////////////////////////////////////////////
// CDrNode    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrNode: public CDrObject
{
///////////////////////////////////////////////////
public:
// Construction                 
	CDrNode();
//////////////////////////////////////
	DECLARE_SERIAL(CDrNode);
//////////////////////////////////////
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual NODECARD*	Parse_drPipe(CString* pstrCard)
						{return (NODECARD*)NULL;};                    //  TOBE DONE
	virtual NODECARD*	GetNodeCard(){return &m_NodeCard;};
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	// for DECKVIEW
	virtual	void		DoFormattedCardView(CString* pstrCard,CString& strFmt){};
	virtual	void		DoUnFormattedCardView(CString* pstrCard){};
	///
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODE_DRAW_PT;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 		FinishObject();
	virtual BOOL 		IsObjectHit(double dNet,WORLD Pt);	// 
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	///////////////////////////////////////////////////////////////
	virtual	CATEGORY	GetCategory(){return m_Category;};
	virtual	void		SetCategory(CATEGORY CT){m_Category = CT;};
	virtual int			GetPrecision(){return m_nPrecision;};
	virtual void		SetPrecision(int nPreci){m_nPrecision = nPreci;};
//todo def inclusion:	
	CString		GetFormat(){return m_FmtStr;};
	void		SetFormat(CString FmtStr){m_FmtStr = FmtStr;};
	double		GetMapFactor(){return m_dMapFactor;};
	void		SetMapFactor(double dFac){m_dMapFactor = dFac;};
	double		GetScaleFactor(){return m_dScaleFactor;};
	void		SetScaleFactor(double dFac){m_dScaleFactor = dFac;};
	long		GetMasterMultFac(){return m_lmf;};   // MasterCard
	void		SetMasterMultFac(long lmf){m_lmf = lmf;};
    ////////////////////////////////////////////////////////////////////// Render
	virtual	pWORLD	 	GetLocalPos(){return &m_LocalPos;};
	virtual	void		SetLocalPos(WORLD Pos){m_LocalPos = Pos;};
	virtual	pWORLD	 	GetWorldPos(){return &m_WorldPos;};
	virtual	void		SetWorldPos(WORLD Pos){m_WorldPos = Pos;};
	virtual	pWORLD	 	GetEyePos(){return &m_EyePos;};
	virtual	void		SetEyePos(WORLD Pos){m_EyePos = Pos;};
	virtual	pWORLD	 	GetScreenPos3D(){return &m_ScreenPos;};
	virtual	void		SetScreenPos3D(WORLD Pos){m_ScreenPos = Pos;};
	virtual	POINT*	 	GetScreenPos2D(){return &m_pt;};
	virtual	void		SetScreenPos2D(POINT Pos){m_pt = Pos;};
	virtual	pWORLD	 	GetNormalWorld(){return &m_NormalWorld;};
	virtual	void		SetNormalWorld(WORLD Normal){m_NormalWorld = Normal;};
	virtual	pWORLD	 	GetNormalEye(){return &m_NormalEye;};
	virtual	void		SetNormalEye(WORLD Normal){m_NormalEye = Normal;};
	virtual	pWORLD	 	GetNormalScreen3D(){return &m_NormalScreen3D;};
	virtual	void		SetNormalScreen3D(WORLD Normal){m_NormalScreen3D = Normal;};
	virtual	POINT* 		GetNormalScreen2D(){return &m_NormalScreen2D;};
	virtual	void		SetNormalScreen2D(POINT Normal){m_NormalScreen2D = Normal;};
	
	long 		GetLabelNo(){return m_nLabelNo;}; 
	void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	////////////////////////////////////////////////////////////////////// Mesh/Control Node
	BOOL		IsMeshNode(){return m_bMeshNode;};
	void		SetMeshNode(BOOL bGen){m_bMeshNode = bGen;};
	BOOL		IsGenerated(){return m_bGenerated;};
	void		SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	BOOL		IsControlNode(){return GetNodeCard()->bnid_c;};
	void		SetControlNode(BOOL b){GetNodeCard()->bnid_c = b;};
	/////////////////////////////////////////////////////////////
	void 		Calc_NormalWorld();
	void 		Calc_NormalEye();
	void 		Calc_NormalScreen3D();
	void 		Calc_WorldPos(pMATRIX pLM,BOOL bYes);
	void 		Calc_EyePos(pMATRIX pViewM);
	void 		ProjectToScreenPos3D(pMATRIX pvv3DM);
	/////////////////////////////////////////////////////////////////////// Input Info
	BOOL		GetInputMode(){return m_bCoord;};
	void		SetInputMode(BOOL b){m_bCoord = b;};
	double		GetLength(){return m_dLength;};
	void		SetLength(double b){m_dLength = b;};
	pWORLD		GetDelta(){return &m_Delta;};	// coords wrt Ref
	void		SetDelta(WORLD b){m_Delta = b;};	// coords wrt Ref
	CString		GetFromID(){return m_FromID;};
	void		SetFromID(CString b){m_FromID = b;};
	CString		GetToID(){return m_ToID;};
	void		SetToID(CString b){m_ToID = b;};
			BOOL		IsRefCN(){return m_bRefCN;};
			void		SetRefCN(BOOL b){m_bRefCN = b;};
			BOOL		IsFromCN(){return m_bFromCN;};
			void		SetFromCN(BOOL b){m_bFromCN = b;};
			BOOL		IsToCN(){return m_bToCN;};
			void		SetToCN(BOOL b){m_bToCN = b;};
	////////////
	BOOL		IsSkewed(){return m_bSkewed;};							
	void		SetSkewed(BOOL bSkewed){m_bSkewed = bSkewed;};
	BOOL		IsLinSpr(){return m_bLinSpr;};							
	void		SetLinSpr(BOOL bLinSpr){m_bLinSpr = bLinSpr;};
	BOOL		IsLinSnu(){return m_bLinSnu;};							
	void		SetLinSnu(BOOL bLinSnu){m_bLinSnu = bLinSnu;};
	////////////
	CList<SUPPCARD,SUPPCARD>*	GetSuppCardList(){return	&m_SuppCardList;};
	CList<STALCARD,STALCARD>*	GetStaLCardList(){return	&m_StaLCardList;};


	
protected:
	
	
	void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
	void 		TransformToEyePos(pMATRIX pViewM);
	void 		ProjectToScreenPos
					(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	void 		Calc_ScreenRectFromCNodes();
	void 		GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes
 

	CList<SUPPCARD,SUPPCARD>		m_SuppCardList;	
	CList<STALCARD,STALCARD>		m_StaLCardList;	
	////////////////////////////// Joint Coordinates (Skewed)
	BOOL		m_bMeshNode;
	////////////////////////////// Render
	WORLD		m_LocalPos;
	WORLD		m_WorldPos;
	WORLD		m_EyePos;
	WORLD		m_ScreenPos;	//3D
    WORLD  		m_NormalWorld;
    WORLD  		m_NormalEye;
    WORLD  		m_NormalScreen3D;
    POINT  		m_NormalScreen2D;
	/////////////////////////////////////////////////////////////
	NODECARD	m_NodeCard;
	int			m_nCardNo;
	////////////////////////////// Input Info
	BOOL		m_bCoord;
	double		m_dLength;
	WORLD		m_Delta;	// coords wrt Ref
	CString		m_FromID;
	BOOL		m_bFromCN;
	BOOL		m_bRefCN;
	CString		m_ToID;
	BOOL		m_bToCN;
	//////////////////////////////
	int 		m_nPrecision;
	BOOL		m_bTransformed;
	double 		m_dMapFactor;
	double		m_dScaleFactor;
	long		m_lmf;           // from MASTER Card
	CString		m_FmtStr;
	/////////////////////////////////// 
	POINT 		m_pt;					// Screen Position 2D 
	//////////////////////////////    							

public:
	virtual ~CDrNode();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrNode)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



