// Patch.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN

#include "glb_Type.h"
#include "glb_Objs.h"
#include "glb_CuPS.h"

#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "XForm.h"
#include "3DMath.h"
////////////////////// ElemObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrFE2D.h"
/////////////////////
#include "surface3.h"
#include "surface4.h"
#include "DrCurve.h"
/////////////////////
#include "DrPatch.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)

#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)	(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)
/////////////////////////////////////////////////////////////////////////////
// CDrPatch
IMPLEMENT_SERIAL(CDrPatch, CDrCurve,1)
/*
BEGIN_MESSAGE_MAP(CDrPatch, CDrCurve)
	//{{AFX_MSG_MAP(CDrPatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrPatch::CDrPatch()
{  
    	
    //////////////////////////////	
    SetObjectType((int)PATCH);
    SetElemType((int)GENR_OBJECT);          //
    //////////////////////////////  
	m_ParentID		= " ";	// if Spawned
	m_ObjectID		= " ";
//	m_instanceXf 	= ;
//	m_raOptions		=;
	m_bInstanced	= FALSE;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	m_nOut		= 0;
	////////////////////
	m_pIn		= NULL;
	m_pInDP		= NULL;
	m_pOut		= NULL;
	m_pOutDP	= NULL;
	for(int i =0;i<4;i++)
	{
		m_pIn_S[i] = NULL;
		m_CurveID[i] = "";
		m_CuLatch[i] = CL_FORWARD;
	}		
	///////////////////	 
	m_pNum_t_T			= NULL;	
	m_pDis_t_T			= NULL;	
	m_pDis_Ang_T		= NULL;	
	m_pNum_t_Ex_T		= NULL;	
	m_pTangents_T		= NULL;	
	m_pCurvatures_T		= NULL;
	////////////////////////////
} 
    	
CDrPatch::~CDrPatch()
{  

	////////////////////////////// Pointers Borrowd from Generating Curves
   								// SHOULD HAVE BEEN ALready DELETED!
								// So NULL them, so that the Curve this
								// Patch is derived from does not attempt
								// to delete again!!!
 	m_pWts_BZ_S			= NULL;		
	m_pNum_t_S			= NULL;
	m_pDis_t_S			= NULL;
	m_pNum_t_Ex_S		= NULL;
   ///////////////////////////////////////////////////////////////////////	
	if(m_pNum_t_T)
	{
		delete m_pNum_t_T;
		m_pNum_t_T = NULL;
	}
	if(m_pDis_t_T)
	{
		delete m_pDis_t_T;
		m_pDis_t_T = NULL;
	}
	if(m_pDis_Ang_T)
	{
		delete m_pDis_Ang_T;
		m_pDis_Ang_T = NULL;
	}
	if(m_pNum_t_Ex_T)
	{
		delete m_pNum_t_Ex_T;
		m_pNum_t_Ex_T = NULL;
	}
	if(m_pTangents_T)
	{
		delete m_pTangents_T;
		m_pTangents_T = NULL;
	}
	if(m_pCurvatures_T)
	{
		delete m_pCurvatures_T;
		m_pCurvatures_T = NULL;
	}
	////////////////////////////
	if(m_pIn)
		FreeMem(m_pIn); 
	if(m_pInDP)
		FreeMemDP(m_pInDP);
	if(m_pOut)
		FreeMem(m_pOut); 
	if(m_pOutDP)
		FreeMemDP(m_pOutDP);
	for(int i =0;i<4;i++)
	{
		if(m_pIn_S[i])
			FreeMem(m_pIn_S[i]);
//	delete m_pIn_S[i];
			m_pIn_S[i] = NULL;
	}		
	m_pIn		= NULL;
	m_pInDP		= NULL;
	m_pOut		= NULL;
	m_pOutDP	= NULL;
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrPatch::ReadyToDelete()
{
	//////////////////////////////////////////////////////////////
	//	REASON:                                                 //
	//		                                                    //
	// 		public means it is ALSO in pObjectMgr->ObjList      //
	//			these will be deleted from ObjList              //
	// 		private means ONLY in the current Object            //
	//		hierarchy means current one is a building block		//
	//////////////////////////////////////////////////////////////
	
	////////////////////////////////////// unload Nodes/No delete:public
	CDListMgr* pNodeList = GetNodeList();
    //////////////////////////////////////
	CDrObject* pObject;
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //Node
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pPatchList = pObject->GetPatchList();
			int index = pPatchList->GetObjectIndex(this);
			if(index>=0)
				pPatchList->RemoveObject(index); //Patch
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// unload CNodes/No delete:public
	pNodeList = GetCNodeList();
    //////////////////////////////////////
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //CNode
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pPatchList = pObject->GetPatchList();
			int index = pPatchList->GetObjectIndex(this);
			if(index>=0)
				pPatchList->RemoveObject(index); //patch
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// unload Curves/No delete:public
	CDListMgr* pCurveList = GetCurveList();
    //////////////////////////////////////
	while(!pCurveList->IsEmpty())
	{
		pObject = (CDrObject*)pCurveList->RemoveHead();  //Curve
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pPatchList = pObject->GetPatchList();
			int index = pPatchList->GetObjectIndex(this);
			if(index>=0)
				pPatchList->RemoveObject(index); //curve
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// delete Elems:private
	CDListMgr* pElemList = GetElemList();
    //////////////////////////////////////
	while(!pElemList->IsEmpty())
	{
		pObject = (CDrObject*)pElemList->RemoveHead();  //Elem
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pNodeList = pObject->GetNodeList();
			while(!pNodeList->IsEmpty())
			{
				CDrObject* pNode = (CDrObject*)pNodeList->RemoveHead(); //Node
				int index = pNode->GetElemList()->GetObjectIndex(pObject);
				if(index>=0)
					pNode->GetElemList()->RemoveObject(index); //Elem
			}		
		/////////////////////////
		}
		//////////
	    delete pObject;
	}
	////////////////////////////////////// delete Triangles:private
	CDListMgr* pTriList = GetTriangleList();
    //////////////////////////////////////
	while(!pTriList->IsEmpty())
	{
		CTriangle* pTri = (CTriangle*)pTriList->RemoveHead();  //Elem
		/////////////////////////////////////////////
		if(pTri)
		{
/*
			CDListMgr* pNodeList = pObject->GetNodeList();
			while(!pNodeList->IsEmpty())
			{
				CDrObject* pNode = (CDrObject*)pNodeList->RemoveHead(); //Node
				int index = pNode->GetElemList()->GetObjectIndex(pObject);
				if(index>=0)
					pNode->GetElemList()->RemoveObject(index); //Elem
			}
*/
			///////////////////////// index List	
			CList<int,int>* pIndexList = pTri->GetCNIndexList();
			while(!pIndexList->IsEmpty())
				pIndexList->RemoveHead(); //Index
			/////////////////////////
		}
		//////////
	    delete pTri;
	}
	/////////////////////////////////////////////////////////////
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	/////////////////////////////////////////////////////////////
	while(!(GetObj3DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetObj3DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	/////////////////////////////////////
}
   
int CDrPatch::DealObjectDialog()
{
/*
	CDrPatchProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrPatch::SetObjectInfo(CDrObject* pObject)
{
	
	CDrCurve::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrPatch* pAdd = (CDrPatch*) pObject;
	//////////////////////////////////////////////////////// PATCHINFO	
	m_bNormalDraw		= pAdd->m_bNormalDraw;			
	m_PatchProc			= pAdd->m_PatchProc;
	m_PatchType			= pAdd->m_PatchType;
	m_PatSubType		= pAdd->m_PatSubType;
	m_CurveType_T		= pAdd->m_CurveType_T;
	m_b2D				= pAdd->m_b2D;
	//////////////////////////////////////////////////////// CopyList
//	if(!(pAdd->m_SolidList.IsEmpty()) )
//		m_SolidList.AddTail(&(pAdd->m_SolidList) ); 
	if(!(pAdd->m_CurveList.IsEmpty()) )
		m_CurveList.AddTail(&(pAdd->m_CurveList) ); 
    ///////////////////////////
	m_nSegUnif_T		= pAdd->m_nSegUnif_T;
	m_bClosed_T			= pAdd->m_bClosed_T;
	m_nMaxINodes_T		= pAdd->m_nMaxINodes_T;
	m_nMaxCNodes_T		= pAdd->m_nMaxCNodes_T;
	m_nMaxCurves_S		= pAdd->m_nMaxCurves_S;
	m_nMaxCurves_T		= pAdd->m_nMaxCurves_T;
	m_nPatchObjectType	= pAdd->m_nPatchObjectType;
	//////////////////////////////////////// 
    for(int i = 0; i<4; i++)              // 
    {
    	m_CurveID[i]	= pAdd->m_CurveID[i];
    	m_CuLatch[i]	= pAdd->m_CuLatch[i];
    }	 
   	m_nSegs_T			= pAdd->m_nSegs_T;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	m_FromPtLocal_T		= pAdd->m_FromPtLocal_T;
	m_FromPtWorld_T		= pAdd->m_FromPtWorld_T;
	m_FromPtEye_T		= pAdd->m_FromPtEye_T;
	m_ToPtLocal_T		= pAdd->m_ToPtLocal_T;
	m_ToPtWorld_T			= pAdd->m_ToPtWorld_T;
	m_ToPtEye_T			= pAdd->m_ToPtEye_T;	
	m_dLen_T				= pAdd->m_dLen_T;
	m_dLenEye_T			= pAdd->m_dLenEye_T;
	m_vAxis_T				= pAdd->m_vAxis_T;	
	m_vAxisEye_T			= pAdd->m_vAxisEye_T;	
	/////////////////////
	m_FromID_T			= pAdd->m_FromID_T;
	m_ToID_T				= pAdd->m_ToID_T;
	/////////////////////////////////////////// Rotate
	m_dAng_1_T			= pAdd->m_dAng_1_T;
	m_dAng_2_T			= pAdd->m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	m_bIncTwist_T		= pAdd->m_bIncTwist_T;	// Incremental?
	m_bIncScale_T		= pAdd->m_bIncScale_T;	// for Sweep
	m_TwistMult_T		= pAdd->m_TwistMult_T;
	m_ScaleMult_T		= pAdd->m_ScaleMult_T;	// for Sweep
	m_TwistStart_T		= pAdd->m_TwistStart_T;
	m_ScaleStart_T		= pAdd->m_ScaleStart_T;	// for Sweep
	m_nOut_S			= pAdd->m_nOut_S;		
	m_nOut_T			= pAdd->m_nOut_T;		
    ////////////////////////////////////// Memory
    for(i = 0; i<4; i++)              // 
    {
    	m_pIn_S[i]	= pAdd->m_pIn_S[i];
    }	 
	//////////////////////
	m_nSubDiv			= pAdd->m_nSubDiv;
	m_nOrient			= pAdd->m_nOrient;
	////////////////////////////////////// NoOfElems
	m_nTotElems			= pAdd->m_nTotElems;
	m_OutMethod_T		= pAdd->m_OutMethod_T;		// Output Method
	m_bUniform_T		= pAdd->m_bUniform_T;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	m_nMaxOutPts_T		= pAdd->m_nMaxOutPts_T;
	m_nMaxOutSeg_T		= pAdd->m_nMaxOutSeg_T;		// Number of Output Segments on ENTIRE Curve in T
	m_pNum_t_T			= pAdd->m_pNum_t_T;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	m_pDis_t_T			= pAdd->m_pDis_t_T;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	m_pDis_Ang_T		= pAdd->m_pDis_Ang_T;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	m_pNum_t_Ex_T		= pAdd->m_pNum_t_Ex_T;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	m_nOrder_T			= pAdd->m_nOrder_T;			// k 
	m_nDim_T			= pAdd->m_nDim_T;			// 4 = RATIONAL/	3 = NONrational 
/*	
	int			m_nData_T;				// GIVEN: # of Data 		= m_nMaxINodes_S  
//	int			m_nSeg_DT_T;			// L = #of CurveSegments 	= m_nMaxCurves 
//	int			m_nSeg_BS_T;			// n
	int			m_nCon_BS_T; 			// n + 1: #of Spline Controls// for drawing ControlNet
	int			m_nMKnots_T;			// n + k + 1 = Total		// Not Need
	int			m_nKnots_T;				// n - k + 3 = distinct		// User Need
//	int			m_nCon_BZ_T;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	int 		m_nDim_T;				// 4 = RATIONAL/	3 = NONrational 
	WEIGHT		m_WtType_T;
	KNOT		m_KnotType_T;
	BOUNDARY	m_BCL_T;
	BOUNDARY	m_BCR_T;
	VECTOR		m_TanL_T;
	VECTOR		m_TanR_T;
	////////////////////// Memory for Interpolation
	pDOUBLE		m_pMKnots_T;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pDOUBLE		m_pWts_BS_T;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	pWORLD		m_pCon_BS_T;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		m_pKnot_T; 	// distinct( for User Need)
	pDOUBLE		m_pWts_DT_T;	// for User Need
	pDOUBLE		m_pWts_BZ_T;
//	pWORLD 		m_pCon_BZ;	// stored in m_CNodeList
*/
	//////////////////////////////////////////////////////////////////// CONICS
	m_nData_Ex_T		= pAdd->m_nData_Ex_T;	// GIVEN: # of Data 		= m_nMaxINodes_S  
	m_bExpanded_T		= pAdd->m_bExpanded_T;	
	m_nMaxENodes_T		= pAdd->m_nMaxENodes_T;
	m_Center_T			= pAdd->m_Center_T;	// Circle
	m_Normal_T			= pAdd->m_Normal_T;	
	m_Radius_T			= pAdd->m_Radius_T;
	m_Theta_T			= pAdd->m_Theta_T;
	m_SegAngle_T		= pAdd->m_SegAngle_T;
	//////////////////////////////////////////////////////////////////// Hole?
	m_bHole_T			= pAdd->m_bHole_T;
	//////////////////////////////////////////////////////////////////// Derivatives
	m_pTangents_T		= pAdd->m_pTangents_T;			// Tangents
	m_pCurvatures_T		= pAdd->m_pCurvatures_T;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    m_Ratio_T			= pAdd->m_Ratio_T;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	if(!(pAdd->m_TriangleList.IsEmpty()) )
		m_TriangleList.AddTail(&(pAdd->m_TriangleList) ); 
	//////////////////////////////  Globals:
	m_nOutGlo_S			= pAdd->m_nOutGlo_S;			//  Total Output in each side of entire Base Patch
/*
	int nSize = sizeof(CDrPatch);		
	BlockCopy((HUGEBLK)(pAdd),(HUGEBLK)(this),sizeof(CDrPatch)  );
	////////////////////////////////////////////// 
*/	
	///////////////////////////////////	
	return;
}		

void CDrPatch::GetObjectInfo(CDrObject* pObject)
{
	
	CDrCurve::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrPatch* pAdd = (CDrPatch*) pObject;
	//////////////////////////////////////////////////////// PATCHINFO	
	pAdd->m_bNormalDraw		= m_bNormalDraw;			
	pAdd->m_PatchProc		= m_PatchProc;
	pAdd->m_PatchType		= m_PatchType;
	pAdd->m_PatSubType		= m_PatSubType;
	pAdd->m_CurveType_T		= m_CurveType_T;
	pAdd->m_b2D				= m_b2D;
	//////////////////////////////////////////////////////// CopyList
//	if(!(m_SolidList.IsEmpty()) )
//		pAdd->m_SolidList.AddTail(&m_SolidList ); 
	if(!(m_CurveList.IsEmpty()) )
		pAdd->m_CurveList.AddTail(&m_CurveList ); 
    ///////////////////////////
	pAdd->m_nSegUnif_T		= m_nSegUnif_T;
	pAdd->m_bClosed_T		= m_bClosed_T;
	pAdd->m_nMaxINodes_T	= m_nMaxINodes_T;
	pAdd->m_nMaxCNodes_T	= m_nMaxCNodes_T;
	pAdd->m_nMaxCurves_S	= m_nMaxCurves_S;
	pAdd->m_nMaxCurves_T	= m_nMaxCurves_T;
	pAdd->m_nPatchObjectType= m_nPatchObjectType;
	//////////////////////////////////////// 
    for(int i = 0; i<4; i++)              // 
    {
    	pAdd->SetCurveID(m_CurveID[i],i);
    	pAdd->SetCurveLatch(m_CuLatch[i],i);
    }	 
   	pAdd->m_nSegs_T			= m_nSegs_T;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	pAdd->m_FromPtLocal_T	= m_FromPtLocal_T;
	pAdd->m_FromPtWorld_T	= m_FromPtWorld_T;
	pAdd->m_FromPtEye_T		= m_FromPtEye_T;
	pAdd->m_ToPtLocal_T		= m_ToPtLocal_T;
	pAdd->m_ToPtWorld_T		= m_ToPtWorld_T;
	pAdd->m_ToPtEye_T		= m_ToPtEye_T;	
	pAdd->m_dLen_T			= m_dLen_T;
	pAdd->m_dLenEye_T		= m_dLenEye_T;
	pAdd->m_vAxis_T			= m_vAxis_T;	
	pAdd->m_vAxisEye_T		= m_vAxisEye_T;	
	/////////////////////
	pAdd->m_FromID_T		= m_FromID_T;
	pAdd->m_ToID_T			= m_ToID_T;
	/////////////////////////////////////////// Rotate
	pAdd->m_dAng_1_T		= m_dAng_1_T;
	pAdd->m_dAng_2_T		= m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	pAdd->m_bIncTwist_T		= m_bIncTwist_T;	// Incremental?
	pAdd->m_bIncScale_T		= m_bIncScale_T;	// for Sweep
	pAdd->m_TwistMult_T		= m_TwistMult_T;
	pAdd->m_ScaleMult_T		= m_ScaleMult_T;	// for Sweep
	pAdd->m_TwistStart_T	= m_TwistStart_T;
	pAdd->m_ScaleStart_T	= m_ScaleStart_T;	// for Sweep
	pAdd->m_nOut_S			= m_nOut_S;		
	pAdd->m_nOut_T			= m_nOut_T;		
    ////////////////////////////////////// Memory
    for(i = 0; i<4; i++)              // 
    {
    	pAdd->SetMemIn(m_pIn_S[i],i);
    }	 
	//////////////////////
	pAdd->m_nSubDiv			= m_nSubDiv;
	pAdd->m_nOrient			= m_nOrient;
	////////////////////////////////////// NoOfElems
	pAdd->m_nTotElems		= m_nTotElems;
	pAdd->m_OutMethod_T		= m_OutMethod_T;		// Output Method
	pAdd->m_bUniform_T		= m_bUniform_T;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	pAdd->m_nMaxOutPts_T	= m_nMaxOutPts_T;
	pAdd->m_nMaxOutSeg_T	= m_nMaxOutSeg_T;		// Number of Output Segments on ENTIRE Curve in T
	pAdd->m_pNum_t_T		= m_pNum_t_T;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_t_T		= m_pDis_t_T;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_Ang_T		= m_pDis_Ang_T;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pAdd->m_pNum_t_Ex_T		= m_pNum_t_Ex_T;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	pAdd->m_nOrder_T		= m_nOrder_T;			// k 
	pAdd->m_nDim_T			= m_nDim_T;			// 4 = RATIONAL/	3 = NONrational 
/*	
	int			m_nData_T;				// GIVEN: # of Data 		= m_nMaxINodes_S  
//	int			m_nSeg_DT_T;			// L = #of CurveSegments 	= m_nMaxCurves 
//	int			m_nSeg_BS_T;			// n
	int			m_nCon_BS_T; 			// n + 1: #of Spline Controls// for drawing ControlNet
	int			m_nMKnots_T;			// n + k + 1 = Total		// Not Need
	int			m_nKnots_T;				// n - k + 3 = distinct		// User Need
//	int			m_nCon_BZ_T;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	int 		m_nDim_T;				// 4 = RATIONAL/	3 = NONrational 
	WEIGHT		m_WtType_T;
	KNOT		m_KnotType_T;
	BOUNDARY	m_BCL_T;
	BOUNDARY	m_BCR_T;
	VECTOR		m_TanL_T;
	VECTOR		m_TanR_T;
	////////////////////// Memory for Interpolation
	pDOUBLE		m_pMKnots_T;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pDOUBLE		m_pWts_BS_T;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	pWORLD		m_pCon_BS_T;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pDOUBLE		m_pKnot_T; 	// distinct( for User Need)
	pDOUBLE		m_pWts_DT_T;	// for User Need
	pDOUBLE		m_pWts_BZ_T;
//	pWORLD 		m_pCon_BZ;	// stored in m_CNodeList
*/
	//////////////////////////////////////////////////////////////////// CONICS
	pAdd->m_nData_Ex_T		= m_nData_Ex_T;	// GIVEN: # of Data 		= m_nMaxINodes_S  
	pAdd->m_bExpanded_T		= m_bExpanded_T;	
	pAdd->m_nMaxENodes_T	= m_nMaxENodes_T;
	pAdd->m_Center_T		= m_Center_T;	// Circle
	pAdd->m_Normal_T		= m_Normal_T;	
	pAdd->m_Radius_T		= m_Radius_T;
	pAdd->m_Theta_T			= m_Theta_T;
	pAdd->m_SegAngle_T		= m_SegAngle_T;
	//////////////////////////////////////////////////////////////////// Hole?
	pAdd->m_bHole_T			= m_bHole_T;
	//////////////////////////////////////////////////////////////////// Derivatives
	pAdd->m_pTangents_T		= m_pTangents_T;			// Tangents
	pAdd->m_pCurvatures_T	= m_pCurvatures_T;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    pAdd->m_Ratio_T			= m_Ratio_T;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	if(!(m_TriangleList.IsEmpty()) )
		pAdd->m_TriangleList.AddTail(&m_TriangleList ); 
	//////////////////////////////  Globals:
	pAdd->m_nOutGlo_S		= m_nOutGlo_S;			//  Total Output in each side of entire Base Patch
	///////////////////////////////////	
	return;
}		

void CDrPatch::Pack_drPipe(CString* pstrCard)
{

	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == PATCH) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
   	/////////////////////////
   	CString pad = " "; 
   	////////////////////////
//	m_PatchCard.bValve  = FALSE;  
   	AddStr(pstrCard,&name,5); 
   	AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}   

/////////////////////////////////////////////////////////////////
void CDrPatch::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	////////////////////
	if(!m_bDirty)
	{
		Calc_PolyNormalWorld();
		Calc_NodeNormalWorld();
		//////////////////
	}	
}
	
void CDrPatch::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
	if(!m_bDirty)
	{
		TransformPolyNormalToEye(pViewM);
		Calc_NodeNormalEye();
		return;
	}
	////////////////////////////////// Need to generate Patch
									// using XFormed CNodes
	else
	{									
	////////////////////////////////////// Need to generate Curves
									////// using XFormed CNodes
		RefillCNEyePosForDirtyDraw();		// for DirtyDraw
		////////////////////////////////// Output memory
		m_pOut		= FixMem(m_nOut);
		m_pOutWts	= FixMemD(m_nOut);
		////////////////////////////////
		if(m_PatSubType == PS_QUADRILAT)
			Generate_Patch4(m_pOut,m_pOutWts);
		if(m_PatSubType == PS_TRIANGLE)
			Generate_Patch3(m_pOut,m_pOutWts);
		///////////////////////////////
	}		
	
} 

BOOL CDrPatch::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	// Return if Object is Culled = TRUE/ Not Culled = FALSE
	if(nType == 1)
		return CullWorld(VDir);
	else
	if(nType == 2)
		return CullScreen(pViewM);
	else
		return FALSE;	// do nothing
}			 
				
void CDrPatch::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
	if(!m_bDirty)
	{
		ProjectPolyNormalToScreen3D(pvv3DM,dScale_U,dScale_V);
		Calc_NodeNormalScreen3D();
	}	
	///////////////////////
/*	
	///////////////// To draw all Bound Rect ////////// Later 
	Rearrange3DCorners(m_ptMinMaxL[0], m_ptMinMaxL[1]);		
	Rearrange3DCorners(m_ptMinMaxW[0], m_ptMinMaxW[1]);		
	Rearrange3DCorners(m_ptMinMaxS[0], m_ptMinMaxS[1]);
	/////////////////////////////////////////////////////////
*/
	//////////////////////////////////////////////////
	// 	2 Ways to Calc Screen Rect:					//
	//			a. Using CNodes Convex Hull			//
	//			b. Using Union of Polygonal Rects	//
	//	FOR NOW, We Will Use Method (a)				//
	//////////////////////////////////////////////////			
	Calc_ScreenRectFromCNodes();
	////////////////////////////////////////////////// If NOT POSTED
	if(!m_bDirty)
		return; 
	else
	{	
		/////////////////////////////////////////// Project for DirtyDraw	
//		ProjectForDirtyDraw(pvv3DM,dScale_U,dScale_V);      // DONE at GODOIT by DrawLine3D
		///////////////////
		return;
	}	
}

////////////////////////////////////////////////////////////
void CDrPatch::UnitAxisFromEndNodes()
{
	///////////////////////////////////////////// EyeVector
	m_vAxisEye_T.x = (m_ToPtEye_T.x - m_FromPtEye_T.x);  
	m_vAxisEye_T.y = (m_ToPtEye_T.y - m_FromPtEye_T.y);  
	m_vAxisEye_T.z = (m_ToPtEye_T.z - m_FromPtEye_T.z);  
	///////////////////////// Unit
	double NewD	= sqrt(	m_vAxisEye_T.x * m_vAxisEye_T.x +  
    					m_vAxisEye_T.y * m_vAxisEye_T.y +
    					m_vAxisEye_T.z * m_vAxisEye_T.z  );
	double r = 1.0/NewD;
	///////////////////////////// Unit vector
	m_vAxisEye_T.x *= r;  
	m_vAxisEye_T.y *= r;  
	m_vAxisEye_T.z *= r;
	///////////////////////////////////////////// LocalVector
	WORLD vAxis;
	vAxis.x = (m_ToPtLocal_T.x - m_FromPtLocal_T.x);  
	vAxis.y = (m_ToPtLocal_T.y - m_FromPtLocal_T.y);  
	vAxis.z = (m_ToPtLocal_T.z - m_FromPtLocal_T.z);  
	///////////////////////// Unit
	double OldD = sqrt(	vAxis.x * vAxis.x +  
    					vAxis.y * vAxis.y +
    					vAxis.z * vAxis.z);
	/////////////////////////    				
	double scale = NewD/OldD;
	m_dLenEye_T = m_dLen_T * scale;
	////////////////
} 
////////////////////////////////////////////////////////////
int CDrPatch::Generate_Patch3(pWORLD pOut, pDOUBLE pOutWts)	// Triangular Patches
{
	///////////////////
	CSurface3* pSurface;
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
    if( m_PatchType == PA_COONS)
    {
		//////////////////////////////////////////////////////////////////////
		nOutActual	= pSurface->Triangles_2D
				(
					m_OutMethod_T	//  Output Method
				,	&m_TriangleList	//	Patch Triangle List
				,	m_bClosed_S		//  IsClosed_S
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nSegUnif_S	//  Number of Output Segments in ALL Dir & ALL patches
				,	m_nMaxCNodes_S	//  number of Total CONTROL points: ALWAYS BEZIER
					//////////////////////////////  Globals:
				,	m_nOut_S		//  Total Output in each side of entire Patch
					//////////
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut			//  Total Output Points Array
				,	pOutWts			//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	nOut			//	expected number of generated Patch vertices	
				);
		////////////////////////////	
	}	
	else	
    if(m_PatchType == PA_GORDON)
    {
		AfxMessageBox("CDrPatch:\nGenerate_Patch3\nGORDON NOT IMPLEMENTED YET");
		return -1;
	}
	else
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGenerate_Patch3\nm_PatchType UNRECOGNIZED");
		return -1;
	}	
	////////////////////////////	
	if(nOutActual<0)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGenerate_Patch3\nnOutActual<0");
		return -1;
	}	
	////////////
	return 0;
	///////
}
			
int CDrPatch::Generate_Patch4(pWORLD pOut, pDOUBLE pOutWts)	// Quadrilateral Patches
{		
	///////////////////
	CSurface4* pSurface;
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
    if(m_PatchType == PA_TENSOR || m_PatchType == PA_COONS)
    {
		pINT pNum_t_S = (m_CurveType_S == CP_CIRCLE)?m_pNum_t_Ex_S:m_pNum_t_S;// Circle Special
		//todo for rotation:
		//pINT pNum_t_T = (m_CurveType_T == CP_CIRCLE)?m_pNum_t_S:m_pNum_t_Ex_T;// Circle Special
		//////////////////////////////////////////////////////////////////////
		nOutActual	= pSurface->TensorProduct_2D
				(
					m_OutMethod_T	//  Output Method
				,	m_bClosed_S		//  IsClosed_S
				,	m_nOrder_S-1	//  Degree in S-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_S	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_S	//  Total Number of Patches 
				,	  pNum_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_T		//  IsClosed_T
				,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_T		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_T	//  Total Number of Patches 
				,	m_pNum_t_T			//  Number of Output Segments Array in T-Dir for each patch
				,	m_pDis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut			//  Total Output Points Array
				,	pOutWts			//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	nOut			//	expected number of generated Patch vertices	
				);
		////////////////////////////	
	}	
	else	
    if(m_PatchType == PA_GORDON)
    {
		AfxMessageBox("CDrPatch:\nGenerate_Patch4\nGORDON NOT IMPLEMENTED YET");
		return -1;
	}
	else
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGenerate_Patch4\nm_PatchType UNRECOGNIZED");
		return -1;
	}	
	////////////////////////////	
	if(nOutActual != nOut)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGenerate_Patch4\nnOutActual != nOut");
		return -1;
	}	
	////////////
	return 0;
	///////
}	

BOOL CDrPatch::CullWorld(WORLD VDir)
{

	CDListMgr* pList;
	POSITION pos;
	BOOL bCulledPatch = TRUE,bCulled;
	//////////////////////
	pList = GetElemList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(!(pObject->GetObjectType() == FE2D) )
		{
			bCulledPatch = FALSE;
			continue;
		}	
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		bCulled = pPoly->CullWorld(VDir);
		///////////////////////////
		if(!bCulled)
			bCulledPatch = FALSE;
	}
	////////////////////////
	SetCulled(bCulledPatch);
	////////////////////
	return bCulledPatch;
	
}
				
BOOL CDrPatch::CullScreen(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	BOOL bCulledPatch = TRUE,bCulled;
	/////////////////////
	pList = GetElemList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(!(pObject->GetObjectType() == FE2D) )
		{
			bCulledPatch = FALSE;
			continue;
		}
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;	
		bCulled = pPoly->CullScreen(pViewM);
		///////////////////////////
		if(!bCulled)
			bCulledPatch = FALSE;
	}
	////////////////////
	return bCulledPatch;
	
}

void CDrPatch::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{

	MATRIX		LMP;	
	pMATRIX		pLMP = &LMP;	
	CDListMgr* pList;
	POSITION pos;
	///////////////////////////////
	BOOL	bYesOP,bYesP = FALSE;
	C3DMath	Math3D;
	Math3D.GetIdentityMATRIX(pLMP);
	//////////////////////////////
	if(IsInstanced())
	{	
		GetLocalTransform(pLMP);
		bYesP	= TRUE;
	}
	
	bYesOP	= bYes && bYesP;
	///////////////////////// 
	if(bYesOP)
	{	
		//////////////// Composite Transform
		Math3D.MultMATRIX(pLM,pLMP,pLMP);
	}
	else
	if(bYes)
	{
		pLMP 	= pLM;
		bYesOP 	= TRUE;
	}
	else
	 bYesOP = bYesP;
	//////////////////////////////////////////// Transform
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_WorldPos(pLMP,bYesOP);
			//////////////////////////////////
		}
	}
	/////////////////////////////////////// Control Nodes
	pList = GetCNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_WorldPos(pLMP,bYesOP);
			//////////////////////////////////
		}
	}	
	/////////////////////////////////////// Bounding Corners
	CXForm XForm;
	WORLD LocalPos;
	///////////////
	for (int i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetLocalCorner(&LocalPos, i);
		//////////////
		if(bYesOP)
			XForm.Transform(&LocalPos, &LocalPos, pLMP);
		/////////////////////////////	
		SetWorldCorner(&LocalPos, i);
		/////////////////////////////
	}	
	///////////////////////////////////////////////////// FromPt & ToPt
	if(bYesOP)
	{
		XForm.Transform(&m_FromPtLocal_T, &m_FromPtWorld_T,pLMP);
		XForm.Transform(&m_ToPtLocal_T, &m_ToPtWorld_T,pLMP);
	}
	else
	{
		m_FromPtWorld_T = m_FromPtLocal_T; 	
		m_ToPtWorld_T 	= m_ToPtLocal_T;
	}	 	
	////////////////////////////////////////////////
}

void CDrPatch::TransformToEyePos(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// View Transform
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_EyePos(pViewM);
			//////////////////////////////////
		}
	}	
	/////////////////////////////////////// Control Nodes
	pList = GetCNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->Calc_EyePos(pViewM);
			//////////////////////////////////
		}
	}	
	/////////////////////////////////////// Bounding Corners
	CXForm XForm;
	WORLD WorldPos;
	///////////////
	for (int i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetWorldCorner(&WorldPos, i);
		//////////////
		XForm.Transform(&WorldPos, &WorldPos,pViewM);
		/////////////////////////// 
		SetEyeCorner(&WorldPos, i);	
		///////////////////////////
	}
	///////////////////////////////////////////////////// FromPt & ToPt
	XForm.Transform(&m_FromPtWorld_T, &m_FromPtEye_T,pViewM);
	XForm.Transform(&m_ToPtWorld_T, &m_ToPtEye_T,pViewM);
	////////////////////////////////////////////////
}

void CDrPatch::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// Project 
/*	                                                            DONE AT ELEM LEVEL
	/////////////////////////////////////// Generated Nodes
	pList = GetNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->ProjectToScreenPos3D(pvv3DM);
			//////////////////////////////////
		}
	} 
*/	
	/////////////////////////////////////// Control Nodes        
	pList = GetCNodeList();
	//////////////////////
	if(!pList->IsEmpty())
	{
		////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			//////////////////////////////////
			pNode->ProjectToScreenPos3D(pvv3DM);
			//////////////////////////////////
		}
	}
	/////////////////////////////////////// Bounding Corners
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	POINT pt;
	///////////////
	for (int i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetEyeCorner(&EyePos, i);
		//////////////
		XForm.Project(pvv3DM,&EyePos, &ScreenPos);
		SetScreen3DCorner(&ScreenPos, i);
		//////////////////////////////////////////////////////
		// 	3DScreenPos belongs to [0,-1] because of CVV	//
		//	So before we Change into Integer Logical		//
		//	Coordinates, we Must Use Screen Client Data		//
		//////////////////////////////////////////////////////
		pt.x = (int)(ScreenPos.x * dScale_U);
		pt.y = (int)(ScreenPos.y * dScale_V);
		////
		SetScreen2DCorner(pt, i);
		/////////////////////////
	} 
	////////////////////////////////////////////// ElemBounds		
	pList = GetElemList();
	///////////////////////////////
	if(!pList->IsEmpty())
	{
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
			///////////////////////////
			if(!(pObject->GetObjectType() == FE2D) )
			{
				continue;
			}
			///////////////////////////
			pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
			/////////
		}
	}
}

void CDrPatch::Calc_ScreenRectFromPoly()
{

	CDListMgr*	pList;
	POSITION 	pos;
	CRect		BoundRect,theRect(0,0,0,0);	
	
	pList = GetElemList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(!(pObject->GetObjectType() == FE2D) )
			continue;
		/////////////////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
//		pPoly->Calc_ScreenRect(&BoundRect);
		BoundRect = pPoly->GetBoundingRect();
		BoundRect.NormalizeRect();
		BoundRect.UnionRect(&theRect,&BoundRect);
		/////////////////////////////////////
	}
	/////////////////////////// set
	m_rectBounding = BoundRect;
	///////////////////////////
}				

void CDrPatch::Calc_PolyNormalWorld()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE2D) )
			continue; 
		///////////////	
		CDrFE2D* pPoly = (CDrFE2D*) pObject;	
		//////////////////////////////////// Compute Centroid info 
		pPoly->Calc_CentroidWorld();
		//////////////////////////////////// Normal
		pPoly->Calc_NormalWorld();
		///////////////////////////
	}
}				

void CDrPatch::TransformPolyNormalToEye(pMATRIX pViewM)
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE2D) )
			continue;
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		if(pPoly->IsCulled())
			return;
		//////////////////////////////////// Compute Centroid info
		pPoly->Calc_CentroidEye();
		//////////////////////////////////// Normal	
		pPoly->TransformNormalToEye(pViewM);
		///////////////////////////
	}
}				

void CDrPatch::ProjectPolyNormalToScreen3D
			(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE2D) )
			continue;
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		if(pPoly->IsCulled())
			return;
		//////////////////////////////////// Compute Centroid info
		pPoly->Calc_CentroidScreen3D(dScale_U,dScale_V);
		///////////	
		pPoly->ProjectNormalToScreen3D
				(pvv3DM,dScale_U,dScale_V);
		///////////////////////////
	}
}				

void CDrPatch::Calc_NodeNormalWorld()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch Creation. We will do this later. todo		//
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetNodeList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
		///////////////////////////
		pNode->Calc_NormalWorld();
		///////////////////////////
	}
}				
void CDrPatch::Calc_NodeNormalEye()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch Creation. We will do this later. todo		//
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetNodeList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
		///////////////////////////
		pNode->Calc_NormalEye();
		///////////////////////////
	}
}				
void CDrPatch::Calc_NodeNormalScreen3D()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Patch Creation. We will do this later. todo		//
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetNodeList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
		///////////////////////////
		pNode->Calc_NormalScreen3D();
		///////////////////////////
	}
}				
///////////////////////////////////////////////////////////////
void CDrPatch::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

//////////////////////////////////////////////////////////////
void CDrPatch::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{ 
	m_bParallel		= bParallel;
    m_nView			= nView;
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX 
	///////////////////////////////////////////////////////////////// PreProcess
	////////////////////////////////////////////// Coordinates XForm
												// Local->World	  
	MATRIX LM;
	BOOL bXForm = FALSE;
	TransformObjectToWorld(&LM,bXForm);
	///////////////////////////////////////////
	TransformObjectToView(&m_ViewM); 
	ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
	///////////////////////////////////
//	FinishObject();//	calc Bounding Rect      DONE in ProjectObject 
	/////////////
}
						
//////////////////////////////////////////////////////////////
void CDrPatch::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

   	CPen    Pen;
   	CPen*   PtrOldPen;
	//////////////
	if(bPenChange)
		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
	else
		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
	//////////////////////////////////////
  	PtrOldPen = PtrDC->SelectObject(&Pen);
    ///////////////////////////////////////////// Draw
	if(m_PatSubType == PS_TRIANGLE)
	{
		////////////////
		GoDoIt_3(PtrDC);
		/////////////////////////////// Controls
		if(IsControlShapeNeeded())
			GoDoControlNodes_3(PtrDC);
		else
		{
			/////////////////////////////// FreeMemory
			FreeMem(m_pIn);
			m_pIn = NULL;
		}	
	}
	else
	if(m_PatSubType == PS_QUADRILAT)
	{
		////////////////
		GoDoIt(PtrDC);
		/////////////////////////////// Controls
		if(IsControlShapeNeeded())
			GoDoControlNodes(PtrDC);
		else
		{
			/////////////////////////////// FreeMemory
			FreeMem(m_pIn);
			m_pIn = NULL;
		}	
	}
	///////////////////////////////
	PtrDC->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
	////////////////////////////////
    
}                            

void CDrPatch::GoDoIt(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	int i,j,k,m,mold;
	//FOR ROTATION: T-dir = hoop/ S-dir = axial
	/////////////////////////////////////////
	for(i =0; i<m_nOut_T;i++)
	{
		k		= i * (m_nOut_S);
		mold	= k;
		///////////////////////////////
		for(j =1; j<m_nOut_S;j++)
		{
			m 	= k + j;
			/////////////////////////////////
			DrawLine3D(PtrDC,m_pOut+mold,m_pOut+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
			mold = m;
		}	
	}
	/////////////////////////////////////////
	for(i =0; i<m_nOut_S;i++)
	{
		mold 	= i;
		///////////////////////////////
		for(j =1; j<m_nOut_T;j++)
		{
			m = i + j*(m_nOut_S);
			/////////////////////////////////
			DrawLine3D(PtrDC,m_pOut+mold,m_pOut+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
			mold = m;
		}	
	}
/*	
	///////////////////////////////////////////// Show Pts
	for( i =0; i<=m_nOut;i++)
	{
		int x,y,len = 3;
		x = m_pOutDP[i].x;
		y = m_pOutDP[i].y;
		PtrDC->MoveTo(x-len,y);
		PtrDC->LineTo(x+len,y);
		PtrDC->MoveTo(x,y-len);
		PtrDC->LineTo(x,y+len);
	} 

*/		
	/////////////////////////////// FreeMemory
	FreeMem(m_pOut);
	FreeMemD(m_pOutWts);
	m_pOut		= NULL;   	
	m_pOutWts	= NULL;   	
   	
}

void CDrPatch::GoDoIt_3(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	CDListMgr* pTriList = GetTriangleList();
	if(pTriList->IsEmpty() )
		return;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So
	////////////////////////
	int nOutSeg_S	= GetSegmentCount_S();			
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		if(nType == 1)
			TRIANGLE_1(PtrDC,nOutSeg_S,iOutGlo,jOutGlo);
		else
		if(nType == 2)
			TRIANGLE_2(PtrDC,nOutSeg_S,iOutGlo,jOutGlo);
		else
		{
			//////////////////
			AfxMessageBox("CDrSolid::GoDoIt_PENTA\nnType !==1 or 2");
			return;
		}
	}										///////////////////////////// end LIST
	/////////////////////////////// FreeMemory
	FreeMem(m_pOut);
	FreeMemD(m_pOutWts);
	m_pOut		= NULL;   	
	m_pOutWts	= NULL;   	
   	
}

void CDrPatch::TRIANGLE_1(CDC* PtrDC,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST)
{ 

	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld;
	int iOut,jOut;
	//////////////////////////////////////////// u-dir
	for (j=0;j<nOutSeg_S;j++)
	{
		iOld = 0;
		//////
		for (m=0;m<nOutSeg_S-j;m++)
		{
			i		= iOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			i++;
			iOut	= iOutGlo_ST + i;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			iOld = i;
		}
	}
	///////////////////////////// v-dir
	for (i=0;i<nOutSeg_S;i++)
	{
		jOld = 0;
		//////
		for (m=0;m<nOutSeg_S-i;m++)
		{
			j		= jOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			j++;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			jOld = j;
		}
	}
	///////////////////////////// w-dir
	for (k=0;k<nOutSeg_S;k++)
	{
		iOld = 0;
		jOld = nOutSeg_S - k;
		//////
		for (m=0;m<nOutSeg_S-k;m++)
		{
			i = iOld;
			j = jOld;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			i++;
			j--;
			iOut	= iOutGlo_ST + i;
			jOut	= jOutGlo_ST + j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			iOld = i;
			jOld = j;
		}
	}
/////////////////////////////////////////////////////////////////// Parallel Sides
// TODO
}									

void CDrPatch::TRIANGLE_2(CDC* PtrDC,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST)
{ 

	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld;
	int iOut,jOut;
	//////////////////////////////////////////// u-dir
	for (j=0;j<nOutSeg_S;j++)
	{
		iOld = 0;
		//////
		for (m=0;m<nOutSeg_S-j;m++)
		{
			i		= iOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			i++;
			iOut	= iOutGlo_ST - i;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			iOld = i;
		}
	}
	///////////////////////////// v-dir
	for (i=0;i<nOutSeg_S;i++)
	{
		jOld = 0;
		//////
		for (m=0;m<nOutSeg_S-i;m++)
		{
			j		= jOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			j++;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			jOld = j;
		}
	}
	///////////////////////////// w-dir
	for (k=0;k<nOutSeg_S;k++)
	{
		iOld = 0;
		jOld = nOutSeg_S - k;
		//////
		for (m=0;m<nOutSeg_S-k;m++)
		{
			i = iOld;
			j = jOld;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L1 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			i++;
			j--;
			iOut	= iOutGlo_ST - i;
			jOut	= jOutGlo_ST - j;
			//////////////////////////////////// Barycentric to Linear: Global
			L2 = BARY2LIN_PT(iOut,jOut,m_nOut_S);
			////
			DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
			////
			iOld = i;
			jOld = j;
		}
	}
/////////////////////////////////////////////////////////////////// Parallel Sides
// TODO
}									

void CDrPatch::GoDoControlNodes(CDC* PtrDC)
{ 
	// index = index of curve, because there are different curves
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	// Create Red Pen for Node
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,RGB(255,0,0)); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////	
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Control Nodes in EYE Coordinates
	int i,j,k,m,mold;
	//FOR ROTATION: T-dir = hoop/ S-dir = axial
	/////////////////////////////////////////
	for(i =0; i<m_nMaxCNodes_T;i++)
	{
		k	 = i * (m_nMaxCNodes_S);
		mold = k;
		///////////////////////////////
		for(j =1; j<m_nMaxCNodes_S;j++)
		{
			m = k + j;
			/////////////////////////////////
			DrawLine3D(PtrDC,m_pIn+mold,m_pIn+m,TRUE);// TRUE = XFormed; FALSE = WORLD
			mold = m;
		}	
	}
	/////////////////////////////////////////
	for(i =0; i<m_nMaxCNodes_S;i++)
	{
		mold 	= i;
		///////////////////////////////
		for(j =1; j<m_nMaxCNodes_T;j++)
		{
			m = i + j*(m_nMaxCNodes_S);
			/////////////////////////////////
			DrawLine3D(PtrDC,m_pIn+mold,m_pIn+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
			mold = m;
		}	
	}
/*		 
	///////////////////////////////////////////// Show Pts
		int nMaxCNodes = m_nMaxCNodes_S * m_nMaxCNodes_T; 
		for( i =0; i<= nMaxCNodes;i++)
		{
			int x,y,len = 3;
			x = m_pInDP[i].x;
			y = m_pInDP[i].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		} 
	}
*/		
	/////////////////////////////// FreeMemory
	FreeMem(m_pIn);
	m_pIn = NULL;   	
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
}

void CDrPatch::GoDoControlNodes_3(CDC* PtrDC)
{ 
	// index = index of curve, because there are different curves
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	// Create Red Pen for Node
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,RGB(255,0,0)); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////	
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Control Nodes in EYE Coordinates
	/////////////////////////////// FreeMemory
	FreeMem(m_pIn);
	m_pIn = NULL;   	
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
}

int CDrPatch::NumberOfPatches()
{
					
	/////////////////////// Compute No. of Patches in S & T direction
	CSurface4* pSurface;
	int nPatches_S,nPatches_T,nOut_S,nOut_T;
	//////////////			A L W A Y S   B E Z I E R		/////////////
	int nPatTotal = pSurface->NumberOfPatches(
						CP_BEZIER,m_nMaxCNodes_S,m_nSegUnif_S,m_bClosed_S,m_nOrder_S,
						CP_BEZIER,m_nMaxCNodes_T,m_nSegUnif_T,m_bClosed_T,m_nOrder_T,
						&nPatches_S,&nPatches_T,&nOut_S,&nOut_T);
    //////////////////////////////// Save
	m_nMaxCurves_S 		= nPatches_S;
	m_nMaxCurves_T 		= nPatches_T;
/*
	m_nOut_S			= nOut_S;				
	m_nOut_T			= nOut_T;				
	m_nOut				= (long)(nOut_S * nOut_T);
	//////////////////////////////////////////////
	if(nPatTotal != (int)m_nOut )
		return -1;
	return nPatTotal;
*/
	//////////////	
	return m_nOut;
						
}

int CDrPatch::NumberOfElements(UINT nPatchType,int nElemType)
{
/*
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CDrPatch* 	pDrCurve;
	int 		index,i;
	CString 	CurveID;
	long 		nVerts,nEdges,nFaces;
	////////////////////////
	if(nPatchType == P_MESH)
	////////////////////////
	{

		///////////////////////////////
		m_nOut_S			= GetMaxOutPts_S();
		m_nOut_T			= GetMaxOutPts_T();
		m_nOut				= (long)(m_nOut_S * m_nOut_T); 
		///////////////////////////////
//		nOut = m_nOut;
	}
	///////////////////////////////////////////////
	if(nPatchType == P_DUCT||nPatchType == P_SWEEP)
	///////////////////////////////////////////////
	{ 
		for(i =0;i<2;i++)
		{
			////////////////////////////////////// get Curve Info	
   			CurveID = GetCurveID(i);	// XSection
   			/////////////////////////
			index	= pObjectMgr->
						GetObjectIndexfromKey(CURVE,CurveID,1);
			if(index>=0)
			{						
				pDrCurve = (CDrPatch*)(pDListMgr->GetObject(index));
				if(pDrCurve)
				{
					if(i==0)    // XSection
						m_nOut_S = pDrCurve->GetMaxOutPts();
					else
					if(i==1)	// Spine
						m_nOut_T = pDrCurve->GetMaxOutPts();
				}
			}			
		}	
		m_nOut = (((long)m_nOut_S)*((long)m_nOut_T) );
		///////////////////////////////////////
	}				
	////////////////////////
	if(nPatchType == P_LOFT)
	////////////////////////
	{ 
		m_nOut_S	= GetSegs() + 1;
		////////////////////////////////////// get Curve Info	
		CurveID = GetCurveID(0);			// 1 of the Curves
		/////////////////////////
		index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);
		if(index>=0)
		{						
			pDrCurve = (CDrPatch*)(pDListMgr->GetObject(index));
			if(pDrCurve)
			{
				m_nOut_T = pDrCurve->GetMaxOutPts();
			}			
		}	
		m_nOut = (((long)m_nOut_S)*((long)m_nOut_T) );
		///////////////////////////////////////
	}				
	///////////////////////////////////////////////////
	if(nPatchType == P_ROTATE||nPatchType == P_EXTRUDE)
	///////////////////////////////////////////////////
	{ 
		m_nOut_T	= GetSegs() + 1;
		////////////////////////////////////// get Curve Info	
		CurveID = GetCurveID(0);	// 1 of the Curves
		/////////////////////////
		index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);
		if(index>=0)
		{						
			pDrCurve = (CDrPatch*)(pDListMgr->GetObject(index));
			if(pDrCurve)
			{
				m_nOut_S = pDrCurve->GetMaxOutPts();
			}			
		}	
		m_nOut = (((long)m_nOut_S)*((long)m_nOut_T) ); 
		////////////////////////////////////////
	}				
	////////////////////////////////////////////////////
	//			 Now Compute No. of Elements          //
	// based on whether:                              //
	//		1.LineType Element i.e., Pipe,Beam etc.   //
	//		2.RectFace Element i.e., Plate etc.       //
	//		3.TriangleFace "                          //
	// 			THESE ARE ESTIMATE ONLY				  //
	//			These may CHANGE because of:		  //	
	//				FLATNESS TEST CRITERIA            //
	//			    SUBDIVISION                       //
	////////////////////////////////////////////////////
	nVerts = m_nOut;
	nEdges = ( ((long)(m_nOut_S-1))* (long)m_nOut_T) +
		 	 ( ((long)(m_nOut_T-1))* (long)m_nOut_S);
	nFaces = nEdges - nVerts + 1; 
	////////////////////////////////////////////////////	 		
	if(nElemType == 1) // Line Type (Edge Only)
		m_nTotElems = nEdges;
	else	
	if(nElemType == 2) // Plane Type (Rect Face)
		m_nTotElems = nFaces;
	else	
	if(nElemType == 3) // Plane Type (Triangular Face)
		m_nTotElems = nFaces*2;
	else
		return -1;
	//////////////
*/	
	return 0;		
}	
/////////////////////////////////////////////////////////////////////////////
BOOL CDrPatch::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrPatch* pDrPatch = (CDrPatch*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrPatch->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrPatch::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrPatch* pPatch = (CDrPatch*)pObject;
		///////////////////////////////////
		if(pPatch->GetObjectType() == PATCH)
		{
			CSize	Size; 
		/*	
			int nType = pLabel->GetType();
			///////////////////////////////////////// LeftTop Corner
			POINT pointTemp = pLabel->GetCorner(nType,nViewNumber);
	       	///////////////////////////////////////// LOG/Scaled
			pRect->left = pointTemp.x;
	    	pRect->top	= pointTemp.y;
	    	///////////////////////////////////////// get FontSize etc.
			CFont	Font;
			Font.DeleteObject;
			Font.CreateFontIndirect(&(pLabel->m_lf));
			CFont* pOldFont = (CFont*) ptrDC->SelectObject(&Font);
			Size		  = ptrDC->GetTextExtent(pLabel->m_Text,
											(pLabel->m_Text).GetLength());
			ptrDC->SelectObject(pOldFont);
			////////////////////////////////////////////////////////////
	    	pRect->right  = pRect->left + Size.cx; 
	    	pRect->bottom = pRect->top  - Size.cy; // Logical
	    	////////////////////////////// Assumed View12
	    	if((point.x>=pRect->left) && (point.x<=pRect->right) &&
	       		(point.y<=pRect->top ) && (point.y>=pRect->bottom)) 
	    	{
		       	return i; 
	    	}
	    	///////////////////
	    */	
		}
	///////////////
	return FALSE;
}
/*****************************************************************************
 *
 *	Function:	AppendToPatch()
 *
 *	Purpose:	Given an array of facets and an array of vertices, expands a
 *				specified patch appending new vertices and facets.
 *
 *****************************************************************************
 */ 
int CDrPatch::AppendToObject
				(
					CDListMgr* pObj3DList,
					CDListMgr* pSolidList, 
					CDListMgr* pCurveList, 
					CDListMgr* pElemList, 
					CDListMgr* pNodeList,
					CDListMgr* pCNodeList
				)
{							
	////////////////////
	if(pObj3DList && !(pObj3DList->IsEmpty()) )
		GetObj3DList()->AddTail(pObj3DList);
	else
		return -1;
	if(pSolidList && !(pSolidList->IsEmpty())  )
		GetSolidList()->AddTail(pSolidList);
	else
		return -1;
	if(pNodeList && !(pNodeList->IsEmpty())  )
		GetNodeList()->AddTail(pNodeList);
	else
		return -1;
	if(pCNodeList && !(pCNodeList->IsEmpty())  )
		GetCNodeList()->AddTail(pCNodeList);
	else
		return -1;
	if(pElemList && !(pElemList->IsEmpty()) )
		GetElemList()->AddTail(pElemList);
	else
		return -1;
	if(pCurveList && !(pCurveList->IsEmpty()) )
		GetCurveList()->AddTail(pCurveList);
	else
		return -1;
	///////////////
	return 0;	
}
/////////////////////////////////////////////////////////////////////////////
void CDrPatch::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	int nCount;     
	WORD	nElementType,nObjectNo,nObjectType,nPenWidth,nPenStyle,nLayer;
	DWORD   crPenColor;
	WORD	wCount;
	
	if (ar.IsStoring())
	{
		TRACE( " Patch   :Storing\n");	// TODO: add loading code here

		ar	<<	/*int*/		(WORD)m_nElemType	// Type = Patch = 2 in ElGlobal.h
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			///////////////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Patch Ends measured in MM_LOENGLISH units
			
			<<	/*UINT*/	(WORD)m_nPenWidth    // pen width for Pipe
			<<	/*COLORREF*/(DWORD)m_crPenColor
			<<	/*UINT*/	(WORD)m_nPenStyle 
			
			<<	/*UINT*/	(WORD)m_nLayer;
		/////////////////////////////////////////////// Lists
		UINT nCount = m_NodeList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_NodeList.Serialize(ar);	
		nCount = m_ElemList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_ElemList.Serialize(ar);
		////////////////////////////////////////////////		
		for(int i=0; i<MAX_NODES_CORNER;i++)	
			ar	<<	/*POINT*/	m_pt[i];



 	}
	else
	{
	
		TRACE( " Patch   :Loading\n");	// TODO: add loading code here


		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo 
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Patch Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
		  	>>	/*UINT*/	nPenWidth    // pen width for Pipe
			>>	/*COLORREF*/crPenColor
			>>	/*UINT*/	nPenStyle 
			>>	/*UINT*/	nLayer;
		/////////////////////////////////////////////// Lists
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_NodeList.Serialize(ar);	
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_ElemList.Serialize(ar);
		////////////////////////////////////////////////		
		for(int i=0; i<MAX_NODES_CORNER;i++)	
			ar	>>	/*POINT*/	m_pt[i];

    //////////////////////////////////////////////    
	m_nElemType		  	= 	(int)nElementType;		// Type = Patch = 2 in ElGlobal.h

    m_nObjectType		= 	(int)nObjectType;
    m_nObjectNo			= 	(UINT)nObjectNo;
	m_nPenWidth 		=	(UINT)nPenWidth;    // pen width for Pipe
	m_crPenColor 		= 	(COLORREF)crPenColor;
	m_nPenStyle 		= 	(UINT)nPenStyle; 
	m_nLayer			=	(UINT)nLayer;
    //////////////////////////////////////////////        

	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////
						 		  		