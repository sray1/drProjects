 // CMI_Gang0.h : header file
//
#ifndef _MI_GANG0_H 
#define _MI_GANG0_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "drNode.h"
#include "drFE0D.h"
#include "DrLabel.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Gang0 : public CObject
{
public:

	CMI_Gang0();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Gang0)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	int			ReciprocateElemMeshList(CDrObject* pElem, CDrObject* pMesh, UINT nGenType);
	int			SetElemInfoID(CString& ElemID,UINT nElemType);		
	void		Setid(CString s){m_id = s;};
	////////////////////////////////////////
	CDrFE0D* 	PostFE0D(CString& Nid,WORLD Pt,BOOL bCNode,BOOL bMNode);//
				// Internal Generation: bMNode = TRUE->LEVEL_KIDDO/FALSE->LEVEL_GRAPA
 	CDrFE0D*	CreateFE0D(CString& Nid,CDrLabel* pLabel,WORLD Pt,BOOL bCNode,BOOL bGen,
							    BOOL bMNode,int& nNodeIndex, int& nLabelIndex);	//Use for Input
	////////////////////////////////////////
	CDrLabel*	CreateFE0DLabel(CDrFE0D* pNode,int& nActiveIndex);
	/////////////////////////////////////////////////// Memory						
	pDOUBLE		FixMemD(long nOut)
				{
					pDOUBLE pOut;
					return ((pOut = new double[nOut]) == NULL)? (pDOUBLE)NULL:pOut;
				};
	
	void 		FreeMemD(pDOUBLE pOut){delete[] pOut;};
	/////////////////////////
	pWORLD 		FixMem(long nOut)
				{
					pWORLD pOut;
					return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
				};
	
	void 		FreeMem(pWORLD pOut)
				{
					if(pOut) 
					delete[] pOut;
				};
	////////////////////////////////////////////////// Posting Helper
	void		SetInfoForFE0DBase(CDrFE0D* pNode,BOOL bGen,BOOL bMNode);
	void		SetInfoForFE0DLabel(CDrFE0D* pAddNode,CDrLabel* pLabel);
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
	double				GetRefTemp(){return m_RefTemp;};				
	void				SetRefTemp(double u){m_RefTemp = u;};
	//
	UINT				GetCardNo(){return m_nCardNo;};		
	void				SetCardNo(UINT u){m_nCardNo = u;};
	////////////////////////////////////////////////////////////////////////////////
		          



	

protected:  
// Attributes


	CString		m_id;
	//////////////////////////////////// Posting Nodes
	CString		m_nid_r;
	CString		m_sup_id;
	CString		m_load_id;
	CString		m_FromID;
	CString		m_ToID;
	double		m_dLength;
	double		m_xWorld;
	double		m_yWorld;
	double		m_zWorld;
	double		m_DxWorld;
	double		m_DyWorld;
	double		m_DzWorld;
	BOOL		m_bnid_c;
 	BOOL		m_bCoord;
	/////////////////////////////////////////// FE0D Common Data Not Included Above
	CString			m_ElNumID;	
	CString			m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	CString			m_rid_0;//			// For BallJoint
	CString			m_pid;  
	CString			m_mid;  
	////////////////////////////////// Indices in List
	UINT			m_ElNum;				// Element Number
	UINT			m_ElTypeNum;			// id Number: Element Type
	UINT			m_rel_0; 
	UINT			m_prop;           //
	UINT			m_mat;           //
	/////////////////////////
	double			m_RefTemp;				//RefrenceTemperature
	////////////////////////////// 
	int				m_nCardNo;
	/////////////////////// Genetics
	UINT			m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
	CDrObject*		m_pGenObj;
	///////////////////////

//Operations
public:

	~CMI_Gang0();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Gang0)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
