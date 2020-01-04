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
#include "MI_Gang1.h"
//////////////////////
#include "RegenMs1.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenMs1,CObject,1)
//IMPLEMENT_SERIAL(CRegenMs1,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenMs1::CRegenMs1()
{
}

CRegenMs1::~CRegenMs1()
{
}
	
int CRegenMs1::UpdateMeshElemCentroids(CDrFE0D* pDrFe0D)
{
	////////////////////////////////////////////////////////////////////// Update Dependent Curves
	CDListMgr* pMs1List;
	int i,j,nCurCount;
//	int i,j,index,nCurCount,nNodCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pMs1List	= pDrFe0D->GetMs1List(); 
	nCurCount	= pMs1List->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pMs1List->FindIndex(i);
		CDrMesh1D* pMesh1D	= (CDrMesh1D*)(pMs1List->GetAt(pos));
		////////////////
		if(pMesh1D)
		{
			pMesh1D->SetShow(FALSE);
			int nElemCount;
			///////////////////////////////////////// FE1Ds
			CDListMgr* pList = pMesh1D->GetFE1DList(); 
			if(pList)
			{
				nElemCount = pList->GetCount();
				/////////////////////////////////
				for(j=0;j<nElemCount;j++)
				{
					pos				= pList->FindIndex(j);
					CDrFE1D* pElem	= (CDrFE1D*)(pList->GetAt(pos));
					////////////////
					UpdateFE1DCentroid(pElem);
					/////////////////////////////////
				}
			}
			//////////////////////
			pMesh1D->SetShow(TRUE);

		}
	}
	//////////
	return 0;
}

int CRegenMs1::UpdateFE1DCentroid(CDrFE1D* pDrFe1D)
{
	int nResult = 0;
	////////////////
	CDListMgr* pList = pDrFe1D->GetFE0DList();
	///
	if(!pList || (pList->GetCount() <2) )
	{
		nResult = -1;
		return nResult;
	}
	///////////////////
	WORLD LocalPos[2];
	CDrFE0D* pFE0D;
	/////////////////////////////////////////// Get Vertices Coords
	for(int i=0;i<2;i++)
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
	pGang->CalcCentroid(&wCentroid,LocalPos,2);
	/////////////////////////////////////////// Replace
	CDrFE0D* pCent = (CDrFE0D*)(pDrFe1D->GetNodeList()->GetObject(0));
	//
	pCent->SetLocalPos(wCentroid);
	////////////////////////////// and
	(pCent->GetNodeCard())->x = (long)wCentroid.x;	
	(pCent->GetNodeCard())->y = (long)wCentroid.y;	
	(pCent->GetNodeCard())->z = (long)wCentroid.z;
	///////////////
	return nResult;

}

void CRegenMs1::Serialize(CArchive& ar)
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


