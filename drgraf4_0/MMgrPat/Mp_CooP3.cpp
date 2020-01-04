// Loft2.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
#include "DegElevate.h"
///////////////////// dialogMgr
//#include "MPatMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "PA_CooP3.h"
 
#include "MP_CooP3.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define	new			DEBUG_NEW
#define	BUFF_SIZE	1024

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  

#define BARY2LIN_PT(i,j,nP)				(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)

#define BARY2LIN_TRI_1_NEW(i,j,nP,nDeg)	( (j)  + ((i)*(2*(nP)-(i)-2))/(nDeg) )/(nDeg)
#define BARY2LIN_TRI_2_NEW(i,j,nP,nDeg)	( (j - nDeg)  + ((i)*(2*(nP)-(i)-2))/(nDeg) - ((nP) - 1) + (i) )/(nDeg)
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_CooP3,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_CooP3::CMP_CooP3()
{
	m_bBack = FALSE;
}

CMP_CooP3::~CMP_CooP3()
{
}
int CMP_CooP3::GoDoIt 
				(
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					CDListMgr*						pCurveList,
					CList<CURVELATCH,CURVELATCH>*	pLatchList
				) 
{
	int nResult = MA_OK;
	//////////////////////////////////////////////////////////
	m_PatchID	= PatchID;
	m_pDrPatch	= pDrPatch;
	///////////////////////////////////////////////////////////////////////////////// Fill Lists
	CDListMgr						CurveList_U;
	CDListMgr*						pCurveList_U = &CurveList_U;
	pCurveList_U->RemoveAll();
	CDListMgr						CurveList_V;
	CDListMgr*						pCurveList_V = &CurveList_V;
	pCurveList_V->RemoveAll();
	CDListMgr						CurveList_W;
	CDListMgr*						pCurveList_W = &CurveList_W;
	pCurveList_V->RemoveAll();
	///
	CList<CURVELATCH,CURVELATCH>	LatchList_U;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_U = &LatchList_U;
	CList<CURVELATCH,CURVELATCH>	LatchList_V;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_V = &LatchList_V;
	CList<CURVELATCH,CURVELATCH>	LatchList_W;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_W = &LatchList_W;
	////////////
	FillCurve_N_LatchLists(pCurveList,pLatchList,pCurveList_U,pLatchList_U,
							pCurveList_V,pLatchList_V,pCurveList_W,pLatchList_W);
	///////////////////////
	int nCurves,nConBZ_Tot;
	///////////////////////////////////////////////////////////////////////////////// All Curves
	// All Curves Done & Info Stored in S-direction 
	////////////////////////////////////////////////////////// Compatibility(Knots)
	int nDim_S,nTopDegree_S,nConBZ_S;
	BOOL bClosed_S;
	///////////////
	if(!AreCurvesCompatible(pCurveList,pLatchList,bClosed_S,nDim_S,
								nTopDegree_S,nConBZ_S) )
		return MA_ERROR;
	////////////////////////////////////////////////////////// Process  Data Curves( Elevate etc)
	nCurves				= pCurveList->GetCount(); 
	nConBZ_Tot			= nConBZ_S * nCurves;  
	pWORLD  pConBZ_S	= new WORLD [nConBZ_Tot]; 	
	pDOUBLE pWtsBZ_S	= new double[nConBZ_Tot];
	/////////////////////////////////////////
	nResult = ProcessCurves(pCurveList,pLatchList,pConBZ_S,pWtsBZ_S,nConBZ_S,
													nConBZ_Tot,nTopDegree_S,nDim_S);
	///////////////////////////////////////////////////////////////////////////////// Patch CNs & Wts
	int nB1,nB2,nTri1,nTri2,nOutPerSeg,nDeg;
	////////////////////////////////////////
	nOutPerSeg	= m_pNum_t_S[0]+1;
	nDeg		= m_nOrder_S - 1;
	////////////////////////////////// Save PatchInfo
	// Each Output Triangle should be all the Output Pts.
	// this will require redundancy but simplify,So ...
	////////////////////////
	int nTri,nEmit;
	///////////////////////////
	nEmit	= nOutPerSeg*(nOutPerSeg+1)/2;	// No. of Output for Each Bezier Triangle
	/////
	nB1		= (nConBZ_S - 1)/nDeg;		// No. of Type1 Triangle Side Controls	
	nB2		= (nConBZ_S - 1 - nDeg)/nDeg;// No. of Type2 Triangle Side Controls	
	nTri1	= (nB1+1)*nB1/2;				// No. of Type1 Triangles	
	nTri2	= (nB2+1)*nB2/2;				// No. of Type2 Triangles	
	nTri	= nTri1 + nTri2;				// No. of Triangles	
	/////////////////
	m_nOut				= (long)(nEmit*nTri);	
	/////////////////////////////////////////////
	// Generate Patch Nodes & Wts
	nConBZ_Tot			= (nConBZ_S*(nConBZ_S+1)/2 );
	pWORLD  pConBZ_Tot	= new WORLD [nConBZ_Tot]; 	
	pDOUBLE pWtsBZ_Tot	= new double[nConBZ_Tot];
	////////////////////////////////////////////
	m_nMaxPatchCNodes	= nConBZ_Tot;		// Save Total Control Nodes
	////////////////////////////////////////////
	nResult = GenerateCNodes(pConBZ_S,pWtsBZ_S,nConBZ_S,pConBZ_Tot,pWtsBZ_Tot,
																	nConBZ_Tot);
	if(nResult == MA_ERROR)
		return MA_ERROR;

	/////////////////////////////////////////////////////////////////////////////// Now Save CNs & Wts
	nResult = CreateSavePatCNodes_N_Wts(pDrPatch,pConBZ_Tot,pWtsBZ_Tot,nConBZ_S);
	/////////////////////////////////////////////////////////////////////////////// Patch Bndry Curves
	m_bGenBCur = bGenBCurve;
	if(bGenBCurve)
	{
		nResult = GeneratePatchBndryCurves();
	}
	////////////////////////////////////////////////////////// Post OtherInfo
	m_PatchType		= PA_TENSOR;
	////////////////////////
	nResult = SetInfoForDataBase(pDrPatch,	pCurveList_U,pCurveList_V,pCurveList_W,
											pLatchList_U,pLatchList_V,pLatchList_W);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_CooP3::FillCurve_N_LatchLists(
					CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pLatchList_V,
					CDListMgr* pCurveList_W,CList<CURVELATCH,CURVELATCH>* pLatchList_W)
{
	CDrCurve*	pCurve;
	CURVELATCH	CuLatch;
	POSITION	pos;
	////////////////////
	pCurve	= (CDrCurve*)pCurveList->GetObject(0);	// Curve_1
	if(pCurve)
		pCurveList_U->InsertObject(pCurve);	
	////
	pCurve	= (CDrCurve*)pCurveList->GetObject(1);	// Curve_2
	if(pCurve)
		pCurveList_V->InsertObject(pCurve);	
	////
	pCurve	= (CDrCurve*)pCurveList->GetObject(2);	// Curve_3
	if(pCurve)
		pCurveList_W->InsertObject(pCurve);	
	//////////////////////////////////////////////////////////
	pos = pLatchList->FindIndex(0);
	CuLatch	= pLatchList->GetAt(pos);
	pLatchList_U->AddTail(CuLatch);
	//
	pos = pLatchList->FindIndex(1);
	CuLatch	= pLatchList->GetAt(pos);
	pLatchList_V->AddTail(CuLatch);
	//
	pos = pLatchList->FindIndex(2);
	CuLatch	= pLatchList->GetAt(pos);
	pLatchList_W->AddTail(CuLatch);
	////////////////////////////////
	return MA_OK;
}

BOOL CMP_CooP3::AreCurvesCompatible(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
											BOOL bClosed,int& nDim_S,int& nTopDegree,int& nCon_BZ)
{
	//////////////////////////////////////////////////////////// ALL Closed or Open
	if(!IsCompat_Closed(pCurveList,bClosed))
		return FALSE;
	else
		m_bClosed_S = bClosed;
	//////////////////////////////////////////////////////////// Segment Compatibility
	PreProcessCurvesControlInfo(pCurveList,nDim_S,nTopDegree); // TopDegree? etc
	////////////////////////////////////////////////////////////////
	m_nDim_S	= nDim_S;
	m_nOrder_S	= nTopDegree + 1;
	/////////////////////////////
	switch(m_nOrder_S)
	{
		case 2:
			m_CurveType_S = CP_LINEAR;
			break;
		case 3:
			m_CurveType_S = CP_QUADRATIC;
//			if() // Circle
//				m_CurveType_S = CP_CIRCLE;
			break;
		case 4:
			m_CurveType_S = CP_BSPLINE;
			if(m_nDim_S == 4)
				m_CurveType_S = CP_NURB;
			break;
		default:
			break;
	}
	//////////////////////////////////////////////////////////// Do it
	int nBezSeg;
	// Total Expected CNodes of EACH Curve
	if(!IsCompat_NumberOfCNodes(pCurveList,nTopDegree,nBezSeg,nCon_BZ) )
	{
		AfxMessageBox(
		"DATA ERROR\nCOMPATIBILITY Problem\nNumber of Bezier Segments MisMatch!!\nTask Cancelled");
		return FALSE;
	}
	else
	{
		m_nSegs_S			= nBezSeg;				
		m_nMaxPatchCNodes_S	= nCon_BZ;
	}	
	//////////////////////////////////////////////////////////// Output Compatibility
	if(!IsCompat_OutputInfo(pCurveList,pLatchList) ) // ElPerSegList etc
	{
		AfxMessageBox(
		"DATA ERROR\nCOMPATIBILITY Problem\nNumber of Elements MisMatch!!\nTask Cancelled");
		return FALSE;
	}
	//////////////////////////////////////////////// Process Output_S
	CDrCurve* pCurve = (CDrCurve*)pCurveList->GetHead();
	SetPatchOutputDataFromCurve(pCurve,1/*nDir*/);
	//////////
	return TRUE;
}

BOOL CMP_CooP3::IsCompat_Closed(CDListMgr* pCurveList,BOOL& bClosed)
{
	/////////////////////////////////////// Is ALL Closed or Open?
	CDListMgr* pList	= pCurveList;
	bClosed				= FALSE;
	int i = -1;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			return FALSE;
   	 	///////////////////////////////////////////// IsClosed
		i++;
		if(i<=0) 
			bClosed = pCurve->IsClosed_S();
		else
		if(bClosed != pCurve->IsClosed_S())
			return FALSE;
		/////	
	}
	////////////
	return TRUE;
}

int CMP_CooP3::PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim_S,int& nTopDegree)
{
	/////////////////////////////////////// Rational?
	nDim_S	= 3;
	if(IsRational(pCurveList))
		nDim_S	= 4;
	/////////////////////////////////////// Find Highest Degree
	nTopDegree	= GetTopDegree(pCurveList);
	////////////
	return MA_OK;
}

BOOL CMP_CooP3::IsRational(CDListMgr* pCurveList)
{
	CDListMgr* pList = pCurveList;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		int nDim = pCurve->GetnDim_S();
		if(4 == nDim)
			return TRUE;
		/////	
	}
	return FALSE;
}

int CMP_CooP3::GetTopDegree(CDListMgr* pCurveList)
{
	CDListMgr* pList = pCurveList;
	//////////////////////////////
	int nDegree=0,nDeg_C;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			continue;
   	 	///////////////////////////////////////////// Get Degree/Update
		nDeg_C = (pCurve->GetOrder_S()) - 1;
		if(nDeg_C>nDegree)
			nDegree = nDeg_C;
		/////	
	}
	return nDegree;
}

BOOL CMP_CooP3::IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
													int& nCurveSeg,int& nConBZ)
{
	// Check All Curves Have Same Number of CNodes after Elevation
	////////////////////////////////////////////////////////////// 
	CDListMgr*	pList = pCurveList;	// Curves making up Profile
	int nDeg_C,nElev,nCon;
	int nConBZOld;
//	BOOL bClosed;
	//////////////////////////////////////////////////////////// Total CNodes
	int k = 0;
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			return FALSE;	// error
		////
		k++;
		nConBZ		= 0;
   	 	///////////////////////////////////////////// Get Degree/Update
		nDeg_C		= (pCurve->GetOrder_S()) - 1;
		nElev		= nTopDegree - nDeg_C;	// How many Elevations	
		nCon 		= pCurve->GetMaxCNodes_S();
		nCurveSeg 	= pCurve->GetMaxBezSegments_S(); 
//		bClosed		= pCurve->IsClosed_S();
   		///////////////////////////////////////////// Update Total Control Nodes
   		nConBZ		= nCon;	
   		if(nElev>0)
   			nConBZ	+= nElev * nCurveSeg;	// nElev Cnodes per Curve Segment
		///////////////////////////////////////////// Check Compatibility
		if(k<=1)
			nConBZOld = nConBZ;	// first time
		else
		if(nConBZOld != nConBZ)	// InCompatible
			return FALSE;
	}
	///////////////
	return TRUE;

}

BOOL CMP_CooP3::IsCompat_OutputInfo(CDListMgr* pCurveList,
						CList<CURVELATCH,CURVELATCH>* pLatchList)
{
	POSITION pos,posL;
	BOOL bCompareBKward = FALSE;
	CURVELATCH LatchOld;
	CURVELATCH Latch;
	/////////////////////////////////////// Is ALL Output Info same?
	CDListMgr* pList	= pCurveList;
	CList<int,int>*	pElperSegList;	 	
	CList<int,int>*	pElperSegListOld;	 	
	int i= -1,j;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (pos = pList->GetFirstObjectPos(),posL = pLatchList->GetHeadPosition();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			return FALSE;
		Latch			= pLatchList->GetNext(posL);  
		pElperSegList	= pCurve->GetElperSegList_S();
   	 	///////////////////////////////////////////// ElperSegList
		i++;
		if(i<=0)
		{
			pElperSegListOld	= pElperSegList;
			LatchOld			= Latch;
			///
			if(pElperSegList->IsEmpty())	// must have some Elems
				return FALSE;
			else
				continue;
		}
		else
		{
			///////////////////////////////////////////// same count of indices?
			if(pElperSegList->GetCount() != pElperSegListOld->GetCount())
				return FALSE;
			/////////////////////////////////////////////////
			bCompareBKward = (LatchOld == Latch)? FALSE:TRUE;
			///////////////////////////////////////////// go over the list
			if(bCompareBKward)
			{
				j = -1;
				for (POSITION posI = pElperSegList->GetTailPosition( );posI !=NULL;)
				{
					j++;
					////
					int nElems = pElperSegList->GetPrev(posI);
					///////
					POSITION posOld = pElperSegListOld->FindIndex(j);
					int nElemsOld = pElperSegList->GetAt(posOld);
					///////////////////////////////////////////////// same
					if(nElemsOld != nElems)
						return FALSE;
				}
			}
			else
			{
				j = -1;
				for (POSITION posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
				{
					j++;
					////
					int nElems = pElperSegList->GetNext(posI);
					///////
					POSITION posOld = pElperSegListOld->FindIndex(j);
					int nElemsOld = pElperSegList->GetAt(posOld);
					///////////////////////////////////////////////// same
					if(nElemsOld != nElems)
						return FALSE;
				}
			}
		}
	}
	////////////
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////
int CMP_CooP3::ProcessCurves(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
							 int nCon_BZTot,int nDegree,int nDim)
{
	int nConActual = 0;
	/////////////////////////////////////////////////////////////// Degree Elevate 
	nConActual = Elevate_PatCurves(pCurveList,pLatchList,
								pCon_BZ, pWts_BZ, nDegree, nDim);
	/////////////////////////
	if(nConActual != nCon_BZTot)
	{
		AfxMessageBox("Internal Problem:\nCMP_CooP4::Elevate_Profile");
		return -1;
	}									
	/////////
	return 0;
}

int CMP_CooP3::Elevate_PatCurves(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
											pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nDegree, int nDim)
{

	/////////////////////////////////// 
	int m,nDegOld,nElev,nSeg_BZ,nConOld,nConNew,nConTot=0,nBegNew=0;
	/////////////////////////////////////// 	
	int nCount=0; 
  	////////////////////////////////////////// memory	
	pWORLD		pConOld;
	pDOUBLE		pWtsOld;
	pWORLD		pConNew;
	pDOUBLE		pWtsNew;
	POSITION	posCurve;
	POSITION	posLatch;	
	//////////////////////////////////////////////////////////// Controls
	for (	posCurve = pCurveList->GetFirstObjectPos(),
			posLatch = pLatchList->GetHeadPosition();posCurve !=NULL;)
	{
		CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetNext(posCurve);
		CURVELATCH cLatch	= pLatchList->GetNext(posLatch);
		BOOL bClosed		= pCurve->IsClosed_S();
		/////////
		if(!pCurve)
			continue;
		CDegElevate DegElevate(bClosed);
		/////////////////////////////////////// GetControl Nodes
		nConOld 	= pCurve->GetMaxCNodes_S();
		nDegOld		= (pCurve->GetOrder_S()) - 1;
		nElev		= nDegree - nDegOld;	// How many Elevations	
		nSeg_BZ 	= pCurve->GetMaxBezSegments_S();
   		/////////////////////////////////////// 
   		nConNew		= nConOld;	
   		if(nElev>0)
   			nConNew	+= nElev * nSeg_BZ;	// nElev Cnodes per Curve Segment 
   		////////////////////////////////////////// memory	
		pConOld 	= new WORLD [nConOld];
		pWtsOld 	= new double[nConOld];
		pConNew 	= new WORLD [nConNew];
		pWtsNew 	= new double[nConNew];
		////////////////////////////////////////// get Old 
		GetCNodeCoords_N_Wts(pCurve, cLatch, pConOld, pWtsOld);
   	 	///////////////////////////////// 
		int nConActual = 
				DegElevate.Elevate_Curve(pConOld, pWtsOld, nDegOld, nElev, pConNew, pWtsNew,
								nSeg_BZ, nDim);
   		////////////////////////////////////////// Free memory
		delete [] pConOld;
		delete [] pWtsOld;
		//////////////////
		if(nConActual != nConNew)
		{
			AfxMessageBox("Internal Problem:\nCMP_CooP4::Elevate_Profile");
			return -1;
		}									
		/////////////////////////////////////// save
		for(m=0;m<nConNew;m++)	
		{
			nConTot++;
			///////////////
			pCon_BZ[nBegNew+m].x = pConNew[m].x; 	
			pCon_BZ[nBegNew+m].y = pConNew[m].y; 	
			pCon_BZ[nBegNew+m].z = pConNew[m].z; 	
			pWts_BZ[nBegNew+m]   = pWtsNew[m]; 	
			///////////////////////////////////
		}
		nBegNew += nConNew;									
   		////////////////////////////////////////// Free memory
		delete [] pConNew;
		delete [] pWtsNew;
		////////////////////////////////////////// 
	}
	//////////////////
	return nConTot;
}

int CMP_CooP3::GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	int nCon_BZ			= pCurve->GetMaxCNodes_S();
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
			if(cLatch == CL_FORWARD)
				pConOld[++j] = *(pNode->GetLocalPos());
			else
			if(cLatch == CL_BACKWARD)
				pConOld[nCon_IndexMax - (++j) ] = *(pNode->GetLocalPos());
			//////////////////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// Wts
	for(j=0;j<nCon_BZ;j++)
	{
		if(cLatch == CL_FORWARD)
			pWtsOld[j] = pWts[j];
		else
		if(cLatch == CL_BACKWARD)
			pWtsOld[nCon_IndexMax - j] = pWts[j];
	}
	/////////
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
int CMP_CooP3::GenerateCNodes(pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ_S,
								pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut)
{
	////////////////////////////////////////////// generate Patch Pts
	CPA_CooP3	PA_CoonP;
	int nOutActual	= PA_CoonP.CoonCurves
			(
				(short)nConBZ_S,	//	number of input Control points in S-dir
				pConBZ,				//	input data point for Curve 1
		      	pWtsBZ,				//	input data Weight for Curve 1 
				pConBZ+nConBZ_S,	//	input data point for Curve 2
		      	pWtsBZ+nConBZ_S,	//	input data Weight for Curve 2 
				pConBZ+nConBZ_S*2,	//	input data point for Curve 3
		      	pWtsBZ+nConBZ_S*2,	//	input data Weight for Curve 3 
				pPatCons,			//	Output ControlPts array
				pPatWts				//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nTotOut)
	{
		AfxMessageBox("Internal ERROR:\nint CMP_CooP3::GenerateCNodes\nnOutActual != nTotOut");
		return MA_ERROR;
	}
	else
		return MA_OK;
}

int CMP_CooP3::CreateSavePatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pConBZ,pDOUBLE pWts_BZ,
																				int nCN_S)
{
	CDListMgr*	pCNList = pDrPatch->GetCNodeList();
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		PatchID;
    CDrNode* 	pAddNode;
	int i,j,k,m;
	///////////////////////////////////////////// Name
	PatchID	= pDrPatch->GetObjectID();
	////////////////////////////////////
	for (i = 0; i<nCN_S; i++)
	{
		for (j = 0; j<nCN_S - i; j++)
		{
   			///////////////////////////////////////// CREATE	
		    //////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
			////////////////////////////////////
			k = nCN_S - i - j - 1; 
		    sprintf(buf,"%s_%d_%d_%d",PatchID,i,j,k);
			//////////////////////////////////// Barycentric to Linear
			m = BARY2LIN_PT(i,j,nCN_S);
			////////////////////////////		
			LocalPos.x	= (pConBZ+m)->x;
			LocalPos.y	= (pConBZ+m)->y;
			LocalPos.z	= (pConBZ+m)->z;
			///////////////////////////////////// in THE List 
			pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
			delete pNid;
			//////////////
			if(!pAddNode)	
				return -1;
			///////////////////////////////////// in PATCH 	
   			pCNList->InsertObject(pAddNode); //CNodeList 
		}				
	}
	////////////////////////////////////////////////////////// save Wts
	pDrPatch->SetMemInWts(pWts_BZ);
	/////////////
	return MA_OK;
}

int CMP_CooP3::GeneratePatchBndryCurves()
{
	{
		AfxMessageBox(
			"Internal ERROR:\nint CMP_CooP3::GeneratePatchBndryCurves()\nNOT Implemented Yet");
		return MA_ERROR;
	}
}

int CMP_CooP3::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,CDListMgr* pCurveList_W,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W)
{
	pDrObject->SetDirty(TRUE);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetPatchProc(PP_COONSTRI);
	pDrObject->SetPatchType(PA_COONS);
	pDrObject->SetPatSubType(PS_TRIANGLE);
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	///////////////////////////////////////////////////////////////////
	pDrObject->SetPrimaryDir(3);// both
	/////////////////////////////////////
	SetInfoForDataBase_1(pDrObject,	pCurveList_U,pCurveLatchList_U,
									pCurveList_V,pCurveLatchList_V,
									pCurveList_W,pCurveLatchList_W);
	/////////////////////////////////////////////////////////
	m_nOut = (long)m_nOut_S*(m_nOut_S+1)/2;
	pDrObject->SetLongOutPts(m_nOut);			// m_nOut	
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	int nOutTotal = pDrObject->NumberOfPatches();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMP_CooP3::SetInfoForDataBase\nm_nOut Mismatch!");
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

void CMP_CooP3::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CDListMgr* pCurveList_W,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W)
{
	///////////////////////////////////////////////////////////////////////////////////
	//	ALL Triangular Info SAVED in S-dir variables in Mi_GangP::InsertMeshInfo_3
	//	EXCEPT: 
	//	m_pDrPatch->SetMaxCNodes_T(m_nMaxPatchCNodes);		// Save Total Control Nodes
	///////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////// CurveList
	CDListMgr* pList; 
	POSITION pos;
	CDrCurve* pCurve;
	///////////////////////////////////////////////// Reciprocate
	pList = pDrObject->GetCurveList(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	pList->AddTail(pCurveList_V);
	pList->AddTail(pCurveList_W);
	/////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
	///////////////////////////////////////////////// Save
	pList = pDrObject->GetCurveList_U(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	///////////////////////////////////////////////// Save
	pList = pDrObject->GetCurveList_V(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_V);
	///////////////////////////////////////////////// Save
	pList = pDrObject->GetCurveList_W(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_W);
	/////////////////////////////////////////////////////////////////
	pDrObject->GetCurveLatchList_U()->RemoveAll();
	pDrObject->GetCurveLatchList_U()->AddTail(pCurveLatchList_U);
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList_V);
	pDrObject->GetCurveLatchList_W()->RemoveAll();
	pDrObject->GetCurveLatchList_W()->AddTail(pCurveLatchList_W);
	///////////////////////////////////////////////////////////////// All Other
	m_pDrPatch->SetCurveType_S(m_CurveType_S);
	//////////////////////////////////////////////////////////////////////////
	int nOutPerSeg	= m_pNum_t_S[0];
//	m_pDrPatch->SetSegmentCount_S(nOutPerSeg);			// Output Uniform for Triangular Patch
	m_pDrPatch->SetOutSegUnif_S(nOutPerSeg);			// Output Uniform for Triangular Patch
	//////////////////////////////////////////////////////////////////////////
	m_pDrPatch->SetClosed_S(m_bClosed_S);
	m_pDrPatch->SetDirty(TRUE);
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	m_pDrPatch->SetMaxCNodes_S(m_nMaxPatchCNodes_S);	// Save Control Nodes in Each side of Triangle
	m_pDrPatch->SetMaxCNodes_T(m_nMaxPatchCNodes);		// Save Total Control Nodes
	m_pDrPatch->SetLongOutPts(m_nOut_S*(m_nOut_S+1)/2);	// Total Vertices			 	
	m_pDrPatch->SetOut_S(m_nOut_S);				// IN EACH DIRECTION	
	m_pDrPatch->SetOrder_S(m_nOrder_S);
	m_pDrPatch->SetnDim_S(m_nDim_S);
	////////////////////////////////////// Now Store Triangle Database
	m_nOut_SCon = m_nMaxPatchCNodes_S;	// for compatibility w/ old version
	//////////////////////////////////
	if(m_nOrder_S == 2)
		InsertTriangle_Linear();
	if(m_nOrder_S == 3)
		InsertTriangle_Quad();
	if(m_nOrder_S == 4)
		InsertTriangle_Cubic();
	////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMP_CooP3::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_CooP3:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_CooP3:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
