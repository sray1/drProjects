// Rotate.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

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
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "MC_Bezier.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
#define	NUM_LEN				12 
#define MIN_INODES_CURVE	2
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////
IMPLEMENT_SERIAL(CMC_Bezier,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Bezier::CMC_Bezier()
{
    /////////////////////////////////////////// Curve
	m_nMaxCurveINodes_S	= MIN_INODES_CURVE;
	m_bClosed_S			= FALSE;
	m_nSegsOut_S		= 0;
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

CMC_Bezier::~CMC_Bezier()
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

int CMC_Bezier::GoDoIt(CDrCurve* pCurve,BOOL bFinal) 
{
	///////////////////////////////
	m_pDrCurve 			= pCurve;
	///////////////////////////////
	m_CurveType_S	= CP_BEZIER;
	m_nOrder_S		= m_pDrCurve->GetOrder_S();
	///////////////////////////////////////////////////// stuff from getinfo
	m_nMaxCurveINodes_S	= m_pDrCurve->GetMaxINodes_S();
//	m_nSegsOut_S		= m_pDrCurve->GetSegmentCount_S();
	m_bClosed_S			= m_pDrCurve->IsClosed_S();
	//////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	InterPolate_BZ(bFinal);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	//////////////////
	return 0;
}			
			
int CMC_Bezier::InterPolate_BZ(BOOL bFinal)
{
	int nOrder = m_pDrCurve->GetOrder_S();
	////////////////////////////////////////////// Set Memory
	if(C1_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	int nData = m_pINodeList->GetCount(); 
	if(SetUpINodes(m_pINodeList,m_pData,nData)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	switch(nOrder)
	{
		case 2:
			if(BZ_Interpolation_C1(m_pCon_BZ_S,m_pData,nData)<0)
				return MA_ERROR;
			break;
		case 3:
			if(BZ_Interpolation_C2(m_pCon_BZ_S,m_pData,nData)<0)
				return MA_ERROR;
			break;
		case 4:
			if(BZ_Interpolation_C3(m_pDrCurve,m_pCon_BZ_S,m_pData,nData)<0)
				return MA_ERROR;
			break;
		default: // general Order = M (Not Implemented Yet)
			return MA_ERROR;
	}
	////////////////////////////////////////////// Get Interpolation Result
	if(BZ_PostInterpolation(m_pCon_BZ_S,m_pData,nData,bFinal)<0)
		return MA_ERROR;
	///////////////////////
	return MA_OK; 
}
	
int CMC_Bezier::C1_SetMemory()
{
    
    ///////////////////////////////////////////////////////// Memory
	m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	/////////////		
	if(!m_pData)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	////////////
	m_pCon_BZ_S	= new WORLD[m_pDrCurve->GetData_S()];
	/////////////		
	if(!m_pCon_BZ_S)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return MA_OK;
    
}
	 		
int CMC_Bezier::BZ_Interpolation_C1(pWORLD pCon_BZ_S,pWORLD pData,int nData)
{
	int i;
	///////////////
	if(nData != 2)
	{
		AfxMessageBox("Internal ERROR:\nCMC_Bezier::BZ_Interpolation_C1\nnData != 2!");
		return MA_ERROR;
	}
    /////////////
	for(i=0;i<nData;i++)	// b0,b1
	{
		(pCon_BZ_S+i)->x = (pData+i)->x; 
		(pCon_BZ_S+i)->y = (pData+i)->y; 
		(pCon_BZ_S+i)->z = (pData+i)->z;
	}	
	////////////////////////////////////////////////////
	return MA_OK;
}
	 		
int CMC_Bezier::BZ_Interpolation_C2(pWORLD pCon_BZ_S,pWORLD pData,int nData)
{
	if(nData != 3)
	{
		AfxMessageBox("Internal ERROR:\nCMC_Bezier::BZ_Interpolation_C2\nnData != 3!");
		return MA_ERROR;
	}
    //////////////////////////////////// b0
	(pCon_BZ_S+0)->x = (pData+0)->x; 
	(pCon_BZ_S+0)->y = (pData+0)->y; 
	(pCon_BZ_S+0)->z = (pData+0)->z; 
	//////////////////////////////////// b2
	(pCon_BZ_S+2)->x = (pData+2)->x; 
	(pCon_BZ_S+2)->y = (pData+2)->y; 
	(pCon_BZ_S+2)->z = (pData+2)->z; 
	//////////////////////////////////// b1
	(pCon_BZ_S+1)->x = 2.*(pData+1)->x - ((pData+0)->x + (pData+2)->x)/2; 
	(pCon_BZ_S+1)->y = 2.*(pData+1)->y - ((pData+0)->y + (pData+2)->y)/2; 
	(pCon_BZ_S+1)->z = 2.*(pData+1)->z - ((pData+0)->z + (pData+2)->z)/2; 
	////////////////////////////////////////////////////
	return MA_OK;
}
	 		
int CMC_Bezier::BZ_Interpolation_C3(CDrCurve* pCurve,pWORLD pCon_BZ_S,pWORLD pData,int nData)
{
	C3DMath Math3D;
	//////////////
	if(nData != 4)
	{
		AfxMessageBox("Internal ERROR:\nCMC_Bezier::BZ_Interpolation_C3\nnData != 4!");
		return MA_ERROR;
	}
    //////////////////////////////////// b0
	(pCon_BZ_S+0)->x = (pData+0)->x; 
	(pCon_BZ_S+0)->y = (pData+0)->y; 
	(pCon_BZ_S+0)->z = (pData+0)->z; 
	//////////////////////////////////// b3
	(pCon_BZ_S+3)->x = (pData+3)->x; 
	(pCon_BZ_S+3)->y = (pData+3)->y; 
	(pCon_BZ_S+3)->z = (pData+3)->z; 
	///////////////////////////////////////////////////////////////////////////// b1 & b2
/*
	/////////////////////////////////// parameter
	WORLD dum;
	double t0,t1,t2,t3,dLen;
	////////////////////////
	t0 = 0;
	//
	Math3D.Sub3DPts((pData+1), (pData+0), &dum);
	dLen = Math3D.Len3DPts(&dum);
	t1 = t0 + dLen;
	//
	Math3D.Sub3DPts((pData+2), (pData+1), &dum);
	dLen = Math3D.Len3DPts(&dum);
	t2 = t1 + dLen;
	//
	Math3D.Sub3DPts((pData+3), (pData+2), &dum);
	dLen = Math3D.Len3DPts(&dum);
	t3 = t2 + dLen;
	///////////////
	t1 /= t3;
	t2 /= t3;
	t3	= 1.0;
*/
	/////////////////////////////////// Get BZKnots
	double t0,t1,t2,t3;
	pDOUBLE pBZKnots = pCurve->GetpKnots_S();
	//
	t0 = pBZKnots[0]; 
	t1 = pBZKnots[1]; 
	t2 = pBZKnots[2]; 
	t3 = pBZKnots[3];
	/////////////////////////////////// Bernsteins
	WORLD p,q;
	double B0t1,B3t1,B0t2,B3t2;
	double B1t1,B2t1,B1t2,B2t2;
	double r;
	///////////////////////////
	B0t1	= (1.- t1)*(1.- t1)*(1.- t1); 	
	B3t1	=	t1*t1*t1; 	
	B0t2	= (1.- t2)*(1.- t2)*(1.- t2); 	
	B3t2	=	t2*t2*t2; 	
	////
	B1t1	= 3.* t1*(1.- t1)*(1.- t1); 	
	B2t1	= 3.* t1*t1*(1.- t1); 	
	B1t2	= 3.* t2*(1.- t2)*(1.- t2); 	
	B2t2	= 3.* t2*t2*(1.- t2);
	r		= 1./(B1t1*B2t2 - B1t2*B2t1); 
	////
	p.x = (pData+1)->x - B0t1*((pData+0)->x) - B3t1*((pData+3)->x); 
	p.y = (pData+1)->y - B0t1*((pData+0)->y) - B3t1*((pData+3)->y); 
	p.z = (pData+1)->z - B0t1*((pData+0)->z) - B3t1*((pData+3)->z);
	//
	q.x = (pData+2)->x - B0t2*((pData+0)->x) - B3t2*((pData+3)->x); 
	q.y = (pData+2)->y - B0t2*((pData+0)->y) - B3t2*((pData+3)->y); 
	q.z = (pData+2)->z - B0t2*((pData+0)->z) - B3t2*((pData+3)->z);
	//////////////////////////////////////////////////////////////////////// b1
	(pCon_BZ_S+1)->x = (B2t2*p.x - B2t1*q.x) * r; 
	(pCon_BZ_S+1)->y = (B2t2*p.y - B2t1*q.y) * r; 
	(pCon_BZ_S+1)->z = (B2t2*p.z - B2t1*q.z) * r; 
	//////////////////////////////////////////////////////////////////////// b2
	(pCon_BZ_S+2)->x = (B1t1*q.x - B1t2*p.x) * r; 
	(pCon_BZ_S+2)->y = (B1t1*q.y - B1t2*p.y) * r; 
	(pCon_BZ_S+2)->z = (B1t1*q.z - B1t2*p.z) * r; 
	////////////////////////////////////////////////////
	return MA_OK;
}
	 		
int CMC_Bezier::BZ_PostInterpolation(pWORLD pCon_BZ_S,pWORLD pData,int nData,BOOL bFinal)
{
	//	Weights can be != 1.0 in the event this curve extracted from Patch etc
	//	So, save the Data Wts	
	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pWts_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		CurveID;
	int			nChLen;
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData 			= pData;
	m_pOut				= pCon_BZ_S; 
	////////////////////////////////////////////////////
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes_S	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<m_nMaxCurveCNodes_S; s++)
	{
		///////////////////////////////////////// CREATE	
//		Nid		= CurveID.Left(nChLen);
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d%d",CurveID,s,t);
		////////////////////////////////////
		j = t*m_nMaxCurveCNodes_S + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		/////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList
//		pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
		//////////
		if(bFinal)
		{
			//011199: DONOT Reciprocate:PRIVATE
			//////////////////////////////////////////// if New Node Change Level/Reciprocate
//			if(pAddNode->GetObjectID() == Nid)
//			{
				//////////////////////////////////////// Reciprocate
//				pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
				////////
//			}
		}
		////////
	}				
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = m_pCNodeList->GetCount();
	CDListMgr* pList = m_pCNodeList;
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
	} 
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory
	m_pWts_BZ_S = new double[m_nMaxCurveCNodes_S]; // needed later for TensorProduct Patch
	pDOUBLE pWts_DT = m_pDrCurve->GetpWts_DT_S();  // Data Wts
	///////////////
	for(s=0;s<m_nMaxCurveCNodes_S;s++)
	{
		if(pWts_DT)
			m_pWts_BZ_S[s] = pWts_DT[s];
		else
			m_pWts_BZ_S[s] = 1.0;
	}
	//////////////////////////////////////		
	m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
/*
	ALREADY DONE in SetInfoForBZBase to comute Output Controls
	//////////////////////////////////////////////////////// Setup Knots
	CDListMgr* pINList = m_pDrCurve->GetINodeList();
	int nData1 = m_pDrCurve->GetData_S();
	if(nData != nData1)
	{
		AfxMessageBox("Internal ERROR\nCMC_Bezier::C1_PostInterpolation\nnData != nData1");
		return MA_ERROR;
	}
	pWORLD inData = new WORLD[nData];
	/////
	SetUpINodes(pINList,inData,nData);
	/////
	m_nKnots_S = m_pDrCurve->GetnKnots_S();
	pDOUBLE m_pKnot_S = new double[m_nKnots_S];	// will be deleted in DrCurve
	/////
	m_KnotType_S = KN_AUTO;	// chordlength
	SetupKnots(inData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
	///////////////////////////////////////////////////// Save
	m_pDrCurve->SetpKnots_S(m_pKnot_S);	// pointer
	//////////////////////////////////////////
	delete [] inData;
*/
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
	////////////////////////////////////////////////////
	return MA_OK;
}

void CMC_Bezier::Serialize(CArchive& ar)
{

	CMI_GangC::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Bezier:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Bezier:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
