// Curve.cpp : implementation file
//


#include "stdafx.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN
                  
/////////////////////
#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_Objs.h"
#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "3DMath.h" 
#include "XForm.h"
////////////////////// ElemObjs
#include "Def_IGen.h"
#include "Ext_Cur.h"
#include "DrNode.h"
/////////////////////
#include "Curve.h"
#include "Curve_1.h"
#include "Curve_2.h"
#include "Curve_3.h"
////////////////////

#include "DrCurve.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrCurve
IMPLEMENT_SERIAL(CDrCurve, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrCurve, CDrObject)
	//{{AFX_MSG_MAP(CDrCurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CDrCurve::CDrCurve()
{  
     //////////////////////////////	
    SetObjectType((int)CURVE);
    SetElemType((int)GENR_OBJECT);          //
	/////////////////////////////////
	m_nMeshElemDim		= 1;			// Formerly m_b2D
										// 0D = Node/1D = Grid or 2D = plate etc 
	//////////////////////////////////////////////
	m_bIso				= FALSE;
	m_IsoToID			= "";				// IsotoCurveID
	/////////////////////////
	m_nCompoType		= NODE;				// Node,CNode(Grid 0D) 
										// pipe,beam(Grid 1D) or BoundaryCondition Elem
										// Triangle/Rect(2D) for patch
										// Cube/thk.shell(3D)for solid
	m_ObjectID			= "";
	/////////////////////////										
	m_CurveType_S	= CP_LINEAR;
	/////////////////////////////////
	m_VNodeList.RemoveAll();       // Expanded   Nodes Pointers  needed for CONICS
	m_CN_BSList.RemoveAll();       // Control Nodes Pointers  needed for delete: B-Spline Control Net
	/////////////////////////
	m_nSegUnif_S		= -1;
	m_bClosed_S			= FALSE; 
	m_nMaxINodes_S		= -1;
	m_nMaxCNodes_S		= -1;			// INTERNALLY: WE ALWAYS STAY WITH  B E Z I E R
	m_nMaxCurves_S		= -1;			// Formerly: m_nMaxCurves	// No. of Curves
	///////////////////////////////////////////////////////////////////////////////////
	m_nCurveObjectType	= -1;		// ObjectType to create; -1 = no creation reqd
	m_bDirty			= TRUE;				// ObjectType NOT SAVED	
	m_bPosted			= FALSE;				// ObjectType NOT SAVED	
    m_bControlDraw		= FALSE;
    //////////////////////////////
	m_pIn				= NULL;
	m_pInWts			= NULL; // Output  Weights -World or Eye Pos for Rational
	m_pInDP				= NULL;
	m_pOut				= NULL;
	m_pOutWts			= NULL;
	m_pOutDP			= NULL;
	m_nOut				= 0;
	////////////////////////////////////////////////////////////////////////////////
	m_alfa_S			= 0.0;		// Cardinal Spline (Catmull-Rom Modified)	
	m_bias_S			= 0.0;		// beta
	m_tension_S			= 0.0;		// beta and hermite
	//////////////////////////////////////////////////////////////////////////////// Output
	m_OutMethod_S		= CO_HORNER;		// Output Method
	m_bUniform_S		= TRUE;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	m_nMaxOutPts_S		= 0;
	m_nMaxOutSeg_S		= 0;		// Number of Output Segments on ENTIRE Curve
	m_pNum_t_S			= NULL;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	m_pDis_t_S			= NULL;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	m_pNum_t_Ex_S		= NULL;		// Expanded Number of Outputs for each Output Segment
	m_pDis_Ang_S		= NULL;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_S+1
	m_pBSeg_Ex_S		= NULL;
	//////////////////////////////////////////////////////////////////////////////// Interpol
	m_Class_S			= 0;				// C0
	m_nOrder_S			= 1;				// k
	m_nData_S			= 0;				// GIVEN: # of Data= nData			= m_nMaxINodes_S  
//	m_nSeg_DT_S;			// L = #of CurveSegments= nData - 1	= m_nMaxCurves_S 
//	m_nSeg_BS_S;			// n
	m_nCon_BS_S			= 0; 			// L + k - 1 = nData + k - 2 = n + 1:
										// #of Spline Controls// for drawing ControlNet
	m_nMKnots_S			= 0;			// n + k + 1 = Total		// Not Need
	m_nKnots_S			= 0;				// n - k + 3 = distinct		// User Need
//	m_nCon_BZ_S;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	m_nDim_S			= 3;				// 4 = RATIONAL/	3 = NONrational 
	m_WtType_S			= WT_AUTO;
	m_KnotType_S		= KN_AUTO;
	m_BCL_S				= BC_AUTO;
	m_BCR_S				= BC_AUTO;
//	m_TanL_S			= ;
//	m_TanR_S			= ;
	////////////////////// Memory for Interpolation
	m_pMKnots_S			= NULL;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	m_pWts_BS_S			= NULL;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	m_pCon_BS_S			= NULL;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	m_pKnot_S			= NULL; 	// distinct( for User Need)
	m_pWts_DT_S			= NULL;	// for User Need
	m_pWts_BZ_S			= NULL;
//	m_pCon_BZ			= NULL;	// stored in m_CNodeList
	//////////////////////////////////////////////////////////////////// CONICS
	m_CircleType		= CIRCLE_BY_NO3;
	m_pFromIDNode_S			= NULL;		// also used:AnchorID for Sweep/Duct
	m_pToIDNode_S			= NULL;
	m_nData_Ex_S		= 0;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	m_bExpanded_S		= FALSE;
	m_nMaxENodes_S		= 0;
//	m_Center_S;	// Circle
//	m_Normal_S;	
//	m_Radius_S;
//	m_Theta_S;
//	m_SegAngle_S;
	//////////////////////////////////////////////// DrPipe Compatibility
	m_pCNode_CC			= NULL;		// Center CNode
	m_pCNode_TI			= NULL;		// Tangent Intersection CNode
	m_pCNode_CA			= NULL;		// CNode_A on Tangent
	m_pCNode_CB			= NULL;		// CNode_B on Tangent
	//////////////////////////////////////////////////////////////////// Hole?
	m_bHole_S			= FALSE;
	///////////////////////
	m_pTangents_S		= NULL;  
	m_pCurvatures_S		= NULL;
    //////////////////////////////////////////////////////////////////// Output
    m_Ratio_S			= 1.0;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Input Type: Normally = 1
	m_InputType			= 1;		// needed later for editing
	m_bArcType			= TRUE;			// needed later for editing
	///////////
	m_ElperSegList_S.RemoveAll();
	m_NodTopoList.RemoveAll();
	m_SuppCardList.RemoveAll();
	m_SuppList.RemoveAll();
	m_StaLCardList.RemoveAll();
	m_StaLList.RemoveAll();
	
} 

CDrCurve::~CDrCurve()
{  
    	
	m_NodTopoList.RemoveAll();
	m_ElperSegList_S.RemoveAll();
    //////////////////////////////	
	if(m_pIn)
	{
		FreeMem(m_pIn); 
		m_pIn	= NULL;
	}		
	if(m_pInDP)
	{
		FreeMemDP(m_pInDP);
		m_pInDP	= NULL;
	}		
	if(m_pOut)
	{
		FreeMem(m_pOut); 
		m_pOut	= NULL;
	}		
	if(m_pOutWts)
	{
		FreeMemD(m_pOutWts); 
		m_pOutWts = NULL;
	}		
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}		
	////////////////////// Memory for Interpolation
	if(m_pMKnots_S)
	{
		delete [] m_pMKnots_S;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
		m_pMKnots_S = NULL;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	
	}		
	if(m_pWts_BS_S)
	{
		delete [] m_pWts_BS_S;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
		m_pWts_BS_S = NULL;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
	}		
//	if(m_pCon_BS_S)
//	{
//		delete [] m_pCon_BS_S;		//---|-- RATIONAL or NONraional
//		m_pCon_BS_S = NULL;		//---|-- RATIONAL or NONraional
//	}		
	////////////////////////////////////////////////////////////////////
	if(m_pKnot_S)
	{
		delete [] m_pKnot_S; 	// distinct( for User Need)
		m_pKnot_S = NULL; 	// distinct( for User Need)
	}		
	if(m_pWts_DT_S)
	{
		delete [] m_pWts_DT_S;	// for User Need
		m_pWts_DT_S = NULL;	// for User Need
	}		
	if(m_pWts_BZ_S)
	{
		delete [] m_pWts_BZ_S;
		m_pWts_BZ_S = NULL;
	}		
//	if(m_pCon_BZ)
//	{
//		delete [] m_pCon_BZ;	// stored in m_CNodeList
//		m_pCon_BZ = NULL;	// stored in m_CNodeList
//	}
	/////////////////////////////
	if(m_pNum_t_S==m_pNum_t_Ex_S)
		m_pNum_t_Ex_S = NULL;
	/////////////////////////
	if(m_pNum_t_S)
	{
		delete [] m_pNum_t_S;
		m_pNum_t_S = NULL;
	}		
	if(m_pNum_t_Ex_S)
	{
		delete [] m_pNum_t_Ex_S;
		m_pNum_t_Ex_S = NULL;
	}		
	if(m_pTangents_S)
	{
		delete [] m_pTangents_S;
		m_pTangents_S = NULL;
	}		
	if(m_pCurvatures_S)
	{
		delete [] m_pCurvatures_S;
		m_pCurvatures_S = NULL;
	}
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////////
}

void CDrCurve::ReadyToDelete()
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
	CDListMgr* pNodeList;
	pNodeList = GetNodeList();
    //////////////////////////////////////
	CDrObject* pObject;
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //Node
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pCurveList = pObject->GetCurveList();
			int index = pCurveList->GetObjectIndex(this);
			if(index>=0)
				pCurveList->RemoveObject(index); //Curve
		/////////////////////////
		}
	//////////
	}
	///////////////////////////////////// 
	while(!(GetLabelList()->IsEmpty()))// delete:private
	{
		pObject = (CDrObject*)(GetLabelList()->RemoveHead());
		delete pObject;	//delete:private	
	}	
	////////////////////////////////////// unload CNodes/delete:private
	pNodeList = GetCNodeList();
    //////////////////////////////////////
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //CNode
		/////////////////////////////////////////////
		if(pObject && (pObject->GetLevelType() == LEVEL_GRAPA))
		{
			CDListMgr* pCurveList = pObject->GetCurveList();
		///////////////////////
			int index = pCurveList->GetObjectIndex(this);
			if(index>=0)
				pCurveList->RemoveObject(index); //curve
		/////////////////////////
		}
		else
			delete pObject;	// LEVEL_KIDDO
	//////////
	}
	////////////////////////////////////// unload INodes/No delete:public
	pNodeList = GetINodeList();
    //////////////////////////////////////
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //INode
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pCurveList = pObject->GetCurveList();
			int index = pCurveList->GetObjectIndex(this);
			if(index>=0)
				pCurveList->RemoveObject(index); //curve
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// unload VNodes/No delete:public
	pNodeList = GetVNodeList();
    //////////////////////////////////////
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //ENode
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pCurveList = pObject->GetCurveList();
			int index = pCurveList->GetObjectIndex(this);
			if(index>=0)
				pCurveList->RemoveObject(index); //curve
		/////////////////////////
		}
	//////////
	}
	///////////////////////////////////// unload 
	while(!(GetSuppList()->IsEmpty()))// unload/no delete Supports: public
	{
		pObject = (CDrObject*)(GetSuppList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	///////////////////////////////////// delete 
	while(!(GetElemList()->IsEmpty()))// unload/delete Elems:Auxiliary Controls: Center,Handle etc 
	{
		pObject = (CDrObject*)GetElemList()->RemoveHead();  //CNode
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pCurveList = pObject->GetCurveList();
			int index = pCurveList->GetObjectIndex(this);
			if(index>=0)
				pCurveList->RemoveObject(index); //curve
				/////////////////////////
		}
		//////////
	}
	/////////////////////////////////////	
	while(!(GetCProfList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetCProfList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	/////////////////////////////////////	
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	/////////////////////////////////////////////////////////////
	while(!(GetObj3DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetObj3DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	////////////////////////////////////// unload Support Expanded/delete:private
	while(!GetSuppCardList()->IsEmpty())
	{
		GetSuppCardList()->RemoveHead();  //Expanded Support
		//////////
	}
	////////////////////////////////////// unload Static Expanded/delete:private
	while(!GetStaLCardList()->IsEmpty())
	{
		GetStaLCardList()->RemoveHead();  //Expanded Static
		//////////
	}
	/////////////////////////////////////
}

int CDrCurve::DealObjectDialog()
{
/*
	CDrCurveProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrCurve::SetObjectInfo(CDrObject* pObject)
{
	int i;
	//////
	CDrObject::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrCurve* pAdd = (CDrCurve*) pObject;
	///////////////////////////////////////////////////////// CURVEINFO
	m_BezierType		= pAdd->m_BezierType;	
	m_nOut				= pAdd->m_nOut;
	m_nMeshElemDim		= pAdd->m_nMeshElemDim;
	//////////////////////////////////////////
	m_bIso				= pAdd->m_bIso;
	m_IsoToID			= pAdd->m_IsoToID;
	m_nCompoType		= pAdd->m_nCompoType;
	m_CompoID			= pAdd->m_CompoID;
	m_CurveType_S		= pAdd->m_CurveType_S;
	m_bSkewed			= pAdd->m_bSkewed;
	m_bLinSpr			= pAdd->m_bLinSpr;
	m_bLinSnu			= pAdd->m_bLinSnu;
    ///////////////////////////
	m_nSegUnif_S		= pAdd->m_nSegUnif_S;
	m_bClosed_S			= pAdd->m_bClosed_S;
	m_nMaxINodes_S		= pAdd->m_nMaxINodes_S;
	m_nMaxCNodes_S		= pAdd->m_nMaxCNodes_S;
	m_nMaxCurves_S		= pAdd->m_nMaxCurves_S;
	//////////////////
	m_nCurveObjectType	= pAdd->m_nCurveObjectType;
	m_bDirty			= pAdd->m_bDirty;	
	m_bPosted			= pAdd->m_bPosted;	
	m_bControlDraw		= pAdd->m_bControlDraw;	
	///////////////////////////////////	
	m_alfa_S			= pAdd->m_alfa_S;			// Cardinal Spline (Catmull-Rom Modified)	
	m_bias_S			= pAdd->m_bias_S;			// beta
	m_tension_S			= pAdd->m_tension_S;		// beta and hermite 
	//////////////////////////////////////////////////////////////////// Interpol
	m_OutMethod_S		= pAdd->m_OutMethod_S;		// Output Method
	m_bUniform_S		= pAdd->m_bUniform_S;		// Output Distribution:

	
	m_nMaxOutPts_S		= pAdd->m_nMaxOutPts_S;
	m_nMaxOutSeg_S		= pAdd->m_nMaxOutSeg_S;		// Number of Output Segments on ENTIRE Curve
	/////////////////////////////////////////
	m_nBSeg_Ex_S		= pAdd->m_nBSeg_Ex_S;
	m_pBSeg_Ex_S		= pAdd->m_pBSeg_Ex_S;
	/////////////////////////////////////////
	m_Class_S			= pAdd->GetClass_S();
	m_nOrder_S			= pAdd->m_nOrder_S;				// k
	m_nData_S			= pAdd->m_nData_S;				// GIVEN: # of Data= nData			= m_nMaxINodes_S  
//	m_nSeg_DT_S			= pAdd->m_nSeg_DT_S;			// L = #of CurveSegments= nData - 1	= m_nMaxCurves_S 
//	m_nSeg_BS_S			= pAdd->m_nSeg_BS_S;			// n
	m_nCon_BS_S			= pAdd->m_nCon_BS_S; 			// L + k - 1 = nData + k - 2 = n + 1:
										// #of Spline Controls// for drawing ControlNet
	m_nMKnots_S			= pAdd->m_nMKnots_S;			// n + k + 1 = Total		// Not Need
	m_nKnots_S			= pAdd->m_nKnots_S;				// n - k + 3 = distinct		// User Need
//	m_nCon_BZ_S			= pAdd->m_nCon_BZ_S;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	m_nDim_S			= pAdd->m_nDim_S;				// 4 = RATIONAL/	3 = NONrational 
	m_WtType_S			= pAdd->m_WtType_S;
	m_KnotType_S		= pAdd->m_KnotType_S;
	m_BCL_S				= pAdd->m_BCL_S;
	m_BCR_S				= pAdd->m_BCR_S;
	m_TanL_S			= pAdd->m_TanL_S;
	m_TanR_S			= pAdd->m_TanR_S;
	m_nData_Ex_S		= pAdd->m_nData_Ex_S;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	m_bExpanded_S		= pAdd->m_bExpanded_S;
	m_nMaxENodes_S		= pAdd->m_nMaxENodes_S;
	m_Center_S			= pAdd->m_Center_S;			// 
	m_Normal_S			= pAdd->m_Normal_S;	
	m_Radius_S			= pAdd->m_Radius_S;			// 
	m_Theta_S			= pAdd->m_Theta_S;			// 
	m_SegAngle_S		= pAdd->m_SegAngle_S;
	//////////																																	
	m_bHole_S			= pAdd->m_bHole_S;
    //////////////////////////////////////////////////////////////////// Output
    m_Ratio_S			= pAdd->m_Ratio_S;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Input Type: Normally = 1
	m_InputType			= pAdd->m_InputType;		// needed later for editing
	m_CircleType		= pAdd->m_CircleType;		// needed later for editing
	m_bArcType			= pAdd->m_bArcType;			// needed later for editing
    //////////////////////////////////////////////////////////////////////////////////////////////////////// POINTERS 
	m_pMKnots_S			= pAdd->m_pMKnots_S;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	m_pWts_BS_S			= pAdd->m_pWts_BS_S;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	m_pCon_BS_S			= pAdd->m_pCon_BS_S;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	m_pKnot_S			= pAdd->m_pKnot_S; 		// distinct( for User Need)
	//////////////////////////////////////////////////////////////////// CONICS
	m_pFromIDNode_S		= pAdd->m_pFromIDNode_S;		// also used:AnchorID for Sweep/Duct
	m_pToIDNode_S		= pAdd->m_pToIDNode_S;
	////////////////////////////////////////////////////////////////////////////////////////////////
	m_pWts_DT_S			= pAdd->m_pWts_DT_S;	// for User Need
	if(pAdd->m_pWts_BZ_S)
	{
		m_pWts_BZ_S = new double[m_nMaxCNodes_S];			
		for(i=0;i<m_nMaxCNodes_S;i++)
			(m_pWts_BZ_S)[i] = pAdd->m_pWts_BZ_S[i]; 
	}
//	m_pCon_BZ			= pAdd->m_pCon_BZ;	// stored in m_CNodeList
	////////////////////////////////////////////
	if(!(pAdd->m_ElperSegList_S.IsEmpty()) )
		m_ElperSegList_S.AddTail(&(pAdd->m_ElperSegList_S) );
	///////////////////////////////////////////// Output/seg
	if(pAdd->m_pNum_t_S)
	{
		m_pNum_t_S = new int[m_nMaxCurves_S];			
		for(i=0;i<m_nMaxCurves_S;i++)
			m_pNum_t_S[i] = pAdd->m_pNum_t_S[i]; 
	}
	if (m_nOrder_S == 2 && m_nMaxCurves_S == 1)
	{
		if(pAdd->m_pDis_t_S)
		{
			m_pDis_t_S = new double[m_nMaxOutSeg_S+1];			
			for(i=0;i<(m_nMaxOutSeg_S+1);i++)
				m_pDis_t_S[i] = pAdd->m_pDis_t_S[i];
		}	
	}
	if(m_CurveType_S == CP_CIRCLE)
	{
		if(pAdd->m_pNum_t_Ex_S)
		{
			m_pNum_t_Ex_S	= new int[m_nMaxCurves_S];			
			m_pDis_Ang_S	= new double[m_nMaxCurves_S];			
			for(i=0;i<m_nMaxCurves_S;i++)
			{
				m_pNum_t_Ex_S[i]	= pAdd->m_pNum_t_Ex_S[i]; 
				m_pDis_Ang_S[i]		= pAdd->m_pDis_Ang_S[i]; 
			}
		}
	}
	//////////////////////////////////////////////// DrPipe Compatibility
	m_pCNode_CC			= pAdd->m_pCNode_CC;		// Center CNode
	m_pCNode_TI			= pAdd->m_pCNode_TI;		// Tangent Intersection CNode
	m_pCNode_CA			= pAdd->m_pCNode_CA;		// CNode_A on Tangent
	m_pCNode_CB			= pAdd->m_pCNode_CB;		// CNode_B on Tangent
	//////////////////////////////////////////////////////////////////// Derivatives
	m_pTangents_S		= pAdd->m_pTangents_S;			// Tangents
	m_pCurvatures_S		= pAdd->m_pCurvatures_S;		// Curvatures
	///////////////////////////////////////////
	m_pIn				= pAdd->m_pIn;	
	m_pInWts			= pAdd->m_pInWts;	
	m_pInDP				= pAdd->m_pInDP; 	
	m_pOut				= pAdd->m_pOut;	
	m_pOutWts			= pAdd->m_pOutWts;	
	m_pOutDP			= pAdd->m_pOutDP; 
	//////////////////////////////////////////////////////// CopyList
	if(!(pAdd->m_SuppList.IsEmpty()) )
		m_SuppList.AddTail(pAdd->GetSuppList() ); 
	if(!(pAdd->m_StaLList.IsEmpty()) )
		m_StaLList.AddTail(pAdd->GetStaLList() ); 
	if(!(pAdd->m_BndryPtList.IsEmpty()) )
		m_BndryPtList.AddTail(&(pAdd->m_BndryPtList) ); 
	if(!(pAdd->m_SuppCardList.IsEmpty()) )
		m_SuppCardList.AddTail(&(pAdd->m_SuppCardList) ); 
	if(!(pAdd->m_StaLCardList.IsEmpty()) )
		m_StaLCardList.AddTail(&(pAdd->m_StaLCardList) ); 
	if(!(pAdd->m_NodTopoList.IsEmpty()) )
		m_NodTopoList.AddTail(&(pAdd->m_NodTopoList) ); 
	////////
	if(!(pAdd->m_LabelList.IsEmpty()) )
		m_LabelList.AddTail(&(pAdd->m_LabelList) ); 
	if(!(pAdd->m_SolidList.IsEmpty()) )
		m_SolidList.AddTail(&(pAdd->m_SolidList) ); 
	if(!(pAdd->m_VNodeList.IsEmpty()) )
		m_VNodeList.AddTail(&(pAdd->m_VNodeList) ); 
	if(!(pAdd->m_INodeList.IsEmpty()) )
		m_INodeList.AddTail(&(pAdd->m_INodeList) ); 
	if(!(pAdd->m_CNodeList.IsEmpty()) )
		m_CNodeList.AddTail(&(pAdd->m_CNodeList) ); 
	if(!(pAdd->m_CN_BSList.IsEmpty()) )
		m_CN_BSList.AddTail(&(pAdd->m_CN_BSList) ); 
	if(!(pAdd->m_NodeList.IsEmpty()) )
		m_NodeList.AddTail(&(pAdd->m_NodeList) ); 
	if(!(pAdd->m_ElemList.IsEmpty()) )
		m_ElemList.AddTail(&(pAdd->m_ElemList) );
	if(!(pAdd->m_PatchList.IsEmpty()) )
		m_PatchList.AddTail(&(pAdd->m_PatchList) ); 
	if(!(pAdd->m_Obj3DList.IsEmpty()) )
		m_Obj3DList.AddTail(&(pAdd->m_Obj3DList) ); 
	if(!(pAdd->m_CProfList.IsEmpty()) )
		m_CProfList.AddTail(&(pAdd->m_CProfList) ); 
	///////////////////////////////////////////////////////
	//////////																																	
	return;
}		

void CDrCurve::GetObjectInfo(CDrObject* pObject)
{
	int i;
	//////
	CDrObject::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrCurve* pAdd = (CDrCurve*) pObject;
    ///////////////////////////////////////////////////////////////// CURVE 
	pAdd->m_BezierType		= m_BezierType;	
	pAdd->m_nMeshElemDim	= m_nMeshElemDim;
	pAdd->m_nOut			= m_nOut;
	//////////////////////////////////////////
	pAdd->m_bIso			= m_bIso;
	pAdd->m_IsoToID			= m_IsoToID;
	pAdd->m_nCompoType		= m_nCompoType;
	pAdd->m_CompoID			= m_CompoID;
	pAdd->m_CurveType_S		= m_CurveType_S;
	pAdd->m_bSkewed			= m_bSkewed;
	pAdd->m_bLinSpr			= m_bLinSpr;
	pAdd->m_bLinSnu			= m_bLinSnu;
    ///////////////////////////
	pAdd->m_nSegUnif_S		= m_nSegUnif_S;
	pAdd->m_bClosed_S		= m_bClosed_S;
	pAdd->m_nMaxINodes_S	= m_nMaxINodes_S;
	pAdd->m_nMaxCNodes_S	= m_nMaxCNodes_S;
	pAdd->m_nMaxOutPts_S	= m_nMaxOutPts_S;
	pAdd->m_nMaxCurves_S	= m_nMaxCurves_S;
	////////////////////
	pAdd->m_nCurveObjectType= m_nCurveObjectType;
	pAdd->m_bDirty			= m_bDirty;	
	pAdd->m_bPosted			= m_bPosted;	
	pAdd->m_bControlDraw	= m_bControlDraw;	
	/////////////////////////////////
	pAdd->m_alfa_S			= m_alfa_S;			// Cardinal Spline (Catmull-Rom Modified)	
	pAdd->m_bias_S			= m_bias_S;			// beta
	pAdd->m_tension_S		= m_tension_S;		// beta and hermite
    //////////////////////////////////////////////////////////////////// output
	pAdd->m_OutMethod_S		= m_OutMethod_S;		// Output Method
	pAdd->m_bUniform_S		= m_bUniform_S;		// Output Distribution:
	pAdd->m_nMaxOutPts_S	= m_nMaxOutPts_S;
	pAdd->m_nMaxOutSeg_S	= m_nMaxOutSeg_S;	// Number of Output Segments on ENTIRE Curve
	/////////////////////////////////////////////
	pAdd->m_nBSeg_Ex_S		= m_nBSeg_Ex_S;
	pAdd->m_pBSeg_Ex_S		= m_pBSeg_Ex_S;
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	pAdd->m_Class_S			= GetClass_S();
	pAdd->m_nOrder_S		= m_nOrder_S;				// k
	pAdd->m_nData_S			= m_nData_S;				// GIVEN: # of Data= nData			= m_nMaxINodes_S  
//	pAdd->m_nSeg_DT_S		= m_nSeg_DT_S;			// L = #of CurveSegments= nData - 1	= m_nMaxCurves_S 
//	pAdd->m_nSeg_BS_S		= m_nSeg_BS_S;			// n
	pAdd->m_nCon_BS_S		= m_nCon_BS_S; 			// L + k - 1 = nData + k - 2 = n + 1:
										// #of Spline Controls// for drawing ControlNet
	pAdd->m_nMKnots_S		= m_nMKnots_S;			// n + k + 1 = Total		// Not Need
	pAdd->m_nKnots_S		= m_nKnots_S;				// n - k + 3 = distinct		// User Need
//	pAdd->m_nCon_BZ_S		= m_nCon_BZ_S;			// (k-1) * L + 1		 	= m_nMaxCNodes_S  		
	pAdd->m_nDim_S			= m_nDim_S;				// 4 = RATIONAL/	3 = NONrational 
	pAdd->m_WtType_S		= m_WtType_S;
	pAdd->m_KnotType_S		= m_KnotType_S;
	pAdd->m_BCL_S			= m_BCL_S;
	pAdd->m_BCR_S			= m_BCR_S;
	pAdd->m_TanL_S			= m_TanL_S;
	pAdd->m_TanR_S			= m_TanR_S;
	//////////////////////////////////////////////////////////////////// CONICS
	pAdd->m_nData_Ex_S		= m_nData_Ex_S;				// GIVEN: # of Data 		= m_nMaxINodes_S  
	pAdd->m_bExpanded_S		= m_bExpanded_S;
	pAdd->m_nMaxENodes_S	= m_nMaxENodes_S;
	pAdd->m_Center_S		= m_Center_S;			// 
	pAdd->m_Normal_S		= m_Normal_S;	
	pAdd->m_Radius_S		= m_Radius_S;			// 
	pAdd->m_Theta_S			= m_Theta_S;			// 
	pAdd->m_SegAngle_S		= m_SegAngle_S;
	//////////////////
	pAdd->m_bHole_S			= m_bHole_S;
    //////////////////////////////////////////////////////////////////// Output
    pAdd->m_Ratio_S			= m_Ratio_S;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Input Type: Normally = 1
	pAdd->m_InputType		= m_InputType;		// needed later for editing
	pAdd->m_CircleType		= m_CircleType;		// needed later for editing
	pAdd->m_bArcType		= m_bArcType;			// needed later for editing
    //////////////////////////////////////////////////////////////////////////////////////////////////////// POINTERS
	pAdd->m_pMKnots_S			= m_pMKnots_S;		//---|-- THESE ACTUALLY	- WE DO NOT NEED, OUR	
	pAdd->m_pWts_BS_S			= pAdd->m_pWts_BS_S;		//---|-- INTERNAL REPRESENTATION: ALWAYS --  B E Z I E R
//	m_pCon_BS_S					= pAdd->m_pCon_BS_S;		//---|-- RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	pAdd->m_pKnot_S				= pAdd->m_pKnot_S; 		// distinct( for User Need)
	//////////////////////////////////////////////////////////////////// CONICS
	pAdd->m_pFromIDNode_S		= pAdd->m_pFromIDNode_S;		// also used:AnchorID for Sweep/Duct
	pAdd->m_pToIDNode_S			= pAdd->m_pToIDNode_S;
	////////////////////////////////////////////////////////////////////////////////////////////////
	pAdd->m_pWts_DT_S	= m_pWts_DT_S;	// for User Need
	if(m_pWts_BZ_S)
	{
		pAdd->m_pWts_BZ_S = new double[m_nMaxCNodes_S];			
		for(i=0;i<m_nMaxCNodes_S;i++)
			(pAdd->m_pWts_BZ_S)[i] = m_pWts_BZ_S[i]; 
	}
	////////////////////////////////////////////
	if(!(m_ElperSegList_S.IsEmpty()) )
		pAdd->m_ElperSegList_S.AddTail(&m_ElperSegList_S);
	///////////////////////////////////////////// Output/seg
	if(m_pNum_t_S)
	{
		pAdd->m_pNum_t_S = new int[m_nMaxCurves_S];			
		for(i=0;i<m_nMaxCurves_S;i++)
			(pAdd->m_pNum_t_S)[i] = m_pNum_t_S[i]; 
	}
	if (m_nOrder_S == 2 && m_nMaxCurves_S == 1)
	{
		if(m_pDis_t_S)
		{
			pAdd->m_pDis_t_S = new double[m_nMaxOutSeg_S+1];			
			for(i=0;i<(m_nMaxOutSeg_S+1);i++)
				(pAdd->m_pDis_t_S)[i] = m_pDis_t_S[i];
		}	
	}
	if(m_CurveType_S == CP_CIRCLE)
	{
		if(m_pNum_t_Ex_S)
		{
			pAdd->m_pNum_t_Ex_S	= new int[m_nMaxCurves_S];			
			pAdd->m_pDis_Ang_S	= new double[m_nMaxCurves_S];			
			for(i=0;i<m_nMaxCurves_S;i++)
			{
				(pAdd->m_pNum_t_Ex_S)[i]	= m_pNum_t_Ex_S[i]; 
				(pAdd->m_pDis_Ang_S)[i]		= m_pDis_Ang_S[i];
			}	
		}
	}
	//////////////////////////////////////////////// DrPipe Compatibility
	m_pCNode_CC			= pAdd->m_pCNode_CC;		// Center CNode
	m_pCNode_TI			= pAdd->m_pCNode_TI;		// Tangent Intersection CNode
	m_pCNode_CA			= pAdd->m_pCNode_CA;		// CNode_A on Tangent
	m_pCNode_CB			= pAdd->m_pCNode_CB;		// CNode_B on Tangent
	//////////////////////////////////////////////////////////////////// Derivatives
	m_pTangents_S		= pAdd->m_pTangents_S;			// Tangents
	m_pCurvatures_S		= pAdd->m_pCurvatures_S;		// Curvatures
	///////////////////////////////////////////
	m_pIn				= pAdd->m_pIn;	
	m_pInWts			= pAdd->m_pInWts;	
	m_pInDP				= pAdd->m_pInDP; 	
	m_pOut				= pAdd->m_pOut;	
	m_pOutWts			= pAdd->m_pOutWts;	
	m_pOutDP			= pAdd->m_pOutDP; 
	//////////////////////////////////////////////////////// CopyList
	pAdd->m_SuppList.AddTail(GetSuppList() ); 
	pAdd->m_StaLList.AddTail(GetStaLList() ); 
	if(!(m_BndryPtList.IsEmpty()) )
		pAdd->m_BndryPtList.AddTail(&m_BndryPtList ); 
	if(!(m_SuppCardList.IsEmpty()) )
		pAdd->m_SuppCardList.AddTail(&m_SuppCardList ); 
	if(!(m_StaLCardList.IsEmpty()) )
		pAdd->m_StaLCardList.AddTail(&m_StaLCardList ); 
	if(!(m_NodTopoList.IsEmpty()) )
		pAdd->m_NodTopoList.AddTail(&m_NodTopoList ); 
	////////
	if(!(m_LabelList.IsEmpty()) )
		pAdd->m_LabelList.AddTail(&m_LabelList ); 
	if(!(m_SolidList.IsEmpty()) )
		pAdd->m_SolidList.AddTail(&m_SolidList ); 
	if(!(m_VNodeList.IsEmpty()) )
		pAdd->m_VNodeList.AddTail(&m_VNodeList ); 
	if(!(m_INodeList.IsEmpty()) )
		pAdd->m_INodeList.AddTail(&m_INodeList ); 
	if(!(m_CNodeList.IsEmpty()) )
		pAdd->m_CNodeList.AddTail(&m_CNodeList ); 
	if(!(m_CN_BSList.IsEmpty()) )
		pAdd->m_CN_BSList.AddTail(&m_CN_BSList ); 
	if(!(m_NodeList.IsEmpty()) )
		pAdd->m_NodeList.AddTail(&m_NodeList ); 
	if(!(m_ElemList.IsEmpty()) )
		pAdd->m_ElemList.AddTail(&m_ElemList );
	if(!(m_PatchList.IsEmpty()) )
		pAdd->m_PatchList.AddTail(&m_PatchList ); 
	if(!(m_Obj3DList.IsEmpty()) )
		pAdd->m_Obj3DList.AddTail(&m_Obj3DList ); 
	if(!(m_CProfList.IsEmpty()) )
		pAdd->m_CProfList.AddTail(&m_CProfList ); 
	////////////////////////////////////////////////////////
	//////////																																	
	return;
}		

void CDrCurve::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrCurve::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_CurveTypes;i++)
   		if(CuTypes[i].num == CURVE) 
   		{
   			name = CuTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
//	m_CurveCard.bValve  = FALSE;  
   AddStr(pstrCard,&name,5); 
   AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}
  
//void CDrCurve::Get_EndTangent(WORLD& tan,BOOL bBegin)
void CDrCurve::Get_EndTangent(WORLD& tan,BOOL bBegin,double dSameNessRatio)
{	
	int nResult = MA_OK;
	//////////////////////////////////////////////////// TanList,if Needed
	CDrNode*	pCNode;
	WORLD		wNodeCoord;
	////////////////
	if(bBegin)
		pCNode		= (CDrNode*)(GetCNodeList()->GetHead()); // Tangent_Beg
	else
		pCNode		= (CDrNode*)(GetCNodeList()->GetTail()); // Tangent_End
	//////////
	wNodeCoord	= *(pCNode->GetLocalPos());
	//
//	Get_TangentAtaNode(wNodeCoord,tan);
	Get_TangentAtaNode(wNodeCoord,tan,dSameNessRatio);
	////////
}
  
//void CDrCurve::Get_EndTangent_Vector(VECTOR& tan,BOOL bBegin)
void CDrCurve::Get_EndTangent_Vector(VECTOR& tan,BOOL bBegin,double dSameNessRatio)
{	
	int nResult = MA_OK;
	//////////////////////////////////////////////////// TanList,if Needed
	CDrNode*	pCNode;
	WORLD		wNodeCoord;
	WORLD		Tangent;
	////////////////
	if(bBegin)
		pCNode		= (CDrNode*)(GetCNodeList()->GetHead()); // Tangent_Beg
	else
		pCNode		= (CDrNode*)(GetCNodeList()->GetTail()); // Tangent_End
	//////////
	wNodeCoord	= *(pCNode->GetLocalPos());
	//
//	Get_TangentAtaNode(wNodeCoord,Tangent);
	Get_TangentAtaNode(wNodeCoord,Tangent,dSameNessRatio);
	// put
	tan.v[0] = Tangent.x;
	tan.v[1] = Tangent.y;
	tan.v[2] = Tangent.z;
	tan.v[3] = 0;
	////////
}
  
//void CDrCurve::Get_TangentAtaNode_Vector(WORLD wNodeCoord,VECTOR& tan)
void CDrCurve::Get_TangentAtaNode_Vector(WORLD wNodeCoord,VECTOR& tan,
												double dSameNessRatio)
{	
	//////////////////////////////////////////////////// TanList,if Needed
	WORLD		Tangent;
	//
//	Get_TangentAtaNode(wNodeCoord,Tangent);
	Get_TangentAtaNode(wNodeCoord,Tangent,dSameNessRatio);
	// put
	tan.v[0] = Tangent.x;
	tan.v[1] = Tangent.y;
	tan.v[2] = Tangent.z;
	tan.v[3] = 0;
	////////
}

/*****************************************************************************
 *
 *	Function:	Calc_3DBoundsLocal()
 *
 *	Purpose:	Calculates the 3d bounds(LOCAL) of a Curve
 *				using CONVEX HULL Property
 *				Called during Mouse Creation
 *
 *****************************************************************************
 */
int CDrCurve::Calc_3DBoundsLocal()
{

	//////////////////////
	CDListMgr*	pNodeList;
	//////////////////////	
	WORLD	dMin,dMax,Coords;
	dMin.x = DBL_MAX; 
	dMin.y = DBL_MAX; 
	dMin.z = DBL_MAX;
	 
	dMax.x = -DBL_MIN; 
	dMax.y = -DBL_MIN; 
	dMax.z = -DBL_MIN;
	///////////////////////////////////////////////////////////////////
	pNodeList = GetCNodeList();     // Control Nodes ( Convex Hull Property)
	///////////////////////////
	for (POSITION pos = pNodeList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pNodeList->GetNextObject(pos);
		///////////////////////
		Coords.x = pNode->GetLocalPos()->x; 				
		Coords.y = pNode->GetLocalPos()->y; 				
		Coords.z = pNode->GetLocalPos()->z; 				
		///////////////////////////////////// compare and adjust
		if(Coords.x<dMin.x) dMin.x = Coords.x; 				
		if(Coords.y<dMin.y) dMin.y = Coords.y; 				
		if(Coords.z<dMin.z) dMin.z = Coords.z;
		 				
		if(Coords.x>dMax.x) dMax.x = Coords.x; 				
		if(Coords.y>dMax.y) dMax.y = Coords.y; 				
		if(Coords.z>dMax.z) dMax.z = Coords.z;
		//////////////////////////////////// 				
	}
	////////////////////////
	SetLocalCorner(&dMin,0);
	SetLocalCorner(&dMax,1);
	////////////////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrCurve::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrCurve::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////////////////////////////////// If NOT POSTED
	if(!m_bDirty)
		return;
	////////////////////////////////////// Need to generate Curves
									////// using XFormed CNodes
	RefillCNEyePosForDirtyDraw();		// for DirtyDraw
	/////////////////////////////
	Gen_XFormedCurveForDirtyDraw();
	///////////////////////////////		
	
}

void CDrCurve::Gen_XFormedCurveForDirtyDraw()
{		
/*
	/////////////////////////////// Free Memory
	if(m_pOut)
	{
		FreeMem(m_pOut);
		m_pOut	= NULL;
	}
	if(m_pOutWts)
	{
		FreeMemD(m_pOutWts);
		m_pOutWts	= NULL;   	
	} 
*/	
	////////////////////////////////////// Output memory
	m_pOut = FixMem(GetLongOutPts());
//	if(m_nDim_S == 4)					// Rational
	m_pOutWts = FixMemD(GetLongOutPts());
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// generate Patch Pts
	int nOut		= (int)m_nOut;  // for now		 	   	
	int nOutActual	= GenerateCurve(m_pOut,m_pOutWts);
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
	    //////////////////////////////////////////
		sprintf(buf,"m_pOut:XFormed Output\nCDrCurve::Gen_XFormedCurveForDirtyDraw");
		AfxMessageBox(*str); // DLL=2 / SubRoutine=1
		///////////////////
		int j,k,L;
		L = (int)GetLongOutPts(); 
		j = sprintf(buf,"m_pOut[%d]\n     X        Y        Z\n",L);
		for(k=0;k<L;k++)
		{
		   j += sprintf( buf + j, "%7.1f %7.1f %7.1f\n", 
		   				m_pOut[k].x,m_pOut[k].y,m_pOut[k].z );
		}
		AfxMessageBox(*str); // DLL=2 / SubRoutine=1
	    ///////////////////
	    delete str;
	}	    
#endif				
	////////////////////////////	
	if(nOutActual != nOut)
		AfxMessageBox("Internal Problem:\nDrCurve:TransformObjectToView");
	////////////
	return;
	///////
}	

BOOL CDrCurve::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
	return FALSE;	// do nothing
}			 

				
void CDrCurve::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
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
	/////////////////////////////////////////// Project for DirtyDraw	
//	ProjectForDirtyDraw(pvv3DM,dScale_U,dScale_V);                         NOT NEEDED
	///////////////////
	return;
}

void CDrCurve::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{

	MATRIX		LMP;	
	pMATRIX		pLMP = &LMP;	
	CDListMgr* pList;
	POSITION pos;
	int nCount;
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
	pList	= GetNodeList();
	nCount	= pList->GetCount();
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
	pList	= GetCNodeList();
	nCount	= pList->GetCount();
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
}

void CDrCurve::TransformToEyePos(pMATRIX pViewM)
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
}

void CDrCurve::ProjectToScreenPos
					(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	CDListMgr* pList;
	POSITION pos;
	//////////////////////////////////////////// Project
/*                                                               // DONE AT ELEM LEVEL/AFTER CLIP
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
}

void CDrCurve::RefillCNEyePosForDirtyDraw()
{
	/////////////////////////////////////////
	CDListMgr* pList;
	WORLD 	EyePos;
	/////////////////////////////////////// Control Nodes
	pList = GetCNodeList();
	///////////////////////
	if(!pList->IsEmpty())
	{
		/////////////////////////////// Free Memory
		if(m_pIn)
		{
			FreeMem(m_pIn);
			m_pIn = NULL;
		}
		/////////////////////////////// Fix Memory
		m_pIn = FixMem((long)pList->GetCount());
		////////
		int i=0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
    		//////////////////////////////////////// NPC Pt.
    		EyePos = *(pNode->GetEyePos());
    		/////////////////////////////////
			m_pIn[i].x = EyePos.x;	  
			m_pIn[i].y = EyePos.y;  
			m_pIn[i].z = EyePos.z;
			/////////////////////////
			i++;
		}
	}	
}

void CDrCurve::RefillCNLocalPosForPosting()
{
	/////////////////////////////////////////
	CDListMgr* pList;
	WORLD 	LocalPos;
	/////////////////////////////////////// Control Nodes
	pList = GetCNodeList();
	///////////////////////
	if(!pList->IsEmpty())
	{
		int i,j;
		j = pList->GetCount();
		/////////////////////////////// Free Memory
		if(m_pIn)
		{
			FreeMem(m_pIn);
			m_pIn = NULL;
		}
		/////////////////////////////// Fix Memory
		m_pIn = FixMem((long)j);
		////////
		i=0;
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
    		//////////////////////////////////////// NPC Pt.
//    		LocalPos = *(pNode->GetWorldPos());
    		LocalPos = *(pNode->GetLocalPos());		// 012897
    		/////////////////////////////////
			m_pIn[i].x = LocalPos.x;	  
			m_pIn[i].y = LocalPos.y;  
			m_pIn[i].z = LocalPos.z;
			/////////////////////////
			i++;
		}
	}	
}
	
void CDrCurve::ProjectForDirtyDraw
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{
	///////////////////////////////////////////////////////////////
	//	NOT NEEDED: DONE at GODOIT & GODOCONTROL by DrawLine3D
	//	BUT NEEDED: for OBJECT HIT Calculation
	///////////////////////////////////////////////////////////////
//	AfxMessageBox("Should NOT be Called\nDRCURVE/PtrojectForDirtyDraw");
	////////////////////////////////////////////////////////////////////
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	////////////////////////////////////////////////// Project for
													// DirtyDraw	
	////////////////////////////////////////// Generated Pts
    for(long j = 0; j<m_nOut; j++)              
	{
    	EyePos.x = m_pOut[j].x;
    	EyePos.y = m_pOut[j].y;
    	EyePos.z = m_pOut[j].z;
		//////////////
		XForm.Project(pvv3DM,&EyePos, &ScreenPos);
		//////////////////////////////////////////////////////
		// 	3DScreenPos belongs to [0,-1] because of CVV	//
		//	So before we Change into Integer Logical		//
		//	Coordinates, we Must Use Screen Client Data		//
		//////////////////////////////////////////////////////
		m_pOutDP[j].x = (int)(ScreenPos.x * dScale_U);
		m_pOutDP[j].y = (int)(ScreenPos.y * dScale_V);
		/////////////////////////
	}		
}

void CDrCurve::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	Rearrange2DCorners();
	FinishObject();
	///////////////
}	

void CDrCurve::Rearrange3DCorners(pWORLD pMin, pWORLD pMax)
{ 

	//We want to reaarange  Min & Max
	////////////////////	
	double	temp;
	///////////////////
	if(pMin->x > pMax->x)     // 
	{
		temp 		= pMin->x;
		pMin->x 	= pMax->x;
		pMax->x 	= temp;
	}			 
	if(pMin->y > pMax->y)     // 
	{
		temp 		= pMin->y;
		pMin->y 	= pMax->y;
		pMax->y 	= temp;
	}			 
	if(pMin->z > pMax->z)     // 
	{
		temp 		= pMin->z;
		pMin->z 	= pMax->z;
		pMax->z 	= temp;
	}			 
	////////////
	return;
}

void CDrCurve::Rearrange2DCorners()
{ 

	//We want to reaarange as TopLeft(m_pt[0]) & RightBottom(m_pt[1]):Logical
	////////////////////	
	int	temp;
	///////////////////
	if(m_pt[0].x > m_pt[1].x)     // left > right: switch
	{
		temp 		= m_pt[0].x;
		m_pt[0].x 	= m_pt[1].x;
		m_pt[1].x 	= temp;
	}			 
	if(m_pt[0].y < m_pt[1].y)     // top < bottom: switch
	{
		temp 		= m_pt[0].y;
		m_pt[0].y 	= m_pt[1].y;
		m_pt[1].y 	= temp;
	}			 
	////////////
	return;
}

void CDrCurve::FinishObject()
{ 

	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
	m_rectBounding = CRect(m_pt[0].x, m_pt[0].y, m_pt[0].x, m_pt[0].y);

	for ( int i=1; i < MAX_NODES_CORNER; i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		m_rectBounding.left     = min(m_rectBounding.left, m_pt[i].x);
		m_rectBounding.right    = max(m_rectBounding.right, m_pt[i].x);
		m_rectBounding.top      = max(m_rectBounding.top, m_pt[i].y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, m_pt[i].y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Curve when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	///////
	return; 
	
} 
//////////////////////////////////////////////////////////////
void CDrCurve::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrCurve::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	if(bPenChange)
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
	else
   		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
  	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////// about tobe Deleted
	if(IsToBeDeleted())
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,RGB(255,255,255));	// WHITE
    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC);
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
	////////////////////////////////////////// Controls
	if(IsControlShapeNeeded())
		GoDoControlNodes(PtrDC);
	else
	{
		/////////////////////////////// FreeMemory
		FreeMem(m_pIn);
		m_pIn = NULL;
	}	
  	//////////////////////////////////////////
    
}                            


void CDrCurve::GoDoIt(CDC* PtrDC)
{ 

    ///////////////////////////////////////////////// Generated Nodes in Eye Coordinates
	if(!m_bDirty)
		return;
	///////////////////////
	if(m_nMeshElemDim == 1)
	{
		///////////////////////////////
		int iold =0;	
		/////////////////////////////////////////
		for(int i =1; i<(int)m_nOut;i++)
		{
			/////////////////////////////////
			DrawLine3D(PtrDC,m_pOut+iold,m_pOut + i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed 
			iold = i;
		}
	}
//	else
	///////////////////////////////////////////// 
//	if(m_nMeshElemDim == 0)
	{
   		CPen    Pen;
   		CPen*   PtrOldPen;                        
		/////////////////////////////////////////////////// 
   		Pen.CreatePen (PS_SOLID,0,RGB(255,255,255));	// white
  		PtrOldPen = PtrDC->SelectObject(&Pen);
		/////////////////////////////////////////// Memory
		if(m_pOutDP)
		{
			FreeMemDP(m_pOutDP);
			m_pOutDP= NULL;
		}		
		m_pOutDP 	= FixMemDP(m_nOut);		// Output Points
		/////////////////////////////////////////// Project for CurvePts	
		ProjectForDirtyDraw(&m_vv3DM,m_dScale_U,m_dScale_V);
		///////
		int i;
		///////////////////////////////////////////// Show Pts
		for( i =0; i<=m_nOut;i++)
		{
			int x,y,len = 2;
			x = m_pOutDP[i].x;
			y = m_pOutDP[i].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		}
		//////////
		if(m_pOutDP)
		{
			FreeMemDP(m_pOutDP);
			m_pOutDP = NULL;
		}		
		///////////////////////////////   	
   		PtrDC->SelectObject(PtrOldPen);   
   		Pen.DeleteObject(); 
	}
	/////////////////////////////// Free Memory
/*
	FreeMem(m_pOut);
	m_pOut	= NULL;
	FreeMemD(m_pOutWts);
	m_pOutWts	= NULL;   
*/	
}

void CDrCurve::GoDoControlNodes(CDC* PtrDC)
{ 

   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	// Create Red Pen for Node
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,RGB(255,0,0)); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
    ///////////////////////////////////////////////// Control Nodes	in EYE Coordinates
	if(!m_pIn)
		RefillCNEyePosForDirtyDraw();
	/////////////////////////////////
    int iold = 0;
	/////////////////////////////////////////
	for(int i =1; i<(int)m_nMaxCNodes_S;i++)
	{
		/////////////////////////////////
		DrawLine3D(PtrDC,m_pIn+iold,m_pIn+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iold = i;
	}
	if(m_bClosed_S)
		DrawLine3D(PtrDC,m_pIn + iold,m_pIn,TRUE);
	/////////////////////////////// Free Memory
/*
	FreeMem(m_pIn);
	m_pIn = NULL;
*/
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
}


int CDrCurve::NumberOfCurves(enum CURVEPROC kind,int nMaxCurveCNodes,
								int* pnCurves,BOOL bClosed,int nOrder)
{					
	/////////////////////// Compute No. of Curves
	CCurve Curve;
	///////////////////////
	return (Curve.NumberOfCurves(kind,nMaxCurveCNodes,pnCurves,m_bClosed_S,nOrder) );
	///////////////////
	return -1;
}	

int CDrCurve::GenerateCurve(pWORLD pOut, pDOUBLE pOutWts)
{
	///////////////////
	int nOutActual;
	////////////////////////////////////////////////////////////////////////////// CUBIC
	if	(m_nOrder_S == 4)// cubic
/*		
			(	m_CurveType_S == CU_HERMITE 		||m_CurveType_S == CU_BEZIER 		||
				m_CurveType_S == CU_BSPLINE 		||m_CurveType_S == CU_NUSPLINE		||
				m_CurveType_S == CU_NURB			||m_CurveType_S == CU_CATMULLROM	||
				m_CurveType_S == CU_CARDISPLINE		||m_CurveType_S == CU_HERMITE		||
				m_CurveType_S == CU_BETA)
			)
*/			
	{				 
		CCurve_3* pCurve;
		nOutActual = pCurve->GenerateCurve
			(
				m_OutMethod_S		// Output Method
			,	m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_S			// Number of Outputs for each Output Segment
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	pOutWts				// Total Output Wts Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			,	(int)m_nOut			// expected number of generated curve vertices
			);
	}
	////////////////////////////////////////////////////////////////////////////// QUADRATIC
	else
	if	(m_nOrder_S == 3) // Quadratic 
/*	
			(	m_CurveType_S == CU_CIRCLE		||m_CurveType_S == CU_QUADRATIC	||
				m_CurveType_S == CU_LAGQUAD		||m_CurveType_S == CU_NURBQUAD	||
				m_CurveType_S == CU_BEZIER		||m_CurveType_S == CU_NURB      ||
				m_CurveType_S == CU_PARABOLA	||m_CurveType_S == CU_ELLIPSE
			)
*/				
	{
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"BezierWts\nCDrCurve::GenerateCurve");
		AfxMessageBox(*str);
		///////////////////
		pDOUBLE Wts = GetpWts_BZ_S();
		//////////////////////////////////////////
		j = sprintf(buf,"BZ_Wts[%d]\n      Wts\n",m_nMaxCNodes_S);
		for(k=0;k<m_nMaxCNodes_S;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,	Wts[k] );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif
///////////////////////////
		CCurve_2* pCurve;
		if(m_CurveType_S == CP_CIRCLE)
		{
			nOutActual = pCurve->GenerateCurve
			(
				m_OutMethod_S		// Output Method
			,	m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_Ex_S		// Output t-distribution array
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	pOutWts				// Total Output Wts Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			,	(int)m_nOut			// expected number of generated curve vertices
			);
		}	
		else
		{
			nOutActual = pCurve->GenerateCurve
			(
				m_OutMethod_S		// Output Method
			,	m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_S			// Number of Outputs for each Output Segment
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	pOutWts				// Total Output Wts Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			,	(int)m_nOut			// expected number of generated curve vertices
			);
		}

	}
	////////////////////////////////////////////////////////////////////////////// LINEAR
	else
	if	(m_nOrder_S == 2) // Linear
/*		
			(	m_CurveType_S == CU_LINEAR	||m_CurveType_S == CU_BEZIER	||
				m_CurveType_S == CU_NURB	)
			)
*/			 
	{				 
		CCurve_1* pCurve;
		nOutActual = pCurve->GenerateCurve
			(
				m_OutMethod_S		// Output Method
			,	m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_S			// Number of Outputs for each Output Segment
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	pOutWts				// Total Output Wts Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			,	(int)m_nOut			// expected number of generated curve vertices
			);
	}
	////////////////////////////	
	if(nOutActual != (int)m_nOut)
		return -1;
	else
		return nOutActual;
}

int CDrCurve::Get_TangentAtaNode(WORLD wNodeCoord,WORLD& Tangent,double dSameNessRatio)
{
	int nResult = 0;
	////////////////
	CCurve* Curve;
	//////////////////////////////////////////////////////////////////////
	RefillCNLocalPosForPosting();
	/////////////////////////////
	nResult = Curve->GetTangentAtaNode(wNodeCoord,Tangent,
								m_nOrder_S-1,m_nMaxCurves_S,m_nMaxCNodes_S,m_nDim_S,
								m_pWts_BZ_S,m_pIn,dSameNessRatio);
	////////////////////////////	
	if(nResult<0)
	{
		AfxMessageBox("Internal Problem:\nCDrCurve:\nGet_TangentAtaNode");
		return -1;
	}	
	////////////
	return 0;
	///////
}	


int CDrCurve::GenerateTangent(pWORLD pOut)
{
	///////////////////
	int nOutActual;
	////////////////////////////////////////////////////////////////////////////// CUBIC
	if	(m_nOrder_S == 4 )// cubic
	{				 
		CCurve_3* pCurve;
		nOutActual = pCurve->MakeTangents
			(
				m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_S			// Number of Outputs for each Output Segment
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			);
	}
	////////////////////////////////////////////////////////////////////////////// QUADRATIC
	else
	if	(m_nOrder_S == 3) // Quadratic 
	{
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 2 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"BezierWts\nCDrCurve::GenerateCurve");
		AfxMessageBox(*str);
		///////////////////
		pDOUBLE Wts = GetpWts_BZ_S();
		//////////////////////////////////////////
		j = sprintf(buf,"BZ_Wts[%d]\n      Wts\n",m_nMaxCNodes_S);
		for(k=0;k<m_nMaxCNodes_S;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,	Wts[k] );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif
///////////////////////////
		CCurve_2* pCurve;

		if(m_CurveType_S == CP_CIRCLE)	// Rational Bezier
		{
			nOutActual = pCurve->MakeTangents
				(
					m_bClosed_S			// IsClosed for Redistribution
				,	m_nMaxCNodes_S		// number of CONTROL points
				,	m_pIn          		// Total CONTROL Points Array  
				,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
				,	m_pWts_BZ_S			// Bezier Rational Weights
				,	m_pNum_t_Ex_S			// Output t-distribution array
				,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
				,	pOut				// Total Output Points Array
				,	m_nMaxCurves_S		// Total Number of Cubic Curves 
				);
		}	
		else
		{
			nOutActual = pCurve->MakeTangents
				(
					m_bClosed_S			// IsClosed for Redistribution
				,	m_nMaxCNodes_S		// number of CONTROL points
				,	m_pIn          		// Total CONTROL Points Array  
				,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
				,	m_pWts_BZ_S			// Bezier Rational Weights
				,	m_pNum_t_S			// Output t-distribution array
				,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
				,	pOut				// Total Output Points Array
				,	m_nMaxCurves_S		// Total Number of Cubic Curves 
				);
		}
	}
	////////////////////////////////////////////////////////////////////////////// LINEAR
	else
	if	(m_nOrder_S == 2) // Linear
	{				 
		CCurve_1* pCurve;
		nOutActual = pCurve->MakeTangents
			(
				m_bClosed_S			// IsClosed for Redistribution
			,	m_nMaxCNodes_S		// number of CONTROL points
			,	m_pIn          		// Total CONTROL Points Array  
			,	m_nDim_S			// 4 = RATIONAL/	3 = NONrational 
			,	m_pWts_BZ_S			// Bezier Rational Weights
			,	m_pNum_t_S			// Output t-distribution array
			,	m_pDis_t_S			// t-Distribution for Single Linear Output Segment
			,	pOut				// Total Output Points Array
			,	m_nMaxCurves_S		// Total Number of Cubic Curves 
			);
	}
	////////////////////////////
	int nTanOut = (int)m_nOut;	// m_nOut in Generate_Curve stores last Pt. for drawing
								// although
								// Last Pt. = Ist Pt. when Closed
								// for Tangent we dont need Last Pt. when Closed
	if(m_bClosed_S)
		nTanOut--;
	if(nOutActual != (int)m_nOut)
		return -1;
	else
		return nOutActual;
}
/////////////////////////////////////////////////////////////////////////////
BOOL CDrCurve::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrCurve* pDrCurve = (CDrCurve*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrCurve->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrCurve::IsObjectHit(int nNet,POINT point)
{
	////////////////////////////////////// Output memory
	pWORLD	pOut	= FixMem(GetLongOutPts());
	pDOUBLE pOutWts = FixMemD(GetLongOutPts());
	////////////////////////////////// Now Generate
	////////////////////////////////////// Need to generate Curves
									////// using XFormed CNodes
	RefillCNEyePosForDirtyDraw();		// for DirtyDraw
	////////////////////////////////// Output memory
/*
	if(m_pOut)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}
	if(m_pOutWts)
	{
		FreeMemD(m_pOutWts);
		m_pOutWts = NULL;
	}
	m_pOut		= FixMem(m_nOut);
	m_pOutWts	= FixMemD(m_nOut);
*/
	////////////////////////////////
	GenerateCurve(pOut,pOutWts);
	/////////////////////////////////////////// Memory
/*
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
*/	
	POINT* pOutDP 	= FixMemDP(m_nOut);		// Output Points
	/////////////////////////////////////////// Project for CurvePts	
//	ProjectForDirtyDraw(&m_vv3DM,m_dScale_U,m_dScale_V);
	////////////////////////////////////////////////////////////////////
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	////////////////////////////////////////////// Project for DirtyDraw	
    for(long j = 0; j<m_nOut; j++)              
	{
    	EyePos.x = pOut[j].x;
    	EyePos.y = pOut[j].y;
    	EyePos.z = pOut[j].z;
		//////////////
		XForm.Project(&m_vv3DM,&EyePos, &ScreenPos);
		//////////////////////////////////////////////////////
		// 	3DScreenPos belongs to [0,-1] because of CVV	//
		//	So before we Change into Integer Logical		//
		//	Coordinates, we Must Use Screen Client Data		//
		//////////////////////////////////////////////////////
		pOutDP[j].x = (int)(ScreenPos.x * m_dScale_U);
		pOutDP[j].y = (int)(ScreenPos.y * m_dScale_V);
		/////////////////////////
	}		
	///////////////////////////////////////////
	if(pOut)
	{
		FreeMem(pOut); 
		pOut	= NULL;
	}		
	if(pOutWts)
	{
		FreeMemD(pOutWts); 
		pOutWts = NULL;
	}		
	///////////////////////////////////////////////////////////////// Check
	POINT*	pScrenOutPts	= pOutDP;
	int		nOut			= GetMaxOutPts_S();
	///////////////////////////////////////////
	POINT ptOld,ptNew;
	ptOld = *pScrenOutPts;
	//////////////////////
	for(int i=1;i<nOut;i++)
	{
		ptNew = *(pScrenOutPts+i);
		///////////////////////////////////// Find Normal to the Line
		C3DMath Math3D;
		double hl,vl,hn,vn,dLen;
		int netH,netV;
		//////////////////////////////////// line
		hl		= (double)(ptNew.x-ptOld.x);
		vl		= (double)(ptNew.y-ptOld.y);
		dLen	= sqrt(hl*hl + vl*vl);
		hl		/= dLen;
		vl		/= dLen;
		//////////////////////////////////// normal
		hn		= - vl;
		vn		= hl;
		///////////////
		netH	= (int)(hn*nNet);
		netV	= (int)(vn*nNet);
		///////////////////////////////////// Form PolygonalRgn: LP
		CRgn Quad;
		POINT	ptCorners[4];
		/////////////////////
		ptCorners[0].x = ptOld.x + netH;
		ptCorners[0].y = ptOld.y + netV;
		ptCorners[1].x = ptOld.x - netH;
		ptCorners[1].y = ptOld.y - netV;
		/////////
		ptCorners[2].x = ptNew.x - netH;
		ptCorners[2].y = ptNew.y - netV;
		ptCorners[3].x = ptNew.x + netH;
		ptCorners[3].y = ptNew.y + netV;
		////////////////////////////////
		BOOL bOk = Quad.CreatePolygonRgn( ptCorners, 4, ALTERNATE );
   		////////////////////////////////////////////// Check
		if(bOk)
		{
			if(Quad.PtInRegion(point))
			{
				Quad.DeleteObject();
				////////////////////
 				if(pOutDP)
				{
					FreeMemDP(pOutDP);
					pOutDP= NULL;
				}
				////////////////////
      			return TRUE;
			}
		}
		else
		{
			AfxMessageBox(
				"Internal Problem:\nCDrCurve::IsObjectHit\nCreatePolygonRgn");
			Quad.DeleteObject();
			////////////////////
 			if(pOutDP)
			{
				FreeMemDP(pOutDP);
				pOutDP= NULL;
			}
			////////////////////
			return FALSE;
		}
		/////////////////////////////// Reset
		ptOld = ptNew;
		Quad.DeleteObject();
		//////////////
	}
	////////////////////
	if(pOutDP)
	{
		FreeMemDP(pOutDP);
		pOutDP= NULL;
	}
	////////////////////
	return FALSE;
}
						 	
/*****************************************************************************
 *
 *	Function:	AppendToCurve()
 *
 *	Purpose:	Given an array of vertices, expands a
 *				specified Curve appending new vertices.
 *
 *	Returns:	INVALID_REQUEST		if Curve index is bad or hGroup is nil
 *				MEMORY_ALLOC_ERROR	if any memory error occurs
 *				noErr				if successfull
 *
 *****************************************************************************
 */ 
int CDrCurve::AppendToObject
				(
					CDListMgr* pSolidList,
					CDListMgr* pObj3DList,
					CDListMgr* pElemList, 
					CDListMgr* pNodeList,
					CDListMgr* pCNodeList,
					CDListMgr* pINodeList,
					CDListMgr* pVNodeList,
					CDListMgr* pCProfList,
					CDListMgr* pPatchList
				)
{							
	////////////////////
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
	if(pINodeList && !(pINodeList->IsEmpty())  )
		GetINodeList()->AddTail(pINodeList);
	else
		return -1;
	if(pVNodeList && !(pVNodeList->IsEmpty())  )
		GetVNodeList()->AddTail(pVNodeList);
	else
		return -1;
	if(pElemList && !(pElemList->IsEmpty()) )
		GetElemList()->AddTail(pElemList);
	else
		return -1;
	if(pCProfList && !(pCProfList->IsEmpty()) )
		GetCProfList()->AddTail(pCProfList);
	else
		return -1;
	if(pPatchList && !(pPatchList->IsEmpty()) )
		GetPatchList()->AddTail(pPatchList);
	else
		return -1;
	if(pObj3DList && !(pObj3DList->IsEmpty()) )
		GetObj3DList()->AddTail(pObj3DList);
	else
		return -1;
	///////////////
	return 0;	
}
/*****************************************************************************
 *
 *	Function:	SetCurveRefCon()
 *
 *	Purpose:	Sets the reference constant for a Curve and its facets.
 *
 *	Returns:	INVALID_REQUEST		if nil in either hG, or if index is
 *									out of bounds for the group.
 *				noErr				otherwise
 *
 *****************************************************************************
  
OsErr	API3D SetCurveRefCon(hGroup hG,int ix,pREFCON3D refCon)
{
	hCurve		hP;
	pCurve		pP;
	pFacet		pF;
	int			nF;

	if( ( !hG ) || ( ix<0 ) )
		return	INVALID_REQUEST;
	if( ( !hG->hP ) || ( ix>=hG->nP ) )
		return	INVALID_REQUEST;
	hP = hG->hP;
	pP = (pCurve)hP + (long)ix;
	pP->refCon = (DWORD FAR*)refCon;
	nF = pP->nF;
	pF = (pFacet)pP->hF;
	while( nF-- ) {
		pF->refCon = (DWORD FAR*)refCon;
		pF++;
	}
	return	noErr;
}
*/
			
int CDrCurve::GetCurrentBezSeg_N_s(int nOut_S,int& nCurBz_S,double& sCur)
{
	// given:	nOut index of total output
	// find:	which Bezier segment it belongs to and its s parametric value	
	//////////////////////////////////////////////////////////////////////////// 	 	   	
	pINT pNum_t_S = (m_CurveType_S == CP_CIRCLE)?m_pNum_t_Ex_S:m_pNum_t_S;// Circle Special
	//////////////
	BOOL bGot_S = FALSE;
	int i,nt_Accum=0;
	int nt_AccumOld,nt_NewTot,nt_Cur;
	//////////////////////////////////////////////////////////////////// S-dir
	for(i=0;i<m_nMaxCurves_S;i++)
	{
		nt_AccumOld	= nt_Accum;
		nt_NewTot	= *(pNum_t_S + i);
		nt_Accum	+= nt_NewTot;
		////////////////////
		if(nOut_S<nt_Accum || ((i == m_nMaxCurves_S)&&(nOut_S==nt_Accum)) )
		{
			bGot_S		= TRUE;
			nCurBz_S	= i;
			//////////////////////////////////// s valu
			nt_Cur		= nOut_S - nt_AccumOld; 
			double del	= 1./double(nt_NewTot);
			sCur		= ((double)nt_Cur)*del;
			////////////
			break;
		}
	}
	//////////////////////
	if(!bGot_S)
		return MA_ERROR;
	else
		return MA_OK;
	///////
}
	
int CDrCurve::GetAPointOnCurrentBezSeg(int nOut_S,pWORLD pOut,pDOUBLE pOutWt)
{
	int nResult = MA_OK;
	////////////////////
	int nCurBz_S;
	double sCur;
	//////////////////////////////////////////////////// Get CurBzSeg and S param
	nResult = GetCurrentBezSeg_N_s(nOut_S,nCurBz_S,sCur);
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////
	CCurve_1* pCurve_1;
	CCurve_2* pCurve_2;
	CCurve_3* pCurve_3;
	///////////////////
	switch(m_nOrder_S)
	{
		//////////////////////////////////////////////////// Go Compute for the currentPatch
		case 2:	// Linear
		nResult = pCurve_1->HO_GetAPointOnABezSegCurve 		// 
							(
								m_nMaxCNodes_S,m_pIn,m_nDim_S,m_pWts_BZ_S,nCurBz_S,sCur,
								pOut,pOutWt,m_nMaxCurves_S 
							);
		break;
		//////////////////////////////////////////////////// Go Compute for the currentPatch
		case 3:	// Quad
		nResult = pCurve_2->HO_GetAPointOnABezSegCurve 		// 
							(
								m_nMaxCNodes_S,m_pIn,m_nDim_S,m_pWts_BZ_S,nCurBz_S,sCur,
								pOut,pOutWt,m_nMaxCurves_S 
							);
		break;
		//////////////////////////////////////////////////// Go Compute for the currentPatch
		case 4:	// Cubic
		nResult = pCurve_3->HO_GetAPointOnABezSegCurve 		// 
							(
								m_nMaxCNodes_S,m_pIn,m_nDim_S,m_pWts_BZ_S,nCurBz_S,sCur,
								pOut,pOutWt,m_nMaxCurves_S 
							);
		break;
		/////////////
		default:
			return MA_ERROR;
	}	
	////////
	return nResult;
}
///////////////////////////////////////////////////////////////////////////////////
void CDrCurve::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	int nCount;     
	WORD	nElementType,nObjectNo,nObjectType,nPenWidth,nPenStyle,nLayer;
	DWORD   crPenColor;
	WORD	wCount;
	
	if (ar.IsStoring())
	{
		TRACE( " Curve   :Storing\n");	// TODO: add loading code here

		ar	<<	/*int*/		(WORD)m_nElemType	// Type = Curve = 2 in ElGlobal.h
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			///////////////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Curve Ends measured in MM_LOENGLISH units
			
			<<	/*UINT*/	(WORD)m_nPenWidth    // pen width for Pipe
			<<	/*COLORREF*/(DWORD)m_crPenColor
			<<	/*UINT*/	(WORD)m_nPenStyle 
			
			<<	/*UINT*/	(WORD)m_nLayer;
		/////////////////////////////////////////////// Lists
		UINT nCount = m_CNodeList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_CNodeList.Serialize(ar);
		//////		
		nCount = m_NodeList.GetCount();
		ar	<<				(WORD)nCount;
		if(nCount)
			m_NodeList.Serialize(ar);
		//////		
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
	
		TRACE( " Curve   :Loading\n");	// TODO: add loading code here


		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo 
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Curve Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
		  	>>	/*UINT*/	nPenWidth    // pen width for Pipe
			>>	/*COLORREF*/crPenColor
			>>	/*UINT*/	nPenStyle 
			>>	/*UINT*/	nLayer;
		/////////////////////////////////////////////// Lists
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_CNodeList.Serialize(ar);
		//////		
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_NodeList.Serialize(ar);
		//////		
		ar	>>				wCount;
		nCount = (UINT)wCount;
		if(nCount)
			m_ElemList.Serialize(ar);
		////////////////////////////////////////////////		
		for(int i=0; i<MAX_NODES_CORNER;i++)	
			ar	>>	/*POINT*/	m_pt[i];

    //////////////////////////////////////////////    
	m_nElemType		  	= 	(int)nElementType;		// Type = Curve = 2 in ElGlobal.h

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

