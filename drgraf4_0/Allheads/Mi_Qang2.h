 // ELMouse.h : header file
//
#ifndef _MI_QANG2_H 
#define _MI_QANG2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "Mi_Gang2.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_Qang2 : public CMI_Gang2
{
public:

	CMI_Qang2();

//////////////////////////////////////
	DECLARE_SERIAL(CMI_Qang2)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

	//////////////////////////////////////////////////////////////////////////////////////// QUAD
	int			Post_PatchNodes_FE0D_4(CDrObject* pMesh,UINT nGenType, pWORLD pOut,int nOut_S,
						int nOut_T,BOOL bCNode,BOOL bMNode,BOOL bAnyWay,BOOL bReverseST);		
	int			Post_PatchNodes_IorC_4(CDrPatch* pPatch, pWORLD pOut, int nOut, BOOL bCNode);		
	int			Post_PatchCurves_4(CDrPatch* pPatch, pWORLD pOut, pDOUBLE pOutWts, int nOut);		
	int			Post_PatchEdges_FE1D_4(CDrMesh2D* pMesh);		
	//
	int			Post_Patch_QUADRILATS(CDrObject* pMesh,CDrObject* pDrPatch,UINT nGenType,
																			UINT nElemType);		
	/////////////////////////////////////////////////////////////////
	void		CalcCentroid_FACE_4(pWORLD Local,pWORLD pC);



protected:  
// Attributes


	int				RotateFaceNodeIndices(pWORLD LPos, int* ix);
	/////////////////////////////////////////////////////////////////////////////////////// Rules
	int				Post_FE2D_4_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	////////////////////////////////////
	int				Post_FE2D_4_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	////////////////////////////////////
	int				PreProcess_SHORTDIAG
					(
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert31[],pWORLD LocalPos31,
						CDrFE0D* pVert32[],pWORLD LocalPos32
					);
	BOOL			IsD1ShorterThanD2(pWORLD LocalPos);
	int				Post_FE2D_4_SHORTDIAG(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	////////////////////////////////////
	CDrFE0D*		CreateIntersectionNode(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,
																		WORLD& LocalPos_In);
	int				PreProcess_INTERSECT
					(
						CDrObject* pMesh,UINT nGenType,
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert31[],pWORLD LocalPos31,
						CDrFE0D* pVert32[],pWORLD LocalPos32,
						CDrFE0D* pVert33[],pWORLD LocalPos33,
						CDrFE0D* pVert34[],pWORLD LocalPos34
					);
	int				Post_FE2D_4_INTERSECT(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	////////////////////////////////////
	CDrFE0D*		CreateCentroidNode_4(CDrObject* pMesh,UINT nGenType,pWORLD LocalPos,
																	WORLD& LocalPos_In);
	int				PreProcess_CENTROID_4
					(
						CDrObject* pMesh,UINT nGenType,
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert31[],pWORLD LocalPos31,
						CDrFE0D* pVert32[],pWORLD LocalPos32,
						CDrFE0D* pVert33[],pWORLD LocalPos33,
						CDrFE0D* pVert34[],pWORLD LocalPos34
					);
	int				Post_FE2D_4_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	/////////////////////////////////////////////////////////////////////////////////////// Elems
	int				Post_QU_4(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// QU_8
	int				Post_QU_8(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// QU_9
	int				Post_QU_9(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// QU_12
	int				Post_QU_12(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	/////////////////////////////////////////////////////// QU_16
	int				Post_QU_16(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);		
	//////////////////////////////////////////////////////////////////////////////////////////////
	int				Post_FE1D_4_NOREF(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType);
	int				Post_FE1D_4_AUTO(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos,
																	UINT nElemType);
	int				PreProcess_SHORTDIAG_FE1D
					(
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert5[],pWORLD LocalPos5
					);
	int				Post_FE1D_4_SHORTDIAG(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	int				PreProcess_INTERSECT_FE1D
					(
						CDrObject* pMesh,UINT nGenType,
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert6[],pWORLD LocalPos6,
						CDrFE0D* pVert3[],pWORLD LocalPos3
					);
	int				Post_FE1D_4_INTERSECT(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);
	int				PreProcess_CENTROID_4_FE1D
					(
						CDrObject* pMesh,UINT nGenType,
						CDrFE0D* pVert[],pWORLD LocalPos,
						CDrFE0D* pVert6[],pWORLD LocalPos6,
						CDrFE0D* pVert3[],pWORLD LocalPos3
					);
	int				Post_FE1D_4_CENTROID(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],
													pWORLD LocalPos,UINT nElemType);




protected:



//Operations
public:

	~CMI_Qang2();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Qang2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
