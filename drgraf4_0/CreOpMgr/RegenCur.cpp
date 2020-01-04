// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "Def_MouseAct.h"
///////////////////// IGens
#include "Def_IGen.h"
#include "DrProf_C.h"
///////////////////// Elems
#include "Def_Elem.h"
/////////////////////
#include "MI_GangC.h" 
#include "MC_Bezier.h" 
#include "MC_Parab.h" 
#include "MC_Circle.h" 
#include "MC_Lin.h"
#include "MC_Quad.h"
#include "MC_Cube.h"
#include "RegenProf_C.h" 
#include "MI_LSupp.h" 
#include "MI_StaL.h" 
//////////////////////
#include "RegenCur.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenCur,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenCur::CRegenCur()
{
}

CRegenCur::~CRegenCur()
{
}
	
int CRegenCur::UpdateCurves(CDrNode* pDrNode)
{
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////////////////// Update Dependent Curves
	CMI_StaL	MI_StaL;
	CMI_LSupp	MI_LSupp;
	CDrProf_C*	pProf_C;
	CDListMgr	CollectProfList;
	CDListMgr*	pCurList;
	CDListMgr*	pProfList;
	int i,j,nCurCount,nProfCount;
	POSITION pos;
	////////////////////////////
	CollectProfList.RemoveAll();
	//////////////////////////////////////////////// Curves
	pCurList	= pDrNode->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		////////////////
		if(pCurve)
		{
			//////////////////////////////////////
			pProfList	= pCurve->GetCProfList();
			nProfCount	= pProfList->GetCount();
			if(nProfCount>0)
			////////////////////////////////////// Curve belongs to a Profile
			{
				for(j=0;j<nProfCount;j++)
				{
					pos		= pProfList->FindIndex(j);
					pProf_C	= (CDrProf_C*)(pProfList->GetAt(pos));
					if(CollectProfList.GetObjectIndex(pProf_C)<0)
						CollectProfList.InsertObject(pProf_C);
				}
			}
			else
			{
			////////////////////////////////////// Regular Curve
				pObjectMgr->ShowObject_On_Off(pCurve,CURVE,FALSE);
				///////////////////////////////// Controls
				ReGen_EditedCurveControls(pCurve);
				///////////////////////////////// Elem Nodes
				if(!(pCurve->GetVNodeList()->IsEmpty()))
					ReGen_EditedCurveVNodeList(pCurve);
				///////////////////////////////// Support, if any
				if(!(pCurve->GetSuppList()->IsEmpty()))
					MI_LSupp.RegenCurveBased(pCurve);
				///////////////////////////////// Static Load, if any
				if(!(pCurve->GetStaLList()->IsEmpty()))
					MI_StaL.RegenCurveBased(pCurve);
				///////////////////////////////// Spectral Load, if any
				pObjectMgr->ShowObject_On_Off(pCurve,CURVE,TRUE);
			}
		}
	}
	//////////////////////////////////////////////// Profile Curves
	pProfList	= &CollectProfList;
	nProfCount	= pProfList->GetCount();
	//
	if(nProfCount<=0)
		return 0;
	////////////////////////////////////// Regenerate
	CRegenProf_C Regen;
	for(j=0;j<nProfCount;j++)
	{
		pos					= pProfList->FindIndex(j);
		CDrProf_C* pProf_C	= (CDrProf_C*)(pProfList->GetAt(pos));
		///////////////////////////////////////////////////////////
		CDListMgr*	pCurveList = pProf_C->GetCurveList();	// Curves making up Profile
		for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
			if(!pCurve)
			{
				AfxMessageBox("Internal Problem:\nCRegenCur::UpdateCurves\n!pCurve");
				return MA_ERROR;
			}
			////////////////////////////////////// Regular Curve
			pObjectMgr->ShowObject_On_Off(pCurve,CURVE,FALSE);
			///////////////////////////////// Controls
			ReGen_EditedCurveControls(pCurve);
			///////////////////////////////// Elem Nodes
			if(!(pCurve->GetVNodeList()->IsEmpty()))
				ReGen_EditedCurveVNodeList(pCurve);
			///////////////////////////////// Support, if any
			if(!(pCurve->GetSuppList()->IsEmpty()))
				MI_LSupp.RegenCurveBased(pCurve);
			///////////////////////////////// Static Load, if any
			if(!(pCurve->GetStaLList()->IsEmpty()))
				MI_StaL.RegenCurveBased(pCurve);
			///////////////////////////////// Spectral Load, if any
			pObjectMgr->ShowObject_On_Off(pCurve,CURVE,TRUE);
		}
		///////////////////////////////////////////
		Regen.ReGen_EditedProf_C_Controls(pProf_C);
		///////////////////////////
	}
	//////////
	return 0;
}

int CRegenCur::ReGen_EditedCurveControls(CDrCurve* pEditedCurve)
{

	//////////////////////////////////////////////////////////////////
	pEditedCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////// Get rid of Old CNodes & Delete 
	CDrObject* pObject;
	while(!(pEditedCurve->GetCNodeList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(pEditedCurve->GetCNodeList()->RemoveHead());
		int nLevelType = pObject->GetLevelType();
		if(nLevelType == LEVEL_GRAPA) //no delete:public
		// 01/12/98
		{
			CDListMgr* pList = pObject->GetCurveList();
			int index = pList->GetObjectIndex(pEditedCurve);
			if(index>=0)
			{
				POSITION pos = pList->FindIndex(index);
				pList->RemoveAt(pos);
			}
			pObject->ReadyToDelete();
		}
		// 01/12/98 end
		else
			delete pObject;	//delete:private	
	}
	/////////////////////////////////////////////////////////// do it
	KNOT KnTyp;
	///////////
	CMI_GangC	MI_GangC;
	CMC_Parab	McParab;
	CMC_Circle	McCircle;
	CMC_Lin		McLin;
	CMC_Quad	McQuad;
	CMC_Cube	McCube;
	CMC_Bezier	McBezier;
	////////////////
	CURVEPROC	SCurveType	= pEditedCurve->GetCurveType_S();
	CIRCLETYPE	CircType	= pEditedCurve->GetCircleType();
	BEZIERTYPE	BezierType	= pEditedCurve->GetBezierType();
	////////////////////////////////////////////////////////
	switch(SCurveType)
	{

		case CP_CIRCLE:
			/////////////////////////////////////////////////// Go Interpolate
			McCircle.GoDoIt(pEditedCurve,TRUE,CircType);	//TRUE=FINAL
			///
			break;
				
		case CP_PARABOLA:
			/////////////
			McParab.GoDoIt(pEditedCurve,TRUE);
			///
			break;
				
		case CP_LINEAR:
			/////////////
			McLin.GoDoIt(pEditedCurve,TRUE);
			///
			break;

		case CP_QUADRATIC:
			/////////////
			KnTyp  = pEditedCurve->GetKnotType_S();
		    pEditedCurve->SetKnotType_S(KN_USER);
			McQuad.GoDoIt(pEditedCurve,TRUE);
			pEditedCurve->SetKnotType_S(KnTyp);
			///
			break;

		case CP_BEZIER:
			/////////////
			if(BezierType == BEZIER_BY_TAN)
				MI_GangC.CreateBezCNsFromTanEnds_Cubic(pEditedCurve);
			else
			if(BezierType == BEZIER_BY_PTS)
				McBezier.GoDoIt(pEditedCurve,TRUE);
			///
			break;

		case CP_BSPLINE:
		case CP_NURB:
			/////////////
			McCube.GoDoIt(pEditedCurve,TRUE);
			///
			break;
		default:
			return -1;
	}
	//////////////////////////////////
	return 0;
}

int CRegenCur::ReGen_EditedCurveVNodeList(CDrCurve* pCurve)
{
	CMI_GangC	MI_GangC;
	CDListMgr* pVNodeList = pCurve->GetVNodeList();
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	int nOut		= pCurve->GetLongOutPts();
	BOOL bClosed	= pCurve->IsClosed_S();
	int nDegree		= pCurve->GetOrder_S() - 1;
	int nSegBZ		= pCurve->GetMaxBezSegments_S();
    CList<int,int>* pElperSegList = pCurve->GetElperSegList_S();		
	//////////////////////////////////////////// Now Generate
	pWORLD	pOut	= MI_GangC.FixMem(nOut);
	pDOUBLE pOutWts = MI_GangC.FixMemD(nOut);
	MI_GangC.SetbBack(FALSE);
	///
	MI_GangC.FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	//////////////////////////////////////////// Edit Nodes,Not Junction Nodes(Already Input)
	int k=-1,s,t,m=-1;
	POSITION pos;
	int nElems;
	//////////
	UINT nType = INODE;
	for (s = 0; s<nSegBZ; s++)
	{
		pos		= pElperSegList->FindIndex(s); 
		nElems	= pElperSegList->GetAt(pos); 
		///
		for(t=0;t<nElems;t++)
		{
			k++;
			if( t == 0)	// Junctions
				continue;
			//////////////////////////////////////////// Update Coords: Old Node
			m++;
			CDrNode* pNode = (CDrNode*)pVNodeList->GetObject(m);
			/////////////////////////////
			pNode->SetLocalPos(pOut[k]);
			(pNode->GetNodeCard())->x = (long)pOut[k].x;	
			(pNode->GetNodeCard())->y = (long)pOut[k].y;	
			(pNode->GetNodeCard())->z = (long)pOut[k].z;
			///////////////////////////////////////////// 
		}
	}	
	/////////////////////////////////////// Free Memory
	MI_GangC.FreeMem(pOut);
	MI_GangC.FreeMemD(pOutWts);
	//////////////
    return MA_OK;
}

void CRegenCur::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" RegenCur:    Storing\n");	
		

	}
	else
	{
		TRACE(" RegenCur:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


