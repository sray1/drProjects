 // MI_Pat_I.h : header file
//
#ifndef _MI_PAT_I_H 
#define _MI_PAT_I_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_Cur_I.h"
#include "DrNode.h"
#include "DrFE2D.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "Def_CuPS.h"                    
#include "Str_BlendEnd.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Pat_I : public CMI_Cur_I
{
public:

	CMI_Pat_I();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Pat_I)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	/////////////////////////////////////////////// 
	int 	LBDownInit_PInsert(UINT nType); 
	int 	LBUpInit_PInsert(enum CURVEPROC kind); 
	int		RBUpExtrudeInsert
				(
					BOOL							bGenBCurve,
					int								nExtruType,
									// 1 = Given: Extrusion Direction Nodes
									// 2 = Given: 3 Lenths (wLen) to Extrude to
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_V, // ist record: elem/seg
																	// 2nd record: #of BezSeg
					WORLD							wLen_V,
					double							dLen_V,
					double							Ratio_V,
					//////////////////////////////////////////////
					CView*							pView
				); 
	int		RBUpRotateInsert
				(
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
															// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// given Curves always taken as U-dir
															// and later switched,if needed,i.e.,
															// nCurDir = 2
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_V, // ist record: elem/seg
																// 2nd record: #of BezSeg
					double							dAngle_V,
					double							Ratio_V,
					BOOL							bAxis,
					int								nAxis,
					BOOL							bNegative,
					//////////////////////////////////////////////
					CView*							pView
				); 
	int 	RBUpLoft2Insert 
					( 
						CString&						PatchID,		
						CDrPatch*						pDrPatch,
						CDListMgr*						pCurveList,
						CList<CURVELATCH,CURVELATCH>*	pLatchList,
						CList<int,int>*					pElperSegList,
						double							Ratio,
						CView*							pView
					); 
	int		RBUpLoftXInsert
				( 
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					CDrCurve*						pBlendCurve_U,
					BOOL							bAdvanced,	// tangents/twist BC
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								nCurDir,	// Curve Direction:1=U/2=V
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					int								nNodes_U,
					int								nNodes_V,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////
					CDListMgr*						pCurveList_U,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_V,
					CDrCurve*						pBlendCurve_V,
					double							Ratio_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				); 
	int		RBUpTensorInsert
				( 
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					BOOL							bAdvanced,
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////////
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								nNodes_U,
					CList<int,int>&					ElperSegList_U,
					double							Ratio_U,
					CDrCurve*						pBlendCurve_U,
					CList<BLENDEND,BLENDEND>*		pEndList_U,	// if(bClosed_U or Linear_U,Circle_U,
																// parabola_U) EndList_U Empty
					//////////////////////////////////////////////
					int								nNodes_V,
					CList<int,int>&					ElperSegList_V,
					double							Ratio_V,
					CDrCurve*						pBlendCurve_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				); 
	int		RBUpGordonInsert
				( 
					BOOL							bAdvanced,	// tangents/twist BC
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////////
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								nNodes_U,
					CDListMgr*						pCurveList_U,
					CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
					CList<int,int>&					ElperSegList_U,
					double							Ratio_U,
					CDrCurve*						pBlendCurve_U,
					CList<BLENDEND,BLENDEND>*		pEndList_U,	// if(bClosed_U or Linear_U,Circle_U,
																// parabola_U) EndList_U Empty
					//////////////////////////////////////////////
					int								nNodes_V,
					CDListMgr*						pCurveList_V,
					CList<CURVELATCH,CURVELATCH>*	pLatchList_V,
					CList<int,int>&					ElperSegList_V,
					double							Ratio_V,
					CDrCurve*						pBlendCurve_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				); 
	int 	RBUpSweepInsert 
					(
						BOOL							bGenBCurve,
						int								nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
						int								nScaleType,
										// 1 = Given: Scale Distribution
										// 2 = Given: Scale Increments etc
						//////////////////////////////////////////
						CString&						PatchID,		
						CDrPatch*						pDrPatch,
						//////////////////////////////////////////
						CDListMgr*						pNodeList,	// One record: Anchor Node
						//////////////////////////////////////////
						CDListMgr*						pCurveList,	// 1: XSection Curve
																	// 2: Spine Curve
						CList<CURVELATCH,CURVELATCH>*	pLatchList,
						//////////////////////////////////////////
						CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
						double							TwistMult,	// if nTwistType = 2 
						BOOL							bIncrement,
						double							TwistStart,
						//////////////////////////////////////////
						CList<double,double>*			pScaleList,	// Distrib,if nScaleType = 1
						double							ScaleMult,			// if nScaleType = 2 
						BOOL							bIncScale,
						double							ScaleStart,
						//////////////////////////////////////////////
						CView*							pView
					); 
	int 	RBUpDuctInsert 
					(
						BOOL							bGenBCurve,
						int								nTwistType,
										// 1 = Given: Twist Distribution
										// 2 = Given: Twist Increments etc
						//////////////////////////////////////////
						CString&						PatchID,		
						CDrPatch*						pDrPatch,
						//////////////////////////////////////////
						CDListMgr*						pNodeList,	// One record: Anchor Node
						//////////////////////////////////////////
						CDListMgr*						pCurveList,	// 1: XSection Curve
																	// 2: Spine Curve
						CList<CURVELATCH,CURVELATCH>*	pLatchList,
						//////////////////////////////////////////
						CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
						double							TwistMult,	// if nTwistType = 2 
						BOOL							bIncrement,
						double							TwistStart,
						//////////////////////////////////////////////
						CView*							pView
					); 
 	int 	RBUpCoonInsert
					(
						BOOL							bGenBCurve,
						PATCHPROC						ppKind, 
						CString&						PatchID,		
						CDrPatch*						pDrPatch,
						CDListMgr*						pCurveList,
						CList<CURVELATCH,CURVELATCH>*	pLatchList,
						CView*							pView
					); 
  				
		
protected:


	///////////////////////////////////////////////////////////// EXTRUDE	
	int		Generate_BndryCurves_EXTRUDE(CDrPatch* pDrPatch,
					CList<int,int>*	pElperSegList,double Ratio);
	int		GenExtrusionCurve_U(CDrPatch* pDrPatch);
	int 	SetUpLocalM_Extrusion(CDListMgr* pCNList,pMATRIX pM);
	int		GenExtrusionCurve_V(CDrPatch* pDrPatch,
					CList<int,int>*	pElperSegList,double Ratio);
		          

protected:  
// Attributes

	CDrPatch* 	m_pDrPatch;
//Operations
public:

	~CMI_Pat_I();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Pat_I)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
