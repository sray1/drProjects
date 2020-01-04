// FE3D.h : header file
//
#ifndef _DRFE3D_H
#define _DRFE3D_H       


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DListMgr.h"
#include "Def_Type.h"
//////////////////////////////
#include "Str_Mesh.h" 
#include "Def_Mesh.h" 
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

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual void		Parse_drPipe(CString* pstrCard){};
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
							double dScale_U,double dScale_V,double dShrink);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return m_nCorners;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual	void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual	BOOL 		CullScreen(pMATRIX pViewM);
	virtual	BOOL 		CullWorld(WORLD ViewDir);

	virtual	POINT*	 	GetCentroidScreen2D(){return &m_CentroidScreen2D;};
	virtual	void		SetCentroidScreen2D(POINT Centroid){m_CentroidScreen2D = Centroid;};
	virtual	pWORLD	 	GetCentroidScreen3D(){return &m_CentroidScreen3D;};
	virtual	void		SetCentroidScreen3D(WORLD Centroid){m_CentroidScreen3D = Centroid;};
	virtual	pWORLD	 	GetCentroidEye(){return &m_CentroidEye;};
	virtual	void		SetCentroidEye(WORLD Centroid){m_CentroidEye = Centroid;};
	virtual	pWORLD	 	GetCentroidWorld(){return &m_CentroidWorld;};
	virtual	void		SetCentroidWorld(WORLD Centroid){m_CentroidWorld = Centroid;};

	virtual	double	 	GetCentroidZdepth(){return m_Zdepth;};
	virtual	void		SetCentroidZdepth(double Zdepth){m_Zdepth = Zdepth;};

	virtual	pWORLD	 	GetNormalWorld(){return &m_NormalWorld;};
	virtual	void		SetNormalWorld(WORLD Normal){m_NormalWorld = Normal;};
	virtual	pWORLD	 	GetNormalEye(){return &m_NormalEye;};
	virtual	void		SetNormalEye(WORLD Normal){m_NormalEye = Normal;};
	virtual	pWORLD	 	GetNormalScreen3D(){return &m_NormalScreen3D;};
	virtual	void		SetNormalScreen3D(WORLD Centroid){m_NormalScreen3D = Centroid;};
	virtual	POINT*	 	GetNormalScreen2D(){return &m_NormalScreen2D;};
	virtual	void		SetNormalScreen2D(POINT Centroid){m_NormalScreen2D = Centroid;};
	virtual BOOL 		IsCulled(){return m_bCulled;};
	virtual void 		SetCulled(BOOL bCulled){m_bCulled = bCulled;};
    //////////////////////////////////////////////////////
	virtual void 		Calc_CentroidWorld();
	virtual void 		Calc_CentroidEye();
	virtual void 		Calc_CentroidScreen3D(double dScale_U,double dScale_V);
	virtual void 		Calc_NormalWorld();
	virtual void 		TransformNormalToEye(pMATRIX pView);
	virtual void 		ProjectNormalToScreen3D
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
 	////////////////////////////////////////////////////////////////////// Members
 	short				GetnNodes(){return m_nNodes;};		
	void				SetnNodes(short s){m_nNodes = s;};		
	///
	CString&			GetElNumID(){return m_ElNumID;};
 	void				SetElNumID(CString p){m_ElNumID = p;};
 	CString&			GetElTypeID(){return m_ElTypeID;};
 	void				SetElTypeID(CString p){m_ElTypeID = p;};
 	CString&			Getline_id(){return m_line_id;};
 	void				Setline_id(CString p){m_line_id = p;};
 	CString&			Getpid(){return m_pid;};
 	void				Setpid(CString p){m_pid = p;};
 	CString&			Getmid(){return m_mid;};
 	void				Setmid(CString p){m_mid = p;};
	//////////////////////////////////
	UINT				GetElNum(){return m_ElNum;};				
	void				SetElNum(UINT u){m_ElNum = u;};			
	UINT				GetElTypeNum(){return m_ElTypeNum;};	
	void				SetElTypeNum(UINT u){m_ElTypeNum = u;};	
	UINT				Getline_no(){return m_line_no;};		
	void				Setline_no(UINT u){m_line_no = u;};		
	UINT				Getprop(){return m_prop;};		
	void				Setprop(UINT u){m_prop = u;};		
	UINT				Getmat(){return m_mat;};		
	void				Setmat(UINT u){m_mat = u;};		
	UINT				Getnumseg(){return m_numseg;};		
	void				Setnumseg(UINT u){m_numseg = u;};
	//
	double				GetRefTemp(){return m_refTemp;};
	void				SetRefTemp(double r){m_refTemp = r;};
	//
	UINT				GetCardNo(){return m_nCardNo;};		
	void				SetCardNo(UINT u){m_nCardNo = u;};
   ////////////////////////////////////////////////////////////////////// helper
	virtual	POINT 		GetCenter(){return m_nCenter;};
	virtual	void		SetCenter(POINT ptCenter){m_nCenter = ptCenter;};
	//////////////////////////
//	CDListMgr*			GetFE0DList(){return &m_FE0DList;};
//	CDListMgr*			GetFE1DList(){return &m_FE2DList;};
//	CDListMgr*			GetFE3DList(){return &m_FE3DList;};
	////////////////////////////////////////////////////////////////// History
/*//082898
	UINT				GetGenObjType(){return m_GenObjType;};
	void				SetGenObjType(UINT bGen){m_GenObjType = bGen;};
	CDrObject*			GetGenObj(){return m_pGenObj;};
	void				SetGenObj(CDrObject* bGen){m_pGenObj = bGen;};
*///082898
	BOOL				IsOnBndry(){return m_bOnBndry;};
	void				SetOnBndry(BOOL b){m_bOnBndry = b;};
	int					GetBndryIndex_C(){return m_BndryIndex_C;};
	void				SetBndryIndex_C(int i){m_BndryIndex_C = i;};
	int					GetBndryIndex_F(){return m_BndryIndex_F;};
	void				SetBndryIndex_F(int i){m_BndryIndex_F = i;};
	////////////////////////////////////////////////////////
 	virtual CString&	Getrid(int i){return m_rid[i];};
 	virtual void		Setrid(CString p,int i){m_rid[i] = p;};
	virtual UINT		Getrel(int i){return m_rel[i];};				
	virtual void		Setrel(UINT u,int i){m_rel[i] = u;};			
	virtual short		GetnCorners(){return m_nCorners;};		// 3 = Triangle/ 4 = Quadrilateral
	virtual void		SetnCorners(short s){m_nCorners = s;};	// 3 = Triangle/ 4 = Quadrilateral
	virtual short		GetnEdges(){return m_nEdges;};			// Bounding Edges
	virtual void		SetnEdges(short s){m_nEdges = s;};		// Bounding Edges
	//////////////////////////////////////////////////////////////////////
	virtual ELEM_DEGREE	GetElDegree(){return m_ElDegree;};		
	virtual void		SetElDegree(ELEM_DEGREE u){m_ElDegree = u;};
	virtual short		GetEdgeDegrees(int i){return m_nEdgeDegree[i];};		
	virtual void		SetEdgeDegrees(short e,int i){m_nEdgeDegree[i] = e;};
	virtual double		GetThkness(){return m_Thkness;};		
	virtual void		SetThkness(double u){m_Thkness = u;};

	 
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
	/////////////////////////////////////////////////////////////////////
	// Note: 
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	short		m_nCorners;			// 3 = Triangle/ 4 = Quadrilateral
	short		m_nEdges;			// Bounding Edges
	short		m_nNodes;			// intermediate + corner Nodes = ALL
//	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc
	short		m_nFaces;			// Bounding Faces
	///////////////////////
	// for Isoparametric: may be different Edge Degree
	short		m_nEdgeDegree[MAX_EDGES_3D];	// 1 = Linear/ 2 = Quadratic etc
	ELEM_DEGREE	m_ElDegree;
	//////////////////////////////////
	CString		m_ElNumID;	
	CString		m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	CString		m_line_id;
	CString		m_rid[MAX_CORNERS_3D]; 
	CString		m_pid,m_mid;  
	//////////////////////////////////
	UINT		m_ElNum;				// Element Number
	UINT		m_ElTypeNum;			// id Number: Element Type
	UINT		m_line_no;
	UINT		m_rel[MAX_CORNERS_3D]; 
	UINT		m_prop,m_mat;           //
	UINT		m_numseg;				//
	/////////////////////////
	double		m_refTemp;				//RefrenceTemperature
	//////////////////////////////////
	double		m_Thkness;			// Thickness
	////////////////////////////// 
	int			m_nCardNo;
	POINT 		m_nCenter; 
	/////////////////////////////////// Data Structure
//	CDListMgr	m_FE0DList;	// All Vrtxs connected to this Cube 
//	CDListMgr	m_FE1DList;	// All Edges connected to this Cube 	
//	CDListMgr	m_FE2DList;	// All Faces connected to this Cube 
//	CDListMgr	m_FE3DList;	// All Cubes connected to this Cube
	/////////////////////// Genetics
//082898	UINT		m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//082898	CDrObject*	m_pGenObj;
	///////////////////////
	BOOL		m_bOnBndry;		// for 1D always TRUE
	int			m_BndryIndex_C;	// which Generating Curve of a Patch is sitting on (2D/3D)
	int			m_BndryIndex_F;	// which Generating Patch of a Solid is sitting on (3D)
	///////////////////////////////// Render 
    BOOL		m_bCulled;
    WORLD  		m_NormalWorld; 			// WorldPos
    WORLD  		m_NormalEye; 			// EyePos
    WORLD  		m_NormalScreen3D;		// Screen3D
    POINT  		m_NormalScreen2D;		// Screen2D
    WORLD		m_CentroidWorld;		// WorldPos
    WORLD		m_CentroidEye;			// EyePos
    WORLD  		m_CentroidScreen3D;		// Screen3D
    POINT  		m_CentroidScreen2D;		// Screen2D
    double		m_Zdepth;				// EyePos

public:
	virtual ~CDrFE3D();
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



