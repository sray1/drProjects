 // mp_Rotat.h : header file
/////////////////////////////////////////////////////////////////////////////
//						L A T E S T  A S  O F  OCTOBER 12, 1998
/////////////////////////////////////////////////////////////////////////////
#ifndef _MC_CIRCLE_H 
#define _MC_CIRCLE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangC.h"
#include "In_Circle.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMC_Circle : public CMI_GangC
class AFX_EXT_CLASS CMC_Circle : public CMI_GangC
{
public:

	CMC_Circle();
//////////////////////////////////////
	DECLARE_SERIAL(CMC_Circle)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	CDrCurve*	CreateCircle(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
					 CURVEPROC kind,CList<int,int>* pElperSegList,CIRCLETYPE nType,
					 double dAng,double SegAngle,double dRadius,BOOL bArc,
					 CDrNode* pFromIDNode,CDrNode* pToIDNode,BOOL bFinal);
				/////////////////////////////////////
	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal,CIRCLETYPE nType); 

protected:
	int			GoDoIt(CDrCurve* pCurve,BOOL bFinal);  
	////////////////////////////////////////////////// Circle
	int			SetCommonInfoForCircle(CDrCurve* pDrObject);
	/////////////////////////////////////////////////////////////////////////////////
	int			CalcAdditionalInfo(CDrCurve* pDrCurve,BOOL bFinal,CIRCLETYPE nType);
	int			CalcAdditionalInfo_Rot(CDrCurve* pDrCurve,BOOL bFinal);
	int			CalcAdditionalInfo_3Node(CDrCurve* pDrCurve,BOOL bFinal);	//2
	int			CalcAdditionalInfo_2N_TI(CDrCurve* pDrCurve,BOOL bFinal);	//3
	int			CalcAdditionalInfo_2N_CC(CDrCurve* pDrCurve,BOOL bFinal);	//4
	int			CalcAdditionalInfo_2CN_TI_R(CDrCurve* pDrCurve,BOOL bFinal);//5
	///
	int			PackINodeList(CDrCurve* pCurve);
	int			PackAuxiliaryList(CDrCurve* pCurve,WORLD& Ne,CDListMgr* pList);
	void		UnitAxisFromEndNodes(pWORLD pNormal,WORLD& FromPt,WORLD& ToPt);
	int			Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE pRadius,
												WORLD Normal,WORLD AxPt);
	int			Calc_C_R_Normal(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal);
	int			Calc_CRNPhifromTI(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal,
										pDOUBLE Phi);
	int			Calc_CRNPhifromCC(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal,
										pDOUBLE Phi);
	int			Calc_NiNj_CRNPhi(pWORLD Data,pWORLD Ni, pWORLD Nj, pWORLD Center,
										pWORLD Normal, pDOUBLE pRadius, pDOUBLE Phi);
	double		Calc_CentralAngles(pWORLD Data, WORLD Center, double Radius,WORLD Normal);
	//////////////////////////////////////////////////////////////////////////////////////
	int			BezierInfo(CDrCurve* pCurve); 
	int			BezierSeg_N_Mesh_Done(CList<int,int>& BSegList,CList<int,int>& ElemList,
									  CList<double,double>& AngList,
										pINT &pBSeg,pINT &pOSeg,pDOUBLE &pODis,
										int& nBSegTot,int& nElemTot,double& dAnglTot); 
	int			BezierSeg_N_Mesh_Update(CList<int,int>& BSegList,CList<int,int>& ElemList,
									  CList<double,double>& AngList,
										pINT &pOSeg,pDOUBLE &pODis, int nBSegs,int& nBSegTot); 
	int			BezierSeg_N_Mesh(CDrCurve* pCurve,WORLD& wNa,WORLD& wNb,WORLD& wNc,
							pINT &pOSeg,pDOUBLE &pODis, int nElems,BOOL bUniform); 
	int			BezierSeg_N_Mesh_Uniform(CDrCurve* pCurve,pINT &pOSeg,pDOUBLE &pODis,
															double dAng,int nElems);
	int			BezierSeg_N_Mesh_NonUniform(CDrCurve* pCurve,pINT &pOSeg,pDOUBLE &pODis,
							double dAng,double dRatio,int nElems);
	int			SetBezierControlInfo(CDrCurve* pDrObject,int nBSeg,
							pINT &pBSeg,pINT &pOSeg,pDOUBLE &pODis,
							int nBSegTot,int nElemTot,double dAnglTot);
	////////////////////////////////////////////////////////////
	int 		InterPolate(BOOL bFinal);
	int 		SetMemory();
	int			GenerateBezier_b0s_b2s(CDrCurve* pCurve);
	int			GetBezEndPtsbyRotation
					(
						int		nData,		//	# of Extended Input Data 
						WORLD	Center,
						WORLD	Axis,		//	unit direction vector of rotation axis
						BOOL	bClosed,
						pDOUBLE	pDis,		//	Angle Distribution for each Bez Patch in degrees
						int		nBSegTot,			//	Total # Bezier Curve Segs
						pINT	pSegBz,		//	Bezier Segments( per Data pair) array
						pWORLD	pData,		//	input extended data array
						pWORLD	pOut		//	Output Pts array
					);	  
	int			GetAPtByRotation(pWORLD pb0 , WORLD AxisPt, WORLD Normal, 
								double dAng, pWORLD pb2);
	int 		PrepInterpolation();
	int 		PostInterpolation(BOOL bFinal);
	///////////////////////////////////////////
	CDrCurve*	GoDoIt(); 
	CDrCurve* 	GetInfo();
	/////////////////////////////////////////////////////////////////// 
		          

protected:  
// Attributes

	CIn_Circle			m_In_Conics;
	UINT				m_nInputType;	// CIRCLE_BY_NO3 etc
	CList<WORLD,WORLD>	m_DataList_Ex;	// Extended for Circle/Ellipse beyond Arc

	
//Operations
public:

	~CMC_Circle();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMC_Circle)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
