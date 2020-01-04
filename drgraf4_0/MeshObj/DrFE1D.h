// Pipe.h : header file
//
#ifndef _DRFE1D_H
#define _DRFE1D_H       

#include "DrObject.h"
#include "DListMgr.h"
#include "Def_Type.h"
//////////////////////////////
#include "Str_Mesh.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrFE1D    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFE1D: public CDrObject
{
public:
// Construction                 
	CDrFE1D();
	DECLARE_SERIAL(CDrFE1D);
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual void		Parse_drPipe(CString* pstrCard){};                    //  TOBE DONE
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
	virtual int			GetMaxCorners(){return (int)MAX_CORNERS_1D;};
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual	int 		Calc_3DBoundsLocal();
	virtual	void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);
	////////////////////////////////////////////////////////////////////////// memory																							
	virtual 	pWORLD			GetMemIn(){return m_pIn;};
	virtual 	pDOUBLE			GetMemInWts(){return m_pInWts;};
	virtual 	POINT*			GetMemInDP(){return m_pInDP;};
	virtual 	pWORLD			GetMemOut(){return m_pOut;};
	virtual 	pDOUBLE			GetMemOutWts(){return m_pOutWts;};
	virtual 	POINT*			GetMemOutDP(){return m_pOutDP;};
	virtual 	void			SetMemIn(pWORLD pMem){m_pIn = pMem;};
	virtual 	void			SetMemInWts(pDOUBLE pMem){m_pInWts = pMem;};
	virtual 	void			SetMemInDP(POINT* pMem){m_pInDP = pMem;};
	virtual 	void			SetMemOut(pWORLD pMem){m_pOut = pMem;};
	virtual 	void			SetMemOutWts(pDOUBLE pMem){m_pOutWts = pMem;};
	virtual 	void			SetMemOutDP(POINT* pMem){m_pOutDP = pMem;};
	/////////////////////////////////////////////////// Memory						
	virtual 	pDOUBLE			FixMemD(long nOut)
								{
									pDOUBLE pOut;
									return ((pOut = new double[nOut]) == NULL)? (pDOUBLE)NULL:pOut;
								};
	
	virtual 	void 			FreeMemD(pDOUBLE pOut){delete[] pOut;};
	/////////////////////////
	virtual 	pWORLD 			FixMem(long nOut)
								{
									pWORLD pOut;
									return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
								};
	
	virtual 	void 			FreeMem(pWORLD pOut){delete[] pOut;};
	/////////////////////////
	virtual 	POINT* 			FixMemDP(long nOut)
				{
					POINT* pOut;
					return ((pOut = new POINT[nOut]) == NULL)? (POINT*)NULL:pOut;
				};
	
	virtual void 	FreeMemDP(POINT* pOut){delete[] pOut;};
	////////////////////////////////////////////////////////////////////// Members
 	short				GetnNodes(){return m_nNodes;};		
	void				SetnNodes(short s){m_nNodes = s;};		
 	short				GetEdgeDegree(){return m_nEdgeDegree;};		
	void				SetEdgeDegree(short s){m_nEdgeDegree = s;}
	///
	CString&			GetElNumID(){return m_ElNumID;};
 	void				SetElNumID(CString p){m_ElNumID = p;};
 	CString&			GetElTypeID(){return m_ElTypeID;};
 	void				SetElTypeID(CString p){m_ElTypeID = p;};
 	CString&			Getline_id(){return m_line_id;};
 	void				Setline_id(CString p){m_line_id = p;};
 	virtual CString&	Getrid(int i){return m_rid[i];};
 	virtual void		Setrid(CString p,int i){m_rid[i] = p;};
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
	virtual UINT		Getrel(int i){return m_rel[i];};				
	virtual void		Setrel(UINT u,int i){m_rel[i] = u;};			
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
//	CDListMgr*			GetFE2DList(){return &m_FE2DList;}; // Oriented
//	CDListMgr*			GetFE3DList(){return &m_FE3DList;};
	////////////////////////////////////////////////////////////////// History
/*//082898
	UINT				GetGenObjType(){return m_GenObjType;};
	void				SetGenObjType(UINT bGen){m_GenObjType = bGen;};
	CDrObject*			GetGenObj(){return m_pGenObj;};
	void				SetGenObj(CDrObject* bGen){m_pGenObj = bGen;};
*/





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


    ////////////////////////////////////// Memory
	pWORLD		m_pIn;		// Control Nodes -WorldCoords
	pDOUBLE		m_pInWts;	// Output  Weights -World or Eye Pos for Rational
	POINT*		m_pInDP;    // Control Nodes -ScreenCoords
	pWORLD		m_pOut;		// Output  Nodes -World or Eye Pos
	pDOUBLE		m_pOutWts;	// Output  Weights -World or Eye Pos for Rational
	POINT*		m_pOutDP;   // Output  Nodes -ScreenCoords
	long		m_nOut;
	/////////////////////////////////////////////////////////////////////
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	short		m_nNodes;			// intermediate + corner Nodes = ALL
	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc
	//////////////////////////////////
	CString		m_ElNumID;	
	CString		m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	CString		m_line_id;
	CString		m_rid[MAX_CORNERS_1D];//
	CString		m_pid,m_mid;  
	//////////////////////////////////
	UINT		m_ElNum;				// Element Number
	UINT		m_ElTypeNum;			// id Number: Element Type
	UINT		m_line_no;
	UINT		m_rel[MAX_CORNERS_1D]; 
	UINT		m_prop,m_mat;           //
	UINT		m_numseg;				//
	/////////////////////////
	double		m_refTemp;				//RefrenceTemperature
	////////////////////////////// 
	int			m_nCardNo;
	POINT 		m_nCenter; 
	/////////////////////////////////// Data Structure
//	CDListMgr	m_FE0DList;	// All Vrtxs connected to this Edge: (1) ->(2): Positive 
//	CDListMgr	m_FE2DList;	// All Faces connected to this Edge 
//	CDListMgr	m_FE3DList;	// All Cubes connected to this Edge
	/////////////////////// Genetics
//082898	UINT		m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//082898	CDrObject*	m_pGenObj;


public:
	virtual ~CDrFE1D();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFE1D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



