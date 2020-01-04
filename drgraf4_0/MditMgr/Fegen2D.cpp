// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "MsMath.h"

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
//////////////////////
#include "Regen2D.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegen2D,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegen2D::CRegen2D()
{
}

CRegen2D::~CRegen2D()
{
}
	
int CRegen2D::Update2Ds(CDrFE0D* pDrNode)
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
{
	pElemToEdit->SetShow(FALSE);	// not quite ready
	////////////////////////////////////////////////// GetObjType
	UINT ObjType = (UINT)pElemToEdit->GetObjectType();
	///////////////
	switch(ObjType)
	{
		/////////////////////////////////////////////////////////// TRIANGLEs
		case TR_3:
			ReComputeAddlNodeCoords_TR_3(pElemToEdit,pEditedNode);
			break;
		case TR_6:
			ReComputeAddlNodeCoords_TR_6(pElemToEdit,pEditedNode);
			break;
		case TR_9:
			ReComputeAddlNodeCoords_TR_9(pElemToEdit,pEditedNode);
			break;
		case TR_10:
			ReComputeAddlNodeCoords_TR_10(pElemToEdit,pEditedNode);
			break;
		/////////////////////////////////////////////////////////// QUADRILATs
		case QU_4:
			ReComputeAddlNodeCoords_QU_4(pElemToEdit,pEditedNode);
			break;
		case QU_8:
			ReComputeAddlNodeCoords_QU_8(pElemToEdit,pEditedNode);
			break;
	return 0;
}

int CRegen2D::ReGen_EditedElemNodes(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
		case QU_9:
			ReComputeAddlNodeCoords_QU_9(pElemToEdit,pEditedNode);
			break;
		case QU_12:
			ReComputeAddlNodeCoords_QU_12(pElemToEdit,pEditedNode);
			break;
		case QU_16:
			ReComputeAddlNodeCoords_QU_16(pElemToEdit,pEditedNode);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReGen_EditedElemNodes\nUNKNOWN 2D ELEMENT!");
			return -1;
	}
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_TR_3(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_TR_6(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_6\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 4 & 6 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 4 & 5 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 5 & 6 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_6\nNodeIndex>2");
			return -1;
	}
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_TR_9(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_9\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 4,5 & 8,9 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 4,5 & 6,7 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 6,7 & 8,9 affected
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_9\nNodeIndex>2");
			return -1;
	}
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_TR_10(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_10\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 4,5 & 8,9 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 4,5 & 6,7 affected
			////////////////////////////////////////////////////// Node 4
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(3); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 6,7 & 8,9 affected
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_TR_10\nNodeIndex>2");
			return -1;
	}
	////////////////////////////////////////////////////// Node 10: All cases
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(5))->GetLocalPos()); // Node 6
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(8))->GetLocalPos()); // Node 9
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(.5,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(9); 
	pDrFE0D->SetLocalPos(NewPos);
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_QU_4(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Nothing to do
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_QU_8(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_8\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 5 & 8 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 5 & 6 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5);
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 6 & 7 affected
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 3:													// indices 7 & 8 affected
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_8\nNodeIndex>2");
			return -1;
	}
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_QU_9(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_9\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 5 & 8 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 5 & 6 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5);
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 6 & 7 affected
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5);
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 3:													// indices 7 & 8 affected
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(0.5,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_9\nNodeIndex>2");
			return -1;
	}
	///////////////////////////////////////////////////////// Coords: Node 9: from 5 & 7 
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(4))->GetLocalPos());	// Node 5
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(6))->GetLocalPos());	// Node 7
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(0.5,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
	pDrFE0D->SetLocalPos(NewPos);
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_QU_12(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_12\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 5,6 & 11,12 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 11
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(10); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 12
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(11); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 5,6 & 7,8 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 7,8 & 9,10 affected
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 10
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(9); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 3:													// indices 9,10 & 11,12 affected
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 10
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(9); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 11
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(10); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 12
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(11); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_12\nNodeIndex>2");
			return -1;
	}
	/////////
	return 0;
}

int CRegen2D::ReComputeAddlNodeCoords_QU_16(CDrFE1D* pElemToEdit,CDrFE0D* pEditedNode)
{
	// Which Corner Node Changed
	CDListMgr* pListV = pElemToEdit->GetFE0DList();
	int index = pListV->GetObjectIndex((CObject*)pEditedNode);
	/////////
	if(index<0)
	{
		AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_16\nNodeIndex Not Found");
		return -1;
	}
	/////////////////////////////////////////////////////// Recompute Affected Coords
	CMsMath		MsMath;
	WORLD		LocalPosB,LocalPosE,NewPos;
	CDrFE0D*	pDrFE0D;
	///////////////
	switch(index)
	{
		case 0:													// indices 5,6 & 11,12 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 11
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(10); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 12
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(11); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 1:													// indices 5,6 & 7,8 affected
			////////////////////////////////////////////////////// Node 5
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(4); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 6
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(5); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 2:													// indices 7,8 & 9,10 affected
			////////////////////////////////////////////////////// Node 7
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(6); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 8
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(1))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(7); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 10
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(9); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		case 3:													// indices 9,10 & 11,12 affected
			////////////////////////////////////////////////////// Node 9
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(8); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 10
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(2))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(9); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 11
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosB);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(10); 
			pDrFE0D->SetLocalPos(NewPos);
			////////////////////////////////////////////////////// Node 12
			LocalPosB = *(((CDrFE0D*)pListV->GetObject(3))->GetLocalPos());
			LocalPosE = *(((CDrFE0D*)pListV->GetObject(0))->GetLocalPos());
			MsMath.Scale3DPts(2.,&LocalPosE);
			MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
			MsMath.Scale3DPts(1./3.,&NewPos);
			///
			pDrFE0D = (CDrFE0D*)pListV->GetObject(11); 
			pDrFE0D->SetLocalPos(NewPos);
			break;
		default:
			AfxMessageBox("ERROR:\nCRegen2D::ReComputeAddlNodeCoords_QU_16\nNodeIndex>2");
			return -1;
	}
	////////////////////////////////////////////////////// Node 13
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(6))->GetLocalPos());	// Node 7
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(11))->GetLocalPos());// Node 12	
	MsMath.Scale3DPts(2.,&LocalPosB);
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(12); 
	pDrFE0D->SetLocalPos(NewPos);
	////////////////////////////////////////////////////// Node 14
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(6))->GetLocalPos());	// Node 7
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(11))->GetLocalPos());// Node 12	
	MsMath.Scale3DPts(2.,&LocalPosE);
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(13); 
	pDrFE0D->SetLocalPos(NewPos);
	////////////////////////////////////////////////////// Node 15
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(7))->GetLocalPos());	// Node 8
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(10))->GetLocalPos());// Node 11	
	MsMath.Scale3DPts(2.,&LocalPosB);
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(14); 
	pDrFE0D->SetLocalPos(NewPos);
	////////////////////////////////////////////////////// Node 16
	LocalPosB = *(((CDrFE0D*)pListV->GetObject(7))->GetLocalPos());	// Node 8
	LocalPosE = *(((CDrFE0D*)pListV->GetObject(10))->GetLocalPos());// Node 11	
	MsMath.Scale3DPts(2.,&LocalPosE);
	MsMath.Add3DPts(&LocalPosB,&LocalPosE,&NewPos);
	MsMath.Scale3DPts(1./3.,&NewPos);
	///
	pDrFE0D = (CDrFE0D*)pListV->GetObject(15); 
	pDrFE0D->SetLocalPos(NewPos);
	/////////
	return 0;
}
///////////////////////////////////////
void CRegen2D::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CRegen2D:    Storing\n");	
		

	}
	else
	{
		TRACE(" CRegen2D:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


