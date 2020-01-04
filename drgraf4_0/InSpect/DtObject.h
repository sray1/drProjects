// Elem.h : header file
//
#ifndef _DROBJECT_H
#define _DROBJECT_H       
#pragma warning(disable:4100)	// unreferenced formal params

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "MatObj.h"
#include "DListMgr.h"
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_CuPS.h"
#include "Def_Objs.h"
#include "Def_Type.h"
#include "Def_Rend.h" 	// Render Attribs.
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_CORNER	2 // Max & Min Corners
// CDrObject///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrObject: public CObject
{
public:
// Construction                 
	CDrObject();

	DECLARE_SERIAL(CDrObject)




// Operations
public: 


	virtual	void 		ReadyToDelete(){};
	////////////////////////////////////////////////////////////////Begin DrObject OverRides
	// for DECKVIEW
	virtual	void		DoFormattedCardView(CString* pstrCard,CString& strFmt){};
	virtual	void		DoUnFormattedCardView(CString* pstrCard){};
	// for DATAVIEW
	virtual	void		DoDataView(CDC* PtrDC,int y){};
	// for VIEW12,VIEW23 etc.
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V){};
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,
							double dzMin,double dScale_U,double dScale_V,double dShrink){};
	virtual void 		Corner_3Dto2D(){};
	virtual	void		DoDrawView(CDC* PtrDC){};					
	virtual	void		DoDrawView(CDC* PtrDC,BOOL bPenChange){};					// node
	virtual	void		DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber){};	// label
	/////////////////////////////
	virtual BOOL		IsParallel(){return m_bParallel;};
    virtual int			GetnView(){return m_nView;};
    virtual double		GetdzMin(){return m_dzMin;};
	virtual double		GetdScale_U(){return m_dScale_U;};		// vv3DToLP:U-direction  
	virtual double		GetdScale_V(){return m_dScale_V;};		// vv3DToLP:V-direction
	virtual pMATRIX		GetpViewM(){return &m_ViewM;};		// viewers transform MATRIX
	virtual pMATRIX		Getpvv3DM(){return &m_vv3DM;};		// Window to 3D Viewport MATRIX
	virtual pMATRIX		GetpComposedM(){return &m_ComposedM;};		// Composite Local/View MATRIX
	virtual void		SetParallel(BOOL b){m_bParallel = b;};
    virtual void		SetnView(int b){m_nView = b;};
    virtual void		SetdzMin(double b){m_dzMin = b;};
	virtual void		SetdScale_U(double b){m_dScale_U = b;};		// vv3DToLP:U-direction  
	virtual void		SetdScale_V(double b){m_dScale_V = b;};		// vv3DToLP:V-direction
	virtual void		SetpViewM(pMATRIX b){m_ViewM = *b;};		// viewers transform MATRIX
	virtual void		Setpvv3DM(pMATRIX b){m_vv3DM = *b;};		// Window to 3D Viewport MATRIX
	virtual void		SetpComposedM(pMATRIX b){m_ComposedM = *b;};// Composite Local/View MATRIX
	///////////////////////////////////////////////////// 
	virtual int 		GetLevelType(){return m_nLevelType;};
	virtual void		SetLevelType(int nType){ m_nLevelType = nType;};
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual int			GetObjectType(){return m_nObjectType;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual	int 	DealObjectDialog(){return (int)NULL;}; 
	///////////////////////////////////////////////////////////////////////
	virtual void 	TransformObjectToWorld(pMATRIX pLM,BOOL bYes){};
	virtual void 	TransformObjectToView(pMATRIX pViewM){};
	virtual void	TransformObjectToViewDirect
						(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes){};
	virtual BOOL 	RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
						{return (BOOL)NULL;};
	virtual void 	ProjectObject
						(	pMATRIX pvv3DM,
							double dScale_U,double dScale_V
						){};
	virtual	int 	Calc_2DBoundsScreen(){return (int)NULL;};
	virtual	int 	Calc_3DBoundsLocal(){return (int)NULL;};
	virtual void	FinishObject(CClientDC* pDC,int nViewNumber){}; // label
	virtual void	FinishObject(int nViewNumber){}; 				// Freehand
	virtual void	FinishObject(){};                        		// node  
	virtual CRect	GetBoundingRect() { return m_rectBounding; };
	////////////////////////////////////////////////////////////////////////// Normal
	virtual void    GetPenInfo(UINT& nWidth,COLORREF& crColor,UINT& nStyle)
					{	nWidth  =	m_nPenWidth;
					 	crColor =	m_crPenColor;
						nStyle  =	m_nPenStyle;
				  	};	
	virtual void    SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidth  = nWidth;
						m_crPenColor = crColor;
					 	m_nPenStyle  = nStyle;
					};
	////////////////////////////////////////////////////////////////////////// HiLite
	virtual void    GetPenInfoHi(UINT& nWidth,COLORREF& crColor,UINT& nStyle)
					{	nWidth  =	m_nPenWidthHi;
					 	crColor =	m_crPenColorHi;
						nStyle  =	m_nPenStyleHi;
				  	};	
	virtual void    SetPenInfoHi(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidthHi  = nWidth;
						m_crPenColorHi = crColor;
					 	m_nPenStyleHi  = nStyle;
					};
	virtual UINT	GetLayer(){return m_nLayer;};
	virtual void	SetLayer(UINT nLayer){m_nLayer = nLayer;};
	///////////////////////////////////////////////////////////////////
	virtual int		GetMaxCorners(){return (int)NULL;};
	virtual	void 	GetRawCoords(long* lCoord, int* pnPrecision, int index){};
	virtual void	SetProjectedCoords(POINT pt, int index){};
	virtual void	RearrangeProjectedCoords(){};// put max/min in right place;					
	//////////////////////////////////////////////////////////////////
	virtual BOOL 	IsObjectHit(double dNet,WORLD Pt)	// 3D 
							{return FALSE;};
	virtual BOOL 	IsObjectHit(int nNet,POINT point,int startIndex)	// Curve/patch
							{return FALSE;};
	virtual BOOL 	IsObjectHit(int nNet,POINT point)					// all else
							{return FALSE;};
	virtual	BOOL 	IsObjectHit(CClientDC* ptrDC,int nNet,POINT point,
								CRect* pRect,int nViewNumber)			// label
							{return FALSE;};
	///////////////////////////						
	virtual BOOL 	IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
							{return FALSE;};
	virtual BOOL 	IsKeyMatch(CString KeyID,UINT KeyNo){return FALSE;};
	//////////////////////////////////////////////////////////////////////////////							
	virtual BOOL	IsClipped(){return m_bClipped;};// 
	virtual void	SetClipped(BOOL  bC){m_bClipped = bC;};     // 
	//////////////////////////////////////////////////////////////////////////////
	virtual BOOL	IsGenerated(){return m_bGenerated;};
	virtual void	SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	virtual BOOL	IsShow(){return m_bShow;};							
	virtual void	SetShow(BOOL bP){m_bShow = bP;};							
	////////////////////////////////////////////////////////////////// Spawned
	virtual	CString&	GetParentID(){return m_ParentID;};
	virtual	void		SetParentID(CString& id){m_ParentID = id;};
	virtual	UINT		GetParentType(){return m_ParentType;};
	virtual	void		SetParentType(UINT id){m_ParentType = id;};
	virtual BOOL		IsInstanced(){return m_bInstanced;};
	virtual void		SetInstanced(BOOL bi){m_bInstanced = bi;};
	virtual	CMatObj*	GetMatObj(){return m_pMatObj;};
	virtual	void 		SetMatObj(CMatObj* xF){m_pMatObj = xF;};
	virtual	int 		SetLocalTransform(pMATRIX xF);
	virtual	int 		CatLocalTransform(pMATRIX xF);
	virtual	int 		GetLocalTransform(pMATRIX xF);
	/////////////////////////////////////////////////////////////
	virtual BOOL	IsControlShapeNeeded(){return (BOOL)NULL;};							
	virtual void	SetControlShapeNeed(BOOL bCSN){};							
	virtual BOOL	IsNormalNeeded(){return (BOOL)NULL;};							
	virtual void	SetNormalNeed(BOOL bNN){};
	/////////////////////////////////////////////////////////////
	virtual BOOL	IsCulled(){return (BOOL)NULL;};							
	virtual void	SetCulled(BOOL bCull){};
	////////////////////////////////////////////////////////////// Support
	virtual BOOL	IsSkewed(){return (BOOL)NULL;};							
	virtual void	SetSkewed(BOOL bSkewed){};
	virtual BOOL	IsLinSpr(){return (BOOL)NULL;};							
	virtual void	SetLinSpr(BOOL bLinSpr){};
	virtual BOOL	IsLinSnu(){return (BOOL)NULL;};							
	virtual void	SetLinSnu(BOOL bLinSnu){};
	/////////////////////////////////////////////////////////////							
	virtual CDListMgr* 	GetSpeLList(){return	&m_SpeLList;};
	virtual CDListMgr* 	GetDynLList(){return	&m_DynLList;};
	virtual CDListMgr* 	GetStaLList(){return	&m_StaLList;};
	virtual CDListMgr* 	GetSuppList(){return	&m_SuppList;};
	virtual CDListMgr*  GetElemList(){return	&m_ElemList;};
	virtual CDListMgr*  GetCurveList(){return	&m_CurveList;};
	virtual CDListMgr*  GetCProfList(){return	&m_CProfList;};
	virtual CDListMgr*  GetPatchList(){return	&m_PatchList;};
	virtual CDListMgr*  GetSolidList(){return	&m_SolidList;}; 
	virtual CDListMgr* 	GetObj3DList(){return	&m_Obj3DList;};
    virtual	CDListMgr*	GetCNodeList(){return	&m_CNodeList;};
    virtual	CDListMgr*	GetINodeList(){return	&m_INodeList;};
    virtual	CDListMgr*	GetNodeList(){return	&m_NodeList;};
    virtual	CDListMgr*	GetLabelList(){return	&m_LabelList;};
	/////////////////////////////////////////////////////////// Mesh
    virtual	CDListMgr*	GetFE0DList(){return	&m_FE0DList;};
    virtual	CDListMgr*	GetFE1DList(){return	&m_FE1DList;};
    virtual	CDListMgr*	GetFE2DList(){return	&m_FE2DList;};
    virtual	CDListMgr*	GetFE3DList(){return	&m_FE3DList;};
    virtual	CDListMgr*	GetMBJ3DList(){return	&m_MBJ3DList;};
	virtual	CDListMgr*	GetMs0List(){return &m_Ms0List;};
	virtual	CDListMgr*	GetMs1List(){return &m_Ms1List;};
	virtual	CDListMgr*	GetMs2List(){return &m_Ms2List;};
	virtual	CDListMgr*	GetMs3List(){return &m_Ms3List;};
	virtual	CDListMgr*	GetMbjList(){return &m_MbjList;};
	///////////////////////////////////////////////////////////////////
	virtual BOOL 		CullWorld(WORLD VDir){return (BOOL)NULL;};
	virtual BOOL 		CullScreen(pMATRIX pViewM){return (BOOL)NULL;};
    ///
	virtual void 		Calc_CentroidWorld(){};
	virtual void 		Calc_CentroidEye(){};
	virtual void 		Calc_CentroidScreen3D(double dScale_U,double dScale_V){};
	virtual void 		Calc_NormalWorld(){};
	virtual void 		TransformNormalToEye(pMATRIX pView){};
	virtual void 		ProjectNormalToScreen3D
							(pMATRIX pvv3DM,double dScale_U,double dScale_V){};
	///
	virtual	pWORLD	 	GetNormalWorld(){return (pWORLD)NULL;};
	virtual	void		SetNormalWorld(WORLD Normal){};
	virtual	pWORLD	 	GetNormalEye(){return (pWORLD)NULL;};
	virtual	void		SetNormalEye(WORLD Normal){};
	virtual	pWORLD	 	GetNormalScreen3D(){return (pWORLD)NULL;};
	virtual	void		SetNormalScreen3D(WORLD Centroid){};
	virtual	POINT*	 	GetNormalScreen2D(){return (POINT*)NULL;};
	virtual	void		SetNormalScreen2D(POINT Centroid){};
	///////////////////////////////////////////////////////////
	virtual CDListMgr* 	GetObjectList(){return (CDListMgr*)NULL;};
	/////////////////////////////////////////////////////////////							
	////////////////////////////////////////// for projection 
	// for smart painting(InvalidateRect) we will find bounding Cnode Coords and store in
	// ConvexHull[MAX_NODES_CURVE] which wil be then supplied thro' GetRawCoords
	/////////////////////////////////////////////////////////////////////////////////////////
	virtual void 	GetLocalCorner(pWORLD pLocalPos, int index);
	virtual void 	SetLocalCorner(pWORLD pLocalPos, int index);
	virtual void 	GetWorldCorner(pWORLD pWorldPos, int index);
	virtual void 	SetWorldCorner(pWORLD pWorldPos, int index);
	virtual void 	GetEyeCorner(pWORLD pEyePos, int index);
	virtual void 	SetEyeCorner(pWORLD pEyePos, int index);
	virtual void 	GetScreen3DCorner(pWORLD pScreenPos, int index);
	virtual void 	SetScreen3DCorner(pWORLD pScreenPos, int index);
	virtual POINT	GetScreen2DCorner(int index)
					{ 
						return m_pt[index];
					};
	virtual void	SetScreen2DCorner(POINT pt, int index)
					{ 
						m_pt[index] = pt;
					};
	////////////////////////////////////////////////////////////////
	virtual SPAWNTYPE	GetSpawnType(){return m_SpawnType;};
	virtual void		SetSpawnType(SPAWNTYPE c){m_SpawnType = c;};
	virtual CATEGORY	GetCategory(){return m_Category;};
	virtual void		SetCategory(CATEGORY c){m_Category = c;};
	virtual SUBCAT		GetSubCat(){return m_SubCat;};
	virtual void		SetSubCat(SUBCAT c){m_SubCat = c;};
	virtual ELEMDIMLIM	GetElemDimLim(){return m_ElemDimLim;};
	virtual void		SetElemDimLim(ELEMDIMLIM c){m_ElemDimLim = c;};
	///////////////////////////////////////////////////////////////////
	virtual BOOL	IsDirty(){return !m_bPosted;};							
	virtual void	SetDirty(BOOL bDirty){m_bPosted	= !bDirty;};							
	virtual BOOL	IsMoved(){return m_bMoved;};// force New 
	virtual void	SetMoved(BOOL  bM){m_bMoved = bM;};     // XForm & Projection
	virtual BOOL	IsEdited(){return m_bEdited;};							
	virtual void	SetEdited(BOOL bP){m_bEdited = bP;};							
	virtual BOOL	IsPosted(){return m_bPosted;};							
	virtual void	SetPosted(BOOL bP){m_bPosted = bP;};							
	virtual BOOL	IsDeleted(){return m_bDeleted;};							
	virtual void	SetDeleted(BOOL bP){m_bDeleted = bP;};	
	////////////////////////////////////////////////////////////// Tobe or NotToBe
	virtual BOOL	IsToBeMoved(){return m_bToBeMoved;};
	virtual void	SetToBeMoved(BOOL  bMoved){};    
	virtual BOOL	IsToBeEdited(){return m_bToBeEdited;};							
	virtual void	SetToBeEdited(BOOL bP){};							
	virtual BOOL	IsToBePosted(){return m_bToBePosted;};							
	virtual void	SetToBePosted(BOOL bP){};							
	virtual BOOL	IsToBeUnPosted(){return m_bToBeUnPosted;};							
	virtual void	SetToBeUnPosted(BOOL bP){};							
	virtual BOOL	IsToBeDeleted(){return m_bToBeDeleted;};							
	virtual void	SetToBeDeleted(BOOL bP){};
	////////////////////////////////////////////////////////////// Card Output
	virtual BOOL	IsFormatted(){return m_bFormatted;};							
	virtual void	SetFormatted(BOOL bP){m_bFormatted = bP;};							



public:

	////////////////////////////////////////////////////////////// Helper: Write
													   /////////// DataView/Card	
	void 		AddStr(CString* pstrDestin,CString* pstrSource, int nCount);
	void 		sprintn(char* s, long n, long lBase,CString FmtStr);
	void 		AddNum(CString* pstrDestin,long lNumber,long lmf, long lBase,
													CString FmtStr);//dreamPipe                                        //drPipe
	void 		AddInt(CString* pstrDestin,int nNum);
	void		AddDouble(CString* pstrDestin,double d);
	///////////////////////////////////////////////////////////
	void 		Transform(pWORLD pptIn, pWORLD pptOut);
	void 		Project(pWORLD pptIn, pWORLD pptOut,BOOL bSize);
	void 		DrawLine3D
				(
					CDC* pDC,pWORLD A, pWORLD B, BOOL Xformed
				); 
	void 		DrawLine3D
				(
					CDC* pDC,
					double x1,double y1,double z1,
					double x2,double y2,double z2,
					BOOL Xformed
				);
	void 		DrawPoint3D(CDC* pDC,pWORLD Pt3D,COLORREF C); 
	void 		DrawPoint3D(CDC* pDC,double x1,double y1,double z1,COLORREF C); 
				 


protected:

// Attributes 

	BOOL		m_bFormatted;			// Card Output
	/////////////////////////////////////////////////
	//////////////////////////////////////////////////////////
	BOOL		m_bStepXform;	// if true:	Local->World->View
								// if False:Local->View		
	/////////////////////////////
	BOOL		m_bClipped; 
	/////////////////////////////
	COLORREF	m_Color;
	//////////////////////
	BOOL		m_bParallel;
    int			m_nView;
    double		m_dzMin;
	double		m_dScale_U;		// vv3DToLP:U-direction  
	double		m_dScale_V;		// vv3DToLP:V-direction
	MATRIX		m_ViewM;		// viewers transform MATRIX
	MATRIX		m_ComposedM;	// Local/View Composite MATRIX
	MATRIX		m_vv3DM;		// Window to 3D Viewport MATRIX
	/////////////////////////////////////////////////////////// 
	int			m_nLevelType;
	int			m_nObjectType;
	long		m_nObjectNo;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	long		m_nLabelNo;
	//////////////////////////////
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
    ////////////////////////////// Normal
	UINT        m_nPenWidth;    // pen width for Pipe
	COLORREF	m_crPenColor;
	UINT		m_nPenStyle;
    ////////////////////////////// HiLite
	UINT        m_nPenWidthHi;    // pen width for Pipe
	COLORREF	m_crPenColorHi;
	UINT		m_nPenStyleHi;
	////////////////////////////// 
	UINT		m_nLayer;
	///////////////////////////////////
	int			m_nLevel;				// Hierarchy Level
	///////////////////////////////////
	BOOL		m_bGenerated;			// generated by Curve or Patch
	BOOL		m_bMoved;							
	BOOL		m_bEdited;							
	BOOL		m_bDeleted;							
	BOOL		m_bPosted;							
	BOOL		m_bDirty;							
	BOOL		m_bShow;							
    //////////////////////////////////////////////////////////////////////////////// 
    WORLD		m_ptMinMaxL[MAX_NODES_CORNER];	// Local Bounding Coords mixed as Min & Max 
    WORLD		m_ptMinMaxW[MAX_NODES_CORNER];	// World Bounding Coords mixed as Min & Max 
    WORLD		m_ptMinMaxE[MAX_NODES_CORNER];	// Eye Bounding Coords mixed as Min & Max 
    WORLD		m_ptMinMaxS[MAX_NODES_CORNER];	// Screen3D Bounding Coords mixed as Min & Max 
 	POINT 		m_pt[MAX_NODES_CORNER];			// SCREEN Coords.of Corners of 3DBoundVolume
	/////////////////////////////////
	CDListMgr	m_LabelList;       // DrLabel Pointers        "      "    "
	CDListMgr	m_CurveList;       // DrCurve Pointers        "      "    "
	CDListMgr	m_NodeList;        // DrNodes Pointers   "      "    "
	CDListMgr	m_INodeList;       // Input   Nodes Pointers  needed for delete
	CDListMgr	m_CNodeList;       // Control Nodes Pointers  needed for delete: Bezier	  Control Net	
	////////////////////////////// 
	BOOL		m_bToBeEdited;
	BOOL		m_bToBeDeleted;
	BOOL		m_bToBeUnDeleted;
	BOOL		m_bToBePosted;
	BOOL		m_bToBeUnPosted;
	BOOL		m_bToBeMoved;
	///////////////////////////////////////////////////////////////////////////


public:
	virtual ~CDrObject();
	void 	Serialize(CArchive& ar);
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrObject)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};


//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif


