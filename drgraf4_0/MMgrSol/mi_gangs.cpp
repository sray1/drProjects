// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"
#include <afxtempl.h>	// CList
#include <float.h>		// DBL_EPSILON

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
///////////////////// 
//#include "drawview.h" //for curve/patch 
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Ms.h" // Mesh Types for Patch
///////////////////// dialogMgr
#include "MSolMgr.h"
//#include "Dlg_Node.h"  
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "Triangle.h"
#include "PentaHed.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "MI_GangS.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define	MAX_DEGREE				6	// Max Control Nodes of a Triangle side (QUINTIC)
#define wEQL(a,b)				((a).x ==(b).x) && ((a).y ==(b).y) \
									&& ((a).z ==(b).z)  

#define BARY2LIN_PT(i,j,nP)		(j)  + (i)*(nP)-(i)*((i)-1)/2
#define BARY2LIN_TRI_1(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2)
#define BARY2LIN_TRI_2(i,j,nP)			(j)  + (i)*(2*(nP)-(i)-2) - (nP) + (i)

#define BARY2LIN_TRI_1_NEW(i,j,nP,nDeg)	( (j)  + ((i)*(2*(nP)-(i)-2))/(nDeg) )/(nDeg)
#define BARY2LIN_TRI_2_NEW(i,j,nP,nDeg)	( (j - nDeg)  + ((i)*(2*(nP)-(i)-2))/(nDeg) - ((nP) - 1) + (i) )/(nDeg)
////////////////////////////////////
IMPLEMENT_SERIAL(CMI_GangS,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMI_GangS::CMI_GangS()
{
	m_pOut		= NULL;
	m_pOutWts	= NULL;		// will be deleted in DrCurve.h
	for (int i=0;i<4;i++)
	{
		m_pIn_S[i]		= NULL;
		m_pInWts_S[i]	= NULL;
	}
    /////////////////////////////////////////// Mesh/Patch
	m_CurrentPatchID	= "BLANK";
	m_nMaxPatchCNodes_S	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes_T	= MIN_CNODES_CURVE;
	m_nMaxPatchCNodes	= m_nMaxPatchCNodes_S * m_nMaxPatchCNodes_T;
}

CMI_GangS::~CMI_GangS()
{
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	   
}

void CMI_GangS::GetInfo_Patch(CDrPatch* pDrPatch)
{
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S();
	m_nMaxPatchCNodes_T 	= pDrPatch->GetMaxCNodes_T();
	m_nOut_SCon				= (int)m_nMaxPatchCNodes_S;
	m_nOut_TCon				= (int)m_nMaxPatchCNodes_T;
	////////////////////////////////////////////////// FILL INFO
	m_nDim_S				= pDrPatch->GetnDim_S();
	m_nDim_T				= pDrPatch->GetnDim_T();
	m_pNum_t_S				= pDrPatch->GetNum_tPointer_S();
	m_pNum_t_T				= pDrPatch->GetNum_tPointer_T();
	m_pDis_t_S				= pDrPatch->GetDis_tPointer_S();
	m_pDis_t_T				= pDrPatch->GetDis_tPointer_T();
	m_pNum_t_Ex_S			= pDrPatch->GetNum_tPointer_Ex_S();
	m_pNum_t_Ex_T			= pDrPatch->GetNum_tPointer_Ex_T();
	m_CurveType_S			= pDrPatch->GetCurveType_S();
	m_CurveType_T			= pDrPatch->GetCurveType_T();
	m_nOrder_S				= pDrPatch->GetOrder_S();
	m_nOrder_T				= pDrPatch->GetOrder_T();
   ///////////////////////////////////
	m_nOut_S				= (int)pDrPatch->GetOut_S();
	m_nOut_T				= (int)pDrPatch->GetOut_T();
	m_nOut_ST				= pDrPatch->GetLongOutPts();
	m_nSegs_S				= pDrPatch->GetMaxBezSegments_S();
	m_nSegs_T				= pDrPatch->GetMaxBezSegments_T();
	///////////////////////////////////////////	
 	m_bClosed_S				= pDrPatch->IsClosed_S();	// X-Section
	m_bClosed_T				= pDrPatch->IsClosed_T();	// X-Section
	m_nSegs_SCon			= m_nOut_SCon - 1;
	m_nSegs_TCon			= m_nOut_TCon - 1;
	m_nMaxSolidCNodes_S		= m_nOut_SCon;
	m_nMaxSolidCNodes_T		= m_nOut_TCon;
	m_nMaxSolidCNodes_ST 	= m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
	m_nOut_STCon			= (int)m_nMaxSolidCNodes_ST;
	////////////////////////////////////////////////////
	m_pWts_BZ_ST			= pDrPatch->GetMemInWts();		
	m_PatchType				= pDrPatch->GetPatchType();
	//////////////////////////////
}

void CMI_GangS::FillCNodesLOCAL_Solid(CDListMgr* pCurveCNodeList,pDOUBLE pWts_S,
							pWORLD pIn,pDOUBLE pInWts,int nMaxCNodes,
							BOOL bSave,BOOL bLoft)
{
	/////////////////////////////////////////
	int i;
	CDrNode* pDrNode;
    /////////////////
	WORLD 	LocalPos;
	//////////////////////////////////////////// Get point 
    for(i = 0; i<nMaxCNodes; i++)              
    {
    	pDrNode = (CDrNode*)(pCurveCNodeList->GetObject(i));
    	//////////////////////////////////////// Save in Patch
    										  // CNodeList
		if(bSave)
		{
				m_pCNodeList->AddTail(pDrNode);
				///////////////////////////////////// Reciprocate 
				int index = (pDrNode->GetSolidList())->GetObjectIndex(m_pDrSolid); // exists already?
				if(index>=0)
					continue;
				/////////////
				pDrNode->GetSolidList()->InsertObject(m_pDrSolid);
		}		
    	//////////////////////////////////////// NPC Pt.
    	LocalPos = *(pDrNode->GetLocalPos());
    	/////////////////////////////////
		pIn[i].x = LocalPos.x;	  
		pIn[i].y = LocalPos.y;  
		pIn[i].z = LocalPos.z;
		//////////////////////////////////////// Wts
		pInWts[i] = pWts_S[i];
	}	
}

int CMI_GangS::InsertMeshInfo_Solid(BOOL bLoft)
{
	//////////////////////////////////////////////////////
	// For ALL cases other than Mesh, All ControlNodes	//
	// Must be Put in CNodeList of the Solid. However,	//
	//	1.	some of them already created by generating	//
	//		patch such as								//
	//			DUCT & SWEEP: X-Section Patch CNodes	//
	//			EXTRUDE/ROT.: Generating Curve CNodes	// I G N O R E
	//			LOFT        : Start & End Curves'		// E V E R Y T H I N G 
	//							CNodes					// H E R E
	//	2.	Rest or In-Betweens have to generate		// 
	//					DrNodes							//
	//	3.	Inherent in Loft creation, Start/End Patches//
	//		Already created CNodes get interweaved		//
	//		Need to sort out because we dont want to	//
	//		create what are already posted				//
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,SolidID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int st,r,j;
	///////////////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (r = 0; r<m_nMaxSolidCNodes_R; r++)
	{
		for (st = 0; st<m_nMaxSolidCNodes_ST; st++)
		{
/* 060997
			if	(	(r == 0) &&
				(	(m_SolidProc == SP_EXTRUDE) ||(m_SolidProc == SP_ROTATE)  )		// first s of them already in List
							// for Extrude & Rotate only
				)	
				continue;   // do nothing
*/
			///////////////////////
			if( bLoft && (r == m_nMaxSolidCNodes_ST-1) )
			{
				// get Already created saved in TemporaryList
				pAddNode = (CDrNode*)m_CNListLoft.GetObject(st);
				///////////////////////////////////// in SOLID 	
   				m_pCNodeList->InsertObject(pAddNode); //CNodeList
   				//////////////
   				continue;
   			}
   			///////////////////////////////////////// CREATE	
			Nid		= SolidID.Left(nChLen);
		    //////////////////////////////////// Name
		    sprintf(buf,"%d_%d_%d",	st/m_nMaxSolidCNodes_S,
		    						st%m_nMaxSolidCNodes_S,r);
		    Nid += buf; 
			////////////////////////////////////
			j = r*m_nMaxSolidCNodes_ST + st;
			////////////////////////////		
			LocalPos.x	= (m_pOut+j)->x;
			LocalPos.y	= (m_pOut+j)->y;
			LocalPos.z	= (m_pOut+j)->z;
			///////////////////////////////////// in THE List 
//092798			if(!(pAddNode = PostNode(Nid,LocalPos,TRUE,FALSE)))	// Create DrCNode
			if(!(pAddNode = PostNode(Nid,LEVEL_KIDDO,LocalPos,TRUE)))	// Create DrCNode
				return -1;
			///////////////////////////////////// in SOLID 	
   			m_pCNodeList->InsertObject(pAddNode); //CNodeList 
//			pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
			///////////////////////////////////// Reciprocate 
			int index = (pAddNode->GetSolidList())->GetObjectIndex(m_pDrSolid); // exists already?
			if(index>=0)
				continue;
			/////////////
			pAddNode->GetSolidList()->InsertObject(m_pDrSolid);
		}				
	}
	////////////////////////////////////////// Save Info inSolid
	m_pDrSolid->SetFromPtLocal_R(m_FromPt);
	m_pDrSolid->SetToPtLocal_R(m_ToPt);
	m_pDrSolid->SetAxis_R(m_vAxis);
	////////////////////////////////////////////////////// All Other
	m_pDrSolid->SetSolidType(m_SolidType);
	m_pDrSolid->SetSolSubType(SS_HEXA);
	m_pDrSolid->SetPatchType(m_PatchType);
	m_pDrSolid->SetMaxCNodes_S(m_nMaxSolidCNodes_S);
	m_pDrSolid->SetMaxCNodes_T(m_nMaxSolidCNodes_T);
	m_pDrSolid->SetMaxCNodes_R(m_nMaxSolidCNodes_R);
	///////////////////////////////////////////////////
	m_pDrSolid->SetMaxBezSegments_S(m_nSegs_S);	
	m_pDrSolid->SetMaxBezSegments_T(m_nSegs_T); 
	m_pDrSolid->SetMaxBezSegments_R(m_nSegs_R); 
	m_pDrSolid->SetClosed_S(m_bClosed_S);
	m_pDrSolid->SetClosed_T(m_bClosed_T);
	m_pDrSolid->SetClosed_R(m_bClosed_R);
	m_pDrSolid->SetDirty(TRUE);
	//////////////////////////////////////////////////
	// call to NumberOfCubicSolides() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	m_pDrSolid->SetLongOutPts(m_nOut);	
	m_pDrSolid->SetOut_S(m_nOut_S);	
	m_pDrSolid->SetOut_T(m_nOut_T);
	m_pDrSolid->SetOut_R(m_nOut_R);
	m_pDrSolid->SetOrder_S(m_nOrder_S);
	m_pDrSolid->SetOrder_T(m_nOrder_T);
	m_pDrSolid->SetOrder_R(m_nOrder_R);
	m_pDrSolid->SetnDim_S(m_nDim_S);
	m_pDrSolid->SetnDim_T(m_nDim_T);
	m_pDrSolid->SetnDim_R(m_nDim_R);
	m_pDrSolid->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetDis_tPointer_S(m_pDis_t_S);			// t-distribution
	m_pDrSolid->SetNum_tPointer_Ex_S(m_pNum_t_Ex_S);// Circle Special
					// Number of Outputs for each Output Segment
	m_pDrSolid->SetNum_tPointer_T(m_pNum_t_T);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetDis_tPointer_T(m_pDis_t_T);			// t-distribution
	m_pDrSolid->SetNum_tPointer_Ex_T(m_pNum_t_Ex_T);// Circle Special
					// Number of Outputs for each Output Segment
	/////////////////////////////////////////////////////////
//	m_pDrSolid->SetNum_tPointer_ST(m_pNum_t_ST);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetNum_tPointer_R(m_pNum_t_R);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetDis_tPointer_R(m_pDis_t_R);			// t-distribution
//	m_pDrSolid->SetNum_tPointer_Ex_ST(m_pNum_t_Ex_ST);// Circle Special
					// Number of Outputs for each Output Segment
	m_pDrSolid->SetNum_tPointer_Ex_R(m_pNum_t_Ex_R);// Circle Special
					// Number of Outputs for each Output Segment
	m_pDrSolid->SetMemInWts(m_pOutWts);		// wiil be deleted in CDrCurve.h
	///////////////////////////////////
	int nOutTotal = m_pDrSolid->NumberOfSolides();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMI_GangS::InsertMeshInfo\nm_nOut Mismatch!");
		return - 1;
	}
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	////////////////
	return 0;
}			

void CMI_GangS::GetInfo_Patch_3(CDrPatch* pDrPatch)
{
	///////////////////////////////////////////////////////////////////////////////////
	//	ALL Triangular Info SAVED in S-dir variables in Mi_GangP::InsertMeshInfo_3
	//	EXCEPT: 
	//	m_nMaxSolidCNodes_T 	= pDrPatch->GetMaxCNodes_T(); // TOTAL of the Triangle
	///////////////////////////////////////////////////////////////////////////////////
    m_pTriList				= pDrPatch->GetTriangleList();
	/////////////////	
	m_nMaxPatchCNodes_S 	= pDrPatch->GetMaxCNodes_S(); // On Each side of the Triangle
	m_nMaxSolidCNodes_T 	= pDrPatch->GetMaxCNodes_T(); // TOTAL of the Triangle
	m_nOut_SCon				= (int)m_nMaxPatchCNodes_S;
	////////////////////////////////////////////////// FILL INFO
	m_nDim_S				= pDrPatch->GetnDim_S();
	m_pNum_t_S				= pDrPatch->GetNum_tPointer_S();
	m_pDis_t_S				= pDrPatch->GetDis_tPointer_S();
	m_pNum_t_Ex_S			= pDrPatch->GetNum_tPointer_Ex_S();
	m_CurveType_S			= pDrPatch->GetCurveType_S();
	m_nOrder_S				= pDrPatch->GetOrder_S();
   ///////////////////////////////////
	m_nOut_S				= (int)pDrPatch->GetOut_S();
	m_nOut_ST				= pDrPatch->GetLongOutPts();		// 
	m_nSegs_S				= pDrPatch->GetOutSegUnif_S();	// Output ( =1 <- set in Mp_Coop3)
																// Assuming Linear Triangles
	///////////////////////////////////////////	
 	m_bClosed_S				= pDrPatch->IsClosed_S();	// X-Section
	m_nSegs_SCon			= m_nOut_SCon - 1;
	m_nMaxSolidCNodes_S		= m_nOut_SCon;
	m_nMaxSolidCNodes_ST 	= m_nMaxSolidCNodes_T;
	m_nOut_STCon			= (int)m_nMaxSolidCNodes_ST;
	////////////////////////////////////////////////////
	m_pWts_BZ_ST			= pDrPatch->GetMemInWts();		
	m_PatchType				= pDrPatch->GetPatchType();
	//////////////////////////////
}

int CMI_GangS::InsertMeshInfo_Solid_3()
{
	//////////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,SolidID;
	int			nChLen;
	char		buf[10];
    CDrNode* 	pAddNode;
	int r,i,j,k,m;
	///////////////////////////////////////////// Name
	SolidID	= m_pDrSolid->GetObjectID();
	nChLen	= SolidID.GetLength();
	if(nChLen>4)
		nChLen = 4;
	////////////////////////////////////
	for (r = 0; r<m_nMaxSolidCNodes_R; r++)
	{
		////////////////////////////////////
		for (i = 0; i<m_nMaxSolidCNodes_S; i++)
		{
			for (j = 0; j<m_nMaxSolidCNodes_S-i; j++)
			{
/*
   				if	(	(r == 0) &&
					(	(m_SolidProc == SP_EXTRUDE) ||(m_SolidProc == SP_ROTATE)  )
							// first s of them already in List
							// for Extrude & Rotate only
					)	
					continue;   // do nothing
*/
				///////////////////////////////////////// CREATE	
				Nid		= SolidID.Left(nChLen);
				//////////////////////////////////// Name
				k = m_nOut_S - i - j - 1; 
				sprintf(buf,"%d_%d_%d_%d",i,j,k,r);
				Nid += buf; 
				//////////////////////////////////// Barycentric to Linear
				m = BARY2LIN_PT(i,j,m_nOut_S) + r * m_nMaxSolidCNodes_ST;
				////////////////////////////		
				LocalPos.x	= (m_pOut+m)->x;
				LocalPos.y	= (m_pOut+m)->y;
				LocalPos.z	= (m_pOut+m)->z;
				///////////////////////////////////// in THE List 
//092798				pAddNode = PostNode(Nid,LocalPos,TRUE,FALSE);	// Create DrCNode
				pAddNode = PostNode(Nid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
				if(!pAddNode)	
					return -1;
				///////////////////////////////////// in SOLID 	
   				m_pCNodeList->InsertObject(pAddNode); //CNodeList 
//				pAddNode->SetLevelType((int)LEVEL_KIDDO);          // private
				///////////////////////////////////// Reciprocate 
				int index = (pAddNode->GetSolidList())->GetObjectIndex(m_pDrSolid); // exists already?
				if(index>=0)
					continue;
				/////////////
				pAddNode->GetSolidList()->InsertObject(m_pDrSolid);
			}				
		}
	}
	////////////////////////////////////////// Save Info inSolid
	m_pDrSolid->SetFromPtLocal_R(m_FromPt);
	m_pDrSolid->SetToPtLocal_R(m_ToPt);
	m_pDrSolid->SetAxis_R(m_vAxis);
	////////////////////////////////////////////////////// All Other
	m_pDrSolid->SetSolidType(m_SolidType);
	m_pDrSolid->SetSolSubType(m_SolSubType);
	m_pDrSolid->SetPatchType(m_PatchType);
	m_pDrSolid->SetMaxCNodes_S(m_nMaxSolidCNodes_S);	// each side of the base Triangle
	m_pDrSolid->SetMaxCNodes_T(m_nMaxSolidCNodes_T);	// TOTAL for the base Triangle in ST plane
	m_pDrSolid->SetMaxCNodes_R(m_nMaxSolidCNodes_R);	// Layers in R-dir
	///////////////////////////////////////////////////
	m_pDrSolid->SetOutSegUnif_S(m_nSegs_S);			// Output in each side of Triangle
														// Assuming Linear Triangle -> = 1
	m_pDrSolid->SetOutSegUnif_R(m_nSegs_R); 
	m_pDrSolid->SetClosed_S(m_bClosed_S);
	m_pDrSolid->SetClosed_R(m_bClosed_R);
	m_pDrSolid->SetDirty(TRUE);
	//////////////////////////////////
	m_pDrSolid->SetOut_S(m_nOut_S);	
	m_pDrSolid->SetnOutGlo_S(m_nOut_S);
	////////////////////////
	m_pDrSolid->SetOut_R(m_nOut_R);
	m_pDrSolid->SetOrder_S(m_nOrder_S);
	m_pDrSolid->SetOrder_R(m_nOrder_R);
	m_pDrSolid->SetnDim_S(m_nDim_S);
	m_pDrSolid->SetnDim_R(m_nDim_R);
	m_pDrSolid->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetDis_tPointer_S(m_pDis_t_S);			// t-distribution
	m_pDrSolid->SetNum_tPointer_Ex_S(m_pNum_t_Ex_S);// Circle Special
					// Number of Outputs for each Output Segment
	/////////////////////////////////////////////////////////
//	m_pDrSolid->SetNum_tPointer_ST(m_pNum_t_ST);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetNum_tPointer_R(m_pNum_t_R);			// Number of Outputs for each Output Segment
	m_pDrSolid->SetDis_tPointer_R(m_pDis_t_R);			// t-distribution
//	m_pDrSolid->SetNum_tPointer_Ex_ST(m_pNum_t_Ex_ST);// Circle Special
					// Number of Outputs for each Output Segment
	m_pDrSolid->SetNum_tPointer_Ex_R(m_pNum_t_Ex_R);// Circle Special
					// Number of Outputs for each Output Segment
	m_pDrSolid->SetMemInWts(m_pOutWts);		// wiil be deleted in CDrCurve.h
	//////////////////////////////////////////////////
	// call to NumberOfBezierPenta() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	m_pDrSolid->NumberOfBezierPenta();
	////////////////////////////////////////////////// 
	m_pDrSolid->SetLongOutPts(m_nOut);					
	////////////////////////////////////// Now Store PentaHedron Database
	InsertPentaHedrons();
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	m_pDrSolid->Calc_3DBoundsLocal();											
	////////////////
	return 0;
}
			
int CMI_GangS::InsertPentaHedrons(CDrSolid* pSolid)
{
	///////////////////////////////////////
	CDrPatch* pPatch	= (CDrPatch*)pSolid->GetPatchList()->GetHead();
    CDListMgr* pTriList	= pPatch->GetTriangleList();
	CDListMgr* pPenList	= pSolid->GetPentaList();
	////////////////////////////////////////////////////////////////
	//	Since Triangular Patch Global Storage Not Done Yet(5/22/96)
	//	m_nOut_ST is re-computed here Correctly:
	////////////////////////////////////////////////////////////////
	int	nOut_S		= pSolid->GetOut_S();
	int nSolides_R	= pSolid->GetMaxBezSegments_R();
	int nOrder_S	= pSolid->GetOrder_S();
	int nOrder_R	= pSolid->GetOrder_R();
	int nConBZ_ST	= pSolid->GetMaxCNodes_T();	// Total_ST
	int nConBZ_R	= pSolid->GetMaxCNodes_R();	
	pINT pNum_t_R	= pSolid->GetNum_tPointer_R();
	////////////////////////////////////////////////////////////////
	int nOut_ST		= nOut_S*(nOut_S+1)/2;
	int K=-1,nMax,m,nOutStartIndex;
	////////////////////////////////////////////////////////////////
	int nTri		= pTriList->GetCount();
	/////////////////////////////////////////
	for (POSITION posT = pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int	nDegree		= pTri->GetDegree();			// Overall Degree of Triangle
		if(nDegree>MAX_DEGREE)
		{
			AfxMessageBox("ERROR:\nCMI_GangS::InsertPenta\nnDegree>MAX_DEGREE");
			return -1;
		}
		int	TriNum		= (nDegree+1)*(nDegree+2)/2;	//  Triangle Number 
		////////////////////////////////////////////
		CList<int,int>* pCNIndexList = pTri->GetCNIndexList();
		int nCon		= pCNIndexList->GetCount();
		if (nCon != TriNum)
		{
			AfxMessageBox("ERROR:\nCMI_GangS::InsertPenta\nnCon != TriNum");
			return -1;
		}
		///////////
		int i = 0;
		/////////////////////////////////////////////////////////// Indices of Controls
		// Max # of Control Nodes Reserved for Quintic (Degree = 5)
		pINT pBot = new int[21];
		pINT pTop = new int[21];
		/////////////////////////////////////////////////////////////////// Base Triangle
		for (POSITION posI = pCNIndexList->GetHeadPosition( );posI !=NULL;)
		{
			/////////////////////////////////// Base Indices
			pBot[i++] = pCNIndexList->GetNext(posI); 
    		///////////////////////////////
		}
		nMax = i;
		/////////////////////////////////////////////// Closed_R modulo
		int nLast	= nConBZ_R*nConBZ_ST; // last one on Last plane before repeat
		/////////////////////////////////////////////////////////////////// Generate Bezier Pentas
		nOutStartIndex = 0;
		///////////////////
		for (int r = 0; r<nSolides_R; r++)
		{
			/////////////////////////////////// Bezier Penta
			CPentaHed* pPen = new CPentaHed;
			////////////////////////////////
			if(!pPen)
			{
				AfxMessageBox("Error:\nCMI_GangS::InsertPenta\nMemory Problem!");
				delete pBot;
				delete pTop;
				return - 1;
			}
			////////////////////////////////
			pPen->SetType(pTri->GetType());
			pPen->SetSolIndex(++K);
			pPen->SetDegree_ST(nOrder_S-1);
			pPen->SetDegree_R(nOrder_R-1);
			////////////////////////////////////////
			CList<int,int>* pCNPIndexList = pPen->GetCNIndexList();
			/////////////////////////////////// save Indices
			for(int k=0;k<nOrder_R;k++)
			{
				/////////////////////////
				for(i=0;i<nMax;i++)
					pTop[i] = (pBot[i] + k * nConBZ_ST)%nLast;	// may be closed_R true 
				////////////////////
				for (m = 0;m<nMax;m++)
				{
					/////// save
					pCNPIndexList->AddTail(pTop[m]);
				}
			}
			////////////////////////////////////////
			pPen->SetiOutGlo_ST(pTri->GetiOutGlo());
			pPen->SetjOutGlo_ST(pTri->GetjOutGlo());
			////////////////////////////////////////////////////////// Output Segment
			pPen->SetOutSeg_S(pTri->GetOutSeg());
			//////////////////////////////////////// take care of Circular
//			if(m_CurveType_R == CU_CIRCLE)
//				pPen->SetOutSeg_R(m_pNum_t_Ex_R[r]);
//			else
			int nt_R = pNum_t_R[r]; 
				pPen->SetOutSeg_R(nt_R);
			/////////////////////////
			pPen->SetOutStartIndex(nOutStartIndex);
			////////////////////////////////////////////////////////// Reset Start Index
			nOutStartIndex += nt_R * nOut_ST;  
			////////////////////////////////////////////////////////// Save PentaHedron
			pPenList->InsertObject(pPen);
			////////////////////////////////////////////////////////// Reset Bottom ConVertices
			for(i=0;i<nMax;i++)
				pBot[i] = pTop[i];
		}
	/////////////////////////////
	delete pBot;
	delete pTop;
	}
	////////////
	return 0;
}	
			
int CMI_GangS::InsertPentaHedrons()
{
	////////////////////////////////////////////////////////////////
	//	Since Triangular Patch Global Storage Not Done Yet(5/22/96)
	//	m_nOut_ST is re-computed here Correctly:
	////////////////////////////////////////////////////////////////
	m_nOut_ST = m_nOut_S*(m_nOut_S+1)/2;
	////////////////////////////////////////////////////////////////
	int K=-1,nMax,m,nOutStartIndex;
	/////////
	int nSolides_R	= m_pDrSolid->GetMaxBezSegments_R();
	////////////////////////////////////////////////////////////////
	int nTri		= m_pTriList->GetCount();
	/////////////////////////////////////////
	for (POSITION posT = m_pTriList->GetFirstObjectPos();posT !=NULL;)
	{
		CTriangle* pTri = (CTriangle*)m_pTriList->GetNextObject(posT);
		/////////////////////////////////////////////// get info
		int	nDegree		= pTri->GetDegree();			// Overall Degree of Triangle
		if(nDegree>MAX_DEGREE)
		{
			AfxMessageBox("ERROR:\nCMI_GangS::InsertPenta\nnDegree>MAX_DEGREE");
			return -1;
		}
		int	TriNum		= (nDegree+1)*(nDegree+2)/2;	//  Triangle Number 
		////////////////////////////////////////////
		CList<int,int>* pCNIndexList = pTri->GetCNIndexList();
		int nCon		= pCNIndexList->GetCount();
		if (nCon != TriNum)
		{
			AfxMessageBox("ERROR:\nCMI_GangS::InsertPenta\nnCon != TriNum");
			return -1;
		}
		///////////
		int i = 0;
		/////////////////////////////////////////////////////////// Indices of Controls
		// Max # of Control Nodes Reserved for Quintic (Degree = 5)
		pINT pBot = new int[21];
		pINT pTop = new int[21];
		/////////////////////////////////////////////////////////////////// Base Triangle
		for (POSITION posI = pCNIndexList->GetHeadPosition( );posI !=NULL;)
		{
			/////////////////////////////////// Base Indices
			pBot[i++] = pCNIndexList->GetNext(posI); 
    		///////////////////////////////
		}
		nMax = i;
		/////////////////////////////////////////////// Closed_R modulo
		int nLast	= m_nOut_RCon*m_nMaxSolidCNodes_T; // last one on Last plane before repeat
		/////////////////////////////////////////////////////////////////// Generate Bezier Pentas
		nOutStartIndex = 0;
		///////////////////
		for (int r = 0; r<nSolides_R; r++)
		{
			/////////////////////////////////// Bezier Penta
			CPentaHed* pPen = new CPentaHed;
			////////////////////////////////
			if(!pPen)
			{
				AfxMessageBox("Error:\nCMI_GangS::InsertPenta\nMemory Problem!");
				delete pBot;
				delete pTop;
				return - 1;
			}
			////////////////////////////////
			pPen->SetType(pTri->GetType());
			pPen->SetSolIndex(++K);
			pPen->SetDegree_ST(m_nOrder_S-1);
			pPen->SetDegree_R(m_nOrder_R-1);
			////////////////////////////////////////
			CList<int,int>* pCNPIndexList = pPen->GetCNIndexList();
			/////////////////////////////////// save Indices
			for(int k=0;k<m_nOrder_R;k++)
			{
				/////////////////////////
				for(i=0;i<nMax;i++)
					pTop[i] = (pBot[i] + k * m_nMaxSolidCNodes_T)%nLast;	// may be closed_R true 
				////////////////////
				for (m = 0;m<nMax;m++)
				{
					/////// save
					pCNPIndexList->AddTail(pTop[m]);
				}
			}
			////////////////////////////////////////
			pPen->SetiOutGlo_ST(pTri->GetiOutGlo());
			pPen->SetjOutGlo_ST(pTri->GetjOutGlo());
			////////////////////////////////////////////////////////// Output Segment
			pPen->SetOutSeg_S(pTri->GetOutSeg());
			//////////////////////////////////////// take care of Circular
//			if(m_CurveType_R == CU_CIRCLE)
//				pPen->SetOutSeg_R(m_pNum_t_Ex_R[r]);
//			else
			int nt_R = m_pNum_t_R[r]; 
				pPen->SetOutSeg_R(nt_R);
			/////////////////////////
			pPen->SetOutStartIndex(nOutStartIndex);
			////////////////////////////////////////////////////////// Reset Start Index
			nOutStartIndex += nt_R * m_nOut_ST;  
			////////////////////////////////////////////////////////// Save PentaHedron
			m_pPenList->InsertObject(pPen);
			////////////////////////////////////////////////////////// Reset Bottom ConVertices
			for(i=0;i<nMax;i++)
				pBot[i] = pTop[i];
		}
	/////////////////////////////
	delete pBot;
	delete pTop;
	}
	////////////
	return 0;
}	
////////////////// Control Node Generation /////////////////
/*
void CMI_GangS::UnitAxisFromEndNodes(int nType)
{
	//////////////////////////////////////////////////////////////
	// nType = 0, do it all the way(Axis):Rotate/Extrude
	//       = 1, just compute LocalPos of m_FromID
	//			  (For Sweep/Duct Anchor Node)
	//////////////////////////////////////////////////////////////

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
    /////////////////
	int 		index;
	CDrNode* 	pDrNode;
//    int			nPrecision;
//	long 		lCoord_1[3],lCoord_2[3];
//	WORLD		ptDest_1,ptDest_2;
	////////////////////////////////////////////////////// FromNode
	index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_FromID,1);
	pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
		AfxMessageBox("Internal ERROR:\nCMI_GangS::UnitAxisFromEndNodes\nindex<0");	
   	///////////////////////////////////////////// get Raw Pt.
   	m_FromPt = *(pDrNode->GetLocalPos());
	//////////////////////////////// For Sweep/duct
	if(nType == 1)
		return; 
	////////////////////////////////////////////////////// ToNode
	index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_ToID,1);
	pDListMgr 	= pObjectMgr->GetObjectList(CNODE);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
		AfxMessageBox("Internal ERROR:\nCMI_GangS::UnitAxisFromEndNodes\nindex<0");	
   	///////////////////////////////////////////// get Raw Pt.
  	m_ToPt = *(pDrNode->GetLocalPos());
	///////////////////////////////////////////// Vector
	m_vAxis.x = m_ToPt.x - m_FromPt.x;  
	m_vAxis.y = m_ToPt.y - m_FromPt.y;  
	m_vAxis.z = m_ToPt.z - m_FromPt.z;  
	///////////////////////// Unit
	double NewD =	m_vAxis.x*m_vAxis.x +  
    				m_vAxis.y*m_vAxis.y +
    				m_vAxis.z*m_vAxis.z;
	/////////////////////
	if(NewD <DBL_EPSILON)
		return;
	////////////////////
	double r = 1.0/sqrt(NewD);
	///////////////////////////// Unit vector
	m_vAxis.x *= r;  
	m_vAxis.y *= r;  
	m_vAxis.z *= r;
	///////////////
}

int CMI_GangS::FillMeshNodesPatch(CDrPatch* pDrPatch, pWORLD pOut, pDOUBLE pOutWts )
{
    //////////////////////////////////////////////////////
	pDrPatch->RefillCNLocalPosForPosting();	// filling m_pIn in DrCurve w/ LocalPos
	///////////////////////////////////////
	if(	m_PatSubType == PS_TRIANGLE)
		pDrPatch->Generate_Patch3(pOut, pOutWts);
	else
		pDrPatch->Generate_Patch4(pOut, pOutWts);
	//////////////////////////////////////////		
	return 0;
}
*/
/*
//	Moved to CreOMgr Dll   01/14/98 

CDrSolid* CMI_GangS::PostSolid(CString& Cid,CString& OldID,SOLIDPROC SProc)
{

	CMSolMgr 	MSolMgr;
	CMSolMgr* 	pMSolMgr = &MSolMgr;
	CDrSolid*	pSolid;
	/////////////////////////////////////////////
	pSolid = pMSolMgr->SpawnSolid(Cid, OldID, SProc);
	//////////////////////////////////////////////
	return pSolid;
}
//	Moved to CreOMgr Dll   01/14/98 end 
*/
////////////////////////////////////////////////////////////
void CMI_GangS::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_GangS:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_GangS:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}
///////////////////////////////////// end of Module //////////////////////		


