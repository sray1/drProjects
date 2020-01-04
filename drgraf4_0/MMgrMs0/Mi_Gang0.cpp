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
#include "MsObjMgr.h"
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
//#include "Def_Lims.h"  
///////////////////// cards
#include "Def_Card.h"
///////////////////// Mesh
#include "Def_Elem.h"
#include "DrFE0D.h"
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
#include "MI_Gang0.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Gang0,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
//#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
/////////////////////////////////////////////////////////////////////////////
CMI_Gang0::CMI_Gang0()
{
}

CMI_Gang0::~CMI_Gang0()
{
}	

int CMI_Gang0::SetElemInfoID(CString& ElemID,UINT nElemType)		
{
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////// 
	char buf[50];
	/////////////////////////////
	pMsObjMgr->BumpLastMeshNo(nElemType);					// bump it
    int nLastNum	= pMsObjMgr->GetLastMeshNo(nElemType);		// internal
	sprintf(buf,"%d",nLastNum);
	ElemID	= "";
	ElemID	+= buf;
	///
	return 0;
}

int CMI_Gang0::ReciprocateElemMeshList(CDrObject* pElem, CDrObject* pMesh, UINT nGenType)
{
	int nResult = 0;
	CDListMgr* pMList = NULL;
	////////////////
	switch(nGenType)
	{
		case MESH0D:	pMList = pElem->GetMs0List();	break; 
		case MESH1D:	pMList = pElem->GetMs1List();	break;  
		case MESH2D:	pMList = pElem->GetMs2List();	break;  
		case MESH3D:	pMList = pElem->GetMs3List();	break;  
		case MBJ3D:		pMList = pElem->GetMbj3DList();	break;  
		default:		
			AfxMessageBox("Internal ERROR\nCMI_Gang0::ReciprocateElemMeshList");
			nResult = -1;
			return nResult;
	}
	////////////////////		
	int index = pMList->GetObjectIndex(pMesh);
	if(index<0) // not in list yet
		pMList->InsertObject(pMesh);
	///////////////
	return nResult;
}

CDrFE0D* CMI_Gang0::PostFE0D(CString& Nid,WORLD Pt,BOOL bCNode,BOOL bMNode)
{
	/////////////////////////////////////////////////////////////////////
	//	For Creation of FE0D:CNODE & MNODE
	/////////////////////////////////////////////////////////////////////
	// Internal Generation: bMNode = TRUE->LEVEL_KIDDO/FALSE->LEVEL_GRAPA
	//////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////////////////
	CDrFE0D*	pNode;
	CDrLabel*	pLabel;
	int nNodeIndex,nLabelIndex;
	/////////////////////////// Create Anyway
	nNodeIndex = -12345;
	pNode = CreateFE0D(Nid,pLabel,Pt,bCNode,TRUE,bMNode,nNodeIndex,nLabelIndex);
													// TRUE = Internally Generated
	//////////////////////////////////////////////////////////////////////////////
	// remove from General Node DataBase, becaause PRIVATE (bGen = TRUE)
	/////////////////////////////////////////////////////////// FE0DList
	pDListMgr		= pObjectMgr->GetObjectList(FE0D);
	/////////////////
	pDListMgr->RemoveObject(nNodeIndex);
	pDListMgr = pObjectMgr->GetObjectList(LABEL);
	pDListMgr->RemoveObject(nLabelIndex);
	//////////////////////////////////////////////
	return pNode;
}

CDrFE0D* CMI_Gang0::CreateFE0D(CString& Nid,CDrLabel* pLabel,WORLD Pt,BOOL bCNode,BOOL bGen,
							    BOOL bMNode,int& nNodeIndex,int& nLabelIndex)
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
	CMsObjMgr* pMsObjMgr 	= pDoc->GetMsObjMgr();
	CDListMgr* pDListMgr;
	/////////////////////////////////////////////////////////// NodeList
	if(bCNode)
		pDListMgr		= pObjectMgr->GetObjectList(MCNODE);
	else
		pDListMgr		= pObjectMgr->GetObjectList(FE0D);
	/////////////////
	CDrFE0D*	pAdd;
	/////////////////////////////////////////////////////////////////////////// Xisting ?
	if(nNodeIndex != -12345)
	{
		CMI_GangN GangN;
//092798		nNodeIndex = GangN.CompareNodeCoords(pDListMgr,Pt,bCNode,bGen,bMNode);
		nNodeIndex = GangN.CompareNodeCoords(pDListMgr,Pt,bCNode,bGen);
		///////////////////
		if(nNodeIndex>=0)
		{
			pAdd		= (CDrFE0D*)pDListMgr->GetObject(nNodeIndex);
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
			pAdd 	= (CDrFE0D*)(pMsObjMgr->AddToDataBase(nNodeIndex,MCNODE));
		else
		if(bMNode)
			pAdd 	= (CDrFE0D*)(pMsObjMgr->AddToDataBase(nNodeIndex,MNODE));
		else
			pAdd 	= (CDrFE0D*)(pMsObjMgr->AddToDataBase(nNodeIndex,FE0D));
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
		m_FromID	= "";
		m_ToID		= "";
		m_dLength	= 0.0;
		m_DxWorld	= 0.0;
		m_DyWorld	= 0.0;
		m_DzWorld	= 0.0;
 		m_bCoord	= TRUE;
		///////////////////////////////////////
		SetInfoForFE0DBase(pAdd,bGen,bMNode);		// TRUE = Generated internally
													// FALSE= Input
		////////////////////////////////////// Label
		pLabel = CreateFE0DLabel(pAdd, nLabelIndex);//
		/////////////////////////////////////// Reciprocate
		pAdd->GetLabelList()->AddTail(pLabel);
	}
	////////////
    return pAdd;
}

CDrLabel* CMI_Gang0::CreateFE0DLabel(CDrFE0D* pNode,int& nActiveIndex)
{
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////////////// Add
	CDrLabel* pNodeLabel	= (CDrLabel*)(pObjectMgr->AddToDataBase(nActiveIndex,LABEL));
	///////////////////////////////////////////////
	SetInfoForFE0DLabel(pNode,pNodeLabel);
	///////////////
    return pNodeLabel;
}


void CMI_Gang0::SetInfoForFE0DBase(CDrFE0D* pNode,BOOL bGen,BOOL bMNode)
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
	pNode->SetObjectType((int)FE0D);
	pNode->SetElemType((int)MESH_OBJECT);			// globals.h
	///
	if(bMNode || m_bnid_c)
		pNode->SetLevelType((int)LEVEL_GRAPA); 			// MeshNode:GRAPA Level
	else
		pNode->SetLevelType((int)LEVEL_KIDDO); 			// Vertex:KIDDO Level
	///
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
		pNode->SetLevelType((int)LEVEL_GRAPA);								// GRAPA Level
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
//		if(!bMNode)
// 			pNode->SetLevelType((int)LEVEL_GRAPA);							// GRAPA Level
   		//////////////////////////////
    	LocalPos.x = m_xWorld; 
    	LocalPos.y = m_yWorld; 
    	LocalPos.z = m_zWorld;

    }	
    //////////////////////////////////////// Save as Local Pos
    pNode->SetMeshNode(bMNode);
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
    pNode->SetFromID(m_FromID);
    pNode->SetToID(m_ToID);
	////////////////////////////////////////// Control Node?	
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

void CMI_Gang0::SetInfoForFE0DLabel(CDrFE0D* pAddNode,CDrLabel* pLabel)
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
    pLabel->SetLevelType((int)LEVEL_GRAPA);         // globals
	pLabel->SetObjectID(m_id);             
	/////////////////////////////////////////////////
	pLabel->SetText(m_id);
	pLabel->SetType(LABEL_NODE);       
//	pLabel->SetViewNum(m_nActiveViewNumber); // Not Needed for the labeltype
	/////////////////////////////
	pLabel->SetNodePtr((CDrNode*)pAddNode);
	pLabel->SetMoved(FALSE);   // forces coord. to be recognized on 3D basis
	/////////////////////////////     
	pLabel->SetColor(Color); 
	pLabel->SetAngle(0);       // Horizontal Label
	pLabel->SetLogFont(lf);
	pLabel->SetLayer(pLayer->GetCurrentLayer());
	////////////
	return;
} 

void CMI_Gang0::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Gang0:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Gang0:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


