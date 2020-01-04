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
#include "CU_Circl.h"
 
#include "MC_Circl.h" 

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
IMPLEMENT_SERIAL(CMC_Circl,CMI_GangC,1)
/////////////////////////////////////////////////////////////////////////////
CMC_Circl::CMC_Circl()
{
	m_pData			= NULL;
	m_pWts_DT_S		= NULL;
}

CMC_Circl::~CMC_Circl()
{
}

CDrCurve* CMC_Circl::GoDoIt() 
{
	//////////////////////////////////////////////////////////
	m_pDrCurve 		= GetInfo();       // PGen Dialog
	if(!m_pDrCurve)		// cancel
		return (CDrCurve*)NULL;
	///////////////////////////////////////////////////////////////////// Go Generate	
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
	////////////////////////////////////////////////////////// Go Interpolate
	m_pCNodeList 	= m_pDrCurve->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Circle_PrepInterpolation();
	Circle();
	Circle_PostInterpolation(TRUE);
	////////////////////////
	m_CurveType_S = CP_CIRCLE;
	////////////////////////
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return (CDrCurve*)NULL;
	/////////////////////
	return m_pDrCurve;
}			


int CMC_Circl::GoDoIt(CDrCurve* pCurve,BOOL bFinal)  
{
	m_CurveType_S	= CP_CIRCLE;
	m_nOrder_S		= 3;
	///////////////////////////////
	m_pDrCurve 			= pCurve;
	////////////////////////////////// tired of typing!
	CDrCurve* pDrCurve	= m_pDrCurve;
	///////////////////////////////////////////////////// stuff from getinfo
	m_nInputType		= pDrCurve->GetInputType();
	///////////////////////////////////////////////
	if(m_nInputType == CIRCLE_BY_ROT)
	{
		m_pFromIDNode 		= pDrCurve->GetFromIDNode_S();
		m_pToIDNode			= pDrCurve->GetToIDNode_S();
		m_nMaxCurveINodes_S	= pDrCurve->GetMaxINodes_S();	//
		///
		m_bAxis				= pDrCurve->IsAxisInput();
		m_nAxis				= pDrCurve->GetAxis();
		m_bNegative			= pDrCurve->IsNegative();
	}
	else
	if(
		m_nInputType == CIRCLE_BY_NO3		||
		m_nInputType == CIRCLE_BY_2N_TI		||
		m_nInputType == CIRCLE_BY_2N_CC		||
		m_nInputType == CIRCLE_BY_2CN_TI_R 
	  )
	{
		m_Center_S			= pDrCurve->GetCenter_S();
		m_Radius_S			= pDrCurve->GetRadius_S();
		m_vAxis_S			= pDrCurve->GetNormal_S();
		m_FromPt_S			= pDrCurve->GetCenter_S();
		m_nMaxCurveINodes_S	= 1;							// Use Only the First One 
	}
	//////////////////////////////////////////////////////
	m_pNum_t_S			= pDrCurve->GetNum_tPointer_S();
	m_pNum_t_Ex_S		= pDrCurve->GetNum_tPointer_Ex_S();
	m_dAng1_S			= 0;		
	m_dAng2_S			= pDrCurve->GetTheta_S();		
	////////////////////////////////////////////////
	m_nSegs_S			= pDrCurve->GetSegmentCount_S();	// # of Bezier Curvees 
									// in Rotation dirn
	////////////////////////////////////////////////
	m_Ratio_S			= pDrCurve->GetRatio_S();
	m_bUnifOT_S			= pDrCurve->IsUniform_S();
	m_nOut_S			= pDrCurve->GetMaxOutPts_S();;
	m_nOrder_S			= pDrCurve->GetOrder_S();
	m_CurveType_S		= pDrCurve->GetCurveType_S();;
	m_nDim_S			= pDrCurve->GetnDim_S();
	m_bClosed_S			= pDrCurve->IsClosed_S();					// for Extrusion
	///////////////////////////////////// Angle Distribution
	m_pDisAng_S			= pDrCurve->GetDis_AngPointer_S();	// Distribution of angles 
	///////////////////////////////////////// Bezier Quadratic
	m_nOut_SCon			= 2 * m_nSegs_S + 1;	// # of  Bezier Controls in S-dir
	if(m_bClosed_S)
			m_nOut_SCon--;
	/////////////////////////////////////
	m_nSegs_SCon		= m_nOut_SCon - 1;
	m_nMaxCurveCNodes_S = m_nOut_SCon;
	////////////////////////////////////////////////// PrepInfo
#ifdef _DEBUG
	///////////////////////////////////////// Check
	int i;
	double dTotAng=0.0,dAngInc;
	//////
	for(i=0;i<m_nSegs_S;i++)
	{
		dAngInc	= m_pDisAng_S[i];
		dTotAng	+= dAngInc;
	}
	if(fabs(dTotAng-(m_dAng2_S-m_dAng1_S) )>.01)
	{
		AfxMessageBox("ERROR\nCMC_Circl::GetInfo()-fabs(dTotAng-(m_dAng2_S-m_dAng1_S) )>.01");
		return -1;
	}
#endif
	///////////////////////////////////////////////////////////////////// Go Generate	
	if(!m_pDrCurve)
		return -1;	// Cancel
	////////////////////////////////////////////////////////// Go Interpolate
	m_pCNodeList 	= m_pDrCurve->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Circle_PrepInterpolation();
	Circle();
	Circle_PostInterpolation(bFinal);
	////////////////////////
	m_CurveType_S = CP_CIRCLE;
	////////////////////////
	m_bFinal = bFinal;
	if(InsertAllInfo_Curve(m_nOrder_S)<0)
		return -1;
	/////////////////////
	return 0;
}			

CDrCurve* CMC_Circl::GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CMCurMgr 	MCurMgr;
	CMCurMgr* 	pMCurMgr = &MCurMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pMCurMgr->DoModal_Cur_I_CIRCLE(&Cid,1) == IDCANCEL)
		return (CDrCurve*)NULL; 
    /////////////////////////////////////////////////////// update
	index 					= pObjectMgr->
								GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{						
		CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		//////////////////////////////
		m_nInputType		= pDrCurve->GetInputType();
   		///////////////////////////////////////////////
		if(m_nInputType == CIRCLE_BY_ROT)
		{
			m_pFromIDNode 			= pDrCurve->GetFromIDNode_S();
			m_pToIDNode				= pDrCurve->GetToIDNode_S();
			m_nMaxCurveINodes_S	= pDrCurve->GetMaxINodes_S();	// 
			///
			m_bAxis				= pDrCurve->IsAxisInput();
			m_nAxis				= pDrCurve->GetAxis();
			m_bNegative			= pDrCurve->IsNegative();
		}
		else
		if(m_nInputType == CIRCLE_BY_NO3)
		{
			m_Center_S			= pDrCurve->GetCenter_S();
			m_Radius_S			= pDrCurve->GetRadius_S();
			m_vAxis_S			= pDrCurve->GetNormal_S();
			m_FromPt_S			= pDrCurve->GetCenter_S();
			m_nMaxCurveINodes_S	= 1;							// Use Only the First One 
		}
		//////////////////////////////////////////////////////
		m_pNum_t_S			= pDrCurve->GetNum_tPointer_S();
		m_pNum_t_Ex_S		= pDrCurve->GetNum_tPointer_Ex_S();
		m_dAng1_S			= 0;		
		m_dAng2_S			= pDrCurve->GetTheta_S();		
		////////////////////////////////////////////////
		m_nSegs_S			= pDrCurve->GetSegmentCount_S();	// # of Bezier Curvees 
															// in Rotation dirn
		////////////////////////////////////////////////
		m_Ratio_S			= pDrCurve->GetRatio_S();
		m_bUnifOT_S			= pDrCurve->IsUniform_S();
		m_nOut_S			= pDrCurve->GetMaxOutPts_S();;
		m_nOrder_S			= pDrCurve->GetOrder_S();
		m_CurveType_S		= pDrCurve->GetCurveType_S();;
		m_nDim_S			= pDrCurve->GetnDim_S();
		m_bClosed_S			= pDrCurve->IsClosed_S();					// for Extrusion
		///////////////////////////////////// Angle Distribution
		m_pDisAng_S			= pDrCurve->GetDis_AngPointer_S();	// Distribution of angles 
		///////////////////////////////////////// Bezier Quadratic
		m_nOut_SCon			= 2 * m_nSegs_S + 1;	// # of  Bezier Controls in S-dir
		if(m_bClosed_S)
				m_nOut_SCon--;
		/////////////////////////////////////
		m_nSegs_SCon		= m_nOut_SCon - 1;
		m_nMaxCurveCNodes_S = m_nOut_SCon;
		////////////////////////////////////////////////// PrepInfo
#ifdef _DEBUG
		///////////////////////////////////////// Check
		int i;
		double dTotAng=0.0,dAngInc;
		//////
		for(i=0;i<m_nSegs_S;i++)
		{
			dAngInc	= m_pDisAng_S[i];
			dTotAng	+= dAngInc;
		}
		if(fabs(dTotAng-(m_dAng2_S-m_dAng1_S) )>.01)
		{
			AfxMessageBox("ERROR\nCMC_Circl::GetInfo()-fabs(dTotAng-(m_dAng2_S-m_dAng1_S) )>.01");
			return (CDrCurve*)NULL;
		}
#endif
		////////////////
		return pDrCurve;
	}
	else 
		return (CDrCurve*)NULL;
}
			
int CMC_Circl::Circle_PrepInterpolation()
{
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
	if(1!=1 ) // iDLL = 12 , Module = 1
	{
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);

		int j;
		//////////
		sprintf(buf,"CMI_GangC::Circle_PrepInterpolation");
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
	
	m_nSeg_DT_S	= CSeg_DT;					// L
	m_nDegree_S	= m_nOrder_S-1;				// k -1
	/////////////////////////////////////////////////////////////////// FillUp 
	m_nData_S	= m_pDrCurve->GetData_Ex_S();	// Adjusted# of Data for Conics(Circle) 
	//////////////////////////////////////////////////////////
	m_nCon_BS_S	= m_pDrCurve->GetnCon_BS_S();
	m_nCon_BZ_S	= m_pDrCurve->GetnCon_BZ_S(); // = m_nMaxCurveCNodes
	////////////////////////////////////////////////////
	return 0;
}
		
int CMC_Circl::Circle() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
//	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////// Memory:ControlPts 
	m_pData		= FixMem((long)m_nMaxCurveINodes_S);
	m_pWts_DT_S	= FixMemD((long)m_nMaxCurveINodes_S);
	if( !m_pData || !m_pWts_DT_S )
	{
		AfxMessageBox("CMC_Circl::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	/////////////////////////// Store LOCAL Pos	
	FillINodesLOCAL(m_pDrCurve->GetINodeList(),
					m_pData,m_pWts_DT_S,m_nMaxCurveINodes_S);
	////////////////////////////////// Save CurveInfo
	m_nOut				= ((long)m_nOut_S);				
	m_nOutCon			= ((long)m_nOut_SCon);				
	m_nMaxCurveCNodes_S	= (int)m_nOutCon;
	/////////////////////////////////////
	if(m_nInputType == CIRCLE_BY_ROT)
	{
		///////////////////////////////////////// AxisVector from
	    									   // end nodes	
		UnitAxisFromEndNodes(&m_vAxis_S);
		///////////////////////////////////////// Center & Radius
		Calc_CandR(m_pData,&m_Center_S, &m_Radius_S, m_vAxis_S, m_FromPt_S);
	}
	/////////////////////////////////////////// Memory OutPts 
	m_pCon_BZ_S = FixMem(m_nOutCon);
	m_pWts_BZ_S	= FixMemD(m_nOutCon);
	if( !m_pCon_BZ_S || !m_pWts_BZ_S )
	{
		AfxMessageBox("CMC_Circl::Rotate\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Rotate 
	int nResult = GenerateCNodes();
	/////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

void CMC_Circl::FillINodesLOCAL(CDListMgr* pCurveCNodeList,
							pWORLD pIn,pDOUBLE pInWts,int nMaxCNodes)
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
    	//////////////////////////////////////// NPC Pt.
    	LocalPos = *(pDrNode->GetLocalPos());
    	/////////////////////////////////
		pIn[i].x = LocalPos.x;	  
		pIn[i].y = LocalPos.y;  
		pIn[i].z = LocalPos.z;
		//////////////////////////////////////// Wts
		pInWts[i] = 1.0;
	}	
}

int CMC_Circl::Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE Radius, WORLD Normal,WORLD AxPt)
{
	///////////////////////////////////////////////////////
	// given:
	//		Data	= a Pt. on the Current Circle
	//		Normal	= to the Plane of the circle
	//		AxPt	= a Pt on the Normal
	// Now
	//		RadVec	= the vector from Data to Center
	//				= RadVecA - RadVecD;
	// where
	//		RadVecD	= the perpendicular vector from Data to Normal
	//				= Data - (Data.dot.Normal)Normal
	//		RadVecA	= the perpendicular vector from AxPt to Normal 
	//				= AxPt - (AxPt.dot.Normal)Normal
	//
	// and		
	//		Center	= rData + RadVec;
	//		Radius	= ||RadVec||
	////////////////////////////////////////////////////////
	C3DMath	Math3D;
	//////////////////////////////////////// RadVec
	WORLD	RadVec,RadVecD,RadVecA,temp;
	double	dotn;
	///////////////////
	dotn	= Math3D.Dot3DPts(pData,&Normal);
	temp.x	= Normal.x;
	temp.y	= Normal.y;
	temp.z	= Normal.z;
	Math3D.Scale3DPts(dotn,&temp);
	Math3D.Sub3DPts(pData, &temp, &RadVecD);
	///////////////////
	dotn	= Math3D.Dot3DPts(&AxPt,&Normal);
	temp.x	= Normal.x;
	temp.y	= Normal.y;
	temp.z	= Normal.z;
	Math3D.Scale3DPts(dotn,&temp);
	Math3D.Sub3DPts(&AxPt, &RadVecD, &RadVecA);
	/////////////////////////////////////////// Radius Vec
	Math3D.Sub3DPts(&RadVecA, &temp, &RadVec);
	/////////////////////////////////////////// Radius
	*Radius = Math3D.Len3DPts(&RadVec); 
	/////////////////////////////////////////// Center
	Math3D.Add3DPts(pData, &RadVec, pCenter);
	/////////
	return 0;

}

void CMC_Circl::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	//////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////
//	int 		index;
//	CDrNode* 	pDrNode;
	////////////////////////////////////////////////////// FromNode
  	///////////////////////////////////////////// get Raw Pt.
   	m_FromPt_S = *(m_pFromIDNode->GetLocalPos());
	////////////////////////////////////////////////////// ToNode or Axis
/*
	if(m_bAxis)
	{
		m_ToPt_S.x = m_FromPt_S.x; 
		m_ToPt_S.y = m_FromPt_S.y; 
		m_ToPt_S.z = m_FromPt_S.z; 
		//
		switch(m_nAxis)
		{
			case 1:	m_bNegative?m_ToPt_S.x += -1.0:m_ToPt_S.x += 1.0;	break;
			case 2:	m_bNegative?m_ToPt_S.y += -1.0:m_ToPt_S.y += 1.0;	break;
			case 3:	m_bNegative?m_ToPt_S.z += -1.0:m_ToPt_S.z += 1.0;	break;
			default:
				{
					AfxMessageBox("Internal ERROR:\nCMC_Circl::UnitAxisFromEndNodes()\nm_nAxis !=1,2or3");
					return;
				}
		}
	}
	else
	{
*/		
	  	///////////////////////////////////////////// get Raw Pt.
	 	m_ToPt_S = *(m_pToIDNode->GetLocalPos());
/*
	}
*/
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&m_ToPt_S, &m_FromPt_S, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;
}

int CMC_Circl::GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Curve Pts
	CCU_Circl	Circle;		 	   	
	int nOutActual	= Circle.RotatePoint
			(
				m_Center_S,
				m_Radius_S,
				m_bClosed_S,
				m_nSegs_S,			//	# of Quadratic Bezier Segments
				m_pDisAng_S,		//	Angle Distribution for each Bez Curve in degrees
				m_vAxis_S,			//	unit rotation vector (direction)
//				m_FromPt_S,			//	a pt. on the rotation vector
				m_nSegs_SCon,		//	subdivision value (interior spaces)
				m_nMaxCurveINodes_S,//	number of input data points
				m_pData,			//	input XSec curve dataPts
				m_pWts_DT_S,		//	input XSec curve Wts
				m_pCon_BZ_S,		//	Output ControlPts
				m_pWts_BZ_S			//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
		return 0;
												
}
	 		
int CMC_Circl::Circle_PostInterpolation(BOOL bFinal)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////////////////////// FillUp 
	////////////////////// Memory for Interpolation
//	m_pDrCurve->SetpMKnots_S(m_pMKnot_S)	//---|	 THESE ACTUALLY NOT NEED, OUR
//	m_pDrCurve->SetpWts_BS_S(m_pWts_BS_S)	//---|-- INTERNAL REPRESENTATION: ALWAYS  B E Z I E R
//	m_pDrCurve->SetpCon_BS_S(m_pCon_BS_S)	//---|   RATIONAL or NONraional
	////////////////////////////////////////////////////////////////////
	// Create CNodes from Bezier Pts. and store in:
	//		MainList and
	//		CNodeList of DrCurve
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	m_pOut				= m_pCon_BZ_S;
	//////////////////////////////////////////////// 
	CurveID				= m_pDrCurve->GetObjectID();
	m_nCon_BZ_S		 	= m_pDrCurve->GetnCon_BZ_S();
	m_pCNodeList		= m_pDrCurve->GetCNodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NUM_LEN-2)
		nChLen = NUM_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	m_bArc = m_pDrCurve->IsArcType();
	///
	for (s = 0; s<m_nCon_BZ_S; s++)
	{
		////////////////////////////////////
		j = t*m_nCon_BZ_S + s;
		////////////////////////////		
		LocalPos.x	= (m_pOut+j)->x;
		LocalPos.y	= (m_pOut+j)->y;
		LocalPos.z	= (m_pOut+j)->z;
		////////////////////////////////////////////////////////////////////////// CREATE	
//		Nid		= CurveID.Left(nChLen);
		Nid		= CurveID;
	    //////////////////////////////////// 
		sprintf(buf,"%d%d",s,t);
		Nid += buf;
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(Nid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		//////////////////////////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		m_pCNodeList->InsertObject(pAddNode); //CNodeList
		//////////
		if(bFinal)
		{
			//////////////////////////////////////////// if New Node Reciprocate
//			if(pAddNode->GetObjectID() == Nid)
//			{
				//////////////////////////////////////// Reciprocate
//				int index = pAddNode->GetCurveList()->GetObjectIndex(m_pDrCurve);
//				if(index<0) // not in the list
//					pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
				////////
			}
			/////////////////////////////////////////////////////////// INODE HANDLE
			// Last One make ADDITIONAL COPY HANDLE Node public
			// for m_nInputType = CIRCLE_BY_ROT
			// for m_nInputType = CIRCLE_BY_NO3 with !m_bArc
			////////////////////////////////////////////////////
			if( (s == m_nCon_BZ_S-1) &&
				( (m_nInputType == CIRCLE_BY_ROT) || ((m_nInputType == CIRCLE_BY_NO3) && !m_bArc) )   ) 
			{

				pObjectMgr->SetNodeInfoID(Nid,FALSE/*bCNode*/,FALSE/*bMNode*/);
				/////////////
				CDrLabel* pLabel;
				int nNodeIndex,nLabelIndex;
				/////////////////////////// Create Anyway
				nNodeIndex = -12345;
				pAddNode = 
					CreateNode(Nid,pLabel,LocalPos,FALSE,TRUE,nNodeIndex,nLabelIndex,LEVEL_GRAPA);
				//////////////////////////////////
				if(!pAddNode)	// Create DrINode
					return -1;
				///////////////////////////////////////////////// Reciprocate
				int index = pAddNode->GetCurveList()->GetObjectIndex(m_pDrCurve);
				if(index<0)
					pAddNode->GetCurveList()->InsertObject(m_pDrCurve);
				//////
				index = m_pDrCurve->GetElemList()->GetObjectIndex(pAddNode);
				if(index<0)
					m_pDrCurve->GetElemList()->InsertObject(pAddNode); // Auxiliary INode in ElemList
			}
		////////////////////////////////////////////////////////////////////////////
		}
		////////
	}
	/////////////////////////////////////////////////////////////// B-Splines
	// 		CONTROL NODE CREATION WILL BE DONE SIMILARLY LATER
	/////////////////////////////////////////////////////////////// save memory				
	m_pDrCurve->SetpWts_BZ_S(m_pWts_BZ_S);
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

void CMC_Circl::Serialize(CArchive& ar)
{

	CMI_GangC::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMC_Circl:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMC_Circl:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
