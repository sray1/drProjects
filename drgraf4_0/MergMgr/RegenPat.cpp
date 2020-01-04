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
/////////////////////
#include "MP_Xtrud.h"
#include "MP_Rotat.h"
#include "MP_Loft2.h"
#include "MP_CoonP.h"
#include "MP_CooP3.h"
#include "MP_Duct.h"
#include "MP_Sweep.h"
///////////////////// Elems
#include "Def_Elem.h"
/////////////////////
//#include "MI_GangC.h" 
//////////////////////
#include "RegenPat.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenPat,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenPat::CRegenPat()
{
}

CRegenPat::~CRegenPat()
{
}
	
int CRegenPat::UpdatePatches(CDrNode* pDrNode)
{
	POSITION pos;
	//////////////////////////////////
	int nCurCount,nPatCount;
	CDListMgr*	pCurList;
	CDListMgr*	pPatList;
	////////////////////////////////////// affected solidList
	int i,j,index;
	CDListMgr	affectList;
	///////////////////////
	affectList.RemoveAll();
	////////////////////////////////////////////////////////////////////// Update Dependent Patches
	//////////////////////////////////////////////// Patches due to Node
	pPatList	= pDrNode->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		////////////////
		if(pPatch)
		{
			index = affectList.GetObjectIndex(pPatch);
			if(index<0)	// not in there
				affectList.InsertObject(pPatch);

		}
	}
	//////////////////////////////////////////////// Patches due to Curve
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		pPatList	= pCurve->GetPatchList(); 
		nPatCount	= pPatList->GetCount();
		///////////
		for(j=0;j<nPatCount;j++)
		{
			pos					= pPatList->FindIndex(j);
			CDrPatch* pPatch	= (CDrPatch*)(pPatList->GetAt(pos));
			//////////////// not in list - insert
			if(pPatch)
			{
				index = affectList.GetObjectIndex(pPatch);
				if(index<0)	// not in there
					affectList.InsertObject(pPatch);
			}
		}
	}
	//////////////////////////////////////////////// Finally, Now Change
	nPatCount	= affectList.GetCount();
	for(i=0;i<nPatCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrPatch* pPatch	= (CDrPatch*)(affectList.GetAt(pos));
		////////////////
		if(pPatch)
		{
			pPatch->SetShow(FALSE);
			ReGen_EditedPatchControls(pPatch);
			pPatch->SetShow(TRUE);

		}
	}
	///////////////////////
	affectList.RemoveAll();
	///////////////////////
	//////////
	return 0;
}

int CRegenPat::ReGen_EditedPatchControls(CDrPatch* pEditedPatch)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	int nResult;
	//////////////////////////////////////////////////////////////////
	PATCHPROC PatchProc = pEditedPatch->GetPatchProc();	// How was it Generated?
	CString strID		= pEditedPatch->GetObjectID();
	/////
	nResult = SetUp_EditedPatchControls(pEditedPatch);
	if(nResult<0)
		return nResult;
	///////////////////
	switch(PatchProc) 
	{
		
		///////////////////////////////////////////////////// Patches Insert
		case PP_EXTRUDE:

			///////////////////
			nResult = ReGen_Controls_EXTRUDE(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_ROTATE: 

			///////////////////
			nResult = ReGen_Controls_ROTATE(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_LOFT2: 

			///////////////////
			nResult = ReGen_Controls_LOFT2(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_DUCT: 

			///////////////////
			nResult = ReGen_Controls_DUCT(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_SWEEP:

			///////////////////
			nResult = ReGen_Controls_SWEEP(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_COONS:
		case PP_LOFT3:		// COONS:		// 
		case PP_LOFT4:
			
			///////////////////
			nResult = ReGen_Controls_COONS(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_TENSOR:
		case PP_GORDON:		// GORDONS
		case PP_FLAT:
		case PP_SPAWN:		// Spawn
		case PP_STITCH:		// Stitch
		case PP_LOFTMANY:	
			return -1;

		//////////////////////////////////////////////////
		default:  
			break;
	}
	///////////
	return -1;
}	

int CRegenPat::SetUp_EditedPatchControls(CDrPatch* pEditedPatch)
{

	///////////////////////////////////////////////////
	pEditedPatch->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////// Get rid of Old CNodes & Delete 
	CDrObject* pObject;
	while(!(pEditedPatch->GetCNodeList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(pEditedPatch->GetCNodeList()->RemoveHead());
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
			pObject->ReadyToDelete();
		else
			delete pObject;	//delete:private	
	}	
	//////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_EXTRUDE(CDrPatch* pEditedPatch,CString* pID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList;
	CDrNode* pDrNode;
	CString NodeID;
	int index;
	//////////////////////////////////////////////////////////////// FromID & ToID
	pList		= pObjectMgr->GetObjectList(CNODE);
	//////////////////////////////////////////////////////////////// FromID
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList();
	pNodeList->RemoveAll();
	///
	NodeID					= pEditedPatch->GetFromID_T();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode					= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	NodeID					= pEditedPatch->GetToID_T();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode		= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	////////////////////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	LatchList.AddTail(pEditedPatch->GetCurveLatch(0));
	//////////
	int nMesh	= pEditedPatch->GetMaxOutSeg_T();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		dLen;
	WORLD		wLen;
	CMP_Xtrud	MP_Xtrud;
	int			nResult;
	/////////
	double	Ratio	= pEditedPatch->GetRatio_T();		
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	if(pEditedPatch->GetExtruType_T() == 2)
	{
		wLen	= pEditedPatch->GetWorldLength_T();
		////////////////////////////////////// World to Physical
		WORtoWOP(&wLen,&wLen);
		//////////////////////
		nResult = MP_Xtrud.SetInfoBase_Type2(*pID,pEditedPatch,pCurveList,&LatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
	}
	else
	{
		dLen	= pEditedPatch->GetLength_T();
		////////////////////////////////////// World to Physical
		WORtoWOP(&dLen,&dLen);
		//////////////////////
		nResult = MP_Xtrud.SetInfoBase(*pID,pEditedPatch,pCurveList,&LatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_ROTATE(CDrPatch* pEditedPatch,CString* pID)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList;
	CDrNode* pDrNode;
	CString NodeID;
	int index;
	//////////////////////////////////////////////////////////////// FromID & ToID
	pList		= pObjectMgr->GetObjectList(CNODE);
	//////////////////////////////////////////////////////////////// FromID
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList();
	pNodeList->RemoveAll();
	///
	NodeID					= pEditedPatch->GetFromID_T();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode					= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	NodeID					= pEditedPatch->GetToID_T();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode		= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	////////////////////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	LatchList.AddTail(pEditedPatch->GetCurveLatch(0));
	//////////
	int nMesh	= pEditedPatch->GetMaxOutSeg_T();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		dLen;
	WORLD		wLen;
	CMP_Rotat	MP_Rotat;
	int			nResult;
	/////////
	double	Ratio	= pEditedPatch->GetRatio_T();		
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
/*

	if(pEditedPatch->GetExtruType_T() == 2)
	{
		wLen	= pEditedPatch->GetWorldLength_T();
		////////////////////////////////////// World to Physical
		WORtoWOP(&wLen,&wLen);
		//////////////////////
		nResult = MP_Rotat.SetInfoBase_Type2(*pID,pEditedPatch,pCurveList,&LatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
	}
	else
	{
*/

		dLen	= pEditedPatch->GetAng_2_T();
		////////////////////////////////////// World to Physical
//		WORtoWOP(&dLen,&dLen);
		//////////////////////
		nResult = MP_Rotat.SetInfoBase(*pID,pEditedPatch,pCurveList,&LatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
/*
	}
*/
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_LOFT2(CDrPatch* pEditedPatch,CString* pID)
{
	CDListMgr* pCurveList = pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	LatchList.AddTail(pEditedPatch->GetCurveLatch(0));
	LatchList.AddTail(pEditedPatch->GetCurveLatch(1));
	//////////
	int nMesh	= pEditedPatch->GetMaxOutSeg_T();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		Ratio			= pEditedPatch->GetRatio_T();		
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Loft2	MP_Loft2;
	int nResult = MP_Loft2.SetInfoBase(*pID,pEditedPatch,pCurveList,&LatchList,
							&ElSegList,Ratio,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_DUCT(CDrPatch* pEditedPatch,CString* pID)
{
	//////////////////////////////////////////////////////////////////////////////
	// Currently(03/05/97):
	//		WE DONOT ALLOW DIFFERENT TWISTMULT, TWISTSTART, SCALEMULT, SCALESTART
	//						FOR DIFFERENT COMPONENTS in:X,Y AND Z
	//							USING VALUES FROM pPatchToIso
	//		SINCE WE PACK FORCES ETC. IN X,Y AND Z DIRECTIONS IN SINGLE PATCH
	//			WE CANNOT ALLOW ANY INPUT BUT TO USE pPatchToIso VALUES
	//		IN LATER VERSION:
	//			WE WILL USE wTwistMult (WORLD) variables for input
	//////////////////////////////////////////////////////////////////////////////
	int i,nResult;
	//////////////////////////////////////////////////////////////// Set up
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList(); 
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	///////////////////////////////////////////////////
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	////////////////////////
	for(i=0;i<3;i++)
		LatchList.AddTail(pEditedPatch->GetCurveLatch(i));
	//////////
	double		dTwistMult		= pEditedPatch->GetTwistMult_T();
	BOOL		bIncrement		= pEditedPatch->IsIncTwist_T();		
	double		dTwistStart		= pEditedPatch->GetTwistStart_T();		
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Duct	MP_Duct;
	nResult = MP_Duct.SetInfoBase(*pID,pEditedPatch,pCurveList,pNodeList,
							&LatchList,dTwistMult,bIncrement,dTwistStart,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_SWEEP(CDrPatch* pEditedPatch,CString* pID)
{
	//////////////////////////////////////////////////////////////////////////////
	// Currently(03/05/97):
	//		WE DONOT ALLOW DIFFERENT TWISTMULT, TWISTSTART, SCALEMULT, SCALESTART
	//						FOR DIFFERENT COMPONENTS in:X,Y AND Z
	//							USING VALUES FROM pPatchToIso
	//		SINCE WE PACK FORCES ETC. IN X,Y AND Z DIRECTIONS IN SINGLE PATCH
	//			WE CANNOT ALLOW ANY INPUT BUT TO USE pPatchToIso VALUES 
	//		IN LATER VERSION:
	//			WE WILL USE wTwistMult (WORLD) variables for input
	//////////////////////////////////////////////////////////////////////////////
	int i,nResult;
	//////////////////////////////////////////////////////////////// Set up
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList(); 
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList();
	///////////////////////////////////////////////////////
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	////////////////////////
	for(i=0;i<4;i++)
		LatchList.AddTail(pEditedPatch->GetCurveLatch(i));
	//////////
	double		dTwistMult		= pEditedPatch->GetTwistMult_T();
	BOOL		bIncrement		= pEditedPatch->IsIncTwist_T();		
	double		dTwistStart		= pEditedPatch->GetTwistStart_T();		
	double		dRadiusMult		= pEditedPatch->GetScaleMult_T();
	BOOL		bIncRad			= pEditedPatch->IsIncScale_T();		
	double		dRadStart		= pEditedPatch->GetScaleStart_T();		
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Sweep	MP_Sweep;
	nResult = MP_Sweep.SetInfoBase(*pID,pEditedPatch,pCurveList,pNodeList,
							&LatchList,dTwistMult,bIncrement,dTwistStart,
							dRadiusMult,bIncRad,dRadStart,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_COONS(CDrPatch* pEditedPatch,CString* pID)
{
	int i;
	//////////////////////////////////////////////////////////////// Set up
	PATCHPROC ppKind = pEditedPatch->GetPatchProc();
	//////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	//////////
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_LOFT3) && (i>2))
			continue;
		LatchList.AddTail(pEditedPatch->GetCurveLatch(i));
	}
	////////////////////////////////////////////////////
	CString		PatCurveID[4];
	CURVELATCH	PatCurveLatch[4];
	POSITION	pos;
	//////////////////////////////////////////////////// Fill Arrays
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_LOFT3) && (i>2))
			continue;
		//////////////////////////////////////////////////////////// ID
		CDrCurve* pDrCurve	= (CDrCurve*)(pCurveList->GetObject(i) );
		PatCurveID[i] = pDrCurve->GetObjectID();
		//////////////////////////////////////////////////////////// Latch
		pos					= LatchList.FindIndex(i);
		PatCurveLatch[i]	= LatchList.GetAt(pos);
		////////////////
	}
	////////////////////////// Triangular Patch
	if(ppKind == PP_LOFT3)
	{
		CMP_CooP3	MP_CoonP;
		/////////////////////
		int nResult = MP_CoonP.GoDoIt(*pID,pEditedPatch,PatCurveID,
										PatCurveLatch);
		//////////////
		if(nResult<0)
			return -1;
	}
	else
	////////////////////////// Quadrilateral Patch
	if(ppKind == PP_LOFT4)
	{	
		CMP_CoonP	MP_CoonP;
		/////////
		int nResult = MP_CoonP.GoDoIt(*pID,pEditedPatch,PatCurveID,
										PatCurveLatch);
		//////////////
		if(nResult<0)
			return -1;
	}
	//////////////////////////////////////////////////////////
	return 0;
}

void CRegenPat::Serialize(CArchive& ar)
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


