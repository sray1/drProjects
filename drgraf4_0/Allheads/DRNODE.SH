// Node.h : header file
//
#ifndef _DRNODE_H
#define _DRNODE_H       

#include "DrObject.h"
#include "DListMgr.h" 
#include "crextern.h"           // card structures
//////////////////// 
#define MAX_NODE_DRAW_PT	1
/////////////////////////////////////////////////////////////////////////////
// CDrNode    ///////////////////////////////////////////////////////////////
class CDrNode: public CDrObject
{
///////////////////////////////////////////////////
public:
// Construction                 
	CDrNode();
	DECLARE_SERIAL(CDrNode);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual NODECARD*	Parse_drPipe(CString* pstrCard)
						{return (NODECARD*)NULL;};                    //  TOBE DONE
	virtual NODECARD*	GetNodeCard(){return &m_NodeCard;};
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual int 		GetLevelType(){return m_nLevelType;};
	virtual void		SetLevelType(int nType){ m_nLevelType = nType;};
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODE_DRAW_PT;};
/*
	virtual	void 		GetRawCoords(long* lCoord, int* pnPrecision, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt = pt;
						};
*/						
    ///////////////////////////////////
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual void 		FinishObject();
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	///////////////////////////////////////////////////////////////
	virtual void        GetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	nWidth  =	m_nPenWidth;
					 	 	crColor =	m_crPenColor;
					  		nStyle  =	m_nPenStyle;
				  		};	
	virtual void        SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	m_nPenWidth  = nWidth;
					 		m_crPenColor = crColor;
					 		m_nPenStyle  = nStyle;
						};
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
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
	virtual CDListMgr*  GetElemList(){return &m_ElemList;};
	virtual long 		GetLabelNo(){return m_nLabelNo;}; 
	virtual void		SetLabelNo(long nNo){ m_nLabelNo = nNo;};
	////////////////////////////////////////////////////////////////////// Control Node
	virtual BOOL		IsGenerated(){return m_bGenerated;};
	virtual void		SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	virtual BOOL		IsControlNode(){return GetNodeCard()->bnid_c;};
	/////////////////////////////////////////////////////////////
	virtual int			GetLevel(){return m_nLevel;};
	virtual void		SetLevel(int nLevel){m_nLevel = nLevel;};
	/////////////////////////////////////////////////////////////
	virtual void 		Calc_NormalWorld();
	virtual void 		Calc_NormalEye();
	virtual void 		Calc_NormalScreen3D();
	virtual void 		Calc_WorldPos(pMATRIX pLM,BOOL bYes);
	virtual void 		Calc_EyePos(pMATRIX pViewM);
	virtual void 		ProjectToScreenPos3D(pMATRIX pvv3DM);

	 
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
 
	int			m_nLevelType;
	int			m_nObjectType;
	int			m_nElemType;	
	long		m_nObjectNo;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	long		m_nLabelNo;
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
	//////////////////////////////
	int 		m_nPrecision;
	BOOL		m_bTransformed;
	double 		m_dMapFactor;
	double		m_dScaleFactor;
	long		m_lmf;           // from MASTER Card
	CString		m_FmtStr;
	//////////////////////////////
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
    //////////////////////////////
	UINT        m_nPenWidth;    // pen width for Pipe
	COLORREF	m_crPenColor;
	UINT		m_nPenStyle;
	////////////////////////////// 
	UINT		m_nLayer;
	/////////////////////////////////// 
	POINT 		m_pt;					// Screen Position 2D 
	BOOL		m_bGenerated;			// generated by Curve or Patch
	///////////////////////////////////
	int			m_nLevel;				// Hierarchy Level
	/////////////////////
    CDListMgr   m_ElemList;		// list of pointers to DrObjects
    							// attached to this Node

public:
	virtual ~CDrNode(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrNode)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



