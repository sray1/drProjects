#ifndef	_PO_FE2D_H_
#define	_PO_FE2D_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Mesh.h"
#include "Str_Mesh.h"
#include "DrObject.h"
#include "DrEdge.h"
#include "DrFE2D.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_FE2D
/////////////////////////////////////////////////////////////////////////////
class CPo_FE2D : public CPo_FE1D
{
// Construction
public:  
	CPo_FE2D(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_FE2D)
//////////////////////////////////////

protected: 
public:
// Implementation

	int					Post_FE2D_4(CDrFE2D* pAddFace,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid);		
	int					Post_FE2D_3(CDrFE2D* pAddFace,CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
												pWORLD LocalPos,CString& Eid);		
	int					FillData_2D(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType);
				  

public:

 	CString&			Getrid(int i){return m_rid[i];};
 	void				Setrid(CString p,int i){m_rid[i] = p;};
	double				GetThkness(){return m_Thick;};
	void				SetThkness(double Thick){m_Thick = Thick;};
	////////////////////////////////////////////////////////
	ELEM_DEGREE			GetElDegree(){return m_ElDegree;};		
	void				SetElDegree(ELEM_DEGREE& u){m_ElDegree = u;};
	/////////////////////////////////////////////////////////////////
	ORIENT				GetOrient(){return m_Orient;};		
	void				SetOrient(ORIENT u){m_Orient = u;};
	///////////////////////////////////////////////////////////////////////////////// Helper
	int					SetFE2DInfo_4(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType);
	int					SetFE2DInfo_3(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType);
	int					SetFE2DInfo_Vrtx(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,
																						int nEnds);
	int					SetFE2DInfo_Edge(CDrFE2D* pFE2D,CDrFE0D* pVert[],CDrObject* pMesh,UINT nGenType,
																						int nEnds);
	CDrEdge*			GetEdge(CDrObject* pMesh,CDrFE0D* pVi,CDrFE0D* pVj,BOOL& bPositive);
	int					Make_CentroidLabel_FACE_4(CDrFE2D* pFace,pWORLD LocalPos,CString& Eid);
	int					Make_CentroidLabel_FACE_3(CDrFE2D* pFace,pWORLD LocalPos,CString& Eid);
	int					EachAddlNodeInfo(CDrFE2D* pFE2D,pWORLD NewPos,CDrObject* pMesh,UINT nGenType);


	
protected:


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


public:
	virtual ~CPo_FE2D(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_FE2D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

