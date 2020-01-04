// Pipe.h : header file
//
#ifndef _DRFE0D_H
#define _DRFE0D_H       

#include "DrNode.h" 
#include "DListMgr.h"
#include "Def_Type.h"
//////////////////////////////
// CDrFE0D    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFE0D: public CDrNode
{
public:
// Construction                 
	CDrFE0D();
	DECLARE_SERIAL(CDrFE0D);
	
	
// Operations
public:

	virtual	void 		ReadyToDelete();
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
//	virtual void		Parse_drPipe(CString* pstrCard){};                    //  TOBE DONE
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	// for DECKVIEW
	virtual	void		DoFormattedCardView(CString* pstrCard,CString& strFmt);
	virtual	void		DoUnFormattedCardView(CString* pstrCard);
	///
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
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
//	virtual	void 		FinishObject();
	virtual BOOL 		IsObjectHit(int nNet,POINT point);
	virtual BOOL 		IsKeyMatch(CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);
	////////////////////////////////////////////////////////////////////// Members
 	CString&			GetElNumID(){return m_ElNumID;};
 	void				SetElNumID(CString p){m_ElNumID = p;};
 	CString&			GetElTypeID(){return m_ElTypeID;};
 	void				SetElTypeID(CString p){m_ElTypeID = p;};
 	CString&			Getrid(){return m_rid_0;};
 	void				Setrid(CString p){m_rid_0 = p;};
 	CString&			Getpid(){return m_pid;};
 	void				Setpid(CString p){m_pid = p;};
 	CString&			Getmid(){return m_mid;};
 	void				Setmid(CString p){m_mid = p;};
	//////////////////////////////////
	UINT				GetElNum(){return m_ElNum;};				
	void				SetElNum(UINT u){m_ElNum = u;};			
	UINT				GetElTypeNum(){return m_ElTypeNum;};	
	void				SetElTypeNum(UINT u){m_ElTypeNum = u;};	
	UINT				Getrel(){return m_rel_0;};				
	void				Setrel(UINT u){m_rel_0 = u;};			
	UINT				Getprop(){return m_prop;};		
	void				Setprop(UINT u){m_prop = u;};		
	UINT				Getmat(){return m_mat;};		
	void				Setmat(UINT u){m_mat = u;};
	//
	double				GetRefTemp(){return m_refTemp;};				
	void				SetRefTemp(double u){m_refTemp = u;};
	////////////////////////////////////////////////////////////////////////////////
	virtual	pWORLD	 	GetNormalWorld(){return &m_NormalWorld;};
	virtual	void		SetNormalWorld(WORLD Normal){m_NormalWorld = Normal;};
	virtual	pWORLD	 	GetNormalEye(){return &m_NormalEye;};
	virtual	void		SetNormalEye(WORLD Normal){m_NormalEye = Normal;};
	virtual	pWORLD	 	GetNormalScreen3D(){return &m_NormalScreen3D;};
	virtual	void		SetNormalScreen3D(WORLD Normal){m_NormalScreen3D = Normal;};
	virtual	POINT* 		GetNormalScreen2D(){return &m_NormalScreen2D;};
	virtual	void		SetNormalScreen2D(POINT Normal){m_NormalScreen2D = Normal;};
	virtual void 		Calc_NormalWorld();
	virtual void 		Calc_NormalEye();
	virtual void 		Calc_NormalScreen3D();
	//////////////////////////////////////////////////////////////////
	virtual BOOL		IsMeshNode(){return m_bMeshNode;};	// MeshNode or Just Vertex
	virtual void		SetMeshNode(BOOL bGen){m_bMeshNode = bGen;};
	////////////////////////////////////////////////////////////////// Data Structure
//	CDListMgr*			GetFE1DList(){return &m_FE1DList;};
//	CDListMgr*			GetFE2DList(){return &m_FE2DList;};
//	CDListMgr*			GetFE3DList(){return &m_FE3DList;};
	////////////////////////////////////////////////////////////////// History
/*//082898 we will be using lists instead
	UINT				GetGenObjType(){return m_GenObjType;};
	void				SetGenObjType(UINT bGen){m_GenObjType = bGen;};
	CDrObject*			GetGenObj(){return m_pGenObj;};
	void				SetGenObj(CDrObject* bGen){m_pGenObj = bGen;};
*/
	//////////////////////////////////////////////////////////////////
	int					GetHist_S(){return m_nHist_S;};
	void				SetHist_S(int i){m_nHist_S = i;};
	int					GetHist_T(){return m_nHist_T;};
	void				SetHist_T(int i){m_nHist_T = i;};
	int					GetHist_R(){return m_nHist_R;};
	void				SetHist_R(int i){m_nHist_R = i;};



protected:


//////////////////////////////////////////////////////////////////////////// These are in DrNODE	
//			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
//			void 		TransformToEyePos(pMATRIX pViewM);
//			void 		ProjectToScreenPos
//							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
//			void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
			
			
// Helper functions
protected:
// Attributes
 

	int			m_nHist_S;	// S-index of the generating Curve/Patch/Solid(-1 = Not On Generatrix)
	int			m_nHist_T;	// T-index of the generating Patch/Solid(-1 = Not On Generatrix)
	int			m_nHist_R;	// R-index of the generating Solid(-1 = Not On Generatrix)
	///////////////////////////////// Render
	CString		m_ElNumID;	
	CString		m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	///
	CString		m_rid_0;//			// For Ball Joint Etc.
	CString		m_pid;  
	CString		m_mid;  
	//////////////////////////////////
	UINT		m_ElNum;			// Element Number
	UINT		m_ElTypeNum;		// id Number: Element Type
	///
	UINT		m_rel_0;			// For Ball Joint Etc.
	UINT		m_prop;           //
	UINT		m_mat;           //
	//////////////////////////////////////////////////////////////////////////
	double		m_refTemp;				//RefrenceTemperature
	/////////////////////////
    WORLD  		m_NormalWorld;
    WORLD  		m_NormalEye;
    WORLD  		m_NormalScreen3D;
    POINT  		m_NormalScreen2D;
	/////////////////////////////////// Data Structure
//	CDListMgr	m_FE1DList;
//	CDListMgr	m_FE2DList;
//	CDListMgr	m_FE3DList;
	/////////////////////// Genetics
//082898	UINT		m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
//082898	CDrObject*	m_pGenObj;
	/////////////////////// For Global Processing

public:
	virtual ~CDrFE0D();
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFE0D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



