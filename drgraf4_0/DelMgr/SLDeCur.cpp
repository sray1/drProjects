// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
//////////////////////
#include "MSTLMgr.h" 
//////////////////////
#include "SLDeCur.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDeCur,CSLDeNod,1)
/////////////////////////////////////////////////////////////////////////////
CSLDeCur::CSLDeCur()
{

	m_bAdvanceOn	= FALSE;
	/////////////////////////////////////////// Static
	m_bTan			= FALSE;
	m_bIso			= FALSE;
	/////////////////////// NonIso
	m_bNonIso		= FALSE;
	m_cid_ParentT	= "";
	m_cid_ParentR	= "";
	m_bIncrement	= FALSE;
	m_Orient		= "FORWARD";
	m_dScale		= 0.0;
	m_dStep			= 0.0;
	m_dStart		= 0.0;
	////////////////////////////////

}

CSLDeCur::~CSLDeCur()
{
}

void CSLDeCur::GetObjectInfo(CSLEObj* pObject)
{
	
	CSLENod::GetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDeCur* pAdd = (CSLDeCur*) pObject;
	////////////////////////////////////////////////////////////////////// Curve
	pAdd->m_bAdvanceOn			= m_bAdvanceOn;	
	/////////////////////////////////////
	if(!(m_NodeList.IsEmpty()) )
		pAdd->m_NodeList.AddTail(&m_NodeList ); 
	if(!(m_ElSegList.IsEmpty()) )
		pAdd->m_ElSegList.AddTail(&m_ElSegList ); 
	////////////////////////////
	pAdd->m_pSNodeT				= m_pSNodeT;
	pAdd->m_pSNodeR				= m_pSNodeR;
	////////////////////////////////////////////////////////////////// Curve
	if(!(m_NodeListT.IsEmpty()) )
		pAdd->m_NodeListT.AddTail(&m_NodeListT ); 
	if(!(m_NodeListR.IsEmpty()) )
		pAdd->m_NodeListR.AddTail(&m_NodeListR ); 
	/////////////////////////////////////////// Static
	for(int i=0;i<4;i++)
	{
		pAdd->m_pCurrentSCurveT[i]		= m_pCurrentSCurveT[i];	// Iso or NonIso curve
		pAdd->m_pCurrentSCurveR[i]		= m_pCurrentSCurveR[i];	// Iso or NonIso curve
	}
	/////////////////////////////////////////// Circle
	pAdd->m_CircType			= m_CircType;
	pAdd->m_nMesh				= m_nMesh;
	pAdd->m_SegAngle			= m_SegAngle;
	pAdd->m_bAutoSeg			= m_bAutoSeg;
	pAdd->m_dAngSpec			= m_dAngSpec;
	pAdd->m_bArc				= m_bArc;
	pAdd->m_dAng				= m_dAng;	
	pAdd->m_FromID				= m_FromID;
	pAdd->m_ToID				= m_ToID;	
	pAdd->m_TIID				= m_TIID;
	pAdd->m_CCID				= m_CCID;	
	pAdd->m_CAID				= m_CAID;
	pAdd->m_CBID				= m_CBID;	
	pAdd->m_NodeType			= m_NodeType;	// NODE or CNODE
	pAdd->m_dRadius				= m_dRadius;
}

void CSLDeCur::SetObjectInfo(CSLEObj* pObject)
{
	
	CSLENod::SetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDeCur* pAdd = (CSLDeCur*) pObject;
	////////////////////////////////////////////////////////////////////// Node
	m_pCurrentNode			= pAdd->m_pCurrentNode;
	m_bAdvanceOn			= pAdd->m_bAdvanceOn;	
	/////////////////////////////////////
	if(!(pAdd->m_NodeList.IsEmpty()) )
		m_NodeList.AddTail(&(pAdd->m_NodeList) ); 
	if(!(pAdd->m_ElSegList.IsEmpty()) )
		m_ElSegList.AddTail(&(pAdd->m_ElSegList) ); 
	////////////////////////////
	m_pSNodeT				= pAdd->m_pSNodeT;
	m_pSNodeR				= pAdd->m_pSNodeR;
	////////////////////////////////////////////////////////////////// Curve
	if(!(pAdd->m_NodeListT.IsEmpty()) )
		m_NodeListT.AddTail(&(pAdd->m_NodeListT) ); 
	if(!(pAdd->m_NodeListR.IsEmpty()) )
		m_NodeListR.AddTail(&(pAdd->m_NodeListR) ); 
	/////////////////////////////////////////// Static
	for(int i=0;i<4;i++)
	{
		m_pCurrentSCurveT[i]		= pAdd->m_pCurrentSCurveT[i];	// Iso or NonIso curve
		m_pCurrentSCurveR[i]		= pAdd->m_pCurrentSCurveR[i];	// Iso or NonIso curve
	}
	/////////////////////////////////////////// Circle
	m_CircType			= pAdd->m_CircType;
	m_nMesh				= pAdd->m_nMesh;
	m_SegAngle			= pAdd->m_SegAngle;
	m_bAutoSeg			= pAdd->m_bAutoSeg;
	m_dAngSpec			= pAdd->m_dAngSpec;
	m_bArc				= pAdd->m_bArc;
	m_dAng				= pAdd->m_dAng;	
	m_FromID			= pAdd->m_FromID;
	m_ToID				= pAdd->m_ToID;	
	m_TIID				= pAdd->m_TIID;
	m_CCID				= pAdd->m_CCID;	
	m_CAID				= pAdd->m_CAID;
	m_CBID				= pAdd->m_CBID;	
	m_NodeType			= pAdd->m_NodeType;	// NODE or CNODE
	m_dRadius			= pAdd->m_dRadius;
}


int CSLDeCur::Get_Values_Iso_Node(CDrNode* pNodeIsoTo, STALPROC StaLProc,CString& CurrentID)
{
	m_pSNodeT = NULL;
	m_pSNodeR = NULL;
	/////////////////////////////////////////////////////////////////////////
	WORLD	NodeT,NodeR;
	CString	Nid,StNID;
	////////////////////////////////////////////
	Nid		= pNodeIsoTo->GetObjectID();
	StNID	= Nid;
	/////////////////////////////////////// GetValues
	int nResult = Get_Values_ManyDirections(Nid,StaLProc);
	///////////////////////////////////////
	if(nResult<0)
		return nResult; 
	/////////////////////////////////////// LocalPos for Node as Forces/Moments
	NodeT.x	= m_dTx;
	NodeT.y	= m_dTy;
	NodeT.z	= m_dTz;
	NodeR.x	= m_dRx;
	NodeR.y	= m_dRy;
	NodeR.z	= m_dRz;
	/////////////////////////////////////// Create Nodes Using GangN
	int			nNodeIndex = -12345;	//create Anyway (ALWAYS)
	int			nLabelIndex= 0;
	CMI_GangN	GangN;
	////////////////////////////
	if(m_bTx||m_bTy||m_bTz)
	{
		StNID += ("_T_" + CurrentID); 
		m_pSNodeT = GangN.CreateNode(StNID,m_pCurrentLabel, NodeT, TRUE,FALSE,FALSE,
									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	}
	if(m_bRx||m_bRy||m_bRz)
	{
		StNID += ("_R_" + CurrentID); 
		m_pSNodeR = GangN.CreateNode(StNID,m_pCurrentLabel, NodeR, TRUE,FALSE,FALSE,
									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
	}
	///////////////////////////////////////////////////////// OverRide Category & ID 
	CATEGORY	cat;
	///////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:		cat		= CA_FORCE;		break;
		case STL_DISPLACE:	cat		= CA_DISPLACE;	break;
		case STL_PRESSURE:	cat		= CA_PRESSURE;	break;
		case STL_THERMAL:	cat		= CA_THERMAL;	break;
		case STL_LUMPWT:	cat		= CA_LUMPWT;	break;
		default:break;
	}
	/////////////////////////////////////// Reciprocate :todo
	if(m_pSNodeT)
	{
		m_pSNodeT->SetCategory(cat);
		m_pSNodeT->SetSubCat(SC_TRAN);
		///////////////////////////////////// ID
		(m_pSNodeT->GetNodeCard())->id = StNID;
	}
	if(m_pSNodeR)
	{
		m_pSNodeR->SetCategory(cat);
		m_pSNodeR->SetSubCat(SC_ROT);
		///////////////////////////////////// ID
		(m_pSNodeR->GetNodeCard())->id = StNID;
	}
	/////////////
	return 0;
}

int CSLDeCur::ShowCurveStaticLoad(CDrCurve* pCurrentCurve,CString* pID,int nHowMany)
{
	///////////////////////////////////////////////////////////////////////
//	 nHowmany			// Used as an afterthought for Updating Support anyway
						// in CMI_LSupp.CreateCurveLinSup
						// even if same coords Curve exists already !!!
						// when nAnyway == -12345
						// Use nHowmany of ShowCurve to pass the variable
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(STATICLOAD);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_StaL	Static;
	CDrStatic*	pCurrentStaL;
	STALCARD	stLCard;
	/////////////////////////
	if(m_bIso || m_bNonIso)
	{
		/////////////////////////
		m_cid_Iso		= pCurrentCurve->GetObjectID();	// this staLcard IsoParametric(Non-Iso) to this Curve
		/////////
		if(m_bTx ||m_bTy ||m_bTz )
			m_cid_ParentT	= m_pCurrentSCurveT[0]->GetObjectID();	// this staLcard part of this Curve of Category CA_FORCE
																// this is m_CID in Iso-Generated Curve
																// this is m_CID in NonIso Input
		if(m_bRx ||m_bRy ||m_bRz )
			m_cid_ParentR	= m_pCurrentSCurveR[0]->GetObjectID();	// this staLcard part of this Curve of Category CA_FORCE
																// this is m_CID in Iso-Generated Curve
																// this is m_CID in NonIso Input
		/////////////////////////
		FillStLCard(stLCard,pID);
		//////////////
		pCurrentStaL = Static.CreateCurveBased(m_StaLProc,stLCard,pCurrentCurve,
								TRUE,m_pCurrentSCurveT[0],m_pCurrentSCurveR[0],CURVE);	// TRUE = NonUniform
	}
	else
	{
		m_cid_Iso		= "";
		m_cid_ParentT	= "";
		m_cid_ParentR	= "";
		/////////////////////////
		FillStLCard(stLCard,pID);
		//////////////
		pCurrentStaL = Static.CreateCurveBased(m_StaLProc,stLCard,pCurrentCurve,
								FALSE,(CDrCurve*)NULL,(CDrCurve*)NULL,CURVE);	// FALSE = Uniform
	}
	////////////////////////////////////////////////////////////////////// Show
	int nActiveIndex = pObjectMgr->GetActiveObjectIndex();	// Get Active Index									
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	pObjectMgr->SetActiveObjectType(STATICLOAD);		    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,STATICLOAD);
	///////////////////////////////
	return 0;
}	 

int CSLDeCur::Get_Values_Iso_Cur(CDrCurve* pCurveIsoTo, STALPROC StaLProc, int IndexSkipNode,
																	BOOL bLastCurve)
{
	// IndexSkipNode = -1; generally except for Triangular/QuadPatch Curves
	/////////////////////////////////////////////////////////////////////////
	CDListMgr* pINodeList = pCurveIsoTo->GetINodeList();
	CURVEPROC SCurveType = pCurveIsoTo->GetCurveType_S();
	/////////////////////////////////////////////////////
	int i;
	POSITION	pos;
	CDrNode*	pNode;
	CString		Nid,StNID;
	int			nNodes = pINodeList->GetCount();
	//////////////////////////////////////////// Last Curve other Node Index
	int			LastCurveOtherIndex = -1;
	if(bLastCurve)
	{
		if(IndexSkipNode>0)
			LastCurveOtherIndex = 0;
		else
		if(IndexSkipNode == 0)
			LastCurveOtherIndex = nNodes-1;;
	}
	////////////////////////////////////////////
	if(!m_NodeListT.IsEmpty())
		m_NodeListT.RemoveAll();
	if(!m_NodeListR.IsEmpty())
		m_NodeListR.RemoveAll();
	///////////////////////////////////////////////////////// LOOP: Curve Nodes
	for(i=0;i<nNodes;i++)
	{
		if(i == IndexSkipNode)
		{
			/////////////////////////////////////// Save in the NodeList: Last One
			if(m_pSNodeT)
				m_NodeListT.AddTail(m_pSNodeT);
			if(m_pSNodeR)
				m_NodeListR.AddTail(m_pSNodeR);
			////////////////////////////
			continue;
		}
		if(i == LastCurveOtherIndex)
		{
			////////////////////////////////////////////// Get Ist Curves
			CDrCurve* pIstSCurveT  = m_pCurrentSCurveT[0];
			CDrCurve* pIstSCurveR  = m_pCurrentSCurveR[0];
			//////////////////////////////////////
			CDrNode* pSNodeT = NULL;
			CDrNode* pSNodeR = NULL;
			////////////////
			if(pIstSCurveT)
				pSNodeT = (CDrNode*)(pIstSCurveT->GetINodeList()->GetHead()); 
			if(pIstSCurveR)
				pSNodeR = (CDrNode*)(pIstSCurveR->GetINodeList()->GetHead()); 
			/////////////////////////////////////// Save in the NodeList: Last One
			if(pSNodeT)
				m_NodeListT.AddTail(pSNodeT);
			if(pSNodeR)
				m_NodeListR.AddTail(pSNodeR);
			////////////////////////////
			continue;
		}
		///////
		pos		= pINodeList->FindIndex( i );
		pNode	= (CDrNode*)(pINodeList->GetAt(pos));
		//////////////////////////////
		switch(SCurveType)
		{
			case CP_LINEAR:
			case CP_QUADRATIC:
			case CP_BEZIER:
			case CP_BSPLINE:
			case CP_NURB:
				///////////////////////// CntlStat
				/////////////////////////
				break;

			case CP_CIRCLE:	
			//////////////////////////////
				switch(m_CircType)
				{
					case CIRCLE_BY_NO3:
						break;
					case CIRCLE_BY_ROT:
						break;
					case CIRCLE_BY_2N_TI:
					case CIRCLE_BY_2N_CC:
						break;
					case CIRCLE_BY_2CN_TI_R:
					default:
						break;
				}
		}
		/////////////////////////////////////////
		CString strID = pCurveIsoTo->GetObjectID();
		strID += "_NC";
		int nResult = Get_Values_Iso_Node(pNode, StaLProc,strID);
		if(nResult<0)
			return nResult;
		/////////////////////////////////////// Save in the NodeList
		if(m_pSNodeT)
			m_NodeListT.AddTail(m_pSNodeT);
		if(m_pSNodeR)
			m_NodeListR.AddTail(m_pSNodeR);
		////////////////////////////
	}
	//////////////
	return 0;
}
			
void CSLDeCur::RemoveMostListsFromCurve(CDrCurve* pAdd)
{
	//m_ElperSegList donot remove	 
	/////////////////////////////////////// RemoveList
	if(!(pAdd->GetLabelList()->IsEmpty())	)
		pAdd->GetLabelList()->RemoveAll(); 
	if(!(pAdd->GetSolidList()->IsEmpty())	)
		pAdd->GetSolidList()->RemoveAll(); 
	if(!(pAdd->GetENodeList()->IsEmpty())	)
		pAdd->GetENodeList()->RemoveAll(); 
	if(!(pAdd->GetINodeList()->IsEmpty())	)
		pAdd->GetINodeList()->RemoveAll(); 
	if(!(pAdd->GetCNodeList()->IsEmpty())	)
		pAdd->GetCNodeList()->RemoveAll(); 
	if(!(pAdd->GetCN_BSList()->IsEmpty())	)
		pAdd->GetCN_BSList()->RemoveAll(); 
	if(!(pAdd->GetNodeList()->IsEmpty())	)
		pAdd->GetNodeList()->RemoveAll(); 
	if(!(pAdd->GetElemList()->IsEmpty())	)
		pAdd->GetElemList()->RemoveAll();
	if(!(pAdd->GetPatchList()->IsEmpty())	)
		pAdd->GetPatchList()->RemoveAll(); 
	if(!(pAdd->GetObj3DList()->IsEmpty())	)
		pAdd->GetObj3DList()->RemoveAll(); 
	if(!(pAdd->GetCProfList()->IsEmpty())	)
		pAdd->GetCProfList()->RemoveAll(); 
	//////////////////////////////////////
	return;
}

int CSLDeCur::Generate_IsoCurveControls(CDrCurve* pCurveIsoTo,int indexC,CString* pID,BOOL bTran)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int			nActiveIndex;
	//////////////////////////////////////////////////////////////////
	CDrCurve* pCurrentSCurve; 
	////////////////////////////////////////////////////////////////// Save ObjectType/Index
//	UINT nTypeOld			= pObjectMgr->GetActiveObjectType();
// 	int nActiveIndexOld		= pObjectMgr->GetActiveObjectIndex();    // for Calling Object
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////// Add to DataBase, if not Existing
	///////////////////////////////////////// delete, if Same Category & Add
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, *pID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		pCurrentSCurve = (CDrCurve*)NULL;
	}
	pCurrentSCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(*pID,nActiveIndex,CURVE));
	pCurrentSCurve->SetShow(FALSE);	// not quite ready
	///////////////////////////////////////////////////////// SetIso Tag
	pCurrentSCurve->SetIso(TRUE);	
	///////////////////////////////////////////////////////// OverRide Category 
	CATEGORY	cat;
	///////////////////
	switch(m_StaLProc)
	{
		case STL_FORCE:		cat		= CA_FORCE;		break;
		case STL_DISPLACE:	cat		= CA_DISPLACE;	break;
		case STL_PRESSURE:	cat		= CA_PRESSURE;	break;
		case STL_THERMAL:	cat		= CA_THERMAL;	break;
		case STL_LUMPWT:	cat		= CA_LUMPWT;	break;
		default:break;
	}
	////////////////////////////////
	pCurrentSCurve->SetCategory(cat);
	if(bTran)
	{
		pCurrentSCurve->SetSubCat(SC_TRAN);
	}
	else
	{
		pCurrentSCurve->SetSubCat(SC_ROT);
	}
	//////////////////////////////////////////////////////////////////////// Clone
	pCurrentSCurve->SetObjectInfo(pCurveIsoTo);
	/////////////////////////////
	pCurrentSCurve->SetShow(FALSE);	// not to show might have been changed by Clone
	pCurrentSCurve->SetIso(TRUE);
	CString id;
	id = pCurveIsoTo->GetObjectID(); 
	pCurrentSCurve->SetIsoToID(id);
	////////////////////////////////// Reset ID
	CString strID;
	strID = *pID + "_" + id;
	pCurrentSCurve->SetObjectID(strID);
	//////////////
	RemoveMostListsFromCurve(pCurrentSCurve);				// except ElperSegList
	/////////////////////////////////////////////////////// Copy ElperSegList
	m_ElSegList.RemoveAll();
	m_ElSegList.AddTail(pCurrentSCurve->GetElperSegList());
	(pCurrentSCurve->GetElperSegList())->RemoveAll();		// now Remove, later stored in GangC
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	CDListMgr* pINodeList = pCurrentSCurve->GetINodeList();
	m_NodeList.RemoveAll();
	if(bTran)
	{
		m_NodeList.AddTail(&m_NodeListT);	// copy Translational
	}
	else
	{
		m_NodeList.AddTail(&m_NodeListR);	// copy Rotational
	}
	pINodeList->AddTail(&m_NodeList);	
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CDrNode*	pAddNode;
	POSITION	pos;
	///////////////////////////
	CURVEPROC SCurveType = pCurrentSCurve->GetCurveType_S();
	////////////////////////////////////////////////////////
	switch(SCurveType)
	{
		case CP_CIRCLE:

			m_SegAngle		= pCurrentSCurve->GetSegAngle_S(); 
			///////////////////////////////////////
			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:

					m_dAng			= pCurrentSCurve->GetTheta_S();
					//////////////////////////////////////////// FromID & ToID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_FromID	= pAddNode->GetObjectID();
					pINodeList->RemoveAt(pos);
					//////////
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					m_ToID		= pAddNode->GetObjectID();
					pINodeList->RemoveTail();
					////////////////////////////////////
					pCurrentSCurve = GangC.CreateCircleByRot(
						*pID,pCurrentSCurve,&m_NodeList,SCurveType,
						&m_ElSegList,CIRCLE_BY_ROT,m_dAng,m_FromID,m_ToID,m_SegAngle);

					break;

					
				case CIRCLE_BY_NO3:

					m_dAngSpec		= pCurrentSCurve->GetTheta_S();
					m_bArc			= pCurrentSCurve->IsArcType();
					//////////////////////////////////////////////				
					pCurrentSCurve = GangC.CreateCircleBy3Node(
						*pID,pCurrentSCurve,&m_NodeList,SCurveType,
						&m_ElSegList,CIRCLE_BY_NO3,m_SegAngle,m_dAngSpec,m_bArc);

					break;

					
				case CIRCLE_BY_2N_TI:
		
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					////////////////////////////////////
					pCurrentSCurve = GangC.CreateCircleBy_2N_TI(
						*pID,pCurrentSCurve,&m_NodeList,SCurveType,
						&m_ElSegList,CIRCLE_BY_2N_TI,m_SegAngle);

					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_CCID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					////////////////////////////////////
					pCurrentSCurve = GangC.CreateCircleBy_2N_CC(
						*pID,pCurrentSCurve,&m_NodeList,SCurveType,
						&m_ElSegList,CIRCLE_BY_2N_CC,m_SegAngle);

					break;

					
				case CIRCLE_BY_2CN_TI_R:

					m_dRadius	= pCurrentSCurve->GetRadius_S();
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
//					pINodeList->RemoveAt(pos);
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					m_CAID		= pAddNode->GetObjectID();
//					pINodeList->RemoveHead();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					m_CBID		= pAddNode->GetObjectID();
//					pINodeList->RemoveTail();
					////////////////////////////////////
					pCurrentSCurve = GangC.CreateCircleBy_2CN_TI_R(
						*pID,pCurrentSCurve,&m_NodeList,SCurveType,
						&m_ElSegList,CIRCLE_BY_2CN_TI_R,m_dRadius,m_SegAngle);

					break;
				
				default:

					break;

			}
			break;
				
		default:
			
			m_bAdvanceOn = FALSE; // because cloned  data already obtained
			/////////////////////
			pCurrentSCurve = GangC.CreateCurve(*pID,pCurrentSCurve,&m_NodeList,SCurveType,
											&m_ElSegList,m_bAdvanceOn,TRUE);// TRUE = Final
	}
////////////////////////////////////////////////////////////////////// Debug
#ifdef _DEBUG 
/*
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		int j;
		/////////////////////////
		j  = sprintf(buf,"CCurMouse::ShowCurve\nAfter CreateCurve\nBefore UpdateViews:\n");
		j += sprintf(buf+j,"Nodes in the CNodeList:\n\t");
		//////////////////////////////
		pList = m_pCurrentCurve->GetCNodeList();
		////////////////////////////////////////
		for (POSITION posI = pList->GetHeadPosition( );posI !=NULL;)
		{
			////
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(posI);
			j += sprintf(buf+j,"%s, ",pNode->GetObjectID());
		}
		sprintf( buf + j-2, ";");
		/////////////////////////	
		AfxMessageBox(*str);
		/////
		delete str;
*/
#endif
/////////////////////////////////////////////////////////////////// Debug End
	/////////////////////////////////////// Override Knot Type
//	pCurrentSCurve->SetKnotType_S(KN_UNIFORM);
	if(bTran)
	{
		m_pCurrentSCurveT[indexC] = pCurrentSCurve;
	}
	else
	{
		m_pCurrentSCurveR[indexC] = pCurrentSCurve;
	}
	//////////////////////////////////
	return 0;
}

int CSLDeCur::Get_Values_NonIso_Cur(STALPROC StaLProc)
{
	AfxMessageBox("Get_Values_NonIso_Cur\nNOT IMPLEMENTED YET");
	return -1;
}

int CSLDeCur::ShowInfo_CurveStaticLoad(CDrCurve* pDrCurve, char* buf, int jStart,CString& CurrentStLID)
{
	int j = jStart;
	///////////////
	CDListMgr* pList;
	///////////////////////////////////////////////////////////// Support Info
	pList = pDrCurve->GetStaLList();
	////////////////////////////////////////////////////////////////////////
	int i;
	CDrStatic*	pDrStatic;
	STALCARD	stLCard;
	POSITION	pos;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		pos			= pList->FindIndex(i);
		pDrStatic	= (CDrStatic*)pList->GetAt(pos);
		////
		if(pDrStatic)
			stLCard = *(pDrStatic->GetStaLCard());					
		else
		{
			AfxMessageBox("Internal ERROR:\nCSLDeCur::FillInfo_CurveStaticLoad\npDrLinSup=NULL"); 
			return -2;
		}
		/////////////////////////////////////////
		if(stLCard.load_id != CurrentStLID)
			continue;
		////////////////////////////////////////////////////// Same LID
		CString		Cid;
		Cid = pDrCurve->GetObjectID();
		/////////////////////////////////////////
		switch (stLCard.StaLProc)
		{
			case STL_FORCE:
			case STL_DISPLACE:	// fall thro'
				j	= FillInfo_6(Cid, stLCard, buf, j);	
				break;
			case STL_PRESSURE:
			case STL_THERMAL:
			case STL_LUMPWT:	// fall thro'
				j	= FillInfo_3(Cid, stLCard, buf, j);	
				break;
			default:
				break;
		}
	}
	//////////
	return j;
}

void CSLDeCur::Serialize(CArchive& ar)
{

	CSLDeNod::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDeCur:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDeCur:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


