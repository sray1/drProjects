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
#include "DrF_M.h"
///////////////////// specials
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
#include "ScaleFac.h"
/////////////////////
#include "MI_F_M.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_F_M,CMI_GangS,1)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
///////////////////////////// for Label
#define	ARROW_TIP_FORCE		6
#define	ARROW_TIP_MOMENT	6
/////////////////////////////////////////////////////////////////////////////
CMI_F_M::CMI_F_M()
{
	m_bCurveTan	= FALSE;
}

CMI_F_M::~CMI_F_M()
{
}	

//////////////////////////////////////////////////////////////////////////// Poting Helper
CDrF_M* CMI_F_M::CreateCurveBased(CString& LoadID, CDrCurve* pCurve,
						double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
						CString& aNid, BOOL bTangent, UINT StaLBased)
{

	m_bReciproDone	= FALSE;
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(FORCE);
	CDrF_M* pAdd;
	int nActiveIndex;
	//////////////////////////////////////////// Output memory
	BOOL bClosed	= pCurve->IsClosed_S();
	int nOut		= pCurve->GetLongOutPts();
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	//////////////////////////////////////////// Generate Tangents, if Needed
	pWORLD	pOutCurveTan;
	m_bCurveTan	= bTangent;
	if(m_bCurveTan)
	{
		int nOutTan		= nOut;
		if(bClosed)
			nOutTan--;
		pOutCurveTan	= FixMem(nOutTan);
		//////////////////////////////////////////// Now Generate
		FillMeshTangentsCurve(pCurve,pOutCurveTan,nOutTan);
		/////////////////////
	}
	///////////////////////////////////////////////////////////////// Add Always
/*
	nActiveIndex = pDListMgr->GetObjectIndex(FORCE, LoadID);
	if(nActiveIndex>=0)
	{
		pAdd = (CDrF_M*)pDListMgr->GetObject(nActiveIndex);
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
	///////////////////////////////////////////////////////////////////////////
	// Remove or Destroy Old One similar to Current LoadID
	////////////////////////////////////////
	CDListMgr* pList = pCurve->GetStaLList();
	////////////////////////////////////////////////////////////////////////
	POSITION pos;
	int i;
	CDrF_M*	pDrF_M;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		pos		= pList->FindIndex(i);
		pDrF_M	= (CDrF_M*)pList->GetAt(pos);
		////
		if(!pDrF_M)
		{
			AfxMessageBox("Internal ERROR:\nCMI_F_M::CreateCurveBased\npDrF_M=NULL"); 
			return (CDrF_M*)NULL;
		}
		//////////////////////////////////////////////////////////////////// Remove
		if((pDrF_M->GetLoadID() == LoadID) )
		{
			pList->RemoveAt(pos);
			//////////////////////////////////////////////////////////////// Delete
			nActiveIndex	= pDListMgr->GetObjectIndex(FORCE, LoadID);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex,FORCE);
			////////
		}
	}
	////////////////////////////////////////////////////////
	int nOutCreate = nOut;
	if(bClosed)
		nOutCreate--;
	//////////////////////////////////////////////////////// Loop Over all MeshPts
	for(i=0; i<nOutCreate;i++)
	{
	    pAdd = (CDrF_M*)(pObjectMgr->AddToDataBase(nActiveIndex,FORCE));
		///////////////////////////////////////////// init Raw StaL Data
		pAdd->InitRawData();
		/////////////////////
		m_StaLBased	= StaLBased;
		m_pCurve	= pCurve;
		m_NodePos	= *(pOut+i);
		//////////
		if(m_bCurveTan)
			m_CurveTan	= *(pOutCurveTan+i);
		////////////////////
		m_LoadID	= LoadID;
		m_aNid		= aNid;
		////////////////// Force
		m_F[0].x	= Tx;
		m_F[0].y	= Ty;
		m_F[0].z	= Tz;
		////////////////// Moment
		m_F[1].x	= Rx;
		m_F[1].y	= Ry;
		m_F[1].z	= Rz;
		///////////////////////////////////////
		SetInfoForBase(pAdd);	
		///////	
	}
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	if(m_bCurveTan)
		FreeMem(pOutCurveTan);
	/////////////////////
/*								
	}
*/
	///////////////////////////////////////
    return pAdd;
}

CDrF_M* CMI_F_M::CreateNodeBased(CString& LoadID, CDrNode* pNode,
						double Tx,double Ty,double Tz,double Rx,double Ry,double Rz,
						CString& aNid, UINT StaLBased)
{

	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(FORCE);
	CDrF_M* pAdd;
	int nActiveIndex;
	///////////////////////////////////////////////////////////////////////////
	// Remove or Destroy Old One similar to Current LoadID
	////////////////////////////////////////
	CDListMgr* pList = pNode->GetStaLList();
	////////////////////////////////////////////////////////////////////////
	POSITION pos;
	int i;
	CDrF_M*	pDrF_M;
	/////////////////////////////////////////////////////////// Go Over List
	for(i=0;i<pList->GetCount();i++)
	{
		pos		= pList->FindIndex(i);
		pDrF_M	= (CDrF_M*)pList->GetAt(pos);
		////
		if(!pDrF_M)
		{
			AfxMessageBox("Internal ERROR:\nCMI_F_M::CreateNodeBased\npDrF_M=NULL"); 
			return (CDrF_M*)NULL;
		}
		//////////////////////////////////////////////////////////////////// Remove
		if((pDrF_M->GetLoadID() == LoadID) )
		{
			pList->RemoveAt(pos);
			//////////////////////////////////////////////////////////////// Delete
			nActiveIndex	= pDListMgr->GetObjectIndex(FORCE, LoadID);
			if(nActiveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nActiveIndex,FORCE);
			////////
		}
	}
	/////////////////////////////////////////////////////////////////////////// Add Always
/*
	nActiveIndex = pDListMgr->GetObjectIndex(FORCE, LoadID);
	if(nActiveIndex>=0)
	{
		pAdd = (CDrF_M*)pDListMgr->GetObject(nActiveIndex);
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
	    pAdd 	= (CDrF_M*)(pObjectMgr->AddToDataBase(nActiveIndex,FORCE));
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
		////////////////// Moment
		m_F[1].x	= Rx;
		m_F[1].y	= Ry;
		m_F[1].z	= Rz;
		///////////////////////////////
		SetInfoForBase(pAdd);	
		///////////////////////////////
/*								
	}
*/
	///////////////////////////////////////
    return pAdd;
}

void CMI_F_M::SetInfoForBase(CDrF_M* pStaL)
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
		///////////////////////////////////////////////// Curvelist
		pStaL->GetCurveList()->AddTail(m_pCurve);
		///////////////////////////////////// Reciprocate
		m_pCurve->GetStaLList()->AddTail(pStaL);
	}
	else
	if(m_StaLBased == PATCH)
	{
		///////////////////////////////////////////////// Patchlist
		pStaL->GetPatchList()->AddTail(m_pPatch);
		///////////////////////////////////// Reciprocate
		m_pPatch->GetStaLList()->AddTail(pStaL);
	}
	else
	if(m_StaLBased == SOLID)
	{
		///////////////////////////////////////////////// Solidlist
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
   	WORLD F,LocalPos,CNodPos;
	pWORLD pDat;
	double dVal;
	CString text;
	char* pBuf;
	CDrNode*	pLabelNode;
	CDrLabel*	pLabel; 
	///////////////
	int i,j,nPts,indexLabel,nActiveIndexSave;
	int nNodeIndex, nForceLabelIndex;
	////////////////////////////////////////////////////////// Skewed Force Axes
	C3DMath	Math3D;
	CXForm	XForm;
	MATRIX Mat;
	pMATRIX pMat = &Mat; 
	MATRIX Rot;
	pMATRIX pRot = &Rot; 
	WORLD NewX;
	pWORLD pNewX = &NewX;
	////////////////////////
	Math3D.GetIdentityMATRIX(pMat);
	Math3D.GetIdentityMATRIX(pRot);
	/////////////////////
	if(m_aNid != "")
	{
		CDListMgr* pList	= pObjectMgr->GetObjectList(NODE);
		int index			= pList->GetObjectIndex(NODE,m_aNid);
		CDrNode* pNode		= (CDrNode*)pList->GetObject(index);
		CNodPos				= *(pNode->GetLocalPos());
		/////////////////////////////////// Get NewX Direction
		Math3D.Sub3DPts(&CNodPos,&m_NodePos,pNewX);
		/////////////////////////////////// Rotate to NewX
		XForm.RotateToNewXMATRIX(pNewX, pMat,XF_REPLACE);
	}
	else
	if(m_bCurveTan)
	{
		/////////////////////////////////// Rotate to NewX = Tangent direction
		XForm.RotateToNewXMATRIX(&m_CurveTan, pMat,XF_REPLACE);
	}
	//////
	for(i=0;i<2;i++)		// Over 0=Force and 1=Moment
	{
		if(pStaL->Getkode(i) == 0)
		continue;
		/////////////	// Over Active One
		nPts = pStaL->GetnPts(i);
		pDat = pStaL->GetpLoc(i);
		/////////////////////////////////// direction cosines
		F.x = m_F[i].x;
		F.y = m_F[i].y;
		F.z = m_F[i].z;
		////////////////////////////////////////////////// Skew:Rotate F to New F 
		if((m_aNid != "") || m_bCurveTan)
		{
			////////////////////////////////////////////// Rotate
			XForm.Transform(&F,&F,pMat);
		}
		////////////////////////////////////////////// Create NewX along F
		XForm.RotateToNewXMATRIX(&F,pRot,XF_REPLACE);
		///////////////////////////// LabelID
		dVal = Math3D.Len3DPts(&F);
		pBuf = text.GetBuffer(30);
		/////////////////////////////
		/////////////// save at this point: Actual Force/Moment
		if(i==0)
		{
			pStaL->SetForce(F);
			indexLabel = ARROW_TIP_FORCE;
			sprintf(pBuf,"F=%.f",dVal);
			text.ReleaseBuffer();
		}		
		if(i==1)
		{
			pStaL->SetMoment(F);
			indexLabel = ARROW_TIP_MOMENT;
			sprintf(pBuf,"M=%.f",dVal);
			text.ReleaseBuffer();
		}		
		/////////////////////////
		for(j=0;j<nPts;j++)
		{
			LocalPos.x = pDat[j].x;
			LocalPos.y = pDat[j].y;
			LocalPos.z = pDat[j].z;
			/////////////////////////////////////////////// Rotate
			XForm.Transform(&LocalPos,&LocalPos,pRot);
			/////////////////////////// strip Scale Factor (World Coord)
//			Mouse.WOPtoWOR(&LocalPos,&LocalPos);
			////////
			pObjectMgr->SCtoDS(&(LocalPos.x));
			pObjectMgr->SCtoDS(&(LocalPos.y));
			pObjectMgr->SCtoDS(&(LocalPos.z));
    		/////////////////////////////////////////////// also Xlate to Node
    		pDat[j].x = (LocalPos.x)*dWorldBase/dMapFactor + m_NodePos.x; 
    		pDat[j].y = (LocalPos.y)*dWorldBase/dMapFactor + m_NodePos.y; 
    		pDat[j].z = (LocalPos.z)*dWorldBase/dMapFactor + m_NodePos.z;
			///////////////////////////////////////////////////////////// Label:CreateCNode
			if(j == indexLabel)
			{
				nActiveIndexSave = pObjectMgr->GetActiveObjectIndex();	// Save Active Index									
				//////////////////////////////////////////////////////
				LocalPos.x = pDat[j].x;
				LocalPos.y = pDat[j].y;
				LocalPos.z = pDat[j].z;
				///
//				Mouse.WORtoWOP(&LocalPos,&LocalPos);
				///////////////////////////////////////////
   				LocalPos.x	= ((double)(LocalPos.x))/dWorldBase*dMapFactor;
   				LocalPos.y	= ((double)(LocalPos.y))/dWorldBase*dMapFactor;
   				LocalPos.z	= ((double)(LocalPos.z))/dWorldBase*dMapFactor;
 				//////////////////////// World Coord
				pObjectMgr->DStoSC(&LocalPos.x);
				pObjectMgr->DStoSC(&LocalPos.y);
				pObjectMgr->DStoSC(&LocalPos.z);
				//////////////////////////////////////// 
				pLabelNode	= CreateNode(text,pLabel,LocalPos, TRUE,FALSE,FALSE,
								nNodeIndex, nForceLabelIndex);// FALSE=Input/TRUE=InternallyGen
				pLabel		= (CDrLabel*)((pLabelNode->GetLabelList())->GetTail());
				////////////////////////////////////////////////////////// Reciprocate
				pStaL->SetLabelNode(pLabelNode);
				pStaL->SetLabelPtr(pLabel);
				///////////////////////////////////
				pLabel->SetContextObj(CO_FORCE);
				///////////////////////////////////////////////////
				pObjectMgr->SetActiveObjectIndex(nActiveIndexSave);		// Restore Active Index									
			}
		}
	}
	////////////////////////////////////////// 
	pStaL->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pStaL->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

void CMI_F_M::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_F_M:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_F_M:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


