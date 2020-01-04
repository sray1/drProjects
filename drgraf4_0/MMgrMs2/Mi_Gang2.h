 // ELMouse.h : header file
//
#ifndef _MI_GANG2_H 
#define _MI_GANG2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "Str_Mesh.h"
#include "DrPatch.h"
#include "DrMesh2D.h"
#include "DrEdge.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "Po_FE2D.h"
#include "Mi_Gang1.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Gang2 : public CMI_Gang1
{
public:

	CMI_Gang2();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_Gang2)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	int					Regen_MESH2D_Elements(CDrObject* pMeshNew,CDrObject* pMeshOld);		
	int					Regen_MESH2D_FE1D(CDrObject* pMeshNew,CDrObject* pMeshOld);		
	int					Regen_MESH2D_FE2D(CDrObject* pMeshNew,CDrObject* pMeshOld);
	void				CloneInfoForRegenElems_FE2D(CDrFE2D* pDrObject,CDrFE2D* pOldObj);
	///
	int					Save_EdgeInfo(CDrEdge* pAddEdge,CDrObject* pMesh,UINT nGenType,int ni,int nj);	
	///
	int					Post_PatchNodes_IorC(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode);		
	int					ShowPatchInfo(CDrPatch* pDrPatch);
	CDrFE0D*			CreateMNode(CDrObject* pMesh,UINT nGenType,WORLD& LocalPos_In);
//	BOOL		IsIntersect_LINE_LINE(pWORLD LocalPos,WORLD& LocalPos_In);
	//////////////////////////////////////////////////////////////////////////////////////// Data
 	CString&			Getrid(int i){return m_rid[i];};
 	void				Setrid(CString p,int i){m_rid[i] = p;};
	////////////////////////////////////////////////////////
	ELEM_DEGREE			GetElDegree(){return m_ElDegree;};		
	void				SetElDegree(ELEM_DEGREE& u){m_ElDegree = u;};
	/////////////////////////////////////////////////////////////////
	ORIENT				GetOrient(){return m_Orient;};		
	void				SetOrient(ORIENT u){m_Orient = u;};
	/////////////////////////////////////////////////////////////////
	double				GetThick(){return m_Thick;};
	void				SetThick(double d){m_Thick = d;};
	/////////////////////////////////////////////////////////////////////////////////////// Elems
	int					Post_TR_3(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// TR_6
	int					Post_TR_6(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// TR_9
	int					Post_TR_9(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// TR_10
	int					Post_TR_10(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		



protected:  
// Attributes


	int				TransferData_2D(CPo_FE2D* pFE2D);		



protected:


	/////////////////////////////////////////// FE2D Common Data Not Included Above
	// Note: 
		//	# of Vertex = 2 always;
		//	# of Nodes is Variable Based on ElementType;	 
	/////////////////////////////////////////////////////////////////////
	CString		m_rid[MAX_CORNERS_2D];//
	//////////////////////////////////
	UINT		m_rel[MAX_CORNERS_2D]; 
	///////////////////////
	// for Isoparametric: may be different Edge Degree
	short		m_nEdgeDegree[MAX_EDGES_2D];	// 1 = Linear/ 2 = Quadratic etc
	ELEM_DEGREE	m_ElDegree;
	//////////////////////// Orientation
	ORIENT		m_Orient;
	double		m_Thick;
	//////////////////////// Plane Eqn
	WORLD		m_Normal_ABC;
	double		m_D;

//Operations
public:

	~CMI_Gang2();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Gang2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
