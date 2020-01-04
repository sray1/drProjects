// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
/////////////////////
#include "MI_GangC.h" 
#include "MC_Circle.h" 
#include "MC_Parab.h" 
#include "MI_CProf.h" 
//////////////////////
#include "MSTLMgr.h" 
//////////////////////
#include "SLDCur.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDCur,CSLDNod,1)
/////////////////////////////////////////////////////////////////////////////
CSLDCur::CSLDCur()
{

	m_bAdvanceOn	= FALSE;
	/////////////////////////////////////////// Static
	m_bTanCur		= FALSE;
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

CSLDCur::~CSLDCur()
{
}

void CSLDCur::GetObjectInfo(CSLDObj* pObject)
{
	
	CSLDNod::GetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDCur* pAdd = (CSLDCur*) pObject;
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

void CSLDCur::SetObjectInfo(CSLDObj* pObject)
{
	
	CSLDNod::SetObjectInfo(pObject);
	///////////////////////////////////   
	CSLDCur* pAdd = (CSLDCur*) pObject;
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


int CSLDCur::Get_Values_Iso_Node(CDrNode* pNodeIsoTo, STALPROC StaLProc,CString& CurrentID)
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
//092798		m_pSNodeT = GangN.CreateNode(StNID,m_pCurrentLabel, NodeT, TRUE,FALSE,FALSE,
//092798									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
		m_pSNodeT = GangN.CreateNode(StNID,m_pCurrentLabel, NodeT, TRUE,FALSE,
							nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
		m_pSNodeT->SetShow(FALSE);
	}
	if(m_bRx||m_bRy||m_bRz)
	{
		StNID += ("_R_" + CurrentID); 
//092798		m_pSNodeR = GangN.CreateNode(StNID,m_pCurrentLabel, NodeR, TRUE,FALSE,FALSE,
//092798									nNodeIndex,nLabelIndex);// FALSE=Input/TRUE=InternallyGen
		m_pSNodeR = GangN.CreateNode(StNID,m_pCurrentLabel, NodeR, TRUE,FALSE,
							nNodeIndex,nLabelIndex,LEVEL_GRAPA);// FALSE=Input/TRUE=InternallyGen
		m_pSNodeR->SetShow(FALSE);
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

int CSLDCur::ShowCurveStaticLoad(CDrCurve* pCurrentCurve,CString* pID)
{
	int nResult = MA_OK;
	////////////////////
	m_nNodPos_S_Beg = 0;		// index of Output NodPos in s direction:Begin
	m_nNodPos_S_End = pCurrentCurve->GetLongOutPts(); // does not recognize "Curve may be Closed!"
								// index of Output NodPos in s direction:End
	if(pCurrentCurve->IsClosed_S())
		m_nNodPos_S_End--;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	pObjectMgr->SetActiveObjectType(STATICLOAD);                   
	/////////////////////////////////////////////////////////////// Using GangSup
	CMI_StaL	MI_StaL;
	STALCARD	stLCard;
	/////////////////////////
	m_cid_Iso		= "";
	m_cid_ParentT	= "";
	m_cid_ParentR	= "";
	m_bUniform		= TRUE;
	/////////////////////////
	if(m_bIso || m_bNonIso)
	{
		m_bUniform = FALSE;
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
	}
	/////////////////////////
	FillStLCard(stLCard,pID);
	//////////////
	CList<STALCARD,STALCARD> TempList;
	TempList.RemoveAll();
	TempList.AddTail(stLCard);
	///
	nResult = MI_StaL.CreateCurveBased(pCurrentCurve,&TempList);
	///
	stLCard = TempList.GetTail(); 
	pCurrentCurve->GetStaLCardList()->AddTail(stLCard);
	////////////////////////////////////////////////////////////////////// Show
	pObjectMgr->ShowObject_On_Off(pCurrentCurve,CURVE,TRUE);
/*
	CDListMgr* pStaLList = pCurrentCurve->GetStaLList(); 
	for (POSITION posI = pStaLList->GetFirstObjectPos( );posI !=NULL;)
	{
		CDrStatic* pStatic = (CDrStatic*)pStaLList->GetNext(posI);
		pObjectMgr->ShowObject_On_Off(pStatic,STATICLOAD,TRUE);
	}
*/
	///////////////////////////////
	return 0;
}	 

int CSLDCur::Get_Values_Iso_Cur(CDrCurve* pCurveIsoTo, STALPROC StaLProc, int IndexSkipNode,
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
			
void CSLDCur::RemoveMostListsFromCurve(CDrCurve* pAdd)
{
	//m_ElperSegList donot remove	 
	/////////////////////////////////////// RemoveList
	if(!(pAdd->GetLabelList()->IsEmpty())	)
		pAdd->GetLabelList()->RemoveAll(); 
	if(!(pAdd->GetSolidList()->IsEmpty())	)
		pAdd->GetSolidList()->RemoveAll(); 
	if(!(pAdd->GetVNodeList()->IsEmpty())	)
		pAdd->GetVNodeList()->RemoveAll(); 
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

int CSLDCur::Generate_IsoCurveControls(CDrCurve* pCurveIsoTo,int indexC,CString* pID,BOOL bTran)
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
	////////////////////////////////////////////////////////////
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
	m_ElSegList.AddTail(pCurrentSCurve->GetElperSegList_S());
	(pCurrentSCurve->GetElperSegList_S())->RemoveAll();		// now Remove, later stored in GangC
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
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	CDrNode*	pAddNode;
	CDrNode*	pAddFromNode;
	CDrNode*	pAddToNode;
	POSITION	pos;
	///////////////////////////
	CURVEPROC SCurveType = pCurrentSCurve->GetCurveType_S();
	////////////////////////////////////////////////////////
	switch(SCurveType)
	{
		case CP_CIRCLE:

			m_SegAngle		= pCurrentSCurve->GetSegAngle_S(); 
			m_dAngSpec		= pCurrentSCurve->GetTheta_S();
			m_dAng   		= m_dAngSpec;
			m_bArc			= pCurrentSCurve->IsArcType();
			///////////////////////////////////////
			switch(m_CircType)
			{
				
				case CIRCLE_BY_ROT:

					m_dAng			= pCurrentSCurve->GetTheta_S();
					//////////////////////////////////////////// FromID & ToID
					pos			= pINodeList->FindIndex( 1 );
					pAddFromNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_FromID	= pAddNode->GetObjectID();
					pINodeList->RemoveAt(pos);
					//////////
					pAddFromNode	= (CDrNode*)(pINodeList->GetTail());
					m_ToID		= pAddNode->GetObjectID();
					pINodeList->RemoveTail();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_NO3:
					break;

					
				case CIRCLE_BY_2N_TI:
		
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_2N_CC:

					//////////////////////////////////////////// CCID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_CCID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;

					
				case CIRCLE_BY_2CN_TI_R:

					m_dRadius	= pCurrentSCurve->GetRadius_S();
					//////////////////////////////////////////// TIID
					pos			= pINodeList->FindIndex( 1 );
					pAddNode	= (CDrNode*)(pINodeList->GetAt(pos));
					m_TIID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CAID
					pAddNode	= (CDrNode*)(pINodeList->GetHead());
					m_CAID		= pAddNode->GetObjectID();
					//////////////////////////////////////////// CBID
					pAddNode	= (CDrNode*)(pINodeList->GetTail());
					m_CBID		= pAddNode->GetObjectID();
					////////////////////////////////////
					break;
				
				default:

					break;

			}
			////////////////////////////////////
			pCurrentSCurve = MC_Circle.CreateCircle(
								*pID,pCurrentSCurve,&m_NodeList,SCurveType,
								&m_ElSegList,m_CircType,m_dAng,m_SegAngle,m_dRadius,
								m_bArc,pAddFromNode,pAddToNode,TRUE);
			break;
			/////////////////
			if(!pCurrentSCurve)
			{
				pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
				return -1;
			}
			break;
				
		case CP_PARABOLA:
			pCurrentSCurve = MC_Parabola.CreateParabola(*pID,pCurrentSCurve,&m_NodeList,SCurveType,
											&m_ElSegList,/*m_bAdvanceOn*/FALSE,TRUE);
			break;
			
		default:
			
			m_bAdvanceOn = FALSE; // because cloned  data already obtained
			/////////////////////
			pCurrentSCurve = GangC.CreateCurve(*pID,pCurrentSCurve,&m_NodeList,SCurveType,
											&m_ElSegList,m_bAdvanceOn,TRUE);// TRUE = Final
	}
	pCurrentSCurve->SetShow(FALSE);	// Do not show
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

int CSLDCur::Get_Values_NonIso_Cur(STALPROC StaLProc)
{
	AfxMessageBox("Get_Values_NonIso_Cur\nNOT IMPLEMENTED YET");
	return -1;
}

int CSLDCur::ShowInfo_CurveStaticLoad(CDrCurve* pDrCurve, char* buf, int jStart,CString& CurrentStLID)
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
			AfxMessageBox("Internal ERROR:\nCSLDCur::FillInfo_CurveStaticLoad\npDrLinSup=NULL"); 
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

void CSLDCur::Serialize(CArchive& ar)
{

	CSLDNod::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDMousC:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDMousC:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


