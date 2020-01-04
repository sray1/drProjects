 // ELMouse.h : header file
//
#ifndef _MI_TANG2_H 
#define _MI_TANG2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "Mi_Gang2.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Tang2 : public CMI_Gang2
{
public:

	CMI_Tang2();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_Tang2)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	int			Post_PatchCurves_3(CDrPatch* pPatch, pWORLD pOut, pDOUBLE pOutWts, int nOut);
	//////////////////////////////////////////////////////////////////////////////////////// TRI
	int			Post_PatchNodes_FE0D_3(CDrObject* pMesh,UINT nGenType,CDrPatch* pDrPatch,pWORLD pOut,
										BOOL bCNode,BOOL bMNode,BOOL bAnyWay);		
	int			Post_PatchNodes_IorC_3(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode);		
	///
	int			Post_PatchEdges_FE1D_3(CDrMesh2D* pMesh);		
	//
	int			Post_Patch_TRIANGLES(CDrObject* pMesh,CDrObject* pDrPatch,UINT nGenType,
																		UINT nElemType);		
	/////////////////////////////////////////////////////////////////
	void		CalcCentroid_FACE_3(pWORLD Local,pWORLD pC);



protected:  
// Attributes


	///////////////////////////////////////////////////////////////////////////////////////////
	void		TRIANGLE_1_Edge(CDrMesh2D* pMesh,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST);
	void		TRIANGLE_2_Edge(CDrMesh2D* pMesh,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST);
	BOOL		IsDuplicated(WORLD& CurrentNodPos,CDrObject* pMesh);
	int			Post_FE0D_TRIANGLE_1(pWORLD pOut,CDrObject* pMesh,UINT nGenType,CDrPatch* pDrPatch,
								BOOL bCNode,BOOL bMNode,BOOL bAnyWay,
								int iOutGlo_ST,int jOutGlo_ST);
	int			Post_FE0D_TRIANGLE_2(pWORLD pOut,CDrObject* pMesh,UINT nGenType,CDrPatch* pDrPatch,
								BOOL bCNode,BOOL bMNode,BOOL bAnyWay,
								int iOutGlo_ST,int jOutGlo_ST);
	int			Post_FE0D_TRIANGLE(WORLD& LocalPos,CDrObject* pMesh,UINT nGenType,
								BOOL bCNode,BOOL bMNode,BOOL bAnyWay);
	/////////////////////////////////////////////////////////////////////////////////////// LIN
	int			Post_OneTriangularPatch_LIN(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
									int nOutPerSeg,int nOutTot_S,int TriangularPatchType);
	int			GetTriangleVertexInfo_1_Lin(int i, int j, int nP, pINT pIndex);
	int			GetTriangleVertexInfo_2_Lin(int i, int j, int nP, pINT pIndex);
	/////////////////////////////////////////////////////////////////////////////////////// QUAD
	int			Post_OneTriangularPatch_QUAD(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
														int nOut_S,int TriangularPatchType);
	int			GetTriangleVertexInfo_1_Quad(int i, int j, int nP, pINT pIndex);
	int			GetTriangleVertexInfo_2_Quad(int i, int j, int nP, pINT pIndex);
	/////////////////////////////////////////////////////////////////////////////////////// CUBIC
	int			Post_OneTriangularPatch_CUBIC(CDrMesh2D* pMesh,int iGlo,int jGlo,UINT nElemType,
														int nOut_S,int TriangularPatchType);
	int			GetTriangleVertexInfo_1_Cubic(int i, int j, int nP, pINT pIndex);
	int			GetTriangleVertexInfo_2_Cubic(int i, int j, int nP, pINT pIndex);
	/////////////////////////////////////////////////////////////////////////////////////// Rules
	int			Post_TRIANGLE(CDrMesh2D* pMesh, pINT ix,UINT nElemType);
	int			Post_FE2D_3_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																UINT nElemType);
	////////////////////////////////////
	int			Post_FE2D_3_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																UINT nElemType);
	////////////////////////////////////
	CDrFE0D*	CreateCentroidNode_3(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,WORLD& LocalPos_In);
	int			PreProcess_CENTROID_3
				(
					CDrObject* pMesh,UINT nGenType,
					CDrFE0D* pVert[],pWORLD LocalPos,
					CDrFE0D* pVert31[],pWORLD LocalPos31,
					CDrFE0D* pVert32[],pWORLD LocalPos32,
					CDrFE0D* pVert33[],pWORLD LocalPos33
				);
	int			Post_FE2D_3_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType);




protected:



//Operations
public:

	~CMI_Tang2();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Tang2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
