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
/////////////////////
#include "MI_GangC.h" 
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
	////////////////////////////////////////////////////////////////////// Update Dependent Curves
	CDListMgr* pCurList;
	int i,nCurCount;
//	int i,j,index,nCurCount,nNodCount;
	POSITION pos;
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
			pCurve->SetShow(FALSE);
/*

			//////////////////////////////////////////////////////////////////////
			//	NOTE:	ReGen_EditedCurveControls calls CreateCurve which when
			//			calls SaveCurveDataBase stores pCurve in DrNode 
			//			Duplicating it everytime in DrNode->CurveList.
			//			So, REMOVE pCurve from DrNode
			//////////////////////////////////////////////////////////////////////
			pNodList	= pCurve->GetINodeList(); 
			nNodCount	= pNodList->GetCount();
			///
			for(j=0;j<nNodCount;j++)
			{
				pos					= pNodList->FindIndex(j);
				CDrNode* pNode		= (CDrNode*)(pNodList->GetAt(pos));
				///
				index				= (pNode->GetCurveList())->GetObjectIndex(pCurve);
				pos					= (pNode->GetCurveList())->FindIndex(index);
				(pNode->GetCurveList())->RemoveAt(pos);
			}
*/
			/////////////////////////////////
			ReGen_EditedCurveControls(pCurve);
			/////////////////////////////////
			pCurve->SetShow(TRUE);

		}
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
	/////////////////////////////////////////////////////// Copy ElperSegList
	CDListMgr	NodeList;
	CList<int,int> ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(pEditedCurve->GetElperSegList());
	(pEditedCurve->GetElperSegList())->RemoveAll();		// now Remove, later stored in GangC
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	CDListMgr* pINodeList = pEditedCurve->GetINodeList();
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CDrNode*	pAddNode;
	POSITION	pos;
	///////////////////////////////////////////// Curve Info
	double		SegAngle,dAng,dAngSpec,dRadius;
	BOOL		bArc,bAdvanceOn;
	CString		FromID,ToID,TIID,CCID,CAID,CBID;
	////////////////////////////////////////////////////////
	CString		ID			= pEditedCurve->GetObjectID();
	CURVEPROC	SCurveType	= pEditedCurve->GetCurveType_S();
	CIRCLETYPE	CircType	= pEditedCurve->GetCircleType();
	////////////////////////////////////////////////////////
	switch(SCurveType)
	{
		case CP_CIRCLE:

			SegAngle		= pEditedCurve->GetSegAngle_S(); 
			///////////////////////////////////////
			switch(CircType)
			{
				
				case CIRCLE_BY_ROT:

					dAng		= pEditedCurve->GetTheta_S();
					//////////////////////////////////////////// FromID & ToID
					FromID		= pEditedCurve->GetFromID_S();
					ToID		= pEditedCurve->GetToID_S();
					////////////////////////////////////
					pEditedCurve = GangC.CreateCircleByRot(
						ID,pEditedCurve,&NodeList,SCurveType,
						&ElSegList,CIRCLE_BY_ROT,dAng,FromID,ToID,SegAngle,TRUE);

					break;

					
				case CIRCLE_BY_NO3:

					dAngSpec		= pEditedCurve->GetTheta_S();
					bArc			= pEditedCurve->IsArcType();
					//////////////////////////////////////////////				
					pEditedCurve = GangC.CreateCircleBy3Node(
						ID,pEditedCurve,&NodeList,SCurveType,
						&ElSegList,CIRCLE_BY_NO3,SegAngle,dAngSpec,bArc,TRUE);

					break;

					
				case CIRCLE_BY_2N_TI:
		
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					TIID		= pAddNode->GetObjectID();
					////////////////////////////////////
					pEditedCurve = GangC.CreateCircleBy_2N_TI(
						ID,pEditedCurve,&NodeList,SCurveType,
						&ElSegList,CIRCLE_BY_2N_TI,SegAngle,TRUE);

					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					CCID		= pAddNode->GetObjectID();
					////////////////////////////////////
					pEditedCurve = GangC.CreateCircleBy_2N_CC(
						ID,pEditedCurve,&NodeList,SCurveType,
						&ElSegList,CIRCLE_BY_2N_CC,SegAngle,TRUE);

					break;

					
				case CIRCLE_BY_2CN_TI_R:

					dRadius		= pEditedCurve->GetRadius_S();
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					TIID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					CAID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					CBID		= pAddNode->GetObjectID();
					////////////////////////////////////
					pEditedCurve = GangC.CreateCircleBy_2CN_TI_R(
						ID,pEditedCurve,&NodeList,SCurveType,
						&ElSegList,CIRCLE_BY_2CN_TI_R,dRadius,SegAngle,TRUE);

					break;
				
				default:

					break;

			}
			break;
				
		default:
			
			bAdvanceOn = FALSE; // because data already Known
			/////////////////////
			pEditedCurve = GangC.CreateCurve(ID,pEditedCurve,&NodeList,SCurveType,
											&ElSegList,bAdvanceOn,TRUE);// TRUE = Final
	}
	//////////////////////////////////
	return 0;
}

void CRegenCur::Serialize(CArchive& ar)
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


