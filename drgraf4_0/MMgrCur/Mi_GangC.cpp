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
#include "Def_MouseAct.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "MCurMgr.h"  
//#include "EDl2Mgr.h"  
//#include "MDlgMgr.h"  
///////////////////// cards
#include "Def_Card.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
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
#include "MC_Parab.h" 
#include "MC_Circle.h" 
#include "MC_Bezier.h"
#include "MC_Lin.h"
#include "MC_Quad.h"
#include "MC_Cube.h"
/////////////////////
#include "Dlg_CClk.h"
#include "MI_GangN.h" 
#include "MI_GangC.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////
IMPLEMENT_SERIAL(CMI_GangC,CObject,1)
/////////////////////////////////////
#define MIN_INODES_CURVE	2
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
//#define	NUM_LEN				12 
#define	MAX_SEG_ANGLE		120
/////////////////////////////////////////////////////////////////////////////
CMI_GangC::CMI_GangC()
{

	m_BezierType= BEZIER_BY_PTS;
	m_bNoDefault= FALSE;	// for Tensor Product etc, it becomes TRUE
    /////////////////////////////////////////// Curve
	m_bClosed_S			= FALSE;
	/////////////////// Memory
	m_MemErr	= 0;
	m_pMKnot_S	= NULL;
	m_pKnot_S	= NULL;
	m_pWts_DT_S	= NULL;
	m_pWts_BS_S	= NULL;
	m_pWts_BZ_S	= NULL;
	m_pData		= NULL;
	m_pCon_BS_S	= NULL;
	m_pCon_BZ_S	= NULL;
	///////////////////
    
}

CMI_GangC::~CMI_GangC()
{
 
	/////////////////// Error:MemoryRelease
	if(m_MemErr<0)
	{
		if(m_pMKnot_S)
		{
			delete [] m_pMKnot_S;
			m_pMKnot_S = NULL;
		}	
		if(m_pKnot_S)
		{
			delete [] m_pKnot_S;
			m_pKnot_S = NULL;
		}	
		if(m_pWts_DT_S)
		{
			delete [] m_pWts_DT_S;
			m_pWts_DT_S = NULL;
		}	
		if(m_pWts_BS_S)
		{
			delete [] m_pWts_BS_S;
			m_pWts_BS_S = NULL;
		}	
		if(m_pWts_BZ_S)
		{
			delete [] m_pWts_BZ_S;
			m_pWts_BZ_S = NULL;
		}	
		if(m_pData)
		{
			delete m_pData;
			m_pData = NULL;
		}	
		if(m_pCon_BS_S)
		{
			delete [] m_pCon_BS_S;
			m_pCon_BS_S = NULL;
		}	
		if(m_pCon_BZ_S)
		{
			delete [] m_pCon_BZ_S;
			m_pCon_BZ_S = NULL;
		}	
	}	
    //////////////////////////////// Memory release
	if(m_pCon_BS_S)
	{
		delete [] m_pCon_BS_S;
		m_pCon_BS_S = NULL;
	}	
	if(m_pCon_BZ_S)
	{
		delete [] m_pCon_BZ_S;
		m_pCon_BZ_S = NULL;
	}
	//////////////////////////////	
}
	
int CMI_GangC::WORtoWOP_VECTOR(VECTOR& TanI)
{
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////// scale etc
	TanI.v[0] /= (dWorldBase/dMapFactor);
	TanI.v[1] /= (dWorldBase/dMapFactor);
	TanI.v[2] /= (dWorldBase/dMapFactor);
	TanI.v[3] /= (dWorldBase/dMapFactor);
	pObjectMgr->DStoSC(&TanI.v[0]);
	pObjectMgr->DStoSC(&TanI.v[1]);
	pObjectMgr->DStoSC(&TanI.v[2]);
	pObjectMgr->DStoSC(&TanI.v[3]);
	/////////////
	return MA_OK;
}
	
int CMI_GangC::WORtoWOP_WORLD(WORLD& TanI)
{
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////// scale etc
	TanI.x /= (dWorldBase/dMapFactor);
	TanI.y /= (dWorldBase/dMapFactor);
	TanI.z /= (dWorldBase/dMapFactor);
	pObjectMgr->DStoSC(&TanI.x);
	pObjectMgr->DStoSC(&TanI.y);
	pObjectMgr->DStoSC(&TanI.z);
	/////////////
	return MA_OK;
}
	
int CMI_GangC::WOPtoWOR_VECTOR(VECTOR& TanI)
{
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////// scale etc
	pObjectMgr->SCtoDS(&TanI.v[0]);
	pObjectMgr->SCtoDS(&TanI.v[1]);
	pObjectMgr->SCtoDS(&TanI.v[2]);
	pObjectMgr->SCtoDS(&TanI.v[3]);
	TanI.v[0] *= (dWorldBase/dMapFactor);
	TanI.v[1] *= (dWorldBase/dMapFactor);
	TanI.v[2] *= (dWorldBase/dMapFactor);
	TanI.v[3] *= (dWorldBase/dMapFactor);
	/////////////
	return MA_OK;
}
	
int CMI_GangC::WOPtoWOR_WORLD(WORLD& TanI)
{
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////// scale etc
	pObjectMgr->SCtoDS(&TanI.x);
	pObjectMgr->SCtoDS(&TanI.y);
	pObjectMgr->SCtoDS(&TanI.z);
	TanI.x *= (dWorldBase/dMapFactor);
	TanI.y *= (dWorldBase/dMapFactor);
	TanI.z *= (dWorldBase/dMapFactor);
	/////////////
	return MA_OK;
}
	
int CMI_GangC::CreateBezCNsFromTanEnds_Cubic(CDrCurve* pCurve)
{
	// creates Control Nodes
	//	b1 = b0 + (del0/3)*m0
	//	b2 = b3 - (del0/3)*m3
	/////////////////////////
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDListMgr* pCNodeList = pCurve->GetCNodeList();
	CDListMgr* pINodeList = pCurve->GetINodeList();
	if(pINodeList->GetCount() != 2)
	{
		AfxMessageBox("Internal ERROR:\nCMI_GangC::CreateCubicBezierFromTanEnds\nNodeCount !=2");
		return MA_ERROR;
	}
	///////
	int i;
	////////////////////////////
	CString* pNid = new CString;
	char* buf = pNid->GetBuffer(BUFF_SIZE);
	CString CurveID = pCurve->GetObjectID();
	////////////
	CDrNode*	pNode;
	WORLD		LocalPos0,LocalPos3,del0,delB;
	double		dLen;
	CDrNode*	pCN;
	CDrNode*	pCN3;
	VECTOR		Tan;
	////////////////////////////////////////////////////////////// del0
	pNode		= (CDrNode*)pINodeList->GetObject(0);
	LocalPos0	= *(pNode->GetLocalPos());
	pNode		= (CDrNode*)pINodeList->GetObject(1);
	LocalPos3	= *(pNode->GetLocalPos());
	///////////////////////////////////////////// scale
	Math3D.Sub3DPts(&LocalPos0,&LocalPos3,&del0);
	dLen = Math3D.Len3DPts(&del0);
	double r = fabs(dLen/3);
	////////////////////////////////////////////////////////////// b0
    //////////////////////////////////// Name
    sprintf(buf,"%s_%d%d",CurveID,0,0);
	///////////////////////////////////// in THE List 
	pCN = PostNode(*pNid,LEVEL_KIDDO,LocalPos0,TRUE);	// Create DrCNode
	if(!pCN)	// Create DrCNode
		return MA_ERROR;
	///////////////////////////////////// in Curve 	
	pCNodeList->InsertObject(pCN); //CNodeList
	////////////////////////////////////////////////////////////// b1 = b0 + 3 * m0
	Tan		= pCurve->GetTanL_S();
	WORtoWOP_VECTOR(Tan);	// deScale internal rep
	////
	delB.x	= r * Tan.v[0];
	delB.y	= r * Tan.v[1];
	delB.z	= r * Tan.v[2];
	//////////////////////////////////// scale WOP->WOR
	Math3D.Add3DPts(&LocalPos0,&delB,&LocalPos0);
    //////////////////////////////////// Name
    sprintf(buf,"%s_%d%d",CurveID,1,0);
	///////////////////////////////////// in THE List 
	pCN = PostNode(*pNid,LEVEL_KIDDO,LocalPos0,TRUE);	// Create DrCNode
	if(!pCN)	// Create DrCNode
		return MA_ERROR;
	///////////////////////////////////// in Curve 	
	pCNodeList->InsertObject(pCN); //CNodeList
	////////////////////////////////////////////////////////////// b3
    //////////////////////////////////// Name
    sprintf(buf,"%s_%d%d",CurveID,3,0);
	///////////////////////////////////// in THE List 
	pCN3 = PostNode(*pNid,LEVEL_KIDDO,LocalPos3,TRUE);	// Create DrCNode
	if(!pCN3)	// Create DrCNode
		return MA_ERROR;
	////////////////////////////////////////////////////////////// b2 = b3 - (3/del0) * m3
	Tan		= pCurve->GetTanR_S();
	WORtoWOP_VECTOR(Tan);	// deScale internal rep
	////
	r = -r;
	delB.x	= r * Tan.v[0];
	delB.y	= r * Tan.v[1];
	delB.z	= r * Tan.v[2];
	//////////////////////////////////// scale WOP->WOR
	Math3D.Add3DPts(&LocalPos3,&delB,&LocalPos3);
    //////////////////////////////////// Name
    sprintf(buf,"%s_%d%d",CurveID,2,0);
	///////////////////////////////////// in THE List 
	pCN = PostNode(*pNid,LEVEL_KIDDO,LocalPos3,TRUE);	// Create DrCNode
	if(!pCN)	// Create DrCNode
		return MA_ERROR;
	///////////////////////////////////// in Curve 	
	pCNodeList->InsertObject(pCN); //CNodeList
	pCNodeList->InsertObject(pCN3); //CNodeList
	delete pNid;
	////////////////////////////////////////////////////////////// Knots & Wts
	// BC_N_KNOTs_N DIMS
	int nCons = 4;	// CUBIC: 4 CNs
	pCurve->SetWtType_S(WT_AUTO);
	//////////////////////////////////
	m_pWts_BZ_S = new double[nCons];				// will be deleted in DrCurve
	for(i=0;i<nCons;i++)
		m_pWts_BZ_S[i] = 1.00;
	pCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
    //////////////////////////////////////////////////////// Knots
	int nData = 2;	// CUBIC: 4 CNs
	pCurve->SetKnotType_S(KN_AUTO);
	//////////////////////////////////////////////////////// Setup Knots
	pWORLD inData = new WORLD[nData];
	/////
	SetUpINodes(pINodeList,inData,nData);
	/////
	m_nKnots_S = nData;
	pDOUBLE m_pKnot_S = new double[m_nKnots_S];	// will be deleted in DrCurve
	/////
	m_KnotType_S = KN_AUTO;	// chordlength
	SetupKnots(inData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
	///////////////////////////////////////////////////// Save
	pCurve->SetpKnots_S(m_pKnot_S);	// pointer
	//////////////////////////////////////////
	delete [] inData;
	/////////////
	return MA_OK;
}

int CMI_GangC::CreateCurveAnyType(CDrCurve* pCurve,CURVEDATA& CDat)
{
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	///////////////////////////////////////// Data
	CString		ID				= CDat.ID;	
	CURVEPROC	CurveType		= CDat.CurveType;
	CIRCLETYPE	CircType		= CDat.CircType;
	BOOL		bFinal			= CDat.bFinal;
	BOOL		bAdvanceOn		= CDat.bAdvanceOn;
	///////////////////////
	CDListMgr*	pNodeList		= CDat.pNodeList;	
	CList<int,int>*	pElSegList	= CDat.pElSegList;	
	///////////////////////
 	CDrNode*	pFromNode		= CDat.pFromNode;  //
 	CDrNode*	pToNode			= CDat.pToNode;  //
	BOOL		bAxis			= CDat.bAxis;
	int			nAxis			= CDat.nAxis;
	BOOL		bNegative		= CDat.bNegative;
	double		dAng			= CDat.dAng;
	double		SegAngle		= CDat.SegAngle;
	double		dRadius			= CDat.dRadius;
	BOOL		bArc			= CDat.bArc;
	//////////////////////////////////////////// 
	MC_Circle.SetAxisInput(bAxis);
	MC_Circle.SetAxis(nAxis);
	MC_Circle.SetNegative(bNegative);
	////////////////////////
	switch(CurveType)
	{
		case CP_CIRCLE:
			////////////////////////////////////
			pCurve = MC_Circle.CreateCircle(
								ID,pCurve,pNodeList,CurveType,
								pElSegList,CircType,dAng,SegAngle,dRadius,
								bArc,pFromNode,pToNode,bFinal);
			break;
				
		case CP_PARABOLA:
			pCurve = MC_Parabola.CreateParabola(ID,pCurve,pNodeList,CurveType,
											pElSegList,bAdvanceOn,bFinal);
			break;
			
		default:
			
			///
			pCurve = CreateCurve(ID,pCurve,pNodeList,CurveType,
									pElSegList,bAdvanceOn,bFinal);
			break;
	}
	if(!pCurve)
		return MA_ERROR;
	///////////////////////////////
	return MA_OK;
}	 

int CMI_GangC::InsertAllInfo_Curve(int nOrder)
{ 

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	// 		ALWAYS	B E Z I E R	CurveType
	///////////////////////////////////// Compute No. of Curves
	int nCurves;
	////////////////////////////////////////////////////////////
	m_pDrCurve->NumberOfCurves(CP_BEZIER,m_nMaxCurveCNodes_S,&nCurves,m_bClosed_S,nOrder);
/*
	/////////////////////////////////////////////////////////// save in DrCurve
	if((m_CurveType_S == CP_CIRCLE) && m_bFinal)
	{
		if(m_nType != CIRCLE_BY_2N_CC)
		{
			m_pDrCurve->SetCenter_S(m_Center_S);
			m_pDrCurve->SetRadius_S(m_Radius_S);				
			m_pDrCurve->SetNormal_S(m_vAxis_S);
			//////////////////////////////////// also as node for future reference
			pObjectMgr->BumpLastInputNo(CNODE);		// bump it
			int nLastNum = pObjectMgr->GetLastInputNo(CNODE);		// internal
			char buf[50];
			sprintf(buf,"%d",nLastNum);
			CString Nid;
			Nid = "Ctr_";
			Nid	+= buf;
			/////////////
			CDrLabel* pLabel;
			int nNodeIndex,nLabelIndex;
			/////////////////////////// Create Anyway
			nNodeIndex = -12345;
			CDrNode* pAddNode = CreateNode(Nid,pLabel,m_Center_S,TRUE,TRUE,
											nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pAddNode)	// Create DrCNode
				return -1;
			///////////////////////////////////////////////// Reciprocate
			pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
			m_pDrCurve->GetElemList()->InsertObject(pAddNode); //Auxiliary CNode in ElemList
			///////////////////////////////////////////////
		}		
	}
*/
	///////////////////////////////////////////
	m_pDrCurve->SetCurveType_S(m_CurveType_S);
	m_pDrCurve->SetMaxBezSegments_S(nCurves);
	m_pDrCurve->SetDirty(TRUE);
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrCurve->Calc_3DBoundsLocal();											
	///////////////
	return 0;
	///////////////
	
}			 

void CMI_GangC::SetUpINodes_Wts(CDListMgr* pList,pWORLD pInDat,pDOUBLE pInWts,int nData)
{
	/////////////////////////////////////////
	int i;
	CDrNode* pDrNode;
    /////////////////
	WORLD 	LocalPos;
	//////////////////////////////////////////// Get point 
    for(i = 0; i<nData; i++)              
    {
    	pDrNode = (CDrNode*)(pList->GetObject(i));
    	//////////////////////////////////////// NPC Pt.
    	LocalPos = *(pDrNode->GetLocalPos());
    	/////////////////////////////////
		pInDat[i].x = LocalPos.x;	  
		pInDat[i].y = LocalPos.y;  
		pInDat[i].z = LocalPos.z;
		//////////////////////////////////////// Wts
		pInWts[i] = 1.0;
	}	
}

int CMI_GangC::SetUpINodes(CDListMgr* pList,pWORLD inData,int nData)
{

	int k;
	///////////
    if(nData<=0)
    	return -1;
    ///////////////////////
    k = -1;
    double x,y,z;
    //////////////	
	POSITION pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrNode* pNode = (CDrNode*)pList->GetNextObject( pos);
		k++;
		x = (pNode->GetNodeCard())->x;
		y = (pNode->GetNodeCard())->y;
		z = (pNode->GetNodeCard())->z;
		inData[k].x = x;
		inData[k].y = y;
		inData[k].z = z;
	}
	///////////
	if(k != (nData-1))
		return -1;
	else
		return 0;
	/////////////		 
}

int CMI_GangC::GenerateCurveVNodes(CDrCurve* pCurve,CString& CurrentNodeID)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	int nOut		= pCurve->GetLongOutPts();
	BOOL bClosed	= pCurve->IsClosed_S();
	pWORLD	pOut	= FixMem(nOut);
	pDOUBLE pOutWts = FixMemD(nOut);
	int nDegree		= pCurve->GetOrder_S() - 1;
	int nSegBZ		= pCurve->GetMaxBezSegments_S();
    CList<int,int>* pElperSegList = pCurve->GetElperSegList_S();		
	//////////////////////////////////////////// Now Generate
	m_bBack = FALSE;
	FillMeshNodesCurve(pCurve,pOut,pOutWts,nOut);
	//////////////////////////////////////////// Post Nodes,Not Junction Nodes(Already Input)
	BOOL bGen = FALSE;
	int k=-1,s,t;
	POSITION pos;
	int nElems;
	//////////
	UINT nType = INODE;
	for (s = 0; s<nSegBZ; s++)
	{
		pos		= pElperSegList->FindIndex(s); 
		nElems	= pElperSegList->GetAt(pos); 

		for(t=0;t<nElems;t++)
		{
			k++;
			if( t == 0)	// Junctions
				continue;
			////////////////////////////////////
			CString	NewNID = "";
			if(k>1) // first one already Bumped by end Node of the Curve in CurMouse:UpdateNewNode
			{
				pObjectMgr->SetNodeInfoID(NewNID,FALSE,(UINT)nType);
				bGen = TRUE;
			}
			else
				NewNID = CurrentNodeID;
			////////////////////////////////////////////////////// Generate
			CDrLabel* pLabel;
			int nNodeIndex,nLabelIndex;
			////////////////////////////////// Create Anyway
			nNodeIndex = -12345;
			CDrNode* pNewNode = CreateNode(NewNID,pLabel,pOut[k],FALSE,TRUE,
										nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pNewNode)	// Create DrCNode
				return MA_ERROR;
			//////////////////////////////////
			pNewNode->SetShow(TRUE);
			///////////////////////////////////////////////////// Reciprocate
			CDListMgr* pCurveList = pNewNode->GetCurveList();
			int index = pCurveList->GetObjectIndex(pCurve);
			if(index<0)
				pCurveList->InsertObject(pCurve);
			////////
			pNewNode->SetVirtual(TRUE);
			pCurve->GetVNodeList()->InsertObject(pNewNode);
			////
		}
	}	
	/////////////////////////////////////// Free Memory
	FreeMem(pOut);
	FreeMemD(pOutWts);
	/////////////////////////////////////// Adjust
	if(bGen)
		pObjectMgr->SetNodeInfoID(CurrentNodeID,FALSE,(UINT)nType);
	//////////////
    return MA_OK;
}

int CMI_GangC::FillMeshNodesCurve(CDrCurve* pDrCurve, pWORLD pOut, pDOUBLE pOutWts, int nOut)
{
    //////////////////////////////////////////////////////
	pDrCurve->RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	pDrCurve->GenerateCurve(pOut, pOutWts);
	//////////////////////////////////////////
	if(!m_bBack)
		return 0;
	////////////////////////////////////////// BackWard
	pWORLD pBk		= FixMem(nOut);
	pDOUBLE pBkWts	= FixMemD(nOut);
	///////////////
	for(int i=0;i<nOut;i++)
	{
		pBk[i].x	= pOut[nOut-i-1].x;
		pBk[i].y	= pOut[nOut-i-1].y;
		pBk[i].z	= pOut[nOut-i-1].z;
		pBkWts[i]	= pOutWts[nOut-i-1];
	}
	/////////////
	for(i=0;i<nOut;i++)
	{
		pOut[i].x	= pBk[i].x;
		pOut[i].y	= pBk[i].y;
		pOut[i].z	= pBk[i].z;
		pOutWts[i]	= pBkWts[i];
	}
	FreeMem(pBk);
	FreeMemD(pBkWts);
	/////////////////
	return 0;

}

int CMI_GangC::FillMeshTangentsCurve(CDrCurve* pDrCurve, pWORLD pOut, int nOut)
{
    //////////////////////////////////////////////////////
	pDrCurve->RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	pDrCurve->GenerateTangent(pOut);
	//////////////////////////////////////////
	if(!m_bBack)
		return 0;
	////////////////////////////////////////// BackWard
	pWORLD pBk		= FixMem(nOut);
	///////////////
	for(int i=0;i<nOut;i++)
	{
		pBk[i].x	= pOut[nOut-i-1].x;
		pBk[i].y	= pOut[nOut-i-1].y;
		pBk[i].z	= pOut[nOut-i-1].z;
	}
	/////////////
	for(i=0;i<nOut;i++)
	{
		pOut[i].x	= pBk[i].x;
		pOut[i].y	= pBk[i].y;
		pOut[i].z	= pBk[i].z;
	}
	FreeMem(pBk);
	/////////////////
	return 0;

}
/*
//	Moved to CreOMgr Dll   01/14/98 

CDrCurve* CMI_GangC::PostCurve(CString& Cid,CString& OldID,CURVEPROC CProc)
{

	CMCurMgr 	EDlgMgr;
	CMCurMgr* 	pEDlgMgr = &EDlgMgr;
	CDrCurve*	pCurve;
	/////////////////////////////////////////////
	pCurve = pEDlgMgr->SpawnCurve(Cid, OldID, CProc);
	//////////////////////////////////////////////
	return pCurve;
}
//	Moved to CreOMgr Dll   01/14/98 end 
*/
CDrCurve* CMI_GangC::CreateCurve(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
								 CURVEPROC kind,CList<int,int>* pElperSegList,
								 BOOL bAdvanceOn,BOOL bFinal)
{
	///////////////////////////////////////////////
	pCurve->GetElperSegList_S()->AddTail(pElperSegList);	// save for later editing etc
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMCurMgr	MDlgMgr;
	CMCurMgr*	pMDlgMgr = &MDlgMgr;
	////////////////////////////////////////////////////// Already in DataBase
	m_pDrCurve 	= pCurve;
	////////////////////////////////////////////// Fill Input Nodes (DONE IN SHOWCURVE)
//	if(!(m_pDrCurve->GetINodeList()->IsEmpty())  )
//		m_pDrCurve->GetINodeList()->RemoveHead();
//	m_pDrCurve->GetINodeList()->AddTail(pNodeList);	// copy
	/////////////////////////////////////////////// Fill EverythingElse
	m_CurveID		= Cid;
	m_CurveType_S	= kind;
	m_bClosed_S		= m_pDrCurve->IsClosed_S();
	m_Ratio_S		= m_pDrCurve->GetRatio_S();
	/////////////////////////////////////////////// interpolate
	if(m_CurveType_S == CP_LINEAR)	// BSpline Linear
	{
		/////////
		m_nOrder_S	= 2;
		m_Ratio_S	= m_pDrCurve->GetRatio_S();
		///////////////////////////////////////
		SetInfoForCurveBase(m_pDrCurve,pElperSegList,bFinal);
		/////////////////////////////// BC & Knot DataBases
		if(bFinal && bAdvanceOn)
			pMDlgMgr->DoModal_Cur_Advance_In(m_pDrCurve,m_nOrder_S);
		else
		if(m_pDrCurve->IsIso())
			SetIsoInfoForCurveBase(m_pDrCurve);
		else
			SetDefaultInfoForCurveBase(m_pDrCurve);
		/////////////
		CMC_Lin McLin;
		////////////////////////////////////////////////////////// Go Interpolate
		McLin.GoDoIt(m_pDrCurve,bFinal);
		///////////////////////
	}
	else
	if(m_CurveType_S == CP_QUADRATIC)	// BSpline Quadratic
	{
		/////////
		m_nOrder_S = 3;
		SetInfoForCurveBase(m_pDrCurve,pElperSegList,bFinal);
		/////////////////////////////// BC & Knot DataBases
		if(bFinal && bAdvanceOn)
			pMDlgMgr->DoModal_Cur_Advance_In(m_pDrCurve,m_nOrder_S);
		else
		if(m_pDrCurve->IsIso())
			SetIsoInfoForCurveBase(m_pDrCurve);
		else
			SetDefaultInfoForCurveBase(m_pDrCurve);
		/////////////
		CMC_Quad McQuad;
		////////////////////////////////////////////////////////// Go Interpolate
		McQuad.GoDoIt(m_pDrCurve,bFinal);
		///////////////////////
	}
	else		
	if(m_CurveType_S == CP_BSPLINE	|| m_CurveType_S == CP_NURB)// BSpline Cubic
	{
		/////////
		m_nOrder_S = 4;
		SetInfoForCurveBase(m_pDrCurve,pElperSegList,bFinal);
		/////////////////////////////// BC & Knot DataBases
		if(bFinal && bAdvanceOn)
			pMDlgMgr->DoModal_Cur_Advance_In(m_pDrCurve,m_nOrder_S);
		else
		if(m_pDrCurve->IsIso())
			SetIsoInfoForCurveBase(m_pDrCurve);
		else
			SetDefaultInfoForCurveBase(m_pDrCurve);
		/////////////
		CMC_Cube McCube;
		////////////////////////////////////////////////////////// Go Interpolate
		McCube.GoDoIt(m_pDrCurve,bFinal);
		///////////////////////
	}
	else
	if(m_CurveType_S == CP_BEZIER)	
	{
		if(m_BezierType == BEZIER_BY_TAN)	// Used Internally for Blending
		{
			m_nOrder_S = 4;					// Cubic for Blending
			///////////////
			SetInfoForCurveBase(m_pDrCurve,pElperSegList,bFinal);
		}
		else
		if(m_BezierType == BEZIER_BY_PTS)
		{
			CDListMgr* pINList = m_pDrCurve->GetINodeList();
			m_nOrder_S = pINList->GetCount();
			/////////////////////////////////
			SetInfoForBezierPtsBase(m_pDrCurve,pElperSegList,bFinal);
		}
		/////////////////////////////// BC & Knot DataBases
		if(bFinal && bAdvanceOn)
			pMDlgMgr->DoModal_Cur_Advance_In(m_pDrCurve,m_nOrder_S);
		else
		if(m_pDrCurve->IsIso())
			SetIsoInfoForCurveBase(m_pDrCurve);
		else
			SetDefaultInfoForCurveBase(m_pDrCurve);
		/////////////////////////////////////////////////// DoIt
		if(m_BezierType == BEZIER_BY_TAN) 
			CreateBezCNsFromTanEnds_Cubic(pCurve);
		else
		if(m_BezierType == BEZIER_BY_PTS)
		{
			CMC_Bezier McBezier;
			///////////////////////
			McBezier.GoDoIt(m_pDrCurve,bFinal);
		}
	}
	////////////
    return m_pDrCurve;
}
 
void CMI_GangC::SetIsoInfoForCurveBase(CDrCurve* pDrObject)
{
	// BC_N_KNOTs_N DIMS
    ////////////////////////////////////////////////// Knots
	pDrObject->SetKnotType_S(KN_USER);
	pDrObject->SetWtType_S(WT_USER);
	////////////////////////////////////////////////////////////////////////
/*		A L R E A D Y  C O P I E D  F R O M  P A R E N T  I S O C U R V E	
	////////////////////////////////////////////////// Boundary
	m_BCL = BC_AUTO;
	pDrObject->SetBCL_S(m_BCL);
 	m_BCR = BC_AUTO;
	pDrObject->SetBCR_S(m_BCR);
	/////////////////////////////////////////////////////// Quadratic
	// Only One BC end is allowable:
	//	 ifLeft	- set tan.v for right 	 -99999.	
	//	 ifRight- set tan.v for left 	= -99999.
	/////////////////////////////////////////////
	VECTOR tan;
	tan.v[0] = -99999.;	
	////////
	pDrObject->SetTanR_S(tan);
//	pDrObject->SetTanL_S(tan);
	///////////////////////////////////////////////////////////////////
	pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	/////////////////////////////////////////////////// Already In
	int nDim 		= 3;			// NonRational
	pDrObject->SetnDim_S(nDim);
	///////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////
	return;
	
}
 
void CMI_GangC::SetDefaultInfoForCurveBase(CDrCurve* pDrObject)
{
	if(m_bNoDefault)
		return;
	/////////////////////
	// BC_N_KNOTs_N DIMS
    ////////////////////////////////////////////////// Knots
	pDrObject->SetKnotType_S(KN_AUTO);
	pDrObject->SetWtType_S(WT_UNIFORM);
	////////////////////////////////////////////////// Boundary
	m_BCL = BC_AUTO;
	pDrObject->SetBCL_S(m_BCL);
 	m_BCR = BC_AUTO;
	pDrObject->SetBCR_S(m_BCR);
	/////////////////////////////////////////////////////// Quadratic
	// Only One BC end is allowable:
	//	 ifLeft	- set tan.v for right 	 -99999.	
	//	 ifRight- set tan.v for left 	= -99999.
	/////////////////////////////////////////////
	VECTOR tan;
	tan.v[0] = -99999.;	
	////////
	pDrObject->SetTanR_S(tan);
//	pDrObject->SetTanL_S(tan);
	///////////////////////////////////////////////////////////////////
	pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	//////////////////////////////
	int nDim 		= 3;			// NonRational
	pDrObject->SetnDim_S(nDim);
	///////////////////////////////////////////////////
	return;
	
} 

//void CDlg_CIRR::SetInfoForDataBase(CDrCurve* pDrObject)
void CMI_GangC::SetInfoForCurveBase(CDrCurve* pDrObject,CList<int,int>* pElperSegList,
									BOOL bFinal)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pINodeList	= pDrObject->GetINodeList();
    int i,nData;  
	CString Nid;
	CDrNode* pDrNode;
	////////////////////////////////////
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed_S);
    /////////////////////////////////////// Reciprocate if Final( Rt.MouseButt)	
										 // makes it easy to del at intermediate
    nData = pINodeList->GetCount();
	if(bFinal)
	{
	   /////////////////
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
		///////////////////
	}
	////////////////////////////////////////////////////////////// interpolation
	pDrObject->SetData_S(nData);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(nData);
	pDrObject->SetOrder_S(m_nOrder_S);				// k
	//////////////////////////////////////////////// CP_BEZIER ALWAYS SINGLE SEGMENT
	m_nCurveSeg 	= nData - 1;
	if(m_CurveType_S == CP_BEZIER)
		m_nCurveSeg 	= 1;
	////////////////////////////////////////////////////////////////////////////////
	pDrObject->SetMaxBezSegments_S(m_nCurveSeg);
	///////////////////////////////////////////////////////////////////////////// Update :BSpline
	// These will be wrong if CP_BEZIER
	// But internally we dont use BSpline Info
	// ONLY USE BEZIER INFO
	// LATER We will handle Multiple Knot and then
	// Merge Bezier and Spline together
	//////////////////////////////////////////////////
	m_nControls 	= nData + m_nOrder_S - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nMaxDistinct 	= nData;
	m_nMaxTotal		= nData + (2 * m_nOrder_S - 2);	// n + k + 1 = nData + (2k - 2)
	if(m_bClosed_S)
	{
		m_nCurveSeg++;
		m_nMaxDistinct++;
		m_nMaxTotal++;
	}
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(m_nMaxDistinct);
	pDrObject->SetnMKnots_S(m_nMaxTotal);
	//////////////////////////////////////////////////////////////////////////////// BEZIER Info
	int nCon_BZ	= (m_nOrder_S - 1) * m_nCurveSeg + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed_S)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	/////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	////////////////////////////////////////////////////////////////////////// ReDistribute
	int nOut;
	//////////////////////////////////////////////////////////////////////////
	//	NOTE:
	//
	//		If single Segment & Linear:
	//			Allow RATIO of First to Last, etc.
	///////////////////////////////////////////////////////////// Linear/Single Segment
	BOOL bCancel = TRUE;
	////////////////////
//	if (m_nOrder_S == 2 && m_nCurveSeg == 1)
	if (m_nCurveSeg == 1)
	{
		/////////////////////
		if(m_Ratio_S == 1.0)		
			m_bUnifOT_S = TRUE;
		else			
			m_bUnifOT_S = FALSE;
		/////////////////////
		m_nMaxOSeg 	= pElperSegList->GetHead();
		///////////////////////////////////////// save
		//			 	in Inter_C1: make One Segment of Control Nodes
		//				with m_nMaxOSeg Output segment in it, i.e.,
		//				1 Segment in S-direction
		/////////////////////////////////////////////////////////////////////
		int i;
		//////
		m_pOSeg = new int[m_nCurveSeg];
		/////////////////////
		m_pOSeg[0] = m_nMaxOSeg;
		/////////////////////
		if(m_bUnifOT_S)			// Uniform and OK
		{
			m_pODis = new double[m_nMaxOSeg+1];
			///////////////////////////////
			double delt;
			delt	= 1.0/m_nMaxOSeg;
			////////////////
			m_pODis[0] = 0.;
			////////////////
			for (i=1;i<=m_nMaxOSeg;i++)
			{
				m_pODis[i] = m_pODis[i-1] + delt;
			}
			/////////////////////////////////////// Uniform needed for Triangular Patch
//			pDrObject->SetSegmentCount_S(m_nMaxOSeg); 	// for Old Compatibility
			pDrObject->SetOutSegUnif_S(m_nMaxOSeg); 	// for Old Compatibility
		}
		else								// NonUniform
		{
			m_pODis = new double[m_nMaxOSeg+1];
			/////////////////////////////////////////////////////////
			// NOTE:	allows Unequal Generation
			//		# of Segments = n + 1			= nSegs 
			//		SPACEs between pts. are:
			//			x, x+a, x+2a, x+3a, ..., x+na
			//		with
			//			x = 2/(segs*(ratio+1))
			//			a = (x*(ratio-1))/(segs-1)
			//
			//////////////////////////////////////////////////////////
			double x	= 2./(m_nMaxOSeg * (m_Ratio_S + 1));
			double a	= (m_nMaxOSeg == 1)?0.:(x * (m_Ratio_S-1))/(m_nMaxOSeg-1);
			//////////////////////////// save
			int i;
			//////
			m_pODis[0] = 0.;
			////////////////
			for (i=0;i<m_nMaxOSeg;i++)
			{
				///////////////////
				m_pODis[i+1] = m_pODis[i] + x + i * a;
				///////////////////
			}
		}
		////////////////////////////////////////////// Total Evaluation Pts
		nOut = m_nMaxOSeg + 1;
		////////////////////////////////////////////////
		pDrObject->SetDis_tPointer_S(m_pODis);	// Number of Outputs for
													// each Curve Segment
	}	
	///////////////////////////////////////////////////////////////// Other Cases:m_nCurveSeg>1
	else															
	{
		///////////////////////////////////////////// Check if Uniform
		m_bUnifOT_S = TRUE;
		int nElems,nElemsPrev;
		///////////////////////////// go over the list
		i = -1;
		for (POSITION posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
		{
			i++;
			////
			nElems = pElperSegList->GetNext(posI); 
			if(!i)
				nElemsPrev = nElems;
    		///////////////////////////////
			if(nElemsPrev != nElems)
			{
				m_bUnifOT_S = FALSE;
				break;
			}
		}
		///////////////////////////////////////
		m_pOSeg = new int[m_nCurveSeg];
		///////////////////////////////////////// save for Uniform
		if(m_bUnifOT_S)
		{
			m_nMaxOSeg 	= pElperSegList->GetHead();
			///////////////////////////////////////
			for (i=0;i<m_nCurveSeg;i++)
			{
				m_pOSeg[i] = m_nMaxOSeg;
			}
			/////////////////////////////////////// Uniform needed for Triangular Patch
//			pDrObject->SetSegmentCount_S(m_nMaxOSeg); 	// for Old Compatibility
			pDrObject->SetOutSegUnif_S(m_nMaxOSeg); 	// for Old Compatibility

		}
		///////////////////////////////////////// save for NonUniform
		else
		{
			i = -1;
			for (POSITION posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
			{
				i++;
				////
				m_pOSeg[i] = pElperSegList->GetNext(posI);
			}
		}
		////////////////////////////////////////////// Total Evaluation Pts
		nOut = 0;
		for (i=0;i<m_nCurveSeg;i++)
			nOut += *(m_pOSeg+i);
		nOut++;
		///////////////////////////
		m_nMaxOSeg = nOut -1;
	}
	//////////////////////	
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	//////////////////////////////////////////		 
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg);	// Number of Output Segments for Entire Curve
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	////////////////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
}
 
int CMI_GangC::SetBZ_Knots(CDrCurve* pCurve)
{
	int i;
	//////////////////////////////////////////////////////// Setup Bezier Knots
	CDListMgr* pINList = pCurve->GetINodeList();
	int nData = pINList->GetCount();
	int nData1 = pCurve->GetData_S();
	if(nData != nData1)
	{
		AfxMessageBox("Internal ERROR\nCMC_Bezier::SetBZ_Knots\nnData != nData1");
		return MA_ERROR;
	}
	pWORLD inData = new WORLD[nData];
	/////
	SetUpINodes(pINList,inData,nData);
	/////
	int nKnots_S = nData;
	pDOUBLE pKnot_S = new double[nKnots_S];	// will be deleted in DrCurve
	KNOT KnotType_S = KN_AUTO;	// chordlength for Cubic Upward
	double dLast;
	/////
	switch(nData)
	{
		case 2:	// Linear
			pKnot_S[0] = 0.0;
			pKnot_S[1] = 1.0;
			break;
		case 3:	// Quad
			pKnot_S[0] = 0.0;
			pKnot_S[1] = 0.5;
			pKnot_S[2] = 1.0;
			break;
		default:	// Other
			SetupKnots(inData,KnotType_S,pKnot_S,nKnots_S);
			///////////////////////////////////////////////////// Scale between 0.0 & 1.0
			dLast = pKnot_S[nKnots_S-1];
			for(i=0;i<nKnots_S;i++)
				pKnot_S[i] /= dLast;
	}
	///////////////////////////////////////////////////// Save
	pDOUBLE pOldKnots = pCurve->GetpKnots_S();
	if(pOldKnots)
		delete [] pOldKnots;
	///	
	pCurve->SetnKnots_S(nKnots_S);
	pCurve->SetpKnots_S(pKnot_S);	// pointer
	//////////////////////////////////////////
	delete [] inData;
	////////////////////////////////////////////////////
	return MA_OK;
}

void CMI_GangC::SetInfoForBezierPtsBase(CDrCurve* pDrObject,CList<int,int>* pElperSegList,
									BOOL bFinal)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
	CDListMgr* pINodeList	= pDrObject->GetINodeList();
    int i,nData;  
	CString Nid;
	CDrNode* pDrNode;
	////////////////////////////////////
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetBezierType(m_BezierType);
	pDrObject->SetObjectID(m_CurveID);	
	pDrObject->SetClosed_S(m_bClosed_S);
    /////////////////////////////////////// Reciprocate if Final( Rt.MouseButt)	
										 // makes it easy to del at intermediate
    nData = pINodeList->GetCount();
	if(bFinal)
	{
	   /////////////////
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
		///////////////////
	}
	////////////////////////////////////////////////////////////// interpolation
	pDrObject->SetData_S(nData);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(nData);
	pDrObject->SetOrder_S(m_nOrder_S);				// k
	//////////////////////////////////////////////// CP_BEZIER ALWAYS SINGLE SEGMENT
	m_nCurveSeg 	= 1;					// L = 1
	//////////////////////////////////////////////////
	m_nControls 	= m_nOrder_S;		// Bezier Controls	        
	m_nMaxDistinct 	= m_nCurveSeg + 1;	// Bezier nKnots = 2 
	if(m_bClosed_S)
	{
		m_nCurveSeg++;
		m_nMaxDistinct++;
		m_nMaxTotal++;
	}
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nControls);	//	
	pDrObject->SetnKnots_S(m_nMaxDistinct);
	//////////////////////////////////////////////////////////////////////////////// BEZIER Info
	int nCon_BZ	= (m_nOrder_S - 1) * m_nCurveSeg + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed_S)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	/////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	////////////////////////////////////////////////////////////////////////// BZKnots
	SetBZ_Knots(pDrObject);	// BZKnots
	////////////////////////////////////////////////////////////////////////// ReDistribute
	int nKnots_S	= pDrObject->GetnKnots_S();
	pDOUBLE pKnot_S	= pDrObject->GetpKnots_S();	// pointer
	//////////////////////////////////////////////////////////////////////////
	//	NOTE:
	//
	//		If single Segment & Linear:
	//			Allow RATIO of First to Last, etc.
	///////////////////////////////////////////////////////////// Linear Segment
	BOOL bCancel = TRUE;
	////////////////////
	if (m_nOrder_S == 2)
	{
		/////////////////////
		if(m_Ratio_S == 1.0)		
			m_bUnifOT_S = TRUE;
		else			
			m_bUnifOT_S = FALSE;
		///////////////////////
		m_nMaxOSeg 	= pElperSegList->GetHead();
		//////////////////////	
		pDrObject->SetRatio_S(m_Ratio_S);					
		pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
		///////////////////////////////////////// save
		//			 	in Inter_C1: make One Segment of Control Nodes
		//				with m_nMaxOSeg Output segment in it, i.e.,
		//				1 Segment in S-direction
		/////////////////////////////////////////////////////////////////////
		int i;
		//////
		m_pOSeg = new int[1];
		/////////////////////
		m_pOSeg[0] = m_nMaxOSeg;
		/////////////////////
		if(m_bUnifOT_S)			// Uniform and OK
		{
			m_pODis = new double[m_nMaxOSeg+1];
			///////////////////////////////
			double delt;
			delt	= 1.0/m_nMaxOSeg;
			////////////////
			m_pODis[0] = 0.;
			////////////////
			for (i=1;i<=m_nMaxOSeg;i++)
			{
				m_pODis[i] = m_pODis[i-1] + delt;
			}
			/////////////////////////////////////// Uniform needed for Triangular Patch
//			pDrObject->SetSegmentCount_S(m_nMaxOSeg); 	// for Old Compatibility
			pDrObject->SetOutSegUnif_S(m_nMaxOSeg); 	// for Old Compatibility
		}
		else								// NonUniform
		{
			m_pODis = new double[m_nMaxOSeg+1];
			/////////////////////////////////////////////////////////
			// NOTE:	allows Unequal Generation
			//		# of Segments = n + 1			= nSegs 
			//		SPACEs between pts. are:
			//			x, x+a, x+2a, x+3a, ..., x+na
			//		with
			//			x = 2/(segs*(ratio+1))
			//			a = (x*(ratio-1))/(segs-1)
			//
			//////////////////////////////////////////////////////////
			double x	= 2./(m_nMaxOSeg * (m_Ratio_S + 1));
			double a	= (m_nMaxOSeg == 1)?0.:(x * (m_Ratio_S-1))/(m_nMaxOSeg-1);
			//////////////////////////// save
			int i;
			//////
			m_pODis[0] = 0.;
			////////////////
			for (i=0;i<m_nMaxOSeg;i++)
			{
				///////////////////
				m_pODis[i+1] = m_pODis[i] + x + i * a;
				///////////////////
			}
		}
	}	
	///////////////////////////////////////////////////////////////// Other Cases:Quadratic/Cubic
	else															
	{
		POSITION posI;
		//////////////
		m_Ratio_S	= 1.0;
		m_bUnifOT_S = FALSE;
		//////////////////////	
		pDrObject->SetRatio_S(m_Ratio_S);					
		pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
		///////////////////////////////////////// save
		//			 	in Inter_C1: make One Segment of Control Nodes
		//				with m_nMaxOSeg Output segment in it, i.e.,
		//				1 Segment in S-direction
		/////////////////////////////////////////////////////////////////////
		///////////////////////////// go over the list
		m_nMaxOSeg = 0;
		for (posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
			m_nMaxOSeg += pElperSegList->GetNext(posI); 
		///////////////////////////////////////
		m_pOSeg = new int[1];
		/////////////////////
		m_pOSeg[0]	= m_nMaxOSeg;
		m_pODis		= new double[m_nMaxOSeg+1];
		////////////////
		m_pODis[0] = 0.;
		///////////////////////////////////////////////// go over List
		int j=0,k=0,nElems;
		double delt;
		for (posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
		{
			nElems = pElperSegList->GetNext(posI);
			///////////////////////////////
			k++;
			delt	= (pKnot_S[k] - pKnot_S[k-1])/nElems;
			////////////////
			for (i=1;i<=nElems;i++)
			{
				j++;
				m_pODis[j]	= m_pODis[j-1] + delt;
			}
			/////////////////////
		}
		/////////////////////////
		if(j != m_nMaxOSeg)
		{
			AfxMessageBox(
				"Internal ERROR:\nCMI_GangC::SetInfoForBezierPtsBase\nj != m_nMaxOSeg");
			return;
		}
	}		
	//////////////////////////////////////////		 
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg);	// Number of Output Segments
//	pDrObject->SetSegmentCount_S(1); 	// for Old Compatibility per patch
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_tPointer_S(m_pODis);	// Number of Outputs for
												// each Curve Segment
	////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMaxOSeg + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

int CMI_GangC::SetupKnots(pWORLD Data, enum KNOT KnotType, pDOUBLE Knot,int nKnots) 
{

	//////////////////////////////////////////////////////////////////////
	//	KNOTS Generated are SIMPLE i.e., NO MULTIPLICITY OTHER THAN 1	//
	// 	OPEN:                                                           //
	//			nKnots = nData											//
	// 	CLOSED:                                                           //
	//			nKnots = nData + 1											//
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j,k,nSize;
		//////////
		sprintf(buf,"CMC_Circle::SetupKnots");
		AfxMessageBox(*str);
		///////////////////
		nSize = nKnots;
		if(m_bClosed_S)
			nSize--;
		j = sprintf(buf,"Data[%d]\n",nSize);
		for(k=0;k<nSize;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f\n", k,
		   					Data[k].x, Data[k].y, Data[k].z);
		}
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
    }
#endif				
	int k;
	////////////////////////////////////////////////////////////// Uniform or User
	if(KnotType == KN_UNIFORM)
	{
		for(k=0;k<nKnots;k++)
			*(Knot+k) = k;
		return 0;
	}
	else
	if(KnotType == KN_USER)
		return 0;			// dont need to do anything
	////////////////////////////////////////////////////////////// Non Uniform
	double delta;
	/////////////
	Knot[0] = 0.0;		// arbitrary
	////////////////////////////////
	int L = nKnots - 1;
	///////////////////
	for(k=0;k<L;k++)
	{
		if(m_bClosed_S)						
			delta = sqrt( 
							( Data[(k+1)%L].x - Data[k].x ) * ( Data[(k+1)%L].x - Data[k].x) +
							( Data[(k+1)%L].y - Data[k].y ) * ( Data[(k+1)%L].y - Data[k].y) +
							( Data[(k+1)%L].z - Data[k].z ) * ( Data[(k+1)%L].z - Data[k].z)
						);
		else						
			delta = sqrt( 
							( Data[k+1].x - Data[k].x ) * ( Data[k+1].x - Data[k].x) +
							( Data[k+1].y - Data[k].y ) * ( Data[k+1].y - Data[k].y) +
							( Data[k+1].z - Data[k].z ) * ( Data[k+1].z - Data[k].z)
						);
		////////////////						
		switch(KnotType)
		{
			case KN_FOLEY:              // fall thro' for now
			case KN_AUTO:
			case KN_CHORDLENGTH:
			
				Knot[k+1] = Knot[k] + delta;
				break;
					
			case KN_CENTRIPETAL:
			
				Knot[k+1] = Knot[k] + sqrt(delta);
				break;
			
		}
	}	
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 0
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j,k;
		///////////////////
		j = sprintf(buf,"Knot[%d]\n",nKnots);
		for(k=0;k<nKnots;k++)
		{
		   j += sprintf( buf + j, "%2d %7.2f\n", k,Knot[k] );
		}
		AfxMessageBox(*str);
    	///////////////////
    	delete str;
    }
#endif				
	/////////////
	return MA_OK;
}						

//////////////////////////////////////////////////////////////////////////// Poting Helper
void CMI_GangC::Serialize(CArchive& ar)
{

	CMI_GangN::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_GangC:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_GangC:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


