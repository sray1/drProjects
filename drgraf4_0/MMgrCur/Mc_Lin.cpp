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
#include "Inter_C1.h"
 
#include "MC_Lin.h" 

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
IMPLEMENT_SERIAL(CMC_Lin,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Lin::CMC_Lin()
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

CMC_Lin::~CMC_Lin()
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

CDrCurve* CMC_Lin::GoDoIt() 
{
	m_CurveType_S	= CP_LINEAR;
	m_nOrder_S		= 2;
	///////////////////////////////
	m_pDrCurve 	= GetInfo(2);                  	// CCon Dialog
	//////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
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
	InterPolate_C1(TRUE);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return (CDrCurve*)NULL;
	/////////////////////
	return m_pDrCurve;
}			

int CMC_Lin::GoDoIt(CDrCurve* pCurve,BOOL bFinal) 
{
	m_CurveType_S	= CP_LINEAR;
	m_nOrder_S		= 2;
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
	InterPolate_C1(bFinal);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	//////////////////
	return 0;
}			

CDrCurve* CMC_Lin::GetInfo(int nButton)
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
			
int CMC_Lin::InterPolate_C1(BOOL bFinal)
{
	CInter_C1	Inter_C1;			// Curve Interpolate: Cubic
	////////////////////////////////////////////// Set Memory
	if(C1_SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
		return -1;
	////////////////////////////////////////////// Set Interpolation Data
	if(C1_PrepInterpolation(&Inter_C1)<0)
		return -1;
	////////////////////////////////////////////// Interpolate
	if(Inter_C1.Interpolate()<0)
		return -1;
	////////////////////////////////////////////// Get Interpolation Result
	if(C1_PostInterpolation(&Inter_C1,bFinal)<0)
		return -1;
	///////////////////////
	return 0; 
}
	
int CMC_Lin::C1_SetMemory()
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
	/////////////////////////////////////////////////
    return 0;
    
}

int CMC_Lin::C1_PrepInterpolation(CInter_C1* pInter_C1)
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
		sprintf(buf,"CMC_Lin::C1_PrepInterpolation");
		AfxMessageBox(*str);
		///////////////////
		j  = sprintf( buf,"nData_S\t = %d\n",m_pDrCurve->GetData_S());
		j += sprintf( buf + j, "nOrder\t = %d\n",m_pDrCurve->GetOrder_S());
		j += sprintf( buf + j, "bClosed\t = %s\n",(m_bClosed_S?"CLOSED":"OPEN") );
		j += sprintf( buf + j, "nDim\t = %d\n",m_pDrCurve->GetnDim_S());
		j += sprintf( buf + j, "Degr\t = %d\n",m_pDrCurve->GetOrder_S()-1);
		j += sprintf( buf + j, "CSeg_DT\t = %d\n",CSeg_DT);
		j += sprintf( buf + j, "nConBS\t = %d\n",m_pDrCurve->GetnCon_BS_S());
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
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pInter_C1->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pInter_C1->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pInter_C1->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pInter_C1->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	//////////////////////////////////////////////////////////
	pInter_C1->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pInter_C1->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pInter_C1->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pInter_C1->SetnSeg_BS_S(nSeg_BS);
	pInter_C1->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pInter_C1->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes_S
	////////////////////////////////////////////// Send Memory
	pInter_C1->SetpData(m_pData);
	pInter_C1->SetpCon_BS_S(m_pCon_BS_S);
	pInter_C1->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMC_Lin::C1_PostInterpolation(CInter_C1* pInter_C1,BOOL bFinal)
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
	m_pData 			= pInter_C1->GetpData();
	m_pCon_BS_S 		= pInter_C1->GetpCon_BS_S();
	m_pCon_BZ_S 		= pInter_C1->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S; 
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
	//////////////////////////////////////////////////////// Setup Knots
	CDListMgr* pINList = m_pDrCurve->GetINodeList();
	int nData1 = m_pDrCurve->GetData_S();
	int nData = pINList->GetCount();
	if(nData != nData1)
	{
		AfxMessageBox("Internal ERROR\nCMC_Lin::C1_PostInterpolation\nnData != nData1");
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

void CMC_Lin::Serialize(CArchive& ar)
{

	CMI_GangC::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Lin:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Lin:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
