// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <math.h> 

#include "3DMath.h"
#include "XForm.h"

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
//#include "EDl2Mgr.h"  
///////////////////// elements
#include "Def_Elem.h"
#include "Def_IGen.h"
#include "DrNode.h"
///////////////////// Labels
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// StaticLoad
#include "Def_StaL.h"
#include "DrThr.h"
///////////////////// specials
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
/////////////////////
#include "MI_Thr.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Thr,CMI_GangS,1)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
//#define	NUM_LEN				12 
#define	TOL_DOUBLE			1.E-6
/////////////////////////////////////////////////////////////////////////////
CMI_Thr::CMI_Thr()
{
}

CMI_Thr::~CMI_Thr()
{
}	

//////////////////////////////////////////////////////////////////////////// Poting Helper
CDrThr* CMI_Thr::CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
						double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(FORCE);
	CDrThr* pAdd;
	int nActiveIndex;
	//////////////////////////////////////////// Output memory
	int nOut		= pCurve->GetLongOutPts();
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	///////////////////////////////////////////////////////////////// Add Always
/*
	nActiveIndex = pDListMgr->GetObjectIndex(FORCE, LoadID);
	if(nActiveIndex>=0)
	{
		pAdd = (CDrThr*)pDListMgr->GetObject(nActiveIndex);
		//////////////////////////////////////////////////// Only Add Node to List 
		pAdd->GetNodeList()->AddTail(pNode);
		///////////////////////////////////// Reciprocate
		(pNode->GetNodeCard())->LoadID = LoadID;
		pNode->GetStaLList()->AddTail(pAdd);
		///////
	}
	else
	{
*/
	//////////////////////////////////////////////////////// Loop Over all MeshPts
	for(int i=0; i<nOut;i++)
	{
	    pAdd = (CDrThr*)(pObjectMgr->AddToDataBase(nActiveIndex,FORCE));
		///////////////////////////////////////////// init Raw StaL Data
		pAdd->InitRawData();
		/////////////////////
		m_StaLBased	= StaLBased;
		m_pCurve	= pCurve;
		m_NodePos	= *(pOut+i);
		////////////////////
		m_LoadID	= LoadID;
		m_aNid		= aNid;
		////////////////// Force
		m_F[0].x	= Tx;
		m_F[0].y	= Ty;
		m_F[0].z	= Tz;
		///////////////////////////////////////
		SetInfoForBase(pAdd);	
		///////	
	}
/*								
	}
*/
	///////////////////////////////////////
    return pAdd;
}

CDrThr* CMI_Thr::CreateNodeBased(CString& LoadID, CDrNode* pNode,
						double Tx,double Ty,double Tz,CString& aNid, UINT StaLBased)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(FORCE);
	CDrThr* pAdd;
	int nActiveIndex;
	/////////////////////////////////////////////////////////////////////////// Add Always
/*
	nActiveIndex = pDListMgr->GetObjectIndex(FORCE, LoadID);
	if(nActiveIndex>=0)
	{
		pAdd = (CDrThr*)pDListMgr->GetObject(nActiveIndex);
		//////////////////////////////////////////////////// Only Add Node to List 
		pAdd->GetNodeList()->AddTail(pNode);
		///////////////////////////////////// Reciprocate
		(pNode->GetNodeCard())->LoadID = LoadID;
		pNode->GetStaLList()->AddTail(pAdd);
		///////
	}
	else
	{
*/
	    pAdd 	= (CDrThr*)(pObjectMgr->AddToDataBase(nActiveIndex,FORCE));
		///////////////////////////////////////////// init Raw StaL Data
		pAdd->InitRawData();
		/////////////////////
		m_StaLBased	= StaLBased;
		m_pNode		= pNode;
		m_NodePos	= *(m_pNode->GetLocalPos());
		////////////////////
		m_LoadID	= LoadID;
		m_aNid		= aNid;
		////////////////// Force
		m_F[0].x	= Tx;
		m_F[0].y	= Ty;
		m_F[0].z	= Tz;
		///////////////////////////////////////
		SetInfoForBase(pAdd);	
		///////	
/*								
	}
*/
	///////////////////////////////////////
    return pAdd;
}

void CMI_Thr::SetInfoForBase(CDrThr* pStaL)
{

	C3DMath Math3D;
	CXForm	XForm;
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
	double Pi180 = 180./3.14159265359;
	//////////////////////////////////			
	LONG  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////
	pStaL->SetObjectType((int)FORCE);
	pStaL->SetElemType((int)STAL_OBJECT);              // globals.h
    pStaL->SetLevelType((int)LEVEL_GRAPA);								// Kid Level
	pStaL->SetObjectID(m_LoadID);             
	/////////////////////////////////////////////////
//		int			ElNum;                 
//		int			IDNum;
	/////////////////////////////////////////////////////////
	if(m_StaLBased == NODE)
	{
		///////////////////////////////////////////////// Nodelist
		pStaL->GetNodeList()->AddTail(m_pNode);
		///////////////////////////////////// Reciprocate
		m_pNode->GetStaLList()->AddTail(pStaL);
	}
	else
	if(m_StaLBased == CURVE)
	{
		///////////////////////////////////////////////// Nodelist
		pStaL->GetCurveList()->AddTail(m_pCurve);
		///////////////////////////////////// Reciprocate
		m_pCurve->GetStaLList()->AddTail(pStaL);
	}
	else
	if(m_StaLBased == PATCH)
	{
		///////////////////////////////////////////////// Nodelist
		pStaL->GetPatchList()->AddTail(m_pPatch);
		///////////////////////////////////// Reciprocate
		m_pPatch->GetStaLList()->AddTail(pStaL);
	}
	else
	if(m_StaLBased == SOLID)
	{
		///////////////////////////////////////////////// Nodelist
		pStaL->GetSolidList()->AddTail(m_pSolid);
		///////////////////////////////////// Reciprocate
		m_pSolid->GetStaLList()->AddTail(pStaL);
	}
	///////////////////////////////////////////////// Kode
	if(m_F[0].x != 0.0 ||m_F[0].y != 0.0 ||m_F[0].z != 0.0)
		pStaL->Setkode(0,1);	// 0:force   1:present
	else
		pStaL->Setkode(0,0);	// 0:force   0:absent
	if(m_F[1].x != 0.0 ||m_F[1].y != 0.0 ||m_F[1].z != 0.0)
		pStaL->Setkode(1,1);	// 1:moment  1:present  
	else
		pStaL->Setkode(1,0);	// 1:moment  0:absent
	///////////////////////////////////////////////// Convert F_M LocalData to WORLD
   	WORLD LocalPos;
	pWORLD pDat;
	int i,j,nPts;
	//////
	for(i=0;i<2;i++)		// Over 0=Force and 1=Moment
	{
		if(pStaL->Getkode(i) == 0)
		continue;
		/////////////	// Over Active One
		nPts = pStaL->GetnPts(i);
		pDat = pStaL->GetpLoc(i);
		/////////////////////////////////// direction cosines
		WORLD F;
		F.x = m_F[i].x;
		F.y = m_F[i].y;
		F.z = m_F[i].z;
		/////////////// save at this point: Actual Force/Moment
		if(i==0)
			pStaL->SetForce(F);	
		if(i==1)
			pStaL->SetMoment(F);	
		///////////////
		MATRIX RotM;
		double dLen = Math3D.Len3DPts(&F);
		if(dLen)
		{
			Math3D.Scale3DPts(dLen,&F);
			///////////////////////////
			double ax = acos(F.x)*Pi180;
			double ay = acos(F.y)*Pi180;
			double az = acos(F.z)*Pi180;
			/////////
			Math3D.GetIdentityMATRIX(&RotM);
			XForm.Rotate_X(&RotM,ax,XF_REPLACE);
			XForm.Rotate_Y(&RotM,ay,XF_REPLACE);
			XForm.Rotate_Z(&RotM,az,XF_REPLACE);
		}
		/////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = pDat[j].x;
			LocalPos.y = pDat[j].y;
			LocalPos.z = pDat[j].z;
			/////////////////////////////////////////////// Rotate
			XForm.Transform(&LocalPos,&LocalPos,&RotM);
			/////////////////////////// strip Scale Factor (World Coord)
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
    		/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
		}
	}
	////////////////////////////////////////// 
	pStaL->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pStaL->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

void CMI_Thr::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Thr:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Thr:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


