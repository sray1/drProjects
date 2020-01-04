///////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
#include "DegElevate.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "Str_BlendEnd.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "Twist.h" 
#include "MP_LoftX.h" 
#include "MP_Tensor.h"
////////////////////// 
#include "MP_Gordon.h" 

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
IMPLEMENT_SERIAL(CMP_Gordon,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Gordon::CMP_Gordon()
{
}

CMP_Gordon::~CMP_Gordon()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Gordon::GoDoIt 
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
				) 
{
	int i,j,nTotData;
	//////////////////////////////////
	nTotData	= nNodes_U * nNodes_V;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	///////////////////////
	m_PatchID	= PatchID;
	m_pDrPatch	= pDrPatch;
	/////////////////////////////////////////////////////////////////////////////////// Loft	
	int nCon_SNew,nCon_TNew;
	CString PatchID_Temp;
	int	nBezSeg,nDim,nTopDegree_S,nTopDegree_T,nConBZ;
	int nCurDir;
	CMP_LoftX* pLoft = new CMP_LoftX;
	//////////////////////////////////////////////////////////////////////////// Info_U
	// Degree Elevation/Set Properties
	//////
	nResult = CheckDegreeElevation(pCurveList_U,pBlendCurve_U,
								nBezSeg,nDim,nTopDegree_S,nConBZ);
	//////////////////////////////////////////////////////////////// Dim up
	if(pBlendCurve_U->GetnDim_S() == 4||pBlendCurve_V->GetnDim_S() == 4)	// override
		nDim = 4;
	////////////////////////////////////////////////////////////////// Fill Info
	nCurDir			= 1;
	nResult = LatticeCurvesInfo(nCurDir,nBezSeg,nConBZ,nDim,nTopDegree_S,
					ElperSegList_U,Ratio_U,pCurveList_U,pBlendCurve_U);
	if(nResult == MA_ERROR)
		return nResult;
	//////////////////////////////////////////////////////////// Loft_1
	PatchID_Temp	= "Loft1";
	CDrPatch* pDrPatch_L1 = new CDrPatch;
	////////////////////////////////////
	nResult = pLoft->GoDoIt(FALSE,TRUE,pBlendCurve_U,bAdvanced,pCornerTwist,TwistMethod,nCurDir,
							PatchID_Temp,pDrPatch_L1,nNodes_U,nNodes_V,pNodeList,
							pCurveList_U,pLatchList_U,ElperSegList_V,
							pBlendCurve_V,Ratio_V,pEndList_V,pView);
	if(nResult == MA_ERROR)
		return nResult;
	//////////////////////////////////////////////////////////////////////////// Info_V
	nResult = CheckDegreeElevation(pCurveList_V,pBlendCurve_V,
								nBezSeg,nDim,nTopDegree_T,nConBZ);// need nTopDegree_T
	/////////////////////// for Blending Order Discrepancy with Curves
	nResult = CheckDegreeElevation_PatchTP(pDrPatch_L1,nTopDegree_S,nTopDegree_T,
															nCon_SNew,nCon_TNew);
	//////////////////////////////////////////////////////////////// Dim up
	if(pBlendCurve_U->GetnDim_S() == 4||pBlendCurve_V->GetnDim_S() == 4)	// override
		nDim = 4;
	////////////////////////////////////////////////////////////////// Fill Info
	nCurDir			= 2;
	nResult = LatticeCurvesInfo(nCurDir,nBezSeg,nConBZ,nDim,nTopDegree_T,
					ElperSegList_V,Ratio_V,pCurveList_V,pBlendCurve_V);
	if(nResult == MA_ERROR)
		return nResult;
	//////////////////////////////////////////////////////////// Loft_2
	PatchID_Temp	= "Loft2";
	CDrPatch* pDrPatch_L2 = new CDrPatch;
	////////////////////////////////////
	nResult = pLoft->GoDoIt(FALSE,TRUE,pBlendCurve_V,bAdvanced,pCornerTwist,TwistMethod,nCurDir,
							PatchID_Temp,pDrPatch_L2,nNodes_V,nNodes_U,pNodeList,
							pCurveList_V,pLatchList_V,ElperSegList_U,
							pBlendCurve_U,Ratio_U,pEndList_U,pView);
	if(nResult == MA_ERROR)
		return nResult;
	/////////////////////// for Blending Order Discrepancy with Curves
	nResult = CheckDegreeElevation_PatchTP(pDrPatch_L2,nTopDegree_S,nTopDegree_T,
															nCon_SNew,nCon_TNew);
	///////////////////////
	delete pLoft;
	////////////////////////////////////////////////////////////////// Tensor Product
	CMP_Tensor* pTensor = new CMP_Tensor;
	PatchID_Temp	= "Tensor";
	CDrPatch* pDrPatch_TP = new CDrPatch;
	////////////////////////////////////
	nResult = pTensor->GoDoIt(FALSE,bAdvanced,PatchID_Temp,pDrPatch_TP,pNodeList,
						pCornerTwist,TwistMethod,
						nNodes_U,ElperSegList_U,Ratio_U,pBlendCurve_U,pEndList_U,
						nNodes_V,ElperSegList_V,Ratio_V,pBlendCurve_V,pEndList_V,
						pView);
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////////
	delete pTensor;
	/////////////////////// for Blending Order Discrepancy with Curves
	// Since Combination is being performed with Control Nodes and
	// NOT surface Pts, All Control Nodes Must be Elevated to same
	// same Degree
	nResult = CheckDegreeElevation_PatchTP(pDrPatch_TP,nTopDegree_S,nTopDegree_T,
															nCon_SNew,nCon_TNew);
	////////////////////////////////////////////////////////////////// Gordon
	nResult = Combine(pDrPatch,pDrPatch_L1,pDrPatch_L2,pDrPatch_TP,
												nCon_SNew,nCon_TNew);
	////////////////////////////////////////////////////////////////// delete
	delete pDrPatch_L1;
	delete pDrPatch_L2;
	delete pDrPatch_TP;
	////////////////////
	m_bAdvancedEnd_T = bAdvanced; 
	m_TwistMethod_T  = TwistMethod;
	if(TwistMethod == TW_USER)
	{
		m_pCornerTwist_T = new WORLD[2][2];	// it is full,if TW_USER
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
				m_pCornerTwist_T[i][j] = pCornerTwist[i][j];
	}
	else
		m_pCornerTwist_T = NULL;
	///////////////////////////////////////////////
	pDrPatch->GetElperSegList_S()->RemoveAll();
	pDrPatch->GetElperSegList_T()->RemoveAll();
	pDrPatch->GetElperSegList_S()->AddTail(&ElperSegList_U);	// save for later editing etc
	pDrPatch->GetElperSegList_T()->AddTail(&ElperSegList_V);	// save for later editing etc
	////////////////
	nResult = SetInfoForDataBase(pDrPatch,pCurveList_U,pCurveList_V,
						pLatchList_U,pLatchList_V,pBlendCurve_U,pBlendCurve_V,
						pEndList_U,pEndList_V);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PostProcess
int CMP_Gordon::CheckDegreeElevation_PatchTP(CDrPatch* pDrPatch,int nTopDeg_U,int nTopDeg_V,
											 int& nCon_SNew,int& nCon_TNew)
{
	int nResult;
	////////////
	int nCon_S,nCon_T,nDim_S,nDim_T,nElev_S,nElev_T,nDeg_S,nDeg_T;
	int nSegBZ_S,nSegBZ_T;
	//////////////////////////////////////////////////////////////
	m_bClosed_S = pDrPatch->IsClosed_S(); 
	m_bClosed_T = pDrPatch->IsClosed_T(); 
	///////////////////////////////////
	nCon_S	= pDrPatch->GetMaxCNodes_S();
	nCon_T	= pDrPatch->GetMaxCNodes_T();
	nSegBZ_S= pDrPatch->GetMaxBezSegments_S();
	nSegBZ_T= pDrPatch->GetMaxBezSegments_T();
	nDim_S	= pDrPatch->GetnDim_S();
	nDim_T	= pDrPatch->GetnDim_T();
	nDeg_S	= pDrPatch->GetOrder_S() - 1;
	nDeg_T	= pDrPatch->GetOrder_T() - 1;
	////////////////////////////////////
	nElev_S = nTopDeg_U - nDeg_S;
	nElev_T = nTopDeg_V - nDeg_T;
	/////////////////////////////
	if(nElev_S<0)
		nElev_S = 0;
	if(nElev_T<0)
		nElev_T = 0;
	///////////////////////////////////////////////
	nCon_SNew			= (nCon_S + nElev_S * nSegBZ_S);
	nCon_TNew			= (nCon_T + nElev_T * nSegBZ_T); 
	////////////////////////////////////////////////////////// no need
	if( (nElev_S<=0) && (nElev_T<=0) )
		return MA_OK;
	////////////////////////////////////////////////////////// Get Patch CNList & Wts Array
	CDListMgr* pCNList	= pDrPatch->GetCNodeList();
	pDOUBLE pWts		= pDrPatch->GetMemInWts();
	////////////////////////////////////////////////////////// One direction at a time:dir_S
	int nConBZ_Tot;
	pWORLD  pConBZ; 	
	pDOUBLE pWtsBZ;
	///////////////
	if(nElev_S>0)
	{
		nConBZ_Tot	= nCon_SNew * nCon_T;
		//////////
		pConBZ		= new WORLD [nConBZ_Tot]; 	
		pWtsBZ		= new double[nConBZ_Tot];
		//////////
		int nConTot;
		////////////
		nResult = ElevatePat_S(pCNList,pWts,nCon_S,nDeg_S,nSegBZ_S,
								pConBZ,pWtsBZ,nElev_S,nDim_S,nConTot);
		///
		if(nResult != MA_OK)
			return nResult;
		///
		if(nConTot != nConBZ_Tot)
			return MA_ERROR;
		///////////////////////////////////////// Update CNList and Wts Array etc.
		while(!pCNList->IsEmpty())
			delete pCNList->RemoveHead(); 
		delete [] pWts;
		///////////////
		pWts = new double[nConBZ_Tot];
		UpdateCN_N_Wts(pCNList,pWts,pConBZ,pWtsBZ,nCon_SNew,nCon_T);
		//////////
		delete [] pConBZ; 	
		delete [] pWtsBZ;
		//////////
	}
	////////////////////////////////////////////////////////// One direction at a time:dir_T
	if(nElev_T>0)
	{
		nConBZ_Tot	= nCon_SNew * nCon_TNew;
		//////////
		pConBZ		= new WORLD [nConBZ_Tot]; 	
		pWtsBZ		= new double[nConBZ_Tot];
		//////////
		int nConTot;
		////////////
		nResult = ElevatePat_T(pCNList,pWts,nCon_T,nDeg_T,nSegBZ_T,
								pConBZ,pWtsBZ,nElev_T,nDim_T,nConTot);
		///
		if(nResult != MA_OK)
			return nResult;
		///
		if(nConTot != nConBZ_Tot)
			return MA_ERROR;
		///////////////////////////////////////// Update CNList and Wts Array etc.
		while(!pCNList->IsEmpty())
			delete pCNList->RemoveHead(); 
		delete [] pWts;
		///////////////
		pWts = new double[nConBZ_Tot];
		UpdateCN_N_Wts(pCNList,pWts,pConBZ,pWtsBZ,nCon_SNew,nCon_TNew);
		//////////
		delete [] pConBZ; 	
		delete [] pWtsBZ;
		//////////
	}
	///////////////////////////////////////////// Save Wts Array etc
	pDrPatch->SetMemInWts(pWts);
	////////////////////////////////////
	pDrPatch->SetMaxCNodes_S(nCon_SNew);
	pDrPatch->SetMaxCNodes_T(nCon_TNew);
	pDrPatch->SetOrder_S(nDeg_S + nElev_S + 1);
	pDrPatch->SetOrder_T(nDeg_T + nElev_T + 1);
	/////////////
	return MA_OK;
}

int CMP_Gordon::UpdateCN_N_Wts(CDListMgr* pCNList,pDOUBLE pWts,pWORLD pCon_BZ,pDOUBLE pWts_BZ,
																int nCon_SNew, int nCon_TNew)
{

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
    CDrNode* 	pAddNode;
	int s,t,k;
	///////////////////////////////////////
	for (t = 0; t<nCon_TNew; t++)
	{
		for (s = 0; s<nCon_SNew; s++)
		{
			k = t* nCon_SNew + s;  
			//////////////////////////////////// Coords
			LocalPos = pCon_BZ[k];
			//////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
			sprintf(buf,"C_%d_%d",s,t);
			///////////////////////////////////// in THE List 
			pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
			delete pNid;
			/////////////
			if(!pAddNode)	// Create DrCNode
				return MA_ERROR;
			///////////////////////////////////// 	
			pCNList->InsertObject(pAddNode); //CNodeList
			/////////////////
			pWts[k] = pWts_BZ[k]; 
		}	
	}
	/////////////////////////////////////////////////////////////////////	
	return MA_OK;
}

int CMP_Gordon::ElevatePat_S(CDListMgr* pCNList,pDOUBLE pWts,int nConOld,int nDegOld,int nSeg_BZ,
							pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nElev, int nDim,int& nConTot)
{

	CDegElevate DegElevate(m_bClosed_S);
	///////////////////////////////////
	int nCol;
	int m,nConNew,nBegNew=0;
	////////////////////////////////////////////
	int nCount	= pCNList->GetCount();
	if(nCount<=0)
		return MA_ERROR;
	//////////////////////////////////////////// 	
	int nColTot	= nCount/nConOld; 
  	////////////////////////////////////////// memory	
	pWORLD		pConOld;
	pDOUBLE		pWtsOld;
	pWORLD		pConNew;
	pDOUBLE		pWtsNew;
	//////////////////////////////////////////////////////////// Controls for each Col
	nConTot=0;
	//////////
	for (nCol=0;nCol<nColTot;nCol++)
	{
		/////////////////////////////////////// GetControl Nodes
   		nConNew		= nConOld;	
   		if(nElev>0)
   			nConNew	+= nElev * nSeg_BZ;	// nElev Cnodes per Curve Segment
		if(m_bClosed_S) 
			nConNew--;
   		////////////////////////////////////////// memory	
		pConOld 	= new WORLD [nConOld];
		pWtsOld 	= new double[nConOld];
		pConNew 	= new WORLD [nConNew];
		pWtsNew 	= new double[nConNew];
		////////////////////////////////////////// get Old 
		GetCNodeCoords_N_Wts_U(pCNList,pWts,pConOld,pWtsOld,nConOld,nCol);
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
			AfxMessageBox("Internal Problem:\nCMP_Gordon::ElevatePat_S");
			return MA_ERROR;
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
	return MA_OK;
}

int CMP_Gordon::GetCNodeCoords_N_Wts_U(CDListMgr* pCNList,pDOUBLE pWts,
										pWORLD pConOld,pDOUBLE pWtsOld,
												int nConBZ_U,int nCol)
{
	POSITION pos;
	/////////////////////////////////////////////////////////////// Coords 
	int j,jStart,index;
	jStart = nConBZ_U*nCol; 
	///////////////////////
	for(j=0;j<nConBZ_U;j++)
	{
		index = j + jStart;
		//////////////////
		pos = pCNList->FindIndex(index);
		CDrNode* pNode = (CDrNode*)pCNList->GetAt(pos);
		///////////////////////////////////////
		pConOld[j] = *(pNode->GetLocalPos());
		/////////////////////////////////////////////////////////// Wts
		pWtsOld[j] = pWts[index];
	}
	/////////
	return 0;
}

int CMP_Gordon::ElevatePat_T(CDListMgr* pCNList,pDOUBLE pWts,int nConOld,int nDegOld,int nSeg_BZ,
							pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nElev, int nDim,int& nConTot)
{

	CDegElevate DegElevate(m_bClosed_T);
	///////////////////////////////////
	int nRow;
	int m,nConNew,nBegNew=0;
	////////////////////////////////////////////
	int nCount	= pCNList->GetCount();
	if(nCount<=0)
		return MA_ERROR;
	//////////////////////////////////////////// 	
	int nRowTot	= nCount/nConOld; 
  	////////////////////////////////////////// memory	
	pWORLD		pConOld;
	pDOUBLE		pWtsOld;
	pWORLD		pConNew;
	pDOUBLE		pWtsNew;
	//////////////////////////////////////////////////////////// Controls for each Col
	nConTot=0;
	//////////
	for (nRow=0;nRow<nRowTot;nRow++)
	{
		/////////////////////////////////////// GetControl Nodes
   		nConNew		= nConOld;	
   		if(nElev>0)
   			nConNew	+= nElev * nSeg_BZ;	// nElev Cnodes per Curve Segment 
		if(m_bClosed_T) 
			nConNew--;
   		////////////////////////////////////////// memory	
		pConOld 	= new WORLD [nConOld];
		pWtsOld 	= new double[nConOld];
		pConNew 	= new WORLD [nConNew];
		pWtsNew 	= new double[nConNew];
		////////////////////////////////////////// get Old 
		GetCNodeCoords_N_Wts_V(pCNList,pWts,pConOld,pWtsOld,nRowTot,nConOld,nRow);
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
			AfxMessageBox("Internal Problem:\nCMP_Gordon::ElevatePat_S");
			return MA_ERROR;
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
	////////////////////////////////////////////////////////// Transpose Cons & Wts
	TransposeCons_N_Wts(pCon_BZ,pWts_BZ,nRowTot,nConNew);
	//////////////////
	return MA_OK;
}

int CMP_Gordon::GetCNodeCoords_N_Wts_V(CDListMgr* pCNList,pDOUBLE pWts,
										pWORLD pConOld, pDOUBLE pWtsOld,
									int nConBZ_U,int nConBZ_V,int nRow)
{
	POSITION pos;
	/////////////////////////////////////////////////////////////// Coords 
	int j,jStart,index;
	jStart = nConBZ_U*nRow; 
	///////////////////////
	for(j=0;j<nConBZ_V;j++)
	{
		index = nRow + j*nConBZ_U;
		//////////////////////////
		pos = pCNList->FindIndex(index);
		CDrNode* pNode = (CDrNode*)pCNList->GetAt(pos);
		///////////////////////////////////////
		pConOld[j] = *(pNode->GetLocalPos());
		pWtsOld[j] = pWts[index];
	}
	/////////
	return 0;
}

int CMP_Gordon::TransposeCons_N_Wts(pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nRowTot,int nColTot)
{
	int i,k,nTot,iRow,jCol,index;
	////////
	nTot				= nRowTot*nColTot; 
	pWORLD	pConTem 	= new WORLD [nTot];
	pDOUBLE	pWtsTem 	= new double[nTot];
	////////////////////////////////////////////////// copy
	for(i=0;i<nTot;i++)
	{
		pConTem[i] = pCon_BZ[i]; 
		pWtsTem[i] = pWts_BZ[i]; 
	}
	////////////////////////////////////////////////// Transpose
	for(k=0;k<nTot;k++)
	{
		iRow = k%nRowTot;
		jCol = k/nRowTot;
		//////////////
		index = jCol + iRow*nColTot;
		/////
		pCon_BZ[k] = pConTem[index]; 
		pWts_BZ[k] = pWtsTem[index]; 
		////////////////////////////
	}
	/////////////
	return MA_OK;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Gordon::CheckDegreeElevation(CDListMgr* pCurveList,CDrCurve* pBlendCurve,
							int& nBezSeg,int& nDim,int& nTopDegree,int& nCon_BZ)
{
	//////////////////////////////////////////////////////////// Segment Compatibility
	PreProcessCurvesControlInfo(pCurveList,nDim,nTopDegree); // TopDegree? etc
	////////////////////////////////////////////////////////////////
	int nDegree = pBlendCurve->GetOrder_S() - 1;
	if(nDegree>nTopDegree)
		nTopDegree = nDegree;
	//////////////////////////////////////////////////////////// Do it
	// Total Expected CNodes of EACH Curve
	if(!IsCompat_NumberOfCNodes(pCurveList,nTopDegree,nBezSeg,nCon_BZ) )
	{
		AfxMessageBox(
		"DATA ERROR\nCOMPATIBILITY Problem\nNumber of Bezier Segments MisMatch!!\nTask Cancelled");
		return MA_ERROR;
	}
	//////////
	return MA_OK;
}

int CMP_Gordon::PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim,int& nTopDegree)
{
	/////////////////////////////////////// Rational?
	nDim	= 3;
	if(IsRational(pCurveList))
		nDim = 4;
	/////////////////////////////////////// Find Highest Degree
	nTopDegree	= GetTopDegree(pCurveList);
	////////////
	return MA_OK;
}

BOOL CMP_Gordon::IsRational(CDListMgr* pCurveList)
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

int CMP_Gordon::GetTopDegree(CDListMgr* pCurveList)
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

BOOL CMP_Gordon::IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
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

int CMP_Gordon::Combine(CDrPatch* pDrPatch,CDrPatch* pDrPatch_L1, 
						CDrPatch* pDrPatch_L2,CDrPatch* pDrPatch_TP,
									 int nCon_SNew,int nCon_TNew)
{
	WORLD LocalPos;
	int sL=-1,s,t;
	//////////////
	CDListMgr* pCNList		= pDrPatch->GetCNodeList(); 
	CDListMgr* pCNList_L1	= pDrPatch_L1->GetCNodeList(); 
	CDListMgr* pCNList_L2	= pDrPatch_L2->GetCNodeList(); 
	CDListMgr* pCNList_TP	= pDrPatch_TP->GetCNodeList();
	/////////////////////
	pDOUBLE pWts_L1	= pDrPatch_L1->GetMemInWts(); 
	pDOUBLE pWts_L2	= pDrPatch_L2->GetMemInWts(); 
	pDOUBLE pWts_TP	= pDrPatch_TP->GetMemInWts(); 
	/////////////////////
	pDOUBLE pWts			= new double[nCon_SNew * nCon_TNew];
	//////////////////////////////////////////////////////
	POSITION pos_L1,pos_L2,pos_TP;
	//////////////////////////////////////////////////////
	for (	pos_L1 = pCNList_L1->GetFirstObjectPos(),
			pos_L2 = pCNList_L2->GetFirstObjectPos(),
			pos_TP = pCNList_TP->GetFirstObjectPos();pos_L1 !=NULL;)
	{
		sL++;
		////
		CDrNode* pNode_L1 = (CDrNode*)pCNList_L1->GetNextObject(pos_L1);
		if(!pNode_L1)
			return MA_ERROR;
		CDrNode* pNode_L2 = (CDrNode*)pCNList_L2->GetNextObject(pos_L2);
		if(!pNode_L2)
			return MA_ERROR;
		CDrNode* pNode_TP = (CDrNode*)pCNList_TP->GetNextObject(pos_TP);
		if(!pNode_TP)
			return MA_ERROR;
   	 	/////////////////////////////////////////////////////////////// Combine 4D:PreImage
		pWts[sL]	=	pWts_L1[sL] + pWts_L2[sL] - pWts_TP[sL];
		///
		LocalPos.x	=	pWts_L1[sL] * (pNode_L1->GetLocalPos())->x + 
						pWts_L2[sL] * (pNode_L2->GetLocalPos())->x - 
						pWts_TP[sL] * (pNode_TP->GetLocalPos())->x ; 
		LocalPos.x	/=	pWts[sL]; 
		LocalPos.y	=	pWts_L1[sL] * (pNode_L1->GetLocalPos())->y + 
						pWts_L2[sL] * (pNode_L2->GetLocalPos())->y - 
						pWts_TP[sL] * (pNode_TP->GetLocalPos())->y ; 
		LocalPos.y	/=	pWts[sL]; 
		LocalPos.z	=	pWts_L1[sL] * (pNode_L1->GetLocalPos())->z + 
						pWts_L2[sL] * (pNode_L2->GetLocalPos())->z - 
						pWts_TP[sL] * (pNode_TP->GetLocalPos())->z ; 
		LocalPos.z	/=	pWts[sL]; 
		/////////////////////////////////////////////////////////////// Save
		s = sL%nCon_SNew;
		t = sL/nCon_SNew;
		////////////////
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_C%d_%d",pDrPatch->GetObjectID(),s,t);
		///////////////////////////////////////// in THE List 
		CDrNode* pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		//////////////
		if(!pAddNode)	// 
			return MA_ERROR;
		////////////////////////////////////////  	
		pCNList->InsertObject(pAddNode); // 

	}
	////////////////////////////////////////////////////// Wts
	pDrPatch->SetMemInWts(pWts);
	/////////////
	return MA_OK;
}

int CMP_Gordon::LatticeCurvesInfo
				(
					int								nDir,
					//////////////////////////////////////////////
					int								nBezSeg,
					int								nConBZ,
					int								nDim,
					int								nDegree,
					//////////////////////////////////////////////
					CList<int,int>&					ElperSegList,
					double							Ratio,
					CDListMgr*						pCurveList,	
					CDrCurve*						pBlendCurve
					///////////////////////////////////////////////
				) 
{
	int nResult = MA_OK;
	CDrCurve* pCurve = (CDrCurve*)pCurveList->GetHead();
	////////////////////////////////////////////////////// Info
	if(nDir == 1)	// S-dir
	{
		//////////////////////////////////////////////// Process Output_S
		SetPatchOutputDataFromCurve(pCurve,1/*nDir*/);
		//////////
		m_nOrder_S			= nDegree + 1;
		m_bClosed_S			= pCurve->IsClosed_S();
		m_nDim_S			= nDim;
		m_CurveType_S		= pBlendCurve->GetCurveType_S();
		m_nSegs_S			= nBezSeg;				
		m_nMaxPatchCNodes_S	= nConBZ;
	}
	else
	if(nDir == 2)	// T-dir
	{
		//////////////////////////////////////////////// Process Output_T
		SetPatchOutputDataFromCurve(pCurve,2/*nDir*/);
		//////////
		m_nOrder_T			= nDegree + 1;
		m_bClosed_T			= pCurve->IsClosed_S();
		m_nDim_T			= nDim;
		m_CurveType_T		= pBlendCurve->GetCurveType_S();
		m_nSegs_T			= nBezSeg;				
		m_nMaxPatchCNodes_T	= nConBZ;
	}
	///////////////////////
	return nResult;
}

int CMP_Gordon::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CDrCurve* pBlendCurve_U,CDrCurve* pBlendCurve_V,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V)
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
	pDrObject->SetPatchProc(PP_GORDON);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(FALSE);
	///////////////////////////////////////////////////////////////////
	pDrObject->SetPrimaryDir(1);// normal direction U dir is U dir
	/////////////////////////////////////
	SetInfoForDataBase_1(pDrObject,	pCurveList_U,pCurveLatchList_U,pBlendCurve_U,
									pCurveList_V,pCurveLatchList_V,pBlendCurve_V,
									pEndList_U,pEndList_V);
	/////////////////////////////////////////////////////////
	m_nOut = (long)m_nOut_S * (long)m_nOut_T;
	pDrObject->SetLongOutPts(m_nOut);			// m_nOut	
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	int nOutTotal = pDrObject->NumberOfPatches();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMP_Gordon::SetInfoForDataBase\nm_nOut Mismatch!");
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


void CMP_Gordon::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,CDrCurve* pBlendCurve_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,CDrCurve* pBlendCurve_V,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V)
{
	////////////////////////////////////////////////////////// EndList
	pDrObject->SetAdvancedEnd_V(m_bAdvancedEnd_T);
//	if(m_bAdvancedEnd_T)
//	{
		pDrObject->GetEndList_U()->RemoveAll();
		pDrObject->GetEndList_U()->AddTail(pEndList_U);
		pDrObject->GetEndList_V()->RemoveAll();
		pDrObject->GetEndList_V()->AddTail(pEndList_V);
//	}
	////////////////////////////////////////////////////////// CurveList
	CDListMgr* pList; 
	POSITION pos;
	CDrCurve* pCurve;
	///////////////////////////////////////////////// Reciprocate
	pList = pDrObject->GetCurveList(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	pList->AddTail(pCurveList_V);
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
	/////
/*
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,RGB(255,0,255),PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
*/
	///////////////////////////////////////////////// Save
	pList = pDrObject->GetCurveList_V(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_V);
	/////
/*
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,RGB(255,0,255),PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
*/
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetAdvancedEnd_V(m_bAdvancedEnd_T);
	pDrObject->SetTwistMethod_V(m_TwistMethod_T);
	pDrObject->SetCornerTwist_V(m_pCornerTwist_T);// it is full,if TW_USER
	/////////
	pDrObject->GetCurveLatchList_U()->RemoveAll();
	pDrObject->GetCurveLatchList_U()->AddTail(pCurveLatchList_U);
	pDrObject->SetBlendCurve_U(pBlendCurve_U);
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList_V);
	pDrObject->SetBlendCurve_V(pBlendCurve_V);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetRatio_T(m_Ratio_T);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_T(m_nMaxOSeg_T); 	// for Old Compatibility
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_S);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_T(m_nMaxOSeg_T);	// Number of Output Segments
//?
	pDrObject->SetMaxOutPts_S(m_nOut_S);
	pDrObject->SetMaxOutPts_T(m_nOut_T);
	pDrObject->SetOut_S(m_nOut_S);
	pDrObject->SetOut_T(m_nOut_T);
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetCurveType_T(m_CurveType_T);
	pDrObject->SetMaxCNodes_S(m_nMaxPatchCNodes_S);
	pDrObject->SetMaxCNodes_T(m_nMaxPatchCNodes_T);
	///////////////////////////////////////////////////
//	pDrObject->SetSegmentCount_S(m_nSegs_S);	
//	pDrObject->SetSegmentCount_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_S(m_nSegs_S);	
	pDrObject->SetMaxBezSegments_T(m_nSegs_T); 
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetClosed_T(m_bClosed_T);
	pDrObject->SetOut_S(m_nOut_S);	
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOrder_S(m_nOrder_S);
	pDrObject->SetOrder_T(m_nOrder_T);
//	pDrObject->SetnDim_S(m_nDim_S);
//	pDrObject->SetnDim_T(m_nDim_T);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_T(4);	// ALWAYS RATIONAL
	///////////////////////////////////////////////////////// for now
	pDrObject->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_T(m_pNum_t_T);			// Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pDis_t_S);			// s-distribution
	pDrObject->SetDis_tPointer_T(m_pDis_t_T);			// t-distribution
	////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMP_Gordon::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Gordon:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Gordon:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
