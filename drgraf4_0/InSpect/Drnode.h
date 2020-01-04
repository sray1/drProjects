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
	virtual CString		GetFormat(){return m_FmtStr;};
	virtual void		SetFormat(CString FmtStr){m_FmtStr = FmtStr;};
	virtual double		GetMapFactor(){return m_dMapFactor;};
	virtual void		SetMapFactor(double dFac){m_dMapFactor = dFac;};
	virtual double		GetScaleFactor(){return m_dScaleFactor;};
	virtual void		SetScaleFactor(double dFac){m_dScaleFactor = dFac;};
	virtual long		GetMasterMultFac(){return m_lmf;};   // MasterCard
	virtual void		SetMasterMultFac(long lmf){m_lmf = lmf;};
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
	
	virtual long 		GetLabelNo(){return m_nLabelNo;}; 
	virtual void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	////////////////////////////////////////////////////////////////////// Mesh/Control Node
	virtual BOOL		IsMeshNode(){return m_bMeshNode;};
	virtual void		SetMeshNode(BOOL bGen){m_bMeshNode = bGen;};
	virtual BOOL		IsGenerated(){return m_bGenerated;};
	virtual void		SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	virtual BOOL		IsControlNode(){return GetNodeCard()->bnid_c;};
	/////////////////////////////////////////////////////////////
	virtual void 		Calc_NormalWorld();
	virtual void 		Calc_NormalEye();
	virtual void 		Calc_NormalScreen3D();
	virtual void 		Calc_WorldPos(pMATRIX pLM,BOOL bYes);
	virtual void 		Calc_EyePos(pMATRIX pViewM);
	virtual void 		ProjectToScreenPos3D(pMATRIX pvv3DM);
	/////////////////////////////////////////////////////////////////////// Input Info
	virtual BOOL		GetInputMode(){return m_bCoord;};
	virtual void		SetInputMode(BOOL b){m_bCoord = b;};
	virtual double		GetLength(){return m_dLength;};
	virtual void		SetLength(double b){m_dLength = b;};
	virtual pWORLD		GetDelta(){return &m_Delta;};	// coords wrt Ref
	virtual void		SetDelta(WORLD b){m_Delta = b;};	// coords wrt Ref
	virtual CString		GetFromID(){return m_FromID;};
	virtual void		SetFromID(CString b){m_FromID = b;};
	virtual CString		GetToID(){return m_ToID;};
	virtual void		SetToID(CString b){m_ToID = b;};
	////////////
	virtual BOOL		IsSkewed(){return m_bSkewed;};							
	virtual void		SetSkewed(BOOL bSkewed){m_bSkewed = bSkewed;};
	virtual BOOL		IsLinSpr(){return m_bLinSpr;};							
	virtual void		SetLinSpr(BOOL bLinSpr){m_bLinSpr = bLinSpr;};
	virtual BOOL		IsLinSnu(){return m_bLinSnu;};							
	virtual void		SetLinSnu(BOOL bLinSnu){m_bLinSnu = bLinSnu;};



	
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
	CString		m_ToID;
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



