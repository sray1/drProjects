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
#include "MS_Xtrud.h"
#include "MS_Xtru3.h"
#include "MS_Rotat.h"
#include "MS_Rota3.h"
#include "MS_Lof42.h"
#include "MS_Lof32.h"
//#include "MS_CoonP.h"
//#include "MS_CooP3.h"
#include "MS_Duct.h"
#include "MS_Duc3.h"
#include "MS_Sweep.h"
#include "MS_Swee3.h"
///////////////////// Elems
#include "Def_Elem.h"
//////////////////////
#include "RegenSol.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenSol,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenSol::CRegenSol()
{
}

CRegenSol::~CRegenSol()
{
}
	
int CRegenSol::UpdateSolids(CDrNode* pDrNode)
{
	POSITION pos;
	//////////////////////////////////
	int nCurCount,nPatCount,nSolCount;
	CDListMgr*	pCurList;
	CDListMgr*	pPatList;
	CDListMgr*	pSolList;
	////////////////////////////////////// affected solidList
	int i,j,k,index;
	CDListMgr	affectList;
	///////////////////////
	affectList.RemoveAll();
	////////////////////////////////////////////////////////////////////// Update Dependent Solids
	//////////////////////////////////////////////// Solids due to Node
	pSolList	= pDrNode->GetSolidList(); 
	nSolCount	= pSolList->GetCount();
	///////////
	for(i=0;i<nSolCount;i++)
	{
		pos					= pSolList->FindIndex(i);
		CDrSolid* pSolid	= (CDrSolid*)(pSolList->GetAt(pos));
		////////////////
		if(pSolid)
		{
			index = affectList.GetObjectIndex(pSolid);
			if(index<0)	// not in there
				affectList.InsertObject(pSolid);

		}
	}
	//////////////////////////////////////////////// Solids due to Curves of Node
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		pSolList	= pCurve->GetSolidList(); 
		nSolCount	= pSolList->GetCount();
		///////////
		for(j=0;j<nSolCount;j++)
		{
			pos					= pSolList->FindIndex(j);
			CDrSolid* pSolid	= (CDrSolid*)(pSolList->GetAt(pos));
			//////////////// not in list - insert
			if(pSolid)
			{
				index = affectList.GetObjectIndex(pSolid);
				if(index<0)	// not in there
					affectList.InsertObject(pSolid);
			}
		}
	}
	//////////////////////////////////////////////// Solids due to Patches of Node
	pPatList	= pDrNode->GetPatchList(); 
	nPatCount	= pPatList->GetCount();
	///////////
	for(i=0;i<nPatCount;i++)
	{
		pos					= pPatList->FindIndex(i);
		CDrPatch* pPatch	= (CDrPatch*)(pPatList->GetAt(pos));
		////////////////
		pSolList	= pPatch->GetSolidList(); 
		nSolCount	= pSolList->GetCount();
		///////////
		for(j=0;j<nSolCount;j++)
		{
			pos					= pSolList->FindIndex(j);
			CDrSolid* pSolid	= (CDrSolid*)(pSolList->GetAt(pos));
			//////////////// not in list - insert
			if(pSolid)
			{
				index = affectList.GetObjectIndex(pSolid);
				if(index<0)	// not in there
					affectList.InsertObject(pSolid);
			}
		}
	}
	//////////////////////////////////////////////// Solids due to Patches of Curves
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
			//////////////////////////////////
			if(pPatch)
			{
				pSolList	= pPatch->GetSolidList(); 
				nSolCount	= pSolList->GetCount();
				///////////
				for(k=0;k<nSolCount;k++)
				{
					pos					= pSolList->FindIndex(k);
					CDrSolid* pSolid	= (CDrSolid*)(pSolList->GetAt(pos));
					//////////////// not in list - insert
					if(pSolid)
					{
						index = affectList.GetObjectIndex(pSolid);
						if(index<0)	// not in there
							affectList.InsertObject(pSolid);
					}
				}
			}
		}
	}
	//////////////////////////////////////////////// Finally, Now Change
	nSolCount	= affectList.GetCount();
	for(i=0;i<nSolCount;i++)
	{
		pos					= affectList.FindIndex(i);
		CDrSolid* pSolid	= (CDrSolid*)(affectList.GetAt(pos));
		////////////////
		if(pSolid)
		{
			pSolid->SetShow(FALSE);
			ReGen_EditedSolidControls(pSolid);
			pSolid->SetShow(TRUE);

		}
	}
	///////////////////////
	affectList.RemoveAll();
	///////////////////////
	//////////
	return 0;
}

int CRegenSol::ReGen_EditedSolidControls(CDrSolid* pEditedSolid)
{                          

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString strCurr;
	int nResult;
	//////////////////////////////////////////////////////////////////
	SOLIDPROC SolidProc = pEditedSolid->GetSolidProc();	// How was it Generated?
	CString strID		= pEditedSolid->GetObjectID();
	/////
	nResult = SetUp_EditedSolidControls(pEditedSolid);
	if(nResult<0)
		return nResult;
	///////////////////
	switch(SolidProc) 
	{
		
		///////////////////////////////////////////////////// Patches Insert
		case SP_EXTRUDE:

			///////////////////
			nResult = ReGen_Controls_EXTRUDE(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_ROTATE: 

			///////////////////
			nResult = ReGen_Controls_ROTATE(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_LOFT2: 

			///////////////////
			nResult = ReGen_Controls_LOFT2(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_DUCT: 

			///////////////////
			nResult = ReGen_Controls_DUCT(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_SWEEP:

			///////////////////
			nResult = ReGen_Controls_SWEEP(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_COONS:
		case SP_LOFT3:		// COONS:		// 
		case SP_LOFT4:
			
			///////////////////
			nResult = ReGen_Controls_COONS(pEditedSolid,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case SP_TENSOR:
		case SP_GORDON:		// GORDONS
		case SP_SPAWN:		// Spawn
		case SP_STITCH:		// Stitch
		case SP_LOFTMANY:	
			return -1;

		//////////////////////////////////////////////////
		default:  
			break;
	}
	///////////
	return -1;
}	

int CRegenSol::SetUp_EditedSolidControls(CDrSolid* pEditedSolid)
{

	///////////////////////////////////////////////////
	pEditedSolid->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////// Get rid of Old CNodes & Delete 
	CDrObject* pObject;
	while(!(pEditedSolid->GetCNodeList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(pEditedSolid->GetCNodeList()->RemoveHead());
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
			pObject->ReadyToDelete();
		else
			delete pObject;	//delete:private	
	}	
	//////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_EXTRUDE(CDrSolid* pEditedSolid,CString* pID)
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
	CDListMgr* pNodeList	= pEditedSolid->GetINodeList();
	pNodeList->RemoveAll();
	///
	NodeID					= pEditedSolid->GetFromID_R();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode					= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	NodeID					= pEditedSolid->GetToID_R();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode		= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// Set up
	CList<PATCHLATCH,PATCHLATCH>	PLatchList;
	PLatchList.RemoveAll();
//	LatchList.AddTail(pEditedSolid->GetCurveLatch(0));
	//////////
	int nMesh	= pEditedSolid->GetMaxOutSeg_R();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		dLen;
	WORLD		wLen;
	int			nResult;
	/////////
	double	Ratio		= pEditedSolid->GetRatio_R();
	/////////////////////////////////////////////
	CDListMgr* pPatchList	= pEditedSolid->GetPatchList();
	CDrPatch* pPatch		= (CDrPatch*)pPatchList->GetObject(0);
/*
	CString PatchID			= pEditedSolid->GetPatchID(0);
	index 					= pObjectMgr->GetObjectIndexfromKey(PATCH,PatchID,1);
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pPatch		= (CDrPatch*)(pDListMgr->GetObject(index));
	CDListMgr PatchList;
	PatchList.RemoveAll();
	PatchList.InsertObject(pPatch);
*/
	PATSUBTYPE PatSubType	= pPatch->GetPatSubType();
	////////////////////////// Triangular Patch
	if(PatSubType == PS_TRIANGLE)
	{
		CMS_Xtru3	MS_Xtrud;
		////////////////////////////////////////////////////////////////////////// Fill Info/Do It
		if(pEditedSolid->GetExtruType_R() == 2)
		{
			wLen	= pEditedSolid->GetWorldLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&wLen,&wLen);
			//////////////////////
			nResult = MS_Xtrud.SetInfoBase_Type2(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
		}
		else
		{
			dLen	= pEditedSolid->GetLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&dLen,&dLen);
			//////////////////////
			nResult = MS_Xtrud.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
		}
		//////////////
	}
	else
	////////////////////////// Quadrilateral Patch
	if(PatSubType == PS_QUADRILAT)
	{	
		CMS_Xtrud	MS_Xtrud;
		////////////////////////////////////////////////////////////////////////// Fill Info/Do It
		if(pEditedSolid->GetExtruType_R() == 2)
		{
			wLen	= pEditedSolid->GetWorldLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&wLen,&wLen);
			//////////////////////
			nResult = MS_Xtrud.SetInfoBase_Type2(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
		}
		else
		{
			dLen	= pEditedSolid->GetLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&dLen,&dLen);
			//////////////////////
			nResult = MS_Xtrud.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
		}
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_ROTATE(CDrSolid* pEditedSolid,CString* pID)
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
	CDListMgr* pNodeList	= pEditedSolid->GetINodeList();
	pNodeList->RemoveAll();
	///
	NodeID					= pEditedSolid->GetFromID_R();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode					= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	NodeID					= pEditedSolid->GetToID_R();
	index					= pList->GetObjectIndex(NODE, NodeID);
	pDrNode		= (CDrNode*)(pList->GetObject(index) );
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// Set up
	CList<PATCHLATCH,PATCHLATCH>	PLatchList;
	PLatchList.RemoveAll();
//	LatchList.AddTail(pEditedSolid->GetCurveLatch(0));
	//////////
	int nMesh	= pEditedSolid->GetMaxOutSeg_R();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		dLen;
	WORLD		wLen;
	int			nResult;
	/////////
	double	Ratio			= pEditedSolid->GetRatio_R();
	/////////////////////////////////////////////
	CDListMgr* pPatchList	= pEditedSolid->GetPatchList();
	CDrPatch* pPatch		= (CDrPatch*)pPatchList->GetObject(0);
	PATSUBTYPE PatSubType	= pPatch->GetPatSubType();
	////////////////////////// Triangular Patch
	if(PatSubType == PS_TRIANGLE)
	{
		CMS_Rota3	MS_Rotat;
		////////////////////////////////////////////////////////////////////////// Fill Info/Do It
/*
		if(pEditedSolid->GetExtruType_R() == 2)
		{
			wLen	= pEditedSolid->GetWorldLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&wLen,&wLen);
			//////////////////////
			nResult = MS_Xtrud.SetInfoBase_Type2(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
		}
		else
		{
*/
			dLen	= pEditedSolid->GetAng_2_R();	// Angle
			//////////////////////
			nResult = MS_Rotat.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
/*
		}
		//////////////
*/
	}
	else
	////////////////////////// Quadrilateral Patch
	if(PatSubType == PS_QUADRILAT)
	{	
		CMS_Rotat	MS_Rotat;
		////////////////////////////////////////////////////////////////////////// Fill Info/Do It
/*
		if(pEditedSolid->GetExtruType_R() == 2)
		{
			wLen	= pEditedSolid->GetWorldLength_R();
			////////////////////////////////////// World to Physical
			WORtoWOP(&wLen,&wLen);
			//////////////////////
			nResult = MS_Rotat.SetInfoBase_Type2(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,wLen,Ratio,m_pView);
		}
		else
		{
*/
			dLen	= pEditedSolid->GetAng_2_R();	// Angle
			//////////////////////
			nResult = MS_Rotat.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							pNodeList,&ElSegList,dLen,Ratio,m_pView);
/*
		}
*/
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_LOFT2(CDrSolid* pEditedSolid,CString* pID)
{
	CDListMgr* pPatchList = pEditedSolid->GetPatchList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<PATCHLATCH,PATCHLATCH>	PLatchList;
	PLatchList.RemoveAll();
//	PLatchList.AddTail(pEditedSolid->GetCurveLatch(0));
//	PLatchList.AddTail(pEditedSolid->GetCurveLatch(1));
	//////////
	int nResult;
	int nMesh	= pEditedSolid->GetMaxOutSeg_R();	// Number of Output Segments
	CList<int,int>	ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(nMesh);
	//////////
	double		Ratio			= pEditedSolid->GetRatio_R();		
	/////////////////////////////////////////////
	CDrPatch* pPatch		= (CDrPatch*)pPatchList->GetObject(0);
	PATSUBTYPE PatSubType	= pPatch->GetPatSubType();
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	////////////////////////// Triangular Patch
	if(PatSubType == PS_TRIANGLE)
	{
		CMS_Lof32	MS_Loft2;
		/////////////////////
		nResult = MS_Loft2.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							&ElSegList,Ratio,m_pView);
	}
	else
	////////////////////////// Quadrilateral Patch
	if(PatSubType == PS_QUADRILAT)
	{	
		CMS_Lof42	MS_Loft2;
		/////////////////////
		nResult = MS_Loft2.SetInfoBase(*pID,pEditedSolid,pPatchList,&PLatchList,
							&ElSegList,Ratio,m_pView);
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_DUCT(CDrSolid* pEditedSolid,CString* pID)
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
	CDListMgr* pNodeList	= pEditedSolid->GetINodeList(); 
	CDListMgr* pCurveList	= pEditedSolid->GetCurveList(); 
	CDListMgr* pPatchList	= pEditedSolid->GetPatchList(); 
	///////////////////////////////////////////////////
	CList<CURVELATCH,CURVELATCH>	CLatchList;
	CLatchList.RemoveAll();
	for(i=0;i<3;i++)
		CLatchList.AddTail(pEditedSolid->GetCurveLatch(i));
	///////////////
	CList<PATCHLATCH,PATCHLATCH>	PLatchList;
	PLatchList.RemoveAll();
	//////////
	double		dTwistMult		= pEditedSolid->GetTwistMult_R();
	BOOL		bIncrement		= pEditedSolid->IsIncTwist_R();		
	double		dTwistStart		= pEditedSolid->GetTwistStart_R();		
	/////////////////////////////////////////////
	CDrPatch* pPatch			= (CDrPatch*)pPatchList->GetObject(0);
	PATSUBTYPE PatSubType		= pPatch->GetPatSubType();
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	////////////////////////// Triangular Patch
	if(PatSubType == PS_TRIANGLE)
	{
		CMS_Duc3	MS_Duct;
		/////////////////////
		nResult = MS_Duct.SetInfoBase(*pID,pEditedSolid,pPatchList,pCurveList,pNodeList,
							&PLatchList,&CLatchList,dTwistMult,bIncrement,dTwistStart,m_pView);
		//////////////
	}
	else
	////////////////////////// Quadrilateral Patch
	if(PatSubType == PS_QUADRILAT)
	{	
		CMS_Duct	MS_Duct;
		/////////////////////
		nResult = MS_Duct.SetInfoBase(*pID,pEditedSolid,pPatchList,pCurveList,pNodeList,
							&PLatchList,&CLatchList,dTwistMult,bIncrement,dTwistStart,m_pView);
		//////////////
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_SWEEP(CDrSolid* pEditedSolid,CString* pID)
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
	CDListMgr* pNodeList	= pEditedSolid->GetINodeList(); 
	CDListMgr* pCurveList	= pEditedSolid->GetCurveList();
	CDListMgr* pPatchList	= pEditedSolid->GetPatchList();
	///////////////////////////////////////////////////////
	CList<CURVELATCH,CURVELATCH>	CLatchList;
	CLatchList.RemoveAll();
	for(i=0;i<4;i++)
		CLatchList.AddTail(pEditedSolid->GetCurveLatch(i));
	///////////////////////////////////////////////////////
	CList<PATCHLATCH,PATCHLATCH>	PLatchList;
	PLatchList.RemoveAll();
	//////////
	double		dTwistMult		= pEditedSolid->GetTwistMult_R();
	BOOL		bIncrement		= pEditedSolid->IsIncTwist_R();		
	double		dTwistStart		= pEditedSolid->GetTwistStart_R();		
	double		dRadiusMult		= pEditedSolid->GetScaleMult_R();
	BOOL		bIncRad			= pEditedSolid->IsIncScale_R();		
	double		dRadStart		= pEditedSolid->GetScaleStart_R();		
	/////////////////////////////////////////////
	CDrPatch* pPatch			= (CDrPatch*)pPatchList->GetObject(0);
	PATSUBTYPE PatSubType		= pPatch->GetPatSubType();
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	////////////////////////// Triangular Patch
	if(PatSubType == PS_TRIANGLE)
	{
		CMS_Swee3 MS_Sweep;
		/////////////////////
		nResult = MS_Sweep.SetInfoBase(*pID,pEditedSolid,pPatchList,pCurveList,pNodeList,
							&PLatchList,&CLatchList,dTwistMult,bIncrement,dTwistStart,
							dRadiusMult,bIncRad,dRadStart,m_pView);
		//////////////
	}
	else
	if(PatSubType == PS_QUADRILAT)
	{
		CMS_Sweep MS_Sweep;
		/////////////////////
		nResult = MS_Sweep.SetInfoBase(*pID,pEditedSolid,pPatchList,pCurveList,pNodeList,
							&PLatchList,&CLatchList,dTwistMult,bIncrement,dTwistStart,
							dRadiusMult,bIncRad,dRadStart,m_pView);
		//////////////
	}
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenSol::ReGen_Controls_COONS(CDrSolid* pEditedSolid,CString* pID)
{
/*
	int i;
	//////////////////////////////////////////////////////////////// Set up
	PATCHPROC ppKind = pEditedSolid->GetPatchProc();
	//////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedSolid->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	//////////
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_LOFT3) && (i>2))
			continue;
		LatchList.AddTail(pEditedSolid->GetCurveLatch(i));
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
		int nResult = MP_CoonP.GoDoIt(*pID,pEditedSolid,PatCurveID,
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
		int nResult = MP_CoonP.GoDoIt(*pID,pEditedSolid,PatCurveID,
										PatCurveLatch);
		//////////////
		if(nResult<0)
			return -1;
	}
	//////////////////////////////////////////////////////////
	return 0;
*/
	return -1;
}

void CRegenSol::Serialize(CArchive& ar)
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


