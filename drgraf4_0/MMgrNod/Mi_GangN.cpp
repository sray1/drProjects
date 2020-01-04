// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h> 

#include "3DMath.h"

#include "Def_Objs.h"
#include "Def_View.h"
#include "Def_Type.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
//#include "Def_Lims.h"  
///////////////////// cards
#include "Def_Card.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// specials
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
#include "DrFont.h"
#include "booleans.h"
/////////////////////
#include "Mouse.h" 
#include "MI_GangN.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_GangN,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
//#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
/////////////////////////////////////////////////////////////////////////////
CMI_GangN::CMI_GangN()
{
}

CMI_GangN::~CMI_GangN()
{
}	

			
void CMI_GangN::SaveINode(CDListMgr* pList,CString* pID)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	////////////////////////////////////////// save in LIST
	int index 				= pObjectMgr->GetObjectIndexfromKey(NODE,*pID,1);
	pDListMgr				= pObjectMgr->GetObjectList(NODE);
	CDrNode* pDrNode 		= (CDrNode*)(pDListMgr->GetObject(index));
	//////////////////////////////////
	pList->InsertObject(pDrNode);
	//////////////////////////////////
}	

CDrNode* CMI_GangN::PostNode(CString& Nid,UINT uLevelType,WORLD Pt,BOOL bCNode)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 			= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 		= pDoc->GetObjectMgr();
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	/////////////////////////////////////////////////////////// Create Anyway
	CDrNode*	pNode;
	pNode = new CDrNode;
    //////////////////////////////////////// Save as Local Pos
	pNode->SetObjectType((int)NODE);
	pNode->SetElemType((int)ELEM_OBJECT);              // globals.h
    pNode->SetLevelType((int)uLevelType);								// Kid Level
    /////////////////////////////
	pNode->SetObjectID(Nid);             
    pNode->SetLocalPos(Pt);
	(pNode->GetNodeCard())->x = (long)Pt.x;	
	(pNode->GetNodeCard())->y = (long)Pt.y;	
	(pNode->GetNodeCard())->z = (long)Pt.z;
	//////////////////////////////////////////	
	(pNode->GetNodeCard())->id 		= Nid;	
	(pNode->GetNodeCard())->sup_id	= "";
	(pNode->GetNodeCard())->nid_r 	= "";
	(pNode->GetNodeCard())->bnid_c 	= bCNode; 
	/////////////////////////////////////////////
	pNode->SetGenerated(TRUE);
	////////////////////////////////////////// 
	pNode->SetFormat(pObjectMgr->GetFormat());
	pNode->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pNode->SetLayer(pLayer->GetCurrentLayer());
	pNode->SetPrecision(pPrecision->GetPrecision());
	pNode->SetMapFactor(pMapFactor->GetMapFactor());
	pNode->SetScaleFactor(pScaleFactor->GetScaleFactor());
	pNode->SetMasterMultFac(1); // temporary: should come from MASTER CARD  todo
	/////////////////////////////////////////////
/*011199	
	/////////////////////////////////////////////////////////////////////
	// Internal Generation: bMNode = TRUE->LEVEL_KIDDO/FALSE->LEVEL_GRAPA
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	CDrLabel*	pLabel = NULL;
	int nNodeIndex,nLabelIndex;
	nNodeIndex = -12345;
	pNode = CreateNode(Nid,pLabel,Pt,bCNode,TRUE,nNodeIndex,nLabelIndex,uLevelType);
													// TRUE = Internally Generated
	//////////////////////////////////////////////////////////////////////////////
	// remove from General Node DataBase, becaause PRIVATE (bGen = TRUE)
	/////////////////////////////////////////////////////////// NodeList
	int nObjType = NODE;
	pDListMgr		= pObjectMgr->GetObjectList(NODE);
	if(bCNode)
	{
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
		nObjType	= CNODE;
	}
	/////////////////
	int nRowIndex;
	pObjectMgr->ObjIndexToRowIndex(nRowIndex, nNodeIndex, nObjType);
	pObjectMgr->DeleteFromRowList(nRowIndex);
	pDListMgr->RemoveObject(nNodeIndex);
	//////////////////////////////////////////////
	nObjType	= LABEL;
	pObjectMgr->ObjIndexToRowIndex(nRowIndex, nLabelIndex, nObjType);
	pObjectMgr->DeleteFromRowList(nRowIndex);
	pDListMgr = pObjectMgr->GetObjectList(LABEL);
	pDListMgr->RemoveObject(nLabelIndex);
*/
	//////////////////////////////////////////////
	return pNode;
}

//int CMI_GangN::CompareNodeCoords(CDListMgr* pDListMgr,WORLD Pt,BOOL bCNode,BOOL bGen,BOOL bMNode)
int CMI_GangN::CompareNodeCoords(CDListMgr* pDListMgr,WORLD Pt,BOOL bCNode,BOOL bGen)
{
//092798 Internal Generation: bMNode = TRUE->LEVEL_KIDDO/FALSE->LEVEL_GRAPA
	//////////////////////////////////////////////////////////////////////////////
	//		if nNodeIndex == -12345 -> Create Anyway							//
	//																			//
	//		if bGen = TRUE ->	internally Generated ( like Posted Cnodes )		//
	//							(ie.Pt ALREADY has								//
	//								WorldBase & MapFactor in it					//
	//				= FALSE ->	Mouse/Dlg Generated ( like Input Nodes )		//
	//							(ie.Pt has NO  ( ie. Physical Coords)			//
	//								WorldBase & MapFactor in it					//
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision 	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor 	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	double dWorldBase = (double)lWorldBase; 
	///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////////////////////////////////
	CHitNet*	pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	double		dTol		= pHitNet->GetSearchDet(); 
	if(bGen == FALSE)	// physical	
	///////////////////////////////
	{
		dTol 	= ((double)(dTol))/dWorldBase*dMapFactor;
		pObjectMgr->DStoSC(&dTol);
	}
	//////////////////////////////////////////////////// Check by Coord
	int nNodeIndex = -1;
	////////////////////
	if(pDListMgr->IsEmpty())
		return nNodeIndex;
	///////////////////////////////////////////////////////////////////// COMPARE
	double LocXm,LocXp,LocYm,LocYp,LocZm,LocZp;
	/////////////////////////////////
	POSITION pos = pDListMgr->GetFirstObjectPos();
	CDrNode* pObject;
	for (int i=0;pos !=NULL;i++)
	{
		pObject = (CDrNode*)pDListMgr->GetNextObject( pos);
		//////////////////////////////////////////////////// Check if CNODE required
		if(
			((!pObject->IsControlNode()) && bCNode) ||
			((pObject->IsControlNode()) && !bCNode)	
		)		
			continue;					// No Hit
/*092798
		//////////////////////////////////////////////////// Check if MNODE required
		if(
			((!pObject->IsMeshNode()) && bMNode) ||
			((pObject->IsMeshNode()) && !bMNode)	
		)		
			continue;					// No Hit
092798*/
		/////////////////////////////////////////////////////////////// Right Type
		WORLD Loc = *(pObject->GetLocalPos());
		////////////////////////////////////// 
		if(bGen == FALSE)	// physical	
		///////////////////////////////
		{
			///////////////////////////////////////////
			Loc.x	= ((double)(Loc.x))/dWorldBase*dMapFactor;
			Loc.y	= ((double)(Loc.y))/dWorldBase*dMapFactor;
			Loc.z	= ((double)(Loc.z))/dWorldBase*dMapFactor;
			////////////////////////////////////////////////////// Physical
			pObjectMgr->DStoSC(&Loc.x);
			pObjectMgr->DStoSC(&Loc.y);
			pObjectMgr->DStoSC(&Loc.z);
			///////////////////////////
		}			
		/////////////////////////////////////////// Compare
		LocXm = Loc.x - dTol;
		LocXp = Loc.x + dTol;
		LocYm = Loc.y - dTol;
		LocYp = Loc.y + dTol;
		LocZm = Loc.z - dTol;
		LocZp = Loc.z + dTol;
		/////////
		if
		(
			(Pt.x >= LocXm && Pt.x <= LocXp) &&
			(Pt.y >= LocYm && Pt.y <= LocYp) &&
			(Pt.z >= LocZm && Pt.z <= LocZp) 
		)
		{
			nNodeIndex = i;
			break;
		}
	}
	//////////////////////////
	return nNodeIndex; 
}


CDrNode* CMI_GangN::CreateNode(CString& Nid,CDrLabel* pLabel,WORLD Pt,BOOL bCNode,BOOL bGen,
					/*092798BOOL bMNode,*/int& nNodeIndex,int& nLabelIndex,UINT uLevelType)
{
	//////////////////////////////////////////////////////////////////////////////
	//		if nNodeIndex == -12345 -> Create Anyway							//
	//																			//
	//		if bGen = TRUE ->	internally Generated ( like Posted Cnodes )		//
	//							(ie.Pt ALREADY has								//
	//								WorldBase & MapFactor in it					//
	//				= FALSE ->	Mouse/Dlg Generated ( like Input Nodes )		//
	//							(ie.Pt has NO  ( ie. Physical Coords)			//
	//								WorldBase & MapFactor in it					//
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	/////////////////////////////////////////////////////////////////// Right NodeList
//	pDListMgr	= pObjectMgr->GetNodeList_OtherContext(bCNode,bMNode);
	pDListMgr	= pObjectMgr->GetNodeList_OtherContext(bCNode,FALSE);
	/////////////////
	CDrNode*	pAdd;
	/////////////////////////////////////////////////////////////////////////// Xisting ?
	if(nNodeIndex != -12345)
	{
//		nNodeIndex = CompareNodeCoords(pDListMgr,Pt,bCNode,bGen,bMNode);
		nNodeIndex = CompareNodeCoords(pDListMgr,Pt,bCNode,bGen);
		///////////////////
		if(nNodeIndex>=0)
		{
			pAdd		= (CDrNode*)pDListMgr->GetObject(nNodeIndex);
			pLabel		= (CDrLabel*)(pAdd->GetLabelList()->GetHead());
			pDListMgr	= pObjectMgr->GetObjectList(LABEL);
			nLabelIndex	= pDListMgr->GetObjectIndex(pLabel);
			////////////
			return pAdd;
		}
	}
	/////////////////////////////////////////////////////////////////////////
	{
		if(bCNode)
			pAdd 	= (CDrNode*)(pObjectMgr->AddToDataBase(nNodeIndex,CNODE));
/*092798
		else
		if(bMNode)
			pAdd 	= (CDrNode*)(pObjectMgr->AddToDataBase(nNodeIndex,MNODE));
092798*/
		else
			pAdd 	= (CDrNode*)(pObjectMgr->AddToDataBase(nNodeIndex,NODE));
		////////////////////////////
		m_id		= Nid;
		m_bnid_c 	= bCNode;
		m_xWorld 	= Pt.x;
		m_yWorld 	= Pt.y;
		m_zWorld	= Pt.z;
		/////////////////////////////////////// Default
		m_sup_id	= "";
		m_load_id	= "";
		m_nid_r 	= "";
//		m_FromID	= "";
//		m_ToID		= "";
//		m_bFromCN	= FALSE;
//		m_bToCN		= FALSE;
		m_dLength	= 0.0;
		m_DxWorld	= 0.0;
		m_DyWorld	= 0.0;
		m_DzWorld	= 0.0;
 		m_bCoord	= TRUE;
		///////////////////////////////////////
//		SetInfoForNodeBase(pAdd,bGen,bMNode);		// TRUE = Generated internally
		SetInfoForNodeBase(pAdd,bGen,uLevelType);		// TRUE = Generated internally
													// FALSE= Input
		////////////////////////////////////// Label
		pLabel = CreateNodeLabel(pAdd, nLabelIndex,uLevelType);//
		/////////////////////////////////////// Reciprocate
		pAdd->GetLabelList()->AddTail(pLabel);
	}
	////////////
    return pAdd;
}

CDrLabel* CMI_GangN::CreateNodeLabel(CDrNode* pNode,int& nActiveIndex,UINT uLevelType)
{
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////////////// Add
	CDrLabel* pNodeLabel	= (CDrLabel*)(pObjectMgr->AddToDataBase(nActiveIndex,LABEL));
	///////////////////////////////////////////////
	m_id = pNode->GetObjectID(); 
	SetInfoForNodeLabel(pNode,pNodeLabel,uLevelType);
	///////////////
    return pNodeLabel;
}

void CMI_GangN::SetInfoForNodeBase(CDrNode* pNode,BOOL bGen,UINT uLevelType)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current Node
	LONG  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////
	pNode->SetObjectType((int)NODE);
	pNode->SetElemType((int)ELEM_OBJECT);              // globals.h
//    pNode->SetLevelType((int)LEVEL_KIDDO);								// Kid Level
    pNode->SetLevelType((int)uLevelType);								// Kid Level
	pNode->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	(pNode->GetNodeCard())->id 		= m_id;	
	(pNode->GetNodeCard())->sup_id	= m_sup_id;
	(pNode->GetNodeCard())->nid_r 	= m_nid_r;
	//////////////////////
   	WORLD LocalPos;
	/////////////////////////////////////////
	pNode->SetGenerated(bGen);
	//////////////////////////
	if(!bGen) // Not Internally generated(i.e. thro' Dialog)
	{
//092798		pNode->SetLevelType((int)LEVEL_GRAPA);								// GRAPA Level
		/////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_xWorld);
		pObjectMgr->SCtoDS(&m_yWorld);
		pObjectMgr->SCtoDS(&m_zWorld);
    	//////////////////////////////
    	LocalPos.x = m_xWorld*dWorldBase/dMapFactor; 
    	LocalPos.y = m_yWorld*dWorldBase/dMapFactor; 
    	LocalPos.z = m_zWorld*dWorldBase/dMapFactor;
	}
	else	// Internally Generated
	{
/*092798
		if(!bMNode)
 			pNode->SetLevelType((int)LEVEL_GRAPA);							// GRAPA Level
092798*/
   		//////////////////////////////
    	LocalPos.x = m_xWorld; 
    	LocalPos.y = m_yWorld; 
    	LocalPos.z = m_zWorld;

    }	
    //////////////////////////////////////// Save as Local Pos
    pNode->SetLocalPos(LocalPos);
    /////////////////////////////
	(pNode->GetNodeCard())->x = (long)LocalPos.x;	
	(pNode->GetNodeCard())->y = (long)LocalPos.y;	
	(pNode->GetNodeCard())->z = (long)LocalPos.z;
	/////////////////////////////////////////////
	pNode->SetInputMode(m_bCoord);
	//////////////////////////////
	WORLD Delta;
	Delta.x = m_DxWorld;
	Delta.y = m_DyWorld;
	Delta.z = m_DzWorld;
	///////////////////////
    pNode->SetDelta(Delta);
	///////////////////////
    pNode->SetLength(m_dLength);
//   pNode->SetFromID(m_FromID);
//    pNode->SetToID(m_ToID);
//    pNode->SetFromCN(m_bFromCN);
//    pNode->SetToCN(m_bToCN);
	//////////////////////////////////////////	
	(pNode->GetNodeCard())->bnid_c 	= m_bnid_c; 
	////////////////////////////////////////// 
	pNode->SetFormat(pObjectMgr->GetFormat());
	pNode->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pNode->SetLayer(pLayer->GetCurrentLayer());
	pNode->SetPrecision(pPrecision->GetPrecision());
	pNode->SetMapFactor(pMapFactor->GetMapFactor());
	pNode->SetScaleFactor(pScaleFactor->GetScaleFactor());
	pNode->SetMasterMultFac(1); // temporary: should come from MASTER CARD  todo
	//////////////////
	return;
	
} 

void CMI_GangN::SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel,UINT uLevelType)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CDrFont* pDrFont 		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	///////////////////////////////////////////////////////// Color/View Number 
	COLORREF Color 	= pDrFont->GetTextColor();
	LOGFONT lf 		= pDrFont->GetCurrentLogFont();
	///////////////////////////////////////////////////////// Update Current Label
	pLabel->SetObjectType((int)LABEL);
	pLabel->SetElemType((int)DRAW_OBJECT);              // globals.h
    pLabel->SetLevelType((int)uLevelType);         // globals
	pLabel->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	pLabel->SetText(m_id);
	pLabel->SetType(LABEL_NODE);       
//	pLabel->SetViewNum(m_nActiveViewNumber); // Not Needed for the labeltype
	/////////////////////////////
	pLabel->SetNodePtr(pAddNode);
	pLabel->SetMoved(FALSE);   // forces coord. to be recognized on 3D basis
	/////////////////////////////     
	pLabel->SetColor(Color); 
	pLabel->SetAngle(0);       // Horizontal Label
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	////////////
	return;
} 

void CMI_GangN::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_GangN:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_GangN:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


