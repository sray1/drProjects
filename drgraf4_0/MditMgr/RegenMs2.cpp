// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// IGens
#include "Def_IGen.h"
///////////////////// Elems
#include "Def_Elem.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "MI_Gang1.h"
//////////////////////
#include "RegenMs1.h"

#include "RegenMs2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenMs2,CObject,1)
//IMPLEMENT_SERIAL(CRegenMs2,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenMs2::CRegenMs2()
{
}

CRegenMs2::~CRegenMs2()
{
}
	
int CRegenMs2::UpdateMeshElemCentroids(CDrFE0D* pDrFe0D)
{
	////////////////////////////////////////////////////////////////////// Update Dependent Mesh2D
	CDListMgr* pMs2List;
	int i,j,nCurCount;
//	int i,j,index,nCurCount,nNodCount;
	POSITION pos;
	//////////////////////////////////////////////// Mesh2Ds
	pMs2List	= pDrFe0D->GetMs2List(); 
	nCurCount	= pMs2List->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pMs2List->FindIndex(i);
		CDrMesh2D* pMesh2D	= (CDrMesh2D*)(pMs2List->GetAt(pos));
		////////////////
		if(pMesh2D)
		{
			pMesh2D->SetShow(FALSE);
			int nElemCount;
			///////////////////////////////////////// FE1Ds
			CDListMgr* pList = pMesh2D->GetFE1DList(); 
			if(pList)
			{
				nElemCount = pList->GetCount();
				/////////////////////////////////
				for(j=0;j<nElemCount;j++)
				{
					pos				= pList->FindIndex(j);
					CDrFE1D* pElem	= (CDrFE1D*)(pList->GetAt(pos));
					////////////////
					CRegenMs1* pRegenMs1;
					pRegenMs1->UpdateFE1DCentroid(pElem);
					/////////////////////////////////
				}
			}
			///////////////////////////////////////// FE2Ds
			pList = pMesh2D->GetFE2DList(); 
			if(pList)
			{
				nElemCount = pList->GetCount();
				/////////////////////////////////
				for(j=0;j<nElemCount;j++)
				{
					pos				= pList->FindIndex(j);
					CDrFE2D* pElem	= (CDrFE2D*)(pList->GetAt(pos));
					////////////////
					UpdateFE2DCentroid(pElem);
					/////////////////////////////////
				}
			}
			//////////////////////
			pMesh2D->SetShow(TRUE);

		}
	}
	//////////
	return 0;
}

int CRegenMs2::UpdateFE2DCentroid(CDrFE2D* pDrFe2D)
{
	int nResult = 0;
	////////////////
	CDListMgr* pList = pDrFe2D->GetFE0DList();
	///
	if(!pList)
	{
		nResult = -1;
		return nResult;
	}
	/////////////////////////////////////////// Get Vertices Coords
	int nCorners = pDrFe2D->GetnCorners();
	///////////////////
	pWORLD LocalPos = new WORLD[nCorners];
	CDrFE0D* pFE0D;
	//////
	for(int i=0;i<nCorners;i++)
	{
		pFE0D = (CDrFE0D*)(pList->GetObject(i));
		if(pFE0D)
		{
			LocalPos[i] = *(pFE0D->GetLocalPos());
		}
		else
		{
			nResult = -1;
			return nResult;
		}
	}
	/////////////////////////////////////////// Recalc Centroid
	WORLD wCentroid;
	///
	CMI_Gang1* pGang;
	pGang->CalcCentroid(&wCentroid,LocalPos,nCorners);
	/////////////////////////////////////////// Replace
	CDrFE0D* pCent = (CDrFE0D*)(pDrFe2D->GetNodeList()->GetObject(0));
	//
	pCent->SetLocalPos(wCentroid);
	////////////////////////////// and
	(pCent->GetNodeCard())->x = (long)wCentroid.x;	
	(pCent->GetNodeCard())->y = (long)wCentroid.y;	
	(pCent->GetNodeCard())->z = (long)wCentroid.z;
	///////////////////
	delete [] LocalPos;
	///////////////
	return nResult;

}

void CRegenMs2::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
//	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" RegenMs1:    Storing\n");	
		

	}
	else
	{
		TRACE(" RegenMs1:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


