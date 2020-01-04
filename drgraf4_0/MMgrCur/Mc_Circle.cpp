// Rotate.cpp : implementation file
//


#include "stdafx.h"
#include <afxtempl.h>		// CList
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 
#include "XForm.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
///////////////////// dialogMgr
#include "MCurMgr.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "HitNet.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
//#include "CU_Circl.h"
 
#include "MC_Circle.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define MIN_CNODES_CURVE	4
#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
////////////////////////////////////
IMPLEMENT_SERIAL(CMC_Circle,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Circle::CMC_Circle()
{
	m_DataList_Ex.RemoveAll();
}

CMC_Circle::~CMC_Circle()
{
}

CDrCurve* CMC_Circle::CreateCircle(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
					 CURVEPROC kind,CList<int,int>* pElperSegList,CIRCLETYPE nType,
					 double dAng,double SegAngle,double dRadius,BOOL bArc,
					 CDrNode* pFromIDNode,CDrNode* pToIDNode,BOOL bFinal)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	m_DataList_Ex.RemoveAll();
	////////////////////////////////////////////////////// Already in DataBase
	m_pDrCurve 	= pCurve;
	/////////////////////////////////////////////// Fill EverythingElse
	m_CurveID		= Cid;
	m_CurveType_S	= kind;
	m_nType			= nType;
	m_bClosed_S		= m_pDrCurve->IsClosed_S();
	m_Ratio_S		= m_pDrCurve->GetRatio_S();
	m_bUnifOT_S		= (m_Ratio_S == 1.0)?TRUE:FALSE;
	m_dAng			= dAng;
	m_pFromIDNode	= pFromIDNode;
	m_pToIDNode		= pToIDNode;
	m_nMesh			= pElperSegList->GetHead();
	m_SegAngle		= SegAngle;
	///////////////////////////// Specific to CIRCLE_BY_ROT 
	if(nType == CIRCLE_BY_ROT)
	{
		m_nMesh			= pElperSegList->GetHead();
		int nBezSeg		= pElperSegList->GetTail();	// # of Bezier Segs
		m_nMesh			*= nBezSeg;
		pElperSegList->RemoveAll();
		pElperSegList->AddTail(m_nMesh);			// Total # of Elems
		m_SegAngle		= m_dAng/nBezSeg;
		if(m_SegAngle>120.)
			m_SegAngle = 120.;
	}
	/////////////////////////////////////////////////////////////////////
	// save only Total Elems for BezInfo Generation in CalcAdditionalInfo
	m_pDrCurve->GetElperSegList_S()->AddTail(pElperSegList);	// to be reset based on nBezSegs
															// in BezierSeg_N_Mesh_Done
	/////////////////////////////
	m_nOrder_S		= 3;
	m_bArc			= bArc;
	m_Radius_S		= dRadius;
	//////////////////////////////////////////////////// Common Info	
	SetCommonInfoForCircle(m_pDrCurve);
	/////////////////////////////////////////////////// Additional Info
	int nResult = CalcAdditionalInfo(pCurve,bFinal,nType);
	ASSERT(nResult>=0);
	////////////////////////////////////////////////////////// Go Interpolate
	GoDoIt(m_pDrCurve,bFinal);	//TRUE=FINAL
	//////////////////////////////////////////////////////////////////// Center
	if(bFinal)
	{
		CString Nid;
		CDrNode* pAddNode;
		////////////
		if(nType != CIRCLE_BY_2N_CC)
		{
			int nChLen;
			///////////////////////////////////////////// Name
			nChLen	= m_CurveID.GetLength();
			if(nChLen>NUM_LEN-2)
				nChLen = NUM_LEN-2;
			//////////////////////////////////////////////////////////////////// Center	
//			Nid		= m_CurveID.Left(nChLen);
			Nid		= m_CurveID;
			Nid		+= "_Ctr"; 
			pAddNode = PostNode(Nid,LEVEL_KIDDO,m_Center_S,TRUE);	// Create DrCNode
			if(!pAddNode)	// Create DrCNode
				return (CDrCurve*)NULL;
			m_pDrCurve->GetElemList()->InsertObject(pAddNode); //ElemList
		}
		/////////////////////////////////////////////////////////// INODE HANDLE
/*
		// Last Control Node make ADDITIONAL COPY HANDLE Node public
		// for m_nInputType = CIRCLE_BY_ROT
		// for m_nInputType = CIRCLE_BY_NO3 with !m_bArc
		////////////////////////////////////////////////////
		if(!m_bArc && !m_bClosed_S) 
		{
			/////////////
			WORLD LocalPos = *(((CDrNode*)m_pCNodeList->GetTail())->GetLocalPos());
			////////////////////////// Create & save in ENodeList
			PackAuxiliaryList(m_pDrCurve,LocalPos,m_pDrCurve->GetENodeList());
		}
*/
		//////////////////////////////////////////// NODE HANDLE Based on BezSegs
		PackINodeList(m_pDrCurve);
		//////////////////////////////////////////////////////// Setup Knots
		CDListMgr* pINList = pCurve->GetINodeList();
		int nData1 = pCurve->GetData_S();
		int nData = pINList->GetCount();
		if(nData != nData1)
		{
			AfxMessageBox("Internal ERROR\nCMC_Circle::CreateCircle\nnData != nData1");
			return (CDrCurve*)NULL;
		}
		pWORLD inData = new WORLD[nData];
		/////
		SetUpINodes(pINList,inData,nData);
		/////
		m_nKnots_S = pCurve->GetnKnots_S();
		pDOUBLE m_pKnot_S = new double[m_nKnots_S];	// will be deleted in DrCurve
		/////
		m_KnotType_S = KN_AUTO;	// chordlength
		SetupKnots(inData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
		///////////////////////////////////////////////////// Save
		pCurve->SetpKnots_S(m_pKnot_S);	// pointer
		//////////////////////////////////////////
		delete [] inData;
	}
	/////////////////////////////////////////////////////////////
	m_DataList_Ex.RemoveAll();
	//////////////////
    return m_pDrCurve;
}

int CMC_Circle::SetCommonInfoForCircle(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pINodeList	= pDrObject->GetINodeList();	// Tangent Intersection CNode
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
	pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetInputType(m_nType);		// 3 = CircleBy2N_TI_RADIUS 
	pDrObject->SetCircleType(m_nType);
	pDrObject->SetOrder_S(m_nOrder_S);				// k = 3 for Circle
	pDrObject->SetCurveType_S(CP_CIRCLE);
	pDrObject->SetSegAngle_S(m_SegAngle);
	pDrObject->SetnDim_S(4);	// Homogeneous(Rational) 
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	pDrObject->SetTheta_S(m_dAng);		
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetArcType(m_bArc);				// for later editing		
	////////////////////////////////////////// Axis Input
	pDrObject->SetAxisInput(m_bAxis);
	pDrObject->SetAxis(m_nAxis);
	pDrObject->SetNegative(m_bNegative);
	////////////////////////////////////////// CIRCLE_BY_ROT
	CDListMgr*  pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	///
	if(m_nType == CIRCLE_BY_ROT)
	{	
		if(m_pFromIDNode)
		{
			pDrObject->SetFromIDNode_S(m_pFromIDNode);
			m_pFromIDNode->GetCurveList()->InsertObject(pDrObject);
		}
		if(m_pToIDNode)
		{
			///////////////////////////////
			pDrObject->SetToIDNode_S(m_pToIDNode);
			m_pToIDNode->GetCurveList()->InsertObject(pDrObject);
		}
	}
	/////////////////
    int nData;  
	CString Nid;
	CDrNode* pDrNode;
	////////////////////////////////////
    nData = pINodeList->GetCount();
	pDrObject->SetData_S(nData);			// GIVEN: # of Data : // will be reset again later
	pDrObject->SetMaxINodes_S(nData);
	/////////////////////////////////
	for (POSITION posI = pINodeList->GetHeadPosition( );posI !=NULL;)
	{
		////
		pDrNode = (CDrNode*)pINodeList->GetNextObject(posI);
		////////////////////////////////// save curve
		int index = (pDrNode->GetCurveList())->GetObjectIndex(pDrObject); // exists already?
		if(index>=0)
			continue;
		/////////////
		pDrNode->GetCurveList()->InsertObject(pDrObject);
	}
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////////////////////////
	return 0;
	
}
///////////////////////////////////////////////////////////////////////////// 
int CMC_Circle::CalcAdditionalInfo(CDrCurve* pDrCurve,BOOL bFinal,CIRCLETYPE nType)
{
	switch(nType)
	{
		case 	CIRCLE_BY_ROT:
			return CalcAdditionalInfo_Rot(pDrCurve,bFinal);
		case 	CIRCLE_BY_NO3:
			return CalcAdditionalInfo_3Node(pDrCurve,bFinal);
		case 	CIRCLE_BY_2N_TI:
			return CalcAdditionalInfo_2N_TI(pDrCurve,bFinal);
		case 	CIRCLE_BY_2N_CC:
			return CalcAdditionalInfo_2N_CC(pDrCurve,bFinal);
		case 	CIRCLE_BY_2CN_TI_R:
			return CalcAdditionalInfo_2CN_TI_R(pDrCurve,bFinal);
		default:
			break;
	}
	/////////
	return -1;
}

int CMC_Circle::PackINodeList(CDrCurve* pCurve)
{
	C3DMath Math3D;
	///////////////
	//	Extra B0,b2 Nodes + original INodes in INodeList 
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	CString ObjID;
	CDListMgr TemList;
	CDListMgr* pINList = pCurve->GetINodeList();
	int nINs	= pINList->GetCount();
	CDListMgr* pCNList = pCurve->GetCNodeList();
	int nCNs	= pCNList->GetCount();
	int nCNStep	= pCurve->GetOrder_S()-1;
	/////////////////////////////////////
	CDrNode* pCNode;
	CDrNode* pINode;
	WORLD wNc; // control Node localpos
	WORLD wNi; // input Node localpos
	int i,j,jStart=0;
	for (i=0;i<nCNs;i += nCNStep)	// only b0's & b2's
	{
		////
		pCNode = (CDrNode*)pCNList->GetObject(i);
		wNc		= *(pCNode->GetLocalPos());
		//////////////////////////////////// Compare
		BOOL bIN= FALSE;
		for(j=jStart;j<nINs;j++)
		{
			pINode = (CDrNode*)pINList->GetObject(j);
			wNi		= *(pINode->GetLocalPos());
			////
			if(Math3D.AreSame_WORLD(&wNc, &wNi,pHitNet->GetDblRatio()))
			{
				bIN		= TRUE;
				jStart	= (j++);
				break;
			}
		}
		if(bIN)
		{
			TemList.InsertObject(pINode);
			continue;
		}
		//////////////////////////////////////////////// Create new	
		pObjectMgr->SetObjInfoID(ObjID,INODE);;		// bump it
		/////////////
		CDrLabel* pLabel;
		int nNodeIndex,nLabelIndex;
		/////////////////////////// Create Anyway
		nNodeIndex = -12345;
		CDrNode* pAddNode = CreateNode(ObjID,pLabel,wNc,FALSE/*Not CNode*/,TRUE,
									nNodeIndex,nLabelIndex,LEVEL_GRAPA);
		//////////////////////////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////////////////// Reciprocate
		pAddNode->GetCurveList()->InsertObject(pCurve);
		TemList.InsertObject(pAddNode); //Auxiliary CNode in ENodList
	}
	/////////////////////////////////////////////// Save
	pINList->RemoveAll();
	pINList->AddTail(&TemList);
	TemList.RemoveAll();
	///////////////////////////////////////////////
	return 0;
}

int CMC_Circle::PackAuxiliaryList(CDrCurve* pCurve,WORLD& Ne,CDListMgr* pList)
{
	//	Extra End in ENodeList
	//	Center in ElemList
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CString ObjID;
	pObjectMgr->SetObjInfoID(ObjID,CNODE);;		// bump it
	/////////////
	CDrLabel* pLabel;
	int nNodeIndex,nLabelIndex;
	/////////////////////////// Create Anyway
	nNodeIndex = -12345;
	CDrNode* pAddNode = CreateNode(ObjID,pLabel,Ne,TRUE,TRUE,
								nNodeIndex,nLabelIndex,LEVEL_GRAPA);
	//////////////////////////////////
	if(!pAddNode)	// Create DrCNode
		return -1;
	///////////////////////////////////////////////// Reciprocate
	pAddNode->GetCurveList()->InsertObject(pCurve);
	pList->InsertObject(pAddNode); //Auxiliary CNode in ENodList
	///////////////////////////////////////////////
	return 0;
}

int CMC_Circle::CalcAdditionalInfo_Rot(CDrCurve* pDrCurve,BOOL bFinal)
{
	double dThetaSpec	= pDrCurve->GetTheta_S();
	double 	dTheta		= dThetaSpec;
	BOOL bClosed		= pDrCurve->IsClosed_S();	
 	CDrNode* pFromNode	= pDrCurve->GetFromIDNode_S();
 	CDrNode* pToNode	= pDrCurve->GetToIDNode_S();
  	///////////////////////////////////////////// get Raw Pt.
   	WORLD wFromPt		= *(pFromNode->GetLocalPos());
 	WORLD wToPt			= *(pToNode->GetLocalPos());
   ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pWORLD pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCMC_Circle::SetAdditionalInfo2");
		return -1;
	}
	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center,Normal;
	double Radius;
	///////////////////////////////////////// AxisVector from
	    									   // end nodes	
	UnitAxisFromEndNodes(&Normal,wFromPt,wToPt);
	///////////////////////////////////////// Center & Radius
	Calc_CandR(pData,&Center,&Radius,Normal,wFromPt);
	///////////////////////////////////////////
	BOOL bExtra = FALSE;
	////////////////////
	if(bClosed)
		dTheta = 360.;
	else
	{
		if(dThetaSpec<0.)dTheta = 0;
		if(dThetaSpec>360.)dTheta = 360.;
		if(dTheta<360.)
			bExtra = TRUE;
	}
	bClosed = (dTheta == 360.)?TRUE:FALSE;
	/////////////////////////////////////////// Override
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetTheta_S(dTheta);		
	pDrCurve->SetClosed_S(bClosed);
	/////////////////////////////////////////////////////////////// Ex_NodeList
	WORLD Ne;
	//////////////////////////////////////////////////////// Ni,i = 1
	for(int k=0;k<nData;k++)
		m_DataList_Ex.AddTail(pData[k]);
	//////////////////////////////////////////////////////// Nj, if NOT Closed
	if(bExtra)
	{
		double dThetaEx = dTheta; 
		GetAPtByRotation(pData,Center,Normal,dThetaEx,&Ne);
		m_DataList_Ex.AddTail(Ne);
	}
	////////////////
	delete [] pData;
	/////////////////////////////////////////////////////////////// Bezier
	BezierInfo(pDrCurve);
	/////////
	return 0;
}
 
int CMC_Circle::CalcAdditionalInfo_3Node(CDrCurve* pDrCurve,BOOL bFinal)
{
	BOOL bArc			= pDrCurve->IsArcType();
	double dThetaSpec	= pDrCurve->GetTheta_S();
	double 	dTheta		= dThetaSpec;
	BOOL bClosed		= pDrCurve->IsClosed_S();	
    ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pWORLD pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCMC_Circle::SetAdditionalInfo2");
		return -1;
	}
	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius;
	Calc_C_R_Normal(pData, &Center, &Radius, &Normal);
	////////////////////////////////////////////////////////// Central Angles etc.
	double dThetaArc = Calc_CentralAngles(pData,Center,Radius,Normal); // angle (N1,N2,N3)
	////////////////////////////////////// if Closed, set angle to 360
	BOOL bExtra = FALSE;
	////////////////////
	if(bClosed)
		dTheta = 360.;
	else
	{
		if(!bArc)
		{
			if(dTheta<0.)dTheta = 0;
			if(dTheta>360.)dTheta = 360.;
			if(dTheta<dThetaArc)
				dTheta = dThetaArc;
			else
			if(dTheta<360.)
				bExtra = TRUE;
		}
		else
			dTheta = dThetaArc;
		///////////////////////
		if(dTheta>dThetaArc && dTheta<360.)
			bExtra = TRUE;
	}
	bClosed = (dTheta == 360.)?TRUE:FALSE;
	/////////////////////////////////////////// Override
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetTheta_S(dTheta);		
	pDrCurve->SetClosed_S(bClosed);
	/////////////////////////////////////////////////////////////// Ex_NodeList
	WORLD Ne;
	//////////////////////////////////////////////////////// Ni,i = 1,2,3
	for(int k=0;k<nData;k++)
		m_DataList_Ex.AddTail(pData[k]);
	//////////////////////////////////////////////////////// Nextra
	if(bExtra)
	{
		double dThetaEx = dTheta - dThetaArc; 
		GetAPtByRotation(pData+2,Center,Normal,dThetaEx,&Ne);
		m_DataList_Ex.AddTail(Ne);
	}
	////////////////
	delete [] pData;
	/////////////////////////////////////////////////////////////// Bezier
	BezierInfo(pDrCurve);
	/////////
	return 0;
}
 
int CMC_Circle::CalcAdditionalInfo_2N_TI(CDrCurve* pDrCurve,BOOL bFinal)
{
	BOOL bArc			= pDrCurve->IsArcType();
	double dThetaSpec	= pDrCurve->GetTheta_S();
	double 	dTheta		= dThetaSpec;
	BOOL bClosed		= pDrCurve->IsClosed_S();	
	//////////////////////////////
	// Content of INodeList:	//
	//		1. NID_I	NODE	//
	//		2. NID_TI	CNODE	//
	//		3. NID_J	NODE	//
	///////////////////////////////////////
    ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pWORLD pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCMC_Circle::SetAdditionalInfo3");
		return -1;
	}
	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius,dThetaArc;
	Calc_CRNPhifromTI(pData, &Center, &Radius, &Normal,&dThetaArc);
	////////////////////////////////////// if Closed, set angle to 360
	BOOL bExtra = FALSE;
	////////////////////
	if(bClosed)
		dTheta = 360.;
	else
	{
		if(!bArc)
		{
			if(dTheta<0.)dTheta = 0;
			if(dTheta>360.)dTheta = 360.;
			if(dTheta<dThetaArc)
				dTheta = dThetaArc;
			else
			if(dTheta<360.)
				bExtra = TRUE;
		}
		else
			dTheta = dThetaArc;
	}
	bClosed = (dTheta == 360.)?TRUE:FALSE;
	/////////////////////////////////////////// Override
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetTheta_S(dTheta);		
	pDrCurve->SetClosed_S(bClosed);
	/////////////////////////////////////////////////////////////// Ex_NodeList
	WORLD Ne;
	//////////////////////////////////////////////////////// Ni,i = 1,3 (NOT TI)
	for(int k=0;k<nData;k+2)
		m_DataList_Ex.AddTail(pData[k]);
	//////////////////////////////////////////////////////// Nextra
	if(bExtra)
	{
		double dThetaEx = dTheta - dThetaArc; 
		GetAPtByRotation(pData+2,Center,Normal,dThetaEx,&Ne);
		m_DataList_Ex.AddTail(Ne);
	}
	////////////////
	delete [] pData;
	/////////////////////////////////////////////////////////////// Bezier
	BezierInfo(pDrCurve);
	/////////
	return 0;
}
 
int CMC_Circle::CalcAdditionalInfo_2N_CC(CDrCurve* pDrCurve,BOOL bFinal)
{
	BOOL bArc			= pDrCurve->IsArcType();
	double dThetaSpec	= pDrCurve->GetTheta_S();
	double 	dTheta		= dThetaSpec;
	BOOL bClosed		= pDrCurve->IsClosed_S();	
	//////////////////////////////
	// Content of INodeList:	//
	//		1. NID_I	NODE	//
	//		2. NID_CC	CNODE	//
	//		3. NID_J	NODE	//
	///////////////////////////////////////
    ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pWORLD pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCMC_Circle::SetAdditionalInfo4");
		return -1;
	}
	////////////////////////////////////////////// Set Data
	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius, dThetaArc;
	Calc_CRNPhifromCC(pData, &Center, &Radius, &Normal,&dThetaArc);
	////////////////////////////////////// if Closed, set angle to 360
	BOOL bExtra = FALSE;
	////////////////////
	if(bClosed)
		dTheta = 360.;
	else
	{
		if(!bArc)
		{
			if(dTheta<0.)dTheta = 0;
			if(dTheta>360.)dTheta = 360.;
			if(dTheta<dThetaArc)
				dTheta = dThetaArc;
			else
			if(dTheta<360.)
				bExtra = TRUE;
		}
		else
			dTheta = dThetaArc;
	}
	bClosed = (dTheta == 360.)?TRUE:FALSE;
	/////////////////////////////////////////// Override
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetTheta_S(dTheta);		
	pDrCurve->SetClosed_S(bClosed);
	/////////////////////////////////////////////////////////////// Ex_NodeList
	WORLD Ne;
	//////////////////////////////////////////////////////// Ni,i = 1,3 (NOT CC)
	for(int k=0;k<nData;k+2)
		m_DataList_Ex.AddTail(pData[k]);
	//////////////////////////////////////////////////////// Nextra
	if(bExtra)
	{
		double dThetaEx = dTheta - dThetaArc; 
		GetAPtByRotation(pData+2,Center,Normal,dThetaEx,&Ne);
		m_DataList_Ex.AddTail(Ne);
	}
	////////////////
	delete [] pData;
	/////////////////////////////////////////////////////////////// Bezier
	BezierInfo(pDrCurve);
	/////////
	return 0;
}
 
int CMC_Circle::CalcAdditionalInfo_2CN_TI_R(CDrCurve* pDrCurve,BOOL bFinal)
{
	BOOL bArc			= pDrCurve->IsArcType();
	double dThetaSpec	= pDrCurve->GetTheta_S();
	double 	dTheta		= dThetaSpec;
	BOOL bClosed		= pDrCurve->IsClosed_S();
	/////////////
	double Radius		= pDrCurve->GetRadius_S();
	//////////////////////////////
	// Content of INodeList:	//
	//		1. CNID_A	CNODE	//
	//		2. NID_TI	CNODE	//
	//		3. CNID_B	CNODE	//
	///////////////////////////////////////
	pWORLD pDat_Ex 			= NULL;
    ///////////////////////////////////////////////////////// Memory
	int nData = pDrCurve->GetMaxINodes_S(); 
	pWORLD pData 	= new WORLD[nData];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCMC_Circle::SetAdditionalInfo3");
		return -1;
	}
	////////////////////////////////////////////// Set Data
	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	if(SetUpINodes(pINodeList,pData,nData)<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal, Ni, Nj;
	double dThetaArc;
	Calc_NiNj_CRNPhi(pData, &Ni, &Nj, &Center, &Normal, &Radius, &dThetaArc);
	////////////////////////////////////// if Closed, set angle to 360
	BOOL bExtra = FALSE;
	////////////////////
	if(bClosed)
		dTheta = 360.;
	else
	{
		if(!bArc)
		{
			if(dTheta<0.)dTheta = 0;
			if(dTheta>360.)dTheta = 360.;
			if(dTheta<dThetaArc)
				dTheta = dThetaArc;
			else
			if(dTheta<360.)
				bExtra = TRUE;
		}
		else
			dTheta = dThetaArc;
	}
	bClosed = (dTheta == 360.)?TRUE:FALSE;
	/////////////////////////////////////////// Override
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetTheta_S(dTheta);		
	pDrCurve->SetClosed_S(bClosed);
	/////////////////////////////////////////////////////////////// Ex_NodeList
	WORLD Ne;
	//////////////////////////////////////////////////////// Ni,Nj
	m_DataList_Ex.AddTail(Ni);
	m_DataList_Ex.AddTail(Nj);
	//////////////////////////////////////////////////////// Nextra
	if(bExtra)
	{
		double dThetaEx = dTheta - dThetaArc; 
		GetAPtByRotation(&Nj,Center,Normal,dThetaEx,&Ne);
		m_DataList_Ex.AddTail(Ne);
	}
	////////////////
	delete [] pData;
	/////////////////////////////////////////////////////////////// Bezier
	BezierInfo(pDrCurve);
	/////////
	return 0;
}

int CMC_Circle::BezierInfo(CDrCurve* pCurve) 
{
	ASSERT(!m_DataList_Ex.IsEmpty());
	int nCount = m_DataList_Ex.GetCount();	// # of Extended Data
	////////////////////////////////////////////////////////// Bezier Info
	CList<int,int>			BSegList;	// Bezier Segments 
	CList<int,int>			ElemList;	// Output for each Segment
	CList<double,double>	AngList;	// Angle for each Segment
	/////////////////////////////////
	pINT	pBSeg = NULL;
	pINT	pOSeg = NULL;
	pDOUBLE pODis = NULL;
	int		nBSegTot	= 0;
	int		nElemTot	= 0;
	double	dAnglTot	= 0;
	///////////////////////////////////////////////////////////// Segs & Mesh
	int nLoop		= (pCurve->IsClosed_S())?nCount:nCount-1;
	WORLD Center	= pCurve->GetCenter_S();
	/////////////
	POSITION	pos;
	WORLD		Ni,Nj;
	int			nElems;
	BOOL		bUniform;
	////////////////////////
	for(int i=0;i<nLoop;i++)
	{
		////////////
		pos			= m_DataList_Ex.FindIndex(i);
		Ni			= m_DataList_Ex.GetAt(pos); 
		pos			= m_DataList_Ex.FindIndex((i+1)%nCount);
		Nj			= m_DataList_Ex.GetAt(pos);
		pos			= pCurve->GetElperSegList_S()->FindIndex(i);	// save for later editing etc
		nElems		= pCurve->GetElperSegList_S()->GetAt(pos);
		bUniform	= pCurve->IsUniform_S();
		// get segs,mesh
		int nBSegs = BezierSeg_N_Mesh(pCurve,Ni,Nj,Center,pOSeg,pODis,nElems,bUniform);
		// update info 
		BezierSeg_N_Mesh_Update(BSegList,ElemList,AngList,pOSeg,pODis,nBSegs,nBSegTot); 
	}
	////////////////////////////////////////////////////////////// 
	BezierSeg_N_Mesh_Done(BSegList,ElemList,AngList,pBSeg,pOSeg,pODis,
							nBSegTot,nElemTot,dAnglTot);
	//////////////////////////////////////////////////// Check
	// ASSERT (nBSegTot == ??,nElemTot == ??,nAnglTot == ??)
	////////////////////////////////////////////////////////////// Set Control Info
	SetBezierControlInfo(pCurve,nLoop,pBSeg,pOSeg,pODis,nBSegTot,nElemTot,dAnglTot);
	/////////
	return 0;
}

int CMC_Circle::BezierSeg_N_Mesh_Done(CList<int,int>& BSegList,CList<int,int>& ElemList,
									  CList<double,double>& AngList,
										pINT &pBSeg,pINT &pOSeg,pDOUBLE &pODis,
										int& nBSegTot,int& nElemTot,double& dAnglTot) 
{
	m_pDrCurve->GetElperSegList_S()->RemoveAll();	// to be reset based on nBezSegs
	///////////////////////////////////////////
	POSITION posI;
	////////////////////////////////////////// Finally put back in Array
	int k;
	//////////////////////////////////////////////////////////////// DataPair Segs
	int nPairs = BSegList.GetCount();
	pBSeg = new int[nPairs];	//	Bezier Segments( per Data pair) array
									//	needed later in b0 & b2 creation
	//////////////////////////////
	if(!pBSeg)
		return -1;
	///////////////////////////////
	int nBSegTotal = 0;
	k = -1;
	for (posI = BSegList.GetHeadPosition( );posI !=NULL;)
	{
		k++;
		pBSeg[k] = BSegList.GetNext(posI); 
		////////////////////////////////// Totals
		nBSegTotal += pBSeg[k]; 
	}
	///////////////////// dont need
	BSegList.RemoveAll(); 
	////////////////////////////////
	if(nBSegTotal != nBSegTot)
	{
		AfxMessageBox("ERROR:\nCMC_Circle::BezierSeg_N_Mesh_Final\nnBSegTotal != nBSegTot");
		return -1;
	}
	////////////////////////////////////////////////////////////////
	int nBSegTotalA = AngList.GetCount();
	if(nBSegTotal != nBSegTotalA)
	{
		AfxMessageBox(
			"ERROR:\nCMC_Circle::BezierSeg_N_Mesh_Final\nnBSegTotal != nBSegTotalA");
		return -1;
	}
	////////////////////////////////////////////////////////////////
	pOSeg = new int[nBSegTotal];
	pODis = new double[nBSegTotal];
	//////////////////////////////
	if(!pOSeg || !pODis)
		return -1;
	//////////////////////////////////////////////////////////////// Elems
	k = -1;
	for (posI = ElemList.GetHeadPosition( );posI !=NULL;)
	{
		k++;
		pOSeg[k] = ElemList.GetNext(posI);
		////////////////////////////////// Reset ElperSegList
		m_pDrCurve->GetElperSegList_S()->AddTail(pOSeg[k]);
		////////////////////////////////// Totals
		nElemTot += pOSeg[k]; 
	}
	///////////////////// dont need
	ElemList.RemoveAll(); 
	//////////////////////////////////////////////////////////////// Angles
	k = -1;
	for (posI = AngList.GetHeadPosition( );posI !=NULL;)
	{
		k++;
		pODis[k] = AngList.GetNext(posI);
		////////////////////////////////// Totals
		dAnglTot += pODis[k]; 
	}
	///////////////////// dont need
	AngList.RemoveAll();
	/////////
	return 0;
}

int CMC_Circle::BezierSeg_N_Mesh_Update(CList<int,int>& BSegList,CList<int,int>& ElemList,
										CList<double,double>& AngList,
										pINT &pOSeg,pDOUBLE &pODis, int nBSegs,int& nBSegTot) 
{

	////////////////////////////////////////// Bezier Segments
	BSegList.AddTail(nBSegs);
	nBSegTot += nBSegs;
	////////////////////////////////////////// Update
	if(!pOSeg || !pODis)
		return -1;
	////////////////////
	for(int k=0;k<nBSegs;k++)
	{
		ElemList.AddTail(pOSeg[k]);
		AngList.AddTail(pODis[k]);
	}
	////////////////////////////// prepare
	delete [] pOSeg;
	pOSeg = NULL;
	delete [] pODis;
	pODis = NULL;
	/////////////
	return 0;
}

int CMC_Circle::BezierSeg_N_Mesh(CDrCurve* pCurve,WORLD& wNa,WORLD& wNb,WORLD& wNc,
						pINT &pOSeg,pDOUBLE &pODis, int nElems,BOOL bUniform) 
{
	///////////////////////////////////////// save
	// if
	//		 Uniform:
	//			 	make As Many Segment of Control Nodes
	//				as Close to SegAng(Default=120) with total of m_nMesh Output segment
	//				in all of them i.e.,
	//				nSegs = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				variable Angles are stored in m_pODis;
	//				m_pONum containing Number of Mesh for each CurveSeg
	//		 NonUniform:
	//			 	make m_nMesh Segments of Control Nodes
	//				with 1 Output segment in each, i.e.,
	//				m_nMesh many CurveSeg in S-direction
	//				nSegs = m_nMesh = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				Total Angle is stored in m_pODis[0];
	//				m_pONum[0] containing Number of Mesh for the Patch
	/////////////////////////////////////////////////////////////// Current Central Angle
	C3DMath Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	WORLD wLocA		= wNa;	
	WORLD wLocB		= wNb;	
	WORLD Center	= wNc;
	double dAng;
	///////////////////////////////////// if Closed & CIRCLE_BY_ROT
	if(Math3D.AreSame_WORLD(&wNb, &wNa,pHitNet->GetDblRatio()))
		dAng = 360.;
	else
	{
		///////////////////////////////////////////////////////////////
		WORLD ca,cb;
		Math3D.Sub3DPts(&Center,&wLocA,&ca);
		Math3D.Sub3DPts(&Center,&wLocB,&cb);
		/////////////////////////////////////////////////
		double dot		= Math3D.Dot3DPts(&ca,&cb);
		double dLenCA	= Math3D.Len3DPts(&ca);
		double dLenCB	= Math3D.Len3DPts(&cb);
		dAng			= acos(dot/dLenCA/dLenCB) * (45./atan(1.0) );
		///////////////////////////////////////////////// Check for right angle
		// dot product may pick up image pt. of the
		// actual pt. wrt CA
		WORLD pt;
		WORLD Normal	= pCurve->GetNormal_S();
		///////////////////////////////////////
		// Generate a Pt. by Rotation
		GetAPtByRotation(&wNa, wNc, Normal, dAng, &pt);
		if(!Math3D.AreSame_WORLD(&wNb, &pt,pHitNet->GetDblRatio()))
			dAng = 360.- dAng;
	}
	///////////////////////////////////////////////////////////////////// do it
	double dRatio	= pCurve->GetRatio_S();
	/////////////
	if(bUniform)
		return BezierSeg_N_Mesh_Uniform(pCurve,pOSeg,pODis,dAng,nElems);
	else
		return BezierSeg_N_Mesh_NonUniform(pCurve,pOSeg,pODis,dAng,dRatio,nElems);
	////////
}

int CMC_Circle::BezierSeg_N_Mesh_Uniform(CDrCurve* pCurve,pINT &pOSeg,pDOUBLE &pODis,
															double dAng,int nElems)
{
	double Epsilon = .00000001;
	// Return:  # of Bezier Curve Segments
	///////////////////////////////////////// save
	// if
	//		 Uniform:
	//			 	make As Many Segment of Control Nodes
	//				as Close to SegAng(Default=120) with total of m_nMesh Output segment
	//				in all of them i.e.,
	//				nSegs = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				variable Angles are stored in m_pODis;
	//				m_pONum containing Number of Mesh for each CurveSeg
	/////////////////////////////////////////////////////////////////////	
	double dMaxAng	= pCurve->GetSegAngle_S();
	//////////////////////////////////////////////////////// Uniform
	int nSegs = -1; // error
	// Max Angle for each Patch Segment = 120;
	// for stability
	////////////////////////////////////////// <=m_SegAngle:One Curve 
	if(dAng<= dMaxAng)
	{
		nSegs = 1;
		//////////////////////////// Memory
		pOSeg = new int[nSegs];
		pODis = new double[nSegs];
		//////////////////////////// save
		pOSeg[0] = nElems;
		pODis[0] = dAng;
		/////////////////////
	}
	else
	{
		int		nTimes,nMesh,nRem,i;
		double	dAngInc,dSegAng;
		////////////////
		dAngInc	= dAng/nElems; // assume dAngInc ALWAYS <=120
		if(dAngInc>120)
		{
			AfxMessageBox("Error:\nToo Few Number of Elements!");
			/////////////////////
			return -1;
		}
		nTimes	= (int)(dMaxAng/dAngInc + Epsilon);	// might create precision problem: a/a = 0
		if(nTimes<1)
			nTimes = 1;
		dSegAng	= nTimes * dAngInc;	// get biggest possible angle<=dMaxAng
		nSegs	= (int)(dAng/dSegAng + Epsilon);
		nMesh	= nSegs*nTimes;
		nRem	= nElems%nMesh;
		////
		if(nRem)
			nSegs++;
		//////////////////////////// Memory
		pOSeg = new int[nSegs];
		pODis = new double[nSegs];
		//////////////////////////// save
		for(i=0;i<nSegs;i++)
		{
			///////////////
			pOSeg[i] = nTimes;
			pODis[i] = dSegAng;
			/////////////////////
		}
		//////////////////////////// adjust  the Last one
		if(nRem)
		{
			int nSeg1 = nSegs -1;
			/////////////////////
			pOSeg[nSeg1] = nElems	- nTimes * nSeg1;
			pODis[nSeg1] = dAng		- dSegAng* nSeg1;
			/////////////////////
		}
	}
	/////////////
	return nSegs;
}

int CMC_Circle::BezierSeg_N_Mesh_NonUniform(CDrCurve* pCurve,pINT &pOSeg,pDOUBLE &pODis,
							double dAng,double dRatio,int nElems)
{
	///////////////////////////////////////
	//		 NonUniform:
	//			 	make m_nMesh Segments of Control Nodes
	//				with 1 Output segment in each, i.e.,
	//				m_nMesh many CurveSeg in S-direction
	//				nSegs = m_nMesh = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				Total Angle is stored in m_pODis[0];
	//				m_pONum[0] containing Number of Mesh for the Patch
	//////////////////////////////////////////////////////// NonUniform
	int nSegs = nElems;
	//////////////////////////// Memory
	pOSeg = new int[nSegs];
	pODis = new double[nSegs];
	/////////////////////////////////////////////////////////
	// NOTE:	allows Unequal Generation
	//		# of Segments = n + 1			= nSegs 
	//		SPACEs between pts. are:
	//			x, x+a, x+2a, x+3a, ..., x+na
	//		with
	//			x = (2*theta)/(segs*(ratio+1))
	//			a = (x*(ratio-1))/(segs-1)
	//
	//////////////////////////////////////////////////////////
	double x	= (2 * dAng)/(nSegs * (dRatio + 1));
	double a	= (nSegs == 1)?0.:(x * (dRatio-1))/(nSegs-1);
	//////////////////////////// save
	int i;
	//////
	for (i=0;i<nSegs;i++)
	{
		pOSeg[i] = 1;	// one Element in each
		double angle = x + i * a;
		/////////////////////////
		if(angle>120)
		{
			AfxMessageBox("Error:\nToo Few Number of Elements!");
			/////////////////////
			return -1;
		}
		///////////////////
		pODis[i] = angle;
		///////////////////
	}
	/////////////
	return nSegs;
}

int CMC_Circle::SetBezierControlInfo(CDrCurve* pDrObject,int nBSeg,
							pINT &pBSeg,pINT &pOSeg,pDOUBLE &pODis,
							int nBSegTot,int nElemTot,double dAnglTot)
{
	int nOrder = pDrObject->GetOrder_S();
	BOOL bClosed = pDrObject->IsClosed_S();
	//////////////////////////////////////////////////////////////////////////
	pDrObject->SetMaxOutSeg_S(nElemTot);		// Total Number of Output Segments
//	pDrObject->SetSegmentCount_S(nBSegTot); 	// # of Curves ( Bezier Segs)
	pDrObject->SetMaxBezSegments_S(nBSegTot); 	// # of Curves ( Bezier Segs)
	pDrObject->SetNum_tPointer_S(pOSeg);		// Number of Outputs for
													// each Curve Segment
	pDrObject->SetNum_tPointer_Ex_S(pOSeg);		// Number of Outputs for
													// each Curve Segment
	//////////////////////////////////////////////////////////////////////////
	double dAng1			= 0;		
	double dAng2			= pDrObject->GetTheta_S();		
	///////////////////////////////////////// Check and correct last angle
	double dAngGiven = dAng2 - dAng1;
	double dAnglast;
	//////
	if(dAnglTot != dAngGiven)
	{
		dAnglast		= pODis[nBSegTot];
		dAnglast		= dAngGiven - (dAnglTot - dAnglast);
		//////////////////////////////////////////////// update
		pODis[nBSegTot] = dAnglast;
	}
	pDrObject->SetDis_AngPointer_S(pODis);		// Number of Angles for
													// Bezier Control Pts. Generation
	//////////////////////////////////////////////////////////////////////////
	pDrObject->SetnBSeg_Ex_S(nBSeg);			// Number of pairs of Data
	pDrObject->SetBSegPointer_Ex_S(pBSeg);		// Number of Bezier Segs for
													// each pair of Data
   ////////////////////////////////////////////////////// Total Evaluation Pts
	int nOut = nElemTot + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////
	int nCon_BZ	= (nOrder - 1) * nBSegTot + 1;	// (k-1) * L + 1 , Open
	if(bClosed)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	////////////////////////////////////////////////////////////////////// Mesh(Output)
	int nData	= (bClosed)?nBSegTot:nBSegTot + 1;
	//////////////////////////////////////////////// Update	 
	pDrObject->SetData_S(nData);		// Generated: # of Data
	pDrObject->SetData_Ex_S(nData);		// Adjusted# of Data for Conics(Circle) 
	////////////////////////////
	int		nControls,nCurveSeg,nMaxDistinct,nMaxTotal;
	///////////////////////////////////////////////////
	nControls 	= nData + nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	nCurveSeg 	= nData - 1;					// L
	nMaxDistinct 	= nData;
	nMaxTotal		= nData + (2 * nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	if(bClosed)
	{
		nCurveSeg++;
		nMaxDistinct++;
		nMaxTotal++;
	}
    ////////////////////
	pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	pDrObject->SetnCon_BS_S(nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(nMaxDistinct);
	pDrObject->SetnMKnots_S(nMaxTotal);
	//////////////////
	return 0;
}
///////////////////////////////////////////////////////////////////////////
int CMC_Circle::GoDoIt(CDrCurve* pCurve,BOOL bFinal,CIRCLETYPE nType)  
{
	m_pDrCurve = pCurve;
	/////////////////////////////////////////////////// Additional Info
	int nResult = CalcAdditionalInfo(pCurve,bFinal,nType);
	ASSERT(nResult>=0);
	///
	GoDoIt(pCurve,bFinal); 
	/////////////////////////////////////////////////// Change Center Coords
	CDrNode* pNode = (CDrNode*)(pCurve->GetElemList()->GetObject(0)); //Center Node
	pNode->SetLocalPos(m_Center_S);
	(pNode->GetNodeCard())->x = (long)m_Center_S.x;
	(pNode->GetNodeCard())->y = (long)m_Center_S.y;
	(pNode->GetNodeCard())->z = (long)m_Center_S.z;
	/////////////////////////////////////////////////// Change Last Control Coords
	if(!m_bArc && !m_bClosed_S) 
	{
		WORLD LocalPos = *(((CDrNode*)m_pCNodeList->GetTail())->GetLocalPos());
		/////////////
		pNode = (CDrNode*)(pCurve->GetVNodeList()->GetObject(0));
		pNode->SetLocalPos(LocalPos);
		(pNode->GetNodeCard())->x = (long)LocalPos.x;
		(pNode->GetNodeCard())->y = (long)LocalPos.y;
		(pNode->GetNodeCard())->z = (long)LocalPos.z;
		////////////////////////////////////////////
	}
	///////////
	return 0;

}

int CMC_Circle::GoDoIt(CDrCurve* pCurve,BOOL bFinal)  
{
	///////////////////////////////////////////////////
	m_CurveType_S	= CP_CIRCLE;
	m_nOrder_S		= 3;
	///////////////////////////////
	m_pDrCurve 			= pCurve;
	////////////////////////////////// tired of typing!
	CDrCurve* pDrCurve	= m_pDrCurve;
	///////////////////////////////////////////////////// stuff from getinfo
	m_nInputType		= pDrCurve->GetInputType();
	///////////////////////////////////////////////
	m_pFromIDNode 		= pDrCurve->GetFromIDNode_S();
	m_pToIDNode			= pDrCurve->GetToIDNode_S();
	m_nMaxCurveINodes_S	= pDrCurve->GetMaxINodes_S();	//
	///
	m_bAxis				= pDrCurve->IsAxisInput();
	m_nAxis				= pDrCurve->GetAxis();
	m_bNegative			= pDrCurve->IsNegative();
	m_Center_S			= pDrCurve->GetCenter_S();
	m_Radius_S			= pDrCurve->GetRadius_S();
	m_vAxis_S			= pDrCurve->GetNormal_S();
	m_FromPt_S			= pDrCurve->GetCenter_S();
	/////////////////////////////////////////////////////////////////////////////////
	m_nBSeg_Ex_S		= pDrCurve->GetnBSeg_Ex_S();// Number of pairs of Data
	m_pBSeg_Ex_S		= pDrCurve->GetBSegPointer_Ex_S();// Number of Bezier Segs for
													// each pair of Data
	//////////////////////////////////////////////////////
	m_pNum_t_S			= pDrCurve->GetNum_tPointer_S();
	m_pNum_t_Ex_S		= pDrCurve->GetNum_tPointer_Ex_S();
	///////////////////////////////////// Angle Distribution
	m_pDisAng_S			= pDrCurve->GetDis_AngPointer_S();	// Distribution of angles 
	m_dAng1_S			= 0;		
	m_dAng2_S			= pDrCurve->GetTheta_S();		
	////////////////////////////////////////////////
//	m_nSegs_S			= pDrCurve->GetSegmentCount_S();	// # of Bezier Curvees 
	m_nSegs_S			= pDrCurve->GetMaxBezSegments_S();	// # of Bezier Curvees 
									// in Rotation dirn
	////////////////////////////////////////////////
	m_Ratio_S			= pDrCurve->GetRatio_S();
	m_bUnifOT_S			= pDrCurve->IsUniform_S();
	m_nOut_S			= pDrCurve->GetMaxOutPts_S();;
	m_nOrder_S			= pDrCurve->GetOrder_S();
	m_CurveType_S		= pDrCurve->GetCurveType_S();;
	m_nDim_S			= pDrCurve->GetnDim_S();
	m_bClosed_S			= pDrCurve->IsClosed_S();					// for Extrusion
	///////////////////////////////////////// Bezier Quadratic
	m_nOut_SCon			= 2 * m_nSegs_S + 1;	// # of  Bezier Controls in S-dir
	if(m_bClosed_S)
			m_nOut_SCon--;
	/////////////////////////////////////
	m_nSegs_SCon		= m_nOut_SCon - 1;
	m_nMaxCurveCNodes_S = m_nOut_SCon;
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	InterPolate(bFinal);
	////////////////////////
	m_bFinal = bFinal;
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	/////////////////////
	return 0;
}			

int CMC_Circle::SetMemory()
{
    
	//////////////////////////////////////////////////////////////////////// Setup Data
	int nData	= m_pDrCurve->GetData_Ex_S();
	m_pData		= new WORLD[nData];
	if(!m_pData)
	{
			AfxMessageBox("ERROR:\nCMC_Circle::SetMemory\nm_pData -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMC_Circle::GenerateBezier_b0s_b2s(CDrCurve* pCurve)
{
	//b0s & b2s are input data for IN_Circle Phase
	////////////////////////////////////////////// Get Info
	int nDataEx	= m_DataList_Ex.GetCount();
	pWORLD pData	= new WORLD[nDataEx];
	if( !pData )
	{
		AfxMessageBox("CMC_Circle::GenerateBezier_b0s_b2s\npData Mem Failure!");
		return -1;
	}
	////////////////////////////////////////////// fillup
//	m_nData_S = nDataEx; 
	for(int k=0;k<nDataEx;k++)
	{
		POSITION pos	= m_DataList_Ex.FindIndex(k);
		pData[k]		= m_DataList_Ex.GetAt(pos);
	}	
	////////////////////////////////////////////// Save CurveInfo
	m_nOut				= ((long)m_nOut_S);				
	m_nOutCon			= ((long)m_nOut_SCon);				
	m_nMaxCurveCNodes_S	= (int)m_nOutCon;
	////////////////////////////////////////////// generate Bezier b0s & b2s
//	int nBSegTot = pCurve->GetSegmentCount_S(); 	// # of Curves ( Bezier Segs)
	int nBSegTot = pCurve->GetMaxBezSegments_S(); 	// # of Curves ( Bezier Segs)
	///	
	int nOut = (m_bClosed_S)?nBSegTot:nBSegTot+1;	// b0s & b2s
	int nOutActual	= 0;
	/////////
	nOutActual	= GetBezEndPtsbyRotation
			(
				nDataEx,			//	# of extended input Data (m_DataList_Ex Count)
				m_Center_S,
				m_vAxis_S,			//	unit rotation vector (direction)
				m_bClosed_S,
				m_pDisAng_S,		//	Angle Distribution for each Bez Curve in degrees
				nBSegTot,			//	Total # Bezier Curve Segs
				m_pBSeg_Ex_S,		//	Bezier Segments( per Data pair) array
				pData,				//	input extended data array
				m_pData				//	Output ControlPts: b0s & b2s
			);	  
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		m_nData_S			= m_pDrCurve->GetData_Ex_S();
		/////////////////////////////////////////////////
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		int j,k;
		//////////
		sprintf(buf,"m_pData\nCMC_Circle::PostInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j = sprintf(buf,"m_pData[%d]\n      X             Y            Z\n",m_nData_S);
		for(k=0;k<m_nData_S;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n", k,
		   							m_pData[k].x,m_pData[k].y,m_pData[k].z );
		}
		if(j>BUFF_SIZE)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
		return 0;
}

int CMC_Circle::GetBezEndPtsbyRotation
	(
		int		nData,		//	# of Extended Input Data 
		WORLD	Center,
		WORLD	Axis,		//	unit direction vector of rotation axis
		BOOL	bClosed,
		pDOUBLE	pDis,		//	Angle Distribution for each Bez Patch in degrees
		int		nBSegTot,	//	Total # Bezier Curve Segs
		pINT	pSegBz,		//	Bezier Segments( per Data pair) array
		pWORLD	pData,		//	input extended data array
		pWORLD	pOut		//	Output Pts array
	)	  
//Return:Int	nOut	//	number of points emitted
{
	//////////////
	pWORLD	pRow,p;
	double	inc = 0;		// initialize
	int		nS,j;
	long	sizeRow;
	////////////////////////////////
	if(!pOut)
	{
		AfxMessageBox("Internal Problem:\nCMC_Circle::RotateCurve\npOut = NULL");
		return -1;
	}
	C3DMath		Math3D;
	///////////////////
	sizeRow		= sizeof(WORLD);
	nS 			= bClosed?nBSegTot:nBSegTot+1;		
	///////////////////
	pWORLD	pb0,pb2;
	WORLD	Tem;
	pWORLD	pTem = &Tem;
	////////////////////////////////////////////////////////////
	int nTimes	= bClosed?nData:nData-1;
	int nOutC	= bClosed?1:0;	// for starting or last b0
	///////////////////////////////////
	pRow = pOut;
	int kk = -1;
	for(int k=0;k<nTimes;k++)
	{
		Math3D.BlockCopy( (HUGEBLK)(pData+k), (HUGEBLK)pRow, sizeRow );
		p	= pRow;
		///////////////////
		pb0		= p - 1;
		//////////////////////////////////////////////// last segment b2 not done
		int nSegBz	= ( (k==nTimes-1)&& bClosed)?pSegBz[k]-1:pSegBz[k];
		///////////////////////////////////////////////////////////////
		for( j=0;j<nSegBz;j++ )	
		{
			kk++;
			///////////////////////////////////////////// Angle
			inc = pDis[kk];	// not cumulative
			//////////////////////////// Reset Start
			pb0++;
			pb2		= pb0 +	1;
			/////////////////////////////////////////// Generate a Pt. by Rotation
			GetAPtByRotation(pb0, Center, Axis, inc, pb2);
			////////
			nOutC++;	// Control Counter
		}
		/////////////////////
		pRow += nSegBz; 
	}
	//////////////////////////////////////////////// finish Up if not Closed
	if(!bClosed)
	{
		Math3D.BlockCopy( (HUGEBLK)(pData+nTimes), (HUGEBLK)pRow, sizeRow ); // last b2
		////////
		nOutC++;	// Control Counter
	}

//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // 
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
 	   ///////////////////////////////////////////
		sprintf(buf,"Leaving CMC_Circle::RotateCurve");
		AfxMessageBox(*str);
		///////////////////
		int j,k;
	    ///////////////////
		j = sprintf(buf,"pOut[%d][%d]: \n",nS,3);
		for(k=0;k<nS;k++)
		{
	   		j += sprintf( buf + j, "k=%2d  %7.2f %7.2f %7.2f \n",k, 
				pOut[k].x, pOut[k].y, pOut[k].z );
		} 
		AfxMessageBox(*str);
		///////////////////
		delete str;
	}		
#endif				
//////////////////////////////////////////////////////////////////
	if(nOutC != nS)
	{
		AfxMessageBox("Internal Problem:\nCMC_Circle::RotateCurve\nnOutC != nS");
		return -1;
	}
	else
		return nS;
	//////////////
}

int CMC_Circle::GetAPtByRotation(pWORLD pb0 , WORLD AxisPt, WORLD Normal, 
								double dAng, pWORLD pb2)
{

/*************************************************************
//	FOLLOWING FORMULA IS NOT BEING USED
//	r = (r dot n)n + [r - (r dot n)n] cos(theta)
//				   + [n cross (r - (r dot n)n)] sin(theta)
//	r = (r dot n)n (1 - cos(theta)) + r cos(theta)
//				   + [n cross r] sin(theta)
//	indicial:
//	r[i] = (r dot n)n[i] (1 - cos(theta)) + r[i] cos(theta)
//				   + (e[i][j][k].n[j].r[k]) sin(theta)
***************************************************************/
	WORLD b2Local;
	pWORLD pb2Local = &b2Local;
	///////////////////////////	
	pb2Local->x	= pb0->x;
	pb2Local->y	= pb0->y;
	pb2Local->z	= pb0->z;
	////////////////////////////////////////////////////////////////// 
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////// Translate AxisPt & DOld to Origin
	XForm.Translate(pRot, -AxisPt.x, -AxisPt.y, -AxisPt.z, XF_REPLACE);	
	//////////////////////////////////////// 	
	XForm.Transform(pb2Local, pb2Local, pRot);	  
	//////////////////////////////////////////////////////////// Generatioe by rotation
	WORLD Origin = {0.0,0.0,0.0};
	double rAng = atan(1.0) * dAng/45.; // radian
	////////////
	Math3D.GetIdentityMATRIX(pRot);
	XForm.RotateAboutLineMATRIX(pRot, &Origin, &Normal,rAng,XF_REPLACE);
	XForm.Transform(pb2Local, pb2Local, pRot);
	//////////////////////////////////////////////////////////// Translate Data Back: New Pt
	Math3D.GetIdentityMATRIX(pRot);
	XForm.Translate(pRot, AxisPt.x, AxisPt.y, AxisPt.z, XF_REPLACE);
	XForm.Transform(pb2Local, pb2Local, pRot);
	/////////////////////	
	pb2->x	= pb2Local->x;
	pb2->y	= pb2Local->y;
	pb2->z	= pb2Local->z;
	///////////////////
	return 0;
}	

int CMC_Circle::InterPolate(BOOL bFinal)
{
	CIn_Circle* pIn_Conics = &m_In_Conics;
	////////////////////////////////////////////// Set Memory
	if(SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Extended Data
	//////////////////////////// Bezier B0s & b2s
	if(GenerateBezier_b0s_b2s(m_pDrCurve)<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(PrepInterpolation()<0)
		return -1;
	////////////////////////////////////////////// Prepare In-between Bezier Info
	if(m_In_Conics.Prepare()<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(m_In_Conics.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(PostInterpolation(bFinal)<0)
		return -1;
	///////////////////////
	return 0; 
}
			
int CMC_Circle::PrepInterpolation()
{
	CIn_Circle* pIn_Circle = &m_In_Conics;
	///////////////////////////////////////////////////////// Get Adjusted Number of Data
	int CSeg_DT	= m_pDrCurve->GetData_Ex_S() - 1;				// L
	if(m_bClosed_S)
		CSeg_DT++;
    /////////////
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_Cur_I::Circle_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,		"nDat_Ex\t = %d\n",m_pDrCurve->GetData_Ex_S());
		j += sprintf( buf + j, 	"nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, 	"bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, 	"Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, 	"CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, 	"nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, 	"nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
		j += sprintf( buf + j, 	"Theta\t = %f\n",m_pDrCurve->GetTheta_S());
		if(j>500)
		{
			 sprintf( buf, "Increase buffer to %d",j);
			 AfxMessageBox(*str);
			 str->ReleaseBuffer();
			 delete str;
			 return -1;
		}	 
		AfxMessageBox(*str);
		str->ReleaseBuffer();
		delete str;
    	///////////////////
    }
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pIn_Circle->SetnData_S(m_pDrCurve->GetData_Ex_S());	// Adjusted# of Data for Conics(Circle) 
	pIn_Circle->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pIn_Circle->SetbClosed_S(m_pDrCurve->IsClosed_S());
	//////////////////////////////////////////////////////////
	pIn_Circle->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pIn_Circle->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pIn_Circle->SetCenter(m_pDrCurve->GetCenter_S());				// k -1
	pIn_Circle->SetRadius(m_pDrCurve->GetRadius_S());				// k -1
	pIn_Circle->SetNormal(m_pDrCurve->GetNormal_S());				// k -1
	
//	pIn_Circle->SetnSeg_BS_S(nSeg_BS);
	pIn_Circle->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pIn_Circle->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes
	////////////////////////////////////////////// Send Memory
	pIn_Circle->SetpData(m_pData);	// Only:b0s & b2s(already generated)
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMC_Circle::PostInterpolation(BOOL bFinal)
{

	CIn_Circle* pIn_Conics	= &m_In_Conics;
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpCon_BS_S(m_pWts_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		CurveID;
	int			nChLen;
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data/Memory
	m_pWts_BS_S			= pIn_Conics->GetpWts_BS_S();
	m_pWts_BZ_S			= pIn_Conics->GetpWts_BZ_S();
	m_pCon_BS_S			= pIn_Conics->GetpCon_BS_S();
	m_pCon_BZ_S			= pIn_Conics->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes_S	= m_pDrCurve->GetnCon_BZ_S();
	m_nCon_BZ_S			= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	/////////////////////////////////////////////////////////////// save memory				
	m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S);	// Rational Weights
	m_bArc = m_pDrCurve->IsArcType();
	/////////////////////////////////
	ASSERT(m_pCNodeList->IsEmpty());
	///
	for (s = 0; s<m_nMaxCurveCNodes_S; s++)
	{
		////////////////////////////////////
		j = t*m_nCon_BZ_S + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		////////////////////////////////////////////////////////////////////////// CREATE	
//		Nid		= CurveID.Left(nChLen);
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d%d",CurveID,s,t);
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		//////////////////////////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList
		//////////
		if(bFinal)
		{
			//011199: DONOT Reciprocate:PRIVATE
			//////////////////////////////////////////// if New Node Reciprocate
//			if(pAddNode->GetObjectID() == Nid)
//			{
				//////////////////////////////////////// Reciprocate
//				int index = pAddNode->GetCurveList()->GetObjectIndex(m_pDrCurve);
//				if(index<0) // not in the list
//					pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
				////////
//			}
		}
		////////
	}
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pWts_BS_S)
	{
		delete [] m_pWts_BS_S;
		m_pWts_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
		m_pOut 		= NULL;
	}	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}
	/////////////////////////////////////////////////////////////////////	
	return 0;
}
///////////////////////////////////////////////////////////////////////////
void CMC_Circle::UnitAxisFromEndNodes(pWORLD pNormal,WORLD& FromPt,WORLD& ToPt)
{
	///////////////
	C3DMath	Math3D;
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&ToPt, &FromPt, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;
}

int CMC_Circle::Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE pRadius,
												WORLD Normal,WORLD AxPt)
{
	//////////////////////////////
	// Content of Data:	//
	//		1. NID_I	NODE	//
	///////////////////////////////////////////////////////
	// given:
	//		Data	= a Pt. on the Current Circle
	//		Normal	= to the Plane of the circle (unit Normal)
	//		AxPt	= a Pt on the Normal
	// Now
	//		Center	= rAxPt + ((rData-rAxPt) dot N) N;
	//		Radius	= ||rCenter - rData||
	////////////////////////////////////////////////////////
	C3DMath	Math3D;
	WORLD	temp;
	//////////////////////////////////////////////////////// Center
	Math3D.Sub3DPts(pData,&AxPt,pCenter);
    Math3D.Set3DPts(&temp, Normal.x, Normal.y, Normal.z);
	Math3D.Scale3DPts(Math3D.Dot3DPts(pCenter,&Normal),&temp);
    Math3D.Set3DPts(pCenter, AxPt.x, AxPt.y, AxPt.z);
	Math3D.Add3DPts(pCenter, &temp, pCenter);			// Center
	//////////////////////////////////////////////////////// Radius
	Math3D.Sub3DPts(pCenter,pData,&temp);
	*pRadius = Math3D.Len3DPts(&temp);
	/////////
	return 0;

}

int CMC_Circle::Calc_C_R_Normal(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal)
{
	//////////////////////////////
	// Content of Data:	//
	//		1. NID_I	NODE	//
	//		2. NID_M	NODE	//
	//		3. NID_J	NODE	//
	///////////////////////////////////////
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////// Translate Center & DOld to Origin
	XForm.Translate(pRot, -Data[0].x, -Data[0].y, -Data[0].z, XF_REPLACE);	
	////////////
	WORLD a,b,c;
	XForm.Transform(&Data[0], &a, pRot);
	XForm.Transform(&Data[1], &b, pRot);
	XForm.Transform(&Data[2], &c, pRot);
	//////////////////////////////////////// midPts
	WORLD mid1,mid2;
	Math3D.Avg3DPts(&a, &b, &mid1);
	Math3D.Avg3DPts(&b, &c, &mid2);
	//////////////////////////////////////// Normal to plane of Circle
	WORLD wN;
	WORLD rab,rac;
	Math3D.Sub3DPts(&b, &a, &rab);
	Math3D.Sub3DPts(&c, &a, &rac);
	Math3D.Cross3DPts(&rab,&rac,&wN);
	///////////////////////////////// Save
	Normal->x = wN.x;
	Normal->y = wN.y;
	Normal->z = wN.z;
	//////////////////////// Normalize
	Math3D.Normalize(Normal,Normal);
	//////////////////////////////////////// Rotation Mat: wN->Z-axis/rab->Y-Axis
	Math3D.GetIdentityMATRIX(pRot);
	XForm.VRCtoWORLDRotationMATRIX(pRot,&wN,&rab);	
	//////////////////////////////////////// Change Effectively to 2D
	WORLD aBar,bBar,cBar,mid1Bar,mid2Bar;
	XForm.Transform(&a, &aBar, pRot);
	XForm.Transform(&b, &bBar, pRot);
	XForm.Transform(&c, &cBar, pRot);
	XForm.Transform(&mid1, &mid1Bar, pRot);
	XForm.Transform(&mid2, &mid2Bar, pRot);
	///////////////////////////////////////
	WORLD Center2;
	double m2Bar,b1Bar,b2Bar;
//	m1Bar = 0;										// 2D slope of ab chord bisector 
	if((cBar.y-bBar.y) == 0.)						// ab perpendicular to ac
	{
		Center2.x 	= mid2Bar.x;	 
		Center2.y 	= mid1Bar.y;
	}
	else
	{	 
		b1Bar 		= mid1Bar.y;						// 2D intercept of ab chord bisector
		m2Bar 		= (bBar.x-cBar.x)/(cBar.y-bBar.y);	// 2D Slope of bc chord bisector
		b2Bar 		= mid2Bar.y - m2Bar*mid2Bar.x;		// 2D intercept of ab chord bisector
		//////////////////////////////////////
		Center2.y 	= b1Bar;
		Center2.x 	= (Center2.y-b2Bar)/m2Bar;	 
	}
	/////////////////		 
	Center2.z 	= 0.;
	//////////////////////////////////////// Transform Center to 3D & Translate Back 
	Math3D.TransposeMATRIX(pRot);
	XForm.Transform(&Center2, Center, pRot);
	///////////////////////////////
	Math3D.GetIdentityMATRIX(pRot);
	XForm.Translate(pRot, Data[0].x, Data[0].y, Data[0].z, XF_REPLACE);	
	XForm.Transform(Center, &Center2, pRot);
	Center->x = Center2.x;
	Center->y = Center2.y;
	Center->z = Center2.z;
	//////////////////////////////////////// Radius
	WORLD rVec;
	Math3D.Sub3DPts(&Data[0], Center, &rVec);
	*Radius = sqrt(rVec.x*rVec.x + rVec.y*rVec.y +rVec.z*rVec.z);
	/////////
	return 0;

}

int CMC_Circle::Calc_CRNPhifromTI(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal,
										pDOUBLE Phi)
{
	//////////////////////////////
	// Content of Data:	//
	//		1. NID_I	NODE	//
	//		2. NID_TI	CNODE	//
	//		3. NID_J	NODE	//
	///////////////////////////////////////
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	////////////
	WORLD a,b,c;
	a = Data[0];	// NID_I
	b = Data[1];	// NID_TI
	c = Data[2];	// NID_J
	//////////////////////////////////////// midPt. of NID_I & NID_J
	WORLD mid;
	Math3D.Avg3DPts(&a, &c, &mid);
	//////////////////////////////////////// Normal to plane of Circle
	WORLD wN;
	WORLD rab,rac;
	Math3D.Sub3DPts(&b, &a, &rab);
	Math3D.Sub3DPts(&c, &a, &rac);
	Math3D.Cross3DPts(&rab,&rac,&wN);
	///////////////////////////////// Save
	Normal->x = wN.x;
	Normal->y = wN.y;
	Normal->z = wN.z;
	//////////////////////// Normalize
	Math3D.Normalize(Normal,Normal);
	/////////////////////////////////////// Radius & Central Angle 
	WORLD raMid;
	Math3D.Sub3DPts(&mid, &a, &raMid);
	double dLenMid	= Math3D.Len3DPts(&raMid); 
	double dLenA	= Math3D.Len3DPts(&rab); 
	double phi = acos( dLenMid/dLenA ); 
	/////////////////////////////// Radius
	*Radius = dLenA/tan(phi);
	/////////////////////////////// Central Angle 
	double pi180 = 180./acos(-1.0);
	*Phi = 2. * phi * pi180;
	/////////////////////////////////////// Center
	Math3D.Cross3DPts(&wN,&rab,Center);
	Math3D.Normalize(Center,Center);
	////////////////
	Center->x = a.x + (*Radius) * Center->x;
	Center->y = a.y + (*Radius) * Center->y;
	Center->z = a.z + (*Radius) * Center->z;
	/////////////////////////////////////// save
	return 0;

}

int CMC_Circle::Calc_CRNPhifromCC(pWORLD Data,pWORLD Center, pDOUBLE Radius, pWORLD Normal,
										pDOUBLE Phi)
{
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	// Content of Data:	//
	//		1. NID_I	NODE	//
	//		2. NID_CC	CNODE	//
	//		3. NID_J	NODE	//
	///////////////////////////////////////
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	////////////
	WORLD a,b,c;
	b = Data[0];	// NID_I
	a = Data[1];	// NID_CC
	c = Data[2];	// NID_J
	//////////////////////////////////////// Normal to plane of Circle
	WORLD wN;
	WORLD rab,rac;
	Math3D.Sub3DPts(&b, &a, &rab);
	Math3D.Sub3DPts(&c, &a, &rac);
	Math3D.Cross3DPts(&rab,&rac,&wN);
	//////////////////////// Normalize
	Math3D.Normalize(&wN,&wN);
	//////////////////// Save
	Normal->x = wN.x;
	Normal->y = wN.y;
	Normal->z = wN.z;
	/////////////////////////////////////// Radius & Central Angle 
	/////////////////////////////// Radius
	*Radius = Math3D.Len3DPts(&rab);
	/////////////////////////////// Central Angle 
	WORLD mid,ram;
	Math3D.Avg3DPts(&b, &c, &mid);
	Math3D.Sub3DPts(&mid, &a, &ram);
	double ramLen	= Math3D.Len3DPts(&ram);
	double phi		= acos(ramLen/(*Radius));
	double pi180 = 180./acos(-1.0);
	*Phi = 2. * phi * pi180;
	/////////////////////////////////////// Center
	*Center = a;
	///////////////////////////////////////////////// Check for Central angle
	// dot product may pick up image pt. of the
	// actual pt. wrt center & generating pt
	// Generate a Pt. by Rotation
	WORLD pt;
	/////////
	GetAPtByRotation(&Data[0], *Center, wN, *Phi, &pt);
	if(!Math3D.AreSame_WORLD(&Data[2], &pt,pHitNet->GetDblRatio()))
		*Phi = 360.- (*Phi);
	/////////////////
	return 0;

}

int CMC_Circle::Calc_NiNj_CRNPhi(pWORLD Data,pWORLD Ni, pWORLD Nj, pWORLD Center,
										pWORLD Normal, pDOUBLE pRadius, pDOUBLE Phi)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
	double dMapFactor   = pMapFactor->GetMapFactor();
	//////////////////////////////
	// Content of Data:	//
	//		1. CNID_A	CNODE	//
	//		2. CNID_TI	CNODE	//
	//		3. CNID_B	CNODE	//
	///////////////////////////////////////
	// ALSO COMPUTES NORMAL to CIRCLE PLANE
	///////////////
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	////////////
	WORLD a,b,c;
	a = Data[0];	// CNID_A
	b = Data[1];	// CNID_TI
	c = Data[2];	// CNID_B
	//////////////////////////////////////// Change Radius from Physical->World
	/////////////////////////////////////////// strip Scale Factor (World Coord)
	pObjectMgr->SCtoDS(pRadius);
    ////////////////////////////////
	(*pRadius) *= (dWorldBase/dMapFactor);	
	//////////////////////////////////////// Normal to plane of Circle
	WORLD wN;
	WORLD rba,rbc,biSector;
	Math3D.Sub3DPts(&a, &b, &rba);
	Math3D.Sub3DPts(&c, &b, &rbc);
	Math3D.Cross3DPts(&rbc,&rba,&wN);
	///////////////////////////////// Save
	Normal->x = wN.x;
	Normal->y = wN.y;
	Normal->z = wN.z;
	Math3D.Normalize(Normal,Normal);
	/////////////////////////////////////// Central Angle 
	Math3D.Sub3DPts(&rba, &rbc, &wN);
	double LenA = Math3D.Len3DPts(&rba);
	double LenB = Math3D.Len3DPts(&rbc);
	double LenC = Math3D.Len3DPts(&wN);
//	c^2 = a^2 + b^2 - 2 * a * b * cos(2*Si)
	double Si = .5 * acos( (LenA*LenA+LenB*LenB-LenC*LenC)/(2*LenA*LenB) ); // Half Angle at TI(radian)	
	/////////////////////////////// Central Angle 
	double pi180 = 180./acos(-1.0);
	double phi= 90. - Si * pi180;				// Degree
	*Phi = 2. * phi;
	/////////////////////////////////////// Center
	Math3D.Normalize(&rba,&rba);
	Math3D.Normalize(&rbc,&rbc);
	Math3D.Avg3DPts(&rba, &rbc, &biSector);
	Math3D.Normalize(&biSector,&biSector);
	double dLenbCC	= (*pRadius)/sin( Si );
	//////////////
	Center->x = b.x + dLenbCC * biSector.x;
	Center->y = b.y + dLenbCC * biSector.y;
	Center->z = b.z + dLenbCC * biSector.z;
	/////////////////////////////////////// Ni
	double dLenab	= (*pRadius)/tan( Si );
	/////////////
	Ni->x = b.x + dLenab * rba.x;
	Ni->y = b.y + dLenab * rba.y;
	Ni->z = b.z + dLenab * rba.z;
	/////////////////////////////////////// Nj
	Nj->x = b.x + dLenab * rbc.x;
	Nj->y = b.y + dLenab * rbc.y;
	Nj->z = b.z + dLenab * rbc.z;
	///////////
	return 0;
}

double CMC_Circle::Calc_CentralAngles(pWORLD Data, WORLD Center, double Radius,WORLD Normal)
{
	// Compute Phi and Si in degrees: Should be called from Pre_Interpolate
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	C3DMath	Math3D;
	double pi180 = 180./acos(-1.0);
	///////////////////////////////////////
	WORLD rCenA,rCenB,rCenC;
	Math3D.Sub3DPts(&Data[0], &Center, &rCenA);
	Math3D.Sub3DPts(&Data[1], &Center, &rCenB);
	Math3D.Sub3DPts(&Data[2], &Center, &rCenC);
//	lCenC = Math3D.Len3DPts(&rCenC);
	///////////////////////////////////////////
	double Norm12	= Radius * Radius;
	double cosPhi	= (Math3D.Dot3DPts(&rCenA,&rCenB))/Norm12;
	double cosSi	= (Math3D.Dot3DPts(&rCenB,&rCenC))/Norm12;
	////////////
	cosPhi			= acos(cosPhi) * pi180;
	cosSi			= acos(cosSi)  * pi180;
	///////////////////////////////////////////////// Check for Central angle
	// dot product may pick up image pt. of the
	// actual pt. wrt center & generating pt
	// Generate a Pt. by Rotation
	WORLD pt;
	/////////
	GetAPtByRotation(&Data[0], Center, Normal, cosPhi, &pt);
	if(!Math3D.AreSame_WORLD(&Data[1], &pt,pHitNet->GetDblRatio()))
		cosPhi = 360.- cosPhi;
	/////////
	GetAPtByRotation(&Data[1], Center, Normal, cosSi, &pt);
	if(!Math3D.AreSame_WORLD(&Data[2], &pt,pHitNet->GetDblRatio()))
		cosSi = 360.- cosSi;
	/////////////////
	return (cosPhi + cosSi);
	/////////
}

void CMC_Circle::Serialize(CArchive& ar)
{

	CMC_Circle::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Circle:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Circle:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
