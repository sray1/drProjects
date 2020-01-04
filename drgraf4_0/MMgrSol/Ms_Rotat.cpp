// Loft2.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 
#include "MsMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
#include "DegElevate.h"
///////////////////// dialogMgr
#include "MPatMgr.h"
//#include "dlg_LoftX.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "Str_BlendEnd.h"
#include "Str_CuPS.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "HitNet.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "PA_Rotat.h" 
#include "MS_Rotat.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define	new			DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMS_Rotat,CMI_GangS,1)
/////////////////////////////////////////////////////////////////////////////
CMS_Rotat::CMS_Rotat()
{
}

CMS_Rotat::~CMS_Rotat()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMS_Rotat::GoDoIt 
				(
					BOOL							bGenBCurve,
					BOOL							bGenBPatch,
					//////////////////////////////////////////
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pPatchList,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_W, // ist record: elem/seg
																	// 2nd record: #of BezSeg
					double							dAngle_W,
					double							Ratio_W,
					BOOL							bAxis,
					int								nAxis,
					BOOL							bNegative,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	m_bGenBCur		= bGenBCurve;
	m_bGenBPat		= bGenBPatch;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//////////////////////////
	if(!IsDataCompatible(pPatchList,pNodeList,pLatchList,&ElperSegList_W,bAxis) )
		return MA_ERROR;
	//////////////////////////////////////////////////////////
	m_SolidID		= SolidID;
	m_pDrSolid		= pDrSolid;
	m_pDrSolid->SetObjectID(SolidID);
	////////////////////////////////////////////////////////// ST_dir
	CDrPatch* pPatch	= (CDrPatch*)pPatchList->GetHead();
	PATCHLATCH pLatch	= pLatchList->GetHead();
	//////////////////////////////////////////
	SetSolidDataFromPatch(pPatch);
	////////////////////////////////////////// get Old 
	pWORLD pPatConBZ = new WORLD[m_nMaxSolidCNodes_ST];
	pDOUBLE pPatWtsBZ = new double[m_nMaxSolidCNodes_ST];
	///
	GetPatCNodeCoords_N_Wts(pPatch, pLatch, pPatConBZ, pPatWtsBZ);
	////////////////////////////////////////////////////////// R-dir
	m_bAxis_R		= bAxis;
	m_nAxis_R		= nAxis;
	m_bNegative_R	= bNegative;
	///////////////////////////
	m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
	m_pToIDNode		= (CDrNode*)(pNodeList->GetObject(1) );
	///////////////////////////////////////// AxisVector from
    											// end nodes	
	UnitAxisFromEndNodes(0);
	/////////////////////////////////////////////////////////////////////////////// R_Info
	GetSolidInfo_R(&ElperSegList_W,Ratio_W,dAngle_W);
	/////////////////////////////////////////////////// New Memory 
	pWORLD pConBZ	= new WORLD[m_nMaxSolidCNodes];
	pDOUBLE pWtsBZ	= new double[m_nMaxSolidCNodes];
	/////////////////////////////////////////////////////////////////////////////// Revolve
	WORLD wAxisPt	= *(m_pFromIDNode->GetLocalPos());
	/////////////
	RevolveCNs_N_WtsOfPatch(pPatConBZ,pPatWtsBZ,m_nMaxSolidCNodes_ST,m_bClosed_R,
			m_nSegs_R,m_pDisAng_R,m_vAxis,wAxisPt,pConBZ,pWtsBZ,m_nMaxSolidCNodes);
	/////////////////////////////////////////////////////////////////////////////// PostSolidData
	PostSolCNodes_N_Wts(pDrSolid,pConBZ,pWtsBZ,m_nMaxSolidCNodes_S,
									m_nMaxSolidCNodes_T,m_nMaxSolidCNodes_R);
	/////////////////////////////////////////////////////// put Original Patch in PatchList
	CDListMgr						PatchList_U;
	CDListMgr*						pPatchList_U = &PatchList_U;
	pPatchList_U->RemoveAll();
	///
	CList<PATCHLATCH,PATCHLATCH>	LatchList_U;
	CList<PATCHLATCH,PATCHLATCH>*	pLatchList_U = &LatchList_U;
	///
	CDListMgr						PatchList_V;
	CDListMgr*						pPatchList_V = &PatchList_V;
	pPatchList_V->RemoveAll();
	///
	CList<PATCHLATCH,PATCHLATCH>	LatchList_V;
	CList<PATCHLATCH,PATCHLATCH>*	pLatchList_V = &LatchList_V;
	///
	CDListMgr						PatchList_W;
	CDListMgr*						pPatchList_W = &PatchList_W;
	pPatchList_W->RemoveAll();
	///
	CList<PATCHLATCH,PATCHLATCH>	LatchList_W;
	CList<PATCHLATCH,PATCHLATCH>*	pLatchList_W = &LatchList_W;
	/////////////////////////////////////////////////////////////
	pPatchList_U->AddTail(pPatchList);
	pLatchList_U->AddTail(pLatchList);
	//////////////////////////////////
	m_SolidType	= SO_TENSOR;
	///////////////////////////////////////////////
	pDrSolid->GetElperSegList_R()->RemoveAll();
	pDrSolid->GetElperSegList_R()->AddTail(&ElperSegList_W);	// save for later editing etc
	////////////////
	nResult = SetInfoForDataBase(pDrSolid,pPatchList_U,pPatchList_V,pPatchList_W,
					pLatchList_U,pLatchList_V,pLatchList_W);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMS_Rotat::ProceessCoordAxis(int nAxis,BOOL bNeg)
{
	// THIS ROUTINE IS NOT USED
	///////////////////////////////////////
	m_nAxis_R		= nAxis;
	m_bNegative_R	= bNeg;
	/////////////////////////////////////// axis
	m_vAxis.x = 0.;  
	m_vAxis.y = 0.;  
	m_vAxis.z = 0.; 
	///////////////
	switch(m_nAxis)
	{
		case 1:
			m_vAxis.x = (m_bNegative)?-1.:1.;
			break;
		case 2:
			m_vAxis.y = (m_bNegative)?-1.:1.;
			break;
		case 3:
			m_vAxis.z = (m_bNegative)?-1.:1.;
			break;
	}
	/////////////
	return MA_OK;
}

BOOL CMS_Rotat::IsDataCompatible(CDListMgr* pPatchList,CDListMgr* pNodeList,
								CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
								CList<int,int>* pElperSegList,BOOL bAxis)
{
	////////////////////////////////////////////////// CurveID
	if(pPatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Rotat::IsDataCompatible\npPatchList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Rotat::IsDataCompatible\npLatchList->GetCount() != 1");
		return FALSE;
	}
	CDrPatch* pDrCurve	= (CDrPatch*)(pPatchList->GetObject(0) );
	////////////////////////////////////////////////// Mesh
	//	ElperSegList_W, // ist record: elem/seg
						// 2nd record: #of BezSeg
	if(pElperSegList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Rotat::IsDataCompatible\npElperSegList->GetCount() != 2");
		return FALSE;
	}
	////////////////////////////////////////////////// FromNodeID & ToNodeID 
	//pNodeList,	// ist record: pFromIDNode
					// 2nd record: pToIDNode
	if(pNodeList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Rotat::IsDataCompatible\npNodeList->GetCount() != 2");
		return FALSE;
	}
	///////////
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMS_Rotat::SetSolidDataFromPatch(CDrPatch* pPatch)
{
	int i;
	pINT	pNum_t_S;
	pDOUBLE	pDis_t_S;
	pINT	pNum_t_T;
	pDOUBLE	pDis_t_T;
	///////
	pNum_t_S				= pPatch->GetNum_tPointer_S();
	pDis_t_S				= pPatch->GetDis_tPointer_S();
	pNum_t_T				= pPatch->GetNum_tPointer_T();
	pDis_t_T				= pPatch->GetDis_tPointer_T();
	///
	m_nSegs_S				= pPatch->GetMaxBezSegments_S();
	m_nSegs_T				= pPatch->GetMaxBezSegments_T();
	m_nOut_S				= (int)pPatch->GetOut_S();
	m_nOut_T				= (int)pPatch->GetOut_T();
	m_nOut_ST				= pPatch->GetLongOutPts();
	/////////////////////////////////////////////////////////// Memory
	if(pNum_t_S)
		m_pNum_t_S			= new int[m_nSegs_S];
	if(pDis_t_S)
		m_pDis_t_S			= new double[m_nOut_S];
	if(pNum_t_T)
		m_pNum_t_T			= new int[m_nSegs_T];
	if(pDis_t_T)
		m_pDis_t_T			= new double[m_nOut_T];
   ////////////////////////////////////////////////////////////
//	m_pNum_t_Ex_S			= pPatch->GetNum_tPointer_Ex_S();
//	m_pNum_t_Ex_T			= pPatch->GetNum_tPointer_Ex_T();
	//////////////////////////////////////////////////
	for (i=0;i<m_nSegs_S;i++)
	{
		if(pNum_t_S)
			m_pNum_t_S[i]		= pNum_t_S[i];
	}
	for (i=0;i<m_nSegs_T;i++)
	{
		if(pNum_t_T)
			m_pNum_t_T[i]		= pNum_t_T[i];
	}
	//
	for (i=0;i<m_nOut_S;i++)
	{
		if(pDis_t_S)
			m_pDis_t_S[i]		= pDis_t_S[i];
	}
	for (i=0;i<m_nOut_T;i++)
	{
		if(pDis_t_T)
			m_pDis_t_T[i]		= pDis_t_T[i];
	}
	////////////////////
	m_Ratio_S				= pPatch->GetRatio_S();
	m_Ratio_T				= pPatch->GetRatio_T();
	m_nMaxOSeg_S			= pPatch->GetOutSegUnif_S();
	m_nMaxOSeg_T			= pPatch->GetOutSegUnif_T();
	m_bUnifOT_S				= pPatch->IsUniform_S();
	m_bUnifOT_T				= pPatch->IsUniform_T();
	/////////////////////////////////////////////////////////////	
//	m_nOut_SCon				= (int)m_nMaxPatchCNodes_S;
//	m_nOut_TCon				= (int)m_nMaxPatchCNodes_T;
	////////////////////////////////////////////////// FILL INFO
	m_nDim_S				= pPatch->GetnDim_S();
	m_nDim_T				= pPatch->GetnDim_T();
	m_CurveType_S			= pPatch->GetCurveType_S();
	m_CurveType_T			= pPatch->GetCurveType_T();
	m_nOrder_S				= pPatch->GetOrder_S();
	m_nOrder_T				= pPatch->GetOrder_T();
	///////////////////////////////////////////	
 	m_bClosed_S				= pPatch->IsClosed_S();	// X-Section
	m_bClosed_T				= pPatch->IsClosed_T();	// X-Section
//	m_nSegs_SCon			= m_nOut_SCon - 1;
//	m_nSegs_TCon			= m_nOut_TCon - 1;
	m_nMaxSolidCNodes_S 	= pPatch->GetMaxCNodes_S();
	m_nMaxSolidCNodes_T 	= pPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
//	m_nOut_STCon			= (int)m_nMaxSolidCNodes_ST;
	////////////////////////////////////////////////////
//	m_pWts_BZ_ST			= pPatch->GetMemInWts();		
	//////////////////////////////
	m_PatSubType			= pPatch->GetPatSubType();
	if(m_PatSubType == PS_TRIANGLE)
		m_SolSubType		= SS_PENTA; 
	else
	if(m_PatSubType == PS_QUADRILAT)
		m_SolSubType		= SS_HEXA;	// 
	///
	return MA_OK;

}
////////////////////////////////////////////////////////////////////////////////////
int CMS_Rotat::RevolveCNs_N_WtsOfPatch(
					pWORLD				pPatConBZ, 	
					pDOUBLE				pPatWtsBZ, 	
					int					nPatConBZ,
					//////////////////////////////////////////////
					BOOL				bClosed,
					int					nSegBZ,//	# of Quadratic Bezier Segments
					pDOUBLE				pDis,	//	Angle Distribution for each Bez Patch in degrees
														//		(not cumulative)
					WORLD				wAxis,	//	unit direction vector of rotation axis
					WORLD				AxisPt, //  a pt. on the rotation vector
					//////////////////////////////////////////////
					pWORLD				pSolConBZ, 	
					pDOUBLE				pSolWtsBZ, 	
					int					nSolConBZ
				)
{
	/////////////////////
	int nOut		= nSolConBZ;  
	////////////////////////////////////////////// generate Patch Pts
	CPA_Rotat	PA_Rotat;
	int nOutActual	= PA_Rotat.RotateCurve
			(
				bClosed,			// Closed?
				nSegBZ,			//	# of Quadratic Bezier Segments
				pDis,			//	Angle Distribution for each Bez Patch in degrees
									//		(not cumulative)
				wAxis,			//	unit extrusion vector (direction)
				AxisPt,			//  a pt. on the rotation vector
				nPatConBZ,		//	number of input data points
				pPatConBZ,		//	input XSec curve dataPts
				pPatWtsBZ,		//	input XSec curve Wts
				pSolConBZ,		//	Output ControlPts
				pSolWtsBZ		//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return MA_ERROR;
	else
		return MA_OK;
}

int CMS_Rotat::PostSolCNodes_N_Wts(CDrSolid* pDrSolid,pWORLD pConBZ,pDOUBLE pWts_BZ,
											int nConBZ_S,int nConBZ_T,int nConBZ_R)
{
	// need to multiply by Curve Wts
	// because the circles are in Std. Form
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int i,j,k,m,nConBZ_ST,nTotal;
	CDrNode*	pNewNode;
	WORLD		wLocalPos;
	CString		SolidID = pDrSolid->GetObjectID();
	////////////////////////////////////////////////////////// CNodes & Wts
	nConBZ_ST	= nConBZ_S	* nConBZ_T;
	nTotal		= nConBZ_ST	* nConBZ_R;	
	//////
	for(k=0;k<nConBZ_R;k++)
	{
		for(j=0;j<nConBZ_T;j++)
		{
			for(i=0;i<nConBZ_S;i++)
			{
				m = i + j*nConBZ_S + k*nConBZ_ST; 
				//////////////////////////////////// Name
				CString* pNid = new CString;
				char* buf = pNid->GetBuffer(BUFF_SIZE);
				sprintf(buf,"%s_%d_%d",SolidID,j,i);
				////////////////////////////////////////////////// Regular 
				wLocalPos = pConBZ[m];
				////////////////////////////////////////////////// Create & Save
				pNewNode = PostNode(*pNid,LEVEL_KIDDO,wLocalPos,TRUE);	// Create DrCNode
				delete pNid;
				//////////////////////////////////
				if(!pNewNode)	// Create DrCNode
					return MA_ERROR;
				///////////////////////////////////
				pDrSolid->GetCNodeList()->InsertObject(pNewNode);
				////////////////////////////////////////////////// 
			}
		}
	}
	////////////////////////////////////////////////////////// save Wts
	pDrSolid->SetMemInWts(pWts_BZ);
	////////////
	return MA_OK;
}
/////////////////////////////////////////////////////////////////////////////////////
int CMS_Rotat::GetPatCNodeCoords_N_Wts(CDrPatch* pPatch, PATCHLATCH pLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pPatch->GetCNodeList();
	pDOUBLE pWts		= pPatch->GetMemInWts();
	int nCon_BZ			= (pPatch->GetMaxCNodes_S())*(pPatch->GetMaxCNodes_T());
	int nCon_IndexMax	= nCon_BZ -1;
	/////////////////////////////////////////////////////////////// Coords 
	int j=-1;
	if(!pList->IsEmpty())
	{
		////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			///////////////////////////////////////
			if(pLatch == PL_FIRST_FORWARD)
				pConOld[++j] = *(pNode->GetLocalPos());
			else	// todo in-between Latching
			if(pLatch == PL_FOURTH_BACKWARD)
				pConOld[nCon_IndexMax - (++j) ] = *(pNode->GetLocalPos());
			//////////////////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// Wts
	for(j=0;j<nCon_BZ;j++)
	{
		if(pLatch == PL_FIRST_FORWARD)
			pWtsOld[j] = pWts[j];
		else	// todo in-between Latching
		if(pLatch == PL_FOURTH_BACKWARD)
			pWtsOld[nCon_IndexMax - j] = pWts[j];
	}
	/////////
	return 0;
}

int CMS_Rotat::GetSolidInfo_R(CList<int,int>* pElperSegList,double Ratio,double dAng)
{
	//	ElperSegList_W:
			// ist record: elem/seg
			// 2nd record: #of BezSeg
	/////////////////////////////////
	int i,nElems;
	double dInc;
	/////////////////////////////////
	if(dAng>360.) 
		dAng = 360.;
	////////////////
	m_bClosed_R	= (dAng==360.)?TRUE:FALSE;
	nElems		= pElperSegList->GetHead();
	m_nSegs_R	= pElperSegList->GetTail();
	m_nOut_R	= nElems * m_nSegs_R + 1;
	////////////////////////////////////////////////////////////////////////// ReDistribute
	dInc		= dAng/m_nSegs_R;
	///////////////////////////////////////
	//
	m_pNum_t_R	= new int[m_nSegs_R];
	m_pDisAng_R	= new double[m_nSegs_R];
	for (i=0;i<m_nSegs_R;i++)
	{
		m_pNum_t_R[i]	= nElems;
		m_pDisAng_R[i]	= dInc;
	}
	//
	if(m_nSegs_R == 1)
	{
		dInc = 1.0/nElems;
		m_pDis_t_R	= new double[m_nOut_R];
		for (i=0;i<(m_nOut_R-1);i++)
			m_pDis_t_R[i]		= i*dInc;
		m_pDis_t_R[m_nOut_R-1]	= 1.0;
	}
	else
		m_pDis_t_R = NULL;
	//////////////////////////////////////////////////////////////////// Set Info
	m_Ratio_R				= Ratio;
	m_nDim_R				= 4;	// 
	m_CurveType_R			= CP_CIRCLE;
	m_nOrder_R				= 3;
	m_CircleType_R			= CIRCLE_BY_ROT;
	m_dAng_1_R				= 0.0;
	m_dAng_2_R				= dAng;
	////////////////////////////////////////
	int nConR				= m_nSegs_R * (m_nOrder_R-1) + 1; 
	m_nMaxSolidCNodes_R		= (m_bClosed_R)?nConR-1:nConR;
	m_nMaxSolidCNodes	 	= m_nMaxSolidCNodes_ST * m_nMaxSolidCNodes_R;
	//////////////////
	return MA_OK;
}
//////////////////////////////////////////////////////////////////////////////////////
int CMS_Rotat::SetInfoForDataBase(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,CDListMgr* pPatchList_V,CDListMgr* pPatchList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_V,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_W)
{
	pDrObject->SetDirty(TRUE);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetSolidProc(SP_ROTATE);
	pDrObject->SetSolidType(SO_TENSOR);
	pDrObject->SetSolSubType(m_SolSubType);
    //////////////////////////////
	pDrObject->SetObjectID(m_SolidID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	pDrObject->SetGenBPatch(m_bGenBPat);
	/////////////////////////////////////////////////////////////////// Info Based on nCurDir
	pDrObject->SetPrimaryDir(1);// 
	SetInfoForDataBase_1(pDrObject,pPatchList_U,pPatchLatchList_U,
				pPatchList_V,pPatchLatchList_V,pPatchList_W,pPatchLatchList_W);
	/////////////////////////////////////////////////////////
	m_nOut = (long)m_nOut_S * (long)m_nOut_T * (long)m_nOut_R;
	pDrObject->SetLongOutPts(m_nOut);			// m_nOut	
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	int nOutTotal = pDrObject->NumberOfSolides();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMI_GangP::InsertMeshInfo\nm_nOut Mismatch!");
		return MA_ERROR;
	}
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	pDrObject->Calc_3DBoundsLocal();
	///////
	return MA_OK;
}

void CMS_Rotat::SetInfoForDataBase_1(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CDListMgr* pPatchList_V,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_V,
					CDListMgr* pPatchList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_W)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	////////////////////////////////////////////////////////// PatchList
	CDListMgr* pList; 
	POSITION pos;
	CDrPatch* pPatch;
	///////////////////////////////////////////////// 
	pList = pDrObject->GetPatchList_U(); 
	pList->RemoveAll();
	pList->AddTail(pPatchList_U);
	pDrObject->GetPatchLatchList_U()->RemoveAll();
	pDrObject->GetPatchLatchList_U()->AddTail(pPatchLatchList_U);
	///////////////////////////////////////////////// Reciprocate
	pList = pDrObject->GetPatchList(); 
	pList->RemoveAll();
	pList->AddTail(pPatchList_U);
	///
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pPatch 	= (CDrPatch*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pPatch->GetSolidList()->GetObjectIndex(pDrObject);
		if(index<0)
			pPatch->GetSolidList()->InsertObject(pDrObject);
	}
	///////////////////////////////////////////////////////////////// Reciprocate
	m_pFromIDNode->GetSolidList()->InsertObject(pDrObject);
	pDrObject->SetFromIDNode_R(m_pFromIDNode);
	///
	m_pToIDNode->GetSolidList()->InsertObject(pDrObject);
	pDrObject->SetToIDNode_R(m_pToIDNode);
	////////////////////////////////////////
	pDrObject->SetAxis_R(m_vAxis);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetRatio_T(m_Ratio_T);					
	pDrObject->SetRatio_R(m_Ratio_R);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetUniform_R(m_bUnifOT_R);		// Output Distribution:
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_T(m_nMaxOSeg_T); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_R(m_nMaxOSeg_R); 	// for Old Compatibility
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_S);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_T(m_nMaxOSeg_T);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_R(m_nMaxOSeg_R);	// Number of Output Segments
//?
	pDrObject->SetMaxOutPts_S(m_nOut_S);
	pDrObject->SetMaxOutPts_T(m_nOut_T);
	pDrObject->SetMaxOutPts_R(m_nOut_R);
	pDrObject->SetOut_S(m_nOut_S);
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOut_R(m_nOut_R);
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetCurveType_T(m_CurveType_T);
	pDrObject->SetCurveType_R(m_CurveType_R);
	pDrObject->SetMaxCNodes_S(m_nMaxSolidCNodes_S);
	pDrObject->SetMaxCNodes_T(m_nMaxSolidCNodes_T);
	pDrObject->SetMaxCNodes_R(m_nMaxSolidCNodes_R);
	///////////////////////////////////////////////////
//	pDrObject->SetSegmentCount_S(m_nSegs_S);	
//	pDrObject->SetSegmentCount_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_S(m_nSegs_S);	
	pDrObject->SetMaxBezSegments_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_R(m_nSegs_R); 
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetClosed_T(m_bClosed_T);
	pDrObject->SetClosed_R(m_bClosed_R);
	pDrObject->SetOut_S(m_nOut_S);	
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOut_R(m_nOut_R);
	pDrObject->SetOrder_S(m_nOrder_S);
	pDrObject->SetOrder_T(m_nOrder_T);
	pDrObject->SetOrder_R(m_nOrder_R);
//	pDrObject->SetnDim_S(m_nDim_S);
//	pDrObject->SetnDim_T(m_nDim_T);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_T(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_R(4);	// ALWAYS RATIONAL
	///////////////////////////////////////////////////////// for now
	pDrObject->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_T(m_pNum_t_T);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_R(m_pNum_t_R);			// Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pDis_t_S);			// s-distribution
	pDrObject->SetDis_tPointer_T(m_pDis_t_T);			// t-distribution
	pDrObject->SetDis_tPointer_R(m_pDis_t_R);			// r-distribution
	////////////////////////////////////////////////////////////////////// Circle Info
	pDrObject->SetAxisInput_R(m_bAxis_R);		// Set if Axis Input
	pDrObject->SetAxisType_R(m_nAxis_R);		// 1=X/2=Y/3=Z
	pDrObject->SetNegative_R(m_bNegative_R);
	pDrObject->SetCircleType_R(m_CircleType_R);
	pDrObject->SetAng_1_R(m_dAng_1_R);
	pDrObject->SetAng_2_R(m_dAng_2_R);
	///
	pDrObject->SetDis_AngPointer_R(m_pDisAng_R);
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	pDrObject->SetGenBPatch(m_bGenBPat);
	////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMS_Rotat::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMS_Rotat:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMS_Rotat:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
