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
#include "DrPipe.h"
#include "DrBeam.h"
#include "DrTruss.h"
#include "DrElbow.h"
//////////////////////
#include "Regen1D.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegen1D,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegen1D::CRegen1D()
{
}

CRegen1D::~CRegen1D()
{
}
	
int CRegen1D::Update1Ds(CDrFE0D* pDrNode)
{
	////////////////////////////////////////////////////////////////////// Update Dependent 1Ds
	CDListMgr* pCurList;
	int i,nCurCount;
//	int i,j,index,nCurCount,nNodCount;
	POSITION pos;
	//////////////////////////////////////////////// 1Ds
	pCurList	= pDrNode->GetFE1DList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrFE1D* pCurve	= (CDrFE1D*)(pCurList->GetAt(pos));
		////////////////
		if(pCurve)
		{
			pCurve->SetShow(FALSE);
			/////////////////////////////////
			ReGen_EditedElemNodes(pCurve,pDrNode);
			/////////////////////////////////
			pCurve->SetShow(TRUE);

		}
	}
	//////////
	return 0;
}

int CRegen1D::ReGen_EditedElemNodes(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	pElemToEdit->SetShow(FALSE);	// not quite ready
	////////////////////////////////////////////////// GetObjType
	UINT ObjType = (UINT)pElemToEdit->GetObjectType();
	///////////////
	switch(ObjType)
	{
		case TRUSS:
			ReComputeAddlNodeCoords_TRUSS(pElemToEdit,pEditedNode);
			break;
		case BEAM:
			ReComputeAddlNodeCoords_BEAM(pElemToEdit,pEditedNode);
			break;
		case PIPE:
			ReComputeAddlNodeCoords_PIPE(pElemToEdit,pEditedNode);
			break;
		case ELBOW:
			ReComputeAddlNodeCoords_ELBOW(pElemToEdit,pEditedNode);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen1D::ReGen_EditedElemNodes\nUNKNOWN 1D ELEMENT!");
			return -1;
	}
	/////////
	return 0;
}

int CRegen1D::ReComputeAddlNodeCoords_TRUSS(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}

int CRegen1D::ReComputeAddlNodeCoords_BEAM(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}

int CRegen1D::ReComputeAddlNodeCoords_PIPE(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}

int CRegen1D::ReComputeAddlNodeCoords_ELBOW(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}
///////////////////////////////////////
void CRegen1D::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" NodEdit:    Storing\n");	
		

	}
	else
	{
		TRACE(" NodEdit:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


