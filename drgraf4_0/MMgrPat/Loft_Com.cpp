
#include "stdafx.h"
#include "DListMgr.h"
#include "DrCurve.h"
#include "Def_MouseAct.h"
///////////////////
#include "Loft_Com.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CLoft_Compat, CObject)
//////////////////// 
BOOL CLoft_Compat::AreCurvesCompatible(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList)
{
	BOOL	bClosed;
	int		nDim_S;
	int		nTopDegree;
	//////////////////////////////////////////////////////////// ALL Closed or Open
	if(!IsCompat_Closed(pCurveList,bClosed))
		return FALSE;
	//////////////////////////////////////////////////////////// Segment Compatibility
	PreProcessCurvesControlInfo(pCurveList,nDim_S,nTopDegree); // TopDegree? etc
	//////////////////////////////////////////////////////////// Do it
	int	nCon_BZ;
	int nBezSeg;
	// Total Expected CNodes of EACH Curve
	if(!IsCompat_NumberOfCNodes(pCurveList,nTopDegree,nBezSeg,nCon_BZ) )
		return FALSE;
	//////////////////////////////////////////////////////////// Output Compatibility
	if(!IsCompat_OutputInfo(pCurveList,pLatchList) ) // ElPerSegList etc
		return FALSE;
	//////////
	return TRUE;
}

BOOL CLoft_Compat::IsCompat_Closed(CDListMgr* pCurveList,BOOL& bClosed)
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

int CLoft_Compat::PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim_S,int& nTopDegree)
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

BOOL CLoft_Compat::IsRational(CDListMgr* pCurveList)
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

int CLoft_Compat::GetTopDegree(CDListMgr* pCurveList)
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

BOOL CLoft_Compat::IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
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

BOOL CLoft_Compat::IsCompat_OutputInfo(CDListMgr* pCurveList,
						CList<CURVELATCH,CURVELATCH>* pLatchList)
{
	POSITION pos,posL;
	BOOL bCompareBKward = FALSE;
	CURVELATCH LatchOld;
	CURVELATCH Latch;
	int nOut,nOutOld,nBezSegs;
	pINT	pNum;
	pINT	pNumOld;
	/////////////////////////////////////// Is ALL Output Info same?
	CDListMgr* pList	= pCurveList;
	int i= -1,j;
	//////////////////////////////////////////////////////////// Find Highest Degree
	for (pos = pList->GetFirstObjectPos(),posL = pLatchList->GetHeadPosition();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pList->GetNextObject(pos);
		if(!pCurve)
			return FALSE;
		Latch	= pLatchList->GetNext(posL);  
		nOut	= (int)pCurve->GetLongOutPts();
		pNum	= pCurve->GetNum_tPointer_S();
   	 	///////////////////////////////////////////// 
		i++;
		if(i<=0)
		{
			nBezSegs		= pCurve->GetMaxBezSegments_S();
			pNumOld			= pNum;
			LatchOld		= Latch;
			nOutOld			= nOut;
			/////////
			continue;
		}
		else
		{
			if(nOutOld	!= nOut)
				return FALSE;
			///////////////////////////////////////// SegmentWise
			bCompareBKward = (LatchOld == Latch)? FALSE:TRUE;
			///////////////////////////////////////////// go over the list
			if(bCompareBKward)
			{
				for (j=0;j<nBezSegs;j++)
				{
					////
					int nElems		= pNum[(nBezSegs-1)-j];
					///////
					int nElemsOld	= pNumOld[j];
					///////////////////////////////////////////////// same
					if(nElemsOld != nElems)
						return FALSE;
				}
			}
			else
			{
				for (j=0;j<nBezSegs;j++)
				{
					////
					int nElems		= pNum[j];
					///////
					int nElemsOld	= pNumOld[j];
					///////////////////////////////////////////////// same
					if(nElemsOld != nElems)
						return FALSE;
				}
			}
		}
	}
	////////////
	return TRUE;
/*
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
*/
}
////////////////////////////// end of Module ////////////////////////
