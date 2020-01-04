 // CMI_Gang1 : header file
//
#ifndef _MI_GANG1_H 
#define _MI_GANG1_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "Str_Mesh.h"
#include "DrCurve.h"
#include "DrMesh1D.h"
#include "MI_Gang0.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Gang1 : public CMI_Gang0
{
public:

	CMI_Gang1();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Gang1)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
    				
		
public:


	/////////////////////////////////////////////////////////////////////// Regen
	int			Regen_MESH1D_Elements(CDrObject* pMesh,CDrObject* pMotherMesh);		
	void		CloneInfoForRegenElems_FE1D(CDrFE1D* pDrObject,CDrFE1D* pOldObj);
	/////////////////////
	int			Post_Curve_Elements(CDrObject* pMesh,CDrObject* pDrCurve,UINT nGenType,UINT nElemType);		
	////////////////////////////////////////////////// Posting Helper
	int			ShowCurveInfo(CDrCurve* pDrCurve);
	int			GenPost_CurveNodes(CDrMesh1D* pMesh,CDrCurve* pDrCurve,BOOL bMNode,BOOL bAnyWay);		
	int			Post_CurveNodes_FE0D(CDrMesh1D* pMesh, pWORLD pOut,int nOut,
										BOOL bCNode,BOOL bMNode,BOOL bAnyWay);		
	int			Post_CurveNodes_IorC(CDrCurve* pCurve,pWORLD pOut, int nOut, BOOL bCNode);		
	////////////////////////////////////////////////////////////////////// Members
 	CString&	Getline_id(){return m_line_id;};
 	void		Setline_id(CString p){m_line_id = p;};
 	CString&	Getrid(int i){return m_rid[i];};
 	void		Setrid(CString p,int i){m_rid[i] = p;};
	//////////////////////////////////
	UINT		Getline_no(){return m_line_no;};		
	void		Setline_no(UINT u){m_line_no = u;};		
	UINT		Getrel(int i){return m_rel[i];};				
	void		Setrel(UINT u,int i){m_rel[i] = u;};			
	UINT		Getnumseg(){return m_numseg;};		
	void		Setnumseg(UINT u){m_numseg = u;};
   ////////////////////////////////////////////////////////////////////// helper
	POINT 		GetCenter(){return m_nCenter;};
	void		SetCenter(POINT ptCenter){m_nCenter = ptCenter;};
	/////////////////////////
	BOOL		IsOnBndry(){return m_bOnBndry;};
	void		SetOnBndry(BOOL b){m_bOnBndry = b;};
	//////////////////////////////////////////////////////// moved to Po_FE1D 090398
//	void		CalcCentroid_EDGE(pWORLD Local,pWORLD pC);
	///
	void		CalcCentroid(pWORLD pCentroid,pWORLD Local,int nVert);




protected:  
// Attributes


	int		TransferData_1D(CPo_FE1D* pFE1D);		
	int		Post_TRUSS(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert);		
	int		Post_BEAM(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert);		
	int		Post_PIPE(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert);		
	int		Post_ELBOW(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,int nVert);		
	/////////////////////////////////////////////////////////////////
	int		GetVertexInfo(CDListMgr* pListV,int* Index,CDrFE0D* pVert[],
											pWORLD LocalPos, int nIndex);
	void	GetLocalPos_Vertices(pWORLD Local,CDrFE0D* pVert[],int nVert);





protected:  
// Attributes

	/////////////////////////////////////////// FE1D Common Data Not Included Above
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	short		m_nNodes;			// intermediate + corner Nodes = ALL
	short		m_nEdgeDegree;		// 1 = Linear/ 2 = Quadratic etc
	//////////////////////////////////
	CString		m_line_id;
	CString		m_rid[MAX_CORNERS_1D];//
	//////////////////////////////////
	UINT		m_line_no;
	UINT		m_rel[MAX_CORNERS_1D]; 
	UINT		m_numseg;				//
	////////////////////////////// 
	POINT 		m_nCenter; 
	///////////////////////
	BOOL		m_bOnBndry;





//Operations
public:

	~CMI_Gang1();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Gang1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
