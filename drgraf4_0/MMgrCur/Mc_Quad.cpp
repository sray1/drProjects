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
#include "NewObjs.h"
#include "DListMgr.h"
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
#include "Inter_C2.h"
 
#include "MC_Quad.h" 

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
IMPLEMENT_SERIAL(CMC_Quad,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Quad::CMC_Quad()
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

CMC_Quad::~CMC_Quad()
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

CDrCurve* CMC_Quad::GoDoIt() 
{
	m_CurveType_S	= CP_QUADRATIC;
	m_nOrder_S		= 3;
	///////////////////////////////
	m_pDrCurve 	= GetInfo(2);                  	// CCon Dialog
	//////////////////////////////////////////////////////////////////// Go Generate	
	if(m_pDrCurve)
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(80);
			
		sprintf(buf,"Got All %d Interpolation Nodes",m_pDrCurve->GetINodeList()->GetCount());
		/////////////////////////	
		AfxMessageBox(*str);
		/////////////////////////
		str->ReleaseBuffer();
		delete str;
	}	
	else
		return (CDrCurve*)NULL;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	InterPolate_C2(TRUE);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return (CDrCurve*)NULL;
	/////////////////////
	return m_pDrCurve;
}			

int CMC_Quad::GoDoIt(CDrCurve* pCurve,BOOL bFinal)  
{
	m_CurveType_S	= CP_QUADRATIC;
	m_nOrder_S		= 3;
	///////////////////////////////
	m_pDrCurve 			= pCurve;
	///////////////////////////////////////////////////// stuff from getinfo
	m_nMaxCurveINodes_S	= m_pDrCurve->GetMaxINodes_S();
//	m_nSegsOut_S		= m_pDrCurve->GetSegmentCount_S();
	m_bClosed_S			= m_pDrCurve->IsClosed_S();
	//////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	InterPolate_C2(bFinal);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	//////////////////
	return 0;
}			

CDrCurve* CMC_Quad::GetInfo(int nButton)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////////////////
	CMCurMgr 	MCurMgr;
	CMCurMgr* 	pMCurMgr = &MCurMgr;
	CString		Cid;
	int index;
	///////////////////////////////////////////////////
	if(nButton ==1)		//Left Button
		if (pMCurMgr->DoModal_Cur_I_LB(&Cid,0) == IDCANCEL)
			return (CDrCurve*)NULL;
	if(nButton ==2)		//Right Button
	{
		/////////////////////////////////////////////////////////
		if (pMCurMgr->DoModal_Cur_I_RB(&Cid,m_nOrder_S) == IDCANCEL)
			return (CDrCurve*)NULL;
	}				 
    /////////////////////////////////////////////////////// update
	index 				= pObjectMgr->
							GetObjectIndexfromKey(CURVE,Cid,1);
	if(index<0)
		return (CDrCurve*)NULL;
	else
	{
		pDListMgr 			= pObjectMgr->GetObjectList(CURVE);
		CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_nMaxCurveINodes_S	= pDrCurve->GetMaxINodes_S();
//		m_nSegsOut_S		= pDrCurve->GetSegmentCount_S();
		m_bClosed_S			= pDrCurve->IsClosed_S();
		////////////////		
		return pDrCurve;
	}
}			
			
int CMC_Quad::InterPolate_C2(BOOL bFinal)
{
	CInter_C2	Inter_C2;			// Curve Interpolate: Cubic
	////////////////////////////////////////////// Set Memory
	if(C2_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(C2_PrepInterpolation(&Inter_C2)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(Inter_C2.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(C2_PostInterpolation(&Inter_C2,bFinal)<0)
		return -1;
	///////////////////////
	return 0; 
}

int CMC_Quad::C2_SetMemory()
{
    
    ///////////////////////////////////////////////////////// Memory
    m_pKnot_S	= m_pDrCurve->GetpKnots_S();
    if(m_pKnot_S == NULL)
	{
		m_pKnot_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pKnot_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	/////////////////////////////////////////		
	m_pWts_DT_S = m_pDrCurve->GetpWts_DT_S();
    if(m_pWts_DT_S == NULL)
    {
		m_pWts_DT_S = new double[m_pDrCurve->GetnKnots_S()];
		if(!m_pWts_DT_S)
		{
			AfxMessageBox("ERROR:Interpolate -Memory Failure!");
			m_MemErr = -1;
			return m_MemErr;
		}
	}
	//////////////////////////////////////////////////////////////////////// Setup Data
	m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	if(!m_pData)
	{
		AfxMessageBox("ERROR:Interpolate -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMC_Quad::C2_PrepInterpolation(CInter_C2* pInter_C2)
{
	////////////
	int CSeg_DT	= m_pDrCurve->GetData_S() - 1;				// L
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
		sprintf(buf,"CMC_Quad::C2_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,"nData_S\t = %d\n",m_pDrCurve->GetData_S());
		j += sprintf( buf + j, "nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, "bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, "nDim\t = %d\n",m_pDrCurve->GetnDim_S());
		j += sprintf( buf + j, "Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, "CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, "nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
		j += sprintf( buf + j, "nKnots\t = %d\n",m_pDrCurve->GetnKnots_S());
		j += sprintf( buf + j, "nMKnots\t = %d\n",m_pDrCurve->GetnMKnots_S());
		j += sprintf( buf + j, "nConBZ\t = %d\n",m_pDrCurve->GetnCon_BZ_S());
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
	///////////////////////////////////	
	BOUNDARY BCL= m_pDrCurve->GetBCL_S();
	BOUNDARY BCR= m_pDrCurve->GetBCR_S();
	VECTOR TanL,TanR;
	if(BCL == BC_TANGENT)
		TanL 	= m_pDrCurve->GetTanL_S();
	if(BCL == BC_TANGENT)
		TanR 	= m_pDrCurve->GetTanR_S();
	//////////////////////////////////////////////////////////
	pDOUBLE pWtsDT,pKnot;
	KNOT KnTyp  = m_pDrCurve->GetKnotType_S();
	WEIGHT WtTyp= m_pDrCurve->GetWtType_S();
	if(WtTyp == WT_USER)
		pWtsDT 	= m_pDrCurve->GetpWts_DT_S();	//  
	if(KnTyp == KN_USER)
		pKnot 	= m_pDrCurve->GetpKnots_S();	//  
	//////////////////////////////////////////////////////////
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pInter_C2->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pInter_C2->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pInter_C2->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pInter_C2->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	pInter_C2->SetKnotType_S(m_pDrCurve->GetKnotType_S());
	pInter_C2->SetWtType_S(m_pDrCurve->GetWtType_S());
	pInter_C2->SetBCL(m_pDrCurve->GetBCL_S());
	pInter_C2->SetBCR(m_pDrCurve->GetBCR_S());
	pInter_C2->SetTanL(m_pDrCurve->GetTanL_S());
	pInter_C2->SetTanR(m_pDrCurve->GetTanR_S());
	//////////////////////////////////////////////////////////
	pInter_C2->SetpWts_DT_S(m_pDrCurve->GetpWts_DT_S());	//  
	pInter_C2->SetpKnot_S(m_pDrCurve->GetpKnots_S());	//
	//////////////////////////////////////////////////////////
	pInter_C2->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pInter_C2->SetnDim_S(m_pDrCurve->GetnDim_S());
	pInter_C2->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pInter_C2->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pInter_C2->SetnSeg_BS_S(nSeg_BS);
	pInter_C2->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pInter_C2->SetnKnots_S(m_pDrCurve->GetnKnots_S());
	pInter_C2->SetnMKnots_S(m_pDrCurve->GetnMKnots_S()); 
	pInter_C2->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes_S
	////////////////////////////////////////////// Send Memory
	pInter_C2->SetpData(m_pData);
	pInter_C2->SetpMKnot_S(m_pMKnot_S);
	pInter_C2->SetpKnot_S(m_pKnot_S);
	pInter_C2->SetpWts_DT_S(m_pWts_DT_S);
	pInter_C2->SetpWts_BS_S(m_pWts_BS_S);
	pInter_C2->SetpWts_BZ_S(m_pWts_BZ_S);
	pInter_C2->SetpCon_BS_S(m_pCon_BS_S);
	pInter_C2->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMC_Quad::C2_PostInterpolation(CInter_C2* pInter_C2,BOOL bFinal)
{

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
	CString		Nid,CurveID;
	int			nChLen;
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData				= pInter_C2->GetpData();
	m_pMKnot_S			= pInter_C2->GetpMKnot_S();
	m_pKnot_S			= pInter_C2->GetpKnot_S();
	m_pWts_DT_S			= pInter_C2->GetpWts_DT_S();
	m_pWts_BS_S			= pInter_C2->GetpWts_BS_S();
	m_pWts_BZ_S			= pInter_C2->GetpWts_BZ_S();
	m_pCon_BS_S			= pInter_C2->GetpCon_BS_S();
	m_pCon_BZ_S			= pInter_C2->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes_S 	= m_pDrCurve->GetnCon_BZ_S();
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
//092798		pAddNode = PostNode(Nid,LocalPos,TRUE,FALSE);	// Create DrCNode
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
#ifdef _DEBUG					
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
#endif	 
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory				
	m_pDrCurve->SetpKnots_S(m_pKnot_S);
	m_pDrCurve->SetpWts_DT_S(m_pWts_DT_S);
	//////////////////////////////////////
	if(m_pDrCurve->GetnDim_S() == 3)		// Non-Rational
	{				
// 		already assigned
//		m_pWts_BZ_S = new double[m_nMaxCurveCNodes_S]; // needed later for TensorProduct Patch
		for(s=0;s<m_nMaxCurveCNodes_S;s++)
			m_pWts_BZ_S[s] = 1.0;
		//////////////////////////////////////		
		m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S); 
	}
	else
		m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S);	// Rational Weights
	/////////////////////////////////////////////////////////////// Now ReleaseMemory
	if(m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}	
	if(m_pMKnot_S)
	{
		delete [] m_pMKnot_S;
		m_pMKnot_S = NULL;
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

void CMC_Quad::Serialize(CArchive& ar)
{

	CMI_GangC::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Quad:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Quad:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
