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
#include "In_Conics.h"
 
#include "MC_Parab.h" 

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
IMPLEMENT_SERIAL(CMC_Parab,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Parab::CMC_Parab()
{
    /////////////////////////////////////////// Curve
	m_nMaxCurveINodes_S	= MIN_INODES_CURVE;
	m_nSegsOut_S		= 0;
}

CMC_Parab::~CMC_Parab()
{
}

CDrCurve* CMC_Parab::CreateParabola(CString& Cid,CDrCurve* pCurve,CDListMgr* pNodeList,
								 CURVEPROC kind,CList<int,int>* pElperSegList,
								 BOOL bAdvanceOn,BOOL bFinal)
{
	////////////////////////////////////////////////////// Already in DataBase
	m_pDrCurve 	= pCurve;
	///////////////////////////////////////////////
	m_pDrCurve->GetElperSegList_S()->AddTail(pElperSegList);	// save for later editing etc
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMCurMgr	MDlgMgr;
	CMCurMgr*	pMDlgMgr = &MDlgMgr;
	/////////////////////////////////////////////// Fill EverythingElse
	m_CurveID		= Cid;
	m_CurveType_S	= kind;
	m_bClosed_S		= m_pDrCurve->IsClosed_S();
	m_Ratio_S		= m_pDrCurve->GetRatio_S();
	m_nInputType	= m_pDrCurve->GetInputType();
	/////////////////////////////////////////////// interpolate
	m_nOrder_S = 3;
	SetInfoForCurveBase(m_pDrCurve,pElperSegList,bFinal);
	//////////////////////////////////////////////////// override
	m_nDim_S = 4; // rational
	m_pDrCurve->SetnDim_S(m_nDim_S); // rational
	m_pDrCurve->SetCurveType_S(m_CurveType_S);
	m_pDrCurve->SetInputType(m_nInputType);		// 1 = PARABOLA_BY_NO3
	/////////////////////////////// BC & Knot DataBases
/*
	if(bFinal && bAdvanceOn)
		pMDlgMgr->DoModal_Cur_Advance_In(m_pDrCurve,m_nOrder_S);
	else
	if(m_pDrCurve->IsIso())
		SetIsoInfoForCurveBase(m_pDrCurve);
	else
		SetDefaultInfoForCurveBase(m_pDrCurve);
*/
	////////////////////////////////////////////////////////// Go Interpolate
	GoDoIt(m_pDrCurve,bFinal);
	////////////
    return m_pDrCurve;
}

CDrCurve* CMC_Parab::GoDoIt() 
{
	m_CurveType_S	= CP_PARABOLA;
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
	InterPolate(TRUE);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return (CDrCurve*)NULL;
	/////////////////////
	return m_pDrCurve;
}			

int CMC_Parab::GoDoIt(CDrCurve* pCurve,BOOL bFinal)  
{
//	m_CurveType_S	= CP_PARABOLA;
//	m_nOrder_S		= 3;
	m_nDim_S		= 4;	// Rational
	///////////////////////////////
	m_pDrCurve 			= pCurve;
	///////////////////////////////
	m_nOrder_S			= m_pDrCurve->GetOrder_S();
	m_CurveType_S		= m_pDrCurve->GetCurveType_S();;
	///////////////////////////////////////////////////// stuff from getinfo
	m_nMaxCurveINodes_S	= m_pDrCurve->GetMaxINodes_S();
	m_bClosed_S			= m_pDrCurve->IsClosed_S();
	///////////////////////////////////////////////////// stuff from getinfo
	m_nInputType		= m_pDrCurve->GetInputType();
	///////////////////////////////////////////////
	m_pNum_t_S			= m_pDrCurve->GetNum_tPointer_S();
	m_pNum_t_Ex_S		= m_pDrCurve->GetNum_tPointer_Ex_S();
	////////////////////////////////////////////////
//	m_nSegsOut_S		= m_pDrCurve->GetSegmentCount_S();	// # of Bezier Curvees 
	m_nSegsOut_S		= m_pDrCurve->GetMaxBezSegments_S();	// # of Bezier Curvees 
									// in Rotation dirn
	////////////////////////////////////////////////
	m_Ratio_S			= m_pDrCurve->GetRatio_S();
	m_bUnifOT_S			= m_pDrCurve->IsUniform_S();
	m_nOut_S			= m_pDrCurve->GetMaxOutPts_S();;
	m_nDim_S			= m_pDrCurve->GetnDim_S();
	m_bClosed_S			= m_pDrCurve->IsClosed_S();					// for Extrusion
	///////////////////////////////////////// Bezier Quadratic
	m_nOut_SCon			= 2 * m_nSegsOut_S + 1;	// # of  Bezier Controls in S-dir
	if(m_bClosed_S)
			m_nOut_SCon--;
	/////////////////////////////////////
	m_nSegs_SCon		= m_nOut_SCon - 1;
	m_nMaxCurveCNodes_S = m_nOut_SCon;
	////////////////////////////////////////////////////////// Go Interpolate
	m_pCNodeList 	= m_pDrCurve->GetCNodeList();	
	//////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	InterPolate(bFinal);
	//////////////////////////////////////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	//////////////////
	return 0;
}			

CDrCurve* CMC_Parab::GetInfo(int nButton)
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
		m_nSegsOut_S		= pDrCurve->GetMaxBezSegments_S();
		
		m_bClosed_S			= pDrCurve->IsClosed_S();
		////////////////		
		return pDrCurve;
	}
}			
			
int CMC_Parab::InterPolate(BOOL bFinal)
{
	CIn_Parab* pIn_Conics = &m_In_Conics;
	////////////////////////////////////////////// Set Memory
	if(SetMemory()<0)
		return -1;
	////////////////////////////////////////////// Set Data
	m_pINodeList = m_pDrCurve->GetINodeList();
	if(SetUpINodes(m_pINodeList,m_pData,m_pDrCurve->GetData_S())<0)
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

int CMC_Parab::SetMemory()
{
    
	//////////////////////////////////////////////////////////////////////// Setup Data
	m_pData 	= new WORLD[m_pDrCurve->GetData_S()];
	if(!m_pData)
	{
			AfxMessageBox("ERROR:\nCMC_Parab::SetMemory\nm_pData -Memory Failure!");
		m_MemErr = -1;
		return m_MemErr;
	}
	/////////////////////////////////////////////////
    return 0;
    
}

int CMC_Parab::PrepInterpolation()
{
	CIn_Parab* pIn_Conics = &m_In_Conics;
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
		sprintf(buf,"CMC_Parab::C2_PrepInterpolation");
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
	//////////////////////////////////////////////////////////
#endif	
	/////////////////////////////////////////////////////////////////// FillUp 
	pIn_Conics->SetnData_S(m_pDrCurve->GetData_S());		// GIVEN: # of Data
	pIn_Conics->SetnOrder_S(m_pDrCurve->GetOrder_S());				// k
	pIn_Conics->SetbClosed_S(m_pDrCurve->IsClosed_S());
/*
	pIn_Conics->SetCurveType(CTyp);
	int nDim 		= 3;			// NonRational
	if(CTyp == CU_NURB)
		nDim 		= 4;			// Homogeneous(Rational)
*/		
	//////////////////////////////////////////////////////////
	pIn_Conics->SetnSeg_DT_S(CSeg_DT);						// L
	///////////////
	pIn_Conics->SetnDim_S(m_pDrCurve->GetnDim_S());
	pIn_Conics->SetnDegree_S(m_pDrCurve->GetOrder_S()-1);				// k -1
	pIn_Conics->SetbClosed_S(m_pDrCurve->IsClosed_S()); 
	
//	pIn_Conics->SetnSeg_BS_S(nSeg_BS);
	pIn_Conics->SetnCon_BS_S(m_pDrCurve->GetnCon_BS_S());
	pIn_Conics->SetnCon_BZ_S(m_pDrCurve->GetnCon_BZ_S()); // = m_nMaxCurveCNodes_S
	////////////////////////////////////////////// Send Memory
	pIn_Conics->SetpData(m_pData);
	pIn_Conics->SetpWts_BS_S(m_pWts_BS_S);
	pIn_Conics->SetpWts_BZ_S(m_pWts_BZ_S);
	pIn_Conics->SetpCon_BS_S(m_pCon_BS_S);
	pIn_Conics->SetpCon_BZ_S(m_pCon_BZ_S);
	////////////////////////////////////////////////////
	return 0;
}
	 		
int CMC_Parab::PostInterpolation(BOOL bFinal)
{

	CIn_Parab* pIn_Conics = &m_In_Conics;
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
	/////////////////////////////////////////////////////////// Data
	////////////////////////////////////////////// Get Memory
	m_pData				= pIn_Conics->GetpData();
	m_pWts_BS_S			= pIn_Conics->GetpWts_BS_S();
	m_pWts_BZ_S			= pIn_Conics->GetpWts_BZ_S();
	m_pCon_BS_S			= pIn_Conics->GetpCon_BS_S();
	m_pCon_BZ_S			= pIn_Conics->GetpCon_BZ_S();
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nMaxCurveCNodes_S = m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	///////////////////////////////////////
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
	//////////////////////////////////////////////////////////// Bezier Wts	
	m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S);	// Rational Weights
	//////////////////////////////////////////////////////// Setup Knots
	CDListMgr* pINList = m_pDrCurve->GetINodeList();
	int nData1 = m_pDrCurve->GetData_S();
	int nData = pINList->GetCount();
	if(nData != nData1)
	{
		AfxMessageBox("Internal ERROR\nCMC_Parab::PostInterpolation\nnData != nData1");
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
/*	Rational
	if(m_pWts_BZ_S)
	{
		delete [] m_pWts_BZ_S;
		m_pWts_BZ_S = NULL;
	}
*/	
	if(m_pOut) 
	{
		delete [] m_pOut;
		m_pOut = NULL;
	}
	/////////////////////////////////////////////////////////////////////	
	return MA_OK;
}

void CMC_Parab::Serialize(CArchive& ar)
{

	CMI_GangC::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Parab:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Parab:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
