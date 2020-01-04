// Patch.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN

#include "Def_MouseAct.h"
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"

#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "XForm.h"
#include "3DMath.h"
////////////////////// ElemObjs
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Ext_Pat.h"
#include "DrNode.h"
//#include "DrFE2D.h"
/////////////////////
#include "surface3.h"
#include "surface4.h"
#include "Pat_Tan3.h"
#include "Pat_Tan4.h"
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

#define BARY2LIN_TRI_1_NEW(i,j,nP,nDeg)	( (j)  + ((i)*(2*(nP)-(i)-2))/(nDeg) )/(nDeg)
#define BARY2LIN_TRI_2_NEW(i,j,nP,nDeg)	( (j - nDeg)  + ((i)*(2*(nP)-(i)-2))/(nDeg) - ((nP) - 1) + (i) )/(nDeg)
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
	/////////////////////////////////
	m_bAdvancedEnd_U	= FALSE;
	m_pCornerTwist_U	= NULL;// it is full,if TW_USER
	m_TwistMethod_U		= TW_AUTO;
	///
	m_bAdvancedEnd_V	= FALSE;
	m_pCornerTwist_V	= NULL;// it is full,if TW_USER
	m_TwistMethod_V		= TW_AUTO;
	///
    m_EndList_U.RemoveAll();
    m_EndList_V.RemoveAll();
	////////////////////////
	m_nNodes_S			= 0;			// for Tensor Product
	m_nNodes_T			= 0;
	m_bGenBCurve		= FALSE;
	m_PatchProc			= PP_COONSQUAD;           // How Generated? PP_EXTRUDE etc
	m_PatchType			= PA_COONS;           	// PA_TENSOR, etc
	m_PatSubType		= PS_QUADRILAT;			// Tringle or Quadrilat
	m_CurveType_T		= CP_LINEAR;         	// PA_BEZIER, etc
	/////////////////////////////////
	m_nMeshElemDim		= 2;			// Formerly m_b2D
										// 0D = Node/1D = Grid or 2D = plate etc 
	/////////////////////////
	m_nSegUnif_T		= -1;
	m_bClosed_T			= FALSE; 
	m_nMaxINodes_T		= -1;
	m_nMaxCNodes_T		= -1;			// INTERNALLY: WE ALWAYS STAY WITH  B E Z I E R
	m_nMaxCurves_T		= -1;			// Formerly: m_nMaxCurves	// No. of Curves
	m_nPatchObjectType	= -1;		// ObjectType to create; -1 = no creation reqd
	///////////////////////////
	m_VCurveList.RemoveAll();       // 
	///////////////////////////
	m_CurveList_U.RemoveAll();       // Curves in u
	m_CurveList_V.RemoveAll();       // Curves in v
	m_CurveList_W.RemoveAll();       // Curves in w for Triangle Patches
	m_CurveLatchList_U.RemoveAll();       // Curves in u
	m_CurveLatchList_V.RemoveAll();       // Curves in v
	m_CurveLatchList_W.RemoveAll();       // Curves in w for Triangle Patches
	//////////////////////////////////////////////////////////////////
	for(int i =0;i<4;i++)
	{
		m_pBndryCurves[i] = NULL;
		m_pIn_S[i] = NULL;
		m_CurveID[i] = "";
		m_CuLatch[i] = CL_FORWARD;
	}
	///////////////////////////
	m_nSegs_T			= -1;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
//	WORLD 		m_FromPtLocal_T;		// used also for Sweep/Duct Anchor
//	WORLD 		m_FromPtWorld_T;	// used also for Sweep/Duct Anchor
//	WORLD 		m_FromPtEye_T;	// used also for Sweep/Duct Anchor
//	WORLD 		m_ToPtLocal_T;			// used also for Sweep/Duct Anchor
//	WORLD 		m_ToPtWorld_T;	// used also for Sweep/Duct Anchor
//	WORLD 		m_ToPtEye_T;		// used also for Sweep/Duct Anchor
	///////////////////////////
	m_nExtruType_T		= 1;
//	double		m_dLen_T;
//	WORLD		m_wLen_T;		// for Type 2 Input

//	double		m_dLenEye_T;
//	WORLD		m_wLenEye_T;
//	WORLD		m_vAxis_T;		// unit Extrusion Axis/XFormed
//	WORLD		m_vAxisEye_T;		// unit Extrusion Axis/XFormed
	/////////////////////
	m_pFromIDNode_T			= NULL;		// also used:AnchorID for Sweep/Duct
	m_pToIDNode_T			= NULL;
	/////////////////////////////////////////// Rotate
//	double		m_dAng_1_T;
//	double		m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	m_nTwistType_T			= 1;
	m_nScaleType_T			= 1;
	m_TwistList_T.RemoveAll();
	m_ScaleList_T.RemoveAll();
	m_bIncTwist_T		= FALSE;	// Incremental?
	m_bIncScale_T		= FALSE;	// for Sweep
//	double		m_TwistMult_T;
//	double		m_ScaleMult_T;	// for Sweep
//	double		m_TwistStart_T;
//	double		m_ScaleStart_T;	// for Sweep
	m_nOut_S			= -1;	//	number of generated Patch vertices in U dir	
	m_nOut_T			= -1;	//	number of generated Patch vertices in V dir	
	/////////////////////////////////////////// Duct/Sweep	: For Iso Parametric
//	WORLD		m_wTwistMult_T;
//	WORLD		m_wScaleMult_T;	// for Sweep
//	WORLD		m_wTwistStart_T;
//	WORLD		m_wScaleStart_T;	// for Sweep
    ////////////////////////////////////// Memory
//	pWORLD		m_pIn_S[4];	// XSec etc Control Pointers (DONE BEFORE)
	////////////////////////////////////// NoOfElems
	m_nTotElems			= -1;
	/////////////////////////////////////////////////////////// Output
	m_OutMethod_T		= PA_HORNER;		// Output Method
	m_bUniform_T		= TRUE;		// Output Distribution:
										// 	true 	= Uniform
										//	false 	= Non-Uniform
	m_nMaxOutPts_T		= 0;
	m_nMaxOutSeg_T		= 0;		// Number of Output Segments on ENTIRE Curve
	m_pNum_t_T			= NULL;			// Number of Outputs for each Output Segment
											//	Num_t[i], i = 1,nMaxOutSeg																							
	m_pDis_t_T			= NULL;			// Number of Outputs for each Linear Single Segment
											//	Dis_t[i], i = 1,nMaxOutSeg																							
	m_pNum_t_Ex_T		= NULL;		// Expanded Number of Outputs for each Output Segment
	m_pDis_Ang_T		= NULL;		// Output theta-distribution array for Circle:
											//	Dis_Ang[i], i = 1,m_nSegUnif_S+1
	//////////////////////////////////////////////////////////////////////////////// Interpol																																		
	m_Class_T			= 0;				// C0
	m_nOrder_T			= 1;				// k
	m_nDim_T			= 3;				// 4 = RATIONAL/	3 = NONrational 
	//////////////////////////////////////////////////////////////////// CONICS
//	int			m_nData_Ex_T;				// GIVEN: # of Data 		= m_nMaxINodes_S  
//	BOOL		m_bExpanded_T;
//	int			m_nMaxENodes_T;
//	WORLD		m_Center_T;	// Circle
//	WORLD		m_Normal_T;	
//	double		m_Radius_T;
//	double		m_Theta_T;
//	double 		m_SegAngle_T;
	//////////////////////////////////////////////////////////////////// Hole?
//	BOOL		m_bHole_T;
	////////////////////////////
	m_pTangents_T		= NULL;  
	m_pNormals			= NULL;  
	m_pCurvatures_T		= NULL;
    /////////////////////////////// Output
    m_Ratio_T			= 1.0;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	m_TriangleList.RemoveAll();       // Triangles
	//////////////////////////////  Globals:
	m_nOutGlo_S			= 0;			//  Total Output in each side of entire Base Patch
	m_ElperSegList_T.RemoveAll();
} 
    	
CDrPatch::~CDrPatch()
{  

	m_ElperSegList_T.RemoveAll();
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
	if(m_pCornerTwist_U);// it is full,if TW_USER
	{
		delete [] m_pCornerTwist_U;
		m_pCornerTwist_U = NULL;
	}
	if(m_pCornerTwist_V);// it is full,if TW_USER
	{
		delete [] m_pCornerTwist_V;
		m_pCornerTwist_V = NULL;
	}
	if(m_pNum_t_T)
	{
		delete [] m_pNum_t_T;
		m_pNum_t_T = NULL;
	}
	if(m_pDis_t_T)
	{
		delete [] m_pDis_t_T;
		m_pDis_t_T = NULL;
	}
	if(m_pDis_Ang_T)
	{
		delete [] m_pDis_Ang_T;
		m_pDis_Ang_T = NULL;
	}
	if(m_pNum_t_Ex_T)
	{
		delete [] m_pNum_t_Ex_T;
		m_pNum_t_Ex_T = NULL;
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
	if(m_pTangents_T)
	{
		delete [] m_pTangents_T;
		m_pTangents_T = NULL;
	}
	if(m_pCurvatures_T)
	{
		delete [] m_pCurvatures_T;
		m_pCurvatures_T = NULL;
	}
	if(m_pNormals)
	{
		delete [] m_pNormals;
		m_pNormals = NULL;
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
		if(m_pBndryCurves[i])
		{
			delete m_pBndryCurves[i];
			m_pBndryCurves[i] = NULL;
		}
		if(m_pIn_S[i])
		{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}
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
	CDrObject* pObject;
	CDListMgr* pNodeList;
	////////////////////////////////////// unload CNodes/delete:private
	pNodeList = GetCNodeList();
    //////////////////////////////////////
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //CNode
		/////////////////////////////////////////////
		if(pObject && (pObject->GetLevelType() == LEVEL_GRAPA))
		{
			CDListMgr* pPatchList = pObject->GetPatchList();
		///////////////////////
			int index = pPatchList->GetObjectIndex(this);
			if(index>=0)
				pPatchList->RemoveObject(index); //curve
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
			CDListMgr* pPatchList = pObject->GetPatchList();
			int index = pPatchList->GetObjectIndex(this);
			if(index>=0)
				pPatchList->RemoveObject(index); //curve
		/////////////////////////
		}
	//////////
	}
	////////////////////////////////////// unload Nodes/No delete:public
	pNodeList = GetNodeList();
    //////////////////////////////////////
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
	///////////////////////////////////// 
	while(!(GetLabelList()->IsEmpty()))// delete:private
	{
		pObject = (CDrObject*)(GetLabelList()->RemoveHead());
		delete pObject;	//delete:private	
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
	//////////////////////////////////////////////////////// CopyList
//	if(!(pAdd->m_SolidList.IsEmpty()) )
//		m_SolidList.AddTail(&(pAdd->m_SolidList) ); 
	if(!(pAdd->m_CurveList.IsEmpty()) )
		m_CurveList.AddTail(&(pAdd->m_CurveList) );
	/////////////////////////////////////////////// GORDONTypeInput
	if(!(pAdd->m_VCurveList.IsEmpty()) )
		m_VCurveList.AddTail(&(pAdd->m_VCurveList) ); 
	/////////////////////////////////// 
	if(!(pAdd->m_CurveList_U.IsEmpty()) )
		m_CurveList_U.AddTail(&(pAdd->m_CurveList_U) ); 
	if(!(pAdd->m_CurveList_V.IsEmpty()) )
		m_CurveList_V.AddTail(&(pAdd->m_CurveList_V) ); 
	if(!(pAdd->m_CurveList_W.IsEmpty()) )
		m_CurveList_W.AddTail(&(pAdd->m_CurveList_W) ); 
	if(!(pAdd->m_CurveLatchList_U.IsEmpty()) )
		m_CurveLatchList_U.AddTail(&(pAdd->m_CurveLatchList_U) ); 
	if(!(pAdd->m_CurveLatchList_V.IsEmpty()) )
		m_CurveLatchList_V.AddTail(&(pAdd->m_CurveLatchList_V) ); 
	if(!(pAdd->m_CurveLatchList_W.IsEmpty()) )
		m_CurveLatchList_W.AddTail(&(pAdd->m_CurveLatchList_W) ); 
	if(!(pAdd->m_ElperSegList_T.IsEmpty()) )
		m_ElperSegList_T.AddTail(&(pAdd->m_ElperSegList_T) ); 
	///
	m_bAdvancedEnd_U	= pAdd->m_bAdvancedEnd_U;
	m_pCornerTwist_U	= pAdd->m_pCornerTwist_U;// it is full,if TW_USER
	m_TwistMethod_U		= pAdd->m_TwistMethod_U;
	///
	m_nNodes_S			= pAdd->m_nNodes_S;			// for Tensor Product
	m_nNodes_T			= pAdd->m_nNodes_T;
	m_bAdvancedEnd_V	= pAdd->m_bAdvancedEnd_V;
	m_pCornerTwist_V	= pAdd->m_pCornerTwist_V;// it is full,if TW_USER
	m_TwistMethod_V		= pAdd->m_TwistMethod_V;
	///
 	if(!(pAdd->m_EndList_U.IsEmpty()) )
		m_EndList_U.AddTail(&(pAdd->m_EndList_U) ); 
 	if(!(pAdd->m_EndList_V.IsEmpty()) )
		m_EndList_V.AddTail(&(pAdd->m_EndList_V) ); 
	///////////////////////////////////////////////////////
	m_bSkewed			= pAdd->m_bSkewed;
	m_bLinSpr			= pAdd->m_bLinSpr;
	m_bLinSnu			= pAdd->m_bLinSnu;
	////////////////////////////// 
	m_nSegUnif_T		= pAdd->m_nSegUnif_T;
	m_bClosed_T			= pAdd->m_bClosed_T;
	m_nMaxINodes_T		= pAdd->m_nMaxINodes_T;
	m_nMaxCNodes_T		= pAdd->m_nMaxCNodes_T;
	m_nMaxCurves_S		= pAdd->m_nMaxCurves_S;
	m_nMaxCurves_T		= pAdd->m_nMaxCurves_T;
	m_nPatchObjectType	= pAdd->m_nPatchObjectType;
	///////////////////////////////////////////////////////////	
    for(int i = 0; i<4; i++)              // 
    {
    	m_CurveID[i]	= pAdd->m_CurveID[i];
    	m_CuLatch[i]	= pAdd->m_CuLatch[i];
    }
	///////////////////////////////////////////////////////////	
   	m_nSegs_T			= pAdd->m_nSegs_T;
	/////////////////////////////////////////// DirtyPatch in EyeSpace
	m_FromPtLocal_T		= pAdd->m_FromPtLocal_T;
	m_FromPtWorld_T		= pAdd->m_FromPtWorld_T;
	m_FromPtEye_T		= pAdd->m_FromPtEye_T;
	m_ToPtLocal_T		= pAdd->m_ToPtLocal_T;
	m_ToPtWorld_T		= pAdd->m_ToPtWorld_T;
	m_ToPtEye_T			= pAdd->m_ToPtEye_T;	
	m_dLen_T			= pAdd->m_dLen_T;
	m_dLenEye_T			= pAdd->m_dLenEye_T;
	m_wLen_T			= pAdd->m_wLen_T;
	m_wLenEye_T			= pAdd->m_wLenEye_T;
	m_vAxis_T			= pAdd->m_vAxis_T;	
	m_vAxisEye_T		= pAdd->m_vAxisEye_T;	
	/////////////////////
	m_pFromIDNode_T			= pAdd->m_pFromIDNode_T;
	m_pToIDNode_T				= pAdd->m_pToIDNode_T;
	/////////////////////////////////////////// Rotate
	m_bAxis_T			= pAdd->m_bAxis_T;	// if Axis Input
	m_nAxis_T			= pAdd->m_nAxis_T;		// 1=X/2=Y/3=Z
	m_bNegative_T		= pAdd->m_bNegative_T;
	m_CircleType_T		= pAdd->m_CircleType_T;
	m_dAng_1_T			= pAdd->m_dAng_1_T;
	m_dAng_2_T			= pAdd->m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	m_nTwistType_T			= pAdd->m_nTwistType_T;
	if(!(pAdd->m_TwistList_T.IsEmpty()) )
		m_TwistList_T.AddTail(&(pAdd->m_TwistList_T) );
	m_nScaleType_T			= pAdd->m_nScaleType_T;
	if(!(pAdd->m_ScaleList_T.IsEmpty()) )
		m_ScaleList_T.AddTail(&(pAdd->m_ScaleList_T) );
	///
	m_bIncTwist_T		= pAdd->m_bIncTwist_T;	// Incremental?
	m_bIncScale_T		= pAdd->m_bIncScale_T;	// for Sweep
	m_TwistMult_T		= pAdd->m_TwistMult_T;
	m_ScaleMult_T		= pAdd->m_ScaleMult_T;	// for Sweep
	m_TwistStart_T		= pAdd->m_TwistStart_T;
	m_ScaleStart_T		= pAdd->m_ScaleStart_T;	// for Sweep
	///////////////////////////////////////////
	m_nOut_S			= pAdd->m_nOut_S;		
	m_nOut_T			= pAdd->m_nOut_T;		
    ////////////////////////////////////// Memory
    for(i = 0; i<4; i++)              // 
    {
		m_pBndryCurves[i]	= pAdd->m_pBndryCurves[i];
    	m_pIn_S[i]			= pAdd->m_pIn_S[i];
    }	 
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
	m_Class_T			= pAdd->m_Class_T;			// k 
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
	m_pNormals			= pAdd->m_pNormals;				// Normals
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
	m_bGenBCurve		= pAdd->m_bGenBCurve;
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
	//////////////////////////////////////////////////////// CopyList
//	if(!(m_SolidList.IsEmpty()) )
//		pAdd->m_SolidList.AddTail(&m_SolidList ); 
	if(!(m_CurveList.IsEmpty()) )
		pAdd->m_CurveList.AddTail(&m_CurveList );
	///////////////////////////////////////////////// GordonTypeInput
	if(!(m_VCurveList.IsEmpty()) )
		pAdd->m_VCurveList.AddTail(&m_VCurveList ); 
	/////////////////////////////////// 
	if(!(m_CurveList_U.IsEmpty()) )
		pAdd->m_CurveList_U.AddTail(&m_CurveList_U ); 
	if(!(m_CurveList_V.IsEmpty()) )
		pAdd->m_CurveList_V.AddTail(&m_CurveList_V ); 
	if(!(m_CurveList_W.IsEmpty()) )
		pAdd->m_CurveList_W.AddTail(&m_CurveList_W ); 
	if(!(m_CurveLatchList_U.IsEmpty()) )
		pAdd->m_CurveLatchList_U.AddTail(&m_CurveLatchList_U ); 
	if(!(m_CurveLatchList_V.IsEmpty()) )
		pAdd->m_CurveLatchList_V.AddTail(&m_CurveLatchList_V ); 
	if(!(m_CurveLatchList_W.IsEmpty()) )
		pAdd->m_CurveLatchList_W.AddTail(&m_CurveLatchList_W ); 
	if(!(m_ElperSegList_T.IsEmpty()) )
		pAdd->m_ElperSegList_T.AddTail(&m_ElperSegList_T ); 
	///
	pAdd->m_nNodes_S		= m_nNodes_S;			// for Tensor Product
	pAdd->m_nNodes_T		= m_nNodes_T;
	pAdd->m_bAdvancedEnd_U	= m_bAdvancedEnd_U;
	pAdd->m_pCornerTwist_U	= m_pCornerTwist_U;// it is full,if TW_USER
	pAdd->m_TwistMethod_U	= m_TwistMethod_U;
	///
	pAdd->m_bAdvancedEnd_V	= m_bAdvancedEnd_V;
	pAdd->m_pCornerTwist_V	= m_pCornerTwist_V;// it is full,if TW_USER
	pAdd->m_TwistMethod_V	= m_TwistMethod_V;
	///
 	if(!(m_EndList_U.IsEmpty()) )
		pAdd->m_EndList_U.AddTail(&m_EndList_U ); 
 	if(!(m_EndList_V.IsEmpty()) )
		pAdd->m_EndList_V.AddTail(&m_EndList_V ); 
	////////////////////////////////////////////////////////   
	pAdd->m_bSkewed			= m_bSkewed;
	pAdd->m_bLinSpr			= m_bLinSpr;
	pAdd->m_bLinSnu			= m_bLinSnu;
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
	pAdd->m_wLen_T			= m_wLen_T;
	pAdd->m_wLenEye_T		= m_wLenEye_T;
	pAdd->m_vAxis_T			= m_vAxis_T;	
	pAdd->m_vAxisEye_T		= m_vAxisEye_T;	
	/////////////////////
	pAdd->m_pFromIDNode_T		= m_pFromIDNode_T;
	pAdd->m_pToIDNode_T			= m_pToIDNode_T;
	/////////////////////////////////////////// Rotate
	pAdd->m_bAxis_T			= m_bAxis_T;	// if Axis Input
	pAdd->m_nAxis_T			= m_nAxis_T;		// 1=X/2=Y/3=Z
	pAdd->m_bNegative_T		= m_bNegative_T;
	pAdd->m_CircleType_T	= m_CircleType_T;
	pAdd->m_dAng_1_T		= m_dAng_1_T;
	pAdd->m_dAng_2_T		= m_dAng_2_T;
	/////////////////////////////////////////// Duct/Sweep
	pAdd->m_nTwistType_T		= m_nTwistType_T;
	if(!m_TwistList_T.IsEmpty())
		pAdd->m_TwistList_T.AddTail(&m_TwistList_T);
	pAdd->m_nScaleType_T		= m_nScaleType_T;
	if(!m_ScaleList_T.IsEmpty())
		pAdd->m_ScaleList_T.AddTail(&m_ScaleList_T);
	///
	pAdd->m_bIncTwist_T		= m_bIncTwist_T;	// Incremental?
	pAdd->m_bIncScale_T		= m_bIncScale_T;	// for Sweep
	pAdd->m_TwistMult_T		= m_TwistMult_T;
	pAdd->m_ScaleMult_T		= m_ScaleMult_T;	// for Sweep
	pAdd->m_TwistStart_T	= m_TwistStart_T;
	pAdd->m_ScaleStart_T	= m_ScaleStart_T;	// for Sweep
	//////////////////////////////////////
	pAdd->m_nOut_S			= m_nOut_S;		
	pAdd->m_nOut_T			= m_nOut_T;		
    ////////////////////////////////////// Memory
    for(i = 0; i<4; i++)              // 
    {
		pAdd->m_pBndryCurves[i] = m_pBndryCurves[i];
    	pAdd->SetMemIn(m_pIn_S[i],i);
    }	 
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
	pAdd->m_Class_T			= m_Class_T;			// k 
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
	pAdd->m_pNormals		= m_pNormals;			// Normals
	pAdd->m_pTangents_T		= m_pTangents_T;		// Tangents
	pAdd->m_pCurvatures_T	= m_pCurvatures_T;		// Curvatures
    //////////////////////////////////////////////////////////////////// Output
    pAdd->m_Ratio_T			= m_Ratio_T;				// for OneSegment Linear Only
	//////////////////////////////////////////////////////////////////// Triangular Patch
	if(!(m_TriangleList.IsEmpty()) )
		pAdd->m_TriangleList.AddTail(&m_TriangleList ); 
	//////////////////////////////  Globals:
	pAdd->m_nOutGlo_S		= m_nOutGlo_S;			//  Total Output in each side of entire Base Patch
	pAdd->m_bGenBCurve		= m_bGenBCurve;
	///////////////////////////////////	
	return;
}		

void CDrPatch::Pack_drPipe(CString* pstrCard)
{

	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_PatchTypes;i++)
   		if(PaTypes[i].num == PATCH) 
   		{
   			name = PaTypes[i].ObjName;
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
				,	m_nMaxCNodes_T	//  number of Total CONTROL points: ALWAYS BEZIER		 // NOT USED
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
    if(m_PatchType == PA_TENSOR || m_PatchType == PA_COONS||m_PatchType == PA_GORDON)
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
				,	m_pNum_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_T		//  IsClosed_T
				,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
				,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nDim_T		//  3= NonRational / 4 = Rational
				,	m_nMaxCurves_T	//  Total Number of Patches 
				,	m_pNum_t_T		//  Number of Output Segments Array in T-Dir for each patch
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
			
int CDrPatch::Generate_Normal3(pWORLD pOut)	// Triangular Patch Normals
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOut		= (int)m_nOut;  // for now
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	for (int i =0; i<nOut; i++)
		Math3D.Cross3DPts(m_pTangents_S+i,m_pTangents_T+i,pOut+i);
	////////////////////////////////////////////
//	delete pTan_S;
//	delete pTan_T;
	/////////
	return 0;

}
			
int CDrPatch::Generate_Tangents_N_Normal3(pWORLD pOut)	// Triangular Patch Normals
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOut		= (int)m_nOut;  // for now
	////////////////////////////////////////////
	m_pTangents_S = new WORLD[nOut];
	m_pTangents_T = new WORLD[nOut];
	////////////////////////////////// Generate Tangents
	if(Generate_Tangent3(m_pTangents_S,1,m_pTangents_T,2)<0)
		////////////////////////////	
		{
			AfxMessageBox("ERROR:\nInternal Problem:\nCDrPatch:\nGenerate_Normal3");
			return -1;
		}	
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	for (int i =0; i<nOut; i++)
		Math3D.Cross3DPts(m_pTangents_S+i,m_pTangents_T+i,pOut+i);
	////////////////////////////////////////////
//	delete pTan_S;
//	delete pTan_T;
	/////////
	return 0;

}
			
int CDrPatch::Generate_Tangent3(pWORLD pOut,int nDir)	// Triangular Patches
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
    if( m_PatchType == PA_COONS)
    {
		///////////////////
		CPat_Tan3 Pat_Tan3;
		//////////////////////////////////////////////////////////////////////
		nOutActual	= Pat_Tan3.MakeTangentsInOneDir
				(
					PA_DECAS		//	deCasteljau SubDivision Method
				,	&m_TriangleList	//	Patch Triangle List
				,	m_bClosed_S		//  IsClosed_S
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nSegUnif_S	//  Number of Output Segments in ALL Dir & ALL patches
				,	m_nMaxCNodes_T	//  number of Total CONTROL points: ALWAYS BEZIER	// NOT USED
					//////////////////////////////  Globals:
				,	m_nOut_S		//  Total Output in each side of entire Patch
					//////////
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut			//  Total Output Tangent Points Array in S-dir
				,	nDir			//	direction 1=S/2=T/3=R
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
			
int CDrPatch::Generate_Tangent3(pWORLD pOut_S,int nDir_1,pWORLD pOut_T,int nDir_2)	// Triangular Patches
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOutActual;
	int nOut		= (int)m_nOut;  // for now
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
    if( m_PatchType == PA_COONS)
    {
		///////////////////
		CPat_Tan3 Pat_Tan3;
		//////////////////////////////////////////////////////////////////////
		nOutActual	= Pat_Tan3.MakeTangents
				(
					PA_DECAS		//	deCasteljau SubDivision Method
				,	&m_TriangleList	//	Patch Triangle List
				,	m_bClosed_S		//  IsClosed_S
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nSegUnif_S	//  Number of Output Segments in ALL Dir & ALL patches
				,	m_nMaxCNodes_T	//  number of Total CONTROL points: ALWAYS BEZIER	// NOT USED
					//////////////////////////////  Globals:
				,	m_nOut_S		//  Total Output in each side of entire Patch
					//////////
				,	m_pIn			//  Total Input CONTROL Points Array
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	pOut_S			//  Total Output Tangent Points Array in S-dir
				,	nDir_1			//	direction 1=S/2=T/3=R
				,	pOut_T			//  Total Output Tangent Points Array in T-dir
				,	nDir_2			//	direction 1=S/2=T/3=R
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

int CDrPatch::Get_Tan_N_NorAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
//														WORLD& Normal)	
													WORLD& Normal,double dSameNessRatio)
// Quadrilateral Normal at an Input Node
{
	/////////////////////////////
	RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	////////////////////////////////// Generate Tangents
//	if(Get_TangentsAtaNode_3(wNodeCoord,Tangent_U,Tangent_V)<0)
	if(Get_TangentsAtaNode_3(wNodeCoord,Tangent_U,Tangent_V,dSameNessRatio)<0)
	////////////////////////////	
	{
		AfxMessageBox("ERROR:\nInternal Problem:\nGet_TangentsAtaNode_4");
		return -1;
	}	
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	Math3D.Cross3DPts(&Tangent_U,&Tangent_V,&Normal);
	/////////
	return 0;

}

//int CDrPatch::Get_A_Tan_AtaNode_3(WORLD wNodeCoord,WORLD& Tangent,int& DirTan)	
int CDrPatch::Get_A_Tan_AtaNode_3(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,	
														double dSameNessRatio)
// Triangular Normal at an Input Node
{
	/////////////////////////////
	RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	////////////////////////////////// Generate Tangents
	int nResult = 0;
	////////////////
	CPat_Tan3* Pat_Tan3;
	//////////////////////////////////////////////////////////////////////
	nResult = Pat_Tan3->DC_GetaTangentAtaNode(wNodeCoord,Tangent,DirTan,
								m_nDim_S,m_bClosed_S,m_nMaxCNodes_T,m_nSegUnif_S,
								&m_TriangleList,m_pInWts,m_pIn,dSameNessRatio);
	////////////////////////////	
	if(nResult<0)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGet_A_TangentAtaNode_3");
		return -1;
	}	
	////////////
	return 0;
	///////

}

//int CDrPatch::Get_TangentsAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V)	// Quadrilateral Patch Tangents
int CDrPatch::Get_TangentsAtaNode_3(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,	// Quadrilateral Patch Tangents
																double dSameNessRatio)
{
	int nResult = 0;
	////////////////
	CPat_Tan3* Pat_Tan3;
	//////////////////////////////////////////////////////////////////////
	nResult = Pat_Tan3->DC_GetTangentsForNormalAtaNode(wNodeCoord,Tangent_U,Tangent_V,
								m_nDim_S,m_bClosed_S,m_nMaxCNodes_T,m_nSegUnif_S,
								&m_TriangleList,m_pInWts,m_pIn,dSameNessRatio);
	////////////////////////////	
	if(nResult<0)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGet_TangentsAtaNode_3");
		return -1;
	}	
	////////////
	return 0;
	///////
}	
			
int CDrPatch::Get_Tan_N_NorAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,
//																			WORLD& Normal)	
													WORLD& Normal,double dSameNessRatio)
// Quadrilateral Normal at an Input Node
{
	/////////////////////////////
	RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	////////////////////////////////// Generate Tangents
//	if(Get_TangentsAtaNode_4(wNodeCoord,Tangent_U,Tangent_V)<0)
	if(Get_TangentsAtaNode_4(wNodeCoord,Tangent_U,Tangent_V,dSameNessRatio)<0)
	////////////////////////////	
	{
		AfxMessageBox("ERROR:\nInternal Problem:\nGet_TangentsAtaNode_4");
		return -1;
	}	
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	Math3D.Cross3DPts(&Tangent_U,&Tangent_V,&Normal);
	/////////
	return 0;

}
			
//int CDrPatch::Get_A_Tan_AtaNode_4(WORLD wNodeCoord,WORLD& Tangent,int& DirTan)	
int CDrPatch::Get_A_Tan_AtaNode_4(WORLD wNodeCoord,WORLD& Tangent,int& DirTan,	
														double dSameNessRatio)
// Quadrilateral Normal at an Input Node
{
	/////////////////////////////
	RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	////////////////////////////////// Generate Tangents
	int nResult = 0;
	////////////////
	CPat_Tan4* Pat_Tan4;
	//////////////////////////////////////////////////////////////////////
	nResult = Pat_Tan4->GetaTangentAtaNode(wNodeCoord,Tangent,DirTan,
								m_nOrder_S-1,m_nMaxCurves_S,m_nMaxCNodes_S,m_nDim_S,
								m_nOrder_T-1,m_nMaxCurves_T,m_nMaxCNodes_T,m_nDim_T,
								m_pInWts,m_pIn,dSameNessRatio);
	////////////////////////////	
	if(nResult<0)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGet_aTangentAtaNode_4");
		return -1;
	}	
	////////////
	return 0;
	///////
}
			
int CDrPatch::Generate_Normal4(pWORLD pOut)	// Quad Patch Normals
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOut		= (int)m_nOut;  // for now
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	for (int i =0; i<nOut; i++)
		Math3D.Cross3DPts(m_pTangents_S+i,m_pTangents_T+i,pOut+i);
	////////////////////////////////////////////
//	delete pTan_S;
//	delete pTan_T;
	/////////
	return 0;

}

//int CDrPatch::Get_TangentsAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V)	// Quadrilateral Patch Tangents
int CDrPatch::Get_TangentsAtaNode_4(WORLD wNodeCoord,WORLD& Tangent_U,WORLD& Tangent_V,	// Quadrilateral Patch Tangents
																double dSameNessRatio)
{
	int nResult = 0;
	////////////////
	CPat_Tan4* Pat_Tan4;
	//////////////////////////////////////////////////////////////////////
	nResult = Pat_Tan4->GetTangentsAtaNode(wNodeCoord,Tangent_U,Tangent_V,
								m_nOrder_S-1,m_nMaxCurves_S,m_nMaxCNodes_S,m_nDim_S,
								m_nOrder_T-1,m_nMaxCurves_T,m_nMaxCNodes_T,m_nDim_T,
								m_pInWts,m_pIn,dSameNessRatio);
	////////////////////////////	
	if(nResult<0)
	{
		AfxMessageBox("Internal Problem:\nCDrPatch:\nGet_TangentsAtaNode_4");
		return -1;
	}	
	////////////
	return 0;
	///////
}	

int CDrPatch::Generate_Tangents_N_Normal4(pWORLD pOut)	// Quadrilateral Patch Normals
{
	////////////////////////////////// Now Generate
// if m_nOut is longer than 32565 call TilePatch 
// To break into number of subPatches with each with nOut < 32565
	//////////////////////////////////////////// 
	int nOut		= (int)m_nOut;  // for now
	////////////////////////////////////////////
	m_pTangents_S = new WORLD[nOut];
	m_pTangents_T = new WORLD[nOut];
	////////////////////////////////// Generate Tangents
	if(Generate_Tangent4(m_pTangents_S, 1)<0)
		////////////////////////////	
		{
			AfxMessageBox("ERROR:\nInternal Problem:\nCDrPatch:\nGenerate_Normal4\nm_pTangents_S");
			return -1;
		}	
	////////////
	if(Generate_Tangent4(m_pTangents_T, 2)<0)
		////////////////////////////	
		{
			AfxMessageBox("ERROR:\nInternal Problem:\nCDrPatch:\nGenerate_Normal4\nm_pTangents_T");
			return -1;
		}	
	////////////////////////////////// Generate Normals
	C3DMath	Math3D;
	///////////////
	for (int i =0; i<nOut; i++)
		Math3D.Cross3DPts(m_pTangents_S+i,m_pTangents_T+i,pOut+i);
	////////////////////////////////////////////
//	delete pTan_S;
//	delete pTan_T;
	/////////
	return 0;

}
			
int CDrPatch::Generate_Tangent4(pWORLD pOut, int nDir)	// Quadrilateral Patch Tangents
{
	//		nDir = 1		-> S-direction Tangents
	//		nDir = 2		-> T-direction Tangents
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
		// for rotation:
		pINT pNum_t_T = (m_CurveType_T == CP_CIRCLE)?m_pNum_t_Ex_T:m_pNum_t_T;// Circle Special
		///////////////////
		CPat_Tan4* pSurface;
		//////////////////////////////////////////////////////////////////////
		if(nDir == 2)					// T-Direction
		{
			nOutActual	= pSurface->MakeTangents
				(
					m_bClosed_S		//  IsClosed_S
				,	m_nOrder_S-1	//  Degree in S-Dir: ALWAYS BEZIER
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nMaxCNodes_S	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nMaxCurves_S	//  Total Number of Patches 
				,	  pNum_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_T		//  IsClosed_T
				,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
				,	m_nDim_T		//  3= NonRational / 4 = Rational
				,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nMaxCurves_T	//  Total Number of Patches 
				,	  pNum_t_T			//  Number of Output Segments Array in T-Dir for each patch
				,	m_pDis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	m_pIn			//  Total Input CONTROL Points Array
				,	pOut			//  Total Output Points Array
				);
			////////////////////////////
		}
		else
		if(nDir == 1)					// S-Direction
		{
			/////////////////////////////////////////////////////////////////// NOTE
			//	In CPat_Tan4::MakeTangents:
			//		It is always the PARTIALS wrt V that are computed
			//		So, for PARTIALS wrt U: Parametric directions are SWITCHED
			///////////////////////////////////////////////////////// Switch Control Locations:U<->V
			int i,j,k;
			////

			pWORLD pIn		= new WORLD[m_nMaxCNodes_S*m_nMaxCNodes_T];
			pDOUBLE pInWts	= new double[m_nMaxCNodes_S*m_nMaxCNodes_T];
			pWORLD pOutTem	= new WORLD[m_nOut_S*m_nOut_T];
			/////////////////////////////////////// Switch
			k=-1;
			/////
			for (i=0;i<m_nMaxCNodes_S;i++)
			{
				for (j=0;j<m_nMaxCNodes_T;j++)
				{
					k++;
					*(pIn+k)	= *(m_pIn    + j*m_nMaxCNodes_S + i);
					*(pInWts+k) = *(m_pInWts + j*m_nMaxCNodes_S + i);
				}
			}
			///////////////////////////////////////
			nOutActual	= pSurface->MakeTangents
				(
					m_bClosed_T		//  IsClosed_T
				,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
				,	m_nDim_T		//  3= NonRational / 4 = Rational
				,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nMaxCurves_T	//  Total Number of Patches 
				,	  pNum_t_T		//  Number of Output Segments Array in T-Dir for each patch
				,	m_pDis_t_T		//  Output t distribution Pts. for Ratio Business				
				,	m_bClosed_S		//  IsClosed_S
				,	m_nOrder_S-1	//  Degree in S-Dir: ALWAYS BEZIER
				,	m_nDim_S		//  3= NonRational / 4 = Rational
				,	m_nMaxCNodes_S	//  number of CONTROL points: ALWAYS BEZIER
				,	m_nMaxCurves_S	//  Total Number of Patches 
				,	  pNum_t_S		//  Number of Output Segments Array in S-Dir for each patch
				,	m_pDis_t_S		//  Output t distribution Pts. for Ratio Business				
				,	  pInWts		//  Rational Bezier Weights Array at input Control Pts		
				,	  pIn			//  Total Input CONTROL Points Array
				,	pOutTem			//  Total Output Points Array
				);
			///////////////////////////////////////////////////// Switch pOut
			k=-1;
			/////
			for (i=0;i<m_nOut_T;i++)
			{
				for (j=0;j<m_nOut_S;j++)
				{
					k++;
					*(pOut+k)	= *(pOutTem    + j*m_nOut_T + i);
				}
			}
			///////////////// delete
			delete [] pIn;
			delete [] pInWts;
			delete [] pOutTem;
			/////////////////
		}
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
			
int CDrPatch::GetCurrentBezSeg_N_st_4(int nOut_S,int nOut_T,int& nCurBz_S,int& nCurBz_T,
									  double& sCur,double& tCur)	// Quadrilateral Patches
{
	// given:	nOut_S & nOut_T indices of total output
	// find:	which Bezier segment it belongs to and its s & t parametric values	
	//////////////////////////////////////////////////////////////////////////// generate Patch Pts		 	   	
	pINT pNum_t_S = (m_CurveType_S == CP_CIRCLE)?m_pNum_t_Ex_S:m_pNum_t_S;// Circle Special
	//////////////
	BOOL bGot_S = FALSE;
	BOOL bGot_T = FALSE;
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
	//////////////////////////////////////////////////////////////////// T-dir
	for(i=0;i<m_nMaxCurves_T;i++)
	{
		nt_AccumOld	= nt_Accum;
		nt_NewTot	= *(m_pNum_t_T + i);
		nt_Accum	+= nt_NewTot;
		////////////////////
		if(nOut_T<nt_Accum || ((i == m_nMaxCurves_T)&&(nOut_T==nt_Accum)) )
		{
			bGot_T		= TRUE;
			nCurBz_T	= i;
			//////////////////////////////////// s valu
			nt_Cur		= nOut_T - nt_AccumOld; 
			double del	= 1./double(nt_NewTot);
			tCur		= ((double)nt_Cur)*del;
			////////////
			break;
		}
	}
	//////////////////////
	if(!bGot_S || !bGot_T)
		return MA_ERROR;
	else
		return MA_OK;
	///////
}
	
int CDrPatch::GetAPointOnCurrentBezSeg_4(int nOut_S,int nOut_T,pWORLD pOut,pDOUBLE pOutWt)
{
	int nResult = MA_OK;
	////////////////////
	int nCurBz_S,nCurBz_T;
	double sCur,tCur;
	//////////////////////////////////////////////////// Get CurBzSeg and S & t params
	nResult = GetCurrentBezSeg_N_st_4(nOut_S,nOut_T,nCurBz_S,nCurBz_T,sCur,tCur);
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////
	CSurface4 Surface4;
	//////////////////////////////////////////////////// Go Compute for the currentPatch
	nResult = Surface4.HO_GetAPointOnABezSegPatch		// RATIONAL BEZIER Patches
					(
						m_bClosed_S		//  IsClosed_S
					,	m_nOrder_S-1	//  Degree in S-Dir: ALWAYS BEZIER
					,	m_nDim_S		//  3= NonRational / 4 = Rational
					,	m_nMaxCNodes_S	//  number of CONTROL points: ALWAYS BEZIER
					,	m_nMaxCurves_S	//  Total Number of Patches 
					,	nCurBz_S// Output s distribution Pts.				
					,	sCur	// Output s distribution Pts.				
					,	m_bClosed_T		//  IsClosed_T
					,	m_nOrder_T-1	//  Degree in T-Dir: ALWAYS BEZIER
					,	m_nDim_T		//  3= NonRational / 4 = Rational
					,	m_nMaxCNodes_T	//  number of CONTROL points: ALWAYS BEZIER
					,	m_nMaxCurves_T	//  Total Number of Patches 
					,	nCurBz_T// Output s distribution Pts.				
					,	tCur	// Output t distribution Pts.				
					,	m_pInWts		//  Rational Bezier Weights Array at input Control Pts		
					,	m_pIn			//  Total Input CONTROL Points Array
					,	pOut			//  Total Output Points Array
					,	pOutWt			//  Total Output Wts Array(WE MAY NEED FOR RATIONAL SOLIDS)
					);
	////////
	return nResult;
}

BOOL CDrPatch::CullWorld(WORLD VDir)
{

	CDListMgr* pList;
	POSITION pos;
	BOOL bCulledPatch = TRUE,bCulled;
	//////////////////////
	pList = GetFE2DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		bCulled = pObject->CullWorld(VDir);
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
	pList = GetFE2DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		bCulled = pObject->CullScreen(pViewM);
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
	pList = GetFE2DList();
	///////////////////////////////
	if(!pList->IsEmpty())
	{
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
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
	
	pList = GetFE2DList();
	///////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		/////////////////////////////////////
//		pPoly->Calc_ScreenRect(&BoundRect);
		BoundRect = pObject->GetBoundingRect();
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
	
	pList = GetFE2DList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		//////////////////////////////////// Compute Centroid info 
		pObject->Calc_CentroidWorld();
		//////////////////////////////////// Normal
		pObject->Calc_NormalWorld();
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
	
	pList = GetFE2DList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		if(pObject->IsCulled())
			return;
		//////////////////////////////////// Compute Centroid info
		pObject->Calc_CentroidEye();
		//////////////////////////////////// Normal	
		pObject->TransformNormalToEye(pViewM);
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
	
	pList = GetFE2DList();
	/////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pList->GetNextObject(pos);
		///////////////////////////
		if(pObject->IsCulled())
			return;
		//////////////////////////////////// Compute Centroid info
		pObject->Calc_CentroidScreen3D(dScale_U,dScale_V);
		///////////	
		pObject->ProjectNormalToScreen3D
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
	///////////////////////////////////////////// about tobe Deleted
	if(IsToBeDeleted())
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,RGB(255,255,255));	// WHITE
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
	//////////////////////////////////////////////
 	if(m_nMeshElemDim == 1 || m_nMeshElemDim == 2)
	{
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
	}
	else
	///////////////////////////////////////////// 
	if(m_nMeshElemDim == 0)
	{
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
			int x,y,len = 3;
			x = m_pOutDP[i].x;
			y = m_pOutDP[i].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		}
		//////////
		FreeMemDP(m_pOutDP);
		m_pOutDP = NULL;	
	}
/*
	/////////////////////////////// FreeMemory
	FreeMem(m_pOut);
	FreeMemD(m_pOutWts);
	m_pOut		= NULL;   	
	m_pOutWts	= NULL;   	
*/   	
}

void CDrPatch::GoDoIt_3(CDC* PtrDC)
{ 

    //////////
	if(!m_bDirty)
		return;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
 	if(m_nMeshElemDim == 1 || m_nMeshElemDim == 2)
	{
		CDListMgr* pTriList = GetTriangleList();
		if(pTriList->IsEmpty() )
			return;
		////////////////////////
		int nTriangle	= pTriList->GetCount();
		////////////////////////////////// Save PatchInfo
		// Each Output Triangle should be all the Output Pts.
		// this will require redundancy but simplify,So
		////////////////////////
//		int nOutSeg_S	= GetSegmentCount_S();			
		int nOutSeg_S	= GetOutSegUnif_S();			
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
				AfxMessageBox("CDrPatch::GoDoIt_3\nnType !==1 or 2");
				return;
			}
		}										///////////////////////////// end LIST
	}
	else
	///////////////////////////////////////////// 
	if(m_nMeshElemDim == 0)
	{
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
			int x,y,len = 3;
			x = m_pOutDP[i].x;
			y = m_pOutDP[i].y;
			PtrDC->MoveTo(x-len,y);
			PtrDC->LineTo(x+len,y);
			PtrDC->MoveTo(x,y-len);
			PtrDC->LineTo(x,y+len);
		}
		//////////
		FreeMemDP(m_pOutDP);
		m_pOutDP = NULL;	
	}
/*
	/////////////////////////////// FreeMemory
	FreeMem(m_pOut);
	FreeMemD(m_pOutWts);
	m_pOut		= NULL;   	
	m_pOutWts	= NULL;   	
*/   	
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
	if(!m_pIn)
		RefillCNEyePosForDirtyDraw();
	/////////////////////////////////
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
	/////////////////////////////// FreeMemory
	FreeMem(m_pIn);
	m_pIn = NULL;   	
*/		
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
						CP_BEZIER,m_nMaxCNodes_S,m_bClosed_S,m_nOrder_S,
						CP_BEZIER,m_nMaxCNodes_T,m_bClosed_T,m_nOrder_T,
						&nPatches_S,&nPatches_T);
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

BOOL CDrPatch::IsObjectHit(int nNet,POINT point)
{
	
	if(m_PatSubType == PS_QUADRILAT)
		return IsObjectHit_Alt_4(nNet,point);
	else
	if(m_PatSubType == PS_TRIANGLE)
		return IsObjectHit_3(nNet,point);
	////////////////////////////////////////
	if(m_PatSubType == PS_QUADRILAT)
		return IsObjectHit_4(nNet,point);
	else
	if(m_PatSubType == PS_TRIANGLE)
		return IsObjectHit_3(nNet,point);
	///////////////////////////////
	else
		return FALSE;
}

void CDrPatch::IsObjectHit_YScanLineWidth(POINT n1,POINT n2,POINT point,
										  int& nMinX,int& nMaxX)
{
	///////////////////////////////////////////////// Generated Nodes in 2DScreen Coordinates
	///////////////////////////////// swap
	if(n2.y<n1.y)
	{
		int temp = n1.y;
		n1.y = n2.y;
		n2.y = temp;
		temp = n1.x;
		n1.x = n2.x;
		n2.x = temp;
	}
	///////////////////////////////// Check yScanline intersection
	if(point.y<n1.y || point.y>n2.y) // outside
		return;
	///////////////////////////////// yes intersection, compute and save x
	double dy = (double)(n2.y - n1.y);
	int x  = (int)( (double)(n1.x) + 
					(double)(n2.x - n1.x) * (double)(n2.y - point.y)/dy);
	///////////////////////////////////// compare and adjust
	if(x<nMinX) nMinX = x; 				
	if(x>nMaxX) nMaxX = x; 				
	////////////////////// 				
}	

BOOL CDrPatch::IsObjectHit_Alt_4(int nNet,POINT point)
{
	if(ObjectHit_Generate2DPts()<0)
		return FALSE;
	//////////////////////	
	int	nMinX,nMaxX;
	nMinX = INT_MAX; 
	nMaxX = -INT_MIN; 
	///////////////////////////////////////////////// Generated Nodes in 2DScreen Coordinates
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
			///////////////////////////////// Edge Nodes
			POINT n1,n2;
			n1 = *(m_pOutDP+mold);
			n2 = *(m_pOutDP+m);
			///////////////////
			mold = m;
			///////////////////////////////// ScanLine Width
			IsObjectHit_YScanLineWidth(n1,n2,point,nMinX,nMaxX);
			//////////////////////////////////// check
			if(point.x>=nMinX && point.x<=nMaxX)
			{
				//////////////////////////////////// Free Memory
				if(m_pOutDP)
				{
					FreeMemDP(m_pOutDP);
					m_pOutDP= NULL;
				}
				return TRUE;
			}
			///////
		}	
	}
	///////////////////////////////////////// Continue to Try
	for(i =0; i<m_nOut_S;i++)
	{
		mold 	= i;
		///////////////////////////////
		for(j =1; j<m_nOut_T;j++)
		{
			m = i + j*(m_nOut_S);
			///////////////////////////////// Edge Nodes
			POINT n1,n2;
			n1 = *(m_pOutDP+mold);
			n2 = *(m_pOutDP+m);
			///////////////////
			mold = m;
			///////////////////////////////// ScanLine Width
			IsObjectHit_YScanLineWidth(n1,n2,point,nMinX,nMaxX);
			//////////////////////////////////// check
			if(point.x>=nMinX && point.x<=nMaxX)
			{
				//////////////////////////////////// Free Memory
				if(m_pOutDP)
				{
					FreeMemDP(m_pOutDP);
					m_pOutDP= NULL;
				}
				return TRUE;
			}
			///////
/*
			///////////////////////////////// swap
			if(n2.y<n1.y)
			{
				int temp = n1.y;
				n1.y = n2.y;
				n2.y = temp;
				temp = n1.x;
				n1.x = n2.x;
				n2.x = temp;
			}
			///////////////////////////////// Check yScanline intersection
			if(point.y<n1.y || point.y>n2.y) // outside
				continue;
			///////////////////////////////// yes intersection, compute and save x
			double dy = (double)(n2.y - n1.y);
			int x  = (int)( (double)(n1.x) + 
							(double)(n2.x - n1.x) * (double)(n2.y - point.y)/dy);
			///////////////////////////////////// compare and adjust
			if(x<nMinX) nMinX = x; 				
			if(x>nMaxX) nMaxX = x; 				
			////////////////////// 
*/			
		}	
	}
	////////////////////////////////////////////////// Free Memory
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
	////////////////////////////////////////////////// Finally, Now Check x;
	if(point.x<nMinX || point.x>nMaxX)
		return FALSE;
	else
		return TRUE;
	////////////////
}

BOOL CDrPatch::IsObjectHit_Alt_3(int nNet,POINT point)
{
	if(ObjectHit_Generate2DPts()<0)
		return FALSE;
	//////////////////////	
	int	nMinX,nMaxX;
	nMinX = INT_MAX; 
	nMaxX = -INT_MIN; 
	///////////////////////////////////////////////// Generated Nodes in 2DScreen Coordinates
	return FALSE;
}

int CDrPatch::ObjectHit_Generate2DPts()
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
	if(m_PatSubType == PS_QUADRILAT)
		Generate_Patch4(pOut,pOutWts);
	else
	if(m_PatSubType == PS_TRIANGLE)
		Generate_Patch3(pOut,pOutWts);
	/////////////////////////////////////////////////////////// Need to Project for 2DPos
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}		
	m_pOutDP 	= FixMemDP(m_nOut);		// Output Points
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
		m_pOutDP[j].x = (int)(ScreenPos.x * m_dScale_U);
		m_pOutDP[j].y = (int)(ScreenPos.y * m_dScale_V);
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
   	///////////////////
	return 0;
}

BOOL CDrPatch::IsObjectHit_4(int nNet,POINT point)
{
	int nBndrys = 4;
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
	Generate_Patch4(pOut,pOutWts);
	////////////////////////////////////// No. of Points for Enclosing Patch
	long	nOutRgn = 0;
	int		nOutCur[4],i,j,nOut;
	POINT*	pScrenOutPts[4];
    ////////////////////////////////////// Loop Over All Bndrys
	for (i=0;i<nBndrys;i++)
	{
		nOut = Collect_BoundaryPoints_4(i);
		/////////////////////////////////
		if(nOut<=0)
		{
			AfxMessageBox(
			"Internal Problem:\nCDrPatch::IsObjectHit_4\nnOut<0");
			return FALSE;
		}
		//////////////////////////
		pScrenOutPts[i] = FixMemDP(nOut);
		///////////////////////////////////////
		for(j=0;j<nOut;j++)
			*(pScrenOutPts[i]+j) = *(m_pOutDP+j);
		///////////
		nOutCur[i]	= nOut;
		nOutRgn	   += nOut;
	}
	//////////////////////// FreeMems
	if(pOut)
	{
		FreeMem(pOut);
		pOut = NULL;
	}
	if(pOutWts)
	{
		FreeMemD(pOutWts);
		pOutWts = NULL;
	}
	//////////////////////// delete for last Curve
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
	///////////////////////////////////// Form PolygonalRgn: LP
	POINT*	ptRgn = FixMemDP(nOutRgn);
	//////////////////////////////////
	int		k = -1;
	/////////////////////
	for(i=0;i<nBndrys;i++)
	{
		nOut = nOutCur[i];
		//////////////////
		for(j=0;j<nOut;j++)
		{
			k++;
			////
			ptRgn[k].x = (pScrenOutPts[i]+j)->x;
			ptRgn[k].y = (pScrenOutPts[i]+j)->y;
		}
		/////////////////////////// delete temp.
		FreeMemDP(pScrenOutPts[i]); 
		///////////////////////////
	}
	////////////////////////////////
	CRgn	Poly;
	BOOL bOk = Poly.CreatePolygonRgn( ptRgn, nOutRgn-1, ALTERNATE );
		// Automatically fills the last to Ist, so -1 above
   	////////////////////////////////////////////// Check
	if(bOk)
	{
		if(Poly.PtInRegion(point))
		{
			Poly.DeleteObject();
			////////////////////
			if(ptRgn)
			{
				FreeMemDP(ptRgn);
				ptRgn = NULL;
			}
			////////////////////
      		return TRUE;
		}
	}
	else
	{
		AfxMessageBox(
			"Internal Problem:\nCDrPatch::IsObjectHit\nCreatePolygonRgn");
		Poly.DeleteObject();
		////////////////////
		if(ptRgn)
		{
			FreeMemDP(ptRgn);
			ptRgn = NULL;
		}
		////////////////////
		return FALSE;
	}
	////////////////////
	return FALSE;

}

BOOL CDrPatch::IsObjectBndryHit(int nNet,POINT point,int& iBndry)
{
	
	if(m_PatSubType == PS_QUADRILAT)
		return IsObjectBndryHit_4(nNet,point,iBndry);
	else
	if(m_PatSubType == PS_TRIANGLE)
		return IsObjectBndryHit_3(nNet,point,iBndry);
	///////////////////////////////
	else
		return FALSE;
}

BOOL CDrPatch::IsObjectBndryHit_4(int nNet,POINT point,int& iBndry)
{
	BOOL bHit = FALSE;
	//////////////////
	int nBndrys = 4;
	////////////////////////////////////// Output memory
	pWORLD	pOut	= FixMem(GetLongOutPts());
	pDOUBLE pOutWts = FixMemD(GetLongOutPts());
	////////////////////////////////// Now Generate
	////////////////////////////////////// Need to generate Curves
									////// using XFormed CNodes
	RefillCNEyePosForDirtyDraw();		// for DirtyDraw
	////////////////////////////////
	Generate_Patch4(pOut,pOutWts);
	////////////////////////////////////// No. of Points for Enclosing Patch
	long	nOutRgn = 0;
	int		i,iBoun,nOut;
	//////////////////////////////////////
	nOut = max(m_nOut_S,m_nOut_T);
	POINT*	pScrenOutPts = FixMemDP(nOut);;
    ////////////////////////////////////// Loop Over All Bndrys
	for (iBoun=0;iBoun<nBndrys;iBoun++)
	{
		/////////////////////////////
		nOut = Collect_BoundaryPoints_4(i,pOut,pScrenOutPts);
		/////////////////////////////////
		if(nOut<=0)
		{
			AfxMessageBox(
			"Internal Problem:\nCDrPatch::IsObjectHit_4\nnOut<0");
			return FALSE;
		}
		///////////////////////////////////////////////////////////////// Check
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
					iBndry = iBoun; 
      				bHit = TRUE;
					////////
					break;
				}
			}
			else
			{
				AfxMessageBox(
					"Internal Problem:\nCDrCurve::IsObjectHit\nCreatePolygonRgn");
				Quad.DeleteObject();
				////////////////////
				return FALSE;
			}
			/////////////////////////////// Reset
			ptOld = ptNew;
			Quad.DeleteObject();
			//////////////
		}
		//////////////
		if(bHit)
			break;
	}
	//////////////////////// FreeMems
	FreeMem(pOut);
	FreeMemD(pOutWts);
	FreeMemDP(pScrenOutPts);
	////////////////////////
	return bHit;
}
	
int CDrPatch::Collect_BoundaryPoints_4(int iBndry,pWORLD pOut,POINT* pOutDP)
{
	////////////////////////////////////// No. of Points for Enclosing Bndry
	int			i,j,nOut = 0,nStep,nStart;
	/////////////////////////////////
	//		t=0		 T_2		t=m_nOut_T
	//    s=0|<----------------/|\
	//		 |					|
	//    S_1|		PATCH		|S_2
	//		 |					|
	//       |					|
	//      \|/---------------->|
	// s= m_nOut_S 	  T_1
	//////////////////////////////////
	if(m_PatSubType == PS_QUADRILAT)
	{
		switch(iBndry)
		{
			case 0:								//	dir_S_1
				nStart	= 0;
				nStep	= 1;
				nOut	= m_nOut_S;
				break; 
			case 2:								//	dir_S_2
				nStart	= m_nOut_S*m_nOut_T - 1;
				nStep	= -1;
				nOut	= m_nOut_S;
				break; 
			case 1:								//	dir_T_1
				nStart	= m_nOut_S-1;
				nStep	= m_nOut_S;
				nOut	= m_nOut_T;
				break;
			case 3:								//	dir_T_2 
				nStart	= m_nOut_S*(m_nOut_T - 1);
				nStep	= -m_nOut_S;
				nOut	= m_nOut_T;
				break;
			default:
				break;
		}
	}
	else
	{
		AfxMessageBox(
		"ERROR:\nInternal Problem:\nCDrPatch::Collect_BoundaryPoints_4\nNOT PS_QUADRILAT");
		return -1;
	}
	////////////////////////////////////////////// temp memory
	pWORLD pOutTem	= FixMem(nOut);
	////////////////////////////////////////////// Now Collect
	int k;
	//////
    for(k=0,i = nStart; k<nOut; k++,i+= nStep)
		*(pOutTem+k) = *(pOut+i);
	///////////////////////
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	////////////////////////////////////////////// Project for DirtyDraw	
    for(j = 0; j<nOut; j++)              
	{
    	EyePos.x = pOutTem[j].x;
    	EyePos.y = pOutTem[j].y;
    	EyePos.z = pOutTem[j].z;
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
	if(pOutTem)
	{
		FreeMem(pOutTem); 
		pOutTem	= NULL;
	}		
	////////////////////
	return nOut;
}
	
int CDrPatch::Collect_BoundaryPoints_4(int iBndry)
{
	////////////////////////////////////// No. of Points for Enclosing Bndry
	int			i,j,nOut = 0,nStep,nStart;
	pWORLD		pOut;
	pDOUBLE		pOutWts;
	/////////////////////////////////
	//		t=0		 T_2		t=m_nOut_T
	//    s=0|<----------------/|\
	//		 |					|
	//    S_1|		PATCH		|S_2
	//		 |					|
	//       |					|
	//      \|/---------------->|
	// s= m_nOut_S 	  T_1
	//////////////////////////////////
	if(m_PatSubType == PS_QUADRILAT)
	{
		switch(iBndry)
		{
			case 0:								//	dir_S_1
				nStart	= 0;
				nStep	= 1;
				nOut	= m_nOut_S;
				break; 
			case 2:								//	dir_S_2
				nStart	= m_nOut_S*m_nOut_T - 1;
				nStep	= -1;
				nOut	= m_nOut_S;
				break; 
			case 1:								//	dir_T_1
				nStart	= m_nOut_S-1;
				nStep	= m_nOut_S;
				nOut	= m_nOut_T;
				break;
			case 3:								//	dir_T_2 
				nStart	= m_nOut_S*(m_nOut_T - 1);
				nStep	= -m_nOut_S;
				nOut	= m_nOut_T;
				break;
			default:
				break;
		}
	}
	else
	{
		AfxMessageBox(
		"ERROR:\nInternal Problem:\nCDrPatch::Collect_BoundaryPoints_4\nNOT PS_QUADRILAT");
		return -1;
	}
	////////////////////////////////////////////// temp memory
	pOut	= FixMem(nOut);
	pOutWts	= FixMemD(nOut);
	////////////////////////////////////////////// Now Collect
	int k;
	//////
    for(k=0,i = nStart; k<nOut; k++,i+= nStep)
		*(pOut+k) = *(m_pOut+i);
	///////////////////////
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	////////////////////////////////////////////// Memory
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
	/////////////////////////////
	m_pOutDP 	= FixMemDP(nOut);		// Output Points
	////////////////////////////////////////////// Project for DirtyDraw	
    for(j = 0; j<nOut; j++)              
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
		m_pOutDP[j].x = (int)(ScreenPos.x * m_dScale_U);
		m_pOutDP[j].y = (int)(ScreenPos.y * m_dScale_V);
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
	////////////////////
	return nOut;

}

BOOL CDrPatch::IsObjectHit_3(int nNet,POINT point)
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
	Generate_Patch3(pOut,pOutWts);
	////////////////////////////////////// No. of Points for Enclosing Patch:Loop Triangles
	long	nOutRgn;
	int		j,nOut;
	POINT*	ptRgn;
    ///////////////////////////////////////////////// Generated Nodes in EYE Coordinates
	CDListMgr* pTriList = GetTriangleList();
	if(pTriList->IsEmpty() )
		return FALSE;
	////////////////////////
	int nTriangle	= pTriList->GetCount();
	/////////////////////////////////////////////////////////////////// LOOP: Triangle List
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int nType		= pTri->GetType();
		int iOutGlo		= pTri->GetiOutGlo();
		int jOutGlo		= pTri->GetjOutGlo();
		/////////////////////////////////////////////////////////////////// Bot & Top Triangle
		nOut = Collect_BoundaryPoints_3(iOutGlo,jOutGlo,nType);	
		/////////////////////////////////
		if(nOut<=0)
		{
			AfxMessageBox(
			"Internal Problem:\nCDrPatch::IsObjectHit_3\nnOut<0");
			return FALSE;
		}
		//////////////////////////
		nOutRgn		= nOut;
		ptRgn		= FixMemDP(nOutRgn);
		///////////////////////////////////////
		for(j=0;j<nOutRgn;j++)
			*(ptRgn+j) = *(m_pOutDP+j);
		//////////////////////// FreeMems
		if(m_pOutDP)
		{
			FreeMemDP(m_pOutDP);
			m_pOutDP= NULL;
		}
		////////////////////////////////
		CRgn	Poly;
		BOOL bOk = Poly.CreatePolygonRgn( ptRgn, nOutRgn, ALTERNATE );
   		////////////////////////////////////////////// Check
		if(bOk)
		{
			if(Poly.PtInRegion(point))
			{
				Poly.DeleteObject();
				////////////////////
				if(ptRgn)
				{
					FreeMemDP(ptRgn);
					ptRgn = NULL;
				}
				////////////////////
      			return TRUE;
			}
		}
		else
		{
			AfxMessageBox(
				"Internal Problem:\nCDrPatch::IsObjectHit\nCreatePolygonRgn");
			Poly.DeleteObject();
			////////////////////
			if(ptRgn)
			{
				FreeMemDP(ptRgn);
				ptRgn = NULL;
			}
			////////////////////
			return FALSE;
		}
	}												// end Triangle LOOP
/*
	////////////////////
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
*/
	/////////////
	return FALSE;
}

BOOL CDrPatch::IsObjectBndryHit_3(int nNet,POINT point,int& iBndry)
{
	/////////////////////////////////////////
	// Triangular Patch is Created Always
	// By Coons Method with 3 Curves
	/////////////////////////////////////////
	for(int i=0;i<3;i++)
	{
		CDrCurve* pCurve = (CDrCurve*)GetCurveList()->GetObject(i);
		if(pCurve->IsObjectHit(nNet,point))
		{
			iBndry = i;
			return TRUE;
		}
	}
	///////////////////////////////
	return FALSE;
}

int CDrPatch::Collect_BoundaryPoints_3(int iOutGlo_ST,int jOutGlo_ST,int nType)
{
	int nBndrys = 3;
	//////////////////////////////////
	if(m_PatSubType != PS_TRIANGLE)
	{
		AfxMessageBox(
		"ERROR:\nInternal Problem:\nCDrPatch::Collect_BoundaryPoints_3\nNOT PS_TRIANGLE");
		return -1;
	}
	////////////////////////////////////// No. of Points for Enclosing Bndry
	int			nOut;
	pWORLD		pOut;
	////////////////////////////////////////////// temp memory
//	nOut	= nBndrys * GetSegmentCount_S(); 
	nOut	= nBndrys * GetOutSegUnif_S(); 
	pOut	= FixMem(nOut);
	////////////////////////////////////////////// Now Collect
	switch(nType)
	{
		case 1:								//	Triangle_1
			TRIANGLE_1_Bndry(pOut,iOutGlo_ST,jOutGlo_ST);
			break; 
		case 2:								//	Triangle_2
			TRIANGLE_2_Bndry(pOut,iOutGlo_ST,jOutGlo_ST);
			break; 
		default:
		{
			AfxMessageBox(
			"ERROR:\nInternal Problem:\nCDrPatch::Collect_BoundaryPoints_3\nILLEGAL nType");
			////////
			if(pOut)
			{
				FreeMem(pOut); 
				pOut	= NULL;
			}		
			return -1;
		}
	}
	///////////////////////
	CXForm XForm;
	WORLD EyePos,ScreenPos;
	////////////////////////////////////////////// Memory
	if(m_pOutDP)
	{
		FreeMemDP(m_pOutDP);
		m_pOutDP= NULL;
	}
	/////////////////////////////
	m_pOutDP 	= FixMemDP(nOut);		// Output Points
	////////////////////////////////////////////// Project for DirtyDraw	
    for(int j = 0; j<nOut; j++)              
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
		m_pOutDP[j].x = (int)(ScreenPos.x * m_dScale_U);
		m_pOutDP[j].y = (int)(ScreenPos.y * m_dScale_V);
		/////////////////////////
	}		
	///////////////////////////////////////////
	if(pOut)
	{
		FreeMem(pOut); 
		pOut	= NULL;
	}		
	////////////////////
	return nOut;

}

void  CDrPatch::TRIANGLE_1_Bndry(pWORLD pOut,int iOutGlo_ST,int jOutGlo_ST)
{ 
	/////////////////////////////////
	//
	//				 j
	//		 
	//				|\
	//				|  \					
	//			 u=0|	  \w=0
	//			   /|\	   _\|			
	//				|		  \			
	//	iOutGlo_ST -|----<-----\
	//	jOutGlo_ST		v=0
	//
	//
	//////////////////////////////////
	int i,j,m=-1,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= GetOut_S();
//	int nOutSeg_S	= GetSegmentCount_S();			
	int nOutSeg_S	= GetOutSegUnif_S();			
	/////////////////////////////////////////////////////// u = 0 side 
	i = 0;
	//////
	for (j=0;j<nOutSeg_S-i;j++)
	{
		iOut	= iOutGlo_ST + i;
		jOut	= jOutGlo_ST + j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	/////////////////////////////////////////////////////// w = 0 side 
	for (i=0;i<nOutSeg_S;i++)
	{
		j		= nOutSeg_S - i;
		/////////////////////////
		iOut	= iOutGlo_ST + i;
		jOut	= jOutGlo_ST + j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	/////////////////////////////////////////////////////// v = 0 side reversed
	j = 0;
	//////
	for (i=0;i<nOutSeg_S;i++)
	{
		iOut	= iOutGlo_ST + nOutSeg_S - i;
		jOut	= jOutGlo_ST + j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	return;
}									

void  CDrPatch::TRIANGLE_2_Bndry(pWORLD pOut,int iOutGlo_ST,int jOutGlo_ST)
{ 
	/////////////////////////////////
	//			 v=0    iOutGlo_ST
	//	i	  \---->----|jOutGlo_ST
	//		    \ _		|			
	//		 	 |\    \|/u=0
	//			    \	|		
	//       	  w=0 \	|		
	//                  \
	//					j
	//
	//////////////////////////////////
	int i,j,m=-1,L1;
	int iOut,jOut;
	////////////////////////
	int nOut_S		= GetOut_S();
//	int nOutSeg_S	= GetSegmentCount_S();
	int nOutSeg_S	= GetOutSegUnif_S();
	/////////////////////////////////////////////////////// u = 0 side 
	i = 0;
	//////
	for (j=0;j<nOutSeg_S-i;j++)
	{
		iOut	= iOutGlo_ST - i;
		jOut	= jOutGlo_ST - j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	/////////////////////////////////////////////////////// w = 0 side 
	for (i=0;j<nOutSeg_S;i++)
	{
		j		= nOutSeg_S - i;
		/////////////////////////
		iOut	= iOutGlo_ST - i;
		jOut	= jOutGlo_ST - j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	/////////////////////////////////////////////////////// v = 0 side reversed
	j = 0;
	//////
	for (i=0;i<nOutSeg_S;i++)
	{
		iOut	= iOutGlo_ST - (nOutSeg_S - i);
		jOut	= jOutGlo_ST - j;
		//////////////////////////////////// Barycentric to Linear: Global
		L1 = BARY2LIN_PT(iOut,jOut,nOut_S);
		////
		m++;
		*(pOut+m) = *(m_pOut+L1);
	}
	return;
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
						 		  		