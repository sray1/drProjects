// Loft2.cpp : implementation file
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
//#include "MPatMgr.h"
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
#include "PA_CoonP.h"
 
#include "MP_CoonP.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_CoonP,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_CoonP::CMP_CoonP()
{
	m_bBack = FALSE;
}

CMP_CoonP::~CMP_CoonP()
{
}
int CMP_CoonP::GoDoIt(
						CString&	PatchID,		
						CDrPatch*	pDrPatch,
//						CString		PatCurveID[],
						CDListMgr*	pCurveList,
//						CURVELATCH	PatCurveLatchID[]
						CList<CURVELATCH,CURVELATCH>*	pLatchList
				     )
{
	POSITION pos;
	m_PatchID = PatchID;
	////////////////////
	m_pCurve_S[0]	= (CDrCurve*)pCurveList->GetObject(0);	// Curve_1
	m_pCurve_S[1]	= (CDrCurve*)pCurveList->GetObject(1);	// Curve_2
	m_pCurve_S[2]	= (CDrCurve*)pCurveList->GetObject(2);	// Curve_3
	m_pCurve_S[3]	= (CDrCurve*)pCurveList->GetObject(3);	// Curve_4
	//////////////////////////////////////////////////////
	pos = pLatchList->FindIndex(0);
	m_CuLatch[0]	= pLatchList->GetAt(pos);
	pos = pLatchList->FindIndex(1);
	m_CuLatch[1]	= pLatchList->GetAt(pos);
	pos = pLatchList->FindIndex(2);
	m_CuLatch[2]	= pLatchList->GetAt(pos);
	pos = pLatchList->FindIndex(3);
	m_CuLatch[3]	= pLatchList->GetAt(pos);
	/////////////////////////////////////////////// ElemCompatibility 
//	if(!CheckElemCompatibility(PatCurveID))
	if(!CheckElemCompatibility())
		return -1;
	/////////////////////////////////////////////// PatBy Controls or Elems
	FindIfPatByControl(&m_bSdirByControl,&m_bTdirByControl);
	/////////////////////////////////////////////// ControlNode Mesh
	m_pDrPatch 		= pDrPatch;
	m_CurrentPatchID= PatchID;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrPatch->GetCNodeList();	
	////////////////////////////////// Info
	m_PatchProc		= PP_COONSQUAD;
	//////////////////////////////////////////////////////////////// ControlNode Mesh
	// NOTE:	Later we will degree elevate and match
	//			segments in both u and v-directions
	//			so that we can build patch by
	//			Coons with Controls only
	//			For now we are settling for less efficient
	//			Coons by Nodes when u & v direction number of
	//			controls or orders donot match.
	/////////////////////////////////////////////////////////////////
//	if(!m_bSdirByControl && !m_bTdirByControl)
	if(!m_bSdirByControl || !m_bTdirByControl)	//050697
	{
		if(Coon()>=0)			// if C_Spawned Curve
			/////////////////////////////////////////////// DATABASE 
			SetInfoForCoonBase(pDrPatch);
	}
	else
	{
		if(Coon_ByControl()>=0)
			/////////////////////////////////////////////// DATABASE 
			SetInfoForCoonBase_ByControl(pDrPatch);
	}
	////////////////////////
	m_PatchType = PA_COONS;
	////////////////////////
	if(InsertMeshInfo(FALSE)<0)		// WE HAVE CHANGED TO FALSE
									// TO SAVE ALL CONTROL NODES
		return -1;
	else
		/////////
		return 0;
}			

int CMP_CoonP::FindIfPatByControl(BOOL* bSdir,BOOL* bTdir)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
    ///////////////////	
	double	Ratio1,Ratio2,Ratio3,Ratio4;;
	int		nOrder1,nOrder2,nOrder3,nOrder4;
	int		nCount1,nCount2,nCount3,nCount4;
	CDrCurve* pDrCurve1;
	CDrCurve* pDrCurve2;
	CDrCurve* pDrCurve3;
	CDrCurve* pDrCurve4;
	////////////////////////////////////////////////////////////////////////// Curve1 :S-Dir
	pDrCurve1	= m_pCurve_S[0];
	nCount1		= pDrCurve1->GetMaxCNodes_S();
	nOrder1		= pDrCurve1->GetOrder_S();
	Ratio1		= pDrCurve1->GetRatio_S();
	////////////////////////////////////////////////////////////////////////// Curve3
	pDrCurve3	= m_pCurve_S[2];
	nCount3		= pDrCurve3->GetMaxCNodes_S();
	nOrder3		= pDrCurve3->GetOrder_S();
	Ratio3		= pDrCurve3->GetRatio_S();
	////////////////////////////////////////////////////////////////////////// Curve2 :T-Dir
	pDrCurve2	= m_pCurve_S[1];
	nCount2		= pDrCurve2->GetMaxCNodes_S();
	nOrder2		= pDrCurve2->GetOrder_S();
	Ratio2		= pDrCurve2->GetRatio_S();
	////////////////////////////////////////////////////////////////////////// Curve4
	pDrCurve4	= m_pCurve_S[3];
	nCount4		= pDrCurve4->GetMaxCNodes_S();
	nOrder4		= pDrCurve4->GetOrder_S();
	Ratio4		= pDrCurve4->GetRatio_S();
	/////////////////////////////////////////////////////////////////////////////////
	*bSdir	= TRUE;
	*bTdir	= TRUE; 
	//////////////////////
	if(nCount1 != nCount3)
	{
		*bSdir	= FALSE;
		return 0;
	}
	if(nCount2 != nCount4)
	{
		*bTdir	= FALSE;
		return 0;
	}
	//////////////////////
	if(nOrder1 != nOrder3)
	{
		*bSdir	= FALSE;
		return 0;
	}
	if(nOrder2 != nOrder4)
	{
		*bTdir	= FALSE;
		return 0;
	}
	/////////////////////////////////////////////////////
	//	For Ratio Business Do it by Nodes NOT by Controls
	//	Single Segment && Linear
	/////////////////////////////////////////////////////
	if(	
		(nCount1 == 2 && nOrder1 == 2 && Ratio1 != 1.0)	|| 
		(nCount2 == 2 && nOrder2 == 2 && Ratio2 != 1.0)	|| 
		(nCount3 == 2 && nOrder3 == 2 && Ratio3 != 1.0)	|| 
		(nCount4 == 2 && nOrder4 == 2 && Ratio4 != 1.0)	
	)
	{  	
		*bSdir	= FALSE;
		*bTdir	= FALSE;
		////
		return 0;
	}
	/////////
	return 0;
}

BOOL CMP_CoonP::CheckElemCompatibility()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
    ///////////////////	
	BOOL bClosed;
	int nOut1,nOut2;
	CDrCurve* pDrCurve1;
	CDrCurve* pDrCurve2;
	CDrCurve* pDrCurve3;
	CDrCurve* pDrCurve4;
    ///////////////////////////////////////////////////////////////////////// Check S-dir Compatibility
	////////////////////////////// nOut_S must be same
	pDrCurve1	= m_pCurve_S[0];
	nOut1		= pDrCurve1->GetMaxOutPts_S();
	bClosed		= pDrCurve1->IsClosed_S();
	////////////////////////////////////////////////////////////////////////// Curve3
	pDrCurve3	= m_pCurve_S[2];
	nOut2		= pDrCurve3->GetMaxOutPts_S();
	bClosed		= pDrCurve3->IsClosed_S();
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_1:\n\tNumber of Elements = %d\nCURVE_3:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return FALSE;
	}
    ///////////////////////////////////////////////////////////////////////// Check T-dir Compatibility
	///////////////////////////////////////////////////////////////////////// Curve2
	pDrCurve2		= m_pCurve_S[1];
	nOut1			= pDrCurve2->GetMaxOutPts_S();
	bClosed			= pDrCurve2->IsClosed_S();
	////////////////////////////////////////////////////////////////////////// Curve4
	pDrCurve4		= m_pCurve_S[3];
	nOut2			= pDrCurve4->GetMaxOutPts_S();
	bClosed			= pDrCurve4->IsClosed_S();
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_2:\n\tNumber of Elements = %d\nCURVE_4:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return FALSE;
	}
	///////////////////////////////////////////////////////////////// OK
	return TRUE;
}

int CMP_CoonP::Coon()
{
	//////////////////////////////////////////////////////////////////////////////////
	//	CoonP is LINEAR interpolation of GENERATED NODES, NOT of CONTROL NODES		//
	//	of the curves in S/T-Direction. So, all generated nodes of Curves will		//
	//	be saved as CNodes of the patch in S/T-Direction and eventually the PATCH	//
	//  will be generated by LINEAR interpolation in S/T- direction,				//
	//					IRRESPECTIVE of CURVETYPE of SPINE							// 												//
	//	THIS INEFFICIENCY is needed for Finite Element Data Generation wherein		//
	//		Total Tally of Generated Nodes are important , Not of Control Nodes		//
	//////////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* 	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CDrCurve*	pDrCurve;
	int			nResult;
	CString		CurveID;
	///////////////////////// 
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	
	if(m_pOutWts != NULL)
	{
		FreeMemD(m_pOutWts);
		m_pOutWts = NULL;
	}	
	///////////////////////////////////////////////////////////////// S-dir
/*
	//////////////////////////////////////////////////////// Curve_1
   	CurveID = m_CurveID_S[0];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[0];
	if(!pDrCurve)
		return -1;
	////////////////////////////////////// Set Curve Info	
	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// PreProcess: Curve_1
	nResult = Pre_Curve(pDrCurve, 0, m_nOut_S);
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////// Curve_3
/*
   	CurveID = m_CurveID_S[2];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[2];
	if(!pDrCurve)
		return -1;
	/////////////////////////////////////////// PreProcess: Curve_3
	nResult = Pre_Curve(pDrCurve, 2, m_nOut_S);
	if(nResult<0)
		return -1;
	/////////////////////////////////////////// Reset S-Con
	Curve_S_Process();
	///////////////////////////////////////////////////////////////// T-dir
/*
	//////////////////////////////////////////////////////// Curve_2
   	CurveID = m_CurveID_S[1];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[1];
	if(!pDrCurve)
		return -1;
	////////////////////////////////////// Set Curve Info	
	GetInfo_Curve_T(pDrCurve);
	/////////////////////////////////////////// PreProcess: Curve_2
	nResult = Pre_Curve(pDrCurve, 1, m_nOut_T);
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////// Curve_4
/*
   	CurveID = m_CurveID_S[3];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[3];
	if(!pDrCurve)
		return -1;
	/////////////////////////////////////////// PreProcess: Curve_4
	nResult = Pre_Curve(pDrCurve, 3, m_nOut_T);
	if(nResult<0)
		return -1;
	/////////////////////////////////////////// Reset T-Con
	Curve_T_Process();
	////////////////////////////////// Save PatchInfo
	m_nOut				= (((long)m_nOut_S)*((long)m_nOut_T) );				
	m_nOutCon			= (((long)m_nOut_SCon)*((long)m_nOut_TCon) );				
	m_nMaxPatchCNodes	= (int)m_nOutCon;
	/////////////////////////////////////////// Memory OutPts 
	m_pOut		= FixMem(m_nOutCon);
	m_pOutWts	= FixMemD(m_nOutCon);
	if( !m_pOut || !m_pOutWts )
	{
		AfxMessageBox("CMP_CoonP::Loft\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Loft 
	nResult = GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
	int i;
	//////
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
    	if(m_pInWts_S[i])
    	{
			FreeMemD(m_pInWts_S[i]);
			m_pInWts_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMP_CoonP::Pre_Curve(CDrCurve* pDrCurve,int i, int nOut)
{

	/////////////////////////////////////////////// Memory OutPts
	m_pIn_S[i]		= FixMem(nOut);
	m_pInWts_S[i]	= FixMemD(nOut);
	if( !m_pIn_S[i] || !m_pInWts_S[i] )
	{
		AfxMessageBox("CMP_CoonP::Pre_Curve\nFixMem Failure!");
		return -1;
	}
	/////////////////////////////////////////////// Generate Curve
	m_bBack = FALSE;
	if(m_CuLatch[i] == CL_BACKWARD)
		m_bBack = TRUE;
	FillMeshNodesCurve(pDrCurve, m_pIn_S[i], m_pInWts_S[i], nOut );
	///////////////
	return 0;

}

int CMP_CoonP::Curve_S_Process()
{
	int i;
	////////////////////////////////////// LINEAR BEZIER in S-direction
	m_nSegs_S			= 1;	// ALWAYS
	m_nOrder_S			= 2;	// ALWAYS
	m_CurveType_S		= CP_LINEAR;
	m_nOut_SCon			= m_nOut_S;
	m_nSegs_SCon		= m_nOut_SCon - 1;
	///////////
	if(m_bClosed_S)
	{
		m_nOut_SCon--;
	}
	/////////////////////////////////////
	m_nMaxPatchCNodes_S = m_nOut_SCon;
	/////////
	m_pNum_t_S			= new int[m_nSegs_SCon];
	for (i=0;i<m_nSegs_SCon;i++)
		m_pNum_t_S[i] = 1;
	////////////////////
	return 0;
}

int CMP_CoonP::Curve_T_Process()
{
	int i;
	////////////////////////////////////// LINEAR BEZIER in S-direction
	m_nSegs_T			= 1;	// ALWAYS
	m_nOrder_T			= 2;	// ALWAYS
	m_CurveType_T		= CP_LINEAR;
	m_nOut_TCon			= m_nOut_T;
	m_nSegs_TCon		= m_nOut_TCon - 1;
	///////////
	if(m_bClosed_T)
	{
		m_nOut_TCon--;
	}
	/////////////////////////////////////
	m_nMaxPatchCNodes_T = m_nOut_TCon;
	/////////
	m_pNum_t_T			= new int[m_nSegs_TCon];
	for (i=0;i<m_nSegs_TCon;i++)
		m_pNum_t_T[i] = 1;
	////////////////////
	return 0;
}

int CMP_CoonP::GetInfo_Curve_T(CDrCurve* pDrCurve)
{
	/////////////////	
	m_pWts_BZ_T			= pDrCurve->GetpWts_BZ_S();		
	m_nMaxCurveCNodes_T = pDrCurve->GetMaxCNodes_S();
	////////////////////////////////////////////////// FILL INFO
	m_nDim_T			= pDrCurve->GetnDim_S();
	m_pNum_t_T			= pDrCurve->GetNum_tPointer_S();
	m_pDis_t_T			= pDrCurve->GetDis_tPointer_S();
	m_pNum_t_Ex_T		= pDrCurve->GetNum_tPointer_Ex_S();
	m_CurveType_T		= pDrCurve->GetCurveType_S();
	m_nOrder_T			= pDrCurve->GetOrder_S();
	///////////////////////////////////////////	
	m_bClosed_T			= pDrCurve->IsClosed_S();		// X-Section
	m_nOut_TCon			= (int)m_nMaxCurveCNodes_T;
    ///////////////////////////////////
	m_nOut_T			= (int)pDrCurve->GetLongOutPts();
	m_nSegs_T			= pDrCurve->GetSegmentCount_S();
	//////// 
	m_nSegs_TCon		= m_nOut_TCon - 1;
	m_nMaxPatchCNodes_T = m_nOut_TCon;
	///////////////////////////////
	return 0;
}

int CMP_CoonP::Coon_ByControl()
{
	//				C O O N  B Y  C O N T R O L 
	//////////////////////////////////////////////////////////////////////////////////
	//	CoonP is LINEAR interpolation of GENERATED NODES, NOT of CONTROL NODES		//
	//	of the curves in S/T-Direction. So, all generated nodes of Curves will		//
	//	be saved as CNodes of the patch in S/T-Direction and eventually the PATCH	//
	//  will be generated by LINEAR interpolation in S/T- direction,				//
	//////////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* 	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CDrCurve*	pDrCurve;
	int			nResult;
	CString		CurveID;
	///////////////////////// 
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	
	if(m_pOutWts != NULL)
	{
		FreeMemD(m_pOutWts);
		m_pOutWts = NULL;
	}	
	///////////////////////////////////////////////////////////////// S-dir
/*
	//////////////////////////////////////////////////////// Curve_1
   	CurveID = m_CurveID_S[0];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[0];
	if(!pDrCurve)
		return -1;
	////////////////////////////////////// Set Curve Info
	// Once in S-dir enough for Element-Based
	// because curve will be generated for
	// new weights etc.
	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// PreProcess: Curve_1
	if(m_bSdirByControl)
		nResult = Pre_Curve_ByControl(pDrCurve, 0, m_nMaxCurveCNodes_S);
	else
		nResult = Pre_Curve(pDrCurve, 0, m_nOut_S);
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////// Curve_3
/*
   	CurveID = m_CurveID_S[2];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[2];
	if(!pDrCurve)
		return -1;
	/////////////////////////////////////////// PreProcess: Curve_3
	if(m_bSdirByControl)
	{
		GetInfo_Curve(pDrCurve);	// for new Weights
		////////////////////////
		nResult = Pre_Curve_ByControl(pDrCurve, 2, m_nMaxCurveCNodes_S);
		if(nResult<0)
			return -1;
	}
	else
	{
		nResult = Pre_Curve(pDrCurve, 2, m_nOut_S);
		if(nResult<0)
			return -1;
		/////////////////////////////////////////// Reset S-Con
		Curve_S_Process();
	}
	///////////////////////////////////////////////////////////////// T-dir
	//////////////////////////////////////////////////////// Curve_2
/*
   	CurveID = m_CurveID_S[1];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[1];
	if(!pDrCurve)
		return -1;
	////////////////////////////////////// Set Curve Info	
	// Once in T-dir enough for Element-Based
	// because curve will be generated for
	// new weights etc.
	GetInfo_Curve_T(pDrCurve);
	/////////////////////////////////////////// PreProcess: Curve_2
	if(m_bTdirByControl)
		nResult = Pre_Curve_ByControl(pDrCurve, 1, m_nMaxCurveCNodes_T);
	else
		nResult = Pre_Curve(pDrCurve, 1, m_nOut_T);
	///////////////
	if(nResult<0)
		return -1;
	//////////////////////////////////////////////////////// Curve_4
/*
   	CurveID = m_CurveID_S[3];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
*/
	pDrCurve	= m_pCurve_S[3];
	if(!pDrCurve)
		return -1;
	/////////////////////////////////////////// PreProcess: Curve_4
	if(m_bTdirByControl)
	{
		GetInfo_Curve_T(pDrCurve);	// for new Weights
		////////////////////////
		nResult = Pre_Curve_ByControl(pDrCurve, 3, m_nMaxCurveCNodes_T);
		if(nResult<0)
			return -1;
	}
	else
	{
		nResult = Pre_Curve(pDrCurve, 3, m_nOut_T);
		if(nResult<0)
			return -1;
		/////////////////////////////////////////// Reset T-Con
		Curve_T_Process();
	}
	////////////////////////////////// Save PatchInfo
	m_nOut				= (((long)m_nOut_S)*((long)m_nOut_T) );				
	m_nOutCon			= (((long)m_nOut_SCon)*((long)m_nOut_TCon) );				
	m_nMaxPatchCNodes	= (int)m_nOutCon;
	/////////////////////////////////////////// Memory OutPts 
	m_pOut		= FixMem(m_nOutCon);
	m_pOutWts	= FixMemD(m_nOutCon);
	if( !m_pOut || !m_pOutWts )
	{
		AfxMessageBox("CMP_CoonP::Loft\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Loft 
	nResult = GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
	int i;
	//////
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
    	if(m_pInWts_S[i])
    	{
			FreeMemD(m_pInWts_S[i]);
			m_pInWts_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMP_CoonP::Pre_Curve_ByControl(CDrCurve* pDrCurve,int i, int nOut)
{

	m_bBack = FALSE;
	if(m_CuLatch[i] == CL_BACKWARD)
		m_bBack = TRUE;
	/////////////////////////////////////////////// Memory OutPts
	if(i == 0 || i == 2)
	{
		m_pIn_S[i]		= FixMem((long)m_nMaxCurveCNodes_S);
		m_pInWts_S[i]	= FixMemD((long)m_nMaxCurveCNodes_S);
		if( !m_pIn_S[i] || !m_pInWts_S[i] )
		{
			AfxMessageBox("CMP_CoonP::Pre_Curve\nFixMem Failure!");
			return -1;
		}
		/////////////////////////////////////////////// Generate Curve
		FillCNodesLOCAL(pDrCurve->GetCNodeList(),m_pWts_BZ_S,
			m_pIn_S[i],m_pInWts_S[i],m_nMaxCurveCNodes_S,FALSE);
	}
	else
	if(i == 1 || i == 3)
	{
		m_pIn_S[i]		= FixMem((long)m_nMaxCurveCNodes_T);
		m_pInWts_S[i]	= FixMemD((long)m_nMaxCurveCNodes_T);
		if( !m_pIn_S[i] || !m_pInWts_S[i] )
		{
			AfxMessageBox("CMP_CoonP::Pre_Curve\nFixMem Failure!");
			return -1;
		}
		/////////////////////////////////////////////// Generate Curve
		FillCNodesLOCAL(pDrCurve->GetCNodeList(),m_pWts_BZ_T,
			m_pIn_S[i],m_pInWts_S[i],m_nMaxCurveCNodes_T,FALSE);
	}
	///////////////
	return 0;

}

int CMP_CoonP::GetInfo_Curve_T_ByControl(CDrCurve* pDrCurve)
{
	/////////////////	
	m_pWts_BZ_T			= pDrCurve->GetpWts_BZ_S();		
	m_nMaxCurveCNodes_T = pDrCurve->GetMaxCNodes_S();
	////////////////////////////////////////////////// FILL INFO
	m_nDim_T			= pDrCurve->GetnDim_S();
	m_pNum_t_T			= pDrCurve->GetNum_tPointer_S();
	m_pDis_t_T			= pDrCurve->GetDis_tPointer_S();
	m_pNum_t_Ex_T		= pDrCurve->GetNum_tPointer_Ex_S();
	m_CurveType_T		= pDrCurve->GetCurveType_S();
	m_nOrder_T			= pDrCurve->GetOrder_S();
	///////////////////////////////////////////	
	m_bClosed_T			= pDrCurve->IsClosed_S();		// X-Section
	m_nOut_TCon			= (int)m_nMaxCurveCNodes_T;
    ///////////////////////////////////
	m_nOut_T			= (int)pDrCurve->GetLongOutPts();
	m_nSegs_T			= pDrCurve->GetSegmentCount_S();
	//////// 
	m_nSegs_TCon		= m_nOut_TCon - 1;
	m_nMaxPatchCNodes_T = m_nOut_SCon;
	///////////////////////////////
	return 0;
}

int CMP_CoonP::GenerateCNodes()
{

	////////////////////////////////////////////// 
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_CoonP	PA_CoonP;
	int nOutActual	= PA_CoonP.CoonCurves
			(
				(short)m_nOut_SCon,	//	number of input Control points in S-dir
				(short)m_nOut_TCon,	//	number of input Control points in T-dir
				m_pIn_S[0],			//	input data point for Curve 1
		      	m_pInWts_S[0],		//	input data Weight for Curve 1 
				m_pIn_S[1],			//	input data point for Curve 2
		      	m_pInWts_S[1],		//	input data Weight for Curve 2 
				m_pIn_S[2],			//	input data point for Curve 3
		      	m_pInWts_S[2],		//	input data Weight for Curve 3 
				m_pIn_S[3],			//	input data point for Curve 4
		      	m_pInWts_S[3],		//	input data Weight for Curve 4 
				m_pOut,				//	Output ControlPts array
				m_pOutWts			//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
		return 0;
												
}

void CMP_CoonP::SetInfoForCoonBase(CDrPatch* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetPatchType(PA_COONS);
	///////////////////////////////////////////
	pDrObject->SetPatchProc(PP_COONSQUAD);
	pDrObject->SetPatSubType(PS_QUADRILAT);
	////////////////////////////////////////////
	pDrObject->SetOrder_S(2);							// k = LINEAR for Loft
	pDrObject->SetOrder_T(2);							// k = LINEAR for Loft
	pDrObject->SetCurveType_T(CP_LINEAR);				// k = LINEAR for Loft
	pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
	pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_S(FALSE);						// k = LINEAR for Loft
	pDrObject->SetClosed_T(FALSE);						// k = LINEAR for Loft
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	/////////////////////////////////
	for(int i=0;i<4;i++)
		pDrObject->SetCurveLatch(m_CuLatch[i],i);
	////////////////////////////////////////////////////////////////////// Reciprocate
	pDrObject->GetCurveList()->RemoveAll();
	CDrCurve* pDrCurve;
	int index;
	//////////////////////////////////////
	pDrCurve	= m_pCurve_S[0];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[1];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[2];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[3];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
//	pDrObject->SetSegs(m_nSegs);
//	pDrObject->SetPatchType(PA_DUCT);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_T(PA_HORNER);		// Output Method
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 


void CMP_CoonP::SetInfoForCoonBase_ByControl(CDrPatch*	pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetPatchType(PA_COONS);
	///////////////////////////////////////////
	pDrObject->SetPatchProc(PP_COONSQUAD);
	pDrObject->SetPatSubType(PS_QUADRILAT);
	////////////////////////////////////////////
	if(m_bSdirByControl)
	{
		pDrObject->SetOrder_S(m_nOrder_S);
		pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
		pDrObject->SetCurveType_S(m_CurveType_S);
		pDrObject->SetClosed_S(m_bClosed_S);
	}
	else
	{
		pDrObject->SetOrder_S(2);							// k = LINEAR for Loft
		pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
		pDrObject->SetCurveType_S(CP_LINEAR);				// k = LINEAR for Loft
		pDrObject->SetClosed_S(FALSE);						// k = LINEAR for Loft
	}
	////////////////////
	if(m_bTdirByControl)
	{
		pDrObject->SetOrder_T(m_nOrder_T);
		pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
		pDrObject->SetCurveType_T(m_CurveType_T);
		pDrObject->SetClosed_T(m_bClosed_T);
	}
	else
	{
		pDrObject->SetOrder_T(2);							// k = LINEAR for Loft
		pDrObject->SetCurveType_T(CP_LINEAR);				// k = LINEAR for Loft
		pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
		pDrObject->SetClosed_T(FALSE);						// k = LINEAR for Loft
	}
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	/////////////////////////////////
	for(int i=0;i<4;i++)
		pDrObject->SetCurveLatch(m_CuLatch[i],i);
	////////////////////////////////////////////////////////////////////// Reciprocate
	pDrObject->GetCurveList()->RemoveAll();
	CDrCurve* pDrCurve;
	int index;
	//////////////////////////////////////
	pDrCurve	= m_pCurve_S[0];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[1];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[2];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
	pDrCurve	= m_pCurve_S[3];
	/////////////////////////////////////////////// Detach, if already there
	index		= pDrCurve->GetPatchList()->GetObjectIndex(pDrObject);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////////////////////////////////////
//	pDrObject->SetSegs(m_nSegs);
//	pDrObject->SetPatchType(PA_DUCT);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_T(PA_HORNER);		// Output Method
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 

void CMP_CoonP::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_CoonP:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_CoonP:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
