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
	/////////////////////////////
	CRect		GetBoundingRect() { return m_rectBounding; };
	/////
	pRENDINFO	GetRInfo(){return &m_RInfo;};
	void 		SetRInfo(pRENDINFO pRA);
	BOOL		IsParallel(){return m_bParallel;};
    int			GetnView(){return m_nView;};
    double		GetdzMin(){return m_dzMin;};
	double		GetdScale_U(){return m_dScale_U;};		// vv3DToLP:U-direction  
	double		GetdScale_V(){return m_dScale_V;};		// vv3DToLP:V-direction
	pMATRIX		GetpViewM(){return &m_ViewM;};		// viewers transform MATRIX
	pMATRIX		Getpvv3DM(){return &m_vv3DM;};		// Window to 3D Viewport MATRIX
	pMATRIX		GetpComposedM(){return &m_ComposedM;};		// Composite Local/View MATRIX
	void		SetParallel(BOOL b){m_bParallel = b;};
    void		SetnView(int b){m_nView = b;};
    void		SetdzMin(double b){m_dzMin = b;};
	void		SetdScale_U(double b){m_dScale_U = b;};		// vv3DToLP:U-direction  
	void		SetdScale_V(double b){m_dScale_V = b;};		// vv3DToLP:V-direction
	void		SetpViewM(pMATRIX b){m_ViewM = *b;};		// viewers transform MATRIX
	void		Setpvv3DM(pMATRIX b){m_vv3DM = *b;};		// Window to 3D Viewport MATRIX
	void		SetpComposedM(pMATRIX b){m_ComposedM = *b;};// Composite Local/View MATRIX
	///////////////////////////////////////////////////// 
	int 		GetLevelType(){return m_nLevelType;};
	void		SetLevelType(int nType){ m_nLevelType = nType;};
	CString		GetObjectID(){return m_ObjectID;}; 
	void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	long 		GetObjectNo(){return m_nObjectNo;}; 
	void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	int			GetObjectType(){return m_nObjectType;};
	void		SetObjectType(int nType){ m_nObjectType = nType;};
	int 		GetElemType(){return m_nElemType;};
	void		SetElemType(int nType){ m_nElemType = nType;};
	void		SetObjectInfo(CDrObject* pObject);
	void 		GetObjectInfo(CDrObject* pObject);
	////////////////////////////////////////////////////////////////////////// Normal
	void    GetPenInfo(UINT& nWidth,COLORREF& crColor,UINT& nStyle)
					{	nWidth  =	m_nPenWidth;
					 	crColor =	m_crPenColor;
						nStyle  =	m_nPenStyle;
				  	};	
	void    SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidth  = nWidth;
						m_crPenColor = crColor;
					 	m_nPenStyle  = nStyle;
					};
	////////////////////////////////////////////////////////////////////////// HiLite
	void    GetPenInfoHi(UINT& nWidth,COLORREF& crColor,UINT& nStyle)
					{	nWidth  =	m_nPenWidthHi;
					 	crColor =	m_crPenColorHi;
						nStyle  =	m_nPenStyleHi;
				  	};	
	void    SetPenInfoHi(UINT nWidth,COLORREF crColor,UINT nStyle)
					{	m_nPenWidthHi  = nWidth;
						m_crPenColorHi = crColor;
					 	m_nPenStyleHi  = nStyle;
					};
	UINT	GetLayer(){return m_nLayer;};
	void	SetLayer(UINT nLayer){m_nLayer = nLayer;};
	//////////////////////////////////////////////////////////////////////////////							
	BOOL	IsClipped(){return m_bClipped;};// 
	void	SetClipped(BOOL  bC){m_bClipped = bC;};     // 
	//////////////////////////////////////////////////////////////////////////////
	BOOL	IsVirtual(){return m_bVirtual;};
	void	SetVirtual(BOOL bGen){m_bVirtual = bGen;};
	BOOL	IsShow(){return m_bShow;};							
	void	SetShow(BOOL bP){m_bShow = bP;};							
	////////////////////////////////////////////////////////////////// Spawned
	CString&	GetParentID(){return m_ParentID;};
	void		SetParentID(CString& id){m_ParentID = id;};
	UINT		GetParentType(){return m_ParentType;};
	void		SetParentType(UINT id){m_ParentType = id;};
	BOOL		IsInstanced(){return m_bInstanced;};
	void		SetInstanced(BOOL bi){m_bInstanced = bi;};
	CMatObj*	GetMatObj(){return m_pMatObj;};
	void 		SetMatObj(CMatObj* xF){m_pMatObj = xF;};
	int 		SetLocalTransform(pMATRIX xF);
	int 		CatLocalTransform(pMATRIX xF);
	int 		GetLocalTransform(pMATRIX xF);
	/////////////////////////////////////////////////////////////							
	CDListMgr* 	GetSpeLList(){return	&m_SpeLList;};
	CDListMgr* 	GetDynLList(){return	&m_DynLList;};
	CDListMgr* 	GetStaLList(){return	&m_StaLList;};
	CDListMgr* 	GetSuppList(){return	&m_SuppList;};
	CDListMgr*  GetElemList(){return	&m_ElemList;};
	CDListMgr*  GetCurveList(){return	&m_CurveList;};
	CDListMgr*  GetCProfList(){return	&m_CProfList;};
	CDListMgr*  GetPatchList(){return	&m_PatchList;};
	CDListMgr*  GetSolidList(){return	&m_SolidList;}; 
	CDListMgr* 	GetObj3DList(){return	&m_Obj3DList;};
    CDListMgr*	GetCNodeList(){return	&m_CNodeList;};
    CDListMgr*	GetINodeList(){return	&m_INodeList;};
    CDListMgr*	GetNodeList(){return	&m_NodeList;};
    CDListMgr*	GetLabelList(){return	&m_LabelList;};
	/////////////////////////////////////////////////////////// Mesh
    CDListMgr*	GetFE0DList(){return	&m_FE0DList;};
    CDListMgr*	GetFE1DList(){return	&m_FE1DList;};
    CDListMgr*	GetFE2DList(){return	&m_FE2DList;};
    CDListMgr*	GetFE3DList(){return	&m_FE3DList;};
	CDListMgr*	GetMs0List(){return &m_Ms0List;};
	CDListMgr*	GetMs1List(){return &m_Ms1List;};
	CDListMgr*	GetMs2List(){return &m_Ms2List;};
	CDListMgr*	GetMs3List(){return &m_Ms3List;};
    CDListMgr*	GetMbj3DList(){return	&m_Mbj3DList;};
	CDListMgr*	GetM2DProfList(){return &m_M2DProfList;};
	CDListMgr*	GetM3DProfList(){return &m_M3DProfList;};
	CDListMgr*	GetMbjProfList(){return &m_M3DProfList;};
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
	SPAWNTYPE	GetSpawnType(){return m_SpawnType;};
	void		SetSpawnType(SPAWNTYPE c){m_SpawnType = c;};
	CATEGORY	GetCategory(){return m_Category;};
	void		SetCategory(CATEGORY c){m_Category = c;};
	SUBCAT		GetSubCat(){return m_SubCat;};
	void		SetSubCat(SUBCAT c){m_SubCat = c;};
	ELEMDIMLIM	GetElemDimLim(){return m_ElemDimLim;};
	void		SetElemDimLim(ELEMDIMLIM c){m_ElemDimLim = c;};
	///////////////////////////////////////////////////////////////////
	BOOL	IsDirty(){return !m_bPosted;};							
	void	SetDirty(BOOL bDirty){m_bPosted	= !bDirty;};							
	BOOL	IsMoved(){return m_bMoved;};// force New 
	void	SetMoved(BOOL  bM){m_bMoved = bM;};     // XForm & Projection
	BOOL	IsEdited(){return m_bEdited;};							
	void	SetEdited(BOOL bP){m_bEdited = bP;};							
	BOOL	IsPosted(){return m_bPosted;};							
	void	SetPosted(BOOL bP){m_bPosted = bP;};							
	BOOL	IsDeleted(){return m_bDeleted;};							
	void	SetDeleted(BOOL bP){m_bDeleted = bP;};	
	////////////////////////////////////////////////////////////// Tobe or NotToBe
	BOOL	IsToBeMoved(){return m_bToBeMoved;};
	void	SetToBeMoved(BOOL  bMoved){};    
	BOOL	IsToBeEdited(){return m_bToBeEdited;};							
	void	SetToBeEdited(BOOL bP){};							
	BOOL	IsToBePosted(){return m_bToBePosted;};							
	void	SetToBePosted(BOOL bP){};							
	BOOL	IsToBeUnPosted(){return m_bToBeUnPosted;};							
	void	SetToBeUnPosted(BOOL bP){};							
	BOOL	IsToBeDeleted(){return m_bToBeDeleted;};							
	void	SetToBeDeleted(BOOL bP){};
	////////////////////////////////////////////////////////////// Card Output
	BOOL	IsFormatted(){return m_bFormatted;};							
	void	SetFormatted(BOOL bP){m_bFormatted = bP;};							



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

	BOOL		m_bVirtual;				// Virtual for Construction Help, Not yet posted
										// cannot be Moved or edited, just for display
										// and use
	BOOL		m_bFormatted;			// Card Output
	/////////////////////////////////////////////////
	CString		m_ParentID;				// If Spawned
	UINT		m_ParentType;
//	MATRIX		m_instanceXf;
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;
    /////////////////////////////////
	SPAWNTYPE	m_SpawnType;
	SUBCAT		m_SubCat;
	CATEGORY	m_Category;
	ELEMDIMLIM	m_ElemDimLim;
	//////////////////////////////////////////////////////////
	BOOL		m_bStepXform;	// if true:	Local->World->View
								// if False:Local->View		
	/////////////////////////////
	RENDINFO	m_RInfo;
	BOOL		m_bClipped; 
	/////////////////////////////
	COLORREF	m_Color;
	double		m_dShrink;
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
	int			m_nElemType;	
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
	/////////////////////////////////////////////////////////////////////////
	CDListMgr	m_LabelList;       // DrLabel Pointers        "      "    "
	CDListMgr	m_Obj3DList;       // DrObject Pointers        "      "    "
	CDListMgr	m_SolidList;       // DrSolid Pointers        "      "    "
	CDListMgr	m_PatchList;       // DrObject Pointers        "      "    "
	CDListMgr	m_CurveList;       // DrCurve Pointers        "      "    "
	CDListMgr	m_CProfList;       // DrCurve Pointers        "      "    "
	CDListMgr	m_NodeList;        // DrNodes Pointers   "      "    "
	CDListMgr	m_INodeList;       // Input   Nodes Pointers  needed for delete
	CDListMgr	m_CNodeList;       // Control Nodes Pointers  needed for delete: Bezier	  Control Net	
	CDListMgr	m_ElemList;		   // DrElem Pointers        "      "    "
	CDListMgr	m_SuppList;        // DrSupport Pointers   "      "    "
	CDListMgr	m_StaLList;        // DrStatic Loads Pointers   "      "    "
	CDListMgr	m_DynLList;        // DrDynamic Loads Pointers   "      "    "
	CDListMgr	m_SpeLList;        // DrSpectral Loads Pointers   "      "    "
	/////////////////////////////////////////////////////////////////////////// Mesh
	CDListMgr	m_FE0DList;			// Vertex or Mesh Node  Pointers  generated by Curve,Patch, Solid	
	CDListMgr	m_FE1DList;			// Mesh FE1D Pointers  generated by Curve, Patch, Solid	
	CDListMgr	m_FE2DList;			// Mesh FE2D Pointers  generated by Patch, Solid	
	CDListMgr	m_FE3DList;			// Mesh FE3D Pointers  generated by Solid	
	CDListMgr	m_Mbj3DList;		// Mesh FE3D Pointers  generated by Solid	
	CDListMgr	m_Ms0List;
	CDListMgr	m_Ms1List;
	CDListMgr	m_Ms2List;
	CDListMgr	m_Ms3List;
	CDListMgr	m_M2DProfList;
	CDListMgr	m_M3DProfList;
	CDListMgr	m_MbjProfList;
	///////////////////////////////////////////////////////////////////////////
	BOOL		m_bLinSpr;
	BOOL		m_bLinSnu;
	BOOL		m_bSkewed;
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


