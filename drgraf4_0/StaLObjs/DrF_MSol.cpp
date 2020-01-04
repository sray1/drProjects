// Solid.cpp : implementation file
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
#include "DrFE3D.h" 
/////////////////////
#include "SolidHex.h"
#include "SolidPen.h"
#include "PentaHed.h"
#include "DrCurve.h"
/////////////////////
#include "DrSolid.h"


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
// CDrSolid
IMPLEMENT_SERIAL(CDrSolid, CDrPatch,1)
/*
BEGIN_MESSAGE_MAP(CDrSolid, CDrPatch)
	//{{AFX_MSG_MAP(CDrSolid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrSolid::CDrSolid()
{  
    	
    //////////////////////////////	
    SetObjectType((int)SOLID);
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
	m_nOut			= 0;
	m_pIn			= NULL;
	m_pInDP			= NULL;
	m_pOut			= NULL;
	m_pOutDP		= NULL;
	///////////////////	 
	m_pNum_t_R		= NULL;	
	m_pDis_t_R		= NULL;
	m_pDis_Ang_R	= NULL;	
	m_pNum_t_Ex_R	= NULL;		
	m_pNum_t_ST		= NULL;		
	m_pDis_t_ST		= NULL;		
	m_pDis_Ang_ST	= NULL;	
	m_pNum_t_Ex_ST	= NULL;	
	///////////////////////
} 
    	
CDrSolid::~CDrSolid()
{  
    	
 
	////////////////////////////// Pointers Borrowd from Generating Curves/Patches
   								// SHOULD HAVE BEEN ALready DELETED!
								// So NULL them, so that the Curve & Patch this
								// Solid is derived from does not attempt
								// to delete again!!!
  	/////////////////	
	m_pNum_t_S		= NULL;
	m_pNum_t_T		= NULL;
	m_pDis_t_S		= NULL;
	m_pDis_t_T		= NULL;
	m_pNum_t_Ex_S	= NULL;
	m_pNum_t_Ex_T	= NULL;
	///////////////////////////////////////////////////////////////////////////////	
	if(m_pNum_t_R)
	{
		delete m_pNum_t_R;
		m_pNum_t_R = NULL;
	}
	if(m_pDis_t_R)
	{
		delete m_pDis_t_R;
		m_pDis_t_R = NULL;
	}
	if(m_pDis_Ang_R)
	{
		delete m_pDis_Ang_R;
		m_pDis_Ang_R = NULL;
	}
	if(m_pNum_t_Ex_R)
	{
		delete m_pNum_t_Ex_R;
		m_pNum_t_Ex_R = NULL;
	}
	if(m_pNum_t_Ex_ST)
	{
		delete m_pNum_t_Ex_ST;
		m_pNum_t_Ex_ST = NULL;
	}
	if(m_pTangents_R)
	{
		delete m_pTangents_R;
		m_pTangents_R = NULL;
	}
	if(m_pCurvatures_R)
	{
		delete m_pCurvatures_R;
		m_pCurvatures_R = NULL;
	}
	if(m_pDis_t_ST)
	{
		delete m_pDis_t_ST;
		m_pDis_t_ST = NULL;
	}
	if(m_pDis_Ang_ST)
	{
		delete m_pDis_Ang_ST;
		m_pDis_Ang_ST = NULL;
	}
	if(m_pNum_t_Ex_ST)
	{
		delete m_pNum_t_Ex_ST;
		m_pNum_t_Ex_ST = NULL;
	}
	///////////////////////
	if(m_pIn)
		FreeMem(m_pIn); 
	if(m_pInDP)
		FreeMemDP(m_pInDP);
	if(m_pOut)
		FreeMem(m_pOut); 
	if(m_pOutDP)
		FreeMemDP(m_pOutDP);
	m_pIn		= NULL;
	m_pInDP		= NULL;
	m_pOut		= NULL;
	m_pOutDP	= NULL;
	///////////////////////////////// prepare
	ReadyToDelete();
	///////////////////////
}

void CDrSolid::ReadyToDelete()
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
			CDListMgr* pSolidList = pObject->GetSolidList();
			int index = pSolidList->GetObjectIndex(this);
			if(index>=0)
				pSolidList->RemoveObject(index); //Patch
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
			CDListMgr* pSolidList = pObject->GetSolidList();
			int index = pSolidList->GetObjectIndex(this);
			if(index>=0)
				pSolidList->RemoveObject(index); //curve
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
			CDListMgr* pSolidList = pObject->GetSolidList();
			int index = pSolidList->GetObjectIndex(this);
			if(index>=0)
				pSolidList->RemoveObject(index); //curve
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// unload Patch/No delete:public
	CDListMgr* pPatchList = GetPatchList();
    //////////////////////////////////////
	while(!pPatchList->IsEmpty())
	{
		pObject = (CDrObject*)pPatchList->RemoveHead();  //Patch
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pSolidList = pObject->GetSolidList();
			int index = pSolidList->GetObjectIndex(this);
			if(index>=0)
				pSolidList->RemoveObject(index); //solid
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// delete PentaHeds:private
	CDListMgr* pTriList = GetPentaList();
    //////////////////////////////////////
	while(!pTriList->IsEmpty())
	{
		CPentaHed* pTri = (CPentaHed*)pTriList->RemoveHead();  //PentaHed
		/////////////////////////////////////////////
		if(pTri)
		{
			///////////////////////// index List	
			CList<int,int>* pIndexList = pTri->GetCNIndexList();
			while(!pIndexList->IsEmpty())
				pIndexList->RemoveHead(); //Index
			/////////////////////////
		}
		//////////
	    delete pTri;
	}
	///////////////////////////////////// delete 
	while(!(GetElemList()->IsEmpty()))// unload/delete Elems: private
		delete (CDrObject*)(GetElemList()->RemoveHead()); //Elems
	/////////////////////////////////////////////////////////////
	while(!(GetObj3DList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetObj3DList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	/////////////////////////////////////
}
   
int CDrSolid::DealObjectDialog()
{
/*
	CDrSolidProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrSolid::SetObjectInfo(CDrObject* pObject)
{
	
	CDrPatch::SetObjectInfo(pObject);
	///////////////////////////////////   
	CDrSolid* pAdd = (CDrSolid*) pObject;
	//////////////////////////////////////////////////////// SOLIDINFO	
	m_SolidProc			= pAdd->m_SolidProc;
	m_SolidType			= pAdd->m_SolidType;
	m_SolSubType		= pAdd->m_SolSubType;
	m_CurveType_R		= pAdd->m_CurveType_R;
	m_n3D				= pAdd->m_n3D;
 	//////////////////////////////////////////////////////// CopyList
	if(!(pAdd->m_PatchList.IsEmpty()) )
		m_PatchList.AddTail(&(pAdd->m_PatchList) ); 
   ///////////////////////////
	m_nSegUnif_R		= pAdd->m_nSegUnif_R;
	m_nMaxINodes_R		= pAdd->m_nMaxINodes_R;
	m_nMaxCurves_R		= pAdd->m_nMaxCurves_R;
	m_bClosed_R			= pAdd->m_bClosed_R;
	m_nMaxCNodes_R		= pAdd->m_nMaxCNodes_R;
	m_nMaxOutPts_R		= pAdd->m_nMaxOutPts_R;
	m_nSolidObjectType	= pAdd->m_nSolidObjectType;
	//////////////////////////////////////// 
    for(int i = 0; i<2; i++)              // 
    {
    	m_PatchID[i]	= pAdd->m_PatchID[i];
    }	 
   	m_nSegs_R			= pAdd->m_nSegs_R;
   	m_nOut_R			= pAdd->m_nOut_R;
	/////////////////////////////////////////// 
	m_FromPtLocal_R		= pAdd->m_FromPtLocal_R;
	m_FromPtWorld_R		= pAdd->m_FromPtWorld_R;
	m_FromPtEye_R		= pAdd->m_FromPtEye_R;
	m_ToPtLocal_R		= pAdd->m_ToPtLocal_R;
	m_ToPtWorld_R		= pAdd->m_ToPtWorld_R;
	m_ToPtEye_R			= pAdd->m_ToPtEye_R;	
	m_dLen_R			= pAdd->m_dLen_R;
	m_dLenEye_R			= pAdd->m_dLenEye_R;
	m_vAxis_R			= pAdd->m_vAxis_R;	
	m_vAxisEye_R		= pAdd->m_vAxisEye_R;	
	/////////////////////
	m_FromID_R			= pAdd->m_FromID_R;
	m_ToID_R			= pAdd->m_ToID_R;
//	m_CurveID			= pAdd->m_CurveID;
	/////////////////////////////////////////// Rotate
	m_dAng_1_R			= pAdd->m_dAng_1_R;
	m_dAng_2_R			= pAdd->m_dAng_2_R;
	/////////////////////////////////////////// Duct/Sweep
	m_bIncTwist_R		= pAdd->m_bIncTwist_R;	// Incremental?
	m_bIncScale_R		= pAdd->m_bIncScale_R;	// for Sweep
	m_TwistMult_R		= pAdd->m_TwistMult_R;
	m_ScaleMult_R		= pAdd->m_ScaleMult_R;	// for Sweep
	m_TwistStart_R		= pAdd->m_TwistStart_R;
	m_ScaleStart_R		= pAdd->m_ScaleStart_R;	// for Sweep
	//////////////////////////////////////////
	m_OutMethod_R		= pAdd->m_OutMethod_R;		// Output Method
	m_bUniform_R		= pAdd->m_bUniform_R;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	m_nMaxOutSeg_R		= pAdd->m_nMaxOutSeg_R;		// Number of Output Segments on ENTIRE Curve in T
	m_pNum_t_R			= pAdd->m_pNum_t_R;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	m_pDis_t_R			= pAdd->m_pDis_t_R;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	m_pDis_Ang_R		= pAdd->m_pDis_Ang_R;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	m_pNum_t_Ex_R		= pAdd->m_pNum_t_Ex_R;		// Expanded Number of Outputs for each Output Segment
	m_pNum_t_ST			= pAdd->m_pNum_t_ST;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	m_pDis_t_ST			= pAdd->m_pDis_t_ST;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	m_pDis_Ang_ST		= pAdd->m_pDis_Ang_ST;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	m_pNum_t_Ex_ST		= pAdd->m_pNum_t_Ex_ST;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	m_nOrder_R			= pAdd->m_nOrder_R;			// k 
	m_nDim_R			= pAdd->m_nDim_R;			// 4 = RATIONAL/	3 = NONrational 
	//////////////////////////////////////////////////////////////////// CONICS
	m_nData_Ex_R		= pAdd->m_nData_Ex_R;	// GIVEN: # of Data 		= m_nMaxINodes_S  
	m_bExpanded_R		= pAdd->m_bExpanded_R;	
	m_nMaxENodes_R		= pAdd->m_nMaxENodes_R;
	m_Center_R			= pAdd->m_Center_R;	// Circle
	m_Normal_R			= pAdd->m_Normal_R;	
	m_Radius_R			= pAdd->m_Radius_R;
	m_Theta_R			= pAdd->m_Theta_R;
	m_SegAngle_R		= pAdd->m_SegAngle_R;
	//////////////////////////////////////////////////////////////////// Hole?
	m_bHole_R			= pAdd->m_bHole_R;
	//////////////////////////////////////////////////////////////////// Derivatives
	m_pTangents_R		= pAdd->m_pTangents_R;			// Tangents
	m_pCurvatures_R		= pAdd->m_pCurvatures_R;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    m_Ratio_R			= pAdd->m_Ratio_R;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	if(!(pAdd->m_PentaList.IsEmpty()) )
		m_PentaList.AddTail(&(pAdd->m_PentaList) ); 
	m_nTriangles_ST		= pAdd->m_nTriangles_ST;			//  Total No of Triangles in Base Patch
/*
	int nSize = sizeof(CDrSolid);		
	BlockCopy((HUGEBLK)(pAdd),(HUGEBLK)(this),sizeof(CDrSolid)  );
	////////////////////////////////////////////// 
*/	
	///////////////////////////////////	
	return;
}		

void CDrSolid::GetObjectInfo(CDrObject* pObject)
{
	
	CDrPatch::GetObjectInfo(pObject);
	///////////////////////////////////   
	CDrSolid* pAdd = (CDrSolid*) pObject;
	//////////////////////////////////////////////////////// SOLIDINFO	
	pAdd->m_SolidProc		= m_SolidProc;
	pAdd->m_SolidType		= m_SolidType;
	pAdd->m_SolSubType		= m_SolSubType;
	pAdd->m_CurveType_R		= m_CurveType_R;
	pAdd->m_n3D				= m_n3D;
 	//////////////////////////////////////////////////////// CopyList
	if(!(m_PatchList.IsEmpty()) )
		pAdd->m_PatchList.AddTail(&m_PatchList ); 
   ///////////////////////////
	pAdd->m_nSegUnif_R		= m_nSegUnif_R;
	pAdd->m_nMaxINodes_R	= m_nMaxINodes_R;
	pAdd->m_nMaxCurves_R	= m_nMaxCurves_R;
	pAdd->m_bClosed_R		= m_bClosed_R;
	pAdd->m_nMaxCNodes_R	= m_nMaxCNodes_R;
	pAdd->m_nMaxOutPts_R	= m_nMaxOutPts_R;
	pAdd->m_nSolidObjectType= m_nSolidObjectType;
	//////////////////////////////////////// 
    for(int i = 0; i<2; i++)              // 
    {
    	pAdd->m_PatchID[i]	= m_PatchID[i];
    }	 
   	pAdd->m_nSegs_R			= m_nSegs_R;
   	pAdd->m_nOut_R			= m_nOut_R;
	/////////////////////////////////////////// 
	pAdd->m_FromPtLocal_R	= m_FromPtLocal_R;
	pAdd->m_FromPtWorld_R	= m_FromPtWorld_R;
	pAdd->m_FromPtEye_R		= m_FromPtEye_R;
	pAdd->m_ToPtLocal_R		= m_ToPtLocal_R;
	pAdd->m_ToPtWorld_R		= m_ToPtWorld_R;
	pAdd->m_ToPtEye_R		= m_ToPtEye_R;	
	pAdd->m_dLen_R			= m_dLen_R;
	pAdd->m_dLenEye_R		= m_dLenEye_R;
	pAdd->m_vAxis_R			= m_vAxis_R;	
	pAdd->m_vAxisEye_R		= m_vAxisEye_R;	
	/////////////////////
	pAdd->m_FromID_R		= m_FromID_R;
	pAdd->m_ToID_R			= m_ToID_R;
//	pAdd->m_CurveID			= m_CurveID;
	/////////////////////////////////////////// Rotate
	pAdd->m_dAng_1_R		= m_dAng_1_R;
	pAdd->m_dAng_2_R		= m_dAng_2_R;
	/////////////////////////////////////////// Duct/Sweep
	pAdd->m_bIncTwist_R		= m_bIncTwist_R;	// Incremental?
	pAdd->m_bIncScale_R		= m_bIncScale_R;	// for Sweep
	pAdd->m_TwistMult_R		= m_TwistMult_R;
	pAdd->m_ScaleMult_R		= m_ScaleMult_R;	// for Sweep
	pAdd->m_TwistStart_R	= m_TwistStart_R;
	pAdd->m_ScaleStart_R	= m_ScaleStart_R;	// for Sweep
	//////////////////////////////////////////
	pAdd->m_OutMethod_R		= m_OutMethod_R;		// Output Method
	pAdd->m_bUniform_R		= m_bUniform_R;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	pAdd->m_nMaxOutSeg_R	= m_nMaxOutSeg_R;		// Number of Output Segments on ENTIRE Curve in T
	pAdd->m_pNum_t_R		= m_pNum_t_R;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_t_R		= m_pDis_t_R;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_Ang_R		= m_pDis_Ang_R;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pAdd->m_pNum_t_Ex_R		= m_pNum_t_Ex_R;		// Expanded Number of Outputs for each Output Segment
	pAdd->m_pNum_t_ST		= m_pNum_t_ST;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_t_ST		= m_pDis_t_ST;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	pAdd->m_pDis_Ang_ST		= m_pDis_Ang_ST;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_T+1
	pAdd->m_pNum_t_Ex_ST	= m_pNum_t_Ex_ST;		// Expanded Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	pAdd->m_nOrder_R		= m_nOrder_R;			// k 
	pAdd->m_nDim_R			= m_nDim_R;			// 4 = RATIONAL/	3 = NONrational 
	//////////////////////////////////////////////////////////////////// CONICS
	pAdd->m_nData_Ex_R		= m_nData_Ex_R;	// GIVEN: # of Data 		= m_nMaxINodes_S  
	pAdd->m_bExpanded_R		= m_bExpanded_R;	
	pAdd->m_nMaxENodes_R	= m_nMaxENodes_R;
	pAdd->m_Center_R		= m_Center_R;	// Circle
	pAdd->m_Normal_R		= m_Normal_R;	
	pAdd->m_Radius_R		= m_Radius_R;
	pAdd->m_Theta_R			= m_Theta_R;
	pAdd->m_SegAngle_R		= m_SegAngle_R;
	//////////////////////////////////////////////////////////////////// Hole?
	pAdd->m_bHole_R			= m_bHole_R;
	//////////////////////////////////////////////////////////////////// Derivatives
	pAdd->m_pTangents_R		= m_pTangents_R;			// Tangents
	pAdd->m_pCurvatures_R	= m_pCurvatures_R;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    pAdd->m_Ratio_R			= m_Ratio_R;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	if(!(m_PentaList.IsEmpty()) )
		pAdd->m_PentaList.AddTail(&m_PentaList ); 
	pAdd->m_nTriangles_ST	= m_nTriangles_ST;			//  Total No of Triangles in Base Patch
	///////////////////////////////////	
	return;
}		

void CDrSolid::Pack_drPipe(CString* pstrCard)
{

	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == SOLID) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
   	/////////////////////////
   	CString pad = " "; 
   	////////////////////////
//	m_SolidCard.bValve  = FALSE;  
   	AddStr(pstrCard,&name,5); 
   	AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}   

/////////////////////////////////////////////////////////////////
void CDrSolid::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	////////////////////
	if(!m_bDirty)
	{
//		Calc_PolyNormalWorld();
//		Calc_NodeNormalWorld();
		//////////////////
	}	
}
	
void CDrSolid::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
	if(!m_bDirty)
	{
//		TransformPolyNormalToEye(pViewM);
//		Calc_NodeNormalEye();
		return;
	}
	////////////////////////////////// Need to generate Solid
									// using XFormed CNodes
	else
	{									
		RefillCNEyePosForDirtyDraw();		// for DirtyDraw
		////////////////////////////////// Output memory
		m_pOut		= FixMem(m_nOut);
		m_pOutWts	= FixMemD(m_nOut);
		////////////////////////////////
		if(	m_SolSubType == SS_HEXA)
			Generate_SolidHex(m_pOut,m_pOutWts);
		if(	m_SolSubType == SS_PENTA)
			Generate_SolidPen(m_pOut,m_pOutWts);
		if( m_PatSubType == SS_TETRA)
			Generate_SolidTet(m_pOut,m_pOutWts);
		///////////////////////////////
	}		
	
} 

BOOL CDrSolid::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
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
				
void CDrSolid::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////
	ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
	/////////////
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

int CDrSolid::NumberOfSolides()
{
	/////////////////////// Compute No. of Solides in S & T direction
	CSolidHex* pSolid;
	int nSolides_S,nSolides_T,nOut_S,nOut_T,nSolides_R;
	///////////////////////
	int nSolTotal = pSolid->NumberOfSolides(
						CP_BEZIER,m_nMaxCNodes_S,m_nSegUnif_S,m_bClosed_S,m_nOrder_S,
						CP_BEZIER,m_nMaxCNodes_T,m_nSegUnif_T,m_bClosed_T,m_nOrder_T,
						CP_BEZIER,m_nMaxCNodes_R,m_nSegUnif_R,m_bClosed_R,m_nOrder_R,
						&nSolides_S,&nSolides_T,&nSolides_R,&nOut_S,&nOut_T,&nOut_T);
    //////////////////////////////// Save
	m_nMaxCurves_S 	= nSolides_S;
	m_nMaxCurves_T 	= nSolides_T;
	m_nMaxCurves_R 	= nSolides_R;
/*
	m_nOut_S			= nOut_S;				
	m_nOut_T			= nOut_T;				
	m_nOut_R			= nOut_R;				
	m_nOut				= (long)(nOut_S * nOut_T * m_nOut_R);
*/	
	/////////	
	return m_nOut;
						
}
/////////////////////////////////////////////////////////////////////
int CDrSolid::NumberOfBezierPenta()
{ 
	/////////////////////// Compute No. of Solides in ST & R direction
	CSolidPen* pSolid;
	int nTr_BZ_ST,nPt_OutST,nSolides_R,nOut_R,nPen_BZ;
	///////////////////////
	int nOutTotal = pSolid->NumberOfBezierPenta(
						CP_BEZIER,m_nMaxCNodes_S,m_nSegUnif_S,m_nOrder_S,
						CP_BEZIER,m_nMaxCNodes_R,m_nSegUnif_R,m_nOrder_R,m_bClosed_R,
						&nTr_BZ_ST,&nPt_OutST,&nSolides_R,&nOut_R,&nPen_BZ);
    //////////////////////////////// Save
	m_nMaxCurves_S 	= nTr_BZ_ST;
	m_nMaxCurves_T 	= nPen_BZ;
	m_nMaxCurves_R 	= nSolides_R;
	///////////////////////////// Output
//	m_nOut			= (long)nOutTotal;
	//////
	return nOutTotal;
} 

////////////////////////////////////////////////////////////
int CDrSolid::Generate_SolidTet(pWORLD pOut, pDOUBLE pOutWts)
{
	AfxMessageBox("CDrSolid::Generate_SolidTet\nNOT IMPEMENTED");
	return -1;
}

int CDrSolid::Generate_SolidPen(pWORLD pOut, pDOUBLE pOutWts)
{
	///////////////////
	CSolidPen* pSolid;
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	int nCons		= m_nMaxCNodes_T*m_nMaxCNodes_R;
	//////////////////////////////////////////////////////////////////////////// generate Solid Pts		 	   	
    if( m_SolidType == SO_TENSOR)
    {
		//////////////////////////////////////////////////////////////////////
		nOutActual	= pSolid->PentaHeds_3D
				(
					m_OutMethod_R	//  Output Method
				,	m_bClosed_R		//  IsClosed_R
				,	nCons			//  Total number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_S		//  3= NonRational / 4 = Rational
					//////////
				,	m_nDim_R		//  3= NonRational / 4 = Rational
				,	m_pDis_t_R		//  Output t distribution Pts. for Ratio Business
				,	m_nMaxCurves_R	//  Total Number of Solids in R-dir 
					//////////////////////////////  Globals:
				,	m_nOutGlo_S		//  Total Output in each side of entire Base Patch
					//////////
				,	&m_PentaList		//	PentaHed List
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut			//  Total Output Points Array
				,	pOutWts			//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	nOut			//	expected number of generated Patch vertices	
				);
		////////////////////////////	
	}	
	else	
    if(m_SolidType == SO_GORDON)
    {
		AfxMessageBox("CDrSolid:\nGenerate_SolidPen\nGORDON NOT IMPLEMENTED YET");
		return -1;
	}
	else	
    if(m_SolidType == SO_COONS)
    {
		AfxMessageBox("CDrSolid:\nGenerate_SolidPen\nCOONS NOT IMPLEMENTED YET");
		return -1;
	}
	else
	{
		AfxMessageBox("Internal Problem:\nCDrSolid:\nGenerate_SolidPen\nm_SolidType UNRECOGNIZED");
		return -1;
	}	
	////////////////////////////	
	if(nOutActual<0)
	{
		AfxMessageBox("Internal Problem:\nCDrSolid:\nGenerate_SolidPen\nnOutActual<0");
		return -1;
	}	
	////////////
	return 0;
	///////
}

int CDrSolid::Generate_SolidHex(pWORLD pOut, pDOUBLE pOutWts)
{
	///////////////////
	CSolidHex* pSolid;
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
    if(m_SolidType == SO_TENSOR)
    {
		pINT pNum_t_R = (m_CurveType_R == CP_CIRCLE)?m_pNum_t_Ex_R:m_pNum_t_R;// Circle Special
		//////////////////////////////////////////////////////////////////////
		nOutActual	= pSolid->TensorProduct_3D
				(
					m_OutMethod_R	//  Output Method
				,	m_bClosed_S		//  IsClosed_S
				,	m_nOrder_S-1	//  Degree in S-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_S	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_S	//  Total Number of Patches 
				,	m_pNum_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_T		//  IsClosed_T
				,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_T		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_T	//  Total Number of Patches 
				,	m_pNum_t_T			//  Number of Output Segments Array in T-Dir for each patch
				,	m_pDis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_R		//  IsClosed_S
				,	m_nOrder_R-1	//  Degree in S-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_R	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_R		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_R	//  Total Number of Patches 
				,	m_pNum_t_R		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_R		//  Output t distribution Pts. for Ratio Business				
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut			//  Total Output Points Array
				,	pOutWts			//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
				,	nOut			//	expected number of generated Patch vertices	
				);
		////////////////////////////	
	}	
	////////////////////////////////////////// We Need CurvePts
	else	
    if(m_SolidType == SO_COONS)
    {
		AfxMessageBox("CDrSolid:1\nGenerate_SolidHex\nCOONS NOT IMPLEMENTED YET");
		return -1;
	}
	else	
    if(m_SolidType == SO_GORDON)
    {
		AfxMessageBox("CDrSolid:1\nGenerate_SolidHex\nGORDON NOT IMPLEMENTED YET");
		return -1;
	}
	else
	{
		AfxMessageBox("Internal Problem:\nCDrSolid:1\nGenerate_SolidHex\nm_SolidType UNRECOGNIZED");
		return -1;
	}	
	////////////////////////////	
	if(nOutActual != nOut)
	{
		AfxMessageBox("Internal Problem:\nCDrSolid:1\nGenerate_SolidHex\nnOutActual != nOut");
		return -1;
	}	
	////////////
	return 0;
	///////
}	

BOOL CDrSolid::CullWorld(WORLD VDir)
{

	CDListMgr* pList;
	POSITION pos;
	BOOL bCulledSolid= TRUE,bCulled;
	//////////////////////
	pList = GetElemList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(!(pObject->GetObjectType() == FE3D) )
		{
			bCulledSolid = FALSE;
			continue;
		}	
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		bCulled = pPoly->CullWorld(VDir);
		///////////////////////////
		if(!bCulled)
			bCulledSolid = FALSE;
	}
	////////////////////////
	SetCulled(bCulledSolid);
	////////////////////
	return bCulledSolid;
	
}
				
BOOL CDrSolid::CullScreen(pMATRIX pViewM)
{

	CDListMgr* pList;
	POSITION pos;
	BOOL bCulledSolid = TRUE,bCulled;
	/////////////////////
	pList = GetElemList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(!(pObject->GetObjectType() == FE3D) )
		{
			bCulledSolid = FALSE;
			continue;
		}
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;	
		bCulled = pPoly->CullScreen(pViewM);
		///////////////////////////
		if(!bCulled)
			bCulledSolid = FALSE;
	}
	////////////////////
	return bCulledSolid;
	
}

void CDrSolid::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
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
		XForm.Transform(&m_FromPtLocal_R, &m_FromPtWorld_R,pLMP);
		XForm.Transform(&m_ToPtLocal_R, &m_ToPtWorld_R,pLMP);
	}
	else
	{
		m_FromPtWorld_R 	= m_FromPtLocal_R; 	
		m_ToPtWorld_R 		= m_ToPtLocal_R;
	}	 	
	////////////////////////////////////////////////
}

void CDrSolid::TransformToEyePos(pMATRIX pViewM)
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
	XForm.Transform(&m_FromPtWorld_R, &m_FromPtEye_R,pViewM);
	XForm.Transform(&m_ToPtWorld_R, &m_ToPtEye_R,pViewM);
	////////////////////////////////////////////////
}

void CDrSolid::ProjectToScreenPos
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
			if(!(pObject->GetObjectType() == FE3D) )
			{
				continue;
			}
			///////////////////////////
			pObject->ProjectObject(pvv3DM,dScale_U,dScale_V);
			/////////
		}
	}		
}

void CDrSolid::Calc_ScreenRectFromPoly()
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
		if(!(pObject->GetObjectType() == FE3D) )
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

void CDrSolid::Calc_PolyNormalWorld()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE3D) )
			continue;
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		pPoly->Calc_NormalWorld();
		///////////////////////////
	}
}				

void CDrSolid::TransformPolyNormalToEye(pMATRIX pViewM)
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE3D) )
			continue;
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		pPoly->TransformNormalToEye(pViewM);
		///////////////////////////
	}
}				

void CDrSolid::ProjectPolyNormalToScreen3D
			(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid/Polygon Creation. We will do this later.	// todo
	////////////////////////////////////////////////////// 	
	CDListMgr* pList;
	POSITION pos;
	
	pList = GetElemList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(!(pObject->GetObjectType() == FE3D) )
			continue;
		///////////////////////////
		CDrFE2D* pPoly = (CDrFE2D*) pObject;
		pPoly->ProjectNormalToScreen3D
				(pvv3DM,dScale_U,dScale_V);
		///////////////////////////
	}
}				

void CDrSolid::Calc_NodeNormalWorld()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid Creation. We will do this later. todo		//
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
void CDrSolid::Calc_NodeNormalEye()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid Creation. We will do this later. todo		//
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
void CDrSolid::Calc_NodeNormalScreen3D()
{

	//////////////////////////////////////////////////////
	// 	An Alternative way would be to Compute during	//
	//	Solid Creation. We will do this later. todo		//
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
void CDrSolid::DoDataView(CDC* PtrDC, int y)
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
void CDrSolid::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
void CDrSolid::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    CPen    Pen;
   	CPen*   PtrOldPen; 
	//////////////////
 	if(bPenChange)
 		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
	else
		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
   ///////////////////////////////////////////// Draw
	if(m_SolSubType == SS_HEXA)
	{
		////////////////
		GoDoIt_HEXA(PtrDC);
		///////////////////////////////
   		PtrDC->SelectObject(PtrOldPen);   
   		Pen.DeleteObject(); 
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
	////////////////////////////////
	else
	if(m_SolSubType == SS_PENTA)
	{
		GoDoIt_PENTA(PtrDC);
		///////////////////////////////
   		PtrDC->SelectObject(PtrOldPen);   
   		Pen.DeleteObject(); 
		/////////////////////////////// Controls
		if(IsControlShapeNeeded())
			GoDoControlNodes_PENTA(PtrDC);
		else
		{
			/////////////////////////////// FreeMemory
			FreeMem(m_pIn);
			m_pIn = NULL;
		}	
	}
	////////////////////////////////
	else
	if(m_SolSubType == SS_TETRA)
	{
		GoDoIt_TETRA(PtrDC);
		///////////////////////////////
   		PtrDC->SelectObject(PtrOldPen);   
   		Pen.DeleteObject(); 
		/////////////////////////////// Controls
		if(IsControlShapeNeeded())
			GoDoControlNodes_TETRA(PtrDC);
		else
		{
			/////////////////////////////// FreeMemory
			FreeMem(m_pIn);
			m_pIn = NULL;
		}	
	}
	////////////////////////////////
    
}            
                
void CDrSolid::GoDoIt_HEXA(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	long r,i,j,k,m,mold;
	long ii;
	///////////////////////////////////////////////////// S - dir
	for(r =0; r<m_nOut_R;r++)
	{
		for(i =0; i<m_nOut_T;i++)
		{
			k = i * (m_nOut_S) 
				+ r * (m_nOut_S * m_nOut_T);
			mold = k;	
//			PtrDC->MoveTo(m_pOutDP[k].x,m_pOutDP[k].y);
			///////////////////////////////
			for(j =1; j<m_nOut_S;j++)
			{
				m = k + j; 
				
				DrawLine3D(PtrDC,m_pOut+mold,m_pOut+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
//				PtrDC->LineTo(m_pOutDP[m].x,m_pOutDP[m].y); 
				mold = m;
			}	
		}
	}	
	///////////////////////////////////////////////////// T - dir
	for(r =0; r<m_nOut_R;r++)
	{
		for(i =0; i<m_nOut_S;i++)
		{
			ii = i  + r *(m_nOut_S * m_nOut_T);
			mold = ii;	
//			PtrDC->MoveTo(m_pOutDP[ii].x,m_pOutDP[ii].y);
			///////////////////////////////
			for(j =1; j<m_nOut_T;j++)
			{
				m = ii + j*(m_nOut_S);

				DrawLine3D(PtrDC,m_pOut+mold,m_pOut+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
//				PtrDC->LineTo(m_pOutDP[m].x,m_pOutDP[m].y);
				mold = m;
			}	
		}
    }
	///////////////////////////////////////////////////// R - dir
	for(i =0; i<m_nOut_S;i++)
	{
		for(j =0; j<m_nOut_T;j++)
		{
			ii = i  + j * m_nOut_S;
			mold = ii;	 
//			PtrDC->MoveTo(m_pOutDP[ii].x,m_pOutDP[ii].y);
			///////////////////////////////
			for(r =1; r<m_nOut_R;r++)
			{
				m = ii + r * (m_nOut_S * m_nOut_T);

				DrawLine3D(PtrDC,m_pOut+mold,m_pOut+m,TRUE);// TRUE = XFormed; FALSE = WORLD 
//				PtrDC->LineTo(m_pOutDP[m].x,m_pOutDP[m].y);
				mold = m;
			}	
		}
    }
/*	    
	///////////////////////////////////////////// Show Pts
		for( ii =0; ii<m_nOut;ii++)
		{
			int x,y,len = 3;
			x = m_pOutDP[ii].x;
			y = m_pOutDP[ii].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		}
*/		 
	///////////////////////////////   	
}

void CDrSolid::GoDoControlNodes_HEXA(CDC* PtrDC)
{ 
	// index = index of curve, because there are different curves
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	int nPenWidth = 0;   
   	Pen.CreatePen (m_nPenStyle,nPenWidth,RGB(255,0,0));
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////	
	if(!m_bDirty)
		return;
   ///////////////////////////////////////////////// Control Nodes
	long r,i,j,k,m,mold;
	long ii;
	///////////////////////////////////////////////////// S - dir
	for(r =0; r<m_nMaxCNodes_R;r++)
	{
		for(i =0; i<m_nMaxCNodes_T;i++)
		{
			k = i * (m_nMaxCNodes_S)
				 + r *(m_nMaxCNodes_S * m_nMaxCNodes_T) ;
			mold = k;	 
//			PtrDC->MoveTo(m_pInDP[k].x,m_pInDP[k].y);
			///////////////////////////////
			for(j =1; j<m_nMaxCNodes_S;j++)
			{
				m = k + j;
				
				DrawLine3D(PtrDC,m_pIn+mold,m_pIn+m,TRUE);// TRUE = XFormed; FALSE = WORLD
//				PtrDC->LineTo(m_pInDP[m].x,m_pInDP[m].y);
				mold = m;
			}	
		}
	}	
	///////////////////////////////////////////////////// T - dir
	for(r =0; r<m_nMaxCNodes_R;r++)
	{
		for(i =0; i<m_nMaxCNodes_S;i++)
		{
			ii = i  + r *(m_nMaxCNodes_S * m_nMaxCNodes_T);
            mold = ii;
//			PtrDC->MoveTo(m_pInDP[ii].x,m_pInDP[ii].y);
			///////////////////////////////
			for(j =1; j<m_nMaxCNodes_T;j++)
			{
				m = ii + j*(m_nMaxCNodes_S);

				DrawLine3D(PtrDC,m_pIn+mold,m_pIn+m,TRUE);// TRUE = XFormed; FALSE = WORLD
//				PtrDC->LineTo(m_pInDP[m].x,m_pInDP[m].y);
				mold = m;
			}	
		}
	}	
	///////////////////////////////////////////////////// R - dir
	for(i =0; i<m_nMaxCNodes_S;i++)
	{
		for(j =0; j<m_nMaxCNodes_T;j++)
		{
			ii = i  + j * m_nMaxCNodes_S;
			mold = ii;	 
//			PtrDC->MoveTo(m_pInDP[ii].x,m_pInDP[ii].y);
			///////////////////////////////
			for(r =1; r<m_nMaxCNodes_R;r++)
			{
				m = ii + r * (m_nMaxCNodes_S * m_nMaxCNodes_T);
					
				DrawLine3D(PtrDC,m_pIn+mold,m_pIn+m,TRUE);// TRUE = XFormed; FALSE = WORLD
//				PtrDC->LineTo(m_pInDP[m].x,m_pInDP[m].y);
				mold = m;
			}	
		}
    }
/*		 
	///////////////////////////////////////////// Show Pts
		long nMaxCNodes = 
			m_nMaxCNodes_S * m_nMaxCNodes_T * m_nMaxCNodes_R; 
		for( ii =0; ii< nMaxCNodes;ii++)
		{
			int x,y,len = 3;
			x = m_pInDP[ii].x;
			y = m_pInDP[ii].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		} 
*/		
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	
}

void CDrSolid::GoDoIt_PENTA(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	CDListMgr* pPenList = GetPentaList();
	if(pPenList->IsEmpty() )
		return;
	////////////////////////
	int nPenta	= pPenList->GetCount();
	////////////////////////////////// Save SolidInfo
	// Each Output PentaHed should have all the Output Pts.
	// this will require redundancy but simplify,So
	////////////////////////
	int nPt,nOutTriNum,nOutSeg_S;
	nOutSeg_S	= GetSegmentCount_S();
	nPt			= nOutSeg_S+1;			// No. of Output Pts. on each side of each Triangle
	nOutTriNum	= nPt*(nPt+1)/2;		// No. of Output Pts. on each  base Triangle	
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pPenList->GetFirstObjectPos();posT !=NULL;)
	{
		CPentaHed* pPen = (CPentaHed*)pPenList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType			= pPen->GetType();
		int nTrMax			= pPen->GetOutSeg_R() + 1;			// Output Triangle on height side
		int nOutStartIndex	= pPen->GetOutStartIndex();
		int iOutGlo_ST		= pPen->GetiOutGlo_ST();
		int jOutGlo_ST		= pPen->GetjOutGlo_ST();
//		int	nOutStart	= pPen->GetOutStartIndex();			// Overall Degree of Triangle
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		if(nType == 1)
			PENTA_1(PtrDC,nTrMax,nOutSeg_S,iOutGlo_ST,jOutGlo_ST,nOutStartIndex);
		else
		if(nType == 2)
			PENTA_2(PtrDC,nTrMax,nOutSeg_S,iOutGlo_ST,jOutGlo_ST,nOutStartIndex);
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

void CDrSolid::PENTA_1(CDC* PtrDC,int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
							int nOutStartIndex)
{ 

	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld,nTr;
	int iOut,jOut,nOutGlo_ST;
	///////////////////////////////////
	nOutGlo_ST = m_nOutGlo_S*(m_nOutGlo_S+1)/2;
	///////////////////////////////////////////
	for(nTr=0;nTr<nTrMax;nTr++)
	{
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				i++;
				iOut	= iOutGlo_ST + i;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				j++;
				jOut	= jOutGlo_ST + j;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				i++;
				j--;
				iOut	= iOutGlo_ST + i;
				jOut	= jOutGlo_ST + j;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
				////
				iOld = i;
				jOld = j;
			}
		}
	}
	/////////////////////////////////////////////////////////////////// Parallel Sides
	// TODO
}									

void CDrSolid::PENTA_2(CDC* PtrDC,int nTrMax,int nOutSeg_S,int iOutGlo_ST,int jOutGlo_ST,
							int nOutStartIndex)
{ 

	/////////////////////////////////////////////////////////////////// Bot & Top Triangle
	int i,j,k,m,L1,L2;
	int iOld,jOld,nTr;
	int iOut,jOut,nOutGlo_ST;
	///////////////////////////////////
	nOutGlo_ST = m_nOutGlo_S*(m_nOutGlo_S+1)/2;
	///////////////////////////////////
	for(nTr=0;nTr<nTrMax;nTr++)
	{
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				i++;
				iOut	= iOutGlo_ST - i;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				j++;
				jOut	= jOutGlo_ST - j;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
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
				L1 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				i++;
				j--;
				iOut	= iOutGlo_ST - i;
				jOut	= jOutGlo_ST - j;
				//////////////////////////////////// Barycentric to Linear: Global
				L2 = BARY2LIN_PT(iOut,jOut,m_nOutGlo_S) + nTr * nOutGlo_ST + nOutStartIndex;
				////
				DrawLine3D(PtrDC,m_pOut+L1,m_pOut+L2,TRUE);// TRUE = XFormed; FALSE = WORLD 
				////
				iOld = i;
				jOld = j;
			}
		}
	}
	/////////////////////////////////////////////////////////////////// Parallel Sides
	// TODO
}									

void CDrSolid::GoDoControlNodes_PENTA(CDC* PtrDC)
{ 
	// index = index of curve, because there are different curves
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	int nPenWidth = 0;   
   	Pen.CreatePen (m_nPenStyle,nPenWidth,RGB(255,0,0));
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////	
	if(!m_bDirty)
		return;
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
	//////////////////
	return;
}

void CDrSolid::GoDoIt_TETRA(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
	//////////
	return;
   	
}

void CDrSolid::GoDoControlNodes_TETRA(CDC* PtrDC)
{ 
	// index = index of curve, because there are different curves
   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	int nPenWidth = 0;   
   	Pen.CreatePen (m_nPenStyle,nPenWidth,RGB(255,0,0));
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////	
	if(!m_bDirty)
		return;
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
	//////////////////
	return;
}

int CDrSolid::NumberOfElements(UINT nSolidType,int nElemType)
{
	return 0;		
}	
/////////////////////////////////////////////////////////////////////////////
BOOL CDrSolid::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrSolid* pDrSolid = (CDrSolid*)(pObject);
	//////////////////////////////////////////////	 
	if((pDrSolid->GetObjectID()) == KeyID)
		return TRUE;
	else	
		return FALSE;
}
	
BOOL CDrSolid::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect)
{
		CDrSolid* pSolid = (CDrSolid*)pObject;
		///////////////////////////////////
		if(pSolid->GetObjectType() == SOLID)
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
 *	Function:	AppendToSolid()
 *
 *	Purpose:	Given an array of facets and an array of vertices, expands a
 *				specified patch appending new vertices and facets.
 *
 *****************************************************************************
 */ 
int CDrSolid::AppendToObject
				(
					CDListMgr* pObj3DList,
					CDListMgr* pPatchList, 
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
	if(pPatchList && !(pPatchList->IsEmpty())  )
		GetPatchList()->AddTail(pPatchList);
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
	///////////////
	return 0;	
}

/////////////////////////////////////////////////////////////////////////////
void CDrSolid::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	int nCount;     
	WORD	nElementType,nObjectNo,nObjectType,nPenWidth,nPenStyle,nLayer;
	DWORD   crPenColor;
	WORD	wCount;
	
	if (ar.IsStoring())
	{
		TRACE( " Solid   :Storing\n");	// TODO: add loading code here

		ar	<<	/*int*/		(WORD)m_nElemType	// Type = Solid = 2 in ElGlobal.h
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			///////////////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Solid Ends measured in MM_LOENGLISH units
			
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
	
		TRACE( " Solid   :Loading\n");	// TODO: add loading code here


		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo 
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Solid Ends measured in MM_LOENGLISH units
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
	m_nElemType		  	= 	(int)nElementType;		// Type = Solid = 2 in ElGlobal.h

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
						 		  		