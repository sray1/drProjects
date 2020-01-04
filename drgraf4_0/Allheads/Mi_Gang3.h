 // ELMouse.h : header file
//
#ifndef _MI_GANG3_H 
#define _MI_GANG3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "Str_Mesh.h"
#include "DrPatch.h"
#include "DrMesh2D.h"
#include "DrEdge.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "DrFE3D.h"
#include "Po_FE2D.h"
#include "Mi_Gang2.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Gang3 : public CMI_Gang2
{
public:

	CMI_Gang3();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_Gang3)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	int					Regen_MESH3D_Elements(CDrObject* pMeshNew,CDrObject* pMeshOld);		



protected:  
// Attributes





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

	~CMI_Gang3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Gang3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
