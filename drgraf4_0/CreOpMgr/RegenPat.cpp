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
#include "Def_Elem.h"
#include "Def_MouseAct.h"
/////////////////////
#include "MI_StaL.h" 
#include "MI_LSupp.h" 
#include "MP_Xtrud.h"
#include "MP_Rotat.h"
//#include "MP_Loft2.h"
#include "MP_LoftX.h"
#include "MP_Gordon.h"
#include "MP_Tensor.h"
#include "MP_CooP4.h"
#include "MP_CooP3.h"
#include "MP_Duct.h"
#include "MP_Sweep.h"
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
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CMI_StaL	MI_StaL;
	CMI_LSupp	MI_LSupp;
	/////////////////////
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
			pObjectMgr->ShowObject_On_Off(pPatch,PATCH,FALSE);
			////////////////////////////////// Controls
			ReGen_EditedPatchControls(pPatch);
			///////////////////////////////// Support, if any
			if(!(pPatch->GetSuppList()->IsEmpty()))
			{
				if(pPatch->GetPatSubType() == PS_QUADRILAT)
					MI_LSupp.RegenPatchBased_4(pPatch);
				else
				if(pPatch->GetPatSubType() == PS_TRIANGLE)
					MI_LSupp.RegenPatchBased_3(pPatch);
			}
			///////////////////////////////// Static Load, if any
			if(!(pPatch->GetStaLList()->IsEmpty()))
			{
				if(pPatch->GetPatSubType() == PS_QUADRILAT)
					MI_StaL.RegenPatchBased_4(pPatch);
				else
				if(pPatch->GetPatSubType() == PS_TRIANGLE)
					MI_StaL.RegenPatchBased_3(pPatch);
			}
			///////////////////////////////// Spectral Load, if any
			pObjectMgr->ShowObject_On_Off(pPatch,PATCH,TRUE);

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

		case PP_LOFTX: 

			///////////////////
			nResult = ReGen_Controls_LOFTX(pEditedPatch,&strID);
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
		case PP_COONSTRI:		// COONS:		// 
		case PP_COONSQUAD:
			
			///////////////////
			nResult = ReGen_Controls_COONS(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_TENSOR:
			///////////////////
			nResult = ReGen_Controls_TENSOR(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_GORDON:		// GORDONS
			///////////////////
			nResult = ReGen_Controls_GORDON(pEditedPatch,&strID);
			if(nResult<0)
				return nResult;
			/////////
			return 0;

		case PP_FLAT:
		case PP_SPAWN:		// Spawn
		case PP_STITCH:		// Stitch
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
	//////////////////////////////////////////////////////////////// FromID & ToID
	pList		= pObjectMgr->GetObjectList(CNODE);
	//////////////////////////////////////////////////////////////// FromID
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList();
	pNodeList->RemoveAll();
	///
	pDrNode					= pEditedPatch->GetFromIDNode_T();
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	pDrNode					= pEditedPatch->GetToIDNode_T();
	pNodeList->InsertObject(pDrNode);
	////////////////////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	LatchList.AddTail(pEditedPatch->GetCurveLatch(0));
	//////////
	CList<int,int>	ElSegList_V;
	ElSegList_V.AddTail(pEditedPatch->GetElperSegList_T());
	//////////
	CMP_Xtrud	MP_Xtrud;
	int			nResult;
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	BOOL bGenBCurve	= pEditedPatch->IsGenBCurve();
	double	Ratio	= pEditedPatch->GetRatio_T();		
	double dLen		= pEditedPatch->GetLength_T();
	WORLD wLen		= pEditedPatch->GetWorldLength_T();
	/////////
	if(pEditedPatch->GetExtruType_T() == 2)
	{
		////////////////////////////////////// World to Physical
		WORtoWOP(&wLen,&wLen);
		//////////////////////
		nResult = MP_Xtrud.GoDoIt(bGenBCurve,2,*pID,pEditedPatch,pNodeList,pCurveList,&LatchList,
							ElSegList_V,wLen,dLen,Ratio,m_pView);
	}
	else
	{
		////////////////////////////////////// World to Physical
		WORtoWOP(&dLen,&dLen);
		//////////////////////
		nResult = MP_Xtrud.GoDoIt(bGenBCurve,1,*pID,pEditedPatch,pNodeList,pCurveList,&LatchList,
							ElSegList_V,wLen,dLen,Ratio,m_pView);
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
	//////////////////////////////////////////////////////////////// FromID & ToID
	pList		= pObjectMgr->GetObjectList(CNODE);
	//////////////////////////////////////////////////////////////// FromID
	CDListMgr* pNodeList	= pEditedPatch->GetINodeList();
	pNodeList->RemoveAll();
	///
	pDrNode					= pEditedPatch->GetFromIDNode_T();
	pNodeList->InsertObject(pDrNode);
	//////////////////////////////////////////////////////////////// ToID
	pDrNode					= pEditedPatch->GetToIDNode_T();
	pNodeList->InsertObject(pDrNode);
	////////////////////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	LatchList.AddTail(pEditedPatch->GetCurveLatch(0));
	//////////
	CList<int,int>	ElSegList_V;
	ElSegList_V.AddTail(pEditedPatch->GetElperSegList_T());
	//////////////////////////////////////////////////////////
	CMP_Rotat	MP_Rotat;
	int			nResult;
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	BOOL		bGenBCurve		= pEditedPatch->IsGenBCurve();
	double		dAngle_V		= pEditedPatch->GetAng_2_T();
	double		Ratio_V			= pEditedPatch->GetRatio_T();
	BOOL		bAxis			= pEditedPatch->IsAxisInput_T();
	int			nAxis			= pEditedPatch->GetAxisType_T();
	BOOL		bNegative		= pEditedPatch->IsNegative_T();
	//////////////////////
	nResult = MP_Rotat.GoDoIt(bGenBCurve,*pID,pEditedPatch,pNodeList,pCurveList,&LatchList,
							ElSegList_V,dAngle_V,Ratio_V,bAxis,nAxis,bNegative,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_LOFT2(CDrPatch* pEditedPatch,CString* pID)
{
	int nResult = MA_ERROR;
	///////////////////////
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
/*
	CMP_Loft2	MP_Loft2;
	int nResult = MP_Loft2.SetInfoBase(*pID,pEditedPatch,pCurveList,&LatchList,
							&ElSegList,Ratio,m_pView);
*/
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_LOFTX(CDrPatch* pEditedPatch,CString* pID)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////
//	CPatMouse PatMouse;
	int nResult;
	//////////////////////////////////////////////////////////////// Set up
	int nCurDir = pEditedPatch->GetPrimaryDir(); 
	/////////////////////////////////////////////////////
	CDListMgr CurveList;
	CurveList.RemoveAll();
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	CList<int,int>	ElSegList_V;
	ElSegList_V.RemoveAll();
	CList<BLENDEND,BLENDEND> EndList_V;	// if(bClosed_V or Linear_V,Circle_V,
													// parabola_V) EndList_V Empty
	////////////////////////////
	if(nCurDir == 1)
	{
		CurveList.AddTail(pEditedPatch->GetCurveList_U()); 
		LatchList.AddTail(pEditedPatch->GetCurveLatchList_U());
		ElSegList_V.AddTail(pEditedPatch->GetElperSegList_T());
		EndList_V.AddTail(pEditedPatch->GetEndList_V());
	}
	else
	if(nCurDir == 2)
	{
		CurveList.AddTail(pEditedPatch->GetCurveList_V()); 
		LatchList.AddTail(pEditedPatch->GetCurveLatchList_V());
		ElSegList_V.AddTail(pEditedPatch->GetElperSegList_S());
		EndList_V.AddTail(pEditedPatch->GetEndList_U());
	}
	else
	if(nCurDir == 3)
	{
		CurveList.AddTail(pEditedPatch->GetCurveList_W()); 
		LatchList.AddTail(pEditedPatch->GetCurveLatchList_W());
	}
	/////////////////////////////////////////////////////////////////////////// 
	CDrCurve*	pBlendCurve_U	= pEditedPatch->GetBlendCurve_U(); 
	CDrCurve*	pBlendCurve_V	= pEditedPatch->GetBlendCurve_V(); 
	//////////////////////////////////////////////////////////
	BOOL		bGenBCurve		= pEditedPatch->IsGenBCurve();
	//////////
	CDListMgr	NodeList;
	int			nNodes_U,nNodes_V;		
	//////
//	nResult = PatMouse.CreateDataNodeList(&NodeList,&CurveList,&LatchList,nNodes_U,nNodes_V);
	nResult = pWnd->GetMouseMgr()->GetDLDMouse()->
			CreateDataNodeList(&NodeList,&CurveList,&LatchList,nNodes_U,nNodes_V);
	//////////////////////////////////////////////////////////
	double		Ratio			= pEditedPatch->GetRatio_T();
	BOOL		bAdvanced		= FALSE;	// tangents/twist BC			For Now
	PWMAT2		pCornerTwist;// it is full,if TW_USER
	TWIST		TwistMethod = TW_AUTO;
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_LoftX	MP_LoftX;
	nResult = MP_LoftX.GoDoIt(	bGenBCurve,FALSE,pBlendCurve_U,bAdvanced,pCornerTwist,TwistMethod,
									nCurDir,
									*pID,pEditedPatch,nNodes_U,nNodes_V,&NodeList,
									&CurveList,&LatchList,ElSegList_V,pBlendCurve_V,
									Ratio,&EndList_V,m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_GORDON(CDrPatch* pEditedPatch,CString* pID)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////
//	CPatMouse PatMouse;
	int nResult;
	//////////////////////////////////////////////////////////////// Set up
	int nCurDir = pEditedPatch->GetPrimaryDir(); 
	/////////////////////////////////////////////////////
	CDListMgr CurveList_U,CurveList_V;
	CurveList_U.AddTail(pEditedPatch->GetCurveList_U()); 
	CurveList_V.AddTail(pEditedPatch->GetCurveList_V()); 
	////
	/////////////////////////////////////////////////////
	CList<CURVELATCH,CURVELATCH> LatchList_U,LatchList_V;
	LatchList_U.AddTail(pEditedPatch->GetCurveLatchList_U());
	LatchList_V.AddTail(pEditedPatch->GetCurveLatchList_V());
	///////// 
	CDrCurve*	pBlendCurve_U	= pEditedPatch->GetBlendCurve_U(); 
	CDrCurve*	pBlendCurve_V	= pEditedPatch->GetBlendCurve_V(); 
	///////// 
	CList<int,int>	ElSegList_U,ElSegList_V;
	ElSegList_U.AddTail(pEditedPatch->GetElperSegList_S());
	ElSegList_V.AddTail(pEditedPatch->GetElperSegList_T());
	//////////////////////////////////////////////////////////
	CDListMgr	NodeList;
	int	nNodes_U,nNodes_V;
	//////
//	nResult = PatMouse.CreateDataNodeList(&NodeList,&CurveList,&LatchList,nNodes_U,nNodes_V);
	nResult = pWnd->GetMouseMgr()->GetDLDMouse()->
			CreateDataNodeList(&NodeList,&CurveList_U,&LatchList_U,nNodes_U,nNodes_V);
	//////////////////////////////////////////////////////////
	double		Ratio_U			= pEditedPatch->GetRatio_S();
	double		Ratio_V			= pEditedPatch->GetRatio_T();
	///////////////////////////////////
	CList<BLENDEND,BLENDEND> EndList_U,EndList_V;	// if(bClosed_V or Linear_V,Circle_V,
													// parabola_V) EndList_V Empty
											// parabola_V) EndList_V Empty
	BOOL bAdvancedEnd			= pEditedPatch->IsAdvancedEnd_V();
//	if(bAdvancedEnd)
//	{
		EndList_U.AddTail(pEditedPatch->GetEndList_U());
		EndList_V.AddTail(pEditedPatch->GetEndList_V());
//	}
	////
	TWIST TwistMethod	= pEditedPatch->GetTwistMethod_V(); 
	PWMAT2 pCornerTwist = NULL;// it is full,if TW_USER
	if(TwistMethod == TW_USER)
		pCornerTwist	= pEditedPatch->GetCornerTwist_V();// it is full,if TW_USER
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Gordon	MP_Gordon;
	nResult = MP_Gordon.GoDoIt(	bAdvancedEnd,*pID,pEditedPatch,&NodeList,pCornerTwist,TwistMethod,
					nNodes_U,&CurveList_U,&LatchList_U,ElSegList_U,Ratio_U,pBlendCurve_U,&EndList_U,
					nNodes_V,&CurveList_V,&LatchList_V,ElSegList_V,Ratio_V,pBlendCurve_V,&EndList_V,
					m_pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////////
	return 0;
}

int CRegenPat::ReGen_Controls_TENSOR(CDrPatch* pEditedPatch,CString* pID)
{
	int nResult;
	//////////////////////////////////////////////////////////////// Set up
	int nCurDir = pEditedPatch->GetPrimaryDir(); 
	/////////////////////////////////////////////////////
	BOOL		bGenBCurve		= pEditedPatch->IsGenBCurve();
	///////// 
	CDrCurve*	pBlendCurve_U	= pEditedPatch->GetBlendCurve_U(); 
	CDrCurve*	pBlendCurve_V	= pEditedPatch->GetBlendCurve_V(); 
	///////// 
	CList<int,int>	ElSegList_U,ElSegList_V;
	ElSegList_U.AddTail(pEditedPatch->GetElperSegList_S());
	ElSegList_V.AddTail(pEditedPatch->GetElperSegList_T());
	//////////////////////////////////////////////////////////
	CDListMgr	NodeList;
	NodeList.AddTail(pEditedPatch->GetINodeList());
	int	nNodes_U,nNodes_V;
	nNodes_U					= pEditedPatch->GetNodes_S();
	nNodes_V					= pEditedPatch->GetNodes_T();
	//////////////////////////////////////////////////////////
	double		Ratio_U			= pEditedPatch->GetRatio_S();
	double		Ratio_V			= pEditedPatch->GetRatio_T();
	///////////////////////////////////
	CList<BLENDEND,BLENDEND>EndList_U,EndList_V;	// if(bClosed_V or Linear_V,Circle_V,
													// parabola_V) EndList_V Empty
	BOOL bAdvancedEnd			= pEditedPatch->IsAdvancedEnd_V();
//	if(bAdvancedEnd)
//	{
		EndList_U.AddTail(pEditedPatch->GetEndList_U());
		EndList_V.AddTail(pEditedPatch->GetEndList_V());
//	}
	////
	TWIST TwistMethod	= pEditedPatch->GetTwistMethod_V(); 
	PWMAT2 pCornerTwist = NULL;// it is full,if TW_USER
	if(TwistMethod == TW_USER)
		pCornerTwist	= pEditedPatch->GetCornerTwist_V();// it is full,if TW_USER
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Tensor	MP_Tensor;
	nResult = MP_Tensor.GoDoIt(bGenBCurve,bAdvancedEnd,*pID,pEditedPatch,&NodeList,pCornerTwist,TwistMethod,
					nNodes_U,ElSegList_U,Ratio_U,pBlendCurve_U,&EndList_U,
					nNodes_V,ElSegList_V,Ratio_V,pBlendCurve_V,&EndList_V,
					m_pView);
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
	CList<double,double>*
				pTwistList		= pEditedPatch->GetTwistList_T();
	BOOL		bGenBCurve		= pEditedPatch->IsGenBCurve();
	int			nTwistType		= pEditedPatch->GetTwistType_T();
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Duct	MP_Duct;
	nResult = MP_Duct.GoDoIt(bGenBCurve,nTwistType,*pID,pEditedPatch,pNodeList,pCurveList,
							&LatchList,pTwistList,dTwistMult,bIncrement,dTwistStart,m_pView);
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
	BOOL		bGenBCurve		= pEditedPatch->IsGenBCurve();
	////
	int			nTwistType		= pEditedPatch->GetTwistType_T();
	double		dTwistMult		= pEditedPatch->GetTwistMult_T();
	BOOL		bIncrement		= pEditedPatch->IsIncTwist_T();		
	double		dTwistStart		= pEditedPatch->GetTwistStart_T();
	CList<double,double>*
				pTwistList		= pEditedPatch->GetTwistList_T();
	///
	int			nScaleType		= pEditedPatch->GetScaleType_T();
	double		dScaleMult		= pEditedPatch->GetScaleMult_T();
	BOOL		bIncScale		= pEditedPatch->IsIncScale_T();		
	double		dScaleStart		= pEditedPatch->GetScaleStart_T();		
	CList<double,double>*
				pScaleList		= pEditedPatch->GetScaleList_T();
	////////////////////////////////////////////////////////////////////////// Fill Info/Do It
	CMP_Sweep	MP_Sweep;
	nResult = MP_Sweep.GoDoIt(bGenBCurve,nTwistType,nScaleType,*pID,pEditedPatch,pNodeList,pCurveList,
							&LatchList,
							pTwistList,dTwistMult,bIncrement,dTwistStart,
							pScaleList,dScaleMult,bIncScale,dScaleStart,m_pView);
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
	BOOL bGenBCurve	 = pEditedPatch->IsGenBCurve();
	//////////////////////////////////////////////////
	CDListMgr* pCurveList	= pEditedPatch->GetCurveList(); 
	//////////////////////////////////////////////////////////////// Set up
	CList<CURVELATCH,CURVELATCH>	LatchList;
	LatchList.RemoveAll();
	//////////
	for(i=0;i<4;i++)
	{
		if((ppKind == PP_COONSTRI) && (i>2))
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
		if((ppKind == PP_COONSTRI) && (i>2))
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
	if(ppKind == PP_COONSTRI)
	{
		CMP_CooP3	MP_CoonP;
		/////////////////////
		int nResult = MP_CoonP.GoDoIt(bGenBCurve,*pID,pEditedPatch,pCurveList,
										&LatchList);
		//////////////
		if(nResult<0)
			return -1;
	}
	else
	////////////////////////// Quadrilateral Patch
	if(ppKind == PP_COONSQUAD)
	{	
		CMP_CooP4	MP_CoonP;
		/////////
		int nResult = MP_CoonP.GoDoIt(bGenBCurve,*pID,pEditedPatch,pCurveList,
										&LatchList);
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
		TRACE(" RegenPat:    Storing\n");	
		

	}
	else
	{
		TRACE(" RegenPat:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


