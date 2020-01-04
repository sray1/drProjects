// Rotate.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "glb_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "EBoxmgr.h" 
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "EDlgMgr.h"
///////////////////// elements
#include "eldefine.h"
#include "elextern.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "spdefine.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "PA_Rotat.h"
 
#include "MP_Rotat.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_Rotat,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Rotat::CMP_Rotat()
{
}

CMP_Rotat::~CMP_Rotat()
{
}

CDrPatch* CMP_Rotat::GoDoIt() 
{
	//////////////////////////////////////////////////////////
	m_pDrPatch 		= GetInfo();       // PGen Dialog
	if(!m_pDrPatch)		// cancel
		return (CDrPatch*)NULL;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrPatch->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Rotate();
	////////////////////////
	m_PatchType = PA_TENSOR;
	////////////////////////
	if(InsertMeshInfo(FALSE)<0)
		return (CDrPatch*)NULL;
	/////////////////////
	return m_pDrPatch;
}			

CDrPatch* CMP_Rotat::GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////////////////
	CEDlgMgr* 	pEDlgMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pEDlgMgr->DoModal_Patch_Rotate(&Cid,4) == IDCANCEL)
			return (CDrPatch*)NULL; 
    /////////////////////////////////////////////////////// update
	m_CurrentPatchID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{						
		CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_PatchProc		= pDrPatch->GetPatchProc();
		m_pNum_t_T		= pDrPatch->GetNum_tPointer_T();
		m_FromID 		= pDrPatch->GetFromID_T();
		m_ToID			= pDrPatch->GetToID_T();
		m_CurveID_S[0]	= pDrPatch->GetCurveID(0);
		m_dAng_1		= pDrPatch->GetAng_1_T();		// Increment for Uniform case
		m_dAng_2		= pDrPatch->GetAng_2_T();
		////////////////////////////////////////////////
		m_nSegs_T		= pDrPatch->GetSegmentCount_T();	// # of Bezier Patches 
															// in Rotation dirn
		////////////////////////////////////////////////
		m_Ratio			= pDrPatch->GetRatio_T();
		m_bUnifOT		= pDrPatch->IsUniform_T();
		m_nOut_T		= pDrPatch->GetMaxOutPts_T();;
		m_nOrder_T		= pDrPatch->GetOrder_T();
		m_CurveType_T	= pDrPatch->GetCurveType_T();;
		m_nDim_T		= pDrPatch->GetnDim_T();
		m_bClosed_T		= pDrPatch->IsClosed_T();					// for Extrusion
		///////////////////////////////////// Angle Distribution
		m_pDisAng_T		= pDrPatch->GetDis_AngPointer_T();	// Distribution of angles 
		///////////////////////////////////////// Bezier Quadratic
		m_nOut_TCon		= 2 * m_nSegs_T + 1;	// # of  Bezier Controls in T-dir
		if(m_bClosed_T)
				m_nOut_TCon--;
		/////////////////////////////////////
		m_nSegs_TCon		= m_nOut_TCon - 1;
		m_nMaxPatchCNodes_T = m_nOut_TCon;

#ifdef _DEBUG
		///////////////////////////////////////// Check
		int i;
		double dTotAng=0.0,dAngInc;
		//////
		for(i=0;i<m_nSegs_T;i++)
		{
			dAngInc	= m_pDisAng_T[i];
			dTotAng	+= dAngInc;
		}
		if(fabs(dTotAng-m_dAng_2)>.01)
		{
			AfxMessageBox("ERROR\nCMP_Rotat::GetInfo()-fabs(dTotAng-m)dAng_2)>.01");
			return (CDrPatch*)NULL;
		}
#endif
		////////////////
		return pDrPatch;
	}
	else 
		return (CDrPatch*)NULL;
}			

int CMP_Rotat::Rotate() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	///////////////////////////////////////////////////
	CString		CurveID;
	BOOL		bPutinCNodeList = TRUE;
	int i;
	///////////////////////////////////////// Generate CNodes
   	CurveID = m_CurveID_S[0];
	//////////////////////////////////////// get Curve Info	
	int index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);
	if(index<0)
	{
		AfxMessageBox("CMP_Rotat::Rotate\nCurveIndex Failure!");
		return -1;
	}
	///////////	
	CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	if(!pDrCurve)
		return -1;
	/////////////////
	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// Memory:ControlPts 
	m_pIn_S[0] = FixMem((long)m_nMaxCurveCNodes_S);
	m_pInWts_S[0]	= FixMemD((long)m_nMaxCurveCNodes_S);
	if( !m_pIn_S[0] || !m_pInWts_S[0] )
	{
		AfxMessageBox("CMP_Rotat::Curve\nFixMemforCNodes Failure!");
		return -1;
	}
	/////////////////////////// Store LOCAL Pos	
	FillCNodesLOCAL(pDrCurve->GetCNodeList(),m_pWts_BZ_S,
		m_pIn_S[0],m_pInWts_S[0],m_nMaxCurveCNodes_S,bPutinCNodeList,
		FALSE);
	////////////////////////////////// Save PatchInfo
	m_nOut				= (((long)m_nOut_S)*((long)m_nOut_T) );				
	m_nOutCon			= (((long)m_nOut_SCon)*((long)m_nOut_TCon) );				
	m_nMaxPatchCNodes	= (int)m_nOutCon;
    ///////////////////////////////////////// AxisVector from
    									   // end nodes	
    UnitAxisFromEndNodes(0);
	/////////////////////////////////////////// Memory OutPts 
	m_pOut = FixMem(m_nOutCon);
	m_pOutWts	= FixMemD(m_nOutCon);
	if( !m_pOut || !m_pOutWts )
	{
		AfxMessageBox("CMP_Rotat::Rotate\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Rotate 
	int nResult = GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			FreeMemD(m_pInWts_S[i]);
			m_pIn_S[i] = NULL;
			m_pInWts_S[i] = NULL;
		}	
	}	
	/////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMP_Rotat::GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Rotat	Rotat;		 	   	
	int nOutActual	= Rotat.RotateCurve
			(
				m_bClosed_T,
				m_nSegs_T,		//	# of Quadratic Bezier Segments
				m_pDisAng_T,	//	Angle Distribution for each Bez Patch in degrees
				m_vAxis,		//	unit rotation vector (direction)
				m_FromPt,		//	a pt. on the rotation vector
				m_nSegs_TCon,	//	subdivision value (interior spaces)
				m_nOut_SCon,	//	number of input data points
				m_pIn_S[0],		//	input XSec curve dataPts
				m_pInWts_S[0],	//	input XSec curve Wts
				m_pOut,			//	Output ControlPts
				m_pOutWts		//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
		return 0;
												
}

void CMP_Rotat::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Rotat:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Rotat:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module //////////////////
