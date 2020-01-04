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
#include "DrFE3D.h"
#include "MI_Gang1.h"
//////////////////////
#include "RegenMs1.h"
#include "RegenMs2.h"

#include "RegenMs3.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenMs3,CObject,1)
//IMPLEMENT_SERIAL(CRegenMs3,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenMs3::CRegenMs3()
{
}

CRegenMs3::~CRegenMs3()
{
}
	
int CRegenMs3::UpdateMeshElemCentroids(CDrFE0D* pDrFe0D)
{
	////////////////////////////////////////////////////////////////////// Update Dependent Mesh2D
	CDListMgr* pMs3List;
	int i,j,nCurCount;
//	int i,j,index,nCurCount,nNodCount;
	POSITION pos;
	//////////////////////////////////////////////// Mesh2Ds
	pMs3List	= pDrFe0D->GetMs3List(); 
	nCurCount	= pMs3List->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pMs3List->FindIndex(i);
		CDrMesh3D* pMesh3D	= (CDrMesh3D*)(pMs3List->GetAt(pos));
		////////////////
		if(pMesh3D)
		{
			pMesh3D->SetShow(FALSE);
			int nElemCount;
			///////////////////////////////////////// FE1Ds
			CDListMgr* pList = pMesh3D->GetFE1DList(); 
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
			pList = pMesh3D->GetFE2DList(); 
			if(pList)
			{
				nElemCount = pList->GetCount();
				/////////////////////////////////
				for(j=0;j<nElemCount;j++)
				{
					pos				= pList->FindIndex(j);
					CDrFE2D* pElem	= (CDrFE2D*)(pList->GetAt(pos));
					////////////////
					CRegenMs2* pRegenMs2;
					pRegenMs2->UpdateFE2DCentroid(pElem);
					/////////////////////////////////
				}
			}
			///////////////////////////////////////// FE3Ds
			pList = pMesh3D->GetFE3DList(); 
			if(pList)
			{
				nElemCount = pList->GetCount();
				/////////////////////////////////
				for(j=0;j<nElemCount;j++)
				{
					pos				= pList->FindIndex(j);
					CDrFE3D* pElem	= (CDrFE3D*)(pList->GetAt(pos));
					////////////////
					UpdateFE3DCentroid(pElem);
					/////////////////////////////////
				}
			}
			//////////////////////
			pMesh3D->SetShow(TRUE);

		}
	}
	//////////
	return 0;
}

int CRegenMs3::UpdateFE3DCentroid(CDrFE3D* pDrFe3D)
{
	int nResult = 0;
	////////////////
	CDListMgr* pList = pDrFe3D->GetFE0DList();
	///
	if(!pList)
	{
		nResult = -1;
		return nResult;
	}
	/////////////////////////////////////////// Get Vertices Coords
	int nCorners = pDrFe3D->GetnCorners();
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
	CDrFE0D* pCent = (CDrFE0D*)(pDrFe3D->GetNodeList()->GetObject(0));
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

void CRegenMs3::Serialize(CArchive& ar)
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


